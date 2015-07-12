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
#include <fstream>

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <cstring>

#include <MUSiiCigtlMsgFILEIO.h>
#include <MUSiiCTCPServerUni.h>

#include <MUSiiCSyncDATACollect.h>
#include <MUSiiCSyncDATACombine.h>

int ReadCalibrationFile(char *CalibrationFN, igtl::Matrix4x4& CalibM, double &Sx, double &Sy)
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

int main (int argc, char* argv[])
{
	
	if (argc != 8) // check number of arguments
	{
	// If not correct, print usage
	std::cerr << "    The port number of MUSiiCSync's Server Socket"   << std::endl;
	std::cerr << "    The Calibration File name"   << std::endl;
	std::cerr << "    IP address of US Data " << std::endl;
	std::cerr << "    Port number of US Data" << std::endl;
	std::cerr << "    IP address of Tracking Data " << std::endl;
	std::cerr << "    Port number of Tracking Data" << std::endl;
	std::cerr << "    The index of Tracking Sensor" << std::endl;
	exit(0);
	}

	int	   Sync_ServerSocket = atoi(argv[1]);
	char*  Syn_Calibration = argv[2];          ///////
	
	char*  US_hostname  = argv[3]; ////
	int    US_port      = atoi(argv[4]); ///

	char*  Track_hostname  = argv[5]; ////
	int    Track_port      = atoi(argv[6]); ////

	int    Sensor_Index = atoi(argv[7]); /////
	
	//// Intialize
	igtl::Matrix4x4 calib;
	double S, Y;
	//ReadCalibrationFile("Calibration_AMS.txt", calib, S, Y);
	ReadCalibrationFile(Syn_Calibration, calib, S, Y);

	igtl::MUSiiCTCPClientUni::Pointer RF_Client = igtl::MUSiiCTCPClientUni::New();
	RF_Client->PrepareNetwork();
	RF_Client->SetReferenceDataSocket(false);

	igtl::MUSiiCTCPClientUni::Pointer Tracker_Client = igtl::MUSiiCTCPClientUni::New();
	Tracker_Client->PrepareNetwork();
	Tracker_Client->SetReferenceDataSocket(true);

	igtl::MUSiiCTCPServerUni::Pointer Sync_Server = igtl::MUSiiCTCPServerUni::New();
	Sync_Server->PrepareNetwork();
	
	igtl::MUSiiCVector<igtl::MUSiiCTCPClientUni::Pointer>::Pointer ClientSet;
	ClientSet = igtl::MUSiiCVector<igtl::MUSiiCTCPClientUni::Pointer>::New();
	ClientSet->concurrent_push_back(RF_Client);
	ClientSet->concurrent_push_back(Tracker_Client);

	igtl::MUSiiCVector<igtl::MUSiiCSyncDataSet::Pointer>::Pointer SyncData;
	SyncData = igtl::MUSiiCVector<igtl::MUSiiCSyncDataSet::Pointer>::New();
	
	igtl::MUSiiCSyncDATACollect::Pointer SyncDataCollect = igtl::MUSiiCSyncDATACollect::New();
	SyncDataCollect->SetInputDataInterface(ClientSet);
	SyncDataCollect->SetOutputDataInterface(SyncData);
	SyncDataCollect->AddClientSocket(Tracker_Client);
	SyncDataCollect->AddClientSocket(RF_Client);
	

	igtl::MUSiiCSyncDATACombine::Pointer SyncDataCombine = igtl::MUSiiCSyncDATACombine::New();
	SyncDataCombine->SetInputDataInterface(SyncData);
	SyncDataCombine->SetOutputDataInterface(Sync_Server->GetNetworkBuffer());
	//SyncDataCombine->SetTrackerIndex(1);
	SyncDataCombine->SetTrackerIndex(Sensor_Index);
	SyncDataCombine->SetCalibrationData(calib);

	//Sync_Server->CreateServer(23478);
	Sync_Server->CreateServer(Sync_ServerSocket);
	SyncDataCombine->DataCombine();
	SyncDataCollect->DataCollect();

	/*RF_Client->ConnectToHost("10.162.34.40", 23877);
	Tracker_Client->ConnectToHost("10.162.34.40", 23578);*/

	RF_Client->ConnectToHost(US_hostname, US_port);
	Tracker_Client->ConnectToHost(Track_hostname, Track_port);

	printf("Prees q for quit this program\n");
	char sel;
	//for(;;)
	//{
	//	/*scanf("%c", &sel);

	//	if( sel == 'q')
	//		break;*/
	//	igtl::Sleep(1000);
	//}

	SyncDataCombine->WaitTask();
	SyncDataCollect->WaitTask();
	
	RF_Client->WaitTask();
	Tracker_Client->WaitTask();

	
	
	Sync_Server->CloseServer();
	SyncDataCombine->StopTask();
	SyncDataCollect->StopTask();
}