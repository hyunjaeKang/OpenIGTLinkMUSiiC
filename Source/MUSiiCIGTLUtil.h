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

#ifndef __MUSIIC_UTIL_
#define __MUSIIC_UTIL_

#include "MUSiiCDef.h"


namespace igtl
{

template<class P, class M>
inline P RetrieveMessage(igtl::MessageBase::Pointer msg, bool crc= true)
{
	if(msg.IsNotNull())
	{	
		msg->Pack();
		/// Copy Header Field of OpenIGTLink
		P temp_msg = M::New();
		temp_msg->InitPack();
		memcpy(temp_msg->GetPackPointer(), msg->GetPackPointer(), temp_msg->GetPackSize());
		temp_msg->Unpack();
		/// Filtering 
		if(strcmp(msg->GetDeviceType(), temp_msg->GetDeviceType()) != 0)
			return NULL;
		temp_msg->AllocatePack();
		int PreSz(msg->GetPackBodySize());
		int PreSz2(msg->GetBodySizeToRead());
		int NesSz(temp_msg->GetPackBodySize());
		int NesSz2(temp_msg->GetBodySizeToRead());
		/// Retrive the Body of OpenIGTLink/OpenIGTLinkMUSiiC Message
		if(PreSz == NesSz)
			memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), NesSz);
		else
			return RetrieveMessageDiffSize<P,M>(msg); ///check point : cannon96
		//memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), PreSz);
		/// Upacking
		if(crc)
		{
			int c = temp_msg->Unpack(1);
			if( c & igtl::MessageHeader::UNPACK_BODY) 
				return temp_msg;
			else 
				return  NULL;
		}
		else
		{
			int c = temp_msg->Unpack();
			return temp_msg;
			if( c & igtl::MessageHeader::UNPACK_BODY) 
				return temp_msg;
			else 
				return  NULL;
		}

	}
	else 
		return NULL;
}




template<class P, class M>
inline P RetrieveMessageDiffSize(igtl::MessageBase::Pointer msg)
{
	if(msg.IsNotNull())
	{	
		/*msg->Pack();
		P temp_msg = M::New();
		temp_msg->SetMessageHeader(msg);
		temp_msg->AllocatePack();*/
		
		msg->Pack();
		/// Copy Header Field of OpenIGTLink
		P temp_msg = M::New();
		temp_msg->InitPack();
		memcpy(temp_msg->GetPackPointer(), msg->GetPackPointer(), temp_msg->GetPackSize());
		temp_msg->Unpack();
		/// Filtering 
		if(strcmp(msg->GetDeviceType(), temp_msg->GetDeviceType()) != 0)
			return NULL;
		temp_msg->AllocatePack();

		int PreSz(msg->GetPackBodySize());
		int PreSz2(msg->GetBodySizeToRead());
		int NesSz(temp_msg->GetPackBodySize());
		int NesSz2(temp_msg->GetBodySizeToRead());
		memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetPackBodySize());
		//memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), msg->GetPackBodySize());
		int c = temp_msg->Unpack(1);
		if( c & igtl::MessageHeader::UNPACK_BODY) 
			return temp_msg;
		else 
			return  NULL;
	}
	else 
		return NULL;
}



template<class P, class M>
inline igtl::MessageBase::Pointer RetrieveMessagefromIODevice(igtl::MessageHeader::Pointer header, igtl::MessageBase::Pointer msg)
{
	if(msg.IsNotNull() && header.IsNotNull())
	{
		P temp_msg = M::New();
		temp_msg->SetMessageHeader(header);
		temp_msg->AllocatePack();
		int sz1 = msg->GetPackBodySize();
		int sz2 = temp_msg->GetPackBodySize();
		memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetPackBodySize());
		int c = temp_msg->Unpack(1);
		//int c = temp_msg->Unpack(0);
		if( c & igtl::MessageHeader::UNPACK_BODY) 
			return (igtl::MessageBase::Pointer)temp_msg;
		else 
			return  NULL;
	}
	else 
		return NULL;
}

