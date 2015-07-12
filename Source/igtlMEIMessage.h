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


#ifndef __igtlEIMessage_h
#define __igtlEIMessage_h

#include <igtlObject.h>
#include <igtlMacro.h>
#include <igtlMath.h>
#include <igtlImageMessage.h>
//#include "igtlMUSiiCutil/igtlM_EI.h"
#include "igtlM_EI.h"

namespace igtl
{
	class IGTLMCommon_EXPORT EIMessage: public ImageMessage
	{
		public:
			typedef EIMessage						Self;
			typedef ImageMessage					Superclass;
			typedef SmartPointer<Self>				Pointer;
			typedef SmartPointer<const Self>		ConstPointer;
			
			igtlTypeMacro(igtl::EIMessage, igtl::ImageMessage)
			igtlNewMacro(igtl::EIMessage);
		
		public:
			void SetImgAng(float ang){ ImgAng = ang;};
			void SetACC(float acc){ACC = acc;};
			void SetBroderWidth(float bw){BroderWidth = bw;};
			void SetAveStrain(float as){AveStrain = as;};
			void SetRecDelay(float rd){RecDelay = rd;};
			
			float GetImgAng(){ return ImgAng;};
			float GetACC(){return ACC;};
			float GetBroderWidth(){return BroderWidth;};
			float GetAveStrain(){return AveStrain;};
			float GetRecDelay(){return RecDelay;};

			void SetDeviceType(std::string devicetype);
		
		protected:
			EIMessage();
			~EIMessage();
		
		protected:
			virtual int GetBodyPackSize();
			virtual int PackBody();
			virtual int UnpackBody();
		
		protected:
			float ImgAng;
			float ACC;
			float BroderWidth;
			float AveStrain;
			float RecDelay;
			
			unsigned char* m_EITag;
		
	};	
}

#endif  // _igtlEIMessage