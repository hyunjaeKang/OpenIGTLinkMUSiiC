/***************************************************************************
Copyright Feb/2011
MUSiiC Laboratory
Hyun-Jae Kang, Philipp J Stolka,Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.
***************************************************************************/
#ifndef __MUSICC_SERVERT_
#define __MUSICC_SERVERT_

#include "MusiicQueue.h"
#include <igtlMultiThreader.h>
#include <igtlServerSocket.h>
#include <igtlClientSocket.h>


#include "MUSiiCUtil.h"


#include <vector>

using namespace igtl;

template <class P> class MusiicTCPSimpleServerUni
{
public:// Methods

	//Constructor
	MusiicTCPSimpleServerUni()
	{
		m_bNetworkThreadTx	=	false;
		m_timeout			=	3;
		m_Server			=   NULL;
		m_sockets.erase(m_sockets.begin(), m_sockets.end());
	}
	
	//Deconstructor
	~MusiicTCPSimpleServerUni()
	{
		CloseServer();
	}

	/// Create Server socket with defined port
	int CreateServer(int port)
	{
		/// If there already is a server, delete the server socket
		//int ss = m_Server->GetServerPort();
		//if(ss != 0)
		//	CloseServer();
	
		/// Create a server socket with given port number
		m_Server = ServerSocket::New();
		int s = m_Server->CreateServer(port);


		if(s < 0)
			return s;
		else
		{
			///1. Create an object of Multithread
			m_Thread = MultiThreader::New();
			///2. Change the bool variable
			m_bNetworkThreadTx = true;
			///3. Start the Network Thread for receiving Data
			m_iNetworkThreadTx = m_Thread->SpawnThread((igtl::ThreadFunctionType) & NetworkThreadTx, this);
			///4. return 1 : Client is connected to a Server
			return 1;
		}
	}

	/// Close Server socket
	int CloseServer()
	{
		if(m_MsgQueue.IsWaiting())
			m_MsgQueue.EnforceRelease();
		
		/// Stop the network thread
		m_bNetworkThreadTx = false;
		m_Thread->TerminateThread(m_iNetworkThreadTx);

		/// Close Server socket
		m_Server->CloseSocket();

		/// intialize Queue
		InitializeQueue();

		/// Delete a list of clients
		m_sockets.erase(m_sockets.begin(), m_sockets.end());

		return 1;
	}

	/// Set Timeout for listening
	void SetTimeout(unsigned long msec) { m_timeout = msec;}

	/// Waiting for connection of any client request
	ClientSocket::Pointer WaitForConnection()					
	{return m_Server->WaitForConnection(m_timeout);}

	/// Send out the message to Network
	void SendMessageData()
	{
		P msg;
		m_MsgQueue.wait_get_pop(msg);

		int sz = m_sockets.size();
		int pcksz = msg->GetPackSize();
		void* ptr = msg->GetPackPointer();

		int szm = GetCountMessageData();
		////Dropping ///////////////////////
		printf("Dropping Size : %d\n", szm-1);
		for(int j=0; j<szm-1;j++)
		{
			P msg;
			//m_MsgQueue.wait_pop(msg);
			m_MsgQueue.try_pop(msg);
			msg.~SmartPointer();
		}
	    /////////////////////

		for(int i=0; i<sz; i++)
		{
			int s = m_sockets[i]->GetConnected();
			if(s)
				m_sockets[i]->Send(ptr, pcksz);
			else
				m_sockets.erase(m_sockets.begin()+i);
		}
	}

	/// Inset a Message Data to Network Queue
	void PutMessageData(P& msg) {m_MsgQueue.push(msg);}

	/// Get the count of Network Queue
	int GetCountMessageData() { return m_MsgQueue.size();}

	/// Network thread
	static void* NetworkThreadTx(void* ptr)
	{
		/// Get the pointer of CMusiicClient Class
		MultiThreader::ThreadInfo* info = static_cast<MultiThreader::ThreadInfo*>(ptr);
		MusiicTCPSimpleServerUni* pServer = static_cast<MusiicTCPSimpleServerUni*>(info->UserData);

		// Create a object of socket 
		ClientSocket::Pointer socket;

		while(pServer->m_bNetworkThreadTx)
		{
			/// ------------------------------------
			/// Waiting for Connection
			/// Waiting for multi-Client connection
			socket = pServer->WaitForConnection();
			if(socket)
				pServer->m_sockets.push_back(socket);

			if(pServer->m_sockets.size() >0)
			{
				/// if there is any Message data in the network queue
				/// Send the Message data to network
				//int sz = pServer->GetCountMessageData(); 
				//if( pServer->GetCountMessageData() >0)
				{
					pServer->SendMessageData();
				}
			}

		}

		return NULL;
	}
	
	int GetNumOfClient(){return m_sockets.size();}
	bool IsConnected() { return m_sockets.size() > 0 ? true : false;}

public:// Attributes

protected:
	void InitializeQueue() {m_MsgQueue.Clear();}
protected://Attributes
	/// A list of Clientsocket
	std::vector<ClientSocket::Pointer> m_sockets;
	/// boolean variable for a network thread
	bool					m_bNetworkThreadTx;

protected:
	ServerSocket::Pointer	m_Server;

	unsigned long			m_timeout;

	/// A pointer of Thread
	MultiThreader::Pointer	m_Thread;

	/// An index of Network thread
	int						m_iNetworkThreadTx;

	/// Message queues
	CMusiicQueue<P>			m_MsgQueue;
};

#endif