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
#include "MUSiiCIGTLRS232C_IOCP.h"
//CMemLeakDetect gMemLeakDetect;
namespace igtl
{
	
//CMemLeakDetect gMemLeakDetect;
/// Constructor
MUSiiCIGTLRS232C_IOCP::MUSiiCIGTLRS232C_IOCP()
{
	//_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	MUSiiCTaskAbstract::m_pNameOfClass="MUSiiCIGTLMsgFileIO";
	/// Initialize
	Initialize();
	
	/*_CrtDumpMemoryLeaks();
	_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );*/
}
	
/// Deconstructor
MUSiiCIGTLRS232C_IOCP::~MUSiiCIGTLRS232C_IOCP()
{
	
	/// Stop Monitoring Thread
	if(m_bMonitoring)
	{
		m_bMonitoring = false;
		this->m_bTaskThread = false;
		PostQueuedCompletionStatus(m_hIOCP_port, 0, NULL, NULL);
		/// Stop All task thread
		this->StopTask(M_ALLTASKOBJECT);
		PostQueuedCompletionStatus(m_hIOCP_port, 0, NULL, NULL);
	}
	

	/// Release Buffer
	int sz(m_RS232CPortList.size());
	for(int i=0; i<sz; i++)
	{
		//LP_MTKRS232C_PORT_INFO rs232_port; 
		//rs232_port = m_RS232CPortList[i];
		DWORD			DErr;
		/// Initialize File handle for RS232 Communication
		ClearCommError(m_RS232CPortList[i]->hRS232Port, &DErr, NULL);
		PurgeComm(m_RS232CPortList[i]->hRS232Port, PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
		CloseHandle(m_RS232CPortList[i]->hRS232Port);
		delete m_RS232CPortList[i];
		m_RS232CPortList[i] = NULL;
	}
	m_RS232CPortList.erase(m_RS232CPortList.begin(), m_RS232CPortList.end());

	igtl::Sleep(500);

	if(m_bIOCP_port == true)
	{
		CloseHandle(m_hIOCP_port);
		m_bIOCP_port = false;
	}
}

/// Open Serial(Rs232C) Port
/// @ Input
/// port       : the name of comport for RS232 communication
/// baudrate   : the baudrate of RS232 communication
/// parity     : parity value of RS232 communication
/// databit    : data-bit of RS232 communication 
/// stopbit    : stop-bit of RS232 communication
/// bflowcheck : boolean value of checking RS232 communication flow								
/// @ Output
/// ID_rs232_port :index of the created RS232C port
int MUSiiCIGTLRS232C_IOCP::OpenComPort(std::string port,
									   std::string baudrate,
									   std::string parity,
								       std::string databit,
									   std::string stopbit, 
									   bool        bflowcheck)
{
	/// Create an instance of MTKRS232C_PORT_INFO for RS232 Communication
	MTKRS232C_PORT_INFO* rs232_port = new MTKRS232C_PORT_INFO;
	
	
	/// Create File Handle for RS232C communication
	rs232_port->hRS232Port = CreateFile(port.c_str(), 
									   GENERIC_READ|GENERIC_WRITE,
							           0,
							           NULL,
							           OPEN_EXISTING,
							           FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, 
							           NULL);

	if(rs232_port->hRS232Port == INVALID_HANDLE_VALUE)
	{
		if(m_bDebug)
			MUSiiC_LOG(logINFO) << "Failed in creating file handle";
		delete rs232_port;
		return -1;
	}

	/// save the number of port
	rs232_port->strPort = port;
	
	/// Setting RS232C Communication
	
	DWORD			DErr;
	/// Initialize File handle for RS232 Communication
	ClearCommError(rs232_port->hRS232Port, &DErr, NULL);
	SetupComm(rs232_port->hRS232Port, MTKRS232_INBUFSIZE,MTKRS232_OUTBUFSIZE);
	PurgeComm(rs232_port->hRS232Port, PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);


	/// -- Setting DCB structure of RS232 Communication
	/// Initialize dcb structure of the instance of MTKRS232C_PORT_INFO
	DCB          dcb;
	

	memset(&dcb, 0, sizeof(dcb));
	/// Setting DCB structure using input information
	dcb.DCBlength = sizeof(dcb);
	/// Getting communication state of file handle
	GetCommState(rs232_port->hRS232Port, &dcb);

	dcb.fBinary   = true;
	dcb.fParity   = true;

	/// Set the speed of RS232 Communication
	if(baudrate.compare("300") == 0)
		dcb.BaudRate = CBR_300;
	else if(baudrate.compare("600") == 0)
		dcb.BaudRate = CBR_600;
	else if(baudrate.compare("1200") == 0)
		dcb.BaudRate = CBR_1200;
	else if(baudrate.compare("2400") == 0)
		dcb.BaudRate = CBR_2400;
	else if(baudrate.compare("4800") == 0)
		dcb.BaudRate = CBR_4800;
	else if(baudrate.compare("9600") == 0)
		dcb.BaudRate = CBR_9600;
	else if(baudrate.compare("14400") == 0)
		dcb.BaudRate = CBR_14400;
	else if(baudrate.compare("19200") == 0)
		dcb.BaudRate = CBR_19200;
	else if(baudrate.compare("38400") == 0)
		dcb.BaudRate = CBR_38400;
	else if(baudrate.compare("57600") == 0)
		dcb.BaudRate = CBR_57600;
	else if(baudrate.compare("115200") == 0)
		dcb.BaudRate = CBR_115200;
	else if(baudrate.compare("128000") == 0)
		dcb.BaudRate = CBR_128000;
	else if(baudrate.compare("256000") == 0)
		dcb.BaudRate = CBR_256000;
	else if(baudrate.compare("230400") == 0)
		dcb.BaudRate = 230400;
	else if(baudrate.compare("460800") == 0)
		dcb.BaudRate = 460800;
	else if(baudrate.compare("921600") == 0)
		dcb.BaudRate = 921600;
	else if(baudrate.compare("PCI_9600") == 0)
		dcb.BaudRate = 1075;
	else if(baudrate.compare("PCI_19200") == 0)
		dcb.BaudRate = 2212;
	else if(baudrate.compare("PCI_38400") == 0)
		dcb.BaudRate = 4300;
	else if(baudrate.compare("PCI_57600") == 0)
		dcb.BaudRate = 6450;
	else if(baudrate.compare("PCI_500K") == 0)
		dcb.BaudRate = 56000;
	else
	{
		CloseHandle(rs232_port->hRS232Port);
		if(m_bDebug)
			MUSiiC_LOG(logINFO) << "Failed in setting the speed of RS232C ";
		delete rs232_port;
		return -1;
	}


	/// Set the parity of RS232 Communication
	std::transform(parity.begin(), parity.end(), parity.begin(), tolower);
	if(parity.compare("none") == 0)
		dcb.Parity = NOPARITY;
	else if(parity.compare("even") == 0) 
		dcb.Parity = EVENPARITY;
	else if(parity.compare("odd") == 0)
		dcb.Parity = ODDPARITY;
	else
	{
		CloseHandle(rs232_port->hRS232Port);
		if(m_bDebug)
			MUSiiC_LOG(logINFO) << "Failed in setting the parity of RS232C ";
		delete rs232_port;
		return -1;
	}

	/// Set the DataBit of RS232 Communication
	std::transform(databit.begin(), databit.end(), databit.begin(), tolower);
	if(databit.compare("7 bit") == 0)
		dcb.ByteSize = 7;
	else if(databit.compare("8 bit") == 0)
		dcb.ByteSize = 8;
	else
	{
		CloseHandle(rs232_port->hRS232Port);
		if(m_bDebug)
			MUSiiC_LOG(logINFO) << "Failed in setting the databit of RS232C ";
		delete rs232_port;
		return -1;
	}

	/// Set the StopBit of RS232 Communication
	std::transform(stopbit.begin(), stopbit.end(), stopbit.begin(), tolower);
	if(stopbit.compare("1 bit") == 0)
		dcb.StopBits = ONESTOPBIT;
	else if(stopbit.compare("1.5 bit") == 0)
		dcb.StopBits = ONE5STOPBITS;
	else if(stopbit.compare("2 bit") == 0)
		dcb.StopBits = TWOSTOPBITS;
	else
	{
		CloseHandle(rs232_port->hRS232Port);
		if(m_bDebug)
			MUSiiC_LOG(logINFO) << "Failed in setting the stopbit of RS232C ";
		delete rs232_port;
		return -1;
	};

	/// Set the Flow-control of RS232 Communication
	dcb.fRtsControl		    = RTS_CONTROL_ENABLE;
	dcb.fDtrControl	 	    = DTR_CONTROL_ENABLE;
	dcb.fOutxDsrFlow	    = FALSE;

	if (bflowcheck)
	{
		dcb.fOutX			= FALSE;
		dcb.fInX			= FALSE;
		dcb.XonLim			= 2048;
		dcb.XoffLim			= 1024;
	}
	else
	{
		dcb.fOutxCtsFlow     = true;
		dcb.fRtsControl      = RTS_CONTROL_HANDSHAKE;
	}

	/// Apply dcb structure to the handle of file for RS232 Communication
	if(!SetCommState(rs232_port->hRS232Port, &dcb))
	{
		CloseHandle(rs232_port->hRS232Port);
		if(m_bDebug)
			MUSiiC_LOG(logINFO) << "Failed in the fucntion of SetCommState ";
		delete rs232_port;
		return -1;
	}

	
	/// Setting parameters of timeout of RS232 Communication
	/// Check this point again : HJKang

	COMMTIMEOUTS CommTimeOuts;

	double m = 9600.00/double(dcb.BaudRate);
	double tt = (200.0*m); //// Check point
	int tmout = (int)tt;
	CommTimeOuts.ReadIntervalTimeout	     = MAXDWORD;//10;//MAXDWORD;
	CommTimeOuts.ReadTotalTimeoutMultiplier	 = 0;//200;//10;//MAXDWORD;//10;//0;
	CommTimeOuts.ReadTotalTimeoutConstant	 = tmout;//50;//20;//MAXDWORD;//200;//0;

	// CBR_9600 is approximately 1bytes/ms.
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant	 = tmout;  //check point

	if(!SetCommTimeouts(rs232_port->hRS232Port, &CommTimeOuts))
	{
		CloseHandle(rs232_port->hRS232Port);
		if(m_bDebug)
			MUSiiC_LOG(logINFO) << "Failed in the fucntion of SetCommTimeouts ";
		return -1;
	}

	/*COMMTIMEOUTS CommTimeOuts;
	GetCommTimeouts(rs232_port->hRS232Port, &CommTimeOuts);*/

	rs232_port->bAvailable = true;

	m_RS232CPortList.push_back(rs232_port);
	int ID_rs232_port(m_RS232CPortList.size() -1);

	/// Connect the created file handle and the handle of IOCP port
	if(m_bIOCP_port == true)
	{
		m_hIOCP_port = CreateIoCompletionPort(rs232_port->hRS232Port, m_hIOCP_port, (ULONG_PTR)rs232_port, 0);
	}
	else
	{
		if(m_bDebug)
			MUSiiC_LOG(logINFO) << "There is no the handle of IOCP port";
		return -1;
	}

	
	return ID_rs232_port;
}

/// GetComPort(), using an index of pre-created comport, get the instance of MTKRS232C_PORT_INFO
/// @ Input
/// index               :index of the created RS232C port
/// @ Output
/// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
LP_MTKRS232C_PORT_INFO MUSiiCIGTLRS232C_IOCP::GetComPort(int index)
{
	MTKRS232C_PORT_INFO* rs232_port;
	if(index >0 && index < m_RS232CPortList.size())
	{
		rs232_port = m_RS232CPortList[index];
	}
	return rs232_port;
}

/// int SendByte(char byte, int index =0); 
/// : Send a character to RS232 port
/// @ Input
/// byte                :character to send to RS232 port
/// index               :index of the created RS232 port
/// @ Output
/// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
int MUSiiCIGTLRS232C_IOCP::SendByte(char byte, int index)
{
	int sz(m_RS232CPortList.size());
	if( sz<1 || index<0 || index>sz-1)
		return -1;
	
	MTKRS232C_PORT_INFO* rs232_port = m_RS232CPortList[index];

	return SendByte(byte, rs232_port);
}

/// int SendByte(char byte, MTKRS232C_PORT_INFO& rs232_port);
/// : Send a character to RS232 port
/// @ Input
/// byte                :character to send to RS232 port
/// rs232_port          :instance of MTKRS232C_PORT_INFO of RS232 port
/// @ Output
/// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
int MUSiiCIGTLRS232C_IOCP::SendByte(char byte, MTKRS232C_PORT_INFO* rs232_port)
{
	int sz(m_RS232CPortList.size());
	if( sz<1 || rs232_port->bAvailable == false)
		return -1;
	
	/// Packing MTKRS232C_IO_DATA for IOCP communication
	MTKRS232C_IO_DATA* pIODATA = new MTKRS232C_IO_DATA;
	ZeroMemory(pIODATA, sizeof(MTKRS232C_IO_DATA));

	strcpy(pIODATA->buf, &byte);
	pIODATA->bRead = false;
	pIODATA->strPort = rs232_port->strPort;
	/// Send Data to RS232 port with asynchronous
	int rSz(0);
	BOOL bSucceeded = WriteFile(rs232_port->hRS232Port, &byte, 1, (LPDWORD)((void*)&rSz), (OVERLAPPED*) pIODATA);
	
	if(bSucceeded == false && GetLastError() != ERROR_IO_PENDING)
		return -1;
	else
		return rSz;
}
	
/// int SendString(char* str, int index =0);
/// : Send a string to RS232 port
/// @ Input
/// str                 :string to send to RS232 port
/// index               :index of the created RS232 port
/// @ Output
/// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
int MUSiiCIGTLRS232C_IOCP::SendString(char* str, int index)
{
	int sz(m_RS232CPortList.size());
	if( sz<1 || index<0 || index>sz-1)
		return -1;

	MTKRS232C_PORT_INFO* rs232_port = m_RS232CPortList[index];

	return SendString(str, rs232_port);
}

/// int SendString(char* str, MTKRS232C_PORT_INFO& rs232_port);
/// : Send a string to RS232 port
/// @ Input
/// str                 :string to send to RS232 port
/// rs232_port          :instance of MTKRS232C_PORT_INFO of RS232 port
/// @ Output
/// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
int MUSiiCIGTLRS232C_IOCP::SendString(char* str, MTKRS232C_PORT_INFO* rs232_port)
{
	int sz(m_RS232CPortList.size());
	if( sz<1 || rs232_port->bAvailable == false)
		return -1;

	int strsz(strlen(str));
	/// Packing MTKRS232C_IO_DATA for IOCP communication
	MTKRS232C_IO_DATA* pIODATA = new MTKRS232C_IO_DATA;
	ZeroMemory(pIODATA, sizeof(MTKRS232C_IO_DATA));
	if(strsz > 4096)
		return -1;
	//std::string msg = str;
	//strcpy(pIODATA->buf, msg.c_str());
	strcpy(pIODATA->buf, str);
	//pIODATA->buf = str;
	
	
	pIODATA->bRead = false;
	pIODATA->strPort = rs232_port->strPort;
	/// Send Data to RS232 port with asynchronous
	DWORD rSz = 0;
	BOOL bSucceeded = WriteFile(rs232_port->hRS232Port, &(pIODATA->buf), strsz, (LPDWORD)((void*)&rSz), (OVERLAPPED*) pIODATA);
	
	if(bSucceeded == false && GetLastError() != ERROR_IO_PENDING)
		return -1;
	else
		return rSz;

}

/// int SendSTLString(std::string str, int index = 0);
/// : Send a string to RS232 port
/// @ Input
/// str                 :string to send to RS232 port
/// index               :index of the created RS232 port
/// @ Output
/// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
int MUSiiCIGTLRS232C_IOCP::SendSTLString(std::string str, int index)
{
	int sz(m_RS232CPortList.size());
	if( sz<1 || index<0 || index>sz-1)
		return -1;

	MTKRS232C_PORT_INFO* rs232_port = m_RS232CPortList[index];

	return SendString((char*)str.c_str(), rs232_port);
}

/// int SendSTLString(std::string str, MTKRS232C_PORT_INFO& rs232_port);
/// : Send a string to RS232 port
/// @ Input
/// str                 :string to send to RS232 port
/// rs232_port          :instance of MTKRS232C_PORT_INFO of RS232 port
/// @ Output
/// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
int MUSiiCIGTLRS232C_IOCP::SendSTLString(std::string str, MTKRS232C_PORT_INFO* rs232_port)
{
	int sz(m_RS232CPortList.size());
	if( sz<1 || rs232_port->bAvailable == false)
		return -1;

	return SendString((char*)str.c_str(), rs232_port);
}

/// int Receive(int index);
/// : Receive a message from RS232 port
/// @ Input
/// index               :index of the created RS232 port
/// @ Output
/// 
int MUSiiCIGTLRS232C_IOCP::Receive(int index)
{
	int sz(m_RS232CPortList.size());
	if( sz<1 || index<0 || index>sz-1)
		return -1;

	MTKRS232C_PORT_INFO* rs232_port = m_RS232CPortList[index];

	return Receive(rs232_port);
}

/// int Receive(MTKRS232C_PORT_INFO& rs232_port);
/// : Receive a message from RS232 port
/// @ Input
/// rs232_port          :instance of MTKRS232C_PORT_INFO of RS232 port
/// @ Output
/// 
int MUSiiCIGTLRS232C_IOCP::Receive(MTKRS232C_PORT_INFO* rs232_port)
{
	int sz(m_RS232CPortList.size());
	if( sz<1 || rs232_port->bAvailable == false)
		return -1;

	/// Packing MTKRS232C_IO_DATA for IOCP communication
	MTKRS232C_IO_DATA* pIODATA = new MTKRS232C_IO_DATA;
	ZeroMemory(pIODATA, sizeof(MTKRS232C_IO_DATA));

	
	pIODATA->bRead = true;
	pIODATA->strPort = rs232_port->strPort;
	/// Receive Data to RS232 port with asynchronous
	DWORD rSz(0);
	BOOL bSucceeded = ReadFile(rs232_port->hRS232Port, &(pIODATA->buf), 4096, (LPDWORD)((void*)&rSz), (OVERLAPPED*) pIODATA);
	
	if(bSucceeded == false && GetLastError() != ERROR_IO_PENDING)
		return -1;
	else
		return rSz;

}

////*************************************************************
///// int SendByte(char byte, int index =0); 
///// : Send a character to RS232 port
///// @ Input
///// byte                :character to send to RS232 port
///// index               :index of the created RS232 port
///// @ Output
///// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
//int MUSiiCIGTLRS232C_IOCP::SendByte_SYNC(char byte, int index)
//{
//	int sz(m_RS232CPortList.size());
//	if( sz<1 || index<0 || index>sz-1)
//		return -1;
//	
//	MTKRS232C_PORT_INFO rs232_port = m_RS232CPortList[index];
//
//	return SendByte_SYNC(byte, rs232_port);
//}
//
///// int SendByte(char byte, MTKRS232C_PORT_INFO& rs232_port);
///// : Send a character to RS232 port
///// @ Input
///// byte                :character to send to RS232 port
///// rs232_port          :instance of MTKRS232C_PORT_INFO of RS232 port
///// @ Output
///// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
//int MUSiiCIGTLRS232C_IOCP::SendByte_SYNC(char byte, MTKRS232C_PORT_INFO& rs232_port)
//{
//	int sz(m_RS232CPortList.size());
//	if( sz<1 || rs232_port.bAvailable == false)
//		return -1;
//	
//	/// Packing MTKRS232C_IO_DATA for IOCP communication
//	MTKRS232C_IO_DATA* pIODATA = new MTKRS232C_IO_DATA;
//	ZeroMemory(pIODATA, sizeof(MTKRS232C_IO_DATA));
//
//	strcpy(pIODATA->buf, &byte);
//	pIODATA->bRead = false;
//	/// Send Data to RS232 port with asynchronous
//	int rSz(0);
//	BOOL bSucceeded = WriteFile(rs232_port.hRS232Port, &byte, 1, (LPDWORD)((void*)&rSz), (OVERLAPPED*) pIODATA);
//	
//	if(bSucceeded == false && GetLastError() != ERROR_IO_PENDING)
//		return -1;
//	else
//		return CheckIOCPQueue();
//}
//	
///// int SendString(char* str, int index =0);
///// : Send a string to RS232 port
///// @ Input
///// str                 :string to send to RS232 port
///// index               :index of the created RS232 port
///// @ Output
///// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
//int MUSiiCIGTLRS232C_IOCP::SendString_SYNC(char* str, int index)
//{
//	int sz(m_RS232CPortList.size());
//	if( sz<1 || index<0 || index>sz-1)
//		return -1;
//
//	MTKRS232C_PORT_INFO rs232_port = m_RS232CPortList[index];
//
//	return SendString_SYNC(str, rs232_port);
//}
//
///// int SendString(char* str, MTKRS232C_PORT_INFO& rs232_port);
///// : Send a string to RS232 port
///// @ Input
///// str                 :string to send to RS232 port
///// rs232_port          :instance of MTKRS232C_PORT_INFO of RS232 port
///// @ Output
///// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
//int MUSiiCIGTLRS232C_IOCP::SendString_SYNC(char* str, MTKRS232C_PORT_INFO& rs232_port)
//{
//	int sz(m_RS232CPortList.size());
//	if( sz<1 || rs232_port.bAvailable == false)
//		return -1;
//
//	int strsz(strlen(str));
//	/// Packing MTKRS232C_IO_DATA for IOCP communication
//	MTKRS232C_IO_DATA* pIODATA = new MTKRS232C_IO_DATA;
//	ZeroMemory(pIODATA, sizeof(MTKRS232C_IO_DATA));
//	if(strsz > 4096)
//		return -1;
//
//	strcpy(pIODATA->buf, str);
//	pIODATA->bRead = false;
//	/// Send Data to RS232 port with asynchronous
//	int rSz(0);
//	//BOOL bSucceeded = WriteFile(rs232_port.hRS232Port, str, strsz, (LPDWORD)((void*)&rSz), (OVERLAPPED*) pIODATA);
//	BOOL bSucceeded = WriteFile(rs232_port.hRS232Port, str, strsz, (LPDWORD)((void*)&rSz), NULL);
//	
//	if(bSucceeded == false && GetLastError() != ERROR_IO_PENDING)
//		return -1;
//	else
//		return CheckIOCPQueue();
//
//}
//
///// int SendSTLString(std::string str, int index = 0);
///// : Send a string to RS232 port
///// @ Input
///// str                 :string to send to RS232 port
///// index               :index of the created RS232 port
///// @ Output
///// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
//int MUSiiCIGTLRS232C_IOCP::SendSTLString_SYNC(std::string str, int index)
//{
//	int sz(m_RS232CPortList.size());
//	if( sz<1 || index<0 || index>sz-1)
//		return -1;
//
//	MTKRS232C_PORT_INFO rs232_port = m_RS232CPortList[index];
//
//	return SendString_SYNC((char*)str.c_str(), rs232_port);
//}
//
///// int SendSTLString(std::string str, MTKRS232C_PORT_INFO& rs232_port);
///// : Send a string to RS232 port
///// @ Input
///// str                 :string to send to RS232 port
///// rs232_port          :instance of MTKRS232C_PORT_INFO of RS232 port
///// @ Output
///// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
//int MUSiiCIGTLRS232C_IOCP::SendSTLString_SYNC(std::string str, MTKRS232C_PORT_INFO& rs232_port)
//{
//	int sz(m_RS232CPortList.size());
//	if( sz<1 || rs232_port.bAvailable == false)
//		return -1;
//
//	return SendString_SYNC((char*)str.c_str(), rs232_port);
//}
//
///// int Receive(int index);
///// : Receive a message from RS232 port
///// @ Input
///// index               :index of the created RS232 port
///// @ Output
///// 
//int MUSiiCIGTLRS232C_IOCP::Receive_SYNC(int index)
//{
//	int sz(m_RS232CPortList.size());
//	if( sz<1 || index<0 || index>sz-1)
//		return -1;
//
//	MTKRS232C_PORT_INFO rs232_port = m_RS232CPortList[index];
//
//	return Receive_SYNC(rs232_port);
//}
//
///// int Receive(MTKRS232C_PORT_INFO& rs232_port);
///// : Receive a message from RS232 port
///// @ Input
///// rs232_port          :instance of MTKRS232C_PORT_INFO of RS232 port
///// @ Output
///// 
//int MUSiiCIGTLRS232C_IOCP::Receive_SYNC(MTKRS232C_PORT_INFO& rs232_port)
//{
//	int sz(m_RS232CPortList.size());
//	if( sz<1 || rs232_port.bAvailable == false)
//		return -1;
//
//	/// Packing MTKRS232C_IO_DATA for IOCP communication
//	MTKRS232C_IO_DATA* pIODATA = new MTKRS232C_IO_DATA;
//	ZeroMemory(pIODATA, sizeof(MTKRS232C_IO_DATA));
//	//char buff[4096];
//	memset(pIODATA->buf, '\0', 4096);
//	//memset(buff, '\0', 4096);
//	
//	pIODATA->bRead = true;
//	/// Receive Data to RS232 port with asynchronous
//	int rSz(0);
//	BOOL bSucceeded = ReadFile(rs232_port.hRS232Port, pIODATA->buf, 4096, (LPDWORD)((void*)&rSz), (OVERLAPPED*) pIODATA);
//	//BOOL bSucceeded = ReadFile(rs232_port.hRS232Port, buff, 4096, (LPDWORD)((void*)&rSz), NULL);
//	
//	if(bSucceeded == false && GetLastError() != ERROR_IO_PENDING)
//		return -1;
//	else
//		return CheckIOCPQueue();
//
//}

int MUSiiCIGTLRS232C_IOCP::StartMonitoring()
{
	m_bMonitoring = true;
	this->Receive();
	int r = this->RunTask(M_THREAD_RUN_CONTINUOUS, 0, this, NULL, NULL, NULL, M_ALLTASKOBJECT);
	

	return r;
}
///////////////////////////////////////////////////////////////////
///protected: ///Operation
///////////////////////////////////////////////////////////////////

void MUSiiCIGTLRS232C_IOCP::Initialize()
{
	/// Create and Initialize the list of RS232 ports
	/*m_pRS232CPortList = igtl::MUSiiCVector<LP_MTKRS232C_PORT_INFO>::New();
	m_pRS232CPortList->concurrent_clear();*/
	m_RS232CPortList.clear();
	
	/// Create an object of IOCP-port
	m_hIOCP_port = INVALID_HANDLE_VALUE;
	m_bIOCP_port = false;
	
	m_hIOCP_port = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if(m_hIOCP_port == NULL)
	{
		if(m_bDebug)
			MUSiiC_LOG(logINFO) << "Failed in creating IOCP port";
	}
	else
		m_bIOCP_port = true;
	
}

//// Task Function for RS232 Communication with IOCP
/// In General, 
/// numOfRun : When using Data-Interface, this number indicate the index of new data in Data-Interface
/// TaskInfo : The argument of this task
/// ptr      : the pointer of caller class
/// data1    : Data 
/// data2    : the Time-stamp of the data
/// data3    : the name of Data
int MUSiiCIGTLRS232C_IOCP::TaskFunction(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	while(m_bMonitoring)
	{
		//std::cout<< "Task function" << std::endl;
		CheckIOCPQueue();             
	}

 	m_bMonitoring = false;
	
	if(m_bDebug)
	{
		MUSiiC_LOG(logINFO) << "RS232 Monitoring is finished";
		std::cout<< "Local Task function is finished" << std::endl;
	}
	return -1;
}

int MUSiiCIGTLRS232C_IOCP::CheckIOCPQueue()
{
	LP_MTKRS232C_PORT_INFO rs232_port;
	LP_MTKRS232C_IO_DATA   rs232_io;
	DWORD                  dwTransfer;
	BOOL                   ret;
	int                    rCallback(0);

	ret = GetQueuedCompletionStatus(m_hIOCP_port, &dwTransfer, 
									(PULONG_PTR)&rs232_port,//(LPDWORD)&client,, //64bit
									(LPOVERLAPPED*)&rs232_io, INFINITE);


	if(m_bMonitoring == false)
	{
		PostQueuedCompletionStatus(m_hIOCP_port, 0, NULL, NULL);
		return -1;
	}

	if(ret == FALSE || rs232_io == NULL)
	{
		if(m_bDebug)
			MUSiiC_LOG(logINFO) << "NULL Data is comming";
		//delete rs232_io;
		rs232_io = NULL;
		return -1;//CheckIOCPQueue();
	}
	else
	{
		int sz(strlen(rs232_io->buf));
		if(rs232_io->bRead)
		{
			
			
			
			////std::cout << "Input Buffer size : " << sz << std::endl;
			if(sz > 0)
				rCallback = this->PostTaskProcessing(M_POST_CONTROL_PRAR_DATA, M_RS232C_RX, this, NULL, rs232_io, rs232_port); // Check point
			else
				rCallback = this->PostTaskProcessing(M_POST_CONTROL_PRAR_DATA, M_RS232C_RX_INCOMPLETE, this, NULL, rs232_io, rs232_port); // Check point
			
			//if(sz >0)
			//{
			//	if(sz>5)
			//	{
			//		//std::string msg = rs232_io->buf;
			//		std::cout << "Got Message:  " <<  rs232_io->buf << std::endl;
			//	}
			//	else
			//	{
			//		//std::string msg = rs232_io->buf;
			//		std::cout << "Got Message:  " <<  rs232_io->buf << std::endl;
			//	}

			//}
			//else
			//{
			//	//this->Receive_SYNC();
			//	//std::cout << "No Message" << std::endl;
			//}
			if(m_bDebug)
				MUSiiC_LOG(logINFO) << "Reading data from RS232 port";

			delete rs232_io;
			rs232_io = NULL;
			//PurgeComm(rs232_port->hRS232Port, PURGE_RXABORT|PURGE_RXCLEAR);
			this->Receive();
		}
		else
		{
			if(sz > 0)
				rCallback = this->PostTaskProcessing(M_POST_CONTROL_PRAR_DATA, M_RS232C_TX, this, NULL, rs232_io, rs232_port); // Check point
			else
				rCallback = this->PostTaskProcessing(M_POST_CONTROL_PRAR_DATA, M_RS232C_TX_INCOMPLETE, this, NULL, rs232_io, rs232_port); // Check point
			//std::string msg = rs232_io->buf;
		    //std::cout << "Sent Message:  " <<  rs232_io->buf << std::endl;
			if(m_bDebug)
				MUSiiC_LOG(logINFO) << "Writing data from RS232 port";
			delete rs232_io;
			rs232_io = NULL;
			//PurgeComm(rs232_port->hRS232Port, PURGE_TXABORT|PURGE_TXCLEAR);
		}
		
	}

	return dwTransfer;
}
};