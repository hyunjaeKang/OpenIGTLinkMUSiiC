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

#include "MUSiiCTCPClientSocketWin.h"
#include "MUSiiCIGTLUtil.h"

namespace igtl
{
	/// Constructor
	MUSiiCTCPClientSocketWin::MUSiiCTCPClientSocketWin()
	{
		m_pNameOfClass="MUSiiCTCPClientSocketWin";
		Initialize();
	}

	/// Deconstructor
	MUSiiCTCPClientSocketWin::~MUSiiCTCPClientSocketWin()
	{
		if(m_pFastMutex.IsNotNull())
			m_pFastMutex->Unlock();

		if(m_bClientThreadsRun)
			this->CloseAllClients();		
	}

	///// Connect to Server(Host) with hostname(host-ip-address) and port
	int MUSiiCTCPClientSocketWin::ConnectToHost(const char* hostname, int port, std::string filter, bool sync, bool reference, bool reconnect)
	{
		int r(-1);
		/// Start network threads for client service.
		if(!m_bClientThreadsRun)
		{
			r = this->StartNetworkThreads();

			// check the network threads
			if(r< 0)
			{
				if(m_bDebug)
					MUSiiC_LOG(logINFO)<<"Clients Network threads cannot not created";

				return -1;
			}
		}

		/// Create new client structure
		LP_CLIENT_DATA client				= CreaterClientSocket();

		if(client)
		{
			struct hostent* hp;
			hp = gethostbyname(hostname);
			if (!hp)
			{
				unsigned long addr = inet_addr(hostname);
				hp = gethostbyaddr((char *)&addr, sizeof(addr), AF_INET);
			}
 
			if (!hp)
			{
				return -1;
			}
				
			/// Set Server Address and port
			client->slntAddr.sin_family			= AF_INET;
			//client->slntAddr.sin_addr.s_addr	= inet_addr(hostname);
			memcpy(&client->slntAddr.sin_addr, hp->h_addr, hp->h_length);
			client->slntAddr.sin_port			= htons(port);
			client->TCP_STATUS					= M_TCP_CLIENT_CONNECTING;
			client->bReconnect					= reconnect;
			client->bReference					= reference;
			client->bSync						= sync;
			/////////////////////////////////////////////////////////////
			// Setting MUSiiCIOFilter

			igtl::MUSiiCIOFilter::Pointer iofilter = igtl::MUSiiCIOFilter::New();
			client->IOFilter = iofilter;
			client->IOFilter->ResetMUSiiCIOFilter();

			/// Setting MUSiiCIOFilter
			if(filter.compare("") != 0)
			{
				client->IOFilter->SetMUSiiCIOFilter(filter);
				this->SetPostInputMUSiiCIOFilterData(filter, true);
				this->SetPostOutputMUSiiCIOFilterData(filter, true);
			}
			///////////////////////////////////////////////////////////////

			/// try to connect. Pass the object of client to Connect_Task
			return m_listClientSocketConnect->concurrent_push_back(client);
		}
		else
			return -1;
	}

	/// Try to reconnect to Server(Host)
	/// To Do :: cannon96
	int MUSiiCTCPClientSocketWin::ReConnectToHost()
	{
		return 0;
	}
	
