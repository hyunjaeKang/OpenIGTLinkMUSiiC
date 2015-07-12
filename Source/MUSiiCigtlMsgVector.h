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
#ifndef __MUSICC_IGTLMSGVECTOR_
#define __MUSICC_IGTLMSGVECTOR_

#include "MUSiiCVector.h"
#include <igtlObject.h>
#include <igtlMessageBase.h>
#include <igtlTypes.h>


namespace igtl
{
class IGTLMCommon_EXPORT MUSiiCIGTLMsgVector:public MUSiiCVector<igtl::MessageBase::Pointer>
{
public:
	typedef MUSiiCIGTLMsgVector						        Self;
	typedef MUSiiCVector<igtl::MessageBase::Pointer>		Superclass;
	typedef SmartPointer<Self>						        Pointer;
	typedef SmartPointer<Self>						        ConstPointer;
	
	/** Method for creation through the object factory. */
	igtlNewMacro(Self);
  
	/** Run-time type information (and related methods). */
	igtlTypeMacro(Self, Superclass);
	
protected:
	
public:
	/// Constructor
	MUSiiCIGTLMsgVector()
	{
	}
	
	/// Deconstructor
	~MUSiiCIGTLMsgVector()
	{
	}

	igtl::MUSiiCVector<igtl::MessageBase::Pointer>::Pointer GetSmartPointer()
	{
		return (igtl::MUSiiCVector<igtl::MessageBase::Pointer>::Pointer)this;
	}
		
protected:
	
	
};
} //end of namespace
#endif