template<class P, class M>
inline igtl::MessageBase::Pointer RetrieveMessagefromIODeviceNoCRC(igtl::MessageHeader::Pointer header, igtl::MessageBase::Pointer msg)
{
	if(msg.IsNotNull() && header.IsNotNull())
	{
		P temp_msg = M::New();
		temp_msg->SetMessageHeader(header);
		temp_msg->AllocatePack();
		int sz1 = msg->GetPackBodySize();
		int sz2 = temp_msg->GetPackBodySize();
		memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetPackBodySize());
		//int c = temp_msg->Unpack(1);
		int c = temp_msg->Unpack(0);
		if( c & igtl::MessageHeader::UNPACK_BODY) 
			return (igtl::MessageBase::Pointer)temp_msg;
		else 
			return  NULL;
	}
	else 
		return NULL;
}
template<class P, class M>
inline P RetrieveSpecificMessagefromIODevice(igtl::MessageHeader::Pointer header, igtl::MessageBase::Pointer msg, bool bCRC = true)
{
	if(msg.IsNotNull() && header.IsNotNull())
	{
		P temp_msg = M::New();
		temp_msg->SetMessageHeader(header);
		temp_msg->AllocatePack();
		/// Filtering 
		if(strcmp(header->GetDeviceType(), temp_msg->GetDeviceType()) != 0)
			return NULL;
		int sz1 = msg->GetPackBodySize();
		int sz2 = temp_msg->GetPackBodySize();
		memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetPackBodySize());
		int c = temp_msg->Unpack(1);
		if(bCRC)
			c = temp_msg->Unpack(1);
		else
			c = temp_msg->Unpack(0);

		if( c & igtl::MessageHeader::UNPACK_BODY) 
			return temp_msg;
		else 
			return  NULL;
	}
	else 
		return NULL;
}

template<class P, class M>
inline igtl::MessageBase::Pointer RetrieveMessagefromIODeviceBackup(igtl::MessageBase::Pointer msg)
{
	if(msg.IsNotNull())
	{	
		msg->Pack();
		P temp_msg = M::New();
		temp_msg->SetMessageHeader(msg);
		temp_msg->AllocatePack();
		memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetPackBodySize());
		int c = temp_msg->Unpack(1);
		if( c & igtl::MessageHeader::UNPACK_BODY) 
			return (igtl::MessageBase::Pointer)temp_msg;
		else 
			return  NULL;
	}
	else 
		return NULL;
}

template<class P, class M>
inline P RetrieveMessagefromIODevice2(igtl::MessageBase::Pointer msg)
{
	if(msg.IsNotNull())
	{	
		msg->Pack();
		P temp_msg = M::New();
		temp_msg->SetMessageHeader(msg);
		temp_msg->AllocatePack();
		memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetPackBodySize());
		int c = temp_msg->Unpack(1);
		if( c & igtl::MessageHeader::UNPACK_BODY) 
			return temp_msg;
		else 
			return  NULL;
	}
	else 
		return NULL;
}

template<class P, class M>
inline P RetrieveMessagefromIODevice3(igtl::MessageBase::Pointer msg) //Fail
{
	if(msg.IsNotNull())
	{	
		msg->Pack();
		igtl::MessageHeader::Pointer header = igtl::MessageHeader::New();
		header->InitPack();
		int ss = header->GetPackSize();
		memcpy(header->GetPackPointer(), msg->GetPackPointer(), header->GetPackSize());
		header->Unpack();

		P temp_msg = M::New();
		temp_msg->SetMessageHeader(header);
		temp_msg->AllocatePack();
		int sz1 = msg->GetPackBodySize();
		int sz2 = temp_msg->GetPackBodySize();
		memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetPackBodySize());
		int c = temp_msg->Unpack(1);
		if( c & igtl::MessageHeader::UNPACK_BODY) 
			return temp_msg;
		else 
			return  NULL;
	}
	else 
		return NULL;
}

template<class P, class M>
inline P RetrieveMessagefromIODevice4(igtl::MessageBase::Pointer msg) //Faile
{
	if(msg.IsNotNull())
	{	
		//msg->Pack();
		igtl::MessageHeader::Pointer header = igtl::MessageHeader::New();
		header->InitPack();
		int ss = header->GetPackSize();
		memcpy(header->GetPackPointer(), msg->GetPackPointer(), header->GetPackSize());
		header->Unpack();

		P temp_msg = M::New();
		temp_msg->SetMessageHeader(header);
		temp_msg->AllocatePack();
		int sz1 = msg->GetPackBodySize();
		int sz2 = temp_msg->GetPackBodySize();
		memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetPackBodySize());
		int c = temp_msg->Unpack(1);
		if( c & igtl::MessageHeader::UNPACK_BODY) 
			return temp_msg;
		else 
			return  NULL;
	}
	else 
		return NULL;
}

template<class P, class M>
inline P RetrieveMessagefromIODevice5(LP_IO_DATA IOdata)
{
	if(IOdata->IGTLMsg.IsNotNull())
	{	
		P temp_msg = M::New();
		temp_msg->SetMessageHeader(IOdata->headerMsg);
		temp_msg->AllocatePack();
		int sz1 = IOdata->IGTLMsg->GetPackBodySize();
		int sz2 = temp_msg->GetPackBodySize();
		memcpy(temp_msg->GetPackBodyPointer(),IOdata->IGTLMsg->GetPackBodyPointer(), temp_msg->GetPackBodySize());
		int c = temp_msg->Unpack(1);
		if( c & igtl::MessageHeader::UNPACK_BODY) 
			return temp_msg;
		else 
			return  NULL;
	}
	else 
		return NULL;
}


