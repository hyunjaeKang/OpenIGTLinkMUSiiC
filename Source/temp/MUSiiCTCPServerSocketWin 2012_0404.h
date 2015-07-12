/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/

#ifndef __MUSIIC_TCP_SERVER_SOCKET_WIN_
#define __MUSIIC_TCP_SERVER_SOCKET_WIN_

#include "MUSiiCTCPServerSocket.h"

#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include "igtlOSUtil.h"
#include "MUSiiCUtil.h"
#include <MUSiiCProfile.h>
#include <list>

/// Loading the library of WinSock2 
#pragma comment(lib, "Ws2_32.lib");


namespace igtl
{

typedef struct
{
	SOCKET hClntSocket;
	SOCKADDR_IN clntAddr;
	/////////////////////////
	OVERLAPPED overlapped;
	WSABUF wsaSendBuf;
	int n_iExpectSumOfSent;
	int n_iSumOfSent;
	igtl::MessageBase::Pointer TxIGTLMsg;
	////////////////////////
	WSABUF wsaRecvBuf;
	int n_iExpectSumOfRecv;
	int n_iSumOfRecv;
	igtl::MessageBase::Pointer RxIGTLMsg;

	//int DataType;
	int RxMode;
	int TXMode;
	int IO_MODE;

} PER_CLIENT_DATA, *LPPER_CLIENT_DATA;

//typedef struct
//{
//	OVERLAPPED overlapped;
//	//char* data_ptr;
//	WSABUF wsaBuf;
//	int DataSize;
//	DWORD RecvDataSize;
//	igtl::MessageBase::Pointer IGTLMsg;
//	// 0: Header
//	// 1: Body
//	int DataType;
//
//
//}PER_IO_DATA, *LPPER_IO_DATA;


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
	
	/// Get the pointer of NetworkBuffer
	igtl::MUSiiCIGTLMsgVector::Pointer GetNetworkBuffer();
	
	/// Creater Server Socket
	int CreateServer(int port, bool useSelfDataIF = true);

	/// Close server socket
	int CloseServer();

	/// Get Num of connected-clients
	int GetNumOfClients();

	/// Check there are clients or not.
	bool IsConnectedClients();

	/////////////////////////////////////////////////////////////
	///Put igtl::MessageBase::Pointer to MUSiiCIODevice
	///          virtual function.
	virtual int PutIGTLMessage(igtl::MessageBase::Pointer msg);

	/////////////////////////////////////////////////////////////
	///Try Put igtl::MessageBase::Pointer to MUSiiCIODevice
	///          virtual function.
	virtual int TryPutIGTLMessage(igtl::MessageBase::Pointer msg);
	
protected: ///Operation
	virtual void Initialize();

	/// Client-Network Task function is implemented in this function.
	//virtual int Task();
	virtual int TaskFunction(int numOfRun, int taskInfo, void* ptr = NULL, void* data1 = NULL, void* data2 = NULL, void* data3 = NULL);
	/// The task function for listening socket
	int ListenTask(int numOfRun, int taskInfo, void* ptr = NULL, void* data1 = NULL, void* data2 = NULL, void* data3 = NULL);
	/// The task function for listening socket
	int SendTask(int numOfRun, int taskInfo, void* ptr = NULL, void* data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	//// Initialize WinSock
	bool InitSocket();
	//// Close a socket
	int CloseSocket(SOCKET s);
	//// Add a new client socket
	void AddNewClients(LPPER_CLIENT_DATA client);
	//// Remove a new client socket
	void RemoveClient(LPPER_CLIENT_DATA client);
	
	//void IOCP_Recv(LPPER_CLIENT_DATA, char* des, int sz);
	
	/// Receive Data
	int IOCP_Recv(LPPER_CLIENT_DATA client, std::string description = " ");
	/// Receive IGTL_HEADER using IOCP
	int IOCP_Recv_IGTLHEADER(LPPER_CLIENT_DATA client, DWORD dwsize);
	/// Receive IGTL_BODY using IOCP
	int IOCP_Recv_IGTLBODY(LPPER_CLIENT_DATA client,DWORD dwsize);
	/// Get IGTL Message from clients
	int GetIGTLMessage(LPPER_CLIENT_DATA client);

	/// Send Data
	int IOCP_Send(LPPER_CLIENT_DATA client,std::string description="");
	/// Send out IGTL Message
	int IOCP_SendIGTL(LPPER_CLIENT_DATA client, DWORD dwsize);

	////// Post-processing for TCP-IP communication
	int TCPServerPostProcessing(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, void* data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	bool RemoveAllClientData();
	// mode 0: Receiving
	// mode 1: Sending
	int ErrorHandling(int errorcode, LPPER_CLIENT_DATA client, std::string desp = " ", int mode = 0);

public:/// Attributes
	enum
	{
		M_IOCP_RX_INIT = 0,
		M_IOCP_Rx_IGTLHEADER,
		M_IOCP_Rx_IGTLHEADERDONE,
		M_IOCP_Rx_IGTLBODY,
		M_IOCP_Rx_IGTLBODYDONE,
		M_IOCP_TX_INIT,
		M_IOCP_Tx_IGTL,
		M_IOCP_Tx_IGTLDONE,
		M_IOCP_Rx,
		M_IOCP_Tx,
	};
protected:/// Attributes
	//// WinSock
	WSADATA								m_WsaData;
	HANDLE								m_hCompletionPort;
	SYSTEM_INFO							m_SystemInfo;
	SOCKADDR_IN							m_ServerAddr;

	/// ServerSock
	SOCKET								m_ListenSocket;
	int									m_iRecvBytes;
	DWORD								m_iFlag;

	/////
	LPPER_CLIENT_DATA					m_pPerClientData;

	/// Client socket container
	//std::list<LPPER_CLIENT_DATA>		m_listPerSocket;
	igtl::MUSiiCVector<LPPER_CLIENT_DATA>::Pointer		m_listPerSocket;


	int									m_iListeningThreadIdx;
	bool								m_bListeningThread;
	int									m_iNetworkThreadIdx;
	bool								m_bNetworkThread;
	int									m_iSendThreadIdx;
	bool								m_bSendThread;


	//// Critical section
	CRITICAL_SECTION					m_CS;

	/// Information of download
	DWORD								m_RecvDataSize;

	/// MUSiiCTaskObject for listening task
	igtl::MUSiiCTaskObject::Pointer		m_pListeningTask;
	igtl::MUSiiCTaskObject::Pointer		m_pSendingTask;

	igtl::MUSiiCProfile					m_Profile;

	int									m_iServerSocket;
	bool								m_buseSelfDataIF;

	///Network Buffer
	igtl::MUSiiCIGTLMsgVector::Pointer m_pInputNetworkBuffer;
	igtl::MUSiiCIGTLMsgVector::Pointer m_pOutputNetworkBuffer;

	igtl::MutexLock::Pointer           m_pFastMutex;

};

}
#endif