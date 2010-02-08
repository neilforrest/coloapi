IF(WIN32)
  cmake_minimum_required(VERSION 2.6.0)
ENDIF(WIN32)

# The name of our project is "ColoAPI".  CMakeLists files in this project can
# refer to the root source directory of the project as ${ColoAPI_SOURCE_DIR} and
# to the root binary directory of the project as ${ColoAPI_BINARY_DIR}.
project (ColoAPI)

# Where to find Source files.
SET( ColoAPI_SRCS "${ColoAPI_SOURCE_DIR}/../src/ARToolKitCamera.cpp"
			    "${ColoAPI_SOURCE_DIR}/../src/ARToolKitMarker.cpp"
			    "${ColoAPI_SOURCE_DIR}/../src/H3DCamera.cpp"
			    "${ColoAPI_SOURCE_DIR}/../src/H3DMarker.cpp"
			    "${ColoAPI_SOURCE_DIR}/../src/CameraInfo.cpp"
			    "${ColoAPI_SOURCE_DIR}/../src/MarkerViewpoint.cpp"
			    "${ColoAPI_SOURCE_DIR}/../src/ColocationDisplay.cpp"
			    "${ColoAPI_SOURCE_DIR}/../src/ColocationMirroredDisplay.cpp"
			    "${ColoAPI_SOURCE_DIR}/../src/Mirror.cpp"
			    "${ColoAPI_SOURCE_DIR}/../src/ColocationViewpoint.cpp"
			    "${ColoAPI_SOURCE_DIR}/../src/Plane.cpp"
			    "${ColoAPI_SOURCE_DIR}/../src/Colo.cpp" )

# Include directories.
INCLUDE_DIRECTORIES( ../src )
INCLUDE_DIRECTORIES( ../include )

# Add optional libs to this variable.
SET(optionalLibs)

# Add required libs to this variable.
SET(requiredLibs)

# Where to find modules, used when finding packages.
SET(CMAKE_MODULE_PATH "$ENV{H3D_ROOT}/build/modules"
                      "${ColoAPI_SOURCE_DIR}/modules")
INCLUDE( StripAndAddLibraryDirectories )

# ARToolkit
# Optional - but essential to viewpoint tracking via ARToolkit
FIND_PACKAGE(ARToolkit)

IF(ARToolKit_FOUND)
  SET(HAVE_ARTOOLKIT 1)
  INCLUDE_DIRECTORIES( ${ARToolKit_INCLUDE_DIRS} )
  SET(optionalLibs ${optionalLibs} ${ARToolKit_LIBRARIES} )
ELSE(ARToolKit_FOUND)
  IF(NOT DEFINED ARTOOLKIT_ROOT)
    SET(ARTOOLKIT_ROOT "" CACHE PATH "Set this to the root directory of your ARToolkit installation (the dir that contains ./include and ./lib")
  ENDIF(NOT DEFINED ARTOOLKIT_ROOT)
ENDIF(ARToolKit_FOUND)

#H3DAPI
FIND_PACKAGE(H3DAPI REQUIRED)

IF(H3DAPI_FOUND)
  INCLUDE_DIRECTORIES( ${H3DAPI_INCLUDE_DIR} )
  SET(requiredLibs ${requiredLibs} ${H3DAPI_LIBRARIES} )
ENDIF(H3DAPI_FOUND)

#H3DUtil
FIND_PACKAGE(H3DUtil REQUIRED)

IF(H3DUTIL_FOUND)
  INCLUDE_DIRECTORIES( ${H3DUTIL_INCLUDE_DIR} ) 
  SET(requiredLibs ${requiredLibs} ${H3DUTIL_LIBRARIES} )
ENDIF(H3DUTIL_FOUND)

#HAPI
FIND_PACKAGE(HAPI REQUIRED)

IF(HAPI_FOUND)
  INCLUDE_DIRECTORIES( ${HAPI_INCLUDE_DIR} ) 
  SET(requiredLibs ${requiredLibs} ${HAPI_LIBRARIES} )
ENDIF(HAPI_FOUND)

