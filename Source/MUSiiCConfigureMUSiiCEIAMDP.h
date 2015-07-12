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
#ifndef __MUSIIC_CONFIGURE_MUSiiCEIAMDP_
#define __MUSIIC_CONFIGURE_MUSiiCEIAMDP_

#include "MUSiiCConfigure.h"
/// The name of Module
#define EI_AMDP		"EI_AMDP"
/// The name of control parameter

namespace igtl
{
typedef struct
{
	
} MUSiiCEIAMDP_Info;
class IGTLMCommon_EXPORT MUSiiCConfigureMUSiiCEIAMDP : public MUSiiCConfigure
{

public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCConfigureMUSiiCEIAMDP	Self;
	typedef MUSiiCConfigure				Superclass;
	typedef SmartPointer<Self>			Pointer;
	typedef SmartPointer<const Self>	ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	/// Constructor
	MUSiiCConfigureMUSiiCEIAMDP();
	
	/// Deconstructor
	~MUSiiCConfigureMUSiiCEIAMDP();

	/// Load pre-defined setting values from XML file with module's name
	virtual int LoadPreDefineSettingsFromXML(std::string const filepath, std::string const moduleName =  EI_AMDP);

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
	MUSiiCEIAMDP_Info						m_MUSiiCEIAMDPInfo;
protected:/// Attributes


};

}

#endif
