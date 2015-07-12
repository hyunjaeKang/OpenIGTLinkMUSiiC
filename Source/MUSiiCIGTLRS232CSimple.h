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
#ifndef __MUSIIC_IGTL_RS232C_SIMPLE_
#define __MUSIIC_IGTL_RS232C_SIMPLE_

#include "MUSiiCIGTLIODevice.h"
/*!
 *  \brief This class is about RS232C communication.\n
 *
 *  The communication method that is implemeneted in this class is based on blocked method.\n
 *   
 */


#if defined(WIN32) || defined (_WIN32) || defined (__WIN32__)
#include <Windows.h>
#else

#endif

namespace igtl
{

class IGTLMCommon_EXPORT MUSiiCIGTLRS232CSimple: public igtl::MUSiiCIGTLIODevice
{
public:
	/** Standard class typedefs. */
	typedef MUSiiCIGTLRS232CSimple		Self;
	typedef MUSiiCIGTLIODevice			Superclass;
	typedef SmartPointer<Self>			Pointer;
	typedef SmartPointer<const Self>	ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	/// Constructor
	MUSiiCIGTLRS232CSimple();
	
	/// Deconstructor
	~MUSiiCIGTLRS232CSimple();

	///Open Serial(Rs232C) Port
	int OpenComPort(std::string port		="COM1",///< the name of comport for RS232 communication
					std::string baudrate	="115200",///< the baudrate of RS232 communication
					std::string parity		="None",///< parity value of RS232 communication
					std::string databit		="8 bit",///< data-bit of RS232 communication
					std::string stopbit		="1 bit"///< stop-bit of RS232 communication
					);

	/// Close Serial(Rs232C) Port
	int ClosePort();

	/// Receive
	std::string Receive();

	/// Send Byte
	int SendByte(char byte);

	/// Send Buffer
	int SendBuffer(char* buffer, int sz);
protected: ///< protected Operation
	///////////////////////////////////////////////////////////////////
	/// Virtual Functions

	/// Initialize class memeber variables
	virtual void Initialize();

	/**
	@brief
		Reset Serial port \n
		Setting serial port with BaudRate, Parity,Daata-bit, and Stop Bit \n
	@param port is the handle of File structor (com port)
	*/
	int ResetSerialPort(HANDLE& port);

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
	virtual int FileIOPostProcessing(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL,igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);
	/// Virtual Functions
	///////////////////////////////////////////////////////////////////

protected: ///< protected attributes
	HANDLE	m_hComPort;
	bool	m_bIsOpenComPort;

	std::string m_sPort;		///< the name of comport for RS232 communication
	std::string m_sBaudrate;	///< the baudrate of RS232 communication
	std::string m_sParity;		///< parity value of RS232 communication
	std::string m_sDatabit;		///< data-bit of RS232 communication
	std::string m_sStopbit;		///< stop-bit of RS232 communication

};
};
#endif
