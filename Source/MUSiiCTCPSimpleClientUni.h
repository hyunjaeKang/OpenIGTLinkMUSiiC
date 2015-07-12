/***************************************************************************
Copyright Dec/2010
MUSiiC Laboratory
Hyun-Jae Kang, Philipp J Stolka,Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.
***************************************************************************/
#ifndef __MUSICC_CLIENTT_
#define __MUSICC_CLIENTT_

#include "MusiicQueue.h"
#include <igtlMultiThreader.h>
#include <igtlClientSocket.h>

#include "MUSiiCUtil.h"

using namespace igtl;


typedef void(*MusiicCALLBACK) (void*, int);

typedef struct
{
	MusiicCALLBACK pCallbackfunction;

}pMusiicCallbackFtn;

template <class T, class P> class CMusiicClientT
{
public://Methods
	
	///Constructor
	CMusiicClientT()
	{
        m_Client                = ClientSocket::New();
		m_iNetworkThreadRx		= 0;
		m_bNetworkThreadRx		= false;
        m_bIsCallbackfunction   = false;
		m_Callbackfunction		= NULL;
	}

	///Deconstructor
	~CMusiicClientT()
	{
		CloseClientSocket();
	}

	/// Establis a communication with a Server
	/// Return value is 0		: Connection is successed
	/// Return value is not 0	: Connection is failed
	int ConnectToServer(const char *hostname, int port, int times = 5)
	{
		///Connect this socket to a Server program
		int s;
		for(int i=0; i<times; i++)
		{
			s= m_Client->ConnectToServer(hostname, port);
			if(s == 0)
				break;
		}
		/// Run Networking Thread for receiving Data (US, EI, Transformation)
		/// if Connection is successed, run the Network thread
		if( s == 0 )
		{
			///1. Create an object of Multithread
			m_Thread = MultiThreader::New();
			///2. Change the bool variable
			m_bNetworkThreadRx = true;
			///3. Start the Network Thread for receiving Data
			m_iNetworkThreadRx = m_Thread->SpawnThread((igtl::ThreadFunctionType) & NetworkThreadRx, this);
		}
		/// if Connection is failed.
		return s; 
	}
	
	/// Close the client socket
	void CloseClientSocket()
	{
		if(m_MsgQueue.IsWaiting())
			m_MsgQueue.EnforceRelease();

		/// Terminate Network Thread
		m_bNetworkThreadRx = false;
		m_Thread->TerminateThread(m_iNetworkThreadRx);

		/// Initialize Queue
		InitializeQueues();

		///Close the client socket
		m_Client->CloseSocket();
	}

	/// Reconnect to a Server Program
	int ReConnectToServer(const char *hostname, int port)
	{
		if(m_Client->GetConnected() > 0)
			CloseClientSocket();

		return ConnectToServer(hostname, port);
	}

	/// Receive Data from the client socket
	int Receive(void *data, int size) { return m_Client->Receive(data, size);}

        /// A golbal function for network thread
	static void* NetworkThreadRx(void* ptr)
	{
		/// Get the pointer of CMusiicClient Class
		MultiThreader::ThreadInfo* info = static_cast<MultiThreader::ThreadInfo*>(ptr);
		CMusiicClientT* pClient = static_cast<CMusiicClientT*>(info->UserData);

		/// Create a pointer of MessageHeader of OpenIGTLink
		MessageHeader::Pointer headerMsg = MessageHeader::New();

		while(pClient->m_bNetworkThreadRx)
		{
			/// Initialize receive buffer
			headerMsg->InitPack();

			/// Receive a header message of OpenIGTLink
			int rx = pClient->Receive(headerMsg->GetPackPointer(), headerMsg->GetPackSize());
		
			if( rx == 0 )
			{
				/// Stop the network thread
				pClient->m_bNetworkThreadRx = false;
				/// Close the socket
				pClient->CloseClientSocket();
			}

			/// Receive next package from network.
			if( rx != headerMsg->GetPackSize())
				continue;

			/// Unpacking of header message of OpenIGTLink
			headerMsg->Unpack();

			/// Receive Message
            ClientSocket::Pointer socket = pClient->GetSocket();
            pClient->ReceiveMessage(socket, headerMsg);
		}

		return NULL;
	}

        /// Receive <T> Message
        int ReceiveMessage(ClientSocket::Pointer& socket, MessageHeader::Pointer& header)
        {
                /// Create a message buffer to receive <T> Message data
                P msg;
                msg = T::New();
                /// Setting message header
                msg->SetMessageHeader(header);
                /// Allocate Message Pack
                msg->AllocatePack();
                /// Receive Data
                socket->Receive(msg->GetPackBodyPointer(), msg->GetPackBodySize());

                /// Deserialize the <T> Message data
                /// If you want to skip CRC check, call Unpack() without any argument.
                int c = msg->Unpack(1);

                /// if CRC check is OK
                if(c & igtl::MessageHeader::UNPACK_BODY)
                {
                        m_MsgQueue.push(msg);

                        ///Awake another application program.
                        if(m_bIsCallbackfunction)
                                m_Callbackfunction(this, 1);

                        return 1;
                }

                return 0;
        }

	/// Get <T> Data Message
	void GetMessageData(P& msg) { m_MsgQueue.wait_get_pop(msg);}

	/// Get a count of <T> Data Message
	int GetCountMessageData() {return m_MsgQueue.size();}

	ClientSocket::Pointer GetSocket() {return m_Client;}

	void SetCallbackfunction(MusiicCALLBACK cbFunc)
	{
		m_Callbackfunction		= cbFunc;
		m_bIsCallbackfunction	= true;
	}

public://Attributes
	/// boolean variable for a networking thread
	bool					m_bNetworkThreadRx;
	/// Callbackfunction
	MusiicCALLBACK			m_Callbackfunction;
	bool					m_bIsCallbackfunction;
protected://Methods

	/// Empty the message queue
	void InitializeQueues() { m_MsgQueue.Clear();}
	
protected://Attributes
	/// A pointer of Client Scoket
	ClientSocket::Pointer	m_Client;
	/// A pointer of Thread
	MultiThreader::Pointer	m_Thread;
	/// An index of Network thread
	int						m_iNetworkThreadRx;

	/// Message(Data) queue
	CMusiicQueue<P>			m_MsgQueue;
};
#endif
