/*=========================================================================

  Program:   OpenIGTLink Library
  Module:    $HeadURL: http://svn.na-mic.org/NAMICSandBox/trunk/OpenIGTLink/Source/igtlutil/igtl_win32header.h $
  Language:  C
  Date:      $Date: 2010-01-17 13:38:05 -0500 (2010-01-17, 일) $
  Version:   $Revision: 5577 $

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

#ifndef __IGTLM_WIN32HEADER_H
#define __IGTLM_WIN32HEADER_H

#include "igtlM_typeconfig.h"

#if (defined(_WIN32) || defined(WIN32)) // && !defined(IGTLSTATIC) 
# ifdef IGTLMCommon_EXPORTS
#  define igtlM_export __declspec(dllexport)
#  define IGTLMCommon_EXPORT __declspec(dllexport)
# else
#  define igtlM_export __declspec(dllimport)
#  define IGTLMCommon_EXPORT __declspec(dllimport)
# endif  /* igtl_common_exports */
#else
/* unix needs nothing */
#define igtlM_export
#define IGTLMCommon_EXPORT 
#endif

#if defined(_WIN32)
#  include <windows.h>
#endif

#if defined(_MSC_VER)
  // Enable MSVC compiler warning messages that are useful but off by default.
#  pragma warning ( disable : 4996 ) /* 'strncpy': This function or variable may be unsafe. */
#endif


#endif /*__IGTL_WIN32HEADER_H*/
