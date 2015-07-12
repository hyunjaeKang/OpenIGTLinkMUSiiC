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

	//char* data = new char[200];


	std::cout << "****************** Testing MUSiiCSyncData ****************" << std::endl;
	
	std::cout <<"***************************************************************" << std::endl;
	std::cout <<"***************************************************************" << std::endl;
	std::cout <<"***************************************************************" << std::endl;

	igtl::MUSiiCSyncDataSet::Pointer pMSyncDataSet = igtl::MUSiiCSyncDataSet::New();
	igtl::MUSiiCSyncData::Pointer pMSyncDataPre = igtl::MUSiiCSyncData::New();
	igtl::MUSiiCSyncData::Pointer pMSyncDataPost = igtl::MUSiiCSyncData::New();

	std::cout <<"Data Collecting Before Reference Data" << std::endl;
	pMSyncDataPre->AddDataIGTLMsg(GetDummyImageMessage());
	pMSyncDataPre->AddDataIGTLMsg(GetDummyImageMessage());
	pMSyncDataPre->AddDataIGTLMsg(GetDummyStringMessage());
	pMSyncDataPre->AddDataIGTLMsg(GetDummyImageMessage());
	pMSyncDataPre->AddDataIGTLMsg(GetDummyStringMessage());
	pMSyncDataPre->AddDataIGTLMsg(GetDummyStringMessage());
	pMSyncDataPre->AddDataIGTLMsg(GetDummyStringMessage());
	pMSyncDataPre->AddDataIGTLMsg(GetDummyStringMessage());
	std::cout <<"=================================================" << std::endl;
	pMSyncDataPre->PrintMUSiiCSyncData("pMSyncDataPre::Data Collecting Before 1-st Reference Data");

	//// 1-st Reference Data
	pMSyncDataSet->SetReferenceIGTLMsg(GetDummyImageMessage());

	pMSyncDataPost->AddDataIGTLMsg(GetDummyImageMessage());
	pMSyncDataPost->AddDataIGTLMsg(GetDummyStringMessage());
	pMSyncDataPost->AddDataIGTLMsg(GetDummyImageMessage());
	std::cout <<"=================================================" << std::endl;
	pMSyncDataPost->PrintMUSiiCSyncData("pMSyncDataPost::Data Collecting After 1-st Reference Data");

	pMSyncDataSet->AddMUSiiCSyncData(pMSyncDataPre);
	pMSyncDataSet->AddMUSiiCSyncData(pMSyncDataPost);
	std::cout <<"+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
	pMSyncDataSet->PrintMUSiiCSyncDataSet("Before Copy");
	pMSyncDataPre = pMSyncDataPost;
	pMSyncDataSet->PrintMUSiiCSyncDataSet("After Copy");

	std::cout <<"***************************************************************" << std::endl;
	std::cout <<"***************************************************************" << std::endl;
	std::cout <<"***************************************************************" << std::endl;
	/////////////////////////////////////////////////////////////////////////////////////////
	//// 2-nd Reference Data
	pMSyncDataSet = igtl::MUSiiCSyncDataSet::New();
	pMSyncDataSet->SetReferenceIGTLMsg(GetDummyImageMessage());
	
	pMSyncDataPost = igtl::MUSiiCSyncData::New();
	pMSyncDataPost->AddDataIGTLMsg(GetDummyImageMessage());
	pMSyncDataPost->AddDataIGTLMsg(GetDummyImageMessage());
	pMSyncDataPost->AddDataIGTLMsg(GetDummyStringMessage());
	pMSyncDataPost->AddDataIGTLMsg(GetDummyImageMessage());
	pMSyncDataPost->AddDataIGTLMsg(GetDummyStringMessage());
	pMSyncDataPost->AddDataIGTLMsg(GetDummyTrackingDataMessage()); ////Check

	std::cout <<"=================================================" << std::endl;
	pMSyncDataPre->PrintMUSiiCSyncData("pMSyncDataPre::Data Collecting After 2nd Reference Data");
	std::cout <<"=================================================" << std::endl;
	pMSyncDataPost->PrintMUSiiCSyncData("pMSyncDataPost::Data Collecting After 2nd Reference Data");

	pMSyncDataSet->AddMUSiiCSyncData(pMSyncDataPre);
	pMSyncDataSet->AddMUSiiCSyncData(pMSyncDataPost);
	std::cout <<"+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
	pMSyncDataSet->PrintMUSiiCSyncDataSet("Before Copy");
	pMSyncDataPre = pMSyncDataPost;
	pMSyncDataSet->PrintMUSiiCSyncDataSet("After Copy");	

	//// 3rd Reference Data
	std::cout <<"***************************************************************" << std::endl;
	std::cout <<"***************************************************************" << std::endl;
	std::cout <<"***************************************************************" << std::endl;
	pMSyncDataSet = igtl::MUSiiCSyncDataSet::New();
	pMSyncDataSet->SetReferenceIGTLMsg(GetDummyImageMessage());
	
	pMSyncDataPost = igtl::MUSiiCSyncData::New();
	pMSyncDataPost->AddDataIGTLMsg(GetDummyImageMessage());
	pMSyncDataPost->AddDataIGTLMsg(GetDummyImageMessage());
	pMSyncDataPost->AddDataIGTLMsg(GetDummyStringMessage());
	pMSyncDataPost->AddDataIGTLMsg(GetDummyImageMessage());
	pMSyncDataPost->AddDataIGTLMsg(GetDummyStringMessage());
	pMSyncDataPost->AddDataIGTLMsg(GetDummyStringMessage());
	pMSyncDataPost->AddDataIGTLMsg(GetDummyStringMessage());
	pMSyncDataPost->AddDataIGTLMsg(GetDummyStringMessage());
	pMSyncDataPost->AddDataIGTLMsg(GetDummyTrackingDataMessage());
	pMSyncDataPost->AddDataIGTLMsg(GetDummyTrackingDataMessage());
	pMSyncDataPost->AddDataIGTLMsg(GetDummyTrackingDataMessage());


	std::cout <<"=================================================" << std::endl;
	pMSyncDataPre->PrintMUSiiCSyncData("pMSyncDataPre::Data Collecting After 3rd Reference Data");
	std::cout <<"=================================================" << std::endl;
	pMSyncDataPost->PrintMUSiiCSyncData("pMSyncDataPost::Data Collecting After 3rd Reference Data");
	pMSyncDataSet->AddMUSiiCSyncData(pMSyncDataPre);
	pMSyncDataSet->AddMUSiiCSyncData(pMSyncDataPost);
	std::cout <<"+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
	pMSyncDataSet->PrintMUSiiCSyncDataSet("Before Copy");
	pMSyncDataPre = pMSyncDataPost;
	pMSyncDataSet->PrintMUSiiCSyncDataSet("After Copy");
	pMSyncDataSet->FindClosestIGTLMsg();
	pMSyncDataSet->PrintClosestIGTLMsg("Testing");
	

	return 0;

}