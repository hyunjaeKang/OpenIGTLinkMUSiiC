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
#ifndef __MUSIIC_SYNC_
#define __MUSIIC_SYNC_

#include "MUSiiCSyncDATA.h"
#include "MUSiiCIGTLTask.h"

namespace igtl
{


class IGTLMCommon_EXPORT MUSiiCSync : public MUSiiCIGTLTask
{
public: // Operations
	typedef MUSiiCSync						Self;
	typedef MUSiiCIGTLTask							Superclass;
	typedef SmartPointer<Self>						Pointer;
	typedef SmartPointer<Self>						ConstPointer;
	
	/** Method for creation through the object factory. */
	igtlNewMacro(MUSiiCSync);
  
	/** Run-time type information (and related methods). */
	igtlTypeMacro(MUSiiCSync, MUSiiCIGTLTask);

	/// Constrcut
	MUSiiCSync();
	/// Deconstruct
	~MUSiiCSync();

	/// RunMUSiiCSync
	int RunMUSiiCSync();
	
	/// Set Calibration information
	bool MUSiiCSync::SetCalibrationData(igtl::Matrix4x4 matrix);

	//// User defined Callback function
	/// Declare a function that is called MUSiiCCallbackInterface
	virtual int PreCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	/// Declare a function that is called MUSiiCCallbackInterface
	virtual int PostCallback(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

protected: ///operations
	virtual void Initialize();
	
	/// Client-Network Task function is implemented in this function.
	virtual int TaskFunction(int numOfRun, int taskInfo, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);
	

	int DataCollectTask(int numOfRun, int taskInfo, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);

	/// Core function MUSiiCSyncDataCollection
	int SyncDataCollection();

	/// Core function MUSiiCSyncDataCollection
	int SyncDataCombine();

	/// Find Close Data against to a reference data in MUSiiCDataSet
	int GetClosestIGTLMsgFromSyncDataSet(igtl::MUSiiCSyncDataSet::Pointer msg);

	/// Initialize Container
	void InitializeContainer();

	/// Update Transformation matrix
	int UpdateTransformationMatrix();

	/// Post processing of MUSiiCSync
	int PostProcessMUSiiCSync();

	/// Put UnSync Message
	int PutUnSyncMessage(igtl::MessageBase::Pointer msg);

	/// Pop UnSyncMessage
	int PopUnSyncMessage();

public: // Attributes

protected: // Attributes

	///////////////////////////////////////////////////////////
	//// Reference Data
	bool															m_bIsGotRefenceData;
	
	
	/////MUSiiCsync Data
	igtl::MUSiiCSyncData::Pointer									m_pTempSyncDataPre;
	bool															m_bTempSyncDataPre;

	igtl::MUSiiCSyncData::Pointer									m_pTempSyncDataPost;
	bool															m_bTempSyncDataPost;

	//// MUSiiCsyncDataSet
	igtl::MUSiiCSyncDataSet::Pointer								m_pSyncDataSet;

	/// Data-Interface
	/*igtl::MUSiiCVector<igtl::MessageBase::Pointer>::Pointer			m_pInputDataIF;
	bool															m_bInputDataIF;*/
	
	igtl::MUSiiCVector<igtl::MUSiiCSyncDataSet::Pointer>::Pointer	m_pPostCollectorDataIF;
	bool															m_bPostCollectorDataIF;

	//////////////////////////////////////////////////////////////////////////////////////
	igtl::Matrix4x4													m_pCalibration;
	bool															m_bCalibration;
	igtl::FastMutexLock::Pointer									m_pFastMutex;
	int																m_iTrackerIndex;

	igtl::FastMutexLock::Pointer									m_pUnSyncFastMutex;

	///DataType
	// 0: ImageMessage
	// 1 : US_Message
	// 2 : EI_Message
	int																m_iDataType;


	std::vector<igtl::MessageBase::Pointer>							m_vIGTLMsg;
	std::vector<igtl::MessageBase::Pointer>							m_vIGTLIMG;
	std::vector<igtl::MessageBase::Pointer>							m_vIGTLUpdatedIMG;
	std::vector<igtl::MessageBase::Pointer>							m_vIGTLTRACKER;
	std::vector<igtl::MessageBase::Pointer>							m_vUnSyncIGTLMsg;

	bool															m_bIsTrackingDataMessage;
	bool															m_bIsGotClosestMessage;
	bool															m_bUpdatedIMGMessages;


	igtl::MUSiiCTaskObject::Pointer									m_pSyncDataCollectTask;


	std::string														m_Prefix_US;//("US");
	std::string														m_Prefix_RF;//("RF");
	std::string														m_Prefix_EI;//("EI");
	

};

} //end of namespace
#endif
