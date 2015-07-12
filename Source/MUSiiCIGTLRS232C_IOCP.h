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
#ifndef __MUSIIC_IGTL_RS232C_
#define __MUSIIC_IGTL_RS232C_
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
#include "MUSiiCIGTLIODevice.h"



namespace igtl
{

/// Structure of RS232 port for IOCP
typedef struct
{
	HANDLE       hRS232Port;
	bool         bAvailable;
    std::string  strPort;

}MTKRS232C_PORT_INFO, *LP_MTKRS232C_PORT_INFO;

/// Structure of RS232 IO Data for IOCP
typedef struct
{
	OVERLAPPED Overlapped;	
	char		buf[4096];
	bool        bRead;

	std::string strPort;

}MTKRS232C_IO_DATA, *LP_MTKRS232C_IO_DATA;

#define MTKRS232_MAXBUFSIZE 5000  /// Max    buffer size of RS232 Communication
#define MTKRS232_INBUFSIZE  5000  /// Input  buffer size of RS232 Communication
#define MTKRS232_OUTBUFSIZE 5000  /// Output buffer size of RS232 Communication

class IGTLMCommon_EXPORT MUSiiCIGTLRS232C_IOCP: public igtl::MUSiiCIGTLIODevice
{
public:
	/** Standard class typedefs. */
	typedef MUSiiCIGTLRS232C_IOCP			Self;
	typedef MUSiiCIGTLIODevice				Superclass;
	typedef SmartPointer<Self>				Pointer;
	typedef SmartPointer<const Self>		ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	/// Constructor
	MUSiiCIGTLRS232C_IOCP();
	
	/// Deconstructor
	~MUSiiCIGTLRS232C_IOCP();


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
	int OpenComPort(std::string port		="COM1",///< the name of comport for RS232 communication
					std::string baudrate	="115200",///< the baudrate of RS232 communication
					std::string parity		="None",///< parity value of RS232 communication
					std::string databit		="8 bit",///< data-bit of RS232 communication
					std::string stopbit		="1 bit",///< stop-bit of RS232 communication
					bool        bflowcheck  = true
					);

	/// GetComPort(), using an index of pre-created comport, get the instance of MTKRS232C_PORT_INFO
	/// @ Input
    /// index               :index of the created RS232C port
	/// @ Output
	/// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
	LP_MTKRS232C_PORT_INFO GetComPort(int index);


	/// int SendByte(char byte, int index =0); 
	/// : Send a character to RS232 port
	/// @ Input
	/// byte                :character to send to RS232 port
    /// index               :index of the created RS232 port
	/// @ Output
	/// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
	int SendByte(char byte, int index =0);

	/// int SendByte(char byte, MTKRS232C_PORT_INFO& rs232_port);
	/// : Send a character to RS232 port
	/// @ Input
	/// byte                :character to send to RS232 port
    /// rs232_port          :instance of MTKRS232C_PORT_INFO of RS232 port
	/// @ Output
	/// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
	int SendByte(char byte, MTKRS232C_PORT_INFO* rs232_port);
	
	/// int SendString(char* str, int index =0);
	/// : Send a string to RS232 port
	/// @ Input
	/// str                 :string to send to RS232 port
    /// index               :index of the created RS232 port
	/// @ Output
	/// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
	int SendString(char* str, int index =0);

	/// int SendString(char* str, MTKRS232C_PORT_INFO& rs232_port);
	/// : Send a string to RS232 port
	/// @ Input
	/// str                 :string to send to RS232 port
    /// rs232_port          :instance of MTKRS232C_PORT_INFO of RS232 port
	/// @ Output
	/// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
	int SendString(char* str, MTKRS232C_PORT_INFO* rs232_port);

	/// int SendSTLString(std::string str, int index = 0);
	/// : Send a string to RS232 port
	/// @ Input
	/// str                 :string to send to RS232 port
    /// index               :index of the created RS232 port
	/// @ Output
	/// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
	int SendSTLString(std::string str, int index = 0);

	/// int SendSTLString(std::string str, MTKRS232C_PORT_INFO& rs232_port);
	/// : Send a string to RS232 port
	/// @ Input
	/// str                 :string to send to RS232 port
    /// rs232_port          :instance of MTKRS232C_PORT_INFO of RS232 port
	/// @ Output
	/// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
	int SendSTLString(std::string str, MTKRS232C_PORT_INFO* rs232_port);

	/// int Receive(int index);
	/// : Receive a message from RS232 port
	/// @ Input
    /// index               :index of the created RS232 port
	/// @ Output
	/// 
	int Receive(int index = 0);

