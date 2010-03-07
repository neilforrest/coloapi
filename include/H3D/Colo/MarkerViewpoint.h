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
#ifndef __MARKERVIEWPOINT_H__
#define __MARKERVIEWPOINT_H__

#include <H3D/Colo/Colo.h>
#include <H3D/Colo/H3DMarker.h>
#include "ColocationViewpoint.h"

namespace H3D
{
	/// \brief Represents a viewpoint used for colocation of haptics and 
	/// graphics with a viewpoint marker tracking system
	///
	/// The position of the viewpoint is determined by the specified tracking marker
	class COLO_API MarkerViewpoint : public ColocationViewpoint
	{
	public:

		/// Field type to set up routes for marker node when it is changed
		class COLO_API UpdateMarker:
		public AutoUpdate< OnNewValueSRefCountedField < TypedSFNode < H3DMarker > > > 
		{
			/// This function is called just before the value in the field is about to change 
			virtual void onPreValueChange( H3DMarker* new_value );
		};

    /// \brief A specialized viewpoint position field used to calculate the final viewpoint
    /// position from the marker position and the marker offset vector
    class COLO_API ViewpointPosition: public TypedField < SFPosition, Types < SFVec3f, SFVec3f > >
    {
      virtual void update();
    };
		
		/// Constructor
		MarkerViewpoint (		Inst< SFSetBind >  _set_bind         = 0,
								Inst< SFVec3f   >  _centerOfRotation = 0,
								Inst< SFString  >  _description      = 0,
								Inst< SFFloat   >  _fieldOfView      = 0,
								Inst< SFBool    >  _jump             = 0,
								Inst< SFNode    >  _metadata         = 0,
								Inst< UpdateOrientation >  _orientation   = 0,
								Inst< ViewpointPosition >  _position         = 0,
								Inst< SFBool    >  _retainUserOffsets = 0,
								Inst< SFTime    >  _bindTime         = 0,
								Inst< SFBool    >  _isBound          = 0,
								Inst< SFMatrix4f > _accForwardMatrix = 0,
								Inst< SFMatrix4f > _accInverseMatrix = 0,
								Inst< UpdateDisplay >	_display = 0,
								Inst< UpdateMarker >	_marker			 = 0,
                Inst< SFVec3f > _markerOffset = 0 );

		/// Override traverseSG() in order to traverse the contained marker and update position
		virtual void traverseSG ( TraverseInfo& ti );

		/// The H3DMarker node used to represent the position of the viewpoint
		auto_ptr < UpdateMarker > marker;

    /// The vector between the point between the eyes and the center of the marker
    auto_ptr < SFVec3f > markerOffset;

		/// Add this node to the H3DNodeDatabase system.
		static H3DNodeDatabase database;
	};

}

#endif