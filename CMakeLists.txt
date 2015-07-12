PROJECT( OpenIGTLinkMUSiiC )

cmake_minimum_required(VERSION 2.4)

if(COMMAND cmake_policy)
     cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

#-----------------------------------------------------------------------------
# OpenIGTlinkMUSiiC version number.
SET(OpenIGTLinkMUSiiC_VERSION_MAJOR "1")
SET(OpenIGTLinkMUSiiC_VERSION_MINOR "0")
SET(OpenIGTLinkMUSiiC_VERSION_PATCH "0")

#-----------------------------------------------------------------------------
# Find OpenIGTlink 
FIND_PACKAGE(OpenIGTLink REQUIRED)

IF(OpenIGTLink_FOUND)
	INCLUDE(${OpenIGTLink_USE_FILE})
	MESSAGE ( STATUS "OpenIGTLink is found!" )
ELSE(OpenIGTLink_FOUND)
	MESSAGE( FATAL_ERROR "This library requires OpenIGTLink. One of these components is missing. Please verify configuration.")
ENDIF(OpenIGTLink_FOUND)

#-----------------------------------------------------------------------------
# OpenIGTLinkMUSiiC build configuration options.

OPTION(BUILD_SHARED_LIBS "Build OpenIGTLinkMUSiiC with shared libraries." OFF)
SET(OpenIGTLinkMUSiiC_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})

OPTION(BUILD_EXAMPLES "Build OpenIGTLinkMUSiiC example programs." OFF)
SET(OpenIGTLinkMUSiiC_BUILD_EXAMPLES ${BUILD_EXAMPLES})

#-----------------------------------------------------------------------------
# Output directories.

