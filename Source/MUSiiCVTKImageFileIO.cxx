/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/

#include "MUSiiCigtlMsgFILEIO.h"
#include "MUSiiCUtil.h"

namespace igtl
{

	
/// Constructor
MUSiiCigtlMsgFILEIO::MUSiiCigtlMsgFILEIO()
{
	m_pNameOfClass="MUSiiCigtlMsgFILEIO";
	Initialize();	
}
	
	/// Deconstructor
MUSiiCigtlMsgFILEIO::~MUSiiCigtlMsgFILEIO()
{
}

///virtual function
/////////////////////////////////////////////////////////////////////////////////
//////Reading File

igtl::MessageBase::Pointer MUSiiCigtlMsgFILEIO::ReadSingleFileRecoverMode(std::string name)
{
	igtl::MessageBase::Pointer temp;
	temp = ReadSingleFile(name, true);
	if(temp.IsNotNull())
		return temp;
	else
	{
		temp = ReadSingleFile(name, false);

		if (strcmp(temp->GetDeviceType(), "IMAGE") == 0)
			return RecoverImageMessage(temp);
		else
			return temp;
	}
}

igtl::MessageBase::Pointer MUSiiCigtlMsgFILEIO::RecoverImageMessage(igtl::MessageBase::Pointer msg)
{
	igtl::ImageMessage::Pointer img = igtl::RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(msg);

	return (igtl::MessageBase::Pointer)DuplicateImageMessage(img);
}


igtl::MessageBase::Pointer MUSiiCigtlMsgFILEIO::ReadSingleFile(std::string name, bool crccheck)
{
	//FILE* pfile = NULL;
	/// 00.Open file with reading mode
	/*pfile = fopen(name.c_str(), "r");
		
	if(pfile == NULL)
		return NULL;*/
	int c;
	std::ifstream is;
	is.open(name.c_str(), std::ios::binary);

	is.seekg(0, std::ios::end);
	int sz = is.tellg();
	is.seekg(0, std::ios::beg);

	//// Get the general header of igtl Message
	/// 01. Create the Message Header
	m_pigtlMsgHeader = igtl::MessageHeader::New();
	/// 02. Initialize the Message Header
	m_pigtlMsgHeader->InitPack();
	/// 03. Get the size of Message Header
	int sh = m_pigtlMsgHeader->GetPackSize();
	/// 04. Read the Message Header from the file
		
		//int r = fread(m_pigtlMsgHeader->GetPackPointer(), 1, sh, pfile);
	is.read((char*)m_pigtlMsgHeader->GetPackPointer(), sh);

	/// 05. Unpack the header 
	//m_pigtlMsgHeader->Unpack();
	
	if(crccheck)
	{
		c = m_pigtlMsgHeader->Unpack(1);

		if(!(c & igtl::MessageHeader::UNPACK_HEADER))
		{
			printf("Header UnPack is FAILED!\n");
			return NULL;
		}
	}
	else
		m_pigtlMsgHeader->Unpack();
	

	if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "BIND") == 0)
	{
		return ReadSingleMessage<igtl::BindMessage::Pointer, igtl::BindMessage>(is,crccheck);
	}
	else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "COLORTABLE") == 0)
	{
		return ReadSingleMessage<igtl::ColorTableMessage::Pointer, igtl::ColorTableMessage>(is,crccheck);
	}
	else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "IMAGE") == 0)
	{
		std::string device(m_pigtlMsgHeader->GetDeviceName());
		std::string us("US");
		std::string ei("EI");
		if(device.find(us)!=std::string::npos)
		{
			return ReadSingleMessage<igtl::USMessage::Pointer, igtl::USMessage>(is,crccheck);
		}
		else if(device.find(ei)!=std::string::npos)
		{
			return ReadSingleMessage<igtl::EIMessage::Pointer, igtl::EIMessage>(is,crccheck);
		}
		else
			return ReadSingleMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(is,crccheck);
	}
	else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "IMGMETA") == 0)
	{
		return ReadSingleMessage<igtl::ImageMetaMessage::Pointer, igtl::ImageMetaMessage>(is,crccheck);
	}
	else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "LBMETA") == 0)
	{
		return ReadSingleMessage<igtl::LabelMetaMessage::Pointer, igtl::LabelMetaMessage>(is,crccheck);
	}
	else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "NDARRAY") == 0)
	{
		return ReadSingleMessage<igtl::NDArrayMessage::Pointer, igtl::NDArrayMessage>(is,crccheck);
	}
	else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "POINT") == 0)
	{
		return ReadSingleMessage<igtl::PointMessage::Pointer, igtl::PointMessage>(is,crccheck);
	}
	else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "POSITION") == 0)
	{
		return ReadSingleMessage<igtl::PositionMessage::Pointer, igtl::PositionMessage>(is,crccheck);
	}
	else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "QTDATA") == 0)
	{
		return ReadSingleMessage<igtl::QuaternionTrackingDataMessage::Pointer, igtl::QuaternionTrackingDataMessage>(is,crccheck);
	}
	else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "STATUS") == 0)
	{
		return ReadSingleMessage<igtl::StatusMessage::Pointer, igtl::StatusMessage>(is,crccheck);
	}
	else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "STRING") == 0)
	{
		return ReadSingleMessage<igtl::StringMessage::Pointer, igtl::StringMessage>(is,crccheck);
	}
	else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "QTDATA") == 0)
	{
		return ReadSingleMessage<igtl::QuaternionTrackingDataMessage::Pointer, igtl::QuaternionTrackingDataMessage>(is,crccheck);
	}
	else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "TDATA") == 0)
	{
		return ReadSingleMessage<igtl::TrackingDataMessage::Pointer, igtl::TrackingDataMessage>(is,crccheck);
	}
	else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "TRANSFORM") == 0)
	{
		return ReadSingleMessage<igtl::TransformMessage::Pointer, igtl::TransformMessage>(is,crccheck);
	}
	else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "TRAJ") == 0)
	{
		return ReadSingleMessage<igtl::TrajectoryMessage::Pointer, igtl::TrajectoryMessage>(is,crccheck);
	}
	else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "GEN") == 0)
	{
		return ReadSingleMessage<igtl::GenMessage::Pointer, igtl::GenMessage>(is,crccheck);
	}
	else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "ARGUMENTS") == 0)
	{
		return ReadSingleMessage<igtl::ArgMessage::Pointer, igtl::ArgMessage>(is,crccheck);
	}
	else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "FILE") == 0)
	{
		return ReadSingleMessage<igtl::FileMessage::Pointer, igtl::FileMessage>(is,crccheck);
	}
	else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "EIIMAGE") == 0)
    {
		return ReadSingleMessage<igtl::FixedImage::Pointer, igtl::FixedImage>(is,crccheck);
	}
	else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "EIUSIMAGE") == 0)
    {
		return ReadSingleMessage<igtl::FixedImageBMODE::Pointer, igtl::FixedImageBMODE>(is,crccheck);
	}
	else if (strcmp(m_pigtlMsgHeader->GetDeviceType(), "") == 0)
	{
		return ReadSingleMessage<igtl::MessageBase::Pointer, igtl::MessageBase>(is,crccheck);
	}
	else 
	{
		return ReadSingleMessage<igtl::MessageBase::Pointer, igtl::MessageBase>(is,crccheck);
	}
}

