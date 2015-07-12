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

#include "igtlMUSMessage.h"

#include <igtl_header.h>
#include <igtl_image.h>

namespace igtl
{
	USMessage::USMessage():
		ImageMessage()
	{
		Type			=0;
		Txf 			=0;		
		Sf 				=0;				
		FPS 			=0;				
		Lden 			=0;			
		SAng 			=0;			
		ProbeID 		=0;		
				
		EA 				=0;				
		Elements 		=0;		
		Pitch 			=0;			
		Radius 			=0;			
		Probe_Angle 	=0;
		TxOffset 		=0;

		Motor_Radius	=0; // Motor_Radius of 3D Probe
		Frames3D        =0; // The number of RF-Frames of 3D RF-Volume

		Frame_Index		=0;   // The index of RF-Frame in 3D RF-Volume
		Focus_Spacing	=0;   // Focus_Spcaing // unit is um
		Focus_Depth		=0;   // Depth of Focus point // unit is um
		Extra_int32_1	=0;   // TBD
		Extra_int32_2	=0;   // TBD

		Extra_int32_3	=0;   // TBD
		Extra_int32_4	=0;   // TBD
		Extra_int32_5	=0;   // TBD

		Motor_Dir		=0;   // The Direction of 2D fram in 3D Volume
		Focus_Count		=0;   // The number of Focus point
		Extra_int8_1	=0;   // TBD
		Extra_int8_2	=0;   // TBD
		Extra_int8_3	=0;   // TBD
		
		m_DeviceName 	="US";		
	}
	
	USMessage::~USMessage()
	{
		////////////////////////////////////
		/// cannon96 To Do
		// std::cout << "~USMessage is called" << std::endl;
		// delete m_USTag;
	}
	
	int USMessage::GetBodyPackSize()
	{
		return GetSubVolumeImageSize() + IGTL_IMAGE_HEADER_SIZE + IGTL_US_TAG_SIZE;
	}
	
	int USMessage::PackBody()
	{
		//Superclass::PackBody();
		igtl::ImageMessage::PackBody();
		
		m_USTag = &m_Image[GetSubVolumeImageSize()];
		igtl_US_tag* us_tager = (igtl_US_tag*) m_USTag;
		
		us_tager->Type			= this->Type;
		us_tager->Txf			= this->Txf;		
		us_tager->Sf			= this->Sf;
		us_tager->FPS			= this->FPS ;
		us_tager->Lden			= this->Lden ;
		us_tager->SAng			= this->SAng ;
		us_tager->ProbeID		= this->ProbeID;
		
		us_tager->EA			= this->EA ;		
		us_tager->Elements		= this->Elements;
		us_tager->Pitch			= this->Pitch;
		us_tager->Radius		= this->Radius ;
		us_tager->Probe_Angle	= this->Probe_Angle ;
		us_tager->TxOffset		= this->TxOffset;

		us_tager->Motor_Radius 	= this->Motor_Radius;
		us_tager->Frames3D 		= this->Frames3D;
		
		us_tager->Frame_Index 	= this->Frame_Index;
		us_tager->Focus_Spacing = this->Focus_Spacing;
		us_tager->Focus_Depth 	= this->Focus_Depth;
		us_tager->Extra_int32_1 = this->Extra_int32_1;
		us_tager->Extra_int32_2 = this->Extra_int32_2;

		us_tager->Extra_int32_3 = this->Extra_int32_3;
		us_tager->Extra_int32_4 = this->Extra_int32_4;
		us_tager->Extra_int32_5 = this->Extra_int32_5;


		us_tager->Motor_Dir 	= this->Motor_Dir;
		us_tager->Focus_Count 	= this->Focus_Count;
		us_tager->Extra_int8_1 	= this->Extra_int8_1;
		us_tager->Extra_int8_2 	= this->Extra_int8_2;
		us_tager->Extra_int8_3 	= this->Extra_int8_3;

				
		igtl_US_Tag_convert_byte_order(us_tager);
		
		return 1;
	}
	
