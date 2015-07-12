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

#include "MUSiiCConfigureMUSiiCBMode.h"

namespace igtl
{

	
/// Constructor
MUSiiCConfigureMUSiiCBMode::MUSiiCConfigureMUSiiCBMode()
{
	m_pNameOfClass="MUSiiCConfigureMUSiiCBMode";
	Initialize();	
}
	
	/// Deconstructor
MUSiiCConfigureMUSiiCBMode::~MUSiiCConfigureMUSiiCBMode()
{
	
}

/// Virtual Function
/// Load pre-defined setting values from XML file with module's name
int MUSiiCConfigureMUSiiCBMode::LoadPreDefineSettingsFromXML(std::string const filepath, std::string const moduleName)
{
	m_sModuleName = moduleName;
	return LoadPreDefineSettings(LoadConfigurationXMLElement(filepath, moduleName));
}

/// Print Control Parameters of each module
int MUSiiCConfigureMUSiiCBMode::PrintModuleControlParameters()
{
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
//protected: ///Operation
//// virtual functions
void MUSiiCConfigureMUSiiCBMode::Initialize()
{
}

/// Get pre-setting values of a specific module
int MUSiiCConfigureMUSiiCBMode::GetPreSettingValuesOfModule()
{
	int r(0);
	//// Get the Image depth of RF_Server
	

	return r;
}

/// Update control parameters
int MUSiiCConfigureMUSiiCBMode::UpdateControlParameters()
{
	TiXmlElement* pChildE;
	int r(0);
	
	return r;
}


/// Virtual Functions
///////////////////////////////////////////////////////////////////
}

