/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/
#ifndef __MUSIIC_SYNC_DATA_COLLECT_
#define __MUSIIC_SYNC_DATA_COLLECT_

//#include "MUSiiCTaskDoubleInterface.h"
//#include "MUSiiCTCPClientUni.h"

#include "MUSiiCSyncDATA.h"
#include "MUSiiCTaskInterfaceAbstract.h"

namespace igtl
{
class IGTLMCommon_EXPORT MUSiiCSyncDATACollect: 
	public MUSiiCTaskInterfaceAbstract<igtl::MessageBase::Pointer, igtl::MUSiiCSyncDataSet::Pointer>
{
public: ///Operations
	typedef MUSiiCSyncDATACollect											Self;
	typedef MUSiiCTaskInterfaceAbstract										Superclass;
	typedef SmartPointer<Self>												Pointer;
	typedef SmartPointer<Self>												ConstPointer;
	
	/** Method for creation through the object factory. */
	igtlNewMacro(Self);
  
	/** Run-time type information (and related methods). */
	igtlTypeMacro(Self, Superclass);

public://Operations
	/// Constructor
	MUSiiCSyncDATACollect();
	/// Deconstructor
	~MUSiiCSyncDATACollect();
	/// Run MUSiiCSyncDataCollect
	int DataCollect();

	//int AddClientSocket(igtl::MUSiiCTCPClientUni::Pointer pClient);

protected://Operations
	/// Initialize Member variables
	virtual void Initialize();

	/// Client-Network Task function is implemented in this function.
	virtual int TaskFunction(int numOfRun, int taskInfo, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);
	
	/// Core function MUSiiCSyncDataCollection
	int SyncDataCollection();

public://Attributes

protected:// Attributes
	/*igtl::MUSiiCSyncDataSet::Pointer							m_SyncDataPack;
	double														m_RefTimeStamp;
	int															m_RefIndex;
	
	igtl::MUSiiCVector<igtl::MUSiiCTCPClientUni::Pointer>::Pointer	m_pClientSet;
	bool														m_bClientSet;

	std::vector<igtl::MUSiiCSyncData::Pointer>					m_TempData_Set;
	bool														m_bTempData_Set;
	std::vector<igtl::MUSiiCSyncData::Pointer>					m_TempData_Set_Pre;
	bool														m_bTempData_Set_Pre;
	*/

	///////////////////////////////////////////////////////////
	//// Reference Data
	bool												m_bIsGotRefenceData;
	
	
	/////MUSiiCsync Data
	igtl::MUSiiCSyncData::Pointer						m_pTempSyncDataPre;
	bool												m_bTempSyncDataPre;

	igtl::MUSiiCSyncData::Pointer						m_pTempSyncDataPost;
	bool												m_bTempSyncDataPost;

	//// MUSiiCsyncDataSet
	igtl::MUSiiCSyncDataSet::Pointer					m_pSyncDataSet;

	/// Data-Interface
	igtl::MUSiiCVector<igtl::MessageBase::Pointer>		m_pInputDataIF;
	igtl::MUSiiCVector<igtl::MUSiiCSyncDataSet::Pointer>	m_pOutputDataIF;



};
};
#endif

