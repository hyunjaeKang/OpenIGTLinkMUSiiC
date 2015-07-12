/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/

#ifndef __MUSIIC_TCP_CLIENT_UNI_
#define __MUSIIC_TCP_CLIENT_UNI_

#include "MUSiiCTCPIO.h"
#include <cstring>
#include <igtlClientSocket.h>
#include "MUSiiCVector.h"
#include "MUSiiCigtlMsgVector.h"
#include <iostream>
#include <fstream>

namespace igtl
{

enum MUSiiC_CLIENT_MODE
{
	M_TCP_CLIENT_NONE	= 9300,
	M_TCP_CLIENT_CLIENT,
	M_TCP_CLIENT_SERVER,
};

class IGTLMCommon_EXPORT MUSiiCTCPClientUni : public MUSiiCTCPIO 
{
public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCTCPClientUni			Self;
	typedef MUSiiCTCPIO					Superclass;
	typedef SmartPointer<Self>			Pointer;
	typedef SmartPointer<const Self>	ConstPointer;

	igtlNewMacro(MUSiiCTCPClientUni);  
	igtlTypeMacro(MUSiiCTCPClientUni, MUSiiCTCPIO);
	
	/// Constructor
	MUSiiCTCPClientUni();
	
	/// Deconstructor
	~MUSiiCTCPClientUni();

	/// Connect to Server(Host) with hostname(host-ip-address) and port
	/// (RunTask)::Start network thread
	int ConnectToHost(const char* hostname, int port, 
					int attempt =3, bool continousattemp = false, 
					bool useSelfDataIF = true);
	
	/// (Pause Task)
	void PauseClientTask();

	/// (Resume Task)
	int ResumeClientTask();
	
	/// Try to reconnect to Server(Host)
	int ReConnectToHost();
	
	/// Close client socket
	void CloseClientSocket(std::string message="");

	////////////////////////////////////////////////////////////////////////
	/// Functions for MUSiiCServerUni

	/// Set a pointer of igtl::ClientSocket for multiple clients connection
	int SetClientSocket(igtl::ClientSocket::Pointer cs, igtl::MutexLock::Pointer pNetworkLock, bool SendDropping = false, int clientindex = 0);

	/// Set a pointer of igtl::ClientSocket for multiple clients connection
	int SetClientSocket2(igtl::ClientSocket::Pointer cs, int clientindex = 0);


	MUSiiC_CLIENT_MODE GetClientMode();

	/// Check whether client socket is alive or not.
	bool IsClienSocket(); 

	//// Set the index of this client
	void SetClientIndex(int clientindex){m_iClientIndex = clientindex;}

	//// Get the index of this client
	int GetClientIndex(){return m_iClientIndex;}

	/// Get the index of this client with string message
	std::string GetClientInfoString();

	/// Set this client socket as Reference Data socket
	void SetReferenceDataSocket(bool ref){m_bReferenceDataScoket = ref;}
	
	/// Get the information of this socket whether Reference Data socket or not
	bool IsReferenceDataSocket(){return m_bReferenceDataScoket;}

	bool IsGotData(){return m_bGotData;}

	void SetGodData(bool got){m_bGotData = got;}

	void Lock(){m_pClientDataLock->Lock();}

	void Unlock(){m_pClientDataLock->Unlock();}

	/// Send Data(igtl Message) to TCP/IP network directly
	int SendigtlMsg2(igtl::MessageBase::Pointer msg= NULL);

protected: ///Operation
	virtual void Initialize();

	/// Client-Network Task function is implemented in this function.
	virtual int TaskFunction(int numOfRun, int taskInfo, void* ptr = NULL, void* data1 = NULL, void* data2 = NULL, void* data3 = NULL);
	
	/// Connect to Server(Host) with hostname(host-ip-address) and port
	int TryConnectToHost(const char* hostname, int port, int attempt);
	
	/// Receive Data(igtl Message) from TCP/IP network
	int ReceiveigtlMsg();

	/// Receive Data-Header(igtl MessageHeader) from TCP/IP network
	int ReceiveigtlMsgHeader();
	
