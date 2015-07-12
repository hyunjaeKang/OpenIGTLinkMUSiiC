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
#include <MUSiiCConfigureMUSiiCSync.h>


igtl::MUSiiCTCPClient::Pointer	gpClient;
igtl::MUSiiCTCPServer::Pointer	gpRFServer;
igtl::MUSiiCTCPServer::Pointer	gpBmodeServer;
igtl::MUSiiCSync::Pointer		gpSync; 

igtl::MUSiiCConfigureMUSiiCSync::Pointer gpConfigSync;


int CheckPreConfigure();
bool bClientConnected;

void PrintMenu()
{
	////////////////////////////////
	std::cout << std::endl;
	std::cout << "*********************************" << std::endl;
	std::cout << "********** How to use ***********" << std::endl;
	std::cout << "01. Show Menu         : Press 'm'" << std::endl;
	std::cout << "02. Quit this program : Press 'q'" << std::endl;
	if(!bClientConnected)
		std::cout << "03. Connect to Host   : Press 'c'" << std::endl;
	std::cout << "*********************************" << std::endl;
	std::cout << std::endl;
	/////////////////////////////
}

/// Declare a function that is called MUSiiCCallbackInterface
int SyncPreCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
{
	return 0;
}



/// Declare a function that is called MUSiiCCallbackInterface
int SyncPostCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
{
	return 0;
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

int ConnectToHostXML()
{
	if(bClientConnected)
	{
		std::cout << "All Clients already are connected" << std::endl;
		return 1;
	}
	int sz(gpConfigSync->m_VTCPClient_Info.size());

	gpClient->SetEnalbePreInputCheckDeviceType(true);
	gpClient->SetEnalbePreOutputCheckDeviceType(true);
	gpClient->SetEnalbePostInputCheckDeviceType(true);
	gpClient->SetEnalbePostOutputCheckDeviceType(true);
	
	//gpRFServer->SetEn
	for(int i=0; i<sz;i++)
	{
		gpClient->ConnectToHost(gpConfigSync->m_VTCPClient_Info[i].ip.c_str(), 
								gpConfigSync->m_VTCPClient_Info[i].port, 
								gpConfigSync->m_VTCPClient_Info[i].filter, 
								gpConfigSync->m_VTCPClient_Info[i].sync,
								gpConfigSync->m_VTCPClient_Info[i].referenceData, 
								gpConfigSync->m_VTCPClient_Info[i].reconnect); 

		igtl::Sleep(100);
	}

	bClientConnected = true;
	return sz;
}

int CreateServer()	
{
	if(gpRFServer.IsNull())
	{
		std::cout << "The pointer of MUSiiCTCPServer is NULL" << std::endl;
		return 0;
	}

	if(gpBmodeServer.IsNull())
	{
		std::cout << "The pointer of MUSiiCTCPServer is NULL" << std::endl;
		return 0;
	}

	int sz(gpConfigSync->m_VTCPServer_Info.size());
	if(sz != 2)
	{
		std::cout << "We need two Server socket" << std::endl;
		return 0;
	}

	gpRFServer->SetEnalbePreInputCheckDeviceType(false);
	gpRFServer->SetEnalbePreOutputCheckDeviceType(false);
	gpRFServer->SetEnalbePostInputCheckDeviceType(false);
	gpRFServer->SetEnalbePostOutputCheckDeviceType(false);

	gpBmodeServer->SetEnalbePreInputCheckDeviceType(false);
	gpBmodeServer->SetEnalbePreOutputCheckDeviceType(false);
	gpBmodeServer->SetEnalbePostInputCheckDeviceType(false);
	gpBmodeServer->SetEnalbePostOutputCheckDeviceType(false);

	int r(0);
	for(int i=0; i<2; i++)
	{
		if(gpConfigSync->m_VTCPServer_Info[i].description.find("RF") != std::string::npos)
		{
			gpRFServer->ResetPreInputMUSiiCIOFilter();
			gpRFServer->SetPreInputMUSiiCIOFilterData("MD_US");
			gpRFServer->SetPreInputMUSiiCIOFilterData(IGTL_TRACKING,false);
			gpRFServer->SetEnalbePreInputCheckDeviceType(false);
			gpRFServer->SetEnalbePostOutputCheckDeviceType(false);
			gpRFServer->CreateServer(gpConfigSync->m_VTCPServer_Info[i].port);
			r++;
		}
		else
		{
			gpBmodeServer->ResetPreInputMUSiiCIOFilter();
			gpBmodeServer->SetPreInputMUSiiCIOFilterData("MD_BMODE");
			gpBmodeServer->SetPreInputMUSiiCIOFilterData(IGTL_TRACKING,false);
			gpBmodeServer->SetEnalbePreInputCheckDeviceType(false);
			gpBmodeServer->SetEnalbePostOutputCheckDeviceType(false);
			gpBmodeServer->CreateServer(gpConfigSync->m_VTCPServer_Info[i].port);
			r++;
		}
	}

	//if(r == 1 && gpSync.IsNotNull())
	if(r == 2 && gpSync.IsNotNull())
		r += gpSync->RunMUSiiCSync();

	return r;
}

int RedefinePreConfigure()
{
	std::cout << "-----------------------------------------" << std::endl;
	std::cout << "Which part do you want to change ? (0-2) " << std::endl;
	std::cout << "Option 0: MUSiiCTCPServer of this module " << std::endl;
	std::cout << "Option 1: MUSiiCTCPClient of this module " << std::endl;
	std::cout << "Option 2: Control parameters of this module " << std::endl;
	std::cout << "-----------------------------------------" << std::endl;

	int input;
	std::cin >> input;

	switch(input)
	{
	case 0:
		gpConfigSync->ReDefineTCPServerMUSiiCConfigure();
		break;
	case 1:
		gpConfigSync->ReDefineTCPClientMUSiiCConfigure();
		break;
	case 2:
		//gpConfigSync->ReDefineControlParameters();
		std::cout << "There is no control parameters in MUSiiCSync" <<std::endl;
		break;
	}

	gpConfigSync->UpdateXMLFile();
	return CheckPreConfigure();

}

int CheckPreConfigure()
{
	int r(0);
	if(gpConfigSync.IsNull())
	{
		std::cout << "The pointer of MUSiiCConfigureTrackerServer is NULL" << std::endl;
		return r;
	}

	r += gpConfigSync->PrintMouldeNetworkSetting();
	r += gpConfigSync->PrintModuleControlParameters();

	std::cout << "Do you want to use this setting values (y/n) " << std::endl;

	std::string tempInput;
	std::cin >> tempInput;

	
	if(igtl::YesNO_To_bool(tempInput))
	{
		r += CreateServer();
	}
	else
		r = RedefinePreConfigure();

	return r;
}
/////////////////////////////////////////////////////////////////////////////////////////////
int ReadCalibrationFile(const char *CalibrationFN, igtl::Matrix4x4& CalibM, double &Sx, double &Sy)
{
	/*
	  0  1  2  3 
	  4  5  6  7
	  8  9  10 11
	  12 13 14 15
	*/
	std::ifstream CalibrationFile( CalibrationFN, std::ios::in );

	if( !CalibrationFile.is_open() )
	{
		Sx = Sy = 1;
		for (int i=0;i<4;i++) 
			for(int j=0; j<4; j++)
				CalibM[i][j]=0;
		CalibM[0][0] = CalibM[1][1] = CalibM[2][2] = CalibM[3][3] = 1;
		return -1;
	}

	std::string str;

	CalibrationFile.ignore(256, '#');
	CalibrationFile.ignore(256, '\n');

	double Tx, Ty, Tz, aa, bb, cc;
	CalibrationFile >> Sx >> Sy >> Tx >> Ty >> Tz >> aa >> bb >> cc;

	double Ca = cos(aa);
	double Sa = sin(aa);
	double Cb = cos(bb);
	double Sb = sin(bb);
	double Cc = cos(cc);
	double Sc = sin(cc);

	CalibM[0][0] = Ca*Cb;				//0
	CalibM[0][1] = Ca*Sb*Sc-Sa*Cc;		//1
	CalibM[0][2] = Ca*Sb*Cc+Sa*Sc;		//2
	CalibM[0][3] = Tx;					//3

	CalibM[1][0] = Sa*Cb;				//4
	CalibM[1][1] = Sa*Sb*Sc+Ca*Cc;		//5
	CalibM[1][2] = Sa*Sb*Cc-Ca*Sc;		//6
	CalibM[1][3] = Ty;					//7

	CalibM[2][0] = -Sb;					//8
	CalibM[2][1] = Cb*Sc;				//9
	CalibM[2][2] = Cb*Cc;				//10
	CalibM[2][3] = Tz;					//11

	CalibM[3][0] = 0;					//12
	CalibM[3][1] = 0;					//13
	CalibM[3][2] = 0;					//14
	CalibM[3][3] = 1;					//15

	return 0;
}

int ReadCalibrationFile2(const char *CalibrationFN, igtl::Matrix4x4& CalibM)//, double &Sx, double &Sy)
{
	/*
	  0  1  2  3 
	  4  5  6  7
	  8  9  10 11
	  12 13 14 15
	*/
	std::ifstream CalibrationFile( CalibrationFN, std::ios::in );

	if( !CalibrationFile.is_open() )
	{
		//Sx = Sy = 1;
		for (int i=0;i<4;i++) 
			for(int j=0; j<4; j++)
				CalibM[i][j]=0;
		CalibM[0][0] = CalibM[1][1] = CalibM[2][2] = CalibM[3][3] = 1;
		return -1;
	}

	std::string str;

	CalibrationFile.ignore(256, '#');
	CalibrationFile.ignore(256, '\n');

	double d11, d12, d13, d14;
	double d21, d22, d23, d24;
	double d31, d32, d33, d34;
	double d41, d42, d43, d44;

	CalibrationFile >> d11 >> d12 >> d13 >> d14;// >> Tz >> aa >> bb >> cc;
	CalibrationFile >> d21 >> d22 >> d23 >> d24;//
	CalibrationFile >> d31 >> d32 >> d33 >> d34;//
	CalibrationFile >> d41 >> d42 >> d43 >> d44;//


	CalibM[0][0] = d11;				//0
	CalibM[0][1] = d12;		//1
	CalibM[0][2] = d13;		//2
	CalibM[0][3] = d14;					//3

	CalibM[1][0] = d21;				//4
	CalibM[1][1] = d22;		//5
	CalibM[1][2] = d23;		//6
	CalibM[1][3] = d24;					//7

	CalibM[2][0] = d31;					//8
	CalibM[2][1] = d32;				//9
	CalibM[2][2] = d33;				//10
	CalibM[2][3] = d34;					//11

	CalibM[3][0] = d41;					//12
	CalibM[3][1] = d42;					//13
	CalibM[3][2] = d43;					//14
	CalibM[3][3] = d44;					//15

	return 1;
}

int main(int argc, char** argv)
{
	bClientConnected	= false;
	gpClient		= igtl::MUSiiCTCPClient::New();
	gpRFServer		= igtl::MUSiiCTCPServer::New();
	gpBmodeServer	= igtl::MUSiiCTCPServer::New();
	gpConfigSync	= igtl::MUSiiCConfigureMUSiiCSync::New();
	
	/// Creater the pointer of MUSiiCSync
	gpSync= igtl::MUSiiCSync::New();
	gpSync->AddExternalGlobalInputCallbackFunction(SyncPreCallback, "SyncPreCallback");
	gpSync->AddExternalGlobalOutputCallbackFunction(SyncPostCallback, "SyncPostCallback");

	
	
	/// Connect MUSiiCSync to MUSiiCTCPClient as post-MUSiiCTaskInterface
	gpClient->AddPostMUSiiCTaskInterface<igtl::MessageBase::Pointer, igtl::MessageBase::Pointer>(gpSync);
	//pClient->AddPostMUSiiCIGTLTask(pSync->GetMUSiiCIGTLTaskPointer());
	/// Connect MUSiiCTCPServer to MUSiiCSync as post-MUSiiCTaskInterface
	gpSync->AddPostMUSiiCTaskInterface<igtl::MessageBase::Pointer, igtl::MessageBase::Pointer>(gpRFServer);
	/// Connect MUSiiCTCPServer to MUSiiCSync as post-MUSiiCTaskInterface
	gpSync->AddPostMUSiiCTaskInterface<igtl::MessageBase::Pointer, igtl::MessageBase::Pointer>(gpBmodeServer);
	
	/////////////////////////////////////////////////////////////////////
	if (argc != 3) // check number of arguments
    {
		// If not correct, print usage
		std::cerr << "Usage: " << argv[0] << " XML_Configuration file path " << "Calibration file path "<<std::endl;
		return 0;
    }
	
	std::string xmlfilename = argv[1];//"New_Config.xml";
	std::string calfilename = argv[2];

	//std::string filename = "New_Config.xml";
	gpConfigSync->LoadPreDefineSettingsFromXML(xmlfilename);
	igtl::Matrix4x4 calib;
	double Sx =0.0;
	double Sy =0.0;
	//ReadCalibrationFile(calfilename.c_str(), calib, Sx, Sy);
	ReadCalibrationFile2(calfilename.c_str(), calib);
	gpSync->SetCalibrationData(calib);
	/////////////////////////////////////////////////////////////////////
	CheckPreConfigure();
	
	PrintMenu();
	/////////////////////////////////////////////////////////////////////
	// Prepare MUSiiCSync Structure
	
	///////////////////////////////////////////////////////////////////////
	///// Initialize variables
	bool bTask(true);
	char c;
	//int port = 12345;

	///////////////////////////////////////////////////////////////////////
	///// Starting Task
	//pServer->CreateServer(port);
	//pSync->RunMUSiiCSync();

	////////////////////////////////////////////////////////////////////////
	////// Task Function
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
				//ConnectToHost();
				ConnectToHostXML();
			
		}
		
		/// Sending Data
		
	}

	///// Please check the order 
	gpClient->CloseAllClients();
	gpSync->StopTask();
	gpRFServer->CloseServer();
	gpBmodeServer->CloseServer();

	return 0;
}