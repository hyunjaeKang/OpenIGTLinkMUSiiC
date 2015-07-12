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

#include "MUSiiCSyncDATA.h"

namespace igtl
{
///MUSiiCSyncDataElements
/// public  operations
MUSiiCSyncDataElements::MUSiiCSyncDataElements()
{
	this->Initialize();
}
/// Deconstructor
MUSiiCSyncDataElements::~MUSiiCSyncDataElements()
{
}
////Get the number of elements
int MUSiiCSyncDataElements::GetSize()
{ 
	return m_SyncDataElements.size();
}

//// Get the iterator of begin of this Data structure
std::map<double, igtl::MessageBase::Pointer>::iterator MUSiiCSyncDataElements::GetBeginIT() 
{
	return m_SyncDataElements.begin();
}

//// Get the iterator of end of this Data structure
std::map<double, igtl::MessageBase::Pointer>::iterator MUSiiCSyncDataElements::GetEndIT() 
{
	return m_SyncDataElements.end();
}

//// Get SyncDataElements
std::map<double, igtl::MessageBase::Pointer>& MUSiiCSyncDataElements::GetDataElements() 
{
	return m_SyncDataElements;
}

/// Add IGTL Message
int MUSiiCSyncDataElements::AddIGTLMsg(igtl::MessageBase::Pointer msg, double  refTS)
{
	if(msg.IsNotNull())
	{
		if(IsTrackingDataMessage(msg))
		{
			std::cout << "tracking" << std::endl; //tracking

		}
		m_SyncDataElements[abs(refTS - GetIGTLTimeStamp(msg))] = msg;
		return m_SyncDataElements.size();
	}
	return 0;
}

//// Add MUSiiCSyncDataElement 
int MUSiiCSyncDataElements::AddMUSiiCSyncDataElement(igtl::MUSiiCSyncDataElements& elements, double refTS)
{
	if(elements.GetSize()>0)
	{
		int r(0);
		/*for(m_ItSyncDataElements = elements.GetBeginIT(); m_ItSyncDataElements != elements.GetEndIT() ; m_ItSyncDataElements++)
			m_SyncDataElements[abs(refTS - m_ItSyncDataElements->first)] = m_ItSyncDataElements->second;*/
		for(m_ItSyncDataElements = elements.GetBeginIT(); m_ItSyncDataElements != elements.GetEndIT() ; m_ItSyncDataElements++)
		{
			double dTimeDiff = abs(refTS - m_ItSyncDataElements->first);
			if(dTimeDiff < 200000.0)
			{
				m_SyncDataElements[dTimeDiff] = m_ItSyncDataElements->second;
				r++;
			}
			else
			{
				std::cout << "Out of Time" << std::endl;

			}
		}
			
		return r;
		//return elements.GetSize();
	}
	return 0;
}

//// Print MUSiiCSyncDataElements
int MUSiiCSyncDataElements::PrintMUSiiCSyncDataElements()
{
	int sz(m_SyncDataElements.size());
	std::cout << std::endl; 
	std::cout << "****** The Number of Elements is "<< sz << "****** " << std::endl; 
	for(m_ItSyncDataElements = m_SyncDataElements.begin();m_ItSyncDataElements != m_SyncDataElements.end();m_ItSyncDataElements++)
		std::cout<< "Time Difference is : " << m_ItSyncDataElements->first << "  , The Device Type is :" << m_ItSyncDataElements->second->GetDeviceType() << "  , The Device Name is :" << m_ItSyncDataElements->second->GetDeviceName() <<std::endl;

	return sz;
}

//// Get the first IGTLMessage in MUSiiCSyncDataElements
igtl::MessageBase::Pointer MUSiiCSyncDataElements::GetFirstIGTLMessage()
{
	int sz(m_SyncDataElements.size());
	if(sz >=1)
	{
		m_ItSyncDataElements = GetBeginIT();
		return m_ItSyncDataElements->second;
	}

	return NULL;
}
//// Get the second IGTLMessage in MUSiiCSyncDataElements
igtl::MessageBase::Pointer MUSiiCSyncDataElements::GetSecondIGTLMessage()
{
	int sz(m_SyncDataElements.size());
	if(sz >= 2)
	{
		m_ItSyncDataElements = GetBeginIT();
		m_ItSyncDataElements++;
		return m_ItSyncDataElements->second;
	}

	return NULL;
}

//// Check the size of MUSiiCSyncDataElements //cannon96
int MUSiiCSyncDataElements::CheckSizeOfSyncDataElements()
{
	int sz(m_SyncDataElements.size());
	if(sz >m_iMaxCount)
		return DeleteMidSyncDataElements(sz);
	return sz;
}

/// Delete the mid of MUSiiCSyncDataElement in the container //cannon96
int MUSiiCSyncDataElements::DeleteMidSyncDataElements(int const sz)
{
	m_ItSyncDataElements = m_SyncDataElements.begin();
	for(int i=0; i<sz/2; i++)
		m_ItSyncDataElements++;

	m_SyncDataElements.erase(m_ItSyncDataElements);

	return m_SyncDataElements.size();
}


//protected: // operations
void MUSiiCSyncDataElements::Initialize()
{	
	m_SyncDataElements.clear();
	m_iMaxCount = 10;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Constructor
MUSiiCSyncData::MUSiiCSyncData()
{
	Initialize();
}
	
///Deconstructor
MUSiiCSyncData::~MUSiiCSyncData()
{
}
////Get the number of SyncData
int MUSiiCSyncData::GetSize()
{ 
	return m_SyncData.size();
}

/// Check there is Data in MUSiiCSyncData structure
bool MUSiiCSyncData::IsSyncData(){return m_bIsSyncData;}
///// Add IGTL Message as Data
int MUSiiCSyncData::AddDataIGTLMsg(igtl::MessageBase::Pointer data)
{
	if(data.IsNotNull())
	{
		std::string device = strlen(data->GetDeviceName()) > 2 ? data->GetDeviceName() : data->GetDeviceType();
		//m_SyncData[device].AddIGTLMsg(data);
		m_SyncData[device].m_SyncDataElements[GetIGTLTimeStamp(data)] = data; ///cannon96
		m_SyncData[device].CheckSizeOfSyncDataElements();						/// cannon96
		int s(m_SyncData.size());
		m_bIsSyncData = s > 0 ? true : false; 
		return s;
	}
	else
		return -1;
}

//// Get the iterator of begin of this Data structure
std::map<std::string , igtl::MUSiiCSyncDataElements>::iterator MUSiiCSyncData::GetBeginIT() {return m_SyncData.begin();}

//// Get the iterator of end of this Data structure
std::map<std::string , igtl::MUSiiCSyncDataElements>::iterator MUSiiCSyncData::GetEndIT() {return m_SyncData.end();}

///// Add MUSiiCSyncData Structure
int MUSiiCSyncData::AddMUSiiCSyncData(igtl::MUSiiCSyncData::Pointer	syncdata, double refTS)
{
	if(syncdata.IsNotNull())
	{
		for(m_ItSyncData = syncdata->GetBeginIT(); m_ItSyncData != syncdata->GetEndIT(); m_ItSyncData++)
		{
			//m_SyncData[m_ItSyncData->first].AddMUSiiCSyncDataElement(m_ItSyncData->second, refTS);
			m_SyncData[m_ItSyncData->first].AddMUSiiCSyncDataElement(m_ItSyncData->second, refTS);
		}
		return 	syncdata->GetSize();
	}
	
	return 0;
}

/// Find Closeest IGTL Messages in MUSiiCSyncDataSet
//int MUSiiCSyncData::FindClosestIGTLMessages(std::vector<igtl::MessageBase::Pointer>& vCloseIGTL)
//{
//	int sz(m_SyncData.size());
//	//std::cout << "The Size of MUSiiCSyncData is  : " << sz << std::endl;
//	for(m_ItSyncData = m_SyncData.begin(); m_ItSyncData != m_SyncData.end(); m_ItSyncData++)
//		vCloseIGTL.push_back(m_ItSyncData->second.GetFirstIGTLMessage());
//	return vCloseIGTL.size();
//}

int MUSiiCSyncData::FindClosestIGTLMessages(std::vector<igtl::MessageBase::Pointer>& vCloseIGTL, double RefTS)
{
	int sz(m_SyncData.size());
	//std::cout << "The Size of MUSiiCSyncData is  : " << sz << std::endl;
	for(m_ItSyncData = m_SyncData.begin(); m_ItSyncData != m_SyncData.end(); m_ItSyncData++)
	{
		igtl::MessageBase::Pointer tempMsg = m_ItSyncData->second.GetFirstIGTLMessage();
		if(tempMsg.IsNotNull())
		{
			if(IsTrackingDataMessage(tempMsg))
			{
				/// Interpolating Tracking Message
				if(m_SyncData.size()>1)
			    { 
					igtl::MessageBase::Pointer tempMsg2 = m_ItSyncData->second.GetSecondIGTLMessage();
					if(tempMsg2.IsNotNull())
					{
						igtl::MessageBase::Pointer IntTrackMsg;
						IntTrackMsg =  InterpolateTrackingMessage(tempMsg,tempMsg2, RefTS);
						if(IntTrackMsg.IsNotNull())
							vCloseIGTL.push_back(IntTrackMsg);
					}
				}
				else
					vCloseIGTL.push_back(tempMsg);
			}
			else
			{ 
				vCloseIGTL.push_back(tempMsg);
			}
		}
	}
	return vCloseIGTL.size();
}
int MUSiiCSyncData::FindCloseTwoIGTLMessages(std::vector<igtl::MessageBase::Pointer>& vCloseIGTL)
{
	int sz(m_SyncData.size());
	//std::cout << "The Size of MUSiiCSyncData is  : " << sz << std::endl;
	for(m_ItSyncData = m_SyncData.begin(); m_ItSyncData != m_SyncData.end(); m_ItSyncData++)
	{
		/// Get the first close IGTL Message
		igtl::MessageBase::Pointer tempMsg = m_ItSyncData->second.GetFirstIGTLMessage();
		if(tempMsg.IsNotNull())
			vCloseIGTL.push_back(tempMsg);
		/// Get the second close IGTL Message
		igtl::MessageBase::Pointer tempMsg2 = m_ItSyncData->second.GetSecondIGTLMessage();
		if(tempMsg2.IsNotNull())
			vCloseIGTL.push_back(tempMsg);
	}
	return vCloseIGTL.size();
}

///// Add MUSiiCSyncData Structure
int MUSiiCSyncData::PrintMUSiiCSyncData(std::string des)
{
	std::cout << "Printing PrintMUSiiCSyncData : Description is :  " << des.c_str() << std::endl;
	int sz(m_SyncData.size());
	//std::cout << "The Size of MUSiiCSyncData is  : " << sz << std::endl;
	for(m_ItSyncData = m_SyncData.begin(); m_ItSyncData != m_SyncData.end(); m_ItSyncData++)
	{
		std::cout <<std::endl;
		std::cout << "The Device Name :" << m_ItSyncData->first << std::endl;
		m_ItSyncData->second.PrintMUSiiCSyncDataElements();
	}

	return sz;
}



//protected: // operations
void MUSiiCSyncData::Initialize()
{
	m_bIsSyncData	= false;
	m_SyncData.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//public: /// Operations
///Constructor
MUSiiCSyncDataSet::MUSiiCSyncDataSet()
{
	Initialize();
}

/// Ceconstructor
MUSiiCSyncDataSet::~MUSiiCSyncDataSet()
{
}

/// Set Reference Data
bool MUSiiCSyncDataSet::SetReferenceIGTLMsg(igtl::MessageBase::Pointer ref)
{
	if(ref.IsNotNull())
	{
		this->m_Ref_Msg				= ref;
		this->m_dReferenceTS		= GetIGTLTimeStamp(ref);
		this->m_bIsReferenceData	= true;			
	}
	else
		return false;
}

//// Print Reference IGTL Message in MUSiiCSyncDataSet
void MUSiiCSyncDataSet::PrintReferenceIGTLMsg(std::string des)
{
	std::cout << "PrintReferenceIGTLMsg (Description is :  " << des.c_str() << ")" << std::endl;
	if(m_bIsReferenceData)
	{
		std::cout << "The device type of Reference Data is :" << m_Ref_Msg->GetDeviceType() << std::endl;
		std::cout << "The device name of Reference Data is :" << m_Ref_Msg->GetDeviceName() << std::endl;
		std::cout << "The time-stamp of Reference Data is : " << m_dReferenceTS << std::endl;
	}
	else
		std::cout<< "There is no Reference Data !!! " << std::endl;

}


///// Add MUSiiCSyncData Structure
int MUSiiCSyncDataSet::AddMUSiiCSyncData(igtl::MUSiiCSyncData::Pointer syncdata)
{
	if(syncdata.IsNotNull())
		m_pSyncDataSet->AddMUSiiCSyncData(syncdata, m_dReferenceTS);
	else
		return 0;
}

/// Check there is Reference Data or not
bool MUSiiCSyncDataSet::IsGotReferenceData()
{
	return m_bIsReferenceData;
}

/// Print the contents of MUSiiCSyncDataSet
int MUSiiCSyncDataSet::PrintMUSiiCSyncDataSet(std::string des)
{
	PrintReferenceIGTLMsg(des);
	return m_pSyncDataSet->PrintMUSiiCSyncData(des);
}

/// Find Closeest IGTL Messages in MUSiiCSyncDataSet
int MUSiiCSyncDataSet::FindClosestIGTLMsg()
{
	m_vIGTLMsgs.clear();
	m_vIGTLMsgs.push_back(m_Ref_Msg);
	double RefTS(GetIGTLTimeStamp2(m_Ref_Msg));
	return m_pSyncDataSet->FindClosestIGTLMessages(m_vIGTLMsgs,RefTS);
}

int MUSiiCSyncDataSet::FindCloseTwoIGTLMsg()
{
	m_vIGTLMsgs.clear();
	m_vIGTLMsgs.push_back(m_Ref_Msg);
	return m_pSyncDataSet->FindCloseTwoIGTLMessages(m_vIGTLMsgs);
}
/// Get Closeest IGTL Messages in MUSiiCSyncDataSet
igtl::MessageBase::Pointer MUSiiCSyncDataSet::GetClosestIGTLMsg(int index)
{
	if(index < m_vIGTLMsgs.size())
		return m_vIGTLMsgs[index];
	return NULL;
}

/// Print Closest IGTL Messages in MUSiiCSyncDataSet
int MUSiiCSyncDataSet::PrintClosestIGTLMsg(std::string des)
{
	int sz(m_vIGTLMsgs.size());
	PrintReferenceIGTLMsg(des);
	for(int i=0; i<sz; i++)
		std::cout << "Device type :  " << m_vIGTLMsgs[i]->GetDeviceType() << " , Device Name: " <<
		m_vIGTLMsgs[i]->GetDeviceName() << ", Time Stamp: " << GetIGTLTimeStamp(m_vIGTLMsgs[i]) << std::endl;
	return sz;
}

///////////////////////////////////////////////////////////////////////////
//protected: // operations
void MUSiiCSyncDataSet::Initialize()
{
	/// Initialize Reference Data
	m_Ref_Msg				= NULL;
	m_bIsReferenceData		= false;
	m_dReferenceTS			= 0.0;

	/// Initialize Data
	m_pSyncDataSet			= igtl::MUSiiCSyncData::New();
	/// Initialize the container for closest IGTLMessages
	m_vIGTLMsgs.clear();
}
}