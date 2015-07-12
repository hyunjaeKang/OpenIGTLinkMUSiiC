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

/*************************************************************************

MusiicTaskAbstract:: This class is basic thread control for MusiicTask*****

***************************************************************************/
#ifndef __MUSIIC_TASK_ABSTRACT_
#define __MUSIIC_TASK_ABSTRACT_

#include "MUSiiCTaskObject.h"

//using namespace igtl;
namespace igtl
{
class IGTLMCommon_EXPORT MUSiiCTaskAbstract : public LightObject   ///public Object 
{
public: /// Methods
	/** Standard class typedefs. */
	typedef MUSiiCTaskAbstract			Self;
	typedef Object						Superclass;
	typedef SmartPointer<Self>			Pointer;
	typedef SmartPointer<const Self>	ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(MUSiiCTaskAbstract, Object);

	///Constructor
	MUSiiCTaskAbstract();
	
	///Deconstructor
	~MUSiiCTaskAbstract();
	
	/// Get the name of Class
	std::string GetNameOfMUSiiCClass();
	
	/// Setting whether using a thread fo task function or not.
	void SetEnableThread(bool bThread=true, int index = M_SELFTASKOBJECT);
	
	/******************************************************************************/
	/************************** External Task Function ****************************/
	/// Add External Global Task function
	int AddExternalGlobalTaskFunction(MusiicTaskFtn Func, std::string name = "", int index = M_SELFTASKOBJECT);

	/// Add External Local Task function
	template<class ObjType, typename funType> 
	inline int AddExternalLocalTaskFunction(ObjType obj, funType fun, std::string name = "", int index = M_SELFTASKOBJECT)
	{

		int r(-1);

		int sz(m_vMUSiiCTaskObjects.size());

		//if(index < sz )
		if(index < sz  || index == M_SELFTASKOBJECT)	
		{
			if(index == M_ALLTASKOBJECT)
			{
				m_bSelfTaskFunction = false;
				for(int i=0; i<sz; i++)
					r += m_vMUSiiCTaskObjects[i]->AddExternalLocalTaskFunction(obj, fun, name);
			}
			else if (index == M_SELFTASKOBJECT || index == 0)
			{
				m_bSelfTaskFunction = false;
				r = m_vMUSiiCTaskObjects[0]->AddExternalLocalTaskFunction(obj, fun, name);
			}
			else
				r = m_vMUSiiCTaskObjects[index]->AddExternalLocalTaskFunction(obj, fun, name);
		}

		return r;
	}

	/// get the number of External Task Functions
	int GetNumOfExternalTaskFunctions();

	/// Call External_class Callback functions using MUSiiCCallbackInterface
	virtual int CallExternalTaskFunctions(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL, int index = M_SELFTASKOBJECT);

	void SetEnableExternalTaskFunctions(bool enable, int index = M_SELFTASKOBJECT);
	bool GetEnableExternalTaskFunctions(int index = M_SELFTASKOBJECT);
	
	/******************************************************************************/
	/************************** Callback Function *********************************/
	
	/*---------------------------------------------------------------------------*/
	/************************** Input Callback Function **************************/
	/// Add External Global callback function
	int AddExternalGlobalInputCallbackFunction(MusiicTaskFtn Func, std::string name = "", int index = M_SELFTASKOBJECT);

	/// Add External Global callback function
	int AddExternalGlobalPreCallbackFunction(MusiicTaskFtn Func, std::string name = "", int index = M_SELFTASKOBJECT);

