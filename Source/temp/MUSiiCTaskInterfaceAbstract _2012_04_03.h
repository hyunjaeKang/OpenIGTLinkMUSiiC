/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/

#ifndef __MUSIIC_TASK_IF_ABSTRACT_
#define __MUSIIC_TASK_IF_ABSTRACT_

#include "MUSiiCTaskAbstract.h"
#include "MUSiiCVector.h"

namespace igtl
{

template<class InputData, class OutputData>
class IGTLMCommon_EXPORT MUSiiCTaskInterfaceAbstract: public MUSiiCTaskAbstract
{
public: ///Operation
	/** Standard class typedefs. */
	//typedef MUSiiCTaskInterfaceAbstract<InputData, OutputData>	Self;
	typedef MUSiiCTaskInterfaceAbstract	                        Self;
	typedef MUSiiCTaskAbstract			                        Superclass;
	typedef SmartPointer<Self>			                        Pointer;
	typedef SmartPointer<const Self>	                        ConstPointer;
	
	typedef igtl::MUSiiCVector<InputData>*                      PInputDataIF;
	typedef igtl::MUSiiCVector<OutputData>*                     POutputDataIF;

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
		Initialize();
	}

	/////////////////////////////////////////////////////////////////////////////
	///// Input Data Interface Set    ///////////////////////////////////////////

	//// Add Input Data-Interface
	//// return: ID of added input data-interface
	int AddInputDataInterface(igtl::MUSiiCVector<InputData>*  pInputDataIF)
	{
		int s(0);
		s = m_pMvInputDATA_IF.concurrent_push_back(pInputDataIF);
		m_bMvInputDATA_IF = s>0 ? true: false;
		return m_pMvInputDATA_IF.concurrent_size()-1;
	}

	/// Get Input Data Interface
	igtl::MUSiiCVector<InputData>* GetInputDataInterface(int index = M_SELFDATAINTERFACE)
	{
		int s(m_pMvInputDATA_IF.concurrent_size());
		PInputDataIF tempIF = NULL;
		if( (m_bMvInputDATA_IF && index < s) || index == M_SELFDATAINTERFACE )
		{
			if(index == M_SELFDATAINTERFACE || index ==0)
				m_pMvInputDATA_IF.concurrent_try_get(tempIF, 0);
			else
				m_pMvInputDATA_IF.concurrent_try_get(tempIF, index);
		}

		return tempIF;
	}

	/// Check Is there InputData Interface
	bool IsInputDataInterface()
	{
		return m_bMvInputDATA_IF;
	}

	/// Initialize Input DataInterfaces 
	virtual bool InitializeInputDataInterface(int index = M_ALLDATAINTERFACE)
	{
		int s(m_pMvInputDATA_IF.concurrent_size());
		
		if( (m_bMvInputDATA_IF && index < s) || index == M_ALLDATAINTERFACE || index == M_SELFDATAINTERFACE )
		{
			if(index == M_ALLDATAINTERFACE)
				for(int i=0; i<s; i++)
					_InitializeInputDataInterface(i);
			else if(index == M_SELFDATAINTERFACE || index == 0)
				_InitializeInputDataInterface(0);
			else
				_InitializeInputDataInterface(index);

			return true;
		}
		else
			return false;
	}

	/// Remove an input interface from this class
	int RemoveInputDataInterface(igtl::MUSiiCVector<InputData>*  pInputDataIF)
	{
		int id(m_pMvInputDATA_IF.concurrent_GetID(pInputDataIF));
		if(ReleaseInputDataInterface(id))
			return m_pMvInputDATA_IF.concurrent_erase_element(id);
		else
			return -1;
	}
	
	/// Remove all Input Data-Interface 
	virtual bool ClearInputDataInterfaceSet()
	{
		if(ReleaseInputDataInterface(M_ALLDATAINTERFACE))
		{
			m_pMvInputDATA_IF.concurrent_clear();
			m_bMvInputDATA_IF = false;
			return true;
		}
		else
			return false;
	}

