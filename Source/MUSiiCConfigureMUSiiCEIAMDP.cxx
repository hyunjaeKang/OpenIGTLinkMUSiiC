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

#include "MUSiiCConfigureMUSiiCEIAMDP.h"

namespace igtl
{

	
/// Constructor
MUSiiCConfigureMUSiiCEIAMDP::MUSiiCConfigureMUSiiCEIAMDP()
{
	m_pNameOfClass="MUSiiCConfigureMUSiiCEIAMDP";
	Initialize();	
}
	
	/// Deconstructor
MUSiiCConfigureMUSiiCEIAMDP::~MUSiiCConfigureMUSiiCEIAMDP()
{
	
}

/// Virtual Function
int MUSiiCConfigureMUSiiCEIAMDP::LoadPreDefineSettingsFromXML(std::string const filepath, std::string const moduleName)
{
	m_sModuleName = moduleName;
	return LoadPreDefineSettings(LoadConfigurationXMLElement(filepath, moduleName));
}

/// Print Control Parameters of each module
int MUSiiCConfigureMUSiiCEIAMDP::PrintModuleControlParameters()
{
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
//protected: ///Operation
//// virtual functions
void MUSiiCConfigureMUSiiCEIAMDP::Initialize()
{
}

/// Get pre-setting values of a specific module
int MUSiiCConfigureMUSiiCEIAMDP::GetPreSettingValuesOfModule()
{
	int r(0);
	//// Get the Image depth of RF_Server
	

	return r;
}

/// Update control parameters
int MUSiiCConfigureMUSiiCEIAMDP::UpdateControlParameters()
{
	TiXmlElement* pChildE;
	int r(0);
	
	return r;
}


/// Virtual Functions
///////////////////////////////////////////////////////////////////
}

