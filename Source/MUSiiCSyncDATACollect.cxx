/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/
#include "MUSiiCSyncDATACollect.h"
#include <cstdlib>
namespace igtl
{
 //Public operations
	MUSiiCSyncDATACollect::MUSiiCSyncDATACollect()
	{
		m_pNameOfClass="MUSiiCSyncDATACollect";
		Initialize();
	}
	MUSiiCSyncDATACollect::~MUSiiCSyncDATACollect()
	{
	}
//
//	/// Run MUSiiCSyncDataCollect
//	int MUSiiCSyncDATACollect::DataCollect()
//	{
//		///To DO:
//		/// Check interface. If there is no interface, just return -1;
//		this->SetEnableThread(true);
//		/// Run network thread for network communication
//		return RunTask(M_THREAD_RUN_CONTINUOUS, 100 , this, NULL, NULL, NULL);
//	}
//
//	int MUSiiCSyncDATACollect::AddClientSocket(igtl::MUSiiCTCPClientUni::Pointer pClient)
//	{
//		if(pClient.IsNotNull())
//		{
//			m_bClientSet = true;
//			return m_pClientSet->concurrent_push_back(pClient);
//		}
//		else
//			return 0;
//	}
//
///// protected operations
	void MUSiiCSyncDATACollect::Initialize()
	{
		

		/*m_RefTimeStamp		= 0.0;
		m_SyncDataPack		= NULL;
		m_RefIndex			= 0;
		m_pClientSet			= igtl::MUSiiCVector<igtl::MUSiiCTCPClientUni::Pointer>::New();

		m_bTempData_Set		= false;
		m_TempData_Set.clear();*/

		/////////////////////////////////////
		m_bIsGotRefenceData	= false;
		
		
		m_pTempSyncDataPre	= igtl::MUSiiCSyncData::New();
		m_bTempSyncDataPre	= true;

		m_pTempSyncDataPost = NULL;
		m_bTempSyncDataPost = false;

		m_pSyncDataSet      = NULL;

	}

	int MUSiiCSyncDATACollect::TaskFunction(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
	{
		return SyncDataCollection();
	}
//
//	/// Core function MUSiiCSyncDataCollection
	int MUSiiCSyncDATACollect::SyncDataCollection()
	{
		igtl::MessageBase::Pointer msg;
		/// ToDo:: cannon96 ::Check Point
		if(this->m_bVPreInputDATA_IF_Set)
			this->m_pVPreInputDATA_IF_Set->Concurrent_wait_get_pop_back_fromMUSiiCVectorSet(msg);
		
		if(msg.IsNotNull())
		{
			if(IsReferenceData(msg))
			{
				if(m_bIsGotRefenceData)
				{
					m_pSyncDataSet->AddMUSiiCSyncData(m_pTempSyncDataPre);
					m_pSyncDataSet->AddMUSiiCSyncData(m_pTempSyncDataPost);
					//////////////////////////////////////////////////////
					m_pTempSyncDataPre	= m_pTempSyncDataPost;	/// To Do : check point	 cannon96
					m_bTempSyncDataPost = false;

					/////////////////////////////////////////////////////////////////////////
					/// ToDo:: cannon96 ::Check Point
					if(this->m_bVPostOutputDATA_IF_Set)
						this->m_pVPostOutputDATA_IF_Set->Concurrent_push_back_ALL(m_pSyncDataSet);
					////////////////////////////////////////////////////////////////////////

					m_bIsGotRefenceData = false;
				}

				//// Create new MUSiiCSyncDataSet
				m_pSyncDataSet = igtl::MUSiiCSyncDataSet::New();
				//// Add Reference Data
				m_pSyncDataSet->SetReferenceIGTLMsg(msg);
				//// Check whether a reference data was got or not
				m_bIsGotRefenceData = true;
			}
			else  /// New Data
			{
				if(!m_bIsGotRefenceData)  /// Before getting a reference data
				{
					if(!m_bTempSyncDataPre)
						m_pTempSyncDataPre = igtl::MUSiiCSyncData::New();
					/// Add New data to Pre_MUSiiCData
					m_pTempSyncDataPre->AddDataIGTLMsg(msg);
					m_bTempSyncDataPre = true;
				}
				else  /// After getting a refernce data
				{
					if(!m_bTempSyncDataPost)
						m_pTempSyncDataPost = igtl::MUSiiCSyncData::New();
					/// Add New data to Post_MUSiiCData
					m_pTempSyncDataPost->AddDataIGTLMsg(msg);
					m_bTempSyncDataPost = true;
				}
			}
		}
		else
			return 0;

	}

};
