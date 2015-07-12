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

#ifndef __MUSIIC_TASK_IF_ABSTRACT_
#define __MUSIIC_TASK_IF_ABSTRACT_

#include "MUSiiCTaskAbstract.h"


namespace igtl
{

template<class InputData, class OutputData>
class IGTLMCommon_EXPORT MUSiiCTaskInterfaceAbstract: public MUSiiCTaskAbstract
{
public: ///Operation
	/** Standard class typedefs. */
	//typedef MUSiiCTaskInterfaceAbstract<InputData, OutputData>	Self;
	typedef MUSiiCTaskInterfaceAbstract<InputData,OutputData>	Self;
	typedef MUSiiCTaskAbstract			                        Superclass;
	typedef SmartPointer<Self>			                        Pointer;
	typedef SmartPointer<const Self>	                        ConstPointer;
	

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);

public:
	/// Constructor
	MUSiiCTaskInterfaceAbstract()
	{
		this->m_pNameOfClass = "MUSiiCTaskInterfaceAbstract";
		Initialize();
	}

	/// Deconstructor
	~MUSiiCTaskInterfaceAbstract()
	{
		if(m_pTaskControlMutex.IsNotNull())
			m_pTaskControlMutex->Unlock();

		this->StopTask(M_ALLTASKOBJECT);
	}

	/////////////////////////////////////////////////////////////////////////////
	///// Pre Input Data Interface Set    ///////////////////////////////////////////

	//// Add Pre-Input Data-Interface
	//// return: ID of added input data-interface
	int AddPreInputDataInterface(igtl::SmartPointer<igtl::MUSiiCVector<InputData> >  pPreInputDataIF)
	{
		int s(0);
		if(pPreInputDataIF.IsNotNull())
		{
			s = m_pVPreInputDATA_IF_Set->AddMUSiiCVectorInputDataIF(pPreInputDataIF);//return value is index of this data-interface
			m_bVPreInputDATA_IF_Set = s>-1?true:false;
		}
		return s;
	}

	/// Get Pre-Input Data Interface
	igtl::SmartPointer<igtl::MUSiiCVector<InputData> > GetPreInputDataInterface(int index = M_SELFDATAINTERFACE)
	{
		if(index == M_SELFDATAINTERFACE )
			index = 0;
		return m_pVPreInputDATA_IF_Set->GetMUSiiCVector(index);

	}

	/// Get Num of Pre-Input Data-Interface
	int GetNumOfPreInputDataInterface()
	{
		if(m_pVPreInputDATA_IF_Set.IsNotNull())
			return m_pVPreInputDATA_IF_Set->GetSizeOfMUSiiCVectorSet();

		return -1;
	}

	/// Check Is there Pre-Input Data Interface
	bool IsPreInputDataInterface()
	{
		m_bVPreInputDATA_IF_Set = m_pVPreInputDATA_IF_Set->IsMUSiiCVectors();
		return m_bVPreInputDATA_IF_Set;
	}

	/// Initialize Pre-Input DataInterfaces 
	virtual bool InitializePreInputDataInterface(int index = M_ALLDATAINTERFACE)
	{	
		bool r(true);
		int s(m_pVPreInputDATA_IF_Set->GetSizeOfMUSiiCVectorSet());
		if(index == M_ALLDATAINTERFACE)
			for(int i=0; i<s; i++)
				r &=m_pVPreInputDATA_IF_Set->CleanMUSiiCVector(i);
		else if(index == M_SELFDATAINTERFACE || index == 0)
			r = m_pVPreInputDATA_IF_Set->CleanMUSiiCVector(0);
		else
			r = m_pVPreInputDATA_IF_Set->CleanMUSiiCVector(index);

		return r;
	}

	/*/// Remove an Pre-Input interface from this class
	int RemovePreInputDataInterface(igtl::SmartPointer<igtl::MUSiiCVector<InputData>>  pPreInputDataIF)
	{
		int s(0);
		s = m_pVPreInputDATA_IF_Set->RemoveMUSiiCVector(pPreInputDataIF);
		m_bVPreInputDATA_IF_Set = s>0?true:false;
		return s;
	}*/

	//// Remove Post Output Data-Interface
	//// return: the size MUSiiCVectSet
	int RemovePreInputDataInterface(igtl::SmartPointer<igtl::MUSiiCVector<InputData> >  pPreInputDataIF)
	{
		int s(-1);
		if(pPreInputDataIF.IsNotNull())
		{
			s  = m_pVPreInputDATA_IF_Set->RemoveMUSiiCVector(pPreInputDataIF);//return value is index of this data-interface
			if(s>-1)
			{
				s  = m_pVPreInputDATA_IF_Set->GetSizeOfMUSiiCVectorSet();
				m_bVPreInputDATA_IF_Set = sz>0?true:false;
			}
		}
		return s;
	}
	
	/// Remove all Pre-Input Data-Interface 
	virtual bool ClearPreInputDataInterfaceSet()
	{
		m_bVPreInputDATA_IF_Set = !m_pVPreInputDATA_IF_Set->ClearMUSiiCVectorSet();
		return !m_bVPreInputDATA_IF_Set;
	}

	/// Initialize Pre-Input DataInterfaces 
	virtual bool ReleasePreInputDataInterface(int index = M_ALLDATAINTERFACE)
	{
		bool r(true);
		int s(m_pVPreInputDATA_IF_Set->GetSizeOfMUSiiCVectorSet());
		if(m_bDebug)
		{
			std::cout << "MUSiiCTaskInterfaceAbstract::ReleasePreInputDataInterface" << std::endl;
			std::cout << "TheSize of ReleasePreInputDataInterface:" << s << std::endl;
		}
		if(index == M_ALLDATAINTERFACE)
			for(int i=0; i<s; i++)
				r &= m_pVPreInputDATA_IF_Set->RelaseMUSiiCVector(i);
		else if(index == M_SELFDATAINTERFACE || index == 0)
			r = m_pVPreInputDATA_IF_Set->RelaseMUSiiCVector(0);
		else
			r = m_pVPreInputDATA_IF_Set->RelaseMUSiiCVector(index);

		m_pVPreInputDATA_IF_Set->EnforceRelease();
		return r;
	}

