///***************************************************************************
//Copyright May/2011
//MUSiiC Laboratory
//Hyun-Jae Kang, Philipp J Stolka,Emad M Boctor
//Johns Hopkins Medical Institutions
//Department of Radiology, Division of Medical Imaging Physics
//
//For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.
//***************************************************************************/

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <stdexcept>
#include <time.h>
#include <MUSiiCProfile.h>


#include <igtlImageMessage.h>
#include <MUSiiCVector.h>
#include <igtlUnit.h>
#include "igtlOSUtil.h"
#include <MUSiiCTaskInterfaceAbstract.h>

#include <MUSiiCTCPServerSocketWin.h>

#include "MUSiiCVectorSet.h"

#include <igtlLightObject.h>
#include <igtlMacro.h>
#include <igtlObjectFactory.h>
#include "igtlM_win32header.h"
#include "MUSiiCUtil.h"

#include <MUSiiCTCPClientSocketWin.h>
#include <map>

using namespace igtl;

#define M_REF_DATA "_M_REF_"

int main(int argc, char** argv)
{
	
	
	igtl::StringMessage::Pointer stMsg = igtl::StringMessage::New();
	stMsg->SetDeviceName("M_StringMessage");
	std::string device(stMsg->GetDeviceName());
	std::string REF("_M_REF_");

	std::cerr << "Before  **************************" << std::endl;
	std::cerr << "Before  " << stMsg->GetDeviceName() << std::endl;
	int rs = device.find(REF);
	std::cerr << "Check Reference Data" << std::endl;
	std::cerr << "The result of Find is " << rs<< std::endl;
	
	if( rs != std::string::npos)
		std::cerr << "This is a Reference Data   ^^" << std::endl;
	else
		std::cerr << "This is not a Reference Data UU" << std::endl;
	std::cerr << "Before  **************************" << std::endl;
	
	
	
	device += REF;
	stMsg->SetDeviceName(device.c_str());
	std::cerr << "After  **************************" << std::endl;
	std::cerr << "After  " << stMsg->GetDeviceName() << std::endl;
	std::string device2(stMsg->GetDeviceName());
	
	//rs = device2.find(REF); //M_REF_DATA
	rs = device2.find(M_REF_DATA); //M_REF_DATA
	std::cerr << "Check Reference Data" << std::endl;
	std::cerr << "The result of Find is " << rs<< std::endl;

	if( rs != std::string::npos)
		std::cerr << "This is a Reference Data   ^^" << std::endl;
	else
		std::cerr << "This is not a Reference Data UU" << std::endl;
	std::cerr << "After  **************************" << std::endl;
	
	
	////std::string device(stMsg->GetDeviceName());
	//strcat((char*)stMsg->GetDeviceName(), "M_REF");
	///*char* REF = "M_REF_";
	//strcat(REF,(char*)stMsg->GetDeviceName());*/
	//std::cerr << "After  " << stMsg->GetDeviceName() << std::endl;
	//char* testC = "M_REF_HELLO";
 ////
	////int r = strncmp(stMsg->GetDeviceName(), "M_REF_", 200) ;
	//int r = strncmp(testC, "M_REF_", 5) ;
	/////*{
	////	std::cerr<< "This data is Reference Data" <<std::endl;
	////}
	////*/

	

	std::map<std::string, std::vector<int>> MUSiiCSyncDataSet;

	
	MUSiiCSyncDataSet["IMAGE"].push_back(0);
	MUSiiCSyncDataSet["IMAGE"].push_back(1);
	MUSiiCSyncDataSet["IMAGE"].push_back(2);

	MUSiiCSyncDataSet["String"].push_back(100);
	MUSiiCSyncDataSet["String"].push_back(100);
	MUSiiCSyncDataSet["String"].push_back(100);
	MUSiiCSyncDataSet["String"].push_back(100);

	std::string str = "MUSiiCData";

	MUSiiCSyncDataSet[str].push_back(1000);
	MUSiiCSyncDataSet[str].push_back(1001);
	MUSiiCSyncDataSet[str].push_back(1002);

	
	char* stringchar = "MUSiiCImageData";

	MUSiiCSyncDataSet[stringchar].push_back(9000);
	MUSiiCSyncDataSet[stringchar].push_back(9001);
	MUSiiCSyncDataSet[stringchar].push_back(9002);
	
	std::map<std::string, std::vector<int>>::iterator it;
	for(it = MUSiiCSyncDataSet.begin(); it!= MUSiiCSyncDataSet.end(); it++)
	{
		int s(it->second.size());
		std::cerr << "The Size of " << it->first <<"  :" << s << std::endl;
		std::cerr << "---------------------------------------------------------" << std::endl;

		for(int i=0; i < s; i++)
			std::cerr << "****** The value is ::  " << it->second[i] <<std::endl;
	}
	
	std::map<std::string, std::vector<int>> MUSiiCSyncDataSet2;

	MUSiiCSyncDataSet2 = MUSiiCSyncDataSet;

	//std::map<std::string, std::vector<int>>::iterator it;
	for(it = MUSiiCSyncDataSet2.begin(); it!= MUSiiCSyncDataSet2.end(); it++)
	{
		int s(it->second.size());
		std::cerr << "The Size of " << it->first <<"  :" << s << std::endl;
		std::cerr << "---------------------------------------------------------" << std::endl;

		for(int i=0; i < s; i++)
			std::cerr << "****** The value is ::  " << it->second[i] <<std::endl;
	}


	std::map<std::string, bool> TestFilter;

	TestFilter["KHJ"] = true;
	std::cerr << "The value of KHJ is " << TestFilter["KHJ"] << std::endl;
	TestFilter["KHJ1"] = false;
	std::cerr << TestFilter.find("KHJ1")->first << std::endl;
	std::cerr << TestFilter.find("KHJ1")->second << std::endl;


//	std::map<std::string , int> MUSiiCIOFilter;

//	MUSiiCIOFilter["IMAGE"]= 10;
//	MUSiiCIOFilter["USMessge"];//= true;
//	MUSiiCIOFilter["USMessge"] = 10;//= true;
//
//	MUSiiCIOFilter["USMessge"] = 100;//= true;
//	MUSiiCIOFilter["USMessge"];//= true;
//
//	std::cerr << "The value of IMAGE is " << MUSiiCIOFilter["IMAGE"] << std::endl;
//	std::cerr << "The value of USMessge is " << MUSiiCIOFilter["USMessge"] << std::endl;
////	std::cerr << "The value of Messge is " << MUSiiCIOFilter["Messge"] << std::endl;
//	std::cerr << "The value is " << MUSiiCIOFilter.find("IMAGE")->first << std::endl;
//	std::cerr << "The value is " << MUSiiCIOFilter.find("IMAGE")->second << std::endl;
//
//	std::cerr << "The value of KHJ is " << MUSiiCIOFilter["KHJ"] << std::endl;
//	std::cerr << "The value of KHJ is " << MUSiiCIOFilter.find("KHJ")->second << std::endl;
//
//	if(MUSiiCIOFilter.find("Messge") == MUSiiCIOFilter.end())
//	{
//		std::cerr << "There is no Data in the map" << std::endl;
//	}
//	else
//	{
//		std::cerr << "Here is the Data in the map" << std::endl;
//		std::cerr << "The value is " << MUSiiCIOFilter["IMAGE"] << std::endl;
//		std::cerr << "The value is " << MUSiiCIOFilter.find("IMAGE")->first << std::endl;
//		std::cerr << "The value is " << MUSiiCIOFilter.find("IMAGE")->second << std::endl;
//	}


	bool r0(false);
	bool r2(true);

	std::cerr << r0 << std::endl;
	std::cerr << r2 << std::endl;
	return 0;
	
	
	/*igtl::MUSiiCTCPClientSocketWin::Pointer pClientSocket;
	pClientSocket = igtl::MUSiiCTCPClientSocketWin::New();

	pClientSocket->ConnectToHost("127.0.0.1", 12345);

	pClientSocket->WaitTask();

	return 1;*/
	
	
	//igtl::MUSiiCTCPServerSocketWin::Pointer pServerSocket;
	//pServerSocket = igtl::MUSiiCTCPServerSocketWin::New();

	//pServerSocket->CreateServer(12345);
	//
	//printf("Hello\n");

	//float a(0.0);
	//while(true)
	//{
	//	
	//	//continue;
	//	if(pServerSocket->IsConnectedClients())// && pServerSocket->GetNumOfClients() >3)
	//	{
	//		int x(128);
	//		int y(1000);
	//		int z(1);
	//		igtl::ImageMessage::Pointer img = igtl::ImageMessage::New();
	//		img->SetDimensions(x, y, z);
	//		img->SetSpacing(1.0,1.0,1.0);
	//		img->SetScalarTypeToUint8();
	//		img->SetDeviceName("Dummy ImageMessage");
	//		img->SetSubVolume(x, y, z, 0,0,0);
	//		img->AllocateScalars();

	//		/*int sz = x*y*z;
	//		*unsigned char* data = new unsigned char [sz];
	//		ZeroMemory(data, sz);
	//		memcpy(img->GetScalarPointer(), data, sz);*/

	//		igtl::Matrix4x4 matrix;
	//		matrix[0][0] = 1.0;  matrix[1][0] = 0.0;  matrix[2][0] = 0.0; matrix[3][0] = 0;
	//		matrix[0][1] = 0.0;  matrix[1][1] = -1.0;  matrix[2][1] = 0.0; matrix[3][1] = 0;
	//		matrix[0][2] = 0.0;  matrix[1][2] = 0.0;  matrix[2][2] = -1.0; matrix[3][2] = 0;
	//		matrix[0][3] = 0.0;  matrix[1][3] = 0.0;  matrix[2][3] = a; matrix[3][3] = 1.0;

	//		//MUSiiC_LOG(logINFO) << "the value of i is  " << a;
	//		a +=0.2;
	//		if(a == 101.0)
	//			a = 0.0;

	//		img->SetMatrix(matrix);
	//		img->Pack();

	//		pServerSocket->PutIGTLMessage((igtl::MessageBase::Pointer)img);

	//		/*MUSiiC_LOG(logINFO) << "MUSiiCServerSocket Send out " << a << "-th ImageMessage";

	//		MUSiiC_LOG(logINFO) << "The size of ImageMessage is  " << img->GetPackSize();*/

	//		//delete data;

	//		igtl::StringMessage::Pointer st = igtl::StringMessage::New();
	//		st->SetDeviceName("Dumy String");
	//		st->SetString("Hello This is Test");
	//		//st->Pack();

	//		pServerSocket->PutIGTLMessage((igtl::MessageBase::Pointer)st);

	//		//MUSiiC_LOG(logINFO) << "The size of StringMessage is  " << st->GetPackSize();
	//	}

	//	igtl::Sleep(20);

	//}

	//


	//pServerSocket->WaitTask();
	//pServerSocket->CloseServer();

	//return 0;

}