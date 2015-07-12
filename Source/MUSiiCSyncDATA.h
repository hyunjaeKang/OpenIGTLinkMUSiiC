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
#ifndef __MUSIIC_SYNC_DATA_
#define __MUSIIC_SYNC_DATA_

#include "MUSiiCIGTLUtil.h"

namespace igtl
{

///////////////////////////////////////////////////////////////////////
class IGTLMCommon_EXPORT MUSiiCSyncDataElements //: public LightObject
{
public: ///Operations
	/// Constructor
	MUSiiCSyncDataElements();
	/// Deconstructor
	~MUSiiCSyncDataElements();
	////Get the number of elements
	int GetSize();

	//// Get the iterator of begin of this Data structure
	std::map<double, igtl::MessageBase::Pointer>::iterator GetBeginIT();

	//// Get the iterator of end of this Data structure
	std::map<double, igtl::MessageBase::Pointer>::iterator GetEndIT();


	//// Get SyncDataElements
	std::map<double, igtl::MessageBase::Pointer>& GetDataElements();

	/// Add IGTL Message
	int AddIGTLMsg(igtl::MessageBase::Pointer msg, double  refTS = 0.0);

	//// Add MUSiiCSyncDataElement 
	int AddMUSiiCSyncDataElement(igtl::MUSiiCSyncDataElements& elements, double refTS = 0.0);

	//// Print MUSiiCSyncDataElements
	int PrintMUSiiCSyncDataElements();

	//// Get the first IGTLMessage in MUSiiCSyncDataElements
	igtl::MessageBase::Pointer GetFirstIGTLMessage();
	//// Get the second IGTLMessage in MUSiiCSyncDataElements
	igtl::MessageBase::Pointer GetSecondIGTLMessage();

	//// Check the size of MUSiiCSyncDataElements //cannon96
	int CheckSizeOfSyncDataElements();

	/// Delete the mid of MUSiiCSyncDataElement in the container //cannon96
	int DeleteMidSyncDataElements(int const sz);
	
protected: // operations
	virtual void Initialize();
public: //attribute
	std::map<double, igtl::MessageBase::Pointer>			m_SyncDataElements;
	std::map<double, igtl::MessageBase::Pointer>::iterator	m_ItSyncDataElements;

	int														m_iMaxCount;
};

///////////////////////////////////////////////////////////////////////
class IGTLMCommon_EXPORT MUSiiCSyncData : public LightObject
{
public: ///Operations
	typedef MUSiiCSyncData						Self;
	typedef LightObject							Superclass;
	typedef SmartPointer<Self>					Pointer;
	typedef SmartPointer<Self>					ConstPointer;
	
	/** Method for creation through the object factory. */
	igtlNewMacro(Self);
  
	/** Run-time type information (and related methods). */
	igtlTypeMacro(Self, Superclass);

public: /// Operations
	/// Constructor
	MUSiiCSyncData();
	
	///Deconstructor
	~MUSiiCSyncData();
	////Get the number of SyncData
	int GetSize();

	/// Check there is Data in MUSiiCSyncData structure
	bool IsSyncData();
	///// Add IGTL Message as Data
	int AddDataIGTLMsg(igtl::MessageBase::Pointer data);

	//// Get the iterator of begin of this Data structure
	std::map<std::string , igtl::MUSiiCSyncDataElements>::iterator GetBeginIT();

	//// Get the iterator of end of this Data structure
	std::map<std::string , igtl::MUSiiCSyncDataElements>::iterator GetEndIT();

	///// Add MUSiiCSyncData Structure
	int AddMUSiiCSyncData(igtl::MUSiiCSyncData::Pointer	syncdata, double refTS = 0.0);

	/// Find Closest IGTL Messages in MUSiiCSyncDataSet
	int FindClosestIGTLMessages(std::vector<igtl::MessageBase::Pointer>& vCloseIGTL, double RefTS = 0.0);

	/// Find Close two IGTL Message in MUSiiCSyncDataSet
	int FindCloseTwoIGTLMessages(std::vector<igtl::MessageBase::Pointer>& vCloseIGTL);

	/// Add MUSiiCSyncData Structure
	int PrintMUSiiCSyncData(std::string des = " ");


protected: // operations
	virtual void Initialize();

protected: // attributes
	bool m_bIsSyncData;
public: //attribute
	std::map<std::string , igtl::MUSiiCSyncDataElements>			m_SyncData;
	std::map<std::string , igtl::MUSiiCSyncDataElements>::iterator	m_ItSyncData;
};

///////////////////////////////////////////////////////////////////////

class IGTLMCommon_EXPORT MUSiiCSyncDataSet : public LightObject
{
public: ///Operations
	typedef MUSiiCSyncDataSet					Self;
	typedef LightObject							Superclass;
	typedef SmartPointer<Self>					Pointer;
	typedef SmartPointer<Self>					ConstPointer;
	
	/** Method for creation through the object factory. */
	igtlNewMacro(Self);
  
	/** Run-time type information (and related methods). */
	igtlTypeMacro(Self, Superclass);

//public: /// Operations
	///Constructor
	MUSiiCSyncDataSet();
	/// Ceconstructor
	~MUSiiCSyncDataSet();

	/// Set Reference Data
	bool SetReferenceIGTLMsg(igtl::MessageBase::Pointer ref);

	//// Print Reference IGTL Message in MUSiiCSyncDataSet
	void PrintReferenceIGTLMsg(std::string des = " ");
	
	///// Add MUSiiCSyncData Structure
	int AddMUSiiCSyncData(igtl::MUSiiCSyncData::Pointer syncdata);

	/// Check there is Reference Data or not
	bool IsGotReferenceData();

	/// Print the contents of MUSiiCSyncDataSet
	int PrintMUSiiCSyncDataSet(std::string des = " ");

	/// Find Closest IGTL Messages in MUSiiCSyncDataSet
	int FindClosestIGTLMsg();

	// Find twp close IGTL Messages in MUSiiCSyncDataSet
	int FindCloseTwoIGTLMsg();

	/// Get Closest IGTL Message
	igtl::MessageBase::Pointer GetClosestIGTLMsg(int index);

	/// Print Closest IGTL Messages in MUSiiCSyncDataSet
	int PrintClosestIGTLMsg(std::string des = " ");

protected: // operations
	virtual void Initialize();
public: //attribute
	/// Reference Data
	igtl::MessageBase::Pointer				m_Ref_Msg;
	bool									m_bIsReferenceData;
	double									m_dReferenceTS;

	/// the pointer of MUSiiCSyncData
	igtl::MUSiiCSyncData::Pointer			m_pSyncDataSet;

	//// A Container for closest IGTLMessages against to Reference Data
	std::vector<igtl::MessageBase::Pointer> m_vIGTLMsgs;

};

};

#endif