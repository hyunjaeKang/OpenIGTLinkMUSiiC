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
#include "MUSiiCIGTLRS232CSimple.h"

namespace igtl
{
/// Constructor
MUSiiCIGTLRS232CSimple::MUSiiCIGTLRS232CSimple()
{
	MUSiiCTaskAbstract::m_pNameOfClass="MUSiiCIGTLMsgFileIO";
	Initialize();
}
	
/// Deconstructor
MUSiiCIGTLRS232CSimple::~MUSiiCIGTLRS232CSimple()
{
	if(m_bIsOpenComPort)
		ClosePort();
}

///Open Serial(Rs232C) Port
int MUSiiCIGTLRS232CSimple::OpenComPort(std::string port,	std::string baudrate, std::string parity, std::string databit, std::string stopbit)
{
	/// Update the informaion RS232C communication
	m_sPort			= port;
	m_sBaudrate		= baudrate;
	m_sParity		= parity;
	m_sDatabit		= databit;
	m_sStopbit		= stopbit;

	/// Create File Handle
	m_hComPort = CreateFile( m_sPort.c_str(),
							 GENERIC_READ|GENERIC_WRITE,
							 0,
							 NULL,
							 OPEN_EXISTING,
							 0, 
							 NULL);
	/// Check the file handle
	if(m_hComPort == INVALID_HANDLE_VALUE)
	{
		/// Failed to create file handle
		m_bIsOpenComPort = false;
		/// return this function with failure
		return -1;
	}

	/// Update condition value of com-port
	m_bIsOpenComPort = true;
	/// Setting Serial communication
	return ResetSerialPort(m_hComPort);
}

/// Close Serial(Rs232C) Port
int MUSiiCIGTLRS232CSimple::ClosePort()
{
	return m_bIsOpenComPort? CloseHandle(m_hComPort) : 0;
}

/// Receive
std::string MUSiiCIGTLRS232CSimple::Receive()
{
	char buf[4096];
	int  rSz;

	memset(buf, '\0', 4096);
	ReadFile(m_hComPort, buf, 4096, (LPDWORD)((void*)&rSz), NULL);

	std::string msg = buf;

	return msg;
}

/// Send Byte
int MUSiiCIGTLRS232CSimple::SendByte(char byte)
{
	int  rSz;
	WriteFile(m_hComPort, &byte, 1, (LPDWORD)((void*)&rSz), NULL);

	return rSz;
}

/// Send Buffer
int MUSiiCIGTLRS232CSimple::SendBuffer(char* buffer, int sz)
{
	int  rSz;
	WriteFile(m_hComPort, buffer, sz, (LPDWORD)((void*)&rSz), NULL);

	return rSz;
}

//protected: ///Operation
///////////////////////////////////////////////////////////////////
/// Virtual Functions

/// Initialize class memeber variables
void MUSiiCIGTLRS232CSimple::Initialize()
{
	m_hComPort			= NULL;
	m_bIsOpenComPort	= false;
	m_sPort				= "COM1";
	m_sBaudrate			= "115200";
	m_sParity			= "None";
	m_sDatabit			= "8 bit";
	m_sStopbit			= "1 bit";
}

/**
	@brief
		Reset Serial port \n
		Setting serial port with BaudRate, Parity,Daata-bit, and Stop Bit \n
	@param port is the handle of File structor (com port)
	*/
int MUSiiCIGTLRS232CSimple::ResetSerialPort(HANDLE& port)
{
	/////////////////////////////////////////////////////
	DCB				dcb;
	DWORD			DErr;
	COMMTIMEOUTS	CommTimeOuts;

	if(!m_bIsOpenComPort)
		return -1;

	memset(&dcb, 0, sizeof(dcb));
	dcb.DCBlength = sizeof(dcb);

	ClearCommError(port, &DErr, NULL);
	
	GetCommState(port, &dcb);

	dcb.fBinary = TRUE;
	dcb.fParity	= TRUE;

	if(m_sBaudrate.compare("300") == 0)
		dcb.BaudRate = CBR_300;
	else if(m_sBaudrate.compare("600") == 0)
		dcb.BaudRate = CBR_600;
	else if(m_sBaudrate.compare("1200") == 0)
		dcb.BaudRate = CBR_1200;
	else if(m_sBaudrate.compare("2400") == 0)
		dcb.BaudRate = CBR_2400;
	else if(m_sBaudrate.compare("4800") == 0)
		dcb.BaudRate = CBR_4800;
	else if(m_sBaudrate.compare("9600") == 0)
		dcb.BaudRate = CBR_9600;
	else if(m_sBaudrate.compare("14400") == 0)
		dcb.BaudRate = CBR_14400;
	else if(m_sBaudrate.compare("19200") == 0)
		dcb.BaudRate = CBR_19200;
	else if(m_sBaudrate.compare("38400") == 0)
		dcb.BaudRate = CBR_38400;
	else if(m_sBaudrate.compare("57600") == 0)
		dcb.BaudRate = CBR_57600;
	else if(m_sBaudrate.compare("115200") == 0)
		dcb.BaudRate = CBR_115200;
	else if(m_sBaudrate.compare("128000") == 0)
		dcb.BaudRate = CBR_128000;
	else if(m_sBaudrate.compare("256000") == 0)
		dcb.BaudRate = CBR_256000;
	else if(m_sBaudrate.compare("PCI_9600") == 0)
		dcb.BaudRate = 1075;
	else if(m_sBaudrate.compare("PCI_19200") == 0)
		dcb.BaudRate = 2212;
	else if(m_sBaudrate.compare("PCI_38400") == 0)
		dcb.BaudRate = 4300;
	else if(m_sBaudrate.compare("PCI_57600") == 0)
		dcb.BaudRate = 6450;
	else if(m_sBaudrate.compare("PCI_500K") == 0)
		dcb.BaudRate = 56000;
	else
	{
		CloseHandle(port);
		m_bIsOpenComPort = false;
		return -1;
	}
	
	std::transform(m_sParity.begin(), m_sParity.end(), m_sParity.begin(), tolower);
	if(m_sParity.compare("none") == 0)
		dcb.Parity = NOPARITY;
	else if(m_sParity.compare("even") == 0) 
		dcb.Parity = EVENPARITY;
	else if(m_sParity.compare("odd") == 0)
		dcb.Parity = ODDPARITY;
	else
	{
		CloseHandle(port);
		m_bIsOpenComPort = false;
		return -1;
	}

	std::transform(m_sDatabit.begin(), m_sDatabit.end(), m_sDatabit.begin(), tolower);
	if(m_sDatabit.compare("7 bit") == 0)
		dcb.ByteSize = 7;
	else if(m_sDatabit.compare("8 bit") == 0)
		dcb.ByteSize = 8;
	else
	{
		CloseHandle(port);
		m_bIsOpenComPort = false;
		return -1;
	}

	std::transform(m_sStopbit.begin(), m_sStopbit.end(), m_sStopbit.begin(), tolower);
	if(m_sStopbit.compare("1 bit") == 0)
		dcb.StopBits = ONESTOPBIT;
	else if(m_sStopbit.compare("1.5 bit") == 0)
		dcb.ByteSize = ONE5STOPBITS;
	else if(m_sStopbit.compare("2 bit") == 0)
		dcb.ByteSize = TWOSTOPBITS;
	else
	{
		CloseHandle(port);
		m_bIsOpenComPort = false;
		return -1;
	};


	/////////////////////////////////////
	dcb.fRtsControl		= RTS_CONTROL_ENABLE;
	dcb.fDtrControl		= DTR_CONTROL_ENABLE;
	dcb.fOutxDsrFlow	= FALSE;

	dcb.fOutX			= FALSE;
	dcb.fInX			= FALSE;
	dcb.XonLim			= 2048;
	dcb.XoffLim			= 1024;

	if(!SetCommState(port, &dcb))
	{
		CloseHandle(port);
		m_bIsOpenComPort = false;
		return -1;
	}
	/////////////////////////////////

	CommTimeOuts.ReadIntervalTimeout			= MAXDWORD;//10;//MAXDWORD;
	CommTimeOuts.ReadTotalTimeoutMultiplier		= 0;//200;//10;//MAXDWORD;//10;//0;
	CommTimeOuts.ReadTotalTimeoutConstant		= 0;//50;//20;//MAXDWORD;//200;//0;
	CommTimeOuts.WriteTotalTimeoutMultiplier	= 0;
	CommTimeOuts.WriteTotalTimeoutConstant		= 0;

	if(!SetCommTimeouts(port, &CommTimeOuts))
	{
		CloseHandle(port);
		m_bIsOpenComPort = false;
		return -1;
	}

	return 1;
}
	
/**
@brief Post processing function for RS232 serial communication \n
		This function is a virtual function.
@param numOfRun : When using Data-Interface, this number indicate the index of new data in Data-Interface
@param TaskInfo : The argument of this task 
@param ptr      : the pointer of caller class 
@param data1    : Data (IGTL Message)
@param data2    : the Time-stamp of the data
@param data3    : the name of Data
*/
int MUSiiCIGTLRS232CSimple::FileIOPostProcessing(int numOfRun, int taskInfo, void* ptr,igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	return this->PostTaskProcessing(numOfRun, taskInfo, ptr, data1, data2, data3); // Check point cannon96
}
/// Virtual Functions
///////////////////////////////////////////////////////////////////

};
