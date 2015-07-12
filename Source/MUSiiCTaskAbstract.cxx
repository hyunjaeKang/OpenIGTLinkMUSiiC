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
#include "MUSiiCTaskAbstract.h"

//using namespace igtl;
namespace igtl
{

///Constructor
MUSiiCTaskAbstract::MUSiiCTaskAbstract()
{
	m_pNameOfClass = "MusiicTaskAbstract";
	Initialize();
}
	
///Deconstructor
MUSiiCTaskAbstract::~MUSiiCTaskAbstract()
{
	this->StopTask(M_ALLTASKOBJECT);
	if(m_pMutex!=NULL)
	{
		m_pMutex->Unlock();
		delete m_pMutex;
	}

	if(m_pFastMutex.IsNotNull())
		m_pFastMutex->Unlock();
}
	

std::string MUSiiCTaskAbstract::GetNameOfMUSiiCClass()
{
	return m_pNameOfClass;
}
	
/// Setting whether using a thread fo task function or not.
void MUSiiCTaskAbstract::SetEnableThread(bool bThread, int index)
{
	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT || index == M_ALLTASKOBJECT)
	{
		if(index == M_ALLTASKOBJECT)
			for(int i=0; i<sz; i++)
				m_vMUSiiCTaskObjects[i]->SetEnableThread(bThread);
		else if (index == M_SELFTASKOBJECT)
			m_vMUSiiCTaskObjects[0]->SetEnableThread(bThread);
		else
			m_vMUSiiCTaskObjects[index]->SetEnableThread(bThread);
	}

	m_bEnableThread = bThread;
}
	
/******************************************************************************/
/************************** External Task Function ****************************/
/// Add External Global Task function
int MUSiiCTaskAbstract::AddExternalGlobalTaskFunction(MusiicTaskFtn Func, std::string name, int index)
{
	
	int r(-1);

	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT || index == M_ALLTASKOBJECT)
	{
		if(index == M_ALLTASKOBJECT)
		{
			m_bSelfTaskFunction = false;
			for(int i=0; i<sz; i++)
				r += m_vMUSiiCTaskObjects[i]->AddExternalGlobalTaskFunction(Func, name);
		}
		else if (index == M_SELFTASKOBJECT || index == 0)
		{
			m_bSelfTaskFunction = false;
			r = m_vMUSiiCTaskObjects[0]->AddExternalGlobalTaskFunction(Func, name);
		}
		else
			r = m_vMUSiiCTaskObjects[index]->AddExternalGlobalTaskFunction(Func, name);
	}

	return r;
}


/// get the number of External Task Functions
int MUSiiCTaskAbstract::GetNumOfExternalTaskFunctions()
{
	int r(0);
	int sz(m_vMUSiiCTaskObjects.size());

	for(int i=0; i<sz; i++)
				r += m_vMUSiiCTaskObjects[i]->GetNumOfExternalTaskFunctions();
	return r;
}

/// Call External_class Callback functions using MUSiiCCallbackInterface
int MUSiiCTaskAbstract::CallExternalTaskFunctions(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3, int index)
{

	int r(-1);

	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT || index == M_ALLTASKOBJECT)
	{
		if(index == M_ALLTASKOBJECT)
		{
			for(int i=0; i<sz; i++)
				r += m_vMUSiiCTaskObjects[i]->CallExternalTaskFunctions(numOfRun, taskInfo, ptr, data1, data2, data3);
		}
		else if (index == M_SELFTASKOBJECT || index == 0)
		{
			r = m_vMUSiiCTaskObjects[0]->CallExternalTaskFunctions(numOfRun, taskInfo, ptr, data1, data2, data3);
		}
		else
			r = m_vMUSiiCTaskObjects[index]->CallExternalTaskFunctions(numOfRun, taskInfo, ptr, data1, data2, data3);
	}

	return r;
}

void MUSiiCTaskAbstract::SetEnableExternalTaskFunctions(bool enable, int index)
{
	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT || index == M_ALLTASKOBJECT)
	{
		if(index == M_ALLTASKOBJECT)
		{
			for(int i=0; i<sz; i++)
				m_vMUSiiCTaskObjects[i]->SetEnableExternalTaskFunctions(enable);
		}
		else if (index == M_SELFTASKOBJECT || index == 0)
		{
			m_vMUSiiCTaskObjects[0]->SetEnableExternalTaskFunctions(enable);
		}
		else
			m_vMUSiiCTaskObjects[index]->SetEnableExternalTaskFunctions(enable);
	}
}

bool MUSiiCTaskAbstract::GetEnableExternalTaskFunctions(int index)
{
	if (index == M_SELFTASKOBJECT || index == 0)
		return m_vMUSiiCTaskObjects[0]->GetEnableExternalTaskFunctions();
	else
		return m_vMUSiiCTaskObjects[index]->GetEnableExternalTaskFunctions();
}
	
/******************************************************************************/
/************************** Callback Function *********************************/
/*---------------------------------------------------------------------------*/
/************************** Input Callback Function **************************/

