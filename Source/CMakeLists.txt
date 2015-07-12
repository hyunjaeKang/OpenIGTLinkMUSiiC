#/***************************************************************************
# Copyright 
# MUSiiC Laboratory
# Hyun-Jae Kang,Emad M Boctor
#
# Department of Computer Science
# Johns Hopkins University
#
# Johns Hopkins Medical Institutions
# Department of Radiology, Division of Medical Imaging Physics

# For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.
# ***************************************************************************/

MESSAGE(STATUS "Source Directory")

# list of libraries

IF(OpenIGTLinkMUSiiC_PLATFORM_WIN32) # for Windows
  SET(LINK_LIBS
    ws2_32
    wsock32
  )
ELSE(OpenIGTLinkMUSiiC_PLATFORM_WIN32) # for POSIX-compatible OSs
  SET(LINK_LIBS
    m
    pthread
  )
  IF(OpenIGTLinkMUSiiC_PLATFORM_QNX)
    SET(LINK_LIBS
      ${LINK_LIBS}
      c
      socket
    )
  ENDIF(OpenIGTLinkMUSiiC_PLATFORM_QNX)
  IF(OpenIGTLinkMUSiiC_PLATFORM_SUNOS)
    SET(LINK_LIBS
      ${LINK_LIBS}
      ${OpenIGTLink_STD_LINK_LIBRARIES}
    )
  ENDIF(OpenIGTLinkMUSiiC_PLATFORM_SUNOS)
ENDIF(OpenIGTLinkMUSiiC_PLATFORM_WIN32)

#-----------------------------------------------------------------------------
# Setting LINK_LIBS
SET( LINK_LIBS ${LINK_LIBS} ${OpenIGTLink_LIBRARIES} )

#-----------------------------------------------------------------------------
# Configure Subdirectories
OPTION(BUILD_MESSAGE "Build OpenIGTLinkMUSiiC Message Types." ON)
SET(OpenIGTLinkMUSiiC_BUILD_MESSAGE ${BUILD_MESSAGE})
# IF(OpenIGTLinkMUSiiC_BUILD_MESSAGE)
 # ADD_SUBDIRECTORY( Messages )
# ENDIF(OpenIGTLinkMUSiiC_BUILD_MESSAGE)

OPTION(BUILD_MULTITASK "Build OpenIGTLinkMUSiiC Task classes." ON)
SET(OpenIGTLinkMUSiiC_BUILD_TASK ${BUILD_MULTITASK})
# IF(OpenIGTLinkMUSiiC_BUILD_TASK)
 # ADD_SUBDIRECTORY( MultiTask )
# ENDIF(OpenIGTLinkMUSiiC_BUILD_TASK)

#-----------------------------------------------------------------------------
# Configure Source code and header files

ADD_SUBDIRECTORY( igtlMUSiiCutil )
	
SET(OpenIGTLinkMUSiiC_SOURCES
	${OpenIGTLinkMUSiiC_SOURCES}
	igtlMUSiiCutil/igtlM_US.c
	igtlMUSiiCutil/igtlM_EI.c
	igtlMUSiiCutil/igtlM_GEN.c
	igtlMUSiiCutil/igtlM_ARG.c
	igtlMUSiiCutil/igtlM_FILE.c
	igtlMFixedImage.cxx
	igtlMUSMessage.cxx
	igtlMEIMessage.cxx
	igtlMGenMessage.cxx
	igtlMArgMessage.cxx
	igtlMFileMessage.cxx
	igtlMFixedImageBMode.cxx
	)
	
SET(OpenIGTLinkMUSiiC_INCLUDE_FILES
	${OpenIGTLinkMUSiiC_INCLUDE_FILES}
	igtlMUSiiCutil/igtl_win32header.h
	igtlMUSiiCutil/igtlM_win32header.h
	igtlMUSiiCutil/igtlM_US.h
	igtlMUSiiCutil/igtlM_EI.h
	igtlMUSiiCutil/igtlM_GEN.h
	igtlMUSiiCutil/igtlM_ARG.h
	igtlMUSiiCutil/igtlM_FILE.h
	igtlMFixedImage.h
	igtlMUSMessage.h
	igtlMGenMessage.h
	igtlMArgMessage.h
	igtlMFileMessage.h
	igtlMEIMessage.h
	igtlMFixedImageBMode.h
	)
