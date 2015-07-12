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

#ifndef __IGTL_FILE_H
#define __IGTL_FILE_H

//#include "igtl_win32header.h"
#include "igtlM_win32header.h"
#include "igtl_util.h"
#include "igtl_types.h"

#define IGTL_FILE_NAME_SIZE				256	
#define IGTL_FILE_HEADER_SIZE			260

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)     /* For 1-byte boundary in memroy */
typedef struct 
{
	char 			Filename[256];
	int				FileSize;
}igtl_File_tag;
#pragma pack()

///*
// * Byte order conversion dor the tag structure
// *
// * This function converts endianness of each member variable
// * in igtl_File_tag from host byte order to network byte order, or
// * vice versa.
// */

void igtlM_export igtl_File_Tag_convert_byte_order(igtl_File_tag* tag);

/*
* CRC calculation
*
* This function calculates CRC of EI Data including header and tag
*
*/

igtl_uint64 igtl_FILE_get_crc(igtl_uint32 msglen, const char* msg);

#ifdef __cplusplus
}
#endif

#endif /* __IGTL_US_H */