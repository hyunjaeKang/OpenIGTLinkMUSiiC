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

#include "MUSiiCIGTLUtil.h"
#include <cmath>

namespace igtl
{

double IGTLMCommon_EXPORT GetIGTLTimeStamp(igtl::MessageBase::Pointer msg)
{

	unsigned int Sec(0),NanoSec(0);
	msg->GetTimeStamp(&Sec, &NanoSec);
	double tm(static_cast<double>(Sec) + static_cast<double>(NanoSec) / 1e9);
	return tm;
}

double IGTLMCommon_EXPORT GetIGTLTimeStamp2(igtl::MessageBase::Pointer msg)
{
	double ts(0.0);
	if(msg.IsNotNull())
	{
		igtl::TimeStamp::Pointer timestamp = igtl::TimeStamp::New();
		msg->GetTimeStamp(timestamp);
		ts = timestamp->GetTimeStamp();
		if(ts<0.1)
		{
			timestamp->GetTime();
			ts = timestamp->GetTimeStamp();
		}
	}
	
	return ts;
}


igtl::TrackingDataElement::Pointer IGTLMCommon_EXPORT ExtractTrackingDataElement(igtl::MessageBase::Pointer msg, int index)
{
	if(msg.IsNotNull())
	{
		igtl::TrackingDataMessage::Pointer tracker;
		tracker = RetrieveMessage<igtl::TrackingDataMessage::Pointer, igtl::TrackingDataMessage>(msg);

		if(tracker.IsNotNull())
		{
			igtl::TrackingDataElement::Pointer trackingData;
			tracker->GetTrackingDataElement(index, trackingData);
			return trackingData;
		}
	}
	
	return NULL;
}

void IGTLMCommon_EXPORT MatrixMultiplication(igtl::Matrix4x4& matA, igtl::Matrix4x4& matB, igtl::Matrix4x4& matC)
{
	int i, j, k;
	/// Initialize 

	for(i=0; i<4; i++)
		for(j=0; j<4;j++)
			matC[i][j] = 0.0;

	//matC = matA x matB
	for(i=0; i<4; i++)
		for(j=0; j<4;j++)
			for(k=0; k<4; k++)
				matC[i][j] = matC[i][j] + (matA[i][k]*matB[k][j]);
}

void IGTLMCommon_EXPORT DuplicateMatrix(igtl::Matrix4x4& matDest, igtl::Matrix4x4& matSrc)
{
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			matDest[i][j] = matSrc[i][j];
}

igtl::ImageMessage::Pointer IGTLMCommon_EXPORT DuplicateImageMessage(igtl::ImageMessage::Pointer img)
{
	igtl::ImageMessage::Pointer img2 = igtl::ImageMessage::New();
	int x,y,z, dimi,dimj,dimk, offi,offj,offk;
	float sx, sy, sz;
	float matrix[4][4];
	/// Get Information 
	img->GetDimensions(x,y,z); ///
	img->GetSpacing(sx,sy,sz); ///
	int type = img->GetScalarType(); ////
	const char* devicename = img->GetDeviceName();
	img->GetSubVolume(dimi,dimj,dimk, offi,offj,offk);
	img->GetMatrix(matrix);
	
	img2->SetDimensions(x,y,z);
	img2->SetSpacing(sz,sy,sz);
	img2->SetScalarType(type);
	img2->SetSubVolume(dimi,dimj,dimk, offi,offj,offk);
	img2->SetDeviceName(devicename);
	img2->SetMatrix(matrix);
	img2->AllocateScalars();

	memcpy(img2->GetScalarPointer(), img->GetScalarPointer(), img2->GetImageSize());

	return img2;

}

igtl::MessageBase::Pointer IGTLMCommon_EXPORT RetriveMessageBase(igtl::MessageHeader::Pointer header, igtl::MessageBase::Pointer msg)
{
	if(header.IsNull() || msg.IsNull())
		return NULL;
	// Check data type and receive data body
    if (strcmp(header->GetDeviceType(), "BIND") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::BindMessage::Pointer, igtl::BindMessage>(header,msg);
    }
    else if (strcmp(header->GetDeviceType(), "COLORTABLE") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::ColorTableMessage::Pointer, igtl::ColorTableMessage>(header,msg);
    }
    else if (strcmp(header->GetDeviceType(), "IMAGE") == 0)
    {
		std::string device(header->GetDeviceName());
		std::string us("US");
		std::string rf("RF");
		std::string ei("EI");
		if((device.find(us)!=std::string::npos) || (device.find(rf)!=std::string::npos))
		{
			return RetrieveMessagefromIODevice<igtl::USMessage::Pointer, igtl::USMessage>(header,msg);
		}
		else if(device.find(ei)!=std::string::npos)
		{
			return RetrieveMessagefromIODevice<igtl::EIMessage::Pointer, igtl::EIMessage>(header,msg);
		}
		else
			return RetrieveMessagefromIODevice<igtl::ImageMessage::Pointer, igtl::ImageMessage>(header,msg);
    }
    else if (strcmp(header->GetDeviceType(), "IMGMETA") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::ImageMetaMessage::Pointer, igtl::ImageMetaMessage>(header,msg);
	}
    else if (strcmp(header->GetDeviceType(), "LBMETA") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::LabelMetaMessage::Pointer, igtl::LabelMetaMessage>(header,msg);
    }
    else if (strcmp(header->GetDeviceType(), "NDARRAY") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::NDArrayMessage::Pointer, igtl::NDArrayMessage>(header,msg);
    }
    else if (strcmp(header->GetDeviceType(), "POINT") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::PointMessage::Pointer, igtl::PointMessage>(header,msg);
    }
	else if (strcmp(header->GetDeviceType(), "POSITION") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::PositionMessage::Pointer, igtl::PositionMessage>(header,msg);
    }
    else if (strcmp(header->GetDeviceType(), "QTDATA") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::QuaternionTrackingDataMessage::Pointer, igtl::QuaternionTrackingDataMessage>(header,msg);
	}
	else if (strcmp(header->GetDeviceType(), "STATUS") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::StatusMessage::Pointer, igtl::StatusMessage>(header,msg);
	}
	else if (strcmp(header->GetDeviceType(), "STRING") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::StringMessage::Pointer, igtl::StringMessage>(header,msg);
	}
	else if (strcmp(header->GetDeviceType(), "TDATA") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::TrackingDataMessage::Pointer, igtl::TrackingDataMessage>(header,msg);
	}
	else if (strcmp(header->GetDeviceType(), "TRANSFORM") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::TransformMessage::Pointer, igtl::TransformMessage>(header,msg);
	}
	else if (strcmp(header->GetDeviceType(), "TRAJ") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::TrajectoryMessage::Pointer, igtl::TrajectoryMessage>(header,msg);
	}
	else if (strcmp(header->GetDeviceType(), "GEN") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::GenMessage::Pointer, igtl::GenMessage>(header,msg);
	}
	else if (strcmp(header->GetDeviceType(), "ARGUMENTS") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::ArgMessage::Pointer, igtl::ArgMessage>(header,msg);
	}
	else if (strcmp(header->GetDeviceType(), "FILE") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::FileMessage::Pointer, igtl::FileMessage>(header,msg);
	}
	else if (strcmp(header->GetDeviceType(), "EIIMAGE") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::FixedImage::Pointer, igtl::FixedImage>(header,msg);
	}
	else if (strcmp(header->GetDeviceType(), "EIUSIMAGE") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::FixedImageBMODE::Pointer, igtl::FixedImageBMODE>(header,msg);
	}
	else 
	return 0;
}

//igtl::MessageBase::Pointer IGTLMCommon_EXPORT RetriveMessageBase(igtl::MessageBase::Pointer msg)
//{
//		// Check data type and receive data body
//    if (strcmp(msg->GetDeviceType(), "BIND") == 0)
//    {
//		return RetrieveMessagefromIODevice<igtl::BindMessage::Pointer, igtl::BindMessage>(msg);
//    }
//    else if (strcmp(msg->GetDeviceType(), "COLORTABLE") == 0)
//    {
//		return RetrieveMessagefromIODevice<igtl::ColorTableMessage::Pointer, igtl::ColorTableMessage>(msg);
//    }
//    else if (strcmp(msg->GetDeviceType(), "IMAGE") == 0)
//    {
//		std::string device(msg->GetDeviceName());
//		std::string us("US");
//		std::string rf("RF");
//		std::string ei("EI");
//		if((device.find(us)!=std::string::npos) || (device.find(rf)!=std::string::npos))
//		{
//			return RetrieveMessagefromIODevice<igtl::USMessage::Pointer, igtl::USMessage>(msg);
//		}
//		else if(device.find(ei)!=std::string::npos)
//		{
//			return RetrieveMessagefromIODevice<igtl::EIMessage::Pointer, igtl::EIMessage>(msg);
//		}
//		else
//			return RetrieveMessagefromIODevice<igtl::ImageMessage::Pointer, igtl::ImageMessage>(msg);
//    }
//    else if (strcmp(msg->GetDeviceType(), "IMGMETA") == 0)
//    {
//		return RetrieveMessagefromIODevice<igtl::ImageMetaMessage::Pointer, igtl::ImageMetaMessage>(msg);
//	}
//    else if (strcmp(msg->GetDeviceType(), "LBMETA") == 0)
//    {
//		return RetrieveMessagefromIODevice<igtl::LabelMetaMessage::Pointer, igtl::LabelMetaMessage>(msg);
//    }
//    else if (strcmp(msg->GetDeviceType(), "NDARRAY") == 0)
//    {
//		return RetrieveMessagefromIODevice<igtl::NDArrayMessage::Pointer, igtl::NDArrayMessage>(msg);
//    }
//    else if (strcmp(msg->GetDeviceType(), "POINT") == 0)
//    {
//		return RetrieveMessagefromIODevice<igtl::PointMessage::Pointer, igtl::PointMessage>(msg);
//    }
//	else if (strcmp(msg->GetDeviceType(), "POSITION") == 0)
//    {
//		return RetrieveMessagefromIODevice<igtl::PositionMessage::Pointer, igtl::PositionMessage>(msg);
//    }
//    else if (strcmp(msg->GetDeviceType(), "QTDATA") == 0)
//    {
//		return RetrieveMessagefromIODevice<igtl::QuaternionTrackingDataMessage::Pointer, igtl::QuaternionTrackingDataMessage>(msg);
//	}
//	else if (strcmp(msg->GetDeviceType(), "STATUS") == 0)
//    {
//		return RetrieveMessagefromIODevice<igtl::StatusMessage::Pointer, igtl::StatusMessage>(msg);
//	}
//	else if (strcmp(msg->GetDeviceType(), "STRING") == 0)
//    {
//		return RetrieveMessagefromIODevice<igtl::StringMessage::Pointer, igtl::StringMessage>(msg);
//	}
//	else if (strcmp(msg->GetDeviceType(), "TDATA") == 0)
//    {
//		return RetrieveMessagefromIODevice<igtl::TrackingDataMessage::Pointer, igtl::TrackingDataMessage>(msg);
//	}
//	else if (strcmp(msg->GetDeviceType(), "TRANSFORM") == 0)
//    {
//		return RetrieveMessagefromIODevice<igtl::TransformMessage::Pointer, igtl::TransformMessage>(msg);
//	}
//	else if (strcmp(msg->GetDeviceType(), "TRAJ") == 0)
//    {
//		return RetrieveMessagefromIODevice<igtl::TrajectoryMessage::Pointer, igtl::TrajectoryMessage>(msg);
//	}
//	else if (strcmp(msg->GetDeviceType(), "GEN") == 0)
//    {
//		return RetrieveMessagefromIODevice<igtl::GenMessage::Pointer, igtl::GenMessage>(msg);
//	}
//	else if (strcmp(msg->GetDeviceType(), "ARGUMENTS") == 0)
//    {
//		return RetrieveMessagefromIODevice<igtl::ArgMessage::Pointer, igtl::ArgMessage>(msg);
//	}
//	else if (strcmp(msg->GetDeviceType(), "FILE") == 0)
//    {
//		return RetrieveMessagefromIODevice<igtl::FileMessage::Pointer, igtl::FileMessage>(msg);
//	}
//	else if (strcmp(msg->GetDeviceType(), "EIIMAGE") == 0)
//    {
//		return RetrieveMessagefromIODevice<igtl::FixedImage::Pointer, igtl::FixedImage>(msg);
//	}
//	else if (strcmp(msg->GetDeviceType(), "EIUSIMAGE") == 0)
//    {
//		return RetrieveMessagefromIODevice<igtl::FixedImageBMODE::Pointer, igtl::FixedImageBMODE>(msg);
//	}
//	else 
//	return 0;
//}


bool IGTLMCommon_EXPORT SetReferenceData(igtl::MessageBase::Pointer msg)
{
	if(msg.IsNotNull())
	{
		std::string device(msg->GetDeviceName());
		std::string REF(M_REF_DATA);
		device = REF + device;
		msg->SetDeviceName(device.c_str());
		return true;
	}
	else
		return false;
}

bool IGTLMCommon_EXPORT IsReferenceData(igtl::MessageBase::Pointer msg)
{
	if(msg.IsNotNull())
	{
		std::string device(msg->GetDeviceName());
		int rs = device.find(M_REF_DATA);
		return (rs != std::string::npos)?true:false;
	}
	else
		return false;
}


bool IGTLMCommon_EXPORT SetSyncData(igtl::MessageBase::Pointer msg)
{
	if(msg.IsNotNull())
	{
		std::string device(msg->GetDeviceName());
		std::string SYNC(M_SYNC_DATA);
		device = SYNC + device;
		msg->SetDeviceName(device.c_str());
		return true;
	}
	else
		return false;
}

bool IGTLMCommon_EXPORT IsSyncData(igtl::MessageBase::Pointer msg)
{
	if(msg.IsNotNull())
	{
		std::string device(msg->GetDeviceName());
		int rs = device.find(M_SYNC_DATA);
		return (rs != std::string::npos)?true:false;
	}
	else
		return false;
}

bool IGTLMCommon_EXPORT IsImageMessage(igtl::MessageBase::Pointer msg)
{
	if(msg.IsNotNull())
	{
		std::string device(msg->GetDeviceType());
		int rs = device.find(IGTL_IMAGE);
		return (rs != std::string::npos)?true:false;
	}
	else
		return false;
}

bool IGTLMCommon_EXPORT IsTrackingDataMessage(igtl::MessageBase::Pointer msg)
{
	if(msg.IsNotNull())
	{
		std::string device(msg->GetDeviceType());
		//int rs = device.find(IGTL_TRACKING);
		//return (rs != std::string::npos)?true:false;
		if(device.find("TDATA") != std::string::npos)
			return true;
		else
			return false;

	}
	else
		return false;
}

/// For Testing OpenIGTLink, OpenIGTlinkMUSiiC

/// Get Dummy Matrix
void IGTLMCommon_EXPORT GetDummyMatrix1(igtl::Matrix4x4& matrix, bool print)
{
	matrix[0][0] = 1.0;  matrix[1][0] = 0.0;  matrix[2][0] = 0.0; matrix[3][0] = 0.0;
	matrix[0][1] = 0.0;  matrix[1][1] = -1.0;  matrix[2][1] = 0.0; matrix[3][1] = 0.0;
	matrix[0][2] = 0.0;  matrix[1][2] = 0.0;  matrix[2][2] = 1.0; matrix[3][2] = 0.0;
	matrix[0][3] = 0.0;  matrix[1][3] = 0.0;  matrix[2][3] = 0.0; matrix[3][3] = 1.0;
}

/// Get Dummy Matrix
void IGTLMCommon_EXPORT GetDummyMatrix2(igtl::Matrix4x4& matrix, bool print)
{
	matrix[0][0] = 1.0;  matrix[1][0] = 0.0;  matrix[2][0] = 0.0; matrix[3][0] = 0.0;
	matrix[0][1] = 0.0;  matrix[1][1] = 1.0;  matrix[2][1] = 0.0; matrix[3][1] = 0.0;
	matrix[0][2] = 0.0;  matrix[1][2] = 0.0;  matrix[2][2] = 1.0; matrix[3][2] = 0.0;
	matrix[0][3] = 10.0;  matrix[1][3] = 10.0;  matrix[2][3] = 1000.0; matrix[3][3] = 1.0;
}

igtl::MessageBase::Pointer IGTLMCommon_EXPORT GetDummyImageMessage(int x, int y, int z, float sx, float sy, float sz)
{ 
	igtl::ImageMessage::Pointer img = igtl::ImageMessage::New();
	/// Set Dimension of ImageMessage
	img->SetDimensions(x,y,z);
	/// Set Spacing value of ImageMessage
	img->SetSpacing(sz, sy, sz);
	/// Set SubVolume of ImageMessage
	img->SetSubVolume(x,y,z,0,0,0);
	/// Set Device Name
	img->SetDeviceName("Dummy_Image");
	/// Set TimeStamp
	igtl::TimeStamp::Pointer ts = igtl::TimeStamp::New();
	//ts->GetTime();
	ts->SetTime(GetQueryTimeStampDouble());
	img->SetTimeStamp(ts);
	/// Allocate Memory Space for this ImageMessage
	img->AllocateScalars();
	/// Set Matrix
	igtl::Matrix4x4 matrix;
	GetDummyMatrix1(matrix);
	img->SetMatrix(matrix);

	/// Set Data

	igtl::Sleep(30);
	/// Return ImageMessage with the pointer MessageBase
	return (igtl::MessageBase::Pointer) img;

}

igtl::MessageBase::Pointer IGTLMCommon_EXPORT GetDummyStringMessage(std::string msg)
{
	igtl::StringMessage::Pointer str = igtl::StringMessage::New();
	str->SetDeviceName("Dummy_StringMessage");
	str->SetString(msg);
	/// Set TimeStamp
	igtl::TimeStamp::Pointer ts = igtl::TimeStamp::New();
	//ts->GetTime();
	//ts->SetTime(GetTimeStampDouble());
	ts->SetTime(GetQueryTimeStampDouble());
	str->SetTimeStamp(ts);

	igtl::Sleep(20);
	/// Return ImageMessage with the pointer MessageBase
	return (igtl::MessageBase::Pointer) str;
}

igtl::MessageBase::Pointer IGTLMCommon_EXPORT GetDummyTrackingDataMessage()
{
	igtl::TrackingDataMessage::Pointer track = igtl::TrackingDataMessage::New();
	track->SetDeviceName("Dummy_TrackingDataMsg");
	igtl::TimeStamp::Pointer ts = igtl::TimeStamp::New();
	//ts->GetTime();
	//ts->SetTime(GetTimeStampDouble());
	ts->SetTime(GetQueryTimeStampDouble());
	track->SetTimeStamp(ts);

	igtl::Matrix4x4 matrix;

	igtl::TrackingDataElement::Pointer trackElement0;
	trackElement0 = igtl::TrackingDataElement::New();
	trackElement0->SetName(M_REF_TRACKER);
	trackElement0->SetType(igtl::TrackingDataElement::TYPE_6D);;
	GetDummyMatrix2(matrix);
	trackElement0->SetMatrix(matrix);

	igtl::TrackingDataElement::Pointer trackElement1;
	trackElement1 = igtl::TrackingDataElement::New();
	trackElement1->SetName("Channel 1");
	trackElement1->SetType(igtl::TrackingDataElement::TYPE_6D);
	GetDummyMatrix2(matrix);
	trackElement1->SetMatrix(matrix);

	igtl::TrackingDataElement::Pointer trackElement2;
	trackElement2 = igtl::TrackingDataElement::New();
	trackElement2->SetName("Channel 2");
	trackElement2->SetType(igtl::TrackingDataElement::TYPE_6D);
	GetDummyMatrix2(matrix);
	trackElement2->SetMatrix(matrix);

	track->AddTrackingDataElement(trackElement0);
	track->AddTrackingDataElement(trackElement1);
	track->AddTrackingDataElement(trackElement2);

	igtl::Sleep(20);
	/// Return ImageMessage with the pointer MessageBase
	return (igtl::MessageBase::Pointer) track;
}

igtl::MessageBase::Pointer IGTLMCommon_EXPORT GetDummyUSMessage(int x, int y, int z, float sx, float sy, float sz)
{
	igtl::USMessage::Pointer us = igtl::USMessage::New();
	
	us->SetDimensions(x,y,z);
	us->SetSpacing(sx,sy,sz);
	us->SetSubVolume(x,y,z,0,0,0);
	us->SetScalarTypeToInt16();
	us->SetDeviceName("Dummy_RF_DATA");
	us->AllocateScalars();
	igtl::TimeStamp::Pointer ts = igtl::TimeStamp::New();
	ts->SetTime(GetQueryTimeStampDouble());
	us->SetTimeStamp(ts);

	igtl::Matrix4x4 matrix1;
	GetDummyMatrix1(matrix1);

	us->SetMatrix(matrix1);
	
	//////////////////////////////////////////////////////
	us->SetUSDataType(USDatatypes::udtRF);
	us->SetTransmitFrequency(10000000);
	us->SetSamplingFrequency(20000000);
	us->SetFPS(24);
	us->SetLineDensity(256);

	us->SetSteeringAngle( 2000);
	us->SetProbeID( 12);
	us->SetExtensionAngle( 0);
	us->SetElements(128);
	us->SetPitch(300);

	us->SetRadius(0);
	us->SetProbeAngle(0);
	us->SetTxOffset(0);
	//____________________________________________________________________________________________________________
	us->SetMotor_Radius(9000);
	us->SetFrames3D(120);

	us->SetFrameIndex(60);
	us->SetFocusSpacing(1000);
	us->SetFocusDepth(2000);
	us->SetExtraInt32_1(1);
	us->SetExtraInt32_2(2);

	us->SetExtraInt32_3( 3);
	us->SetExtraInt32_4( 4);
	us->SetExtraInt32_5( 5);

	us->SetMotor_Dir(2);
	us->SetFocus_Count(3);
	us->SetExtra_int8_1( 10);
	us->SetExtra_int8_2( 20);
	us->SetExtra_int8_3( 30);

	return (igtl::MessageBase::Pointer)us;
}

igtl::USMessage::Pointer IGTLMCommon_EXPORT GetDummyUSMessage2(int x, int y, int z, float sx, float sy, float sz)
{
	igtl::USMessage::Pointer us = igtl::USMessage::New();
	
	us->SetDimensions(x,y,z);
	us->SetSpacing(sx,sy,sz);
	us->SetSubVolume(x,y,z,0,0,0);
	us->SetScalarTypeToInt16();
	us->SetDeviceName("Dummy_RF_DATA");
	us->AllocateScalars();

	igtl::Matrix4x4 matrix1;
	GetDummyMatrix1(matrix1);

	us->SetMatrix(matrix1);
	us->SetElements(128);
	us->SetExtensionAngle(3000);
	us->SetFPS(30);
	us->SetLineDensity(256);


	us->SetUSDataType(USDatatypes::udtRF);
	us->SetTransmitFrequency(10000000);
	us->SetSamplingFrequency(20000000);
	us->SetFPS(24);
	us->SetLineDensity(256);
	us->SetSteeringAngle(2000);
	us->SetProbeID(12);
			
	us->SetExtensionAngle(0);
	us->SetElements(128);
	us->SetPitch(300);
	us->SetRadius(0);
	us->SetProbeAngle(0);
	us->SetTxOffset(0);


	return us;
}

igtl::USMessage::Pointer IGTLMCommon_EXPORT ConvertUSMsg1ToUSMsg2(igtl::USMessage::Pointer pUSMsg)
{
	igtl::USMessage::Pointer us = igtl::USMessage::New();

	us->SetDeviceName(pUSMsg->GetDeviceName());
	
	int   size[3];          // image dimension
	float spacing[3];       // spacing (mm/pixel)
	int   svsize[3];        // sub-volume size
	int   svoffset[3];      // sub-volume offset
	int   scalarType;       // scalar type

	scalarType = pUSMsg->GetScalarType();
	pUSMsg->GetDimensions(size);
	pUSMsg->GetSpacing(spacing);
	pUSMsg->GetSubVolume(svsize, svoffset);

	us->SetScalarType(scalarType);
	us->SetDimensions(size);
	us->SetSpacing(spacing);
	us->SetSubVolume(svsize, svoffset);
	us->AllocateScalars();
	
	igtl::TimeStamp::Pointer ts = igtl::TimeStamp::New();
	pUSMsg->GetTimeStamp(ts);
	us->SetTimeStamp(ts);

	

	igtl::Matrix4x4 matrix1;
	pUSMsg->GetMatrix(matrix1);
	us->SetMatrix(matrix1);
	
	/// Data Copy
	memcpy (us->GetScalarPointer(), pUSMsg->GetScalarPointer(), pUSMsg->GetImageSize());
	//////////////////////////////////////////////////////
	us->SetUSDataType(USDatatypes::udtRF);
	us->SetTransmitFrequency(pUSMsg->GetTransmitFrequency());
	us->SetSamplingFrequency(pUSMsg->GetSamplingFrequency());
	us->SetFPS(pUSMsg->GetFPS());
	us->SetLineDensity(pUSMsg->GetLineDensity());

	us->SetSteeringAngle(pUSMsg->GetSteeringAngle());
	us->SetProbeID(pUSMsg->GetProbeID());
	us->SetExtensionAngle(pUSMsg->GetExtensionAngle());
	us->SetElements(pUSMsg->GetElements());
	us->SetPitch(pUSMsg->GetPitch());

	us->SetRadius(pUSMsg->GetRadius());
	us->SetProbeAngle(pUSMsg->GetProbeAngle());
	us->SetTxOffset(pUSMsg->GetTxOffset());
	//____________________________________________________________________________________________________________
	/*us->SetMotor_Radius(9000);
	us->SetFrames3D(120);

	us->SetFrameIndex(60);
	us->SetFocusSpacing(1000);
	us->SetFocusDepth(2000);
	us->SetExtraInt32_1(1);
	us->SetExtraInt32_2(2);

	us->SetExtraInt32_3( 3);
	us->SetExtraInt32_4( 4);
	us->SetExtraInt32_5( 5);

	us->SetMotor_Dir(2);
	us->SetFocus_Count(3);
	us->SetExtra_int8_1( 10);
	us->SetExtra_int8_2( 20);
	us->SetExtra_int8_3( 30);*/

	return us;

}

igtl::MessageBase::Pointer IGTLMCommon_EXPORT GetDummyEIMessage(int x, int y, int z, float sx, float sy, float sz)
{
	igtl::EIMessage::Pointer us = igtl::EIMessage::New();
	
	us->SetDimensions(x,y,z);
	us->SetSpacing(sx,sy,sz);
	us->SetSubVolume(x,y,z,0,0,0);
	us->SetScalarTypeToInt16();
	us->SetDeviceName("Dummy_EI_DATA");
	us->AllocateScalars();

	igtl::Matrix4x4 matrix1;
	GetDummyMatrix1(matrix1);

	us->SetMatrix(matrix1);

	us->SetACC(10.0);
	us->SetAveStrain(1.0);
	us->SetBroderWidth(5.0);
	us->SetRecDelay(0.5);


	return (igtl::MessageBase::Pointer)us;
}


void IGTLMCommon_EXPORT PrintUSMessage(igtl::USMessage::Pointer msg, std::string des)
{
	if(msg.IsNotNull())
	{	
		std::cout << "Print USMessage: " << des.c_str() << std::endl;
		std::cout << "Device type       : " << msg->GetDeviceType() << std::endl;

		int   size[3];          // image dimension
		float spacing[3];       // spacing (mm/pixel)
		int   svsize[3];        // sub-volume size
		int   svoffset[3];      // sub-volume offset
		int   scalarType;       // scalar type

		scalarType = msg->GetScalarType();
		msg->GetDimensions(size);
		msg->GetSpacing(spacing);
		msg->GetSubVolume(svsize, svoffset);

		std::cout << "Device Name           : " << msg->GetDeviceName() << std::endl;
		std::cout << "Scalar Type           : " << scalarType << std::endl;
		std::cout << "Dimensions            : ("
				  << size[0] << ", " << size[1] << ", " << size[2] << ")" << std::endl;
		std::cout << "Spacing               : ("
				  << spacing[0] << ", " << spacing[1] << ", " << spacing[2] << ")" << std::endl;
		std::cout << "Sub-Volume dimensions : ("
				  << svsize[0] << ", " << svsize[1] << ", " << svsize[2] << ")" << std::endl;
		std::cout << "Sub-Volume offset     : ("
				  << svoffset[0] << ", " << svoffset[1] << ", " << svoffset[2] << ")" << std::endl << std::endl;
		
		std::cout << "The matrix of USMessage: " <<std::endl;
		igtl::Matrix4x4 mat;
		msg->GetMatrix(mat);
		igtl::PrintMatrix(mat);

		std::cout << "Extra information of USMessage: " <<std::endl;
		std::cout << "USDataType        :" << msg->GetUSDataType()<<std::endl;
		std::cout << "TransmitFrequency :" << msg->GetTransmitFrequency()<<std::endl;
		std::cout << "SamplingFrequency :" << msg->GetSamplingFrequency()<<std::endl;
		std::cout << "FPS               :" << msg->GetFPS()<<std::endl;
		std::cout << "LineDensity       :" << msg->GetLineDensity()<<std::endl;
		std::cout << "SteeringAngle     :" << msg->GetSteeringAngle()<<std::endl;
		std::cout << "ProbeID           :" << msg->GetProbeID()<<std::endl;
		std::cout << "ExtensionAngle    :" << msg->GetExtensionAngle()<<std::endl;
		std::cout << "Elements          :" << msg->GetElements()<<std::endl;
		std::cout << "Pitch             :" << msg->GetPitch()<<std::endl;
		std::cout << "Radius            :" << msg->GetRadius()<<std::endl;			
		std::cout << "ProbeAngle        :" << msg->GetProbeAngle()<<std::endl;
		std::cout << "TxOffset          :" << msg->GetTxOffset()<<std::endl;
		
		////////////////////////////////////////// Version 2.0
		std::cout << "Motor_Radius      :" <<msg->GetMotor_Radius()<<std::endl;
		std::cout << "Frames3D          :" <<msg->GetFrames3D()<<std::endl;

		std::cout << "Frame_Index       :" <<msg->GetFrameIndex()<<std::endl;
		std::cout << "Focus_Spacing     :" <<msg->GetFocusSpacing()<<std::endl;
		std::cout << "Focus_Depth       :" <<msg->GetFocusDepth()<<std::endl;
		std::cout << "Extra_int32_1     :" <<msg->GetExtraInt32_1()<<std::endl;
		std::cout << "Extra_int32_2     :" <<msg->GetExtraInt32_2()<<std::endl;

		std::cout << "Extra_int32_3     :" <<msg->GetExtraInt32_3()<<std::endl;
		std::cout << "Extra_int32_4     :" <<msg->GetExtraInt32_4()<<std::endl;
		std::cout << "Extra_int32_5     :" <<msg->GetExtraInt32_5()<<std::endl;

		std::cout << "Motor_Dir         :" <<(int)msg->GetMotor_Dir() <<std::endl;
		std::cout << "Focus_Count       :" <<(int)msg->GetFocus_Count() <<std::endl;
		std::cout << "Extra_int8_1      :" <<(int)msg->GetExtra_int8_1() <<std::endl;
		std::cout << "Extra_int8_2      :" <<(int)msg->GetExtra_int8_2() <<std::endl;
		std::cout << "Extra_int8_3      :" <<(int)msg->GetExtra_int8_3() <<std::endl;

		std::cout << std::endl;

	}
	else
		std::cout << "PrintUSMessage::Input Message is NULL" << std::endl;

	std::cout << std::endl;
}


void IGTLMCommon_EXPORT PrintUSMessageMB(igtl::MessageBase::Pointer msg, std::string des)
{
	if(msg.IsNotNull())
	{
		igtl::USMessage::Pointer tempUS;
		tempUS = RetrieveMessage<igtl::USMessage::Pointer, igtl::USMessage>(msg);
		PrintUSMessage(tempUS, des);
	}
	else
		std::cout << "PrintUSMessageMB::Input Message is NULL" << std::endl;

	std::cout << std::endl;
}

///////////////////////////////////////////////////////////////////////////////////////
void IGTLMCommon_EXPORT PrintImageMessage(igtl::ImageMessage::Pointer msg, std::string des)
{
	if(msg.IsNotNull())
	{
		igtl::Matrix4x4 matrix;
		std::cout << "Print ImageMessage: " << des.c_str() << std::endl;
		std::cout << "Device type      : " << msg->GetDeviceType() << std::endl;

		int   size[3];          // image dimension
		float spacing[3];       // spacing (mm/pixel)
		int   svsize[3];        // sub-volume size
		int   svoffset[3];      // sub-volume offset
		int   scalarType;       // scalar type

		scalarType = msg->GetScalarType();
		msg->GetDimensions(size);
		msg->GetSpacing(spacing);
		msg->GetSubVolume(svsize, svoffset);

		std::cout << "Device Name           : " << msg->GetDeviceName() << std::endl;
		std::cout << "Scalar Type           : " << scalarType << std::endl;
		std::cout << "Dimensions            : ("
				  << size[0] << ", " << size[1] << ", " << size[2] << ")" << std::endl;
		std::cout << "Spacing               : ("
				  << spacing[0] << ", " << spacing[1] << ", " << spacing[2] << ")" << std::endl;
		std::cout << "Sub-Volume dimensions : ("
				  << svsize[0] << ", " << svsize[1] << ", " << svsize[2] << ")" << std::endl;
		std::cout << "Sub-Volume offset     : ("
				  << svoffset[0] << ", " << svoffset[1] << ", " << svoffset[2] << ")" << std::endl << std::endl;
		
		std::cout << "The matrix of USMessage: " <<std::endl;
		igtl::Matrix4x4 mat;
		msg->GetMatrix(mat);
		igtl::PrintMatrix(mat);
	}
	else
		std::cout << "PrintImageMessage::Input Message is NULL" << std::endl;

	std::cout << std::endl;
}



void IGTLMCommon_EXPORT PrintImageMessageMB(igtl::MessageBase::Pointer msg, std::string des)
{
	if(msg.IsNotNull())
	{
		igtl::ImageMessage::Pointer tempImg;
		tempImg = RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(msg);
		PrintImageMessage(tempImg);
	}
	else
		std::cout << "PrintImageMessageMB::Input Message is NULL" << std::endl;

	std::cout << std::endl;
}


////////////////////////////////////////////////////////////////////////////////

void IGTLMCommon_EXPORT PrintEIMessage(igtl::EIMessage::Pointer msg, std::string des)
{
	if(msg.IsNotNull())
	{	
		std::cout << "Print EIMessage: " << des.c_str() << std::endl;
		std::cout << "Device type       : " << msg->GetDeviceType() << std::endl;

		int   size[3];          // image dimension
		float spacing[3];       // spacing (mm/pixel)
		int   svsize[3];        // sub-volume size
		int   svoffset[3];      // sub-volume offset
		int   scalarType;       // scalar type

		scalarType = msg->GetScalarType();
		msg->GetDimensions(size);
		msg->GetSpacing(spacing);
		msg->GetSubVolume(svsize, svoffset);

		std::cout << "Device Name           : " << msg->GetDeviceName() << std::endl;
		std::cout << "Scalar Type           : " << scalarType << std::endl;
		std::cout << "Dimensions            : ("
				  << size[0] << ", " << size[1] << ", " << size[2] << ")" << std::endl;
		std::cout << "Spacing               : ("
				  << spacing[0] << ", " << spacing[1] << ", " << spacing[2] << ")" << std::endl;
		std::cout << "Sub-Volume dimensions : ("
				  << svsize[0] << ", " << svsize[1] << ", " << svsize[2] << ")" << std::endl;
		std::cout << "Sub-Volume offset     : ("
				  << svoffset[0] << ", " << svoffset[1] << ", " << svoffset[2] << ")" << std::endl << std::endl;
		
		std::cout << "The matrix of USMessage: " <<std::endl;
		igtl::Matrix4x4 mat;
		msg->GetMatrix(mat);
		igtl::PrintMatrix(mat);

		std::cout << "Extra information of EIMessage: " <<std::endl;
		std::cout << "ImgAng      :" << msg->GetImgAng()<<std::endl;
		std::cout << "ACC         :" << msg->GetACC()<<std::endl;
		std::cout << "BroderWidth :" << msg->GetBroderWidth()<<std::endl;
		std::cout << "AveStrain   :" << msg->GetAveStrain()<<std::endl;
		std::cout << "RecDelay    :" << msg->GetRecDelay()<<std::endl;

		std::cout << std::endl;

	}
	else
		std::cout << "PrintUSMessage::Input Message is NULL" << std::endl;

	std::cout << std::endl;
}


void IGTLMCommon_EXPORT PrintEIMessageMB(igtl::MessageBase::Pointer msg, std::string des)
{
	if(msg.IsNotNull())
	{
		igtl::EIMessage::Pointer tempUS;
		tempUS = RetrieveMessage<igtl::EIMessage::Pointer, igtl::EIMessage>(msg);
		PrintEIMessage(tempUS, des);
	}
	else
		std::cout << "PrintUSMessageMB::Input Message is NULL" << std::endl;

	std::cout << std::endl;
}

igtl::TrackingDataElement::Pointer IGTLMCommon_EXPORT GetReferenceTrackingData(igtl::TrackingDataMessage::Pointer track)
{
	if(track.IsNotNull())
	{
		int nElements = track->GetNumberOfTrackingDataElements();
		for (int i = 0; i < nElements; i ++)
		{
			igtl::TrackingDataElement::Pointer trackingElement;
			track->GetTrackingDataElement(i, trackingElement);
			if(strcmp(trackingElement->GetName(), M_REF_TRACKER) == 0)
				return trackingElement;
		}
	}
	return NULL;
}

int IGTLMCommon_EXPORT IsReferenceTrackingData(igtl::TrackingDataMessage::Pointer track)
{
	if(track.IsNotNull())
	{
		int nElements = track->GetNumberOfTrackingDataElements();
		for (int i = 0; i < nElements; i ++)
		{
			igtl::TrackingDataElement::Pointer trackingElement;
			track->GetTrackingDataElement(i, trackingElement);
			if(strcmp(trackingElement->GetName(), M_REF_TRACKER) == 0)
				return i;
		}
	}
	return NULL;
}


int IGTLMCommon_EXPORT kbhit()
{
#if defined(WIN32) || defined (_WIN32) || defined (__WIN32__)
	return _kbhit();
#else
	struct termios oldt, newt;
	int ch;
	int oldf;
 
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
	ch = getchar();
 
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);
 
