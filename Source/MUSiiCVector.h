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
#ifndef __MUSICC_VECTOR_
#define __MUSICC_VECTOR_

#include <vector>
#include <igtlMacro.h>
#include <igtlConditionVariable.h>
#include <igtlLightObject.h>
#include <igtlFastMutexLock.h>
#if defined(WIN32) || defined (_WIN32) || defined (__WIN32__)
#include "igtlM_win32header.h"
#endif
#include <string>
#include "MUSiiCProfile.h"

namespace igtl
{
template<class Data> class IGTLMCommon_EXPORT MUSiiCVector : public LightObject
{
public:
	typedef MUSiiCVector<Data>						Self;
	typedef LightObject							Superclass;
	typedef SmartPointer<Self>						Pointer;
	typedef SmartPointer<Self>						ConstPointer;
	
	/** Method for creation through the object factory. */
	igtlNewMacro(Self);
  
	/** Run-time type information (and related methods). */
	igtlTypeMacro(Self, Superclass);
	
protected:
	std::vector<Data>					m_MVector;
	/// Condition Variable for multithreaded programming 
	igtl::ConditionVariable::Pointer	m_Cond;
	/// Mutex for multithreaded programming 
	igtl::SimpleMutexLock				*m_Lock;

	//igtl::MutexLock::Pointer			m_Mutex;
	igtl::FastMutexLock::Pointer		m_Mutex;
	
	/// A boolean variable for checking current the status of Queue
	bool								m_bWaiting;
	/// A boolean variable to enforce termination.
	bool								m_bTerminate;
	/// A boolean variable about using self-mutex
	bool								m_bSelfMutex;

	std::string							m_Description;


	bool								m_bDebug;


	/// Condition Variable for multithreaded programming 
	igtl::ConditionVariable::Pointer	m_SetCond;
	/// Mutex for multithreaded programming 
	igtl::SimpleMutexLock				*m_SetLock;
	///
	bool                                m_bUseMUSiiCVectorSet;

	bool								m_bIsData;

	int									m_iIndex;
	
public:
	/// Constructor
	MUSiiCVector()
	{
		m_Cond					= igtl::ConditionVariable::New();
		m_Lock					= igtl::SimpleMutexLock::New();
		//m_Mutex				= igtl::MutexLock::New();
		m_Mutex					= igtl::FastMutexLock::New();
		m_Description			= "";
		m_bDebug				= false;
		m_bWaiting				= false;
		m_bTerminate			= false;
		m_bSelfMutex			= true;
		m_MVector.clear();
		m_SetCond				= NULL;
		m_SetLock				= NULL;
		m_bUseMUSiiCVectorSet	= false;
		m_bIsData               = false;
		m_iIndex				= -1;
	}

	/// Deconstructor
	~MUSiiCVector()
	{
		/*m_Cond.~SmartPointer();*/
		if(m_bSelfMutex)
		{
			m_Lock->Unlock();
			if(m_bDebug) 
				MUSiiC_LOG(logINFO) << "MUSiiC_Vector:: " << m_Description.c_str() << "delete m_Lock"; 
			delete m_Lock;
		}

		if(m_SetLock != NULL)
		{
			m_SetLock->Unlock();
			if(m_bDebug) 
				MUSiiC_LOG(logINFO) << "MUSiiC_Vector:: " << m_Description.c_str() << "delete m_Lock"; 
			delete m_SetLock;
		}

		if(m_Mutex.IsNotNull())
			m_Mutex->Unlock();
	}

	/// Set Debug Info
	void SetEnableDebugInfo(bool enable = true){m_bDebug= enable;}

    /// Set the conditional value of this class as the conditional value of MUSiiCVectorSet
	bool SetVectorSetCond(igtl::ConditionVariable::Pointer Cond, igtl::SimpleMutexLock* lock)
	{
		/// Check a input conditional value
		if(Cond.IsNotNull())
		{
			m_SetCond = Cond;
			m_SetLock = lock;
			m_bUseMUSiiCVectorSet = true;
		}
		else /// If the input conditional value is NULL
		{
			m_SetCond = NULL;
			m_SetLock = NULL;
			m_bUseMUSiiCVectorSet = false;
		}

		return m_bUseMUSiiCVectorSet;
	}

	bool IsData(){return m_bIsData;}

	void SetIndex(int index){m_iIndex = index;}

	int GetIndex(){return m_iIndex;}

	/// Check whether container is empty or not with mutex
	bool concurrent_empty() const
	{
		m_Mutex->Lock();
		bool b = empty();
		m_Mutex->Unlock();
		return b;
	}

	/// Clear contents of vector
	void concurrent_clear()
	{
		m_Mutex->Lock();
		if(m_bDebug) 
				MUSiiC_LOG(logINFO) << "MUSiiC_Vector:: " << m_Description.c_str() << "  Clear";
		clear();
		m_Mutex->Unlock();
	}
	
	/// Erase idx-th element of vector with mutex
	/// the index of idx is based "0 (zero)"
	int concurrent_erase_element(int idx)
	{
		m_Mutex->Lock();
		int s = m_MVector.size();
		
		if( idx > s || idx < 0)
		{
			m_Mutex->Unlock();
			return -1;
		}
		
		m_MVector.erase(m_MVector.begin()+idx);
		s = m_MVector.size();
		m_bIsData = s>0?true:false;
		m_Mutex->Unlock();
		
		return s;
	}
	
	/// erase elements between  idx1-th and idx2-th of vector with mutex
	/// idx1 and idx2 are zero-base
	int concurrent_erase_elements(int idx1, int idx2)
	{
		///Swap the idx1 and idx2
		if( idx1 > idx2)
		{
			int temp = idx2;
			idx2 = idx1;
			idx1 = temp;
		}
		
		m_Mutex->Lock();
		int s = m_MVector.size();
		
		if( idx1 < 0 || idx2 > s )
		{
			m_Mutex->Unlock();
			return -1;
		}
		
		m_MVector.erase(m_MVector.begin()+idx1, m_MVector.begin()+idx2);
		s = m_MVector.size();
		m_bIsData = s>0?true:false;
		m_Mutex->Unlock();
		
		return s;
	}
	
	/// Get a size of vector
	int concurrent_size()
	{	
		m_Mutex->Lock();
		int s = size();
		m_bIsData = s>0?true:false;
		m_Mutex->Unlock();
		return s;
	}
	
	/// Insert an element to the queue
	/// The return value is the size of MUSiiCVector
	virtual int concurrent_push_back(Data const& data)
	{
		///Insert Data into vector
		m_Mutex->Lock();
		m_MVector.push_back(data);
		m_Mutex->Unlock();
		//if(m_bWaiting)
		{
			m_Cond->Signal();
			m_bWaiting	= false;

			if(m_bUseMUSiiCVectorSet)
				m_SetCond->Signal();
		}
		int s(size());
		m_bIsData = s>0?true:false;
		return s;
	}
 
    /// Concurrent remove the specific data in the MUSiiCVector
	/// The return value is the size of MUSiiCVector
	virtual int concurrent_remove(Data const& data)
	{
		m_Mutex->Lock();
		int sz(size());
		for(int i=0; i<sz; i++)
		{
			if(m_MVector[i] == data)
			{
				m_MVector.erase(m_MVector.begin()+i);
				m_Mutex->Unlock();
				int s(size());
				m_bIsData = s>0?true:false;
				return s;
			}
		}

		m_Mutex->Unlock();
		return 0;
	}

	/// Get ID of the specific data in the MUSiiCVector
	/// The return value is the ID of the specific Data in MUSiiCVector
	virtual int concurrent_GetID(Data const& data)
	{
		m_Mutex->Lock();
		int sz(size());
		for(int i=0; i<sz; i++)
		{
			if(m_MVector[i] == data)
			{
				m_Mutex->Unlock();
				return i;
			}
		}

		m_Mutex->Unlock();
		return -1;
	}
	
	/// Insert an element to the queue
	/// The return value is the size of MUSiiCVector
	virtual int try_push_back(Data const& data)
	{
		///Insert Data into 
		m_MVector.push_back(data);
		
		if(m_bUseMUSiiCVectorSet)
				m_SetCond->Signal();

		int s(size());
		m_bIsData = s>0?true:false;
		return s;
	}
	
	/// Get idx-th element from vector without removing the element
	/// the idx is zero-base
	/// Without Condition variable (without waiting)
	virtual int concurrent_try_get(Data& data, int idx)
	{
		/// Lock the mutex
		m_Mutex->Lock();
		/// Get size of vector
		int s = m_MVector.size();
		/// check whether vector is empty or not
		if(m_MVector.empty() || idx < 0 || idx >= s)
		{
			m_Mutex->Unlock();
			return -1;
		}
		/// Get the first element from vector
		data = m_MVector[idx];
		/// Release mutex
		m_Mutex->Unlock();
		/// return the size of vector 
		m_bIsData = s>0?true:false;
		return s;
	}


	/// Get idx-th element from vector without removing the element
	/// the idx is zero-base
	/// Without Condition variable (without waiting)
	virtual Data concurrent_try_GetData(int idx)
	{
		Data data;
		/// Lock the mutex
		m_Mutex->Lock();
		/// Get size of vector
		int s = m_MVector.size();
		/// check whether vector is empty or not
		if(m_MVector.empty() || idx < 0 || idx >= s)
		{
			m_Mutex->Unlock();
			data = NULL;
			return data;
		}
		/// Get the first element from vector
		data = m_MVector[idx];
		/// Release mutex
		m_Mutex->Unlock();
		/// return the size of vector 
		m_bIsData = s>0?true:false;
		return data;
	}

	/// User-defined operator "[]" for MUSiiCVector
	/// I think this function is useless.
	virtual Data operator[](int idx)
	{
		return concurrent_try_GetData(idx);
	}
	
	/// Get idx-th element from vector with removing the element
	/// the idx is zero-base
	/// Without Condition variable (without waiting)
	virtual int concurrent_try_get_pop(Data& data, int idx, bool dropping = false)
	{
		/// Lock the mutex
		//printf("%p   mutex:%p :: %s concurrent_try_get_pop Locking\n",this, m_Lock,m_Description.c_str());
		m_Mutex->Lock();
		/// Get size of vector
		int s = m_MVector.size();
		/// check whether vector is empty or not
		if(m_MVector.empty() || idx < 0 || idx >= s)
		{
			//printf("%p   mutex:%p :: %s concurrent_try_get_pop Locking, No Data\n",this, m_Lock,m_Description.c_str());
			m_Mutex->Unlock();
			return -1;
		}
		
		if(dropping)
		{
			s = drop_sequence_elements(idx);
			idx = s-1; /// Update idx
		}
		
		/// Get the first element from vector
		data = m_MVector[idx];
		/// Delete the first element of vector
		erase_element(idx);
		/// Get size of vector
		s = m_MVector.size();
		m_bIsData = s>0?true:false;
		/// Release mutex
		//printf("%p   mutex:%p :: %s concurrent_try_get_pop Unocking, Got Data\n",this, m_Lock,m_Description.c_str());
		m_Mutex->Unlock();
		/// return the size of vector 
		return s;
	}

	/// Get idx-th element from vector with removing the element
	/// the idx is zero-base
	/// Without Condition variable (without waiting)
	/// Check this function :: cannon96
	virtual Data concurrent_try_GetData_pop(int idx, bool dropping = false)
	{
		/// Create Data Object
		Data data;
		
		/// Lock the mutex
		//printf("%p   mutex:%p :: %s concurrent_try_get_pop Locking\n",this, m_Lock,m_Description.c_str());
		m_Mutex->Lock();
		/// Get size of vector
		int s = m_MVector.size();
		/// check whether vector is empty or not
		if(m_MVector.empty() || idx < 0 || idx >= s)
		{
			//printf("%p   mutex:%p :: %s concurrent_try_get_pop Locking, No Data\n",this, m_Lock,m_Description.c_str());
			m_Mutex->Unlock();
			data = NULL;
			return data;
		}
		
		if(dropping)
		{
			s = drop_sequence_elements(idx);
			idx = s-1; /// Update idx
		}

		
		/// Get the first element from vector
		data = m_MVector[idx];
		/// Delete the first element of vector
		erase_element(idx);
		/// Get size of vector
		s = m_MVector.size();
		m_bIsData = s>0?true:false;
		/// Release mutex
		//printf("%p   mutex:%p :: %s concurrent_try_get_pop Unocking, Got Data\n",this, m_Lock,m_Description.c_str());
		m_Mutex->Unlock();
		/// return the size of vector 
		return data;
	}

	/// User-defined operator "()" for MUSiiCVector
	/// I think this function is useless.
	virtual Data operator()(int idx,  bool dropping = false)
	{
		return concurrent_try_GetData_pop(idx, dropping);
	}
	
	
	//virtual Data concurrent_try_GetData(int idx)
	//virtual Data concurrent_try_GetData_pop(int idx, bool dropping = false)
	
	/// Get the first element from vector without removing the element
	/// Without Condition variable (waiting)
	virtual int concurrent_try_get_front(Data& data)
	{
		return concurrent_try_get(data, 0);
	}

	/// Get the first element from vector without removing the element
	/// Without Condition variable (waiting)
	//virtual Data concurrent_try_GetData_front(Data& data)
	virtual Data concurrent_try_GetData_front()
	{
		return concurrent_try_GetData(0);
	}
	
	/// Get the first element from vector with removing the element
	/// Without Condition variable (waiting)
	virtual int concurrent_try_get_pop_front(Data& data)
	{
		return concurrent_try_get_pop(data, 0, false);
	}
	
	/// Get the first element from vector with removing the element
	/// Without Condition variable (waiting)
	virtual Data concurrent_try_GetData_pop_front()
	{
		return concurrent_try_GetData_pop(0, false);
	}

	///////////////////////////////////////////////////////////////////////
	/// Get the last element from vector without removing the element
	/// Without Condition variable (waiting)
	virtual int concurrent_try_get_back(Data& data)
	{
		int s = concurrent_size();
		return concurrent_try_get(data, s-1);
	}
	
	/// Get the last element from vector without removing the element
	/// Without Condition variable (waiting)
	virtual Data concurrent_try_GetData_back(Data& data)
	{
		int s = concurrent_size();
		return concurrent_try_GetData(s-1);
	}

	/// Get the last element from vector with removing the element
	/// Without Condition variable (waiting)
	virtual int concurrent_try_get_pop_back(Data& data, bool dropping = false)
	{
		int s = concurrent_size();
		return concurrent_try_get_pop(data, s-1, dropping);
	}

	/// Get the last element from vector with removing the element
	/// Without Condition variable (waiting)
	virtual Data concurrent_try_GetData_pop_back(bool dropping = false)
	{
		int s = concurrent_size();
		return concurrent_try_GetData_pop(s-1, dropping);
	}

	///////////////////////////////////////////////////////////////////////////////////
	
	
	/// Get idx-th element from vector without removing the element
	/// the idx is zero-base 
	/// With Condition variable
	virtual int concurrent_wait_get(Data& data, int idx)
	{
		if(idx < 0 ) return -1;
		int s = size();
		while(1)
		{
			m_Mutex->Lock();
			if(!m_MVector.empty() && idx < s)
			{
				break;
			}
			else if(m_MVector.empty() && m_bTerminate)
			{
				m_bTerminate = false;
				m_bWaiting = false;
				m_Mutex->Unlock();
				return -1;
			}
			else
			{
				m_bWaiting	= true;
				m_Mutex->Unlock();
				m_Lock->Lock();
				m_Cond->Wait(m_Lock);
				m_Lock->Unlock();
				continue;
			}
		}
		
		data = m_MVector[idx];
		s = size();
		m_bIsData = s>0?true:false;
		m_Mutex->Unlock();
		return s;
	}

	/// Get idx-th element from vector without removing the element
	/// the idx is zero-base 
	/// With Condition variable
	virtual Data concurrent_wait_GetData(int idx)
	{
		Data data;
		if(idx < 0 )
		{
			data = NULL;
			return data;
		}
		int s = size();
		
		while(1)
		{
			m_Mutex->Lock();
			if(!m_MVector.empty() && idx < s)
			{
				break;
			}
			else if(m_MVector.empty() && m_bTerminate)
			{
				m_bTerminate = false;
				m_bWaiting = false;
				m_Mutex->Unlock();
				data = NULL;
				return data;
			}
			else
			{
				m_bWaiting	= true;
				m_Mutex->Unlock();
				m_Lock->Lock();
				m_Cond->Wait(m_Lock);
				m_Lock->Unlock();
				continue;
			}
		}
		
		data = m_MVector[idx];
		s = size();
		m_bIsData = s>0?true:false;
		m_Mutex->Unlock();
		return data;
	}
	
	/// Get idx-th element from vector with removing the element
	/// the idx is zero-base 
	/// With Condition variable
	virtual int concurrent_wait_get_pop(Data& data, int idx, bool dropping = false)
	{
		if(idx < 0 ) return -1;
		int s;
		while(1)
		{
			//printf("%p : mutex:%p :%s concurrent_wait_get_pop Locking\n", this, m_Lock, m_Description.c_str());
			m_Mutex->Lock();
			s = size();
			if(!m_MVector.empty() && idx < s)
			{
				break;
			}
			else if(m_MVector.empty() && m_bTerminate)
			{
				m_bTerminate = false;
				m_bWaiting = false;
				m_Mutex->Unlock();
				return -1;
			}
			else
			{
				
				m_bWaiting	= true;
				m_Mutex->Unlock();
				m_Lock->Lock();
				m_Cond->Wait(m_Lock);
				m_Lock->Unlock();
				continue;
			}
		}
		
		if(dropping)
		{
			s = drop_sequence_elements(idx);
			idx = s-1; /// Update idx
		}
		
		data = m_MVector[idx];
		/// Delete the first element of vector
		erase_element(idx);
		s = size();
		m_bIsData = s>0?true:false;
		m_Mutex->Unlock();
		//printf("%p :  mutex:%p : %s concurrent_wait_get_pop Unocking & data got\n", this,m_Lock, m_Description.c_str());
		return s;
	}

	/// Get idx-th element from vector with removing the element
	/// the idx is zero-base 
	/// With Condition variable
	virtual Data concurrent_wait_GetData_pop(int idx, bool dropping = false)
	{
		Data data;
		if(idx < 0 )
		{
			data = NULL;
			return data;
		}

		int s;
		while(1)
		{
			//printf("%p : mutex:%p :%s concurrent_wait_get_pop Locking\n", this, m_Lock, m_Description.c_str());
			m_Mutex->Lock();
			s = size();
			if(!m_MVector.empty() && idx < s)
			{
				break;
			}
			else if(m_MVector.empty() && m_bTerminate)
			{
				m_bTerminate = false;
				m_bWaiting = false;
				m_Mutex->Unlock();
				data = NULL;
				return data;
			}
			else
			{
				
				m_bWaiting	= true;
				m_Mutex->Unlock();
				m_Lock->Lock();
				m_Cond->Wait(m_Lock);
				m_Lock->Unlock();
				continue;
			}
		}
		
		if(dropping)
		{
			s = drop_sequence_elements(idx);
			idx = s-1; /// Update idx
		}
		
		data = m_MVector[idx];
		/// Delete the first element of vector
		erase_element(idx);
		s = size();
		m_bIsData = s>0?true:false;
		m_Mutex->Unlock();
		//printf("%p :  mutex:%p : %s concurrent_wait_get_pop Unocking & data got\n", this,m_Lock, m_Description.c_str());
		return data;
	}
	
	/// Get the first element from vector without removing the element
	/// With Condition variable (waiting)
	virtual int concurrent_wait_get_front(Data& data)
	{
		return concurrent_wait_get(data, 0);
	}
	
	/// Get the first element from vector without removing the element
	/// With Condition variable (waiting)
	virtual Data concurrent_wait_GetData_front()
	{
		return concurrent_wait_GetData(0);
	}
	
	/// Get the first element from vector with removing the element
	/// With Condition variable (waiting)
	virtual int concurrent_wait_get_pop_front(Data& data)
	{
		return concurrent_wait_get_pop(data, 0, false);
	}


	/// Get the first element from vector with removing the element
	/// With Condition variable (waiting)
	virtual Data concurrent_wait_GetData_pop_front()
	{
		return concurrent_wait_GetData_pop(0, false);
	}
	
	/// Get the first element from vector without removing the element
	/// With Condition variable (waiting)
	virtual int concurrent_wait_get_back(Data& data)
	{
		int s = concurrent_size();
		return concurrent_wait_get(data, s-1);
	}

	/// Get the first element from vector without removing the element
	/// With Condition variable (waiting)
	virtual Data concurrent_wait_GetData_back()
	{
		int s = concurrent_size();
		return concurrent_wait_GetData(s-1);
	}
	
	/// Get the first element from vector with removing the element
	/// With Condition variable (waiting)
	virtual int concurrent_wait_get_pop_back(Data& data, bool dropping = false)
	{
		int s = concurrent_size();
		return concurrent_wait_get_pop(data, s-1, dropping);
	}

	/// Get the first element from vector with removing the element
	/// With Condition variable (waiting)
	virtual Data concurrent_wait_GetData_pop_back(bool dropping = false)
	{
		int s = concurrent_size();
		return concurrent_wait_GetData_pop(s-1, dropping);
	}
	
	
	/// Check a status of this queue
	bool IsWaiting() {return m_bWaiting;}

	/// Enforce release Mutex and conditional variable
	/// for terminating thread.
	void EnforceRelease()
	{
		/// To Do : check this point:: cannon96
		//if(m_bWaiting) 
		{
			std::cout << "MUSiiCVector EnforceRelease" << std::endl;
			m_bTerminate = true;
			m_Cond->Signal();
			if(m_bUseMUSiiCVectorSet)
				m_SetCond->Signal();
		}
	}

    /// Set a description of this class
	void SetDescription(std::string des)
	{
		m_Description = des;
	}

    /// Get the discription of this class
	std::string GetDescription()
	{
		return m_Description;
	}
	
	
	
protected:
	/// Check whether container is empty or not
	bool empty() const
	{
		return m_MVector.empty();
	}
	
	/// Clear contents of vector
	void clear()
	{
		m_MVector.clear();
	}
	
	/// erase idx-th element of vector without mutex
	/// the index of idx is based "0 (zero)"
	int erase_element(int idx)
	{
		int s = m_MVector.size();
		
		if( idx > s || idx < 0)
			return -1;
		
		m_MVector.erase(m_MVector.begin()+idx);
		return m_MVector.size();
	}
	
	/// erase elements between  idx1-th and idx2-th of vector without mutex
	/// idx1 and idx2 are zero-base
	int erase_elements(int idx1, int idx2)
	{
		int s = m_MVector.size();
		
		///Swap the idx1 and idx2
		if( idx1 > idx2)
		{
			int temp = idx2;
			idx2 = idx1;
			idx1 = temp;
		}
		
		if( idx1 < 0 || idx2 > s )
			return -1;
		
		m_MVector.erase(m_MVector.begin()+idx1, m_MVector.begin()+idx2);
		s = size();
		m_bIsData = s>0?true:false;
		return  s;
	}
	
	/// Get a size of vector
	int size()
	{	
		return m_MVector.size();
	}
	
	/// Insert an element to the queue
	virtual int push_back(Data const& data)
	{
		///Insert Data into queue
		m_MVector.push_back(data);
		int s(size());
		m_bIsData = s>0?true:false;
		return  s;
	}
	
	/// Delete elements ( from 0 to idx-1)
	/// idx is zero-base
	virtual int drop_sequence_elements(int idx)
	{
		return erase_elements(0,idx-1);
	}

    /// Drop Elements from MUSiiCVector
	virtual int drop_elements(std::vector<int>& list)
	{
		int s ,j;
		s = list.size();
		for(int i=0; i<s; i++)
		{	
			j = list[i];
			erase_element(j);
		}
		
		s = size();
		m_bIsData = s>0?true:false;
		return  s;
	}

	

};
} //end of namespace
#endif
