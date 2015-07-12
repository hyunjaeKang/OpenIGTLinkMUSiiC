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
#ifndef __MUSIIC_FILE_IO_ABSTRACT_
#define __MUSIIC_FILE_IO_ABSTRACT_


#include "MUSiiCIGTLIODevice.h"

namespace igtl
{

template<class FILEDATA> 
class IGTLMCommon_EXPORT MUSiiCFileIOAbstract : public MUSiiCIGTLIODevice
{

public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCFileIOAbstract<FILEDATA>				Self;
	typedef MUSiiCIGTLIODevice					Superclass;
	typedef SmartPointer<Self>					Pointer;
	typedef SmartPointer<const Self>			ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	/// Constructor
	MUSiiCFileIOAbstract()
	{
		MUSiiCTaskAbstract::m_pNameOfClass="MUSiiCFileIOAbstract";
		Initialize();	
	}
	
	/// Deconstructor
	~MUSiiCFileIOAbstract()
	{
	}

	/// Get File Mode
	int GetFileMode()
	{
		return m_FileMode;
	}

	/////////////////////////////////////////////////////////////////////////////////
	//////                             Reading File                        //////////
	
	/// Virtual Function
	/// Reading a Single file
	virtual FILEDATA ReadSingleFile(std::string filepath)
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "MUSiiCFileIOAbstract::ReadSingleFile";
		return NULL;
	}

	/// Reading a Single File with Callback Interface
	int ReadSingleFileCB(std::string filepath)
	{
		if(SetFilePath(filepath)>0)
		{
			this->SetEnableThread(false);
			m_iFileMode = M_READ_SINGLE_CB;
			return RunTask(1, m_iFileMode, this, NULL, NULL, NULL);
		}
		return -1;
	}

	/// Read Single File with Thread
	int ReadSingleFileTH(std::string filepath)
	{
		if(SetFilePath(filepath)>0)
		{
			this->SetEnableThread(true);
			m_iFileMode = M_READ_SINGLE_TH;
			return RunTask(1, m_iFileMode, this, NULL, NULL, NULL);
		}
		return -1;
	}

	/// Read Multiple files with Callback function
	int ReadMultiFilesCB(std::vector<std::string>& filepath_list)
	{	
		if(SetFilePathList(filepath_list)>0)
		{
			this->SetEnableThread(false);
			m_iFileMode = M_READ_MULTI_CB;
			return RunTask(1, m_iFileMode, this, NULL, NULL, NULL);
		}
		return -1;
	}

	/// Read Multiple files with Callback function and Thread
	int ReadMultiFilesTH(std::vector<std::string>& filepath_list)
	{
		if(SetFilePathList(filepath_list)>0)
		{
			this->SetEnableThread(true);
			m_iFileMode = M_READ_MULTI_TH;
			return RunTask(1, m_iFileMode, this, NULL, NULL, NULL);
		}
		return -1;
	}



	//////                             Reading File                        //////////
	/////////////////////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////////////////////
	//////                             Writing File                        //////////
	
	/// Virtual Function
	virtual int WriteSingleFile(FILEDATA filedata, std::string filepath)
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "MUSiiCFileIOAbstract::WriteSingleFile";
		
