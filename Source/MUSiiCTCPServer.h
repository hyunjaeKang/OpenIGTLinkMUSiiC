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

#ifndef __MUSIIC_TCP_SERVER__
#define __MUSIIC_TCP_SERVER__

#include "MUSiiCTCPIO.h"

#if defined(WIN32) || defined (_WIN32) || defined (__WIN32__)
#include "MUSiiCTCPServerSocketWin.h"
#else
#include "MUSiiCTCPServerSocketNoWin.h"
#endif

namespace igtl
{

class IGTLMCommon_EXPORT MUSiiCTCPServer : public MUSiiCTCPIO 
{
public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCTCPServer					Self;
	typedef MUSiiCTCPIO						Superclass;
	typedef SmartPointer<Self>				Pointer;
	typedef SmartPointer<const Self>		ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	/// Constructor
	MUSiiCTCPServer();
	
	/// Deconstructor
	~MUSiiCTCPServer();
	

	///////////////////////////////////////////////////////////
	/// The information of TCP_IO  
	virtual int GetTCPStatus();

	//////////////////////////////////////////////////////////////////////
	/// Creater Server Socket //
	virtual int CreateServer(int port);

	/// Close server socket
	virtual int CloseServer();

	/// Get Num of connected-clients
	virtual int GetNumOfClients();

	/// Check there are clients or not.
	virtual bool IsConnectedClients();

	////////////////////////////////////////
	/// Get the list of Connected client list
	igtl::MUSiiCVector<LP_CLIENT_DATA>::Pointer GetConnectedClientList();


protected: ///Operation
	virtual void Initialize();

public:/// Attributes
	
protected:/// Attributes
	
	igtl::MUSiiCTCPServerSocket::Pointer m_pMUSiiCTCPServerSocket;

#if defined(WIN32) || defined (_WIN32) || defined (__WIN32__)
	igtl::MUSiiCTCPServerSocketWin::Pointer m_pMUSiiCTCPServerSocketWin; 
#else
	igtl::MUSiiCTCPServerSocketNoWin::Pointer m_pMUSiiCTCPServerSocketNoWin;
#endif
};

}
#endif