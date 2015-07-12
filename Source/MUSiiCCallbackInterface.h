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
/****************************************************************************

MusiicTaskAbstract:: This class is basic thread control for MusiicTask*****

***************************************************************************/

#ifndef MUSIICCALLBACKINTERFACE_H
#define MUSIICCALLBACKINTERFACE_H

#include <igtlMacro.h>
#include <igtlLightObject.h>
#include <igtlObjectFactory.h>
#include <string>
#include <igtlMessageBase.h>
//#if defined(WIN32) || defined (_WIN32) || defined (__WIN32__)
#include "igtlM_win32header.h"
//#endif
//
//#include "MUSiiCUtil.h"
namespace igtl
{
/// Define Musiic Task function with Global function.
/// In General, 
/// numOfRun : How many iteration or how many times of this taskfuntion
/// TaskInfo : The argument of this task
/// ptr      : the pointer of caller class
/// data1    : Data (igtlMessage)
/// data2    : the Time-stamp of the data
/// data3    : the name of Data
//typedef int(*MusiicTaskFtn) (int, int, void*, void*, void*, void*);
	typedef int(*MusiicTaskFtn) (int, int, void*, igtl::MessageBase::Pointer, void*, void*); // cannon96: second version of CallbackInterface

class IGTLMCommon_EXPORT MUSiiCCallbackInterface : public LightObject
{
public: ///Operations
	typedef MUSiiCCallbackInterface					Self;
	typedef LightObject								Superclass;
	typedef SmartPointer<Self>						Pointer;
	typedef SmartPointer<Self>						ConstPointer;
	
	/** Method for creation through the object factory. */
	igtlNewMacro(MUSiiCCallbackInterface);
  
	/** Run-time type information (and related methods). */
	igtlTypeMacro(MUSiiCCallbackInterface, LightObject);

public: //Operations
    /// Constructor
    MUSiiCCallbackInterface();

    /// Deconstructor
    ~MUSiiCCallbackInterface();

    /// Virtual function to call predefined callback function
    /// In General, 
	/// numOfRun : How many iteration or how many times of this taskfuntion
	/// TaskInfo : The argument of this task
	/// ptr      : the pointer of caller class
	/// data1    : Data (igtlMessage)
	/// data2    : the Time-stamp of the data
	/// data3    : the name of Data
	virtual int Notify(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

    /// Check there is callback-fucntion or not.
    bool IsCallBackFunction();

	/// Check this interface is for Global Function or not.
	bool IsGlobalCallBackFunction();

	/// Set this callback interface with enable or not
	void SetEnable(bool active = true);

	/// Check the enability of this callback interface.
	bool GetEnable();

	/// Set a Return value
	void SetReturnValue(int returnvalue);

	/// Get the Return value
	int GetReturnValue();

	/// Get the name of funtion
	std::string GetName();

	/// set Name
	void SetName(std::string name);

public: //Attributes

protected: /// attributes
    /// An boolean variable of callbackfunction
    bool			m_bIsCallBackFunction;
	bool			m_bGlobalFunction;

	/// Control callback Interface
	std::string		m_strFunctionName;
	bool			m_bActive;
	int				m_iReturnValue;
};

/*****************************************************************************************/
class IGTLMCommon_EXPORT MUSiiCGlobalCallbackInterface : public MUSiiCCallbackInterface
{
public: ///Operations
	typedef MUSiiCGlobalCallbackInterface					Self;
	typedef MUSiiCCallbackInterface							Superclass;
	typedef SmartPointer<Self>								Pointer;
	typedef SmartPointer<Self>								ConstPointer;
	
	/** Method for creation through the object factory. */
	igtlNewMacro(Self);
  
	/** Run-time type information (and related methods). */
	igtlTypeMacro(Self, Superclass);
public:
    /// Constructor
    MUSiiCGlobalCallbackInterface();

    /// Deconstructor
    ~MUSiiCGlobalCallbackInterface();

	/// Setting a Global function as callback interface 
	bool SetGlobalFunction(MusiicTaskFtn fun, std::string name = "");