		return 0;
	}

	///Write single file with callback function
	int WriteSingleFileCB(FILEDATA data, std::string filepath)
	{
		if(SetDataFilePath(data, filepath)>0)
		{
			this->SetEnableThread(false);
			m_iFileMode = M_WRITE_SINGLE_CB;
			return RunTask(1, m_iFileMode, this, NULL, NULL, NULL);
		}
		return -1;
	}

	/// Write single file with Callback function and Thread
	int WriteSingleFileTH(FILEDATA data, std::string filepath)
	{
		if(SetDataFilePath(data, filepath)>0)
		{
			this->SetEnableThread(true);
			m_iFileMode = M_WRITE_SINGLE_TH;
			return RunTask(1, m_iFileMode, this, NULL, NULL, NULL);
		}
		return -1;
	}

	/// Write multiple files with Callback function
	int WriteMultiFilesCB(std::vector<FILEDATA>& data_list, std::vector<std::string>& filepath_list)
	{
		if(SetDataListSetFilePathList(data_list, filepath_list)>0)
		{
			this->SetEnableThread(false);
			m_iFileMode = M_WRITE_MULTI_CB;
			return RunTask(1, m_iFileMode, this, NULL, NULL, NULL);
		}
		return -1;
	}

	/// Write multiple files with Callback function and Thread
	int WriteMultiFilesTH(std::vector<FILEDATA>& datas, std::vector<std::string>& file_list)
	{
		if(SetDataListSetFilePathList(data_list, filepath_list)>0)
		{
			this->SetEnableThread(true);
			m_iFileMode = M_WRITE_MULTI_TH;
			return RunTask(1, m_iFileMode, this, NULL, NULL, NULL);
		}
		return -1;
	}

	////-----------------------------------------------------------------------////
	//// Writing a streaming data on hard disk
	int WriteStreamData(std::string name, bool drop = false)
	{
		m_sFilePath = name;
		m_bFileDrop = drop;
		this->SetEnableThread(true);
		m_iFileMode = M_WRITE_STREAM_DATA;
		return RunTask(M_THREAD_RUN_CONTINUOUS, m_iFileMode, this, NULL, NULL, NULL);
	}

	/// Stop Writing Streaming Data
	int WriteStreamDataStop()
	{
		m_iFileMode = M_WRITE_STREAM_DATA_DONE;
		this->StopTask();
		return FileIOPostProcessing(M_PRE_CONTROL_PRAR, m_iFileMode, this, NULL, NULL, NULL);
	}

	/// Resume Writing Streaming Data
	int WriteStreamDataResume()
	{
		m_iFileMode = M_WRITE_STREAM_DATA_RESUME;
		this->ResumeTaks();
		return FileIOPostProcessing(M_PRE_CONTROL_PRAR, m_iFileMode, this, NULL, NULL, NULL);
	}

	/// Pause Writing Streaming Data
	int WriteStreamDataPause()
	{
		m_iFileMode = M_WRITE_STREAM_DATA_PAUSE;
		this->PauseTaks();
		return FileIOPostProcessing(M_PRE_CONTROL_PRAR, m_iFileMode, this, NULL, NULL, NULL);
	}
	//////                             Writing File                        //////////
	/////////////////////////////////////////////////////////////////////////////////
	
	int PutInputData(FILEDATA const& data)
	{
		m_pVInputFileData->concurrent_push_back(data);
		m_bVInputFileData = m_pVInputFileData->concurrent_size() > 0 ? true: false;
	}
	
	/// Get InputData Buffer
	igtl::SmartPointer<igtl::MUSiiCVector<FILEDATA>> GetInputDataBuffer()
	{
		return m_pVInputFileData.IsNotNull() ? m_pVInputFileData : NULL;
	}


	///------------------------------------------------------------------------------
	/// Get Output Data Buffer
	igtl::SmartPointer<igtl::MUSiiCVector<FILEDATA>> GetOutputDataBuffer()
	{
		return m_pVOutputFileData.IsNotNull() ? m_pVOutputFileData : NULL;
	}
	