	/// Get Pre-Input_MUSiiCVectorSet of this class
	igtl::SmartPointer<igtl::MUSiiCVectorSet<InputData> > GetPreInputMUSiiCVectorSet()
	{
		return m_pVPreInputDATA_IF_Set.IsNotNull()? m_pVPreInputDATA_IF_Set:NULL ;
	}

	/// Set Pre-Input_MUSiiCVectorSet as the Pre-Input MUSiiCVectorSet of  this class
	bool SetPreInputMUSiiCVectorSet(igtl::SmartPointer<igtl::MUSiiCVectorSet<InputData> > pVPreInputMUSiiCVectorSet)
	{
		if(pVPreInputMUSiiCVectorSet.IsNotNull())
		{
			m_pVPreInputDATA_IF_Set = pVPreInputMUSiiCVectorSet;
			return true;
		}

		return false;
	}
	///// Pre Input Data Interface Set    ///////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////////////////
	///// Pre Output Data Interface    ////////////////////////////////////////////////////
	
	//// return: ID of added Pre-Ouput data-interface
	int AddPreOutputDataInterface(igtl::SmartPointer<igtl::MUSiiCVector<InputData> >  pPreOutputDataIF)
	{
		int s(0);
		s = m_pVPreOutputDATA_IF_Set->AddMUSiiCVectorOutputDataIF(pPreOutputDataIF);
		m_bVPreOutputDATA_IF_Set = s>-1?true:false;
		return s;
	}

	/// Get Pre-Ouput Data Interface
	igtl::SmartPointer<igtl::MUSiiCVector<InputData> > GetPreOutputDataInterface(int index = M_SELFDATAINTERFACE)
	{
		if(index == M_SELFDATAINTERFACE )
			index = 0;
		return m_pVPreOutputDATA_IF_Set->GetMUSiiCVector(index);
	}

	/// Get Num of Pre-Ouput Data-Interface
	int GetNumOfPreOutputDataInterface()
	{
		if(m_pVPreOutputDATA_IF_Set.IsNotNull())
			return m_pVPreOutputDATA_IF_Set->GetSizeOfMUSiiCVectorSet();

		return -1;
	}

	/// Check Is there Pre-Ouput Data-Interface
	bool IsPreOutputDataInterface()
	{
		m_bVPreOutputDATA_IF_Set = m_pVPreOutputDATA_IF_Set->IsMUSiiCVectors();
		return m_bVPreOutputDATA_IF_Set;
	}

	/// Initialize Pre-Ouput DataInterfaces 
	virtual bool InitializePreOutputDataInterface(int index = M_ALLDATAINTERFACE)
	{
		bool r(true);
		int s(m_pVPreOutputDATA_IF_Set->GetSizeOfMUSiiCVectorSet());
		if(index == M_ALLDATAINTERFACE)
			for(int i=0; i<s; i++)
				r &=m_pVPreOutputDATA_IF_Set->CleanMUSiiCVector(i);
		else if(index == M_SELFDATAINTERFACE || index == 0)
			r = m_pVPreOutputDATA_IF_Set->CleanMUSiiCVector(0);
		else
			r = m_pVPreOutputDATA_IF_Set->CleanMUSiiCVector(index);

		return r;
	}

	/*/// Remove an Pre-Ouput interface from this class
	int RemovePreOutputDataInterface(igtl::SmartPointer<igtl::MUSiiCVector<InputData>>  pPreOutputDataIF)
	{
		int s(0);
		s = m_pVPreOutputDATA_IF_Set->RemoveMUSiiCVector(pPreOutputDataIF);
		m_bVPreOutputDATA_IF_Set = s>0?true:false;
		return s;
	}*/

	//// Remove Post Output Data-Interface
	//// return: the size MUSiiCVectSet
	int RemovePreOutputDataInterface(igtl::SmartPointer<igtl::MUSiiCVector<InputData> >  pPreOutputDataIF)
	{
		int s(-1);
		if(pPreOutputDataIF.IsNotNull())
		{
			s  = m_pVPreOutputDATA_IF_Set->RemoveMUSiiCVector(pPreOutputDataIF);//return value is index of this data-interface
			if(s>-1)
			{
				s  = m_pVPreOutputDATA_IF_Set->GetSizeOfMUSiiCVectorSet();
				m_bVPreOutputDATA_IF_Set = sz>0?true:false;
			}
		}
		return s;
	}
	
	/// Remove all Pre-Ouput Data-Interface 
	virtual bool ClearPreOutputDataInterfaceSet()
	{
		return m_pVPreOutputDATA_IF_Set->ClearMUSiiCVectorSet();
	}

	/// Initialize Pre-Ouput DataInterfaces 
	virtual bool ReleasePreOutputDataInterface(int index = M_ALLDATAINTERFACE)
	{
		bool r(true);
		int s(m_pVPreOutputDATA_IF_Set->GetSizeOfMUSiiCVectorSet());
		if(index == M_ALLDATAINTERFACE)
			for(int i=0; i<s; i++)
				r &= m_pVPreOutputDATA_IF_Set->RelaseMUSiiCVector(i);
		else if(index == M_SELFDATAINTERFACE || index == 0)
			r = m_pVPreOutputDATA_IF_Set->RelaseMUSiiCVector(0);
		else
			r = m_pVPreOutputDATA_IF_Set->RelaseMUSiiCVector(index);

		m_pVPreOutputDATA_IF_Set->EnforceRelease();
		return r;
	}

