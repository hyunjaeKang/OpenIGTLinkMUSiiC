/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/
/*
#include "MUSiiCTaskSingleInterface.h"

namespace igtl
{
	/// Constructor
	MUSiiCTaskSingleInterface::MUSiiCTaskSingleInterface()
	{
		m_pNameOfClass="MUSiiCTaskSingleInterface";
		Initialize();
	}

	/// Deconstructor
	MUSiiCTaskSingleInterface::~MUSiiCTaskSingleInterface()
	{
	}

	/// Set MUSiiCigtlMsgVector as data interface
	bool MUSiiCTaskSingleInterface::SetigtlMsgInterface(igtl::MUSiiCigtlMsgVector::Pointer igtlmsgIF)
	{
		if(igtlmsgIF.IsNotNull())
		{
			m_pigtlMsg_IF = igtlmsgIF;
			m_bigtlMsg_IF = true;
		}
		return m_bigtlMsg_IF;
	}

	/// Get MUSiiCigtlMsgVector 
	igtl::MUSiiCigtlMsgVector::Pointer MUSiiCTaskSingleInterface::GetigtlMsgInterface()
	{
		return m_bigtlMsg_IF? m_pigtlMsg_IF : NULL;
	}

	/// Check whether data-interface was setted?
	bool MUSiiCTaskSingleInterface::Is_igtlMsgInterface()
	{
		return m_bigtlMsg_IF;
	}

////Protected function
	void MUSiiCTaskSingleInterface::Initialize()
	{
		MUSiiCTaskInterfaceAbstract::Initialize();
		m_bigtlMsg_IF = false;
		m_pigtlMsg_IF = NULL;	
	}

	/// Initialize igtlMsg_Interface (DataQueue)
	bool MUSiiCTaskSingleInterface::InitializeDataInterface()
	{
		if(m_bigtlMsg_IF)
			m_pigtlMsg_IF->concurrent_clear();
		
		return m_bigtlMsg_IF;
	}

	/// Release DataQueue
	bool MUSiiCTaskSingleInterface::ReleaseDataInterface()
	{
		if(m_bigtlMsg_IF)
			if(m_pigtlMsg_IF->IsWaiting())
				m_pigtlMsg_IF->EnforceRelease();

		return m_bigtlMsg_IF;
	}

}*/