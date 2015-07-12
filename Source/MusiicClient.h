/***************************************************************************
Copyright Dec/2010
MUSiiC Laboratory
Philipp J Stolka, Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.
***************************************************************************/
#pragma once

#include "MusiicQueue.h"
#include <igtlMultiThreader.h>
#include <igtlClientSocket.h>

#include <igtlUSMessage.h>
#include <igtlEIMessage.h>
#include <igtlTransformMessage.h>
#include <igtlImageMessage.h>
#include <igtlPositionMessage.h>
#include <igtlStatusMessage.h>

using namespace igtl;

class MusiicClient
{
public:
	MusiicClient(void);
	~MusiicClient(void);

	/// Establis a communication with a Server
	/// Return value is 1		: Connection is successed
	/// Return value is not 1	: Connection is successed
	int ConnectToServer(const char *hostname, int port);

	
	/// Get Count of each message queue
	int GetCountUSMsg()							{return m_USMsgQueue.size();}
	int GetCountEIMsg()							{return m_EIMsgQueue.size();}
	int GetCountImageMsg()						{return m_ImageMsgQueue.size();}
	int GetCountTransformMsg()					{return m_TransformMsgQueue.size();}
	int GetCountPositionMsg()					{return m_PositionMsgQueue.size();}
	int GetCountStatusMsg()						{return m_StatusMsgQueue.size();}

	/// Check whether socket is connected or not
	int IsConnected()							{return m_Client->GetConnected();}


	/// Receive Data from the client socket
	int Receive(void *data, int size);
	/// Close the client socket
	void CloseClientSocket();							

	int ReConnectToServer(const char *hostname, int port);

	// Receive US Data Message
	int ReceiveUSData(ClientSocket::Pointer& socket, MessageHeader::Pointer& header);
	// Receive EI Data Message
	int ReceiveEIData(ClientSocket::Pointer& socket, MessageHeader::Pointer& header);
	// Receive Transformation Data Message
	int ReceiveTransform(ClientSocket::Pointer& socket, MessageHeader::Pointer& header);
	// Receive Position Data Message
	int ReceivePosition(ClientSocket::Pointer& socket, MessageHeader::Pointer& header);
	// Receive Image Data Message
	int ReceiveImage(ClientSocket::Pointer& socket, MessageHeader::Pointer& header);
	// Receive STATUS Data Message
	int ReceiveStatus(ClientSocket::Pointer& socket, MessageHeader::Pointer& header);


	// Get US Data Message
	void GetUSData(USMessage::Pointer& msg) {m_USMsgQueue.wait_pop(msg);}
	// Get EI Data Message
	void GetEIData(EIMessage::Pointer& msg) {m_EIMsgQueue.wait_pop(msg);}
	// Get Transformation Data Message
	void GetTransform(TransformMessage::Pointer& msg) {m_TransformMsgQueue.wait_pop(msg);}
	// Get Position Data Message
	void GetPosition(PositionMessage::Pointer& msg) {m_PositionMsgQueue.wait_pop(msg);}
	// Get Image Data Message
	void GetImage(ImageMessage::Pointer& msg) {m_ImageMsgQueue.wait_pop(msg);}
	// Get STATUS Data Message
	void GetStatus(StatusMessage::Pointer& msg) {m_StatusMsgQueue.wait_pop(msg);}
	

	/// Get the pointer of socket
	ClientSocket::Pointer	GetSocket()			{return m_Client;}

public:
	/// boolean variable for a networking thread
	bool										m_bNetworkThreadRx;
	
protected:
	/// Client socket
	ClientSocket::Pointer						m_Client;
	
	/// Message queues
	CMusiicQueue<USMessage::Pointer>			m_USMsgQueue;
	CMusiicQueue<EIMessage::Pointer>			m_EIMsgQueue;
	CMusiicQueue<ImageMessage::Pointer>			m_ImageMsgQueue;
	CMusiicQueue<TransformMessage::Pointer>		m_TransformMsgQueue;
	CMusiicQueue<PositionMessage::Pointer>		m_PositionMsgQueue;
	CMusiicQueue<StatusMessage::Pointer>		m_StatusMsgQueue;

	/// A pointer of Thread
	MultiThreader::Pointer						m_Thread;

	/// An index of Network thread
	int											m_iNetworkThreadRx;

protected:
	void InitializeQueues();

};