/// Add External Global callback function
int MUSiiCTaskAbstract::AddExternalGlobalInputCallbackFunction(MusiicTaskFtn Func, std::string name, int index)
{
	int r(0);

	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT || index == M_ALLTASKOBJECT)
	{
		if(index == M_ALLTASKOBJECT)
		{
			for(int i=0; i<sz; i++)
				r += m_vMUSiiCTaskObjects[i]->AddExternalGlobalInputCallbackFunction(Func, name);
		}
		else if (index == M_SELFTASKOBJECT || index == 0)
		{
			r = m_vMUSiiCTaskObjects[0]->AddExternalGlobalInputCallbackFunction(Func, name);
		}
		else
			r = m_vMUSiiCTaskObjects[index]->AddExternalGlobalInputCallbackFunction(Func, name);
	}

	m_bEnableExternalInputCallbackFuntions = true;
	return r;
}

int MUSiiCTaskAbstract::AddExternalGlobalPreCallbackFunction(MusiicTaskFtn Func, std::string name, int index)
{
	return AddExternalGlobalInputCallbackFunction(Func, name, index);
}
		
/// Set a callbackinterface of another MUSiiCTask class
int MUSiiCTaskAbstract::AddInputCallbackInterface(igtl::MUSiiCCallbackInterface::Pointer cbInterface, int index)
{
	if(cbInterface.IsNull())
		return 0;
	
	int r(0);

	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT || index == M_ALLTASKOBJECT)
	{
		if(index == M_ALLTASKOBJECT)
		{
			for(int i=0; i<sz; i++)
				r += m_vMUSiiCTaskObjects[i]->AddInputCallbackInterface(cbInterface);
		}
		else if (index == M_SELFTASKOBJECT || index == 0)
		{
			r = m_vMUSiiCTaskObjects[0]->AddInputCallbackInterface(cbInterface);
		}
		else
			r = m_vMUSiiCTaskObjects[index]->AddInputCallbackInterface(cbInterface);
	}

	m_bEnableExternalInputCallbackFuntions = true;
	return r;
}

int MUSiiCTaskAbstract::AddPreCallbackInterface(igtl::MUSiiCCallbackInterface::Pointer cbInterface, int index)
{
	return AddInputCallbackInterface(cbInterface, index);
}

/// ************** New
/// Remove the CallbackInterface of given MUSiiCTask Calss
/// Return value is the number of output CallbackInterface of this class.
/// If the return value is less than zero, this means the error of this function
int MUSiiCTaskAbstract::RemoveInputCallbackInterface(igtl::MUSiiCCallbackInterface::Pointer cbInterface)
{
	if(cbInterface.IsNull())
		return -1;

	int r(0);

	int sz(m_vMUSiiCTaskObjects.size());

	for(int i=0; i<sz ;i++)
	{
		r = m_vMUSiiCTaskObjects[i]->RemoveInputCallbackInterface(cbInterface);
		if(r>-1)
		{
			r=0;
			for(int j=0; j<sz; j++)
				r += m_vMUSiiCTaskObjects[j]->GetNumOfExternalInputCallbackFunctions();

			m_bEnableExternalInputCallbackFuntions = r>0 ? true : false;
			
			return r;
		}
	}
	return -1;
}

int MUSiiCTaskAbstract::RemovePreCallbackInterface(igtl::MUSiiCCallbackInterface::Pointer cbInterface)
{
	return RemoveInputCallbackInterface(cbInterface);
}
	
/// get the number of External Callback Functions
int MUSiiCTaskAbstract::GetNumOfExternalInputCallbackFunctions(int index)
{

	int r(0);

	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT || index == M_ALLTASKOBJECT)
	{
		if(index == M_ALLTASKOBJECT)
		{
			for(int i=0; i<sz; i++)
				r += m_vMUSiiCTaskObjects[i]->GetNumOfExternalInputCallbackFunctions();
		}
		else if (index == M_SELFTASKOBJECT || index == 0)
		{
			r = m_vMUSiiCTaskObjects[0]->GetNumOfExternalInputCallbackFunctions();
		}
		else
			r = m_vMUSiiCTaskObjects[index]->GetNumOfExternalInputCallbackFunctions();
	}

	return r;
}

int MUSiiCTaskAbstract::GetNumOfExternalPreCallbackFunctions(int index)
{
	return GetNumOfExternalInputCallbackFunctions(index);
}

/// Call External_class Callback functions using MUSiiCCallbackInterface
int MUSiiCTaskAbstract::CallExternalInputCallbackFunctions(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3,int index)
{
	int r(0);

	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT || index == M_ALLTASKOBJECT)
	{
		if(index == M_ALLTASKOBJECT)
		{
			for(int i=0; i<sz; i++)
				r += m_vMUSiiCTaskObjects[i]->CallExternalInputCallbackFunctions(numOfRun, taskInfo, ptr, data1, data2, data3);
		}
		else if (index == M_SELFTASKOBJECT || index == 0)
		{
			r = m_vMUSiiCTaskObjects[0]->CallExternalInputCallbackFunctions(numOfRun, taskInfo, ptr, data1, data2, data3);
		}
		else
			r = m_vMUSiiCTaskObjects[index]->CallExternalInputCallbackFunctions(numOfRun, taskInfo, ptr, data1, data2, data3);
	}

	return r;
}