	if(ch != EOF)
	{
	ungetc(ch, stdin);
	return 1;
	}
 
	return 0;
#endif
}

std::string IGTLMCommon_EXPORT GetMUSiiCTCPServerMessage(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	std::string message("");
	std::string space(" ");
	std::string sep("::");

	SOCKADDR_IN	SAddr;
	SOCKADDR_IN	CAddr;
	

	if(numOfRun == M_PRE_CONTROL_PRAR || numOfRun ==  M_PRE_CONTROL_PRAR_DATA)
	{
		switch(taskInfo)
		{
			case M_TCP_SERVER_CREATED:
				SAddr =  *(SOCKADDR_IN*)data2;
				message = GetNowTimeString() + sep + space;
				message += "MUSiiCTCPServer(";
				message += GetPort(SAddr);
				message +=") is created";
				break;
			case M_TCP_SERVER_CLOSED:
				SAddr =  *(SOCKADDR_IN*)data2;
				message = GetNowTimeString() + sep + space;
				message += "MUSiiCTCPServer(";
				message += GetPort(SAddr);
				message +=") is closed";
				break;
			case M_TCP_CLIENT_CONNECTED:
				SAddr =  *(SOCKADDR_IN*)data2;
				CAddr =  *(SOCKADDR_IN*)data3;
				message = GetNowTimeString() + sep + space;
				message += "MUSiiCTCPClient(";
				message += GetIP_Port(CAddr);
				message +=") is connected at ";
				message += "MUSiiCTCPServer(";
				message += GetPort(SAddr);
				message +=")";
				break;
			case M_TCP_CLIENT_DISCONNECTED:
				SAddr =  *(SOCKADDR_IN*)data2;
				CAddr =  *(SOCKADDR_IN*)data3;
				message = GetNowTimeString() + sep + space;
				message += "MUSiiCTCPClient(";
				message += GetIP_Port(CAddr);
				message +=") is disconnected from ";
				message += "MUSiiCTCPServer(";
				message += GetPort(SAddr);
				message +=")";
				break;
			case M_TCP_DATA_SENT:
				SAddr =  *(SOCKADDR_IN*)data2;
				CAddr =  *(SOCKADDR_IN*)data3;
				message = GetNowTimeString() + sep + space;
				message += "MUSiiCTCPServer(";
				message += GetPort(SAddr);
				message +=") send Data to";
				message += "MUSiiCTCPClient(";
				message += GetIP_Port(CAddr);
				message +=")";
				break;
			case M_TCP_DATA_RECEIVED:
				SAddr =  *(SOCKADDR_IN*)data2;
				CAddr =  *(SOCKADDR_IN*)data3;
				message = GetNowTimeString() + sep + space;
				message += "MUSiiCTCPServer(";
				message += GetPort(SAddr);
				message +=") received Data";
				if(data1.IsNotNull())
				{
					message +="(Device Type: ";
					message +=data1->GetDeviceType();
					message +=" , Device Name: ";
					message +=data1->GetDeviceName();
					message +=")";
				}
				message += " from MUSiiCTCPClient(";
				message += GetIP_Port(CAddr);
				message +=")";
				break;

			default:
				break;
		}
	}
	else if (numOfRun == M_PRE_CONTROL_PRAR_DATA)
	{

	}

	return message;
}

