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
#define EI_NCC		"FilteredNCC"
/// The name of control parameter
#define EI_NCC_WINDOW				"windows"
#define EI_NCC_DISPLACEMENT			"displacement"
#define EI_NCC_OVERLAP				"overlap"
#define EI_NCC_LOOKAHEAD			"lookahead"
#define EI_NCC_CC_THRES				"cross_correlation_threshold"

#define EI_NCC_STRAIN_POS_NOISE		"strain_value_positive_noise"
#define EI_NCC_STRAIN_NEG_NOISE		"strain_value_negative_noise"
#define EI_NCC_ENABLE_POS_CONTRAST	"enable_positive_threshold_contrast"
#define EI_NCC_POS_THRES_CONTRAST	"positive_threshold_contrast"
#define EI_NCC_POS_THRES_STD		"positive_threshold_standard_deviation"

#define EI_NCC_ENABLE_NEG_CONTRAST	"enable_negative_threshold_contrast"
#define EI_NCC_NEG_THRES_CONTRAST	"negative_threshold_contrast"
#define EI_NCC_NEG_THRES_STD		"negative_threshold_standard_deviation"
#define EI_NCC_MEDIAN_FILTER_W		"median_filter_width"
#define EI_NCC_MEDIAN_FILTER_H		"median_filter_height"

#define EI_NCC_AVG_FILTER_D			"average_filter_depth"


namespace igtl
{
typedef struct
{
	/// "windows"
	int		iWINDOW;
	/// "displacement"
	float	fDISPLACEMENT;
	/// "overlap"
	float	fOVERLAP;
	/// "lookahead"
	int		iLOOKAHEAD;
	/// "cross_correlation_threshold"
	float	fCC_THRES;
	
	/// "strain_value_positive_noise"
	float	fSTRAIN_POS_NOISE;
	/// "strain_value_negative_noise"
	float	fSTRAIN_NEG_NOISE;
	/// "enable_positive_threshold_contrast"
	bool	bENABLE_POS_CONTRAST;
	/// "positive_threshold_contrast"
	float	fPOS_THRES_CONTRAST;
	/// "positive_threshold_standard_deviation"
	float	fPOS_THRES_STD;
	
	/// "enable_negative_threshold_contrast"
	bool	bENABLE_NEG_CONTRAST;
	/// "negative_threshold_contrast"
	float	fNEG_THRES_CONTRAST;
	/// "negative_threshold_standard_deviation"
	float	fNEG_THRES_STD;
	/// "median_filter_width"
	int		iMEDIAN_FILTER_W;
	/// "median_filter_height"
	int		iMEDIAN_FILTER_H;
	
	/// "average_filter_depth"
	int		iAVG_FILTER_D;
	
} MUSiiCEINCC_Info;
class IGTLMCommon_EXPORT MUSiiCConfigureMUSiiCEINCC : public MUSiiCConfigure
{

public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCConfigureMUSiiCEINCC	Self;
	typedef MUSiiCConfigure				Superclass;
	typedef SmartPointer<Self>			Pointer;
	typedef SmartPointer<const Self>	ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	/// Constructor
	MUSiiCConfigureMUSiiCEINCC();
	
	/// Deconstructor
	~MUSiiCConfigureMUSiiCEINCC();

	/// Load pre-defined setting values from XML file with module's name
	virtual int LoadPreDefineSettingsFromXML(std::string const filepath, std::string const moduleName =  EI_NCC);

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
	MUSiiCEINCC_Info						m_MUSiiCEINCCInfo;
protected:/// Attributes


};

}

#endif
