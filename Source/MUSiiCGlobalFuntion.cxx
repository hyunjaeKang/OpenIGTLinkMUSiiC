/**************************************************************************
# Hyun-Jae Kang, Philipp J Stolka,Emad M Boctor
# Johns Hopkins Medical Institutions
# Department of Radiology, Division of Medical Imaging Physics

# For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.
***************************************************************************/

#include "MUSiiCCallbackInterface.h"
namespace igtl
{
///Global function for creating the pointer of callback interface
template<class ObjType, typename funType> 
igtl::MUSiiCCallbackInterface::Pointer IGTLCommon_EXPORT CreateLocalCallbackInterface(ObjType obj, funType fun, std::string name)
{
	
	igtl::MUSiiCLocalCallbackInterface<ObjType, funType>::Pointer callback =
	igtl::MUSiiCLocalCallbackInterface<ObjType, funType>::New();

	
	if(callback->SetLocalFunction(obj, fun, name))
		return static_cast< igtl::MUSiiCCallbackInterface::Pointer >(callback);
	else
		return NULL;
}

///Global function for creating the pointer of callback interface
igtl::MUSiiCCallbackInterface::Pointer IGTLCommon_EXPORT CreateGlobalCallbackInterface(MusiicTaskFtn fun,std::string name)
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
igtl::MUSiiCCallbackInterface::Pointer IGTLCommon_EXPORT CreateExternalLocalTask(ObjType obj, funType fun, std::string name)
{
	return CreateLocalCallbackInterface(obj, fun, name);
}

///Global function for creating the pointer of TaskInterface interface
igtl::MUSiiCCallbackInterface::Pointer IGTLCommon_EXPORT CreateExternalGlobalTask(MusiicTaskFtn fun, std::string name)
{
	return CreateGlobalCallbackInterface(fun, name);
}
}