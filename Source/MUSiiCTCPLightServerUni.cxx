/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/
#include "MUSiiCTCPLightServerUni.h"

namespace igtl
{
	/// Constructor
	MUSiiCTCPLightServerUni::MUSiiCTCPLightServerUni()
	{
		m_pNameOfClass="MUSiiCTCPLightServerUni";
		Initialize();
	}
	
	/// Deconstructor
	MUSiiCTCPLightServerUni::~MUSiiCTCPLightServerUni()
	{
	}

	/// Get the pointer of NetworkBuffer
	igtl::MUSiiCigtlMsgVector::Pointer MUSiiCTCPLightServerUni::GetNetworkBuffer()
	{
		return m_pNetworkBuffer;
	}

	/// Creater Server Socket
	int MUSiiCTCPLightServerUni::CreateServer(int port, bool useSelfDataIF)
	{
		/*if(!m_bigtlMsg_IF)
			return -1;*/

		///check is there data-interface
		if(useSelfDataIF && !IsDataInterface()) // && !m_bDATA_IF)
			PrepareNetwork(useSelfDataIF);

		/// Check data interface
		if(!IsDataInterface())
			return -1;
		
		/// If there is already server socket, then delete the server socket
		if(m_pigtlServerSocket.IsNotNull())
			m_pigtlServerSocket->CloseSocket();

		m_pigtlServerSocket = igtl::ServerSocket::New();
		m_bigtlServerSocket = true;

		m_R=m_pigtlServerSocket->CreateServer(port);

		if(m_R>-1)
		{
			m_tcp_status = M_TCP_Server_Created;
			
			///Sending callback information
			double ts = this->GetCurrentTimestamp();
			std::string msg("ServerSocket is created");
			TCPServerPostProcessing(0, m_tcp_status, this, NULL, &ts, &msg);
			
			/// Prepare networking thread
			SetEnableThread(true);
			
			std::string str("ServerSocket");
			this->m_pNetworkBuffer->SetDescription(str);
			/// Run network thread for network communication
			return RunTask(M_THREAD_RUN_CONTINUOUS, m_tcp_status, this, NULL, NULL, NULL);
		}
		else
		{
			m_tcp_status = M_TCP_Server_Disconnected;
			///Sending callback information
			double ts = this->GetCurrentTimestamp();
			std::string msg("ServerSocket is not created");
			TCPServerPostProcessing(0, m_tcp_status, this, NULL, &ts, &msg);
		}

		return m_R;
	}

	/// (Pause Task)
	void MUSiiCTCPLightServerUni::PauseServerTask()
	{
		PauseTask();
		m_tcp_status = M_TCP_Server_Pause;
	}

	/// (Resume Task)
	int MUSiiCTCPLightServerUni::ResumeServerTask()
	{
		m_tcp_status = M_TCP_Server_Connected;
		return ResumeTask();
	}

	/// cannon96
	/// Close server socket
	int MUSiiCTCPLightServerUni::CloseServer()
	{
		
		///Stop Task
		/// Stop Task
		//if(m_tcp_status == M_TCP_Server_Created)
		this->StopTask();

		/// Release Send-Out buffer
		ReleaseNetworkBuffer();

		/// Close Socket
		m_pigtlServerSocket->CloseSocket();
		/// Set tcp status
		m_tcp_status = M_TCP_Server_Disconnected;

		////Close all client socket (cannon96)
		for(int i=0; i<GetNumOfClients();i++) 
		{
			m_MSUiiCTCPClients[i]->CloseClientSocket("Server socket is closed");
		}
		return 0;
	}

	/// Set time-out for listening a request of client's connection
	/// the unit of timeout is msec.
	void MUSiiCTCPLightServerUni::SetTimeout(unsigned long msec)
	{
		m_lTimeout = msec;
	}

	/// Set Dropping 
	void MUSiiCTCPLightServerUni::SetDropping(bool drop)
	{
		m_bDropping = drop;
	}

	/// Set Pop 
	void MUSiiCTCPLightServerUni::SetPopping(bool pop)
	{
		m_bPop = pop;
	}

	/// Get Num of connected-clients
	int MUSiiCTCPLightServerUni::GetNumOfClients()
	{
		return m_MSUiiCTCPClients.size();
	}