	/// Add External Local callback function
	template<class ObjType, typename funType> 
	inline int AddExternalLocalInputCallbackFunction(ObjType obj, funType fun, std::string name = "", int index = M_SELFTASKOBJECT)
	{
		int r(0);

		int sz(m_vMUSiiCTaskObjects.size());

		if(index < sz  || index == M_SELFTASKOBJECT)
		{
			if(index == M_ALLTASKOBJECT)
			{
				for(int i=0; i<sz; i++)
					r += m_vMUSiiCTaskObjects[i]->AddExternalLocalInputCallbackFunction(obj, fun, name);
			}
			else if (index == M_SELFTASKOBJECT || index == 0)
			{
				r = m_vMUSiiCTaskObjects[0]->AddExternalLocalInputCallbackFunction(obj, fun, name);
			}
			else
				r = m_vMUSiiCTaskObjects[index]->AddExternalLocalInputCallbackFunction(obj, fun, name);

			m_bEnableExternalInputCallbackFuntions = true;
		}

		
		return r;
	}

	/// Add External Local callback function
	template<class ObjType, typename funType> 
	inline int AddExternalLocalPreCallbackFunction(ObjType obj, funType fun, std::string name = "", int index = M_SELFTASKOBJECT)
	{
		return AddExternalLocalInputCallbackFunction(obj, fun, name, index);
	}
	
	/// Set a callbackinterface of another MUSiiCTask class
	int AddInputCallbackInterface(igtl::MUSiiCCallbackInterface::Pointer cbInterface, int index = M_SELFTASKOBJECT);

	/// Set a callbackinterface of another MUSiiCTask class
	int AddPreCallbackInterface(igtl::MUSiiCCallbackInterface::Pointer cbInterface, int index = M_SELFTASKOBJECT);

	/// ************** New
	/// Remove the CallbackInterface of given MUSiiCTask Calss
	/// Return value is the number of output CallbackInterface of this class.
	/// If the return value is less than zero, this means the error of this function
	int RemoveInputCallbackInterface(igtl::MUSiiCCallbackInterface::Pointer cbInterface);

	int RemovePreCallbackInterface(igtl::MUSiiCCallbackInterface::Pointer cbInterface);

	/// get the number of External Callback Functions
	int GetNumOfExternalInputCallbackFunctions(int index = M_SELFTASKOBJECT);

	int GetNumOfExternalPreCallbackFunctions(int index = M_SELFTASKOBJECT);

	/// Call External_class Callback functions using MUSiiCCallbackInterface
	virtual int CallExternalInputCallbackFunctions(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL, int index = M_SELFTASKOBJECT);

	/// Call External_class Callback functions using MUSiiCCallbackInterface
	virtual int CallExternalPreCallbackFunctions(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL, int index = M_SELFTASKOBJECT);

	void SetEnableExternalInputCallbackFunctions(bool enable, int index = M_SELFTASKOBJECT);

	void SetEnableExternalPreCallbackFunctions(bool enable, int index = M_SELFTASKOBJECT);

	bool GetEnableExternalInputCallbackFunctions(int index = M_SELFTASKOBJECT);

	bool GetEnableExternalPreCallbackFunctions(int index = M_SELFTASKOBJECT);

	/// Set Input CallbackInterfaceControl of Self_Task_Object with given callbackinterface control
	bool SetSelfTaskInputCallbackInterfaceControl(igtl::MUSiiCCallbackInterfaceControl::Pointer pCallbackIFControl);
	bool SetSelfTaskPreCallbackInterfaceControl(igtl::MUSiiCCallbackInterfaceControl::Pointer pCallbackIFControl);

	/// Get Input CallbackInterfaceControl of Self_Task_Object 
	igtl::MUSiiCCallbackInterfaceControl::Pointer GetSelfTaskInputCallbackInterfaceControl();
	igtl::MUSiiCCallbackInterfaceControl::Pointer GetSelfTaskPreCallbackInterfaceControl();


	/************************** Input Callback Function **************************/
	/*---------------------------------------------------------------------------*/

	/*---------------------------------------------------------------------------*/
	/************************** Output Callback Function **************************/
	/// Add External Global callback function

	int AddExternalGlobalOutputCallbackFunction(MusiicTaskFtn Func, std::string name = "", int index = M_SELFTASKOBJECT);

	int AddExternalGlobalPostCallbackFunction(MusiicTaskFtn Func, std::string name = "", int index = M_SELFTASKOBJECT);

