/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/
#ifndef __MUSIIC_SYNC_DATA_COMBINE_
#define __MUSIIC_SYNC_DATA_COMBINE_

//#include "MUSiiCTaskDoubleInterface.h"
#include "MUSiiCIGTLUtil.h"
#include "MUSiiCSyncDATA.h"
#include "igtlFastMutexLock.h"
#include "MUSiiCTaskInterfaceAbstract.h"
//
namespace igtl
{
class IGTLMCommon_EXPORT MUSiiCSyncDATACombine: 
	public MUSiiCTaskInterfaceAbstract<igtl::MUSiiCSyncDataSet::Pointer, igtl::MessageBase::Pointer>
{
public: ///Operations
	typedef MUSiiCSyncDATACombine		Self;
	typedef MUSiiCTaskInterfaceAbstract	Superclass;
	typedef SmartPointer<Self>			Pointer;
	typedef SmartPointer<Self>			ConstPointer;
	
	/** Method for creation through the object factory. */
	igtlNewMacro(Self);
  
	/** Run-time type information (and related methods). */
	igtlTypeMacro(Self, Superclass);

public:// Operations
	/// Constructor
	MUSiiCSyncDATACombine();
	/// Deconstructor
	~MUSiiCSyncDATACombine();
	/// Run MUSiiCSyncDataCombine
	int DataCombine();

	bool SetCalibrationData(igtl::Matrix4x4 matrix);

	//void SetTrackerIndex(int index);

	//void SetImageDataType(int id){m_iDataType = id;}

protected://Operations
	/// Initialize Member variables
	virtual void Initialize();

	/// Client-Network Task function is implemented in this function.
	virtual int TaskFunction(int numOfRun, int taskInfo, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);
	
	//Core function MUSiiCSyncDataCollection
	int SyncDataCombine();
	
	////// Find Closest data from data-set
	//igtl::MUSiiCSyncDataElement::Pointer FindClosestData(igtl::MUSiiCSyncData::Pointer data_set);

	////// Update transformation matrix
	//int UpdateTransformationMatrix(std::vector<MUSiiCSyncDataElement::Pointer>& SyncData);

	////// Generate Bind Message and Send out
	//int GenerateBindMessage(std::vector<MUSiiCSyncDataElement::Pointer>& SyncData);

	int GetClosestIGTLMsgFromSyncDataSet(igtl::MUSiiCSyncDataSet::Pointer msg);

	void InitializeContainer();

	int UpdateTransformationMatrix();

	int PostProcessMUSiiCSync();

public:// Attributes

protected://Attributes
	//std::vector<MUSiiCSyncDataElement::Pointer>		m_vSyncData;
	igtl::Matrix4x4									m_pCalibration;
	bool											m_bCalibration;
	igtl::FastMutexLock::Pointer					m_pFastMutex;
	int												m_iTrackerIndex;

	///DataType
	// 0: ImageMessage
	// 1 : US_Message
	// 2 : EI_Message
	int												m_iDataType;


	std::vector<igtl::MessageBase::Pointer>         m_vIGTLMsg;
	std::vector<igtl::MessageBase::Pointer>         m_vIGTLIMG;
	std::vector<igtl::MessageBase::Pointer>         m_vIGTLUpdatedIMG;
	std::vector<igtl::MessageBase::Pointer>         m_vIGTLTRACKER;

	bool											m_bIsTrackingDataMessage;
	bool											m_bIsGotClosestMessage;
	bool											m_bUpdatedIMGMessages;

};
};

#endif