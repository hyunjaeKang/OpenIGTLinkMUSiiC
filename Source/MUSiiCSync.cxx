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

#include "MUSiiCSync.h"

namespace igtl
{

	/// Constrcut
	MUSiiCSync::MUSiiCSync()
	{
		this->m_pNameOfClass = "MUSiiCSync";
		Initialize();
	}

	/// Deconstrcut
	MUSiiCSync::~MUSiiCSync()
	{
	}

	/// RunMUSiiCSync
	int MUSiiCSync::RunMUSiiCSync()
	{
		this->SetEnableThread(true);
		return RunTask(M_THREAD_RUN_CONTINUOUS,100, this, NULL, NULL, NULL,M_ALLTASKOBJECT);
	}

	/// Set Calibration information
	bool MUSiiCSync::SetCalibrationData(igtl::Matrix4x4 matrix)
	{
		if(matrix != NULL)
		{
			for(int i=0; i<4; i++)
				for(int j=0; j<4; j++)
					m_pCalibration[i][j] = matrix[i][j];

			m_bCalibration = true;
		}
		
		return m_bCalibration;
	}

	// Declare a function that is called MUSiiCCallbackInterface
	/// Called by PreMUSiiCTask
	int MUSiiCSync::PreCallback(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2 , void* data3)
	{
		if(m_bDebug && ptr != NULL)
		{
			MUSiiCTaskAbstract* pTask = (MUSiiCTaskAbstract*) ptr;
			std::cout << "MUSiiCSync::PreCallback' of " << this->GetNameOfMUSiiCClass().c_str() << std::endl;
			std::cout << "Triggered by " << pTask->GetNameOfMUSiiCClass().c_str() << std::endl;
		}
		return 1;
	}

	/// Declare a function that is called MUSiiCCallbackInterface
	/// Called by PostMUSiiCTask
	int MUSiiCSync::PostCallback(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2 , void* data3)
	{
		if(m_bDebug && ptr != NULL)
		{
			MUSiiCTaskAbstract* pTask = (MUSiiCTaskAbstract*) ptr;
			std::cout << "MUSiiCSync::PostCallback' of " << this->GetNameOfMUSiiCClass().c_str() << std::endl;
			std::cout << "Triggered by " << pTask->GetNameOfMUSiiCClass().c_str() << std::endl;
		}
		////////////////////////////////////////////////////////////////////////////////////////////////
		if(data1.IsNotNull())
		{
			if(IsStringMessage(data1))
				return CallALLPreTaskCallbackInterface(numOfRun, taskInfo, this, data1, data2, data3);
				
		}
		return 0;
	}


////protected: operations
	void MUSiiCSync::Initialize()
	{
		m_bIsGotRefenceData			= false;
		
		
		m_pTempSyncDataPre			= igtl::MUSiiCSyncData::New();
		m_bTempSyncDataPre			= false;

		m_pTempSyncDataPost			= igtl::MUSiiCSyncData::New();;
		m_bTempSyncDataPost			= false;

		m_pSyncDataSet				= NULL;

		//m_pInputDataIF			= igtl::MUSiiCVector<igtl::MessageBase::Pointer>::New();
		m_pPostCollectorDataIF		= igtl::MUSiiCVector<igtl::MUSiiCSyncDataSet::Pointer>::New();
		m_pPostCollectorDataIF->concurrent_clear();
		m_bPostCollectorDataIF		= true;

		///////////////////////////////////////
		m_pFastMutex				= igtl::FastMutexLock::New();
		m_bCalibration				= false;

		m_iDataType					= 0;

		m_pUnSyncFastMutex			= igtl::FastMutexLock::New();

		/////////////////////////////////////////////////
		InitializeContainer();
		m_bIsTrackingDataMessage	= false;
		m_bIsGotClosestMessage		= false;

		////////////////////////////////////////////////
		/// Add MUSiiCTaskObject for Data Collecting 
		m_pSyncDataCollectTask		= igtl::MUSiiCTaskObject::New();
		m_pSyncDataCollectTask->AddExternalLocalTaskFunction(this, &MUSiiCSync::DataCollectTask, "MUSiiCSync Data Collection");
		this->AddTaskObject(m_pSyncDataCollectTask);


		//////////////////////////////////////////////
		m_Prefix_US = "US";
		m_Prefix_RF = "RF";
		m_Prefix_EI = "EI";

		m_vUnSyncIGTLMsg.clear();


	}

