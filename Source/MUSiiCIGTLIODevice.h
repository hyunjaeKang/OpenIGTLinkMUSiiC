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
#ifndef __MUSIIC_DEVICE_IO_
#define __MUSIIC_DEVICE_IO_

#include "MUSiiCIGTLTask.h"

namespace igtl
{

class IGTLMCommon_EXPORT MUSiiCIGTLIODevice: public MUSiiCIGTLTask
{
public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCIGTLIODevice					Self;
	typedef MUSiiCIGTLTask						Superclass;
	typedef SmartPointer<Self>					Pointer;
	typedef SmartPointer<const Self>			ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	/// Constructor
	MUSiiCIGTLIODevice();
	
	/// Deconstructor
	~MUSiiCIGTLIODevice();
	

	////////////////////////////////////////////////////////////
	/// ETC
	
	/// Get MUSiiC_IO_DeviceType
	int GetIODeviceType();
	
	

protected: ///Operation
	/// Initialize class memeber variables
	virtual void Initialize();

	/// Set MUSiiC_IO_DeviceType
	void SetIODeviceType(int iodevice_type);

	
	
public:/// Attributes
	

protected:/// Attributes

	
	/// The object that represents a type of IO_DEVICE
	int								m_IODevice_Type;
};
}
#endif
