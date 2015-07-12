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


#ifndef __MUSIIC_TCP_CLIENT_SOCKET_WIN_
#define __MUSIIC_TCP_CLIENT_SOCKET_WIN_

#include "MUSiiCTCPClientSocket.h"

namespace igtl
{

class IGTLMCommon_EXPORT MUSiiCTCPClientSocketWin : public MUSiiCTCPClientSocket
{
public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCTCPClientSocketWin			Self;
	typedef MUSiiCTCPClientSocket				Superclass;
	typedef SmartPointer<Self>					Pointer;
	typedef SmartPointer<const Self>			ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	/////////////////////////////////////////////////////////////
	/// Constructor
	MUSiiCTCPClientSocketWin();
	
	/// Deconstructor
	~MUSiiCTCPClientSocketWin();

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

	/// Client-Network Task function is implemented in this function.
	//virtual int Task();
	virtual int TaskFunction(int numOfRun, int taskInfo, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);
	/// The task function for listening socket
	int ConnectTask(int numOfRun, int taskInfo, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);
	/// The task function for listening socket
	int SendTask(int numOfRun, int taskInfo, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	//// Initialize WinSock
	bool InitSocket();

	///Create Client Socket
	LP_CLIENT_DATA CreaterClientSocket();
	
	//// Close a socket
	int CloseSocket(SOCKET s);

	//// Add a new client socket
	void AddNewClients(LP_CLIENT_DATA client);
	//// Remove a new client socket
	void RemoveClient(LP_CLIENT_DATA client);

	/// Send IGTL Message
	int IOCP_Recv_IGTLMsg(LP_CLIENT_DATA client);
	/// Receive Data
	int IOCP_Recv(LP_CLIENT_DATA client, LP_IO_DATA IOdata, std::string description = " ");
	/// Receive IGTL_HEADER using IOCP
	int IOCP_Recv_IGTLHEADER(LP_CLIENT_DATA client, LP_IO_DATA IOdata, DWORD dwsize);
	/// Receive IGTL_BODY using IOCP
	int IOCP_Recv_IGTLBODY(LP_CLIENT_DATA client, LP_IO_DATA IOdata,DWORD dwsize);
	/// Get IGTL Message from clients
	//int GetIGTLMessage(LPPER_CLIENT_DATA client);
	int GetIGTLMessage(LP_CLIENT_DATA client, LP_IO_DATA IOdata);

	/// Send IGTL Message
	int IOCP_Send_IGTLMsg(LP_CLIENT_DATA client,igtl::MessageBase::Pointer msg);
	/// Send IGTL Message to All connected clients excluding pre-defined client
	int IOCP_Send_IGTLMsg_Exclude(LP_CLIENT_DATA client,igtl::MessageBase::Pointer msg);
	/// Send IGTL Message to All connected
	int IOCP_Send_IGTLMsg_ALLClients(igtl::MessageBase::Pointer msg);
	/// Send Data
	int IOCP_Send(LP_CLIENT_DATA client,LP_IO_DATA IOdata,std::string description="");
	/// Send out IGTL Message
	int IOCP_SendIGTL(LP_CLIENT_DATA client, LP_IO_DATA IOdata, DWORD dwsize);
	/// Send out IGTL Message
	int IOCP_SendIGTLDone(LP_CLIENT_DATA client, LP_IO_DATA IOdata);
	/// Send out MUSiiCIOFilter of client
	int IOCP_SendMUSiiCIOFilter(LP_CLIENT_DATA client);
	/// Send out std::string of MUSiiCIOFilter of client
	int _IOCP_SendMUSiiCIOFilter(LP_CLIENT_DATA client, std::string& filter);

	/// To Do :: cannon96 
	/// Delete this function
	////// Post-processing for TCP-IP communication
	int TCPServerPostProcessing(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);
	
	//////////////////////////////
	bool RemoveAllClientData();
	// mode 0: Receiving
	// mode 1: Sending
	int ErrorHandling(int errorcode, LP_CLIENT_DATA client, std::string desp = " ", int mode = 0);

	/////////////////////////////
	int StartNetworkThreads();


	////////////////////////////////////////
	/// Get the list of Connected client list
	igtl::MUSiiCVector<LP_CLIENT_DATA>::Pointer GetConnectedClientList();

	/// Get the number of connected client list
	int GetNumOfConnectedClients();
	

public:/// Attributes

	
protected:/// Attributes
	/// Client socket container
	igtl::MUSiiCVector<LP_CLIENT_DATA>::Pointer	m_listClientSocket;

	igtl::MUSiiCVector<LP_CLIENT_DATA>::Pointer	m_listClientSocketConnect;

	//// WinSock
	WSADATA							 	        m_WsaData;
	HANDLE								        m_hCompletionPort;
	DWORD								        m_iFlag;

	bool										m_bInitSocket;

	LP_CLIENT_DATA								m_pClient;
	LP_IO_DATA							        m_pPerIOData;
	LP_CLIENT_DATA								m_pLastConnectedClient;


	/// MUSiiCTaskObject for Connect task
	igtl::MUSiiCTaskObject::Pointer		        m_pConnectTask;
	/// MUSiiCTaskObject for Sending task
	igtl::MUSiiCTaskObject::Pointer		        m_pSendingTask;

	/// Information of Thread
	int								            m_iConnectThreadIdx;
	bool								        m_bConnectThread;
	int									        m_iNetworkThreadIdx;
	bool								        m_bNetworkThread;
	int									        m_iSendThreadIdx;
	bool								        m_bSendThread;

	bool										m_bClientThreadsRun;
	
	igtl::MUSiiCProfile					        m_Profile;

	igtl::MutexLock::Pointer                    m_pFastMutex;	
};
}
#endif
