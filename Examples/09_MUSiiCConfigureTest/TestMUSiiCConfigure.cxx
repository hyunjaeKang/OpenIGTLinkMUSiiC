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
This a basic example is about how to use MUSiiCConfigure.

01. Create a pointer of MUSiiCConfigure
02. Load XML file
03. Check the information of TCP_Network and control parameters
***************************************************************************/

#include <MUSiiCConfigureRFServer.h>
#include <MUSiiCConfigureMUSiiCEINCC.h>

int main(int argc, char** argv)
{
	
	std::string filename = "New_Config.xml";

	//////////////////////////////////////////////////////////////////////////////////
	igtl::MUSiiCConfigureRFServer::Pointer pRFConf = igtl::MUSiiCConfigureRFServer::New();
	
	pRFConf->LoadPreDefineSettingsFromXML(filename, RF_SERVER);

	pRFConf->PrintXMLElement(pRFConf->GetModuleElement());

	pRFConf->PrintMouldeNetworkSetting();
	////// Modify Control parameters of RF-Server
	pRFConf->Rf_Server_Info.sampling_frequency = 5000000;
	pRFConf->Rf_Server_Info.depth = 40;
	pRFConf->Rf_Server_Info.focus_count = 0;
	
	pRFConf->UpdateXMLFile();
	////////////////////////////////////////////////////
	pRFConf->PrintXMLElement(pRFConf->GetModuleElement());


	///////////////////////////////////////////////////////////////////////////////////////////
	igtl::MUSiiCConfigureMUSiiCEINCC::Pointer pNCCConfig = igtl::MUSiiCConfigureMUSiiCEINCC::New();

	pNCCConfig->LoadPreDefineSettingsFromXML(filename);

	pNCCConfig->PrintMouldeNetworkSetting();
	pNCCConfig->PrintXMLElement(pNCCConfig->GetModuleElement());
	pNCCConfig->PrintModuleControlParameters();

	pNCCConfig->m_MUSiiCEINCCInfo.iWINDOW = 3;
	pNCCConfig->m_MUSiiCEINCCInfo.fCC_THRES = 10.0;
	pNCCConfig->m_MUSiiCEINCCInfo.fDISPLACEMENT = 1000.00;

	pNCCConfig->UpdateXMLFile();

	pNCCConfig->PrintXMLElement(pNCCConfig->GetModuleElement());
	pNCCConfig->PrintModuleControlParameters();






	return 0;
}