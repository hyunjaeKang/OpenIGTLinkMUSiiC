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

#include <iostream>
#include <MUSiiCTCPClient.h>

/// Global function for pre-callback function
int GPreCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
{
	std::cout << "Global-PreCallback function is called" << std::endl;
	std::cout << std::endl;
	return 1;
}

/// Global function for post-callback function
int GPostCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
{
	std::cout << "Global-PostCallback function is called" << std::endl;
	std::cout << std::endl;
	return 1;
}

class LCallbackTest
{
public:
	LCallbackTest()
	{
	}

	~LCallbackTest()
	{
	}

	int LPreCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
	{
		std::cout << "Local-PreCallback function is called" << std::endl;
		std::cout << std::endl;
		return 1;
	}

	int LPostCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
	{
		std::cout << "Local-PostCallback function is called" << std::endl;
		std::cout << std::endl;
		return 1;
	}
};

int main(int argc, char** argv)
{

	igtl::MUSiiCTCPClient::Pointer pClient = igtl::MUSiiCTCPClient::New();
	LCallbackTest callbackObj;


	/// Setting global callback function
	/*pClient->AddExternalGlobalPreCallbackFunction(GPreCallback, "Global_Pre_CB");
	pClient->AddExternalGlobalPostCallbackFunction(GPostCallback, "Global_Post_CB");*/

	/*pClient->AddExternalGlobalInputCallbackFunction(GPreCallback, "Global_Input_CB");
	pClient->AddExternalGlobalOutputCallbackFunction(GPostCallback, "Global_Output_CB");
	*/
	/// Setting local callback function

	pClient->AddExternalLocalPreCallbackFunction(&callbackObj, &LCallbackTest::LPreCallback, "Local Pre CB", 0);
	pClient->AddExternalLocalPostCallbackFunction(&callbackObj, &LCallbackTest::LPreCallback, "Local Post CB", 0);

	/*pClient->AddExternalLocalInputCallbackFunction(&callbackObj, &LCallbackTest::LPreCallback, "Local Input CB");
	pClient->AddExternalLocalOutputCallbackFunction(&callbackObj, &LCallbackTest::LPreCallback, "Local Output CB");*/
	
	pClient->ConnectToHost("127.0.0.1", 1234);
	bool g_bTask;
	g_bTask = true;
	char c;
	while(g_bTask)
	{
		if(igtl::kbhit())
		{
			c = getchar();
			if(c == 'q')
			{
				g_bTask = false;
				break;
			}
		}
	}

	pClient->CloseAllClients();


	return 0;
}