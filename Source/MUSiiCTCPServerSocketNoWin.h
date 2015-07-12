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

#ifndef __MUSIIC_TCP_SERVER_SOCKET_NO_WIN_
#define __MUSIIC_TCP_SERVER_SOCKET_NO_WIN_

#include "MUSiiCTCPServerSocket.h"

namespace igtl
{

class IGTLMCommon_EXPORT MUSiiCTCPServerSocketNoWin : public MUSiiCTCPServerSocket 
{
public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCTCPServerSocketNoWin			Self;
	typedef MUSiiCTCPServerSocket				Superclass;
	typedef SmartPointer<Self>					Pointer;
	typedef SmartPointer<const Self>			ConstPointer;

	igtlNewMacro(Self);  
	igtlTypeMacro(Self, Superclass);
	
	/// Constructor
	MUSiiCTCPServerSocketNoWin();
	
	/// Deconstructor
	~MUSiiCTCPServerSocketNoWin();
	
	/// Creater Server Socket
	virtual int CreateServer(int port);

	/// Close server socket
	virtual int CloseServer();

	/// Get Num of connected-clients
	virtual int GetNumOfClients();

	/// Check there are clients or not.
	virtual bool IsConnectedClients();

	
	
protected: ///Operation
	virtual void Initialize();


public:/// Attributes
	
protected:/// Attributes
	
};

}
#endif