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

#include "MUSiiCTCPClientSocket.h"
#include "MUSiiCIGTLUtil.h"

namespace igtl
{
	/// Constructor
	MUSiiCTCPClientSocket::MUSiiCTCPClientSocket()
	{
		m_pNameOfClass="MUSiiCTCPClientSocket";
		Initialize();
	}

	/// Deconstructor
	MUSiiCTCPClientSocket::~MUSiiCTCPClientSocket()
	{
		
	}

	//////////////////////////////////////////////////////////////////////////
	///// Connect to Server(Host) with hostname(host-ip-address) and port
	int MUSiiCTCPClientSocket::ConnectToHost(const char* hostname, int port, std::string filter, bool sync, bool reference, bool reconnect)
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "virtual function:: "<<GetNameOfMUSiiCClass().c_str() <<"::ConnectToHost";

		return 0;
	}
	
	
	/// Try to reconnect to Server(Host)
	int MUSiiCTCPClientSocket::ReConnectToHost()
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "virtual function:: "<<GetNameOfMUSiiCClass().c_str()<<"::ReConnectToHost";

		return 0;
	}

	/// Close client socket
	void MUSiiCTCPClientSocket::CloseClientSocket(LP_CLIENT_DATA pClient)
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "virtual function:: "<<GetNameOfMUSiiCClass().c_str() <<"::CloseClientSocket";
	}

	/// Close All created clients
	int MUSiiCTCPClientSocket::CloseAllClients()
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "virtual function:: "<<GetNameOfMUSiiCClass().c_str() <<"::CloseAllClients";

		return 0;
	}


///////////////////////////////////////////////////////////////////////////////
	void MUSiiCTCPClientSocket::Initialize()
	{

	}

}