	int MUSiiCSync::TaskFunction(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
	{
		//return SyncDataCollection();
		/// Running sequence 
		/// 01. MUSiiCSyncDataCombine
		/// 02. MUSiiCSyncDataCollector

		/// Core function MUSiiCSyncDataCollection
		return SyncDataCombine();
	}

	int MUSiiCSync::DataCollectTask(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
	{
		return SyncDataCollection();
	}


	int MUSiiCSync::SyncDataCollection()
	{
		igtl::MessageBase::Pointer msg;
		/// ToDo:: cannon96 ::Check Point
		if(this->m_bVPreInputDATA_IF_Set)
			this->m_pVPreInputDATA_IF_Set->Concurrent_wait_get_pop_back_fromMUSiiCVectorSet(msg);
		if(msg.IsNotNull())
		{
			if (strcmp(msg->GetDeviceType(), "STRING") == 0)
			{
				PutUnSyncMessage(msg);	
				PopUnSyncMessage();
				return 0;
			}
		}
		
		if(msg.IsNotNull())
		{
			if(IsReferenceData(msg))// New Reference Data
			{
				if(m_bIsGotRefenceData)
				{
					if(m_pSyncDataSet.IsNotNull())
					{
						m_pSyncDataSet->AddMUSiiCSyncData(m_pTempSyncDataPre);
						m_pSyncDataSet->AddMUSiiCSyncData(m_pTempSyncDataPost);
						//////////////////////////////////////////////////////
						m_pTempSyncDataPre	= m_pTempSyncDataPost;	/// To Do : check point	 cannon96
						m_bTempSyncDataPost = false;

						/////////////////////////////////////////////////////////////////////////
						/// ToDo:: cannon96 ::Check Point
						if(this->m_bPostCollectorDataIF)
							this->m_pPostCollectorDataIF->concurrent_push_back(m_pSyncDataSet);
						////////////////////////////////////////////////////////////////////////

						m_bIsGotRefenceData = false;
					}
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
				if(IsSyncData(msg))
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
				else
					PutUnSyncMessage(msg);
					

			}
		}
		else
			return 0;

	}


	/// Core function MUSiiCSyncDataCollection
	int MUSiiCSync::SyncDataCombine()
	{
		igtl::MUSiiCSyncDataSet::Pointer msg;
		/// ToDo:: cannon96 ::Check Point
		if(this->m_bPostCollectorDataIF)
			this->m_pPostCollectorDataIF->concurrent_wait_get_pop_front(msg);
		
		
		if(msg.IsNotNull())
		{
			/// Get Closeest IGTL Messages from MUSiiCSyncDataSet 
			int sz(GetClosestIGTLMsgFromSyncDataSet(msg));

			/// If there is a trackingDataMessage, update transformationMatrix
			if(m_bIsTrackingDataMessage)
				UpdateTransformationMatrix();

			return  PostProcessMUSiiCSync();
		}
		return 0;
	}

	/// Find Close Data against to a reference data in MUSiiCDataSet
	int MUSiiCSync::GetClosestIGTLMsgFromSyncDataSet(igtl::MUSiiCSyncDataSet::Pointer msg)
	{
		if(msg.IsNotNull())
		{
			int sz(msg->FindClosestIGTLMsg());
			InitializeContainer();
			for(int i=0; i<sz; i++)
			{
				double Ref_Time;
				/// Get Closeest IGTL Message in MUSiiCSyncDataSet
				igtl::MessageBase::Pointer tempMsg = msg->GetClosestIGTLMsg(i);
				/*if(IsReferenceData(tempMsg))
					Ref_Time = tempMsg->GetTimeStamp();*/
				if(tempMsg.IsNotNull())
				{
					//// Get IMAGEMessage
					if(IsImageMessage(tempMsg))
					{
						/*std::string device3 = tempMsg->GetDeviceName();
						if(device3.find("MD_BMODE")!=std::string::npos)
						{
							std::cout << "BMode Message" << std::endl;
						}*/
						m_vIGTLIMG.push_back(tempMsg);
						continue;
					}

					/// Get TrackingDataMessage
					if(IsTrackingDataMessage(tempMsg))
					{
						m_vIGTLTRACKER.push_back(tempMsg);
						m_bIsTrackingDataMessage = true;
						continue;
					}

					/// Get general IGTL Message
					m_vIGTLMsg.push_back(tempMsg);
				}
				else
					sz--;
			}

			m_bIsGotClosestMessage = sz>0 ? true: false;
			return sz;
		}

		return 0;
	}

	/// Initialize Container
	void MUSiiCSync::InitializeContainer()
	{
		m_vIGTLMsg.clear();
		m_vIGTLIMG.clear();
		m_vIGTLTRACKER.clear();
		m_vIGTLUpdatedIMG.clear();
		m_bIsTrackingDataMessage = false;
		m_bUpdatedIMGMessages = false;
	}

	//// Need to check this function
	int MUSiiCSync::UpdateTransformationMatrix()
	{
		int sz = m_vIGTLTRACKER.size();
		igtl::TrackingDataMessage::Pointer tracker = NULL;
		igtl::TrackingDataElement::Pointer ReftrackingData = NULL;
		for(int i=0; i< sz; i++)
		{
			tracker = RetrieveMessage<igtl::TrackingDataMessage::Pointer, igtl::TrackingDataMessage>(m_vIGTLTRACKER[i]);
			ReftrackingData = GetReferenceTrackingData(tracker);
			if(ReftrackingData.IsNotNull())
				break;
		}

		if(ReftrackingData.IsNotNull())
		{
			m_bUpdatedIMGMessages = true;
			/// Get Tracking information from TrackingDataMessage
			igtl::Matrix4x4 trackingMat;
			ReftrackingData->GetMatrix(trackingMat);
			igtl::Matrix4x4 updatedMat;

			/// Update the tracking information using pre-defined calibration data
			if(m_bCalibration)
				MatrixMultiplication(trackingMat,m_pCalibration, updatedMat); 
			else
				DuplicateMatrix(updatedMat, trackingMat);//updatedMat = trackingMat;
			
			sz = m_vIGTLIMG.size();

			for(int i=0; i<sz; i++)
			{
				/*igtl::ImageMessage::Pointer img = RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(m_vIGTLIMG[i]);
				if(img.IsNotNull())
				{
					img->SetMatrix(updatedMat);
					m_vIGTLUpdatedIMG.push_back((igtl::MessageBase::Pointer)img);
				}*/

				std::string device(m_vIGTLIMG[i]->GetDeviceName());
			
				/*std::string device3 = m_vIGTLIMG[i]->GetDeviceName();
				if(device3.find("MD_BMODE")!=std::string::npos)
				{
					std::cout << "BMode Message" << std::endl;
				}*/

				if((device.find(m_Prefix_US)!=std::string::npos) || (device.find(m_Prefix_RF)!=std::string::npos))
				{
					igtl::USMessage::Pointer us = RetrieveMessage<igtl::USMessage::Pointer, igtl::USMessage>(m_vIGTLIMG[i]);
					us->SetMatrix(updatedMat);
					m_vIGTLUpdatedIMG.push_back((igtl::MessageBase::Pointer)us);
				}
				else if(device.find(m_Prefix_EI)!=std::string::npos)
				{
					igtl::EIMessage::Pointer ei = RetrieveMessage<igtl::EIMessage::Pointer, igtl::EIMessage>(m_vIGTLIMG[i]);
					ei->SetMatrix(updatedMat);
					m_vIGTLUpdatedIMG.push_back((igtl::MessageBase::Pointer)ei);
				}
				else
				{
					igtl::ImageMessage::Pointer img = RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(m_vIGTLIMG[i]);
					img->SetMatrix(updatedMat);
					m_vIGTLUpdatedIMG.push_back((igtl::MessageBase::Pointer)img);
				}
			}

			return sz;
		}

		return 0;
	}

	int MUSiiCSync::PostProcessMUSiiCSync()
	{
		int total_sz, sz, i;

		total_sz = 0;

		igtl::MessageBase::Pointer msg;
		
		if(m_bUpdatedIMGMessages)
		{
			sz = m_vIGTLUpdatedIMG.size();
			total_sz += sz;
			for(i=0; i<sz;i++)
				this->PostTaskProcessing(M_POST_DATA, M_SYNC_UPDATEDIMAGE, this,m_vIGTLUpdatedIMG[i], NULL, NULL); 
		}
		else
		{
			sz = m_vIGTLIMG.size();
			total_sz += sz;
			/// ToDo:: cannon96 ::Check Point
			for(i=0; i<sz;i++)
				this->PostTaskProcessing(M_POST_DATA, M_SYNC_IMAGE, this,m_vIGTLIMG[i], NULL, NULL);
		}

		sz = m_vIGTLTRACKER.size();
		total_sz += sz;
		/// ToDo:: cannon96 ::Check Point
		for(i=0; i<sz;i++)
			this->PostTaskProcessing(M_POST_DATA, M_SYNC_TRACKER, this,m_vIGTLTRACKER[i], NULL, NULL);

		sz = m_vIGTLMsg.size();
		total_sz += sz;
		/// ToDo:: cannon96 ::Check Point
		for(i=0; i<sz;i++)
			this->PostTaskProcessing(M_POST_DATA, M_SYNC_IGTLMSG, this,m_vIGTLMsg[i], NULL, NULL);

		PopUnSyncMessage();

		return sz;
	}


	/// Put UnSync Message
	int MUSiiCSync::PutUnSyncMessage(igtl::MessageBase::Pointer msg)
	{
		m_pUnSyncFastMutex->Lock();
		m_vUnSyncIGTLMsg.push_back(msg);
		m_pUnSyncFastMutex->Unlock();

		return m_vUnSyncIGTLMsg.size();
	}

	/// Pop UnSyncMessage
	int MUSiiCSync::PopUnSyncMessage()
	{
		m_pUnSyncFastMutex->Lock();
		for(int i=0; i<m_vUnSyncIGTLMsg.size(); i++)
			this->PostTaskProcessing(M_POST_DATA, M_UNSYNC_IGTLMSG, this,m_vUnSyncIGTLMsg[i], NULL, NULL);
		m_pUnSyncFastMutex->Unlock();

		m_vUnSyncIGTLMsg.clear();

		return m_vUnSyncIGTLMsg.size();

	}


}