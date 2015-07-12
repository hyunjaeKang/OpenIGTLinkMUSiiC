/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/

#include "MUSiiCTaskInterfaceAbstract.h"
namespace igtl
{
	
	/// Constructor
	MUSiiCTaskInterfaceAbstract::MUSiiCTaskInterfaceAbstract()
	{
		m_pNameOfClass="MUSiiCTaskInterfaceAbstract";
		Initialize();
	}

	/// Deconstructor
	MUSiiCTaskInterfaceAbstract::~MUSiiCTaskInterfaceAbstract()
	{
	}

	///Start Task with a independent thread
	int MUSiiCTaskInterfaceAbstract::RunTask(int numOfRun,int taskInfo, void* ptr, void* data1, void* data2, void* data3)
	{
		/// Initialize Data Queue
		InitializeDataIF();
		
		/// Setting the state of Task
		m_TaskState = M_TAKS_RUNNING;/////??????/
		
		/// Run task-thread
		return MUSiiCTaskAbstract::RunTask(numOfRun, taskInfo, ptr, data1, data2, data3);
	}

	/// Stop Task-Thread
	void MUSiiCTaskInterfaceAbstract::StopTask()
	{
		/// if the queue is blocked by condition variable,
		/// release the condition variable for stopping thread
		//ReleaseDataIF();
		
		/// Stop task thread
		MUSiiCTaskAbstract::StopTask();
		
		/// if the queue is blocked by condition variable,
		/// release the condition variable for stopping thread
		ReleaseDataIF();

		/// Intialize the data-queue.
		InitializeDataIF();
		
		/// Setting the state of Task
		m_TaskState = M_TASK_STOPPED;
	}
	
	/// Resume Task-Thread
	int MUSiiCTaskInterfaceAbstract::ResumeTask()
	{
		/// Setting the state of Task
		m_TaskState = M_TAKS_RUNNING;
		
		/// Run task-thread
		return MUSiiCTaskAbstract::RunTask();
	}

	/// Pause Task-Thread
	void MUSiiCTaskInterfaceAbstract::PauseTask()
	{
		/// if the queue is blocked by condition variable,
		/// release the condition variable for stopping thread
		ReleaseDataIF();
		/// Stop task thread
		MUSiiCTaskAbstract::StopTask();
		
		/// Setting the state of Task
		m_TaskState = M_TAKS_PAUSED;
	}
	
	MUSiiCTaskState MUSiiCTaskInterfaceAbstract::GetTaskState()
	{
		return m_TaskState;
	}

//protected:///Operation
	/// Initialize Member variables
	void MUSiiCTaskInterfaceAbstract::Initialize()
	{
		MUSiiCTaskAbstract::Initialize();
		m_TaskState = M_TASK_STOPPED;
	}
 	/// Task function
	int MUSiiCTaskInterfaceAbstract::Task(int numOfRun, int taskInfo, void* ptr, void* data1, void* data2, void* data3)
	{		
		int r(-1);
		/*m_TaskState = M_TAKS_RUNNING;
		
		r = MUSiiCTaskAbstract::Task(numOfRun, taskInfo,ptr,data1, data2, data3);
		
		if(!m_bTaskThread)
			m_TaskState = M_TASK_STOPPED;*/

		return r;
	}
	
	/// The core function of task-Thread
	void* MUSiiCTaskInterfaceAbstract::TaskThreading()
	{
		void* r;
		/*m_TaskState=M_TAKS_RUNNING;
		r= MUSiiCTaskAbstract::TaskThreading();
		m_TaskState=M_TASK_STOPPED;*/
		return r;
	}
	
	/// Initialize DataQueue
	bool MUSiiCTaskInterfaceAbstract::InitializeDataIF()
	{
		return true;
	}
	
	// Release DataQueue
	bool MUSiiCTaskInterfaceAbstract::ReleaseDataIF()
	{
		return true;
	}

};