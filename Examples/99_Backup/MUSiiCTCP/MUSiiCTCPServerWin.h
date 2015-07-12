/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Philipp J Stolka,Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.
***************************************************************************/
#ifndef _MUSiiCTCPServerBi__
#define _MUSiiCTCPServerBi__
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

#include "igtlMultiThreader.h"
#include "igtlOSUtil.h"
#include "MUSiiCUtil.h"
#include <MUSiiCProfile.h>
#include <list>

#pragma 
#pragma comment(lib, "Ws2_32.lib");//comment(lib, "Ws2_32.lib");

typedef struct
{
	SOCKET hClntSocket;
	SOCKADDR_IN clntAddr;

} PER_CLIENT_DATA, *LPPER_CLIENT_DATA;

typedef struct
{
	OVERLAPPED overlapped;
	//char* data_ptr;
	WSABUF wsaBuf;
	int DataSize;
	DWORD RecvDataSize;
	igtl::MessageBase::Pointer IGTLMsg;
	// 0: Header
	// 1: Body
	int DataType;


}PER_IO_DATA, *LPPER_IO_DATA;

class MUSiiCTCPServerWin
{
public: ///Operations
	/// Constructor
	MUSiiCTCPServerWin();
	/// Deconstructor
	~MUSiiCTCPServerWin();

	/// Create ServerSocket
	/// Input:: port number
	bool CreateServer(int port);

	/// Thread function
	static void* ListeningThread(void* ptr);
	/// Listening function
	void* Listening();

	/// Thread function
	static void* WorkingThread(void* ptr);
	/// Check completion socket
	void* Networking();

protected: /// Operations
	bool InitSocket();
	int CloseSocket(SOCKET s);
	void AddNewClients(LPPER_CLIENT_DATA client);
	void RemoveClient(LPPER_CLIENT_DATA client);
	void IOCP_Recv(LPPER_CLIENT_DATA, char* des, int sz);
	int IOCP_Recv_IGTLHEADER(LPPER_CLIENT_DATA client);
	int IOCP_Recv_IGTLBODY(LPPER_CLIENT_DATA client, LPPER_IO_DATA PerIOData);
	int GetIGTLMessage(LPPER_IO_DATA PerIOData);

public: /// Attributes

protected: /// Attributes
	WSADATA                       m_WsaData;
	HANDLE                        m_hCompletionPort;
	SYSTEM_INFO                   m_SystemInfo;
	SOCKADDR_IN                   m_ServerAddr;

	LPPER_IO_DATA	              m_pPerIOData;
	LPPER_CLIENT_DATA             m_pPerClientData;

	SOCKET                        m_ServerSocket;
	int		                      m_iRecvBytes;
	DWORD                         m_iFlag;

	std::list<LPPER_CLIENT_DATA>  m_listPerSocket;

	int                           m_iListeningThreadIdx;
	bool                          m_bListeningThread;
	int                           m_iNetworkThreadIdx;
	bool                          m_bNetworkThread;
	igtl::MultiThreader::Pointer  m_pNetworkThread;

	CRITICAL_SECTION              m_CS;

	DWORD                         m_RecvDataSize;
	igtl::MUSiiCProfile           m_Profile;
};

#endif