std::string IGTLMCommon_EXPORT GetMUSiiCTCPClientMessage(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	std::string message("");
	std::string space(" ");
	std::string sep("::");

	SOCKADDR_IN	SAddr;
	SOCKADDR_IN	CAddr;
	

	if(numOfRun == M_POST_CONTROL_PRAR || numOfRun == M_POST_CONTROL_PRAR_DATA)
	{
		switch(taskInfo)
		{
			case M_TCP_CLIENTS_SERVICE_INIT:
				message = GetNowTimeString() + sep + space;
				message = "Network Thread of MUSiiCTCPClient is started";
				break;
			case M_TCP_CLIENTS_SERVICE_FINISH:
				message = GetNowTimeString() + sep + space;
				message = "Network Thread of MUSiiCTCPClient is stopped";
				break;
			case M_TCP_CLIENT_CONNECTED:
				SAddr =  *(SOCKADDR_IN*)data2;
				CAddr =  *(SOCKADDR_IN*)data3;
				message = GetNowTimeString() + sep + space;
				message += "MUSiiCTCPClient(";
				message += GetIP_Port(CAddr);
				message +=") is connected at ";
				message += "MUSiiCTCPServer(";
				message += GetPort(SAddr);
				message +=")";
				break;
			case M_TCP_CLIENT_DISCONNECTED:
				SAddr =  *(SOCKADDR_IN*)data2;
				CAddr =  *(SOCKADDR_IN*)data3;
				message = GetNowTimeString() + sep + space;
				message += "MUSiiCTCPClient(";
				message += GetIP_Port(CAddr);
				message +=") is disconnected from ";
				message += "MUSiiCTCPServer(";
				message += GetPort(SAddr);
				message +=")";
				break;
			case M_TCP_DATA_SENT:
				SAddr =  *(SOCKADDR_IN*)data2;
				CAddr =  *(SOCKADDR_IN*)data3;
				message = GetNowTimeString() + sep + space;
				message += "MUSiiCTCPServer(";
				message += GetPort(SAddr);
				message +=") send Data to";
				message += "MUSiiCTCPClient(";
				message += GetIP_Port(CAddr);
				message +=")";
				break;
			case M_TCP_DATA_RECEIVED:
				SAddr =  *(SOCKADDR_IN*)data2;
				CAddr =  *(SOCKADDR_IN*)data3;
				message = GetNowTimeString() + sep + space;
				message += "MUSiiCTCPServer(";
				message += GetPort(SAddr);
				message +=") received Data";
				if(data1.IsNotNull())
				{
					message +="(Device Type: ";
					message +=data1->GetDeviceType();
					message +=" , Device Name: ";
					message +=data1->GetDeviceName();
					message +=")";
				}
				message += " from MUSiiCTCPClient(";
				message += GetIP_Port(CAddr);
				message +=")";
				break;
			default:
				break;
		}
	}
	else if (numOfRun == M_PRE_CONTROL_PRAR_DATA)
	{

	}

	return message;
}

