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

#include "MUSiiCTCPClient.h"
#include "MUSiiCIGTLUtil.h"

namespace igtl
{
	/// Constructor
	MUSiiCTCPClient::MUSiiCTCPClient()
	{
		m_pNameOfClass="MUSiiCTCPClient";
		Initialize();
	}

	/// Deconstructor
	MUSiiCTCPClient::~MUSiiCTCPClient()
	{
		
	}

	/// The information of TCP_IO  
	int MUSiiCTCPClient::GetTCPStatus()
	{
		return m_pMUSiiCTCPClientSocket->GetTCPStatus();
	}

	
	////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	///// Connect to Server(Host) with hostname(host-ip-address) and port
	int MUSiiCTCPClient::ConnectToHost(const char* hostname, int port, std::string filter, bool sync, bool reference, bool reconnect)
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "virtual function:: "<<GetNameOfMUSiiCClass().c_str() <<"::ConnectToHost";

		return m_pMUSiiCTCPClientSocket->ConnectToHost(hostname, port, filter, sync, reference, reconnect);
	}
	
	
	/// Try to reconnect to Server(Host)
	int MUSiiCTCPClient::ReConnectToHost()
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "virtual function:: "<<GetNameOfMUSiiCClass().c_str() <<"::ReConnectToHost";

		return m_pMUSiiCTCPClientSocket->ReConnectToHost();
	}

	/// Close client socket
	void MUSiiCTCPClient::CloseClientSocket(LP_CLIENT_DATA pClient)
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "virtual function:: "<<GetNameOfMUSiiCClass().c_str() <<"::ReConnectToHost";

		m_pMUSiiCTCPClientSocket->CloseClientSocket(pClient);
	}

	/// Close All created clients
	int MUSiiCTCPClient::CloseAllClients()
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "virtual function:: "<<GetNameOfMUSiiCClass().c_str()<<"::CloseAllClients";

		return m_pMUSiiCTCPClientSocket->CloseAllClients();
	}

	// Declare a function that is called MUSiiCCallbackInterface
	/// Called by PreMUSiiCTask
	int MUSiiCTCPClient::PreCallback(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2 , void* data3)
	{
		if(m_bDebug && ptr != NULL)
		{
			MUSiiCTaskAbstract* pTask = (MUSiiCTaskAbstract*) ptr;
			std::cout << "MUSiiCTCPClient::PreCallback' of " << this->GetNameOfMUSiiCClass().c_str() << std::endl;
			std::cout << "Triggered by " << pTask->GetNameOfMUSiiCClass().c_str() << std::endl;
		}
		return 1;
	}

	/// Declare a function that is called MUSiiCCallbackInterface
	/// Called by PostMUSiiCTask
	int MUSiiCTCPClient::PostCallback(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2 , void* data3)
	{
		if(m_bDebug && ptr != NULL)
		{
			MUSiiCTaskAbstract* pTask = (MUSiiCTaskAbstract*) ptr;
			std::cout << "MUSiiCTCPClient::PostCallback' of " << this->GetNameOfMUSiiCClass().c_str() << std::endl;
			std::cout << "Triggered by " << pTask->GetNameOfMUSiiCClass().c_str() << std::endl;
		}
		////////////////////////////////////////////////////////////////////////////////////////////////
		if(data1.IsNotNull())
		{
			if(IsStringMessage(data1))
				return this->PutIGTLMessage(data1); ///Sending StringMessage
				
		}
		return 0;
	}
	
		
	///////////////////////////////////////////////////////////////
	/////Put igtl::MessageBase::Pointer to MUSiiCIODevice
	/////          virtual function.
	//int MUSiiCTCPClient::PutIGTLMessage(igtl::MessageBase::Pointer msg)
	//{
	//	if(this->m_bDebug)
	//		MUSiiC_LOG(logINFO) << "virtual function:: "<<GetNameOfMUSiiCClass().c_str() <<"::PutIGTLMessage";
	//	return m_pMUSiiCTCPClientSocket->PutIGTLMessage(msg);
	//}

	///////////////////////////////////////////////////////////////
	/////Try Put igtl::MessageBase::Pointer to MUSiiCIODevice
	/////          virtual function.
	//int MUSiiCTCPClient::TryPutIGTLMessage(igtl::MessageBase::Pointer msg)
	//{
	//	
	//	if(this->m_bDebug)
	//		MUSiiC_LOG(logINFO) << "virtual function:: "<<GetNameOfMUSiiCClass().c_str() <<"::TryPutIGTLMessage";
	//	return m_pMUSiiCTCPClientSocket->TryPutIGTLMessage(msg);
	//}

