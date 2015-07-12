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



#ifndef __igtlGenMessage_h
#define __igtlGenMessage_h
/*=========================================================================
	igtl::GenMessage::Pointer genMsg = igtl::GenMessage::New();
	genMsg->AllocateData(void* src, int sz);
	genMsg->Pack();
	
	genMsg->Unpack(1);
	memcpy(genMsg->GetDataPointer(), (void*)dst, genMsg->GetDataSize());
	
=========================================================================*/
#include "igtlObject.h"
//#include "igtlMacros.h"
#include "igtlMath.h"
#include "igtlMessageBase.h"
#include "igtlTypes.h"
#include "igtlM_win32header.h"

namespace igtl
{
class IGTLMCommon_EXPORT GenMessage: public MessageBase
{
public:
	typedef GenMessage                  	Self;
	typedef MessageBase                   	Superclass;
	typedef SmartPointer<Self>            	Pointer;
	typedef SmartPointer<const Self>      	ConstPointer;

	igtlTypeMacro(igtl::GenMessage, igtl::MessageBase);
	igtlNewMacro(igtl::GenMessage);

public:
	//void 	SetDataSize(int sz) { m_DataSize = size;}
	void 	AllocateData(void* src, int sz);
	int 	GetDataSize(){return m_DataSize;}
	void*	GetDataPointer(){ return (void*) m_DataBody;}
	
protected:
	GenMessage();
	~GenMessage();
		
protected:
	virtual int		GetBodyPackSize();
	virtual int  	PackBody();
	virtual int  	UnpackBody();
  
	int 			m_DataSize;
	unsigned char*	m_DataBody;
	
}; // class Gen Message

} // namespce igtl

#endif // __igtlGenMessage_h