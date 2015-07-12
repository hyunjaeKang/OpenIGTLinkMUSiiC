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
This an example is about FakeImageServer.

***************************************************************************/
#include <MUSiiCTCPServer.h>
#include <MUSiiCIGTLUtil.h>

bool gShowSendingData;
bool gShowSendingFPS;
int  gFrameRate;
igtl::MUSiiCProfile gProfile;


igtl::BindMessage::Pointer g_bindMsg1B;
igtl::BindMessage::Pointer g_bindMsg23; 

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


igtl::ImageMessage::Pointer GenerateTestImageMessage(int i)
{
	
	int   size[]     = {256, 256, 1};       // image dimension
    float spacing[]  = {1.0, 1.0, 5.0};     // spacing (mm/pixel)
    int   svsize[]   = {256, 256, 1};       // sub-volume size
    int   svoffset[] = {0, 0, 0};           // sub-volume offset
    int   scalarType = igtl::ImageMessage::TYPE_UINT8;// scalar type

	igtl::ImageMessage::Pointer imgMsg = igtl::ImageMessage::New();
	imgMsg->SetDimensions(size);
    imgMsg->SetSpacing(spacing);
    imgMsg->SetScalarType(scalarType);
    imgMsg->SetDeviceName("ImagerClient");
    imgMsg->SetSubVolume(svsize, svoffset);
    imgMsg->AllocateScalars();

	char filename[128];
	sprintf(filename, "igtlTestImage%d.raw", i+1);
	std::cerr << "Reading " << filename << "..." << std::endl;

	//------------------------------------------------------------
	// Load raw data from the file
	FILE *fp = fopen(filename, "rb");
	if (fp == NULL)
	{
		std::cerr << "File opeining error: " << filename << std::endl;
		return 0;
	}
	
	int fsize = imgMsg->GetImageSize();
	size_t b = fread(imgMsg->GetScalarPointer(), 1, fsize, fp);
	fclose(fp);

	igtl::Matrix4x4 matrix;
	matrix[0][0] = 1.0;  matrix[1][0] = 0.0;  matrix[2][0] = 0.0; matrix[3][0] = 0.0;
	matrix[0][1] = 0.0;  matrix[1][1] = -1.0;  matrix[2][1] = 0.0; matrix[3][1] = 0.0;
	matrix[0][2] = 0.0;  matrix[1][2] = 0.0;  matrix[2][2] = 1.0; matrix[3][2] = 0.0;
	matrix[0][3] = 0.0;  matrix[1][3] = 0.0;  matrix[2][3] = 0.0; matrix[3][3] = 1.0;

	imgMsg->SetMatrix(matrix);
	
	//imgMsg->Pack();
	
	return imgMsg;
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
	PrintMenu();
	/////////////////////////////////////
	char c;
	int r(0);
	bool bTask(true);
	int idx(0);
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
	gFrameRate = 100;
	gShowSendingFPS = false;
	gProfile.SetSampleSizeOfFPS(100);

	g_bindMsg1B = igtl::BindMessage::New();
	g_bindMsg23 = igtl::BindMessage::New();

	
	////
	
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
		

		//igtl::MessageBase::Pointer msg = GetBindImageMessage(idx);
		///*igtl::MessageBase::Pointer msg = igtl::MessageBase::New(); 
	 //   GetBindImageMessage(idx, msg);*/
		//idx++;


		/// Sending Data
		if(pServer->IsConnectedClients()&& bSending)
		{
			
			///////////
			igtl::ImageMessage::Pointer Img1 = igtl::ImageMessage::New();
			Img1 = GenerateTestImageMessage(0);
			Img1->SetDeviceName("FirstImage");
			Img1->Pack();

			/// Create the 2nd Image Message
	
			igtl::ImageMessage::Pointer Img2 = igtl::ImageMessage::New();
			Img2 = GenerateTestImageMessage(1);
			Img2->SetDeviceName("SecondImage");
			Img2->Pack();

			/// Create the 3rd Image Message
	
			igtl::ImageMessage::Pointer Img3 = igtl::ImageMessage::New();
			Img3 = GenerateTestImageMessage(2);
			Img3->SetDeviceName("ThridImage");
			Img3->Pack();

			/// Generate a BindMessage with Image2 and Image3
			igtl::BindMessage::Pointer bindMsg23 = igtl::BindMessage::New();
			//g_bindMsg23 = igtl::BindMessage::New();
			bindMsg23->Init();
			bindMsg23->SetDeviceName("BindMessage_23");
			bindMsg23->AppendChildMessage(Img2);
			bindMsg23->AppendChildMessage(Img3);
			bindMsg23->Pack();

			/// Generate a BindMessage with Image1 and bindMsg23
			igtl::BindMessage::Pointer bindMsg1B = igtl::BindMessage::New();
			//g_bindMsg1B = igtl::BindMessage::New();
			bindMsg1B->Init();
			bindMsg1B->SetDeviceName("BindMessage_1B");
			bindMsg1B->AppendChildMessage(Img1);
			bindMsg1B->AppendChildMessage(bindMsg23);
			
			
			pServer->PutIGTLMessage((igtl::MessageBase::Pointer)bindMsg1B);
			igtl::Sleep(gFrameRate);
			//igtl::Sleep(10);
			idx++;

			if(idx == 10)
			{
				idx = 0;
			}
		}
	}

	/// Close MUSiiCServerSocket
	pServer->CloseServer();
	/// The pointer of MUSiiCTCPServer is automatically deleted when this program is terminated.
	return 0;
}