########################################################

IF(OpenIGTLinkMUSiiC_BUILD_TASK)


SET(OpenIGTLinkMUSiiC_SOURCES
	${OpenIGTLinkMUSiiC_SOURCES}
	#MUSiiCGlobalFuntion.cxx
	# MUSiiCIGTLMsgVector.cxx
	MUSiiCCallbackInterface.cxx
	#MUSiiCGlobalFuntion.cxx
	MUSiiCCallbackInterfaceControl.cxx
	MUSiiCTaskObject.cxx
	MUSiiCTaskAbstract.cxx
	# MUSiiCTaskInterfaceAbstract.cxx
	#MUSiiCTaskSingleInterface.cxx
	#MUSiiCTaskDoubleInterface.cxx
	MUSiiCIOFilter.cxx
	MUSiiCIGTLTask.cxx
	MUSiiCIGTLIODevice.cxx
	MUSiiCDataObject.cxx
	# MUSiiCigtlSocketWrap.cxx
	MUSiiCTCPIO.cxx
	MUSiiCTCPServer.cxx
	MUSiiCTCPServerSocket.cxx
	MUSiiCTCPServerSocketNoWin.cxx
	MUSiiCTCPServerSocketWin.cxx
	MUSiiCTCPClient.cxx
	MUSiiCTCPClientSocket.cxx
	MUSiiCTCPClientSocketNoWin.cxx
	MUSiiCTCPClientSocketWin.cxx
	# MUSiiCTCPServerUni.cxx
	# MUSiiCTCPLightServerUni.cxx
	# MUSiiCTCPClientUni.cxx
	#MUSiiCFileIOAbstract.cxx
	# MUSiiCigtlMsgFILEIO.cxx
	MUSiiCSyncDATA.cxx
	MUSiiCSync.cxx
	MUSiiCIGTLUtil.cxx
	MUSiiCProfile.cxx
	###########################
	# MUSiiCFileIOAbstract.cxx
	# MUSiiCFileIOTemplate.cxx
	MUSiiCIGTLFileIO.cxx
	MUSiiCBindIGTLFileIO.cxx
	# MUSiiCVTKImageFileIO.cxx
	tinyxml.cpp
	tinystr.cpp
	tinyxmlerror.cpp
	tinyxmlparser.cpp
	MUSiiCXMLFileIO.cxx
	MUSiiCConfigure.cxx
	MUSiiCConfigureRFServer.cxx
	MUSiiCConfigureMUSiiCSync.cxx
	MUSiiCConfigureTrackerServer.cxx
	MUSiiCConfigureMUSiiCBMode.cxx
	MUSiiCConfigureMUSiiCEIAMDP.cxx
	MUSiiCConfigureMUSiiCEINCC.cxx
	MUSiiCConfigureMUSiiCEITrUE.cxx
	MUSiiCIGTLRS232C_IOCP.cxx
	MUSiiCIGTLRS232CSimple.cxx
	#MemLeakDetect.cpp
	)