	/// Get Pre-Input_MUSiiCVectorSet of this class
	igtl::SmartPointer<igtl::MUSiiCVectorSet<InputData> > GetPreOutputMUSiiCVectorSet()
	{
		return m_pVPreOutputDATA_IF_Set.IsNotNull()? m_pVPreOutputDATA_IF_Set: NULL;
	}

	

	/// Set Pre-Output_MUSiiCVectorSet as the Pre-Output MUSiiCVectorSet of  this class
	bool SetPreOutputMUSiiCVectorSet(igtl::SmartPointer<igtl::MUSiiCVectorSet<InputData> > pVPreOutputMUSiiCVectorSet)
	{
		if(pVPreOutputMUSiiCVectorSet.IsNotNull())
		{
			m_pVPreOutputDATA_IF_Set = pVPreOutputMUSiiCVectorSet;
			return true;
		}

		return false;
	}
	///// Output Data Interface    ////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////

	//--------------------------------------------------------------------------------/

	/////////////////////////////////////////////////////////////////////////////////
	///// PostInput Data Interface Set    ///////////////////////////////////////////

	//// Add Post Input Data-Interface
	//// return: ID of added input data-interface
	int AddPostInputDataInterface(igtl::SmartPointer<igtl::MUSiiCVector<OutputData> >  pPostInputDataIF)
	{
		int s(-1);
		if(pPostInputDataIF.IsNotNull())
		{
			s = m_pVPostInputDATA_IF_Set->AddMUSiiCVectorInputDataIF(pPostInputDataIF);//return value is index of this data-interface
			m_bVPostInputDATA_IF_Set = s>-1?true:false;
		}
		return s;
	}



	/// Get Post Input Data Interface
	igtl::SmartPointer<igtl::MUSiiCVector<OutputData>> GetPostInputDataInterface(int index = M_SELFDATAINTERFACE)
	{
		if(index == M_SELFDATAINTERFACE )
			index = 0;
		return m_pVPostInputDATA_IF_Set->GetMUSiiCVector(index);

	}

	/// Get Num of InputData-Interface
	int GetNumOfPostInputDataInterface()
	{
		if(m_pVPostInputDATA_IF_Set.IsNotNull())
			return m_pVPostInputDATA_IF_Set->GetSizeOfMUSiiCVectorSet();

		return -1;
	}

	/// Check Is there InputData Interface
	bool IsPostInputDataInterface()
	{
		m_bVPostInputDATA_IF_Set = m_pVPostInputDATA_IF_Set->IsMUSiiCVectors();
		return m_bVPostInputDATA_IF_Set;
	}

	/// Initialize Input DataInterfaces 
	virtual bool InitializePostInputDataInterface(int index = M_ALLDATAINTERFACE)
	{	
		bool r(true);
		//int s(m_pVInputDATA_IF_Set.GetSizeOfMUSiiCVectorSet());
		int s(m_pVPostInputDATA_IF_Set->GetSizeOfMUSiiCVectorSet());
		if(index == M_ALLDATAINTERFACE)
			for(int i=0; i<s; i++)
				r &=m_pVPostInputDATA_IF_Set->CleanMUSiiCVector(i);
		else if(index == M_SELFDATAINTERFACE || index == 0)
			r = m_pVPostInputDATA_IF_Set->CleanMUSiiCVector(0);
		else
			r = m_pVPostInputDATA_IF_Set->CleanMUSiiCVector(index);

		return r;
	}

	/*/// Remove an input interface from this class
	int RemovePostInputDataInterface(igtl::SmartPointer<igtl::MUSiiCVector<OutputData>>  pPostInputDataIF)
	{
		int s(0);
		s = m_pVPostInputDATA_IF_Set->RemoveMUSiiCVector(pPreInputDataIF);
		m_bVPostInputDATA_IF_Set = s>0?true:false;
		return s;
	}*/

	//// Remove Post Input Data-Interface
	//// return: the size MUSiiCVectSet
	int RemovePostInputDataInterface(igtl::SmartPointer<igtl::MUSiiCVector<OutputData>>  pPostInputDataIF)
	{
		int s(-1);
		if(pPostInputDataIF.IsNotNull())
		{
			s  = m_pVPostInputDATA_IF_Set->RemoveMUSiiCVector(pPostInputDataIF);//return value is index of this data-interface
			if(s>-1)
			{
				s  = m_pVPostInputDATA_IF_Set->GetSizeOfMUSiiCVectorSet();
				m_bVPostInputDATA_IF_Set = s>0?true:false;
			}
		}
		return s;
	}
	
	/// Remove all Input Data-Interface 
	virtual bool ClearPostInputDataInterfaceSet()
	{
		m_bVPostInputDATA_IF_Set = !m_pVPostInputDATA_IF_Set->ClearMUSiiCVectorSet();
		return !m_bVPostInputDATA_IF_Set;
	}

	/// Initialize Input DataInterfaces 
	virtual bool ReleasePostInputDataInterface(int index = M_ALLDATAINTERFACE)
	{
		bool r(true);
		int s(m_pVPostInputDATA_IF_Set->GetSizeOfMUSiiCVectorSet());
		if(index == M_ALLDATAINTERFACE)
			for(int i=0; i<s; i++)
				r &= m_pVPostInputDATA_IF_Set->RelaseMUSiiCVector(i);
		else if(index == M_SELFDATAINTERFACE || index == 0)
			r = m_pVPostInputDATA_IF_Set->RelaseMUSiiCVector(0);
		else
			r = m_pVPostInputDATA_IF_Set->RelaseMUSiiCVector(index);

		m_pVPostInputDATA_IF_Set->EnforceRelease();
		return r;
	}

	/// Get Post Input_MUSiiCVectorSet of this class
	igtl::SmartPointer<igtl::MUSiiCVectorSet<OutputData>> GetPostInputMUSiiCVectorSet()
	{
		return m_pVPostInputDATA_IF_Set.IsNotNull()? m_pVPostInputDATA_IF_Set:NULL ;
	}

