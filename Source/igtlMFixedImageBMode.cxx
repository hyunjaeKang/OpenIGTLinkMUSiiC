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

#include "igtlMFixedImageBMode.h"

#include <igtl_header.h>
#include <igtl_image.h>

namespace igtl
{
	FixedImageBMODE::FixedImageBMODE():
		ImageMessage()
	{		
		m_DeviceName 	="FIXED_BMODEIMAGE";
		m_DefaultBodyType  = "EIUSIMAGE";
	}
	
	void FixedImageBMODE::SetDeviceType(std::string devicetype)
	{
		this->m_DefaultBodyType = devicetype;
		this->m_BodyType		= devicetype;
	}
	FixedImageBMODE::~FixedImageBMODE()
	{
	}
} //namespace igtl