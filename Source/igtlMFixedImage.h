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

#ifndef __igtlFMessage_h
#define __igtlFMessage_h

#include <igtlObject.h>
#include <igtlMacro.h>
#include <igtlMath.h>
#include <igtlImageMessage.h>
#include "igtlM_win32header.h"

namespace igtl
{
	class IGTLMCommon_EXPORT FixedImage: public ImageMessage
	{
		public:
			typedef FixedImage						Self;
			typedef ImageMessage					Superclass;
			typedef SmartPointer<Self>				Pointer;
			typedef SmartPointer<const Self>		ConstPointer;
			
			igtlTypeMacro(igtl::FixedImage, igtl::ImageMessage)
			igtlNewMacro(igtl::FixedImage);
		
		public:
			void SetDeviceType(std::string devicetype);
		
		protected:
			FixedImage();
			~FixedImage();
		
		protected:
		
		protected:		
	};	
}

#endif  // _igtlEIMessage