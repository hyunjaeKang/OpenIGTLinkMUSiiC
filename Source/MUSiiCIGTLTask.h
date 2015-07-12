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
#ifndef __MUSIIC_IGTL_TASK_
#define __MUSIIC_IGTL_TASK_

#include "MUSiiCTaskInterfaceAbstract.h"

namespace igtl
{

class IGTLMCommon_EXPORT MUSiiCIGTLTask: public MUSiiCTaskInterfaceAbstract<igtl::MessageBase::Pointer, igtl::MessageBase::Pointer>
{
public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCIGTLTask						Self;
	typedef MUSiiCTaskInterfaceAbstract			Superclass;
	typedef SmartPointer<Self>					Pointer;
	typedef SmartPointer<const Self>			ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	/// Constructor
	MUSiiCIGTLTask();
	
	/// Deconstructor
	~MUSiiCIGTLTask();

	////////////////////////////////////////////////////////////
	/// MUSiiC IO Filter
	
	
	/// ******* Input MUSiiC IO Filter

	/// Set Input-MUSiiCIOFilter
	virtual bool SetPreInputMUSiiCIOFilter(igtl::MUSiiCIOFilter::Pointer filter);

	/// Get InputMUSiiCIOFilter of this class
	virtual igtl::MUSiiCIOFilter::Pointer GetPreInputMUSiiCIOFilter();

	/// Check there is MUSiiCIOFilter
	virtual bool IsPreInputMUSiiCIOFilter();

	/// Set the boolean value of MUSiiCIOFilter
	virtual bool SetEnablePreInputMUSiiCIOFilter(bool enable = true);

	/// Get the boolean value of MUSiiCIOFilter
	virtual bool GetEnablePreInputMUSiiCIOFilter();

	////----------------------------------------------------------------//////
	/// Reset Input MUSiiC IO Filter
	virtual void ResetPreInputMUSiiCIOFilter();

	/// Set Input MUSiiCIOFilter using Data_Type or DeviceName
	/// return : the size of MUSiiCIOFIlter
	virtual int SetPreInputMUSiiCIOFilterData(std::string datatype, bool enable = true);

	/// Get How many data-type are defined in MUSiiCIOFilter
	virtual int GetNumberOfDataTypePreInputMUSiiCIOFilter();

	/// Get The list of data-type 
	virtual std::vector<std::string>& GetDataTypeListFromPreInputMUSiiCIOFilter();

	/// Remove data-type from MUSiiCIOFilter
	virtual int RemoveDataTypeFromPreInputMUSiiCIOFilter(std::string datatype);

	/// Check the data-type is or not in MUSiiCIOFilter
	virtual bool IsDataTypeFromPreInputMUSiiCIOFilter(std::string datatype);

	//// Check MessageBase using pre-defined IOFilter
	virtual igtl::MessageBase::Pointer CheckMessageBasePreInputMUSiiCIOFilter(igtl::MessageBase::Pointer msg);

	virtual void PrintPreInputMUSiiCIOFilter();

	bool GetEnalbePreInputCheckDeviceType(){return m_bPreInputCheckDeviceType;}

	void SetEnalbePreInputCheckDeviceType(bool enable){m_bPreInputCheckDeviceType = enable;}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// ******* Output MUSiiC IO Filter

	/// Set Input-MUSiiCIOFilter
	virtual bool SetPreOutputMUSiiCIOFilter(igtl::MUSiiCIOFilter::Pointer filter);

	/// Get InputMUSiiCIOFilter of this class
	virtual igtl::MUSiiCIOFilter::Pointer GetPreOutputMUSiiCIOFilter();

	/// Check there is MUSiiCIOFilter
	virtual bool IsPreOutputMUSiiCIOFilter();

	/// Set the boolean value of MUSiiCIOFilter
	virtual bool SetEnablePreOutputMUSiiCIOFilter(bool enable = true);

	/// Get the boolean value of MUSiiCIOFilter
	virtual bool GetEnablePreOutputMUSiiCIOFilter();