	/// Unpack US Message
	int USMessage::UnpackBody()
	{
		igtl::ImageMessage::UnpackBody();

		/// cannon96 :: Check the size of extra data-filed of USMessage
		/*int s0(this->GetPackBodySize() );
		int s1(this->GetSubVolumeImageSize());
		int diff(s0-s1);*/

		if((this->GetPackBodySize() -this->GetSubVolumeImageSize()) == 169) /// USMessage version 2.0
		{
			m_USTag = &m_Image[GetSubVolumeImageSize()];
			igtl_US_tag* us_tager = (igtl_US_tag*) m_USTag;
			igtl_US_Tag_convert_byte_order(us_tager);
		
			this->Type				= 2;//us_tager->Type;
			this->Txf				= us_tager->Txf ;		
			this->Sf				= us_tager->Sf;
			this->FPS				= us_tager->FPS ;
			this->Lden				= us_tager->Lden ;
			this->SAng				= us_tager->SAng ;
			this->ProbeID			= us_tager->ProbeID;
		
			this->EA				= us_tager->EA ;		
			this->Elements			= us_tager->Elements;
			this->Pitch				= us_tager->Pitch;
			this->Radius			= us_tager->Radius ;
			this->Probe_Angle		= us_tager->Probe_Angle ;
			this->TxOffset			= us_tager->TxOffset;

			this->Motor_Radius 		= us_tager->Motor_Radius;
			this->Frames3D 			= us_tager->Frames3D;
		
			this->Frame_Index 		= us_tager->Frame_Index;
			this->Focus_Spacing		= us_tager->Focus_Spacing;
			this->Focus_Depth 		= us_tager->Focus_Depth;
			this->Extra_int32_1		= us_tager->Extra_int32_1;
			this->Extra_int32_2		= us_tager->Extra_int32_2;

			this->Extra_int32_3		= us_tager->Extra_int32_3;
			this->Extra_int32_4		= us_tager->Extra_int32_4;
			this->Extra_int32_5		= us_tager->Extra_int32_5;


			this->Motor_Dir 		= us_tager->Motor_Dir;
			this->Focus_Count 		= us_tager->Focus_Count;
			this->Extra_int8_1 		= us_tager->Extra_int8_1;
			this->Extra_int8_2 		= us_tager->Extra_int8_2;
			this->Extra_int8_3 		= us_tager->Extra_int8_3;
		}
		else if((this->GetPackBodySize() -this->GetSubVolumeImageSize()) == 124) /// USMessage version 1.0
		{
			m_USTag = &m_Image[GetSubVolumeImageSize()];
			igtl_US_tag1* us_tager = (igtl_US_tag1*) m_USTag;
			igtl_US_Tag1_convert_byte_order(us_tager);
		
			this->Type				= 1;//us_tager->Type;
			this->Txf				= us_tager->Txf ;		
			this->Sf				= us_tager->Sf;
			this->FPS				= us_tager->FPS ;
			this->Lden				= us_tager->Lden ;
			this->SAng				= us_tager->SAng ;
			this->ProbeID			= us_tager->ProbeID;
		
			this->EA				= us_tager->EA ;		
			this->Elements			= us_tager->Elements;
			this->Pitch				= us_tager->Pitch;
			this->Radius			= us_tager->Radius ;
			this->Probe_Angle		= us_tager->Probe_Angle ;
			this->TxOffset			= us_tager->TxOffset;

			this->Motor_Radius 		= 0;
			this->Frames3D 			= 0;
		
			this->Frame_Index 		= 0;
			this->Focus_Spacing		= 0;
			this->Focus_Depth 		= 0;
			this->Extra_int32_1		= 0;
			this->Extra_int32_2		= 0;

			this->Extra_int32_3		= 0;
			this->Extra_int32_4		= 0;
			this->Extra_int32_5		= 0;


			this->Motor_Dir 		= 0;
			this->Focus_Count 		= 0;
			this->Extra_int8_1 		= 0;
			this->Extra_int8_2 		= 0;
			this->Extra_int8_3 		= 0;
		}
		else
		{
			this->Type				= 0;
			this->Txf				= 0;		
			this->Sf				= 0;
			this->FPS				= 0;
			this->Lden				= 0;
			this->SAng				= 0;
			this->ProbeID			= 0;
		
			this->EA				= 0;		
			this->Elements			= 0;
			this->Pitch				= 0;
			this->Radius			= 0;
			this->Probe_Angle		= 0;
			this->TxOffset			= 0;

			this->Motor_Radius 		= 0;
			this->Frames3D 			= 0;
		
			this->Frame_Index 		= 0;
			this->Focus_Spacing		= 0;
			this->Focus_Depth 		= 0;
			this->Extra_int32_1		= 0;
			this->Extra_int32_2		= 0;

			this->Extra_int32_3		= 0;
			this->Extra_int32_4		= 0;
			this->Extra_int32_5		= 0;


			this->Motor_Dir 		= 0;
			this->Focus_Count 		= 0;
			this->Extra_int8_1 		= 0;
			this->Extra_int8_2 		= 0;
			this->Extra_int8_3 		= 0;
		}

		return 1;
	}
} //namespace igtl