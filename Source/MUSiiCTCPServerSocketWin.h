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

#ifndef __MUSIIC_TCP_SERVER_SOCKET_WIN_
#define __MUSIIC_TCP_SERVER_SOCKET_WIN_

#include "MUSiiCTCPServerSocket.h"

namespace igtl
{

class IGTLMCommon_EXPORT MUSiiCTCPServerSocketWin : public MUSiiCTCPServerSocket 
{
public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCTCPServerSocketWin			Self;
	typedef MUSiiCTCPServerSocket				Superclass;
	typedef SmartPointer<Self>					Pointer;
	typedef SmartPointer<const Self>			ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	/////////////////////////////////////////////////////////////
	/// Constructor
	MUSiiCTCPServerSocketWin();
	
	/// Deconstructor
	~MUSiiCTCPServerSocketWin();
		
	/// Creater Server Socket
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

	/// Client-Network Task function is implemented in this function.
	//virtual int Task();
	virtual int TaskFunction(int numOfRun, int taskInfo, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);
	/// The task function for listening socket
	int ListenTask(int numOfRun, int taskInfo, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);
	/// The task function for listening socket
	int SendTask(int numOfRun, int taskInfo, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	//// Initialize WinSock
	bool InitSocket();
	//// Close a socket
	int CloseSocket(SOCKET s);
	//// Add a new client socket
	void AddNewClients(LP_CLIENT_DATA client);
	//// Remove a new client socket
	void RemoveClient(LP_CLIENT_DATA client);
	
	//void IOCP_Recv(LPPER_CLIENT_DATA, char* des, int sz);
	
	
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
	

	////// Post-processing for TCP-IP communication
	/// To Do :: cannon96 
	/// Delete this function
	int TCPServerPostProcessing(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	bool RemoveAllClientData();
	// mode 0: Receiving
	// mode 1: Sending
	int ErrorHandling(int errorcode, LP_CLIENT_DATA client, std::string desp = " ", int mode = 0);

public:/// Attributes
	
protected:/// Attributes
	//// WinSock
	WSADATA							 				m_WsaData;
	HANDLE											m_hCompletionPort;
	SYSTEM_INFO										m_SystemInfo;
	SOCKADDR_IN										m_ServerAddr;

	/// ServerSock
	SOCKET											m_ListenSocket;
	int												m_iRecvBytes;
	DWORD											m_iFlag;

	/////
	LP_CLIENT_DATA									m_pPerClientData;
	LP_IO_DATA										m_pPerIOData;

	/// Client socket container
	igtl::MUSiiCVector<LP_CLIENT_DATA>::Pointer		m_listPerSocket;

	/// Information of Thread
	int												m_iListeningThreadIdx;
	bool											m_bListeningThread;
	int												m_iNetworkThreadIdx;
	bool											m_bNetworkThread;
	int												m_iSendThreadIdx;
	bool											m_bSendThread;


	/// Information of download
	DWORD											m_RecvDataSize;

	/// MUSiiCTaskObject for listening task
	igtl::MUSiiCTaskObject::Pointer		            m_pListeningTask;
	igtl::MUSiiCTaskObject::Pointer		            m_pSendingTask;

	igtl::MUSiiCProfile								m_Profile;

	int												m_iServerSocket; // Do I need this value
	bool								            m_buseSelfDataIF;

	igtl::MutexLock::Pointer						m_pFastMutex;

	bool											m_bInitWinSock;

};

}
#endif