	/// Check there are clients or not.
	bool MUSiiCTCPLightServerUni::IsConnectedClients()
	{
		return GetNumOfClients()>0?true:false;
	}

	

///Protected::operations
	void MUSiiCTCPLightServerUni::Initialize()
	{
		MUSiiCTCPIO::Initialize();

		m_MSUiiCTCPClients.clear();
		m_tcp_status = M_TCP_Server_Disconnected;

		m_bPop = true;
		m_R = -1;

		m_bigtlServerSocket = false;
		m_iPort = -1;
		m_lTimeout= 3;
		m_bDropping = false;

		m_pServerMutex = igtl::MutexLock::New();
		
	}
	

	////TODO::cannon 96
	/// Client-Network Task function is implemented in this function.
	int MUSiiCTCPLightServerUni::TaskFunction(int numOfRun, int taskInfo, void* ptr, void* data1, void* data2, void* data3)
	{
		igtl::ClientSocket::Pointer client;
		client = WaitForConnection();
		
		
		if(client.IsNotNull())
		{
			m_pServerMutex->Lock();
			igtl::MUSiiCTCPClientUni::Pointer pMClient = igtl::MUSiiCTCPClientUni::New();
			if(pMClient->SetClientSocket2(client,GetNumOfClients())>-1)
			{
				/*pMClient->SetClientIndex(m_MSUiiCTCPClients.size());
				char des[100] ={0,};
				sprintf(des, "%d-th client", pMClient->GetClientIndex());
				pMClient->GetDataInterface()->SetDescription(des);*/ 
				m_MSUiiCTCPClients.push_back(pMClient);
				///Sending callback information
				double ts = this->GetCurrentTimestamp();
				std::string msg("Client is connected");
				m_tcp_status = M_TCP_Server_Connected;
				TCPServerPostProcessing(0, m_tcp_status, this, NULL, &ts, &msg);
			}
			m_pServerMutex->Unlock();
		}
		
		
		if(IsDataInterface() && m_MSUiiCTCPClients.size()>0)
			return SendigtlMsg();
		else
			return 0;
	}

	/// Send Data(igtl Message) to TCP/IP network
	int MUSiiCTCPLightServerUni::SendigtlMsg()
	{
		int s = GetNumOfClients(); 
		igtl::MessageBase::Pointer tempMsg;
		
		if(m_bDropping)
			m_pDATA_IF->concurrent_wait_get_pop_back(tempMsg, true);
		else
			m_pDATA_IF->concurrent_wait_get_pop_front(tempMsg);

		if(s>0)
		{
			if(tempMsg.IsNull())
				return 0;//-1;
			m_pServerMutex->Lock();
			for(int i=0; i<s;i++)
			{
				if(m_MSUiiCTCPClients[i]->IsClienSocket())
				{
					{
						m_MSUiiCTCPClients[i]->SendigtlMsg2(tempMsg);
						double	ts = GetMsgTimeStamp(tempMsg);
						std::string msg = "IGTL";//= tempMsg->GetDeviceName();
						TCPServerPostProcessing(i, m_tcp_status, this, NULL, &ts, &msg);
					}
				}
				else
				{
					m_MSUiiCTCPClients.erase(m_MSUiiCTCPClients.begin()+i);
					s-=1;
				}
			}
			m_pServerMutex->Unlock();
		}
		else
		{			
			///Sending callback information
			double ts = this->GetCurrentTimestamp();
			std::string msg("No Client is connected");
			m_tcp_status = M_TCP_Server_NO_Client;
			TCPServerPostProcessing(0, m_tcp_status, this, NULL, &ts, &msg);
		}
		
		return s;
	}

	/// Waiting for a request to connect from any client
	igtl::ClientSocket::Pointer MUSiiCTCPLightServerUni::WaitForConnection()
	{
		if(m_pigtlServerSocket.IsNotNull())
		{
			return m_pigtlServerSocket->WaitForConnection(m_lTimeout);
		}
		else
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
	int MUSiiCTCPLightServerUni::TCPServerPostProcessing(int numOfRun, int taskInfo, void* ptr, void* data1, void* data2, void* data3)
	{
		int r(0);
		if(m_bEnableExternalOutputCallbackFuntions)
		{
			r = CallExternalOutputCallbackFunctions(numOfRun, taskInfo, ptr, data1, data2, data3);
		}
		return r;
	}
}