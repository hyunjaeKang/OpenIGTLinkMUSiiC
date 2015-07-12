/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/

#include "MUSiiCSyncDATACombine.h"
#include <cstring>

namespace igtl
{

//////public:// Operations
	/// Constructor
	MUSiiCSyncDATACombine::MUSiiCSyncDATACombine()
	{
		m_pNameOfClass="MUSiiCSyncDATACombine";
		Initialize();
	}
	/// Deconstructor
	MUSiiCSyncDATACombine::~MUSiiCSyncDATACombine()
	{
	}
	/// Run MUSiiCSyncDataCombine
	int MUSiiCSyncDATACombine::DataCombine()
	{
		///To DO:
		/// Check interface. If there is no interface, just return -1;
		/*this->SetEnableThread(true);
		/// Run network thread for network communication
		return RunTask(M_THREAD_RUN_CONTINUOUS, 100 , this, NULL, NULL, NULL);*/

		return 0;
	}

	/// Set Calibration information
	bool MUSiiCSyncDATACombine::SetCalibrationData(igtl::Matrix4x4 matrix)
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

	//void MUSiiCSyncDATACombine::SetTrackerIndex(int index)
	//{
	//	//m_pFastMutex->Lock();
	//	m_iTrackerIndex = index;
	//	//m_pFastMutex->Unlock();
	//}

//protected://Operations
	/// Initialize Member variables
	void MUSiiCSyncDATACombine::Initialize()
	{

		m_pFastMutex	= igtl::FastMutexLock::New();
		m_bCalibration  = false;

		m_iDataType		= 0;

		/////////////////////////////////////////////////
		InitializeContainer();
		m_bIsTrackingDataMessage = false;
		m_bIsGotClosestMessage   = false;
	}

	/// Client-Network Task function is implemented in this function.
	int MUSiiCSyncDATACombine::TaskFunction(int numOfRun, int taskInfo, void* ptr, igtl::MessageBase::Pointer data1, void* data2, void* data3)
	{
		return SyncDataCombine();
	}
	
