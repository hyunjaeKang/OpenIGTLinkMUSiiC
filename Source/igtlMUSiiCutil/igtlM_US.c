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

#include <string.h>
#include <math.h>

#include "igtlM_US.h"
#include <igtl_util.h>

void igtlM_export igtl_US_Tag_convert_byte_order(igtl_US_tag * tag)
{
	//igtl_uint32 tmp;
	
	if(igtl_is_little_endian())
	{
		tag->Type			= BYTE_SWAP_INT32(tag->Type);
		tag->Txf 			= BYTE_SWAP_INT32(tag->Txf);
		tag->Sf 			= BYTE_SWAP_INT32(tag->Sf);
		tag->FPS 			= BYTE_SWAP_INT32(tag->FPS);
		tag->Lden 			= BYTE_SWAP_INT32(tag->Lden);

		tag->SAng 			= BYTE_SWAP_INT32(tag->SAng);
		tag->ProbeID 		= BYTE_SWAP_INT32(tag->ProbeID);
		tag->EA 			= BYTE_SWAP_INT32(tag->EA);
		tag->Elements 		= BYTE_SWAP_INT32(tag->Elements);
		tag->Pitch 			= BYTE_SWAP_INT32(tag->Pitch);
		
		tag->Radius 		= BYTE_SWAP_INT32(tag->Radius);
		tag->Probe_Angle 	= BYTE_SWAP_INT32(tag->Probe_Angle);
		tag->TxOffset 		= BYTE_SWAP_INT32(tag->TxOffset);
		//____________________________________________________
		tag->Motor_Radius 	= BYTE_SWAP_INT32(tag->Motor_Radius);
		tag->Frames3D 		= BYTE_SWAP_INT32(tag->Frames3D);
		
		tag->Frame_Index 	= BYTE_SWAP_INT32(tag->Frame_Index);
		tag->Focus_Spacing 	= BYTE_SWAP_INT32(tag->Focus_Spacing);
		tag->Focus_Depth 	= BYTE_SWAP_INT32(tag->Focus_Depth);
		tag->Extra_int32_1 	= BYTE_SWAP_INT32(tag->Extra_int32_1);
		tag->Extra_int32_2 	= BYTE_SWAP_INT32(tag->Extra_int32_2);

		tag->Extra_int32_3 	= BYTE_SWAP_INT32(tag->Extra_int32_3);
		tag->Extra_int32_4 	= BYTE_SWAP_INT32(tag->Extra_int32_4);
		tag->Extra_int32_5 	= BYTE_SWAP_INT32(tag->Extra_int32_5);


		tag->Motor_Dir 		= tag->Motor_Dir;
		tag->Focus_Count 	= tag->Focus_Count;
		tag->Extra_int8_1 	= tag->Extra_int8_1;
		tag->Extra_int8_2 	= tag->Extra_int8_2;
		tag->Extra_int8_3 	= tag->Extra_int8_3;
	}
}

/// For USMessage version 1.0
void igtlM_export igtl_US_Tag1_convert_byte_order(igtl_US_tag1 * tag)
{
	//igtl_uint32 tmp;
	
	if(igtl_is_little_endian())
	{
		tag->Type			= BYTE_SWAP_INT32(tag->Type);
		tag->Txf 			= BYTE_SWAP_INT32(tag->Txf);
		tag->Sf 			= BYTE_SWAP_INT32(tag->Sf);
		tag->FPS 			= BYTE_SWAP_INT32(tag->FPS);
		tag->Lden 			= BYTE_SWAP_INT32(tag->Lden);

		tag->SAng 			= BYTE_SWAP_INT32(tag->SAng);
		tag->ProbeID 		= BYTE_SWAP_INT32(tag->ProbeID);
		tag->EA 			= BYTE_SWAP_INT32(tag->EA);
		tag->Elements 		= BYTE_SWAP_INT32(tag->Elements);
		tag->Pitch 			= BYTE_SWAP_INT32(tag->Pitch);
		
		tag->Radius 		= BYTE_SWAP_INT32(tag->Radius);
		tag->Probe_Angle 	= BYTE_SWAP_INT32(tag->Probe_Angle);
		tag->TxOffset 		= BYTE_SWAP_INT32(tag->TxOffset);
		
	}
}

igtl_uint64 igtl_US_get_crc(igtl_image_header *header, void* image, igtl_US_tag * tag)
{
	igtl_uint64 crc;
	
	crc = igtl_image_get_crc(header, image);
	crc = crc64( (unsigned char*) tag, (int) IGTL_US_TAG_SIZE, crc);
	
	return crc;
}