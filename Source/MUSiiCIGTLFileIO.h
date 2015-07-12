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
#ifndef __MUSIIC_IGTL_MSG_FILE_IO_
#define __MUSIIC_IGTL_MSG_FILE_IO_

#include "MUSiiCFileIOAbstract.h"

namespace igtl
{
class IGTLMCommon_EXPORT MUSiiCIGTLMsgFileIO: public MUSiiCFileIOAbstract<igtl::MessageBase::Pointer>
{
public:
	/** Standard class typedefs. */
	typedef MUSiiCIGTLMsgFileIO			Self;
	typedef MUSiiCFileIOAbstract		Superclass;
	typedef SmartPointer<Self>			Pointer;
	typedef SmartPointer<const Self>	ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	/// Constructor
	MUSiiCIGTLMsgFileIO();
	
	/// Deconstructor
	~MUSiiCIGTLMsgFileIO();

	/// Virtual Function
	/// Read IGTLMsgHeader and IGTLMsgBody
	virtual int ReadIGTLHeader(std::string filepath, igtl::MessageHeader::Pointer pOutHeader, igtl::MessageBase::Pointer pOutIGTLBody);
	/// Reading a Single file
	virtual igtl::MessageBase::Pointer ReadSingleFile(std::string filepath);

	/// Virtual Function
	virtual int WriteSingleFile(igtl::MessageBase::Pointer filedata, std::string filepath);

	/// Reading a specific message
	/// 01. Reading Single BindMessage
	virtual igtl::BindMessage::Pointer ReadSingleBindMessage(std::string filepath);

	/// 02. Reading Single ColorTableMessage
	virtual igtl::ColorTableMessage::Pointer ReadSingleColorTableMessage(std::string filepath);
	
	/// 03.Reading Single USMessage
	virtual igtl::USMessage::Pointer ReadSingleUSMessage(std::string filepath);

	/// 04.Reading Single ImageMessage
	virtual igtl::ImageMessage::Pointer ReadSingleImageMessage(std::string filepath, bool bCRC = true);

	/// 05.Reading Single EIMessage
	virtual igtl::EIMessage::Pointer ReadSingleEIMessage(std::string filepath);

	/// 06.Reading Single ImageMetaMessage
	virtual igtl::ImageMetaMessage::Pointer ReadSingleImageMetaMessage(std::string filepath);

	/// 07.Reading Single LabelMetaMessage
	virtual igtl::LabelMetaMessage::Pointer ReadSingleLabelMetaMessage(std::string filepath);

	/// 08.Reading Single NDArrayMessage
	virtual igtl::NDArrayMessage::Pointer ReadSingleNDArrayMessage(std::string filepath);
	
	/// 09.Reading Single PointMessage
	virtual igtl::PointMessage::Pointer ReadSinglePointMessage(std::string filepath);
	
	/// 10.Reading Single PositionMessage
	virtual igtl::PositionMessage::Pointer ReadSinglePositionMessage(std::string filepath);

	/// 11.Reading Single QuaternionTrackingDataMessage
	virtual igtl::QuaternionTrackingDataMessage::Pointer ReadSingleQuaternionTrackingDataMessage(std::string filepath);

	/// 12.Reading Single StatusMessage
	virtual igtl::StatusMessage::Pointer ReadSingleStatusMessagee(std::string filepath);

	/// 13.Reading Single StringMessage
	virtual igtl::StringMessage::Pointer ReadSingleStringMessage(std::string filepath);

	/// 14.Reading Single TrackingDataMessage
	virtual igtl::TrackingDataMessage::Pointer ReadSingleTrackingDataMessage(std::string filepath);

	/// 15.Reading Single TransformMessage
	virtual igtl::TransformMessage::Pointer ReadSingleTransformMessage(std::string filepath);

	/// 16.Reading Single TrajectoryMessage
	virtual igtl::TrajectoryMessage::Pointer ReadSingleTrajectoryMessage(std::string filepath);
	
	/// 17.Reading Single GenMessage
	virtual igtl::GenMessage::Pointer ReadSingleGenMessage(std::string filepath);

	/// 18.Reading Single ArgMessage
	virtual igtl::ArgMessage::Pointer ReadSingleArgMessage(std::string filepath);

	/// 19.Reading Single FileMessage
	virtual igtl::FileMessage::Pointer ReadSingleFileMessage(std::string filepath);

	/// 20.Reading Single FixedImage(EIIMAGE)
	virtual igtl::FixedImage::Pointer ReadSingleFixedImage(std::string filepath);

	/// 21.Reading Single FixedImage(EIUSIMAGE)
	virtual igtl::FixedImageBMODE::Pointer ReadSingleFixedImageBMODE(std::string filepath);

	template<class P, class M>
	inline P ReadSpecificSingleMessage(std::string filepath, bool bCRC = true)
	{
		igtl::MessageHeader::Pointer pIGTLHeader = igtl::MessageHeader::New();
		igtl::MessageBase::Pointer pIGTLBody     = igtl::MessageBase::New();
		if (ReadIGTLHeader(filepath, pIGTLHeader, pIGTLBody) >0 )
		{
			return RetrieveSpecificMessagefromIODevice<P, M>(pIGTLHeader, pIGTLBody, bCRC);
		}
		else
			return NULL;
	}


	///
	bool SetUseIGTLFileIndex(bool bUseIGTLFileIndex = true);

	

protected: ///Operation
	///////////////////////////////////////////////////////////////////
	/// Virtual Functions

	/// Initialize class memeber variables
	virtual void Initialize();

	//// Convert an IGTL Message (igtl::MessageBase::Pointer) to FileData structure
	virtual igtl::MessageBase::Pointer ConvertToFileData(igtl::MessageBase::Pointer msg);

	//// Convert an FileData structure to IGTL Message (igtl::MessageBase::Pointer) 
	virtual igtl::MessageBase::Pointer ConvertToIGTLMsg(igtl::MessageBase::Pointer data);
	
	/// Reading Single File with callbackInterface or Thread
	virtual int _ReadFilesCB(int taskInfo);
	
	/// Writing Single File with callbackInterface or Thread
	virtual int _WriteFilesCB(int taskInfo);
	
	/// Writing Single File with callbackInterface or Thread
	virtual int _WriteStreamData(int taskInfo);
	
	//// Post processing function for File IO
	/// In General, 
	/// numOfRun : When using Data-Interface, this number indicate the index of new data in Data-Interface
	/// TaskInfo : The argument of this task
	/// ptr      : the pointer of caller class
	/// data1    : Data 
	/// data2    : the Time-stamp of the data
	/// data3    : the name of Data
	virtual int FileIOPostProcessing(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL,igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);
	/// Virtual Functions
	///////////////////////////////////////////////////////////////////

protected: /// Attributes
	int  m_iIGTLFileIndex;
	bool m_bUseIGTLFileIndex;


};
};
#endif