protected: ///Operation
	///////////////////////////////////////////////////////////////////
	/// Virtual Functions

	/// Initialize class memeber variables
	virtual void Initialize()
	{
		//////////////////////////////////////////////////////////////
		//// Vector Conatiner
		/// Input FileData container
		m_pVInputFileData			= igtl::MUSiiCVector<FILEDATA>::New();
		m_bVInputFileData			= false;
		m_pVInputFileData->concurrent_clear();
		/// Output FileData container
		m_pVOutputFileData			= igtl::MUSiiCVector<FILEDATA>::New();
		m_bVOutputFileData			= false;
		m_pVOutputFileData->concurrent_clear();

		///////////////////////////////////////////////////////////////
		////
		m_bConvertIGTLToFileData	= false;
		m_iFileMode					= 0;
		m_sFilePath					= "";
		m_vFileNameList.clear();
		m_bFileDrop					= false;
		m_bIGTLFileIO				= false;
	}

	//// Convert an IGTL Message (igtl::MessageBase::Pointer) to FileData structure
	virtual FILEDATA ConvertToFileData(igtl::MessageBase::Pointer msg)
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "MUSiiCFileIOAbstract::ConvertToFileData";
		return NULL;
	}

	//// Convert an FileData structure to IGTL Message (igtl::MessageBase::Pointer) 
	virtual igtl::MessageBase::Pointer ConvertToIGTLMsg(FILEDATA& data)
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "MUSiiCFileIOAbstract::ConvertToIGTLMsg";
		return NULL;
	}

	/// Reading Single File with callbackInterface or Thread
	virtual int _ReadFilesCB(int taskInfo)
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "MUSiiCFileIOAbstract::_ReadFilesCB";

		return 1;
	}
	
	/// Writing Single File with callbackInterface or Thread
	virtual int _WriteFilesCB(int taskInfo)
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "MUSiiCFileIOAbstract::_WriteFilesCB";

		return 1;
	}
	
	/// Writing Single File with callbackInterface or Thread
	virtual int _WriteStreamData(int taskInfo)
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "MUSiiCFileIOAbstract::_WriteStreamData";

		return 1;
	}
	
	//// Post processing function for File IO
	/// In General, 
	/// numOfRun : When using Data-Interface, this number indicate the index of new data in Data-Interface
	/// TaskInfo : The argument of this task
	/// ptr      : the pointer of caller class
	/// data1    : Data 
	/// data2    : the Time-stamp of the data
	/// data3    : the name of Data
	virtual int FileIOPostProcessing(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL,igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
	{
		if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "MUSiiCFileIOAbstract::FileIOPostProcessing";
		return 0;
	}
	/// Virtual Functions
	///////////////////////////////////////////////////////////////////

	
	///////////////////////////////////////////////////////////////////
	/// Virtual Functions

	//// Core Task function for File IO
	/// In General, 
	/// numOfRun : When using Data-Interface, this number indicate the index of new data in Data-Interface
	/// TaskInfo : The argument of this task
	/// ptr      : the pointer of caller class
	/// data1    : Data 
	/// data2    : the Time-stamp of the data
	/// data3    : the name of Data
	virtual int TaskFunction(int numOfRun= 0, int taskInfo = 0, void* ptr = NULL, igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL)
	{
		switch(taskInfo)
		{
		case M_READ_SINGLE_CB:
		case M_READ_SINGLE_TH:
		case M_READ_MULTI_CB:
		case M_READ_MULTI_TH:
			_ReadFilesCB(taskInfo);
			break;
		case M_WRITE_SINGLE_CB:
		case M_WRITE_SINGLE_TH:
		case M_WRITE_MULTI_CB:
		case M_WRITE_MULTI_TH:
			_WriteFilesCB(taskInfo);
			break;
		case M_WRITE_STREAM_DATA:
			_WriteStreamData(taskInfo);
			break;
		}
		return 1;
	}

	/// Virtual Functions
	///////////////////////////////////////////////////////////////////
	
	//// Set a given filepath as the member file name;
	int SetFilePath(std::string filepath, bool intialzie = true)
	{
		if(filepath.length()<3)
			return false;

		if(intialzie)
			m_vFileNameList.clear();

		m_vFileNameList.push_back(filepath);
		return m_vFileNameList.size();
	}

	/// Set a list of File path for multiple File IO
	int SetFilePathList(std::vector<std::string> filepath_list)
	{
		m_vFileNameList.clear();
		m_vFileNameList = filepath_list;
		return m_vFileNameList.size();
	}

	/// Set data and file-path for saving data
	int SetDataFilePath(FILEDATA data, std::string filepath, bool intialzie = true)
	{
		if(intialzie)
		{
			m_vFileNameList.clear();
			m_pVInputFileData->concurrent_clear();
		}

		if(data != NULL)
		{
			if(m_pVInputFileData->concurrent_push_back(data) > 0)
			{
				m_bVInputFileData = true;
				return SetFilePath(filepath,intialzie);
			}
		}
		return -1;
	}

	/// Set data and file-path for saving data
	int SetDataListSetFilePathList(std::vector<FILEDATA> data_list, std::vector<std::string> filepath_list)
	{
		{
			m_vFileNameList.clear();
			m_pVInputFileData->concurrent_clear();
		}

		int sz_data(data_list.size());
		int sz_path(filepath_list.size());

		if(sz_data <= sz_path)
		{
			for(int i=0; i<sz_data; i++)
				SetDataFilePath(data_list[i], filepath_list[i], false);

			return sz_data;
		}
		else //(sz_data > sz_path)
		{
			for(int i=0; i<sz_path; i++)
				SetDataFilePath(data_list[i], filepath_list[i], false);

			for(int j=sz_path; j< sz_data; j++)
			{
				std::stringstream ss;
				ss << j;
				SetDataFilePath(data_list[i],filepath_list[i]+ss.str(), false);
			}

			return sz_data;
		}
	}


public:/// Attributes
	

protected:/// Attributes
	//////////////////////////////////////////////////////////////
	//// Vector Conatiner
	/// Input FileData container
	igtl::SmartPointer<igtl::MUSiiCVector<FILEDATA>>	    m_pVInputFileData;
	bool												m_bVInputFileData;

	/// Output FileData container
	igtl::SmartPointer<igtl::MUSiiCVector<FILEDATA>>	    m_pVOutputFileData;
	bool												m_bVOutputFileData;

	bool												m_bConvertIGTLToFileData;
	int												m_iFileMode;
	std::string									    m_sFilePath;
	std::vector<std::string>							m_vFileNameList;
	bool												m_bFileDrop;
	bool												m_bIGTLFileIO;
};
}

#endif
