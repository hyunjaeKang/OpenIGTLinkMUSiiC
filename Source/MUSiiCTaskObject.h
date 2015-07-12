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
#ifndef __MUSIIC_TASK_OBJECT_
#define __MUSIIC_TASK_OBJECT_
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
#include "MUSiiCIGTLUtil.h"


//using namespace igtl;
namespace igtl
{
class IGTLMCommon_EXPORT MUSiiCTaskObject : public Object 
{
public: /// Methods
	/** Standard class typedefs. */
	typedef MUSiiCTaskObject            Self;
	typedef Object                      Superclass;
	typedef SmartPointer<Self>          Pointer;
	typedef SmartPointer<const Self>    ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(MUSiiCThreadObject, Object);

	///Constructor
	MUSiiCTaskObject();
	
	///Deconstructor
	~MUSiiCTaskObject();
	
	/// Get the name of Class
	std::string GetNameOfMUSiiCClass();
	
	/// Setting whether using a thread fo task function or not.
	void SetEnableThread(bool bThread=true);
	
	/******************************************************************************/
	/************************** External Task Function ****************************/
	/// Add External Global Task function
	int AddExternalGlobalTaskFunction(MusiicTaskFtn Func, std::string name = "");

	/// Add External Local Task function
	template<class ObjType, typename funType> 
	inline int AddExternalLocalTaskFunction(ObjType obj, funType fun, std::string name = "")
	{
		int r(-1);
		r = m_pExternalTaskFunctions->AddExternalLocalFunction(obj, fun, name);;
		m_bEnableExternalTaskFuntions = (r>-1)? true: false;
		return r;
	}

	/// get the number of External Task Functions
	int GetNumOfExternalTaskFunctions();