	/// Set Post-Input_MUSiiCVectorSet as the Post-Input MUSiiCVectorSet of  this class
	bool SetPostInputMUSiiCVectorSet(igtl::SmartPointer<igtl::MUSiiCVectorSet<OutputData>> pVPostInputMUSiiCVectorSet)
	{
		if(pVPostInputMUSiiCVectorSet.IsNotNull())
		{
			m_pVPostInputDATA_IF_Set = pVPostInputMUSiiCVectorSet;
			return true;
		}

		return false;
	}

	///// Post Input Data Interface Set    ///////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////////////////
	///// Post Output Data Interface    ////////////////////////////////////////////////////
	
	//// return: ID of added Pre-output data-interface
	int AddPostOutputDataInterface(igtl::SmartPointer<igtl::MUSiiCVector<OutputData>>  pPostOutputDataIF)
	{
		int s(-1);
		if(pPostOutputDataIF.IsNotNull())
		{
			s = m_pVPostOutputDATA_IF_Set->AddMUSiiCVectorOutputDataIF(pPostOutputDataIF);
			m_bVPostOutputDATA_IF_Set = s>-1?true:false;
		}
		return s;
	}

	/// Get PreOutput Data Interface
	igtl::SmartPointer<igtl::MUSiiCVector<InputData>> GetPostOutputDataInterface(int index = M_SELFDATAINTERFACE)
	{
		if(index == M_SELFDATAINTERFACE )
			index = 0;
		return m_pVPostOutputDATA_IF_Set->GetMUSiiCVector(index);
	}

	/// Get Num of InputData-Interface
	int GetNumOfPostOutputDataInterface()
	{
		if(m_pVPostOutputDATA_IF_Set.IsNotNull())
			return m_pVPostOutputDATA_IF_Set->GetSizeOfMUSiiCVectorSet();

		return -1;
	}

	/// Check Is there InputData Interface
	bool IsPostOutputDataInterface()
	{
		m_bVPostOutputDATA_IF_Set = m_pVPostOutputDATA_IF_Set->IsMUSiiCVectors();
		return m_bVPostOutputDATA_IF_Set;
	}

	/// Initialize Input DataInterfaces 
	virtual bool InitializePostOutputDataInterface(int index = M_ALLDATAINTERFACE)
	{
		bool r(true);
		int s(m_pVPostOutputDATA_IF_Set->GetSizeOfMUSiiCVectorSet());
		if(index == M_ALLDATAINTERFACE)
			for(int i=0; i<s; i++)
				r &=m_pVPostOutputDATA_IF_Set->CleanMUSiiCVector(i);
		else if(index == M_SELFDATAINTERFACE || index == 0)
			r = m_pVPostOutputDATA_IF_Set->CleanMUSiiCVector(0);
		else
			r = m_pVPostOutputDATA_IF_Set->CleanMUSiiCVector(index);

		return r;
	}

	/*/// Remove an input interface from this class
	int RemovePostOutputDataInterface(igtl::SmartPointer<igtl::MUSiiCVector<OutputData>>  pPostOutputDataIF)
	{
		int s(0);
		s = m_pVPostOutputDATA_IF_Set->RemoveMUSiiCVector(pPostOutputDataIF);
		m_bVPostOutputDATA_IF_Set = s>0?true:false;
		return s;
	}*/

	//// Remove Post Output Data-Interface
	//// return: the size MUSiiCVectSet
	int RemovePostOutputDataInterface(igtl::SmartPointer<igtl::MUSiiCVector<OutputData>>  pPostOutputDataIF)
	{
		int s(-1);
		if(pPostOutputDataIF.IsNotNull())
		{
			s  = m_pVPostOutputDATA_IF_Set->RemoveMUSiiCVector(pPostOutputDataIF);//return value is index of this data-interface
			if(s>-1)
			{
				s  = m_pVPostOutputDATA_IF_Set->GetSizeOfMUSiiCVectorSet();
				m_bVPostOutputDATA_IF_Set = s>0?true:false;
			}
		}
		return s;
	}
	
	/// Remove all Input Data-Interface 
	virtual bool ClearPostOutputDataInterfaceSet()
	{
		return m_pVPostOutputDATA_IF_Set->ClearMUSiiCVectorSet();
	}

	/// Initialize Input DataInterfaces 
	virtual bool ReleasePostOutputDataInterface(int index = M_ALLDATAINTERFACE)
	{
		bool r(true);
		int s(m_pVPostOutputDATA_IF_Set->GetSizeOfMUSiiCVectorSet());
		if(index == M_ALLDATAINTERFACE)
			for(int i=0; i<s; i++)
				r &= m_pVPostOutputDATA_IF_Set->RelaseMUSiiCVector(i);
		else if(index == M_SELFDATAINTERFACE || index == 0)
			r = m_pVPostOutputDATA_IF_Set->RelaseMUSiiCVector(0);
		else
			r = m_pVPostOutputDATA_IF_Set->RelaseMUSiiCVector(index);

		m_pVPostOutputDATA_IF_Set->EnforceRelease();

		return r;
	}

	/// Get Post Output_MUSiiCVectorSet of this class
	igtl::SmartPointer<igtl::MUSiiCVectorSet<OutputData>> GetPostOutputMUSiiCVectorSet()
	{
		return m_pVPostOutputDATA_IF_Set.IsNotNull()? m_pVPostOutputDATA_IF_Set: NULL;
	}

	/// Set Post-Output_MUSiiCVectorSet as the Post-Output MUSiiCVectorSet of  this class
	bool SetPostOutputMUSiiCVectorSet(igtl::SmartPointer<igtl::MUSiiCVectorSet<OutputData>> pVPostOutputMUSiiCVectorSet)
	{
		if(pVPostOutputMUSiiCVectorSet.IsNotNull())
		{
			m_pVPostOutputDATA_IF_Set = pVPostOutputMUSiiCVectorSet;
			return true;
		}

		return false;
	}

