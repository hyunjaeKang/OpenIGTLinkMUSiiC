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
		if(m_pFastMutex.IsNotNull())
			m_pFastMutex->Unlock();

		this->CloseServer();
	}

	/// Creater Server Socket
	int MUSiiCTCPServerSocketWin::CreateServer(int port)
	{
		m_iServerSocket   = port;
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
		m_tcp_status			= M_TCP_SERVER_CREATED;
		m_bNetworkThread		= true;
		m_bListeningThread		= true;
		m_bSendThread			= true;

		this->m_tcp_status		= M_TCP_SERVER_CREATED;
		

		m_pParentTCPIO->TCPPostProcessing(M_PRE_CONTROL_PRAR,M_TCP_SERVER_CREATED, this, NULL, &m_ServerAddr, NULL); 
		this->SetEnableThread(true, M_ALLTASKOBJECT);
		return this->RunTask(M_THREAD_RUN_CONTINUOUS, m_tcp_status, this, NULL, NULL, NULL, M_ALLTASKOBJECT);
		
	}
//

	/// Close server socket
	int MUSiiCTCPServerSocketWin::CloseServer()
	{
		if(m_bDebug)
				MUSiiC_LOG(logINFO) << "MUSiiCTCPServerWin::Close Server:  ";
		m_bListeningThread		= false;
		m_bNetworkThread		= false;
		m_bSendThread			= false;

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
		this->m_tcp_status		= M_TCP_SERVER_CLOSED;
		m_pParentTCPIO->TCPPostProcessing(M_PRE_CONTROL_PRAR,M_TCP_SERVER_CLOSED, this, NULL, &m_ServerAddr, NULL); 
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


	////////////////////////////////////////
	/// Get the list of Connected client list
	igtl::MUSiiCVector<LP_CLIENT_DATA>::Pointer MUSiiCTCPServerSocketWin::GetConnectedClientList()
	{
		return m_listPerSocket;
	}


/////Protected::operations
	void MUSiiCTCPServerSocketWin::Initialize()
	{
		
		this->m_tcp_status		= M_TCP_DISCONNECTED;
		/// Initialize the object of MUSiiCTaskObject
		m_pListeningTask		= igtl::MUSiiCTaskObject::New();
		/// Connect external task function to the task-object
		m_pListeningTask->AddExternalLocalTaskFunction(this, &MUSiiCTCPServerSocketWin::ListenTask, "Listening Task");
		/// Add the object to this class
		this->AddTaskObject(m_pListeningTask);

		/// Initialize the object of MUSiiCTaskObject
		m_pSendingTask		= igtl::MUSiiCTaskObject::New();
		/// Connect external task function to the task-object
		m_pSendingTask->AddExternalLocalTaskFunction(this, &MUSiiCTCPServerSocketWin::SendTask, "Sending Task");
		/// Add the object to this class
		this->AddTaskObject(m_pSendingTask);


		/////////////////////////////////////////////////////
		//// Listening Task
		m_iListeningThreadIdx		= 0;
		m_bListeningThread			= false;
	
		//// Network Task
		m_iNetworkThreadIdx			= 0;
		m_bNetworkThread			= false;
		
		/// Sending Task
		m_iSendThreadIdx			= 0;
		m_bSendThread				= false;

		m_pPerClientData			= NULL;

		m_pPerClientData			= NULL;

		m_ListenSocket				= 0;
		m_iRecvBytes				= 0;
		m_iFlag						= 0;

		///
		m_listPerSocket = igtl::MUSiiCVector<LP_CLIENT_DATA>::New();
		m_listPerSocket->concurrent_clear();

		m_iServerSocket			= 0;
		m_buseSelfDataIF			= false;

		m_bInitWinSock            = false;

		/// Initialize Critical Section
		m_pFastMutex = igtl::MutexLock::New();
		//this->SetEnableDebug(true);

		///Initialize WinSock
		if(WSAStartup(MAKEWORD(2,2), &m_WsaData) != 0)
		{
			MUSiiC_LOG(logERROR) << "MUSiiCTCPServerWin::WSAStartup Error";
			m_bInitWinSock = false;
		}
		else
			m_bInitWinSock = true;
	}


	//// Initialize WinSocket /// cannon96 :: Done 
	bool MUSiiCTCPServerSocketWin::InitSocket()
	{
		///Recheck WinSock
		if(!m_bInitWinSock)
		{
			if(WSAStartup(MAKEWORD(2,2), &m_WsaData) != 0)
			{
				MUSiiC_LOG(logERROR) << "MUSiiCTCPServerWin::WSAStartup Error";
				return false;
			}
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
	void MUSiiCTCPServerSocketWin::AddNewClients(LP_CLIENT_DATA client)
	{
		//EnterCriticalSection(&m_CS);
		m_pFastMutex->Lock();
		//m_listPerSocket.push_back(client);
		m_listPerSocket->concurrent_push_back(client);
		//LeaveCriticalSection(&m_CS);
		m_pFastMutex->Unlock();
	}

	/// Remove a disconnected socket
	void MUSiiCTCPServerSocketWin::RemoveClient(LP_CLIENT_DATA client)
	{
		m_pFastMutex->Lock();
		m_listPerSocket->concurrent_remove(client);
		if(client->hClntSocket > 0 && client->hClntSocket < 4000000)
		{
			CloseSocket(client->hClntSocket);
			delete client;
			client = NULL;
		}
		m_pFastMutex->Unlock();
	}

	/// Recv IGTL Message
	int MUSiiCTCPServerSocketWin::IOCP_Recv_IGTLMsg(LP_CLIENT_DATA client)
	{
		if(client != NULL)
		{
			///Create Data IO object for the connected client.
			LP_IO_DATA pPerIOData = new IO_DATA;
			ZeroMemory(pPerIOData, sizeof(IO_DATA));
			//pPerIOData->IGTLMsg = igtl::MessageBase::New();
			pPerIOData->IO_MODE = M_IOCP_Rx;
			pPerIOData->RxMode = M_IOCP_RX_INIT;

			//return IOCP_Recv_IGTLHEADER(m_pPerClientData,pPerIOData,0); //cannon96
			return IOCP_Recv_IGTLHEADER(client,pPerIOData,0);
		}
		else
			return 0;

	}

	/// Receive Function using IOCP
	int MUSiiCTCPServerSocketWin::IOCP_Recv(LP_CLIENT_DATA client, LP_IO_DATA IOdata, std::string description)
	{
		DWORD RecvDataSize = 0, iFlag = 0;
		int error = WSARecv(client->hClntSocket,
							&(IOdata->wsaBuf),
							1,
							&RecvDataSize,//&(PerIOData->RecvDataSize),
							&iFlag,
							&(IOdata->Overlapped),
							NULL);

		return ErrorHandling(error, client, description);
	}
	//// Receive IGTL_Header Message
	int MUSiiCTCPServerSocketWin::IOCP_Recv_IGTLHEADER(LP_CLIENT_DATA client, LP_IO_DATA IOdata, DWORD dwsize)
	{
		
		//Initialize IGTL MessageBase
		if(IOdata->RxMode == M_IOCP_RX_INIT)
		{
			IOdata->headerMsg         = igtl::MessageHeader::New();
			IOdata->headerMsg->InitPack();
			IOdata->wsaBuf.buf			= (char*)IOdata->headerMsg->GetPackPointer();
			IOdata->wsaBuf.len			= IOdata->headerMsg->GetPackSize();
			IOdata->n_iExpectSum		= IOdata->headerMsg->GetPackSize();
			IOdata->n_iSum				= 0;
			IOdata->RxMode				= M_C_IOCP_Rx_IGTLHEADER;
			m_iFlag = 0;
			//receive IGTL_HEADER
			return IOCP_Recv(client, IOdata, "M_IOCP_Rx_IGTLHEADER");
		}
		else
		{
			IOdata->n_iSum+=(int) dwsize;
			if(IOdata->n_iSum < IOdata->n_iExpectSum)
			{
				//receive more data
				IOdata->wsaBuf.buf = (char*)IOdata->headerMsg->GetPackPointer()+IOdata->n_iSum;
				IOdata->wsaBuf.len = IOdata->n_iExpectSum - IOdata->n_iSum;
				//receive IGTL_HEADER
				return IOCP_Recv(client, IOdata, "M_IOCP_Rx_IGTLHEADER");
			}
			else
			{
				// Receive IGTL Body
				// Change data type
				IOdata->RxMode = M_IOCP_Rx_IGTLHEADERDONE;
				return IOCP_Recv_IGTLBODY(client, IOdata, 0);
			}
		}
	}

	//// Receive IGTL_Body Message
	int MUSiiCTCPServerSocketWin::IOCP_Recv_IGTLBODY(LP_CLIENT_DATA client,LP_IO_DATA IOdata, DWORD dwsize)
	{
		if(IOdata->RxMode == M_IOCP_Rx_IGTLHEADERDONE)
		{
			IOdata->headerMsg->Unpack();
			////////////////////////////////////
			IOdata->IGTLMsg = igtl::MessageBase::New();
			IOdata->IGTLMsg->SetMessageHeader(IOdata->headerMsg);
			//////////////////////////////////////
			IOdata->IGTLMsg->AllocatePack();
			IOdata->wsaBuf.buf     = (char*)IOdata->IGTLMsg->GetPackBodyPointer();
			IOdata->wsaBuf.len     = IOdata->IGTLMsg->GetBodySizeToRead();
			IOdata->n_iExpectSum   = IOdata->IGTLMsg->GetBodySizeToRead();
			IOdata->n_iSum         = 0;
			IOdata->RxMode         = M_IOCP_Rx_IGTLBODY;
			m_iFlag = 0;
			//receive IGTLBody
			return IOCP_Recv(client, IOdata,"M_IOCP_Rx_IGTLBODY");
		}
		else
		{
			IOdata->n_iSum +=(int) dwsize;
			if(IOdata->n_iSum < IOdata->n_iExpectSum)
			{
				//receive more data
				IOdata->wsaBuf.buf = (char*)IOdata->IGTLMsg->GetPackBodyPointer()+IOdata->n_iSum;
				IOdata->wsaBuf.len = IOdata->n_iExpectSum - IOdata->n_iSum;
				//receive IGTLBody
				return IOCP_Recv(client, IOdata,"M_IOCP_Rx_IGTLBODY");
			}
			else
			{
				// Doing post processing
				// Change data type
				IOdata->RxMode = M_IOCP_Rx_IGTLBODYDONE;
				return GetIGTLMessage(client,IOdata);
			}
		}
	}

	

	/// Retrive IGTL Message from IOCP data buffer.
	int MUSiiCTCPServerSocketWin::GetIGTLMessage(LP_CLIENT_DATA client,LP_IO_DATA IOdata)
	{
		if(IOdata != NULL)
		{
			 igtl::MessageBase::Pointer msg = RetriveMessageBase(IOdata->headerMsg, IOdata->IGTLMsg);

			 bool bIsString = IsStringMessage(msg);
			//if (strcmp(msg->GetDeviceType(), "STRING") == 0)
			if(bIsString)
			 {	
				 igtl::StringMessage::Pointer str = RetrieveMessage<igtl::StringMessage::Pointer, igtl::StringMessage>(msg);

				 if (strcmp(str->GetDeviceName(), M_IO_FILTER) == 0)
				 {
					 client->IOFilter->SetMUSiiCIOFilter(str->GetString(), true);
				 }
				 else if(strcmp(str->GetDeviceName(), M_CONTROL_PAR) == 0)
				 {
					 this->IOCP_Send_IGTLMsg_Exclude(client, msg);
				 }
			 }

			//// To Do:: Set MUSiiCFileIO Filter of Client structure using StringMessage:: KHJ
			if(m_pParentTCPIO->CheckMessageBasPreOutputMUSiiCIOFilter(msg).IsNotNull() || bIsString)
			{
				/// TCP Post Processing
				//// Post processing function for TCP/IP Communication 
				/// In General, 
				/// numOfRun : When using Data-Interface, this number indicate the index of new data in Data-Interface
				/// TaskInfo : TCP status
				/// ptr      : the pointer of caller class
				/// data1    : Data 
				/// data2    : the address of server socket
				/// data3    : the address of client socket
			
				m_pParentTCPIO->TCPPostProcessing(M_PRE_CONTROL_PRAR_DATA, M_TCP_DATA_RECEIVED, this, msg, &m_ServerAddr, &(client->clntAddr));
			}
		}		
		delete IOdata;

		return IOCP_Recv_IGTLMsg(client);
	}


	/// Send IGTL Message
	int MUSiiCTCPServerSocketWin::IOCP_Send_IGTLMsg(LP_CLIENT_DATA client,igtl::MessageBase::Pointer msg)
	{
		if(client != NULL && msg.IsNotNull() && client->TXMode == M_IOCP_Tx_IGTLDONE )
		{
			//if(client->IOFilter->CheckMessageBase(msg,m_bPostOutputCheckDeviceType).IsNotNull())
			//if(this->CheckMessageBasPostOutputeMUSiiCIOFilter(msg).IsNotNull())
			{
				LP_IO_DATA pPerIOData = new IO_DATA;
				ZeroMemory(pPerIOData, sizeof(IO_DATA));
				pPerIOData->IO_MODE = M_IOCP_Tx;
				pPerIOData->TXMode = M_IOCP_TX_INIT;
				pPerIOData->IGTLMsg = msg;
				return IOCP_SendIGTL(client,pPerIOData,0);
			}
			/*else
			{
				if(this->m_bDebug)
					MUSiiC_LOG(logINFO) << "Given Message is filtered by MUSiiCIOFilter";
				return 0;
			}*/
		}
		else
		{
			if(client == NULL)
				MUSiiC_LOG(logERROR) << "Client is NULL";
			else if( client->TXMode != M_C_IOCP_Tx_IGTLDONE)
				if(m_bDebug)
					MUSiiC_LOG(logINFO) << "Client socket is sending another data!";
			else if(msg.IsNull())
				if(m_bDebug)
					MUSiiC_LOG(logINFO) << "**Temp Message of IGTL is NULL Message";
			return 0;
		}
	}


	/// Send IGTL Message to All connected clients excluding pre-defined client
	/// If the return value is -1, this means that there is no pre-defined client in the list
	int MUSiiCTCPServerSocketWin::IOCP_Send_IGTLMsg_Exclude(LP_CLIENT_DATA client,igtl::MessageBase::Pointer msg)
	{
		//EnterCriticalSection(&m_CS);
		m_pFastMutex->Lock();
			
		LP_CLIENT_DATA temp = NULL;
		int sz(m_listPerSocket->concurrent_size());
		int r(0);
				
		for(int i=0; i<sz; i++)
		{
			//// To Do:: Apply MUSiiCFileIO Filter :: KHJ
			m_listPerSocket->concurrent_try_get(temp, i);
			if(temp != client)
			{
				IOCP_Send_IGTLMsg(temp, msg);
				r++;
			}
		}
			
		//LeaveCriticalSection(&m_CS);
		m_pFastMutex->Unlock();
		return (r == sz)? -1 : r;
	}


	/// Send IGTL Message to All connected
	int MUSiiCTCPServerSocketWin::IOCP_Send_IGTLMsg_ALLClients(igtl::MessageBase::Pointer msg)
	{
		//EnterCriticalSection(&m_CS);
		m_pFastMutex->Lock();
			
		LP_CLIENT_DATA temp = NULL;
		int sz(m_listPerSocket->concurrent_size());
		int r(0);
				
		for(int i=0; i<sz; i++)
		{
			//// To Do:: Apply MUSiiCFileIO Filter :: KHJ
			m_listPerSocket->concurrent_try_get(temp, i);
			IOCP_Send_IGTLMsg(temp, msg);
		}
			
		//LeaveCriticalSection(&m_CS);
		m_pFastMutex->Unlock();
		return r;
	}

	/// Sending function using IOCP
	int MUSiiCTCPServerSocketWin::IOCP_Send(LP_CLIENT_DATA client, LP_IO_DATA IOdata, std::string description )
	{
		DWORD SendDataSize = 0, iFlag = 0;	
		int error = WSASend(client->hClntSocket,
							&(IOdata->wsaBuf),
							1,
							&SendDataSize,//&(PerIOData->RecvDataSize),
							iFlag,
							&(IOdata->Overlapped),
							NULL);
		
		return ErrorHandling(error, client, description, 1);
	}

	/// Sending OpenIGTL Message
	int MUSiiCTCPServerSocketWin::IOCP_SendIGTL(LP_CLIENT_DATA client, LP_IO_DATA IOdata, DWORD dwsize)
	{

		if(IOdata->TXMode == M_IOCP_TX_INIT)
		{
			IOdata->IGTLMsg->Pack();
			IOdata->wsaBuf.buf = (char*)IOdata->IGTLMsg->GetPackPointer();
			IOdata->wsaBuf.len = IOdata->IGTLMsg->GetPackSize();
			IOdata->n_iExpectSum = IOdata->IGTLMsg->GetPackSize();
			IOdata->n_iSum = 0;
			IOdata->TXMode = M_IOCP_Tx_IGTL;
			m_pFastMutex->Lock();
			client->TXMode = M_IOCP_Tx_IGTL;
			m_pFastMutex->Unlock();
			IOCP_Send(client, IOdata, "M_IOCP_TX_INIT");
		}
		else
		{
			IOdata->n_iSum +=(int) dwsize;
			if(IOdata->n_iSum < IOdata->n_iExpectSum)
			{
				//receive more data
				IOdata->wsaBuf.buf = (char*)IOdata->IGTLMsg->GetPackPointer()+IOdata->n_iSum;
				IOdata->wsaBuf.len = IOdata->n_iExpectSum - IOdata->n_iSum;
				//receive IGTL_HEADER
				return IOCP_Send(client,IOdata,"M_IOCP_Tx_IGTL");
			}
			else
			{
				// Change data type
				IOdata->TXMode = M_IOCP_Tx_IGTLDONE;
				IOCP_SendIGTLDone(client, IOdata);
			}
		}

		return 0;
	}

	/// Sent out IGTL Message
	int MUSiiCTCPServerSocketWin::IOCP_SendIGTLDone(LP_CLIENT_DATA client, LP_IO_DATA IOdata)
	{
		if(!IOdata)
		{
			if(m_bDebug)
				MUSiiC_LOG(logINFO) << "pPerIOData is NULL";
			return 0;
		}
		if(m_bDebug)
			MUSiiC_LOG(logINFO) << "IOCP_SendIGTLDone:: try to delete data";
		IOdata->TXMode = M_IOCP_Tx_IGTLDONE;
		delete IOdata;

		m_pFastMutex->Lock();
		client->TXMode = M_IOCP_Tx_IGTLDONE;
		m_pFastMutex->Unlock();
		
		if(m_bDebug)
			MUSiiC_LOG(logINFO) << "IOCP_SendIGTLDone:: Did";
		
		/// Notify TCP status
		m_pParentTCPIO->TCPPostProcessing(M_PRE_CONTROL_PRAR,M_TCP_DATA_SENT, this, NULL, &m_ServerAddr, &(client->clntAddr)); 

		return 1;
	}

//	
//
//	////TODO::cannon 96
//	/// Client-Network Task function is implemented in this function.
	int MUSiiCTCPServerSocketWin::TaskFunction(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
	{
	
		LP_CLIENT_DATA client = NULL;
		LP_IO_DATA pPerIOData = NULL;
		//LPOVERLAPPED lpOv = NULL;
		DWORD dwTransfer;
		BOOL ret;

		while(m_bNetworkThread)
		{
			
			
#if defined _M_IX86
			ret = GetQueuedCompletionStatus(m_hCompletionPort, &dwTransfer,
				(LPDWORD)&client,//(PULONG_PTR)&client,//(LPDWORD)&client, //64bit
				(LPOVERLAPPED*)&pPerIOData, INFINITE);
#elif defined _M_X64
			ret = GetQueuedCompletionStatus(m_hCompletionPort, &dwTransfer,
				(PULONG_PTR)&client,//(LPDWORD)&client, //64bit
				(LPOVERLAPPED*)&pPerIOData, INFINITE);
#endif
			
			/// check disconnection of client
			if(dwTransfer == 0)
			{
				if(client)
				{
					if(m_bDebug)
						MUSiiC_LOG(logINFO) << "Disconnected %s client:" << inet_ntoa(client->clntAddr.sin_addr);
					
					m_pParentTCPIO->TCPPostProcessing(M_PRE_CONTROL_PRAR,M_TCP_CLIENT_DISCONNECTED, this, NULL, &m_ServerAddr, &(client->clntAddr)); 
					RemoveClient(client);					
				}
				continue;
			}
			if(!pPerIOData)
			{
				MUSiiC_LOG(logINFO) << "pPerIOData is NULL";// << inet_ntoa(client->clntAddr.sin_addr);
				continue;
			}
			
			if(pPerIOData->IO_MODE == M_IOCP_Rx)
			{
				switch (pPerIOData->RxMode)
				{
					case M_IOCP_RX_INIT:
						IOCP_Recv_IGTLHEADER(client, pPerIOData,0);
						break;
					case M_IOCP_Rx_IGTLHEADER:
						IOCP_Recv_IGTLHEADER(client, pPerIOData, dwTransfer);
						break;
					case M_IOCP_Rx_IGTLHEADERDONE:
						IOCP_Recv_IGTLBODY(client, pPerIOData, 0);
						break;
					case M_IOCP_Rx_IGTLBODY:
						IOCP_Recv_IGTLBODY(client, pPerIOData, dwTransfer);
						break;
					case M_IOCP_Rx_IGTLBODYDONE:
						GetIGTLMessage(client,pPerIOData);
						break;
					default:
						break;
				}
			}
			else if(pPerIOData->IO_MODE == M_IOCP_Tx)
			{
				if(m_bDebug)
					MUSiiC_LOG(logINFO) << "Data Tx";
				switch (pPerIOData->TXMode)
				{
					case M_IOCP_TX_INIT:
						break;
					case M_IOCP_Tx_IGTL:
						IOCP_SendIGTL(client, pPerIOData, dwTransfer);
						break;
					case M_IOCP_Tx_IGTLDONE:
						break;
					default:
						break;
				}
			}
		
		}

		m_bNetworkThread = false;

		if(m_bDebug)
				MUSiiC_LOG(logINFO) << "Core:Networking Thread is Finished";
		return NULL;
	}

	////////////////////////////////////////////////////////////////////////////////
	/// Listening Task
	int MUSiiCTCPServerSocketWin::ListenTask(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
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
			m_pPerClientData = (LP_CLIENT_DATA)malloc(sizeof(CLIENT_DATA));
			//m_pPerClientData = new PER_CLIENT_DATA;
			ZeroMemory(m_pPerClientData, sizeof(CLIENT_DATA));
			/// Client Socket
			m_pPerClientData->hClntSocket = hClientSock;
			/// Copy client address
			memcpy(&(m_pPerClientData->clntAddr), &ClientAddr, addrLen);
			m_pPerClientData->bReconnect = false;
			m_pPerClientData->bReference = false;

			//// Initialize the MUSiiC IO Filter of client
			igtl::MUSiiCIOFilter::Pointer iofilter = igtl::MUSiiCIOFilter::New();
			m_pPerClientData->IOFilter = iofilter;
			m_pPerClientData->IOFilter->ResetMUSiiCIOFilter();

			
			/// Set new client to IOCP
			CreateIoCompletionPort((HANDLE)m_pPerClientData->hClntSocket, m_hCompletionPort, (DWORD)m_pPerClientData, 0); 

		
			m_pFastMutex->Lock();
			m_pPerClientData->TXMode = M_IOCP_Tx_IGTLDONE;
			m_pFastMutex->Unlock();

			///////////////////////////////////////////

			/// Add new client to the list of connected client
			AddNewClients(m_pPerClientData);

			/// Receive IGTL Message
			IOCP_Recv_IGTLMsg(m_pPerClientData);
			
			/// Notify TCP status
			m_pParentTCPIO->TCPPostProcessing(M_PRE_CONTROL_PRAR,M_TCP_CLIENT_CONNECTED, this, NULL, &m_ServerAddr, &(m_pPerClientData->clntAddr)); 
		}

		m_bListeningThread = false;
		if(m_bDebug)
				MUSiiC_LOG(logINFO) << "Listening Thread is Finished";
		return NULL;
	}

	///////////////////////////////////////////////////////////////////////////////////////
	//// Sending Task
	int MUSiiCTCPServerSocketWin::SendTask(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
	{
		while(m_bSendThread)
		{
			
			igtl::MessageBase::Pointer tempMsg;//= igtl::MessageBase::New();
			if(m_bDebug)
				MUSiiC_LOG(logINFO) << "Waiting Data";
			this->m_pVPreInputDATA_IF_Set->Concurrent_wait_get_pop_front_fromMUSiiCVectorSet(tempMsg);

			if(m_bDebug)
				MUSiiC_LOG(logINFO) << "Got Data";
			if(this->IsConnectedClients())
			{
				bool bIsString = IsStringMessage(tempMsg);
				/// Send the given data to all connected clients
				if(m_pParentTCPIO->CheckMessageBasePreInputMUSiiCIOFilter(tempMsg).IsNotNull() || bIsString)
					IOCP_Send_IGTLMsg_ALLClients(tempMsg);
			}
		}

		m_bSendThread = false;
		if(m_bDebug)
				MUSiiC_LOG(logINFO) << "Sending Thread is Finished";
		return NULL;
	}

	
	/// To Do :: cannon96 
	/// Delete this function
	//// Post processing function for TCP/IP Communication 
	/// In General, 
	/// numOfRun : When using Data-Interface, this number indicate the index of new data in Data-Interface
	/// TaskInfo : The argument of this task
	/// ptr      : the pointer of caller class
	/// data1    : Data 
	/// data2    : the Time-stamp of the data
	/// data3    : the name of Data
	int MUSiiCTCPServerSocketWin::TCPServerPostProcessing(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
	{
		int r(0);
		if(m_bEnableExternalOutputCallbackFuntions)
		{
			r = CallExternalOutputCallbackFunctions(numOfRun, taskInfo, ptr, data1, data2, data3);
		}
		return r;
	}

	//Handling of an error from IOCP function
	int MUSiiCTCPServerSocketWin::ErrorHandling(int errorcode, LP_CLIENT_DATA client,std::string desp , int mode)
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
		LP_CLIENT_DATA temp = NULL;
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