	/// Initialize Input DataInterfaces 
	virtual bool ReleaseInputDataInterface(int index = M_ALLDATAINTERFACE)
	{
		int s(m_pMvInputDATA_IF.concurrent_size());
		if( (m_bMvInputDATA_IF && index < s) || index == M_ALLDATAINTERFACE || index == M_SELFDATAINTERFACE )
		{
			if(index == M_ALLDATAINTERFACE)
				for(int i=0; i<s; i++)
					_ReleaseInputDataInterface(i);
			else if(index == M_SELFDATAINTERFACE || index == 0)
				_ReleaseInputDataInterface(0);
			else
				_ReleaseInputDataInterface(index);

			return true;
		}
		else
			return false;
	}

	///// Input Data Interface Set    ///////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	///// Output Data Interface    ////////////////////////////////////////////////////
	//// Add Input Data-Interface
	//// return: ID of added input data-interface
	int AddOutputDataInterface(igtl::MUSiiCVector<OutputData>*  pOutputDataIF)
	{
		int s(0);
		s = m_pMvOutputDATA_IF.concurrent_push_back(pOutputDataIF);
		m_bMvOutputDATA_IF = s>0 ? true: false;
		return m_pMvOutputDATA_IF.concurrent_size()-1;
	}

	/// Get Input Data Interface
	igtl::MUSiiCVector<OutputData>* GetOutputDataInterface(int index = M_SELFDATAINTERFACE)
	{
		int s(m_pMvOutputDATA_IF.concurrent_size());
		POutputDataIF tempIF = NULL;
		
		if( (m_bMvOutputDATA_IF && index < s) || index == M_SELFDATAINTERFACE )
		{
			if(index == M_SELFDATAINTERFACE || index ==0)
				m_pMvOutputDATA_IF.concurrent_try_get(tempIF, 0);
			else
				m_pMvOutputDATA_IF.concurrent_try_get(tempIF, index);
		}

		return tempIF;
	}

	/// Check Is there InputData Interface
	bool IsOutputDataInterface()
	{
		return m_bMvOutputDATA_IF;
	}

	/// Initialize Input DataInterfaces 
	virtual bool InitializeOutputDataInterface(int index = M_ALLDATAINTERFACE)
	{
		int s(m_pMvOutputDATA_IF.concurrent_size());
		
		if( (m_bMvOutputDATA_IF && index < s) || index == M_ALLDATAINTERFACE || index == M_SELFDATAINTERFACE )
		{
			if(index == M_ALLDATAINTERFACE)
				for(int i=0; i<s; i++)
					_InitializeOutputDataInterface(i);
			else if(index == M_SELFDATAINTERFACE || index == 0)
				_InitializeOutputDataInterface(0);
			else
				_InitializeOutputDataInterface(index);

			return true;
		}
		else
			return false;
	}

	/// Remove an input interface from this class
	int RemoveOutputDataInterface(igtl::MUSiiCVector<InputData>*  pOutputDataIF)
	{
		int id(m_pMvOutputDATA_IF.concurrent_GetID(pOutputDataIF));
		if(ReleaseOutputDataInterface(id))
			return m_pMvOutputDATA_IF.concurrent_erase_element(id);
		else
			return -1;
	}
	
	/// Remove all Input Data-Interface 
	virtual bool ClearOutputDataInterfaceSet()
	{
		if(ReleaseOutputDataInterface(M_ALLDATAINTERFACE))
		{
			m_pMvOutputDATA_IF.concurrent_clear();
			m_bMvOutputDATA_IF = false;
			return true;
		}
		else
			return false;
	}

	/// Initialize Input DataInterfaces 
	virtual bool ReleaseOutputDataInterface(int index = M_ALLDATAINTERFACE)
	{
		int s(m_pMvOutputDATA_IF.concurrent_size());
		if( (m_bMvOutputDATA_IF && index < s) || index == M_ALLDATAINTERFACE || index == M_SELFDATAINTERFACE )
		{
			if(index == M_ALLDATAINTERFACE)
				for(int i=0; i<s; i++)
					_ReleaseOutputDataInterface(i);
			else if(index == M_SELFDATAINTERFACE || index == 0)
				_ReleaseOutputDataInterface(0);
			else
				_ReleaseOutputDataInterface(index);

			return true;
		}
		else
			return false;
	}

