# - Find an OpenIGTLinkMUSiiC installation or build tree.

# When OpenIGTLinkMUSiiC is found, the OpenIGTLinkMUSiiCConfig.cmake file is sourced to setup the
# location and configuration of OpenIGTLinkMUSiiC.  Please read this file, or
# OpenIGTLinkMUSiiCConfig.cmake.in from the OpenIGTLinkMUSiiC source tree for the full list of
# definitions.  Of particular interest is OpenIGTLinkMUSiiC_USE_FILE, a CMake source file
# that can be included to set the include directories, library directories,
# and preprocessor macros.  In addition to the variables read from
# OpenIGTLinkMUSiiCConfig.cmake, this find module also defines
#  OpenIGTLinkMUSiiC_DIR  - The directory containing OpenIGTLinkMUSiiCConfig.cmake.  
#             This is either the root of the build tree, 
#             or the lib/InsightToolkit directory.  
#             This is the only cache entry.
#   
#  OpenIGTLinkMUSiiC_FOUND - Whether OpenIGTLinkMUSiiC was found.  If this is true, 
#              OpenIGTLinkMUSiiC_DIR is okay.
#
#  USE_OpenIGTLinkMUSiiC_FILE - The full path to the UseOpenIGTLinkMUSiiC.cmake file.  
#                 This is provided for backward 
#                 compatability.  Use OpenIGTLinkMUSiiC_USE_FILE
#                 instead.


SET(OpenIGTLinkMUSiiC_DIR_STRING "directory containing OpenIGTLinkMUSiiCConfig.cmake.  This is either the root of the build tree, or PREFIX/lib/igtl for an installation.")

# Search only if the location is not already known.
IF(NOT OpenIGTLinkMUSiiC_DIR)
  # Get the system search path as a list.
  IF(UNIX)
    STRING(REGEX MATCHALL "[^:]+" OpenIGTLinkMUSiiC_DIR_SEARCH1 "$ENV{PATH}")
  ELSE(UNIX)
    STRING(REGEX REPLACE "\\\\" "/" OpenIGTLinkMUSiiC_DIR_SEARCH1 "$ENV{PATH}")
  ENDIF(UNIX)
  STRING(REGEX REPLACE "/;" ";" OpenIGTLinkMUSiiC_DIR_SEARCH2 ${OpenIGTLinkMUSiiC_DIR_SEARCH1})

  # Construct a set of paths relative to the system search path.
  SET(OpenIGTLinkMUSiiC_DIR_SEARCH "")
  FOREACH(dir ${OpenIGTLinkMUSiiC_DIR_SEARCH2})
    SET(OpenIGTLinkMUSiiC_DIR_SEARCH ${OpenIGTLinkMUSiiC_DIR_SEARCH} "${dir}/../lib/igtl")
  ENDFOREACH(dir)

  #
  # Look for an installation or build tree.
  #
  FIND_PATH(OpenIGTLinkMUSiiC_DIR OpenIGTLinkMUSiiCConfig.cmake
    # Look for an environment variable OpenIGTLinkMUSiiC_DIR.
    $ENV{OpenIGTLinkMUSiiC_DIR}

    # Look in places relative to the system executable search path.
    ${OpenIGTLinkMUSiiC_DIR_SEARCH}

    # Look in standard UNIX install locations.
    /usr/local/lib/igtl
    /usr/lib/igtl

    # Read from the CMakeSetup registry entries.  It is likely that
    # OpenIGTLinkMUSiiC will have been recently built.
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild1]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild2]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild3]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild4]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild5]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild6]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild7]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild8]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild9]
    [HKEY_CURRENT_USER\\Software\\Kitware\\CMakeSetup\\Settings\\StartPath;WhereBuild10]

    # Help the user find it if we cannot.
    DOC "The ${OpenIGTLinkMUSiiC_DIR_STRING}"
  )
ENDIF(NOT OpenIGTLinkMUSiiC_DIR)

# If OpenIGTLinkMUSiiC was found, load the configuration file to get the rest of the
# settings.
IF(OpenIGTLinkMUSiiC_DIR)
  SET(OpenIGTLinkMUSiiC_FOUND 1)
  INCLUDE(${OpenIGTLinkMUSiiC_DIR}/OpenIGTLinkMUSiiCConfig.cmake)

  # Set USE_OpenIGTLinkMUSiiC_FILE for backward-compatability.
  SET(USE_OpenIGTLinkMUSiiC_FILE ${OpenIGTLinkMUSiiC_USE_FILE})
ELSE(OpenIGTLinkMUSiiC_DIR)
  SET(OpenIGTLinkMUSiiC_FOUND 0)
  IF(OpenIGTLinkMUSiiC_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Please set OpenIGTLinkMUSiiC_DIR to the ${OpenIGTLinkMUSiiC_DIR_STRING}")
  ENDIF(OpenIGTLinkMUSiiC_FIND_REQUIRED)
ENDIF(OpenIGTLinkMUSiiC_DIR)


