# - Try to find ARToolKit
# Once done, this will define
#
#  ARToolKit_FOUND - system has ARToolKit
#  ARToolKit_INCLUDE_DIRS - the ARToolKit include directories
#  ARToolKit_LIBRARIES - link these to use ARToolKit

include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(ARToolKit_PKGCONF ARToolKit)

# TODO: Add linux/MacOSX install locations...
SET(ARToolKit_INCLUDE_SEARCH_PATHS "C:/Program Files/ARToolkit/ARToolKit/include")
SET(ARToolKit_LIB_SEARCH_PATHS "C:/Program Files/ARToolkit/ARToolKit/lib")

find_package(GLUT)

# Include dir
find_path(ARToolKit_INCLUDE_DIR
  NAMES "AR/ar.h"
  PATHS ${ARToolKit_INCLUDE_SEARCH_PATHS} ${ARToolKit_PKGCONF_INCLUDE_DIRS}
)

# Find the libraries
find_library(ARToolKit_LIBRARY
  NAMES libAR.a libAR
  PATHS ${ARToolKit_LIB_SEARCH_PATHS} ${ARToolKit_PKGCONF_LIBRARY_DIRS}
)

find_library(ARToolKit_Video_LIBRARY
  NAMES libARvideo.a libARvideo
  PATHS ${ARToolKit_LIB_SEARCH_PATHS} ${ARToolKit_PKGCONF_LIBRARY_DIRS}
)

find_library(ARToolKit_GSub_LIBRARY
  NAMES libARgsub.a libARgsub
  PATHS ${ARToolKit_LIB_SEARCH_PATHS} ${ARToolKit_PKGCONF_LIBRARY_DIRS}
)



# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(ARToolKit_PROCESS_INCLUDES ARToolKit_INCLUDE_DIR)
set(ARToolKit_PROCESS_LIBS ARToolKit_LIBRARY ARToolKit_Video_LIBRARY ARToolKit_GSub_LIBRARY)
libfind_process(ARToolKit)