//// This function a test function for checking IGTL MessageBase pointer from IO Device
template<class P>
inline igtl::MessageBase::Pointer ConvertMessageBase(P msg)
{
	if(msg.IsNotNull())
	{	
		int BodySz(msg->GetPackBodySize());
		msg->Pack();
		igtl::MessageBase::Pointer temp_msg = igtl::MessageBase::New();
		temp_msg->InitPack();
		int s1 = temp_msg->GetPackSize();
		int s2 = msg->GetPackSize();
		memcpy(temp_msg->GetPackPointer(), msg->GetPackPointer(), temp_msg->GetPackSize());
		temp_msg->Unpack();
		temp_msg->AllocatePack();
		int s3 = temp_msg->GetBodySizeToRead();
		int s4 = msg->GetBodySizeToRead();
		//memcpy(temp_msg->GetPackBodyPointer(), msg->GetPackBodyPointer(), temp_msg->GetBodySizeToRead());
		memcpy(temp_msg->GetPackBodyPointer(), msg->GetPackBodyPointer(), BodySz);
		//return temp_msg;
		int c = temp_msg->Unpack(1);
		if( c & igtl::MessageHeader::UNPACK_BODY) 
			return temp_msg;
		else 
			return  NULL;
	}
	else 
		return NULL;
}

double IGTLMCommon_EXPORT GetIGTLTimeStamp(igtl::MessageBase::Pointer msg);

double IGTLMCommon_EXPORT GetIGTLTimeStamp2(igtl::MessageBase::Pointer msg);

igtl::TrackingDataElement::Pointer IGTLMCommon_EXPORT ExtractTrackingDataElement(igtl::MessageBase::Pointer msg, int index);

void IGTLMCommon_EXPORT MatrixMultiplication(igtl::Matrix4x4& matA, igtl::Matrix4x4& matB, igtl::Matrix4x4& matC);

void IGTLMCommon_EXPORT DuplicateMatrix(igtl::Matrix4x4& matDest, igtl::Matrix4x4& matSrc);

igtl::ImageMessage::Pointer IGTLMCommon_EXPORT DuplicateImageMessage(igtl::ImageMessage::Pointer img);

//igtl::MessageBase::Pointer IGTLMCommon_EXPORT RetriveMessageBase(igtl::MessageBase::Pointer msg); // cannon96
igtl::MessageBase::Pointer IGTLMCommon_EXPORT RetriveMessageBase(igtl::MessageHeader::Pointer header,igtl::MessageBase::Pointer msg); // cannon96

bool IGTLMCommon_EXPORT SetReferenceData(igtl::MessageBase::Pointer msg);
bool IGTLMCommon_EXPORT IsReferenceData(igtl::MessageBase::Pointer msg);

bool IGTLMCommon_EXPORT SetSyncData(igtl::MessageBase::Pointer msg);
bool IGTLMCommon_EXPORT IsSyncData(igtl::MessageBase::Pointer msg);

bool IGTLMCommon_EXPORT IsImageMessage(igtl::MessageBase::Pointer msg);
bool IGTLMCommon_EXPORT IsTrackingDataMessage(igtl::MessageBase::Pointer msg);

/// For Testing OpenIGTLink, OpenIGTlinkMUSiiC

void IGTLMCommon_EXPORT GetDummyMatrix1(igtl::Matrix4x4& matrix, bool print = false);

void IGTLMCommon_EXPORT GetDummyMatrix2(igtl::Matrix4x4& matrix, bool print = false);

igtl::MessageBase::Pointer IGTLMCommon_EXPORT GetDummyImageMessage(int x = 300, int y= 400, int z = 1, float sx = 0.5, float sy = 0.6, float sz = 1.0);

igtl::MessageBase::Pointer IGTLMCommon_EXPORT GetDummyStringMessage(std::string msg = "TestString");

igtl::MessageBase::Pointer IGTLMCommon_EXPORT GetDummyTrackingDataMessage();

igtl::MessageBase::Pointer IGTLMCommon_EXPORT GetDummyUSMessage(int x = 128, int y= 1024, int z = 1, float sx = 0.5, float sy = 0.6, float sz = 1.0);

igtl::USMessage::Pointer IGTLMCommon_EXPORT GetDummyUSMessage2(int x = 128, int y= 1024, int z = 1, float sx = 0.5, float sy = 0.6, float sz = 1.0);