	///// Output Data Interface    ////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////

	//--------------------------------------------------------------------------------/

	//--------------------------------------------------------------------------------///////////////

	//--------------------------------------------------------------------------------/
	/////////////////////////////////////////////////////////////////////////////
	///// Data Interface    ////////////////////////////////////////////////////
	virtual bool InitializeALLDataInterface()
	{
		return this->InitializePreInputDataInterface() && this->InitializePreOutputDataInterface() && this->InitializePostInputDataInterface() && this->InitializePostOutputDataInterface();;
	}

	virtual bool ReleaseALLDataInterface()
	{
		if(m_bDebug)
			std::cout << " ReleaseALLDataInterface" << std::endl;
		bool r = this->ReleasePreInputDataInterface();
		r &= this->ReleasePreOutputDataInterface();
		r &= this->ReleasePostInputDataInterface();
		r &= this->ReleasePostOutputDataInterface();

		return r;
		/*return return this->ReleasePreInputDataInterface()&& this->ReleasePreOutputDataInterface() && this->ReleasePostInputDataInterface() && this->ReleasePostOutputDataInterface();*/
	}
	///// Data Interface    ////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	///// Self Data Interface    ////////////////////////////////////////////////////

	//// Get SelfInputDatainterface
	igtl::SmartPointer<igtl::MUSiiCVector<InputData>> GetSelfPreInputDataInterface()
	{

		if(m_pSelfPreInputDataInterface.IsNotNull())
		{
			if(!m_bSelfPreInputDataInterface)
			{
				int s(this->GetNumOfPreInputDataInterface());
				this->AddPreInputDataInterface(m_pSelfPreInputDataInterface);

				m_bSelfPreInputDataInterface = this->GetNumOfPreInputDataInterface() == s+1 ? true: false;
			}
			
			m_bUseSelfPreInputDataInterface = true;
			return m_pSelfPreInputDataInterface;
		}

		return NULL;
	}

	//// Get SelfOutputDatainterface
	igtl::SmartPointer<igtl::MUSiiCVector<InputData>> GetSelfPreOutputDataInterface()
	{
		if(m_pSelfPreOutputDataInterface.IsNotNull())
		{
			if(!m_bSelfPreOutputDataInterface)
			{
				int s(this->GetNumOfPreOutputDataInterface());
				this->AddPreOutputDataInterface(m_pSelfPreOutputDataInterface);

				m_bSelfPreOutputDataInterface = this->GetNumOfPreOutputDataInterface() == s+1 ? true: false;
			}
			
			m_bUseSelfPreOutputDataInterface = true;
			return m_pSelfPreOutputDataInterface;
		}

		return NULL;
	}

	/////////////////////////////////////////////////////////////////////////////
	///// Self Data Interface    ////////////////////////////////////////////////////

	
	//////////////////////////////////////////////////////////////////////////////
	///////// Task Function //////////////////////////////////////////////////////
	/// Run the task funtion with/without thread
	virtual int RunTask(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL, int index = M_SELFTASKOBJECT)
	{
		if(InitializeALLDataInterface())
		{
			/// Backup Task-Information
			m_iNumOfRun  = numOfRun;
			m_iTaskInfo  = taskInfo;
			m_Ptr        = ptr;
			m_pData1     = data1; 
			m_pData2     = data2; 
			m_pData3     = data3;
			m_iTaskIndex = index;
			
			return igtl::MUSiiCTaskAbstract::RunTask(numOfRun, taskInfo, ptr, data1, data2, data3, index);
		}
		else
			return -1;
	}
	/// Stop the task thread
	virtual void StopTask(int index = M_SELFTASKOBJECT)
	{
		if(m_bDebug)
			std::cout << "MUSiiCTaskInterfaceAbstract::StopTask()" << std::endl;
		if(this->ReleaseALLDataInterface())
		{
			igtl::MUSiiCTaskAbstract::StopTask(index);
			this->InitializeALLDataInterface();
		}
	}

	/// Wiat for the task thread
	virtual void WaitTask(int index = M_SELFTASKOBJECT)
	{
		igtl::MUSiiCTaskAbstract::WaitTask(index);
	}

	/// Pause the  the task thread
	virtual void PauseTaks(int index = M_SELFTASKOBJECT)
	{
		if(this->ReleaseALLDataInterface())
		{
			igtl::MUSiiCTaskAbstract::StopTask(index);
			this->m_iTaskStatus = M_TAKS_PAUSED;
		}
	}

	/// Resume the  the task thread
	virtual int ResumeTaks(int index = M_SELFTASKOBJECT)
	{
		return igtl::MUSiiCTaskAbstract::RunTask(m_iNumOfRun, m_iTaskInfo, m_Ptr, m_pData1, m_pData2, m_pData3, m_iTaskIndex);
	}


	///////// Task Function //////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	//////// Link MUSiiCTaskInterfaceAbstract


	//// Add another MUSiiCTaskInterfaceAbstract as the previous Task Class
	template<class In, class Out>
	bool AddPreMUSiiCTaskInterface(igtl::MUSiiCTaskInterfaceAbstract<In,Out>* pre_task)
	{
		int r(0);
		if(pre_task)
		{
			/// Connect CallbackInterface of MUSiiCTask
			if(this->AddPreMUSiiCTask((igtl::MUSiiCTaskAbstract::Pointer)pre_task))
			{
				/// Connect Data Interface
				r = pre_task->AddPostOutputDataInterface(this->GetSelfPreInputDataInterface());
				r = pre_task->AddPostInputDataInterface(this->GetSelfPreOutputDataInterface());

				m_pTaskControlMutex->Lock();
				m_vPreMUSiiCTaskList.push_back(pre_task->GetMUSiiCTaskAbstractPointer());
				m_pTaskControlMutex->Unlock();

				return r>0?true:false;
			}
		}
		return false;
	}

