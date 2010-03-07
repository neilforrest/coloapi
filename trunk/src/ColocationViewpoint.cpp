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
#include <H3D/Colo/ColocationViewpoint.h>
#include <GL/glew.h>

using namespace H3D;

// Add this node to the H3DNodeDatabase system.
H3DNodeDatabase ColocationViewpoint::database(	"ColocationViewpoint", 
												&(newInstance<ColocationViewpoint>), 
												typeid( ColocationViewpoint ),
												&Viewpoint::database );

// Add the x3d field interface.
namespace ColocationViewpointInternals 
{
	FIELDDB_ELEMENT( ColocationViewpoint, display, INPUT_OUTPUT );
}

/// This function is called just before the value in the field is about to change 
void ColocationViewpoint::UpdateDisplay::onPreValueChange( ColocationDisplay* new_value )
{
	ColocationViewpoint* owner= static_cast < ColocationViewpoint* > ( getOwner() );

	// Unroute
	ColocationDisplay* display= owner->display->getValue();
	if ( display )
	{
		display->normal->unroute ( owner->orientation );
		display->up->unroute ( owner->orientation );
	}

	// Route
	if ( new_value )
	{
		new_value->normal->route ( owner->orientation );
		new_value->up->route ( owner->orientation );
	}
}

// Field used to update the orientation of the viewpoint based on position and the
// colocation display position and orientation
void ColocationViewpoint::UpdateOrientation::update ()
{	
	if ( routes_in.size() < 2 )
	{
		value= Rotation();
	}
	else
	{
		
		// The three corners of the screen (points on the plane)
		const Vec3f &displayNormal	= static_cast< SFVec3f * >( routes_in[0] )->getValue();
		const Vec3f &displayUp		= static_cast< SFVec3f * >( routes_in[1] )->getValue();

		// Construct a look-at matrix
		// Looking down (parallel to) the display normal, with the display up vector as the camera up vector
		Vec3f zaxis=  displayNormal;				// z-axis is opposite to display normal
													// NB. Because for the Viewpoint rotation=0 is looking
													// down (in the opposite direction to) the z-axis, there is
													// no need to invert the displayNormal

		Vec3f yaxis=  displayUp;					// y-axis is display up vector
		Vec3f xaxis = yaxis.crossProduct(zaxis);	// x-axis is purp. to up vector and zaxis

		xaxis.normalizeSafe();
		yaxis.normalizeSafe();

		//Console(4) << "UpdateOrientation::update():" << endl;
		//Console(4) << "displayNormal = " << displayNormal << endl;
		//Console(4) << "displayUp = " << displayUp << endl;
		//Console(4) << "--------------" << endl;
		//Console(4) << "xaxis = " << xaxis << endl;
		//Console(4) << "yaxis = " << yaxis << endl;
		//Console(4) << "zaxis = " << zaxis << endl;
		//Console(4) << endl;
		
		if ( xaxis.length() > 0 && yaxis.length() > 0 && zaxis.length() > 0 )
		{
			// Set the orientation value
			value= Rotation ( Matrix3f (xaxis.x, yaxis.x, zaxis.x,
										xaxis.y, yaxis.y, zaxis.y,
										xaxis.z, yaxis.z, zaxis.z ) );
		}
	}
}

// Constructor
ColocationViewpoint::ColocationViewpoint (	Inst< SFSetBind >  _set_bind,
											Inst< SFVec3f   >  _centerOfRotation,
											Inst< SFString  >  _description,
											Inst< SFFloat   >  _fieldOfView,
											Inst< SFBool    >  _jump,
											Inst< SFNode    >  _metadata,
											Inst< UpdateOrientation >  _orientation,
											Inst< SFPosition >  _position,
											Inst< SFBool    >  _retainUserOffsets,
											Inst< SFTime    >  _bindTime,
											Inst< SFBool    >  _isBound,
											Inst< SFMatrix4f > _accForwardMatrix,
											Inst< SFMatrix4f > _accInverseMatrix,
											Inst< UpdateDisplay >   _display,
											Inst< SFRotation > _headOrientation ) :
Viewpoint ( _set_bind,_centerOfRotation,
		   _description,_fieldOfView,_jump,_metadata,
		   _orientation,_position,_retainUserOffsets,
		   _bindTime,_isBound,_accForwardMatrix,_accInverseMatrix ),
		   display ( _display ),
		   headOrientation ( _headOrientation )
{
	type_name = "ColocationViewpoint";
	database.initFields( this );
}

