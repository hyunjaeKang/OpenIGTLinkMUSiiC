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

#ifndef __IGTL_US_H
#define __IGTL_US_H

//#include "igtl_win32header.h"
#include "igtlM_win32header.h"
#include "igtl_util.h"
#include "igtl_types.h"
#include "igtl_image.h"

//#define IGTL_US_TAG_SIZE 52
#define IGTL_US_TAG_SIZE 97

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)     /* For 1-byte boundary in memroy */

enum USDatatypes
{
    /// Screen Capture Image   : *.png , 32bit
	udtScreen           = 0x00000001,
    /// Pre Scan Convert       : *.bpr ,  8bit
	udtBPre             = 0x00000002,
    /// Scan converted         :  *.b8 ,  8bit
	udtBPost            = 0x00000004,
    /// Scan converted         : *.b32 , 32bit
	udtBPost32          = 0x00000008,    
    /// Radio Frequency        :  *.rf , 16bit
	udtRF               = 0x00000010,
    /// M-mode Pre Scan        : *.mpr ,  8bit
	udtMPre             = 0x00000020,
    /// M-mode Scan converted  :   *.m ,  8bit
	udtMPost            = 0x00000040,
    /// 					   :  *.drf, 16bit
	udtPWRF             = 0x00000080,
    /// 					   :   *.pw,  8bit
	udtPWSpectrum       = 0x00000100,
    /// 					   :  *.crf, 16bit
	udtColorRF          = 0x00000200,
    /// Coloe+B-Mode Image     : *.col , 32bit
	udtColorPost        = 0x00000400,
    /// 					   : *.*   ,  ?bit
	udtColorSigma       = 0x00000800,
    /// Color Velocity/variance:  *.cw , 16bit
	udtColorVelocity    = 0x00001000
};

typedef struct 
{     
	    igtl_int32 Type;			// data types can also be determined by file extension
		igtl_int32 Txf;				// transmit frequency of ultrasound probe
		igtl_int32 Sf;				// sampling frequency of ultrasound machine
		igtl_int32 FPS;				// frame rate or pulse repetition period in Doppler modes
		igtl_int32 Lden;			// Line density: can be used to calculate elment spacing if potch and native # elements is known

		igtl_int32 SAng;			// Steering Angle of Ultrasound image
		igtl_int32 ProbeID;			// ID of ultrasound probe
		igtl_int32 EA;				// Extension Angle
		igtl_int32 Elements;		// The number of elements in the probe that acquire the image
		igtl_int32 Pitch;			// The spacing between elements of the probe that acquired the image
		
		igtl_int32 Radius;			// The curvature of the probe that acquired the image
		igtl_int32 Probe_Angle;		// The field of view of the probe that acquired the image. (Phased array)
		igtl_int32 TxOffset; 		// For phased array, the number of elements that are offset in the steered image
		//____________________________________________________________________________________________________________
		igtl_int32 Motor_Radius;    // Motor_Radius of 3D Probe
		igtl_int32 Frames3D;        // The number of RF-Frames of 3D RF-Volume

		igtl_int32 Frame_Index;   // The index of RF-Frame in 3D RF-Volume
		igtl_int32 Focus_Spacing;   // Focus_Spcaing // unit is um
		igtl_int32 Focus_Depth;     // Depth of Focus point // unit is um
		igtl_int32 Extra_int32_1;   // TBD
		igtl_int32 Extra_int32_2;   // TBD

		igtl_int32 Extra_int32_3;   // TBD
		igtl_int32 Extra_int32_4;   // TBD
		igtl_int32 Extra_int32_5;   // TBD

		igtl_int8  Motor_Dir;       // The Direction of 2D fram in 3D Volume
		igtl_int8  Focus_Count;     // The number of Focus point
		igtl_int8  Extra_int8_1;    // TBD
		igtl_int8  Extra_int8_2;    // TBD
		igtl_int8  Extra_int8_3;    // TBD

} igtl_US_tag;

typedef struct 
{     
	    igtl_int32 Type;			// data types can also be determined by file extension
		igtl_int32 Txf;				// transmit frequency of ultrasound probe
		igtl_int32 Sf;				// sampling frequency of ultrasound machine
		igtl_int32 FPS;				// frame rate or pulse repetition period in Doppler modes
		igtl_int32 Lden;			// Line density: can be used to calculate elment spacing if potch and native # elements is known

		igtl_int32 SAng;			// Steering Angle of Ultrasound image
		igtl_int32 ProbeID;			// ID of ultrasound probe
		igtl_int32 EA;				// Extension Angle
		igtl_int32 Elements;		// The number of elements in the probe that acquire the image
		igtl_int32 Pitch;			// The spacing between elements of the probe that acquired the image
		
		igtl_int32 Radius;			// The curvature of the probe that acquired the image
		igtl_int32 Probe_Angle;		// The field of view of the probe that acquired the image. (Phased array)
		igtl_int32 TxOffset; 		// For phased array, the number of elements that are offset in the steered image
		//____________________________________________________________________________________________________________

} igtl_US_tag1;

#pragma pack()

/*
 * Byte order conversion dor the tag structure
 *
 * This function converts endianness of each member variable
 * in igtl_EI_tag from host byte order to network byte order, or
 * vice versa.
 */

/// For USMessage :: Version 2.0
void igtlM_export igtl_US_Tag_convert_byte_order(igtl_US_tag * tag);

/// For USMessage :: Version 1.0
void igtlM_export igtl_US_Tag1_convert_byte_order(igtl_US_tag1 * tag);

/*
* CRC calculation
*
* This function calculates CRC of EI Data including header and tag
*
*/
igtl_uint64 igtl_US_get_crc(igtl_image_header *header, void* image, igtl_US_tag* tag);

#ifdef __cplusplus
}
#endif

#endif /* __IGTL_US_H */