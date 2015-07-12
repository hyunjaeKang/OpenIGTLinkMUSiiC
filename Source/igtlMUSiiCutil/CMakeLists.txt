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

MESSAGE(STATUS "igtlMUSiiCutil")
# SET( LINK_LIBS ${LINK_LIBS} ${OpenIGTLink_LIBRARIES} )
# Copy "igtl_win32header.h" file to existing OpenIGTLink include directory
# IF(WIN32)
# FILE (COPY "igtl_win32header.h" DESTINATION ${OpenIGTLink_INCLUDE_DIRS})
# ENDIF(WIN32)
if(OpenIGTLinkMUSiiC_BUILD_SHARED_LIBS)
  set(igtlMUSiiCutil_BUILD_SHARED_LIBS ${OpenIGTLinkMUSiiC_BUILD_SHARED_LIBS})
endif(OpenIGTLinkMUSiiC_BUILD_SHARED_LIBS)

if(OpenIGTLinkMUSiiC_BUILD_GENERATE_PIC)
  set(igtluMUSiiCtil_BUILD_GENERATE_PIC ${OpenIGTLinkMUSiiC_BUILD_GENERATE_PIC})
  set(IGTLMUSiiCSTATIC 1)
endif(OpenIGTLinkMUSiiC_BUILD_GENERATE_PIC)

SET(igtlMUSiiCutil_HEADS
  igtl_win32header.h
  igtlM_win32header.h
  igtlM_US.h
  igtlM_EI.h
  igtlM_GEN.h
  igtlM_ARG.h
  igtlM_FILE.h
  )

SET(igtlMUSiiCutil_SOURCES
  igtlM_US.c
  igtlM_EI.c
  igtlM_GEN.c
  igtlM_ARG.c
  igtlM_FILE.c
  )   
  


ADD_LIBRARY(igtlMUSiiCutil
  ${igtlMUSiiCutil_HEADS}
  ${igtlMUSiiCutil_SOURCES}
)

TARGET_LINK_LIBRARIES(igtlMUSiiCutil
 ${LINK_LIBS}
 )

SET_TARGET_PROPERTIES(igtlMUSiiCutil PROPERTIES
  VERSION ${OpenIGTLinkMUSiiC_VERSION_MAJOR}.${OpenIGTLinkMUSiiC_VERSION_MINOR}.${OpenIGTLinkMUSiiC_VERSION_PATCH}
  SOVERSION ${OpenIGTLinkMUSiiC_VERSION_MAJOR}
)