std::string IGTLMCommon_EXPORT GetIP_Port(SOCKADDR_IN& Addr)
{
	std::string message ("IP Address: ");
	message += (inet_ntoa(Addr.sin_addr));

	int port2 = ntohs(Addr.sin_port);
	//std::string port;

	//std::stringstream ss;//create a stringstream
 //   ss << port2;//add number to the stream
	char buffer[255];
	sprintf(buffer, "%d", ntohs(Addr.sin_port));
	std::string tempmsg = buffer;
	message += " Port: " + tempmsg;
    return message;
}

std::string IGTLMCommon_EXPORT GetIP(SOCKADDR_IN& Addr)
{
	std::string message ("IP Address: ");
	message += (inet_ntoa(Addr.sin_addr));
    return message;
}

std::string IGTLMCommon_EXPORT GetPort(SOCKADDR_IN& Addr)
{
	std::string message ("Port: ");
	//std::stringstream ss;//create a stringstream
 //   ss << ntohs(Addr.sin_port);;//add number to the stream
	//message += ss.str();
 //   return message;

	char buffer[255];
	sprintf(buffer, "%d", ntohs(Addr.sin_port));
	return message+buffer;
}


///////////////////////////////////////////////////////////////////
/// Generating file-path using time_stamp
std::string IGTLMCommon_EXPORT GenerateIGTLFilePath(std::string filepath, double timestamp)
{
	if(timestamp == 0.0)
		timestamp = GetTimeStampDouble();

	/*std::stringstream ss;
	ss << timestamp;*/
	char temptimestamp[256];
	sprintf(temptimestamp, "%f", timestamp);
	std::string ss = temptimestamp;

	//std::string temp_path = filepath+ss.str()+".igtl";
	std::string temp_path = filepath+ss+".igtl";
	return temp_path;
}

