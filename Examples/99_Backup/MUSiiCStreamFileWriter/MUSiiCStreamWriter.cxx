/***************************************************************************
Copyright May/2011
MUSiiC Laboratory
Hyun-Jae Kang, Philipp J Stolka,Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

#############################################################################
This example program is showing how to use MUSiiCTaskAbstract class with exteral task function.
***************************************************************************/

#include <stdio.h>
#include <igtlOSUtil.h> //igtl::Sleep
#include <igtlImageMessage.h>

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <cstring>

#include <MUSiiCTCPClientUni.h>
#include <MUSiiCTCPServerUni.h>
#include <MUSiiCigtlMsgFILEIO.h>

class CallbackInfo
{
public:
	CallbackInfo()
	{
		m_bigtlMsgVector = false;
	}
	
	~CallbackInfo()
	{
	}

	bool SetDataInterface(igtl::MUSiiCigtlMsgVector::Pointer msgVector)
	{
		if(msgVector.IsNotNull())
		{
			m_pigtlMsgVector = msgVector;
			m_bigtlMsgVector = true;
		}
		else
			m_bigtlMsgVector = false;

		return m_bigtlMsgVector;

	}

	int Callbackfunction(int numOfRun, int TaskInfo, void* ptr, void* data1, void* data2, void* data3)
	{
		std::string des;
		bool bData = GetDescription(TaskInfo, des, data1);
		printCallbackInfo(des, bData, numOfRun, TaskInfo, ptr, data1, data2, data3);

		return 0;
	}
	
	void printCallbackInfo(std::string description, bool data, int numOfRun, int Taskinfo, void* ptr, void* data1, void* data2, void* data3)
	{
		double t;
		t = *(double*)data2;
		std::string* name = (std::string*) data3;

		printf("\n");
		printf("/// %s ///\n", description.c_str());
		
		if(data)
			printf("index of data: %d, TaskInfo: %d\n", numOfRun, Taskinfo);
		else
			printf("index of client: %d, TaskInfo: %d\n", numOfRun, Taskinfo);
		
		printf("Message: %s\n", name->c_str() );
		printf("timestamp: %f\n", t);
		printf("\n");
		if(!data)
		{
			int s = m_pigtlMsgVector->concurrent_size();
			printf("The size of Data buffer is %d\n", s);
			printf("=============================\n");
		}
		else
		{
		}

	}

	bool GetDescription(int TaskInfo, std::string& des, void* data1)
	{
		bool bData;
		std::string des_temp;
		switch(TaskInfo)
		{
			case igtl::M_TCP_Connected:
				des_temp = "CallbackInfo::TCP Client is connected";
				break;
			case igtl::M_TCP_Connecting:
				des_temp = "CallbackInfo::TCP Client is connecting";
				break;
			case igtl::M_TCP_Disconnected:
				des_temp = "CallbackInfo::TCP Client is disconnected";
				break;
			case igtl::M_TCP_ServerClient_Connected:
				des_temp = "CallbackInfo::TCP Client is connected as server sub socket";
				break;
		}
			
		std::string temp2;
		if(data1 == NULL)
		{
			temp2 = "_ without Data";
			bData = false;
		}
		else 
		{
			temp2 = "_ with Data";
			bData = true;
		}


		des = des_temp +temp2;
		return bData;
				
	}

public:
	igtl::MUSiiCigtlMsgVector::Pointer m_pigtlMsgVector;
	bool m_bigtlMsgVector;
};
int main (int argc, char* argv[])
{	
	//------------------------------------------------------------
	// Parse Arguments

	if (argc != 4) // check number of arguments
	{
	// If not correct, print usage
	std::cerr << "    <hostname> : IP or host name"                    << std::endl;
	std::cerr << "    <port>     : Port # (18944 in Slicer default)"   << std::endl;
	std::cerr << "    prefix of filename : " << std::endl;
	exit(0);
	}

	char*  hostname = argv[1];
	int    port     = atoi(argv[2]);
	char*  pre_fix_filename = argv[3];

	igtl::MUSiiCTCPClientUni::Pointer pClient = igtl::MUSiiCTCPClientUni::New();
	pClient->PrepareNetwork();
	

	igtl::MUSiiCigtlMsgFILEIO::Pointer pIgtlFileIO = igtl::MUSiiCigtlMsgFILEIO::New();

	pIgtlFileIO->SetDataInterface(pClient->GetDataInterface());
	std::string filename(pre_fix_filename);

	pIgtlFileIO->WriteStreamData(filename);

	pClient->ConnectToHost(hostname, port);

	printf("Prees q for quit this program\n");
	char sel;
	for(;;)
	{
		scanf("%c", &sel);

		if( sel == 'q')
			break;
	}
	
	pIgtlFileIO->WriteStreamDataStop();
	pClient->CloseClientSocket();
	
	
	
	//igtl::MUSiiCTCPServerUni::Pointer pServer = igtl::MUSiiCTCPServerUni::New();
	//pServer->PrepareNetwork();

	//CallbackInfo call;

	//////Create the pointer of MUSiiCTCPClientUni
	//igtl::MUSiiCTCPClientUni::Pointer m_pClient;
	//m_pClient = igtl::MUSiiCTCPClientUni::New();
	////// Setting callback function
	//m_pClient->AddExternalLocalCallbackFunction(&call, &CallbackInfo::Callbackfunction);
	//m_pClient->PrepareNetwork();
	//call.SetDataInterface(m_pClient->GetNetworkBuffer());
	//m_pClient->SetClientIndex(2);
	/////Connect
	//int r = m_pClient->ConnectToHost("10.162.34.40", 23978);//2397);//23978);

	////igtl::Sleep(5000);
	//m_pClient->WaitTask();

	//igtl::MUSiiC_TCP_STATUS tcp_status;
	//tcp_status =  m_pClient->GetTCPStatus();
	//
	//switch(tcp_status)
	//{
	//	case igtl::M_TCP_Connected:
	//		printf("Connected\n");
	//		break;
	//	case igtl::M_TCP_Connecting:
	//		printf("Connecting\n");
	//		break;
	//	case igtl::M_TCP_Disconnected:
	//		printf("Disconnected\n");
	//		break;
	//}
	

	return 0;
}