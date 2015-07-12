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

#ifndef __MUSiiC_DEF_
#define __MUSiiC_DEF_

#define M_REF_DATA "M_REF_"
#define M_SYNC_DATA "M_SYNC_"

//// DeviceName of MUSiiCDATA for MUSiiCIOFilter /////

/// Device Name
#define M_ALL_DATA			"MD_ALL_DATA"
#define M_US				"MD_US"
#define M_US_2D				"MD_US_2D"
#define M_US_3D				"MD_US_3D"
#define M_RF				"MD_RF"
#define M_RF_PRE_DATA_2D	"MD_RF_PRE_DATA_2D"
#define M_RF_PREDATA_3D		"MD_RF_PREDATA_3D"
#define M_RF_DATA_2D		"MD_RF_DATA_2D"
#define M_RF_DATA_3D		"MD_RF_DATA_3D"
#define M_DUMMY_RF          "MD_Dummy_RF_DATA"
#define M_EI				"MD_EI"
#define M_EI_DATA_2D		"MD_EI_DATA_2D"
#define M_EI_DATA_3D		"MD_EI_DATA_3D"
#define M_DUMMY_EI          "MD_Dummy_EI_DATA"
#define M_BMODE				"MD_BMODE"
#define M_BMODE_2D			"MD_BMODE_2D"
#define M_BMODE_3D			"MD_BMODE_3D"
#define M_EM_TRACKER		"MD_EM_TRACKER"
#define M_2D_PA				"MD_PA_2D"
#define M_3D_PA				"MD_PA_3D"
#define M_REF_TRACKER		"MD_REF_TRACKER"
#define M_ACTIVE_TRACKER	"MD_ACTIVE_TRACKER"
#define M_ACTIVE_TRACKER1	"MD_ACTIVE_TRACKER1"
#define M_ACTIVE_TRACKER2	"MD_ACTIVE_TRACKER2"
#define M_DUMMY_TRACKER     "MD_Dummy_TrackingDataMsg"
#define M_DUMMY_IMAGE       "MD_Dummy_Image"
/// Device Name of String Message
#define M_IO_FILTER			"MD_IO_FILTER"
#define M_CONTROL_PAR		"MD_CONTROL_PAR"

/// Device Type
#define IGTL_BIND			"BIND"
#define IGTL_COLOR_TABLE	"COLORTABLE"
#define IGTL_IMAGE			"IMAGE"
#define IGTL_IMAGEMETA		"IMGMETA"
#define IGTL_LABELMETA		"LBMETA"
#define IGTL_NDARRAY		"NDARRAY"
#define IGTL_POINT			"POINT"
#define IGTL_POSITION		"POSITION"
#define IGTL_QUATERNION		"QTDATA"
#define IGTL_STATUS			"STATUS"
#define IGTL_STRING			"STRING"
#define IGTL_TRACKING		"TDATA"
#define IGTL_TRANSFORM		"TRANSFORM"
#define IGTL_TRAJECTORY		"TRAJ"
#define IGTLM_GEN			"GEN"
#define IGTLM_ARGUMENT		"ARGUMENTS"
#define IGTLM_FILE			"FILE"
#define IGTLM_FIXEDIMAGE	"EIIMAGE"
#define IGTLM_FIXEDBMODE	"EIUSIMAGE"



//// General Including File
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "igtlMConfigure.h"
//////////////////////////////////////////////////////
/// Header Files for OpenIGTLink and OpenIGTLinkMUSiiC
#include <igtlMessageBase.h>
#include <igtlBindMessage.h>
#include <igtlColorTableMessage.h>
#include <igtlImageMessage.h>
#include <igtlImageMetaMessage.h>
#include <igtlLabelMetaMessage.h>
#include <igtlNDArrayMessage.h>
#include <igtlPointMessage.h>
#include <igtlPositionMessage.h>
#include <igtlQuaternionTrackingDataMessage.h>
#include <igtlSensorMessage.h>
#include <igtlStatusMessage.h>
#include <igtlStringMessage.h>
#include <igtlTrackingDataMessage.h>
#include <igtlTransformMessage.h>
#include <igtlTrajectoryMessage.h>
#include "igtlMUSMessage.h"
#include "igtlMEIMessage.h"
#include "igtlMGenMessage.h"
#include "igtlMArgMessage.h"
#include "igtlMFileMessage.h"
#include "igtlMFixedImage.h"
#include "igtlMFixedImageBMode.h"

///////////////////////////////////////////////////////
#include <igtlLightObject.h>
#include <igtlMacro.h>
#include <igtlObjectFactory.h>
#include <igtlOSUtil.h>
#include <igtlMultiThreader.h>
#include <igtlFastMutexLock.h>
#include <igtlTimeStamp.h>

