#ifndef __ARTOOLKITCAMERA_H__
#define __ARTOOLKITCAMERA_H__

#include <H3D/Colo/H3DCamera.h>
#include <H3D/SFString.h>
#include <AR/config.h>
#include <AR/video.h>
#include <AR/param.h>			// arParamDisp()
#include <AR/ar.h>
#include <AR/gsub_lite.h>

namespace H3D
{
	class ARToolKitMarker;

	/// Represents a camera in the ARToolkit
	class COLO_API ARToolKitCamera : public H3DCamera
	{
	public:
		/// Constructor
		ARToolKitCamera (	Inst< SFNode>		_metadata= 0,
							Inst< SFVec3f >		_position= 0,
							Inst< SFRotation >	_orientation= 0,
							Inst< SFString >	_videoConfiguration= 0,
							Inst< SFString >	_cameraParametersFilename= 0 );

		/// Destructor
		virtual ~ARToolKitCamera();

		/// Initialise the camera
		virtual void initialize ();

		/// Perform any per frame processing required. e.g. Grab and process a video frame
		/// Called every scene traversal
		/// Override updateCamera in order to grab and process the camera image each frame
		virtual void updateCamera ( );

		/// Get the transformation of the specified marker using this camera
		/// \param[in] marker The marker instance
		/// \param[out] translation The translation for the marker in world coordinates
		/// \param[out] rotation The rotation for the marker in world coordinates
		/// \return true if successful, or false otherwise
		virtual bool updateMarker ( const H3DMarker& marker, Vec3f& translation, Rotation& rotation );

		/// The video source configuration string
		auto_ptr < SFString > videoConfiguration;

		/// Path to file containing camera parameters 
		auto_ptr < SFString > cameraParametersFilename;

		/// Add this node to the H3DNodeDatabase system.
		static H3DNodeDatabase database;

	protected:

		/// Get the index of the specified pattern id in the detected markers array having the highest confidence
		/// \return The index of the specified marker, or -1 if not found
		int getDetectedMarkerIndex ( int markerId );

		// Camera parameter
		ARParam	ARTCparam;

		// Video parameters
		AR2VideoParamT* ARTVideo;

		// Most recent image.
		ARUint8						*ARTImage;

		// Details of markers detected by this camera
		ARMarkerInfo    *marker_info;					// Pointer to array holding the details of detected markers.
		int             marker_num;						// Count of number of markers detected.
	};

}

#endif