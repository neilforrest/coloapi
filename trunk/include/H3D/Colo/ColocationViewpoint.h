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
#ifndef __COLOCATIONVIEWPOINT_H__
#define __COLOCATIONVIEWPOINT_H__

#include <H3D/Viewpoint.h>
#include "ColocationDisplay.h"
#include "OnValueRefCountedSField.h"

namespace H3D
{

	/// Represents a viewpoint used for colocation of haptics and graphics
	class COLO_API ColocationViewpoint : public Viewpoint
	{
	public:
		typedef TypedSFNode< ColocationDisplay > SFColocationDisplay;

		/// Field type to set up routes for display node when it is changed
		class COLO_API UpdateDisplay:
		public AutoUpdate< OnNewValueSRefCountedField < TypedSFNode < ColocationDisplay > > > 
		{
			/// This function is called just before the value in the field is about to change 
			virtual void onPreValueChange( ColocationDisplay* new_value );
		};

		/// \brief Field used to update the orientation of the viewpoint based on position and the
		/// colocation display position and orientation
		class COLO_API UpdateOrientation : public TypedField < SFOrientation, void,
												 Types < 
														 SFVec3f,		// The normal of the display
														 SFVec3f > >	// The up vector of the display
		{
			/// Update the field value from inputs
			virtual void update ();
		};

		/// Constructor
		ColocationViewpoint (	Inst< SFSetBind >	_set_bind			= 0,
								Inst< SFVec3f   >	_centerOfRotation	= 0,
								Inst< SFString  >	_description		= 0,
								Inst< SFFloat   >	_fieldOfView		= 0,
								Inst< SFBool    >	_jump				= 0,
								Inst< SFNode    >	_metadata			= 0,
								Inst< UpdateOrientation >  _orientation	= 0,
								Inst< SFPosition >  _position			= 0,
								Inst< SFBool    >	_retainUserOffsets	= 0,
								Inst< SFTime    >	_bindTime			= 0,
								Inst< SFBool    >	_isBound			= 0,
								Inst< SFMatrix4f >	_accForwardMatrix	= 0,
								Inst< SFMatrix4f >	_accInverseMatrix	= 0,
								Inst< UpdateDisplay >	_display		= 0,
								Inst< SFRotation > _headOrientation		= 0);

		/// Calculate and set the projection matrix
		virtual void setupProjection( EyeMode eye_mode,
									  H3DFloat width, H3DFloat height,
									  H3DFloat clip_near, H3DFloat clip_far,
									  StereoInfo* stereo_info = 0 );

		/// The colocation display on which this viewpoint will be displayed
		/// 
		/// <b>Access type:</b> inputOutput
		auto_ptr < UpdateDisplay > display;

		/// The orientation of the viewer's head
		/// Since the 'orientation' field is used to set the actual orientation of the Viewpoint node, 
		/// which is controlled by CollocationViewpoint to always be the opposite of the display normal,
		/// we need another field to define the viewer's head orientation. 
		/// This field is used to calculate the interocular offset based on head orientation.
		auto_ptr < SFRotation > headOrientation;

		/// Add this node to the H3DNodeDatabase system.
		static H3DNodeDatabase database;

	};

}

#endif