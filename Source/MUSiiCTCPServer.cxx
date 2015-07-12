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
#include "MUSiiCTCPServer.h"

namespace igtl
{
	/// Constructor
	MUSiiCTCPServer::MUSiiCTCPServer()
	{
		m_pNameOfClass="MUSiiCTCPServer";
		Initialize();
	}
	
	/// Deconstructor
	MUSiiCTCPServer::~MUSiiCTCPServer()
	{
	}
	
	///////////////////////////////////////////////////////////
	/// The information of TCP_IO  
	int MUSiiCTCPServer::GetTCPStatus()
	{
		return m_pMUSiiCTCPServerSocket->GetTCPStatus();
	}
	
	////////////////////////////////////////////////////////////////////

	/// Creater Server Socket
	int MUSiiCTCPServer::CreateServer(int port)
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "virtual function:: "<<this->GetNameOfMUSiiCClass().c_str()<<"::CreateServer";
		return m_pMUSiiCTCPServerSocket->CreateServer(port);
	}

	/// Close server socket
	int MUSiiCTCPServer::CloseServer()
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "virtual function:: "<<this->GetNameOfMUSiiCClass().c_str() <<"::CloseServer";
		return m_pMUSiiCTCPServerSocket->CloseServer();
	}

	/// Get Num of connected-clients
	int MUSiiCTCPServer::GetNumOfClients()
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "virtual function:: "<<this->GetNameOfMUSiiCClass().c_str()<<"::GetNumOfClients";
		return m_pMUSiiCTCPServerSocket->GetNumOfClients();
	}

	/// Check there are clients or not.
	bool MUSiiCTCPServer::IsConnectedClients()
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "virtual function:: "<<this->GetNameOfMUSiiCClass().c_str()<<"::IsConnectedClients";
		return m_pMUSiiCTCPServerSocket->IsConnectedClients();
	}


	////////////////////////////////////////
	/// Get the list of Connected client list
	igtl::MUSiiCVector<LP_CLIENT_DATA>::Pointer MUSiiCTCPServer::GetConnectedClientList()
	{
		return m_pMUSiiCTCPServerSocket->GetConnectedClientList();
	}



/////Protected::operations
	void MUSiiCTCPServer::Initialize()
	{
#if defined(WIN32) || defined (_WIN32) || defined (__WIN32__)
		m_pMUSiiCTCPServerSocketWin		=  igtl::MUSiiCTCPServerSocketWin::New();
		m_pMUSiiCTCPServerSocket		=  m_pMUSiiCTCPServerSocketWin;
#else
		m_pMUSiiCTCPServerSocketNoWin	=  igtl::MUSiiCTCPServerSocketNoWin::New();
		m_pMUSiiCTCPServerSocket		=  m_pMUSiiCTCPServerSocketNoWin;
#endif

		/// Callback interface
		/// 01.Connect the PreInputMUSiiCVectorSet of MUSiiCClientSocket and the PreInputMUSiiCVectorSet of this class
		this->SetPreCallbackInterfaceControlOfMUSiiCTaskObject(m_pMUSiiCTCPServerSocket->GetPreCallbackInterfaceControlOfMUSiiCTaskObject());
		/// 02.Connect the PostInputMUSiiCVectorSet of MUSiiCClientSocket and the PreInputMUSiiCVectorSet of this class
		this->SetPostCallbackInterfaceControlOfMUSiiCTaskObject(m_pMUSiiCTCPServerSocket->GetPostCallbackInterfaceControlOfMUSiiCTaskObject());
		
		/// Data Interface
		/// 03.Connect the PreInputMUSiiCVector of MUSiiCClientSocket and the PreInputMUSiiCVector of this class
		this->SetPreInputMUSiiCVectorSet(m_pMUSiiCTCPServerSocket->GetPreInputMUSiiCVectorSet());
		/// 04.Connect the PreOutputMUSiiCVector of MUSiiCClientSocket and the PreOutputMUSiiCVector of this class
		this->SetPreOutputMUSiiCVectorSet(m_pMUSiiCTCPServerSocket->GetPreOutputMUSiiCVectorSet());

		/// 05.Connect the PostInputMUSiiCVector of MUSiiCClientSocket and the PostInputMUSiiCVector of this class
		this->SetPostInputMUSiiCVectorSet(m_pMUSiiCTCPServerSocket->GetPostInputMUSiiCVectorSet());
		/// 06.Connect the PostOutputMUSiiCVector of MUSiiCClientSocket and the PostOutputMUSiiCVector of this class
		this->SetPostOutputMUSiiCVectorSet(m_pMUSiiCTCPServerSocket->GetPostOutputMUSiiCVectorSet());
		/// 07. Connect Input MUSiiCIO Filter
		this->SetPreInputMUSiiCIOFilter(m_pMUSiiCTCPServerSocket->GetPreInputMUSiiCIOFilter());

		/// 08. Connect Output MUSiiCIO Filter
		this->SetPreOutputMUSiiCIOFilter(m_pMUSiiCTCPServerSocket->GetPreOutputMUSiiCIOFilter());

		/// 09.Set Parent MUSiiCTCPIO pointer
		m_pMUSiiCTCPServerSocket->SetParentMUSiiCTCPIO(this);


	}


}