/// Converting std::string to booleand (true/false)
bool IGTLMCommon_EXPORT string_To_bool(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return (str.compare("true") == 0)? true: false;
}

bool IGTLMCommon_EXPORT YesNO_To_bool(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	if((str.compare("yes") == 0) || (str.compare("y") == 0))
		return true;
	else
		return false;
}

/// Converting std::string to int
int IGTLMCommon_EXPORT string_To_int(std::string const str)
{
	return atoi(str.c_str());
}

/// Converting std::string to float
float IGTLMCommon_EXPORT string_To_float(std::string const str)
{
	return atof(str.c_str());
}

/// Converting std::string to double
double IGTLMCommon_EXPORT string_To_double(std::string const str)
{
	return atof(str.c_str());
}


/// Converting std::string to booleand (true/false)
std::string IGTLMCommon_EXPORT bool_To_string(bool const& value)
{
	return value ? "true":"false";
}

/// Converting int to std::string
std::string IGTLMCommon_EXPORT int_To_string(int const& value)
{
	char buffer[255];
	sprintf(buffer, "%d", value);
	return buffer;
}

/// Converting float to std::string 
std::string IGTLMCommon_EXPORT float_To_string(float const& value)
{
	char buffer[255];
	sprintf(buffer, "%f", value);
	return buffer;
}

