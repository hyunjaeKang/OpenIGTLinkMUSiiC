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
#include "igtlMArgMessage.h"
#include "igtl_header.h"

namespace igtl
{
ArgMessage::ArgMessage():
	GenMessage()
{
	m_Arguments.clear();
	m_ArgumentList.clear();
	m_NumOfArg = 0;
	this->m_DefaultBodyType = "ARGUMENTS";

}

ArgMessage::~ArgMessage()
{
}

void ArgMessage::AddArgument(char* arg)
{
	std::string a = arg;
	m_ArgumentList.push_back(a);
	m_NumOfArg = m_ArgumentList.size();
}

void ArgMessage::AllocateArguments()
{
	int i;
	for( i=0; i<m_NumOfArg-1 ; i++)
	{
		m_Arguments += m_ArgumentList[i];
		m_Arguments += " ";
	}
	
	m_Arguments += m_ArgumentList[i];
	
	AllocateData((void*)m_Arguments.c_str(), m_Arguments.size());
}

int ArgMessage::PackBody()
{
	GenMessage::PackBody();
	
	return 1;
}

int ArgMessage::UnpackBody()
{
	GenMessage::UnpackBody();
	
	m_Arguments = (char*) m_DataBody;
	char* pch;
	pch = strtok ((char*) m_Arguments.c_str()," ");
	while (pch != NULL)
	{
		AddArgument(pch);
		pch = strtok (NULL, " ");
	}
	
	return 1;
}

const char* ArgMessage::GetArgument(int idx)
{
	if(idx > m_NumOfArg)
		return " ";
	else
		return m_ArgumentList[idx].c_str();
}


}
