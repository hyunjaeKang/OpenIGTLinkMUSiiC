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

#include "MUSiiCCallbackInterfaceControl.h"
//#include "MUSiiCGlobalFuntion.cxx"

namespace igtl
{

/// Constructor
MUSiiCCallbackInterfaceControl::MUSiiCCallbackInterfaceControl()
{
	m_ExternalInterface.clear();
}
	
/// Deconstructor
MUSiiCCallbackInterfaceControl::~MUSiiCCallbackInterfaceControl()
{
	m_ExternalInterface.clear();
}
	
/********************************************************************************/
/********************************************************************************/
	
/***** Add Task Function ***********/
//// Add  Global Task Function
int MUSiiCCallbackInterfaceControl::AddExternalGlobalFunction(MusiicTaskFtn fun, std::string name)
{
	return AddInterface(CreateGlobalIF(fun, name), m_ExternalInterface);
}
	
//// Add Local Task-function 
//template<class ObjType, typename funType> 
//int MUSiiCCallbackInterfaceControl::AddExternalLocalFunction(ObjType obj, funType fun, std::string name)
//{
//	return AddInterface(CreateLocalIF(obj, fun, name), m_ExternalInterface);
//}

/// Add MUSiiCCallback Interface
int MUSiiCCallbackInterfaceControl::AddExternalInterface(igtl::MUSiiCCallbackInterface::Pointer task)
{
	return AddInterface(task, m_ExternalInterface);
}

/// ************** New
/// Remove MUSiiCCallback Interface
/// Return value is the size of the container of CallbackInterfaceControl
/// If the return value is less than zero(0), this means the error of this function
int MUSiiCCallbackInterfaceControl::RemoveExternalInterface(igtl::MUSiiCCallbackInterface::Pointer task)
{
	return RemoveInterface(task, m_ExternalInterface);
}
	
/***** Get Info Task Functions ***********/
/// Get the number of External Task Functions
int MUSiiCCallbackInterfaceControl::GetNumOfExternalInterfaces()
{ 
	return m_ExternalInterface.size();
}

/// Get the ID of a specific external task interface using it's name
int MUSiiCCallbackInterfaceControl::GetIDOfExternalInterface(std::string name)
{
	return FindID(name, m_ExternalInterface);
}

/// Get the name of a specific external task interface using it's ID
std::string MUSiiCCallbackInterfaceControl::GetNameOfExternalInterface(int id)
{
	return FindName(id, m_ExternalInterface);
}
	
/// GetEnable
/// Check the enability of a task interface with it's ID.
bool MUSiiCCallbackInterfaceControl::GetEnableExternalInterfaceID(int id)
{
	return GetEnable(id,m_ExternalInterface);
}

/// Check the enability of a task interface with it's name
bool MUSiiCCallbackInterfaceControl::GetEnableExternalInterfaceName(std::string name)
{
	return GetEnableExternalInterfaceID(GetIDOfExternalInterface(name));
}
/// Get the return value of a task interface with its ID
int MUSiiCCallbackInterfaceControl::GetRetunValueOfExternalInterfaceID(int id)
{
	return GetReturnValue(id,m_ExternalInterface); 
}
/// Get the return value of a task interface with its Name
int MUSiiCCallbackInterfaceControl::GetRetunValueOfExternalInterfaceName(std::string name)
{
	return GetRetunValueOfExternalInterfaceID(GetIDOfExternalInterface(name)); 
}
/// Get the list of external task functions by itself
std::vector<igtl::MUSiiCCallbackInterface::Pointer>& MUSiiCCallbackInterfaceControl::GetExternalTaskList()
{
	return m_ExternalInterface;
}
/***** Set Task Functions ************/
	
/// Set all task interface with enable or not
void MUSiiCCallbackInterfaceControl::SetEnableAllExternalInterfaces(bool enable)
{
	SetEnableAll(enable, m_ExternalInterface);
}

/// Set one task interface with enable or not with it's ID
bool MUSiiCCallbackInterfaceControl::SetEnableExternalInterfaceID(int id, bool enable)
{
	return SetEnable(id, enable, m_ExternalInterface);
}
	
/// Set one task interface with enable or not with it's name
bool MUSiiCCallbackInterfaceControl::SetEnableExternalInterfaceName(std::string name, bool enable)
{
	return SetEnableExternalInterfaceID(GetIDOfExternalInterface(name),enable);
}
	
/// Set some task interfaces with enable or not with it's ID-List
int MUSiiCCallbackInterfaceControl::SetEnableSomeExternalInterfaceIDs(std::vector<int>& idxs, bool enable)
{
	return SetEnableSome(idxs, enable, m_ExternalInterface);
}

/// Set some task interfaces with enable or not with it's Name-List
int MUSiiCCallbackInterfaceControl::SetEnableSomeExternalInterfaceNames(std::vector<std::string>& names, bool enable)
{
	std::vector<int> tempList;
	for(int i=0; i<(int)names.size(); i++)
		tempList.push_back(GetIDOfExternalInterface(names[i]));	

	return SetEnableSome(tempList, enable, m_ExternalInterface);
}
	
/***** Call Task Functions ***********/
	
/// Call All external Functions
int MUSiiCCallbackInterfaceControl::CallAllExternalInterfaces(int numOfRun,int taskInfo,void* ptr,igtl::MessageBase::Pointer data1,void* data2,void* data3)
{
	return CallALLIF(m_ExternalInterface, numOfRun, taskInfo, ptr, data1, data2, data3);
}

/// Call All external Functions excluding one function with a ID
int MUSiiCCallbackInterfaceControl::CallAllExternalInterfacesExcludeID(int id, int numOfRun, int taskInfo, void* ptr,igtl::MessageBase::Pointer data1,void* data2,void* data3)
{
	int r(-1);
	if(SetEnableExternalInterfaceID(id, false))
	{
		r = CallAllExternalInterfaces(numOfRun, taskInfo, ptr, data1, data2, data3);
		if(SetEnableExternalInterfaceID(id, true))
			return r;
		else
			r = -1;
	}

	return r;
}

/// Call All external Functions excluding one function with a name
int MUSiiCCallbackInterfaceControl::CallAllExternalInterfacesExcludeName(std::string name, int numOfRun, int taskInfo, void* ptr,igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	int r(-1);
	if(SetEnableExternalInterfaceName(name, false))
	{
		r = CallAllExternalInterfaces(numOfRun, taskInfo, ptr, data1, data2, data3);
		if(SetEnableExternalInterfaceName(name, true))
			return r;
		else
			r = -1;
	}

	return r;
}

/// Call All external Functions excluding some functions with their ids
int MUSiiCCallbackInterfaceControl::CallAllExternalInterfacesExcludeIDs(std::vector<int>& ids, int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	int r(-1);
	if(SetEnableSomeExternalInterfaceIDs(ids, false))
	{
		r = CallAllExternalInterfaces(numOfRun,taskInfo, ptr, data1, data2, data3);
		if(SetEnableSomeExternalInterfaceIDs(ids, true))
			return r;
		else
			r = -1;
	}

	return r;
}

/// Call All external Functions excluding some functions with their names
int MUSiiCCallbackInterfaceControl::CallAllExternalInterfacesExcludeNames(std::vector<std::string>& names, int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	int r(-1);
	if(SetEnableSomeExternalInterfaceNames(names, false))
	{
		r = CallAllExternalInterfaces(numOfRun, taskInfo, ptr, data1, data2, data3);
		if(SetEnableSomeExternalInterfaceNames(names, true))
			return r;
		else
			r = -1;
	}

	return r;
}


/// Call one external task function with the ID
int MUSiiCCallbackInterfaceControl::CallOneExternalInterfaceID(int id, 
								int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	return CallOneIF(id, m_ExternalInterface, numOfRun, taskInfo, ptr, data1, data2, data3);
}
	
/// Call One external task function with the name
int MUSiiCCallbackInterfaceControl::CallOneExternalInterfaceName(std::string name, 
	int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	return CallOneExternalInterfaceID(GetIDOfExternalInterface(name), numOfRun, taskInfo, ptr, data1, data2, data3);
}

/// Call Some external Task function with ID-List
int MUSiiCCallbackInterfaceControl::CallSomeExternalInterfacesIDs(std::vector<int>& idxs, 
	int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	return CallIF(idxs, m_ExternalInterface, numOfRun, taskInfo, ptr, data1, data2, data3);
}

/// Call Some external Task function with Name-List
int MUSiiCCallbackInterfaceControl::CallSomeExternalInterfacesNames(std::vector<std::string>& names, 
	int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	std::vector<int> tempList;
	for(int i=0; i< (int)names.size(); i++)
		tempList.push_back(GetIDOfExternalInterface(names[i]));	
		
	return CallIF(tempList, m_ExternalInterface, numOfRun, taskInfo, ptr, data1, data2, data3);
}
///protected: ///Operations

//// Create Global callback interface
igtl::MUSiiCCallbackInterface::Pointer MUSiiCCallbackInterfaceControl::CreateGlobalIF(MusiicTaskFtn fun, std::string name)
{
	igtl::MUSiiCCallbackInterface::Pointer IF;
	IF = igtl::CreateGlobalCallbackInterface(fun, name);
	return IF;
}
	

/// Create Local callback interface
//template<class ObjType, typename funType> 
//igtl::MUSiiCCallbackInterface::Pointer MUSiiCCallbackInterfaceControl::CreateLocalIF(ObjType obj, funType fun, std::string name)
//{
//	igtl::MUSiiCCallbackInterface::Pointer IF;
//	IF = CreateLocalCallbackInterface(obj, fun, name);
//	return IF;
//}
	
	
/// Add MUSiiCCallbackInterace to a specific container
/// Return value is the ID of new interface
int MUSiiCCallbackInterfaceControl::AddInterface(igtl::MUSiiCCallbackInterface::Pointer cb, 
													std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container)
{
	int s(-1);

	if(cb.IsNotNull())
	{
		container.push_back(cb);
		s = container.size();
		///This number indicate the ID of new callback Function is added
		return s-1; 
	}
	return s;
}

/// ************** New
/// Remove MUSiiCCallbackInterace to a specific container
/// Return value is the size of container
/// If the return value is less than zero, this means the error of this function.
int MUSiiCCallbackInterfaceControl::RemoveInterface(igtl::MUSiiCCallbackInterface::Pointer cb, 
													std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container)
{
	int s(-1);

	if(cb.IsNotNull())
	{
		s = container.size();
		for(int i = 0; i<s;i++)
		{
			if(container[i] == cb)
			{
				container.erase(container.begin()+i);
				s = container.size();
				return s;
			}
		}
		///This number indicate the ID of new callback Function is added
		return -1; 
	}
	return -1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//// Find the ID of the interface that has a specific name
int MUSiiCCallbackInterfaceControl::FindID(std::string name, 
										std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container)
{
	int s = container.size();

	for(int i=0; i<s; i++)
	{
		if(name.compare(container[i]->GetName()) == 0)
			return i;
	}

	return -1;
}

/// Find the function name of the interface that has a specific ID
std::string MUSiiCCallbackInterfaceControl::FindName(int id, 
											std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container)
{
	std::string temp = "";

	if( CheckID(id, container))
		temp = container[id]->GetName();

	return temp;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
/// Call One-Interface with the ID
int MUSiiCCallbackInterfaceControl::CallOneIF(int idx, std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container,
			int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	int s1 = container.size();
	/// check the idx
	if( CheckID(idx, container))
	{
		if(container[idx]->GetEnable())
			container[idx]->SetReturnValue(container[idx]->Notify(numOfRun, taskInfo, ptr, data1, data2, data3));
		else
			container[idx]->SetReturnValue(-2);

		return 1;
	}
	else
		return 0;
}

//// Call callbackInterface with ID-List
int MUSiiCCallbackInterfaceControl::CallIF(std::vector<int>& IF_ID_List, std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container,
			int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	int s1 = container.size();
	int s2 = IF_ID_List.size();
	int r  = 0;
	/// check the size
	if(s2 <= s1)
	{
		for(int i=0; i<s2; i++)
			r+= CallOneIF(IF_ID_List[i], container, numOfRun, taskInfo, ptr, data1, data2, data3);
			
		return r;
	}
	else
		return r; 
}

//// Call All Interface
int MUSiiCCallbackInterfaceControl::CallALLIF(std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container,
			int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	int s1 = container.size();
	int r = 0;
	for(int i=0; i<s1; i++)
		r+= CallOneIF(i, container, numOfRun, taskInfo, ptr, data1, data2, data3);

	return r;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
/// GetEnable
bool MUSiiCCallbackInterfaceControl::GetEnable(int idx, std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container)
{
	if(CheckID(idx, container))
		return container[idx]->GetEnable();
	else
		return false;
}

/// Get the return value of external function with it's ID
int MUSiiCCallbackInterfaceControl::GetReturnValue(int idx, std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container)
{
	if(CheckID(idx, container))
		return container[idx]->GetReturnValue();
	else
		return -2;
}

/// check the index number
bool MUSiiCCallbackInterfaceControl::CheckID(int idx, std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container)
{
	return ( idx > -1 && idx < (int)container.size())? true : false; 
}

/// Set a specific function with enable or disable
bool MUSiiCCallbackInterfaceControl::SetEnable(int idx, bool enable, std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container)
{
	if(CheckID(idx, container))
	{
		container[idx]->SetEnable(enable);
		return true;
	}
	else
		return false;
}

/// Set all functions with enable or disable
void MUSiiCCallbackInterfaceControl::SetEnableAll(bool enable, std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container)
{
	for(int i=0; i <(int)container.size(); i++)
		container[i]->SetEnable(enable);
}

int MUSiiCCallbackInterfaceControl::SetEnableSome(std::vector<int>& IF_ID_List, bool enable, std::vector<igtl::MUSiiCCallbackInterface::Pointer>& container)
{
	int s1 = container.size();
	int s2 = IF_ID_List.size();
	int r  = 0;
	/// check the size
	if(s2 <= s1)
	{
		for(int i=0; i<s2; i++)
			if(SetEnable(IF_ID_List[i], enable, container))
				r++;
		return r;
	}
	else
		return r; 
}

}
