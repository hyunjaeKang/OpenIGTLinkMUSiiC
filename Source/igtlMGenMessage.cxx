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

#include <stdio.h>
#include <string.h>
#include "igtl_header.h"
#include "igtlMGenMessage.h"

namespace igtl
{

GenMessage::GenMessage():
	MessageBase()
{
	this->m_DataSize = 0;
	this->m_DataBody = NULL;
	this->m_DefaultBodyType = "GEN";
}

GenMessage::~GenMessage()
{
}

int GenMessage::GetBodyPackSize()
{
	return m_DataSize;
}

int GenMessage::PackBody()
{
	return 1;
}

int GenMessage::UnpackBody()
{
	m_DataSize = GetPackBodySize(); //This function is of MessageBase class.
	m_DataBody = m_Body; //Real Data Pointer
	
	return 1;
}

void GenMessage::AllocateData( void* src, int sz)
{
	m_DataSize = sz+1;
	AllocatePack(); //Allocated memory space for saving src data
	m_DataBody = this->m_Body;
	memcpy(m_DataBody, src, sz); //Copy Data to Message
	m_DataBody[sz] = 0;
}

}
