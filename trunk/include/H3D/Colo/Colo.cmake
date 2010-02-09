//  Copyright 2010, Neil Forrest
//
//  This file is part of ColoAPI.
//
//  ColoAPI is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  ColoAPI is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with ColoAPI.  If not, see <http://www.gnu.org/licenses/>.
//
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
#cmakedefine HAVE_ARTOOLKIT

#include <H3D/LibraryInfo.h>

// Function to extract information about the library.
extern "C" COLO_API H3D::LibraryInfo getLibraryInfo();

#endif