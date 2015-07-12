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

#include "MUSiiCIGTLTask.h"

namespace igtl
{
	/// Constructor
	MUSiiCIGTLTask::MUSiiCIGTLTask()
	{
		igtl::MUSiiCTaskAbstract::m_pNameOfClass="MUSiiCIODevice";
		Initialize();		
	}
	
	/// Deconstructor
	MUSiiCIGTLTask::~MUSiiCIGTLTask()
	{
	}

	////////////////////////////////////////////////////////////
	/// MUSiiC IO Filter
	
	
	/// ******* Input MUSiiC IO Filter

	/// Set Input-MUSiiCIOFilter
	bool MUSiiCIGTLTask::SetPreInputMUSiiCIOFilter(igtl::MUSiiCIOFilter::Pointer filter)
	{
		if(filter.IsNotNull())
		{
			m_pPreInputMUSiiCIOFilter			= filter;
			return m_bIsPreInputMUSiiCIOFilter	= true;
		}

		return m_bIsPreInputMUSiiCIOFilter		= false;
	}

	/// Get InputMUSiiCIOFilter of this class
	igtl::MUSiiCIOFilter::Pointer MUSiiCIGTLTask::GetPreInputMUSiiCIOFilter()
	{
		return m_bIsPreInputMUSiiCIOFilter? m_pPreInputMUSiiCIOFilter: NULL;
	}

	/// Check there is MUSiiCIOFilter
	bool MUSiiCIGTLTask::IsPreInputMUSiiCIOFilter()
	{
		if(m_pPreInputMUSiiCIOFilter.IsNotNull())
			return m_bIsPreInputMUSiiCIOFilter;
		else
			return false;
	}

	/// Set the boolean value of MUSiiCIOFilter
	bool MUSiiCIGTLTask::SetEnablePreInputMUSiiCIOFilter(bool enable)
	{
		if(m_pPreInputMUSiiCIOFilter.IsNotNull())
			return m_bIsPreInputMUSiiCIOFilter = enable;
		else
			return m_bIsPreInputMUSiiCIOFilter = false;
	}

	/// Get the boolean value of MUSiiCIOFilter
	bool MUSiiCIGTLTask::GetEnablePreInputMUSiiCIOFilter()
	{
		if(m_pPreInputMUSiiCIOFilter.IsNotNull())
			return m_bIsPreInputMUSiiCIOFilter;
		else
			return m_bIsPreInputMUSiiCIOFilter = false;
	}

	////----------------------------------------------------------------//////
	/// Reset Input MUSiiC IO Filter
	void MUSiiCIGTLTask::ResetPreInputMUSiiCIOFilter()
	{
		m_pPreInputMUSiiCIOFilter->ResetMUSiiCIOFilter();
	}

	/// Set Input MUSiiCIOFilter using Data_Type or DeviceName
	/// return : the size of MUSiiCIOFIlter
	int MUSiiCIGTLTask::SetPreInputMUSiiCIOFilterData(std::string datatype, bool enable)
	{
		return m_pPreInputMUSiiCIOFilter->SetMUSiiCIOFilter(datatype, enable);
	}

	/// Get How many data-type are defined in MUSiiCIOFilter
	int MUSiiCIGTLTask::GetNumberOfDataTypePreInputMUSiiCIOFilter()
	{
		return m_pPreInputMUSiiCIOFilter->GetNumberOfDataType();
	}

	/// Get The list of data-type 
	std::vector<std::string>& MUSiiCIGTLTask::GetDataTypeListFromPreInputMUSiiCIOFilter()
	{
		return m_pPreInputMUSiiCIOFilter->GetDataTypeList();
	}

	/// Remove data-type from MUSiiCIOFilter
	int MUSiiCIGTLTask::RemoveDataTypeFromPreInputMUSiiCIOFilter(std::string datatype)
	{
		return m_pPreInputMUSiiCIOFilter->RemoveDataType(datatype);
	}

	/// Check the data-type is or not in MUSiiCIOFilter
	bool MUSiiCIGTLTask::IsDataTypeFromPreInputMUSiiCIOFilter(std::string datatype)
	{
		return m_pPreInputMUSiiCIOFilter->IsDataType(datatype);
	}

	//// Check MessageBase using pre-defined IOFilter
	igtl::MessageBase::Pointer MUSiiCIGTLTask::CheckMessageBasePreInputMUSiiCIOFilter(igtl::MessageBase::Pointer msg)
	{
		return m_pPreInputMUSiiCIOFilter->CheckMessageBase(msg, m_bPreInputCheckDeviceType);
	}

