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
#ifndef __MUSIIC_BINDIGTL_MSG_FILE_IO_
#define __MUSIIC_BINDIGTL_MSG_FILE_IO_

#include "MUSiiCIGTLFileIO.h"

namespace igtl
{
class IGTLMCommon_EXPORT MUSiiCBindIGTLMsgFileIO: public MUSiiCIGTLMsgFileIO
{
public:
	/** Standard class typedefs. */
	typedef MUSiiCBindIGTLMsgFileIO	    Self;
	typedef MUSiiCIGTLMsgFileIO		    Superclass;
	typedef SmartPointer<Self>			Pointer;
	typedef SmartPointer<const Self>	ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	/// Constructor
	MUSiiCBindIGTLMsgFileIO();
	
	/// Deconstructor
	~MUSiiCBindIGTLMsgFileIO();


protected: ///Operation
	///////////////////////////////////////////////////////////////////
	/// Virtual Functions

	/// Initialize class memeber variables
	virtual void Initialize();

	
	/// Writing Single File with callbackInterface or Thread
	virtual int _WriteStreamData(int taskInfo);

	/// Writing single file for the function of WriteStreamData
	virtual int _WriteStreamData_SingleFile(igtl::MessageBase::Pointer tempMsg, bool bBindMsg = false, int BindIdx = 0);
	

protected: /// Attributes
	

};
};
#endif
