/***************************************************************************
Copyright June/2011
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.
***************************************************************************/
#ifndef __MUSICC_TASK_
#define __MUSICC_TASK_

#include <stdio.h>
#include <igtlMultiThreader.h>
#include "MusiicQueue.h"

#include <igtlUSMessage.h>
#include <igtlEIMessage.h>
#include <igtlArgMessage.h>
#include <igtlGenMessage.h>
#include <igtlFileMessage.h>

#include <igtlTransformMessage.h>
#include <igtlImageMessage.h>
#include <igtlPointMessage.h>
#include <igtlPositionMessage.h>
#include <igtlStatusMessage.h>

using namespace igtl;


///Define MusiicTaskCallback function
typedef void(*MusiicTaskCallBack) (void*, int);

typedef struct
{
	MusiicTaskCallBack pMTaskCallBack;
}pMusiicTaskCallBackFtn;

///Define Musiic function
typedef int(*MusiicTask) (void*);

typedef struct
{
	MusiicTask pMTask;
}pMusiicTask;

/// CMusiicTask has it's own independent thread for own task
/// class I :: the data type of input data
/// class O :: the data type of output data
template<class I, class O> class CMusiicTask
{
public: /// Methods
	///Constructor
	CMusiicTask()
		:m_bTaskThread(false),
		m_pThread(NULL),
		m_iThreadIdx(-1),
		m_bIsTaskFunction(false)
	{
		InitializeQueues();
	}

	///Deconstructor
	~CMusiicTask()
	{
	}
	
	virtual int RusTask() ///*******
	{
		m_pThread = MultiThreader::New();
		m_bTaskThread = true;
		m_iThreadIdx = m_pThread->SpawnThread((ThreadFunctionType) &TaskThread, this);
		return m_iThreadIdx;
	}

	virtual void StopTask() ///*******
	{
		if(m_InputDataQueue.IsWaiting())
			m_InputDataQueue.EnforceRelease();

		if(m_OutputDataQueue.IsWaiting())
			m_OutputDataQueue.EnforceRelease();
		
		m_bTaskThread = false;
		m_pThread->TerminateThread(m_iThreadIdx);
	}

	void SetTaskCallBackFunction(MusiicTaskCallBack cbFunc) ////////////
	{
		m_CallBackFunction = cbFunc;
		m_bIsTaskCallBackFunction = true;
	}
	
	bool IsTaskCallBackFunction(){return m_bIsTaskCallBackFunction;} //////////

	
	void SetTaskFunction(MusiicTask Func) //////////
	{
		m_TaskFunction = Func;
		m_bIsTaskFunction = true;
	}

	bool IsTaskFunction(){return m_bIsTaskFunction;} //////////
	
	int GetCountInputData(){return m_InputDataQueue.size();} /////*******
	int GetCountOutputData(){return m_OutputDataQueue.size();} /////*******

	void PutInputData(I& data) {m_InputDataQueue.push(data);}  /////*******
	
	/// Getting a data from m_OutputDataQueue
	/// if dropping is true,
	/// Throw away sz-1 data from m_OutputDataQueue.
	/// And then, getting the last data only
	bool GetOutputData(O& data, bool dropping = false)  /////*******
	{
		/// Throw away sz-1 data from m_OutputDataQueue
		if(dropping)
		{
			int sz = GetCountOutputData();
			for(int i=0; i<sz-1;i++)
			{
				O temp;
				//m_OutputDataQueue.try_pop(temp);
				m_OutputDataQueue.wait_pop(temp);
			}
		}

		//return m_OutputDataQueue.try_pop(data);
		return m_OutputDataQueue.wait_pop(data);
		
	}

	/// Getting a data from m_InputDataQueue
	/// if dropping is true,
	/// Throw away sz-1 data from m_InputDataQueue.
	/// And then, getting the last data only
	bool GetInputData(I& data, bool dropping = false) /////*******
	{
		/// Throw away sz-1 data from m_InputDataQueue
		if(dropping)
		{
			int sz = GetCountInputData();
			for(int i=0; i<sz-1;i++)
			{
				I temp;
				//m_InputDataQueue.try_pop(temp);
				m_InputDataQueue.wait_pop(temp);
			}
		}
		//return m_InputDataQueue.try_pop(data);
		return m_InputDataQueue.wait_pop(data);
	}

	void PutOutputData(O& data) {m_OutputDataQueue.push(data);} /////*******

	virtual int Task() /////*******
	{
		//if(!m_bIsTaskFunction)
		{
			m_CallBackFunction(this, 1);
			return 1;
		}
		/*else
			return 0;*/
	}

	int GetThreadIdx(){return m_iThreadIdx;} ////////////

public: /// Attributes

protected: /// Methods
	

	static void* TaskThread(void* ptr) ///////////////
	{
		MultiThreader::ThreadInfo* info = static_cast<MultiThreader::ThreadInfo*>(ptr);
		CMusiicTask* pTaskClass = static_cast<CMusiicTask*>(info->UserData);
		
		while(pTaskClass->m_bTaskThread == true)
			if(pTaskClass->m_bIsTaskFunction)
				pTaskClass->m_TaskFunction(pTaskClass);
			else
				pTaskClass->Task();
			
		printf("End TaskTread\n");
		return NULL;
	}
	
	void InitializeQueues() /////*******
	{
		m_InputDataQueue.Empty();
		m_OutputDataQueue.Empty();
	}

	
	
protected: /// Attributes
	/// Thread Data
	bool					m_bTaskThread;
	MultiThreader::Pointer	m_pThread;
	int						m_iThreadIdx;
	
	///Data Container
	MusiicQueue<I>			m_InputDataQueue;
	MusiicQueue<O>			m_OutputDataQueue;

	///CallBack Function
	MusiicTaskCallBack		m_CallBackFunction;
	bool					m_bIsTaskCallBackFunction;

	///Task Function
	MusiicTask				m_TaskFunction;
	bool					m_bIsTaskFunction;
	void*					m_Caller;
};

#endif