	void MUSiiCIGTLTask::PrintPreInputMUSiiCIOFilter()
	{
		m_pPreInputMUSiiCIOFilter->PrintIOFilter();
	}



	////////////////////////////////////////////////////////////////////
	/// ******* Output MUSiiC IO Filter

	/// Set Input-MUSiiCIOFilter
	bool MUSiiCIGTLTask::SetPreOutputMUSiiCIOFilter(igtl::MUSiiCIOFilter::Pointer filter)
	{
		if(filter.IsNotNull())
		{
			m_pPreOutputMUSiiCIOFilter				= filter;
			return m_bIsPreOutputMUSiiCIOFilter	= true;
		}

		return m_bIsPreOutputMUSiiCIOFilter		= false;
	}

	/// Get InputMUSiiCIOFilter of this class
	igtl::MUSiiCIOFilter::Pointer MUSiiCIGTLTask::GetPreOutputMUSiiCIOFilter()
	{
		return m_bIsPreOutputMUSiiCIOFilter? m_pPreOutputMUSiiCIOFilter: NULL;
	}

	/// Check there is MUSiiCIOFilter
	bool MUSiiCIGTLTask::IsPreOutputMUSiiCIOFilter()
	{
		if(m_pPreOutputMUSiiCIOFilter.IsNotNull())
			return m_bIsPreOutputMUSiiCIOFilter;
		else
			return false;
	}

	/// Set the boolean value of MUSiiCIOFilter
	bool MUSiiCIGTLTask::SetEnablePreOutputMUSiiCIOFilter(bool enable)
	{
		if(m_pPreOutputMUSiiCIOFilter.IsNotNull())
			return m_bIsPreOutputMUSiiCIOFilter = enable;
		else
			return m_bIsPreOutputMUSiiCIOFilter = false;
	}

	/// Get the boolean value of MUSiiCIOFilter
	bool MUSiiCIGTLTask::GetEnablePreOutputMUSiiCIOFilter()
	{
		if(m_pPreOutputMUSiiCIOFilter.IsNotNull())
			return m_bIsPreOutputMUSiiCIOFilter;
		else
			return m_bIsPreOutputMUSiiCIOFilter = false;
	}

	////----------------------------------------------------------------//////
	/// Reset Output MUSiiC IO Filter
	void MUSiiCIGTLTask::ResetPreOutputMUSiiCIOFilter()
	{
		m_pPreOutputMUSiiCIOFilter->ResetMUSiiCIOFilter();
	}

	/// Set Output MUSiiCIOFilter using Data_Type or DeviceName
	/// return : the size of MUSiiCIOFIlter
	int MUSiiCIGTLTask::SetPreOutputMUSiiCIOFilterData(std::string datatype, bool enable)
	{
		return m_pPreOutputMUSiiCIOFilter->SetMUSiiCIOFilter(datatype, enable);
	}

	/// Get How many data-type are defined in Output MUSiiCIOFilter
	int MUSiiCIGTLTask::GetNumberOfDataTypePreOutputMUSiiCIOFilter()
	{
		return m_pPreOutputMUSiiCIOFilter->GetNumberOfDataType();
	}

	/// Get The list of data-type 
	std::vector<std::string>& MUSiiCIGTLTask::GetDataTypeListFromPreOutputMUSiiCIOFilter()
	{
		return m_pPreOutputMUSiiCIOFilter->GetDataTypeList();
	}

	/// Remove data-type from MUSiiCIOFilter
	int MUSiiCIGTLTask::RemoveDataTypeFromPreOutputMUSiiCIOFilter(std::string datatype)
	{
		return m_pPreOutputMUSiiCIOFilter->RemoveDataType(datatype);
	}

	/// Check the data-type is or not in MUSiiCIOFilter
	bool MUSiiCIGTLTask::IsDataTypeFromPreOutputMUSiiCIOFilter(std::string datatype)
	{
		return m_pPreOutputMUSiiCIOFilter->IsDataType(datatype);
	}

	//// Check MessageBase using pre-defined IOFilter
	igtl::MessageBase::Pointer MUSiiCIGTLTask::CheckMessageBasPreOutputMUSiiCIOFilter(igtl::MessageBase::Pointer msg)
	{
		return m_pPreOutputMUSiiCIOFilter->CheckMessageBase(msg, m_bPreOutputCheckDeviceType);
	}

