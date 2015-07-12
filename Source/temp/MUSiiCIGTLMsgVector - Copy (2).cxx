/***************************************************************************
Copyright Dec/2010
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/

#include "MUSiiCIGTLMsgVector.h"

namespace igtl
{
	MUSiiCIGTLMsgVector::MUSiiCIGTLMsgVector()
	{
		this->m_Description = "MUSiiCIGTLMsgVector";
	}
	
	MUSiiCIGTLMsgVector::~MUSiiCIGTLMsgVector()
	{
		this->EnforceRelease();
	}
}