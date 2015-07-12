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

#include "MUSiiCTCPIO.h"

namespace igtl
{
	/// Constructor
	MUSiiCTCPIO::MUSiiCTCPIO()
	{
		m_pNameOfClass="MUSiiCTCPIO";
		Initialize();	
	}
	
	/// Deconstructor
	MUSiiCTCPIO::~MUSiiCTCPIO()
	{
	}

	int MUSiiCTCPIO::GetTCPStatus()
	{
		return m_tcp_status;
	}

	/// Set a pointer of MUSiiCTCPIO as the posinter of parents
	bool MUSiiCTCPIO::SetParentMUSiiCTCPIO(igtl::MUSiiCTCPIO::Pointer parent)
	{
		if(parent.IsNotNull())
		{
			m_pParentTCPIO = parent;
			m_bParentTCPIO = true;
		}

		return m_bParentTCPIO;
	}

	/// Remove the posinter of parents
	bool MUSiiCTCPIO::RemoveParentMUSiiCTCPIO()
	{
		if(m_bParentTCPIO && m_pParentTCPIO.IsNotNull())
		{
			m_pParentTCPIO = NULL;
			m_bParentTCPIO = false;
		}

		return !m_bParentTCPIO;
	}

////protected functions
	void MUSiiCTCPIO::Initialize()
	{
		m_IODevice_Type		= M_TCP_DEVICE_IO;
		m_pParentTCPIO		= NULL;
		m_bParentTCPIO		= false;
	}

	//// Post processing function for TCP/IP Communication 
	/// In General, 
	/// numOfRun : When using Data-Interface, this number indicate the index of new data in Data-Interface
	/// TaskInfo : TCP status
	/// ptr      : the pointer of caller class
	/// data1    : Data 
	/// data2    : the address of server socket
	/// data3    : the address of client socket
	int MUSiiCTCPIO::TCPPostProcessing(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
	{
		return this->PostTaskProcessing(numOfRun, taskInfo, ptr, data1, data2, data3); // Check point
		
		//int r(0);
		//if(this->m_bEnableExternalOutputCallbackFuntions)
		//{
		//	//////////////////////////////////////////////////////
		//	if( taskInfo == M_TCP_DATA_RECEIVED)
		//	{
		//		if(this->m_bvOutputDATA_IF) 
		//		{
		//			//if(data1 != NULL)
		//			if(data1.IsNotNull())
		//			{
		//				//igtl::MessageBase* tempMsg = (igtl::MessageBase*) data1;
		//			
		//				if(m_bUSEOutputNetworkBuffer)
		//				{
		//					if(m_bDebug)
		//						MUSiiC_LOG(logINFO) << "Use Self Output Network Buffer";
		//					r = m_pVOutputDATA_IF_Set->Concurrent_push_back_ALL(data1);
		//				}
		//				else
		//				{
		//					if(m_bDebug)
		//						MUSiiC_LOG(logINFO) << "Not Use Self Output Network Buffer";
		//				
		//					for(int i=1; i< m_pVOutputDATA_IF_Set->GetSizeOfMUSiiCVectorSet(); i++)
		//					   r += m_pVOutputDATA_IF_Set->Concurrent_push_back(data1, i);
		//				}				
		//			
		//				r = this->CallExternalOutputCallbackFunctions(r, M_TCP_DATA_RECEIVED_NODATA, ptr, NULL, data2, data3);
		//			}
		//			else
		//			{
		//				if(m_bDebug)
		//					MUSiiC_LOG(logINFO) << "Received Datais NULL Data";
		//				r = this->CallExternalOutputCallbackFunctions(numOfRun, M_TCP_DATA_RECEIVED_NULLDATA, ptr, NULL, data2, data3);
		//			}
		//		}
		//		else
		//		{
		//			//if(data1 != NULL)
		//			if(data1.IsNotNull())
		//			{
		//				//igtl::MessageBase* tempMsg = (igtl::MessageBase*) data1;

		//				if(m_bDebug)
		//					MUSiiC_LOG(logINFO) << "Received Data ( " << data1->GetDeviceName() << " ) is sent to Callbackfunction";
		//			
		//				r = this->CallExternalOutputCallbackFunctions(numOfRun, M_TCP_DATA_RECEIVED_DATA, ptr, data1, data2, data3);
		//			}
		//			else
		//			{	 if(m_bDebug)
		//					MUSiiC_LOG(logINFO) << "Received Datais NULL Data";
		//				r = this->CallExternalOutputCallbackFunctions(numOfRun, M_TCP_DATA_RECEIVED_NULLDATA, ptr, NULL, data2, data3);
		//			}
		//		}
		//	}
		//	else
		//	{
		//		r = this->CallExternalOutputCallbackFunctions(numOfRun, taskInfo, ptr, NULL, data2, data3);
		//	}
		//	//////////////////////////////////////////////////////
		//}
		////else if(this->m_bvOutputDATA_IF && data1 != NULL)
		//else if(this->m_bvOutputDATA_IF && data1.IsNotNull())
		//{
		//	if(m_bDebug)
		//		MUSiiC_LOG(logINFO) << "Not Using Callbackfunction, Just Using DataInterface.";

		//	//igtl::MessageBase* tempMsg = (igtl::MessageBase*) data1;

		//	if(m_bUSEOutputNetworkBuffer)
		//	{
		//		if(m_bDebug)
		//			MUSiiC_LOG(logINFO) << "Use Self Output Network Buffer";
		//		r = m_pVOutputDATA_IF_Set->Concurrent_push_back_ALL(data1);
		//	}
		//	else
		//	{
		//		if(m_bDebug)
		//			MUSiiC_LOG(logINFO) << "Not Use Self Output Network Buffer";
		//				
		//		for(int i=1; i< m_pVOutputDATA_IF_Set->GetSizeOfMUSiiCVectorSet(); i++)
		//			r += m_pVOutputDATA_IF_Set->Concurrent_push_back(data1, i);
		//	}
		//}

		// return 0;
	}
}