/// Converting double to std::string 
std::string IGTLMCommon_EXPORT double_To_string(double const& value)
{
	char buffer[255];
	sprintf(buffer, "%f", value);
	return buffer;
}


/* ===============================================================*/

bool IGTLMCommon_EXPORT IsReferenceInString(std::string msg)
{
	std::string tempstr = msg;
	std::transform(tempstr.begin(), tempstr.end(), tempstr.begin(), ::tolower);

	if(tempstr.find("ref") != std::string::npos)
		return true;
	else
		return false;
}


/////////////////////////////////////////////////////////////////////
/// Converting double to std::string 
bool IGTLMCommon_EXPORT IsAllDataIOFilter(std::string const str)
{
	std::string tempstr = str;
	std::transform(tempstr.begin(), tempstr.end(), tempstr.begin(), ::tolower);

	if(tempstr.find("all") != std::string::npos)
		return true;
	else
		return false;
}

bool IGTLMCommon_EXPORT IsStringMessage(igtl::MessageBase::Pointer msg)
{
	if(msg.IsNotNull())
	{
		if(strcmp(msg->GetDeviceType(), "STRING") == 0)
			return true;
		else
			return false;
	}
	else
		return false;
}


int	IGTLMCommon_EXPORT 	HexStringToInt(std::string str)
{
	//std::string s = t1;//"-0x10002";
    char * p;
    long n = strtol( str.c_str(), & p, 16 ); 
    if ( * p != 0 ) 
	{  
        //std::cout << "not a number" << std::endl;
		return 0;
    }    
	else 
	{  
        //std::cout << n << std::endl;
		return n;
    }
}

