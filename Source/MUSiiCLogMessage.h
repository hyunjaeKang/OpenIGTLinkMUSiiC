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

#ifndef __MUSiiCLOGMANAGER__
#define __MUSiiCLOGMANAGER__


#include "MUSiiCTime.h"

enum TLogLevel{ logERROR, logWARNING, logINFO, logDEBUG, logDEBUG1, logDEBUG2, logDEBUG3, logDEBUG4};

class MUSiiCOutput2File
{
public:
	MUSiiCOutput2File(std::string logFileName = "")
	{
		/*FILE* pFile = fopen(logFileName.c_str(), "a");
		this->Stream() = pFile;*/
	}

	static FILE*& Stream()
	{
		static FILE* pStream = stderr;
		return pStream;
	}

	static void Output(const std::string& msg)
	{
		FILE* pStream = Stream();
		if(!pStream)
			return;
		std::fprintf(pStream, "%s", msg.c_str());
		std::fflush(pStream);
	}
};


template <typename T>
class MUSiiCLog
{
public:
	/// Constructor
	MUSiiCLog()
	{
		/*FILE* pFile = fopen("MUSiiCLogFile.log", "a");
		MUSiiCOutput2File::Stream() = pFile;*/
	}
	/// Deconstructor
	virtual ~MUSiiCLog()
	{
		os << std::endl;
		T::Output(os.str());
	}

	std::ostringstream& Get(TLogLevel level = logINFO)
	{
		os << "Function Name" << __FUNCTION__ << ", Line:" << __LINE__<<std::endl;

		os << "   " << ToString(level) << ":  ";
		os << "-" << igtl::GetNowTimeString();
		os <<std::string(level > logDEBUG ? level - logDEBUG : 0, '\t');
		return os;
	}

	std::ostringstream& GetDebug(char* file, char* function, long line, TLogLevel level = logINFO)
	{
		
		os << "File: " << file << std::endl; 
		os << "Function: " << function << ", Line: " << line << std::endl; 
		os << "   " << ToString(level) << ":  ";
		os << "-" << igtl::GetNowTimeString();
		os <<std::string(level > logDEBUG ? level - logDEBUG : 0, '\t');
		return os;
	}

	std::ostringstream& Get3(char* file, char* function, long line, TLogLevel level = logINFO)
	{
		
		switch(level)
		{
		case logDEBUG:
		case logDEBUG1:
		case logDEBUG2:
		case logDEBUG3:
		case logDEBUG4:
		case logERROR:
			os << "File: " << file << std::endl; 
			os << "Function: " << function << ", Line: " << line << ", Error is detected." << std::endl; 
			break;
		}

		os << "* " << ToString(level) << ":  ";
		os << "- " << igtl::GetNowTimeString() << "  ";
		os <<std::string(level > logDEBUG ? level - logDEBUG : 0, '\t');
		return os;
	}

public:
	static TLogLevel& ReportingLevel()
	{
		static TLogLevel reportingLevel = logDEBUG4;
		return reportingLevel;
	}

	static std::string ToString(TLogLevel level)
	{
		static const char* const buffer[] = { "ERROR",
			"WARNING", "INFO", "DEBUG", "DEBUG1",
			"DEBUG2", "DEBUG3", "DEBUG4"};
		return buffer[level];
	}
	
	static TLogLevel FromString(const std::string& level)
	{
		if(level == "DEBUG4")  return logDEBUG4;
		if(level == "DEBUG3")  return logDEBUG3;
		if(level == "DEBUG2")  return logDEBUG2;
		if(level == "DEBUG1")  return logDEBUG1;
		if(level == "DEBUG")   return logDEBUG;
		if(level == "INFO")    return logINFO;
		if(level == "WARNING") return logWARNING;
		if(level == "ERROR")   return logERROR;

		MUSiiCLog<T>().Get(logWARNING) << "Unknow logging level'" << level << " ', Using INFO level as default.";
		return logINFO;
	}

protected:
	std::ostringstream os;

private:
	MUSiiCLog(const MUSiiCLog&);
	MUSiiCLog& operator =(const MUSiiCLog&);
};

typedef MUSiiCLog<MUSiiCOutput2File> MUSiiCLogManager;

#ifndef FILELOG_MAX_LEVEL
#define FILELOG_MAX_LEVEL logDEBUG4
#endif //FILELOG_MAX_LEVEL

#define MUSiiC_LOG1(level) \
	if(level > FILELOG_MAX_LEVEL) ; \
	else if (level > MUSiiCLogManager::ReportingLevel() || !MUSiiCOutput2File::Stream());\
	else MUSiiCLogManager().Get(level)

#define MUSiiC_LOG2(level) \
	if(level > FILELOG_MAX_LEVEL) ; \
	else if (level > MUSiiCLogManager::ReportingLevel() || !MUSiiCOutput2File::Stream());\
	else MUSiiCLogManager().GetDebug(__FILE__, __FUNCTION__ , __LINE__ , level)

#define MUSiiC_LOG(level) \
	if(level > FILELOG_MAX_LEVEL) ; \
	else if (level > MUSiiCLogManager::ReportingLevel() || !MUSiiCOutput2File::Stream());\
	else MUSiiCLogManager().Get3((char*)__FILE__, (char*)__FUNCTION__ , __LINE__ , level)


#endif //__MUSiiCLOGMANAGER__