	void MUSiiCIGTLTask::PrintPreOutputMUSiiCIOFilter()
	{
		m_pPreOutputMUSiiCIOFilter->PrintIOFilter();
	}


	////////////////////////////////////////////////////////////////////////////
	/// Post Task

	/// ******* Input MUSiiC IO Filter

	/// Set Input-MUSiiCIOFilter
	bool MUSiiCIGTLTask::SetPostInputMUSiiCIOFilter(igtl::MUSiiCIOFilter::Pointer filter)
	{
		if(filter.IsNotNull())
		{
			m_pPostInputMUSiiCIOFilter			= filter;
			return m_bIsPostInputMUSiiCIOFilter	= true;
		}

		return m_bIsPostInputMUSiiCIOFilter		= false;
	}

	/// Get InputMUSiiCIOFilter of this class
	igtl::MUSiiCIOFilter::Pointer MUSiiCIGTLTask::GetPostInputMUSiiCIOFilter()
	{
		return m_bIsPostInputMUSiiCIOFilter? m_pPostInputMUSiiCIOFilter: NULL;
	}

	/// Check there is MUSiiCIOFilter
	bool MUSiiCIGTLTask::IsPostInputMUSiiCIOFilter()
	{
		if(m_pPostInputMUSiiCIOFilter.IsNotNull())
			return m_bIsPostInputMUSiiCIOFilter;
		else
			return false;
	}

	/// Set the boolean value of MUSiiCIOFilter
	bool MUSiiCIGTLTask::SetEnablePostInputMUSiiCIOFilter(bool enable)
	{
		if(m_pPostInputMUSiiCIOFilter.IsNotNull())
			return m_bIsPostInputMUSiiCIOFilter = enable;
		else
			return m_bIsPostInputMUSiiCIOFilter = false;
	}

	/// Get the boolean value of MUSiiCIOFilter
	bool MUSiiCIGTLTask::GetEnablePostInputMUSiiCIOFilter()
	{
		if(m_pPostInputMUSiiCIOFilter.IsNotNull())
			return m_bIsPostInputMUSiiCIOFilter;
		else
			return m_bIsPostInputMUSiiCIOFilter = false;
	}

	////----------------------------------------------------------------//////
	/// Reset Input MUSiiC IO Filter
	void MUSiiCIGTLTask::ResetPostInputMUSiiCIOFilter()
	{
		m_pPostInputMUSiiCIOFilter->ResetMUSiiCIOFilter();
	}

	/// Set Input MUSiiCIOFilter using Data_Type or DeviceName
	/// return : the size of MUSiiCIOFIlter
	int MUSiiCIGTLTask::SetPostInputMUSiiCIOFilterData(std::string datatype, bool enable)
	{
		return m_pPostInputMUSiiCIOFilter->SetMUSiiCIOFilter(datatype, enable);
	}

	/// Get How many data-type are defined in MUSiiCIOFilter
	int MUSiiCIGTLTask::GetNumberOfDataTypePostInputMUSiiCIOFilter()
	{
		return m_pPostInputMUSiiCIOFilter->GetNumberOfDataType();
	}

	/// Get The list of data-type 
	std::vector<std::string>& MUSiiCIGTLTask::GetDataTypeListFromPostInputMUSiiCIOFilter()
	{
		return m_pPostInputMUSiiCIOFilter->GetDataTypeList();
	}

	/// Remove data-type from MUSiiCIOFilter
	int MUSiiCIGTLTask::RemoveDataTypeFromPostInputMUSiiCIOFilter(std::string datatype)
	{
		return m_pPostInputMUSiiCIOFilter->RemoveDataType(datatype);
	}

	/// Check the data-type is or not in MUSiiCIOFilter
	bool MUSiiCIGTLTask::IsDataTypeFromPostInputMUSiiCIOFilter(std::string datatype)
	{
		return m_pPostInputMUSiiCIOFilter->IsDataType(datatype);
	}

	//// Check MessageBase using pre-defined IOFilter
	igtl::MessageBase::Pointer MUSiiCIGTLTask::CheckMessageBasePostInputMUSiiCIOFilter(igtl::MessageBase::Pointer msg)
	{
		return m_pPostInputMUSiiCIOFilter->CheckMessageBase(msg, m_bPostInputCheckDeviceType);
	}

	void MUSiiCIGTLTask::PrintPostInputMUSiiCIOFilter()
	{
		m_pPostInputMUSiiCIOFilter->PrintIOFilter();
	}



