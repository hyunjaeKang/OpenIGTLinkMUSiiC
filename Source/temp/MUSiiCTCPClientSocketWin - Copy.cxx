/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/

#include "MUSiiCTCPClientUni.h"
#include "MUSiiCUtil.h"

namespace igtl
{
//	/// Constructor
//	MUSiiCTCPClientUni::MUSiiCTCPClientUni()
//	{
//		m_pNameOfClass="MUSiiCTCPClientUni";
//		Initialize();
//	}
//
//	/// Deconstructor
//	MUSiiCTCPClientUni::~MUSiiCTCPClientUni()
//	{
//		
//	}
//
//	/// Get Client Mode
//	MUSiiC_CLIENT_MODE MUSiiCTCPClientUni::GetClientMode()
//	{
//		return m_ClientMode;
//	}
//	
//
//	/// Connect to Server(Host) with hostname(host-ip-address) and port
//	int MUSiiCTCPClientUni::ConnectToHost(const char* hostname, int port, 
//										int attempt, bool continousattemp, bool useSelfDataIF)
//	{
//		///check is there data-interface
//		if(useSelfDataIF && !IsDataInterface()) // && !m_bDATA_IF)
//			PrepareNetwork(useSelfDataIF);
//
//		/// Check data interface
//		if(!IsDataInterface()&& !m_bEnableExternalOutputCallbackFuntions)
//			return -1;
//
//		m_ClientMode		= M_TCP_CLIENT_CLIENT;
//		m_sHostName			= hostname;
//		m_iHostPort			= port;
//		m_iAttempt			= attempt;
//		m_bContinuousAttemp = continousattemp;
//		m_bUseDataInterface = IsDataInterface();//useSelfDataIF;
//
//		m_tcp_status = M_TCP_Connecting;
//		/// In this class will use task-thread for receiving data from TCP/IP network
//		SetEnableThread(true); 
//
//		m_pigtlMsgHeader = igtl::MessageHeader::New();
//		
//		/// Run network thread for network communication
//		return RunTask(M_THREAD_RUN_CONTINUOUS, m_tcp_status, this, NULL, NULL, NULL);
//		//this->WaitTask();
//		
//		///// Run network thread for network communication
//		//int r = RunTask(M_THREAD_RUN_CONTINUOUS, m_tcp_status, this, NULL, NULL, NULL);
//		////this->WaitTask();
//
//		//if(m_tcp_status == M_TCP_Connected)
//		//	return RunTask(M_THREAD_RUN_CONTINUOUS, m_tcp_status, this, NULL, NULL, NULL);
//		//else
//		//	return -1;
//		/*if(TryConnectToHost(m_sHostName.c_str(), m_iHostPort, m_iAttempt) == 0)
//			return RunTask();
//		else
//			return -1;*/
//	}
//
//	/// (Pause Task)
//	void MUSiiCTCPClientUni::PauseClientTask()
//	{
//		PauseTask();
//		m_tcp_status = M_TCP_Pause;
//	}
//
//	/// (Resume Task)
//	int MUSiiCTCPClientUni::ResumeClientTask()
//	{
//		m_tcp_status = M_TCP_Connected;
//		return ResumeTask();
//	}
//	
//	/// Try to reconnect to Server(Host)
//	int MUSiiCTCPClientUni::ReConnectToHost()
//	{
//		if(m_tcp_status == M_TCP_Connected || m_tcp_status == M_TCP_Connecting)
//			return 0;
//		else if (m_tcp_status == M_TCP_Pause)
//			return ResumeClientTask();
//		else
//		{
//			m_tcp_status = M_TCP_Connecting;
//
//			m_pigtlMsgHeader = igtl::MessageHeader::New();
//			/// Run network thread for network communication
//			if(TryConnectToHost(m_sHostName.c_str(), m_iHostPort, m_iAttempt) == 0)
//			{
//				m_tcp_status = M_TCP_Connected;
//				return RunTask(M_THREAD_RUN_CONTINUOUS, m_tcp_status, this, NULL, NULL, NULL);
//			}
//			else
//				return -1;
//		}
//
//	}
//	
//	/// Close client socket
//	/// Please check this function
//	void MUSiiCTCPClientUni::CloseClientSocket(std::string message)
//	{
//		/// Release Send-Out buffer
//		ReleaseNetworkBuffer();
//		
//		m_pigtlClientSocket->CloseSocket();
//
//		/// Stop Task
//		if(m_tcp_status == M_TCP_Connected)
//			this->StopTask();
//		
//		
//
//		/// Initialize Send-Out buffer
//		InitializeNetworkBuffer();
//		m_bNetworkBuffer = false;
//
//		/// Set tcp status
//		m_tcp_status = M_TCP_Disconnected;
//
//		double ts = GetCurrentTimestamp();
//		std::string tempmessage("_CloseClientScoket");
//		message = GetClientInfoString()+message+tempmessage;
//		TCPPostProcessing(m_iClientIndex, m_tcp_status, this, NULL, &ts , &message);
//	}
//
//	/// Set a pointer of igtl::ClientSocket for multiple clients connection
//	int MUSiiCTCPClientUni::SetClientSocket(igtl::ClientSocket::Pointer cs, igtl::MutexLock::Pointer pNetworkLock, bool SendDropping, int clientindex)
//	{
//		m_ClientMode = M_TCP_CLIENT_SERVER;
//		
//		/// Set the pointer of igtlClientScoket with member variable
//		m_pigtlClientSocket = cs;
//		m_bigtlClientSocket = true;
//
//		m_bAlive = true;
//
//		if(pNetworkLock.IsNotNull())
//			m_pNetworkLock = pNetworkLock;
//
//		SetEnableThread(true);
//		//// Create Network Buffer
//		/// m_bNetworkBuffer = CreateNetworkBuffer();
//		PrepareNetwork();
//		//// Setting dropping
//		m_bSendDropping = SendDropping;
//		/// Set the index of this client
//		SetClientIndex(clientindex);
//		/// Initialize the netweok bufffer
//		InitializeNetworkBuffer();
//		/// 
//		m_tcp_status = M_TCP_ServerClient_Connected;
//		/// Start Task-thread for sending data to TCP/IP network 
//		return RunTask(M_THREAD_RUN_CONTINUOUS, m_tcp_status, this, NULL, NULL, NULL);
//	}
//
//	/// Set a pointer of igtl::ClientSocket for multiple clients connection
//	int MUSiiCTCPClientUni::SetClientSocket2(igtl::ClientSocket::Pointer cs, int clientindex)
//	{
//		m_ClientMode = M_TCP_CLIENT_SERVER;
//		
//		/// Set the pointer of igtlClientScoket with member variable
//		m_pigtlClientSocket = cs;
//		m_bigtlClientSocket = true;
//
//		m_bAlive = true;
//
//		/// Set the index of this client
//		SetClientIndex(clientindex);
//
//		return clientindex;
//	}
//
//
///////protected function
//	
//	/*/// Release Send-Out network buffer
//	bool MUSiiCTCPClientUni::ReleaseNetworkBuffer()
//	{
//		if(m_bNetworkBuffer)
//			if(m_pNetworkBuffer->IsWaiting())
//				m_pNetworkBuffer->EnforceRelease();
//
//		return m_bNetworkBuffer;
//	}*/
//
///////////////////////////////////////////////////////////////////////////////
//	void MUSiiCTCPClientUni::Initialize()
//	{
//		MUSiiCTCPIO::Initialize();
//
//		m_ClientMode			= M_TCP_CLIENT_NONE;
//		m_sHostName				= "";
//		m_iHostPort				= -1;
//		m_iAttempt				= -1;
//		m_bigtlClientSocket		= false;
//		m_bSendDropping			= false;
//		m_bUseDataInterface		= true;
//		m_iClientIndex			= 0;
//
//		m_bReferenceDataScoket	= false;
//		m_bGotData				= false;
//		m_bAlive					= false;
//
//		m_tcp_status = M_TCP_Disconnected;
//
//		m_iSendBufferSize			= 10; 
//		m_pNetworkLock				= NULL;
//
//		m_pClientDataLock			= igtl::MutexLock::New();
//	}
//	//////////////////////////////////////////////////////////////
//	//////////////////////////////////////////////////////////////
//	/// Implemtation of Task of client network
//	//////////////////////////////////////////////////////////////
//	//////////////////////////////////////////////////////////////
//	int MUSiiCTCPClientUni::TaskFunction(int numOfRun, int taskInfo, void* ptr, void* data1, void* data2, void* data3)
//	{
//		switch(m_ClientMode)
//		{
//			case M_TCP_CLIENT_CLIENT:
//				if(m_tcp_status == M_TCP_Connecting) //Connecting
//				{
//					bool r;
//					r = (TryConnectToHost(m_sHostName.c_str(), m_iHostPort, m_iAttempt)>-1)?true:false;
//					m_bTaskThread = m_bContinuousAttemp || r;
//				}
//				else if (m_tcp_status == M_TCP_Connected || m_tcp_status == M_TCP_Connected_DATA) //Connected
//					return ReceiveigtlMsg();
//				else // Disconnected
//					this->StopTask(); //Stop network-thread
//				break;
//
//			case M_TCP_CLIENT_SERVER:
//				if(m_tcp_status == M_TCP_ServerClient_Connected) //Connecting
//					return SendigtlMsg();
//				break;
//			
//			default:
//				break;
//
//		}
//
//		return 1;
//	}
//	
//	/// Connect to Server(Host) with hostname(host-ip-address) and port
//	int MUSiiCTCPClientUni::TryConnectToHost(const char* hostname, int port, int attempt)
//	{
//		int i,s;
//
//		////Description
//		std::string tcp;
//		/// Timestamp
//		double ts;
//		
//		if(m_pigtlClientSocket.IsNotNull())
//			m_pigtlClientSocket->CloseSocket();
//
//		m_pigtlClientSocket	= igtl::ClientSocket::New();
//		m_bigtlClientSocket = true;
//		
//		if(!m_bigtlClientSocket)
//			return -1;
//
//		if(m_tcp_status == M_TCP_Connected)
//			s = 0;
//		else if (m_tcp_status == M_TCP_Connecting)
//		{
//			for(i=0; i<attempt; i++)
//			{
//				s = m_pigtlClientSocket->ConnectToServer(hostname, port);
//				
//				if(s == 0) ///Connected
//				{
//					m_bAlive = true;
//					m_tcp_status = M_TCP_Connected;
//					tcp = "_Client Socket is Connected";
//					break;
//				}
//				else
//				{
//					s=-1;
//					m_tcp_status = M_TCP_Disconnected;
//					tcp = "_Client Sockst is failed to Connecting ";
//					this->CloseClientSocket(tcp);
//				}
//			}
//		}
//
//		ts = GetCurrentTimestamp();
//		
//		tcp = GetClientInfoString()+tcp;
//		////Post processing
//		TCPPostProcessing(m_iClientIndex, m_tcp_status, this, NULL, &ts, &tcp); 
//		//TCPPostProcessing(m_iClientIndex, m_tcp_status, this, NULL, &ts, NULL); 
//		return s;
//	}
//
//	/// Get the index of this client with string message
//	std::string MUSiiCTCPClientUni::GetClientInfoString()
//	{
//		char msg2 [50];
//		sprintf(msg2, "ID:%3d (%s : %d) ",m_iClientIndex, m_sHostName.c_str(), m_iHostPort);
//		std::string tempmsg(msg2);
//		return tempmsg;
//	}
//
//	//// Post processing function for TCP/IP Communication 
//	/// In General, 
//	/// numOfRun : When using Data-Interface, this number indicate the index of new data in Data-Interface
//	/// TaskInfo : The argument of this task
//	/// ptr      : the pointer of caller class
//	/// data1    : Data 
//	/// data2    : the Time-stamp of the data
//	/// data3    : the name of Data
//	int MUSiiCTCPClientUni::TCPPostProcessing(int numOfRun, int taskInfo, void* ptr, void* data1, void* data2, void* data3)
//	{
//		int r(0);
//		if(m_bEnableExternalOutputCallbackFuntions)
//		{
//			if(m_bDATA_IF)
//			{
//				if(data1 != NULL)
//				{
//					igtl::MessageBase* tempMsg = (igtl::MessageBase*)data1;
//					/////////////////////////////////////////////////////////////////////
//					//std::ofstream outfile("ReceivedData_TCPPostProcessing.igtl", std::ofstream::binary);
//					//outfile.write((char*)tempMsg->GetPackPointer(), tempMsg->GetPackSize());
//					//outfile.close();
//					//////////////////////////////////////////////////////////////////////////////////
//					r = m_pDATA_IF->concurrent_push_back((igtl::MessageBase*) data1);
//					r = CallExternalOutputCallbackFunctions(r, taskInfo, ptr, NULL, data2, data3);
//				}
//				else
//					r = CallExternalOutputCallbackFunctions(numOfRun, taskInfo, ptr, NULL, data2, data3);
//			}
//			 else
//				 r = CallExternalOutputCallbackFunctions(numOfRun, taskInfo, ptr, data1, data2, data3);
//		}
//		else if(m_bDATA_IF && data1 != NULL)
//		{
//			igtl::MessageBase* temp = (igtl::MessageBase*)data1;
//			/////////////////////////////////////////////////////////////////////
//			//std::ofstream outfile("ReceivedData_TCPPostProcessing.igtl", std::ofstream::binary);
//			//outfile.write((char*)temp->GetPackPointer(), temp->GetPackSize());
//			//outfile.close();
//			//////////////////////////////////////////////////////////////////////////////////
//			r = m_pDATA_IF->concurrent_push_back(temp);
//		}
//
//		return r;
//	}
//	
//
//	/*/// Get Time_stamp from a message ///Go to 
//	double MUSiiCTCPClientUni::GetMsgTimeStamp(igtl::MessageBase* msg)
//	{
//		igtl::TimeStamp::Pointer ts = igtl::TimeStamp::New();
//
//		msg->GetTimeStamp(ts);
//
//		double t = ts->GetTimeStamp();
//		
//		if(t <= 0.1)
//		{
//			ts->GetTime();
//			t = ts->GetTimeStamp();
//		}
//
//		return t;
//	}*/
//	/// receive igtl Message from TCP/IP Network
//	int MUSiiCTCPClientUni::ReceiveigtlMsg()
//	{
//		int rxh,rxb;
//		/// Receive the igtl MessageHeader
//		rxh = ReceiveigtlMsgHeader();
//		if(rxh > -1)
//		{
//			rxb = ReceiveigtlMsgBody();
//			if (rxb >-1) 
//				return rxh+rxb;
//			else
//				return -1;
//		}
//		else
//			return -1;
//	}
//
//	/// Receive Data-Header(igtl MessageHeader) from TCP/IP network
//	int MUSiiCTCPClientUni::ReceiveigtlMsgHeader()
//	{
//		/// Check IsConnected?
//		/// I think this function only work beginning time.
//		if(!IsClienSocket())
//			return -1;
//		
//		int rx;
//		/// Initialize the pointer of igtl Message Header
//		/// m_pigtlMsgHeader = igtl::MessageHeader::New();
//		m_pigtlMsgHeader->InitPack();
//
//		/// Receive igtl Message Header
//		rx = m_pigtlClientSocket->Receive(m_pigtlMsgHeader->GetPackPointer(), m_pigtlMsgHeader->GetPackSize());
//
//		if(rx <=0)
//			m_bAlive = false;
//
//		if ( rx <= 0 ||rx != m_pigtlMsgHeader->GetPackSize())
//		{
//			/// Disconnect
//			CloseClientSocket("_ReceiveigtlMsgHeader");
//			return -1;
//		}
//		else
//		{
//			/// Unpacking of header message of OpenIGTLink
//			/*int c = m_pigtlMsgHeader->Unpack(1);
//			if(c & igtl::MessageHeader::UNPACK_BODY)
//			{
//				printf("IGTLHeader is received\n");
//				return rx;
//			}
//			else
//			{
//				printf("IGTLHeader is received\n");
//				return -1;
//			}*/
//			m_pigtlMsgHeader->Unpack();
//			return rx;
//		}
//	}
//	
//	/// Receive Data-Body (igtl MessageBase) from TCP/IP network
//	int MUSiiCTCPClientUni::ReceiveigtlMsgBody()
//	{
//		// Check data type and receive data body
//      if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "BIND") == 0)
//        {
//			return ReceiveMessage<igtl::BindMessage::Pointer, igtl::BindMessage>();
//        }
//      else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "COLORTABLE") == 0)
//        {
//			return ReceiveMessage<igtl::ColorTableMessage::Pointer, igtl::ColorTableMessage>();
//        }
//      else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "IMAGE") == 0)
//        {
//			std::string device(m_pigtlMsgHeader->GetDeviceName());
//			std::string us("US");
//			std::string ei("EI");
//			if(device.find(us)!=std::string::npos)
//			{
//				return ReceiveMessage<igtl::USMessage::Pointer, igtl::USMessage>();
//			}
//			else if(device.find(ei)!=std::string::npos)
//			{
//				return ReceiveMessage<igtl::EIMessage::Pointer, igtl::EIMessage>();
//			}
//			else
//				return ReceiveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>();
//        }
//      else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "IMGMETA") == 0)
//        {
//			return ReceiveMessage<igtl::ImageMetaMessage::Pointer, igtl::ImageMetaMessage>();
//		}
//      else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "LBMETA") == 0)
//        {
//			return ReceiveMessage<igtl::LabelMetaMessage::Pointer, igtl::LabelMetaMessage>();
//        }
//      else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "NDARRAY") == 0)
//        {
//			return ReceiveMessage<igtl::NDArrayMessage::Pointer, igtl::NDArrayMessage>();
//        }
//      else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "POINT") == 0)
//        {
//			return ReceiveMessage<igtl::PointMessage::Pointer, igtl::PointMessage>();
//        }
//	   else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "POSITION") == 0)
//        {
//			return ReceiveMessage<igtl::PositionMessage::Pointer, igtl::PositionMessage>();
//        }
//      else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "QTDATA") == 0)
//        {
//			return ReceiveMessage<igtl::QuaternionTrackingDataMessage::Pointer, igtl::QuaternionTrackingDataMessage>();
//		}
//	  else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "STATUS") == 0)
//        {
//			return ReceiveMessage<igtl::StatusMessage::Pointer, igtl::StatusMessage>();
//		}
//	  else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "STRING") == 0)
//        {
//			return ReceiveMessage<igtl::StringMessage::Pointer, igtl::StringMessage>();
//		}
//	  else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "QTDATA") == 0)
//        {
//			return ReceiveMessage<igtl::QuaternionTrackingDataMessage::Pointer, igtl::QuaternionTrackingDataMessage>();
//		}
//	  else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "TDATA") == 0)
//        {
//			return ReceiveMessage<igtl::TrackingDataMessage::Pointer, igtl::TrackingDataMessage>();
//		}
//	  else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "TRANSFORM") == 0)
//        {
//			return ReceiveMessage<igtl::TransformMessage::Pointer, igtl::TransformMessage>();
//		}
//	  else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "TRAJ") == 0)
//        {
//			return ReceiveMessage<igtl::TrajectoryMessage::Pointer, igtl::TrajectoryMessage>();
//		}
//	  else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "GEN") == 0)
//        {
//			return ReceiveMessage<igtl::GenMessage::Pointer, igtl::GenMessage>();
//		}
//	  else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "ARGUMENTS") == 0)
//        {
//			return ReceiveMessage<igtl::ArgMessage::Pointer, igtl::ArgMessage>();
//		}
//	  else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "FILE") == 0)
//        {
//			return ReceiveMessage<igtl::FileMessage::Pointer, igtl::FileMessage>();
//		}
//	  else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "EIIMAGE") == 0)
//        {
//			return ReceiveMessage<igtl::FixedImage::Pointer, igtl::FixedImage>();
//		}
//	  else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "EIUSIMAGE") == 0)
//        {
//			return ReceiveMessage<igtl::FixedImageBMODE::Pointer, igtl::FixedImageBMODE>();
//		}
//	  else 
//		return 0;
//	}
//
//	/// Check whether client socket is alive or not.
//	bool MUSiiCTCPClientUni::IsClienSocket()
//	{
//		//return (m_pigtlClientSocket->GetConnected()>0)?true:false;
//		//static int rr = 0;
//		///*int r = m_pigtlClientSocket->GetConnected();
//		//printf("%d :: Socket connected %d\n", rr, r);
//		//if(r>0)
//		//	printf("Socket is alive\n");
//		//else
//		//	printf("Socket is Dead\n");
//
//		//printf("++++++++++++++++++++++++++++\n");
//		//rr++;*/
//		//
//		//return true;
//		return m_bAlive;
//	}
//
//	/// Send Data(igtl Message) to TCP/IP network
//	int MUSiiCTCPClientUni::SendigtlMsg(igtl::MessageBase::Pointer msg)
//	{
//		int s;
//		double ts(0.0);
//		std::string textmsg;
//		//Check socket is alive?
//		//if(m_pigtlClientSocket->GetConnected())
//		/*if(m_pNetworkBuffer->concurrent_size()<1)
//			return 0;*/
//		
//		if(!IsClienSocket())
//		{
//			CloseClientSocket();
//			return -1;
//		}
//
//		igtl::MessageBase::Pointer tempMsg;
//		//igtl::MessageBase::Pointer tempMsg = igtl::MessageBase::New();
//		//igtl::MessageBase* tempMsg = NULL;
//
//		//printf("03_1:Try to get Data from %d -th client network buffer\n", this->m_iClientIndex);
//		if(m_bNetworkBuffer)
//		{
//			/// Get igtl Message (Data) from SendOut-Buffer (MUSiiCigtlMsgVector)
//			if(m_bSendDropping)
//				m_pNetworkBuffer->concurrent_wait_get_pop_back(tempMsg,true);
//				//m_pNetworkBuffer->concurrent_try_get_pop_back(tempMsg,true);
//			else
//			{
//				if(m_iClientIndex == 0)
//					m_pNetworkBuffer->concurrent_wait_get_pop_front(tempMsg);	
//				else
//					m_pNetworkBuffer->concurrent_wait_get_pop_front(tempMsg);	
//			}
//				//m_pNetworkBuffer->concurrent_try_get_pop_front(tempMsg);	
//		}
//		else
//			tempMsg = msg;
//		
//		//printf("03_2:Get Data from %d -th client network buffer\n", this->m_iClientIndex);
//		if(tempMsg.IsNull())
//		{
//			return -1;
//		}
//		/// Send out the data (igtl Message)
//		int ps =  tempMsg->GetPackSize();
//		//printf("The size of pack %d\n", ps);
//		//printf("04.%d-th client try to send data\n", this->m_iClientIndex);
//		m_pNetworkLock->Lock();
//		if(m_iClientIndex == 0)
//			s = m_pigtlClientSocket->Send(tempMsg->GetPackPointer(), tempMsg->GetPackSize());
//		else
//			s = m_pigtlClientSocket->Send(tempMsg->GetPackPointer(), tempMsg->GetPackSize());
//		m_pNetworkLock->Unlock();
//		//printf("The size of written message %d\n", s);
//		if(m_iClientIndex == 0)
//			printf("05.%d-th client sent %d-size data\n", this->m_iClientIndex, s);
//		else
//			printf("05.%d-th client sent %d-size data\n", this->m_iClientIndex, s);
//		
//		if(s<=0)
//			m_bAlive= false;
//
//		ts = GetMsgTimeStamp(tempMsg);
//		std::string msg2;
//
//		if( tempMsg.IsNotNull())
//			msg2 = "IGTL";//tempMsg->GetDeviceType();
//		else
//			msg2 = "NULL Data";
//
//		//TCPPostProcessing(0, m_tcp_status, this, tempMsg, &ts, &msg2);
//		TCPPostProcessing(0, m_tcp_status, this, NULL, &ts, &msg2);
//		
//		return s;
//	}
//
//	/// Send Data(igtl Message) to TCP/IP network directly
//	int MUSiiCTCPClientUni::SendigtlMsg2(igtl::MessageBase::Pointer msg)
//	{
//		int s;
//		double ts(0.0);
//		std::string textmsg;
//
//		if(msg.IsNull())
//			return 0;
//		
//		if(!IsClienSocket())
//		{
//			CloseClientSocket();
//			return -1;
//		}
//
//		/// Send out the data (igtl Message)
//		int ps =  msg->GetPackSize();
//		
//		//s = m_pigtlClientSocket->Send(msg->GetPackPointer(), msg->GetPackSize());
//		int length = msg->GetPackSize();
//		int total = 0; 
//		int block_size = 500;
//		int temp_block_size = 0;
//		int temp_length;
//		const char* buffer = reinterpret_cast<const char*>(msg->GetPackPointer());
//		do
//		{
//			temp_length = length-total;
//			temp_block_size = block_size < temp_length ? block_size : temp_length; 
//			s = m_pigtlClientSocket->Send(buffer+total, temp_block_size);
//
//			if(s<1)
//				return 0;
//			total += temp_block_size;
//		}while(total < length);
//	
//		if(s<=0)
//			m_bAlive= false;
//
//		ts = GetMsgTimeStamp(msg);
//		std::string msg2;
//
//		if( msg.IsNotNull())
//			msg2 = "IGTL";//tempMsg->GetDeviceType();
//		else
//			msg2 = "NULL Data";
//
//		TCPPostProcessing(0, m_tcp_status, this, NULL, &ts, &msg2);
//		
//		return s;
//	}

}