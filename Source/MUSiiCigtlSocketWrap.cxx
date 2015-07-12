/***************************************************************************
Copyright 
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/

#include "MUSiiCigtlSocketWrap.h"

#if defined(_WIN32) && !defined(__CYGWIN__)
  #include <windows.h>
  #include <winsock2.h> 
#else
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <netinet/tcp.h>
  #include <arpa/inet.h>
  #include <netdb.h>
  #include <unistd.h>
  #include <sys/time.h>
#endif

#include <string.h>

#if defined(_WIN32) && !defined(__CYGWIN__)
#define WSA_VERSION MAKEWORD(1,1)
#define igtlCloseSocketMacro(sock) (closesocket(sock))
#else
#define igtlCloseSocketMacro(sock) (close(sock))
#endif


namespace igtl
{
	/// Constructor
	MUSiiCigtlSocketWrap::MUSiiCigtlSocketWrap()
	{
	}
	
	/// Deconstructor
	MUSiiCigtlSocketWrap::~MUSiiCigtlSocketWrap()
	{
	}

	int MUSiiCigtlSocketWrap::MGetSocketDescriptor()
	{
		return this->m_SocketDescriptor;
	}

	// Description:
	// Returns the port to which the socket is connected.
	// 0 on error.
	int MUSiiCigtlSocketWrap::MGetPort(int socketdescriptor)
	{
		return GetPort(socketdescriptor); 
	}

	/// Convert IP addresses from a dots-and-number string to a struct in_addr and back
	/// return -1: Error
	/// return  0: No error
	int MUSiiCigtlSocketWrap::MGetIP(int socketdescriptor, std::string& ip)
	{
		struct sockaddr_in sockinfo;
		memset(&sockinfo, 0, sizeof(sockinfo));
		#if defined(OpenIGTLink_HAVE_GETSOCKNAME_WITH_SOCKLEN_T)
		socklen_t sizebuf = sizeof(sockinfo);
		#else
		int sizebuf = sizeof(sockinfo);
		#endif
		//  FIXME: Setup configuration for VTK_HAVE_GETSOCKNAME_WITH_SOCKLEN_T so we can uncomment these lines
		if(getsockname(socketdescriptor, reinterpret_cast<sockaddr*>(&sockinfo), &sizebuf) != 0)
		{
			ip =  inet_ntoa(sockinfo.sin_addr);
			return 0;
		}
		else 
		{
			ip ="";
			return -1;
		}
	}
}