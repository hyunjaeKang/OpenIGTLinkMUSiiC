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
#ifndef __MUSIIC_CONFIGURE_MUSiiCSYNC_
#define __MUSIIC_CONFIGURE_MUSiiCSYNC_

#include "MUSiiCConfigure.h"
/// The name of Module
#define EI_TRUE		"EI_TrUE"
/// The name of control parameter

///// The name of Module
//#define RF_SERVER		"RF_Server"
///// The name of control parameter
//#define RF_DEPTH		"depth"
//#define RF_FOCUS_COUNT	"focus_count"
//#define RF_FOCUS_DEPTH	"focus_depth"
//#define RF_FOCUS_SPAC	"focus_space"
//#define RF_SAMPLE_FREQ	"sampling_frequency"


namespace igtl
{
typedef struct
{
	int focus_count;
	int sampling_frequency;
	int focus_space;
	int focus_dpeth;
	int depth; // mm
	
} MUSiiCEITrUE_Info;
class IGTLMCommon_EXPORT MUSiiCConfigureMUSiiCEITrUE : public MUSiiCConfigure
{

public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCConfigureMUSiiCEITrUE	Self;
	typedef MUSiiCConfigure				Superclass;
	typedef SmartPointer<Self>			Pointer;
	typedef SmartPointer<const Self>	ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	/// Constructor
	MUSiiCConfigureMUSiiCEITrUE();
	
	/// Deconstructor
	~MUSiiCConfigureMUSiiCEITrUE();

	/// Load pre-defined setting values from XML file with module's name
	virtual int LoadPreDefineSettingsFromXML(std::string const filepath, std::string const moduleName =  EI_TRUE);

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
	MUSiiCEITrUE_Info						m_MUSiiCEITrUEInfo;
protected:/// Attributes


};

}

#endif
