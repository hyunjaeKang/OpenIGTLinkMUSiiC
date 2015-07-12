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

#include "MUSiiCConfigure.h"

namespace igtl
{
	
/// Constructor
MUSiiCConfigure::MUSiiCConfigure()
{
	m_pNameOfClass="MUSiiCConfigure";
	Initialize();	
}
	
	/// Deconstructor
MUSiiCConfigure::~MUSiiCConfigure()
{
	
}

/// Load pre-defined setting values from XML file with module's name
int MUSiiCConfigure::LoadPreDefineSettingsFromXML(std::string const filepath, std::string const moduleName)
{
	m_sModuleName = moduleName;
	return LoadPreDefineSettings(LoadConfigurationXMLElement(filepath, moduleName));
}


//// Find XML Element with depth-first searching method
TiXmlElement* MUSiiCConfigure::FindXMLElement(TiXmlElement* in_element, std::string name)
{
	if(!in_element)
	{
		std::cout << "The TiXML Element of is NULL pointer" << std::endl;
		return NULL;
	}
	
	if(name.compare(in_element->Value()) == 0)
	{
		return in_element;
	}
	else
	{
		TiXmlElement* temp_element = NULL;
		temp_element = in_element->FirstChildElement(name.c_str());

		if(temp_element != NULL)
		{
			if(this->m_bDebug) 
				std::cout << "The value of element is " << temp_element->Value() << std::endl;
			return temp_element;
		}
		else
		{
			TiXmlElement* pChild = in_element->FirstChildElement();
			for(pChild; pChild; pChild = pChild->NextSiblingElement())
			{
				TiXmlElement* temp = NULL;
				temp =  FindXMLElement(pChild, name);

				if(temp != NULL)
					return temp;
				else
					continue;
			}
		}
		return NULL;
	}
}

/// Load Configuration XML file and searching pre-defined control parameters of a module
TiXmlElement* MUSiiCConfigure::LoadConfigurationXMLElement(std::string filepath, std::string moduleName)
{
	m_pReadRootElement = this->ReadSingleFile(filepath);
	if(m_pReadRootElement != NULL)
	{
		m_pModule = this->FindXMLElement(m_pReadRootElement, moduleName);

		return m_pModule;
	}
	return NULL;
}

/// Load pre-defined setting values from XML Element with module's name
int MUSiiCConfigure::LoadPreDefineSettings(TiXmlElement* in_element)
{
	if(in_element == NULL)
		return -1;

	if(ConvertTiXmlElementToStringMap(in_element)>0)
		return GetPreSettingValues();
	else
		return 0;

}

/// Get a TinyXMLElement of a specific module
TiXmlElement* MUSiiCConfigure::GetModuleElement()
{
	return m_pModule;
}

/// Update XML file with overwiriting 
int MUSiiCConfigure::UpdateXMLFile()
{
	int r(0);
	r+=UpdateNetworkSetting();
	r+=UpdateControlParameters();
	if(r > 0)
		return WriteSingleFile(m_pReadRootElement, m_sReadFilePath);
	else
		return 0;
}

/// Print Control Parameters of each module
int MUSiiCConfigure::PrintModuleControlParameters()
{
	return 0;
}

/// Print Network setting of each moudle
int MUSiiCConfigure::PrintMouldeNetworkSetting()
{
	int r(0);
	std::cout << " =======================================================" <<std::endl;
	std::cout << this->GetNameOfMUSiiCClass().c_str() << ": Network Setting" << std::endl;
	r+= PrintPredefinedTCPServerSetting();
	r+= PrintPredefinedTCPClientSetting();
	std::cout << " =======================================================" <<std::endl;
	return r;
}


/// Re-Define Information of  MUSiiCTCPServer (console mode)
int MUSiiCConfigure::ReDefineTCPServerMUSiiCConfigure()
{
	this->m_VTCPServer_Info.clear();
	
	std::string temp;
	int NumOfServer;
	int tempINT;
	std::cout << "Set the number of server socket" <<std::endl;
	std::cin >> NumOfServer;

	for(int i=0; i< NumOfServer; i++)
	{
		MTKTCPServerInfo server;
		
		/// Set a name of Server
		std::cout << i << "-Server::Set a Name of MUSiiCTCPServer" <<std::endl;
		std::cin >> temp;
		server.description = temp;
		
		/// Set a MUSiiCIOFILTER of Server
		std::cout << i << "-Server::Set a MUSiiCIOFilter of MUSiiCTCPServer" <<std::endl;
		std::cin >> temp;
		server.filter = temp;
		
		/// Set a MUSiiCIOFILTER of Server
		std::cout << i << "-Server::Set a port number of MUSiiCTCPServer" <<std::endl;
		std::cin >> tempINT;
		server.port = tempINT;
		
		/// Insert new server information to the TCPServer Info container of MUSiiCConfigure
		this->m_VTCPServer_Info.push_back(server);
		std::cout << "Setting of "<< i << "-Server socket done" << std::endl;
	}
	std::cout << "Setting of All-Server sockets  done" << std::endl;
	return this->m_VTCPServer_Info.size();
}

/// Re-Define Information of  MUSiiCTCPClient (console mode)
int MUSiiCConfigure::ReDefineTCPClientMUSiiCConfigure()
{
	this->m_VTCPClient_Info.clear();
	
	std::string temp;
	int NumOfServer;
	int tempINT;
	std::cout << "Set the number of Client socket" <<std::endl;
	std::cin >> NumOfServer;

	for(int i=0; i< NumOfServer; i++)
	{
		MTKTCPClientInfo client;
		
		/// Set a name of Server
		std::cout << i << "-Client::Set a Name of MUSiiCTCPClient" <<std::endl;
		std::cin >> temp;
		client.description = temp;
		
		/// Set a MUSiiCIOFILTER of Server
		std::cout << i << "-Client::Set a ip address MUSiiCTCPServer to be connected" <<std::endl;
		std::cin >> temp;
		client.ip = temp;
		
		/// Set a MUSiiCIOFILTER of Server
		std::cout << i << "-Client::Set a port number of MUSiiCTCPServer to be connected" <<std::endl;
		std::cin >> tempINT;
		client.port = tempINT;

		/// Set a MUSiiCIOFILTER of Server
		std::cout << i << "-Client::Set a MUSiiCIOFilter of MUSiiCTCPClient" <<std::endl;
		std::cin >> temp;
		client.filter = temp;
			
		/// Set a MUSiiCIOFILTER of Server
		std::cout << i << "-Client::Set an Enable of Reference Data of MUSiiCTCPClient(y/n)" <<std::endl;
		std::cin >> temp;
		client.referenceData = YesNO_To_bool(temp);
		
		/// Set a MUSiiCIOFILTER of Server
		std::cout << i << "-Client::Set Enable of Sync of MUSiiCTCPClient(y/n)" <<std::endl;
		std::cin >> temp;
		client.sync = YesNO_To_bool(temp);
		
		
		/// Set a MUSiiCIOFILTER of Server
		std::cout << i << "-Client::Set Enable of Reconnectiopn of MUSiiCTCPClient(y/n)" <<std::endl;
		std::cin >> temp;
		client.reconnect = YesNO_To_bool(temp);

		/// Insert new server information to the TCPServer Info container of MUSiiCConfigure
		this->m_VTCPClient_Info.push_back(client);
		std::cout << "Setting of "<< i << "-Client socket done" << std::endl;
	}

	std::cout << "Setting of All-Client sockets  done" << std::endl;

	return this->m_VTCPClient_Info.size();
}


/// Re-Define control parameters of this module
int MUSiiCConfigure::ReDefineControlParameters()
{
	return 0;
}


/////////////////////////////////////////////////////////////////////////////////////
//protected: ///Operation
//// virtual functions
void MUSiiCConfigure::Initialize()
{
	m_pModule = NULL;

	/// Initialize the map of XML contents
	m_vXMLSettings.clear();

	/// Initialize the list TCP_Server's Information
	m_VTCPServer_Info.clear();

	/// Initialize the list TCP_Client's Information
	m_VTCPClient_Info.clear();

	/// Initialize temporary element value
	m_sEValue = "";

	/// Initialize module Name
	m_sModuleName = "";
}

//// Convert TiXmlElement to String
int MUSiiCConfigure::ConvertTiXmlElementToStringMap(TiXmlElement* in_elemen)
{
	m_vXMLSettings.clear();

	if(!in_elemen)
	{
		std::cout << "The TiXML Element is NULL pointer" << std::endl;
		return -1;
	}

	TiXmlElement*	pChild		= NULL;
	pChild= in_elemen->FirstChildElement();

	for(pChild; pChild; pChild = pChild->NextSiblingElement())
	{
		TiXmlElement*	tempChild = pChild->FirstChildElement();
		if(tempChild == NULL)
			m_vXMLSettings[pChild->Value()] = pChild->FirstChild()->ToText()->Value();
		else 
			continue;
	}

	return m_vXMLSettings.size();
}

/// Check XML element using key-value
bool MUSiiCConfigure::LookAtXMLElement(std::string const key, std::string& value)
{
	if( (m_pMapit = m_vXMLSettings.find(key)) == m_vXMLSettings.end())
	{
		value = "";
		return false;
	}

	value = m_pMapit->second;
	return true;
}

/// Apply pre-setting values
int MUSiiCConfigure::GetPreSettingValues()
{
	int r(0);

	r += GetTCPServerInfo(); 
	r += GetTCPClientInfo(); 
	r += GetPreSettingValuesOfModule(); 

	return r;
}

/// Get the informations of TCP_Clients
int MUSiiCConfigure::GetTCPServerInfo()
{
	if(LookAtXMLElement(MC_NUM_OF_SERVER, m_sEValue))
	{
		m_VTCPServer_Info.clear();

		int sz(string_To_int(m_sEValue));
		int r(0);
		for(int i=0; i<sz;i++)
			r += GetTCPServerInfoElements(i);

		return r;
	}
	return 0;
}

/// Get the information of TCP_Server
int MUSiiCConfigure::GetTCPServerInfoElements(int index)
{
	std::string sindex(int_To_string(index));
	MTKTCPServerInfo serverInfo;
	int r(0);

	/// Getting the name of TCP Server
	if(LookAtXMLElement(MC_SERVER_NAME+sindex, m_sEValue))
		serverInfo.description = m_sEValue; 
	else
		serverInfo.description = "No Name";


	/// Getting the IO Filter of TCP Server
	if(LookAtXMLElement(MC_SERVER_IOFILTER+sindex, m_sEValue))
	{
		if(IsAllDataIOFilter(m_sEValue))
			serverInfo.filter = "ALL";
		else
			serverInfo.filter = m_sEValue; 
	}
	else
		serverInfo.filter = "";

	/// Getting the port number of TCP server
	if(LookAtXMLElement(MC_SERVER_TCP_PORT+sindex, m_sEValue))
	{
		serverInfo.port = string_To_int(m_sEValue); 
		r++;
		m_VTCPServer_Info.push_back(serverInfo);
	}
	else
		serverInfo.port = 999;

	return r;
}

/// Get the informations of TCP_Clients
int MUSiiCConfigure::GetTCPClientInfo()
{
	if(LookAtXMLElement(MC_NUM_OF_CLIENT, m_sEValue))
	{
		m_VTCPClient_Info.clear();

		int sz(string_To_int(m_sEValue));
		int r(0);
		for(int i=0; i<sz;i++)
			r += GetTCPClientInfoElements(i);

		return r;
	}
	return 0;
}

/// Get the information of TCP_Client
int MUSiiCConfigure::GetTCPClientInfoElements(int index)
{
	std::string sindex(int_To_string(index));
	MTKTCPClientInfo clientInfo;
	int r(0);

	//// Get the port numbe of server that this client will connect
	if(LookAtXMLElement(MC_CLIENT_TCP_PORT+sindex, m_sEValue))
	{
		clientInfo.port = string_To_int(m_sEValue);
		r++;
	}
	else
	{
		clientInfo.port = 9999;
		return 0;
	}

	//// Get the ip of server that this client will connect
	if(LookAtXMLElement(MC_CLIENT_TCP_IP+sindex, m_sEValue))
	{
		clientInfo.ip = (m_sEValue);
		r++;
	}
	else
	{
		clientInfo.ip = "No IP";
		return 0;
	}

	/// Getting the IO Filter of TCP Client
	if(LookAtXMLElement(MC_CLIENT_IOFILTER+sindex, m_sEValue))
	{
		if(IsAllDataIOFilter(m_sEValue))
			clientInfo.filter = "ALL";
		else
			clientInfo.filter = m_sEValue; 
	}
	else
		clientInfo.filter = "";

	/// Getting the name of TCP client
	if(LookAtXMLElement(MC_CLIENT_NAME+sindex, m_sEValue))
	{
		clientInfo.description = m_sEValue; 
	}
	else
		clientInfo.description = "No Name";

	/// Getting the sync_enable of TCP client
	if(LookAtXMLElement(MC_CLIENT_SYNC+sindex, m_sEValue))
	{
		clientInfo.sync = string_To_bool(m_sEValue); 
	}
	else
		clientInfo.sync = false;


	/// Getting the reference_data_enable of TCP client
	if(LookAtXMLElement(MC_CLIENT_REF+sindex, m_sEValue))
	{
		clientInfo.referenceData = string_To_bool(m_sEValue); 
	}
	else
		clientInfo.referenceData = false;


	/// Getting the reconnection_enable of TCP client
	if(LookAtXMLElement(MC_CLIENT_RECONN+sindex, m_sEValue))
	{
		clientInfo.reconnect = string_To_bool(m_sEValue); 
	}
	else
		clientInfo.reconnect = true;

	if( r == 2)
	{
		m_VTCPClient_Info.push_back(clientInfo);
		return 1;
	}
	else
		return 0;
}

/// Get pre-setting values of a specific module
int MUSiiCConfigure::GetPreSettingValuesOfModule()
{
	return 0;
}

/// Set the informations of TCP_Servers
int MUSiiCConfigure::SetTCPServerInfo()
{
	TiXmlElement* pChildE;
	int r(0);
	
	//// Set the number of active-sensor of EM_Tracker
	pChildE = m_pModule->FirstChildElement(MC_NUM_OF_SERVER);
	if(pChildE !=NULL)
	{
		int sz(m_VTCPServer_Info.size());
		pChildE->FirstChild()->SetValue(int_To_string(sz).c_str());
		for(int i=0; i<sz;i++)
			r+= SetTCPServerInfoElements(i);
	}
	return r;
}


/// Set the information of TCP_Server
int MUSiiCConfigure::SetTCPServerInfoElements(int index)
{	
	std::string sindex(int_To_string(index));
	std::string temp;
	TiXmlElement* pChildE;
	int r(0);

	/// Setting the name of TCP Server
	temp = MC_SERVER_NAME+sindex;
	pChildE = m_pModule->FirstChildElement(temp.c_str());
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(m_VTCPServer_Info[index].description.c_str());
		r++;
	}

