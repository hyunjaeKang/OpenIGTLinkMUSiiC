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
This a basic example is about how to use SimpleMUSiiCSync.

***************************************************************************/
#include <MUSiiCTCPClient.h>
#include <MUSiiCTCPServer.h>
#include <MUSiiCSync.h>

/// Declare a function that is called MUSiiCCallbackInterface
int PreCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
{
	/*std::cout << "PreCallback Function called!" << std::endl;
	std::cout << std::endl;*/
	return 0;
}



/// Declare a function that is called MUSiiCCallbackInterface
int PostCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
{
	/*std::cout << "PostCallback Function called!" << std::endl;
	std::cout << std::endl;*/
	return 0;
}



/// Declare a function that is called MUSiiCCallbackInterface
int ClientPreCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
{
	/*std::cout << "ClientPreCallback Function called!" << std::endl;
	std::cout << std::endl;*/
	return 0;
}



/// Declare a function that is called MUSiiCCallbackInterface
int ClientPostCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
{
	/*std::cout << "ClientPostCallback Function called!" << std::endl;
	std::cout << std::endl;*/
	return 0;
}

/// Declare a function that is called MUSiiCCallbackInterface
int ServerPreCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
{
	/*std::cout << "ServerPreCallback Function called!" << std::endl;
	std::cout << std::endl;

	std::cout << igtl::GetMUSiiCTCPServerMessage(numOfRun, taskInfo, ptr, data1, data2, data3) << std::endl;
	std::cout << std::endl;*/

	return 0;
}



/// Declare a function that is called MUSiiCCallbackInterface
int ServerPostCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
{
	/*std::cout << "ServerPostCallback Function called!" << std::endl;
	std::cout << std::endl;*/
	return 0;
}

/// Declare a function that is called MUSiiCCallbackInterface
int SyncPreCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
{
	/*std::cout << "SyncPreCallback Function called!" << std::endl;
	std::cout << std::endl;*/
	return 0;
}



/// Declare a function that is called MUSiiCCallbackInterface
int SyncPostCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
{
	/*std::cout << "SyncPostCallback Function called!" << std::endl;
	std::cout << std::endl;*/
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
	std::cout << "*********************************" << std::endl;
	std::cout << std::endl;
	/////////////////////////////
}


int ConnectToHost(igtl::MUSiiCTCPClient::Pointer pClient)
{

	/*return pClient->ConnectToHost("127.0.0.1", 1235, true, "", false); */

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
		return pClient->ConnectToHost(ip.c_str(), port, "", true, reference, true);
	else
	{
		std::cout << "Trying to connect to Host is canceled." << std::endl;
		return -1;
	}

}

int main(int argc, char** argv)
{
	PrintMenu();
	/////////////////////////////////////////////////////////////////////
	// Prepare MUSiiCSync Structure
	
	/// Creater the pointer of MUSiiCTCPClient
	igtl::MUSiiCTCPClient::Pointer pClient = igtl::MUSiiCTCPClient::New();
	pClient->AddExternalGlobalInputCallbackFunction(ClientPreCallback, "ClientPreCallback");
	pClient->AddExternalGlobalOutputCallbackFunction(ClientPostCallback, "ClientPostCallback");
		
	/// Creater the pointer of MUSiiCSync
	igtl::MUSiiCSync::Pointer pSync = igtl::MUSiiCSync::New();
	pSync->AddExternalGlobalInputCallbackFunction(SyncPreCallback, "SyncPreCallback");
	pSync->AddExternalGlobalOutputCallbackFunction(SyncPostCallback, "SyncPostCallback");

	/// Creater the pointer of MUSiiCTCPServer
	igtl::MUSiiCTCPServer::Pointer pServer = igtl::MUSiiCTCPServer::New();
	pServer->AddExternalGlobalInputCallbackFunction(ServerPreCallback, "ServerPreCallback");
	pServer->AddExternalGlobalOutputCallbackFunction(ServerPostCallback, "ServerPostCallback");
	
	/// Connect MUSiiCSync to MUSiiCTCPClient as post-MUSiiCTaskInterface
	pClient->AddPostMUSiiCTaskInterface<igtl::MessageBase::Pointer, igtl::MessageBase::Pointer>(pSync);
	//pClient->AddPostMUSiiCIGTLTask(pSync->GetMUSiiCIGTLTaskPointer());
	/// Connect MUSiiCTCPServer to MUSiiCSync as post-MUSiiCTaskInterface
	pSync->AddPostMUSiiCTaskInterface<igtl::MessageBase::Pointer, igtl::MessageBase::Pointer>(pServer);
	//pSync->AddPostMUSiiCIGTLTask(pServer->GetMUSiiCIGTLTaskPointer());

	/////////////////////////////////////////////////////////////////////
	/// Initialize variables
	bool bTask(true);
	char c;
	int port = 12345;

	/////////////////////////////////////////////////////////////////////
	/// Starting Task
	pServer->CreateServer(port);
	pSync->RunMUSiiCSync();

	//////////////////////////////////////////////////////////////////////
	//// Task Function
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
			
		}
		
		/// Sending Data
		
	}

	/// Please check the order 
	pClient->CloseAllClients();
	pSync->StopTask();
	pServer->CloseServer();

	return 0;
}