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
This an example is about FakeStringIServer.

***************************************************************************/
#include <MUSiiCTCPServer.h>
#include <MUSiiCIGTLUtil.h>

bool gShowSendingData;
bool gShowSendingFPS;
int  gFrameRate;
igtl::MUSiiCProfile gProfile;

//// User defined Callback function
/// Declare a function that is called MUSiiCCallbackInterface
int PreCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
{
	if(taskInfo == M_TCP_DATA_SENT && gShowSendingFPS)
		std::cout << "FPS of Data-Sending is " << gProfile.GetFPS() << std::endl;
	
	if(taskInfo == M_TCP_DATA_SENT && !gShowSendingData)
		return 0;



//	std::cout << "<<<<<< PreCallback Function called!" << std::endl;
	std::cout << igtl::GetMUSiiCTCPServerMessage(numOfRun, taskInfo, ptr, data1, data2, data3) << std::endl;
	//MUSiiC_LOG(logINFO) << igtl::GetMUSiiCTCPServerMessage(numOfRun, taskInfo, ptr, data1, data2, data3);
	std::cout << std::endl;
	return 0;
}

/// Declare a function that is called MUSiiCCallbackInterface
int PostCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
{
	std::cout << "PostCallback Function called!" << std::endl;
	std::cout << std::endl;
	return 0;
}

void SetFrameRate()
{
	std::cout << "Enter frmae rates per second" << std::endl;
	int fps;
	scanf("%d", &fps);
	gFrameRate = 1000/fps;
}

void PrintMenu()
{
	////////////////////////////////
	std::cout << std::endl;
	std::cout << "*********************************" << std::endl;
	std::cout << "****** How to use ***************" << std::endl;
	std::cout << "01. Show Menu         : Press 'm'" << std::endl;
	std::cout << "02. Quit this program : Press 'q'" << std::endl;
	std::cout << "03. Send Data         : Press 's'" << std::endl;
	std::cout << "04. Show Sending Data : Press 'd'" << std::endl;
	std::cout << "05. Set Frame Rate    : Press 'f'" << std::endl;
	std::cout << "06. Show Frame Rate   : Press 'p'" << std::endl;
	std::cout << "*********************************" << std::endl;
	std::cout << std::endl;
	/////////////////////////////
}

using namespace igtl;
int main(int argc, char** argv)
{
	if (argc != 2) // check number of arguments
    {
		// If not correct, print usage
		std::cerr << "Usage: " << argv[0] << " <port>"    << std::endl;
		std::cerr << "<port>     : Port # (18944 in Slicer default)"   << std::endl;
		return 0;
    }

	int    port     = atoi(argv[1]);
	//////////////////////////////////////
	PrintMenu();
	/////////////////////////////////////
	char c;
	int r(0);
	bool bTask(true);
	////////////////////////////////////
	/// 01. Create a pointer of MUSiiCTCPServer
	igtl::MUSiiCTCPServer::Pointer pServer = igtl::MUSiiCTCPServer::New();
	pServer->AddExternalGlobalInputCallbackFunction(PreCallback, "PreCallbackFunction");
	pServer->AddExternalGlobalOutputCallbackFunction(PostCallback, "PostCallbackFunction");
	/// 02. Creater Server Socket
	r = pServer->CreateServer(port);

	bool bSending(false);
	bool bSendingUS(true);
	bool bSendingIMAGE(false);
	bool bSendingSTRING(false);
	bool bSendingEI(false);
	gShowSendingData = false;
	gFrameRate = 30;
	gShowSendingFPS = false;
	gProfile.SetSampleSizeOfFPS(100);
	
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
			else if(c == 's')
				bSending = !bSending;
			else if(c == 'd')
				gShowSendingData = !gShowSendingData;
			else if(c == 'h')
				gShowSendingData = false;
			else if(c == 'f')
				SetFrameRate();
			else if(c == 'p')
				gShowSendingFPS=!gShowSendingFPS;

		}
		
		/// Sending Data
		if(pServer->IsConnectedClients()&& bSending)
		{
			pServer->PutIGTLMessage(GetDummyStringMessage());
			igtl::Sleep(gFrameRate);
		}
	}

	/// Close MUSiiCServerSocket
	pServer->CloseServer();
	/// The pointer of MUSiiCTCPServer is automatically deleted when this program is terminated.
	return 0;
}