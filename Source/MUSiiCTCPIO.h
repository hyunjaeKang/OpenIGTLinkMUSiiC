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
#ifndef __MUSIIC_TCP_IO_
#define __MUSIIC_TCP_IO_


#include "MUSiiCIGTLIODevice.h"

namespace igtl
{

class IGTLMCommon_EXPORT MUSiiCTCPIO : public MUSiiCIGTLIODevice
{

public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCTCPIO							Self;
	typedef MUSiiCIGTLIODevice					Superclass;
	typedef SmartPointer<Self>					Pointer;
	typedef SmartPointer<const Self>			ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	/// Constructor
	MUSiiCTCPIO();
	
	/// Deconstructor
	~MUSiiCTCPIO();

	///////////////////////////////////////////////////////////
	/// The information of TCP_IO  
	virtual int GetTCPStatus();

	/// Set a pointer of MUSiiCTCPIO as the posinter of parents
	bool SetParentMUSiiCTCPIO(igtl::MUSiiCTCPIO::Pointer parent);

	/// Remove the posinter of parents
	bool RemoveParentMUSiiCTCPIO();
	
	//// Post processing function for TCP/IP Communication 
	/// In General, 
	/// numOfRun : When using Data-Interface, this number indicate the index of new data in Data-Interface
	/// TaskInfo : The argument of this task
	/// ptr      : the pointer of caller class
	/// data1    : Data 
	/// data2    : the Time-stamp of the data
	/// data3    : the name of Data
	virtual int TCPPostProcessing(int numOfRun, int taskInfo, void* ptr,igtl::MessageBase::Pointer data1, void* data2, void* data3);

protected: ///Operation
	virtual void Initialize();

public:/// Attributes
	

protected:/// Attributes
	
	int							m_tcp_status;
	////
	igtl::MUSiiCTCPIO::Pointer	m_pParentTCPIO;
	bool						m_bParentTCPIO;

};

}

#endif