	/// int Receive(MTKRS232C_PORT_INFO& rs232_port);
	/// : Receive a message from RS232 port
	/// @ Input
    /// rs232_port          :instance of MTKRS232C_PORT_INFO of RS232 port
	/// @ Output
	/// 
	int Receive(MTKRS232C_PORT_INFO* rs232_port);

	//*************************************************
	///*/// int SendByte(char byte, int index =0); 
	///// : Send a character to RS232 port
	///// @ Input
	///// byte                :character to send to RS232 port
 //   /// index               :index of the created RS232 port
	///// @ Output
	///// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
	//int SendByte_SYNC(char byte, int index =0);

	///// int SendByte(char byte, MTKRS232C_PORT_INFO& rs232_port);
	///// : Send a character to RS232 port
	///// @ Input
	///// byte                :character to send to RS232 port
 //   /// rs232_port          :instance of MTKRS232C_PORT_INFO of RS232 port
	///// @ Output
	///// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
	//int SendByte_SYNC(char byte, MTKRS232C_PORT_INFO& rs232_port);
	//
	///// int SendString(char* str, int index =0);
	///// : Send a string to RS232 port
	///// @ Input
	///// str                 :string to send to RS232 port
 //   /// index               :index of the created RS232 port
	///// @ Output
	///// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
	//int SendString_SYNC(char* str, int index =0);

	///// int SendString(char* str, MTKRS232C_PORT_INFO& rs232_port);
	///// : Send a string to RS232 port
	///// @ Input
	///// str                 :string to send to RS232 port
 //   /// rs232_port          :instance of MTKRS232C_PORT_INFO of RS232 port
	///// @ Output
	///// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
	//int SendString_SYNC(char* str, MTKRS232C_PORT_INFO& rs232_port);

	///// int SendSTLString(std::string str, int index = 0);
	///// : Send a string to RS232 port
	///// @ Input
	///// str                 :string to send to RS232 port
 //   /// index               :index of the created RS232 port
	///// @ Output
	///// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
	//int SendSTLString_SYNC(std::string str, int index = 0);

	///// int SendSTLString(std::string str, MTKRS232C_PORT_INFO& rs232_port);
	///// : Send a string to RS232 port
	///// @ Input
	///// str                 :string to send to RS232 port
 //   /// rs232_port          :instance of MTKRS232C_PORT_INFO of RS232 port
	///// @ Output
	///// MTKRS232C_PORT_INFO :the instance of MTKRS232C_PORT_INFO
	//int SendSTLString_SYNC(std::string str, MTKRS232C_PORT_INFO& rs232_port);

	///// int Receive(int index);
	///// : Receive a message from RS232 port
	///// @ Input
 //   /// index               :index of the created RS232 port
	///// @ Output
	///// 
	//int Receive_SYNC(int index = 0);

	///// int Receive(MTKRS232C_PORT_INFO& rs232_port);
	///// : Receive a message from RS232 port
	///// @ Input
 //   /// rs232_port          :instance of MTKRS232C_PORT_INFO of RS232 port
	///// @ Output
	///// 
	//int Receive_SYNC(MTKRS232C_PORT_INFO& rs232_port);*/

	//////////////////////////////////////////////////
	int StartMonitoring();
protected: ///Operation
	///////////////////////////////////////////////////////////////////
	/// Virtual Functions

	/// Initialize class memeber variables
	virtual void Initialize();

	
	//// Post processing function for File IO
	/// In General, 
	/// numOfRun : When using Data-Interface, this number indicate the index of new data in Data-Interface
	/// TaskInfo : The argument of this task
	/// ptr      : the pointer of caller class
	/// data1    : Data 
	/// data2    : the Time-stamp of the data
	/// data3    : the name of Data
	/*virtual int FileIOPostProcessing(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL,igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);*/

	//// Task Function for RS232 Communication with IOCP
	/// In General, 
	/// numOfRun : When using Data-Interface, this number indicate the index of new data in Data-Interface
	/// TaskInfo : The argument of this task
	/// ptr      : the pointer of caller class
	/// data1    : Data 
	/// data2    : the Time-stamp of the data
	/// data3    : the name of Data
	virtual int TaskFunction(int numOfRun, int taskInfo, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);
	
	int CheckIOCPQueue();

	

public: ///Attributes
	/// The list of RS232C port
	std::vector<LP_MTKRS232C_PORT_INFO> m_RS232CPortList;
protected: /// Attributes
	
	/// Handle of IOCP-port
	HANDLE m_hIOCP_port;

	/// boolean value of IOCP-port
	bool   m_bIOCP_port;

	bool   m_bMonitoring;

};
};
#endif
