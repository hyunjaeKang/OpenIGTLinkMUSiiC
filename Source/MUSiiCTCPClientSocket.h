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

#ifndef __MUSIIC_TCP_CLIENT_SOCKET_
#define __MUSIIC_TCP_CLIENT_SOCKET_

#include "MUSiiCTCPIO.h"


namespace igtl
{
class IGTLMCommon_EXPORT MUSiiCTCPClientSocket : public MUSiiCTCPIO 
{
public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCTCPClientSocket			Self;
	typedef MUSiiCTCPIO						Superclass;
	typedef SmartPointer<Self>				Pointer;
	typedef SmartPointer<const Self>		ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	/// Constructor
	MUSiiCTCPClientSocket();
	
	/// Deconstructor
	~MUSiiCTCPClientSocket();

	///// Connect to Server(Host) with hostname(host-ip-address) and port
	////int ConnectToHost(const char* hostname, int port, bool reconnect = true);
	//virtual int ConnectToHost(const char* hostname, int port, bool reconnect = true, std::string filter ="", bool sync= false,bool reference = false);

	///// Connect to Server(Host) with hostname(host-ip-address) and port
	virtual int ConnectToHost(const char* hostname, int port, std::string filter ="", bool sync = false, bool reference = false, bool reconnect = true);
	
	
	/// Try to reconnect to Server(Host)
	virtual int ReConnectToHost();

	/// Close client socket
	virtual void CloseClientSocket(LP_CLIENT_DATA pClient= NULL);

	/// Close All created clients
	virtual int CloseAllClients();
	
protected: ///Operation
	virtual void Initialize();

	
public:/// Attributes

};
}
#endif
