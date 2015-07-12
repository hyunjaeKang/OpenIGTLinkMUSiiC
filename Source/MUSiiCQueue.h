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
#ifndef __MUSICC_QUEUE_
#define __MUSICC_QUEUE_

#include <queue>
#include <deque>

#include <igtlConditionVariable.h>
#include <igtlOSUtil.h>
#include <igtlFastMutexLock.h>

//#pragma comment (lib, "OpenIGTLink.lib")

template<typename Data>

class CMusiicQueue
{

private:
	/// Data Container (std::queue)
	std::queue<Data>					MQueue;
	/// Condition Variable for multithreaded programming 
	igtl::ConditionVariable::Pointer	m_Cond;
	/// Mutex for condition variable
	igtl::SimpleMutexLock				*m_Lock;
	/// Mutex for multithreaded programming
	igtl::FastMutexLock::Pointer		m_Mutex;
	/// A boolean variable for checking current the status of Queue
	bool								m_bWaiting;
	/// A boolean variable to enforce termination.
	bool								m_bTerminate;

	bool								m_bSelfMutex;

public:
	/// Constructor
	CMusiicQueue()
	{
		m_Cond			= igtl::ConditionVariable::New();
		m_Lock			= igtl::SimpleMutexLock::New();
		m_Mutex			= igtl::FastMutexLock::New();
		m_bWaiting		= false;
		m_bTerminate	= false;
		m_bSelfMutex	= true;
	}

	/// Constructor
	CMusiicQueue(igtl::ConditionVariable::Pointer Cond, igtl::SimpleMutexLock* Lock)
	{
		m_Cond = Cond;
		m_Lock = Lock;
		m_bWaiting		= false;
		m_bTerminate	= false;
		m_bSelfMutex	= false;
	}

	/// Deconstructor
	~CMusiicQueue()
	{
		if(m_bSelfMutex)
			delete m_Lock;
	}

	/// Insert an element to the queue
	int push(Data const& data)
	{
		m_Mutex->Lock();
		MQueue.push(data);
		m_Mutex->Unlock();

		//if(m_bWaiting)
		{
			m_Cond->Signal();
			m_bWaiting	= false;
		}
		
		return size();
	}
	/// Check whether container is empty or not
	bool IsEmpty() const
	{
		m_Mutex->Lock();
		bool b = MQueue.empty();
		m_Mutex->Unlock();

		return b;
	}

	/// Access element and delete the element
	/// without Mutex and Event 
	bool try_pop(Data& value, bool dropping = false)
	{
		m_Mutex->Lock();
		if(MQueue.empty())
			return false;
		
		/// Dropping 
		if(dropping)
		{
			int s = size();
			for(int i=0; i<s-1; i++)
			{
				value	= MQueue.front();
				MQueue.pop();
			}
		}

		value	= MQueue.front();
		MQueue.pop();
		
		m_Mutex->Unlock();
		return true;
	}

	/// Access element and delete the element
	/// with Mutex and Event 
	bool wait_get_pop(Data& value, bool dropping = false)
	{
		while(1)
		{
			m_Mutex->Lock();
			if(!MQueue.empty())
			{
				break;
			}
			//else if(MQueue.empty() && m_bTerminate)
			else if(m_bTerminate)
			{
				m_bTerminate = false;
				m_bWaiting = false;
				m_Mutex->Unlock();
				return false;
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
			int s = size();
			for(int i=0; i<s-1; i++)
			{
				value	= MQueue.front();
				MQueue.pop();
			}
		}

		value	= MQueue.front();
		MQueue.pop();

		m_Mutex->Unlock();
	}

	/// Get the size of the queue
	int size()
	{
		m_Mutex->Lock();
		int s = MQueue.size();
		m_Mutex->Unlock();

		return s;
	}
	/// Delete all contents of the Queue
	void Clear()
	{
		m_Mutex->Lock();
		while(!MQueue.empty())
		{
			MQueue.pop();
		}
		m_Mutex->Unlock();
	}

	/// Check a status of this queue
	bool IsWaiting() {return m_bWaiting;}

	void EnforceRelease()
	{
		//if(m_bWaiting)
		{
			m_bTerminate = true;
			m_Cond->Signal();
		}
	}
};
#endif