    /// Virtual function to call predefined callback function
	/// In General, 
	/// numOfRun : How many iteration or how many times of this taskfuntion
	/// TaskInfo : The argument of this task
	/// ptr      : the pointer of caller class
	/// data1    : Data (igtlMessage)
	/// data2    : the Time-stamp of the data
	/// data3    : the name of Data
    virtual int Notify(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

protected: /// attributes
    /// An boolean variable of callbackfunction
	MusiicTaskFtn	m_gFun;

};

/*****************************************************************************************/
template<class ObjType, typename funType> class MUSiiCLocalCallbackInterface: public MUSiiCCallbackInterface
{
public: ///Operations
	typedef MUSiiCLocalCallbackInterface<ObjType, funType>	Self;
	typedef MUSiiCCallbackInterface							Superclass;
	typedef SmartPointer<Self>								Pointer;
	typedef SmartPointer<Self>								ConstPointer;
	
	/** Method for creation through the object factory. */
	igtlNewMacro(Self);
        //igtlNewMacro(MUSiiCLocalCallbackInterface);
 
  
	/** Run-time type information (and related methods). */
	igtlTypeMacro(Self, Superclass);
//        igtlTypeMacro(MUSiiCLocalCallbackInterface, Superclass);

public: ///operations
    MUSiiCLocalCallbackInterface()
	{
		m_obj = NULL;
		m_fun = NULL;
		m_bIsCallBackFunction = false;
		m_bGlobalFunction	  = false;

		m_strFunctionName		= "";
		m_bActive				= true;
		m_iReturnValue			= -1;
	}

    ///Deconstructor
    ~MUSiiCLocalCallbackInterface()
    {
    }

	/// Set Function
	bool SetLocalFunction(ObjType obj, funType fun, std::string name = "")
	{
		m_bIsCallBackFunction = false;
		
		if(obj != NULL && fun != NULL)
		{
			m_obj					= obj;
			m_fun					= fun;
			m_bIsCallBackFunction	= true;
			
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
	/// data1    : Data 
	/// data2    : the Time-stamp of the data
	/// data3    : the name of Data
    virtual int Notify(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
    {
        int r(-1);
		if(m_bIsCallBackFunction && m_bActive)
			r = (m_obj->*m_fun)(numOfRun, taskInfo, ptr, data1, data2, data3);
        return r;
    }

    ObjType GetPaterent(){return m_obj;}


protected: /// attributes
    ObjType    m_obj;
    funType    m_fun;
};
//
/////Global function for creating the pointer of callback interface
template<class ObjType, typename funType> inline igtl::MUSiiCCallbackInterface::Pointer IGTLMCommon_EXPORT CreateLocalCallbackInterface(ObjType obj, funType fun, std::string name = "" )
{
	SmartPointer<igtl::MUSiiCLocalCallbackInterface<ObjType, funType> > callback;
	callback  = igtl::MUSiiCLocalCallbackInterface<ObjType, funType>::New();

	if(callback->SetLocalFunction(obj, fun, name))
		return static_cast< igtl::MUSiiCCallbackInterface::Pointer >(callback);
	else
		return NULL;
}

///Global function for creating the pointer of callback interface
//extern "C" igtl::MUSiiCCallbackInterface::Pointer IGTLCommon_EXPORT CreateGlobalCallbackInterface(MusiicTaskFtn fun,std::string name = "");
inline igtl::MUSiiCCallbackInterface::Pointer IGTLMCommon_EXPORT CreateGlobalCallbackInterface(MusiicTaskFtn fun,std::string name = "")
{
	igtl::MUSiiCGlobalCallbackInterface::Pointer callback =
		igtl::MUSiiCGlobalCallbackInterface::New();

	if(callback->SetGlobalFunction(fun, name))
		return static_cast< igtl::MUSiiCCallbackInterface::Pointer >(callback);
	else
		return NULL;
}
/// Global function for creating the pointer of TaskInterface interface
template<class ObjType, typename funType> 
inline igtl::MUSiiCCallbackInterface::Pointer IGTLMCommon_EXPORT CreateExternalLocalTask(ObjType obj, funType fun, std::string name = "")
{
	return CreateLocalCallbackInterface(obj, fun, name);
}

///Global function for creating the pointer of TaskInterface interface
//extern "C" igtl::MUSiiCCallbackInterface::Pointer IGTLCommon_EXPORT CreateExternalGlobalTask(MusiicTaskFtn fun, std::string name = "");
inline igtl::MUSiiCCallbackInterface::Pointer IGTLMCommon_EXPORT CreateExternalGlobalTask(MusiicTaskFtn fun, std::string name = "")
{
	return CreateGlobalCallbackInterface(fun, name);
}

} //end of namespace


#endif // MUSIICCALLBACKINTERFACE_H