SET(OpenIGTLinkMUSiiC_INCLUDE_FILES
	${OpenIGTLinkMUSiiC_INCLUDE_FILES}
	MUSiiCQueue.h
	MUSiiCVector.h
	MUSiiCVectorSet.h
	MUSiiCIGTLMsgVector.h
	MUSiiCCallbackInterface.h
	MUSiiCCallbackInterfaceControl.h
	MUSiiCTaskObject.h
	MUSiiCTaskAbstract.h
	MUSiiCTaskInterfaceAbstract.h
	# MUSiiCTaskSingleInterface.h
	# MUSiiCTaskDoubleInterface.h
	MUSiiCIOFilter.h
	MUSiiCIGTLTask.h
	MUSiiCIGTLIODevice.h
	MUSiiCDataObject.h
	# MUSiiCigtlSocketWrap.h
	MUSiiCTCPIO.h
	MUSiiCTCPIO.h
	MUSiiCTCPServer.h
	MUSiiCTCPServerSocket.h
	MUSiiCTCPServerSocketNoWin.h
	MUSiiCTCPServerSocketWin.h
	MUSiiCTCPClient.h
	MUSiiCTCPClientSocket.h
	MUSiiCTCPClientSocketNoWin.h
	MUSiiCTCPClientSocketWin.h
	# MUSiiCTCPServerUni.h
	# MUSiiCTCPLightServerUni.h
	# MUSiiCTCPClientUni.h
	# MUSiiCFileIOAbstract.h
	# MUSiiCigtlMsgFILEIO.h
	# MUSiiCigtlMsgFilter.h
	MUSiiCSyncDATA.h
	MUSiiCSync.h
	MUSiiCDef.h
	MUSiiCIGTLUtil.h
	# MUSiiCTCPSimpleClientUni.h
	# MUSiiCTCPSimpleServerUni.h
	MUSiiCLogMessage.h
	MUSiiCProfile.h
	MUSiiCTime.h
	###########################
	MUSiiCFileIOAbstract.h
	# MUSiiCFileIOTemplate.h
	MUSiiCIGTLFileIO.h
	MUSiiCBindIGTLFileIO.h
	# MUSiiCVTKImageFileIO.h
	tinyxml.h
	tinystr.h
	MUSiiCXMLFileIO.h
	MUSiiCConfigure.h
	MUSiiCConfigureRFServer.h
	MUSiiCConfigureMUSiiCSync.h
	MUSiiCConfigureTrackerServer.h
	MUSiiCConfigureMUSiiCBMode.h
	MUSiiCConfigureMUSiiCEIAMDP.h
	MUSiiCConfigureMUSiiCEINCC.h
	MUSiiCConfigureMUSiiCEITrUE.h
	MUSiiCIGTLRS232C_IOCP.h
	MUSiiCIGTLRS232CSimple.h
	#MemLeakDetect.h
	#dbgint.h
	)

ENDIF(OpenIGTLinkMUSiiC_BUILD_TASK)

#-----------------------------------------------------------------------------
# Configure Output

ADD_LIBRARY(OpenIGTLinkMUSiiC
  ${OpenIGTLinkMUSiiC_SOURCES}
  ${OpenIGTLinkMUSiiC_INCLUDE_FILES}
  )
  
  
TARGET_LINK_LIBRARIES(OpenIGTLinkMUSiiC
  ${LINK_LIBS}
  )

SET_TARGET_PROPERTIES(OpenIGTLinkMUSiiC PROPERTIES
  VERSION ${OpenIGTLinkMUSiiC_VERSION_MAJOR}.${OpenIGTLinkMUSiiC_VERSION_MINOR}.${OpenIGTLinkMUSiiC_VERSION_PATCH}
  SOVERSION ${OpenIGTLinkMUSiiC_VERSION_MAJOR}
)

INSTALL(FILES ${OpenIGTLinkMUSiiC_INCLUDE_FILES}
  DESTINATION ${OpenIGTLinkMUSiiC_INSTALL_INCLUDE_DIR}
  COMPONENT Development)

INSTALL(TARGETS OpenIGTLinkMUSiiC
  RUNTIME DESTINATION ${OpenIGTLinkMUSiiC_INSTALL_BIN_DIR} COMPONENT RuntimeLibraries
  LIBRARY DESTINATION ${OpenIGTLinkMUSiiC_INSTALL_LIB_DIR} COMPONENT RuntimeLibraries
  ARCHIVE DESTINATION ${OpenIGTLinkMUSiiC_INSTALL_LIB_DIR} COMPONENT Development)