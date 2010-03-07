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
#include <H3D/Colo/Colo.h>
#ifdef HAVE_ARTOOLKIT

#include <H3D/Colo/ARToolKitCamera.h>
#include <H3D/Colo/ARToolKitMarker.h>
#include <AR/gsub.h>

using namespace H3D;

namespace
{
	// Set a default camera configuration string for target OS
#ifdef _WIN32
	const char* vconf = "ARData/WDM_camera_flipV.xml";
#else
	const char* vconf = "";
#endif	
}

// Add this node to the H3DNodeDatabase system.
H3DNodeDatabase ARToolKitCamera::database( "ARToolKitCamera", 
										   &(newInstance<ARToolKitCamera>), 
										   typeid( ARToolKitCamera ),
										   &H3DCamera::database );

// Add the x3d field interface.
namespace ARToolKitCameraInternals 
{
	FIELDDB_ELEMENT( ARToolKitCamera, videoConfiguration, INITIALIZE_ONLY );
	FIELDDB_ELEMENT( ARToolKitCamera, cameraParametersFilename, INITIALIZE_ONLY );
}

// Constructor
ARToolKitCamera::ARToolKitCamera (  Inst< SFNode>		_metadata,
									Inst< SFVec3f >		_position,
									Inst< SFRotation >	_orientation,
								    Inst< SFString >	_videoConfiguration,
									Inst< SFString >	_cameraParametersFilename )
: H3DCamera ( _metadata, _position, _orientation ),
  videoConfiguration ( _videoConfiguration ),
  cameraParametersFilename ( _cameraParametersFilename ),
  ARTVideo ( NULL ),
  ARTImage ( NULL ),
  marker_info ( NULL ),
  marker_num ( 0 )
{
	type_name = "ARToolKitCamera";
	database.initFields( this );

	// Set default camera parameters
	videoConfiguration->setValue ( vconf );
	cameraParametersFilename->setValue ( "ARData/camera_para.dat" );
}

// Destructor
ARToolKitCamera::~ARToolKitCamera()
{
	// Stop and clean up this video context
	ar2VideoCapStop(ARTVideo);
	ar2VideoClose(ARTVideo);
}

// Initialise the camera
void ARToolKitCamera::initialize ()
{
	ARParam wparam;
	int xsize, ysize;

	// Open the video path.
	if ((ARTVideo = ar2VideoOpen(const_cast<char*>(videoConfiguration->getValue().c_str()))) == NULL) {
		Console(3) << "Unable to open connection to camera." << endl;
		return;
	}

	// TODO: If above step fails on MacOSX we get a crash
	
	// Find the size of the window.
	if (ar2VideoInqSize(ARTVideo, &xsize, &ysize) < 0) return;

	// Load the camera parameters, resize for the window and init.
	if (arParamLoad(cameraParametersFilename->getValue().c_str(), 1, &wparam) < 0) {
		Console(3) << "Error loading parameter file for camera." << endl;
		return;
	}
	arParamChangeSize(&wparam, xsize, ysize, &ARTCparam);
	arInitCparam(&ARTCparam);

	arParamDisp(&ARTCparam);
	//ARTThreshhold = 100;

	// Start the video capture for this camera.
	if (ar2VideoCapStart(ARTVideo) != 0) {
		Console(3) << "Unable to begin camera data capture for camera." << endl;
		return;
	}
}

// Override updateCamera in order to grab and process the camera image each frame
void ARToolKitCamera::updateCamera ( )
{
	H3DCamera::updateCamera ( );

	ARUint8 *image;

	// Grab a video frame.
	if ((image = ar2VideoGetImage(ARTVideo)) != NULL)
	{
		ARTImage = image;	// Save the fetched image.
				
		// Detect the markers in the video frame.
		if (int result= arDetectMarker(ARTImage, 100, &marker_info, &marker_num) < 0) {
			Console (3) << "arDetectMarker() reports an error code " << result << endl;
		}
	}
}

// Get the transformation of the specified marker using this camera
// \param[in] marker The marker instance
// \param[out] translation The translation for the marker in world coordinates
// \param[out] rotation The rotation for the marker in world coordinates
// \return true if successful, or false otherwise.
bool ARToolKitCamera::updateMarker ( const H3DMarker& marker, Vec3f& translation, Rotation& rotation )
{
	const ARToolKitMarker* artkMarker= dynamic_cast < const ARToolKitMarker* > ( &marker );
	if ( artkMarker )
	{
		// Get the detected marker information
		int k= getDetectedMarkerIndex ( artkMarker->getPatternId() );

		if ( k == -1 )
		{
			// Marker is not visible
			return false;
		}

		// Pattern centre (in)
		double patternCentre[2]= {	artkMarker->patternCentre->getValue().x,
									artkMarker->patternCentre->getValue().y };

		// Pattern transform (out)
		double pt[3][4];

		// Get the transformation between the marker and the real camera into pt.
		arGetTransMat( &(marker_info[k]), 
						patternCentre, 
						artkMarker->patternWidth->getValue(), 
						pt );

		// Get the transformation of the marker in local coordinates
		double m[16];
		argConvGlpara ( pt, m );
		
		Matrix4f transform= 
			Matrix4f (  (float)m[0], (float)m[4], (float)m[8], (float)m[12]/1000.0f /* mm -> m */, 
						(float)m[1], (float)m[5], (float)m[9], (float)m[13]/1000.0f, 
						(float)m[2], (float)m[6], (float)m[10], (float)m[14]/1000.0f, 
						0.0f, 0.0f, 0.0f, 1.0f );
		
		// Because y and z axis are inverted, rotate 180 around x
		transform= Rotation ( 1, 0, 0, (H3DFloat)H3DUtil::Constants::pi ) * transform;

		// Set marker translation
		translation= transform.getTranslationPart();
		
		// Set marker rotation
    rotation= Rotation ( transform.getRotationPart().inverse() );
		
		return true;
	}
	else
	{
		return false;
	}
}

// Get the index of the specified pattern id in the detected markers array having the highest confidence
// \return The index of the specified marker, or -1 if not found
int ARToolKitCamera::getDetectedMarkerIndex ( int markerId )
{
	// Check through the marker_info array for highest confidence
	// visible marker matching our preferred pattern.
	int k = -1;
	for (int j = 0; j < marker_num; j++) 
	{
		if ( marker_info[j].id == markerId ) 
		{
			if (k == -1) k = j; // First marker detected.
			else if(marker_info[j].cf > marker_info[k].cf) k = j; // Higher confidence marker detected.
		}
	}

	return k;
}

#endif //HAVE_ARTOOLKIT