int MUSiiCTaskAbstract::CallExternalPreCallbackFunctions(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3,int index)
{
	return CallExternalInputCallbackFunctions(numOfRun, taskInfo, ptr, data1, data2, data3,index);
}
/// Set External callback function will use or not
void MUSiiCTaskAbstract::SetEnableExternalInputCallbackFunctions(bool enable, int index)
{

	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT || index == M_ALLTASKOBJECT)
	{
		if(index == M_ALLTASKOBJECT)
		{
			for(int i=0; i<sz; i++)
				m_vMUSiiCTaskObjects[i]->SetEnableExternalInputCallbackFunctions(enable);
		}
		else if (index == M_SELFTASKOBJECT || index == 0)
		{
			m_vMUSiiCTaskObjects[0]->SetEnableExternalInputCallbackFunctions(enable);
		}
		else
			m_vMUSiiCTaskObjects[index]->SetEnableExternalInputCallbackFunctions(enable);
	}

	m_bEnableExternalInputCallbackFuntions = enable;
}

void MUSiiCTaskAbstract::SetEnableExternalPreCallbackFunctions(bool enable, int index)
{
	SetEnableExternalInputCallbackFunctions(enable,index);
}
/// Set External callback function will use or not
bool MUSiiCTaskAbstract::GetEnableExternalInputCallbackFunctions(int index)
{
	bool r(true);

	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT || index == M_ALLTASKOBJECT)
	{
		if(index == M_ALLTASKOBJECT)
		{
			for(int i=0; i<sz; i++)
				r &= m_vMUSiiCTaskObjects[i]->GetEnableExternalInputCallbackFunctions();
		}
		else if (index == M_SELFTASKOBJECT || index == 0)
		{
			r = m_vMUSiiCTaskObjects[0]->GetEnableExternalInputCallbackFunctions();
		}
		else
			r = m_vMUSiiCTaskObjects[index]->GetEnableExternalInputCallbackFunctions();
	}

	return r;
}

bool MUSiiCTaskAbstract::GetEnableExternalPreCallbackFunctions(int index)
{
	return GetEnableExternalInputCallbackFunctions(index);
}

/// Set Input CallbackInterfaceControl of Self_Task_Object with given callbackinterface control
bool MUSiiCTaskAbstract::SetSelfTaskInputCallbackInterfaceControl(igtl::MUSiiCCallbackInterfaceControl::Pointer pCallbackIFControl)
{
	if(m_pSelfMUSiiCTaskObject.IsNotNull())
		return m_pSelfMUSiiCTaskObject->SetInputCallbackInterfaceControl(pCallbackIFControl);
	return false;
}

bool MUSiiCTaskAbstract::SetSelfTaskPreCallbackInterfaceControl(igtl::MUSiiCCallbackInterfaceControl::Pointer pCallbackIFControl)
{
	return SetSelfTaskInputCallbackInterfaceControl(pCallbackIFControl);
}
/// Get Input CallbackInterfaceControl of Self_Task_Object 
igtl::MUSiiCCallbackInterfaceControl::Pointer MUSiiCTaskAbstract::GetSelfTaskInputCallbackInterfaceControl()
{
	if(m_pSelfMUSiiCTaskObject.IsNotNull())
		return m_pSelfMUSiiCTaskObject->GetInputCallbackInterfaceControl();
	return NULL;
}

igtl::MUSiiCCallbackInterfaceControl::Pointer MUSiiCTaskAbstract::GetSelfTaskPreCallbackInterfaceControl()
{
	return GetSelfTaskInputCallbackInterfaceControl();
}

/************************** Input Callback Function **************************/
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/************************** Output Callback Function **************************/
/// Add External Global callback function
int MUSiiCTaskAbstract::AddExternalGlobalOutputCallbackFunction(MusiicTaskFtn Func, std::string name, int index)
{
	int r(0);

	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT || index == M_ALLTASKOBJECT)
	{
		if(index == M_ALLTASKOBJECT)
		{
			for(int i=0; i<sz; i++)
				r += m_vMUSiiCTaskObjects[i]->AddExternalGlobalOutputCallbackFunction(Func, name);
		}
		else if (index == M_SELFTASKOBJECT || index == 0)
		{
			r = m_vMUSiiCTaskObjects[0]->AddExternalGlobalOutputCallbackFunction(Func, name);
		}
		else
			r = m_vMUSiiCTaskObjects[index]->AddExternalGlobalOutputCallbackFunction(Func, name);
	}

	m_bEnableExternalOutputCallbackFuntions = true;
	return r;
}

int MUSiiCTaskAbstract::AddExternalGlobalPostCallbackFunction(MusiicTaskFtn Func, std::string name, int index)
{
	return AddExternalGlobalOutputCallbackFunction(Func, name, index);
}
		
