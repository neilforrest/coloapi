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