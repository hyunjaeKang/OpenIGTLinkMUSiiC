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
#ifndef __MUSIIC_DATA_OBJECT_
#define __MUSIIC_DATA_OBJECT_




#include <igtlLightObject.h>
#include <igtlMacro.h>
#include <igtlObjectFactory.h>
#include "igtlM_win32header.h"
#include "MUSiiCIGTLUtil.h"

namespace igtl
{


class IGTLMCommon_EXPORT MUSiiCDataObject : public LightObject
{
public: // Operations
	typedef MUSiiCDataObject						Self;
	typedef LightObject								Superclass;
	typedef SmartPointer<Self>						Pointer;
	typedef SmartPointer<Self>						ConstPointer;
	
	/** Method for creation through the object factory. */
	igtlNewMacro(MUSiiCDataObject);
  
	/** Run-time type information (and related methods). */
	igtlTypeMacro(MUSiiCDataObject, LightObject);

	/// Constrcut
	MUSiiCDataObject();
	/// Deconstruct
	~MUSiiCDataObject();

	/// Get the name of Class
	std::string GetNameOfMUSiiCClass();

	/// Set IGTL Message as MUSiiCDataObject
	bool SetIGTLMessage(igtl::MessageBase::Pointer msg, bool ref = false);

	/// Get IGTL Message from MUSiiCDataObject
	igtl::MessageBase::Pointer GetIGTLMessage();

	/// Set this data-Object is Reference Data or not
	void SetReferenceData(bool ref = true);
	
	/// Check this data-Object is Reference Data or not
	bool IsReferenceData();





protected: // Operations
	virtual void Initialize();

public: // Attributes

protected: // Attributes
	/// Information of MusiicTask Class
	std::string					m_pNameOfClass;
	/// Message of OpenIGTLink/OpenIGTLinkMUSiiC
	igtl::MessageBase::Pointer  m_pMsg;
	/// A boolean value represent this data object is reference data or not
	bool						m_bReference;

};

} //end of namespace
#endif
