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


#ifndef __igtlArgMessage_h
#define __igtlArgMessage_h
/*=========================================================================
	igtl::ArgMessage::Pointer argMsg = igtl::ArgMessage::New();
	argMsg->AddArgument(char* argument1);
	argMsg->AddArgument(char* argument2);
	argMsg->AddArgument(char* argument3);
	argMsg->AllocateArguments();
	argMsg->Pack();
	
	
	argMsg->Unpack(1);
	int sz = argMsg->GetNumOfArguments();
	char* arg1 = argMsg->GetArgument(0);
	char* arg2 = argMsg->GetArgument(1);
	char* arg3 = argMsg->GetArgument(2);
	
=========================================================================*/
#include "igtlMGenMessage.h"
#include <string>

namespace igtl
{
class IGTLMCommon_EXPORT ArgMessage: public GenMessage
{
public:
	typedef ArgMessage                  	Self;
	typedef GenMessage                   	Superclass;
	typedef SmartPointer<Self>            	Pointer;
	typedef SmartPointer<const Self>      	ConstPointer;

	igtlTypeMacro(igtl::ArgMessage, igtl::GenMessage);
	igtlNewMacro(igtl::ArgMessage);
	
public:
	void AddArgument(char* arg);
	void AllocateArguments();
	
	const char* GetArgument(int idx);
	std::string& GetArgments(){return m_Arguments;}
	int GetNumOfArguments(){return m_NumOfArg;}
	
protected:
	ArgMessage();
	~ArgMessage();
	
	virtual int  	PackBody();
	virtual int  	UnpackBody();
	
protected:
	std::string m_Arguments;
	std::vector<std::string> m_ArgumentList;
	int 	m_NumOfArg;
};

}
#endif // __igtlArgMessage_h