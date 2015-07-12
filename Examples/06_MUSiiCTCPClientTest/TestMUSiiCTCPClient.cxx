///***************************************************************************
// MUSiiC Laboratory
// Hyun-Jae Kang, Emad M Boctor
//
// Department of Computer Science Department
// Johns Hopkins University
//
// Johns Hopkins Medical Institutions
// Department of Radiology, Division of Medical Imaging Physics
//
// For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.
//***************************************************************************/

/***************************************************************************
This a basic example is about how to use MUSiiCTCPClient.

01. Create a pointer of MUSiiCTCPClient
02. Create Client Socket
03. Check are there any connected clients?
    >> if there are, send data
	>> if not, skip
04. Close Client Socket
***************************************************************************/

#include <MUSiiCTCPClient.h>
bool gShowSendingData;
bool gShowSendingFPS;
int  gFrameRate;
igtl::MUSiiCProfile gProfile;

//// User defined Callback function
/// Declare a function that is called MUSiiCCallbackInterface
int PreCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
{
	std::cout << "PreCallback Function called!" << std::endl;
	return 0;
}

/// Declare a function that is called MUSiiCCallbackInterface
int PostCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
{
	//std::cout << "PostCallback Function called!" << std::endl;
	std::cout << igtl::GetMUSiiCTCPClientMessage(numOfRun, taskInfo, ptr, data1, data2, data3) << std::endl;
	if(taskInfo == M_TCP_DATA_RECEIVED && gShowSendingFPS)
		std::cout << "FPS of Data-Sending is " << gProfile.GetFPS() << std::endl;
	
	if(taskInfo == M_TCP_DATA_RECEIVED && !gShowSendingData)
		return 0;

	std::cout << igtl::GetMUSiiCTCPClientMessage(numOfRun, taskInfo, ptr, data1, data2, data3) << std::endl;

	std::cout << std::endl;
	return 0;
}

void PrintMenu()
{
	////////////////////////////////
	std::cout << std::endl;
	std::cout << "*********************************" << std::endl;
	std::cout << "********** How to use ***********" << std::endl;
	std::cout << "01. Show Menu         : Press 'm'" << std::endl;
	std::cout << "02. Quit this program : Press 'q'" << std::endl;
	std::cout << "03. Connect to Host   : Press 'c'" << std::endl;
	std::cout << "04. Show Sending Data : Press 'd'" << std::endl;
	std::cout << "05. Show Frame Rate   : Press 'p'" << std::endl;
	std::cout << "*********************************" << std::endl;
	std::cout << std::endl;
	/////////////////////////////
}


int ConnectToHost(igtl::MUSiiCTCPClient::Pointer pClient)
{
	std::string ip;
	int port;
	std::string filter;
	bool reference;
	char c;
	std::string temp;
	
	std::cout << std::endl;
	std::cout <<"ConnectToHost" <<std::endl;
	std::cout <<"Enter IP Address of Host"<<std::endl;
	std::cin >> ip;
	////
	std::cout <<"Enter Port Number of Host" <<std::endl;
	std::cin>>port;
	////
	std::cout <<"Enter Data-type of MUSiiCIOFilter" <<std::endl;
	std::cin >> filter;
	////
	std::cout <<"Enter Is Reference socket:: y or n" <<std::endl;
	std::cin >> temp;
	if(temp.compare("y") != std::string::npos)
		reference = true;
	else 
		reference = false;
	////

	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////

	std::cout << "***** Please check your Input Information *****" << std::endl;
	std::cout << "* IP Address of Host  : " << ip << std::endl;
	std::cout << "* Port Number of Host : " << port << std::endl;
	std::cout << "* MUSiiCIOFilter      : " << filter << std::endl;
	
	if(reference)
		temp = "Yes";
	else
		temp = "NO";
	std::cout << "* Reference socket    : " << temp << std::endl;
	
	std::cout << "***** Correct (y/n)?  *****" << std::endl;
	std::cin >> temp;
	if(temp.compare("y") != std::string::npos)
		return pClient->ConnectToHost(ip.c_str(), port, "", false,reference,true);
	else
	{
		std::cout << "Trying to connect to Host is canceled." << std::endl;
		return -1;
	}

	//return pClient->ConnectToHost("127.0.0.1", 12345, true, "", true);
}

int main(int argc, char** argv)
{
	char c;
	int r(0);
	bool bTask(true);
	gShowSendingData = false;
	gShowSendingFPS = false;

	/// 01. Create a pointer of MUSiiCTCPClient
	igtl::MUSiiCTCPClient::Pointer pClient = igtl::MUSiiCTCPClient::New();
	pClient->AddExternalGlobalInputCallbackFunction(PreCallback, "PreCallbackFunction");
	pClient->AddExternalGlobalOutputCallbackFunction(PostCallback, "PostCallbackFunction");

	PrintMenu();
	while(bTask)
	{
		if(igtl::kbhit())
		{
			c = getchar();
			if(c == 'q')
			{
				bTask = false;
				break;
			}
			else if(c == 'm')
				PrintMenu();
			else if(c == 'c')
				ConnectToHost(pClient);
			else if(c == 'd')
				gShowSendingData = !gShowSendingData;
			else if(c == 'p')
				gShowSendingFPS=!gShowSendingFPS;
			
		}
		
	}

	/// Close MUSiiCClientSockets
	pClient->CloseAllClients();
	/// The pointer of MUSiiCTCPClient is automatically deleted when this program is terminated.
	return 0;
}