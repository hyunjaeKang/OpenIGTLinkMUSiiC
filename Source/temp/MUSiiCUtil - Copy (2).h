/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/

#ifndef __MUSIIC_UTIL_
#define __MUSIIC_UTIL_

#include "MUSiiCDef.h"

namespace igtl
{

double IGTLMCommon_EXPORT GetIGTLTimeStamp(igtl::MessageBase::Pointer msg);
double IGTLMCommon_EXPORT GetIGTLTimeStamp2(igtl::MessageBase::Pointer msg);

//template<class P, class M>
//inline P RetrieveMessage2(igtl::MessageBase::Pointer msg)
//{
//	if(msg.IsNotNull())
//	{	
//		int p0 = msg->GetPackSize();
//		int BodySz(msg->GetPackBodySize());
//		
//		int size00 = strlen((const char*)(msg->GetPackPointer()));
//		int size01 = strlen((const char*)(msg->GetPackBodyPointer()));
//		
//		//msg->Pack();
//		//igtl::MessageHeader::Pointer headerMsg;
//		//headerMsg = igtl::MessageHeader::New();
//		//// Initialize receive buffer
//		//headerMsg->InitPack();
//		//memcpy(headerMsg->GetPackPointer(), msg->GetPackPointer(), headerMsg->GetPackSize());
//		//// Deserialize the header
//		//headerMsg->Unpack();
//		//
//		
//		P temp_msg = M::New();
//		temp_msg->InitPack();
//		int s1 = temp_msg->GetPackSize();
//		int s2 = msg->GetPackSize();
//		memcpy(temp_msg->GetPackPointer(), msg->GetPackPointer(), temp_msg->GetPackSize());
//		temp_msg->Unpack();
//		//temp_msg->SetMessageHeader(headerMsg);
//		//temp_msg->SetMessageHeader(msg);
//		temp_msg->AllocatePack();
//		int p1 = temp_msg->GetPackSize();
//		int s3 = temp_msg->GetBodySizeToRead();
//		int s4 = msg->GetBodySizeToRead();
//		int s5 = temp_msg->GetPackBodySize();
//		int s6 = msg->GetPackBodySize();
//
//		int size0 = strlen((const char*)(temp_msg->GetPackBodyPointer()));
//		int size1 = strlen((const char*)(msg->GetPackBodyPointer()));
//		//memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetPackBodySize());
//		//memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetBodySizeToRead());
//		//memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), BodySz);
//		memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), s6);
//		int c = temp_msg->Unpack(1);
//		if( c & igtl::MessageHeader::UNPACK_BODY) 
//			return temp_msg;
//		else 
//			return  NULL;
//	}
//	else 
//		return NULL;
//	
//	//if(msg.IsNotNull())
//	//{	
//	//	msg->Pack();
//	//	P temp_msg = M::New();
//	//	temp_msg->InitPack();
//	//	
//	//	int s1 = temp_msg->GetPackSize();
//	//	int s2 = msg->GetPackSize();
//	//	
//	//	memcpy(temp_msg->GetPackPointer(), msg->GetPackPointer(), temp_msg->GetPackSize());
//	//	temp_msg->Unpack();
//	//	temp_msg->AllocatePack();
//	//	
//	//	int s3 = temp_msg->GetBodySizeToRead();
//	//	int s4 = msg->GetBodySizeToRead();
//	//	
//	//	memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetPackBodySize());
//	//	//int c = temp_msg->Unpack(1);
//	//	int c = temp_msg->Unpack();
//	//	//if(c & M::UNPACK_BODY)
//	//	if( c & igtl::MessageHeader::UNPACK_BODY) 
//	//		return temp_msg;
//	//	else 
//	//		return  NULL;
//	//}
//	//else 
//	//	return NULL;
//	
//	//if(msg.IsNotNull())
//	//{	
//	//	int BodySz(msg->GetPackBodySize());
//	//	msg->Pack();
//	//	P temp_msg = M::New();
//	//	temp_msg->SetMessageHeader(msg);
//	//	temp_msg->AllocatePack();
//	//	int s =temp_msg->GetPackBodySize();
//	//	//memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetPackBodySize());
//	//	memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), BodySz);
//	//	int c = temp_msg->Unpack(1);
//	//	//int c = temp_msg->Unpack();
//	//	//if(c & M::UNPACK_BODY)
//	//	if( c & igtl::MessageHeader::UNPACK_BODY) 
//	//		return temp_msg;
//	//	else 
//	//		return  NULL;
//	//}
//	//else 
//	//	return NULL;
//}

template<class P, class M>
inline P RetrieveMessage(igtl::MessageBase::Pointer msg)
{
	if(msg.IsNotNull())
	{	
		int BodySz(msg->GetPackBodySize());
		msg->Pack();
		P temp_msg = M::New();
		temp_msg->InitPack();
		memcpy(temp_msg->GetPackPointer(), msg->GetPackPointer(), temp_msg->GetPackSize());
		temp_msg->Unpack();
		temp_msg->AllocatePack();
		int s = msg->GetPackBodySize();
		int s1 = temp_msg->GetPackBodySize();
		//memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), BodySz);
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


//template<class P, class M>
//inline P RetrieveMessage3(igtl::MessageBase::Pointer msg)
//{
//	
//	//if(msg.IsNotNull())
//	//{	
//	//	int BodySz(msg->GetPackBodySize());
//	//
//	//	msg->Pack();
//	//	igtl::MessageHeader::Pointer headerMsg;
//	//	headerMsg = igtl::MessageHeader::New();
//	//	// Initialize receive buffer
//	//	headerMsg->InitPack();
//	//	memcpy(headerMsg->GetPackPointer(), msg->GetPackPointer(), headerMsg->GetPackSize());
//	//	// Deserialize the header
//	//	headerMsg->Unpack();
//	//	
//	//	P temp_msg = M::New();
//	//	temp_msg->SetMessageHeader(headerMsg);
//	//	temp_msg->AllocatePack();
//
//	//		int s3 = temp_msg->GetBodySizeToRead();
//	//		int s4 = msg->GetBodySizeToRead();
//
//	//		int s5 = temp_msg->GetPackBodySize();
//	//		int s6 = msg->GetPackBodySize();
//	//	
//	//	memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetPackBodySize());
//	//	//memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetBodySizeToRead());
//	//	//memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), BodySz);
//	//	//memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), s6);
//	//	int c = temp_msg->Unpack(1);
//	//	if( c & igtl::MessageHeader::UNPACK_BODY) 
//	//		return temp_msg;
//	//	else 
//	//		return  NULL;
//	//}
//	//else 
//	//	return NULL;
//	
//	
//	
//	if(msg.IsNotNull())
//	{	
//		int BodySz(msg->GetPackBodySize());
//		msg->Pack();
//		P temp_msg = M::New();
//		temp_msg->InitPack();
//			int s1 = temp_msg->GetPackSize();
//			int s2 = msg->GetPackSize();
//		memcpy(temp_msg->GetPackPointer(), msg->GetPackPointer(), temp_msg->GetPackSize());
//		temp_msg->Unpack();
//		temp_msg->AllocatePack();
//			int s3 = temp_msg->GetBodySizeToRead();
//			int s4 = msg->GetBodySizeToRead();
//		//memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetPackBodySize());
//		memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), BodySz);
//		int c = temp_msg->Unpack(1);
//		if( c & igtl::MessageHeader::UNPACK_BODY) 
//			return temp_msg;
//		else 
//			return  NULL;
//	}
//	else 
//		return NULL;
//}


template<class P, class M>
inline igtl::MessageBase::Pointer RetrieveMessagefromIODevice(igtl::MessageBase::Pointer msg)
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
//template<class P, class M>
//inline P RetrieveMessagefromIODevice(igtl::MessageBase::Pointer msg)
//{
//	if(msg.IsNotNull())
//	{	
//		//int BodySz(msg->GetPackBodySize());
//		msg->Pack();
//		P temp_msg = M::New();
//		temp_msg->SetMessageHeader(msg);
//		temp_msg->AllocatePack();
//		//int s =temp_msg->GetPackBodySize();
//		memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetPackBodySize());
//		//memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), BodySz);
//		int c = temp_msg->Unpack(1);
//		if( c & igtl::MessageHeader::UNPACK_BODY) 
//			return temp_msg;
//		else 
//			return  NULL;
//	}
//	else 
//		return NULL;
//}


//template<class P, class M>
//inline P RetrieveMessagefromIODevice2(igtl::MessageBase::Pointer msg)
//{
//	if(msg.IsNotNull())
//	{	
//		int BodySz(msg->GetPackBodySize());
//		msg->Pack();
//		P temp_msg = M::New();
//		temp_msg->SetMessageHeader(msg);
//		temp_msg->AllocatePack();
//		int s =temp_msg->GetPackBodySize();
//		//memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetPackBodySize());
//		memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), BodySz);
//		int c = temp_msg->Unpack(1);
//		if( c & igtl::MessageHeader::UNPACK_BODY) 
//			return temp_msg;
//		else 
//			return  NULL;
//	}
//	else 
//		return NULL;
//}
//template<class P, class M>
//inline P RecoverIGTLMSg(igtl::MessageBase::Pointer msg)
//{
//	if(msg.IsNotNull())
//	{	
//		msg->Pack();
//		P temp_msg = M::New();
//		temp_msg->InitPack();
//		int s1 = temp_msg->GetPackSize();
//		int s2 = msg->GetPackSize();
//		memcpy(temp_msg->GetPackPointer(), msg->GetPackPointer(), temp_msg->GetPackSize());
//		temp_msg->Unpack();
//		temp_msg->AllocatePack();
//		int s3 = temp_msg->GetBodySizeToRead();
//		int s4 = msg->GetBodySizeToRead();
//		memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetPackBodySize());
//		int c = temp_msg->Unpack(1);
//		//int c = temp_msg->Unpack();
//		//if(c & M::UNPACK_BODY)
//		if( c & igtl::MessageHeader::UNPACK_BODY) 
//			return temp_msg;
//		else 
//			return  NULL;
//	}
//	else 
//		return NULL;
//	//if(msg.IsNotNull())
//	//{	
//	//	//msg->Pack();
//	//	P temp_msg = M::New();
//	//	temp_msg->SetMessageHeader(msg);
//	//	temp_msg->AllocatePack();
//	//	memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetPackBodySize());
//	//	//int c = temp_msg->Unpack(1);
//	//	//int c = temp_msg->Unpack();
//
//	//	/*if( c & igtl::MessageHeader::UNPACK_BODY) 
//	//		return temp_msg;
//	//	else 
//	//		return  NULL;*/
//	//	return temp_msg;
//	//}
//	//else 
//	//	return NULL;
//}

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


igtl::TrackingDataElement::Pointer IGTLMCommon_EXPORT ExtractTrackingInfo(igtl::MessageBase::Pointer msg, int index);

void IGTLMCommon_EXPORT MatrixMultiplication(igtl::Matrix4x4& matA, igtl::Matrix4x4& matB, igtl::Matrix4x4& matC);

igtl::ImageMessage::Pointer IGTLMCommon_EXPORT DuplicateImageMessage(igtl::ImageMessage::Pointer img);

igtl::MessageBase::Pointer IGTLMCommon_EXPORT RetriveMessageBase(igtl::MessageBase::Pointer msg);

bool IGTLMCommon_EXPORT SetReferenceData(igtl::MessageBase::Pointer msg);
bool IGTLMCommon_EXPORT IsReferenceData(igtl::MessageBase::Pointer msg);

/// For Testing OpenIGTLink, OpenIGTlinkMUSiiC

void IGTLMCommon_EXPORT GetDummyMatrix1(igtl::Matrix4x4& matrix, bool print = false);

void IGTLMCommon_EXPORT GetDummyMatrix2(igtl::Matrix4x4& matrix, bool print = false);

igtl::MessageBase::Pointer IGTLMCommon_EXPORT GetDummyImageMessage(int x = 300, int y= 400, int z = 1, float sx = 0.5, float sy = 0.6, float sz = 1.0);

igtl::MessageBase::Pointer IGTLMCommon_EXPORT GetDummyStringMessage(std::string msg = "TestString");

igtl::MessageBase::Pointer IGTLMCommon_EXPORT GetDummyTrackingDataMessage();

igtl::MessageBase::Pointer IGTLMCommon_EXPORT GetDummyUSMessage(int x = 128, int y= 1024, int z = 1, float sx = 0.5, float sy = 0.6, float sz = 1.0);




};



#endif