	////////////////////////////////////////////////////////////////////
	/// ******* Output MUSiiC IO Filter

	/// Set Input-MUSiiCIOFilter
	bool MUSiiCIGTLTask::SetPostOutputMUSiiCIOFilter(igtl::MUSiiCIOFilter::Pointer filter)
	{
		if(filter.IsNotNull())
		{
			m_pPostOutputMUSiiCIOFilter				= filter;
			return m_bIsPostOutputMUSiiCIOFilter	= true;
		}

		return m_bIsPostOutputMUSiiCIOFilter		= false;
	}

	/// Get InputMUSiiCIOFilter of this class
	igtl::MUSiiCIOFilter::Pointer MUSiiCIGTLTask::GetPostOutputMUSiiCIOFilter()
	{
		return m_bIsPostOutputMUSiiCIOFilter? m_pPostOutputMUSiiCIOFilter: NULL;
	}

	/// Check there is MUSiiCIOFilter
	bool MUSiiCIGTLTask::IsPostOutputMUSiiCIOFilter()
	{
		if(m_pPostOutputMUSiiCIOFilter.IsNotNull())
			return m_bIsPostOutputMUSiiCIOFilter;
		else
			return false;
	}

	/// Set the boolean value of MUSiiCIOFilter
	bool MUSiiCIGTLTask::SetEnablePostOutputMUSiiCIOFilter(bool enable)
	{
		if(m_pPostOutputMUSiiCIOFilter.IsNotNull())
			return m_bIsPostOutputMUSiiCIOFilter = enable;
		else
			return m_bIsPostOutputMUSiiCIOFilter = false;
	}

	/// Get the boolean value of MUSiiCIOFilter
	bool MUSiiCIGTLTask::GetEnablePostOutputMUSiiCIOFilter()
	{
		if(m_pPostOutputMUSiiCIOFilter.IsNotNull())
			return m_bIsPostOutputMUSiiCIOFilter;
		else
			return m_bIsPostOutputMUSiiCIOFilter = false;
	}

	////----------------------------------------------------------------//////
	/// Reset Output MUSiiC IO Filter
	void MUSiiCIGTLTask::ResetPostOutputMUSiiCIOFilter()
	{
		m_pPostOutputMUSiiCIOFilter->ResetMUSiiCIOFilter();
	}

	/// Set Output MUSiiCIOFilter using Data_Type or DeviceName
	/// return : the size of MUSiiCIOFIlter
	int MUSiiCIGTLTask::SetPostOutputMUSiiCIOFilterData(std::string datatype, bool enable)
	{
		return m_pPostOutputMUSiiCIOFilter->SetMUSiiCIOFilter(datatype, enable);
	}

	/// Get How many data-type are defined in Output MUSiiCIOFilter
	int MUSiiCIGTLTask::GetNumberOfDataTypePostOutputMUSiiCIOFilter()
	{
		return m_pPostOutputMUSiiCIOFilter->GetNumberOfDataType();
	}

	/// Get The list of data-type 
	std::vector<std::string>& MUSiiCIGTLTask::GetDataTypeListFromPostOutputMUSiiCIOFilter()
	{
		return m_pPostOutputMUSiiCIOFilter->GetDataTypeList();
	}

	/// Remove data-type from MUSiiCIOFilter
	int MUSiiCIGTLTask::RemoveDataTypeFromPostOutputMUSiiCIOFilter(std::string datatype)
	{
		return m_pPostOutputMUSiiCIOFilter->RemoveDataType(datatype);
	}

	/// Check the data-type is or not in MUSiiCIOFilter
	bool MUSiiCIGTLTask::IsDataTypeFromPostOutputMUSiiCIOFilter(std::string datatype)
	{
		return m_pPostOutputMUSiiCIOFilter->IsDataType(datatype);
	}

	//// Check MessageBase using pre-defined IOFilter
	igtl::MessageBase::Pointer MUSiiCIGTLTask::CheckMessageBasPostOutputMUSiiCIOFilter(igtl::MessageBase::Pointer msg)
	{
		if(msg.IsNotNull())
			return m_pPostOutputMUSiiCIOFilter->CheckMessageBase(msg, m_bPostOutputCheckDeviceType);
		else 
			return NULL;
	}

	void MUSiiCIGTLTask::PrintPostOutputMUSiiCIOFilter()
	{
		m_pPostOutputMUSiiCIOFilter->PrintIOFilter();
	}