	/// Setting the IOFilter of TCP Server
	temp = MC_SERVER_IOFILTER+sindex;
	pChildE = m_pModule->FirstChildElement(temp.c_str());
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(m_VTCPServer_Info[index].filter.c_str());
		r++;
	}

	/// Setting the port of TCP Server
	temp = MC_SERVER_TCP_PORT+sindex;
	pChildE = m_pModule->FirstChildElement(temp.c_str());
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(int_To_string(m_VTCPServer_Info[index].port).c_str());
		r++;
	}


	return r;
}

/// Set the informations of TCP_Clients
int MUSiiCConfigure::SetTCPClientInfo()
{
	TiXmlElement* pChildE;
	int r(0);
	
	//// Set the number of active-sensor of EM_Tracker
	pChildE = m_pModule->FirstChildElement(MC_NUM_OF_CLIENT);
	if(pChildE !=NULL)
	{
		int sz(m_VTCPClient_Info.size());
		pChildE->FirstChild()->SetValue(int_To_string(sz).c_str());
		for(int i=0; i<sz;i++)
			r+= SetTCPClientInfoElements(i);
	}
	return r;
}

/// Get the information of TCP_Client
int MUSiiCConfigure::SetTCPClientInfoElements(int index)
{
	std::string sindex(int_To_string(index));
	std::string temp;
	TiXmlElement* pChildE;
	int r(0);

	/// Setting the port of MUSiiCTCPServer will be connected
	temp = MC_CLIENT_TCP_PORT+sindex;
	pChildE = m_pModule->FirstChildElement(temp.c_str());
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(int_To_string(m_VTCPClient_Info[index].port).c_str());
		r++;
	}

	/// Setting the ip of MUSiiCTCPServer will be connected
	temp = MC_CLIENT_TCP_IP+sindex;
	pChildE = m_pModule->FirstChildElement(temp.c_str());
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue((m_VTCPClient_Info[index].ip).c_str());
		r++;
	}
	/// Setting the IOFilter of TCP Client
	temp = MC_CLIENT_IOFILTER+sindex;
	pChildE = m_pModule->FirstChildElement(temp.c_str());
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(m_VTCPClient_Info[index].filter.c_str());
		r++;
	}

	/// Setting the name of TCP Client
	temp = MC_CLIENT_NAME+sindex;
	pChildE = m_pModule->FirstChildElement(temp.c_str());
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue((m_VTCPClient_Info[index].description).c_str());
		r++;
	}

	/// Setting enable of sync of TCP Client
	temp = MC_CLIENT_SYNC+sindex;
	pChildE = m_pModule->FirstChildElement(temp.c_str());
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(bool_To_string(m_VTCPClient_Info[index].sync).c_str());
		r++;
	}

	/// Setting enable of sync of TCP Client
	temp = MC_CLIENT_REF+sindex;
	pChildE = m_pModule->FirstChildElement(temp.c_str());
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(bool_To_string(m_VTCPClient_Info[index].referenceData).c_str());
		r++;
	}

	/// Setting enable of sync of TCP Client
	temp = MC_CLIENT_RECONN+sindex;
	pChildE = m_pModule->FirstChildElement(temp.c_str());
	if(pChildE !=NULL)
	{
		pChildE->FirstChild()->SetValue(bool_To_string(m_VTCPClient_Info[index].reconnect).c_str());
		r++;
	}

	return r;
	

}
/// Update network parameters
int MUSiiCConfigure::UpdateNetworkSetting()
{
	int r(0);
	r+= SetTCPServerInfo();
	r+= SetTCPClientInfo();
	return 0;
}

