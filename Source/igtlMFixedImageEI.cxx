/***************************************************************************
# Copyright 
# MUSiiC Laboratory
# Hyun-Jae Kang, Philipp J Stolka,Emad M Boctor
# Johns Hopkins Medical Institutions
# Department of Radiology, Division of Medical Imaging Physics

# For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.
# ***************************************************************************/

#include "igtlMFixedImage.h"

#include <igtl_header.h>
#include <igtl_image.h>

namespace igtl
{
	FixedImage::FixedImage():
		ImageMessage()
	{		
		m_DeviceName 	="FIXED_IMAGE";
		m_DefaultBodyType  = "EIIMAGE";
	}
	
	void FixedImage::SetDeviceType(std::string devicetype)
	{
		this->m_DefaultBodyType = devicetype;
		this->m_BodyType		= devicetype;
	}
	FixedImage::~FixedImage()
	{
	}
} //namespace igtl