#if defined(WIN32) || defined (_WIN32) || defined (__WIN32__)
#include "igtlM_win32header.h"
#endif


#include "MUSiiCIOFilter.h" ///
#include "MUSiiCCallbackInterfaceControl.h" ///
#include "MUSiiCProfile.h" ///
#include "MUSiiCVectorSet.h" ///
#include "MUSiiCIGTLMsgVector.h" ///

/// Debugging
#if defined(WIN32) || defined (_WIN32) || defined (__WIN32__)
//#include "MemLeakDetect.h"
//#pragma warning(disable:4100)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
//
#endif

//////////////////////////////////////////////////////
/// Network 

#if defined(WIN32) || defined (_WIN32) || defined (__WIN32__)
/////// WinSock library
#include <WinSock2.h>
/// Loading the library of WinSock2 
#pragma comment(lib, "Ws2_32.lib")
/// Data structure of client
typedef struct
{
	SOCKET							hClntSocket;
	SOCKADDR_IN						slntAddr;
	SOCKADDR_IN						clntAddr;
	int								TXMode;
	int								TCP_STATUS;
	bool							bReconnect;
	bool							bReference;
	bool							bSync;
	igtl::MUSiiCIOFilter::Pointer	IOFilter;
} CLIENT_DATA, *LP_CLIENT_DATA;

typedef struct
{
	OVERLAPPED Overlapped;
	WSABUF wsaBuf;
	int n_iExpectSum;
	int n_iSum;
	igtl::MessageHeader::Pointer headerMsg;
	igtl::MessageBase::Pointer IGTLMsg;
	int RxMode;
	int TXMode;
	int IO_MODE;
}IO_DATA, *LP_IO_DATA;
#else
//////////////////////////////////////////
/// Data structure of Non-Windows socket

//// Include Files

/// Data Structure
typedef struct
{
	//SOCKET					hClntSocket;
	//SOCKADDR_IN				slntAddr;
	//SOCKADDR_IN				clntAddr;
	int						TXMode;
	int						TCP_STATUS;
	bool					bReconnect;
	bool					bReference;
	igtl::MUSiiCIOFilter	IOFilter;
} CLIENT_DATA, *LP_CLIENT_DATA;

///Data IO Strucure for IOCP
typedef struct
{
	//OVERLAPPED Overlapped;
	//WSABUF wsaBuf;
	int n_iExpectSum;
	int n_iSum;
    igtl::MessageHeader::Pointer headerMsg;
	igtl::MessageBase::Pointer IGTLMsg;
	int RxMode;
	int TXMode;
	int IO_MODE;
}IO_DATA, *LP_IO_DATA;

#endif


#if defined(WIN32) || defined (_WIN32) || defined (__WIN32__)
#include <conio.h>
#else
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

//////////////////////////////////////////

//============================================
/// Pre-defined Parameters of MUSiiCTaskObject
#define M_THREAD_START					9900
#define M_THREAD_STOP					9901
#define M_THREAD_PAUSE					9902
#define M_THREAD_RESUME					9903
#define M_THREAD_RUN_STREAM				9904
#define M_THREAD_RUN_CONTINUOUS			9905

//============================================
/// Pre-defined Parameters of MUSiiCTaskAbstract
#define M_SELFTASKOBJECT				9800
#define M_ALLTASKOBJECT					9801
/////////////////////////
/////////////////////////
#define M_TAKS_START					9700
#define M_TAKS_STARTED					9701
#define M_TAKS_STOP					    9702
#define M_TASK_STOPPED					9703
#define M_TAKS_PAUSE					9704
#define M_TAKS_PAUSED					9705
#define M_TAKS_RESUME					9706
#define M_TAKS_RESUMED					9707
#define M_TAKS_RUNNING					9708
#define M_TAKS_WAITTING					9709
//============================================
/// Pre-defined Parameters of MUSiiCTaskInterfaceAbstract
#define M_SELFDATAINTERFACE				9600
#define M_ALLDATAINTERFACE				9601

//============================================
/// Pre-defined Parameters of MUSiiCIODevice
#define M_NO_DEVICE_IO 					9500
#define M_TCP_DEVICE_IO 				9501
#define M_FILE_DEVICE_IO				9502
#define M_GRAPHIC_DEVICE_IO				9503

//============================================
/// Pre-defined Parameters of MUSiiCTCPIO