igtl::ImageMessage::Pointer MUSiiCigtlMsgFILEIO::ReadSingImage(std::string name)
{
	std::ifstream is;
	is.open(name.c_str(), std::ios::binary);

	is.seekg(0, std::ios::end);
	int sz = is.tellg();
	is.seekg(0, std::ios::beg);


	//// Get the general header of igtl Message
	/// 01. Create the Message Header
	m_pigtlMsgHeader = igtl::MessageHeader::New();
	/// 02. Initialize the Message Header
	m_pigtlMsgHeader->InitPack();
	/// 03. Get the size of Message Header
	int sh = m_pigtlMsgHeader->GetPackSize();
	/// 04. Read the Message Header from the file
		
		//int r = fread(m_pigtlMsgHeader->GetPackPointer(), 1, sh, pfile);
	is.read((char*)m_pigtlMsgHeader->GetPackPointer(), sh);

	/// 05. Unpack the header 
	m_pigtlMsgHeader->Unpack();

	//// get the body of igtl Message
	/// 06.Create temp igtl Message
		
	//igtl::MessageBase::Pointer temp = igtl::MessageBase::New();
	igtl::ImageMessage::Pointer temp = igtl::ImageMessage::New();
	/// 07. Set Message_Header
	temp->SetMessageHeader(m_pigtlMsgHeader);
	/// 08. Allocate Memory for igtlMessage
	temp->AllocatePack();
	/// 09. Get the size of body
	int sb = temp->GetPackBodySize();
	/// 10. Read the body of igtlMessage
	//r = fread(temp->GetPackBodyPointer(), 1, sb, pfile);
	is.read((char*)temp->GetPackBodyPointer(), sb);

	/// 11. Unpack the Message
	temp->Unpack();
	/// 12. Close file
	//fclose(pfile);
	is.close();
	
	//return (igtl::MessageBase*)temp;
	return temp;
}

