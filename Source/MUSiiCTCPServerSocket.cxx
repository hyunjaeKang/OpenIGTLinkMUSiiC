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
#include "MUSiiCTCPServerSocket.h"

namespace igtl
{
	/// Constructor
	MUSiiCTCPServerSocket::MUSiiCTCPServerSocket()
	{
		m_pNameOfClass="MUSiiCTCPServerSocket";
		Initialize();
	}
	
	/// Deconstructor
	MUSiiCTCPServerSocket::~MUSiiCTCPServerSocket()
	{
	}

	////////////////////////////////////////////////////////////////////

	/// Creater Server Socket
	int MUSiiCTCPServerSocket::CreateServer(int port)
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "virtual function:: "<<this->GetNameOfMUSiiCClass().c_str()<<"::CreateServer";

		return 0;
	}

	/// Close server socket
	int MUSiiCTCPServerSocket::CloseServer()
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "virtual function:: "<<this->GetNameOfMUSiiCClass().c_str() <<"::CloseServer";
		return 0;
	}

	/// Get Num of connected-clients
	int MUSiiCTCPServerSocket::GetNumOfClients()
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "virtual function:: "<<this->GetNameOfMUSiiCClass().c_str()<<"::GetNumOfClients";
		return 0;
	}

	/// Check there are clients or not.
	bool MUSiiCTCPServerSocket::IsConnectedClients()
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "virtual function:: "<<this->GetNameOfMUSiiCClass().c_str()<<"::IsConnectedClients";
		return false;
	}


	////////////////////////////////////////
	/// Get the list of Connected client list
	igtl::MUSiiCVector<LP_CLIENT_DATA>::Pointer MUSiiCTCPServerSocket::GetConnectedClientList()
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "virtual function:: "<<this->GetNameOfMUSiiCClass().c_str()<<"::GetConnectedClientList";
		return NULL;
	}



//protected: ///Operation
	void MUSiiCTCPServerSocket::Initialize()
	{
	}

	

	
}