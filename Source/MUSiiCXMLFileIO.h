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
#ifndef __MUSIIC_XML_FILE_IO_
#define __MUSIIC_XML_FILE_IO_

#include "MUSiiCFileIOAbstract.h"
#include "tinyxml.h"
#include "tinystr.h"


namespace igtl
{

	class IGTLMCommon_EXPORT MUSiiCXMLFileIO : public MUSiiCFileIOAbstract<TiXmlElement*>
{

public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCXMLFileIO				Self;
	typedef MUSiiCFileIOAbstract		Superclass;
	typedef SmartPointer<Self>			Pointer;
	typedef SmartPointer<const Self>	ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	/// Constructor
	MUSiiCXMLFileIO();
	
	/// Deconstructor
	~MUSiiCXMLFileIO();

	/// Virtual Function
	/// Reading a Single file
	virtual TiXmlElement* ReadSingleFile(std::string filepath= "");

	/// Virtual Function
	virtual int WriteSingleFile(TiXmlElement* filedata = NULL, std::string filepath = "");

	/// Print TiXmlElement
	int PrintXMLElement(TiXmlElement* element = NULL, int level = 0);

	/// Write XML file
	int WriteXMLFile(TiXmlElement* filedata = NULL, std::string const filepath = "", std::string const version="1.0",std::string encoding = "",std::string standalone ="" );
protected: ///Operation
	//// virtual functions
	virtual void Initialize();

	//// Convert an IGTL Message (igtl::MessageBase::Pointer) to FileData structure
	virtual TiXmlElement* ConvertToFileData(igtl::MessageBase::Pointer msg);

	//// Convert an FileData structure to IGTL Message (igtl::MessageBase::Pointer) 
	virtual igtl::MessageBase::Pointer ConvertToIGTLMsg(TiXmlElement* data);
	
	/// Reading Single File with callbackInterface or Thread
	virtual int _ReadFilesCB(int taskInfo);
	
	/// Writing Single File with callbackInterface or Thread
	virtual int _WriteFilesCB(int taskInfo);
	
	/// Writing Single File with callbackInterface or Thread
	virtual int _WriteStreamData(int taskInfo);
	
	//// Post processing function for File IO
	/// In General, 
	/// numOfRun : When using Data-Interface, this number indicate the index of new data in Data-Interface
	/// TaskInfo : The argument of this task
	/// ptr      : the pointer of caller class
	/// data1    : Data 
	/// data2    : the Time-stamp of the data
	/// data3    : the name of Data
	virtual int FileIOPostProcessing(int numOfRun = 0, int taskInfo = 0, void* ptr = NULL,igtl::MessageBase::Pointer data1 = NULL, void* data2 = NULL, void* data3 = NULL);
	/// Virtual Functions
	///////////////////////////////////////////////////////////////////

public:/// Attributes
	
protected:/// Attributes

	/// Tiny XML
	TiXmlDocument		m_ReadXmlDoc;
	TiXmlDeclaration*	m_pReadDesclaration;
	TiXmlElement*		m_pReadRootElement;
	std::string			m_sReadFilePath;

	TiXmlDocument		m_WriteXmlDoc;
	TiXmlDeclaration*	m_pWriteDesclaration;
	TiXmlElement*		m_pWriteRootElement;
	std::string			m_sWriteFilePath;


	bool				m_bLoadXMLFile;
	bool				m_bOverWriteXMLFile;

	std::string			m_XmlVersion;
	std::string			m_XmlEncoding;
	std::string			m_XmlStandAlone;


	

};

}

#endif
