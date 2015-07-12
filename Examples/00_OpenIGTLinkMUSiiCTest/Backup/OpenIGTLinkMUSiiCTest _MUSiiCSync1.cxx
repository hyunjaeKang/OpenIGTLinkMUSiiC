///***************************************************************************
//Copyright May/2011
//MUSiiC Laboratory
//Hyun-Jae Kang, Philipp J Stolka,Emad M Boctor
//Johns Hopkins Medical Institutions
//Department of Radiology, Division of Medical Imaging Physics
//
//For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.
//***************************************************************************/



//#ifdef _DEBUG
//#define new DEBUG_NEW
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
//#endif
//
//#define malloc DEBUG_MALLOC
//#define DEBUG_MALLOC(size) _malloc_dbg(size, _NORMAL_BLOCK, __FILE__ , __LINE__)





//_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

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


#include "MUSiiCSyncDATA.h"

//// MFC Memory Leak Checking//////////////////
#include <crtdbg.h>

#ifdef _DEBUG
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif

////////////////////////////////////////////



using namespace igtl;
struct SyncDataE
{
	std::map<float, std::string> syncDataE;
};

void PrintIOFilter(std::map<std::string, bool>& iof, std::string des = "")
{
	std::cerr << "Description is :  " << des.c_str() << std::endl;

	std::map<std::string, bool>::iterator it;
	for(it = iof.begin(); it!= iof.end(); it++)
		std::cerr << "Data Type is : " << it->first << "  : the value is : " << it->second << std::endl;


	std::cerr << "" << std::endl;
}

void PrintSyncData(std::map<std::string, SyncDataE>& sysdata, std::string des = " ")
{
	std::cerr << "Description is :  " << des.c_str() << std::endl;
	std::map<std::string, SyncDataE>::iterator it;
	std::map<float,  std::string >::iterator its;

	std::cout << "Size  Of DataSet is   :" << sysdata.size() << std::endl;
	for(it = sysdata.begin(); it!= sysdata.end(); it++)
	{
		std::cout << "The data type :" << it->first << std::endl;
		std::cout << "Size  Of DataEleme is   :" << it->second.syncDataE.size() << std::endl;
		for(its = it->second.syncDataE.begin();its != it->second.syncDataE.end();its++)
			std::cout << "The time difference is : " << its->first << "  and then, the message is " << its->second << std::endl;

		std::cout << std::endl;
	}
}





int main(int argc, char** argv)
{
	
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	/////////////////////////////////////////////
	//std::map<std::string, bool> IOF;

	//IOF[M_2D_Pre_RF] = true;
	//IOF[M_2D_RF] = true;

	//PrintIOFilter(IOF, "Generating IO Filter");
	//
	//IOF.erase(M_3D_RF);
	//PrintIOFilter(IOF, "After Erasing Non-Key element");
	//
	//IOF.erase(M_2D_RF);
	//PrintIOFilter(IOF, "After Erasing M_2D_RF Key");

	//
	////std::map<std::string, std::map<float, std::string>> SyncData;
	//std::map<std::string, SyncDataE> SyncData;
	////SyncData[M_2D_RF] = std::pair<float, std::string>(1.0,"Hello");
	//SyncData[M_2D_RF].syncDataE[0.1] = "Hello";//std::pair<float, std::string>(1.0,"Hello");
	//SyncData[M_2D_RF].syncDataE[0.2] = "Hello2";
	//SyncData[M_2D_RF].syncDataE[0.01] = "Hello3";

	//SyncData[M_3D_RF].syncDataE[0.11] = "3D_RF_1";//std::pair<float, std::string>(1.0,"Hello");
	//SyncData[M_3D_RF].syncDataE[0.02] = "3D_RF_2";
	//SyncData[M_3D_RF].syncDataE[0.001] = "3D_RF_3";

	//PrintSyncData(SyncData, "Testing MUSiiCSyncData");
	//
	//////////////////////////////////////////////////////////////////////

	//std::map<std::string, SyncDataE> SyncData2;
	//SyncData2 = SyncData;

	//

	//std::cout << "Size  Of SyncData is   :" << SyncData.size() << std::endl;
	//std::cout << "Size  Of SyncData2 is   :" << SyncData2.size() << std::endl;


	//{

	//	std::map<std::string, SyncDataE>& SyncData3 = SyncData2;
	//	int aa = 3;
	//	int bb = 5;
	//	double aaa = 7.7;
	//}
	
	
	//// Memory Leak 
	//char* data = new char[300];

	std::cout << "****************** Testing MUSiiCSyncData ****************" << std::endl;
	
	igtl::MUSiiCSyncDataSet::Pointer pMSyncDataSet = igtl::MUSiiCSyncDataSet::New();
	igtl::MUSiiCSyncData::Pointer pMSyncDataPre = igtl::MUSiiCSyncData::New();
	igtl::MUSiiCSyncData::Pointer pMSyncDataPost = igtl::MUSiiCSyncData::New();

	pMSyncDataPost->AddDataIGTLMsg(GetDummyImageMessage());
	pMSyncDataPost->AddDataIGTLMsg(GetDummyImageMessage());
	pMSyncDataPost->AddDataIGTLMsg(GetDummyStringMessage());
	pMSyncDataPost->AddDataIGTLMsg(GetDummyImageMessage());
	pMSyncDataPost->AddDataIGTLMsg(GetDummyStringMessage());
	pMSyncDataPost->AddDataIGTLMsg(GetDummyStringMessage());
	pMSyncDataPost->AddDataIGTLMsg(GetDummyStringMessage());
	pMSyncDataPost->AddDataIGTLMsg(GetDummyStringMessage());

	std::cout <<"=================================================" << std::endl;
	pMSyncDataPost->PrintMUSiiCSyncData("pMSyncDataPost::Getting Data");
	
	
	pMSyncDataPre = pMSyncDataPost;
	std::cout <<"=================================================" << std::endl;
	pMSyncDataPost->PrintMUSiiCSyncData("pMSyncDataPost::Copy operation");
	std::cout <<"=================================================" << std::endl;
	pMSyncDataPre->PrintMUSiiCSyncData("pMSyncDataPre::Copy operation");

	
	
	pMSyncDataSet->AddMUSiiCSyncData(pMSyncDataPre);
	pMSyncDataSet->AddMUSiiCSyncData(pMSyncDataPost);
	std::cout <<"+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
	pMSyncDataSet->PrintMUSiiCSyncDataSet();

	
	pMSyncDataPost = igtl::MUSiiCSyncData::New();
	std::cout <<"=================================================" << std::endl;
	pMSyncDataPost->PrintMUSiiCSyncData("pMSyncDataPost::Re_Generating");
	std::cout <<"=================================================" << std::endl;
	pMSyncDataPre->PrintMUSiiCSyncData("pMSyncDataPre::Re_Generating");


	std::map<std::string , igtl::MUSiiCSyncDataElements>::iterator	ItSyncData;
	ItSyncData = pMSyncDataPre->GetBeginIT();


		




	return 0;

}