	////----------------------------------------------------------------//////
	/// Reset Output MUSiiC IO Filter
	virtual void ResetPreOutputMUSiiCIOFilter();

	/// Set Output MUSiiCIOFilter using Data_Type or DeviceName
	/// return : the size of MUSiiCIOFIlter
	virtual int SetPreOutputMUSiiCIOFilterData(std::string datatype, bool enable = true);

	/// Get How many data-type are defined in Output MUSiiCIOFilter
	virtual int GetNumberOfDataTypePreOutputMUSiiCIOFilter();

	/// Get The list of data-type 
	virtual std::vector<std::string>& GetDataTypeListFromPreOutputMUSiiCIOFilter();

	/// Remove data-type from MUSiiCIOFilter
	virtual int RemoveDataTypeFromPreOutputMUSiiCIOFilter(std::string datatype);

	/// Check the data-type is or not in MUSiiCIOFilter
	virtual bool IsDataTypeFromPreOutputMUSiiCIOFilter(std::string datatype);

	//// Check MessageBase using pre-defined IOFilter
	virtual igtl::MessageBase::Pointer CheckMessageBasPreOutputMUSiiCIOFilter(igtl::MessageBase::Pointer msg);

	virtual void PrintPreOutputMUSiiCIOFilter();

	bool GetEnalbePreOutputCheckDeviceType(){return m_bPreOutputCheckDeviceType;}

	void SetEnalbePreOutputCheckDeviceType(bool enable){m_bPreOutputCheckDeviceType = enable;}

	/// MUSiiC IO Filter
	////////////////////////////////////////////////////////////


	///// To/From Post

	/// ******* Input MUSiiC IO Filter

	/// Set Input-MUSiiCIOFilter
	virtual bool SetPostInputMUSiiCIOFilter(igtl::MUSiiCIOFilter::Pointer filter);

	/// Get InputMUSiiCIOFilter of this class
	virtual igtl::MUSiiCIOFilter::Pointer GetPostInputMUSiiCIOFilter();

	/// Check there is MUSiiCIOFilter
	virtual bool IsPostInputMUSiiCIOFilter();

	/// Set the boolean value of MUSiiCIOFilter
	virtual bool SetEnablePostInputMUSiiCIOFilter(bool enable = true);

	/// Get the boolean value of MUSiiCIOFilter
	virtual bool GetEnablePostInputMUSiiCIOFilter();

	////----------------------------------------------------------------//////
	/// Reset Input MUSiiC IO Filter
	virtual void ResetPostInputMUSiiCIOFilter();

	/// Set Input MUSiiCIOFilter using Data_Type or DeviceName
	/// return : the size of MUSiiCIOFIlter
	virtual int SetPostInputMUSiiCIOFilterData(std::string datatype, bool enable = true);

	/// Get How many data-type are defined in MUSiiCIOFilter
	virtual int GetNumberOfDataTypePostInputMUSiiCIOFilter();

	/// Get The list of data-type 
	virtual std::vector<std::string>& GetDataTypeListFromPostInputMUSiiCIOFilter();

	/// Remove data-type from MUSiiCIOFilter
	virtual int RemoveDataTypeFromPostInputMUSiiCIOFilter(std::string datatype);

	/// Check the data-type is or not in MUSiiCIOFilter
	virtual bool IsDataTypeFromPostInputMUSiiCIOFilter(std::string datatype);

	//// Check MessageBase using pre-defined IOFilter
	virtual igtl::MessageBase::Pointer CheckMessageBasePostInputMUSiiCIOFilter(igtl::MessageBase::Pointer msg);

	virtual void PrintPostInputMUSiiCIOFilter();

	bool GetEnalbePostInputCheckDeviceType(){return m_bPostInputCheckDeviceType;}

	void SetEnalbePostInputCheckDeviceType(bool enable){m_bPostInputCheckDeviceType = enable;}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// ******* Output MUSiiC IO Filter

