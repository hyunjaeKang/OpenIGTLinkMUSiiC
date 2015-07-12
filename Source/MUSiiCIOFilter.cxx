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

#include "MUSiiCIOFilter.h"

namespace igtl
{

	/// Constrcut
	MUSiiCIOFilter::MUSiiCIOFilter()
	{
		this->m_pNameOfClass = ("MUSiiCIOFilter");
		this->Initialize();
	}

	/// Deconstrcut
	MUSiiCIOFilter::~MUSiiCIOFilter()
	{
	}

	/// Get the name of Class
	std::string  MUSiiCIOFilter::GetNameOfMUSiiCClass()
	{
		return m_pNameOfClass;
	}

	/// Set the name of Parent class
	void MUSiiCIOFilter::SetNameOfParentMUSiiCClass(std::string pName)
	{
		m_pNameOfParents = pName;
	}

	/// Get the name of Parent
	std::string MUSiiCIOFilter::GetNameOfParentMUSiiCClass()
	{
		return m_pNameOfParents;
	}

	/// Reset MUSiiCIOFilter
	void MUSiiCIOFilter::ResetMUSiiCIOFilter()
	{
		m_MUSiiCIOFilter.clear();
	}

	/// Set MUSiiCIOFilter using Data_Type or DeviceName
	int MUSiiCIOFilter::SetMUSiiCIOFilter(std::string datatype, bool enable)
	{
		/// IGTL_STRING Message is default message type 
		if(!CheckDataType("STRING"))
		{
			m_MUSiiCIOFilter["STRING"] = true;
		}
		m_MUSiiCIOFilter[datatype] = enable;
		return m_MUSiiCIOFilter.size();
	}

	/// Check a Datatype whether is pass or not.
	/// TO Do cannon96 Check this function
	bool MUSiiCIOFilter::CheckDataType(std::string datatype)
	{
		/// Default of MUSiiCIOFilter is pass all data
		if(m_MUSiiCIOFilter.size() == 0)
			return true;
		else
		{
			std::map<std::string, bool>::iterator it;
			for(it = m_MUSiiCIOFilter.begin(); it != m_MUSiiCIOFilter.end() ; it++)
			{
				if(datatype.find(it->first) != std::string::npos)
					return it->second;
				else if(datatype.find("ALL") != std::string::npos)
					return true;
				else if(datatype.compare("") == 0)
					return true;
			}
		}
		
		return false;
	}

	/// Check a Datatype whether is pass or not.
	/// TO Do cannon96 Check this function
	bool MUSiiCIOFilter::CheckDataType2(std::string datatype)
	{
		/// Default of MUSiiCIOFilter is pass all data
		if(m_MUSiiCIOFilter.size() == 0)
			return true;
		if(m_MUSiiCIOFilter.find(datatype) == m_MUSiiCIOFilter.end())
			return false;
		else
			return m_MUSiiCIOFilter.find(datatype)->second;
	}

	//// Check Data using pre-defined IOFilter
	//// cannon96 Please check this function 
	igtl::MessageBase::Pointer MUSiiCIOFilter::CheckMessageBase(igtl::MessageBase::Pointer msg, bool checkDevicetype)
	{
		if(msg.IsNull())
			return NULL;

		if(this->CheckDataType(msg->GetDeviceName()))
			return msg;
		else if(checkDevicetype)
			if(this->CheckDataType(msg->GetDeviceType()))
				return msg;

		return NULL;
	}

	//// Check Data using pre-defined IOFilter
	//// cannon96 Please check this function 
	igtl::MessageBase::Pointer MUSiiCIOFilter::CheckMessageBase2(igtl::MessageBase::Pointer msg, bool checkDevicetype)
	{
		if(this->CheckDataType2(msg->GetDeviceName()))
			return msg;
		else if(checkDevicetype)
			if(this->CheckDataType2(msg->GetDeviceType()))
				return msg;

		return NULL;
	}

	/// Get How many data-type are defined in MUSiiCIOFilter
	int MUSiiCIOFilter::GetNumberOfDataType()
	{
		return m_MUSiiCIOFilter.size();
	}

	/// Get The list of data-type 
	std::vector<std::string>& MUSiiCIOFilter::GetDataTypeList()
	{
		std::vector<std::string> list;
		std::map<std::string, bool>::iterator it;
		for(it = m_MUSiiCIOFilter.begin(); it != m_MUSiiCIOFilter.end() ; it++)
			list.push_back(it->first);

		return list;
	}

	/// Remove data-type from MUSiiCIOFilter
	int MUSiiCIOFilter::RemoveDataType(std::string datatype)
	{
		if(CheckDataType(datatype))
		{
			m_MUSiiCIOFilter.erase(datatype);
			return m_MUSiiCIOFilter.size();
		}
		else
			return -1;
	}

	/// Check the data-type is or not in MUSiiCIOFilter
	bool MUSiiCIOFilter::IsDataType(std::string datatype)
	{
		return m_MUSiiCIOFilter.count(datatype)>0 ? true: false;
	}


	void MUSiiCIOFilter::PrintIOFilter()
	{
		std::cerr << "This is MUSiiCIOFilter of " << m_pNameOfParents << std::endl;

		for(m_pIt = m_MUSiiCIOFilter.begin(); m_pIt != m_MUSiiCIOFilter.end(); m_pIt++)
			std::cerr << "Data Type is : " << m_pIt->first << "  : the value is : " << m_pIt->second << std::endl;

		std::cerr << "The size of MUSiiCIOFilter is " << m_MUSiiCIOFilter.size();
	}

////protected operations
	/// Initialize this class
	void MUSiiCIOFilter::Initialize()
	{
		this->ResetMUSiiCIOFilter();	
	}
}