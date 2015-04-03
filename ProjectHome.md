# ColoAPI #

ColoAPI is a library of [H3DAPI](http://www.h3dapi.org/) nodes to support haptic and graphic colocation with headtracking via [ARToolkit](http://sourceforge.net/projects/artoolkit/). Using an ARToolkit marker to indicate the user's head position, the viewpoint can be updated in real time enabling graphics and haptics to remain colocated independent of viewing position. It is designed to be extended to incorporate other tracking systems if needed.

Thanks to Alastair Barrow for helping with the viewpoint geometry calculations.

Please report bugs and comments via googlecode or to neil.david.forrest@gmail.com

## Videos ##

Video demonstrations of ColoAPI:

  * [Simple demo using laptop screen and camera](http://www.youtube.com/watch?v=Gnkhet_wwiw)

  * [Demo using home-made colocation mirror](http://www.youtube.com/watch?v=0RVnBqCGm3M)

## Example Usage ##

Adding viewpoint tracking requires that you specify the parameters of your display and camera and define a viewpoint of type MarkerViewpoint. For example, here we define a mirrored colocation display:

```
	<CameraInfo>
		<ARToolKitCamera position='0 0.69 0.02 ' orientation='6.86043e-009 0.987607 0.156948 3.14159' />
	</CameraInfo>

	<MarkerViewpoint>
		<ARToolKitMarker />
		<ColocationMirroredDisplay>
			<ColocationDisplay 	topLeft='-0.225 0.43 0.225'
				 		topRight='0.225 0.43 0.225'
				 		bottomRight='0.225 0.555 -0.075' />
			<Mirror 	topLeft='-0.245 0.31 -0.075' 
				 	topRight='0.245 0.31 -0.075'
				 	bottomRight='0.245 0.235 0.20' />
		</ColocationMirroredDisplay>
	</MarkerViewpoint>
```

Refer to the examples provided with the source for more information.

## Getting Started ##

  1. Obtain the latest source:
    * [Checkout source via svn](http://code.google.com/p/coloapi/source/checkout) or
    * [Download the source as a zip archive](http://coloapi.googlecode.com/files/coloapi-source-0.1.0.zip)

> 2. Refer to README.txt for build instructions.

## Requirements ##

  * Tested platforms: Windows (XP), Mac (Leopard), Linux (Ubuntu)

  * H3DAPI 2.1 (http://www.h3dapi.org/)

  * ARToolkit >= 2.72 (http://sourceforge.net/projects/artoolkit/)
> > Optional - required for head tracking features

## Compilation ##

  * Generate build files using CMake, e.g. For Visual Studio 2005:
```
	cd build
	mkdir vs
	cd vs
	cmake .. -G"Visual Studio 8 2005"
```

  * Build the BUILD\_ALL target in release mode

  * Build the INSTALL target


## Running Examples ##

  * Print off 'HIRO' pattern from ARToolkit (refer to ARToolkit documentation)

  * Change working directory to the 'examples' directory within the coloapi directory

  * Connect external USB camera if required

  * View any of the example .x3d files using h3dload or h3dviewer


> e.g.
```
		cd examples
		H3DLoad SimpleARTracking.x3d
```

  * Use 'HIRO' marker on forehead to denote head position

  * Refer to ARToolkit documentation for best tracking performance


## Trouble Shooting ##

  * ColoAPI must be built with same compiler and settings as H3DAPI, H3DLoad and H3DViewer.
    * Rebuild all of H3DAPI with your compiler if required.

  * ARToolkit installation location may have to be specified manually via CMake.
    * By default we look for it at C:/Program Files/ARToolkit/
    * Use the CMake GUI or run 'ccmake .' or edit CMakeCache.txt in order to define ARTOOLKIT\_ROOT
      * Set ARTOOLKIT\_ROOT to the ARToolkit installation directory (the one that contains 'include/' and 'lib/') then run cmake again.