	/// Set Input-MUSiiCIOFilter
	virtual bool SetPostOutputMUSiiCIOFilter(igtl::MUSiiCIOFilter::Pointer filter);

	/// Get InputMUSiiCIOFilter of this class
	virtual igtl::MUSiiCIOFilter::Pointer GetPostOutputMUSiiCIOFilter();

	/// Check there is MUSiiCIOFilter
	virtual bool IsPostOutputMUSiiCIOFilter();

	/// Set the boolean value of MUSiiCIOFilter
	virtual bool SetEnablePostOutputMUSiiCIOFilter(bool enable = true);

	/// Get the boolean value of MUSiiCIOFilter
	virtual bool GetEnablePostOutputMUSiiCIOFilter();

	////----------------------------------------------------------------//////
	/// Reset Output MUSiiC IO Filter
	virtual void ResetPostOutputMUSiiCIOFilter();

	/// Set Output MUSiiCIOFilter using Data_Type or DeviceName
	/// return : the size of MUSiiCIOFIlter
	virtual int SetPostOutputMUSiiCIOFilterData(std::string datatype, bool enable = true);

	/// Get How many data-type are defined in Output MUSiiCIOFilter
	virtual int GetNumberOfDataTypePostOutputMUSiiCIOFilter();

	/// Get The list of data-type 
	virtual std::vector<std::string>& GetDataTypeListFromPostOutputMUSiiCIOFilter();

	/// Remove data-type from MUSiiCIOFilter
	virtual int RemoveDataTypeFromPostOutputMUSiiCIOFilter(std::string datatype);

	/// Check the data-type is or not in MUSiiCIOFilter
	virtual bool IsDataTypeFromPostOutputMUSiiCIOFilter(std::string datatype);

	//// Check MessageBase using pre-defined IOFilter
	virtual igtl::MessageBase::Pointer CheckMessageBasPostOutputMUSiiCIOFilter(igtl::MessageBase::Pointer msg);

	virtual void PrintPostOutputMUSiiCIOFilter();

	bool GetEnalbePostOutputCheckDeviceType(){return m_bPostOutputCheckDeviceType;}

	void SetEnalbePostOutputCheckDeviceType(bool enable){m_bPostOutputCheckDeviceType = enable;}

	/// MUSiiC IO Filter
	////////////////////////////////////////////////////////////
	

	////////////////////////////////////////////////////////////
	/// ETC
	
	
	/////////////////////////////////////////////////////////////
	///// Data Handling
	/////////////////////////////////////////////////////////////
	///Put igtl::MessageBase::Pointer to MUSiiCIODevice
	///          virtual function.
	/// We need to re-implement this function for specific purpose.
	virtual int PutIGTLMessage(igtl::MessageBase::Pointer msg);

	/////////////////////////////////////////////////////////////
	///Try Put igtl::MessageBase::Pointer to MUSiiCIODevice
	///          virtual function.
	/// We need to re-implement this function for specific purpose.
	virtual int TryPutIGTLMessage(igtl::MessageBase::Pointer msg);
	

	///// Data Handling
	/////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	//////// Link MUSiiCTaskInterfaceAbstract

	//// Add another MUSiiCIGTLTask as the previous Task Class
	bool AddPreMUSiiCIGTLTask(igtl::MUSiiCIGTLTask::Pointer pre_task);

	//Reemove pre-defined MUSiiCIGTLTask from Pre-MUSiiCIGTLTask List. 	
	bool RemovePreMUSiiCIGTLTask(igtl::MUSiiCIGTLTask::Pointer pre_task);


	////// Add another MUSiiCIGTLTask as the post Task Class
	bool AddPostMUSiiCIGTLTask(igtl::MUSiiCIGTLTask::Pointer post_task);

	//Reemove pre-defined MUSiiCIGTLTask from Post-MUSiiCIGTLTask List. 	
	bool RemovePostMUSiiCIGTLTask(igtl::MUSiiCIGTLTask::Pointer post_task);
	//////// Link MUSiiCTaskInterfaceAbstract
	/////////////////////////////////////////////////////////////////////////////