	/// Core function MUSiiCSyncDataCollection
	int MUSiiCSyncDATACombine::SyncDataCombine()
	{
		igtl::MUSiiCSyncDataSet::Pointer msg;
		/// ToDo:: cannon96 ::Check Point
		if(this->m_bVPreInputDATA_IF_Set)
			this->m_pVPreInputDATA_IF_Set->Concurrent_wait_get_pop_back_fromMUSiiCVectorSet(msg);
		
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

	int MUSiiCSyncDATACombine::GetClosestIGTLMsgFromSyncDataSet(igtl::MUSiiCSyncDataSet::Pointer msg)
	{
		if(msg.IsNotNull())
		{
			int sz(msg->FindClosestIGTLMsg());
			InitializeContainer();
			for(int i=0; i<sz; i++)
			{
				/// Get Closeest IGTL Message in MUSiiCSyncDataSet
				igtl::MessageBase::Pointer tempMsg = msg->GetClosestIGTLMsg(i);
				if(tempMsg.IsNotNull())
				{
					//// Get IMAGEMessage
					if(IsImageMessage(tempMsg))
					{
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

	void MUSiiCSyncDATACombine::InitializeContainer()
	{
		m_vIGTLMsg.clear();
		m_vIGTLIMG.clear();
		m_vIGTLTRACKER.clear();
		m_vIGTLUpdatedIMG.clear();
		m_bIsTrackingDataMessage = false;
		m_bUpdatedIMGMessages = false;
	}

	//// Need to check this function
	int MUSiiCSyncDATACombine::UpdateTransformationMatrix()
	{
		int sz = m_vIGTLTRACKER.size();
		igtl::TrackingDataMessage::Pointer tracker;
		igtl::TrackingDataElement::Pointer ReftrackingData;
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
			
			sz = m_vIGTLMsg.size();

			for(int i=0; i<sz; i++)
			{
				igtl::ImageMessage::Pointer img = RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(m_vIGTLIMG[i]);
				if(img.IsNotNull())
				{
					img->SetMatrix(updatedMat);
					m_vIGTLUpdatedIMG.push_back((igtl::MessageBase::Pointer)img);
				}
			}

			return sz;
		}

		return 0;
	}


	int MUSiiCSyncDATACombine::PostProcessMUSiiCSync()
	{
		int total_sz, sz, i;

		total_sz = 0;

		igtl::MessageBase::Pointer msg;
		
		if(m_bUpdatedIMGMessages)
		{
			sz = m_vIGTLUpdatedIMG.size();
			total_sz += sz;
			for(i=0; i<sz;i++)
				this->m_pVPostOutputDATA_IF_Set->Concurrent_push_back_ALL(m_vIGTLUpdatedIMG[i]);
		}
		else
		{
			sz = m_vIGTLIMG.size();
			total_sz += sz;
			/// ToDo:: cannon96 ::Check Point
			for(i=0; i<sz;i++)
				this->m_pVPostOutputDATA_IF_Set->Concurrent_push_back_ALL(m_vIGTLIMG[i]);
		}

		sz = m_vIGTLTRACKER.size();
		total_sz += sz;
		/// ToDo:: cannon96 ::Check Point
		for(i=0; i<sz;i++)
			this->m_pVPostOutputDATA_IF_Set->Concurrent_push_back_ALL(m_vIGTLTRACKER[i]);

		sz = m_vIGTLMsg.size();
		total_sz += sz;
		/// ToDo:: cannon96 ::Check Point
		for(i=0; i<sz;i++)
			this->m_pVPostOutputDATA_IF_Set->Concurrent_push_back_ALL(m_vIGTLMsg[i]);



		return sz;
	}

	////// Update transformation matrix
	//int MUSiiCSyncDATACombine::UpdateTransformationMatrix(std::vector<MUSiiCSyncDataElement::Pointer>& SyncData)
	//{
	//	igtl::TrackingDataElement::Pointer tracker;

	//	std::vector<igtl::USMessage::Pointer> vImageSet; //KHJ
	//	//std::vector<igtl::ImageMessage::Pointer> vImageSet;

	//	int sz = SyncData.size();

	//	for(int i=0; i< sz;i++)
	//	{
	//		igtl::MessageBase::Pointer temp_msg = SyncData[i]->m_Msg; 
	//		if (strcmp(temp_msg->GetDeviceType(), "TDATA") == 0)
	//		{
	//			//m_pFastMutex->Lock();
	//			int index = m_iTrackerIndex;
	//			//m_pFastMutex->Unlock();

	//			igtl::TrackingDataMessage::Pointer trackingData2;
	//			trackingData2 = RetrieveMessage< igtl::TrackingDataMessage::Pointer, igtl::TrackingDataMessage>(temp_msg);

	//			tracker = ExtractTrackingInfo(temp_msg, index);
	//		}
	//		else if (strcmp(temp_msg->GetDeviceType(), "IMAGE") == 0)
	//		{
	//			//igtl::ImageMessage::Pointer temp_img = RetrieveMessage<igtl::ImageMessage::Pointer, igtl::ImageMessage>(temp_msg);//KHJ
	//			igtl::USMessage::Pointer temp_img = RetrieveMessage<igtl::USMessage::Pointer, igtl::USMessage>(temp_msg);
	//			if(temp_img.IsNotNull())
	//				vImageSet.push_back(temp_img);
	//		}
	//	}

	//	igtl::Matrix4x4 tackingMatrix;
	//	
	//	int sz_i = vImageSet.size();

	//	if(tracker.IsNotNull())
	//	{
	//		tracker->GetMatrix(tackingMatrix);

	//		for(int j=0; j<sz_i; j++)
	//		{
	//			if(m_bCalibration)
	//			{
	//				igtl::Matrix4x4 matC;
	//				vImageSet[j]->GetMatrix(matC);
	//				MatrixMultiplication(tackingMatrix,m_pCalibration, matC); 
	//				vImageSet[j]->SetMatrix(matC);
	//			}
	//			else
	//				vImageSet[j]->SetMatrix(tackingMatrix);
	//		}
	//	}

	//	/*igtl::BindMessage::Pointer bindMsg = igtl::BindMessage::New();
	//	bindMsg->Init();
	//	for(int k=0; k < sz_i; k++)
	//	{
	//		vImageSet[k]->Pack();
	//		bindMsg->AppendChildMessage(vImageSet[k]);
	//	}
	//	
	//	if(tracker.IsNotNull())
	//	{
	//		igtl::TransformMessage::Pointer transform = igtl::TransformMessage::New();
	//		transform->SetMatrix(tackingMatrix);
	//		transform->Pack();
	//		bindMsg->AppendChildMessage(transform);
	//	}

	//	bindMsg->Pack();*/

	//	if(m_bOutputDATA_IF)
	//	{
	//		//m_pOutputDATA_IF->concurrent_push_back((igtl::MessageBase::Pointer)bindMsg);
	//		if(vImageSet.size() > 0)
	//		{
	//			static int Run_index = 0;
	//			igtl::USMessage::Pointer temp_msg3 = vImageSet[0]; //KHJ
	//			//igtl::ImageMessage::Pointer temp_msg3 = vImageSet[0];
	//			temp_msg3->Pack();

	//			m_pOutputDATA_IF->concurrent_push_back((igtl::MessageBase::Pointer)temp_msg3);
	//			printf("Send out %d Data\n",Run_index);
	//			//fflush(stdout);
	//			//system("cls");
	//			Run_index++;
	//			vImageSet.clear();
	//		}
	//	}

	//	return sz_i;
	//}

};