	/// Close client socket
	void MUSiiCTCPClientSocketWin::CloseClientSocket(LP_CLIENT_DATA pClient)
	{
		if(pClient == NULL)
			pClient = m_pLastConnectedClient;

		if(pClient != NULL)
		{
			if(m_bDebug)
				MUSiiC_LOG(logINFO) << "The Client is will be closed";
				
			this->RemoveClient(pClient);	
		}
		else
			MUSiiC_LOG(logERROR)<<"The pointer of Client is NULL";
				
	}
	

///////////////////////////////////////////////////////////////////////////////
	void MUSiiCTCPClientSocketWin::Initialize()
	{
		this->m_tcp_status			= M_TCP_DISCONNECTED;

		
		/// Initialize the object of MUSiiCTaskObject
		m_pConnectTask			= igtl::MUSiiCTaskObject::New();
		/// Connect external task function to the task-object
		m_pConnectTask->AddExternalLocalTaskFunction(this, &MUSiiCTCPClientSocketWin::ConnectTask, "Listening Task");
		/// Add the object to this class
		this->AddTaskObject(m_pConnectTask);

		/// Initialize the object of MUSiiCTaskObject
		m_pSendingTask			= igtl::MUSiiCTaskObject::New();
		/// Connect external task function to the task-object
		m_pSendingTask->AddExternalLocalTaskFunction(this, &MUSiiCTCPClientSocketWin::SendTask, "Sening Task");
		/// Add the object to this class
		this->AddTaskObject(m_pSendingTask);
		
		///
		m_listClientSocket			= igtl::MUSiiCVector<LP_CLIENT_DATA>::New();
		m_listClientSocket->concurrent_clear();

		m_listClientSocketConnect	= igtl::MUSiiCVector<LP_CLIENT_DATA>::New();
		m_listClientSocketConnect->concurrent_clear();

		m_iConnectThreadIdx			= 0;
		m_bConnectThread			= false;
		m_iNetworkThreadIdx			= 0;
		m_bNetworkThread			= false;
		m_iSendThreadIdx			= 0;
		m_bSendThread				= false;

		/// Initialize Critical Section
		m_pFastMutex				= igtl::MutexLock::New();
		
		m_bInitSocket				= false;
		InitSocket();

		m_bClientThreadsRun			= false;

		m_pLastConnectedClient      = NULL;
		
	}

	bool MUSiiCTCPClientSocketWin::InitSocket()
	{
		if(WSAStartup(MAKEWORD(2,2), &m_WsaData) != 0)
		{
			MUSiiC_LOG(logERROR) << "MUSiiCTCPServerWin::WSAStartup Error";
			return false;
		}

		/// Create Completion Port
		m_hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
		if(m_hCompletionPort == NULL)
		{
			MUSiiC_LOG(logERROR) << "MUSiiCTCPServerWin::CreateIoCompletionPort Error";
			return false;
		}

		m_bInitSocket = true;

		return m_bInitSocket;
	}
	
	///Create Client Socket
	LP_CLIENT_DATA MUSiiCTCPClientSocketWin::CreaterClientSocket()
	{
		if(!m_bInitSocket)
		{
			if(m_bDebug)
				MUSiiC_LOG(logINFO) << "Re-Initializing WinSock";
			InitSocket();
		}

		/// Create client socket
		SOCKET clientsocket;
		/// Create a Server Socket for listening a connection request from a client
		clientsocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
		if(clientsocket == INVALID_SOCKET)
		{
			MUSiiC_LOG(logERROR) << "MUSiiCTCPServerWin::WSASocket Error (Server Socket)";
			return false;
		}

		/// Create a pointer of client
		m_pClient = new CLIENT_DATA;
		/// Initialize client
		ZeroMemory(m_pClient, sizeof(CLIENT_DATA));
		/// Client Socket
		m_pClient->hClntSocket = clientsocket;
		/// Set new client to IOCP :: Check point (KHJ)
		//CreateIoCompletionPort((HANDLE)m_pClient->hClntSocket, m_hCompletionPort, (DWORD)m_pClient, 0);
		m_pClient->TCP_STATUS = M_TCP_DISCONNECTED;
		//return the pointer of new client structure
		return 	m_pClient;
	}

	/// Close WinSock
	int MUSiiCTCPClientSocketWin::CloseSocket(SOCKET s)
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
	void MUSiiCTCPClientSocketWin::AddNewClients(LP_CLIENT_DATA client)
	{
		//EnterCriticalSection(&m_CS);
		m_pFastMutex->Lock();
		//m_listPerSocket.push_back(client);
		m_listClientSocket->concurrent_push_back(client);
		//LeaveCriticalSection(&m_CS);
		m_pFastMutex->Unlock();
	}

	/// Remove a disconnected socket
	void MUSiiCTCPClientSocketWin::RemoveClient(LP_CLIENT_DATA client)
	{
		m_pFastMutex->Lock();
		m_listClientSocket->concurrent_remove(client);
		if(client->hClntSocket > 0 && client->hClntSocket < 4000000)
		{
			CloseSocket(client->hClntSocket);
			delete client;
			client = NULL;
		}
		m_pFastMutex->Unlock();
	}

