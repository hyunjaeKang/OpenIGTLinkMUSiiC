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


#include "igtlMFileMessage.h"
#include "igtl_header.h"
//#include "igtlMUSiiCutil/igtlM_FILE.h"
#include "igtlM_FILE.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




namespace igtl
{

FileMessage::FileMessage():
	GenMessage()
{
	memset(m_FileName, 0, 256);
	this->m_FileSize = 0;
	this->m_FileBody = NULL;
	this->m_DefaultBodyType = "FILE";
}

FileMessage::~FileMessage()
{
}

int FileMessage::ReadFile(const char* path)
{
	FILE* pFile;
	long lSize;
	char* buffer;
	size_t result;	

	///Get Current Directory
	/*char the_path[501];
    getcwd(the_path, 500);
	std::cerr << the_path << std::endl;*/

	pFile = fopen(path, "rb");
	//pFile = fopen("Test.txt", "rb");
	if(pFile == NULL) return -1;

	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	
	m_FileSize = lSize;

	///Get Filename from path
	memset(m_FileName, 0, IGTL_FILE_NAME_SIZE);
	strcpy(m_FileName, GetFileNameFromPath(path).c_str());

	/// Calculate the size of body

	int bodysize = m_FileSize + IGTL_FILE_HEADER_SIZE;
	
	// allocate memory to contain the whole file:
	buffer = (char*) malloc (sizeof(char)*bodysize); ///
	if (buffer == NULL) return -1;

	/// Tx::Packing the name of file
    memcpy(buffer, m_FileName, IGTL_FILE_NAME_SIZE);
    /// Tx::Packing the size of file
    memcpy(buffer+IGTL_FILE_NAME_SIZE, &m_FileSize, sizeof(int) );
	
	// copy the file into the buffer:
	result = fread (buffer+IGTL_FILE_HEADER_SIZE,1,lSize,pFile);
	if (result != lSize) return -1;

	/// File Name, File Size ?????
	AllocateData(buffer, bodysize);
	
	/// File Pointer 
	m_FileBody = m_DataBody + IGTL_FILE_HEADER_SIZE;

	// terminate
	fclose (pFile);
	free (buffer);

	return 1;
}


int FileMessage::WriteFile(const char* path)
{
	FILE * pFile;
	
	pFile = fopen(path, "wb");
	size_t result = fwrite( (unsigned char*) GetFileBodyPointer(), 1, m_FileSize, pFile);
	if(result != m_FileSize) return -1;
	fclose(pFile);
	
	return 1;
}

std::string FileMessage::GetFileNameFromPath(const char* path) 
{
    std::string s(path);
    return s.substr(s.find_last_of("/\\") + 1);
}

int FileMessage::PackBody()
{
	GenMessage::PackBody();
	
	return 1;
}

int FileMessage::UnpackBody()
{
	GenMessage::UnpackBody();
	
	memcpy(m_FileName, m_DataBody, IGTL_FILE_NAME_SIZE);
	memcpy(&m_FileSize, m_DataBody+IGTL_FILE_NAME_SIZE, sizeof(int));
	//strcpy(m_Filename,(char*) m_DataBody); 
	m_FileBody = m_DataBody + IGTL_FILE_HEADER_SIZE;
	return 1;
}

void* FileMessage::GetFileBodyPointer() 
{ 
	return m_FileBody;
}

}