/// Set a callbackinterface of another MUSiiCTask class
int MUSiiCTaskAbstract::AddOutputCallbackInterface(igtl::MUSiiCCallbackInterface::Pointer cbInterface, int index)
{
	if(cbInterface.IsNull())
		return 0;

	int r(0);

	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT || index == M_ALLTASKOBJECT)
	{
		if(index == M_ALLTASKOBJECT)
		{
			for(int i=0; i<sz; i++)
				r += m_vMUSiiCTaskObjects[i]->AddOutputCallbackInterface(cbInterface);
		}
		else if (index == M_SELFTASKOBJECT || index == 0)
		{
			r = m_vMUSiiCTaskObjects[0]->AddOutputCallbackInterface(cbInterface);
		}
		else
			r = m_vMUSiiCTaskObjects[index]->AddOutputCallbackInterface(cbInterface);
	}

	m_bEnableExternalOutputCallbackFuntions = true;
	return r;
}

int MUSiiCTaskAbstract::AddPostCallbackInterface(igtl::MUSiiCCallbackInterface::Pointer cbInterface, int index)
{
	return AddOutputCallbackInterface( cbInterface, index);
}

/// ************** New
/// Remove the CallbackInterface of given MUSiiCTask Calss
/// Return value is the number of output CallbackInterface of this class.
/// If the return value is less than zero, this means the error of this function
int MUSiiCTaskAbstract::RemoveOutputCallbackInterface(igtl::MUSiiCCallbackInterface::Pointer cbInterface)
{
	if(cbInterface.IsNull())
		return -1;

	int r(0);

	int sz(m_vMUSiiCTaskObjects.size());

	for(int i=0; i<sz ;i++)
	{
		r = m_vMUSiiCTaskObjects[i]->RemoveOutputCallbackInterface(cbInterface);
		if(r>-1)
		{
			r=0;
			for(int j=0; j<sz; j++)
				r += m_vMUSiiCTaskObjects[j]->GetNumOfExternalOutputCallbackFunctions();

			m_bEnableExternalOutputCallbackFuntions = r>0 ? true : false;
			
			return r;
		}
	}
	return -1;
}

int MUSiiCTaskAbstract::RemovePostCallbackInterface(igtl::MUSiiCCallbackInterface::Pointer cbInterface)
{
	return RemoveOutputCallbackInterface( cbInterface);
}
	
/// get the number of External Callback Functions
int MUSiiCTaskAbstract::GetNumOfExternalOutputCallbackFunctions(int index)
{

	int r(0);

	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT || index == M_ALLTASKOBJECT)
	{
		if(index == M_ALLTASKOBJECT)
		{
			for(int i=0; i<sz; i++)
				r += m_vMUSiiCTaskObjects[i]->GetNumOfExternalOutputCallbackFunctions();
		}
		else if (index == M_SELFTASKOBJECT || index == 0)
		{
			r = m_vMUSiiCTaskObjects[0]->GetNumOfExternalOutputCallbackFunctions();
		}
		else
			r = m_vMUSiiCTaskObjects[index]->GetNumOfExternalOutputCallbackFunctions();
	}

	return r;
}

int MUSiiCTaskAbstract::GetNumOfExternalPostCallbackFunctions(int index)
{
	return GetNumOfExternalOutputCallbackFunctions(index);
}

/// Call External_class Callback functions using MUSiiCCallbackInterface
int MUSiiCTaskAbstract::CallExternalOutputCallbackFunctions(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3,int index)
{
	int r(0);

	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT || index == M_ALLTASKOBJECT)
	{
		if(index == M_ALLTASKOBJECT)
		{
			for(int i=0; i<sz; i++)
				r += m_vMUSiiCTaskObjects[i]->CallExternalOutputCallbackFunctions(numOfRun, taskInfo, ptr, data1, data2, data3);
		}
		else if (index == M_SELFTASKOBJECT || index == 0)
		{
			r = m_vMUSiiCTaskObjects[0]->CallExternalOutputCallbackFunctions(numOfRun, taskInfo, ptr, data1, data2, data3);
		}
		else
			r = m_vMUSiiCTaskObjects[index]->CallExternalOutputCallbackFunctions(numOfRun, taskInfo, ptr, data1, data2, data3);
	}

	return r;
}

int MUSiiCTaskAbstract::CallExternalPostCallbackFunctions(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3,int index)	
{
	return CallExternalOutputCallbackFunctions(numOfRun, taskInfo, ptr, data1, data2, data3,index);
}

/// Set External callback function will use or not
void MUSiiCTaskAbstract::SetEnableExternalOutputCallbackFunctions(bool enable, int index)
{

	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT || index == M_ALLTASKOBJECT)
	{
		if(index == M_ALLTASKOBJECT)
		{
			for(int i=0; i<sz; i++)
				m_vMUSiiCTaskObjects[i]->SetEnableExternalOutputCallbackFunctions(enable);
		}
		else if (index == M_SELFTASKOBJECT || index == 0)
		{
			m_vMUSiiCTaskObjects[0]->SetEnableExternalOutputCallbackFunctions(enable);
		}
		else
			m_vMUSiiCTaskObjects[index]->SetEnableExternalOutputCallbackFunctions(enable);
	}

	m_bEnableExternalOutputCallbackFuntions = enable;
}

