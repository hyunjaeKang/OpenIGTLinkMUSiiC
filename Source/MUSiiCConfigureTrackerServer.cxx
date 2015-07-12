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

#include "MUSiiCConfigureTrackerServer.h"



namespace igtl
{

/// Constructor
MUSiiCConfigureTrackerServer::MUSiiCConfigureTrackerServer()
{
	m_pNameOfClass="MUSiiCConfigureTrackerServer";
	Initialize();	
}
	
	/// Deconstructor
MUSiiCConfigureTrackerServer::~MUSiiCConfigureTrackerServer()
{
	
}

/// Virtual Function
int MUSiiCConfigureTrackerServer::LoadPreDefineSettingsFromXML(std::string const filepath, std::string const moduleName)
{
	m_sModuleName = moduleName;
	return LoadPreDefineSettings(LoadConfigurationXMLElement(filepath, moduleName));
}

/// Print Control Parameters of each module
int MUSiiCConfigureTrackerServer::PrintModuleControlParameters()
{
	//// Print out module name
	std::cout << "==================================================================================" <<std::endl;
	std::cout << "Control parameters of " << m_sModuleName.c_str() << std::endl;
	std::cout << "The Value of " << EM_NUM_OF_ACTIVE	<< 	": " << int_To_string(EM_Server_Info.Num_Of_Active_sensor).c_str() << std::endl;
	std::cout << "The Value of " << EM_SENSOR1_ACTIVE	<< 	": " << bool_To_string(EM_Server_Info.SersorsInfo[0].Active).c_str() << std::endl;
	std::cout << "The Value of " << EM_SENSOR1_NAME		<< 	": " << EM_Server_Info.SersorsInfo[0].Name.c_str() << std::endl;
	std::cout << "The Value of " << EM_SENSOR2_ACTIVE	<< 	": " << bool_To_string(EM_Server_Info.SersorsInfo[1].Active).c_str() << std::endl;
	std::cout << "The Value of " << EM_SENSOR2_NAME		<< 	": " << EM_Server_Info.SersorsInfo[1].Name.c_str()<< std::endl;
	std::cout << "The Value of " << EM_SENSOR3_ACTIVE	<< 	": " << bool_To_string(EM_Server_Info.SersorsInfo[2].Active).c_str() << std::endl;
	std::cout << "The Value of " << EM_SENSOR3_NAME		<< 	": " << EM_Server_Info.SersorsInfo[2].Name.c_str() << std::endl;
	std::cout << "The Value of " << EM_SENSOR4_ACTIVE	<< 	": " << bool_To_string(EM_Server_Info.SersorsInfo[3].Active).c_str() << std::endl;
	std::cout << "The Value of " << EM_SENSOR4_NAME		<< 	": " << EM_Server_Info.SersorsInfo[3].Name.c_str() << std::endl;

	std::cout << "==================================================================================" <<std::endl;

	return 0;
}

/// Re-Define control parameters of this module
int MUSiiCConfigureTrackerServer::ReDefineControlParameters()
{
	std::string tempstring;
	std::cout << "==================================================================================" <<std::endl;
	int NumOfSensor(4);
	std::cout << "The number of Sensor is " <<  NumOfSensor << std::endl;
	EM_Server_Info.Num_Of_Active_sensor = NumOfSensor;
	for(int i=0; i< NumOfSensor; i++)
	{
		std::cout << i << ":EM_Sensor :: Name " << std::endl;
		std::cin >>tempstring;
		EM_Server_Info.SersorsInfo[i].Name = tempstring;
		
		std::cout << i << ":EM_Sensor :: Active (y/n) " << std::endl;
		std::cin >>tempstring;
		EM_Server_Info.SersorsInfo[i].Active = YesNO_To_bool(tempstring);

		std::cout << std::endl;
	}

	std::cout << "==================================================================================" <<std::endl;
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
//protected: ///Operation
//// virtual functions
void MUSiiCConfigureTrackerServer::Initialize()
{
	this->EM_Server_Info.Num_Of_Active_sensor = 4;
	for(int i=0; i>4; i++)
	{
		this->EM_Server_Info.SersorsInfo[i].Active = false;
		this->EM_Server_Info.SersorsInfo[i].Name = "No Name";
	}
}


/// Get pre-setting values of a specific module
int MUSiiCConfigureTrackerServer::GetPreSettingValuesOfModule()
{
	int r(0);
	//// Get the number of active-sensor of EM_Tracker
	if(LookAtXMLElement(EM_NUM_OF_ACTIVE, m_sEValue))
	{
		EM_Server_Info.Num_Of_Active_sensor= string_To_int(m_sEValue);
		r++;
	}
	else
		EM_Server_Info.Num_Of_Active_sensor = 0;
	
	//// Get the enable of sensor 1
	if(LookAtXMLElement(EM_SENSOR1_ACTIVE, m_sEValue))
	{
		EM_Server_Info.SersorsInfo[0].Active= string_To_bool(m_sEValue);
		r++;
	}
	else
		EM_Server_Info.SersorsInfo[0].Active = false;

	//// Get the enable of sensor 2
	if(LookAtXMLElement(EM_SENSOR2_ACTIVE, m_sEValue))
	{
		EM_Server_Info.SersorsInfo[1].Active= string_To_bool(m_sEValue);
		r++;
	}
	else
		EM_Server_Info.SersorsInfo[1].Active = false;

	//// Get the enable of sensor 3
	if(LookAtXMLElement(EM_SENSOR3_ACTIVE, m_sEValue))
	{
		EM_Server_Info.SersorsInfo[2].Active= string_To_bool(m_sEValue);
		r++;
	}
	else
		EM_Server_Info.SersorsInfo[2].Active = false;

	//// Get the enable of sensor 4
	if(LookAtXMLElement(EM_SENSOR4_ACTIVE, m_sEValue))
	{
		EM_Server_Info.SersorsInfo[3].Active= string_To_bool(m_sEValue);
		r++;
	}
	else
		EM_Server_Info.SersorsInfo[3].Active = false;


	//// Get the name of sensor 1
	if(LookAtXMLElement(EM_SENSOR1_NAME, m_sEValue))
	{
		EM_Server_Info.SersorsInfo[0].Name= m_sEValue;
		r++;
	}
	else
		EM_Server_Info.SersorsInfo[0].Name= "No_Name";

	//// Get the name of sensor 2
	if(LookAtXMLElement(EM_SENSOR2_NAME, m_sEValue))
	{
		EM_Server_Info.SersorsInfo[1].Name= m_sEValue;
		r++;
	}
	else
		EM_Server_Info.SersorsInfo[1].Name= "No_Name";

	//// Get the name of sensor 3
	if(LookAtXMLElement(EM_SENSOR3_NAME, m_sEValue))
	{
		EM_Server_Info.SersorsInfo[2].Name= m_sEValue;
		r++;
	}
	else
		EM_Server_Info.SersorsInfo[2].Name= "No_Name";

	//// Get the name of sensor 4
	if(LookAtXMLElement(EM_SENSOR4_NAME, m_sEValue))
	{
		EM_Server_Info.SersorsInfo[3].Name= m_sEValue;
		r++;
	}
	else
		EM_Server_Info.SersorsInfo[3].Name= "No_Name";

	return r;
}

/// Update control parameters
int MUSiiCConfigureTrackerServer::UpdateControlParameters()
{
	TiXmlElement* pChildE;
	int r(0);
	//// Set the number of active-sensor of EM_Tracker
	pChildE = m_pModule->FirstChildElement(EM_NUM_OF_ACTIVE);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(int_To_string(EM_Server_Info.Num_Of_Active_sensor).c_str());
		r++;
	}

	//// Set the enable of sensor 1
	pChildE = m_pModule->FirstChildElement(EM_SENSOR1_ACTIVE);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(bool_To_string(EM_Server_Info.SersorsInfo[0].Active).c_str());
		r++;
	}