	/// Add External Local callback function
	template<class ObjType, typename funType> 
	inline int AddExternalLocalOutputCallbackFunction(ObjType obj, funType fun, std::string name = "", int index = M_SELFTASKOBJECT)
	{
		int r(0);

		int sz(m_vMUSiiCTaskObjects.size());

		if(index < sz  || index == M_SELFTASKOBJECT)
		{
			if(index == M_ALLTASKOBJECT)
			{
				for(int i=0; i<sz; i++)
					r += m_vMUSiiCTaskObjects[i]->AddExternalLocalOutputCallbackFunction(obj, fun, name);
			}
			else if (index == M_SELFTASKOBJECT || index == 0)
			{
				r = m_vMUSiiCTaskObjects[0]->AddExternalLocalOutputCallbackFunction(obj, fun, name);
			}
			else
				r = m_vMUSiiCTaskObjects[index]->AddExternalLocalOutputCallbackFunction(obj, fun, name);

			m_bEnableExternalOutputCallbackFuntions = true;
		}

			
		return r;
	}

	template<class ObjType, typename funType> 
	inline int AddExternalLocalPostCallbackFunction(ObjType obj, funType fun, std::string name = "", int index = M_SELFTASKOBJECT)
	{
		return AddExternalLocalOutputCallbackFunction(obj, fun, name, index);
	}
		
	/// Set a callbackinterface of another MUSiiCTask class
	int AddOutputCallbackInterface(igtl::MUSiiCCallbackInterface::Pointer cbInterface, int index = M_SELFTASKOBJECT);
	int AddPostCallbackInterface(igtl::MUSiiCCallbackInterface::Pointer cbInterface, int index = M_SELFTASKOBJECT);

	/// ************** New
	/// Remove the CallbackInterface of given MUSiiCTask Calss
	/// Return value is the number of output CallbackInterface of this class.
	/// If the return value is less than zero, this means the error of this function
	int RemoveOutputCallbackInterface(igtl::MUSiiCCallbackInterface::Pointer cbInterface);
	int RemovePostCallbackInterface(igtl::MUSiiCCallbackInterface::Pointer cbInterface);

	/// get the number of External Callback Functions
	int GetNumOfExternalOutputCallbackFunctions(int index = M_SELFTASKOBJECT);
	int GetNumOfExternalPostCallbackFunctions(int index = M_SELFTASKOBJECT);

	/// Call External_class Callback functions using MUSiiCCallbackInterface
	virtual int CallExternalOutputCallbackFunctions(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1= NULL, void* data2 = NULL, void* data3 = NULL, int index = M_SELFTASKOBJECT);
	virtual int CallExternalPostCallbackFunctions(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1= NULL, void* data2 = NULL, void* data3 = NULL, int index = M_SELFTASKOBJECT);

	void SetEnableExternalOutputCallbackFunctions(bool enable, int index = M_SELFTASKOBJECT);
	void SetEnableExternalPostCallbackFunctions(bool enable, int index = M_SELFTASKOBJECT);

	bool GetEnableExternalOutputCallbackFunctions(int index = M_SELFTASKOBJECT);
	bool GetEnableExternalPostCallbackFunctions(int index = M_SELFTASKOBJECT);

	/// Set Output CallbackInterfaceControl of Self_Task_Object with given callbackinterface control
	bool SetSelfTaskOutputCallbackInterfaceControl(igtl::MUSiiCCallbackInterfaceControl::Pointer pCallbackIFControl);
	bool SetSelfTaskPostCallbackInterfaceControl(igtl::MUSiiCCallbackInterfaceControl::Pointer pCallbackIFControl);
	/// Get Output CallbackInterfaceControl of Self_Task_Object 
	igtl::MUSiiCCallbackInterfaceControl::Pointer GetSelfTaskOutputCallbackInterfaceControl();
	igtl::MUSiiCCallbackInterfaceControl::Pointer GetSelfTaskPostCallbackInterfaceControl();

	/************************** Output Callback Function **************************/
	/*---------------------------------------------------------------------------*/

