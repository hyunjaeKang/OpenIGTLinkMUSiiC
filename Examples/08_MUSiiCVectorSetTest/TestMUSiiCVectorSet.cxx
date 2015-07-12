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
	std::cout << "PostCallback Function called!" << std::endl;
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
	std::string ip;
	int port;
	std::string filter;
	bool reference;

	std::cout << std::endl;
	std::cout <<"ConnectToHost" <<std::endl;
	std::cout <<"Enter IP Address of Host" <<std::endl;
	////
	std::cout <<"Enter Port Number of Host" <<std::endl;
	////
	std::cout <<"Enter Data-type of MUSiiCIOFilter" <<std::endl;
	////
	std::cout <<"Enter Is Reference socket:: y or n" <<std::endl;
	////

	return pClient->ConnectToHost(ip.c_str(), port, filter, false,reference,true);

}

int main(int argc, char** argv)
{
	char c;
	int r(0);
	bool bTask(true);

	/// 01. Create a pointer of MUSiiCTCPClient
	igtl::MUSiiCTCPClient::Pointer pClient = igtl::MUSiiCTCPClient::New();
	pClient->AddExternalGlobalInputCallbackFunction(PreCallback, "PreCallbackFunction");
	pClient->AddExternalGlobalOutputCallbackFunction(PostCallback, "PostCallbackFunction");

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
		
	}

	/// Close MUSiiCClientSockets
	pClient->CloseAllClients();
	/// The pointer of MUSiiCTCPClient is automatically deleted when this program is terminated.
	return 0;
}