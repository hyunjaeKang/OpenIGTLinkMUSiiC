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

#ifndef MUSIICINTERFACE_CONTROL
#define MUSIICINTERFACE_CONTROL

#include <vector>
#include "MUSiiCCallbackInterface.h"

namespace igtl
{

class IGTLMCommon_EXPORT MUSiiCCallbackInterfaceControl: public LightObject
{
public: ///Operations
	typedef MUSiiCCallbackInterfaceControl			Self;
	typedef LightObject								Superclass;
	typedef SmartPointer<Self>						Pointer;
	typedef SmartPointer<Self>						ConstPointer;
	
	/** Method for creation through the object factory. */
	igtlNewMacro(Self);
  
	/** Run-time type information (and related methods). */
	igtlTypeMacro(Self, Superclass);
	
public: /// Operations
	/// Constructor
	MUSiiCCallbackInterfaceControl();
	
	/// Deconstructor
	~MUSiiCCallbackInterfaceControl();
	
	/********************************************************************************/
	/********************************************************************************/
	
	/***** Add Task Function ***********/
	//// Add  Global Task Function
	int AddExternalGlobalFunction(MusiicTaskFtn fun, std::string name = "");
	
	//// Add Local Task-function 
	template<class ObjType, typename funType> 
	inline int AddExternalLocalFunction(ObjType obj, funType fun, std::string name = "")
	{
		return AddInterface(CreateLocalIF(obj, fun, name), m_ExternalInterface);
	}

	/// Add MUSiiCCallback Interface
	int AddExternalInterface(igtl::MUSiiCCallbackInterface::Pointer task);

	/// ************** New
	/// Remove MUSiiCCallback Interface
	/// Return value is the size of the container of CallbackInterfaceControl
	/// If the return value is less than zero(0), this means the error of this function
	int RemoveExternalInterface(igtl::MUSiiCCallbackInterface::Pointer task);
	
	/***** Get Info Task Functions ***********/
	/// Get the number of External Task Functions
	int GetNumOfExternalInterfaces();

	/// Get the ID of a specific external task interface using it's name
	int GetIDOfExternalInterface(std::string name);

	/// Get the name of a specific external task interface using it's ID
	std::string GetNameOfExternalInterface(int id);
	
	/// GetEnable
	/// Check the enability of a task interface with it's ID.
	bool GetEnableExternalInterfaceID(int id);

	/// Check the enability of a task interface with it's name
	bool GetEnableExternalInterfaceName(std::string name);

	/// Get the return value of a task interface with its ID
	int GetRetunValueOfExternalInterfaceID(int id);

	/// Get the return value of a task interface with its Name
	int GetRetunValueOfExternalInterfaceName(std::string name);

	/// Get the list of external task functions by itself
	std::vector<igtl::MUSiiCCallbackInterface::Pointer>& GetExternalTaskList();

	/***** Set Task Functions ************/
	
	/// Set all task interface with enable or not
	void SetEnableAllExternalInterfaces(bool enable = true);

	/// Set one task interface with enable or not with it's ID
	bool SetEnableExternalInterfaceID(int id, bool enable = true);
	
	/// Set one task interface with enable or not with it's name
	bool SetEnableExternalInterfaceName(std::string name, bool enable= true);
	
	/// Set some task interfaces with enable or not with it's ID-List
	int SetEnableSomeExternalInterfaceIDs(std::vector<int>& idxs, bool enable = true);

	/// Set some task interfaces with enable or not with it's Name-List
	int SetEnableSomeExternalInterfaceNames(std::vector<std::string>& names, bool enable = true);
	
	/***** Call Task Functions ***********/
	
	/// Call All external Functions
	int CallAllExternalInterfaces(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	/// Call All external Functions excluding one function with a ID
	int CallAllExternalInterfacesExcludeID(int id, int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	/// Call All external Functions excluding one function with a name
	int CallAllExternalInterfacesExcludeName(std::string name, int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	/// Call All external Functions excluding some functions with their ids
	int CallAllExternalInterfacesExcludeIDs(std::vector<int>& ids, int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	/// Call All external Functions excluding some functions with their names
	int CallAllExternalInterfacesExcludeNames(std::vector<std::string>& names, int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);


	/// Call one external task function with the ID
	int CallOneExternalInterfaceID(int id, int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);
	
	/// Call One external task function with the name
	int CallOneExternalInterfaceName(std::string name, 
		int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	/// Call Some external Task function with ID-List
	int CallSomeExternalInterfacesIDs(std::vector<int>& idxs, 
		int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	/// Call Some external Task function with Name-List
	int CallSomeExternalInterfacesNames(std::vector<std::string>& names, 
		int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);
protected: ///Operations

	//// Create Global callback interface
	igtl::MUSiiCCallbackInterface::Pointer CreateGlobalIF(MusiicTaskFtn fun, std::string name = "");
	

	/// Create Local callback interface
	template<class ObjType, typename funType> 
	inline igtl::MUSiiCCallbackInterface::Pointer CreateLocalIF(ObjType obj, funType fun, std::string name = "")
	{
		igtl::MUSiiCCallbackInterface::Pointer IF;
		IF = CreateLocalCallbackInterface(obj, fun, name);
		return IF;
	}
	
	
	/// Add MUSiiCCallbackInterace to a specific container
	/// Return value is the ID of new interface
	int AddInterface(igtl::MUSiiCCallbackInterface::Pointer cb, 
		std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container);

	/// ************** New
	/// Remove MUSiiCCallbackInterace to a specific container
	/// Return value is the size of container
	/// If the return value is less than zero, this means the error of this function.
	int RemoveInterface(igtl::MUSiiCCallbackInterface::Pointer cb, 
														std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container);

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//// Find the ID of the interface that has a specific name
	int FindID(std::string name, std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container);

	/// Find the function name of the interface that has a specific ID
	std::string FindName(int id, std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container);
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Call One-Interface with the ID
	int CallOneIF(int idx, std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container,
				int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	//// Call callbackInterface with ID-List
	int CallIF(std::vector<int>& IF_ID_List, std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container,
				int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	//// Call All Interface
	int CallALLIF(std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container,
				int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	/// GetEnable
	bool GetEnable(int idx, std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container);

	/// Get the return value of external function with it's ID
	int GetReturnValue(int idx, std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container);

	/// check the index number
	bool CheckID(int idx, std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container);

	/// Set a specific function with enable or disable
	bool SetEnable(int idx, bool enable, std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container);

	/// Set all functions with enable or disable
	void SetEnableAll(bool enable, std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container);

	int SetEnableSome(std::vector<int>& IF_ID_List, bool enable, std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container);

public: /// Attributes

protected: /// Attributes
	std::vector<igtl::MUSiiCCallbackInterface::Pointer> m_ExternalInterface;
};

};
#endif
