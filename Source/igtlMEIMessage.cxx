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

#include "igtlMEIMessage.h"
#include "igtl_header.h"
#include "igtl_image.h"

namespace igtl
{
	EIMessage::EIMessage():
		ImageMessage()
	{
		ImgAng 			= 0.0;
		ACC				= 0.0;
		BroderWidth		= 0.0;
		AveStrain		= 0.0;
		RecDelay		= 0.0;
		
		m_DeviceName 	="EI";
		//m_DefaultBodyType  = "MUSiiC_EI";
	}
	
	void EIMessage::SetDeviceType(std::string devicetype)
	{
		this->m_DefaultBodyType = devicetype;
		this->m_BodyType = devicetype;
	}
	EIMessage::~EIMessage()
	{
	}
	
	int EIMessage::GetBodyPackSize()
	{
		return GetSubVolumeImageSize() + IGTL_IMAGE_HEADER_SIZE + IGTL_EI_TAG_SIZE;
	}
	
	int EIMessage::PackBody()
	{
		Superclass::PackBody();
		
		m_EITag = &m_Image[GetSubVolumeImageSize()];
		igtl_EI_tag* ei_tager = (igtl_EI_tag*) m_EITag;
		
		ei_tager->ImgAng 			= this->ImgAng;
		ei_tager->ACC 				= this->ACC;
		ei_tager->BroderWidth 	= this->BroderWidth;
		ei_tager->AveStrain 		= this->AveStrain;
		ei_tager->RecDelay 		= this->RecDelay;
		
		igtl_EITag_convert_byte_order(ei_tager);
		
		return 1;
	}
	
	int EIMessage::UnpackBody()
	{
		Superclass::UnpackBody();

		int s0 = this->GetPackBodySize();
		int s1 = this->GetSubVolumeImageSize();
		int diff = s0-s1;

		if((this->GetPackBodySize() -this->GetSubVolumeImageSize()) == 92)
		{
			m_EITag = &m_Image[GetSubVolumeImageSize()];
			igtl_EI_tag* ei_tager = (igtl_EI_tag*) m_EITag;
			igtl_EITag_convert_byte_order(ei_tager);
		
			this->ImgAng 			= ei_tager->ImgAng;
			this->ACC 				= ei_tager->ACC;
			this->BroderWidth 		= ei_tager->BroderWidth;
			this->AveStrain 		= ei_tager->AveStrain;
			this->RecDelay 			= ei_tager->RecDelay;
		}
		else
		{
			this->ImgAng 			= 0.0;
			this->ACC 				= 0.0;
			this->BroderWidth 		= 0.0;
			this->AveStrain 		= 0.0;
			this->RecDelay 			= 0.0;
		}
		
		return 1;
	}
} //namespace igtl