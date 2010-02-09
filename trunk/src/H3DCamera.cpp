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
#include <H3D/Colo/H3DCamera.h>

using namespace H3D;

// Add this node to the H3DNodeDatabase system.
H3DNodeDatabase H3DCamera::database(	"H3DCamera", 
										NULL, 
										typeid( H3DCamera ),
										&X3DNode::database );

namespace H3DCameraInternals 
{
	FIELDDB_ELEMENT( H3DCamera, position, INPUT_OUTPUT );
	FIELDDB_ELEMENT( H3DCamera, orientation, INPUT_OUTPUT );
}

// Constructor
H3DCamera::H3DCamera (  Inst< SFNode> _metadata,
						Inst< SFVec3f > _position,
						Inst< SFRotation > _orientation )
: X3DNode ( _metadata ),
  position ( _position ),
  orientation ( _orientation )
{
	type_name = "H3DCamera";
	database.initFields( this );
}

// Get a transformation from camera local coordinates to world
// A matrix representing a transformation from camera local coordinates to world
Matrix4f H3DCamera::getLocalToWorldMatrix ()
{
	Matrix4f m ( orientation->getValue() );
	Vec3f pos= position->getValue();

	m[0][3]= pos.x;
	m[1][3]= pos.y;
	m[2][3]= pos.z;

	//Console(3) << "m: " << m << endl;

	return m;
}