	/// Get the pointer of MUSiiCIGTLTask of this class
	igtl::MUSiiCIGTLTask::Pointer GetMUSiiCIGTLTaskPointer();
	

protected: ///Operation
	/// Initialize class memeber variables
	virtual void Initialize();


	////////////////////////////////////////////////////////////////////////////////////////////
	//// Re-implementation virtual functions of MUSiiCTaskInterface Abstract ///////////////////
	
	/// Send IGTL Message to Pre-MUSiiCTask class
	/// This function is virtual function.
	/// We have to re-implement this function on MUSIiCIODevice, and other MUSiiCTask classes (MUSiiCSyncCombine, MUSiiCSuncDataCollectot)
	/// To Do: cannon96
	virtual int SendIGTLMsgToPreTask(igtl::MessageBase::Pointer data);

	/// Send IGTL Message to Pre-MUSiiCTask class
	/// This function is virtual function.
	/// We have to re-implement this function on MUSIiCIODevice, and other MUSiiCTask classes (MUSiiCSyncCombine, MUSiiCSuncDataCollectot)
	/// To Do: cannon96
	virtual int SendIGTLMsgToPostTask(igtl::MessageBase::Pointer data);

	///Retrieve Inpudata from void* data 
	/// This function is virtual function.
	/// We have to re-implement this function on MUSIiCIODevice, and other MUSiiCTask classes (MUSiiCSyncCombine, MUSiiCSuncDataCollectot)
	/// To Do: cannon96
	virtual igtl::MessageBase::Pointer RetrieveInputData(void* data);

	///Retrieve Outpudata from void* data
	/// This function is virtual function.
	/// We have to re-implement this function on MUSIiCIODevice, and other MUSiiCTask classes (MUSiiCSyncCombine, MUSiiCSuncDataCollectot)
	/// To Do: cannon96
	virtual igtl::MessageBase::Pointer RetrieveOutputData(void* data);

	//// Re-implementation virtual functions of MUSiiCTaskInterface Abstract ///////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	
		
public:/// Attributes
	

protected:/// Attributes
	/// The pointer of MUSiiCIOFilter
	igtl::MUSiiCIOFilter::Pointer	m_pPreInputMUSiiCIOFilter;

	/// The boolean variable of MUSiiCIOFilter
	bool							m_bIsPreInputMUSiiCIOFilter;

	/// The boolean variable for MUSiiCIOFilter :: Checking DeviceType (Input Data)
	bool							m_bPreInputCheckDeviceType;

	/// The pointer of MUSiiCIOFilter
	igtl::MUSiiCIOFilter::Pointer	m_pPreOutputMUSiiCIOFilter;

	/// The boolean variable of MUSiiCIOFilter
	bool							m_bIsPreOutputMUSiiCIOFilter;

	/// The boolean variable for MUSiiCIOFilter :: Checking DeviceType (Output Data)
	bool							m_bPreOutputCheckDeviceType;

	
	//////////////////////////////////////////////////////////////////////////////////////////
	
	/// The pointer of MUSiiCIOFilter
	igtl::MUSiiCIOFilter::Pointer	m_pPostInputMUSiiCIOFilter;

	/// The boolean variable of MUSiiCIOFilter
	bool							m_bIsPostInputMUSiiCIOFilter;

	/// The boolean variable for MUSiiCIOFilter :: Checking DeviceType (Input Data)
	bool							m_bPostInputCheckDeviceType;

	/// The pointer of MUSiiCIOFilter
	igtl::MUSiiCIOFilter::Pointer	m_pPostOutputMUSiiCIOFilter;

	/// The boolean variable of MUSiiCIOFilter
	bool							m_bIsPostOutputMUSiiCIOFilter;

	/// The boolean variable for MUSiiCIOFilter :: Checking DeviceType (Output Data)
	bool							m_bPostOutputCheckDeviceType;
};
}
#endif
