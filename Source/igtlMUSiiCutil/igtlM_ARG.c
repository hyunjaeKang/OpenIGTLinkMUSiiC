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

#include "igtlM_ARG.h"
#include <igtl_util.h>


igtl_uint64 igtl_ARG_get_crc(igtl_uint32 msglen, const char* msg)
{
	igtl_uint64 crc = crc64(0, 0, 0);

	crc = crc64((unsigned char*)msg, msglen, crc);

	return crc;
}