// Calculate and set the projection matrix
void ColocationViewpoint::setupProjection(	EyeMode eye_mode,
											H3DFloat width, H3DFloat height,
											H3DFloat clip_near, H3DFloat clip_far,
											StereoInfo* stereo_info ) 
{
	// TODO: Devise more intellegent way of obtaining clipping planes?

	// Define the shortest distance from the eye to the near clipping plane
	static const H3DFloat NCPD = 0.05f;

	// Define the shortest distance from the eye to the far clipping plane
	static const H3DFloat FCPD = 1.0f;

	H3DFloat top, bottom, right, left;

	// The colocation display
	const ColocationDisplay* colocationDisplay= display->getValue();

	// The position of the camera
	Vec3f eye= position->getValue();

	// Stereo rendering parameter, which are used later, to cancel
	// out fixed interocular translation made by H3DWindowNode
	H3DFloat interocular_distance = (H3DFloat) 0.06;
	Vec3f rightEyeOffset;

	// Adjust eye position to match left or right eye if required by render mode
	if ( eye_mode == LEFT_EYE || eye_mode == RIGHT_EYE )
	{
		if( !stereo_info )
		  stereo_info = StereoInfo::getActive();

		if( stereo_info )
		  interocular_distance = stereo_info->interocularDistance->getValue();

		// Calculate an offset vector for the right eye, and rotate to match the orientation of the viewpoint
    rightEyeOffset= Matrix3f ( headOrientation->getValue() ) * Vec3f ( interocular_distance/2, 0, 0 );

		// Adjust the eye position to match either left or right eye
		if ( eye_mode == LEFT_EYE )
			eye-= rightEyeOffset;
		else if ( eye_mode == RIGHT_EYE )
			eye+= rightEyeOffset;
	}
	
	// The projection plane's normal
	const Vec3f& displayNormal= colocationDisplay->normal->getValue();
	
	// The display's up vector
	const Vec3f& displayUp= colocationDisplay->up->getValue();
	
	// The top left corner of the projection plane
	const Vec3f& displayTopLeft= colocationDisplay->topLeft->getValue();

	// The top right corner of the projection plane
	const Vec3f& displayTopRight= colocationDisplay->topRight->getValue();

	// The bottom left corner of the projection plane
	const Vec3f& displayBottomLeft= colocationDisplay->bottomLeft->getValue();

	// Find the shortest distance from the eye to the projection plane
	H3DFloat eyeToDisplay= (eye - displayTopLeft).dotProduct(displayNormal);
	
	// Calculate the point on the display closest to eye
	Vec3f eyeDisplayPoint= eye - eyeToDisplay*displayNormal;
	
	//Define a unit vector in the left direction of the projection plane
	Vec3f displayLeft = displayTopLeft-displayTopRight;
	displayLeft.normalizeSafe();
	
	// Calculate the distance to the left side of the projection plane from the eyeDisplayPoint
	H3DFloat Pleft = (displayTopLeft-eyeDisplayPoint).dotProduct(displayLeft);
	
	// Calculate the distance to the left side of the near plane:
	left = NCPD*(Pleft/eyeToDisplay);
		
	//Calculate the distance to the right side of the projection plane from the PPP
	H3DFloat Pright = (displayTopRight-eyeDisplayPoint).dotProduct(-displayLeft);
	//Calculate the distance to the left side of the near plane:
	right = NCPD*(Pright/eyeToDisplay);
	
	//Calculate the distance to the top side of the projection plane from the PPP
	H3DFloat Ptop = (displayTopLeft-eyeDisplayPoint).dotProduct(displayUp);
	//Calculate the distance to the top side of the near plane:
	top = NCPD*(Ptop/eyeToDisplay);

	//Calculate the distance to the bottom side of the projection plane from the PPP
	H3DFloat Pbottom = (displayBottomLeft-eyeDisplayPoint).dotProduct(-displayUp);
	//Calculate the distance to the left side of the near plane:
	bottom = NCPD*(Pbottom/eyeToDisplay);

	glFrustum(-left,right,-bottom,top,NCPD,FCPD);

	// Cancel out the fixed x-axis interocular translation made in H3DWindowNode
	// since we perform our own interocular translation based on orientation
	Vec3f adjust= Matrix3f ( orientation->getValue() ).inverse() * rightEyeOffset;
	if ( eye_mode == RIGHT_EYE )
	{
		glTranslatef ( interocular_distance/2, 0, 0 );
		glTranslatef ( -adjust.x, -adjust.y, -adjust.z );
	}
	else if ( eye_mode == LEFT_EYE )
	{
		glTranslatef ( -interocular_distance/2, 0, 0 );
		glTranslatef ( adjust.x, adjust.y, adjust.z );
	}
}