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


#ifndef __MUSIIC_CONFIGURE_
#define __MUSIIC_CONFIGURE_

/////  Key value for TCP Connection in MUSiiC_Configuration XML file
#define MC_NUM_OF_SERVER		"num_of_server"
#define MC_SERVER_TCP_PORT		"server_tcp_port"
#define MC_SERVER_NAME			"server_name"
#define MC_SERVER_IOFILTER		"server_io_filter"

#define MC_NUM_OF_CLIENT		"num_of_client"
#define MC_CLIENT_TCP_PORT		"client_tcp_port"
#define MC_CLIENT_TCP_IP		"client_tcp_ip"
#define MC_CLIENT_IOFILTER		"client_tcp_filter"
#define MC_CLIENT_NAME			"client_tcp_name"
#define MC_CLIENT_SYNC			"client_tcp_sync"
#define MC_CLIENT_REF			"client_tcp_ref"
#define MC_CLIENT_RECONN		"client_tcp_reconn"


#include "MUSiiCXMLFileIO.h"

namespace igtl
{
class IGTLMCommon_EXPORT MUSiiCConfigure : public MUSiiCXMLFileIO
{

public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCConfigure				Self;
	typedef MUSiiCXMLFileIO				Superclass;
	typedef SmartPointer<Self>			Pointer;
	typedef SmartPointer<const Self>	ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	/// Constructor
	MUSiiCConfigure();
	
	/// Deconstructor
	~MUSiiCConfigure();

	/// Load pre-defined setting values from XML file with module's name
	virtual int LoadPreDefineSettingsFromXML(std::string const filepath, std::string const moduleName);

	//// Find XML Element with depth-first searching method
	TiXmlElement* FindXMLElement(TiXmlElement* in_element, std::string name);

	/// Load Configuration XML file and searching pre-defined control parameters of a module
	TiXmlElement* LoadConfigurationXMLElement(std::string filepath, std::string moduleName); 

	/// Load pre-defined setting values from XML Element with module's name
	int LoadPreDefineSettings(TiXmlElement* in_element);

	/// Get a TinyXMLElement of a specific module
	TiXmlElement* GetModuleElement();

	/// Update XML file with overwiriting 
	int UpdateXMLFile();

	/// Print Control Parameters of each module
	virtual int PrintModuleControlParameters();

	/// Print Network setting of each moudle
	virtual int PrintMouldeNetworkSetting();

	/// Re-Define Information of  MUSiiCTCPServer (console mode)
	virtual int ReDefineTCPServerMUSiiCConfigure();

	/// Re-Define Information of  MUSiiCTCPClient (console mode)
	virtual int ReDefineTCPClientMUSiiCConfigure();

	/// Re-Define control parameters of this module
	virtual int ReDefineControlParameters();

protected: ///Operation
	//// virtual functions
	virtual void Initialize();

	//// Convert TiXmlElement to String
	int ConvertTiXmlElementToStringMap(TiXmlElement* in_elemen);

	/// Check XML element using key-value
	bool LookAtXMLElement(std::string const key, std::string& value);

	/// Apply pre-setting values
	int GetPreSettingValues();

	/// Get the informations of TCP_Servers
	int GetTCPServerInfo();

	/// Get the information of TCP_Server
	int GetTCPServerInfoElements(int index = 0);

	/// Get the informations of TCP_Clients
	int GetTCPClientInfo();

	/// Get the information of TCP_Client
	int GetTCPClientInfoElements(int index = 0);
	
	/// Get pre-setting values of a specific module
	virtual int GetPreSettingValuesOfModule();

	
	/// Set the informations of TCP_Servers
	int SetTCPServerInfo();

	/// Set the information of TCP_Server
	int SetTCPServerInfoElements(int index = 0);

	/// Set the informations of TCP_Clients
	int SetTCPClientInfo();

	/// Get the information of TCP_Client
	int SetTCPClientInfoElements(int index = 0);
	
	/// Update network parameters
	virtual int UpdateNetworkSetting();

	/// Update control parameters
	virtual int UpdateControlParameters();

	/// Print pre-defined server info of each moudle
	int PrintPredefinedTCPServerSetting();
	
	/// Print pre-defined client info of each moudle
	int PrintPredefinedTCPClientSetting();

public:/// Attributes
	
	/// The list TCP_Server's Information
	std::vector<MTKTCPServerInfo>					m_VTCPServer_Info;
	
	/// The list TCP_Client's Information
	std::vector<MTKTCPClientInfo>					m_VTCPClient_Info;

protected:/// Attributes

	/// TiXmlElement for pre-defined of specific module
	TiXmlElement*									m_pModule;
	/// Map structure for containing XML element's value
	std::map<std::string, std::string>				m_vXMLSettings;
	/// Map iterator of Map structure
	std::map<std::string, std::string>::iterator	m_pMapit;
	/// temporary element value
	std::string										m_sEValue;

	/// The name of Module 
	std::string										m_sModuleName;

};

}

#endif
