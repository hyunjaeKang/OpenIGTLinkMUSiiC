/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/
/*
#include "MUSiiCFileIOAbstract.h"

namespace igtl
{
	/// Constructor
	MUSiiCFileIOAbstract::MUSiiCFileIOAbstract()	
	{
		m_pNameOfClass="MUSiiCFileIOAbstract";
		Initialize();
	}
	
	/// Deconstructor
	MUSiiCFileIOAbstract::~MUSiiCFileIOAbstract()
	{
		//MUSiiCIODevice::~MUSiiCIODevice();
	}

	/// Set File Mode
	void MUSiiCFileIOAbstract::SetFileMode(MUSiiC_FILE_MODE filemode)
	{
		m_FileMode = filemode;
	}

	/// Get File Mode
	MUSiiC_FILE_MODE MUSiiCFileIOAbstract::GetFileMode()
	{
		return m_FileMode;
	}

	///Read Multiple Files
	int MUSiiCFileIOAbstract::ReadMultipleFiles(std::list<std::string>& file_list)
	{
		m_sFileList.clear();
		m_sFileList = file_list;

		m_FileMode = M_FILE_READ;
		
		int s = RunTask(false);
		
		WaitTask();
		
		return s;
	}

	///Read Single File
	int MUSiiCFileIOAbstract::ReadSingleFile(std::string& filepath)
	{
		m_sFileList.clear();
		m_sFileList.push_back(filepath);

		m_FileMode = M_FILE_READ;
		
		int s = RunTask(false);
		
		WaitTask();
		
		return s;
	}

	///Write Multiple Files
	int MUSiiCFileIOAbstract::WriteMultipleFiles(std::list<std::string>& file_list, bool pop)
	{
		m_sFileList.clear();
		m_sFileList = file_list;

		m_FileMode = M_FILE_WRITE;

		m_bFilePop = pop;
		
		int s = RunTask(false);
		
		WaitTask();
		
		return s;
	}

	///Write Single File
	int MUSiiCFileIOAbstract::WriteSingleFile(std::string& filepath, bool pop)
	{
		m_sFileList.clear();
		m_sFileList.push_back(filepath);

		m_FileMode = M_FILE_WRITE;

		m_bFilePop = pop;
		
		int s = RunTask(false);
		
		WaitTask();
		
		return s;
	}


	//////////////////////////////////////////////////////
	/// Protected operation
	void MUSiiCFileIOAbstract::Initialize()
	{
		MUSiiCIODevice::Initialize();

		m_FileMode = M_FILE_READ;
		m_bFilePop = true;
		m_sFileList.clear();
		m_IODevice_Type = M_FILE_IO;
	}

	/// Thread-function was implemented in this function
	int MUSiiCFileIOAbstract::TaskFunction(void* ptr, void* data1, void* data2, void* data3,int v)
	{
		switch(m_FileMode)
		{
			case M_FILE_READ:
				ReadFiles();
				break;
			case M_FILE_WRITE:
				WriteFiles(false);
				break;
			case M_MULIT_FILES_WRITE:
				WriteFiles(true);
				break;
			default:
				break;
		}

		/// Call the pre-defined callback function for notify when File-IO is finished
		return MUSiiCTaskInterfaceAbstract::Task();
	}
	/// To handle multiple files
	int MUSiiCFileIOAbstract::ReadFiles()
	{
		/// Check there is interface or not.
		if(!m_bigtlMsg_IF) return -1;
		
		/// Check ths size of the list-container that contains file-paths
		int s;
		s = m_sFileList.size();
		if(s <= 0 ) return -1;

		std::list<std::string>::iterator it;

		std::string temp_file_path;

		for(it=m_sFileList.begin(); it !=m_sFileList.end(); ++it)
		{
			temp_file_path = *it;
			if(ReadFile(temp_file_path.c_str()) < 0)
				return -1;
		}

		return s;
	}
	/// Core function for reading file 
	int MUSiiCFileIOAbstract::ReadFile(const char* filepath)
	{
		return 1;
	}
	/// To handle multiple files
	int MUSiiCFileIOAbstract::WriteFiles(bool multiple)
	{
		/// Check there is interface or not.
		if(!m_bigtlMsg_IF) return -1;
		
		/// Check ths size of the list-container that contains file-paths
		int s;
		s = m_sFileList.size();
		if(s <= 0 ) return -1;

		std::string temp_file_path;

		if(multiple)
		{
			/// Discrecte File Saving Mode
			/// We need the size of Interface at this time
			s = m_pigtlMsg_IF->concurrent_size();
			
			for(int i=0; i<s; i++)
			{
				char index[3];
				sprintf(index, "%3d", i);
				temp_file_path =  index + m_sFileList.front();
				if(WriteFile(temp_file_path.c_str(), m_bFilePop, i) < 0)
					return -1;
			}
		}
		else
		{
			temp_file_path =  m_sFileList.front();
			s = WriteFile(temp_file_path.c_str(), m_bFilePop, 0);
		}

		return s;
	}
	
	/// Core function for writing file
	int MUSiiCFileIOAbstract::WriteFile(const char* filepath, bool pop, int idx)
	{
		return 1;
	}

}*/