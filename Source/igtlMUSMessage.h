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

/*!
 *  \brief This is a test class.
 *
 * Some details about the Test class
 */




#ifndef __igtlUSMessage_h
#define __igtlUSMessage_h




#include <igtlObject.h>
#include <igtlMacro.h>
#include <igtlMath.h>
#include <igtlImageMessage.h>
//#include "igtlMUSiiCutil/igtlM_US.h"
#include "igtlM_US.h"


namespace igtl
{
	/*! 
	 *  \brief This is a test class. Before
	 *
	 * Some details about the Test class
	 */
	class IGTLMCommon_EXPORT USMessage: public igtl::ImageMessage
	
	//class USMessage: public igtl::ImageMessage
	{
		public:
			typedef USMessage						Self;
			typedef igtl::ImageMessage				Superclass;
			typedef igtl::SmartPointer<Self>		Pointer;
			typedef igtl::SmartPointer<const Self>	ConstPointer;
			
			igtlTypeMacro(igtl::USMessage, igtl::ImageMessage)
			igtlNewMacro(igtl::USMessage);
		
		public:
			void SetUSDataType(USDatatypes type){Type =type;};
			void SetTransmitFrequency(int txf){ Txf = txf;};
			void SetSamplingFrequency(int sf){Sf = sf;};
			void SetFPS(int fps){FPS = fps;};
			void SetLineDensity(int ld){Lden = ld;};

			void SetSteeringAngle(int sa){SAng = sa;};
			void SetProbeID(int id){ProbeID = id;};
			void SetExtensionAngle(int ea){ EA = ea;};
			void SetElements(int num){Elements = num;};
			void SetPitch(int pitch){Pitch = pitch;};

			void SetRadius(int r){Radius = r;};
			void SetProbeAngle(int pa){Probe_Angle = pa;};
			void SetTxOffset(int txoffset){TxOffset = txoffset;};
			//____________________________________________________________________________________________________________
			void SetMotor_Radius(int motor_radius){Motor_Radius = motor_radius;};
			void SetFrames3D(int frames3D){Frames3D = frames3D;};

			void SetFrameIndex(int frameIndex){Frame_Index = frameIndex;};
			void SetFocusSpacing(int focusSp){Focus_Spacing = focusSp;};
			void SetFocusDepth(int focusDep){Focus_Depth = focusDep;};
			void SetExtraInt32_1(int extra_int32_1){Extra_int32_1 = extra_int32_1;};
			void SetExtraInt32_2(int extra_int32_2){Extra_int32_2 = extra_int32_2;};

			void SetExtraInt32_3(int extra_int32_3){Extra_int32_3 = extra_int32_3;};
			void SetExtraInt32_4(int extra_int32_4){Extra_int32_4 = extra_int32_4;};
			void SetExtraInt32_5(int extra_int32_5){Extra_int32_5 = extra_int32_5;};

			void SetMotor_Dir(char dir){Motor_Dir = dir;};
			void SetFocus_Count(char focusCount){Focus_Count = focusCount;};
			void SetExtra_int8_1(char extra_int8_1){Extra_int8_1 = extra_int8_1;};
			void SetExtra_int8_2(char extra_int8_2){Extra_int8_2 = extra_int8_2;};
			void SetExtra_int8_3(char extra_int8_3){Extra_int8_3 = extra_int8_3;};
			
			////////////////////////////////////////////////////////////////////////////////////
			int GetUSDataType(){return Type;};
			int GetTransmitFrequency(){ return Txf;};
			int GetSamplingFrequency(){ return Sf;};
			int GetFPS(){ return FPS;};
			int GetLineDensity(){ return Lden;};
			int GetSteeringAngle(){ return SAng;};
			int GetProbeID(){ return ProbeID;};
			
			int GetExtensionAngle(){ return EA;};
			int GetElements(){ return Elements;};
			int GetPitch(){ return Pitch;};
			int GetRadius(){ return Radius;};
			int GetProbeAngle(){ return Probe_Angle;};
			int GetTxOffset(){ return TxOffset;};
			//____________________________________________________________________________________________________________
			int GetMotor_Radius(){ return Motor_Radius;};
			int GetFrames3D(){ return Frames3D;};

			int GetFrameIndex(){ return Frame_Index;};
			int GetFocusSpacing(){ return Focus_Spacing;};
			int GetFocusDepth(){ return Focus_Depth;};
			int GetExtraInt32_1(){ return Extra_int32_1;};
			int GetExtraInt32_2(){ return Extra_int32_2;};

			int GetExtraInt32_3(){ return Extra_int32_3;};
			int GetExtraInt32_4(){ return Extra_int32_4;};
			int GetExtraInt32_5(){ return Extra_int32_5;};

			char GetMotor_Dir(){ return Motor_Dir;};
			char GetFocus_Count(){ return Focus_Count;};
			char GetExtra_int8_1(){ return Extra_int8_1;};
			char GetExtra_int8_2(){ return Extra_int8_2;};
			char GetExtra_int8_3(){ return Extra_int8_3;};

		
		protected:
			USMessage();
			~USMessage();
		
		protected:
			virtual int GetBodyPackSize();
			virtual int PackBody();
			virtual int UnpackBody();
		
		protected:
			int Type;			///< Data type - data types can also be determinned by file extensions.
			int Txf;			///< transmit frequency of ultrasound probe
			int Sf;				///< sampling frequency of ultrasound machine
			int FPS;			///< frame rate or pulse repetition period in Doppler modes
			int Lden;			///< Line density: can be used to calculate elment spacing if potch and native # elements is known

			int SAng;			///< Steering Angle of Ultrasound image
			int ProbeID;		///< ID of ultrasound probe
			int EA;				///< Extension Angle
			int Elements;		///< The number of elements in the probe that acquire the image
			int Pitch;			///< The spacing between elements of the probe that acquired the image
			
			int Radius;			///< The curvature of the probe that acquired the image
			int Probe_Angle;	///< The field of view of the probe that acquired the image. (Phased array)
			int TxOffset; 		///< For phased array, the number of elements that are offset in the steered image

			//____________________________________________________________________________________________________________
			int Motor_Radius;    ///< Motor_Radius of 3D Probe
			int Frames3D;        ///< The number of RF-Frames of 3D RF-Volume

			int Frame_Index;	 ///< The index of RF-Frame in 3D RF-Volume
			int Focus_Spacing;   ///< Focus_Spcaing // unit is um
			int Focus_Depth;     ///< Depth of Focus point // unit is um
			int Extra_int32_1;   ///< TBD
			int Extra_int32_2;   ///< TBD

			int Extra_int32_3;   ///< TBD
			int Extra_int32_4;   ///< TBD
			int Extra_int32_5;   ///< TBD

			char  Motor_Dir;       ///< The Direction of 2D fram in 3D Volume
			char  Focus_Count;     ///< The number of Focus point
			char  Extra_int8_1;    ///< TBD
			char  Extra_int8_2;    ///< TBD
			char  Extra_int8_3;    ///< TBD
			
			unsigned char* m_USTag;
		
	};	

	/*! \class Test class.h "inc/class.h"
	 *  \brief This is a test class. after
	 *
	 * Some details about the Test class
	 */
}

/*! 
*  \brief This is a test class. after2
*
* Some details about the Test class
*/
#endif  // _igtlEIMessage


/*! 
*  \brief This is a test class. after3
*
* Some details about the Test class
*/