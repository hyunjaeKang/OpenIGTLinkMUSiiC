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

#ifndef __MUSIIC_TCP_CLIENT_
#define __MUSIIC_TCP_CLIENT_

#include "MUSiiCTCPIO.h"

#if defined(WIN32) || defined (_WIN32) || defined (__WIN32__)
#include "MUSiiCTCPClientSocketWin.h"
#else
#include "MUSiiCTCPClientSocketNoWin.h"
#endif

namespace igtl
{

class IGTLMCommon_EXPORT MUSiiCTCPClient : public MUSiiCTCPIO 
{
public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCTCPClient			    Self;
	typedef MUSiiCTCPIO					Superclass;
	typedef SmartPointer<Self>			Pointer;
	typedef SmartPointer<const Self>	ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	/// Constructor
	MUSiiCTCPClient();
	
	/// Deconstructor
	~MUSiiCTCPClient();

	///////////////////////////////////////////////////////////
	/// The information of TCP_IO  
	virtual int GetTCPStatus();

	//////////////////////////////////////////////////////////////////////

	///// Connect to Server(Host) with hostname(host-ip-address) and port
	/*int ConnectToHost(const char* hostname, int port, bool reconnect = true, std::string filter ="", bool sync=false, bool reference = false);*/

	///// Connect to Server(Host) with hostname(host-ip-address) and port
	virtual int ConnectToHost(const char* hostname, int port, std::string filter ="", bool sync = false, bool reference = false, bool reconnect = true);
	
	/// Try to reconnect to Server(Host)
	int ReConnectToHost();


	/// Close client socket
	void CloseClientSocket(LP_CLIENT_DATA pClient= NULL);


	/// Close All created clients
	int CloseAllClients();

	//// User defined Callback function
	/// Declare a function that is called MUSiiCCallbackInterface
	virtual int PreCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	/// Declare a function that is called MUSiiCCallbackInterface
	virtual int PostCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	///////////////////////////////////////////////////////////////
	/////Put igtl::MessageBase::Pointer to MUSiiCIODevice
	/////          virtual function.
	//virtual int PutIGTLMessage(igtl::MessageBase::Pointer msg);

	///////////////////////////////////////////////////////////////
	/////Try Put igtl::MessageBase::Pointer to MUSiiCIODevice
	/////          virtual function.
	//virtual int TryPutIGTLMessage(igtl::MessageBase::Pointer msg);

protected: ///Operation
	virtual void Initialize();

	
public:/// Attributes
	
protected:/// Attributes

	igtl::MUSiiCTCPClientSocket::Pointer m_pMUSiiCTCPClientSocket;

#if defined(WIN32) || defined (_WIN32) || defined (__WIN32__)
	igtl::MUSiiCTCPClientSocketWin::Pointer m_pMUSiiCTCPClientSocketWin; 
#else
	igtl::MUSiiCTCPClientSocketNoWin::Pointer m_pMUSiiCTCPClientSocketNoWin;
#endif
};
}
#endif