igtl::MessageBase::Pointer IGTLMCommon_EXPORT GetDummyEIMessage(int x = 128, int y= 1024, int z = 1, float sx = 0.5, float sy = 0.6, float sz = 1.0);


igtl::USMessage::Pointer IGTLMCommon_EXPORT ConvertUSMsg1ToUSMsg2(igtl::USMessage::Pointer pUSMsg);

void IGTLMCommon_EXPORT PrintUSMessage(igtl::USMessage::Pointer msg, std::string des = "");
void IGTLMCommon_EXPORT PrintUSMessageMB(igtl::MessageBase::Pointer msg, std::string des = "");

void IGTLMCommon_EXPORT PrintImageMessage(igtl::ImageMessage::Pointer msg, std::string des = "");
void IGTLMCommon_EXPORT PrintImageMessageMB(igtl::MessageBase::Pointer msg, std::string des = "");


void IGTLMCommon_EXPORT PrintEIMessage(igtl::EIMessage::Pointer msg, std::string des = "");
void IGTLMCommon_EXPORT PrintEIMessageMB(igtl::MessageBase::Pointer msg, std::string des = "");

igtl::TrackingDataElement::Pointer IGTLMCommon_EXPORT GetReferenceTrackingData(igtl::TrackingDataMessage::Pointer track);

int IGTLMCommon_EXPORT IsReferenceTrackingData(igtl::TrackingDataMessage::Pointer track);

int IGTLMCommon_EXPORT kbhit();

std::string IGTLMCommon_EXPORT GetMUSiiCTCPServerMessage(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

std::string IGTLMCommon_EXPORT GetMUSiiCTCPClientMessage(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

#if defined(WIN32) || defined (_WIN32) || defined (__WIN32__)
std::string IGTLMCommon_EXPORT GetIP_Port(SOCKADDR_IN& Addr);

std::string IGTLMCommon_EXPORT GetIP(SOCKADDR_IN& Addr);

std::string IGTLMCommon_EXPORT GetPort(SOCKADDR_IN& Addr);
#else
    
#endif
///////////////////////////////////////////////////////////////////
/// Generating file-path using time_stamp
std::string IGTLMCommon_EXPORT GenerateIGTLFilePath(std::string filepath, double timestamp = 0.0);

/// Converting std::string to booleand (true/false)
bool IGTLMCommon_EXPORT string_To_bool(std::string str);
/// Converting std::string to booleand (yes/no)
bool IGTLMCommon_EXPORT YesNO_To_bool(std::string str);
/// Converting std::string to int
int IGTLMCommon_EXPORT string_To_int(std::string const str);
/// Converting std::string to float
float IGTLMCommon_EXPORT string_To_float(std::string const str);
/// Converting std::string to double
double IGTLMCommon_EXPORT string_To_double(std::string const str);


/// Converting std::string to booleand (true/false)
std::string IGTLMCommon_EXPORT bool_To_string(bool const& value);
/// Converting int to std::string
std::string IGTLMCommon_EXPORT int_To_string(int const& value);
/// Converting float to std::string 
std::string IGTLMCommon_EXPORT float_To_string(float const& value);
/// Converting double to std::string 
std::string IGTLMCommon_EXPORT double_To_string(double const& value);

/*-----------------------------------------------------------------*/
bool IGTLMCommon_EXPORT IsReferenceInString(std::string msg);

/////////////////////////////////////////////////////////////////////
/// Converting double to std::string 
bool IGTLMCommon_EXPORT IsAllDataIOFilter(std::string const str);

bool IGTLMCommon_EXPORT IsStringMessage(igtl::MessageBase::Pointer msg);

int	IGTLMCommon_EXPORT 	HexStringToInt(std::string str);


/////////////////////////////////////////////////////////////////////
igtl::MessageBase::Pointer IGTLMCommon_EXPORT InterpolateTrackingMessage(igtl::MessageBase::Pointer Tr1,igtl::MessageBase::Pointer Tr2,double RefTs = 0.0);

bool IGTLMCommon_EXPORT InterpolateTmat(igtl::Matrix4x4& Tmin, double Ts_Min,
	                                    igtl::Matrix4x4& Tmax, double Ts_Max,
										double Ts, igtl::Matrix4x4& T_Out);

bool IGTLMCommon_EXPORT slerp_Interpolation(float* q_min, float* q_max, float intp, float* q_int);

/////////////////////////////////////////////////////////////////////
/// Check BindMessage
std::vector<igtl::MessageBase::Pointer> IGTLMCommon_EXPORT CheckBindMessage(igtl::MessageBase::Pointer msg);
};





#endif
