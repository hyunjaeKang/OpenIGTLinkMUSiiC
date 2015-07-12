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
#include "MUSiiCBindIGTLFileIO.h"

namespace igtl
{
/// Constructor
MUSiiCBindIGTLMsgFileIO::MUSiiCBindIGTLMsgFileIO()
{
	MUSiiCIGTLMsgFileIO::m_pNameOfClass="MUSiiCBindIGTLMsgFileIO";
	Initialize();
}
	
/// Destructor
MUSiiCBindIGTLMsgFileIO::~MUSiiCBindIGTLMsgFileIO()
{
}


///////////////////////////////////////////////////////////////////
/// Virtual Functions

/// Initialize class memeber variables
void MUSiiCBindIGTLMsgFileIO::Initialize()
{
	this->m_bIGTLFileIO = true;
	m_iIGTLFileIndex    = 0;
	m_bUseIGTLFileIndex = false;
}
	
/// Writing Single File with callbackInterface or Thread
int MUSiiCBindIGTLMsgFileIO::_WriteStreamData(int taskInfo)
{
	if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "MUSiiCIGTLMsgFileIO::_WriteStreamData";

	igtl::MessageBase::Pointer tempMsg;//= igtl::MessageBase::New();
	if(m_bDebug)
		MUSiiC_LOG(logINFO) << "Waiting Data";

	if(this->m_bVPreInputDATA_IF_Set)
		this->m_pVPreInputDATA_IF_Set->Concurrent_wait_get_pop_front_fromMUSiiCVectorSet(tempMsg);


	std::vector<igtl::MessageBase::Pointer> Messages;

	Messages = igtl::CheckBindMessage(tempMsg);

	int MsgSz = Messages.size();

	if(MsgSz>1)
	{
		int r(0);
		for(int i=0; i<MsgSz; i++)
		{
			r +=  _WriteStreamData_SingleFile(Messages.at(i), true, i);
			
		}
		
		m_iIGTLFileIndex++;
		return r;
	}
	else if (MsgSz == 1) 
	{
		return _WriteStreamData_SingleFile(Messages.at(0));
	}
	else
		return 1;
}




/// Writing single file for the function of WriteStreamData
int MUSiiCBindIGTLMsgFileIO::_WriteStreamData_SingleFile(igtl::MessageBase::Pointer tempMsg, bool bBindMsg,  int BindIdx)
{
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


			if(bBindMsg)
			{
				char Bindindex [100];
				sprintf(Bindindex, "%03d", BindIdx);
				std::string BindIdx(Bindindex);

				std::string BindMessagePreFix("Bind");
				std::string deviceName(tempMsg->GetDeviceName());
				std::string H("_");

				std::string igtlFilePath = m_sFilePath + std::string(BufIGTLindex) + H + 
					                       BindMessagePreFix + H + BindIdx + H + deviceName + std::string(".igtl"); 	
				WriteSingleFile(tempMsg, igtlFilePath);
				m_iFileMode = M_WRITE_STREAM_DATA_DOING;
			}
			else
			{
				std::string igtlFilePath = m_sFilePath + std::string(BufIGTLindex) + std::string(".igtl"); 	
				WriteSingleFile(tempMsg, igtlFilePath);
				m_iFileMode = M_WRITE_STREAM_DATA_DOING;

				m_iIGTLFileIndex++;
			}
		}
		else
		{
			double timestamp(0.0);
			timestamp = GetIGTLTimeStamp2(tempMsg);

			
			if(bBindMsg)
			{
				char Bindindex [100];
				sprintf(Bindindex, "%03d", BindIdx);
				std::string BindIdx(Bindindex);

				char temptimestamp[256];
				sprintf(temptimestamp, "%f", timestamp);
				std::string TimeStampStr(temptimestamp);

				std::string BindMessagePreFix("Bind");
				std::string deviceName(tempMsg->GetDeviceName());
				std::string H("_");

				std::string igtlFilePath = m_sFilePath + TimeStampStr + H + BindMessagePreFix + H + BindIdx + H + deviceName + std::string(".igtl"); 

				WriteSingleFile(tempMsg, igtlFilePath);
				m_iFileMode = M_WRITE_STREAM_DATA_DOING;

			}
			else
			{
				WriteSingleFile(tempMsg, GenerateIGTLFilePath(m_sFilePath, timestamp));
				m_iFileMode = M_WRITE_STREAM_DATA_DOING;
			}
		}
		return FileIOPostProcessing(M_PRE_CONTROL_PRAR, m_iFileMode, this, NULL, NULL, NULL);
	}

	return 1;
}

	

/// Virtual Functions
///////////////////////////////////////////////////////////////////

};