	/// New **********
	//Reemove pre-defined MUSiiCTaskInterface from Pre-MUSiiCTaskInterface List. 	
	template<class In, class Out>
	bool RemovePreMUSiiCTaskInterface(igtl::MUSiiCTaskInterfaceAbstract<In,Out>* pre_task)
	{
	
		int r(0);
		if(pre_task)
		{
			/// Connect CallbackInterface of MUSiiCTask
			igtl::MUSiiCTaskAbstract::Pointer tempPreTask = pre_task->GetMUSiiCTaskAbstractPointer();
		
			int sz = m_vPreMUSiiCTaskList.size();
			for(int i=0 ; i<sz; i++)
			{
				if(m_vPreMUSiiCTaskList[i] == tempPreTask)
				{
					if(this->RemovePreMUSiiCTask(tempPreTask))
					{
						r = pre_task->RemovePostOutputDataInterface(this->GetSelfPreInputDataInterface());
						r = pre_task->RemovePostInputDataInterface(this->GetSelfPreOutputDataInterface());
						m_pTaskControlMutex->Lock();
						m_vPreMUSiiCTaskList.erase(m_vPreMUSiiCTaskList.begin()+i);
						m_pTaskControlMutex->Unlock();
					
						return r>-1?true:false;
					}
				}
			}
		}
		return false;
	}

	////// Add another MUSiiCTaskInterfaceAbstract as the post Task Class
	template<class In, class Out>
	bool AddPostMUSiiCTaskInterface(igtl::MUSiiCTaskInterfaceAbstract<In,Out>* post_task)
	{
		int r(0);
		if(post_task)
		{
			/// Connect CallbackInterface of MUSiiCTask
			if(this->AddPostMUSiiCTask((igtl::MUSiiCTaskAbstract::Pointer)post_task))
			{
				/// Connect Data Interface
				r = this->AddPostOutputDataInterface(post_task->GetSelfPreInputDataInterface());
				r = this->AddPostInputDataInterface(post_task->GetSelfPreOutputDataInterface());
				m_pTaskControlMutex->Lock();
				m_vPostMUSiiCTaskList.push_back(post_task->GetMUSiiCTaskAbstractPointer());
				m_pTaskControlMutex->Unlock();
				return r>0?true:false;
			}
		}
		return false;
	}


	/// New **********
	//Reemove pre-defined MUSiiCTaskInterface from Post-MUSiiCTaskInterface List. 	
	template<class In, class Out>
	bool RemovePostMUSiiCTaskInterface(igtl::MUSiiCTaskInterfaceAbstract<In,Out>* post_task)
	{
	
		int r(0);
		if(post_task)
		{
			/// Connect CallbackInterface of MUSiiCTask
			igtl::MUSiiCTaskAbstract::Pointer tempPostTask = post_task->GetMUSiiCTaskAbstractPointer();
		
			int sz = m_vPostMUSiiCTaskList.size();
			for(int i=0 ; i<sz; i++)
			{
				if(m_vPostMUSiiCTaskList[i] == tempPostTask)
				{
					if(this->RemovePostMUSiiCTask(tempPostTask))
					{
						r = this->RemovePostOutputDataInterface(post_task->GetSelfPreInputDataInterface());
						r = this->RemovePostInputDataInterface(post_task->GetSelfPreOutputDataInterface());
						m_pTaskControlMutex->Lock();
						m_vPostMUSiiCTaskList.erase(m_vPostMUSiiCTaskList.begin()+i);
						m_pTaskControlMutex->Unlock();
					
						return r>-1?true:false;
					}
				}
			}
		}
		return false;
	}
	////// Remove MUSiiCTaskInterfaceAbstract as the previous Task Class
	//template<class In, class Out>
	//bool RemovePostMUSiiCTaskInterface(igtl::MUSiiCTaskInterfaceAbstract<In,Out>* post_task)
	//{
	//	
	//	//// To Do: cannon96 OpenIGTLinkMUSiiC 2.1
	//	/*int r(0);
	//	if(pre_task)
	//	{
	//		/// Connect CallbackInterface of MUSiiCTask
	//		if(this->AddPreMUSiiCTask((igtl::MUSiiCTaskAbstract::Pointer)pre_task))
	//		{
	//			/// Connect Data Interface
	//			r = pre_task->AddPostOutputDataInterface(this->GetSelfPreInputDataInterface());
	//			r = pre_task->AddPostInputDataInterface(this->GetSelfPreOutputDataInterface());

	//			///
	//			m_vPreMUSiiCTaskList.push_back(pre_task->GetMUSiiCTaskAbstractPointer());

	//			return r>0?true:false;
	//		}
	//	}*/
	//	return false;
	//}
	/// Data-Casting to the pointer of MUSiiCTaskAbstract class
	igtl::MUSiiCTaskAbstract::Pointer GetMUSiiCTaskAbstractPointer()
	{
		return (igtl::MUSiiCTaskAbstract::Pointer)this;
	}

	//////////////////////////////////////////////////////////////////////
	void SetEnableUseIGTLMessage(bool enable = true)
	{
		m_bUseIGTLMessage = enable;
	}

