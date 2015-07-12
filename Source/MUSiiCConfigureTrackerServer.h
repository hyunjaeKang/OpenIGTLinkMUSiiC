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
#ifndef __MUSIIC_CONFIGURE_MUSiiC_TRACKER_SERVER_
#define __MUSIIC_CONFIGURE_MUSiiC_TRACKER_SERVER_

#include "MUSiiCConfigure.h"


/// The name of Module
#define EM_TRACKER		"EM_Tracker"
/// The name of control parameter
#define EM_NUM_OF_ACTIVE		"num_of_active_sensor"
#define EM_SENSOR1_ACTIVE		"sensor1_active"
#define EM_SENSOR1_NAME			"sensor1_name"
#define EM_SENSOR2_ACTIVE		"sensor2_active"
#define EM_SENSOR2_NAME			"sensor2_name"
#define EM_SENSOR3_ACTIVE		"sensor3_active"
#define EM_SENSOR3_NAME			"sensor3_name"
#define EM_SENSOR4_ACTIVE		"sensor4_active"
#define EM_SENSOR4_NAME			"sensor4_name"


namespace igtl
{
typedef struct
{
	bool			Active;
	std::string		Name;
} EMSensor_Info;

typedef struct
{
	int				Num_Of_Active_sensor;
	/*bool			Sensor1_Active;
	bool			Sensor2_Active;
	bool			Sensor3_Active;
	bool			Sensor4_Active;
	std::string		Snesor1_Name;
	std::string		Snesor2_Name;
	std::string		Snesor3_Name;
	std::string		Snesor4_Name;*/
	
	EMSensor_Info	SersorsInfo[4];
} EMServer_Info;

class IGTLMCommon_EXPORT MUSiiCConfigureTrackerServer : public MUSiiCConfigure
{

public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCConfigureTrackerServer		Self;
	typedef MUSiiCConfigure						Superclass;
	typedef SmartPointer<Self>					Pointer;
	typedef SmartPointer<const Self>			ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	/// Constructor
	MUSiiCConfigureTrackerServer();
	
	/// Deconstructor
	~MUSiiCConfigureTrackerServer();

	/// Load pre-defined setting values from XML file with module's name
	virtual int LoadPreDefineSettingsFromXML(std::string const filepath, std::string const moduleName =  EM_TRACKER);

	/// Print Control Parameters of each module
	virtual int PrintModuleControlParameters();

	/// Re-Define control parameters of this module
	virtual int ReDefineControlParameters();
	
protected: ///Operation
	//// virtual functions
	virtual void Initialize();

	/// Get pre-setting values of a specific module
	virtual int GetPreSettingValuesOfModule();

	/// Update control parameters
	virtual int UpdateControlParameters();

public:/// Attributes
	EMServer_Info		EM_Server_Info;
protected:/// Attributes


};

}

#endif
