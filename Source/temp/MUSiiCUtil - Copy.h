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

#include <igtlMessageBase.h>

#include <igtlBindMessage.h>

#include <igtlColorTableMessage.h>

#include <igtlImageMessage.h>
#include <igtlImageMetaMessage.h>
#include <igtlLabelMetaMessage.h>

#include <cstring>

#include <igtlNDArrayMessage.h>

#include <igtlPointMessage.h>
#include <igtlPositionMessage.h>

#include <igtlQuaternionTrackingDataMessage.h>

#include <igtlSensorMessage.h>
#include <igtlStatusMessage.h>
#include <igtlStringMessage.h>

#include <igtlTrackingDataMessage.h>
#include <igtlTransformMessage.h>
#include <igtlTrajectoryMessage.h>

#include "igtlMUSMessage.h"
#include "igtlMEIMessage.h"
#include "igtlMGenMessage.h"
#include "igtlMArgMessage.h"
#include "igtlMFileMessage.h"
#include "igtlMFixedImage.h"
#include "igtlMFixedImageBMode.h"

namespace igtl
{

double IGTLMCommon_EXPORT GetTimeStamp(igtl::MessageBase::Pointer msg);

template<class P, class M>
inline P RetrieveMessage(igtl::MessageBase::Pointer msg)
{
	//if(msg.IsNotNull())
	//{	
	//	int p0 = msg->GetPackSize();
	//	int BodySz(msg->GetPackBodySize());
	//	msg->Pack();
	//	//igtl::MessageHeader::Pointer headerMsg;
	//	//headerMsg = igtl::MessageHeader::New();
	//	//// Initialize receive buffer
	//	//headerMsg->InitPack();
	//	//memcpy(headerMsg->GetPackPointer(), msg->GetPackPointer(), headerMsg->GetPackSize());
	//	//// Deserialize the header
	//	//headerMsg->Unpack();
	//	//
	//	
	//	P temp_msg = M::New();
	//	temp_msg->InitPack();
	//	int s1 = temp_msg->GetPackSize();
	//	int s2 = msg->GetPackSize();
	//	memcpy(temp_msg->GetPackPointer(), msg->GetPackPointer(), temp_msg->GetPackSize());
	//	temp_msg->Unpack();
	//	//temp_msg->SetMessageHeader(headerMsg);
	//	temp_msg->AllocatePack();
	//	int p1 = temp_msg->GetPackSize();
	//	int s3 = temp_msg->GetBodySizeToRead();
	//	int s4 = msg->GetBodySizeToRead();
	//	int s5 = temp_msg->GetPackBodySize();
	//	int s6 = msg->GetPackBodySize();
	//	//memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetPackBodySize());
	//	//memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetBodySizeToRead());
	//	//memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), BodySz);
	//	memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), s5);
	//	int c = temp_msg->Unpack(1);
	//	if( c & igtl::MessageHeader::UNPACK_BODY) 
	//		return temp_msg;
	//	else 
	//		return  NULL;
	//}
	//else 
	//	return NULL;
	
	//if(msg.IsNotNull())
	//{	
	//	msg->Pack();
	//	P temp_msg = M::New();
	//	temp_msg->InitPack();
	//	
	//	int s1 = temp_msg->GetPackSize();
	//	int s2 = msg->GetPackSize();
	//	
	//	memcpy(temp_msg->GetPackPointer(), msg->GetPackPointer(), temp_msg->GetPackSize());
	//	temp_msg->Unpack();
	//	temp_msg->AllocatePack();
	//	
	//	int s3 = temp_msg->GetBodySizeToRead();
	//	int s4 = msg->GetBodySizeToRead();
	//	
	//	memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetPackBodySize());
	//	//int c = temp_msg->Unpack(1);
	//	int c = temp_msg->Unpack();
	//	//if(c & M::UNPACK_BODY)
	//	if( c & igtl::MessageHeader::UNPACK_BODY) 
	//		return temp_msg;
	//	else 
	//		return  NULL;
	//}
	//else 
	//	return NULL;
	
	if(msg.IsNotNull())
	{	
		int BodySz(msg->GetPackBodySize());
		msg->Pack();
		P temp_msg = M::New();
		temp_msg->SetMessageHeader(msg);
		temp_msg->AllocatePack();
		int s =temp_msg->GetPackBodySize();
		//memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetPackBodySize());
		memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), BodySz);
		int c = temp_msg->Unpack(1);
		//int c = temp_msg->Unpack();
		//if(c & M::UNPACK_BODY)
		if( c & igtl::MessageHeader::UNPACK_BODY) 
			return temp_msg;
		else 
			return  NULL;
	}
	else 
		return NULL;
}


template<class P, class M>
inline P RetrieveMessageIO(igtl::MessageBase::Pointer msg)
{
	if(msg.IsNotNull())
	{	
		//int BodySz(msg->GetPackBodySize());
		msg->Pack();
		P temp_msg = M::New();
		temp_msg->SetMessageHeader(msg);
		temp_msg->AllocatePack();
		int s =temp_msg->GetPackBodySize();
		memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetPackBodySize());
		//memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), BodySz);
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
inline P RecoverIGTLMSg(igtl::MessageBase::Pointer msg)
{
	if(msg.IsNotNull())
	{	
		msg->Pack();
		P temp_msg = M::New();
		temp_msg->InitPack();
		int s1 = temp_msg->GetPackSize();
		int s2 = msg->GetPackSize();
		memcpy(temp_msg->GetPackPointer(), msg->GetPackPointer(), temp_msg->GetPackSize());
		temp_msg->Unpack();
		temp_msg->AllocatePack();
		int s3 = temp_msg->GetBodySizeToRead();
		int s4 = msg->GetBodySizeToRead();
		memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetPackBodySize());
		//int c = temp_msg->Unpack(1);
		int c = temp_msg->Unpack();
		//if(c & M::UNPACK_BODY)
		if( c & igtl::MessageHeader::UNPACK_BODY) 
			return temp_msg;
		else 
			return  NULL;
	}
	else 
		return NULL;
	//if(msg.IsNotNull())
	//{	
	//	//msg->Pack();
	//	P temp_msg = M::New();
	//	temp_msg->SetMessageHeader(msg);
	//	temp_msg->AllocatePack();
	//	memcpy(temp_msg->GetPackBodyPointer(),msg->GetPackBodyPointer(), temp_msg->GetPackBodySize());
	//	//int c = temp_msg->Unpack(1);
	//	//int c = temp_msg->Unpack();

	//	/*if( c & igtl::MessageHeader::UNPACK_BODY) 
	//		return temp_msg;
	//	else 
	//		return  NULL;*/
	//	return temp_msg;
	//}
	//else 
	//	return NULL;
}


template<class P>
inline igtl::MessageBase::Pointer ConvertMessageBase(P msg)
{
	if(msg.IsNotNull())
	{	
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
		memcpy(temp_msg->GetPackBodyPointer(), msg->GetPackBodyPointer(), temp_msg->GetBodySizeToRead());
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
};



#endif
