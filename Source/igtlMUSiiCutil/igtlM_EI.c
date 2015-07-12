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

#include "igtlM_EI.h"
#include <igtl_util.h>

void igtlM_export igtl_EITag_convert_byte_order(igtl_EI_tag * tag)
{
	igtl_uint32 tmp;
	
	if(igtl_is_little_endian())
	{
		tmp = (igtl_uint32) (tag->ImgAng);
		tmp = BYTE_SWAP_INT32(tmp);
		tmp = (igtl_uint32) (tag->ACC);
		tmp = BYTE_SWAP_INT32(tmp);
		tmp = (igtl_uint32) (tag->BroderWidth);
		tmp = BYTE_SWAP_INT32(tmp);
		tmp = (igtl_uint32) (tag->AveStrain);
		tmp = BYTE_SWAP_INT32(tmp);
		tmp = (igtl_uint32) (tag->RecDelay);
		tmp = BYTE_SWAP_INT32(tmp);
	}
}

igtl_uint64 igtl_EI_get_crc(igtl_image_header *header, void* image, igtl_EI_tag * tag)
{
	igtl_uint64 crc;
	
	crc = igtl_image_get_crc(header, image);
	crc = crc64( (unsigned char*) tag, (int) IGTL_EI_TAG_SIZE, crc);
	
	return crc;
}