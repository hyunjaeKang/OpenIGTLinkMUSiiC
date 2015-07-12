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
#include "MUSiiCIGTLFileIO.h"

namespace igtl
{
/// Constructor
MUSiiCIGTLMsgFileIO::MUSiiCIGTLMsgFileIO()
{
	MUSiiCTaskAbstract::m_pNameOfClass="MUSiiCIGTLMsgFileIO";
	Initialize();
}
	
/// Deconstructor
MUSiiCIGTLMsgFileIO::~MUSiiCIGTLMsgFileIO()
{

}

/// Virtual Function
int MUSiiCIGTLMsgFileIO::ReadIGTLHeader(std::string filepath, igtl::MessageHeader::Pointer pOutIGTLHeader, igtl::MessageBase::Pointer pOutIGTLBody)
{
	std::ifstream is;
	is.open(filepath.c_str(), std::ios::binary);

	///////////////////////////////////////////
	is.seekg(0, std::ios::end);
	int file_sz(is.tellg());
	is.seekg(0, std::ios::beg);
	///////////////////////////////////////////
	/// 01. Create the Message Header
	//pOutIGTLHeader = igtl::MessageHeader::New();
	/// 02. Initialize the Message Header
	pOutIGTLHeader->InitPack();
	/// 03. Read the Message Header from the pOutHeader
	is.read((char*)pOutIGTLHeader->GetPackPointer(), pOutIGTLHeader->GetPackSize());
	/// 04. Unpack the header
	pOutIGTLHeader->Unpack();
	/// 05. Create the MessageBase
	//pOutIGTLBody = igtl::MessageBase::New();
	/// 06. Set IGTLHeader on IGTLMessage
	pOutIGTLBody->SetMessageHeader(pOutIGTLHeader);
	/// 07. Allocate memory of IGTMessage
	pOutIGTLBody->AllocatePack();
	/// 08. Read the body of IGTLMessage
	is.read((char*)pOutIGTLBody->GetPackBodyPointer(), pOutIGTLBody->GetPackBodySize());
	/// 09. Close File
	is.close();
	if(pOutIGTLHeader.IsNotNull() && pOutIGTLBody.IsNotNull())
		return 1;
	else
		return 0;
}

/// Reading a Single file
igtl::MessageBase::Pointer MUSiiCIGTLMsgFileIO::ReadSingleFile(std::string filepath)
{
	std::ifstream is;
	is.open(filepath.c_str(), std::ios::binary);

	///////////////////////////////////////////
	is.seekg(0, std::ios::end);
	int file_sz(is.tellg());
	is.seekg(0, std::ios::beg);
	///////////////////////////////////////////
	/// 01. Create the Message Header
	igtl::MessageHeader::Pointer pIGTLMsgHeader = igtl::MessageHeader::New();
	/// 02. Initialize the Message Header
	pIGTLMsgHeader->InitPack();
	/// 03. Read the Message Header from the file
	is.read((char*)pIGTLMsgHeader->GetPackPointer(), pIGTLMsgHeader->GetPackSize());
	/// 04. Unpack the header
	pIGTLMsgHeader->Unpack();
	/// 05. Create the MessageBase
	igtl::MessageBase::Pointer pIGTLMsg = igtl::MessageBase::New();
	/// 06. Set IGTLHeader on IGTLMessage
	pIGTLMsg->SetMessageHeader(pIGTLMsgHeader);
	/// 07. Allocate memory of IGTMessage
	pIGTLMsg->AllocatePack();
	/// 08. Read the body of IGTLMessage
	is.read((char*)pIGTLMsg->GetPackBodyPointer(), pIGTLMsg->GetPackBodySize());
	/// 09. Close File
	is.close();
	/// 10. Retrieve IGTL Message
	igtl::MessageBase::Pointer msg = RetriveMessageBase(pIGTLMsgHeader, pIGTLMsg);
	/// 11. return IGTL Message
	return msg;
}

/// 01. Reading Single BindMessage
igtl::BindMessage::Pointer MUSiiCIGTLMsgFileIO::ReadSingleBindMessage(std::string filepath)
{
	return ReadSpecificSingleMessage<igtl::BindMessage::Pointer, igtl::BindMessage>(filepath);
}