	/// Call External_class Callback functions using MUSiiCCallbackInterface
	virtual int CallExternalTaskFunctions(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	void SetEnableExternalTaskFunctions(bool enable);
	bool GetEnableExternalTaskFunctions();
	
	/******************************************************************************/
	/************************** Callback Function *********************************/
	
	/*---------------------------------------------------------------------------*/
	/************************** Input Callback Function **************************/

	/// Add External Global callback function
	int AddExternalGlobalInputCallbackFunction(MusiicTaskFtn Func, std::string name = "");

	/// Add External Local callback function
	template<class ObjType, typename funType> 
	inline int AddExternalLocalInputCallbackFunction(ObjType obj, funType fun, std::string name = "")
	{
		int r(-1);
		r = m_pExternalInputCallbackFunctions->AddExternalLocalFunction(obj, fun, name);
		m_bEnableExternalInputCallbackFuntions = (r>-1)? true: false;
		return r;
	}

	/// Set a callbackinterface of another MUSiiCTask class
	int AddInputCallbackInterface(igtl::MUSiiCCallbackInterface::Pointer cbInterface);

	/// ************** New
	/// Remove a callbackinterface of another MUSiiCTask class
	/// Return value is the index of new CallbackInterface
	/// if the return value is less than zero, this means the error of this function.
	int RemoveInputCallbackInterface(igtl::MUSiiCCallbackInterface::Pointer cbInterface);
	
	/// get the number of External Callback Functions
	int GetNumOfExternalInputCallbackFunctions();

	/// Call External_class Callback functions using MUSiiCCallbackInterface
	virtual int CallExternalInputCallbackFunctions(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	void SetEnableExternalInputCallbackFunctions(bool enable);
	bool GetEnableExternalInputCallbackFunctions();

	/// Get the pointer of Input CallbackInterfaceControl
	igtl::MUSiiCCallbackInterfaceControl::Pointer GetInputCallbackInterfaceControl();

	/// Set this CallbackInterfaceControl with given CallbackInterfaceControl
	bool SetInputCallbackInterfaceControl(igtl::MUSiiCCallbackInterfaceControl::Pointer callbackIFControl);

	/************************** Input Callback Function **************************/
	/*---------------------------------------------------------------------------*/
	
	/*---------------------------------------------------------------------------*/
	/************************** Output Callback Function **************************/

	/// Add External Global callback function
	int AddExternalGlobalOutputCallbackFunction(MusiicTaskFtn Func, std::string name = "");

	/// Add External Local callback function
	template<class ObjType, typename funType> 
	inline int AddExternalLocalOutputCallbackFunction(ObjType obj, funType fun, std::string name = "")
	{
		int r(-1);
		r = m_pExternalOutputCallbackFunctions->AddExternalLocalFunction(obj, fun, name);
		m_bEnableExternalOutputCallbackFuntions = (r>-1)? true: false;
		return r;
	}

	/// Set a callbackinterface of another MUSiiCTask class
	int AddOutputCallbackInterface(igtl::MUSiiCCallbackInterface::Pointer cbInterface);

	/// ************** New
	/// Remove a callbackinterface of another MUSiiCTask class
	/// Return value is the index of new CallbackInterface
	/// if the return value is less than zero, this means the error of this function.
	int RemoveOutputCallbackInterface(igtl::MUSiiCCallbackInterface::Pointer cbInterface);
	
	/// get the number of External Callback Functions
	int GetNumOfExternalOutputCallbackFunctions();

	/// Call External_class Callback functions using MUSiiCCallbackInterface
	virtual int CallExternalOutputCallbackFunctions(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	void SetEnableExternalOutputCallbackFunctions(bool enable);
	bool GetEnableExternalOutputCallbackFunctions();


	/// Get the pointer of Input CallbackInterfaceControl
	igtl::MUSiiCCallbackInterfaceControl::Pointer GetOutputCallbackInterfaceControl();

	/// Set this CallbackInterfaceControl with given CallbackInterfaceControl
	bool SetOutputCallbackInterfaceControl(igtl::MUSiiCCallbackInterfaceControl::Pointer callbackIFControl);


	/************************** Output Callback Function **************************/
	/*---------------------------------------------------------------------------*/
	

	/*---------------------------------------------------------------------------*/
	/************************** Self Callback Interface **************************/
	//// Get the pointer of Pre_SelfCallbackInterface of MUSiiCTaskObject
	igtl::MUSiiCCallbackInterface::Pointer GetPreSlefCallBackInterface();
	
	//// Get the pointer of Post_SelfCallbackInterface of MUSiiCTaskObject
	igtl::MUSiiCCallbackInterface::Pointer GetPostSlefCallBackInterface();

	/******************************************************************************/
	/// Declare a function that is called Pre-MUSiiCCallbackInterface
	virtual int PreCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);
	/// Declare a function that is called Post-MUSiiCCallbackInterface
	virtual int PostCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);
	
	/************************** Self Callback Interface **************************/
	/*---------------------------------------------------------------------------*/
	/************************** Callback Function *********************************/
	/******************************************************************************/
	
	/******************************************************************************/
	/************************** Task Function *************************************/
	/// Run the task funtion with/without thread
	virtual int RunTask(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);
	/// Set Task-Information
	virtual void SetTaskInfo(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);
	/// Stop the task thread
	virtual void StopTask();

	/// Wiat for the task thread
	virtual void WaitTask();

	/// Getting the index of current thread
	int GetThreadIdx();

	/// ????? Do we need this function?
	bool SetTaskMutexPointer(SimpleMutexLock* mutex);

	/// 
	void SetEnableDebug(bool enable = true) {m_bDebug = enable;}

	/// Get Current Timestamp
	double GetCurrentTimestamp(){ return GetTimeStampDouble();}
#if defined(WIN32) || defined (_WIN32) || defined (__WIN32__)
	/// Get Current Timestamp with sec and nanosec
	double GetQueryTimeStamp() { return GetQueryTimeStampDouble();}
#endif
	/// Enable Debug Message
	void EnableDebug(){m_bDebug = true;}

	/// Disable Debug Message
	void DisableDebug(){m_bDebug = false;}
	
protected: /// Methods
	/// Initialize Member variables
	virtual void Initialize();

	/// Thread function
	static void* TaskThread(void* ptr);

	/// The core function of task-Thread
	virtual void* TaskThreading();
	
	/// This function is main-part of MusiicTask 
	virtual int Task(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	/// The user-defined task function.
	/// You can make your own taskfunction by making subclass of MUSiiCAbstract
	virtual int TaskFunction(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	/// Declare a function that is called Pre-MUSiiCCallbackInterface
	int PreNotified(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	/// Declare a function that is called Post-MUSiiCCallbackInterface
	int PostNotified(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);
public: /// Attributes
	

protected: /// Attributes
	/// Information of MusiicTask Class
	std::string										m_pNameOfClass;

	/// Thread Data
	bool											m_bTaskThread;
	MultiThreader::Pointer							m_pThread;
	int												m_iThreadIdx;
	bool											m_bEnableThread;
	
	bool											m_bRunContinuous;

	int												m_iNumOfRun;
	int												m_iTaskInfo;
	void*											m_pPtr;
	igtl::MessageBase::Pointer 						m_pData1;
	void*											m_pData2;
	void*											m_pData3;

	igtl::FastMutexLock::Pointer					m_pFastMutex;
	
	///Task Function
	MUSiiCCallbackInterfaceControl::Pointer			m_pExternalTaskFunctions;
	bool											m_bEnableExternalTaskFuntions;
	
	/// Callback Interface
	/// Input Callback Interface for feedback information
	MUSiiCCallbackInterfaceControl::Pointer			m_pExternalInputCallbackFunctions;
	bool											m_bEnableExternalInputCallbackFuntions;
	
	/// Output Callbcak Interface for out-put data
	MUSiiCCallbackInterfaceControl::Pointer			m_pExternalOutputCallbackFunctions;
	bool											m_bEnableExternalOutputCallbackFuntions;

	/*MUSiiCCallbackInterface::Pointer				m_pSelfCallBackInterface;
	std::string										m_sNameOfSelfCallbackInterface;*/

	/// this callback interface pointer will connect to the output CallbackInterfaceControl of Pre-MUSiiCTask Class or Pre-MUSiiCTask Object
	igtl::MUSiiCCallbackInterface::Pointer			m_pPreSlefCallBackInterface;
	std::string										m_sNameOfSelfPreCallbackInterface;
	/// this callback interface pointer will connect to the input CallbackInterfaceControl of Post-MUSiiCTask Class or Post-MUSiiCTask Object
	igtl::MUSiiCCallbackInterface::Pointer			m_pPostSlefCallBackInterface;
	std::string										m_sNameOfSelfPostCallbackInterface;

	//External Mutex Pointer ::A pointer of Mutex ?????
	SimpleMutexLock									*m_pMutex;	//Do we need this value?
	bool											m_bIsMutex;	//Do we need this value?

	// Debug Information
	bool                                            m_bDebug;


};
};
#endif
