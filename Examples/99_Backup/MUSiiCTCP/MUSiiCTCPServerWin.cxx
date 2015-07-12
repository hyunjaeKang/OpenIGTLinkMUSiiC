/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Philipp J Stolka,Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.
***************************************************************************/

#include "MUSiiCTCPServerWin.h"
//public: ///Operations
/// Constructor
MUSiiCTCPServerWin::MUSiiCTCPServerWin()
{
	m_pNetworkThread      = igtl::MultiThreader::New();
	
	m_iListeningThreadIdx = 0;
	m_bListeningThread    = 0;
	m_iNetworkThreadIdx   = false;
	m_bNetworkThread      = false;

	m_pPerIOData          = NULL;
    m_pPerClientData      = NULL;

	m_ServerSocket        = 0;
	m_iRecvBytes          = 0;
	m_iFlag               = 0;

	m_listPerSocket.clear();

	/// Initialize Critical Section
	InitializeCriticalSection(&m_CS);
	m_Profile.SetSampleSizeOfFPS(100);
}
/// Deconstructor
MUSiiCTCPServerWin::~MUSiiCTCPServerWin()
{
	DeleteCriticalSection(&m_CS);
}

/// Create ServerSocket
/// Input:: port number
bool MUSiiCTCPServerWin::CreateServer(int port)
{
	/// 01.Initialize Server Socket and Completion Port
	if(!InitSocket())
		return false;

	/// 02.Initialize a object of SOCKADDR_IN
	ZeroMemory(&m_ServerAddr, sizeof(SOCKADDR_IN));
	m_ServerAddr.sin_family      = AF_INET;
	m_ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	/// Set the Server socket with a given port number
	m_ServerAddr.sin_port        = htons(port);

	/// 03.Bind
	if(bind(m_ServerSocket, (PSOCKADDR)&m_ServerAddr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		MUSiiC_LOG(logERROR) << "MUSiiCTCPServerWin::Bind Error";
		CloseSocket(m_ServerSocket);
		return false;
	}

	/// 04.Listen
	if(listen(m_ServerSocket, 5) == SOCKET_ERROR)
	{
		MUSiiC_LOG(logERROR) << "MUSiiCTCPServerWin::Listen Error";
		CloseSocket(m_ServerSocket);
		return false;
	}

	/// 05.Start listen-thread and working-thread
	m_bListeningThread = true;
	m_iListeningThreadIdx = m_pNetworkThread->SpawnThread((igtl::ThreadFunctionType)&ListeningThread, this);

	m_bNetworkThread = true;
	m_iNetworkThreadIdx = m_pNetworkThread->SpawnThread((igtl::ThreadFunctionType)&WorkingThread, this);


	return true;
}

/// Thread function
void* MUSiiCTCPServerWin::ListeningThread(void* ptr)
{
	igtl::MultiThreader::ThreadInfo* info	= static_cast<igtl::MultiThreader::ThreadInfo*>(ptr);
	MUSiiCTCPServerWin* pTaskClass	= static_cast<MUSiiCTCPServerWin*>(info->UserData);
		
	return pTaskClass->Listening();
}
/// Listening function
void* MUSiiCTCPServerWin::Listening()
{
	do
	{
		SOCKET hClientSock;
		SOCKADDR_IN ClientAddr;
		int addrLen = sizeof(ClientAddr);

		hClientSock = accept(m_ServerSocket, (PSOCKADDR)&ClientAddr, &addrLen);
		/// Notify new Client is connected
		/// Call a callback function or leave log message

		///////////////////////////////////////////
		m_pPerClientData = (LPPER_CLIENT_DATA)malloc(sizeof(PER_CLIENT_DATA));
		/// Client Socket
		m_pPerClientData->hClntSocket = hClientSock;
		/// Copy client address
		memcpy(&(m_pPerClientData->clntAddr), &ClientAddr, addrLen);
		/// Add new client to the list of connected client
		AddNewClients(m_pPerClientData);
		/// Set new client to IOCP
		CreateIoCompletionPort((HANDLE)m_pPerClientData->hClntSocket, m_hCompletionPort, (DWORD)m_pPerClientData, 0); 
		/// TO DO ::Receive IGTL Header
		IOCP_Recv_IGTLHEADER(m_pPerClientData);

	}while(m_bListeningThread);
	return NULL;
}

/// Thread function
void* MUSiiCTCPServerWin::WorkingThread(void* ptr)
{
	igtl::MultiThreader::ThreadInfo* info	= static_cast<igtl::MultiThreader::ThreadInfo*>(ptr);
	MUSiiCTCPServerWin* pTaskClass	= static_cast<MUSiiCTCPServerWin*>(info->UserData);
		
	return pTaskClass->Networking();
}
/// Check completion socket
void* MUSiiCTCPServerWin::Networking()
{
	LPPER_CLIENT_DATA pPerSocketData = NULL;
	LPPER_IO_DATA pPerIOData = NULL;
	DWORD dwTransfer;
	bool ret;

	while(m_bNetworkThread)
	{
		ret = GetQueuedCompletionStatus(m_hCompletionPort, &dwTransfer, 
			                            (LPDWORD)&pPerSocketData,
										(LPOVERLAPPED*)&pPerIOData, INFINITE);

		if(dwTransfer == 0)
		{
			if(pPerIOData)
			{
				printf("Disconnected %s client\n", inet_ntoa(pPerSocketData->clntAddr.sin_addr));
				RemoveClient(pPerSocketData);

				CloseSocket(pPerSocketData->hClntSocket);
				delete pPerSocketData;
				delete pPerIOData;
			}
			continue;
		}

		/// Got Header of IGTL Message
		if(pPerIOData->DataType == 0)
		{
			IOCP_Recv_IGTLBODY(pPerSocketData, pPerIOData);
		}
		else if(pPerIOData->DataType == 1) /// Got Body of IGTL Message
		{
			pPerIOData->RecvDataSize += dwTransfer;
			if(pPerIOData->RecvDataSize == pPerIOData->DataSize)
			{
				GetIGTLMessage(pPerIOData);
				IOCP_Recv_IGTLHEADER(pPerSocketData);
			}
			else
			{
				pPerIOData->wsaBuf.buf = (char*)pPerIOData->IGTLMsg->GetPackBodyPointer() + pPerIOData->RecvDataSize ;
				pPerIOData->wsaBuf.len = pPerIOData->DataSize - pPerIOData->RecvDataSize;
				pPerIOData->DataSize = pPerIOData->IGTLMsg->GetBodySizeToRead();
				pPerIOData->DataType = 1;
				m_iFlag = 0;

				int error = WSARecv(pPerSocketData->hClntSocket,
									&(pPerIOData->wsaBuf),
									1,
									&m_RecvDataSize,//(PerIOData->RecvDataSize),
									&m_iFlag,
									&(pPerIOData->overlapped),
									NULL);

				if(error == 0)
				{
					//printf("Call WSARecv fucntion to receive IGTL BODY Message to %s\n", inet_ntoa(pPerSocketData->clntAddr.sin_addr));
				}
				else if(error == SOCKET_ERROR && WSAGetLastError() == WSA_IO_PENDING)
				{
					//printf("Request WSARecv fucntion to receive IGTL BODY Message to %s\n", inet_ntoa(pPerSocketData->clntAddr.sin_addr));
				}
				else
				{
					//printf("Failed to call WSARecv Function\n");
					/*CloseSocket(client->hClntSocket);
					delete client;
					delete PerIOData;*/
				}
			}

			
		}



	}
	return NULL;
}

//protected: /// Operations
bool MUSiiCTCPServerWin::InitSocket()
{
	///Initialize WinSock
	if(WSAStartup(MAKEWORD(2,2), &m_WsaData) != 0)
	{
		MUSiiC_LOG(logERROR) << "MUSiiCTCPServerWin::WSAStartup Error";
		return false;
	}

	/// Create a Server Socket for listening a connection request from a client
	m_ServerSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if(m_ServerSocket == INVALID_SOCKET)
	{
		MUSiiC_LOG(logERROR) << "MUSiiCTCPServerWin::WSASocket Error (Server Socket)";
		return false;
	}

	/// Create Completion Port
	m_hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if(m_hCompletionPort == NULL)
	{
		MUSiiC_LOG(logERROR) << "MUSiiCTCPServerWin::CreateIoCompletionPort Error";
		/// To Do:: Create close socket function
		CloseSocket(m_ServerSocket);
		return false;
	}

	return true;
}

int MUSiiCTCPServerWin::CloseSocket(SOCKET s)
{	
	int r(0);
	/// Check Socket
	if(s != INVALID_SOCKET)
	{
		MUSiiC_LOG(logINFO) << "MUSiiCTCPServerWin::Close Server Socket";
		/// Close socket
		r = closesocket(s);
	}
	return r;
}

void MUSiiCTCPServerWin::AddNewClients(LPPER_CLIENT_DATA client)
{
	EnterCriticalSection(&m_CS);
	m_listPerSocket.push_back(client);
	LeaveCriticalSection(&m_CS);
}

void MUSiiCTCPServerWin::RemoveClient(LPPER_CLIENT_DATA client)
{
	EnterCriticalSection(&m_CS);
	m_listPerSocket.remove(client);
	LeaveCriticalSection(&m_CS);
}


int MUSiiCTCPServerWin::IOCP_Recv_IGTLHEADER(LPPER_CLIENT_DATA client)
{
	//printf("IOCP_Recv_IGTLHEADER\n");
	/// Initialize Data Structure
	LPPER_IO_DATA PerIOData = new PER_IO_DATA;
	ZeroMemory(PerIOData, sizeof(PER_IO_DATA));
	//Initialize IGTL MessageBase
	PerIOData->IGTLMsg = igtl::MessageBase::New();
	PerIOData->IGTLMsg->InitPack();
	PerIOData->wsaBuf.buf = (char*)PerIOData->IGTLMsg->GetPackPointer();
	PerIOData->wsaBuf.len = PerIOData->IGTLMsg->GetPackSize();
	PerIOData->DataSize = PerIOData->IGTLMsg->GetPackSize();
	PerIOData->DataType = 0;
	m_iFlag = 0;
	DWORD RecvDataSize;
	int error = WSARecv(client->hClntSocket,
		                &(PerIOData->wsaBuf),
			            1,
			            &m_RecvDataSize,//&(PerIOData->RecvDataSize),
						&m_iFlag,
			            &(PerIOData->overlapped),
			            NULL);

	if(error == 0)
	{
		//printf("Call WSARecv fucntion to receive IGTL Header Message to %s\n", inet_ntoa(client->clntAddr.sin_addr));
	}
	else if(error == SOCKET_ERROR && WSAGetLastError() == WSA_IO_PENDING)
	{
		//printf("Request WSARecv fucntion to receive IGTL Header Message to %s\n", inet_ntoa(client->clntAddr.sin_addr));
	}
	else
	{
		//printf("Failed to call WSARecv Function\n");
		/*CloseSocket(client->hClntSocket);
		delete client;
		delete PerIOData;*/
	}

	return error;
}

int MUSiiCTCPServerWin::IOCP_Recv_IGTLBODY(LPPER_CLIENT_DATA client, LPPER_IO_DATA PerIOData)
{
	//printf("IOCP_Recv_IGTLBODY\n");
	PerIOData->IGTLMsg->Unpack();
	PerIOData->IGTLMsg->AllocatePack();

	PerIOData->wsaBuf.buf = (char*)PerIOData->IGTLMsg->GetPackBodyPointer();
	PerIOData->wsaBuf.len = PerIOData->IGTLMsg->GetBodySizeToRead();
	PerIOData->DataSize = PerIOData->IGTLMsg->GetBodySizeToRead();
	PerIOData->DataType = 1;
	m_iFlag = 0;

	int error = WSARecv(client->hClntSocket,
		                &(PerIOData->wsaBuf),
			            1,
			            &m_RecvDataSize,//(PerIOData->RecvDataSize),
			            &m_iFlag,
			            &(PerIOData->overlapped),
			            NULL);

	if(error == 0)
	{
		//printf("Call WSARecv fucntion to receive IGTL BODY Message to %s\n", inet_ntoa(client->clntAddr.sin_addr));
	}
	else if(error == SOCKET_ERROR && WSAGetLastError() == WSA_IO_PENDING)
	{
		//printf("Request WSARecv fucntion to receive IGTL BODY Message to %s\n", inet_ntoa(client->clntAddr.sin_addr));
	}
	else
	{
		//printf("Failed to call WSARecv Function\n");
		/*CloseSocket(client->hClntSocket);
		delete client;
		delete PerIOData;*/
	}

	return error;
}


int MUSiiCTCPServerWin::GetIGTLMessage(LPPER_IO_DATA PerIOData)
{
	//printf("GetIGTLMessage\n");
	int c = PerIOData->IGTLMsg->Unpack(1);
	if(c & igtl::MessageHeader::UNPACK_BODY)
	{
		igtl::MessageBase::Pointer msg = PerIOData->IGTLMsg;

		igtl::ImageMessage::Pointer img = igtl::RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(msg);

		igtl::Matrix4x4 matrix;
		img->GetMatrix(matrix);
		//igtl::PrintMatrix(matrix);
		std::cerr << std::endl;
		std::cerr << "FPS is: " <<  m_Profile.GetFPS() << std::endl;
		delete PerIOData;

		return 1;
	}
	else
	{
		delete PerIOData;
		return 0;
	}
}