///////////////////////////////////////////////////////////////////////////////////
/// Write Single file with Callback function
int MUSiiCigtlMsgFILEIO::WriteSingleFile(igtl::MessageBase::Pointer data, std::string name)
{
	if(data.IsNotNull())
	{
		if (strcmp(data->GetDeviceType(), "BIND") == 0)
		{
			return WriteSingleMessage<igtl::BindMessage::Pointer, igtl::BindMessage>(data, name);
		}
		else if (strcmp(data->GetDeviceType(), "COLORTABLE") == 0)
		{
			return WriteSingleMessage<igtl::ColorTableMessage::Pointer, igtl::ColorTableMessage>(data, name);
		}
		else if (strcmp(data->GetDeviceType(), "IMAGE") == 0)
		{
			std::string device(data->GetDeviceName());
			std::string us("US");
			std::string ei("EI");
			if(device.find(us)!=std::string::npos)
			{
				return WriteSingleMessage<igtl::USMessage::Pointer, igtl::USMessage>(data, name);
			}
			else if(device.find(ei)!=std::string::npos)
			{
				return WriteSingleMessage<igtl::EIMessage::Pointer, igtl::EIMessage>(data, name);
			}
			else
				return WriteSingleMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(data, name);
		}
		else if (strcmp(data->GetDeviceType(), "IMGMETA") == 0)
		{
			return WriteSingleMessage<igtl::ImageMetaMessage::Pointer, igtl::ImageMetaMessage>(data, name);
		}
		else if (strcmp(data->GetDeviceType(), "LBMETA") == 0)
		{
			return WriteSingleMessage<igtl::LabelMetaMessage::Pointer, igtl::LabelMetaMessage>(data, name);
		}
		else if (strcmp(data->GetDeviceType(), "NDARRAY") == 0)
		{
			return WriteSingleMessage<igtl::NDArrayMessage::Pointer, igtl::NDArrayMessage>(data, name);
		}
		else if (strcmp(data->GetDeviceType(), "POINT") == 0)
		{
			return WriteSingleMessage<igtl::PointMessage::Pointer, igtl::PointMessage>(data, name);
		}
		else if (strcmp(data->GetDeviceType(), "POSITION") == 0)
		{
			return WriteSingleMessage<igtl::PositionMessage::Pointer, igtl::PositionMessage>(data, name);
		}
		else if (strcmp(data->GetDeviceType(), "QTDATA") == 0)
		{
			return WriteSingleMessage<igtl::QuaternionTrackingDataMessage::Pointer, igtl::QuaternionTrackingDataMessage>(data, name);
		}
		else if (strcmp(data->GetDeviceType(), "STATUS") == 0)
		{
			return WriteSingleMessage<igtl::StatusMessage::Pointer, igtl::StatusMessage>(data, name);
		}
		else if (strcmp(data->GetDeviceType(), "STRING") == 0)
		{
			return WriteSingleMessage<igtl::StringMessage::Pointer, igtl::StringMessage>(data, name);
		}
		else if (strcmp(data->GetDeviceType(), "QTDATA") == 0)
		{
			return WriteSingleMessage<igtl::QuaternionTrackingDataMessage::Pointer, igtl::QuaternionTrackingDataMessage>(data, name);
		}
		else if (strcmp(data->GetDeviceType(), "TDATA") == 0)
		{
			return WriteSingleMessage<igtl::TrackingDataMessage::Pointer, igtl::TrackingDataMessage>(data, name);
		}
		else if (strcmp(data->GetDeviceType(), "TRANSFORM") == 0)
		{
			return WriteSingleMessage<igtl::TransformMessage::Pointer, igtl::TransformMessage>(data, name);
		}
		else if (strcmp(data->GetDeviceType(), "TRAJ") == 0)
		{
			return WriteSingleMessage<igtl::TrajectoryMessage::Pointer, igtl::TrajectoryMessage>(data, name);
		}
		else if (strcmp(data->GetDeviceType(), "GEN") == 0)
		{
			return WriteSingleMessage<igtl::GenMessage::Pointer, igtl::GenMessage>(data, name);
		}
		else if (strcmp(data->GetDeviceType(), "ARGUMENTS") == 0)
		{
			return WriteSingleMessage<igtl::ArgMessage::Pointer, igtl::ArgMessage>(data, name);
		}
		else if (strcmp(data->GetDeviceType(), "FILE") == 0)
		{
			return WriteSingleMessage<igtl::FileMessage::Pointer, igtl::FileMessage>(data, name);
		}
		else if (strcmp(data->GetDeviceType(), "") == 0)
		{
			return WriteSingleMessage<igtl::MessageBase::Pointer, igtl::MessageBase>(data, name);
		}
		else 
		{
			return WriteSingleMessage<igtl::MessageBase::Pointer, igtl::MessageBase>(data, name);
		}
	}
	else
		return 0;
}