	/// 02. Reading Single ColorTableMessage
igtl::ColorTableMessage::Pointer MUSiiCIGTLMsgFileIO::ReadSingleColorTableMessage(std::string filepath)
{
	return ReadSpecificSingleMessage<igtl::ColorTableMessage::Pointer, igtl::ColorTableMessage>(filepath);
}


//igtl::USMessage::Pointer MUSiiCIGTLMsgFileIO::ReadSingleUSMessage(std::string filepath)
//{
//	std::ifstream is;
//	is.open(filepath.c_str(), std::ios::binary);
//
//	///////////////////////////////////////////
//	is.seekg(0, std::ios::end);
//	int file_sz(is.tellg());
//	is.seekg(0, std::ios::beg);
//	///////////////////////////////////////////
//	/// 01. Create the Message Header
//	igtl::MessageHeader::Pointer pIGTLMsgHeader = igtl::MessageHeader::New();
//	/// 02. Initialize the Message Header
//	pIGTLMsgHeader->InitPack();
//	/// 03. Read the Message Header from the file
//	is.read((char*)pIGTLMsgHeader->GetPackPointer(), pIGTLMsgHeader->GetPackSize());
//	/// 04. Unpack the header
//	pIGTLMsgHeader->Unpack();
//	/// 05. Create the MessageBase
//	igtl::MessageBase::Pointer pIGTLMsg = igtl::MessageBase::New();
//	/// 06. Set IGTLHeader on IGTLMessage
//	pIGTLMsg->SetMessageHeader(pIGTLMsgHeader);
//	/// 07. Allocate memory of IGTMessage
//	pIGTLMsg->AllocatePack();
//	/// 08. Read the body of IGTLMessage
//	is.read((char*)pIGTLMsg->GetPackBodyPointer(), pIGTLMsg->GetPackBodySize());
//	/// 09. Close File
//	is.close();
//	std::string device(pIGTLMsgHeader->GetDeviceName());
//	std::string us("US");
//	std::string rf("RF");
//	if((device.find(us)!=std::string::npos) || (device.find(rf)!=std::string::npos))
//	{
//		//return RetrieveMessagefromIODevice<igtl::USMessage::Pointer, igtl::USMessage>(header,msg);
//		igtl::USMessage::Pointer temp_us = igtl::USMessage::New();
//		temp_us->SetMessageHeader(pIGTLMsgHeader);
//		temp_us->AllocatePack();
//		int sz1 = pIGTLMsg->GetPackBodySize();
//		int sz2 = temp_us->GetPackBodySize();
//		memcpy(temp_us->GetPackBodyPointer(),pIGTLMsg->GetPackBodyPointer(), temp_us->GetPackBodySize());
//		int c = temp_us->Unpack(1);
//		if( c & igtl::MessageHeader::UNPACK_BODY) 
//		{
//			int v(temp_us->GetUSDataType());
//			if (v <2)
//			{
//				igtl::USMessage::Pointer temp_us2 = igtl::ConvertUSMsg1ToUSMsg2(temp_us);
//				return temp_us2;
//			}
//			else
//				return temp_us;
//		}
//		else 
//			return  NULL;
//	}
//	else 
//		return NULL;
//	/// 10. Retrieve IGTL Message
//	/*igtl::MessageBase::Pointer msg = RetriveMessageBase(pIGTLMsgHeader, pIGTLMsg);
//	/// 11. return IGTL Message
//	return msg;*/
//}
/// 03.Reading Single USMessage
igtl::USMessage::Pointer MUSiiCIGTLMsgFileIO::ReadSingleUSMessage(std::string filepath)
{
	igtl::MessageHeader::Pointer pIGTLMsgHeader = igtl::MessageHeader::New();
	igtl::MessageBase::Pointer pIGTLMsgBody = igtl::MessageBase::New();
	
	if (ReadIGTLHeader(filepath, pIGTLMsgHeader, pIGTLMsgBody) >0 )
	{
		std::string device(pIGTLMsgHeader->GetDeviceName());
		if (ReadIGTLHeader(filepath, pIGTLMsgHeader, pIGTLMsgBody) >0 )
		{
			std::string device(pIGTLMsgHeader->GetDeviceName());
			std::string us("US");
			std::string rf("RF");
			if((device.find(us)!=std::string::npos) || (device.find(rf)!=std::string::npos))
			{
				//return RetrieveMessagefromIODevice<igtl::USMessage::Pointer, igtl::USMessage>(header,msg);
				igtl::USMessage::Pointer temp_us = igtl::USMessage::New();
				temp_us->SetMessageHeader(pIGTLMsgHeader);
				temp_us->AllocatePack();
				int sz1 = pIGTLMsgBody->GetPackBodySize();
				int sz2 = temp_us->GetPackBodySize();
				memcpy(temp_us->GetPackBodyPointer(),pIGTLMsgBody->GetPackBodyPointer(), temp_us->GetPackBodySize());
				int c = temp_us->Unpack(1);
				if( c & igtl::MessageHeader::UNPACK_BODY) 
				{
					int v(temp_us->GetUSDataType());
					if (v <2)
					{
						igtl::USMessage::Pointer temp_us2 = igtl::ConvertUSMsg1ToUSMsg2(temp_us);
						return temp_us2;
					}
					else
						return temp_us;
				}
				else 
					return  NULL;
			}
			else 
				return NULL;
		}
		else
			return NULL;
	}
	else
		return NULL;
}

/// 04.Reading Single ImageMessage
igtl::ImageMessage::Pointer MUSiiCIGTLMsgFileIO::ReadSingleImageMessage(std::string filepath, bool bCRC)
{
	return ReadSpecificSingleMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(filepath, bCRC);
}

/// 05.Reading Single EIMessage
igtl::EIMessage::Pointer MUSiiCIGTLMsgFileIO::ReadSingleEIMessage(std::string filepath)
{
	return ReadSpecificSingleMessage<igtl::EIMessage::Pointer, igtl::EIMessage>(filepath);
}

/// 06.Reading Single ImageMetaMessage
igtl::ImageMetaMessage::Pointer MUSiiCIGTLMsgFileIO::ReadSingleImageMetaMessage(std::string filepath)
{
	return ReadSpecificSingleMessage<igtl::ImageMetaMessage::Pointer, igtl::ImageMetaMessage>(filepath);
}

/// 07.Reading Single LabelMetaMessage
igtl::LabelMetaMessage::Pointer MUSiiCIGTLMsgFileIO::ReadSingleLabelMetaMessage(std::string filepath)
{
	return ReadSpecificSingleMessage<igtl::LabelMetaMessage::Pointer, igtl::LabelMetaMessage>(filepath);
}

/// 08.Reading Single NDArrayMessage
igtl::NDArrayMessage::Pointer MUSiiCIGTLMsgFileIO::ReadSingleNDArrayMessage(std::string filepath)
{
	return ReadSpecificSingleMessage<igtl::NDArrayMessage::Pointer, igtl::NDArrayMessage>(filepath);
}
	
/// 09.Reading Single PointMessage
igtl::PointMessage::Pointer MUSiiCIGTLMsgFileIO::ReadSinglePointMessage(std::string filepath)
{
	return ReadSpecificSingleMessage<igtl::PointMessage::Pointer, igtl::PointMessage>(filepath);
}
	
/// 10.Reading Single PositionMessage
igtl::PositionMessage::Pointer MUSiiCIGTLMsgFileIO::ReadSinglePositionMessage(std::string filepath)
{
	return ReadSpecificSingleMessage<igtl::PositionMessage::Pointer, igtl::PositionMessage>(filepath);
}

/// 11.Reading Single QuaternionTrackingDataMessage
igtl::QuaternionTrackingDataMessage::Pointer MUSiiCIGTLMsgFileIO::ReadSingleQuaternionTrackingDataMessage(std::string filepath)
{
	return ReadSpecificSingleMessage<igtl::QuaternionTrackingDataMessage::Pointer, igtl::QuaternionTrackingDataMessage>(filepath);
}

/// 12.Reading Single StatusMessage
igtl::StatusMessage::Pointer MUSiiCIGTLMsgFileIO::ReadSingleStatusMessagee(std::string filepath)
{
	return ReadSpecificSingleMessage<igtl::StatusMessage::Pointer, igtl::StatusMessage>(filepath);
}

/// 13.Reading Single StringMessage
igtl::StringMessage::Pointer MUSiiCIGTLMsgFileIO::ReadSingleStringMessage(std::string filepath)
{
	return ReadSpecificSingleMessage<igtl::StringMessage::Pointer, igtl::StringMessage>(filepath);
}

/// 14.Reading Single TrackingDataMessage
igtl::TrackingDataMessage::Pointer MUSiiCIGTLMsgFileIO::ReadSingleTrackingDataMessage(std::string filepath)
{
	return ReadSpecificSingleMessage<igtl::TrackingDataMessage::Pointer, igtl::TrackingDataMessage>(filepath);
}

/// 15.Reading Single TransformMessage
igtl::TransformMessage::Pointer MUSiiCIGTLMsgFileIO::ReadSingleTransformMessage(std::string filepath)
{
	return ReadSpecificSingleMessage<igtl::TransformMessage::Pointer, igtl::TransformMessage>(filepath);
}

/// 16.Reading Single TrajectoryMessage
igtl::TrajectoryMessage::Pointer MUSiiCIGTLMsgFileIO::ReadSingleTrajectoryMessage(std::string filepath)
{
	return ReadSpecificSingleMessage<igtl::TrajectoryMessage::Pointer, igtl::TrajectoryMessage>(filepath);
}
	
/// 17.Reading Single GenMessage
igtl::GenMessage::Pointer MUSiiCIGTLMsgFileIO::ReadSingleGenMessage(std::string filepath)
{
	return ReadSpecificSingleMessage<igtl::GenMessage::Pointer, igtl::GenMessage>(filepath);
}

/// 18.Reading Single ArgMessage
igtl::ArgMessage::Pointer MUSiiCIGTLMsgFileIO::ReadSingleArgMessage(std::string filepath)
{
	return ReadSpecificSingleMessage<igtl::ArgMessage::Pointer, igtl::ArgMessage>(filepath);
}

/// 19.Reading Single FileMessage
igtl::FileMessage::Pointer MUSiiCIGTLMsgFileIO::ReadSingleFileMessage(std::string filepath)
{
	return ReadSpecificSingleMessage<igtl::FileMessage::Pointer, igtl::FileMessage>(filepath);
}


/// 20.Reading Single FixedImage(EIIMAGE)
igtl::FixedImage::Pointer MUSiiCIGTLMsgFileIO::ReadSingleFixedImage(std::string filepath)
{
	return ReadSpecificSingleMessage<igtl::FixedImage::Pointer, igtl::FixedImage>(filepath);
}

/// 21.Reading Single FixedImage(EIUSIMAGE)
igtl::FixedImageBMODE::Pointer MUSiiCIGTLMsgFileIO::ReadSingleFixedImageBMODE(std::string filepath)
{
	return ReadSpecificSingleMessage<igtl::FixedImageBMODE::Pointer, igtl::FixedImageBMODE>(filepath);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Virtual Function
int MUSiiCIGTLMsgFileIO::WriteSingleFile(igtl::MessageBase::Pointer filedata, std::string filepath)
{
	/// 00. Open file with writing mode
	std::ofstream outfile(filepath.c_str(), std::ofstream::binary);
	/// 01. Pack the data
	filedata->Pack();
	/// 02. Get the size of data
	int s = filedata->GetPackSize();
	/// 03. Write the data on the file
	outfile.write((char*)filedata->GetPackPointer(), filedata->GetPackSize());
	/// 04. Close file
	outfile.close();

	return s;
}

bool MUSiiCIGTLMsgFileIO::SetUseIGTLFileIndex(bool bUseIGTLFileIndex)
{
	this->m_bUseIGTLFileIndex = true;
	this->m_iIGTLFileIndex    = 0;

	return this->m_bUseIGTLFileIndex;
}
//protected: ///Operation
///////////////////////////////////////////////////////////////////
/// Virtual Functions

/// Initialize class memeber variables
void MUSiiCIGTLMsgFileIO::Initialize()
{
	this->m_bIGTLFileIO = true;
	m_iIGTLFileIndex    = 0;
	m_bUseIGTLFileIndex = false;
}

//// Convert an IGTL Message (igtl::MessageBase::Pointer) to FileData structure
igtl::MessageBase::Pointer MUSiiCIGTLMsgFileIO::ConvertToFileData(igtl::MessageBase::Pointer msg)
{
	return msg;
}

//// Convert an FileData structure to IGTL Message (igtl::MessageBase::Pointer) 
igtl::MessageBase::Pointer MUSiiCIGTLMsgFileIO::ConvertToIGTLMsg(igtl::MessageBase::Pointer data)
{
	return data;
}
	
/// Reading Single File with callbackInterface or Thread
int MUSiiCIGTLMsgFileIO::_ReadFilesCB(int taskInfo)
{
	if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "MUSiiCIGTLMsgFileIO::_ReadFilesCB";

	m_iFileMode = ++taskInfo;
	int sz(m_vFileNameList.size());
	int szr(0);
	for(int i=0; i<sz; i++)
	{
		igtl::MessageBase::Pointer msg = ReadSingleFile(m_vFileNameList[i]);
		if(msg.IsNull())
			continue;
		
		szr++;
		FileIOPostProcessing(M_POST_CONTROL_PRAR_DATA, taskInfo, this, msg, NULL, NULL);
	}
	m_iFileMode = ++taskInfo;
	FileIOPostProcessing(M_POST_CONTROL_PRAR, taskInfo, this, NULL, NULL, NULL);
	return szr;
}
	
/// Writing Single File with callbackInterface or Thread
int MUSiiCIGTLMsgFileIO::_WriteFilesCB(int taskInfo)
{
	if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "MUSiiCIGTLMsgFileIO::_WriteFilesCB";

	m_iFileMode = ++taskInfo;
	int sz(m_vFileNameList.size());
	int szr(0);
	for(int i=0; i<sz; i++)
	{
		szr += WriteSingleFile(m_pVInputFileData->concurrent_try_GetData(i),m_vFileNameList[i]); 
		FileIOPostProcessing(M_PRE_CONTROL_PRAR, taskInfo, this, NULL, NULL, NULL);
	}
	m_iFileMode = ++taskInfo;
	FileIOPostProcessing(M_PRE_CONTROL_PRAR, taskInfo, this, NULL, NULL, NULL);
	return szr;
}
	
/// Writing Single File with callbackInterface or Thread
int MUSiiCIGTLMsgFileIO::_WriteStreamData(int taskInfo)
{
	if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "MUSiiCIGTLMsgFileIO::_WriteStreamData";

	igtl::MessageBase::Pointer tempMsg;//= igtl::MessageBase::New();
	if(m_bDebug)
		MUSiiC_LOG(logINFO) << "Waiting Data";

	if(this->m_bVPreInputDATA_IF_Set)
		this->m_pVPreInputDATA_IF_Set->Concurrent_wait_get_pop_front_fromMUSiiCVectorSet(tempMsg);

	if(tempMsg.IsNotNull())
	{
		if(m_bDebug)
			MUSiiC_LOG(logINFO) << "Got Data";

		if (m_bUseIGTLFileIndex)
		{
			char BufIGTLindex [100];
			if(m_iIGTLFileIndex > 999)
			{
				int KK  = m_iIGTLFileIndex/1000;
				int KK_ = m_iIGTLFileIndex/1000;
				sprintf(BufIGTLindex, "%dK%03d", KK, KK_);
			}
			else
			{
				sprintf(BufIGTLindex, "%03d", m_iIGTLFileIndex);
			}


			std::string igtlFilePath = m_sFilePath + std::string(BufIGTLindex) + std::string(".igtl"); 	
			WriteSingleFile(tempMsg, igtlFilePath);
			m_iFileMode = M_WRITE_STREAM_DATA_DOING;

			m_iIGTLFileIndex++;
		}
		else
		{
			double timestamp(0.0);
			timestamp = GetIGTLTimeStamp2(tempMsg);

			WriteSingleFile(tempMsg, GenerateIGTLFilePath(m_sFilePath, timestamp));
			m_iFileMode = M_WRITE_STREAM_DATA_DOING;
		}
		return FileIOPostProcessing(M_PRE_CONTROL_PRAR, m_iFileMode, this, NULL, NULL, NULL);
	}
	return 1;
}
	
//// Post processing function for File IO
/// In General, 
/// numOfRun : When using Data-Interface, this number indicate the index of new data in Data-Interface
/// TaskInfo : The argument of this task
/// ptr      : the pointer of caller class
/// data1    : Data 
/// data2    : the Time-stamp of the data
/// data3    : the name of Data
int MUSiiCIGTLMsgFileIO::FileIOPostProcessing(int numOfRun, int taskInfo, void* ptr,igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	return this->PostTaskProcessing(numOfRun, taskInfo, ptr, data1, data2, data3); // Check point cannon96
}
/// Virtual Functions
///////////////////////////////////////////////////////////////////

};
