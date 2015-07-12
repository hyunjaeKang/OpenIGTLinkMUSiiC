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

PROJECT(MUSiiCSyncTest)

cmake_minimum_required(VERSION 2.4)
if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

find_package(OpenIGTLink REQUIRED)

include(${OpenIGTLink_USE_FILE})

find_package(OpenIGTLinkMUSiiC REQUIRED)

include(${OpenIGTLinkMUSiiC_USE_FILE})

#-----------------------------------------------------------------------------
# Setting LINK_LIBS
SET( LINK_LIBS ${LINK_LIBS} ${OpenIGTLink_LIBRARIES} )
SET( LINK_LIBS ${LINK_LIBS} ${OpenIGTLinkMUSiiC_LIBRARIES} )

MESSAGE(STATUS "Example MUSiiCSyncTest Directory")

ADD_EXECUTABLE(TestMUSiiCSync TestMUSiiCSync.cxx)
TARGET_LINK_LIBRARIES(TestMUSiiCSync ${LINK_LIBS})

  