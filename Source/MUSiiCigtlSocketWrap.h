/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/
#ifndef __MUSIIC_IGTLSOCKET_WRAP_
#define __MUSIIC_IGTLSOCKET_WRAP_

#include <igtlSocket.h>
#include "igtlM_win32header.h"

namespace igtl
{
class IGTLMCommon_EXPORT MUSiiCigtlSocketWrap : public Socket
{

public: ///Operation
	/** Standard class typedefs. */
	typedef MUSiiCigtlSocketWrap					Self;
	typedef Socket				Superclass;
	typedef SmartPointer<Self>			Pointer;
	typedef SmartPointer<const Self>	ConstPointer;

	igtlNewMacro(MUSiiCigtlSocketWrap);  
	igtlTypeMacro(MUSiiCigtlSocketWrap, Socket);
	
	/// Constructor
	MUSiiCigtlSocketWrap();
	
	/// Deconstructor
	~MUSiiCigtlSocketWrap();

	/// Get SocketDescriptor
	int MGetSocketDescriptor();

	// Description:
	// Returns the port to which the socket is connected.
	// 0 on error.
	int MGetPort(int socketdescriptor);

	/// Convert IP addresses from a dots-and-number string to a struct in_addr and back
	int MGetIP(int socketdescriptor, std::string& ip);




protected: ///Operation

public:/// Attributes
	
protected:/// Attributes

};
}
#endif