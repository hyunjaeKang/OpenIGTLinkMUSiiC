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

#include "MUSiiCCallbackInterface.h"
//#include "MUSiiCGlobalFuntion.cxx"

namespace igtl
{
///Constructor
MUSiiCCallbackInterface::MUSiiCCallbackInterface()
{
    m_bIsCallBackFunction	= false;
	m_bGlobalFunction		= false;

	m_strFunctionName		= "";
	m_bActive				= true;
	m_iReturnValue			= -1;
}

/// Deconstructor
MUSiiCCallbackInterface::~MUSiiCCallbackInterface()
{
}

/// Virtual function to call predefined callback function
/// In General, 
/// numOfRun : How many iteration or how many times of this taskfuntion
/// TaskInfo : The argument of this task
/// ptr      : the pointer of caller class
/// data1    : Data (igtlMessage)
/// data2    : the Time-stamp of the data
/// data3    : the name of Data
int MUSiiCCallbackInterface::Notify(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1,void* data2,void* data3)
{
	return 0;
}

/// Check there is callback-fucntion or not.
bool MUSiiCCallbackInterface::IsCallBackFunction() 
{
	return m_bIsCallBackFunction;
}

/// Check this interface is for Global Function or not.
bool MUSiiCCallbackInterface::IsGlobalCallBackFunction() 
{
	return m_bGlobalFunction;
}

/// Set this callback interface with enable or not
void MUSiiCCallbackInterface::SetEnable(bool active)
{
	m_bActive = active;
}

/// Check the enability of this callback interface.
bool MUSiiCCallbackInterface::GetEnable()
{
	return m_bActive;
}

/// Set a Return value
void MUSiiCCallbackInterface::SetReturnValue(int returnvalue)
{
	m_iReturnValue = returnvalue;
}

/// Get the Return value
int MUSiiCCallbackInterface::GetReturnValue() 
{
	return m_iReturnValue;
}

/// Get the name of funtion
std::string MUSiiCCallbackInterface::GetName() 
{
	return m_strFunctionName;
}

/// set Name
void MUSiiCCallbackInterface::SetName(std::string name) 
{
	m_strFunctionName = name;
}

/*****************************************************************************************/
///Constructor
MUSiiCGlobalCallbackInterface::MUSiiCGlobalCallbackInterface()
{
    m_bIsCallBackFunction	= false;
	m_bGlobalFunction		= false;
	m_gFun					= NULL;

	m_strFunctionName		= "";
	m_bActive				= true;
	m_iReturnValue			= -1;
}

/// Deconstructor
MUSiiCGlobalCallbackInterface::~MUSiiCGlobalCallbackInterface()
{
	if(m_gFun != NULL)
	{
		//delete m_gFun;
		m_gFun = NULL;
	}
}

/// Setting a Global function as callback interface 
bool MUSiiCGlobalCallbackInterface::SetGlobalFunction(MusiicTaskFtn fun, std::string name)
{
	m_bIsCallBackFunction = false;
		
	if(fun != NULL)
	{
		m_gFun = fun;
		m_bIsCallBackFunction = true;
		m_bGlobalFunction = true;

		m_bActive				= true;
		m_strFunctionName		= name;
		m_iReturnValue			= -1;
	}

	return m_bIsCallBackFunction;
}

/// Virtual function to call predefined callback function
/// In General, 
/// numOfRun : How many iteration or how many times of this taskfuntion
/// TaskInfo : The argument of this task
/// ptr      : the pointer of caller class
/// data1    : Data (igtlMessage)
/// data2    : the Time-stamp of the data
/// data3    : the name of Data
int MUSiiCGlobalCallbackInterface::Notify(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	int r(-1);
    if(m_bIsCallBackFunction && m_bActive)
			r = m_gFun(numOfRun, taskInfo, ptr, data1, data2, data3);
    return r;
}


/*****************************************************************************************/


} //end of namespace