	/*---------------------------------------------------------------------------*/
	/************************** General Callback Function **************************/

	/// Get Callback interface of MUSiiCTackObject
	//igtl::MUSiiCCallbackInterface::Pointer GetTaskObjectCallbackInterface(int index = M_SELFTASKOBJECT);

	//// Get the pointer of Pre_SelfCallbackInterface of MUSiiCTaskObject
	igtl::MUSiiCCallbackInterface::Pointer GetTaskObjectPreSlefCallBackInterface(int index = M_SELFTASKOBJECT);

	//// Get the pointer ofPost_SelfCallbackInterface of MUSiiCTaskObject
	igtl::MUSiiCCallbackInterface::Pointer GetTaskObjecPostSlefCallBackInterface(int index = M_SELFTASKOBJECT);
	
	//// Get the pointer of Pre_SelfCallbackInterface of MUSiiCTaskObject
	igtl::MUSiiCCallbackInterface::Pointer GetPreSlefCallBackInterface();
	
	//// Get the pointer of Post_SelfCallbackInterface of MUSiiCTaskObject
	igtl::MUSiiCCallbackInterface::Pointer GetPostSlefCallBackInterface();

	//// User defined Callback function
	/// Declare a function that is called MUSiiCCallbackInterface
	virtual int PreCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	/// Declare a function that is called MUSiiCCallbackInterface
	virtual int PostCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	/////////////////////////////////////////////////////////////////////////////

	/// Get Pre-CallbackInterfaceControl of TaskObject
	igtl::MUSiiCCallbackInterfaceControl::Pointer GetPreCallbackInterfaceControlOfMUSiiCTaskObject(int index = M_SELFTASKOBJECT);

	/// Get Pre-CallbackInterfaceControl of TaskObject
	igtl::MUSiiCCallbackInterfaceControl::Pointer GetPostCallbackInterfaceControlOfMUSiiCTaskObject(int index = M_SELFTASKOBJECT);


	/// Set Pre-CallbackInterfaceControl of TaskObject with the given CallbackInterface Control
	bool SetPreCallbackInterfaceControlOfMUSiiCTaskObject(igtl::MUSiiCCallbackInterfaceControl::Pointer callIFControl,int index = M_SELFTASKOBJECT);

	/// Set Pre-CallbackInterfaceControl of TaskObject with the given CallbackInterface Control
	bool SetPostCallbackInterfaceControlOfMUSiiCTaskObject(igtl::MUSiiCCallbackInterfaceControl::Pointer callIFControl, int index = M_SELFTASKOBJECT);



	/*---------------------------------------------------------------------------*/
	/************************** General Callback Function **************************/
	
	/******************************************************************************/
	

	/******************************************************************************/
	/************************** Task Function *************************************/
	
	//// Add Task Object
	int AddTaskObject(igtl::MUSiiCTaskObject::Pointer pTaskObject);

	/// Get the number of Task Object
	int GetNumOfTaskObject();

	//// Clear Task Object List
	int ClearTaskObject(igtl::MUSiiCTaskObject::Pointer pTaskObject);

	//// Remove Task Object 
	int RemoveTaskObject(int index);

	/// Get the pointer of Task object.
	igtl::MUSiiCTaskObject::Pointer GetTaskObject(int index = M_SELFTASKOBJECT); 

	/// Run the task funtion with/without thread
	virtual int RunTask(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL, int index = M_SELFTASKOBJECT);
	/// Stop the task thread
	virtual void StopTask(int index = M_SELFTASKOBJECT);

	/// Wiat for the task thread
	virtual void WaitTask(int index = M_SELFTASKOBJECT);

	/// Getting the index of current thread
	int GetThreadIdx(int index = M_SELFTASKOBJECT);

	/// ????? Do we need this function?
	bool SetTaskMutexPointer(SimpleMutexLock* mutex, int index = M_SELFTASKOBJECT);

	

	
	/************************** Task Function *************************************/
	/******************************************************************************/