	bool GetEnableUseIGTLMessage()
	{
		return m_bUseIGTLMessage;
	}


	
public:///Attributes
	std::vector<igtl::MUSiiCTaskAbstract::Pointer>			m_vPreMUSiiCTaskList;
	std::vector<igtl::MUSiiCTaskAbstract::Pointer>			m_vPostMUSiiCTaskList;

protected:///Operation
	/// Initialize Member variables
	virtual void Initialize()
	{
		/// Initialize Pre-Input interface
		m_pVPreInputDATA_IF_Set				= igtl::MUSiiCVectorSet<InputData>::New();
		m_pVPreInputDATA_IF_Set->ClearMUSiiCVectorSet();
		m_bVPreInputDATA_IF_Set				= false;

		/// Initialize Pre-Output interface
		m_pVPreOutputDATA_IF_Set			= igtl::MUSiiCVectorSet<InputData>::New();
		m_pVPreOutputDATA_IF_Set->ClearMUSiiCVectorSet();
		m_bVPreOutputDATA_IF_Set			= false;

		/// Initialize Post-Input interface
		m_pVPostInputDATA_IF_Set			= igtl::MUSiiCVectorSet<OutputData>::New();
		m_pVPostInputDATA_IF_Set->ClearMUSiiCVectorSet();
		m_bVPostInputDATA_IF_Set			= false;

		/// Initialize Post-Output interface
		m_pVPostOutputDATA_IF_Set			= igtl::MUSiiCVectorSet<OutputData>::New();
		m_pVPostOutputDATA_IF_Set->ClearMUSiiCVectorSet();
		m_bVPostOutputDATA_IF_Set			= false;


		/// A Pointer of MUSiiCVector for PreSelfInputDataInterface
		m_pSelfPreInputDataInterface		= igtl::MUSiiCVector<InputData>::New();
		// A boolean variable of SelfInputDataInterface
		m_bSelfPreInputDataInterface		= false;
		m_bUseSelfPreInputDataInterface		= false;


		/// A Pointer of MUSiiCVector for PreSelfOutputDataInterface
		m_pSelfPreOutputDataInterface		= igtl::MUSiiCVector<InputData>::New();
		// A boolean variable of SelfInputDataInterface
		m_bSelfPreOutputDataInterface		= false;
		m_bUseSelfPreOutputDataInterface	= false;

		/// Initialize Task Information
		m_iNumOfRun							= 0;
		m_iTaskInfo							= 0;
		m_Ptr								= NULL;
		m_pData1							= NULL; 
		m_pData2							= NULL; 
		m_pData3							= NULL;
		m_iTaskIndex						= 0;

		m_vPreMUSiiCTaskList.clear();
		m_vPostMUSiiCTaskList.clear();

		m_pTaskControlMutex = igtl::FastMutexLock::New();

		m_bUseIGTLMessage					= false;
	}