	/// MUSiiC IO Filter
	////////////////////////////////////////////////////////////
	

	////////////////////////////////////////////////////////////
	/// ETC

	
	/////////////////////////////////////////////////////////////
	///// Data Handling
	/////////////////////////////////////////////////////////////
	///Put igtl::MessageBase::Pointer to MUSiiCIODevice
	///          virtual function.
	///          if return value is -1, this means the error of this function/
	int MUSiiCIGTLTask::PutIGTLMessage(igtl::MessageBase::Pointer msg)
	{
		if(m_pSelfPreInputDataInterface.IsNotNull())
		{
			if(!m_bSelfPreInputDataInterface)
			{
				int s(this->GetNumOfPreInputDataInterface());
				this->AddPreInputDataInterface(m_pSelfPreInputDataInterface);

				m_bSelfPreInputDataInterface = this->GetNumOfPreInputDataInterface() == s+1 ? true: false;
			}
			
			m_bUseSelfPreInputDataInterface = true;

			if(this->m_bSelfPreInputDataInterface) ///check point
				return this->m_pSelfPreInputDataInterface->concurrent_push_back(msg);
		}
		return -1;
	}

	/////////////////////////////////////////////////////////////
	///Try Put igtl::MessageBase::Pointer to MUSiiCIODevice
	///          virtual function.
	///          if return value is -1, this means the error of this function/
	int MUSiiCIGTLTask::TryPutIGTLMessage(igtl::MessageBase::Pointer msg)
	{
		if(m_pSelfPreInputDataInterface.IsNotNull())
		{
			if(!m_bSelfPreInputDataInterface)
			{
				int s(this->GetNumOfPreInputDataInterface());
				this->AddPreInputDataInterface(m_pSelfPreInputDataInterface);

				m_bSelfPreInputDataInterface = this->GetNumOfPreInputDataInterface() == s+1 ? true: false;
			}
			
			m_bUseSelfPreInputDataInterface = true;

			if(this->m_bSelfPreInputDataInterface) ///check point
				return this->m_pSelfPreInputDataInterface->try_push_back(msg);
		}
		return -1;
	}

	///// Data Handling
	/////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	//////// Link MUSiiCTaskInterfaceAbstract

	//// Add another MUSiiCIGTLTask as the previous Task Class
	bool MUSiiCIGTLTask::AddPreMUSiiCIGTLTask(igtl::MUSiiCIGTLTask::Pointer pre_task)
	{
		if(pre_task.IsNotNull())
			return this->AddPreMUSiiCTaskInterface<igtl::MessageBase::Pointer, igtl::MessageBase::Pointer>(pre_task);
		else 
			return false;
	}


	//Reemove pre-defined MUSiiCIGTLTask from Pre-MUSiiCIGTLTask List. 	
	bool MUSiiCIGTLTask::RemovePreMUSiiCIGTLTask(igtl::MUSiiCIGTLTask::Pointer pre_task)
	{
		if(pre_task.IsNotNull())
			return this->RemovePreMUSiiCTaskInterface<igtl::MessageBase::Pointer, igtl::MessageBase::Pointer>(pre_task);
		else
			return false;
	}


	////// Add another MUSiiCIGTLTask as the post Task Class
	bool MUSiiCIGTLTask::AddPostMUSiiCIGTLTask(igtl::MUSiiCIGTLTask::Pointer post_task)
	{
		if(post_task.IsNotNull())
			return this->AddPostMUSiiCTaskInterface<igtl::MessageBase::Pointer, igtl::MessageBase::Pointer>(post_task);
		else 
			return false;
	}

	//Reemove pre-defined MUSiiCIGTLTask from Post-MUSiiCIGTLTask List. 	
	bool MUSiiCIGTLTask::RemovePostMUSiiCIGTLTask(igtl::MUSiiCIGTLTask::Pointer post_task)
	{
		if(post_task.IsNotNull())
			return this->RemovePostMUSiiCTaskInterface<igtl::MessageBase::Pointer, igtl::MessageBase::Pointer>(post_task);
		else
			return false;
	}
	//////// Link MUSiiCTaskInterfaceAbstract
	/////////////////////////////////////////////////////////////////////////////

