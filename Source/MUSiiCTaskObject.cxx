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
#include "MUSiiCTaskObject.h"


//using namespace igtl;
namespace igtl
{
//
///Constructor
MUSiiCTaskObject::MUSiiCTaskObject()
{
	/*_CrtDumpMemoryLeaks();
	_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );*/
	m_pNameOfClass = "MUSiiCTaskObject";
	Initialize();
}
	
///Deconstructor
MUSiiCTaskObject::~MUSiiCTaskObject()
{
	if(m_pFastMutex.IsNotNull())
		m_pFastMutex->Unlock();
	
	if(m_bIsMutex)
		m_pMutex->Unlock();
	
	if(m_bDebug)
		MUSiiC_LOG(logINFO) << " Class Name is : " <<  m_pNameOfClass.c_str() <<"Stop";
	this->StopTask();
	if(m_bDebug)
		MUSiiC_LOG(logINFO) << " Class Name is : " <<  m_pNameOfClass.c_str() <<"Stopped";

	if(m_bIsMutex)
		delete m_pMutex;
}
	
/// Get the name of Class
std::string MUSiiCTaskObject::GetNameOfMUSiiCClass()
{
	return m_pNameOfClass;
}
	
/// Setting whether using a thread fo task function or not.
void MUSiiCTaskObject::SetEnableThread(bool bThread)
{
	m_bEnableThread = bThread;
}
	
/******************************************************************************/
/************************** External Task Function ****************************/
/// Add External Global Task function
int MUSiiCTaskObject::AddExternalGlobalTaskFunction(MusiicTaskFtn Func, std::string name)
{
	int r(-1);
	r = m_pExternalTaskFunctions->AddExternalGlobalFunction(Func, name);
	m_bEnableExternalTaskFuntions = (r>-1)? true: false;
	return r;
}

/// get the number of External Task Functions
int MUSiiCTaskObject::GetNumOfExternalTaskFunctions()
{
	return m_pExternalTaskFunctions->GetNumOfExternalInterfaces();
}

/// Call External_class Callback functions using MUSiiCCallbackInterface
int MUSiiCTaskObject::CallExternalTaskFunctions(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	return m_pExternalTaskFunctions->CallAllExternalInterfaces(numOfRun, taskInfo, ptr, data1, data2, data3);
}

/// Set an External task function as Main Task function.
void MUSiiCTaskObject::SetEnableExternalTaskFunctions(bool enable)
{
	m_bEnableExternalTaskFuntions = enable;
}

/// Get an External task function as Main Task function.
bool MUSiiCTaskObject::GetEnableExternalTaskFunctions()
{
	return m_bEnableExternalTaskFuntions;
}
	
/******************************************************************************/
/************************** Callback Function *********************************/

/*---------------------------------------------------------------------------*/
/************************** Input Callback Function **************************/
/// Add External Global callback function
int MUSiiCTaskObject::AddExternalGlobalInputCallbackFunction(MusiicTaskFtn Func, std::string name)
{
	int r(-1);
	r = m_pExternalInputCallbackFunctions->AddExternalGlobalFunction(Func, name);
	m_bEnableExternalInputCallbackFuntions = (r>-1)? true: false;
	return r;
}

/// Set a callbackinterface of another MUSiiCTask class
int MUSiiCTaskObject::AddInputCallbackInterface(igtl::MUSiiCCallbackInterface::Pointer cbInterface)
{
	if(cbInterface.IsNull())
		return 0;

	int r(-1);
	r = m_pExternalInputCallbackFunctions->AddExternalInterface(cbInterface);
	m_bEnableExternalInputCallbackFuntions = (r>-1)? true: false;
	return r;
}

/// ************** New
/// Remove a callbackinterface of another MUSiiCTask class
/// Return value is the index of new CallbackInterface
/// if the return value is less than zero, this means the error of this function.
int MUSiiCTaskObject::RemoveInputCallbackInterface(igtl::MUSiiCCallbackInterface::Pointer cbInterface)
{
	if(cbInterface.IsNull())
		return 0;

	int r(-1);
	r = m_pExternalInputCallbackFunctions->RemoveExternalInterface(cbInterface);
	if(r == -1)
		MUSiiC_LOG(logINFO) << "Wrong CallbackInterface";
		
	r = m_pExternalInputCallbackFunctions->GetNumOfExternalInterfaces();
	
	m_bEnableExternalInputCallbackFuntions = (r>0)? true: false;
	return r;
}



/// get the number of External Callback Functions
int MUSiiCTaskObject::GetNumOfExternalInputCallbackFunctions()
{
	return m_pExternalInputCallbackFunctions->GetNumOfExternalInterfaces();
}

/// Call External_class Callback functions using MUSiiCCallbackInterface
int MUSiiCTaskObject::CallExternalInputCallbackFunctions(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	return m_pExternalInputCallbackFunctions->CallAllExternalInterfaces(numOfRun, taskInfo, ptr, data1, data2, data3);
}

void MUSiiCTaskObject::SetEnableExternalInputCallbackFunctions(bool enable)
{
	m_bEnableExternalInputCallbackFuntions = enable;
}

bool MUSiiCTaskObject::GetEnableExternalInputCallbackFunctions()
{
	return m_bEnableExternalInputCallbackFuntions;
}

/// Get the pointer of Input CallbackInterfaceControl
igtl::MUSiiCCallbackInterfaceControl::Pointer MUSiiCTaskObject::GetInputCallbackInterfaceControl()
{
	return m_pExternalInputCallbackFunctions;
}

/// Set this CallbackInterfaceControl with given CallbackInterfaceControl
bool MUSiiCTaskObject::SetInputCallbackInterfaceControl(igtl::MUSiiCCallbackInterfaceControl::Pointer callbackIFControl)
{
	if(callbackIFControl.IsNotNull())
	{
		m_pExternalInputCallbackFunctions = callbackIFControl;
		return true;
	}
	return false;
}

/************************** Input Callback Function **************************/
/*---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------*/
/************************** Output Callback Function **************************/

/// Add External Global callback function
int MUSiiCTaskObject::AddExternalGlobalOutputCallbackFunction(MusiicTaskFtn Func, std::string name)
{
	int r(-1);
	r = m_pExternalOutputCallbackFunctions->AddExternalGlobalFunction(Func, name);
	m_bEnableExternalOutputCallbackFuntions = (r>-1)? true: false;
	return r;
}
		
/// Set a callbackinterface of another MUSiiCTask class
int MUSiiCTaskObject::AddOutputCallbackInterface(igtl::MUSiiCCallbackInterface::Pointer cbInterface)
{
	if(cbInterface.IsNull())
		return 0;

	int r(-1);
	r = m_pExternalOutputCallbackFunctions->AddExternalInterface(cbInterface);
	m_bEnableExternalOutputCallbackFuntions = (r>-1)? true: false;
	return r;
}

/// ************** New
/// Remove a callbackinterface of another MUSiiCTask class
/// Return value is the index of new CallbackInterface
/// if the return value is less than zero, this means the error of this function.
int MUSiiCTaskObject::RemoveOutputCallbackInterface(igtl::MUSiiCCallbackInterface::Pointer cbInterface)
{
	if(cbInterface.IsNull())
		return 0;

	int r(-1);
	r = m_pExternalOutputCallbackFunctions->RemoveExternalInterface(cbInterface);
	if(r == -1)
		MUSiiC_LOG(logINFO) << "Wrong CallbackInterface";
		
	r = m_pExternalOutputCallbackFunctions->GetNumOfExternalInterfaces();
	
	m_bEnableExternalOutputCallbackFuntions = (r>0)? true: false;
	return r;
}
	


/// get the number of External Callback Functions
int MUSiiCTaskObject::GetNumOfExternalOutputCallbackFunctions()
{
	return m_pExternalOutputCallbackFunctions->GetNumOfExternalInterfaces();
}

/// Call External_class Callback functions using MUSiiCCallbackInterface
int MUSiiCTaskObject::CallExternalOutputCallbackFunctions(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	return m_pExternalOutputCallbackFunctions->CallAllExternalInterfaces(numOfRun, taskInfo, ptr, data1, data2, data3);
}

void MUSiiCTaskObject::SetEnableExternalOutputCallbackFunctions(bool enable)
{
	m_bEnableExternalOutputCallbackFuntions = enable;
}

bool MUSiiCTaskObject::GetEnableExternalOutputCallbackFunctions()
{
	return m_bEnableExternalOutputCallbackFuntions;
}

/// Get the pointer of Input CallbackInterfaceControl
igtl::MUSiiCCallbackInterfaceControl::Pointer MUSiiCTaskObject::GetOutputCallbackInterfaceControl()
{
	return m_pExternalOutputCallbackFunctions;
}

/// Set this CallbackInterfaceControl with given CallbackInterfaceControl
bool MUSiiCTaskObject::SetOutputCallbackInterfaceControl(igtl::MUSiiCCallbackInterfaceControl::Pointer callbackIFControl)
{
	if(callbackIFControl.IsNotNull())
	{
		m_pExternalOutputCallbackFunctions = callbackIFControl;
		return true;
	}
	return false;
}

/*---------------------------------------------------------------------------*/
/************************** Self Callback Interface **************************/
//// Get the pointer of Pre_SelfCallbackInterface of MUSiiCTaskObject
igtl::MUSiiCCallbackInterface::Pointer MUSiiCTaskObject::GetPreSlefCallBackInterface()
{
	return m_pPreSlefCallBackInterface.IsNotNull()? m_pPreSlefCallBackInterface:NULL;
}

//// Get the pointer of Post_SelfCallbackInterface of MUSiiCTaskObject
igtl::MUSiiCCallbackInterface::Pointer MUSiiCTaskObject::GetPostSlefCallBackInterface()
{
	return m_pPostSlefCallBackInterface.IsNotNull()? m_pPostSlefCallBackInterface:NULL;
}

/******************************************************************************/
/// Declare a function that is called MUSiiCCallbackInterface
int MUSiiCTaskObject::PreCallback(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	if(m_bDebug && ptr != NULL)
	{
		MUSiiCTaskObject* pTask = (MUSiiCTaskObject*) ptr;
		MUSiiC_LOG(logINFO) << " Pre-Callback Function : " << this->m_sNameOfSelfPreCallbackInterface.c_str();
		MUSiiC_LOG(logINFO) << " Class Name is : " << pTask->GetNameOfMUSiiCClass().c_str();
		MUSiiC_LOG(logINFO) << " This Fucntion is virtual function  : " << pTask->GetNameOfMUSiiCClass().c_str();
	}

	return 1;
}


/// Declare a function that is called MUSiiCCallbackInterface
int MUSiiCTaskObject::PostCallback(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	if(m_bDebug && ptr != NULL)
	{
		MUSiiCTaskObject* pTask = (MUSiiCTaskObject*) ptr;
		MUSiiC_LOG(logINFO) << " Post-Callback Function : " << this->m_sNameOfSelfPostCallbackInterface.c_str();
		MUSiiC_LOG(logINFO) << " Class Name is : " << pTask->GetNameOfMUSiiCClass().c_str();
		MUSiiC_LOG(logINFO) << " This Fucntion is virtual function  : " << pTask->GetNameOfMUSiiCClass().c_str();
	}

	return 1;
}

/************************** Self Callback Interface **************************/
/*---------------------------------------------------------------------------*/
/************************** Callback Function *********************************/
/******************************************************************************/


/******************************************************************************/
/************************** Task Function *************************************/
/// Run the task funtion with/without thread
int MUSiiCTaskObject::RunTask(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	SetTaskInfo(numOfRun, taskInfo, ptr, data1, data2, data3);
	if(m_bEnableThread)
	{
		m_pThread        = MultiThreader::New();
		m_bRunContinuous = (m_iNumOfRun == M_THREAD_RUN_CONTINUOUS)? true : false;
		m_bTaskThread    = true;
		m_iThreadIdx     = m_pThread->SpawnThread((ThreadFunctionType) &TaskThread, this);
		return m_iThreadIdx;
	}
	else
	{
		int i;
		for(i=0; i< m_iNumOfRun; i++)
			if(Task(i, taskInfo, ptr, data1, data2, data3) < 0)
				return -1;

		return i;
	}
}

/// Set Task-Information
void MUSiiCTaskObject::SetTaskInfo(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	m_iNumOfRun  = numOfRun;
	m_iTaskInfo  = taskInfo;
	m_pPtr       = ptr;
	m_pData1     = data1;
	m_pData2     = data2;
	m_pData3     = data3;
}
/// Stop the task thread
void MUSiiCTaskObject::StopTask()
{	
	if(m_bDebug)
			MUSiiC_LOG(logINFO) << " Class Name is : " << this->GetNameOfMUSiiCClass().c_str() << " will stop its Task function";
	
	m_bTaskThread	= false;
	this->WaitTask();

	if(m_bDebug)
			MUSiiC_LOG(logINFO) << " Class Name is : " << this->GetNameOfMUSiiCClass().c_str() << " is stopped";
}

/// Wiat for the task thread
void MUSiiCTaskObject::WaitTask()
{
	if(m_bEnableThread)
	{
		if(m_bDebug)
			MUSiiC_LOG(logINFO) << " Class Name is : " << this->GetNameOfMUSiiCClass().c_str() << " Wait Task Function will be Finished";
		
		if(m_pThread.IsNotNull())
			m_pThread->TerminateThread(m_iThreadIdx);

		if(m_bDebug)
			MUSiiC_LOG(logINFO) << " Class Name is : " << this->GetNameOfMUSiiCClass().c_str() << " Task Function is stopped";
	}
}

/// Getting the index of current thread
int MUSiiCTaskObject::GetThreadIdx() 
{
	return m_iThreadIdx;
}

/// ????? Do we need this function?
bool MUSiiCTaskObject::SetTaskMutexPointer(SimpleMutexLock* mutex)
{
	if(mutex == NULL)
		m_bIsMutex = false;
	else
	{
		m_pMutex = mutex;
		m_bIsMutex = true;
	}

	return m_bIsMutex;
}


///////////////////////////////////////////////////////////////////////////////////////////
///protected: /// Methods
/// Initialize Member variables
void MUSiiCTaskObject::Initialize()
{
	/// Thread Data
	m_bTaskThread						     = false;
	m_pThread							     = NULL;
	m_iThreadIdx						     = -1;
	m_bEnableThread						     = true;
	
	m_bRunContinuous					     = true;
	m_iNumOfRun							     = 1;
	m_iTaskInfo							     = 0;
	m_pPtr								     = this;
	m_pData1							     = NULL;
	m_pData2							     = NULL;
	m_pData3							     = NULL;
	m_pFastMutex                             = igtl::FastMutexLock::New();

	///Task Function
	/// Glbal Task Function
	m_pExternalTaskFunctions                 = MUSiiCCallbackInterfaceControl::New();
	m_bEnableExternalTaskFuntions	 	     = false;
	
	/// CallbackFunction
	m_pExternalInputCallbackFunctions        = MUSiiCCallbackInterfaceControl::New();
	m_bEnableExternalInputCallbackFuntions	 = false;

	m_pExternalOutputCallbackFunctions       = MUSiiCCallbackInterfaceControl::New();
	m_bEnableExternalOutputCallbackFuntions	 = false;
	
	/// Self Pre-callback interface
	std::string str = "_Pre_Callback";
	m_sNameOfSelfPreCallbackInterface        = GetNameOfMUSiiCClass() + str;
	m_pPreSlefCallBackInterface              = 
		igtl::CreateLocalCallbackInterface(this,&MUSiiCTaskObject::PreNotified, m_sNameOfSelfPreCallbackInterface);

	/// Self Post-callback interface
	str = "_Post_Callback";
	m_sNameOfSelfPostCallbackInterface       = GetNameOfMUSiiCClass() + str;
	m_pPostSlefCallBackInterface             = 
		igtl::CreateLocalCallbackInterface(this,&MUSiiCTaskObject::PostNotified, m_sNameOfSelfPostCallbackInterface);
	
	//External Mutex Pointer ::A pointer of Mutex ?????
	m_pMutex							     = NULL;  //Do we need this value?
	m_bIsMutex							     = false; //Do we need this value?
	
	// Debug Information
	m_bDebug                                 = false;
}

/// Thread function
void* MUSiiCTaskObject::TaskThread(void* ptr)
{
	MultiThreader::ThreadInfo* info			= static_cast<MultiThreader::ThreadInfo*>(ptr);
	MUSiiCTaskObject* pTaskClass			= static_cast<MUSiiCTaskObject*>(info->UserData);
		
	return pTaskClass->TaskThreading();
}

/// The core function of task-Thread
void* MUSiiCTaskObject::TaskThreading()
{
	/// When Taskfunction is called in Task-Thread
	/// The Task-function should use MUSiiCVector<data> interface for thread-safety
	int iNumOfRun(0);
	
	while(m_bTaskThread == true && iNumOfRun < m_iNumOfRun)
	{
		if(Task(iNumOfRun, m_iTaskInfo, m_pPtr, m_pData1, m_pData2, m_pData3)<0)
		{
			m_bTaskThread = false;
			MUSiiC_LOG(logERROR)<< "Task-Function returned -1";
			/// Debug Information	
			if(m_bDebug)
				MUSiiC_LOG(logINFO) << " Class Name is : " << this->GetNameOfMUSiiCClass().c_str()<< " Task Function is stopped";
		}
		else
			if(!m_bRunContinuous)
				iNumOfRun++;
	}

	m_bTaskThread = false;
	/// Debug Information
	if(m_bDebug)
			MUSiiC_LOG(logINFO) << " Class Name is : " << this->GetNameOfMUSiiCClass().c_str() << " Task Function is stopped";
			
	return NULL;
}
	
/// This function is main-part of MusiicTask 
int MUSiiCTaskObject::Task(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	int r(-1);
	if(m_bEnableExternalTaskFuntions)
	{
		r = CallExternalTaskFunctions(numOfRun, taskInfo,ptr, data1, data2, data3);
		if(m_bDebug)
			MUSiiC_LOG(logINFO) << " External Task function is called";

	}
	else
	{
		/// To implement your own task function
		//////////////////////////////////////
		r = TaskFunction(numOfRun, taskInfo,ptr,data1, data2, data3);
		if(m_bDebug)
			MUSiiC_LOG(logINFO) << " Inner Task function is called";
	}

	return r;
}

/// The user-defined task function.
/// You can make your own taskfunction by making subclass of MUSiiCAbstract
int MUSiiCTaskObject::TaskFunction(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	int r(1);
	return r;
}

/// Declare a function that is called Pre-MUSiiCCallbackInterface
int MUSiiCTaskObject::PreNotified(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	int r(-1);
	m_pFastMutex->Lock();
	r = PreCallback(numOfRun, taskInfo, ptr, data1, data2, data3);
	m_pFastMutex->Unlock();
	return r;
}

/// Declare a function that is called Post-MUSiiCCallbackInterface
int MUSiiCTaskObject::PostNotified(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	int r(-1);
	m_pFastMutex->Lock();
	r = PostCallback(numOfRun, taskInfo, ptr, data1, data2, data3);
	m_pFastMutex->Unlock();
	return r;
}

};

