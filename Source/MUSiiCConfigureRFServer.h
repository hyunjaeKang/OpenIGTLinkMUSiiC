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
#ifndef __MUSIIC_CONFIGURE_MUSiiC_RFSERVER_
#define __MUSIIC_CONFIGURE_MUSiiC_RFSERVER_

#include "MUSiiCConfigure.h"


/// The name of Module
#define RF_SERVER		"RF_Server"
/// The name of control parameter
#define RF_DEPTH		"depth"
#define RF_FOCUS_COUNT	"focus_count"
#define RF_FOCUS_DEPTH	"focus_depth"
#define RF_FOCUS_SPAC	"focus_space"
#define RF_SAMPLE_FREQ	"sampling_frequency"

namespace igtl
{

typedef struct
{
	int focus_count;
	int sampling_frequency;
	int focus_space;
	int focus_dpeth;
	int depth; // mm
} RFServer_Info;

class IGTLMCommon_EXPORT MUSiiCConfigureRFServer : public MUSiiCConfigure
{

public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCConfigureRFServer		Self;
	typedef MUSiiCConfigure				Superclass;
	typedef SmartPointer<Self>			Pointer;
	typedef SmartPointer<const Self>	ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	/// Constructor
	MUSiiCConfigureRFServer();
	
	/// Deconstructor
	~MUSiiCConfigureRFServer();

	/// Load pre-defined setting values from XML file with module's name
	virtual int LoadPreDefineSettingsFromXML(std::string const filepath, std::string const moduleName =  RF_SERVER);

	/// Print Control Parameters of each module
	virtual int PrintModuleControlParameters();
	
protected: ///Operation
	//// virtual functions
	virtual void Initialize();

	/// Get pre-setting values of a specific module
	virtual int GetPreSettingValuesOfModule();

	/// Update control parameters
	virtual int UpdateControlParameters();

public:/// Attributes
	RFServer_Info		Rf_Server_Info;
	
protected:/// Attributes


};

}

#endif
