ColoAPI (http://coloapi.googlecode.com)
========================================================
Neil Forrest 2010 (neil.david.forrest@gmail.com)
--------------------------------------------------------

ColoAPI is a library of H3DAPI nodes to support haptic and graphic colocation with headtracking 
via ARToolkit. Using an ARToolkit marker to indicate the users head position, the viewpoint 
can be updated in real time enabling graphics and haptics to remain colocated independent of 
viewing position.

Requirements
------------

 * H3DAPI 2.1 (www.h3dapi.org)

 Optional - required for head tracking features
 * ARToolkit >= 2.72 (http://sourceforge.net/projects/artoolkit/)

Compilation
-----------

 * Generate build files using CMake, e.g. For Visual Studio 2005:

	cd build
	mkdir vs
	cd vs
	cmake .. -G"Visual Studio 8 2005"

 * Build the BUILD_ALL target in release mode

 * Build the INSTALL target


Running Examples
----------------

 * Print off 'HIRO' pattern from ARToolkit (refer to ARToolkit documentation)

 * Change working directory to the 'examples' directory within the coloapi directory

 * Connect external USB camera if required

 * View any of the example .x3d files using h3dload or h3dviewer

	e.g.
		cd examples
		h3dload SimpleARTracking.x3d

 * Use 'HIRO' marker on forehead to denote head position

 * Refer to ARToolkit documentation for best tracking performance


Trouble Shooting
----------------

 * ColoAPI must be built with same compiler and settings as H3DAPI, H3DLoad and H3DViewer. 
   Rebuild all of H3DAPI with your compiler if required.

 * ARToolkit installation location may have to be specified manually via CMake
   Use the CMake GUI or run 'ccmake .' or edit CMakeCache.txt in order to define ARTOOLKIT_ROOT
   Set ARTOOLKIT_ROOT to the ARToolkit installation directory (the one that contains 'include/' and 'lib/')
   then run cmake again.


SimpleARTracking.x3d
--------------------

Simple ARToolkit head tracking colocation example where monitor is in x-y plane (center at 0, 0, 0) and
camera is placed above display looking along the display normal.

Adjust corners of display and camera position to match your measurements.


MirroredARTracking.x3d
----------------------

This demo defines a mirrored colocation display by defining 3 corners of the actual display
and 3 corners of the mirror.

Adjust corners of display and mirror and camera position to match your measurements.

NOTE: The "Mirror in Y" option should be enabled in the viewer.


FixedViewpoint.x3d
------------------

This demo uses a fixed viewing position (not tracked by ARToolkit or other) and the graphics are rendered
based on this specified position and the specified parameters of the display (and mirror, if present).

This demo should function without ARToolkit installed.


Bugs and Comments
-----------------

Please report bugs and comments via googlecode (http://coloapi.googlecode.com) or to neil.david.forrest@gmail.com
