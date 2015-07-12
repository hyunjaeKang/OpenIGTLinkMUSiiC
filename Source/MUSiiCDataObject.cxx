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

#include "MUSiiCDataObject.h"

namespace igtl
{

	/// Constrcut
	MUSiiCDataObject::MUSiiCDataObject()
	{
		this->m_pNameOfClass = "MUSiiCDataObject";
	}

	/// Deconstrcut
	MUSiiCDataObject::~MUSiiCDataObject()
	{
	}

	/// Get the name of Class
	std::string MUSiiCDataObject::GetNameOfMUSiiCClass()
	{
		return m_pNameOfClass;
	}

	/// Set IGTL Message as MUSiiCDataObject
	bool MUSiiCDataObject::SetIGTLMessage(igtl::MessageBase::Pointer msg, bool ref)
	{
		if(msg.IsNotNull())
		{
			m_pMsg = msg;
			m_bReference = ref;
			return true;
		}
		else
			return false;
	}

	/// Get IGTL Message from MUSiiCDataObject
	igtl::MessageBase::Pointer MUSiiCDataObject::GetIGTLMessage()
	{
		return m_pMsg.IsNotNull()? m_pMsg : NULL;
	}

	/// Set this data-Object is Reference Data or not
	void MUSiiCDataObject::SetReferenceData(bool ref)
	{
		m_bReference = ref;
	}

	
	/// Check this data-Object is Reference Data or not
	bool MUSiiCDataObject::IsReferenceData()
	{
		return m_bReference;
	}

////protected: operations
	void MUSiiCDataObject::Initialize()
	{
		this->m_pMsg       = NULL;
		this->m_bReference = false;
	}

}