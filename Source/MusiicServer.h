/***************************************************************************
Copyright Feb/2011
MUSiiC Laboratory
Hyun-Jae Kang, Philipp J Stolka,Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.
***************************************************************************/

#pragma once

#include "MusiicQueue.h"
#include <igtlMultiThreader.h>
#include <igtlServerSocket.h>
#include <igtlClientSocket.h>

#include <igtlUSMessage.h>
#include <igtlEIMessage.h>
#include <igtlTransformMessage.h>
#include <igtlImageMessage.h>
#include <igtlPositionMessage.h>
#include <igtlStatusMessage.h>

#include <vector>

using namespace igtl;

class MusiicServer
{
public:
	MusiicServer(void);
	~MusiicServer(void);

	/// Create Server socket with defined port
	int CreateServer(int port);

	/// Close Server socket
	int CloseServer();

	/// Get Count of each message queue
	int GetCountUSMsg()											{return m_USMsgQueue.size();}
	int GetCountEIMsg()											{return m_EIMsgQueue.size();}
	int GetCountImageMsg()										{return m_ImageMsgQueue.size();}
	int GetCountTransformMsg()									{return m_TransformMsgQueue.size();}
	int GetCountPositionMsg()									{return m_PositionMsgQueue.size();}
	int GetCountStatusMsg()										{return m_StatusMsgQueue.size();}

	// Put US Data to Network queue
	void PutUSData(USMessage::Pointer msg)						{m_USMsgQueue.push(msg);}
	// Put EI Data to Network queue
	void PutEIData(EIMessage::Pointer msg)						{m_EIMsgQueue.push(msg);}
	// Put Transformation Data to Network queue
	void PutTransformationData(TransformMessage::Pointer msg)	{m_TransformMsgQueue.push(msg);}
	// Put Position Data to Network queue
	void PutPositionData(PositionMessage::Pointer msg)			{m_PositionMsgQueue.push(msg);}
	// Put Image Data to Network queue
	void PutImageData(ImageMessage::Pointer msg)				{m_ImageMsgQueue.push(msg);}
	// Put STATUS Data to Network queue
	void PutStatusData(StatusMessage::Pointer msg)				{m_StatusMsgQueue.push(msg);}


	// Send US Data to Network 
	void SendUSData();						
	// Send EI Data to Network
	void SendEIData();						
	// Send Transformation Data to Network
	void SendTransformationData();	
	// Send Position Data to Network
	void SendPositionData();			
	// Send Image Data to Network
	void SendImageData();				
	// Send STATUS Data to Network 
	void SendStatusData();				

	// SetTimeout
	void SetTimeout(unsigned long msec)							{m_timeout = msec;}

	/// Waiting for connection of any client request
	ClientSocket::Pointer WaitForConnection()					{return m_Server->WaitForConnection(m_timeout);}


public:
	/// A list of socket
	//std::vector<Socket::Pointer>				m_sockets;
	std::vector<ClientSocket::Pointer>			m_sockets;
	/// boolean variable for a networking thread
	bool										m_bNetworkThreadTx;

protected:
	ServerSocket::Pointer						m_Server;

	unsigned long								m_timeout;

	/// A pointer of Thread
	MultiThreader::Pointer						m_Thread;

	/// An index of Network thread
	int											m_iNetworkThreadTx;


	/// Message queues
	CMusiicQueue<USMessage::Pointer>			m_USMsgQueue;
	CMusiicQueue<EIMessage::Pointer>			m_EIMsgQueue;
	CMusiicQueue<ImageMessage::Pointer>			m_ImageMsgQueue;
	CMusiicQueue<TransformMessage::Pointer>		m_TransformMsgQueue;
	CMusiicQueue<PositionMessage::Pointer>		m_PositionMsgQueue;
	CMusiicQueue<StatusMessage::Pointer>		m_StatusMsgQueue;

protected:
	void InitializeQueue();
};

