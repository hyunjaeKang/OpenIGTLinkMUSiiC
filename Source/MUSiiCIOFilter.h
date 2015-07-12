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
#ifndef __MUSIIC_IO_FILTER_
#define __MUSIIC_IO_FILTER_

#include <igtlLightObject.h>
#include <igtlMacro.h>
#include <igtlObjectFactory.h>
#include <string>
#include <map>
#include <igtlMessageBase.h>
//#if defined(WIN32) || defined (_WIN32) || defined (__WIN32__)
#include "igtlM_win32header.h"
//#endif

namespace igtl
{

class IGTLMCommon_EXPORT MUSiiCIOFilter : public LightObject
{
public: // Operations
	typedef MUSiiCIOFilter							Self;
	typedef LightObject								Superclass;
	typedef SmartPointer<Self>						Pointer;
	typedef SmartPointer<Self>						ConstPointer;
	
	/** Method for creation through the object factory. */
	igtlNewMacro(MUSiiCIOFilter);
  
	/** Run-time type information (and related methods). */
	igtlTypeMacro(MUSiiCIOFilter, LightObject);

	/// Constrcut
	MUSiiCIOFilter();
	/// Deconstruct
	~MUSiiCIOFilter();

	/// Get the name of Class
	std::string GetNameOfMUSiiCClass();

	/// Set the name of Parent class
	void SetNameOfParentMUSiiCClass(std::string pName);

	/// Get the name of Parent
	std::string GetNameOfParentMUSiiCClass();

	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	/// Reset MUSiiCIOFilter
	void ResetMUSiiCIOFilter();

	/// Set MUSiiCIOFilter using Data_Type or DeviceName
	/// return : the size of MUSiiCIOFIlter
	int SetMUSiiCIOFilter(std::string datatype, bool enable = true);

	/// Check a Datatype whether is pass or not.
	/// return value
	///        - true: We can use the data-type
	///        - false: We cannot use the data-type
	bool CheckDataType(std::string datatype);


	/// Check a Datatype whether is pass or not.
	/// return value
	///        - true: We can use the data-type
	///        - false: We cannot use the data-type
	bool CheckDataType2(std::string datatype);

	//// Check MessageBase using pre-defined IOFilter
	igtl::MessageBase::Pointer CheckMessageBase(igtl::MessageBase::Pointer msg,bool checkDevicetype = false);

	//// Check MessageBase using pre-defined IOFilter
	igtl::MessageBase::Pointer CheckMessageBase2(igtl::MessageBase::Pointer msg,bool checkDevicetype = false);

	//// Check IGTL Message using pre-defined IOFilter
	template<class P> inline P CheckIGTLMessage(P msg, bool checkDevicetype = false)
	{
		if(this->CheckDataType(msg->GetDeviceName()))
			return msg;
		else if(checkDevicetype)
			if(this->CheckDataType(msg->GetDeviceType()))
				return msg;

		return NULL;
	}

	/// Get How many data-type are defined in MUSiiCIOFilter
	int GetNumberOfDataType();

	/// Get The list of data-type 
	std::vector<std::string>& GetDataTypeList();

	/// Remove data-type from MUSiiCIOFilter
	int RemoveDataType(std::string datatype);

	/// Check the data-type is or not in MUSiiCIOFilter
	bool IsDataType(std::string datatype);

	void PrintIOFilter();
protected: // Operations
	/// Initialize this class
	virtual void Initialize();
public: // Attributes
	/// Information of MusiicTask Class
	std::string								m_pNameOfClass;
	std::string								m_pNameOfParents;

protected: // Attributes
	std::map<std::string, bool>				m_MUSiiCIOFilter;
	std::map<std::string, bool>::iterator	m_pIt;
};

} //end of namespace
#endif
