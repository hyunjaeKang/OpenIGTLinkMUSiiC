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

#ifndef __igtlFMessageBMODE_h
#define __igtlFMessageBMODE_h

#include <igtlObject.h>
#include <igtlMacro.h>
#include <igtlMath.h>
#include <igtlImageMessage.h>
#include "igtlM_win32header.h"

namespace igtl
{
	class IGTLMCommon_EXPORT FixedImageBMODE: public ImageMessage
	{
		public:
			typedef FixedImageBMODE						Self;
			typedef ImageMessage					Superclass;
			typedef SmartPointer<Self>				Pointer;
			typedef SmartPointer<const Self>		ConstPointer;
			
			igtlTypeMacro(igtl::FixedImageBMODE, igtl::ImageMessage)
			igtlNewMacro(igtl::FixedImageBMODE);
		
		public:
			void SetDeviceType(std::string devicetype);
		
		protected:
			FixedImageBMODE();
			~FixedImageBMODE();
		
		protected:
		
		protected:		
	};	
}

#endif  // _igtlEIMessage