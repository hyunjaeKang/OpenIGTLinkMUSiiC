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

#include "MUSiiCConfigureMUSiiCSync.h"

namespace igtl
{

	
/// Constructor
MUSiiCConfigureMUSiiCSync::MUSiiCConfigureMUSiiCSync()
{
	m_pNameOfClass="MUSiiCConfigureMUSiiCSync";
	Initialize();	
}
	
	/// Deconstructor
MUSiiCConfigureMUSiiCSync::~MUSiiCConfigureMUSiiCSync()
{
	
}

/// Virtual Function
int MUSiiCConfigureMUSiiCSync::LoadPreDefineSettingsFromXML(std::string const filepath, std::string const moduleName)
{
	m_sModuleName = moduleName;
	return LoadPreDefineSettings(LoadConfigurationXMLElement(filepath, moduleName));
}

/// Print Control Parameters of each module
int MUSiiCConfigureMUSiiCSync::PrintModuleControlParameters()
{
	//// Print out module name
	std::cout << "==================================================================================" <<std::endl;
	std::cout << "Control parameters of " << m_sModuleName.c_str() << std::endl;

	std::cout << "==================================================================================" <<std::endl;
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
//protected: ///Operation
//// virtual functions
void MUSiiCConfigureMUSiiCSync::Initialize()
{
}

/// Get pre-setting values of a specific module
int MUSiiCConfigureMUSiiCSync::GetPreSettingValuesOfModule()
{
	int r(0);
	//// Get the Image depth of RF_Server
	

	return r;
}

/// Update control parameters
int MUSiiCConfigureMUSiiCSync::UpdateControlParameters()
{
	TiXmlElement* pChildE;
	int r(0);
	
	return r;
}


/// Virtual Functions
///////////////////////////////////////////////////////////////////
}

