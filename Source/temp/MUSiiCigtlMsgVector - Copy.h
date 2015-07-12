/***************************************************************************
Copyright Dec/2010
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/
#ifndef __MUSICC_IGTLMSGVECTOR_
#define __MUSICC_IGTLMSGVECTOR_

#include "MUSiiCVector.h"
#include <igtlObject.h>
#include <igtlMessageBase.h>
#include <igtlTypes.h>

namespace igtl
{
class IGTLCommon_EXPORT MUSiiCigtlMsgVector:public MUSiiCVector<igtl::MessageBase::Pointer>
{
public:
	typedef MUSiiCigtlMsgVector							Self;
	typedef MUSiiCVector<igtl::MessageBase::Pointer>	Superclass;
	typedef SmartPointer<Self>							Pointer;
	typedef SmartPointer<Self>							ConstPointer;
	
	/** Method for creation through the object factory. */
	igtlNewMacro(MUSiiCigtlMsgVector);
  
	/** Run-time type information (and related methods). */
	igtlTypeMacro(MUSiiCigtlMsgVector, MUSiiCVector<igtl::MessageBase::Pointer>);
	
protected:
	
public:
	/// Constructor
	MUSiiCigtlMsgVector();
	
	/// Constructor
	//MUSiiCigtlMsgVector(igtl::ConditionVariable::Pointer Cond, igtl::SimpleMutexLock*  Lock);
	
	/// Deconstructor
	~MUSiiCigtlMsgVector();
	
	/// Find an index of specific igtlMessage on MUSiiCVector
	int Find_igtlMsg(igtl::MessageBase::Pointer data, std::vector<int>& list);
	
	/// Get the number of a specific igtlMessage on MUSiiCVector
	int GetCount_igtlMsg(igtl::MessageBase::Pointer data);
	
	/// Get idx-th element (a specific igtlMessage) from vector without removing the element
	/// the idx is zero-base
	/// Without Condition variable (without waiting)
	virtual int concurrent_try_get(igtl::MessageBase::Pointer data, int idx);
	
	/// Get idx-th element (a specific igtlMessage) from vector with removing the element
	/// the idx is zero-base
	/// Without Condition variable (without waiting)
	virtual int concurrent_try_get_pop(igtl::MessageBase::Pointer data, int idx, bool dropping = false);
	
	/// Get the first element (a specific igtlMessage) from vector without removing the element
	/// Without Condition variable (waiting)
	virtual int concurrent_try_get_front(igtl::MessageBase::Pointer data);
	
	/// Get the first element (a specific igtlMessage) from vector with removing the element
	/// Without Condition variable (waiting)
	virtual int concurrent_try_get_pop_front(igtl::MessageBase::Pointer data );
	
	/// Get the last element (a specific igtlMessage) from vector without removing the element
	/// Without Condition variable (waiting)
	virtual int concurrent_try_get_back(igtl::MessageBase::Pointer data);
	
	/// Get the last element (a specific igtlMessage) from vector with removing the element
	/// Without Condition variable (waiting)
	virtual int concurrent_try_get_pop_back(igtl::MessageBase::Pointer data, bool dropping = false);
	
	/// Get idx-th element (a specific igtlMessage) from vector without removing the element
	/// the idx is zero-base 
	/// With Condition variable
	virtual int concurrent_wait_get(igtl::MessageBase::Pointer data, int idx);
	
	/// Get idx-th element (a specific igtlMessage) from vector with removing the element
	/// the idx is zero-base 
	/// With Condition variable
	virtual int concurrent_wait_get_pop(igtl::MessageBase::Pointer data, int idx, bool dropping = false);
	
	/// Get the first element (a specific igtlMessage) from vector without removing the element
	/// With Condition variable (waiting)
	virtual int concurrent_wait_get_front(igtl::MessageBase::Pointer data);
	
	/// Get the first element (a specific igtlMessage) from vector with removing the element
	/// With Condition variable (waiting)
	virtual int concurrent_wait_get_pop_front(igtl::MessageBase::Pointer data);
	
	
	/// Get the first element (a specific igtlMessage) from vector without removing the element
	/// With Condition variable (waiting)
	virtual int concurrent_wait_get_back(igtl::MessageBase::Pointer data);
	
	
	/// Get the first element (a specific igtlMessage) from vector with removing the element
	/// With Condition variable (waiting)
	virtual int concurrent_wait_get_pop_back(igtl::MessageBase::Pointer data, bool dropping = false);
	
		
protected:
	
	
};
} //end of namespace
#endif