/// Update control parameters
int MUSiiCConfigure::UpdateControlParameters()
{
	return 0;
}


/// Print pre-defined server info of each moudle
int MUSiiCConfigure::PrintPredefinedTCPServerSetting()
{
	int r(m_VTCPServer_Info.size());
	std::cout << "-----------------------------------------------------" << std::endl;
	std::cout << "Pre-defined setting values of MUSiiCTCPServer" << std::endl;
	std::cout << "Num of TCP Server Socket: " << r <<std::endl;
	if(r>0)
	{
		for(int i=0; i < r; i++)
		{
			std::cout << "MUSiiCTCPServer(" << i <<"): Name:: " << m_VTCPServer_Info[i].description.c_str() << std::endl;
			std::cout << "MUSiiCTCPServer(" << i <<"): Port:: " << m_VTCPServer_Info[i].port << std::endl;
			std::cout << "MUSiiCTCPServer(" << i <<"): MUSiiCIO Filter:: " << m_VTCPServer_Info[i].filter.c_str() << std::endl;
			std::cout << std::endl;
		}
	}
	else
		std::cout << "There is no pre-defined information of MUSiiCTCPServer" << std::endl;
	std::cout << "-----------------------------------------------------" << std::endl;
	return r;
}
	
/// Print pre-defined client info of each moudle
int MUSiiCConfigure::PrintPredefinedTCPClientSetting()
{
	int r(m_VTCPClient_Info.size());
	std::cout << "-----------------------------------------------------" << std::endl;
	std::cout << "Pre-defined setting values of MUSiiCTCPClient" << std::endl;
	std::cout << "Num of TCP Client Socket: " << r <<std::endl;
	if(r>0)
	{
		for(int i=0; i < r; i++)
		{
			std::cout << "MUSiiCTCPClient(" << i <<"): Name:: " << m_VTCPClient_Info[i].description.c_str() << std::endl;
			std::cout << "MUSiiCTCPClient(" << i <<"): Server IP:: " << m_VTCPClient_Info[i].ip.c_str() << std::endl;
			std::cout << "MUSiiCTCPClient(" << i <<"): Server Port:: " << m_VTCPClient_Info[i].port << std::endl;
			std::cout << "MUSiiCTCPClient(" << i <<"): MUSiiCIO Filter:: " << m_VTCPClient_Info[i].filter.c_str() << std::endl;
			std::cout << "MUSiiCTCPClient(" << i <<"): Enable Reconnect:: " << bool_To_string(m_VTCPClient_Info[i].reconnect).c_str() << std::endl;
			std::cout << "MUSiiCTCPClient(" << i <<"): Enable Sync:: " << bool_To_string(m_VTCPClient_Info[i].sync).c_str() << std::endl;
			std::cout << "MUSiiCTCPClient(" << i <<"): Enable Reference:: " << bool_To_string(m_VTCPClient_Info[i].referenceData).c_str() << std::endl;
			std::cout << std::endl;
		}
	}
	else
		std::cout << "There is no pre-defined information of MUSiiCTCPClient" << std::endl;
	std::cout << "-----------------------------------------------------" << std::endl;
	return r;
}
/// Virtual Functions
///////////////////////////////////////////////////////////////////
}