# If on Mac we need to include the QuickTime framework
IF(APPLE)
   #SET(GUI_TYPE MACOSX_BUNDLE)
   INCLUDE_DIRECTORIES ( /Developer/Headers/FlatCarbon )
   FIND_LIBRARY(CARBON_LIBRARY Carbon)
   FIND_LIBRARY(QUICKTIME_LIBRARY QuickTime )
   FIND_LIBRARY(APP_SERVICES_LIBRARY ApplicationServices )
   MARK_AS_ADVANCED (CARBON_LIBRARY
                     QUICKTIME_LIBRARY
                     APP_SERVICES_LIBRARY)
   SET(EXTRA_LIBS ${CARBON_LIBRARY} ${QUICKTIME_LIBRARY} ${APP_SERVICES_LIBRARY})
ENDIF (APPLE)

# NF: Added this to compile on Mac
# Optional extra library. Without this H3D API can not load scenes defined with X3D syntax.
FIND_PACKAGE(Xerces)
IF(XERCES_FOUND)
  SET(HAVE_XERCES 1)
  INCLUDE_DIRECTORIES( ${XERCES_INCLUDE_DIR} ) 
  SET(optionalLibs ${optionalLibs} ${XERCES_LIBRARIES} )
ENDIF(XERCES_FOUND)

# OpenGL
FIND_PACKAGE(OpenGL REQUIRED)

IF(OPENGL_FOUND)
  INCLUDE_DIRECTORIES( ${OPENGL_INCLUDE_DIR} ) 
  SET(requiredLibs ${requiredLibs} ${OPENGL_LIBRARIES} )
ENDIF(OPENGL_FOUND)

# Glut.
FIND_PACKAGE(GLUT REQUIRED)

IF( NOT GLUT_FOUND AND WIN32 )
  FIND_PACKAGE(GLUTWin REQUIRED)
ENDIF( NOT GLUT_FOUND AND WIN32 )

IF(GLUT_FOUND)
  INCLUDE_DIRECTORIES( ${GLUT_INCLUDE_DIR} )
  IF( WIN32 )
    STRIP_AND_ADD_LIBRARY_DIRECTORIES( ${GLUT_LIBRARIES} )
  ELSE( WIN32 )
    SET(requiredLibs ${requiredLibs} ${GLUT_LIBRARIES} )
  ENDIF( WIN32 )
ENDIF(GLUT_FOUND)

# Define compile flags for all configurations, then add to them
SET( ColoAPI_COMPILE_FLAGS "" )

# Create build files.

# make sure symbols are exported by defining some symbols on the command line
SET( ColoAPI_COMPILE_FLAGS "${ColoAPI_COMPILE_FLAGS} -DCOLO_EXPORTS" )

ADD_LIBRARY ( ColoAPI SHARED ${ColoAPI_SRCS})

TARGET_LINK_LIBRARIES( ColoAPI ${requiredLibs} ${optionalLibs} ${EXTRA_LIBS} )

# Debug version should have _d postfix.
SET_TARGET_PROPERTIES( ColoAPI PROPERTIES DEBUG_POSTFIX "_d" )

# set the install directory to the H3D directory on Windows
IF(WIN32) 
  # Set compile and link properties for projects.
  IF(MSVC80)
    # Remove some warnings about deprecated functions. Do not treat wchar_t as built in type
    SET( ColoAPI_COMPILE_FLAGS "${ColoAPI_COMPILE_FLAGS} -D_CRT_SECURE_NO_DEPRECATE /Zc:wchar_t-" )
  ELSEIF(MSVC90)
    # Remove some warnings about deprecated functions. Do not treat wchar_t as built in type. Compile on multiple processors/threads if possible.
    SET( ColoAPI_COMPILE_FLAGS "${ColoAPI_COMPILE_FLAGS} -D_CRT_SECURE_NO_DEPRECATE /Zc:wchar_t- /MP" )
  ENDIF(MSVC80)
ENDIF(WIN32)
#Set install dir
SET( CMAKE_INSTALL_PREFIX ${ColoAPI_SOURCE_DIR}/.. CACHE PATH "Install path prefix, prepended onto install directories." FORCE )

# apply compile flags for project
SET_TARGET_PROPERTIES( ColoAPI PROPERTIES COMPILE_FLAGS "${ColoAPI_COMPILE_FLAGS}" )

# autogenerate Colo.h depending on the libraries available.
CONFIGURE_FILE( ${ColoAPI_SOURCE_DIR}/../include/H3D/Colo/Colo.cmake ${ColoAPI_SOURCE_DIR}/../include/H3D/Colo/Colo.h )

# Install to this destination.
INSTALL( TARGETS ColoAPI
         LIBRARY DESTINATION lib
         RUNTIME DESTINATION bin
	 ARCHIVE DESTINATION lib )

