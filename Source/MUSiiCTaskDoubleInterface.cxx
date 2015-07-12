/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/

#include "MUSiiCTaskDoubleInterface.h"

namespace igtl
{
	// Constructor
	MUSiiCTaskDoubleInterface::MUSiiCTaskDoubleInterface()
		:m_bigtlMsg_IN_IF(false),
		m_bigtlMsg_OUT_IF(false)
	{
		MUSiiCTaskInterfaceAbstract::MUSiiCTaskInterfaceAbstract();
		m_pNameOfClass="MUSiiCTaskDoubleInterface";
	}

	/// Deconstructor
	MUSiiCTaskDoubleInterface::~MUSiiCTaskDoubleInterface()
	{
		MUSiiCTaskInterfaceAbstract::~MUSiiCTaskInterfaceAbstract(); 
	}

	/// Set MUSiiCigtlMsgVector as data interface
	bool MUSiiCTaskDoubleInterface::SetInputigtlMsgIF(igtl::MUSiiCigtlMsgVector::Pointer igtlmsgIF)
	{
		if(igtlmsgIF.IsNotNull())
		{
			m_igtlMsg_IN_IF = igtlmsgIF;
			m_bigtlMsg_IN_IF = true;
		}
		return m_bigtlMsg_IN_IF;
	}

	/// Set MUSiiCigtlMsgVector as data interface
	bool MUSiiCTaskDoubleInterface::GetInputigtlMsgIF(igtl::MUSiiCigtlMsgVector::Pointer igtlmsgIF)
	{
		if(m_bigtlMsg_IN_IF)
			igtlmsgIF = m_igtlMsg_IN_IF;

		return m_bigtlMsg_IN_IF;
	}
	
	/// Check whether data-interface was setted?
	bool MUSiiCTaskDoubleInterface::Is_InputigtlMsg_IF()
	{
		return m_bigtlMsg_IN_IF;
	}

	/// Set MUSiiCigtlMsgVector as data interface
	bool MUSiiCTaskDoubleInterface::SetOutputigtlMsgIF(igtl::MUSiiCigtlMsgVector::Pointer igtlmsgIF)
	{
		if(igtlmsgIF.IsNotNull())
		{
			m_igtlMsg_OUT_IF = igtlmsgIF;
			m_bigtlMsg_OUT_IF = true;
		}
		return m_bigtlMsg_OUT_IF;
	}

	/// Set MUSiiCigtlMsgVector as data interface
	bool MUSiiCTaskDoubleInterface::GetOutputigtlMsgIF(igtl::MUSiiCigtlMsgVector::Pointer igtlmsgIF)
	{
		if(m_bigtlMsg_OUT_IF)
			igtlmsgIF = m_igtlMsg_OUT_IF;

		return m_bigtlMsg_OUT_IF;
	}
	
	/// Check whether data-interface was setted?
	bool MUSiiCTaskDoubleInterface::Is_OutputigtlMsg_IF()
	{
		return m_bigtlMsg_OUT_IF;
	}

	/// Initialize Input-DataQueue
	bool MUSiiCTaskDoubleInterface::InitializeInputDataQueue()
	{
		if(m_bigtlMsg_IN_IF)
			m_igtlMsg_IN_IF->concurrent_clear();
		
		return m_bigtlMsg_IN_IF;
	}
	/// Release Input-DataQueue
	bool MUSiiCTaskDoubleInterface::ReleaseInputDataQueue()
	{
		if(m_bigtlMsg_IN_IF)
			if(m_igtlMsg_IN_IF->IsWaiting())
				m_igtlMsg_IN_IF->EnforceRelease();

		return m_bigtlMsg_IN_IF;
	}

	/// Initialize Output-DataQueue
	bool MUSiiCTaskDoubleInterface::InitializeOutputDataQueue()
	{
		if(m_bigtlMsg_OUT_IF)
			m_igtlMsg_OUT_IF->concurrent_clear();
		
		return m_bigtlMsg_OUT_IF;

	}
	/// Release Output-DataQueue
	bool MUSiiCTaskDoubleInterface::ReleaseOutputDataQueue()
	{
		if(m_bigtlMsg_OUT_IF)
			if(m_igtlMsg_OUT_IF->IsWaiting())
				m_igtlMsg_OUT_IF->EnforceRelease();

		return m_bigtlMsg_OUT_IF;
	}

	/// Initialize DataQueue
	bool MUSiiCTaskDoubleInterface::InitializeDataQueue()
	{
		return  InitializeInputDataQueue()&&InitializeOutputDataQueue();
	}
	/// Release DataQueue
	bool MUSiiCTaskDoubleInterface::ReleaseDataQueue()
	{
		return ReleaseInputDataQueue()&&ReleaseOutputDataQueue();
	}
}