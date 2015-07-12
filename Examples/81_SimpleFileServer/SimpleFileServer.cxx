///***************************************************************************
// MUSiiC Laboratory
// Hyun Jae Kang, Emad M Boctor
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
This an example is about FakeRFServer.

***************************************************************************/

//#include <MUSiiCIGTLUtil.h>
//#include <io.h>
//#include <direct.h>
//#include <MUSiiCIGTLFileIO.h>

#include <io.h>
#include <stdio.h>
#include <direct.h>
#include <MUSiiCIGTLFileIO.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <vector>

#include <MUSiiCTCPServer.h>
#include <MUSiiCIGTLUtil.h>



using namespace igtl;
////////////////////////////
/// Global Variables

int index;
///////////////////////////////

std::vector<igtl::MessageBase::Pointer> g_MemoryBuffer;
int  gFrameRate;
bool gShowSendingData;
bool gShowSendingFPS;
igtl::MUSiiCProfile gProfile;
//igtl::MUSiiCIGTLMsgFileIO::Pointer g_pFileIO;

igtl::MUSiiCTCPServer::Pointer g_pServer;

//// User defined Callback function
/// Declare a function that is called MUSiiCCallbackInterface
int PreCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
{
	if(taskInfo == M_TCP_DATA_SENT && gShowSendingFPS)
		std::cout << "FPS of Data-Sending is " << gProfile.GetFPS() << std::endl;
	
	if(taskInfo == M_TCP_DATA_SENT && !gShowSendingData)
		return 0;


	std::cout << igtl::GetMUSiiCTCPServerMessage(numOfRun, taskInfo, ptr, data1, data2, data3) << std::endl;
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
	//std::cout << "04. Show Sending Data : Press 'd'" << std::endl;
	std::cout << "05. Set Frame Rate    : Press 'f'" << std::endl;
	//std::cout << "06. Show Frame Rate   : Press 'p'" << std::endl;
	std::cout << "*********************************" << std::endl;
	std::cout << std::endl;
	/////////////////////////////
}


int CheckDirectory(std::string dir_path)
{

	std::cout <<"CheckDirectory::File Path :: " << dir_path << std::endl;
	/// Check destination Directory
	struct stat status;

    if ( access( dir_path.c_str(), 0 ) == 0 )
    {
      struct stat status;
      stat( dir_path.c_str(), &status );

      if ( status.st_mode & S_IFDIR )
      {
         std::cout << "The directory exists." << std::endl;
      }
      else
      {
         std::cout << "The path you entered is a file." << std::endl;
      }
	}
	else
	{
      std::cout << "Path doesn't exist." << std::endl;
	  return 0;
	}

}

int LoadIGTLFiles(std::string path)
{
	igtl::MUSiiCIGTLMsgFileIO::Pointer pFileIO = igtl::MUSiiCIGTLMsgFileIO::New();

	struct _finddata_t	c_file;
	intptr_t			hFile;

	_chdir(path.c_str());

	std::cout <<"LoadIGTLFiles::File Path  :: " << path << std::endl;

	////check source directory
	//if (CheckDirectory(path) <1)
	//{
	//	std::cout << "Source directory does not exist" << std::endl;
	//	return 0;
	//}
	//else
	//	std::cout << "Source directory exists" << std::endl;

	if((hFile = _findfirst("*.igtl", &c_file)) == -1L)
		return false;
	else
	{
		do{
			std::string filename, num;
			std::string pathF;
			filename = c_file.name;
			printf("File name is %s\n", c_file.name);
			igtl::MessageBase::Pointer msg = pFileIO->ReadSingleFile(filename.c_str());
			
			g_MemoryBuffer.push_back(msg);
			
			/*if(strcmp(msg->GetDeviceType(), "IMAGE") == 0)
			{
				
				igtl::ImageMessage::Pointer img = igtl::RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(msg);
				if(img->GetScalarType() == igtl::ImageMessage::TYPE_UINT8)
				{
					std::string IMG_Path =".bmp";
					IMG_Path = filename+IMG_Path;
					int x, y, z;
					img->GetDimensions(x,y,z);
					writeBitmap(IMG_Path.c_str(), (unsigned char*)img->GetScalarPointer(),x,y,32);

					printf("Index:%d :: igtl file of %s saved as BMP Image\n", index, filename.c_str());
				}
				else
				{
					std::cout << "ImageMessage does not have 8bit image data" << std::endl;
				}
			}
			else
			{
				printf("Index:%d :: igtl file of %s is not image Data\n", index, filename.c_str());
			}*/

			index++;
	

		}while(_findnext(hFile, &c_file) ==0);
		_findclose(hFile);
	}
}

int SendLoadedIGTLMessage()
{
	if(g_pServer->IsConnectedClients()) ///&& bSending)
	{
		int sz(g_MemoryBuffer.size());
		for (int i=0; i< sz ; i++)
		{
			g_pServer->PutIGTLMessage(g_MemoryBuffer[i]);
			igtl::Sleep(gFrameRate);
			std::cout << "Sending Message" << i << std::endl;
		}

		return sz;
	}

	return 0;

}

int main(int argc, char** argv)
{
	
	if (argc != 3) // check number of arguments
	{
		// If not correct, print usage
		std::cerr << "Usage::   SimpleFileServer.exe server_port Src_Dir "  << std::endl;
		std::cerr << "Example:: SimpleFileServer.exe 1234 C:/IGTLData/ "  << std::endl;
		exit(0);
	}


	int    port     = atoi(argv[1]);

	std::string src_Path = argv[2];
	index = 0;

	std::cout <<"File Path" << src_Path << std::endl;


	
	char c;
	int r(0);
	bool bTask(true);
	
	/// Initialize the global memory buffer
	g_MemoryBuffer.clear();

	////////////////////////////////////
	/// 01. Create a pointer of MUSiiCTCPServer
	g_pServer = igtl::MUSiiCTCPServer::New();
	g_pServer->AddExternalGlobalInputCallbackFunction(PreCallback, "PreCallbackFunction");
	g_pServer->AddExternalGlobalOutputCallbackFunction(PostCallback, "PostCallbackFunction");
	/// 02. Creater Server Socket
	r = g_pServer->CreateServer(port);
	

	LoadIGTLFiles(src_Path);

	if(g_MemoryBuffer.size()>0)
		std::cout << g_MemoryBuffer.size() << " Files are loaded ^^ " << std::endl;
	else
		std::cout  << " No File are loaded ^^ " << std::endl;

	bool bSending(false);
	bool bSendingUS(true);
	bool bSendingIMAGE(false);
	bool bSendingSTRING(false);
	bool bSendingEI(false);
	gShowSendingData = false;
	gFrameRate = 1;
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
				SendLoadedIGTLMessage();
			/*else if(c == 't')
				bSending = false;*/
			/*else if(c == 'd')
				gShowSendingData = !gShowSendingData;
			else if(c == 'h')
				gShowSendingData = false;*/
			else if(c == 'f')
				SetFrameRate();
			else if(c == 'p')
				gShowSendingFPS=!gShowSendingFPS;

		}
		
	}

	/// Close MUSiiCServerSocket
	g_pServer->CloseServer();
	g_MemoryBuffer.clear();

	return 0;


}