/////////////////////////////////////////////////////////////////////
igtl::MessageBase::Pointer IGTLMCommon_EXPORT InterpolateTrackingMessage(igtl::MessageBase::Pointer Tr1, igtl::MessageBase::Pointer Tr2, double RefTs)
{
	igtl::TrackingDataMessage::Pointer tracker1         = NULL;
	tracker1 = RetrieveMessage<igtl::TrackingDataMessage::Pointer, igtl::TrackingDataMessage>(Tr1);
	igtl::TrackingDataElement::Pointer ReftrackingData1 = GetReferenceTrackingData(tracker1);
	igtl::Matrix4x4 Tmat1;
	ReftrackingData1->GetMatrix(Tmat1);
	double T1 = GetIGTLTimeStamp2(Tr1);
	
    igtl::TrackingDataMessage::Pointer tracker2         = NULL;
	tracker2 = RetrieveMessage<igtl::TrackingDataMessage::Pointer, igtl::TrackingDataMessage>(Tr2);
	igtl::TrackingDataElement::Pointer ReftrackingData2 = GetReferenceTrackingData(tracker2);;
	igtl::Matrix4x4 Tmat2;
	ReftrackingData2->GetMatrix(Tmat2);
	double T2 = GetIGTLTimeStamp2(Tr2);
	
	double Tmax = std::max(T1, T2);

	if(Tmax >= RefTs) /// Interpolation
	{
		igtl::TrackingDataMessage::Pointer OutputT = igtl::TrackingDataMessage::New();

		OutputT->SetDeviceName(tracker1->GetDeviceName());
		unsigned int secp  = (unsigned int)(RefTs);
		unsigned int fracp = (unsigned int)((RefTs-secp)*1e9);
		OutputT->SetTimeStamp(secp, fracp);

		igtl::Matrix4x4 Tmat_Int;
		bool r(false);
		if(Tmax == T1)
			r = InterpolateTmat(Tmat2, T2, Tmat1, T1, RefTs,Tmat_Int); 
		else
			r = InterpolateTmat(Tmat1, T1, Tmat2, T2, RefTs,Tmat_Int); 

		
		igtl::TrackingDataElement::Pointer TrackingEle = igtl::TrackingDataElement::New();
		TrackingEle->SetName(ReftrackingData1->GetName());
		TrackingEle->SetType(igtl::TrackingDataElement::TYPE_6D);
		TrackingEle->SetMatrix(Tmat_Int);
		OutputT->AddTrackingDataElement(TrackingEle);
		return (igtl::MessageBase::Pointer) OutputT;
		
	}
	
	double DiffT1 = abs(T1 - RefTs);
	double DiffT2 = abs(T2 - RefTs); 
	double minT = std::min(DiffT1, DiffT2);

	return minT == DiffT1 ? Tr1 : Tr2;
	
	//////////////////////////////////////////////////////////////////////////////

} ///