IF(NOT LIBRARY_OUTPUT_PATH)
  SET (LIBRARY_OUTPUT_PATH ${OpenIGTLinkMUSiiC_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all libraries.")
ENDIF(NOT LIBRARY_OUTPUT_PATH)
IF(NOT EXECUTABLE_OUTPUT_PATH)
  SET (EXECUTABLE_OUTPUT_PATH ${OpenIGTLinkMUSiiC_BINARY_DIR}/bin CACHE INTERNAL "Single output directory for building all executables.")
ENDIF(NOT EXECUTABLE_OUTPUT_PATH)
MARK_AS_ADVANCED(LIBRARY_OUTPUT_PATH EXECUTABLE_OUTPUT_PATH)

SET(OpenIGTLinkMUSiiC_LIBRARY_PATH "${LIBRARY_OUTPUT_PATH}")
SET(OpenIGTLinkMUSiiC_EXECUTABLE_PATH "${EXECUTABLE_OUTPUT_PATH}")

SET(OpenIGTLinkMUSiiC_CMAKE_DIR "${OpenIGTLinkMUSiiC_SOURCE_DIR}/CMake")
SET(CMAKE_MODULE_PATH "${OpenIGTLinkMUSiiC_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})

#-----------------------------------------------------------------------------
# Installation vars.
# OpenIGTLinkMUSiiC_INSTALL_BIN_DIR          - binary dir (executables)
# OpenIGTLinkMUSiiC_INSTALL_LIB_DIR          - library dir (libs)
# OpenIGTLinkMUSiiC_INSTALL_DATA_DIR         - share dir (say, examples, data, etc)
# OpenIGTLinkMUSiiC_INSTALL_INCLUDE_DIR      - include dir (headers)
# OpenIGTLinkMUSiiC_INSTALL_PACKAGE_DIR      - package/export configuration files
# OpenIGTLinkMUSiiC_INSTALL_NO_DEVELOPMENT   - do not install development files
# OpenIGTLinkMUSiiC_INSTALL_NO_RUNTIME       - do not install runtime files
# OpenIGTLinkMUSiiC_INSTALL_NO_DOCUMENTATION - do not install documentation files

IF(NOT OpenIGTLinkMUSiiC_INSTALL_BIN_DIR)
  SET(OpenIGTLinkMUSiiC_INSTALL_BIN_DIR "bin")
ENDIF(NOT OpenIGTLinkMUSiiC_INSTALL_BIN_DIR)

IF(NOT OpenIGTLinkMUSiiC_INSTALL_LIB_DIR)
  SET(OpenIGTLinkMUSiiC_INSTALL_LIB_DIR "lib/igtl")
ENDIF(NOT OpenIGTLinkMUSiiC_INSTALL_LIB_DIR)

IF(NOT OpenIGTLinkMUSiiC_INSTALL_DATA_DIR)
  SET(OpenIGTLinkMUSiiC_INSTALL_DATA_DIR "share/igtl")
ENDIF(NOT OpenIGTLinkMUSiiC_INSTALL_DATA_DIR)

IF(NOT OpenIGTLinkMUSiiC_INSTALL_INCLUDE_DIR)
  SET(OpenIGTLinkMUSiiC_INSTALL_INCLUDE_DIR "include/igtl")
ENDIF(NOT OpenIGTLinkMUSiiC_INSTALL_INCLUDE_DIR)

IF(NOT OpenIGTLinkMUSiiC_INSTALL_PACKAGE_DIR)
  SET(OpenIGTLinkMUSiiC_INSTALL_PACKAGE_DIR ${OpenIGTLinkMUSiiC_INSTALL_LIB_DIR}
    CACHE INTERNAL "")
ENDIF(NOT OpenIGTLinkMUSiiC_INSTALL_PACKAGE_DIR)

IF(NOT OpenIGTLinkMUSiiC_INSTALL_NO_DOCUMENTATION)
  SET(OpenIGTLinkMUSiiC_INSTALL_NO_DOCUMENTATION 0)
ENDIF(NOT OpenIGTLinkMUSiiC_INSTALL_NO_DOCUMENTATION)

SET(OpenIGTLinkMUSiiC_DIR "${CMAKE_BINARY_DIR}" CACHE INTERNAL "OpenIGTLinkMUSiiC dir to be used by subprojects")


#-----------------------------------------------------------------------------
# Include directories

SET(OpenIGTLinkMUSiiC_INCLUDE_DIRS_BUILD_TREE ${OpenIGTLinkMUSiiC_INCLUDE_DIRS_BUILD_TREE}
  ${OpenIGTLinkMUSiiC_BINARY_DIR}
  ${OpenIGTLinkMUSiiC_SOURCE_DIR}/Source
  ${OpenIGTLinkMUSiiC_SOURCE_DIR}/Source/igtlMUSiiCutil
)

INCLUDE_DIRECTORIES(
  ${OpenIGTLinkMUSiiC_INCLUDE_DIRS_BUILD_TREE}
  )
  
#-----------------------------------------------------------------------------
# Generate Configuration Header files.
# Can I delete this part?

include (${OpenIGTLinkMUSiiC_SOURCE_DIR}/OpenIGTLinkMUSiiCConfigPlatform.cmake)

CONFIGURE_FILE(${OpenIGTLinkMUSiiC_SOURCE_DIR}/igtlMConfigure.h.in 
  ${OpenIGTLinkMUSiiC_BINARY_DIR}/igtlMConfigure.h)

CONFIGURE_FILE(${OpenIGTLinkMUSiiC_SOURCE_DIR}/igtlM_typeconfig.h.in 
  ${OpenIGTLinkMUSiiC_BINARY_DIR}/igtlM_typeconfig.h)

CONFIGURE_FILE(${OpenIGTLinkMUSiiC_SOURCE_DIR}/igtlMTypeConfig.h.in 
  ${OpenIGTLinkMUSiiC_BINARY_DIR}/igtlMTypeConfig.h)
  
 #-----------------------------------------------------------------------------
# Help other projects use OpenIGTLinkMUSiiC.

# Copy the UseOpenIGTLinkMUSiiC.cmake file to the binary tree for backward compatability.
CONFIGURE_FILE(${OpenIGTLinkMUSiiC_SOURCE_DIR}/UseOpenIGTLinkMUSiiC.cmake.in
${OpenIGTLinkMUSiiC_BINARY_DIR}/UseOpenIGTLinkMUSiiC.cmake COPYONLY IMMEDIATE)

# Create the OpenIGTLinkMUSiiCConfig.cmake file containing the OpenIGTLinkMUSiiC configuration.
INCLUDE (${OpenIGTLinkMUSiiC_SOURCE_DIR}/GenerateOpenIGTLinkMUSiiCConfig.cmake)

# Save the compiler settings so another project can import them.
INCLUDE(${CMAKE_ROOT}/Modules/CMakeExportBuildSettings.cmake)
CMAKE_EXPORT_BUILD_SETTINGS(${OpenIGTLinkMUSiiC_BINARY_DIR}/OpenIGTLinkMUSiiCBuildSettings.cmake)

# Save library dependencies.
#EXPORT_LIBRARY_DEPENDENCIES(${OpenIGTLink_BINARY_DIR}/OpenIGTLinkLibraryDepends.cmake)

INSTALL(FILES
  ${OpenIGTLinkMUSiiC_BINARY_DIR}/OpenIGTLinkMUSiiCBuildSettings.cmake
#  ${OpenIGTLink_BINARY_DIR}/OpenIGTLinkLibraryDepends.cmake
  ${OpenIGTLinkMUSiiC_BINARY_DIR}/UseOpenIGTLinkMUSiiC.cmake
  ${OpenIGTLinkMUSiiC_BINARY_DIR}/Utilities/OpenIGTLinkMUSiiCConfig.cmake
  DESTINATION ${OpenIGTLinkMUSiiC_INSTALL_PACKAGE_DIR}
  COMPONENT Development
  )

INSTALL(FILES
  ${OpenIGTLinkMUSiiC_BINARY_DIR}/igtlMConfigure.h
  DESTINATION ${OpenIGTLinkMUSiiC_INSTALL_INCLUDE_DIR}
  COMPONENT Development
  )

INSTALL(FILES
  ${OpenIGTLinkMUSiiC_BINARY_DIR}/igtlM_typeconfig.h
  DESTINATION ${OpenIGTLinkMUSiiC_INSTALL_INCLUDE_DIR}
  COMPONENT Development
  )

INSTALL(FILES
  ${OpenIGTLinkMUSiiC_BINARY_DIR}/igtlMTypeConfig.h
  DESTINATION ${OpenIGTLinkMUSiiC_INSTALL_INCLUDE_DIR}
  COMPONENT Development
  ) 
  
Message( STATUS ${OpenIGTLinkMUSiiC_INSTALL_PREFIX})
#-----------------------------------------------------------------------------
# Add compiler flags OpenIGTLink needs to work on this platform.  This must be
# done AFTER the call to CMAKE_EXPORT_BUILD_SETTINGS.

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenIGTLinkMUSiiC_REQUIRED_C_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenIGTLinkMUSiiC_REQUIRED_CXX_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenIGTLinkMUSiiC_REQUIRED_LINK_FLAGS}")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${OpenIGTLinkMUSiiC_REQUIRED_LINK_FLAGS}")
SET(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${OpenIGTLinkMUSiiC_REQUIRED_LINK_FLAGS}")



#-----------------------------------------------------------------------------
# Configure Subdirectories

ADD_SUBDIRECTORY(Source)

IF(OpenIGTLinkMUSiiC_BUILD_EXAMPLES)
 ADD_SUBDIRECTORY( Examples )
ENDIF(OpenIGTLinkMUSiiC_BUILD_EXAMPLES)