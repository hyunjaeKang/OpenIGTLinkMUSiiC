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
#ifndef __MUSIIC_CONFIGURE_MUSiiCBMODE_
#define __MUSIIC_CONFIGURE_MUSiiCBMODE_

#include "MUSiiCConfigure.h"
/// The name of Module
#define MUSiiC_BMODE		"B-MODE"
/// The name of control parameter

namespace igtl
{
typedef struct
{
	
} MUSiiCBmode_Info;

class IGTLMCommon_EXPORT MUSiiCConfigureMUSiiCBMode : public MUSiiCConfigure
{

public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCConfigureMUSiiCBMode	Self;
	typedef MUSiiCConfigure				Superclass;
	typedef SmartPointer<Self>			Pointer;
	typedef SmartPointer<const Self>	ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	/// Constructor
	MUSiiCConfigureMUSiiCBMode();
	
	/// Deconstructor
	~MUSiiCConfigureMUSiiCBMode();

	/// Load pre-defined setting values from XML file with module's name
	virtual int LoadPreDefineSettingsFromXML(std::string const filepath, std::string const moduleName =  MUSiiC_BMODE);

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
	MUSiiCBmode_Info						m_MUSiiCBModeInfo;
protected:/// Attributes


};

}

#endif