// Interpolating homogenous Transformation matrix using Time stamp
bool IGTLMCommon_EXPORT InterpolateTmat(igtl::Matrix4x4& Tmin, double Ts_Min,
	                                    igtl::Matrix4x4& Tmax, double Ts_Max,
										double Ts, igtl::Matrix4x4& T_Out)
{
	double T_Span = abs(Ts_Max - Ts_Min);
	float T_Int   = (float)(abs(Ts - Ts_Min)/T_Span);

	float q_min[4];
	float q_max[4];
	float q_int[4];

	/// Get a quaternion from transformation matrix of T_Min
	igtl::MatrixToQuaternion(Tmin, q_min);

	/// Get a quaternion from transformation matrix of T_Min
	igtl::MatrixToQuaternion(Tmax, q_max);

	/// Slerp interpolation for quaternion
	slerp_Interpolation(q_min, q_max, T_Int, q_int);

	/// Convert the interpolated quaternion to transformation matrix 
	igtl::QuaternionToMatrix(q_int,T_Out); 

	/// Update transformation part
	T_Out[0][3] = ((1.0 - T_Int)*Tmin[0][3]) + (T_Int*Tmax[0][3]);
	T_Out[1][3] = ((1.0 - T_Int)*Tmin[1][3]) + (T_Int*Tmax[1][3]);
	T_Out[2][3] = ((1.0 - T_Int)*Tmin[2][3]) + (T_Int*Tmax[2][3]);

	return true;
}

/// float* q represents quaternion
/// q[0] = x,  q[1] = y,  q[2] = z,  q[3] = w,  
/// This function is from Quaternion.cpp that is created by Philipp J. Stolka
bool IGTLMCommon_EXPORT slerp_Interpolation(float* q_min, float* q_max, float intp, float* q_int)
{
	int i;
	// Get an angle between two quaternion
	double costheta = 0.0;

	for(i=0; i<4; i++)
		costheta = costheta + q_min[i]*q_max[i];
	
	double theta = (costheta <1 || costheta>-1 ? 0 : acos(costheta));
	double ratioA;
	double ratioB;

	if(abs(theta) < 1e-10)
	{
		ratioA = 0.5;
		ratioB = 0.5;
	}
	else
	{
		double sinTheta = sqrt(1.0 - costheta*costheta);

		ratioA = sin((1.0 - intp)*theta)/sinTheta;
		ratioB = sin(intp*theta)/sinTheta;
	}

	for(i=0; i<4; i++)
		q_int[i] = (ratioA*q_min[i]) + (ratioB* q_max[i]);
		
	return true;
}


std::vector<igtl::MessageBase::Pointer> IGTLMCommon_EXPORT CheckBindMessage(igtl::MessageBase::Pointer msg)
{
	std::vector<igtl::MessageBase::Pointer> Messages;

	if(msg.IsNotNull())
	{
		if (strcmp(msg->GetDeviceType(), "BIND") == 0)
		{
			igtl::BindMessage::Pointer bind;
			bind = igtl::RetrieveMessage<igtl::BindMessage::Pointer, igtl::BindMessage>(msg);
		
			int NumOfChild(bind->GetNumberOfChildMessages());
		
			for(int i=0; i<NumOfChild; i++)
			{
				if (strcmp(bind->GetChildMessageType(i), "BIND") == 0)
				{
					igtl::BindMessage::Pointer localbind = igtl::BindMessage::New();
					bind->GetChildMessage(i, localbind);
					localbind->Unpack();
					std::vector<igtl::MessageBase::Pointer> SubMessages;
					SubMessages = CheckBindMessage((igtl::MessageBase::Pointer)localbind);
					for(int j=0; j<SubMessages.size(); j++)
					{
						igtl::MessageBase::Pointer tempMsg;
						tempMsg = SubMessages.at(j);
						Messages.push_back(tempMsg);
					}
					SubMessages.clear();
				}
				else if(strcmp(bind->GetChildMessageType(i), "IMAGE") == 0)
				{
					igtl::ImageMessage::Pointer ImgMsg = igtl::ImageMessage::New();
					bind->GetChildMessage(i, ImgMsg);
					ImgMsg->Unpack();
					Messages.push_back((igtl::MessageBase::Pointer)ImgMsg);
				}
			
			}
		}
		else
			Messages.push_back(msg);
	}

	return Messages;
}

};