void MUSiiCTaskAbstract::SetEnableExternalPostCallbackFunctions(bool enable, int index)
{
	SetEnableExternalOutputCallbackFunctions(enable, index);
}

/// Set External callback function will use or not
bool MUSiiCTaskAbstract::GetEnableExternalOutputCallbackFunctions(int index)
{
	bool r(true);

	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT || index == M_ALLTASKOBJECT)
	{
		if(index == M_ALLTASKOBJECT)
		{
			for(int i=0; i<sz; i++)
				r &= m_vMUSiiCTaskObjects[i]->GetEnableExternalOutputCallbackFunctions();
		}
		else if (index == M_SELFTASKOBJECT || index == 0)
		{
			r = m_vMUSiiCTaskObjects[0]->GetEnableExternalOutputCallbackFunctions();
		}
		else
			r = m_vMUSiiCTaskObjects[index]->GetEnableExternalOutputCallbackFunctions();
	}

	return r;
}

bool MUSiiCTaskAbstract::GetEnableExternalPostCallbackFunctions(int index)
{
	return GetEnableExternalOutputCallbackFunctions(index);
}
/// Set Input CallbackInterfaceControl of Self_Task_Object with given callbackinterface control
bool MUSiiCTaskAbstract::SetSelfTaskOutputCallbackInterfaceControl(igtl::MUSiiCCallbackInterfaceControl::Pointer pCallbackIFControl)
{
	if(m_pSelfMUSiiCTaskObject.IsNotNull())
		return m_pSelfMUSiiCTaskObject->SetOutputCallbackInterfaceControl(pCallbackIFControl);
	return false;
}

bool MUSiiCTaskAbstract::SetSelfTaskPostCallbackInterfaceControl(igtl::MUSiiCCallbackInterfaceControl::Pointer pCallbackIFControl)
{
	return SetSelfTaskOutputCallbackInterfaceControl(pCallbackIFControl);
}
/// Get Input CallbackInterfaceControl of Self_Task_Object 
igtl::MUSiiCCallbackInterfaceControl::Pointer MUSiiCTaskAbstract::GetSelfTaskOutputCallbackInterfaceControl()
{
	if(m_pSelfMUSiiCTaskObject.IsNotNull())
		return m_pSelfMUSiiCTaskObject->GetOutputCallbackInterfaceControl();
	return NULL;
}

igtl::MUSiiCCallbackInterfaceControl::Pointer MUSiiCTaskAbstract::GetSelfTaskPostCallbackInterfaceControl()
{
	return GetSelfTaskOutputCallbackInterfaceControl();
}
	
/******************************************************************************/
/// Declare a function that is called MUSiiCCallbackInterface

/// Get Callback interface of MUSiiCTackObject
igtl::MUSiiCCallbackInterface::Pointer MUSiiCTaskAbstract::GetTaskObjectPreSlefCallBackInterface(int index)
{
	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT )
	{
		if (index == M_SELFTASKOBJECT || index == 0)
			return m_vMUSiiCTaskObjects[0]->GetPreSlefCallBackInterface();
		else
			return m_vMUSiiCTaskObjects[index]->GetPreSlefCallBackInterface();
	}
	else
		return NULL;
}


/// Get Callback interface of MUSiiCTackObject
igtl::MUSiiCCallbackInterface::Pointer MUSiiCTaskAbstract::GetTaskObjecPostSlefCallBackInterface(int index)
{
	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT )
	{
		if (index == M_SELFTASKOBJECT || index == 0)
			return m_vMUSiiCTaskObjects[0]->GetPostSlefCallBackInterface();
		else
			return m_vMUSiiCTaskObjects[index]->GetPostSlefCallBackInterface();
	}
	else
		return NULL;
}


//// Get the pointer of Pre_SelfCallbackInterface of MUSiiCTaskObject
igtl::MUSiiCCallbackInterface::Pointer MUSiiCTaskAbstract::GetPreSlefCallBackInterface()
{
	return m_pPreSlefCallBackInterface.IsNotNull()? m_pPreSlefCallBackInterface:NULL;
}

//// Get the pointer of Post_SelfCallbackInterface of MUSiiCTaskObject
igtl::MUSiiCCallbackInterface::Pointer MUSiiCTaskAbstract::GetPostSlefCallBackInterface()
{
	return m_pPostSlefCallBackInterface.IsNotNull()? m_pPostSlefCallBackInterface:NULL;
}

