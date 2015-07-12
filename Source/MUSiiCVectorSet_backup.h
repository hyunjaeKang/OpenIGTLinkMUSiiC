/***************************************************************************
Copyright Dec/2010
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/
#ifndef __MUSICC_VECTOR_SET_
#define __MUSICC_VECTOR_SET_

#include "MUSiiCVector.h"

namespace igtl
{
template<class Data> class IGTLMCommon_EXPORT MUSiiCVectorSet : public LightObject
{
public:
	typedef MUSiiCVectorSet<Data>					Self;
	typedef LightObject							Superclass;
	typedef SmartPointer<Self>						Pointer;
	typedef SmartPointer<Self>						ConstPointer;
	
	/** Method for creation through the object factory. */
	igtlNewMacro(Self);
  
	/** Run-time type information (and related methods). */
	igtlTypeMacro(Self, Superclass);
	
protected:
	igtl::MUSiiCVector<igtl::MUSiiCVector<Data>*>	m_MVector;
	/// Condition Variable for multithreaded programming 
	igtl::ConditionVariable::Pointer			    m_Cond;
	/// Mutex for multithreaded programming 
	igtl::SimpleMutexLock						    *m_Lock;
	//SmartPointer<igtl::SimpleMutexLock>				m_Lock;

	/// A boolean variable for checking current the status of Queue
	bool								            m_bWaiting;
	/// A boolean variable to enforce termination.
	bool								            m_bTerminate;
	/// A boolean variable about using self-mutex
	bool								            m_bSelfMutex;

	std::string							            m_sDescription;


	bool								            m_bDebug;

	bool											m_bIsVectors;

