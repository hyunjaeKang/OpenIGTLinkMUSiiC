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

#include "MUSiiCConfigureMUSiiCEINCC.h"

namespace igtl
{

	
/// Constructor
MUSiiCConfigureMUSiiCEINCC::MUSiiCConfigureMUSiiCEINCC()
{
	m_pNameOfClass="MUSiiCConfigureMUSiiCEINCC";
	Initialize();	
}
	
	/// Deconstructor
MUSiiCConfigureMUSiiCEINCC::~MUSiiCConfigureMUSiiCEINCC()
{
	
}

/// Virtual Function
int MUSiiCConfigureMUSiiCEINCC::LoadPreDefineSettingsFromXML(std::string const filepath, std::string const moduleName)
{
	m_sModuleName = moduleName;
	return LoadPreDefineSettings(LoadConfigurationXMLElement(filepath, moduleName));
}

/// Print Control Parameters of each module
int MUSiiCConfigureMUSiiCEINCC::PrintModuleControlParameters()
{
	//// Print out module name
	std::cout << "==================================================================================" <<std::endl;
	std::cout << "Control parameters of " << m_sModuleName.c_str() << std::endl;
	std::cout << "The Value of " << EI_NCC_WINDOW			<< 	": " << int_To_string(m_MUSiiCEINCCInfo.iWINDOW).c_str() << std::endl;
	std::cout << "The Value of " << EI_NCC_DISPLACEMENT		<< 	": " << float_To_string(m_MUSiiCEINCCInfo.fDISPLACEMENT).c_str() << std::endl;
	std::cout << "The Value of " << EI_NCC_OVERLAP			<< 	": " << float_To_string(m_MUSiiCEINCCInfo.fOVERLAP).c_str() << std::endl;
	std::cout << "The Value of " << EI_NCC_LOOKAHEAD		<< 	": " << int_To_string(m_MUSiiCEINCCInfo.iLOOKAHEAD ).c_str() << std::endl;
	std::cout << "The Value of " << EI_NCC_CC_THRES			<< 	": " << float_To_string(m_MUSiiCEINCCInfo.fCC_THRES).c_str() << std::endl;

	std::cout << "The Value of " << EI_NCC_STRAIN_POS_NOISE		<< 	": " << float_To_string(m_MUSiiCEINCCInfo.fSTRAIN_POS_NOISE).c_str() << std::endl;
	std::cout << "The Value of " << EI_NCC_STRAIN_NEG_NOISE		<< 	": " << float_To_string(m_MUSiiCEINCCInfo.fSTRAIN_NEG_NOISE).c_str() << std::endl;
	std::cout << "The Value of " << EI_NCC_ENABLE_POS_CONTRAST	<< 	": " << bool_To_string(m_MUSiiCEINCCInfo.bENABLE_POS_CONTRAST).c_str() << std::endl;
	std::cout << "The Value of " << EI_NCC_POS_THRES_CONTRAST	<< 	": " << float_To_string(m_MUSiiCEINCCInfo.fPOS_THRES_CONTRAST).c_str() << std::endl;
	std::cout << "The Value of " << EI_NCC_POS_THRES_STD		<< 	": " << float_To_string(m_MUSiiCEINCCInfo.fPOS_THRES_STD).c_str() << std::endl;

	std::cout << "The Value of " << EI_NCC_ENABLE_NEG_CONTRAST	<< 	": " << bool_To_string(m_MUSiiCEINCCInfo.bENABLE_NEG_CONTRAST).c_str() << std::endl;
	std::cout << "The Value of " << EI_NCC_NEG_THRES_CONTRAST	<< 	": " << float_To_string(m_MUSiiCEINCCInfo.fNEG_THRES_CONTRAST).c_str() << std::endl;
	std::cout << "The Value of " << EI_NCC_NEG_THRES_STD		<< 	": " << float_To_string(m_MUSiiCEINCCInfo.fNEG_THRES_STD).c_str() << std::endl;
	std::cout << "The Value of " << EI_NCC_MEDIAN_FILTER_W		<< 	": " << int_To_string(m_MUSiiCEINCCInfo.iMEDIAN_FILTER_W).c_str() << std::endl;
	std::cout << "The Value of " << EI_NCC_MEDIAN_FILTER_H		<< 	": " << int_To_string(m_MUSiiCEINCCInfo.iMEDIAN_FILTER_H).c_str() << std::endl;

	std::cout << "The Value of " << EI_NCC_AVG_FILTER_D			<< 	": " << int_To_string(m_MUSiiCEINCCInfo.iAVG_FILTER_D).c_str() << std::endl;

	std::cout << "==================================================================================" <<std::endl;
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
//protected: ///Operation
//// virtual functions
void MUSiiCConfigureMUSiiCEINCC::Initialize()
{
}

/// Get pre-setting values of a specific module
int MUSiiCConfigureMUSiiCEINCC::GetPreSettingValuesOfModule()
{
	int r(0);
	///////////////////////////////////////////////////////////////
	//// Get the Window for EI_NCC
	if(LookAtXMLElement(EI_NCC_WINDOW, m_sEValue))
	{
		m_MUSiiCEINCCInfo.iWINDOW = string_To_int(m_sEValue);
		r++;
	}
	else
		m_MUSiiCEINCCInfo.iWINDOW = 1;

	//// Get the displacement for EI_NCC
	if(LookAtXMLElement(EI_NCC_DISPLACEMENT, m_sEValue))
	{
		m_MUSiiCEINCCInfo.fDISPLACEMENT = string_To_float(m_sEValue);
		r++;
	}
	else
		m_MUSiiCEINCCInfo.fDISPLACEMENT = 2.3;

	//// Get the EI_NCC_OVERLAP
	if(LookAtXMLElement(EI_NCC_OVERLAP, m_sEValue))
	{
		m_MUSiiCEINCCInfo.fOVERLAP = string_To_float(m_sEValue);
		r++;
	}
	else
		m_MUSiiCEINCCInfo.fOVERLAP = 4.5;

	//// Get the EI_NCC_LOOKAHEAD
	if(LookAtXMLElement(EI_NCC_LOOKAHEAD, m_sEValue))
	{
		m_MUSiiCEINCCInfo.iLOOKAHEAD = string_To_int(m_sEValue);
		r++;
	}
	else
		m_MUSiiCEINCCInfo.iLOOKAHEAD = 0;

	//// Get the EI_NCC_CC_THRES
	if(LookAtXMLElement(EI_NCC_CC_THRES, m_sEValue))
	{
		m_MUSiiCEINCCInfo.fCC_THRES = string_To_float(m_sEValue);
		r++;
	}
	else
		m_MUSiiCEINCCInfo.fCC_THRES = 0.0;

	///////////////////////////////////////////////////////////////
	//// Get the EI_NCC_STRAIN_POS_NOISE
	if(LookAtXMLElement(EI_NCC_STRAIN_POS_NOISE, m_sEValue))
	{
		m_MUSiiCEINCCInfo.fSTRAIN_POS_NOISE = string_To_float(m_sEValue);
		r++;
	}
	else
		m_MUSiiCEINCCInfo.fSTRAIN_POS_NOISE = 0.0;

	//// Get the EI_NCC_STRAIN_NEG_NOISE
	if(LookAtXMLElement(EI_NCC_STRAIN_NEG_NOISE, m_sEValue))
	{
		m_MUSiiCEINCCInfo.fSTRAIN_NEG_NOISE = string_To_float(m_sEValue);
		r++;
	}
	else
		m_MUSiiCEINCCInfo.fSTRAIN_NEG_NOISE = 0.0;

	//// Get the EI_NCC_ENABLE_POS_CONTRAST
	if(LookAtXMLElement(EI_NCC_ENABLE_POS_CONTRAST, m_sEValue))
	{
		m_MUSiiCEINCCInfo.bENABLE_POS_CONTRAST = string_To_bool(m_sEValue);
		r++;
	}
	else
		m_MUSiiCEINCCInfo.bENABLE_POS_CONTRAST = false;

	//// Get the EI_NCC_POS_THRES_CONTRAST
	if(LookAtXMLElement(EI_NCC_POS_THRES_CONTRAST, m_sEValue))
	{
		m_MUSiiCEINCCInfo.fPOS_THRES_CONTRAST = string_To_float(m_sEValue);
		r++;
	}
	else
		m_MUSiiCEINCCInfo.fPOS_THRES_CONTRAST = 0.0;

	//// Get the EI_NCC_POS_THRES_STD
	if(LookAtXMLElement(EI_NCC_POS_THRES_STD, m_sEValue))
	{
		m_MUSiiCEINCCInfo.fPOS_THRES_STD = string_To_float(m_sEValue);
		r++;
	}
	else
		m_MUSiiCEINCCInfo.fPOS_THRES_STD = 0.0;

	//////////////////////////////////////////////////////////////

	//// Get the EI_NCC_ENABLE_NEG_CONTRAST
	if(LookAtXMLElement(EI_NCC_ENABLE_NEG_CONTRAST, m_sEValue))
	{
		m_MUSiiCEINCCInfo.bENABLE_NEG_CONTRAST = string_To_bool(m_sEValue);
		r++;
	}
	else
		m_MUSiiCEINCCInfo.bENABLE_NEG_CONTRAST = true;

	//// Get the EI_NCC_NEG_THRES_CONTRAST
	if(LookAtXMLElement(EI_NCC_NEG_THRES_CONTRAST, m_sEValue))
	{
		m_MUSiiCEINCCInfo.fNEG_THRES_CONTRAST = string_To_float(m_sEValue);
		r++;
	}
	else
		m_MUSiiCEINCCInfo.fNEG_THRES_CONTRAST = 0.0;

	//// Get the EI_NCC_NEG_THRES_STD
	if(LookAtXMLElement(EI_NCC_NEG_THRES_STD, m_sEValue))
	{
		m_MUSiiCEINCCInfo.fNEG_THRES_STD = string_To_float(m_sEValue);
		r++;
	}
	else
		m_MUSiiCEINCCInfo.fNEG_THRES_STD = 0.0;

	//// Get the EI_NCC_MEDIAN_FILTER_W
	if(LookAtXMLElement(EI_NCC_MEDIAN_FILTER_W, m_sEValue))
	{
		m_MUSiiCEINCCInfo.iMEDIAN_FILTER_W = string_To_int(m_sEValue);
		r++;
	}
	else
		m_MUSiiCEINCCInfo.iMEDIAN_FILTER_W = 0;

	//// Get the EI_NCC_MEDIAN_FILTER_H
	if(LookAtXMLElement(EI_NCC_MEDIAN_FILTER_H, m_sEValue))
	{
		m_MUSiiCEINCCInfo.iMEDIAN_FILTER_H = string_To_int(m_sEValue);
		r++;
	}
	else
		m_MUSiiCEINCCInfo.iMEDIAN_FILTER_H = 0;

	////////////////////////////////////////////////////////////////////
	//// Get the EI_NCC_AVG_FILTER_D
	if(LookAtXMLElement(EI_NCC_AVG_FILTER_D, m_sEValue))
	{
		m_MUSiiCEINCCInfo.iAVG_FILTER_D = string_To_int(m_sEValue);
		r++;
	}
	else
		m_MUSiiCEINCCInfo.iAVG_FILTER_D = 0.0;



	return r;
}

/// Update control parameters
int MUSiiCConfigureMUSiiCEINCC::UpdateControlParameters()
{
	TiXmlElement* pChildE;
	int r(0);


	///////////////////////////////////////////////////////////////
	//// Set the Window for EI_NCC
	pChildE = m_pModule->FirstChildElement(EI_NCC_WINDOW);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(int_To_string(m_MUSiiCEINCCInfo.iWINDOW).c_str());
		r++;
	}

	//// Set the displacement for EI_NCC
	pChildE = m_pModule->FirstChildElement(EI_NCC_DISPLACEMENT);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(float_To_string(m_MUSiiCEINCCInfo.fDISPLACEMENT).c_str());
		r++;
	}
	//// Set the EI_NCC_OVERLAP
	pChildE = m_pModule->FirstChildElement(EI_NCC_OVERLAP);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(float_To_string(m_MUSiiCEINCCInfo.fOVERLAP).c_str());
		r++;
	}
	//// Set the EI_NCC_LOOKAHEAD
	pChildE = m_pModule->FirstChildElement(EI_NCC_LOOKAHEAD);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(int_To_string(m_MUSiiCEINCCInfo.iLOOKAHEAD ).c_str());
		r++;
	}
	
	//// Set the EI_NCC_CC_THRES
	pChildE = m_pModule->FirstChildElement(EI_NCC_CC_THRES);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(float_To_string(m_MUSiiCEINCCInfo.fCC_THRES).c_str());
		r++;
	}

	///////////////////////////////////////////////////////////////
	//// Set the EI_NCC_STRAIN_POS_NOISE
	pChildE = m_pModule->FirstChildElement(EI_NCC_STRAIN_POS_NOISE);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(float_To_string(m_MUSiiCEINCCInfo.fSTRAIN_POS_NOISE).c_str());
		r++;
	}

	//// Set the EI_NCC_STRAIN_NEG_NOISE
	pChildE = m_pModule->FirstChildElement(EI_NCC_STRAIN_NEG_NOISE);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(float_To_string(m_MUSiiCEINCCInfo.fSTRAIN_NEG_NOISE).c_str());
		r++;
	}

	//// Set the EI_NCC_ENABLE_POS_CONTRAST	
	pChildE = m_pModule->FirstChildElement(EI_NCC_ENABLE_POS_CONTRAST);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(bool_To_string(m_MUSiiCEINCCInfo.bENABLE_POS_CONTRAST).c_str());
		r++;
	}

	//// Set the EI_NCC_POS_THRES_CONTRAST
	pChildE = m_pModule->FirstChildElement(EI_NCC_POS_THRES_CONTRAST);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(float_To_string(m_MUSiiCEINCCInfo.fPOS_THRES_CONTRAST).c_str());
		r++;
	}
	
	//// Set the EI_NCC_POS_THRES_STD
	pChildE = m_pModule->FirstChildElement(EI_NCC_POS_THRES_STD);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(float_To_string(m_MUSiiCEINCCInfo.fPOS_THRES_STD).c_str());
		r++;
	}
	//////////////////////////////////////////////////////////////

	//// Set the EI_NCC_ENABLE_NEG_CONTRAST
	pChildE = m_pModule->FirstChildElement(EI_NCC_ENABLE_NEG_CONTRAST);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(bool_To_string(m_MUSiiCEINCCInfo.bENABLE_NEG_CONTRAST).c_str());
		r++;
	}

	//// Set the EI_NCC_NEG_THRES_CONTRAST
	pChildE = m_pModule->FirstChildElement(EI_NCC_NEG_THRES_CONTRAST);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(float_To_string(m_MUSiiCEINCCInfo.fNEG_THRES_CONTRAST).c_str());
		r++;
	}
	//// Set the EI_NCC_NEG_THRES_STD
	pChildE = m_pModule->FirstChildElement(EI_NCC_NEG_THRES_STD);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(float_To_string(m_MUSiiCEINCCInfo.fNEG_THRES_STD).c_str());
		r++;
	}
	//// Set the EI_NCC_MEDIAN_FILTER_W
	pChildE = m_pModule->FirstChildElement(EI_NCC_MEDIAN_FILTER_W);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(int_To_string(m_MUSiiCEINCCInfo.iMEDIAN_FILTER_W).c_str());
		r++;
	}
	//// Set the EI_NCC_MEDIAN_FILTER_H
	pChildE = m_pModule->FirstChildElement(EI_NCC_MEDIAN_FILTER_H);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(int_To_string(m_MUSiiCEINCCInfo.iMEDIAN_FILTER_H).c_str());
		r++;
	}
	////////////////////////////////////////////////////////////////////
	//// Set the EI_NCC_AVG_FILTER_D	
	pChildE = m_pModule->FirstChildElement(EI_NCC_AVG_FILTER_D);
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(int_To_string(m_MUSiiCEINCCInfo.iAVG_FILTER_D).c_str());
		r++;
	}

	return r;
}


/// Virtual Functions
///////////////////////////////////////////////////////////////////
}

