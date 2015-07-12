/*=========================================================================

  Program:   OpenIGTLink Library
  Module:    $RCSfile$
  Language:  C
  Date:      $Date: 2009-11-17 22:53:00 -0500 (Tue, 17 Nov 2009) $
  Version:   $Revision: 5366 $

  Copyright (c) Insight Software Consortium. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
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

#ifndef __IGTL_EI_H
#define __IGTL_EI_H

//#include "igtl_win32header.h"
#include "igtlM_win32header.h"
#include "igtl_util.h"
#include "igtl_types.h"
#include "igtl_image.h"

#define IGTL_EI_TAG_SIZE 20

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)     /* For 1-byte boundary in memroy */


typedef struct 
{     
	    igtl_float32 	ImgAng;
		igtl_float32 	ACC;
		igtl_float32 	BroderWidth;
		igtl_float32 	AveStrain;
		igtl_float32 	RecDelay;	
} igtl_EI_tag;

#pragma pack()

/*
 * Byte order conversion dor the tag structure
 *
 * This function converts endianness of each member variable
 * in igtl_EI_tag from host byte order to network byte order, or
 * vice versa.
 */

void igtlM_export igtl_EITag_convert_byte_order(igtl_EI_tag * tag);

/*
* CRC calculation
*
* This function calculates CRC of EI Data including header and tag
*
*/
igtl_uint64 igtl_EI_get_crc(igtl_image_header *header, void* image, igtl_EI_tag* tag);

#ifdef __cplusplus
}
#endif

#endif /* __IGTL_EI_H */