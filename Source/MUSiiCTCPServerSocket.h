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

#ifndef __MUSIIC_TCP_SERVER_SOCKET_
#define __MUSIIC_TCP_SERVER_SOCKET_

#include "MUSiiCTCPIO.h"

namespace igtl
{

class IGTLMCommon_EXPORT MUSiiCTCPServerSocket : public MUSiiCTCPIO 
{
public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCTCPServerSocket		Self;
	typedef MUSiiCTCPIO				Superclass;
	typedef SmartPointer<Self>			Pointer;
	typedef SmartPointer<const Self>	ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	/// Constructor
	MUSiiCTCPServerSocket();
	
	/// Deconstructor
	~MUSiiCTCPServerSocket();
	
	//////////////////////////////////////////////////////////////////////
	/// Creater Server Socket //
	virtual int CreateServer(int port);

	/// Close server socket
	virtual int CloseServer();

	/// Get Num of connected-clients
	virtual int GetNumOfClients();

	/// Check there are clients or not.
	virtual bool IsConnectedClients();

	////////////////////////////////////////
	/// Get the list of Connected client list
	virtual igtl::MUSiiCVector<LP_CLIENT_DATA>::Pointer GetConnectedClientList();
	
protected: ///Operation
	virtual void Initialize();

public:/// Attributes
	
protected:/// Attributes
	
	
};

}
#endif