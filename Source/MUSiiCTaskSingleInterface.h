/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/

#ifndef __MUSICC_TASK_SINGLE_IF_
#define __MUSICC_TASK_SINGLE_IF_

#include "MUSiiCTaskInterfaceAbstract.h"
#include "MUSiiCVector.h"

namespace igtl
{

template<class Data> class IGTLMCommon_EXPORT MUSiiCTaskSingleInterface: public MUSiiCTaskInterfaceAbstract
{
public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCTaskSingleInterface<Data>	Self;
	typedef MUSiiCTaskInterfaceAbstract					Superclass;
	typedef SmartPointer<Self>							Pointer;
	typedef SmartPointer<const Self>					ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	//////////////////////////////////////////////////////////////////////////////
	/// Constructor
	MUSiiCTaskSingleInterface()
	{
		m_pNameOfClass="MUSiiCTaskSingleInterface";
		Initialize();
	}

	/// Deconstructor
	~MUSiiCTaskSingleInterface()
	{
	}

	/// Set MUSiiCVector<Data>as data interface
	bool SetDataInterface(igtl::MUSiiCVector<Data>* DataIF)//(igtl::MUSiiCVector<Data>::Pointer DataIF)
	{
		if(DataIF!=NULL)
		{
			m_pDATA_IF = DataIF;
			m_bDATA_IF = true;
		}
		return m_bDATA_IF;
	}

	/// Get MUSiiCVector<Data>as data interface 
	igtl::MUSiiCVector<Data>* GetDataInterface()
	{
		return m_bDATA_IF? m_pDATA_IF : NULL;
	}
	
	/// Check whether data-interface was setted?
	bool IsDataInterface()
	{
		return m_bDATA_IF;
	}

	/// Initialize DataQueue
	virtual bool InitializeDataIF()
	{
		if(m_bDATA_IF)
			m_pDATA_IF->concurrent_clear();

		return m_bDATA_IF;
	}
	
	/// Release DataQueue
	virtual bool ReleaseDataIF()
	{
		if(m_bDATA_IF)
			if(m_pDATA_IF->IsWaiting())
				m_pDATA_IF->EnforceRelease();

		return m_bDATA_IF;
	}
public:///Attributes
	
protected:///Operation
	/// Initialize Member variables
	virtual void Initialize()
	{
		MUSiiCTaskInterfaceAbstract::Initialize();
		m_bDATA_IF = false;
		m_pDATA_IF = NULL;	
	}
 	/// Initialize DataQueue
	virtual bool InitializeDataInterface()
	{
		if(m_bDATA_IF)
			m_pDATA_IF->concurrent_clear();
		
		return m_bDATA_IF;
	}
	/// Release DataQueue
	virtual bool ReleaseDataInterface()
	{
		if(m_bDATA_IF)
			if(m_pDATA_IF->IsWaiting())
				m_pDATA_IF->EnforceRelease();

		return m_bDATA_IF;
	}

protected:///Attributes
	/// a pointer of MUSiiCigtlMsgVector for data-Interface
	igtl::MUSiiCVector<Data>*					m_pDATA_IF;

	// A boolean variable of MUSiiCigtlMsgVector as data-Interface
	bool										m_bDATA_IF;

};
}
#endif