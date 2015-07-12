/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/

#ifndef __MUSIIC_TASK_IF_ABSTRACT_
#define __MUSIIC_TASK_IF_ABSTRACT_

#include "MUSiiCTaskAbstract.h"
#include "MUSiiCVector.h"

namespace igtl
{

enum MUSiiCTaskState
{
	M_TASK_STOPPED 	= 9700,
	M_TAKS_RUNNING,
	M_TAKS_PAUSED,
};

class IGTLMCommon_EXPORT MUSiiCTaskInterfaceAbstract: public MUSiiCTaskAbstract
{
public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCTaskInterfaceAbstract	Self;
	typedef MUSiiCTaskAbstract			Superclass;
	typedef SmartPointer<Self>			Pointer;
	typedef SmartPointer<const Self>	ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(MUSiiCTaskInterfaceAbstract, MUSiiCTaskAbstract);
	
	/// Constructor
	MUSiiCTaskInterfaceAbstract();

	/// Deconstructor
	~MUSiiCTaskInterfaceAbstract();

	///Start Task with a independent thread
	virtual int RunTask(int numOfRun = M_THREAD_RUN_CONTINUOUS,int taskInfo = 0, void* ptr = NULL, void* data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	/// Stop Task-Thread
	virtual void StopTask();
	
	/// Resume Task-Thread
	virtual int ResumeTask();

	/// Pause Task-Thread
	virtual void PauseTask();
	
	MUSiiCTaskState GetTaskState();

public:///Attributes
	
protected:///Operation
	/// Initialize Member variables
	virtual void Initialize();
 	/// Task function
	virtual int Task(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, void* data1 = NULL, void* data2 = NULL, void* data3 = NULL);
	
	/// The core function of task-Thread
	virtual void* TaskThreading();
	
	/// Initialize DataQueue
	virtual bool InitializeDataIF();
	
	/// Release DataQueue
	virtual bool ReleaseDataIF();

protected:///Attributes
	MUSiiCTaskState m_TaskState;

};
};
#endif
