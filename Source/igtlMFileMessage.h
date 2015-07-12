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


#ifndef __igtlFileMessage_h
#define __igtlFileMessage_h
/*=========================================================================
	igtl::FileMessage::Pointer fMsg = igtl::FileMessage::New();
	fMsg->ReadFile(const char* path);
	fMsg->Pack();
	
	fMsg->Unpack(1);
	fMsg->WriteFile(const char* path);
	
=========================================================================*/
#include "igtlMGenMessage.h"
namespace igtl
{
class IGTLMCommon_EXPORT FileMessage: public GenMessage
{
public:
	typedef FileMessage                  	Self;
	typedef GenMessage                   	Superclass;
	typedef SmartPointer<Self>            	Pointer;
	typedef SmartPointer<const Self>      	ConstPointer;

	igtlTypeMacro(igtl::FileMessage, igtl::GenMessage);
	igtlNewMacro(igtl::FileMessage);

	
public:
	int ReadFile(const char* path);
	int WriteFile(const char* path);
	void* GetFileBodyPointer();
	int GetFileSize(){return m_FileSize;}
	char* GetFileName(){return m_FileName;}
	
protected:
	FileMessage();
	~FileMessage();
	
	virtual int  	PackBody();
	virtual int  	UnpackBody();

	std::string GetFileNameFromPath(const char* path); 
	
	char m_FileName[256];
	//std::string 		m_Filename;
	int  m_FileSize;
	unsigned char* m_FileBody;
};
}
#endif // __igtlArgMessage_h