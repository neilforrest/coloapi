#ifndef __H3DCAMERA_H__
#define __H3DCAMERA_H__

#include <H3D/Colo/Colo.h>
#include <H3D/X3DNode.h>
#include <H3D/SFVec3f.h>
#include <H3D/SFRotation.h>

namespace H3D
{
	class H3DMarker;

	/// Represents an abstract camera in an AR tracking system
	class COLO_API H3DCamera : public X3DNode
	{
	public:
		/// Constructor
		H3DCamera ( Inst< SFNode> _metadata= 0,
					Inst< SFVec3f > _position= 0,
					Inst< SFRotation > _orientation= 0 );

		/// Returns the default container field
		virtual string defaultXMLContainerField() {
		  return "camera";
		}

		/// Perform any per frame processing required to succesully implement updateMarker(). 
		/// e.g. Grab and process a video frame.
		/// Called every scene traversal
		virtual void updateCamera ( ) {};

		/// Get the transformation of the specified marker using this camera
		/// \param[in] marker The marker instance
		/// \param[out] translation The translation for the marker in world coordinates
		/// \param[out] rotation The rotation for the marker in world coordinates
		/// \return true if successful, or false otherwise.
		virtual bool updateMarker ( const H3DMarker& marker, Vec3f& translation, Rotation& rotation )= 0;

		/// Get a transformation from camera local coordinates to world
		/// \return A matrix representing a transformation from camera local coordinates to world
		Matrix4f getLocalToWorldMatrix ();
		
		/// The camera position in world coordinates
		auto_ptr < SFVec3f > position;

		/// The orientation of the camera 
		auto_ptr < SFRotation > orientation;

		/// Add this node to the H3DNodeDatabase system.
		static H3DNodeDatabase database;

	protected:

		/// Helper function to 
	};

}

#endif