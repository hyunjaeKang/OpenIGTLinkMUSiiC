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

#include "MUSiiCTCPClientSocketNoWin.h"
#include "MUSiiCIGTLUtil.h"

namespace igtl
{
	/// Constructor
	MUSiiCTCPClientSocketNoWin::MUSiiCTCPClientSocketNoWin()
	{
		m_pNameOfClass="MUSiiCTCPClientSocketNoWin";
		Initialize();
	}

	/// Deconstructor
	MUSiiCTCPClientSocketNoWin::~MUSiiCTCPClientSocketNoWin()
	{
		
	}

	//////////////////////////////////////////////////////////////////////////
	///// Connect to Server(Host) with hostname(host-ip-address) and port
	int MUSiiCTCPClientSocketNoWin::ConnectToHost(const char* hostname, int port, bool reconnect)
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "virtual function:: "<<GetNameOfMUSiiCClass().c_str()<<"::ConnectToHost";

		return 0;
	}
	
	
	/// Try to reconnect to Server(Host)
	int MUSiiCTCPClientSocketNoWin::ReConnectToHost()
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "virtual function:: "<<GetNameOfMUSiiCClass().c_str() <<"::ReConnectToHost";

		return 0;
	}

	/// Close All created clients
	int MUSiiCTCPClientSocketNoWin::CloseAllClients()
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "virtual function:: "<<GetNameOfMUSiiCClass().c_str() <<"::CloseAllClients";

		return 0;
	}


///////protected function

	void MUSiiCTCPClientSocketNoWin::Initialize()
	{
		
	}

}