	///// Output Data Interface    ////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	///// Data Interface    ////////////////////////////////////////////////////
	virtual bool InitializeALLDataInterface()
	{
		return this->InitializeInputDataInterface() && this->InitializeOutputDataInterface();
	}

	virtual bool ReleaseALLDataInterface()
	{
		return this->ReleaseInputDataInterface() && this->ReleaseOutputDataInterface();
	}
	///// Data Interface    ////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////
	///////// Task Function //////////////////////////////////////////////////////
	/// Run the task funtion with/without thread
	virtual int RunTask(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL, void* data1 = NULL, void* data2 = NULL, void* data3 = NULL, int index = M_SELFTASKOBJECT)
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
	

public:///Attributes
	enum
	{
		M_SELFDATAINTERFACE = 9600,
		M_ALLDATAINTERFACE  = 9601,
	};

protected:///Operation
	/// Initialize Member variables
	virtual void Initialize()
	{
		/// Initialize Input interface
		m_pMvInputDATA_IF.concurrent_clear();
		m_bMvInputDATA_IF			= false;

		/// Initialize Output interface
		m_pMvOutputDATA_IF.concurrent_clear();
		m_bMvOutputDATA_IF			 = false;

		/// Initialize Task Information
		m_iNumOfRun				    = 0;
		m_iTaskInfo				    = 0;
		m_Ptr					    = NULL;
		m_pData1					= NULL; 
		m_pData2					= NULL; 
		m_pData3					= NULL;
		m_iTaskIndex				= 0;
	}

	//// Release Input Data-Interface
	void _ReleaseInputDataInterface(int index)
	{
		PInputDataIF tempIF;
		m_pMvInputDATA_IF.concurrent_try_get(tempIF, index);
		if(tempIF)
			if(tempIF->IsWaiting())
				tempIF->EnforceRelease();
	}

	//// Initialize Input Data-Interface
	void _InitializeInputDataInterface(int index)
	{
		_ReleaseInputDataInterface(index);
		
		PInputDataIF tempIF;
		m_pMvInputDATA_IF.concurrent_try_get(tempIF, index);
		if(tempIF)
			tempIF->concurrent_clear();
	}

	//// Release Input Data-Interface
	void _ReleaseOutputDataInterface(int index)
	{
		POutputDataIF tempIF;
		m_pMvOutputDATA_IF.concurrent_try_get(tempIF, index);
		if(tempIF)
			if(tempIF->IsWaiting())
				tempIF->EnforceRelease();
	}

	//// Initialize Input Data-Interface
	void _InitializeOutputDataInterface(int index)
	{
		_ReleaseOutputDataInterface(index);
		
		POutputDataIF tempIF;
		m_pMvOutputDATA_IF.concurrent_try_get(tempIF, index);
		if(tempIF)
			tempIF->concurrent_clear();
	}

protected:///Attributes
	
	/// a pointer of MUSiiCVector for Input Data interface
	igtl::MUSiiCVector<PInputDataIF>		        m_pMvInputDATA_IF;
	// A boolean variable of MUSiiCigtlMsgVector as Input-Interface
	bool								            m_bMvInputDATA_IF;

	/// a pointer of MUSiiCVector with Output Data interface
	igtl::MUSiiCVector<POutputDataIF>		        m_pMvOutputDATA_IF;
	// A boolean variable of MUSiiCigtlMsgVector as Output-Interface
	bool								            m_bMvOutputDATA_IF;

	/// Initialize Task Information
	int                                             m_iNumOfRun;
	int                                             m_iTaskInfo;
	void*                                           m_Ptr;
	void*                                           m_pData1; 
	void*                                           m_pData2; 
	void*                                           m_pData3;
	int                                             m_iTaskIndex;
};
};
#endif