	/// Receive IGTL Message
	int MUSiiCTCPClientSocketWin::IOCP_Recv_IGTLMsg(LP_CLIENT_DATA client)
	{
		if(client != NULL)
		{
			///Create Data IO object for the connected client.
			IO_DATA* pPerIOData = new IO_DATA;
			ZeroMemory(pPerIOData, sizeof(IO_DATA));
			//pPerIOData->IGTLMsg = igtl::MessageBase::New();
			pPerIOData->IO_MODE = M_C_IOCP_Rx;
			pPerIOData->RxMode = M_C_IOCP_RX_INIT;

			return IOCP_Recv_IGTLHEADER(client,pPerIOData,0);
		}
		else
			return 0;
	}

	/// Receive Function using IOCP
	int MUSiiCTCPClientSocketWin::IOCP_Recv(LP_CLIENT_DATA client, LP_IO_DATA IOdata, std::string description)
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
	int MUSiiCTCPClientSocketWin::IOCP_Recv_IGTLHEADER(LP_CLIENT_DATA client, LP_IO_DATA IOdata, DWORD dwsize)
	{
		
		//Initialize IGTL MessageBase
		if(IOdata->RxMode == M_C_IOCP_RX_INIT)
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
				IOdata->RxMode = M_C_IOCP_Rx_IGTLHEADERDONE;
				return IOCP_Recv_IGTLBODY(client, IOdata, 0);
			}
		}
	}

	//// Receive IGTL_Body Message
	int MUSiiCTCPClientSocketWin::IOCP_Recv_IGTLBODY(LP_CLIENT_DATA client,LP_IO_DATA IOdata, DWORD dwsize)
	{
		if(IOdata->RxMode == M_C_IOCP_Rx_IGTLHEADERDONE)
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
			IOdata->RxMode         = M_C_IOCP_Rx_IGTLBODY;
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
				IOdata->RxMode = M_C_IOCP_Rx_IGTLBODYDONE;
				return GetIGTLMessage(client,IOdata);
			}
		}
	}

	

	/// Retrive IGTL Message from IOCP data buffer.
	int MUSiiCTCPClientSocketWin::GetIGTLMessage(LP_CLIENT_DATA client,LP_IO_DATA IOdata)
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

			/// Set Reference Data
			if(client->bReference)
				SetReferenceData(msg);

			/// Set Sync Data
			if(client->bSync)
				SetSyncData(msg);

			//if(client->IOFilter->CheckMessageBase(IOdata->IGTLMsg, m_bPreInputCheckDeviceType).IsNotNull())
			if(m_pParentTCPIO->CheckMessageBasPostOutputMUSiiCIOFilter(msg).IsNotNull() || bIsString)
			{
				/*if(IsTrackingDataMessage(msg))
				{
					std::cout << "Tracking Message" << std::endl;
				}*/
				//// To Do:: Set MUSiiCFileIO Filter of Client structure using StringMessage:: KHJ

				/// TCP Post Processing
				//// Post processing function for TCP/IP Communication 
				/// In General, 
				/// numOfRun : When using Data-Interface, this number indicate the index of new data in Data-Interface
				/// TaskInfo : TCP status
				/// ptr      : the pointer of caller class
				/// data1    : Data 
				/// data2    : the address of server socket
				/// data3    : the address of client socket
				m_pParentTCPIO->TCPPostProcessing(M_POST_CONTROL_PRAR_DATA, M_TCP_DATA_RECEIVED, this, msg, &(client->slntAddr), &(client->clntAddr));
			}
		}		
		delete IOdata;

		return IOCP_Recv_IGTLMsg(client);
	}

	/// Send IGTL Message
	int MUSiiCTCPClientSocketWin::IOCP_Send_IGTLMsg(LP_CLIENT_DATA client,igtl::MessageBase::Pointer msg)
	{
		if(client != NULL && msg.IsNotNull() && client->TXMode == M_C_IOCP_Tx_IGTLDONE)
		{
			LP_IO_DATA pPerIOData = new IO_DATA;
			ZeroMemory(pPerIOData, sizeof(IO_DATA));
			pPerIOData->IO_MODE = M_C_IOCP_Tx;
			pPerIOData->TXMode = M_C_IOCP_TX_INIT;
			pPerIOData->IGTLMsg = msg;
			return IOCP_SendIGTL(client, pPerIOData, 0);
		}
		else
		{
			if(client == NULL)
				MUSiiC_LOG(logERROR) << "Client is NULL";
			else if( client->TXMode != M_C_IOCP_Tx_IGTLDONE)
				MUSiiC_LOG(logINFO) << "Client socket is sending another data!";
			else if(msg.IsNull())
				MUSiiC_LOG(logINFO) << "**Temp Message of IGTL is NULL Message";
			return 0;
		}
	}

	/// Send IGTL Message to All connected clients excluding pre-defined client
	int MUSiiCTCPClientSocketWin::IOCP_Send_IGTLMsg_Exclude(LP_CLIENT_DATA client,igtl::MessageBase::Pointer msg)
	{
		//EnterCriticalSection(&m_CS);
		m_pFastMutex->Lock();
			
		LP_CLIENT_DATA temp = NULL;

		int sz(m_listClientSocket->concurrent_size());
		int r(0);
				
		for(int i=0; i<sz; i++)
		{
			m_listClientSocket->concurrent_try_get(temp, i);
			if(temp != client)
			{
				IOCP_Send_IGTLMsg(temp, msg);
				r++;
			}
		}
			
		m_pFastMutex->Unlock();
		return (r == sz)? -1 : r;
	}
	/// Send IGTL Message to All connected
	int MUSiiCTCPClientSocketWin::IOCP_Send_IGTLMsg_ALLClients(igtl::MessageBase::Pointer msg)
	{
		//EnterCriticalSection(&m_CS);
		m_pFastMutex->Lock();
			
		LP_CLIENT_DATA temp = NULL;

		int sz(m_listClientSocket->concurrent_size());
		int r(0);
				
		for(int i=0; i<sz; i++)
		{
			m_listClientSocket->concurrent_try_get(temp, i);
			IOCP_Send_IGTLMsg(temp, msg);
		}
			
		m_pFastMutex->Unlock();
		return r;
}

	/// Sending function using IOCP
	int MUSiiCTCPClientSocketWin::IOCP_Send(LP_CLIENT_DATA client, LP_IO_DATA IOdata, std::string description )
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
	int MUSiiCTCPClientSocketWin::IOCP_SendIGTL(LP_CLIENT_DATA client, LP_IO_DATA IOdata, DWORD dwsize)
	{

		if(IOdata->TXMode == M_C_IOCP_TX_INIT)
		{
			IOdata->IGTLMsg->Pack();
			IOdata->wsaBuf.buf = (char*)IOdata->IGTLMsg->GetPackPointer();
			IOdata->wsaBuf.len = IOdata->IGTLMsg->GetPackSize();
			IOdata->n_iExpectSum = IOdata->IGTLMsg->GetPackSize();
			IOdata->n_iSum = 0;
			IOdata->TXMode = M_C_IOCP_Tx_IGTL;
			m_pFastMutex->Lock();
			client->TXMode = M_C_IOCP_Tx_IGTL;
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
				IOdata->TXMode = M_C_IOCP_Tx_IGTLDONE;
				IOCP_SendIGTLDone(client, IOdata);
			}
		}

		return 0;
	}

	/// Sent out IGTL Message
	int MUSiiCTCPClientSocketWin::IOCP_SendIGTLDone(LP_CLIENT_DATA client, LP_IO_DATA IOdata)
	{
		if(!IOdata)
		{
			if(m_bDebug)
				MUSiiC_LOG(logINFO) << "pPerIOData is NULL";
			return 0;
		}
		
		if(m_bDebug)
			MUSiiC_LOG(logINFO) << "IOCP_SendIGTLDone:: try to delete data";
		
		IOdata->TXMode = M_C_IOCP_Tx_IGTLDONE;
		delete IOdata;

		m_pFastMutex->Lock();
		client->TXMode = M_C_IOCP_Tx_IGTLDONE;
		m_pFastMutex->Unlock();
		
		if(m_bDebug)
			MUSiiC_LOG(logINFO) << "IOCP_SendIGTLDone:: Did";
		
		/// Notify TCP status
		m_pParentTCPIO->TCPPostProcessing(M_POST_CONTROL_PRAR,M_TCP_DATA_SENT, this, NULL, &(client->slntAddr), &(client->clntAddr)); 

		return 1;
	}

	/// Send out MUSiiCIOFilter of client
	int MUSiiCTCPClientSocketWin::IOCP_SendMUSiiCIOFilter(LP_CLIENT_DATA client)
	{
		if(client != NULL)
		{
			if(client->IOFilter.IsNotNull())
			{
				std::vector<std::string> MUSiiCFilterList;
				MUSiiCFilterList =  client->IOFilter->GetDataTypeList();
				int i(0), r(0), sz(0);
				sz = MUSiiCFilterList.size();
				for(i = 0; i<sz; i++)
					r+=_IOCP_SendMUSiiCIOFilter(client, MUSiiCFilterList[i]);

				return r;
			}
		}
		return 0;
	}

	/// To Do :: check this function cannon96
	/// Send out std::string of MUSiiCIOFilter of client
	int MUSiiCTCPClientSocketWin::_IOCP_SendMUSiiCIOFilter(LP_CLIENT_DATA client, std::string& filter)
	{
		igtl::StringMessage::Pointer pFilter = igtl::StringMessage::New();
		pFilter->SetDeviceName(M_IO_FILTER); // Using this string value "M_IO_FILTER" for encoding and decoding for MUSiiCIOFilter
		pFilter->SetString(filter);
		return IOCP_Send_IGTLMsg(client, (igtl::MessageBase::Pointer)pFilter);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	////TODO::cannon 96
//	/// Client-Network Task function is implemented in this function.
	int MUSiiCTCPClientSocketWin::TaskFunction(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
	{
	
		LP_CLIENT_DATA client = NULL;
		LP_IO_DATA pPerIOData = NULL;
		//LPOVERLAPPED lpOv = NULL;
		DWORD dwTransfer;
		BOOL ret;

		while(m_bNetworkThread)
		{
			
			ret = GetQueuedCompletionStatus(m_hCompletionPort, &dwTransfer, 
											(PULONG_PTR)&client,//(LPDWORD)&client,, //64bit
											(LPOVERLAPPED*)&pPerIOData, INFINITE);

			
			/// check disconnection of client
			if(dwTransfer == 0)
			{
				if(client)
				{
					if(client->bReconnect)// && client->TCP_STATUS == M_TCP_CLIENT_CONNECTED)
					{
						if(m_bDebug)
						{
							MUSiiC_LOG(logINFO) << "Disconnected %s client (Socket::" << client->hClntSocket <<")";
							MUSiiC_LOG(logINFO) << "Reconnecte the server:" << inet_ntoa(client->slntAddr.sin_addr);
							
						}
						
						this->ConnectToHost(inet_ntoa(client->slntAddr.sin_addr), ntohs(client->slntAddr.sin_port));
						m_pParentTCPIO->TCPPostProcessing(M_POST_CONTROL_PRAR,M_TCP_CLIENT_DISCONNECTED, this, NULL, &(client->slntAddr), &(client->clntAddr)); 
						RemoveClient(client);
						
					}
					else
					{
						if(m_bDebug)
							MUSiiC_LOG(logINFO) << "Disconnected %s client:" << inet_ntoa(client->clntAddr.sin_addr);

						m_pParentTCPIO->TCPPostProcessing(M_POST_CONTROL_PRAR,M_TCP_CLIENT_DISCONNECTED, this, NULL, &(client->slntAddr), &(client->clntAddr)); 
						RemoveClient(client);
					}
				}
				continue;
			}
			if(!pPerIOData)
			{
				MUSiiC_LOG(logINFO) << "pPerIOData is NULL";// << inet_ntoa(client->clntAddr.sin_addr);
				continue;
			}
			
			if(pPerIOData->IO_MODE == M_C_IOCP_Rx)
			{
				switch (pPerIOData->RxMode)
				{
					case M_C_IOCP_RX_INIT:
						IOCP_Recv_IGTLHEADER(client, pPerIOData,0);
						break;
					case M_C_IOCP_Rx_IGTLHEADER:
						IOCP_Recv_IGTLHEADER(client, pPerIOData, dwTransfer);
						break;
					case M_C_IOCP_Rx_IGTLHEADERDONE:
						IOCP_Recv_IGTLBODY(client, pPerIOData, 0);
						break;
					case M_C_IOCP_Rx_IGTLBODY:
						IOCP_Recv_IGTLBODY(client, pPerIOData, dwTransfer);
						break;
					case M_C_IOCP_Rx_IGTLBODYDONE:
						GetIGTLMessage(client,pPerIOData);
						break;
					default:
						break;
				}
			}
			else if(pPerIOData->IO_MODE == M_C_IOCP_Tx)
			{
				MUSiiC_LOG(logINFO) << "Data Tx";
				switch (pPerIOData->TXMode)
				{
					case M_C_IOCP_TX_INIT:
						break;
					case M_C_IOCP_Tx_IGTL:
						IOCP_SendIGTL(client, pPerIOData, dwTransfer);
						break;
					case M_C_IOCP_Tx_IGTLDONE:
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
	/// Connecting Task
	int MUSiiCTCPClientSocketWin::ConnectTask(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
	{
		while(m_bConnectThread)
		{
			LP_CLIENT_DATA ptempClient;
			int sz(m_listClientSocketConnect->concurrent_size());
			m_listClientSocketConnect->concurrent_wait_get_pop_front(ptempClient);

			//if(ptempClient->TCP_STATUS == M_TCP_CLIENT_CONNECTING || ptempClient->TCP_STATUS == M_TCP_CLIENT_RECONNECTING)
			{
			
				///Connect
				if(connect(ptempClient->hClntSocket,(PSOCKADDR)&ptempClient->slntAddr,sizeof(SOCKADDR_IN))==SOCKET_ERROR)
				{
					MUSiiC_LOG(logINFO) << "*** Client cannot connect the server";
					if(ptempClient->bReconnect)
					{
						if(m_bDebug)
						{
							///Reconnect
							MUSiiC_LOG(logINFO) << "Disconnected %s client Socket(:" << ptempClient->hClntSocket <<")";
							MUSiiC_LOG(logINFO) << "Reconnecte the server:" << inet_ntoa(ptempClient->slntAddr.sin_addr);						
						}

						ptempClient->TCP_STATUS = M_TCP_CLIENT_RECONNECTING;
						this->m_listClientSocketConnect->concurrent_push_back(ptempClient);
					}
					else
					{
						if(m_bDebug)
							MUSiiC_LOG(logINFO) << "Disconnected %s client Socket(:" << ptempClient->hClntSocket <<")";

						m_pParentTCPIO->TCPPostProcessing(M_POST_CONTROL_PRAR,M_TCP_CLIENT_DISCONNECTED, this, NULL, &(ptempClient->slntAddr), &(ptempClient->clntAddr)); 
					
						if(ptempClient->hClntSocket > 0 && ptempClient->hClntSocket < 4000000)
						{
							CloseSocket(ptempClient->hClntSocket);
							delete ptempClient;
							ptempClient = NULL;
						}
					}

					continue;
				}

				/////Testing about getting this client socket information
				//int s(sizeof(ptempClient->hClntSocket));

				/// To Do: Get ////////////////////////////////////////////
				/// Test Code :: cannon96

				/*char name[255];
				PHOSTENT hostinfo;
				char* name_ip;
				if(::gethostname(name, sizeof(name)) == 0)
				{
					hostinfo = gethostbyname(name);
					if(hostinfo != NULL)
						name_ip = inet_ntoa(*(in_addr*)*hostinfo->h_addr_list);
				}
				if(getpeername(ptempClient->hClntSocket, (SOCKADDR*)&ptempClient->clntAddr, &s) == -1)
				{
					MUSiiC_LOG(logINFO) << "The error of getpeername";
				}*/
			
				
				//////////////////////////////////////////////////////////////////////
				ptempClient->TCP_STATUS = M_TCP_CLIENT_CONNECTED;
				////Save the last connected client
				m_pLastConnectedClient = ptempClient;

				/// Add new client to the list of connected client
				AddNewClients(ptempClient);
				/// Set new client to IOCP
				CreateIoCompletionPort((HANDLE)ptempClient->hClntSocket, m_hCompletionPort, (DWORD)ptempClient, 0); 

				m_pFastMutex->Lock();
				ptempClient->TXMode = M_C_IOCP_Tx_IGTLDONE;
				m_pFastMutex->Unlock();

				////////////////////////////////////////////
				/// Sending MUSiiCIO filter
				// IOCP_SendMUSiiCIOFilter(ptempClient); //cannon96

				///////////////////////////////////////////

				/// Receive IGTL Message
				IOCP_Recv_IGTLMsg(ptempClient);

				/// Notify TCP status
				m_pParentTCPIO->TCPPostProcessing(M_POST_CONTROL_PRAR,M_TCP_CLIENT_CONNECTED, this, NULL, &(ptempClient->slntAddr), &(ptempClient->clntAddr)); 
			}
		}

		m_bConnectThread = false;
		if(m_bDebug)
				MUSiiC_LOG(logINFO) << "Listening Thread is Finished";
		return NULL;
	}

	///////////////////////////////////////////////////////////////////////////////////////
	//// Sending Task
	int MUSiiCTCPClientSocketWin::SendTask(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
	{
		while(m_bSendThread)
		{
			
			igtl::MessageBase::Pointer tempMsg;//= igtl::MessageBase::New();
			if(m_bDebug)
				MUSiiC_LOG(logINFO) << "Waiting Data";

			if(this->m_bVPreInputDATA_IF_Set)
				this->m_pVPreInputDATA_IF_Set->Concurrent_wait_get_pop_front_fromMUSiiCVectorSet(tempMsg);

			if(tempMsg.IsNotNull() )
			{
				if(m_bDebug)
					MUSiiC_LOG(logINFO) << "Got Data";
			
				
				bool IsString = IsStringMessage(tempMsg);
				/// Send the given data to all connected clients
				if(m_pParentTCPIO->CheckMessageBasePostInputMUSiiCIOFilter(tempMsg).IsNotNull() || IsString)
					IOCP_Send_IGTLMsg_ALLClients(tempMsg);
			}
		}

		m_bSendThread = false;
		if(m_bDebug)
				MUSiiC_LOG(logINFO) << "Sending Thread is Finished";
		return NULL;
	}

	int MUSiiCTCPClientSocketWin::StartNetworkThreads()
	{
		/// 05.Start listen-thread and working-thread
		m_tcp_status			= M_TCP_SERVER_CREATED;
		m_bNetworkThread		= true;
		m_bConnectThread		= true;
		m_bSendThread			= true;

		this->m_tcp_status		= M_TCP_CLIENTS_SERVICE_INIT;
		m_pParentTCPIO->TCPPostProcessing(M_POST_CONTROL_PRAR,M_TCP_CLIENTS_SERVICE_INIT, this, NULL, NULL, NULL); 
		this->SetEnableThread(true, M_ALLTASKOBJECT);
		
		int r = this->RunTask(M_THREAD_RUN_CONTINUOUS, m_tcp_status, this, NULL, NULL, NULL, M_ALLTASKOBJECT);

		m_bClientThreadsRun = r>-1 ? true: false ;

		return r;
	}

	/// Close All Clients
	/// Stop All thread
	int MUSiiCTCPClientSocketWin::CloseAllClients()
	{
		if(m_bDebug)
				MUSiiC_LOG(logINFO) << "MUSiiCTCPServerWin::Close Server:  ";
		m_bConnectThread		= false;
		m_bNetworkThread		= false;
		m_bSendThread			= false;

		//Close network thread
		PostQueuedCompletionStatus(m_hCompletionPort, 0, NULL, NULL);
		/// Stop All task thread
		this->StopTask(M_ALLTASKOBJECT);
		
		/// Close Listening socket
		RemoveAllClientData();
		WSACleanup();
		this->m_tcp_status		= M_TCP_CLIENTS_SERVICE_FINISH;
		m_pParentTCPIO->TCPPostProcessing(M_POST_CONTROL_PRAR,M_TCP_CLIENTS_SERVICE_FINISH, this, NULL, NULL, NULL); 

		m_bClientThreadsRun = false;
		return 0;
	}


	//Handling of an error from IOCP function
	int MUSiiCTCPClientSocketWin::ErrorHandling(int errorcode, LP_CLIENT_DATA client,std::string desp , int mode)
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
	bool MUSiiCTCPClientSocketWin::RemoveAllClientData()
	{
		LP_CLIENT_DATA temp = NULL;
		/*while (!m_listPerSocket.empty())
		{
			temp = m_listPerSocket.front();
			RemoveClient(temp);
		}*/

		int sz(m_listClientSocket->concurrent_size());
		for(int i=0; i <sz ; i++)
		{
			m_listClientSocket->concurrent_try_get(temp, i);
			RemoveClient(temp);
		}

		return m_listClientSocket->concurrent_empty();
	}


	////////////////////////////////////////
	/// Get the list of Connected client list
	igtl::MUSiiCVector<LP_CLIENT_DATA>::Pointer MUSiiCTCPClientSocketWin::GetConnectedClientList()
	{ 
		return m_listClientSocketConnect;
	}

	/// Get the number of connected client list
	int MUSiiCTCPClientSocketWin::GetNumOfConnectedClients()
	{
		return m_listClientSocketConnect->concurrent_size();
	}
}