	/// Get the pointer of MUSiiCIGTLTask of this class
	igtl::MUSiiCIGTLTask::Pointer MUSiiCIGTLTask::GetMUSiiCIGTLTaskPointer()
	{
		return (igtl::MUSiiCIGTLTask::Pointer)this;
	}

//protected: ///Operation
	/// Initialize class memeber variables
	void MUSiiCIGTLTask::Initialize()
	{		
		//// Input IO Filter
		m_bIsPreInputMUSiiCIOFilter		= false;
		//m_pInputMUSiiCIOFilter		= NULL;
		m_pPreInputMUSiiCIOFilter		    = igtl::MUSiiCIOFilter::New();
		/// The boolean variable for MUSiiCIOFilter :: Checking DeviceType (Input Data)
		m_bPreInputCheckDeviceType			= false;

		//// Output IO Filter
		
		m_bIsPreOutputMUSiiCIOFilter       = false;
		m_pPreOutputMUSiiCIOFilter			= igtl::MUSiiCIOFilter::New();
		/// The boolean variable for MUSiiCIOFilter :: Checking DeviceType (Output Data)
		m_bPreOutputCheckDeviceType		= false;

		/////////////////////////////////////////

		//// Input IO Filter
		m_bIsPostInputMUSiiCIOFilter		= false;
		//m_pInputMUSiiCIOFilter		= NULL;
		m_pPostInputMUSiiCIOFilter		    = igtl::MUSiiCIOFilter::New();
		/// The boolean variable for MUSiiCIOFilter :: Checking DeviceType (Input Data)
		m_bPostInputCheckDeviceType			= false;

		//// Output IO Filter
		
		m_bIsPostOutputMUSiiCIOFilter       = false;
		m_pPostOutputMUSiiCIOFilter			= igtl::MUSiiCIOFilter::New();
		/// The boolean variable for MUSiiCIOFilter :: Checking DeviceType (Output Data)
		m_bPostOutputCheckDeviceType		= false;

		///////////////////////////////////
		/// cannon96

		//// Use IGTL Message
		this->SetEnableUseIGTLMessage(true);

	}


	/// Send IGTL Message to Pre-MUSiiCTask class
	/// This function is virtual function.
	/// We have to re-implement this function on MUSIiCIODevice, and other MUSiiCTask classes (MUSiiCSyncCombine, MUSiiCSuncDataCollectot)
	/// To Do: cannon96
	int MUSiiCIGTLTask::SendIGTLMsgToPreTask(igtl::MessageBase::Pointer data)
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << this->GetNameOfMUSiiCClass().c_str() << "SendIGTLMsgToPreTask";

		if(data.IsNotNull() && this->m_bVPreOutputDATA_IF_Set && m_bUseIGTLMessage)
		{
			return m_pVPreOutputDATA_IF_Set->Concurrent_push_back_ALL(data);
		}
		return -1;
	}

	/// Send IGTL Message to Pre-MUSiiCTask class
	/// This function is virtual function.
	/// We have to re-implement this function on MUSIiCIODevice, and other MUSiiCTask classes (MUSiiCSyncCombine, MUSiiCSuncDataCollectot)
	/// To Do: cannon96
	int MUSiiCIGTLTask::SendIGTLMsgToPostTask(igtl::MessageBase::Pointer data)
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << this->GetNameOfMUSiiCClass().c_str() << "SendIGTLMsgToPostTask";
		
		if(data.IsNotNull() && this->m_bVPostOutputDATA_IF_Set && m_bUseIGTLMessage)
		{
			return m_pVPostOutputDATA_IF_Set->Concurrent_push_back_ALL(data);
		}
		return -1;
	}

	///Retrieve Inpudata from void* data 
	/// This function is virtual function.
	/// We have to re-implement this function on MUSIiCIODevice, and other MUSiiCTask classes (MUSiiCSyncCombine, MUSiiCSuncDataCollectot)
	/// To Do: cannon96
	igtl::MessageBase::Pointer MUSiiCIGTLTask::RetrieveInputData(void* data)
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << this->GetNameOfMUSiiCClass().c_str();

		igtl::MessageBase::Pointer tempdata = (igtl::MessageBase*)data;
		return tempdata;
	}

	///Retrieve Outpudata from void* data
	/// This function is virtual function.
	/// We have to re-implement this function on MUSIiCIODevice, and other MUSiiCTask classes (MUSiiCSyncCombine, MUSiiCSuncDataCollectot)
	/// To Do: cannon96
	igtl::MessageBase::Pointer MUSiiCIGTLTask::RetrieveOutputData(void* data)
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << this->GetNameOfMUSiiCClass().c_str();

		igtl::MessageBase::Pointer tempdata = (igtl::MessageBase*)data;
		return tempdata;
	}
} ;