int MUSiiCigtlMsgFILEIO::WriteSingleImageMessage(igtl::MessageBase::Pointer data, std::string name)
{
	FILE* pfile = NULL;
	/// 00. Open file with writing mode
	pfile = fopen(name.c_str(), "w");

	if(pfile == NULL)
		return NULL;

	igtl::ImageMessage::Pointer img2;
	img2 = igtl::RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(data);
	/// 01. Pack the data
	img2->Pack();
	/// 02. Get the size of data
	int s = img2->GetPackSize();
	/// 03. Write the data on the file
	int r = fwrite(img2->GetPackPointer(), 1, s, pfile);
	/// 04. Close file
	fclose(pfile);

	return r;
}
	
///protected: ///Operation
//// virtual functions
void MUSiiCigtlMsgFILEIO::Initialize()
{
	MUSiiCFileIOAbstract<igtl::MessageBase::Pointer>::Initialize();
	

	m_pigtlMsgHeader = NULL;
	m_pts = igtl::TimeStamp::New();
}


/////////////////////////////////////////////////////////////////////////////////
/// The core function of reading a single file with callback interface
int MUSiiCigtlMsgFILEIO::_ReadSingleFileCB(int idx, std::vector<std::string>* file_list)
{
	std::string  name = file_list->at(idx);
	
	igtl::MessageBase::Pointer msg;
	msg = ReadSingleFile(name);

	double ts = GetMsgTimeStamp(msg);
	return FileIOPostProcessing(idx, m_FileMode, this, msg, (void*)(&ts), &name);
}

/// The core function of writing a single file with callback interface
int MUSiiCigtlMsgFILEIO::_WriteSingleFileCB(int idx, std::vector<igtl::MessageBase::Pointer>* datas, std::vector<std::string>* file_list)
{
	std::string  name = file_list->at(idx);
	
	igtl::MessageBase::Pointer msg;
	msg = datas->at(idx);

	WriteSingleFile(msg, name);

	double ts = GetMsgTimeStamp(msg);
	return FileIOPostProcessing(idx, m_FileMode, this, msg, (void*)(&ts), &name);
}

/// The core function of writing a data from straming data line to local hard-dish
int MUSiiCigtlMsgFILEIO::_WriteStreamData(std::string* name)
{
	igtl::MessageBase::Pointer msg;
	//igtl::MessageBase* msg = NULL;
	//std::string* temp = name;
	//std::string temp2 = name->c_str();
	//msg = m_pDATA_IF->concurrent_wait_get_pop_back(m_bFileDrop);
	m_pDATA_IF->concurrent_wait_get_pop_front(msg);//(m_bFileDrop);
	
	if(msg.IsNotNull())
	{
		/*std::ofstream outfile("ReceivedData__WriteStreamData.igtl", std::ofstream::binary);
		outfile.write((char*)msg->GetPackPointer(), msg->GetPackSize());
		outfile.close();*/
		
		//std::string name_t = GenerateFileName(m_sFilename);
		WriteSingleFile(msg, m_sFilename);
	
		double ts = GetMsgTimeStamp(msg);
		return FileIOPostProcessing(M_THREAD_RUN_CONTINUOUS, m_FileMode, this, msg, (void*)(&ts), &name);
	}
	else
		return 0;
}

double MUSiiCigtlMsgFILEIO::GetMsgTimeStamp(igtl::MessageBase::Pointer msg)
{
	msg->GetTimeStamp(m_pts);
	//msg->GetTimeStamp(&sec,&nano);
	//if(sec == 0)
	double t = m_pts->GetTimeStamp();

	if(t <= 0.1)
	{
		m_pts->GetTime();
		double t = m_pts->GetTimeStamp();
	}

	return m_pts->GetTimeStamp();
}

}

