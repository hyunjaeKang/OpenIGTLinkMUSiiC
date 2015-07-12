/***************************************************************************
Copyright June/2011
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.


MusiicTaskSingleInterface::	This class has only one data-queue.
				This class is subclass of MusiicTaskAbstract
***************************************************************************/

#ifndef __MUSICC_TASK_SI_
#define __MUSICC_TASK_SI_

#include "MusiicQueue.h"
#include "MusiicTaskAbstract.h"


/// MusiicTaskSingleInterface :: MusiicTask for Single Data Interface
/// class D :: the data type of input data
namespace igtl
{
template<class Data> class MUSiiCTaskSingleInterface:public MUSiiCTaskAbstract
{
public: ///Operation
	
	///Constructor
	MUSiiCTaskSingleInterface()
		:m_pDataQueue(NULL),
		m_bIsDataQueue(false)
	{
		m_pNameOfClass ="MusiicTaskSingleInterface";
		InitializeDataQueue();
	}
	
	///Deconstructor
	~MUSiiCTaskSingleInterface()
	{
	}

	///Start Task with a independent thread
	virtual int RunTask()
	{
		InitializeDataQueue();
		return MUSiiCTaskAbstract::RusTask();
	}
	
	/// Stop Task-Thread
	virtual void StopTask()
	{
		/// if the queue is blocked by condition variable,
		/// release the condition variable for stopping thread
		ReleaseDataQueue();
		
		/// Stop task thread
		MUSiiCTaskAbstract::StopTask();
		
		/// Intialize the data-queue.
		InitializeDataQueue();
	}

	/// Resume Task-Thread
	virtual int ResumeTask()
	{
		return MUSiiCTaskAbstract::RusTask();
	}
	
	/// Pause Task-Thread
	virtual void PauseTask()
	{
		ReleaseDataQueue();
		MUSiiCTaskAbstract::StopTask();
	}

	/// Task function
	virtual int Task()
	{
		return MUSiiCTaskAbstract::Task();
	}

	///Get the size of Data-queue
	//int GetCountData(){return m_pDataQueue->size();}

	/// Getting a data from m_pDataQueue
	/// if dropping is true,
	/// Throw away sz-1 data from m_InputDataQueue.
	/// And then, getting the last data only
	bool GetData(Data& data, bool dropping = false) 
	{
		/// Throw away sz-1 data from m_InputDataQueue
		if(dropping)
		{
			int sz = GetCountData();
			for(int i=0; i<sz-1;i++)
			{
				I temp;
				m_pDataQueue->wait_pop(temp);
			}
		}
		return m_pDataQueue->wait_pop(data);
	}
	
	/// Add a data at data-queue
	void PutData(Data& data) {m_pDataQueue->push(data);}

	/// Connect external dataqueue(:MusiicDataQueue<D>) to
	/// Interanl the pointer of dataqueue
	bool SetDataQueue(SmartPointer<MUSiiCQueue<Data>> dataqueue)
	//bool SetDataQueue(MUSiiCQueue<Data>::Pointer dataqueue)
	{
		/*if(dataqueue == NULL)
		{
			m_pDataQueue = NULL;
			m_bIsDataQueue = false;
		}
		else*/
		if(dataqueue.IsNull())// == NULL)
		{
			m_pDataQueue = NULL;
			m_bIsDataQueue = false;
		}
		else
		{
			m_pDataQueue = dataqueue;
			m_bIsDataQueue = true;
		}
		return m_bIsDataQueue;
	}

	/// Check  whether the pointer of dataqueue is connect to an external dataqueue or not
	bool IsDataQueue(){return m_bIsDataQueue;}

public:///Attributes

protected:///Operation
 	
	/// Initialize DataQueue
	bool InitializeDataQueue()
	{
		if(m_bIsDataQueue)
			m_pDataQueue->Empty();
		return m_bIsDataQueue;
	}

	bool ReleaseDataQueue()
	{
		if(m_bIsDataQueue)
			if(m_pDataQueue->IsWaiting())
				m_pDataQueue->EnforceRelease();

		return m_bIsDataQueue;
	}

protected:///Attributes
	///the pointer Data Container
	//igtl::MUSiiCQueue<Data>::Pointer	m_pDataQueue;
	
	SmartPointer<MUSiiCQueue<Data>>		m_pDataQueue;
	bool								m_bIsDataQueue;
};
};
#endif

//namespace igtl
//{
//template<typename Data> class MUSiiCTaskSingleInterface:public MUSiiCTaskAbstract
//{
//public:
//	//MUSiiCQueue<double>::Pointer	m_pDataQueue;
//	SmartPointer<MUSiiCQueue<Data>> m_pQ;
//};
//};
//#endif