///////protected function
///////////////////////////////////////////////////////////////////////////////
	void MUSiiCTCPClient::Initialize()
	{
#if defined(WIN32) || defined (_WIN32) || defined (__WIN32__)
		m_pMUSiiCTCPClientSocketWin		=  igtl::MUSiiCTCPClientSocketWin::New();
		m_pMUSiiCTCPClientSocket		=  m_pMUSiiCTCPClientSocketWin;
#else
		m_pMUSiiCTCPClientSocketNoWin	=  igtl::MUSiiCTCPClientSocketNoWin::New();
		m_pMUSiiCTCPClientSocket		=  m_pMUSiiCTCPClientSocketNoWin;
#endif
		
		/// Callback interface
		/// 01.Connect the PreInputMUSiiCVectorSet of MUSiiCClientSocket and the PreInputMUSiiCVectorSet of this class
		this->SetPreCallbackInterfaceControlOfMUSiiCTaskObject(m_pMUSiiCTCPClientSocket->GetPreCallbackInterfaceControlOfMUSiiCTaskObject());
		/// 02.Connect the PostInputMUSiiCVectorSet of MUSiiCClientSocket and the PreInputMUSiiCVectorSet of this class
		this->SetPostCallbackInterfaceControlOfMUSiiCTaskObject(m_pMUSiiCTCPClientSocket->GetPostCallbackInterfaceControlOfMUSiiCTaskObject());
		
		/// Data Interface
		/// 03.Connect the PreInputMUSiiCVector of MUSiiCClientSocket and the PreInputMUSiiCVector of this class
		this->SetPreInputMUSiiCVectorSet(m_pMUSiiCTCPClientSocket->GetPreInputMUSiiCVectorSet());
		/// 04.Connect the PreOutputMUSiiCVector of MUSiiCClientSocket and the PreOutputMUSiiCVector of this class
		this->SetPreOutputMUSiiCVectorSet(m_pMUSiiCTCPClientSocket->GetPreOutputMUSiiCVectorSet());

		/// 05.Connect the PostInputMUSiiCVector of MUSiiCClientSocket and the PostInputMUSiiCVector of this class
		this->SetPostInputMUSiiCVectorSet(m_pMUSiiCTCPClientSocket->GetPostInputMUSiiCVectorSet());
		/// 06.Connect the PostOutputMUSiiCVector of MUSiiCClientSocket and the PostOutputMUSiiCVector of this class
		this->SetPostOutputMUSiiCVectorSet(m_pMUSiiCTCPClientSocket->GetPostOutputMUSiiCVectorSet());
		/// 07. Connect Input MUSiiCIO Filter
		this->SetPostInputMUSiiCIOFilter(m_pMUSiiCTCPClientSocket->GetPostInputMUSiiCIOFilter());

		/// 08. Connect Output MUSiiCIO Filter
		this->SetPostOutputMUSiiCIOFilter(m_pMUSiiCTCPClientSocket->GetPostOutputMUSiiCIOFilter());

		/// 09.Set Parent MUSiiCTCPIO pointer
		m_pMUSiiCTCPClientSocket->SetParentMUSiiCTCPIO(this);
	}

}