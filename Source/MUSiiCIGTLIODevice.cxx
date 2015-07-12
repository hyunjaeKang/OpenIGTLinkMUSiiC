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

#include "MUSiiCIGTLIODevice.h"

namespace igtl
{
	/// Constructor
	MUSiiCIGTLIODevice::MUSiiCIGTLIODevice()
	{
		igtl::MUSiiCTaskAbstract::m_pNameOfClass="MUSiiCIODevice";
		Initialize();		
	}
	
	/// Deconstructor
	MUSiiCIGTLIODevice::~MUSiiCIGTLIODevice()
	{
	}


	////////////////////////////////////////////////////////////
	/// ETC
	
	/// Get MUSiiC_IO_DeviceType
	int MUSiiCIGTLIODevice::GetIODeviceType()
	{
		return m_IODevice_Type;
	}
	
//protected: ///Operation
	/// Initialize class memeber variables
	void MUSiiCIGTLIODevice::Initialize()
	{		
		/// IO_Device Type
		m_IODevice_Type					= M_NO_DEVICE_IO;
	}

	/// Set MUSiiC_IO_DeviceType
	void MUSiiCIGTLIODevice::SetIODeviceType(int iodevice_type)
	{
		m_IODevice_Type = iodevice_type;
	}

	
} ;