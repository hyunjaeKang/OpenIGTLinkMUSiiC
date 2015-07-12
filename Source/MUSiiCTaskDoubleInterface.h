/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/

#ifndef __MUSIIC_TASK_DOUBLE_IF_
#define __MUSIIC_TASK_DOUBLE_IF_

#include "MUSiiCTaskInterfaceAbstract.h"

namespace igtl
{
template<class InputData, class OutputData>
	class IGTLMCommon_EXPORT MUSiiCTaskDoubleInterface: public MUSiiCTaskInterfaceAbstract
{
public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCTaskDoubleInterface		Self;
	typedef MUSiiCTaskInterfaceAbstract		Superclass;
	typedef SmartPointer<Self>				Pointer;
	typedef SmartPointer<const Self>		ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(MUSiiCTaskDoubleInterface, MUSiiCTaskInterfaceAbstract);
	
	//////////////////////////////////////////////////////////////////////////////
	/// Constructor
	MUSiiCTaskDoubleInterface()
	{
		m_pNameOfClass="MUSiiCTaskDoubleInterface";
		Initialize();
	}

	/// Deconstructor
	~MUSiiCTaskDoubleInterface()
	{
	}

	////////////////////////////////////////////////////////////////////////////////
	/// Set MUSiiCVector<InputData> as data interface
	bool SetInputDataInterface(igtl::MUSiiCVector<InputData>* InputDATAIF)
	{
		if(InputDATAIF !=NULL)
		{
			const char* name = this->GetNameOfClass();
			m_pInputDATA_IF = InputDATAIF;
			m_bInputDATA_IF = true;
		}

		return m_bInputDATA_IF;
	}

	/// Get Input Data interface (MUSiiCVector<InputData>)
	igtl::MUSiiCVector<InputData>* GetInputDataInterface()
	{
		return m_bInputDATA_IF? m_pInputDATA_IF : NULL ;
	}

	/// Check Is there InputData Interface
	bool IsInputDataInterface()
	{
		return m_bInputDATA_IF;
	}

	/// Initialize Input Data Interface
	virtual bool InitializeInputDataInterface()
	{
		if(m_bInputDATA_IF)
			m_pInputDATA_IF->concurrent_clear();

		return m_bInputDATA_IF;
	}
	
	/// Release Output Data interface
	virtual bool ReleaseInputDataInterface()
	{
		if(m_bInputDATA_IF)
			if(m_pInputDATA_IF->IsWaiting())
				m_pInputDATA_IF->EnforceRelease();

		return m_bInputDATA_IF;
	}

	////////////////////////////////////////////////////////////////////////////////
	/// Set MUSiiCVector<OutputData> as data interface
	bool SetOutputDataInterface(igtl::MUSiiCVector<OutputData>* OutputDATAIF)
	{
		if(OutputDATAIF !=NULL)
		{
			m_pOutputDATA_IF = OutputDATAIF;
			m_bOutputDATA_IF = true;
		}

		return m_bOutputDATA_IF;
	}

	/// Get Input Data interface (MUSiiCVector<OutputData>)
	igtl::MUSiiCVector<OutputData>* GetOutputDataInterface()
	{
		return m_bOutputDATA_IF? m_pOutputDATA_IF : NULL ;
	}

	/// Check Is there InputData Interface
	bool IsOutputDataInterface()
	{
		return m_bOutputDATA_IF;
	}

	/// Initialize Input Data Interface
	virtual bool InitializeOutputDataInterface()
	{
		if(m_bOutputDATA_IF)
			m_pOutputDATA_IF->concurrent_clear();

		return m_bOutputDATA_IF;
	}
	
	/// Release Output Data interface
	virtual bool ReleaseOutputDataInterface()
	{
		if(m_bOutputDATA_IF)
			if(m_pOutputDATA_IF->IsWaiting())
				m_pOutputDATA_IF->EnforceRelease();

		return m_bOutputDATA_IF;
	}

public:///Attributes
	
protected:///Operation
	/// Initialize Member variables
	virtual void Initialize()
	{
		MUSiiCTaskInterfaceAbstract::Initialize();
		m_pInputDATA_IF		= NULL;
		m_bInputDATA_IF		= false;
		m_pOutputDATA_IF	= NULL;
		m_bOutputDATA_IF	= false;
	}

	/// Initialize DataQueue
	virtual bool InitializeDataIF()
	{
		return InitializeInputDataInterface() && InitializeOutputDataInterface();
	}
	
	/// Release DataQueue
	virtual bool ReleaseDataIF()
	{
		return ReleaseInputDataInterface() && ReleaseOutputDataInterface();
	}

protected:///Attributes
	/// a pointer of MUSiiCVector for Input Data interface
	igtl::MUSiiCVector<InputData>*		m_pInputDATA_IF;

	// A boolean variable of MUSiiCigtlMsgVector as Input-Interface
	bool								m_bInputDATA_IF;

	/// a pointer of MUSiiCVector with Input Data interface
	igtl::MUSiiCVector<OutputData>*		m_pOutputDATA_IF;

	// A boolean variable of MUSiiCigtlMsgVector as Output-Interface
	bool								m_bOutputDATA_IF;
};
} // end of namespace
#endif