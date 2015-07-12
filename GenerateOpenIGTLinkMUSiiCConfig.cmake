# Generate the OpenIGTLinkMUSiiCConfig.cmake file in the build tree.  Also configure
# one for installation.  The file tells external projects how to use
# OpenIGTLinkMUSiiC.

#-----------------------------------------------------------------------------
# Settings specific to the build tree.

# Generate CMake lines that will define the OpenIGTLinkMUSiiC_SOURCE_DIR in the OpenIGTLinkMUSiiCConfig.cmake.
# We want this to happen only in the OpenIGTLinkMUSiiCConfig.cmake of the build dir, not in the
# installed or relocatable one.
SET(OpenIGTLinkMUSiiC_CONFIG_CODE "
# The OpenIGTLinkMUSiiC source tree.
# For backward compatibility issues we still need to define this variable, although
# it is highly probable that it will cause more harm than being useful. 
# Use OpenIGTLinkMUSiiC_INCLUDE_DIRS instead, since OpenIGTLinkMUSiiC_SOURCE_DIR may point to non-existent directory
IF(NOT OpenIGTLinkMUSiiC_LEGACY_REMOVE)
  SET(OpenIGTLinkMUSiiC_SOURCE_DIR \"${OpenIGTLinkMUSiiC_SOURCE_DIR}\")
ENDIF(NOT OpenIGTLinkMUSiiC_LEGACY_REMOVE)"
)

# The "use" file.
SET(OpenIGTLinkMUSiiC_USE_FILE ${OpenIGTLinkMUSiiC_BINARY_DIR}/UseOpenIGTLinkMUSiiC.cmake)

# The build settings file.
SET(OpenIGTLinkMUSiiC_BUILD_SETTINGS_FILE ${OpenIGTLinkMUSiiC_BINARY_DIR}/OpenIGTLinkMUSiiCBuildSettings.cmake)

# Library directory.
SET(OpenIGTLinkMUSiiC_LIBRARY_DIRS_CONFIG ${OpenIGTLinkMUSiiC_LIBRARY_PATH})

# Determine the include directories needed.
SET(OpenIGTLinkMUSiiC_INCLUDE_DIRS_CONFIG
  ${OpenIGTLinkMUSiiC_INCLUDE_DIRS_BUILD_TREE}
  ${OpenIGTLinkMUSiiC_INCLUDE_DIRS_SYSTEM}
)

#-----------------------------------------------------------------------------
# Configure OpenIGTLinkMUSiiCConfig.cmake for the build tree.
CONFIGURE_FILE(${OpenIGTLinkMUSiiC_SOURCE_DIR}/OpenIGTLinkMUSiiCConfig.cmake.in
               ${OpenIGTLinkMUSiiC_BINARY_DIR}/OpenIGTLinkMUSiiCConfig.cmake @ONLY IMMEDIATE)

#-----------------------------------------------------------------------------
# Settings specific to the install tree.

# The library dependencies file.
SET(OpenIGTLinkMUSiiC_LIBRARY_DEPENDS_FILE "\${OpenIGTLinkMUSiiC_INSTALL_PREFIX}/${OpenIGTLinkMUSiiC_INSTALL_PACKAGE_DIR}/OpenIGTLinkMUSiiCLibraryDepends.cmake")

# The "use" file.
SET(OpenIGTLinkMUSiiC_USE_FILE \${OpenIGTLinkMUSiiC_INSTALL_PREFIX}/${OpenIGTLinkMUSiiC_INSTALL_PACKAGE_DIR}/UseOpenIGTLinkMUSiiC.cmake)

# The build settings file.
SET(OpenIGTLinkMUSiiC_BUILD_SETTINGS_FILE \${OpenIGTLinkMUSiiC_INSTALL_PREFIX}/${OpenIGTLinkMUSiiC_INSTALL_PACKAGE_DIR}/OpenIGTLinkMUSiiCBuildSettings.cmake)

# Include directories.
SET(OpenIGTLinkMUSiiC_INCLUDE_DIRS_CONFIG \${OpenIGTLinkMUSiiC_INSTALL_PREFIX}/${OpenIGTLinkMUSiiC_INSTALL_INCLUDE_DIR})
FOREACH(DIR ${OpenIGTLinkMUSiiC_INCLUDE_RELATIVE_DIRS})
  LIST(APPEND OpenIGTLinkMUSiiC_INCLUDE_DIRS_CONFIG \${OpenIGTLinkMUSiiC_INSTALL_PREFIX}/${OpenIGTLinkMUSiiC_INSTALL_INCLUDE_DIR}/${DIR})
ENDFOREACH(DIR)
IF(OpenIGTLinkMUSiiC_INCLUDE_DIRS_SYSTEM)
  LIST(APPEND OpenIGTLinkMUSiiC_INCLUDE_DIRS_CONFIG ${OpenIGTLinkMUSiiC_INCLUDE_DIRS_SYSTEM})
ENDIF(OpenIGTLinkMUSiiC_INCLUDE_DIRS_SYSTEM)

# Link directories.
SET(OpenIGTLinkMUSiiC_LIBRARY_DIRS_CONFIG "\${OpenIGTLinkMUSiiC_INSTALL_PREFIX}/${OpenIGTLinkMUSiiC_INSTALL_LIB_DIR}")

#-----------------------------------------------------------------------------
# Configure OpenIGTLinkMUSiiCConfig.cmake for the install tree.

# Construct the proper number of GET_FILENAME_COMPONENT(... PATH)
# calls to compute the installation prefix.
STRING(REGEX REPLACE "/" ";" OpenIGTLinkMUSiiC_INSTALL_PACKAGE_DIR_COUNT
  "${OpenIGTLinkMUSiiC_INSTALL_PACKAGE_DIR}")
SET(OpenIGTLinkMUSiiC_CONFIG_CODE "
# Compute the installation prefix from this OpenIGTLinkMUSiiCConfig.cmake file location.
GET_FILENAME_COMPONENT(OpenIGTLinkMUSiiC_INSTALL_PREFIX \"\${CMAKE_CURRENT_LIST_FILE}\" PATH)")
FOREACH(p ${OpenIGTLinkMUSiiC_INSTALL_PACKAGE_DIR_COUNT})
  SET(OpenIGTLinkMUSiiC_CONFIG_CODE
    "${OpenIGTLinkMUSiiC_CONFIG_CODE}\nGET_FILENAME_COMPONENT(OpenIGTLinkMUSiiC_INSTALL_PREFIX \"\${OpenIGTLinkMUSiiC_INSTALL_PREFIX}\" PATH)"
    )
ENDFOREACH(p)


CONFIGURE_FILE(${OpenIGTLinkMUSiiC_SOURCE_DIR}/OpenIGTLinkMUSiiCConfig.cmake.in
               ${OpenIGTLinkMUSiiC_BINARY_DIR}/Utilities/OpenIGTLinkMUSiiCConfig.cmake @ONLY IMMEDIATE)