	/// Receive Data-Body (igtl MessageBase) from TCP/IP network
	int ReceiveigtlMsgBody();
	
	/// Send Data(igtl Message) to TCP/IP network
	int SendigtlMsg(igtl::MessageBase::Pointer msg= NULL);

	/*/// Release Send-Out network buffer
	bool ReleaseNetworkBuffer();*/

	//// Post-processing for TCP-IP communication
	int TCPPostProcessing(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, void* data1 = NULL, void* data2 = NULL, void* data3 = NULL);
	
	//double GetMsgTimeStamp(igtl::MessageBase* msg);

	template<class P, class M>
	inline int ReceiveMessage()
	{
		/// To Do :: Cannon96
		/// Check IsConnected?
		/// I think this function only work beginning time.
		if(!IsClienSocket())
			return -1;
		//m_pigtlMsgHeader->Unpack();
		int rx, c;
		/// Create temp igtlMessage
		//igtl::MessageBase::Pointer tempMsg = igtl::MessageBase::New();
		P tempMsg = M::New();
		/// Set MessageHeader
		tempMsg->SetMessageHeader(m_pigtlMsgHeader);
		/// Allocate Message on Memory
		tempMsg->AllocatePack();

		/// Receive igtlMessage from TCP/IP network
		int tbd_sz =  tempMsg->GetPackBodySize();

		rx = m_pigtlClientSocket->Receive(tempMsg->GetPackBodyPointer(),tbd_sz);

		/*if(tbd_sz == rx)
		{
			printf("Same size\n");
		}
		else
		{
			printf("Different size\n");
		}*/

		if(rx <=0)
			m_bAlive = false;

		if(rx > 0)
		{
			c = tempMsg->Unpack(1);
			///check CRC of igtlMessage
			if(c & igtl::MessageHeader::UNPACK_BODY)
			{
				m_tcp_status = M_TCP_Connected_DATA;
				double ts = GetMsgTimeStamp((igtl::MessageBase::Pointer)tempMsg);
				TCPPostProcessing(0, m_tcp_status, this, tempMsg, &ts, NULL);//&msg);
			}
		}
		else
		{
			CloseClientSocket("_ReceiveigtlMsgBody");
			return -1;
		}

		return rx;

	}
public:/// Attributes
	/// a pointer of igtl ClientSocket 
	igtl::ClientSocket::Pointer			m_pigtlClientSocket;

	int									m_iSendBufferSize;
protected:/// Attributes

	/// The mode of Client class
	/// 9300 : None
	/// 9301 : Client
	/// 9302 : Server
	MUSiiC_CLIENT_MODE					m_ClientMode;

	/*/// a pointer of igtl ClientSocket 
	igtl::ClientSocket::Pointer			m_pigtlClientSocket;*/
	
	/// Host's name or IP address
	std::string							m_sHostName;
	
	/// Host's Port number
	int									m_iHostPort;

	/// the number of attempt to connect to host 
	int									m_iAttempt;

	/// the boolean variable for retrying to connect
	bool								m_bContinuousAttemp;
	
	/// a boolean variable of the pointer of igtl ClientSocket 
	bool								m_bigtlClientSocket;
	
	/// a Network buffer to send-out data to TCP/IP network
	////igtl::MUSiiCigtlMsgVector::Pointer	m_pNetworkBuffer;
	//igtl::MUSiiCigtlMsgVector::Pointer	m_pNetworkBuffer;
	///// a boolean variable of the Network buffer to send-out data to TCP/IP network
	//bool								m_bNetworkBuffer;

	/// A pointer of message_header
	igtl::MessageHeader::Pointer		m_pigtlMsgHeader;

	bool								m_bSendDropping;

	bool								m_bUseDataInterface;

	//// Variables for multi-Client
	//// the index of this client socket
	int									m_iClientIndex;
	/// the boolean variable of this client socket is a reference data socket or not
	bool								m_bReferenceDataScoket;

	bool								m_bGotData;

	bool								m_bAlive;

	igtl::MutexLock::Pointer			m_pNetworkLock;

	igtl::MutexLock::Pointer			m_pClientDataLock;
};
}
#endif