public:
	
	
public:
	/// Constructor
	MUSiiCVectorSet()
	{
		m_Cond			= igtl::ConditionVariable::New();
		//m_Lock			= igtl::SimpleMutexLock::New();
		m_Lock			= new igtl::SimpleMutexLock;
		m_sDescription  = "";
		m_bDebug        = false;
		m_bWaiting      = false;
		m_bTerminate    = false;
		m_bSelfMutex    = true;
		m_bIsVectors    = false;
		m_MVector.concurrent_clear();
	}


	/// Deconstructor
	~MUSiiCVectorSet()
	{
		if(m_bSelfMutex)
		{
			if(m_bDebug) 
				MUSiiC_LOG(logINFO) << "MUSiiCVectorSet:: " << m_sDescription.c_str() << "delete m_Lock"; 
			delete m_Lock;
		}
	}

	/// Set Debug Info
	void SetEnableDebugInfo(bool enable = true){m_bDebug= enable;}

	std::string GetDescription(){return m_sDescription;}
	
	int GetSizeOfMUSiiCVectorSet(){return m_MVector.concurrent_size();}
	
	/// Add an object of MUSiiCVector
	/// return value is the ID of new MUSiiCVector
	int AddMUSiiCVector(igtl::MUSiiCVector<Data>* pMVector)
	{
		 int s(0);
		 if(pMVector)
		 {
			if(pMVector->SetVectorSetCond(this->m_Cond, this->m_Lock))
			{
				s = m_MVector.concurrent_push_back(pMVector);
				m_bIsVectors =  s>0 ? true : false;
				return s-1;
			}
		 }

		 return -1;
	}
	
	/// Get a object of MUSiiCVector from MUSiiCVectorSet using index number
	igtl::MUSiiCVector<Data>* GetMUSiiCVector(int index= 0)
	{
		if(m_bISVector && CheckIndex(index))
		{
			igtl::MUSiiCVector<Data>* tempVector = NULL;
			m_MVector.concurrent_try_get(tempVector, index);
			return tempVector;
		}
		return NULL;
	}
	
	/// Check the given index is available or not
	bool CheckIndex(int index = 0){return index < m_MVector.concurrent_size()? true : false;}

	/// Check that IS there a MUSiiCVector object on MUSiiCVectorSet
	bool IsMUSiiCVectors(){return m_bIsVectors;}

	//// Relase MUSiiCVector with given index
	bool RelaseMUSiiCVector(int index)
	{
		if(m_bIsVectors && CheckIndex(index))
		{
			igtl::MUSiiCVector<Data>* tempVector = NULL;
			m_MVector.concurrent_try_get(tempVector, index);
			if(tempVector && tempVector->IsWaiting())
			{
				tempVector->EnforceRelease();
				return true;
			}
		}

		return false;
	}

	/// Empty all contens of a specific MUSiiCVector
	bool CleanMUSiiCVector(int index)
	{
		if(m_bIsVectors && CheckIndex(index))
		{
			igtl::MUSiiCVector<Data>* tempVector = NULL;
			m_MVector.concurrent_try_get(tempVector, index);
			if(tempVector)
			{
				tempVector->concurrent_clear();
				return true;
			}
		}

		return false;
	}

	//// Remove a MUSiiCVector using its ID
	int RemoveMUSiiCVectorID(int index)
	{
		int s(0);
		if(this->RelaseMUSiiCVector(index))
		{
			s = m_MVector.concurrent_erase_element(index);
		    m_bIsVectors =  s>0 ? true : false;
			return s;
		}
		else
			return -1;
	}


	//// Remove a MUSiiCVector 
	int RemoveMUSiiCVector(igtl::MUSiiCVector<Data>* pMVector)
	{
		return this->RemoveMUSiiCVectorID(m_MVector.concurrent_GetID(pMVector));
	}


	//// Clear MUSiiCVectorSet
	bool ClearMUSiiCVectorSet()
	{
		int s(m_MVector.concurrent_size());
		bool r(true);

		for(int i=0; i<s; i++)
			r &= this->RelaseMUSiiCVector(i);

		if(r)
		{
			m_MVector.concurrent_clear();
			m_bIsVectors = false;
			return true;
		}

		return false;
	}


	// data : an instance data
	// Vindex : the index of MUSiiCVector in MUSiiCVectorSet
	int Try_push_back(Data const& data, int Vindex)
	{
		if(m_bIsVectors && CheckIndex(Vindex))
		{
			igtl::MUSiiCVector<Data>* tempVector = NULL;
			m_MVector.concurrent_try_get(tempVector, Vindex);
			return tempVector->try_push_back(data);
		}
	}
	
	/// Put Data into all MUSiiCVector of MUSiiCVectorSet
	// data : an instance data
	int Try_push_back_ALL(Data const& data)
	{
		int r(0);
		int s(m_MVector.concurrent_size());
		for(int i=0; i<s; i++)
			r += this->Try_push_back(data,i);

		return r;
	}

	/// Put Data into a specific MUSiiCVector
	// data : an instance data
	// Vindex : the index of MUSiiCVector in MUSiiCVectorSet
	int Concurrent_push_back(Data const& data, int Vindex)
	{
		if(m_bIsVectors && CheckIndex(Vindex))
		{
			igtl::MUSiiCVector<Data>* tempVector = NULL;
			m_MVector.concurrent_try_get(tempVector, Vindex);
			return tempVector->concurrent_push_back(data);
		}
	}

	/// Put Data into all MUSiiCVector of MUSiiCVectorSet
	// data : an instance data
	int Concurrent_push_back_ALL(Data const& data)
	{
		int r(0)
		int s(m_MVector.concurrent_size());
		for(int i=0; i<s; i++)
			r += this->Concurrent_push_back(data,i);

		return r;
	}

	///
	// Vindex : the index of MUSiiCVector in MUSiiCVectorSet
	bool IsDataAtMUSiiCVector(int Vindex)
	{
		if(m_bIsVectors && CheckIndex(Vindex))
		{
			igtl::MUSiiCVector<Data>* tempVector = NULL;
			m_MVector.concurrent_try_get(tempVector, Vindex);
			return tempVector->IsData();
		}

		return false;
	}


	///
	// data : an instance data
	// Vindex : the index of MUSiiCVector in MUSiiCVectorSet
	// Dindex : the index of DATA in MUSiiCVector
	int Concurrent_Try_Get(Data& data, int Vindex, int Dindex)
	{
		if(m_bIsVectors && CheckIndex(Vindex))
		{
			igtl::MUSiiCVector<Data>* tempVector = NULL;
			m_MVector.concurrent_try_get(tempVector, Vindex);
			return tempVector->concurrent_try_get(data, Dindex);
		}

		return -1;
	}

	///
	// data : an instance data
	// Vindex : the index of MUSiiCVector in MUSiiCVectorSet
	// Dindex : the index of DATA in MUSiiCVector
	int Concurrent_Try_Get_Pop(Data& data, int Vindex, int Dindex)
	{
		if(m_bIsVectors && CheckIndex(Vindex))
		{
			igtl::MUSiiCVector<Data>* tempVector = NULL;
			m_MVector.concurrent_try_get(tempVector, Vindex);
			return tempVector->concurrent_try_get_pop(data, Dindex);
		}

		return -1;
	}

	// data : an instance data
	// Vindex : the index of MUSiiCVector in MUSiiCVectorSet
	// Dindex : the index of DATA in MUSiiCVector
	int Concurrent_Try_Get_front(Data& data, int Vindex)
	{
		if(m_bIsVectors && CheckIndex(Vindex))
		{
			igtl::MUSiiCVector<Data>* tempVector = NULL;
			m_MVector.concurrent_try_get(tempVector, Vindex);
			return tempVector->concurrent_try_get_front(data);
		}

		return -1;
	}

	////
	// data : an instance data
	// Vindex : the index of MUSiiCVector in MUSiiCVectorSet
	int Concurrent_Try_Get_Pop_front(Data& data, int Vindex)
	{
		if(m_bIsVectors && CheckIndex(Vindex))
		{
			igtl::MUSiiCVector<Data>* tempVector = NULL;
			m_MVector.concurrent_try_get(tempVector, Vindex);
			return tempVector->concurrent_try_get_pop_front(data);
		}

		return -1;
	}

	//////
	// data : an instance data
	// Vindex : the index of MUSiiCVector in MUSiiCVectorSet
	int Concurrent_Try_Get_back(Data& data, int Vindex)
	{
		if(m_bIsVectors && CheckIndex(Vindex))
		{
			igtl::MUSiiCVector<Data>* tempVector = NULL;
			m_MVector.concurrent_try_get(tempVector, Vindex);
			return tempVector->concurrent_try_get_back(data, Dindex);
		}

		return -1;
	}

	////
	// data : an instance data
	// Vindex : the index of MUSiiCVector in MUSiiCVectorSet
	int Concurrent_Try_Get_Pop_back(Data& data, int Vindex)
	{
		if(m_bIsVectors && CheckIndex(Vindex))
		{
			igtl::MUSiiCVector<Data>* tempVector = NULL;
			m_MVector.concurrent_try_get(tempVector, Vindex);
			return tempVector->concurrent_try_get_pop_back(data, Dindex);
		}

		return -1;
	}

	//////////////////
	// data : an instance data
	// Vindex : the index of MUSiiCVector in MUSiiCVectorSet
	// Dindex : the index of DATA in MUSiiCVector
	int Concurrent_wait_get(Data& data, int Vindex, int Dindex)
	{
		if(m_bIsVectors && CheckIndex(Vindex))
		{
			igtl::MUSiiCVector<Data>* tempVector = NULL;
			m_MVector.concurrent_try_get(tempVector, Vindex);
			return tempVector->concurrent_wait_get(data, Dindex);
		}
		return -1;
	}
	
	
	//////////////////
	// data : an instance data
	// Vindex : the index of MUSiiCVector in MUSiiCVectorSet
	int Concurrent_wait_get_front(Data& data, int Vindex)
	{
		if(m_bIsVectors && CheckIndex(Vindex))
		{
			igtl::MUSiiCVector<Data>* tempVector = NULL;
			m_MVector.concurrent_try_get(tempVector, Vindex);
			return tempVector->concurrent_wait_get_front(data);
		}
		return -1;
	}
	

	//////////////////
	// data : an instance data
	// Vindex : the index of MUSiiCVector in MUSiiCVectorSet
	int Concurrent_wait_get_back(Data& data, int Vindex)
	{
		if(m_bIsVectors && CheckIndex(Vindex))
		{
			igtl::MUSiiCVector<Data>* tempVector = NULL;
			m_MVector.concurrent_try_get(tempVector, Vindex);
			return tempVector->concurrent_wait_get_back(data);
		}
		return -1;
	}

	//////////////////
	// data : an instance data
	// Vindex : the index of MUSiiCVector in MUSiiCVectorSet
	// Dindex : the index of DATA in MUSiiCVector
	int Concurrent_wait_get_pop(Data& data, int Vindex, int Dindex)
	{
		if(m_bIsVectors && CheckIndex(Vindex))
		{
			igtl::MUSiiCVector<Data>* tempVector = NULL;
			m_MVector.concurrent_try_get(tempVector, Vindex);
			return tempVector->concurrent_wait_get_pop(data, Dindex);
		}
		return -1;
	}

	//////////////////
	// data : an instance data
	// Vindex : the index of MUSiiCVector in MUSiiCVectorSet
	int Concurrent_wait_get_pop_front(Data& data, int Vindex)
	{
		if(m_bIsVectors && CheckIndex(Vindex))
		{
			igtl::MUSiiCVector<Data>* tempVector = NULL;
			m_MVector.concurrent_try_get(tempVector, Vindex);
			return tempVector->concurrent_wait_get_pop_front(data);
		}
		return -1;
	}

	//////////////////
	// data : an instance data
	// Vindex : the index of MUSiiCVector in MUSiiCVectorSet
	int Concurrent_wait_get_pop_back(Data& data, int Vindex)
	{
		if(m_bIsVectors && CheckIndex(Vindex))
		{
			igtl::MUSiiCVector<Data>* tempVector = NULL;
			m_MVector.concurrent_try_get(tempVector, Vindex);
			return tempVector->concurrent_wait_get_pop_back(data);
		}
		return -1;
	}

	//////////////////////////////////////////////////////////////

	int Concurrent_wait_get_pop_front_fromMUSiiCVectorSet(Data& data)
	{
		int s(m_MVector.concurrent_size());
		int i(0);
		for(i=0; i<s; i++)
		{
			igtl::MUSiiCVector<Data>* tempVector = NULL;
			m_MVector.concurrent_try_get(tempVector, i);
			if(tempVector->concurrent_size()>0)
			{
				this->m_bWaiting = false;
				return tempVector->concurrent_try_get_pop_front(data);
			}
		}

		if(m_bDebug) 
				MUSiiC_LOG(logINFO) << "MUSiiCVectorSet:: Waiting" ; 
		this->m_bWaiting = true;

		m_Lock->Lock();
		m_Cond->Wait(m_Lock);
		m_Lock->Unlock();
		
		if(m_bDebug) 
				MUSiiC_LOG(logINFO) << "MUSiiCVectorSet:: Got Signal" ;

		for(i=0; i<s; i++)
		{
			igtl::MUSiiCVector<Data>* tempVector = NULL;
			m_MVector.concurrent_try_get(tempVector, i);
			if(tempVector->IsData())
			{
				this->m_bWaiting = false;
				
				if(m_bDebug) 
					MUSiiC_LOG(logINFO) << "MUSiiCVectorSet:: Got data from " << i <<"-th MUSiiCVector" ;

				//return tempVector->concurrent_try_get_pop_front(data);
				return tempVector->concurrent_wait_get_pop_front(data);
			}
		}
	}

	//////////////////////////////////////////////////////////////////
	int Concurrent_wait_get_pop_back_fromMUSiiCVectorSet(Data& data)
	{
		int s(m_MVector.concurrent_size());
		int i(0);
		for(i=0; i<s; i++)
		{
			igtl::MUSiiCVector<Data>* tempVector = NULL;
			m_MVector.concurrent_try_get(tempVector, i);
			if(tempVector->concurrent_size()>0)
			{
				this->m_bWaiting = false;
				return tempVector->concurrent_try_get_pop_back(data);
			}
		}

		if(m_bDebug) 
				MUSiiC_LOG(logINFO) << "MUSiiCVectorSet:: Waiting" ; 
		this->m_bWaiting = true;
		m_Lock->Lock();
		m_Cond->Wait(m_Lock);
		m_Lock->Unlock();

		if(m_bDebug) 
				MUSiiC_LOG(logINFO) << "MUSiiCVectorSet:: Got Signal" ;

		for(i=0; i<s; i++)
		{
			igtl::MUSiiCVector<Data>* tempVector = NULL;
			m_MVector.concurrent_try_get(tempVector, i);
			if(tempVector->IsData())
			{
				this->m_bWaiting = false;

				if(m_bDebug) 
					MUSiiC_LOG(logINFO) << "MUSiiCVectorSet:: Got data from " << i <<"-th MUSiiCVector" ;

				return tempVector->concurrent_try_get_pop_back(data);
			}
		}
	}


	////////////////////////////////
	//// Get number of Data in this MUSiiCVectorSet
	int GetNumOfDataALL()
	{
		int r(0)
		int s(m_MVector.concurrent_size());
		for(int i=0; i<s; i++)
		{
			igtl::MUSiiCVector<Data>* tempVector = NULL;
			m_MVector.concurrent_try_get(tempVector, Vindex);
			r += tempVector->concurrent_size();
		}
		
		return r;
	}

	//// Get number of Data in a specific MUSiiCVector
	int GetNumOfData(int Vindex)
	{
		if(m_bIsVectors && CheckIndex(Vindex))
		{
			igtl::MUSiiCVector<Data>* tempVector = NULL;
			m_MVector.concurrent_try_get(tempVector, Vindex);
			return tempVector->concurrent_size();
		}
		return -1;
	}

	
};
} //end of namespace
#endif
