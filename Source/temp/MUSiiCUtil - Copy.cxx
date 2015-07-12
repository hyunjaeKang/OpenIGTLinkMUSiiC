/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/

#include "MUSiiCUtil.h"

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


igtl::TrackingDataElement::Pointer IGTLMCommon_EXPORT ExtractTrackingInfo(igtl::MessageBase::Pointer msg, int index)
{
	igtl::TrackingDataMessage::Pointer tracker;
	tracker = RetrieveMessage<igtl::TrackingDataMessage::Pointer, igtl::TrackingDataMessage>(msg);

	igtl::TrackingDataElement::Pointer trackingData;
	tracker->GetTrackingDataElement(index, trackingData);

	return trackingData;
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
	{
		for(j=0; j<4;j++)
		{
			for(k=0; k<4; k++)
			{
				matC[i][j] = matC[i][j] + (matA[i][k]*matB[k][j]);
			}
		}
	}

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

igtl::MessageBase::Pointer IGTLMCommon_EXPORT RetriveMessageBase(igtl::MessageBase::Pointer msg)
{
		// Check data type and receive data body
    if (strcmp(msg->GetDeviceType(), "BIND") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::BindMessage::Pointer, igtl::BindMessage>(msg);
    }
    else if (strcmp(msg->GetDeviceType(), "COLORTABLE") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::ColorTableMessage::Pointer, igtl::ColorTableMessage>(msg);
    }
    else if (strcmp(msg->GetDeviceType(), "IMAGE") == 0)
    {
		std::string device(msg->GetDeviceName());
		std::string us("US");
		std::string rf("RF");
		std::string ei("EI");
		if((device.find(us)!=std::string::npos) || (device.find(rf)!=std::string::npos))
		{
			return RetrieveMessagefromIODevice<igtl::USMessage::Pointer, igtl::USMessage>(msg);
		}
		else if(device.find(ei)!=std::string::npos)
		{
			return RetrieveMessagefromIODevice<igtl::EIMessage::Pointer, igtl::EIMessage>(msg);
		}
		else
			return RetrieveMessagefromIODevice<igtl::ImageMessage::Pointer, igtl::ImageMessage>(msg);
    }
    else if (strcmp(msg->GetDeviceType(), "IMGMETA") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::ImageMetaMessage::Pointer, igtl::ImageMetaMessage>(msg);
	}
    else if (strcmp(msg->GetDeviceType(), "LBMETA") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::LabelMetaMessage::Pointer, igtl::LabelMetaMessage>(msg);
    }
    else if (strcmp(msg->GetDeviceType(), "NDARRAY") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::NDArrayMessage::Pointer, igtl::NDArrayMessage>(msg);
    }
    else if (strcmp(msg->GetDeviceType(), "POINT") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::PointMessage::Pointer, igtl::PointMessage>(msg);
    }
	else if (strcmp(msg->GetDeviceType(), "POSITION") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::PositionMessage::Pointer, igtl::PositionMessage>(msg);
    }
    else if (strcmp(msg->GetDeviceType(), "QTDATA") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::QuaternionTrackingDataMessage::Pointer, igtl::QuaternionTrackingDataMessage>(msg);
	}
	else if (strcmp(msg->GetDeviceType(), "STATUS") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::StatusMessage::Pointer, igtl::StatusMessage>(msg);
	}
	else if (strcmp(msg->GetDeviceType(), "STRING") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::StringMessage::Pointer, igtl::StringMessage>(msg);
	}
	else if (strcmp(msg->GetDeviceType(), "TDATA") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::TrackingDataMessage::Pointer, igtl::TrackingDataMessage>(msg);
	}
	else if (strcmp(msg->GetDeviceType(), "TRANSFORM") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::TransformMessage::Pointer, igtl::TransformMessage>(msg);
	}
	else if (strcmp(msg->GetDeviceType(), "TRAJ") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::TrajectoryMessage::Pointer, igtl::TrajectoryMessage>(msg);
	}
	else if (strcmp(msg->GetDeviceType(), "GEN") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::GenMessage::Pointer, igtl::GenMessage>(msg);
	}
	else if (strcmp(msg->GetDeviceType(), "ARGUMENTS") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::ArgMessage::Pointer, igtl::ArgMessage>(msg);
	}
	else if (strcmp(msg->GetDeviceType(), "FILE") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::FileMessage::Pointer, igtl::FileMessage>(msg);
	}
	else if (strcmp(msg->GetDeviceType(), "EIIMAGE") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::FixedImage::Pointer, igtl::FixedImage>(msg);
	}
	else if (strcmp(msg->GetDeviceType(), "EIUSIMAGE") == 0)
    {
		return RetrieveMessagefromIODevice<igtl::FixedImageBMODE::Pointer, igtl::FixedImageBMODE>(msg);
	}
	else 
	return 0;
}


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
   std::string device(msg->GetDeviceName());
   int rs = device.find(M_REF_DATA);
   return (rs != std::string::npos)?true:false;
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


	return (igtl::MessageBase::Pointer)us;
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


	return (igtl::MessageBase::Pointer)us;
}


void IGTLMCommon_EXPORT PrintUSMessage(igtl::USMessage::Pointer msg, std::string des)
{
	if(msg.IsNotNull())
	{	
		std::cout << "Print USMessage: " << des.c_str() << std::endl;
		std::cout << "The device type       : " << msg->GetDeviceType() << std::endl;
		std::cout << "The device Name       : " << msg->GetDeviceName() << std::endl;

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
		std::cout << "The device type      : " << msg->GetDeviceType() << std::endl;
		std::cout << "The device Name      : " << msg->GetDeviceName() << std::endl;

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


};
