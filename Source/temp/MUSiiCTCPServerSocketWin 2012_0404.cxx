/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/
#include "MUSiiCTCPServerSocketWin.h"

namespace igtl
{
	/// Constructor
	MUSiiCTCPServerSocketWin::MUSiiCTCPServerSocketWin()
	{
		m_pNameOfClass="MUSiiCTCPServerSocketWin";
		Initialize();
	}
	
	/// Deconstructor
	MUSiiCTCPServerSocketWin::~MUSiiCTCPServerSocketWin()
	{
		this->CloseServer();
		DeleteCriticalSection(&m_CS);
	}

	/// Creater Server Socket
	int MUSiiCTCPServerSocketWin::CreateServer(int port, bool useSelfDataIF)
	{
		m_iServerSocket   = port;
		m_buseSelfDataIF  = useSelfDataIF;
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
		if(bind(m_ListenSocket, (PSOCKADDR)&m_ServerAddr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
		{
			MUSiiC_LOG(logERROR) << "MUSiiCTCPServerWin::Bind Error";
			CloseSocket(m_ListenSocket);
			return false;
		}

		/// 04.Listen
		if(listen(m_ListenSocket, 5) == SOCKET_ERROR)
		{
			MUSiiC_LOG(logERROR) << "MUSiiCTCPServerWin::Listen Error";
			CloseSocket(m_ListenSocket);
			return false;
		}

		/// 05.Start listen-thread and working-thread
		m_tcp_status       = M_TCP_Server_Created;
		m_bNetworkThread   = true;
		m_bListeningThread = true;
		m_bSendThread      = true;
		
		this->SetEnableThread(true, MUSiiCTaskAbstract::M_ALLTASKOBJECT);
		
		return this->RunTask(MUSiiCTaskObject::M_THREAD_RUN_CONTINUOUS, m_tcp_status, this, NULL, NULL, NULL, M_ALLTASKOBJECT);
		
	}
//

	/// Close server socket
	int MUSiiCTCPServerSocketWin::CloseServer()
	{
		if(m_bDebug)
				MUSiiC_LOG(logINFO) << "MUSiiCTCPServerWin::Close Server:  ";
		m_bListeningThread = false;
		m_bNetworkThread   = false;
		m_bSendThread      = false;

		//Close network thread
		PostQueuedCompletionStatus(m_hCompletionPort, 0, NULL, NULL);
		if(m_bDebug)
				MUSiiC_LOG(logINFO) << "MUSiiCTCPServerWin::Try to finish the networking thread  ";
		/// Close Listen Socket
		this->CloseSocket(m_ListenSocket);
		if(m_bDebug)
				MUSiiC_LOG(logINFO) << "MUSiiCTCPServerWin::Try to finish the listening thread  ";
		/// Stop All task thread
		this->StopTask(M_ALLTASKOBJECT);
		/// Close Listening socket
		RemoveAllClientData();
		WSACleanup();
		return 0;
	}

	/// Get Num of connected-clients
	int MUSiiCTCPServerSocketWin::GetNumOfClients()
	{
		int sz(0);
		sz = m_listPerSocket->concurrent_size();
		return sz;
	}

	/// Check there are clients or not.
	bool MUSiiCTCPServerSocketWin::IsConnectedClients()
	{
		return GetNumOfClients()>0?true:false;
	}

	/////////////////////////////////////////////////////////////
	///Put igtl::MessageBase::Pointer to MUSiiCIODevice
	///          virtual function.
	int MUSiiCTCPServerSocketWin::PutIGTLMessage(igtl::MessageBase::Pointer msg)
	{
		return this->m_pInputNetworkBuffer->concurrent_push_back(msg);
	}

	/////////////////////////////////////////////////////////////
	///Try Put igtl::MessageBase::Pointer to MUSiiCIODevice
	///          virtual function.
	int MUSiiCTCPServerSocketWin::TryPutIGTLMessage(igtl::MessageBase::Pointer msg)
	{
		return 1;
	}

/////Protected::operations
	void MUSiiCTCPServerSocketWin::Initialize()
	{
		/// Initialize the object of MUSiiCTaskObject
		m_pListeningTask = igtl::MUSiiCTaskObject::New();
		/// Connect external task function to the task-object
		m_pListeningTask->AddExternalLocalTaskFunction(this, &MUSiiCTCPServerSocketWin::ListenTask, "Listening Task");
		/// Add the object to this class
		this->AddTaskObject(m_pListeningTask);

		/// Initialize the object of MUSiiCTaskObject
		m_pSendingTask = igtl::MUSiiCTaskObject::New();
		/// Connect external task function to the task-object
		m_pSendingTask->AddExternalLocalTaskFunction(this, &MUSiiCTCPServerSocketWin::SendTask, "Sening Task");
		/// Add the object to this class
		this->AddTaskObject(m_pSendingTask);


		/////////////////////////////////////////////////////
		//// Listening Task
		m_iListeningThreadIdx = 0;
		m_bListeningThread    = false;
	
		//// Network Task
		m_iNetworkThreadIdx   = 0;
		m_bNetworkThread      = false;
		
		/// Sending Task
		m_iSendThreadIdx      = 0;
		m_bSendThread         = false;

		m_pPerClientData      = NULL;

		m_pPerClientData      = NULL;

		m_ListenSocket        = 0;
		m_iRecvBytes          = 0;
		m_iFlag               = 0;

		m_listPerSocket = igtl::MUSiiCVector<LPPER_CLIENT_DATA>::New();
		m_listPerSocket->concurrent_clear();

		m_iServerSocket       = 0;
		m_buseSelfDataIF      = false;

		/// Initialize Critical Section
		m_pFastMutex = igtl::MutexLock::New();
		this->SetEnableDebug(true);

		/// Create Self-Data interface
		m_pInputNetworkBuffer = igtl::MUSiiCIGTLMsgVector::New();
		m_pInputNetworkBuffer->concurrent_clear();
		m_pOutputNetworkBuffer = igtl::MUSiiCIGTLMsgVector::New();
		m_pOutputNetworkBuffer->concurrent_clear();
		/// Connect 
		this->AddInputDataInterface(m_pInputNetworkBuffer);
		this->AddOutputDataInterface(m_pOutputNetworkBuffer);
	
	}


	//// Initialize WinSocket
	bool MUSiiCTCPServerSocketWin::InitSocket()
	{
		///Initialize WinSock
		if(WSAStartup(MAKEWORD(2,2), &m_WsaData) != 0)
		{
			MUSiiC_LOG(logERROR) << "MUSiiCTCPServerWin::WSAStartup Error";
			return false;
		}

		/// Create a Server Socket for listening a connection request from a client
		m_ListenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
		if(m_ListenSocket == INVALID_SOCKET)
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
			CloseSocket(m_ListenSocket);
			return false;
		}

		return true;
	}

	/// Close WinSock
	int MUSiiCTCPServerSocketWin::CloseSocket(SOCKET s)
	{	
		int r(0);
		/// Check Socket
		if(s != INVALID_SOCKET)
		{
			if(m_bDebug)
				MUSiiC_LOG(logINFO) << "MUSiiCTCPServerWin::Close Socket:  " << s;
			/// Close socket
			r = closesocket(s);
		}
		return r;
	}

	/// Add new Clients
	void MUSiiCTCPServerSocketWin::AddNewClients(LPPER_CLIENT_DATA client)
	{
		//EnterCriticalSection(&m_CS);
		m_pFastMutex->Lock();
		//m_listPerSocket.push_back(client);
		m_listPerSocket->concurrent_push_back(client);
		//LeaveCriticalSection(&m_CS);
		m_pFastMutex->Unlock();
	}

	/// Remove a disconnected socket
	void MUSiiCTCPServerSocketWin::RemoveClient(LPPER_CLIENT_DATA client)
	{
		m_pFastMutex->Lock();
		//m_listPerSocket.remove(client);
		m_listPerSocket->concurrent_remove(client);
		//MUSiiC_LOG(logINFO) << "RemoveClient :: The size of m_listPerSocket is " << m_listPerSocket->concurrent_size();
		
		CloseSocket(client->hClntSocket);
		delete client;
		client = NULL;
		m_pFastMutex->Unlock();
	}

	int MUSiiCTCPServerSocketWin::IOCP_Recv(LPPER_CLIENT_DATA client,  std::string description)
	{
		DWORD RecvDataSize = 0, iFlag = 0;
		int error = WSARecv(client->hClntSocket,
							&(client->wsaRecvBuf),
							1,
							&RecvDataSize,//&(PerIOData->RecvDataSize),
							&iFlag,
							&(client->overlapped),
							NULL);

		return ErrorHandling(error, client, description);
	}
	//// Receive IGTL_Header Message
	int MUSiiCTCPServerSocketWin::IOCP_Recv_IGTLHEADER(LPPER_CLIENT_DATA client, DWORD dwsize)
	{
		
		//Initialize IGTL MessageBase
		if(client->RxMode == M_IOCP_RX_INIT)
		{
			client->RxIGTLMsg           = igtl::MessageBase::New();
			client->RxIGTLMsg->InitPack();
			client->wsaRecvBuf.buf     = (char*)client->RxIGTLMsg->GetPackPointer();
			client->wsaRecvBuf.len     = client->RxIGTLMsg->GetPackSize();
			client->n_iExpectSumOfRecv = client->RxIGTLMsg->GetPackSize();
			client->n_iSumOfRecv       = 0;
			client->RxMode           = M_IOCP_Rx_IGTLHEADER;
			m_iFlag = 0;
			//receive IGTL_HEADER
			return IOCP_Recv(client, "M_IOCP_Rx_IGTLHEADER");
		}
		else
		{
			client->n_iSumOfRecv+=(int) dwsize;
			if(client->n_iSumOfRecv < client->n_iExpectSumOfRecv)
			{
				//receive more data
				client->wsaRecvBuf.buf = (char*)client->RxIGTLMsg->GetPackPointer()+client->n_iSumOfRecv;
				client->wsaRecvBuf.len = client->n_iExpectSumOfRecv - client->n_iSumOfRecv;
				//receive IGTL_HEADER
				return IOCP_Recv(client, "M_IOCP_Rx_IGTLHEADER");
			}
			else
			{
				// Receive IGTL Body
				// Change data type
				client->RxMode = M_IOCP_Rx_IGTLHEADERDONE;
				return IOCP_Recv_IGTLBODY(client, 0);
			}
		}
	}

	//// Receive IGTL_Body Message
	int MUSiiCTCPServerSocketWin::IOCP_Recv_IGTLBODY(LPPER_CLIENT_DATA client,DWORD dwsize)
	{
		if(client->RxMode == M_IOCP_Rx_IGTLHEADERDONE)
		{
			client->RxIGTLMsg->Unpack();
			client->RxIGTLMsg->AllocatePack();
			client->wsaRecvBuf.buf     = (char*)client->RxIGTLMsg->GetPackBodyPointer();
			client->wsaRecvBuf.len     = client->RxIGTLMsg->GetBodySizeToRead();
			client->n_iExpectSumOfRecv = client->RxIGTLMsg->GetBodySizeToRead();
			client->n_iSumOfRecv       = 0;
			client->RxMode             = M_IOCP_Rx_IGTLBODY;
			m_iFlag = 0;
			//receive IGTLBody
			return IOCP_Recv(client, "M_IOCP_Rx_IGTLBODY");
		}
		else
		{
			client->n_iSumOfRecv+=(int) dwsize;
			if(client->n_iSumOfRecv < client->n_iExpectSumOfRecv)
			{
				//receive more data
				client->wsaRecvBuf.buf = (char*)client->RxIGTLMsg->GetPackBodyPointer()+client->n_iSumOfRecv;
				client->wsaRecvBuf.len = client->n_iExpectSumOfRecv - client->n_iSumOfRecv;
				//receive IGTLBody
				return IOCP_Recv(client, "M_IOCP_Rx_IGTLBODY");
			}
			else
			{
				// Doing post processing
				// Change data type
				client->RxMode = M_IOCP_Rx_IGTLBODYDONE;
				return GetIGTLMessage(client);
			}
		}
	}

	

	/// Retrive IGTL Message from IOCP data buffer.
	int MUSiiCTCPServerSocketWin::GetIGTLMessage(LPPER_CLIENT_DATA client)
	{
		int c = client->RxIGTLMsg->Unpack(1);
		if(c & igtl::MessageHeader::UNPACK_BODY)
		{
			igtl::MessageBase::Pointer msg = client->RxIGTLMsg;

			igtl::ImageMessage::Pointer img = igtl::RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(msg);

			igtl::Matrix4x4 matrix;
			img->GetMatrix(matrix);
			igtl::PrintMatrix(matrix);
			std::cerr << std::endl;
			//std::cerr << "FPS is: " <<  m_Profile.GetFPS() << std::endl;
			
			
			if(m_bDebug)
				MUSiiC_LOG(logINFO) << "FPS is: " << m_Profile.GetFPS();
			
			/// TCP Post Processing
			//this->TCPServerPostProcessing(
		}

		client->RxMode = M_IOCP_RX_INIT;
		return IOCP_Recv_IGTLHEADER(client, 0);
	}

	int MUSiiCTCPServerSocketWin::IOCP_Send(LPPER_CLIENT_DATA client, std::string description )
	{
		DWORD SendDataSize = 0, iFlag = 0;	
		int error = WSASend(client->hClntSocket,
							&(client->wsaSendBuf),
							1,
							&SendDataSize,//&(PerIOData->RecvDataSize),
							iFlag,
							&(client->overlapped),
							NULL);

		return ErrorHandling(error, client, description, 1);
	}

	int MUSiiCTCPServerSocketWin::IOCP_SendIGTL(LPPER_CLIENT_DATA client, DWORD dwsize)
	{
		DWORD SendDataSize = 0, iFlag = 0;

		if(client->TXMode == M_IOCP_TX_INIT)
		{
			client->TxIGTLMsg->Pack();
			client->wsaSendBuf.buf = (char*)client->TxIGTLMsg->GetPackPointer();
			client->wsaSendBuf.len = client->TxIGTLMsg->GetPackSize();
			client->n_iExpectSumOfSent = client->TxIGTLMsg->GetPackSize();
			client->n_iSumOfSent = 0;
			client->TXMode = M_IOCP_Tx_IGTL;
			IOCP_Send(client, "M_IOCP_TX_INIT");
		}
		else
		{
			client->n_iSumOfSent+=(int) dwsize;
			if(client->n_iSumOfSent < client->n_iExpectSumOfSent)
			{
				//receive more data
				client->wsaSendBuf.buf = (char*)client->TxIGTLMsg->GetPackPointer()+client->n_iSumOfRecv;
				client->wsaSendBuf.len = client->n_iExpectSumOfSent - client->n_iSumOfSent;
				//receive IGTL_HEADER
				return IOCP_Send(client,"M_IOCP_Tx_IGTL");
			}
			else
			{
				// Change data type
				client->TXMode = M_IOCP_Tx_IGTLDONE;
			}
		}
	}

//	
//
//	////TODO::cannon 96
//	/// Client-Network Task function is implemented in this function.
	int MUSiiCTCPServerSocketWin::TaskFunction(int numOfRun, int taskInfo, void* ptr, void* data1, void* data2, void* data3)
	{
	
		LPPER_CLIENT_DATA client = NULL;
		//LPPER_IO_DATA pPerIOData = NULL;
		LPOVERLAPPED lpOv = NULL;
		DWORD dwTransfer;
		bool ret;

		while(m_bNetworkThread)
		{
			ret = GetQueuedCompletionStatus(m_hCompletionPort, &dwTransfer, 
											(LPDWORD)&client,
											&lpOv, INFINITE);
			
			/// check disconnection of client
			if(dwTransfer == 0)
			{
				if(client)
				{
					if(m_bDebug)
						MUSiiC_LOG(logINFO) << "Disconnected %s client:" << inet_ntoa(client->clntAddr.sin_addr);
					////Remove Client(LPPER_CLIENT_DATA pPerSocketData);
					RemoveClient(client);
				}
				continue;
			}

			
			if(m_pPerClientData->IO_MODE == M_IOCP_Rx)
			{
				switch (client->RxMode)
				{
					case M_IOCP_RX_INIT:
						IOCP_Recv_IGTLHEADER(client, 0);
						break;
					case M_IOCP_Rx_IGTLHEADER:
						IOCP_Recv_IGTLHEADER(client, dwTransfer);
						break;
					case M_IOCP_Rx_IGTLHEADERDONE:
						IOCP_Recv_IGTLBODY(client, 0);
						break;
					case M_IOCP_Rx_IGTLBODY:
						IOCP_Recv_IGTLBODY(client, dwTransfer);
						break;
					case M_IOCP_Rx_IGTLBODYDONE:
						GetIGTLMessage(client);
						break;
					default:
						break;
				}
			}
			else if(m_pPerClientData->IO_MODE == M_IOCP_Tx)
			{
				MUSiiC_LOG(logINFO) << "Data Tx";
				switch (client->TXMode)
				{
					case M_IOCP_TX_INIT:
						break;
					case M_IOCP_Tx_IGTL:
						IOCP_SendIGTL(client, dwTransfer);
						break;
					case M_IOCP_Tx_IGTLDONE:
						break;
					default:
						break;
				}
			}
		
			/*switch (client->RxMode)
			{
				case M_IOCP_RX_INIT:
					IOCP_Recv_IGTLHEADER(client, 0);
					break;
				case M_IOCP_Rx_IGTLHEADER:
					IOCP_Recv_IGTLHEADER(client, dwTransfer);
					break;
				case M_IOCP_Rx_IGTLHEADERDONE:
					IOCP_Recv_IGTLBODY(client, 0);
					break;
				case M_IOCP_Rx_IGTLBODY:
					IOCP_Recv_IGTLBODY(client, dwTransfer);
					break;
				case M_IOCP_Rx_IGTLBODYDONE:
					GetIGTLMessage(client);
					break;
				case M_IOCP_TX_INIT:
					break;
				case M_IOCP_Tx_IGTL:
					break;
				case M_IOCP_Tx_IGTLDONE:
					break;
				default:
					break;
			}*/
		}

		m_bNetworkThread = false;
		if(m_bDebug)
				MUSiiC_LOG(logINFO) << "Core:Networking Thread is Finished";
		return NULL;
	}

	////////////////////////////////////////////////////////////////////////////////
	/// Listening Task
	int MUSiiCTCPServerSocketWin::ListenTask(int numOfRun, int taskInfo, void* ptr, void* data1, void* data2, void* data3)
	{
		while(m_bListeningThread)
		{
			SOCKET hClientSock;
			SOCKADDR_IN ClientAddr;
			int addrLen = sizeof(ClientAddr);

			hClientSock = accept(m_ListenSocket, (PSOCKADDR)&ClientAddr, &addrLen);
			/// Notify new Client is connected
			/// Call a callback function or leave log message

			///////////////////////////////////////////
			//m_pPerClientData = (LPPER_CLIENT_DATA)malloc(sizeof(PER_CLIENT_DATA));
			m_pPerClientData = new PER_CLIENT_DATA;
			ZeroMemory(m_pPerClientData, sizeof(PER_CLIENT_DATA));
			/// Client Socket
			m_pPerClientData->hClntSocket = hClientSock;
			/// Copy client address
			memcpy(&(m_pPerClientData->clntAddr), &ClientAddr, addrLen);
			/// Add new client to the list of connected client
			AddNewClients(m_pPerClientData);
			/// Set new client to IOCP
			CreateIoCompletionPort((HANDLE)m_pPerClientData->hClntSocket, m_hCompletionPort, (DWORD)m_pPerClientData, 0); 
			/// TO DO ::Receive IGTL Header
			m_pPerClientData->RxMode = M_IOCP_RX_INIT;
			m_pPerClientData->TXMode = M_IOCP_Tx_IGTLDONE;
			m_pPerClientData->IO_MODE = M_IOCP_Rx;
			IOCP_Recv_IGTLHEADER(m_pPerClientData,0);

		}

		m_bListeningThread = false;
		if(m_bDebug)
				MUSiiC_LOG(logINFO) << "Listening Thread is Finished";
		return NULL;
	}

	///////////////////////////////////////////////////////////////////////////////////////
	//// Sending Task
	int MUSiiCTCPServerSocketWin::SendTask(int numOfRun, int taskInfo, void* ptr, void* data1, void* data2, void* data3)
	{
		while(m_bSendThread)
		{
			
			igtl::MessageBase::Pointer tempMsg;
			if(m_bDebug)
				MUSiiC_LOG(logINFO) << "Waiting Data";
			this->m_pVInputDATA_IF_Set->Concurrent_wait_get_pop_front_fromMUSiiCVectorSet(tempMsg);

			if(m_bDebug)
				MUSiiC_LOG(logINFO) << "Got Data";
			
			//EnterCriticalSection(&m_CS);
			m_pFastMutex->Lock();
			
			LPPER_CLIENT_DATA temp = NULL;
			
			
			int sz(m_listPerSocket->concurrent_size());
			//MUSiiC_LOG(logINFO) << "SendTask :: The size of m_listPerSocket is " << sz;
				
			for(int i=0; i<sz; i++)
			{
				m_listPerSocket->concurrent_try_get(temp, i);
				if(temp->TXMode == M_IOCP_Tx_IGTLDONE)
				{
					if(tempMsg.IsNotNull())
					{
						//if(i>2)
						{
							temp->TxIGTLMsg = tempMsg;
							temp->TXMode = M_IOCP_TX_INIT;
							temp->IO_MODE = M_IOCP_Tx;

							IOCP_SendIGTL(temp,0);
						}
					}
				}
			}
			
			//LeaveCriticalSection(&m_CS);
			m_pFastMutex->Unlock();
		}

		m_bSendThread = false;
		if(m_bDebug)
				MUSiiC_LOG(logINFO) << "Sending Thread is Finished";
		return NULL;
	}

	//// Post processing function for TCP/IP Communication 
	/// In General, 
	/// numOfRun : When using Data-Interface, this number indicate the index of new data in Data-Interface
	/// TaskInfo : The argument of this task
	/// ptr      : the pointer of caller class
	/// data1    : Data 
	/// data2    : the Time-stamp of the data
	/// data3    : the name of Data
	int MUSiiCTCPServerSocketWin::TCPServerPostProcessing(int numOfRun, int taskInfo, void* ptr, void* data1, void* data2, void* data3)
	{
		int r(0);
		if(m_bEnableExternalOutputCallbackFuntions)
		{
			r = CallExternalOutputCallbackFunctions(numOfRun, taskInfo, ptr, data1, data2, data3);
		}
		return r;
	}

	//Handling of an error from IOCP function
	int MUSiiCTCPServerSocketWin::ErrorHandling(int errorcode, LPPER_CLIENT_DATA client,std::string desp , int mode)
	{
		if(errorcode == 0)
		{
			if(m_bDebug)
			{
				if(mode == 0) MUSiiC_LOG(logINFO) << "1: Call WSARecv fucntion to receive "<< desp.c_str() << inet_ntoa(client->clntAddr.sin_addr);
				else MUSiiC_LOG(logINFO) << "1: Call WSASend fucntion to send " << desp.c_str() << inet_ntoa(client->clntAddr.sin_addr);
			}
		}
		else if(errorcode == SOCKET_ERROR && WSAGetLastError() == WSA_IO_PENDING)
		{
			if(m_bDebug)
			{
				if(mode == 0) MUSiiC_LOG(logINFO) << "2: Request WSARecv fucntion to receive   " << desp.c_str() << inet_ntoa(client->clntAddr.sin_addr);
				else MUSiiC_LOG(logINFO) << "2: Request WSASend fucntion to send  " << desp.c_str() << inet_ntoa(client->clntAddr.sin_addr);
			}
		}
		else
		{
			if(m_bDebug)
			{
				if(mode == 0) MUSiiC_LOG(logINFO) << "3: Failed to call WSARecv Function  " << desp.c_str()<< inet_ntoa(client->clntAddr.sin_addr);
				else MUSiiC_LOG(logINFO) << "3: Failed to call WSASend Function  " << desp.c_str()<< inet_ntoa(client->clntAddr.sin_addr);
			}
			
			RemoveClient(client);
		}

		return errorcode;
	}

	/////////////////////////////////////////////////////////////
	bool MUSiiCTCPServerSocketWin::RemoveAllClientData()
	{
		LPPER_CLIENT_DATA temp = NULL;
		/*while (!m_listPerSocket.empty())
		{
			temp = m_listPerSocket.front();
			RemoveClient(temp);
		}*/

		int sz(m_listPerSocket->concurrent_size());
		for(int i=0; i <sz ; i++)
		{
			m_listPerSocket->concurrent_try_get(temp, i);
			RemoveClient(temp);
		}

		return m_listPerSocket->concurrent_empty();
	}
}