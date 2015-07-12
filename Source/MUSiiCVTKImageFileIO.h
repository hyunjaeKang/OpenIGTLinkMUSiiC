/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/
#ifndef __MUSIIC_IGTL_MSG_FILE_IO_
#define __MUSIIC_IGTL_MSG_FILE_IO_


#include "MUSiiCFileIOAbstract.h"
#include "MUSiiCUtil.h"
#include <igtlMessageBase.h>
#include <igtlImageMessage.h>

#include <iostream>
#include <fstream>

namespace igtl
{

class IGTLMCommon_EXPORT MUSiiCigtlMsgFILEIO : public MUSiiCFileIOAbstract<igtl::MessageBase::Pointer>
{

public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCigtlMsgFILEIO									Self;
	typedef MUSiiCFileIOAbstract<igtl::MessageBase::Pointer>	Superclass;
	typedef SmartPointer<Self>									Pointer;
	typedef SmartPointer<const Self>							ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	/// Constructor
	MUSiiCigtlMsgFILEIO();
	
	/// Deconstructor
	~MUSiiCigtlMsgFILEIO();

	///virtual function
	/////////////////////////////////////////////////////////////////////////////////
	//////Reading File
	virtual igtl::MessageBase::Pointer ReadSingleFile(std::string name, bool crccheck = true);
	virtual igtl::MessageBase::Pointer ReadSingleFileRecoverMode(std::string name);
	igtl::ImageMessage::Pointer ReadSingImage(std::string name);
	igtl::MessageBase::Pointer RecoverImageMessage(igtl::MessageBase::Pointer msg);

	///////////////////////////////////////////////////////////////////////////////////
	/// Write Single file with Callback function
	virtual int WriteSingleFile(igtl::MessageBase::Pointer data, std::string name);

	int WriteSingleImageMessage(igtl::MessageBase::Pointer data, std::string name);

	template<class P, class M>
	inline igtl::MessageBase::Pointer ReadSingleMessage(std::ifstream& is, bool crccheck = true)
	{
		int c;
		//// get the body of igtl Message
		/// 06.Create temp igtl Message
		P temp = M::New();
		//igtl::ImageMessage::Pointer temp = igtl::ImageMessage::New();
		/// 07. Set Message_Header
		temp->SetMessageHeader(m_pigtlMsgHeader);
		/// 08. Allocate Memory for igtlMessage
		temp->AllocatePack();
		/// 09. Get the size of body
		int sb = temp->GetPackBodySize();
		/// 10. Read the body of igtlMessage
		//r = fread(temp->GetPackBodyPointer(), 1, sb, pfile);
		is.read((char*)temp->GetPackBodyPointer(), sb);
		/// 11. Close file
		is.close();
		/// 12. Unpack the Message
		if(crccheck)
		{
			c = temp->Unpack(1);
			if(c & igtl::MessageHeader::UNPACK_BODY)
			{
				printf("UnPack is OK!!\n");
				return (igtl::MessageBase::Pointer) temp;	
			}
			else
			{
				printf("UnPack is Failed!!\n");
				return NULL;
			}
		}
		else
		{
			temp->Unpack();
			return (igtl::MessageBase::Pointer) temp;	
		}
	}

	template<class P, class M>
	inline P ReadSingleMessage2(std::ifstream& is)
	{
		//// get the body of igtl Message
		/// 06.Create temp igtl Message
		P temp = M::New();
		//igtl::ImageMessage::Pointer temp = igtl::ImageMessage::New();
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
	
	template<class P, class M>
	inline int WriteSingleMessage(igtl::MessageBase::Pointer data, std::string name)
	{
		//FILE* pfile = NULL;
		/*std::ofstream outfile2("ReceivedData_WriteSingleMessage1_pre_pack.igtl", std::ofstream::binary);
		outfile2.write((char*)data->GetPackPointer(), data->GetPackSize());
		outfile2.close();*/
		igtl::TimeStamp::Pointer tsp = igtl::TimeStamp::New();
		data->GetTimeStamp(tsp);
		double ts(tsp->GetTimeStamp());
		std::string name_t = GenerateFileName(name, ts);

		/// 00. Open file with writing mode
		//pfile = fopen(name.c_str(), "w");
		std::ofstream outfile(name_t.c_str(), std::ofstream::binary);

		P temp_msg = M::New();
		temp_msg = igtl::RetrieveMessage<P,M>(data);
		/// 01. Pack the data
		temp_msg->Pack();
		/// 02. Get the size of data
		int s = temp_msg->GetPackSize();
		/// 03. Write the data on the file
		//int r = fwrite(temp_msg->GetPackPointer(), 1, s, pfile);
		outfile.write((char*)temp_msg->GetPackPointer(), temp_msg->GetPackSize());
		/// 04. Close file
//		fclose(pfile);
		outfile.close();

		return s;	
	}
	
protected: ///Operation
	//// virtual functions
	virtual void Initialize();


	/////////////////////////////////////////////////////////////////////////////////
	/// The core function of reading a single file with callback interface
	virtual int _ReadSingleFileCB(int idx, std::vector<std::string>* file_list);

	/// The core function of writing a single file with callback interface
	virtual int _WriteSingleFileCB(int idx, std::vector<igtl::MessageBase::Pointer>* datas, std::vector<std::string>* file_list);

	/// The core function of writing a data from straming data line to local hard-dish
	virtual int _WriteStreamData(std::string* name);

	double GetMsgTimeStamp(igtl::MessageBase::Pointer msg);

public:/// Attributes
	
protected:/// Attributes
	igtl::MessageHeader::Pointer	m_pigtlMsgHeader;
	igtl::TimeStamp::Pointer		m_pts; 

	

};

}

#endif
