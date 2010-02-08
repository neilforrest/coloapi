#ifndef __COLO_H__
#define __COLO_H__

// Define dll exports/imports as required on Windows
#if defined(WIN32) || defined(__WIN32__)
#include <windows.h>
#ifdef COLO_EXPORTS
#define COLO_API __declspec(dllexport)
#else
#define COLO_API __declspec(dllimport)
#endif

#ifdef _MSC_VER
// disable dll-interface warnings for stl-exports 
#pragma warning( disable: 4251 )
#endif

#endif

#if defined(__APPLE__) && defined(__MACH__)
#define MACOSX
#define COLO_API
#define HAVE_SYS_TIME_H
#endif

#if defined(__linux)
#define LINUX
#define COLO_API 
#define HAVE_SYS_TIME_H
#endif

#define COLO_MAJOR_VERSION 1
#define COLO_MINOR_VERSION 0
#define COLO_BUILD_VERSION 0

/// Undef if you do not have ARToolkit(http://www.hitl.washington.edu/artoolkit/) installed.
/// Required for viewpoint headtracking via ARToolkit.
#define HAVE_ARTOOLKIT

#include <H3D/LibraryInfo.h>

// Function to extract information about the library.
extern "C" COLO_API H3D::LibraryInfo getLibraryInfo();

#endif