	/******************************************************************************/
	/************************** Connect MUSiiCTask ********************************/

	/// Add an object of MUSiiCTaskAbstract as Pre-Task
	virtual bool AddPreMUSiiCTask(igtl::MUSiiCTaskAbstract::Pointer pre_task);


	/// Remove an object of MUSiiCTaskAbstract as Pre-Task
	virtual bool RemovePreMUSiiCTask(igtl::MUSiiCTaskAbstract::Pointer pre_task);

	
	/// Add an object of MUSiiCTaskAbstract as Post-Task
	virtual bool AddPostMUSiiCTask(igtl::MUSiiCTaskAbstract::Pointer post_task);

	/// Remove an object of MUSiiCTaskAbstract as Pre-Task
	virtual bool RemovePostMUSiiCTask(igtl::MUSiiCTaskAbstract::Pointer post_task);


	/************************** Connect MUSiiCTask ********************************/
	/******************************************************************************/

	/******************************************************************************/
	/************************** ETC ***********************************************/
	/// Get Current Timestamp
	double GetCurrentTimestamp(){ return GetTimeStampDouble();}
#if defined(WIN32) || defined (_WIN32) || defined (__WIN32__)
	/// Get Current Timestamp with sec and nanosec
	double GetQueryTimeStamp() { return GetQueryTimeStampDouble();}
#endif

	/// Set Debug Information
	void SetEnableDebug(bool enable = true); 

	/// Get This-Task status
	int GetTaskStatus(){return m_iTaskStatus;}


	//----------------------------------------------------------------------------------//

	/************************** ETC ***********************************************/
	/******************************************************************************/
	
	
public: /// Attributes
	
protected: /// Methods
	/// Initialize Member variables
	virtual void Initialize();

	/// Pre-Task Function
	int PreTaskFunction(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);
	
	/// The user-defined task function.
	/// You can make your own taskfunction by making subclass of MUSiiCAbstract
	virtual int TaskFunction(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	
	/// Declare a function that is called MUSiiCCallbackInterface
	int PreNotified(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	int PostNotified(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

protected: /// Attributes
	/// Information of MusiicTask Class
	/*char*											m_pNameOfClass;*/
	std::string										m_pNameOfClass;

	/// TO DO:: Please check this container
	std::vector<igtl::MUSiiCTaskObject::Pointer>    m_vMUSiiCTaskObjects;
	
	igtl::MUSiiCTaskObject::Pointer					m_pSelfMUSiiCTaskObject;
	bool											m_bSelfTaskFunction;

	/// Self callback interface
	/*MUSiiCCallbackInterface::Pointer				m_pSelfCallBackInterface;
	std::string										m_sNameOfSelfCallbackInterface;*/

	/// this callback interface pointer will connect to the output CallbackInterfaceControl of Pre-MUSiiCTask Class or Pre-MUSiiCTask Object
	igtl::MUSiiCCallbackInterface::Pointer			m_pPreSlefCallBackInterface;
	std::string										m_sNameOfPreSelfCallbackInterface;
	/// this callback interface pointer will connect to the input CallbackInterfaceControl of Post-MUSiiCTask Class or Post-MUSiiCTask Object
	igtl::MUSiiCCallbackInterface::Pointer			m_pPostSlefCallBackInterface;
	std::string										m_sNameOfPostSelfCallbackInterface;

	////////////////////////////////////////////////////////////////////////////////
	bool											m_bEnableThread;
	bool											m_bTaskThread;

	bool											m_bDebug;

	int												m_iTaskStatus;


	//////////////////////////////////////////////////////////////////////////////

	bool											m_bEnableExternalInputCallbackFuntions;
	bool											m_bEnableExternalOutputCallbackFuntions;

	//A pointer of Mutex ?????
	SimpleMutexLock									*m_pMutex;	//Do we need this value?
	bool											m_bIsMutex;	//Do we need this value?

	igtl::FastMutexLock::Pointer					m_pFastMutex;

};
};
#endif
