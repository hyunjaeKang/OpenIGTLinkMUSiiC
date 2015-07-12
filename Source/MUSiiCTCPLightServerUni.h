/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/

#ifndef __MUSIIC_TCP_LIGHTSERVER_UNI_
#define __MUSIIC_TCP_LIGHTSERVER_UNI_

#include "MUSiiCTCPClientUni.h"
#include <igtlServerSocket.h>
#include <vector>

namespace igtl
{

class IGTLMCommon_EXPORT MUSiiCTCPLightServerUni : public MUSiiCTCPIO 
{
public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCTCPLightServerUni			Self;
	typedef MUSiiCTCPIO					Superclass;
	typedef SmartPointer<Self>			Pointer;
	typedef SmartPointer<const Self>	ConstPointer;

	igtlNewMacro(MUSiiCTCPLightServerUni);  
	igtlTypeMacro(MUSiiCTCPLightServerUni, MUSiiCTCPIO);
	
	/// Constructor
	MUSiiCTCPLightServerUni();
	
	/// Deconstructor
	~MUSiiCTCPLightServerUni();
	
	/// Get the pointer of NetworkBuffer
	igtl::MUSiiCigtlMsgVector::Pointer GetNetworkBuffer();
	
	/// Creater Server Socket
	int CreateServer(int port, bool useSelfDataIF = true);

	/// (Pause Task)
	void PauseServerTask();

	/// (Resume Task)
	int ResumeServerTask();

	/// Close server socket
	int CloseServer();

	/// Set time-out for listening a request of client's connection
	void SetTimeout(unsigned long msec);

	/// Set Dropping 
	void SetDropping(bool drop=false);

	/// Set Pop 
	void SetPopping(bool pop=true);

	/// Get Num of connected-clients
	int GetNumOfClients();

	/// Check there are clients or not.
	bool IsConnectedClients();

	
	
protected: ///Operation
	virtual void Initialize();

	/// Client-Network Task function is implemented in this function.
	//virtual int Task();
	virtual int TaskFunction(int numOfRun, int taskInfo, void* ptr = NULL, void* data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	/// Send Data(igtl Message) to TCP/IP network
	int SendigtlMsg();

	/// Waiting for a request to connect from any client
	igtl::ClientSocket::Pointer WaitForConnection();

	//// Post-processing for TCP-IP communication
	int TCPServerPostProcessing(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, void* data1 = NULL, void* data2 = NULL, void* data3 = NULL);


public:/// Attributes
	
protected:/// Attributes
	
	/// a pointer of igtl ServerSocket
	igtl::ServerSocket::Pointer						m_pigtlServerSocket;

	/// a boolean variable of the pointer of igtl Server Socket
	bool											m_bigtlServerSocket;

	/// a port number of Server socket
	int												m_iPort;

	/// time-out for listening a request of client's connection
	unsigned long									m_lTimeout;

	/// the list of MSUiiCTCPClientUni's pointer
	std::vector<igtl::MUSiiCTCPClientUni::Pointer>	m_MSUiiCTCPClients;

	/// a boolean variable for dropping data 
	bool											m_bDropping;

	/// a boolean variable for pop data 
	bool											m_bPop;

	int												m_R;

	int												m_iIdex;

	//igtl::FastMutexLock::Pointer					m_pServerMutex;
	igtl::MutexLock::Pointer						m_pServerMutex;
};

}
#endif