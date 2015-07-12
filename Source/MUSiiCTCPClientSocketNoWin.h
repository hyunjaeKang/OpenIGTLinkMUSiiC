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

#ifndef __MUSIIC_TCP_CLIENT_SOCKET_NO_WIN_
#define __MUSIIC_TCP_CLIENT_SOCKET_NO_WIN_

#include "MUSiiCTCPClientSocket.h"

namespace igtl
{

class IGTLMCommon_EXPORT MUSiiCTCPClientSocketNoWin : public MUSiiCTCPClientSocket 
{
public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCTCPClientSocketNoWin			Self;
	typedef MUSiiCTCPClientSocket				Superclass;
	typedef SmartPointer<Self>					Pointer;
	typedef SmartPointer<const Self>			ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	/// Constructor
	MUSiiCTCPClientSocketNoWin();
	
	/// Deconstructor
	~MUSiiCTCPClientSocketNoWin();

	
	///// Connect to Server(Host) with hostname(host-ip-address) and port
	int ConnectToHost(const char* hostname, int port, bool reconnect = true);
	
	
	/// Try to reconnect to Server(Host)
	int ReConnectToHost();

	/// Close All created clients
	int CloseAllClients();

protected: ///Operation
	virtual void Initialize();

public:/// Attributes
	
protected:/// Attributes

	
};
}
#endif