	//// Set the enable of sensor 2
	pChildE = m_pModule->FirstChildElement(EM_SENSOR2_ACTIVE);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(bool_To_string(EM_Server_Info.SersorsInfo[1].Active).c_str());
		r++;
	}

	//// Set the enable of sensor 3
	pChildE = m_pModule->FirstChildElement(EM_SENSOR3_ACTIVE);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(bool_To_string(EM_Server_Info.SersorsInfo[2].Active).c_str());
		r++;
	}

	//// Set the enable of sensor 4
	pChildE = m_pModule->FirstChildElement(EM_SENSOR4_ACTIVE);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(bool_To_string(EM_Server_Info.SersorsInfo[3].Active).c_str());
		r++;
	}


	//// Set the name of sensor 1
	pChildE = m_pModule->FirstChildElement(EM_SENSOR1_NAME);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(EM_Server_Info.SersorsInfo[0].Name.c_str());
		r++;
	}

	//// Set the name of sensor 2
	pChildE = m_pModule->FirstChildElement(EM_SENSOR2_NAME);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(EM_Server_Info.SersorsInfo[1].Name.c_str());
		r++;
	}

	//// Set the name of sensor 3
	pChildE = m_pModule->FirstChildElement(EM_SENSOR3_NAME);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(EM_Server_Info.SersorsInfo[2].Name.c_str());
		r++;
	}

	//// Set the name of sensor 4
	pChildE = m_pModule->FirstChildElement(EM_SENSOR4_NAME);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(EM_Server_Info.SersorsInfo[3].Name.c_str());
		r++;
	}

	return r;
}

/// Virtual Functions
///////////////////////////////////////////////////////////////////
}

