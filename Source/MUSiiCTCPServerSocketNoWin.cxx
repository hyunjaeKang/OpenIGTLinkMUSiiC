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
#include "MUSiiCTCPServerSocketNoWin.h"

namespace igtl
{
/// Constructor
	/// Constructor
	MUSiiCTCPServerSocketNoWin::MUSiiCTCPServerSocketNoWin()
	{
		m_pNameOfClass="MUSiiCTCPServerSocketNoWin";
		Initialize();
	}
	
	/// Deconstructor
	MUSiiCTCPServerSocketNoWin::~MUSiiCTCPServerSocketNoWin()
	{
		this->CloseServer();
	}

	////////////////////////////////////////////////////////////////////

	/// Creater Server Socket
	int MUSiiCTCPServerSocketNoWin::CreateServer(int port)
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "virtual function:: "<<this->GetNameOfMUSiiCClass().c_str()<<"::CreateServer";

		return 0;
	}

	/// Close server socket
	int MUSiiCTCPServerSocketNoWin::CloseServer()
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "virtual function:: "<<this->GetNameOfMUSiiCClass().c_str() <<"::CloseServer";
		return 0;
	}

	/// Get Num of connected-clients
	int MUSiiCTCPServerSocketNoWin::GetNumOfClients()
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "virtual function:: "<<this->GetNameOfMUSiiCClass().c_str() <<"::GetNumOfClients";
		return 0;
	}

	/// Check there are clients or not.
	bool MUSiiCTCPServerSocketNoWin::IsConnectedClients()
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "virtual function:: "<<this->GetNameOfMUSiiCClass().c_str()<<"::IsConnectedClients";
		return false;
	}

/////Protected::operations
	void MUSiiCTCPServerSocketNoWin::Initialize()
	{
		
	}
	


}