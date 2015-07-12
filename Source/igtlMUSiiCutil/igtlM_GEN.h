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

#ifndef __IGTL_GEN_H
#define __IGTL_GEN_H

//#include "igtl_win32header.h"
#include "igtlM_win32header.h"
#include "igtl_util.h"
#include "igtl_types.h"


//#define IGTL_US_TAG_SIZE 52

#ifdef __cplusplus
extern "C" {
#endif

/*
* CRC calculation
*
* This function calculates CRC of EI Data including header and tag
*
*/
igtl_uint64 igtl_GEN_get_crc(igtl_uint32 msglen, const char* msg);

#ifdef __cplusplus
}
#endif

#endif /* __IGTL_US_H */