//// User defined Callback function
/// Declare a function that is called MUSiiCCallbackInterface
int MUSiiCTaskAbstract::PreCallback(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	if(m_bDebug && ptr != NULL)
	{
		MUSiiCTaskAbstract* pTask = (MUSiiCTaskAbstract*) ptr;
		std::cout << "MUSiiCTaskAbstract::PreCallback' of " << this->GetNameOfMUSiiCClass().c_str() << std::endl;
		std::cout << "Triggered by " << pTask->GetNameOfMUSiiCClass().c_str() << std::endl;
	}
	return 1;
}

//// User defined Callback function
/// Declare a function that is called MUSiiCCallbackInterface
int MUSiiCTaskAbstract::PostCallback(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	if(m_bDebug && ptr != NULL)
	{
		MUSiiCTaskAbstract* pTask = (MUSiiCTaskAbstract*) ptr;
		std::cout << "MUSiiCTaskAbstract::PostCallback' of " << this->GetNameOfMUSiiCClass().c_str() << std::endl;
		std::cout << "Triggered by " << pTask->GetNameOfMUSiiCClass().c_str() << std::endl;
	}
	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////
/// Get Pre-CallbackInterfaceControl of TaskObject
igtl::MUSiiCCallbackInterfaceControl::Pointer MUSiiCTaskAbstract::GetPreCallbackInterfaceControlOfMUSiiCTaskObject(int index)
{
	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT )
	{
		if (index == M_SELFTASKOBJECT || index == 0)
			return m_vMUSiiCTaskObjects[0]->GetInputCallbackInterfaceControl();
		else
			return m_vMUSiiCTaskObjects[index]->GetInputCallbackInterfaceControl();
	}
	else
		return NULL;
}

	/// Get Pre-CallbackInterfaceControl of TaskObject
igtl::MUSiiCCallbackInterfaceControl::Pointer MUSiiCTaskAbstract::GetPostCallbackInterfaceControlOfMUSiiCTaskObject(int index)
{
	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT )
	{
		if (index == M_SELFTASKOBJECT || index == 0)
			return m_vMUSiiCTaskObjects[0]->GetOutputCallbackInterfaceControl();
		else
			return m_vMUSiiCTaskObjects[index]->GetOutputCallbackInterfaceControl();
	}
	else
		return NULL;
}

/// Set Pre-CallbackInterfaceControl of TaskObject with the given CallbackInterface Control
bool MUSiiCTaskAbstract::SetPreCallbackInterfaceControlOfMUSiiCTaskObject(igtl::MUSiiCCallbackInterfaceControl::Pointer callIFControl,int index)
{
	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT )
	{
		if (index == M_SELFTASKOBJECT || index == 0)
			return m_vMUSiiCTaskObjects[0]->SetInputCallbackInterfaceControl(callIFControl);
		else
			return m_vMUSiiCTaskObjects[index]->SetInputCallbackInterfaceControl(callIFControl);
	}
	else
		return NULL;
}

/// Set Pre-CallbackInterfaceControl of TaskObject with the given CallbackInterface Control
bool MUSiiCTaskAbstract::SetPostCallbackInterfaceControlOfMUSiiCTaskObject(igtl::MUSiiCCallbackInterfaceControl::Pointer callIFControl, int index)
{
	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT )
	{
		if (index == M_SELFTASKOBJECT || index == 0)
			return m_vMUSiiCTaskObjects[0]->SetOutputCallbackInterfaceControl(callIFControl);
		else
			return m_vMUSiiCTaskObjects[index]->SetOutputCallbackInterfaceControl(callIFControl);
	}
	else
		return NULL;
}

/******************************************************************************/
/************************** Task Function *************************************/
/// Run the task funtion with/without thread
//// Add Task Object
int MUSiiCTaskAbstract::AddTaskObject(igtl::MUSiiCTaskObject::Pointer pTaskObject)
{
	if(pTaskObject.IsNull())
		return 0;

	m_vMUSiiCTaskObjects.push_back(pTaskObject);
	return m_vMUSiiCTaskObjects.size();
}

/// Get the number of Task Object
int MUSiiCTaskAbstract::GetNumOfTaskObject()
{
	return m_vMUSiiCTaskObjects.size();
}

//// Clear Task Object List
int MUSiiCTaskAbstract::ClearTaskObject(igtl::MUSiiCTaskObject::Pointer pTaskObject)
{
	m_vMUSiiCTaskObjects.clear();
	return m_vMUSiiCTaskObjects.size();
}

//// Remove Task Object 
int MUSiiCTaskAbstract::RemoveTaskObject(int index)
{
	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT || index == M_ALLTASKOBJECT)
	{
		if (index == M_SELFTASKOBJECT || index == 0)
			m_vMUSiiCTaskObjects.erase(m_vMUSiiCTaskObjects.begin()+0);//
		else
			m_vMUSiiCTaskObjects.erase(m_vMUSiiCTaskObjects.begin()+index);

		return m_vMUSiiCTaskObjects.size();
	}
	else
		return 0;
}

/// Get the pointer of Task object.
igtl::MUSiiCTaskObject::Pointer MUSiiCTaskAbstract::GetTaskObject(int index)
{
	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT || index == M_ALLTASKOBJECT)
	{
		if (index == M_SELFTASKOBJECT || index == 0)
			return m_vMUSiiCTaskObjects[0];
		else
			return m_vMUSiiCTaskObjects[index];
	}
	else
		return NULL;
}