	/// PostTaskProcessing
	virtual int PostTaskProcessing(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
	{
		int r(0); /// return value
	
		switch(numOfRun)
		{
			case M_PRE_CONTROL_PRAR:
				r = CallALLPreTaskCallbackInterface(M_PRE_CONTROL_PRAR, taskInfo, ptr, data1, data2, data3);
				break;
		
			case M_POST_CONTROL_PRAR:
				r = CallALLPostTaskCallbackInterface(M_POST_CONTROL_PRAR, taskInfo, ptr, data1, data2, data3);
				break;
		
			case M_PRE_DATA:
			case M_PRE_CONTROL_PRAR_DATA:
				if(m_bUseIGTLMessage)
				{
					if(IsStringMessage(data1))// StringMessage 
						r = CallALLPreTaskCallbackInterface(M_PRE_CONTROL_PRAR_DATA, taskInfo, ptr, data1, data2, data3);
					else if(SendIGTLMsgToPreTask(data1)>-1) /// cannon96 :: check this line
						r = CallALLPreTaskCallbackInterface(M_PRE_CONTROL_PRAR, taskInfo, ptr, NULL, data2, data3);
					else
						r = CallALLPreTaskCallbackInterface(M_PRE_CONTROL_PRAR_DATA, taskInfo, ptr, data1, data2, data3);
				}
				else
					if(SendDataToPreTask(data2)>-1)  /// cannon96 :: check this line
						r = CallALLPreTaskCallbackInterface(M_PRE_CONTROL_PRAR, taskInfo, ptr, NULL, NULL, data3);
					else
						r = CallALLPreTaskCallbackInterface(M_PRE_CONTROL_PRAR_DATA, taskInfo, ptr, NULL, data2, data3);
				break;
		
			case M_POST_DATA:
			case M_POST_CONTROL_PRAR_DATA:
				/// Check this point
				/// Why did I check StringMessage
				if(m_bUseIGTLMessage)
				{
					if(IsStringMessage(data1)) //StringMessage
						r = CallALLPostTaskCallbackInterface(M_POST_CONTROL_PRAR_DATA, taskInfo, ptr, data1, data2, data3);
					else if(SendIGTLMsgToPostTask(data1)>-1)
						r = CallALLPostTaskCallbackInterface(M_POST_CONTROL_PRAR, taskInfo, ptr, NULL, data2, data3);
					else
						r = CallALLPostTaskCallbackInterface(M_POST_CONTROL_PRAR_DATA, taskInfo, ptr, data1, data2, data3);

				}
				else
					if(SendDataToPostTask(data2)>-1)
						r = CallALLPostTaskCallbackInterface(M_POST_CONTROL_PRAR, taskInfo, ptr, NULL, NULL, data3);
					else
						r = CallALLPostTaskCallbackInterface(M_POST_CONTROL_PRAR_DATA, taskInfo, ptr, NULL, data2, data3);

				break;
		
			default:
				MUSiiC_LOG(logERROR) << "NO Defined Message";
				break;
		}

		return r;

	}

	/// Call the callback interfaces of Pre-Task
	/// Return value(-1) means the Error of this function
	int CallALLPreTaskCallbackInterface(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
	{	
		/*if(this->GetNumOfExternalInputCallbackFunctions()>0)
			m_bEnableExternalInputCallbackFuntions = true;
		else
			m_bEnableExternalInputCallbackFuntions = false;*/

		if(this->m_bEnableExternalInputCallbackFuntions)
		{
			return this->CallExternalInputCallbackFunctions(numOfRun, taskInfo, ptr, data1, data2, data3, M_ALLTASKOBJECT);
		}
		
		return -1;
	}

	/// Call the callback interfaces of Post-Task
	/// Return value(-1) means the Error of this function
	int CallALLPostTaskCallbackInterface(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
	{
		/*if(this->GetNumOfExternalOutputCallbackFunctions()>0)
			m_bEnableExternalOutputCallbackFuntions = true;
		else
			m_bEnableExternalOutputCallbackFuntions = false;*/

		if(this->m_bEnableExternalOutputCallbackFuntions)
		{
			return this->CallExternalOutputCallbackFunctions(numOfRun, taskInfo, ptr, data1, data2, data3, M_ALLTASKOBJECT);
		}
		
		return -1;
	}

	/// Send Data (Input Data-type) to Pre-MUSiiCTask class
	virtual int SendDataToPreTask(void* data)
	{
		if(data != NULL && this->m_bVPreOutputDATA_IF_Set)
		{
			return m_pVPreOutputDATA_IF_Set->Concurrent_push_back_ALL(RetrieveInputData(data));
		}
		return -1;
	}

	/// Send IGTL Message to Pre-MUSiiCTask class
	/// This function is virtual function.
	/// We have to re-implement this function on MUSIiCIODevice, and other MUSiiCTask classes (MUSiiCSyncCombine, MUSiiCSuncDataCollectot)
	/// To Do: cannon96
	virtual int SendIGTLMsgToPreTask(igtl::MessageBase::Pointer data)
	{
		if(data.IsNotNull() && this->m_bVPreOutputDATA_IF_Set && m_bUseIGTLMessage)
		{
			return 0;//m_pVPreOutputDATA_IF_Set->Concurrent_push_back_ALL(data);
		}
		return -1;
	}

	/// Send Data (Input Data-type) to Pre-MUSiiCTask class
	virtual int SendDataToPostTask(void* data)
	{
		if(data != NULL && this->m_bVPostOutputDATA_IF_Set)
		{
			return m_pVPostOutputDATA_IF_Set->Concurrent_push_back_ALL(RetrieveInputData(data));
		}
		return -1;
	}

	/// Send IGTL Message to Pre-MUSiiCTask class
	/// This function is virtual function.
	/// We have to re-implement this function on MUSIiCIODevice, and other MUSiiCTask classes (MUSiiCSyncCombine, MUSiiCSuncDataCollectot)
	/// To Do: cannon96
	virtual int SendIGTLMsgToPostTask(igtl::MessageBase::Pointer data)
	{
		if(data.IsNotNull() && this->m_bVPostOutputDATA_IF_Set && m_bUseIGTLMessage)
		{
			return 0;//m_pVPostOutputDATA_IF_Set->Concurrent_push_back_ALL(data);
		}
		return -1;
	}

	/// Retrieve Inpudata from void* data 
	/// This function is virtual function.
	/// We have to re-implement this function on MUSIiCIODevice, and other MUSiiCTask classes (MUSiiCSyncCombine, MUSiiCSuncDataCollectot)
	/// To Do: cannon96
	virtual InputData RetrieveInputData(void* data)
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << this->GetNameOfMUSiiCClass().c_str();

		InputData tempdata = *(InputData*)data;
		return tempdata;
	}

	/// Retrieve Outpudata from void* data
	/// This function is virtual function.
	/// We have to re-implement this function on MUSIiCIODevice, and other MUSiiCTask classes (MUSiiCSyncCombine, MUSiiCSuncDataCollectot)
	/// To Do: cannon96
	virtual OutputData RetrieveOutputData(void* data)
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << this->GetNameOfMUSiiCClass().c_str();

		OutputData tempdata = *(OutputData*)data;
		return tempdata;
	}


protected:///Attributes
	
	/// a pointer of MUSiiCVectorSet for Input Data interface for Pre-Task
	igtl::SmartPointer<igtl::MUSiiCVectorSet<InputData>>	m_pVPreInputDATA_IF_Set;
	// A boolean variable of MUSiiCVectorSet as Input-Interface
	bool													m_bVPreInputDATA_IF_Set;

	/// a pointer of MUSiiCVectorSet for Output Data interface for Pre-Task
	igtl::SmartPointer<igtl::MUSiiCVectorSet<InputData>>	m_pVPreOutputDATA_IF_Set;
	// A boolean variable of MUSiiCVectorSet as Input-Interface
	bool													m_bVPreOutputDATA_IF_Set;

	/// a pointer of MUSiiCVectorSet for Input Data interface for Post-Task
	igtl::SmartPointer<igtl::MUSiiCVectorSet<OutputData>>	m_pVPostInputDATA_IF_Set;
	// A boolean variable of MUSiiCVectorSet as Input-Interface
	bool													m_bVPostInputDATA_IF_Set;

	/// a pointer of MUSiiCVectorSet for Output Data interface for Post-Task
	igtl::SmartPointer<igtl::MUSiiCVectorSet<OutputData>>	m_pVPostOutputDATA_IF_Set;
	// A boolean variable of MUSiiCVectorSet as Input-Interface
	bool													m_bVPostOutputDATA_IF_Set;


	/// A Pointer of MUSiiCVector for SelfInputDataInterface
	igtl::SmartPointer<igtl::MUSiiCVector<InputData>>		m_pSelfPreInputDataInterface;
	// A boolean variable of SelfInputDataInterface
	bool													m_bSelfPreInputDataInterface;
	bool													m_bUseSelfPreInputDataInterface;


	/// A Pointer of MUSiiCVector for SelfInputDataInterface
	igtl::SmartPointer<igtl::MUSiiCVector<InputData>>		m_pSelfPreOutputDataInterface;
	// A boolean variable of SelfInputDataInterface
	bool													m_bSelfPreOutputDataInterface;
	bool													m_bUseSelfPreOutputDataInterface;


	/// Initialize Task Information
	int														m_iNumOfRun;
	int														m_iTaskInfo;
	void*													m_Ptr;
	igtl::MessageBase::Pointer								m_pData1; 
	void*													m_pData2; 
	void*													m_pData3;
	int														m_iTaskIndex;

	igtl::FastMutexLock::Pointer							m_pTaskControlMutex;

	bool													m_bUseIGTLMessage;

	
};
};
#endif
