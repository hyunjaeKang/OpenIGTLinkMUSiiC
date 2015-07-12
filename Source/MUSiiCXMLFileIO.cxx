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

#include "MUSiiCXMLFileIO.h"

namespace igtl
{

	
/// Constructor
MUSiiCXMLFileIO::MUSiiCXMLFileIO()
{
	m_pNameOfClass="MUSiiCXMLFileIO";
	Initialize();	
}
	
	/// Deconstructor
MUSiiCXMLFileIO::~MUSiiCXMLFileIO()
{
	
}

/// Virtual Function
/// Reading a Single file
TiXmlElement* MUSiiCXMLFileIO::ReadSingleFile(std::string filepath)
{
	m_sReadFilePath = filepath;
	m_ReadXmlDoc = TiXmlDocument(filepath.c_str());
	/// Loading XML file
	if(!m_ReadXmlDoc.LoadFile())
		return NULL;

	/// Handle of TinyXML
	TiXmlHandle		hDoc(&m_ReadXmlDoc);
	TiXmlHandle		hRoot(0);

	///Get De
	m_pReadDesclaration = m_ReadXmlDoc.FirstChild()->ToDeclaration();

	/// Root element of XML file
	m_pReadRootElement = hDoc.FirstChildElement().Element();

	if(!m_pReadRootElement)
	{
		m_bLoadXMLFile = false;
		return NULL;
	}
	else
	{
		m_bLoadXMLFile = true;
		return m_pReadRootElement;
	}

}

/// Virtual Function
int MUSiiCXMLFileIO::WriteSingleFile(TiXmlElement* filedata, std::string filepath)
{
	if(!filedata)
		return -1;

	/// Add Declaration
	if(m_sReadFilePath.compare(filepath) == 0)
	{
		m_bOverWriteXMLFile = true;
		m_pWriteDesclaration = new TiXmlDeclaration(*m_pReadDesclaration);
	}
	else
		m_pWriteDesclaration = new TiXmlDeclaration(m_XmlVersion.c_str(), m_XmlEncoding.c_str(),m_XmlStandAlone.c_str());
	
	m_WriteXmlDoc.LinkEndChild(m_pWriteDesclaration);
	
	m_pWriteRootElement = new TiXmlElement(*filedata);
	m_WriteXmlDoc.LinkEndChild(m_pWriteRootElement);
	return m_WriteXmlDoc.SaveFile(filepath.c_str());
}

/// Write XML file
int MUSiiCXMLFileIO::WriteXMLFile(TiXmlElement* filedata, std::string const filepath, std::string const version,std::string encoding,std::string standalone)
{
	m_XmlVersion	= version;
	m_XmlEncoding	= encoding;
	m_XmlStandAlone = standalone;

	return WriteSingleFile(filedata, filepath);
}


/////////////////////////////////////////////////////////////////////////////////////
//// Print XML Element
int MUSiiCXMLFileIO::PrintXMLElement(TiXmlElement* element, int level)
{
	if(!element)
	{
		std::cout << "The TiXML Element of " << level << " is NULL pointer" << std::endl;
		return -1;
	}

	TiXmlElement*	pChild		= NULL;
	std::string		space		= "";

	for(int i=0; i<level; i++)
		space = space + "---";
	
	pChild= element->FirstChildElement();
	if(pChild == NULL)
	{
		std::cout << space.c_str() <<"(Level:"<< level <<")"<< " The Element is " << element->Value() << ":   " << element->FirstChild()->ToText()->Value() << std::endl;
	}
	else
	{
		int levelT = level+1;
		std::cout << space.c_str() <<"(Level:"<< level <<")"<< " The Element is " << element->Value() <<std::endl;
		for(pChild; pChild; pChild = pChild->NextSiblingElement())
		{
			PrintXMLElement(pChild, levelT);
		}

		std::cout << std::endl;
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
//protected: ///Operation
//// virtual functions
void MUSiiCXMLFileIO::Initialize()
{
	//// Tiny XML
	m_pReadRootElement		= NULL;
	m_pReadDesclaration		= NULL;
	m_sReadFilePath			= "";

	m_pWriteDesclaration	= NULL;
	m_pWriteRootElement		= NULL;
	m_sWriteFilePath		= "";

	m_bLoadXMLFile			= false;
	m_bOverWriteXMLFile		= false;

	m_XmlVersion			= "1.0";
	m_XmlEncoding			= "";
	m_XmlStandAlone			= "";
}

//// Convert an IGTL Message (igtl::MessageBase::Pointer) to FileData structure
TiXmlElement* MUSiiCXMLFileIO::ConvertToFileData(igtl::MessageBase::Pointer msg)
{
	return NULL;
}

//// Convert an FileData structure to IGTL Message (igtl::MessageBase::Pointer) 
igtl::MessageBase::Pointer MUSiiCXMLFileIO::ConvertToIGTLMsg(TiXmlElement* data)
{
	return NULL;
}
	
/// Reading Single File with callbackInterface or Thread  ///Check point cannon96
int MUSiiCXMLFileIO::_ReadFilesCB(int taskInfo)
{
	if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "MUSiiCIGTLMsgFileIO::_ReadFilesCB";

	m_iFileMode = ++taskInfo;
	int sz(m_vFileNameList.size());
	int szr(0);
	for(int i=0; i<sz; i++)
	{
		TiXmlElement* pRoot = ReadSingleFile(m_vFileNameList[i]);

		if(pRoot == NULL)
			continue;
		
		m_pVOutputFileData->concurrent_push_back(pRoot);
		
		szr++;
		FileIOPostProcessing(M_POST_CONTROL_PRAR, taskInfo, this, NULL, NULL, NULL);
	}
	m_iFileMode = ++taskInfo;
	FileIOPostProcessing(M_POST_CONTROL_PRAR, taskInfo, this, NULL, NULL, NULL);
	return szr;
}
	
/// Writing Single File with callbackInterface or Thread  ///Check point cannon96
int MUSiiCXMLFileIO::_WriteFilesCB(int taskInfo)
{
	if(this->m_bDebug)
			MUSiiC_LOG(logINFO) << "MUSiiCIGTLMsgFileIO::_WriteFilesCB";

	m_iFileMode = ++taskInfo;
	int sz(m_vFileNameList.size());
	int szr(0);
	for(int i=0; i<sz; i++)
	{
		szr += WriteSingleFile(m_pVInputFileData->concurrent_try_GetData(i),m_vFileNameList[i]); 
		FileIOPostProcessing(M_PRE_CONTROL_PRAR, taskInfo, this, NULL, NULL, NULL);
	}
	m_iFileMode = ++taskInfo;
	FileIOPostProcessing(M_PRE_CONTROL_PRAR, taskInfo, this, NULL, NULL, NULL);
	return szr;
}
	
/// Writing Single File with callbackInterface or Thread
int MUSiiCXMLFileIO::_WriteStreamData(int taskInfo)   ///Check point cannon96:: This version does not support this function
{
	return 0;
}
	
//// Post processing function for File IO
/// In General, 
/// numOfRun : When using Data-Interface, this number indicate the index of new data in Data-Interface
/// TaskInfo : The argument of this task
/// ptr      : the pointer of caller class
/// data1    : Data 
/// data2    : the Time-stamp of the data
/// data3    : the name of Data
int MUSiiCXMLFileIO::FileIOPostProcessing(int numOfRun, int taskInfo, void* ptr,igtl::MessageBase::Pointer data1, void* data2, void* data3)
{
	return this->PostTaskProcessing(numOfRun, taskInfo, ptr, data1, data2, data3); // Check point cannon96
}
/// Virtual Functions
///////////////////////////////////////////////////////////////////
}