int MUSiiCTaskAbstract::RunTask(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3, int index)
{
	int r(0);

	int sz(m_vMUSiiCTaskObjects.size());
	
	m_iTaskStatus =  M_TAKS_RUNNING;

    m_bTaskThread = m_bEnableThread;//

	if(index < sz || index == M_SELFTASKOBJECT || index == M_ALLTASKOBJECT)
	{
		if(index == M_ALLTASKOBJECT)
		{
			for(int i=0; i<sz; i++)
				r += m_vMUSiiCTaskObjects[i]->RunTask(numOfRun, taskInfo, ptr, data1, data2, data3);
		}
		else if (index == M_SELFTASKOBJECT || index == 0)
		{
			r = m_vMUSiiCTaskObjects[0]->RunTask(numOfRun, taskInfo, ptr, data1, data2, data3);
		}
		else
			r = m_vMUSiiCTaskObjects[index]->RunTask(numOfRun, taskInfo, ptr, data1, data2, data3);
	}

	return r;
}
/// Stop the task thread
void MUSiiCTaskAbstract::StopTask(int index)
{	
	int sz(m_vMUSiiCTaskObjects.size());

	m_bTaskThread = false;
	
	if(index < sz || index == M_SELFTASKOBJECT || index == M_ALLTASKOBJECT)
	{
		if(index == M_ALLTASKOBJECT)
		{
			for(int i=0; i<sz; i++)
			{
				m_vMUSiiCTaskObjects[i]->StopTask();
				if(m_bDebug)
					std::cout << i << "-th task is terminated" <<std::endl;
			}
		}
		else if (index == M_SELFTASKOBJECT || index == 0)
		{
			m_vMUSiiCTaskObjects[0]->StopTask();
		}
		else
			m_vMUSiiCTaskObjects[index]->StopTask();
	}

	m_iTaskStatus =  M_TASK_STOPPED;
}

/// Wiat for the task thread
void MUSiiCTaskAbstract::WaitTask(int index)
{
	int sz(m_vMUSiiCTaskObjects.size());
	m_iTaskStatus =  M_TAKS_WAITTING;
	
	if(index < sz || index == M_SELFTASKOBJECT || index == M_ALLTASKOBJECT)
	{
		if(index == M_ALLTASKOBJECT)
		{
			for(int i=0; i<sz; i++)
				m_vMUSiiCTaskObjects[i]->WaitTask();
		}
		else if (index == M_SELFTASKOBJECT || index == 0)
		{
			m_vMUSiiCTaskObjects[0]->WaitTask();
		}
		else
			m_vMUSiiCTaskObjects[index]->WaitTask();
	}
}

/// Getting the index of current thread
int MUSiiCTaskAbstract::GetThreadIdx(int index) 
{
	int r(0);

	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT || index == M_ALLTASKOBJECT)
	{
		if (index == M_SELFTASKOBJECT || index == 0)
		{
			r = m_vMUSiiCTaskObjects[0]->GetThreadIdx();
		}
		else
			r = m_vMUSiiCTaskObjects[index]->GetThreadIdx();
	}

	return r;
}

/// ????? Do we need this function?
bool MUSiiCTaskAbstract::SetTaskMutexPointer(SimpleMutexLock* mutex, int index)
{
	bool r(true);

	int sz(m_vMUSiiCTaskObjects.size());

	if(index < sz || index == M_SELFTASKOBJECT || index == M_ALLTASKOBJECT)
	{
		if(index == M_ALLTASKOBJECT)
		{
			for(int i=0; i<sz; i++)
				r &= m_vMUSiiCTaskObjects[i]->SetTaskMutexPointer(mutex);
		}
		else if (index == M_SELFTASKOBJECT || index == 0)
		{
			r = m_vMUSiiCTaskObjects[0]->SetTaskMutexPointer(mutex);
		}
		else
			r = m_vMUSiiCTaskObjects[index]->SetTaskMutexPointer(mutex);
	}

	return r;
}

/////
void MUSiiCTaskAbstract::SetEnableDebug(bool enable)
{
	m_bDebug = enable;

	int sz(m_vMUSiiCTaskObjects.size());
	for(int i=0; i<sz; i++)
		m_vMUSiiCTaskObjects[i]->SetEnableDebug(m_bDebug);

}

/******************************************************************************/
/************************** Connect MUSiiCTask ********************************/

/// Add an object of MUSiiCTaskAbstract as Pre-Task
bool MUSiiCTaskAbstract::AddPreMUSiiCTask(igtl::MUSiiCTaskAbstract::Pointer pre_task)
{

	if(pre_task.IsNotNull())
	{
		int r1(0), r2(0);
		r1 = pre_task->AddOutputCallbackInterface(this->GetPreSlefCallBackInterface());
		r2 = this->AddInputCallbackInterface(this->GetPostSlefCallBackInterface());
		
		return r1*r2>-1?true:false;
	}
	return false;
}

