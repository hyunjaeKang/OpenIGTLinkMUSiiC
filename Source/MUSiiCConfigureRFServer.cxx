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

#include "MUSiiCConfigureRFServer.h"

namespace igtl
{

	
/// Constructor
MUSiiCConfigureRFServer::MUSiiCConfigureRFServer()
{
	m_pNameOfClass="MUSiiCConfigureRFServer";
	Initialize();	
}
	
	/// Deconstructor
MUSiiCConfigureRFServer::~MUSiiCConfigureRFServer()
{
	
}

/// Virtual Function
int MUSiiCConfigureRFServer::LoadPreDefineSettingsFromXML(std::string const filepath, std::string const moduleName)
{
	m_sModuleName = moduleName;
	return LoadPreDefineSettings(LoadConfigurationXMLElement(filepath, moduleName));
}

/// Print Control Parameters of each module
int MUSiiCConfigureRFServer::PrintModuleControlParameters()
{
	//// Print out module name
	std::cout << "==================================================================================" <<std::endl;
	std::cout << "Control parameters of " << m_sModuleName.c_str() << std::endl;
	std::cout << "The Value of " << RF_DEPTH		<< 	": " << int_To_string(Rf_Server_Info.depth).c_str() << std::endl;
	std::cout << "The Value of " << RF_FOCUS_COUNT	<< 	": " << int_To_string(Rf_Server_Info.focus_count).c_str() << std::endl;
	std::cout << "The Value of " << RF_FOCUS_DEPTH	<< 	": " << int_To_string(Rf_Server_Info.focus_dpeth).c_str() << std::endl;
	std::cout << "The Value of " << RF_FOCUS_SPAC	<< 	": " << int_To_string(Rf_Server_Info.focus_space).c_str() << std::endl;
	std::cout << "The Value of " << RF_SAMPLE_FREQ	<< 	": " << int_To_string(Rf_Server_Info.sampling_frequency).c_str() << std::endl;
	std::cout << "==================================================================================" <<std::endl;

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
//protected: ///Operation
//// virtual functions
void MUSiiCConfigureRFServer::Initialize()
{
}


/// Get pre-setting values of a specific module
int MUSiiCConfigureRFServer::GetPreSettingValuesOfModule()
{
	int r(0);
	//// Get the Image depth of RF_Server
	if(LookAtXMLElement(RF_DEPTH, m_sEValue))
	{
		Rf_Server_Info.depth = string_To_int(m_sEValue);
		r++;
	}
	else
		Rf_Server_Info.depth = 40;


	//// Get the focus_count of RF_Server
	if(LookAtXMLElement(RF_FOCUS_COUNT, m_sEValue))
	{
		Rf_Server_Info.focus_count = string_To_int(m_sEValue);
		r++;
	}
	else
		Rf_Server_Info.focus_count = 0;


	//// Get the focus_depth of RF_Server
	if(LookAtXMLElement(RF_FOCUS_DEPTH, m_sEValue))
	{
		Rf_Server_Info.focus_dpeth = string_To_int(m_sEValue);
		r++;
	}
	else
		Rf_Server_Info.focus_dpeth = 0;

	//// Get the focus_depth of RF_Server
	if(LookAtXMLElement(RF_FOCUS_SPAC, m_sEValue))
	{
		Rf_Server_Info.focus_space = string_To_int(m_sEValue);
		r++;
	}
	else
		Rf_Server_Info.focus_space = 0;

	//// Get the focus_depth of RF_Server
	if(LookAtXMLElement(RF_SAMPLE_FREQ, m_sEValue))
	{
		Rf_Server_Info.sampling_frequency = string_To_int(m_sEValue);
		r++;
	}
	else
		Rf_Server_Info.sampling_frequency = 20000000;

	return r;
}

/// Update control parameters
int MUSiiCConfigureRFServer::UpdateControlParameters()
{
	TiXmlElement* pChildE;
	int r(0);


	pChildE = m_pModule->FirstChildElement(RF_DEPTH);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(int_To_string(Rf_Server_Info.depth).c_str());
		r++;
	}

	pChildE = m_pModule->FirstChildElement(RF_FOCUS_COUNT);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(int_To_string(Rf_Server_Info.focus_count).c_str());
		r++;
	}

	pChildE = m_pModule->FirstChildElement(RF_FOCUS_DEPTH);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(int_To_string(Rf_Server_Info.focus_dpeth).c_str());
		r++;
	}

	pChildE = m_pModule->FirstChildElement(RF_FOCUS_SPAC);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(int_To_string(Rf_Server_Info.focus_space).c_str());
		r++;
	}

	pChildE = m_pModule->FirstChildElement(RF_SAMPLE_FREQ);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(int_To_string(Rf_Server_Info.sampling_frequency).c_str());
		r++;
	}

	ConvertTiXmlElementToStringMap(m_pModule);
	return r;
}


/// Virtual Functions
///////////////////////////////////////////////////////////////////
}