#define M_TCP_DISCONNECTED				9400
#define M_TCP_SERVER_CREATED			9401
#define M_TCP_SERVER_CLOSED				9402
#define M_TCP_CLIENT_CONNECTED			9403
#define M_TCP_DATA_RECEIVED				9404
#define M_TCP_DATA_RECEIVED_DATA		9405
#define M_TCP_DATA_RECEIVED_NULLDATA	9406
#define M_TCP_DATA_RECEIVED_NODATA		9407
#define M_TCP_DATA_SENT					9408
#define M_TCP_CLIENTS_SERVICE_INIT		9409
#define M_TCP_CLIENTS_SERVICE_FINISH	9410
#define M_TCP_CLIENT_CONNECTING			9411
#define M_TCP_CLIENT_RECONNECTING		9412
#define M_TCP_CLIENT_DISCONNECTED		9413


//============================================
/// Pre-defined Parameters of MUSiiCTCPClientSocketWin

#define M_IOCP_RX_INIT					0
#define M_IOCP_Rx_IGTLHEADER			1
#define M_IOCP_Rx_IGTLHEADERDONE		2
#define M_IOCP_Rx_IGTLBODY				3
#define M_IOCP_Rx_IGTLBODYDONE			4
#define M_IOCP_TX_INIT					5
#define M_IOCP_Tx_IGTL					6
#define M_IOCP_Tx_IGTLDONE				7
#define M_IOCP_Rx						8
#define M_IOCP_Tx						9



//============================================
/// Pre-defined Parameters of MUSiiCTCPClientSocketWin
#define M_C_IOCP_RX_INIT				10
#define M_C_IOCP_Rx_IGTLHEADER			11
#define M_C_IOCP_Rx_IGTLHEADERDONE		12
#define M_C_IOCP_Rx_IGTLBODY			13
#define M_C_IOCP_Rx_IGTLBODYDONE		14
#define M_C_IOCP_TX_INIT				15
#define M_C_IOCP_Tx_IGTL				16
#define M_C_IOCP_Tx_IGTLDONE			17
#define M_C_IOCP_Rx						18
#define M_C_IOCP_Tx						19



//============================================
/// Pre-defined Parameters of MUSiiCCallbakcInterface
#define	M_PRE_CONTROL_PRAR				30
#define M_POST_CONTROL_PRAR				31
#define M_PRE_DATA						32
#define M_POST_DATA						33
#define M_PRE_CONTROL_PRAR_DATA			34
#define M_POST_CONTROL_PRAR_DATA		35



//============================================
/// Pre-defined Parameters of MUSiiCSync
#define M_SYNC_UPDATEDIMAGE				50
#define M_SYNC_IMAGE					51
#define M_SYNC_TRACKER					52
#define M_SYNC_IGTLMSG					53
#define M_UNSYNC_IGTLMSG				54


//============================================
/// Pre-defined index of MUSiiCFileIO mode
#define M_READ_SINGLE_CB 				150
#define M_READ_SINGLE_CB_DOING 			151
#define M_READ_SINGLE_CB_DONE 			152

#define M_READ_SINGLE_TH				153
#define M_READ_SINGLE_TH_DOING			154
#define M_READ_SINGLE_TH_DONE			155

#define M_READ_MULTI_CB					156
#define M_READ_MULTI_CB_DOING			157
#define M_READ_MULTI_CB_DONE			158

#define M_READ_MULTI_TH					159
#define M_READ_MULTI_TH_DOING			160
#define M_READ_MULTI_TH_DONE			161

#define M_WRITE_SINGLE_CB				162
#define M_WRITE_SINGLE_CB_DOING			163
#define M_WRITE_SINGLE_CB_DONE			164

#define M_WRITE_SINGLE_TH				165
#define M_WRITE_SINGLE_TH_DOING			166
#define M_WRITE_SINGLE_TH_DONE			167

#define M_WRITE_MULTI_CB				168
#define M_WRITE_MULTI_CB_DOING			169
#define M_WRITE_MULTI_CB_DONE			170

#define M_WRITE_MULTI_TH				171
#define M_WRITE_MULTI_TH_DOING			172
#define M_WRITE_MULTI_TH_DONE			173

#define M_WRITE_STREAM_DATA				174
#define M_WRITE_STREAM_DATA_DOING		175
#define M_WRITE_STREAM_DATA_DONE		176
#define M_WRITE_STREAM_DATA_PAUSE		177
#define M_WRITE_STREAM_DATA_RESUME		178

//============================================
/// Pre-defined index of MUSiiCFileIO mode
#define M_RS232C_RX 				    190
#define M_RS232C_RX_INCOMPLETE 			191
#define M_RS232C_TX 			        192
#define M_RS232C_TX_INCOMPLETE 			193


//============================================
/// Data structure of client
typedef struct
{
  int		   port; 
  bool         sync;
  bool         referenceData;
  bool		   reconnect;
  std::string  ip;
  std::string  filter;
  std::string  description;

} MTKTCPClientInfo;

typedef struct
{
  int			port;
  std::string   description;
  std::string   filter;
} MTKTCPServerInfo;


#endif