/// Remove an object of MUSiiCTaskAbstract as Pre-Task
bool MUSiiCTaskAbstract::RemovePreMUSiiCTask(igtl::MUSiiCTaskAbstract::Pointer pre_task)
{

	if(pre_task.IsNotNull())
	{
		int r1(0), r2(0);
		r1 = pre_task->RemoveOutputCallbackInterface(this->GetPreSlefCallBackInterface());
		r2 = this->RemoveInputCallbackInterface(this->GetPostSlefCallBackInterface());
		
		return r1*r2>-1?true:false;
	}
	return false;
}


/// Add an object of MUSiiCTaskAbstract as Post-Task
bool MUSiiCTaskAbstract::AddPostMUSiiCTask(igtl::MUSiiCTaskAbstract::Pointer post_task)
{
	//std::cout << "MUSiiCTaskAbstract::AddPostMUSiiCTask "<<std::endl;

	if(post_task.IsNotNull())
	{
		int r1(0), r2(0);
		r1 = this->AddOutputCallbackInterface(post_task->GetPreSlefCallBackInterface());
		r2 = post_task->AddInputCallbackInterface(this->GetPostSlefCallBackInterface());
		return r1*r2>-1?true:false;
	}
	return false;
}


/// Remove an object of MUSiiCTaskAbstract as Pre-Task
bool MUSiiCTaskAbstract::RemovePostMUSiiCTask(igtl::MUSiiCTaskAbstract::Pointer post_task)
{
	if(post_task.IsNotNull())
	{
		int r1(0), r2(0);
		r1 = this->RemoveOutputCallbackInterface(post_task->GetPreSlefCallBackInterface());
		r2 = post_task->RemoveInputCallbackInterface(this->GetPostSlefCallBackInterface());
		
		return r1*r2>0?true:false;
	}
	return false;
}


/************************** Connect MUSiiCTask ********************************/
/******************************************************************************/
	
///protected: /// Methods
/// Initialize Member variables
void MUSiiCTaskAbstract::Initialize()
{
		
	m_pFastMutex                            = igtl::FastMutexLock::New();

	m_bEnableThread                         = false;
	m_bTaskThread                           = false;

	m_pMutex                                = NULL;
	m_bIsMutex                              = false;

	m_bDebug                                = false;

	m_bEnableExternalInputCallbackFuntions  = false;
	m_bEnableExternalOutputCallbackFuntions = false;

	m_iTaskStatus							= M_TASK_STOPPED;


	/// Self Task Object
	m_pSelfMUSiiCTaskObject = igtl::MUSiiCTaskObject::New();
	m_pSelfMUSiiCTaskObject->AddExternalLocalTaskFunction(this, &MUSiiCTaskAbstract::PreTaskFunction, "MUSiiCTaskAbstract_TaskFunction"); 
	m_vMUSiiCTaskObjects.push_back(m_pSelfMUSiiCTaskObject);
	//////////////////////////////////////////////////
	m_bSelfTaskFunction      = true;

	/// Self Callback Interface
	std::string str("_Pre_Callback");
	m_sNameOfPreSelfCallbackInterface = GetNameOfMUSiiCClass() + str;
	m_pPreSlefCallBackInterface= 
		igtl::CreateLocalCallbackInterface(this,&MUSiiCTaskAbstract::PreNotified, m_sNameOfPreSelfCallbackInterface);

	str = "_Post_Callback";
	m_sNameOfPostSelfCallbackInterface = GetNameOfMUSiiCClass() + str;
	m_pPostSlefCallBackInterface= 
		igtl::CreateLocalCallbackInterface(this,&MUSiiCTaskAbstract::PostNotified, m_sNameOfPostSelfCallbackInterface);
	//////////////////////////////////////////////////

}


int MUSiiCTaskAbstract::PreTaskFunction(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	int r(0);
	if(m_bSelfTaskFunction) //default value of this variable is "TRUE"
		r = TaskFunction(numOfRun, taskInfo,ptr,data1, data2, data3);
		
	return r;
}	


/// The user-defined task function.
/// You can make your own taskfunction by making subclass of MUSiiCAbstract
int MUSiiCTaskAbstract::TaskFunction(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	int r(0);
	return r;
}

/// Declare a function that is called MUSiiCCallbackInterface
/// This function will be called by Pre-MUSiiCTaskAbstract
int MUSiiCTaskAbstract::PreNotified(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	int r(-1);
	m_pFastMutex->Lock();
	r = PreCallback(numOfRun, taskInfo, ptr, data1, data2, data3);
	m_pFastMutex->Unlock();
	return r;
}


/// Declare a function that is called MUSiiCCallbackInterface
/// This function will be called by Post-MUSiiCTaskAbstract
int MUSiiCTaskAbstract::PostNotified(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	int r(-1);
	m_pFastMutex->Lock();
	r = PostCallback(numOfRun, taskInfo, ptr, data1, data2, data3);
	m_pFastMutex->Unlock();
	return r;
}

};

