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
#include <H3D/Colo/ColocationDisplay.h>

using namespace H3D;

// Add this node to the H3DNodeDatabase system.
H3DNodeDatabase ColocationDisplay::database( "ColocationDisplay", 
										   &(newInstance<ColocationDisplay>), 
										   typeid( ColocationDisplay ),
										   &Plane::database );

ColocationDisplay::ColocationDisplay( 
										Inst< SFNode   >  _metadata,
										Inst < SFVec3f > _topLeft,
										Inst < SFVec3f > _topRight,
										Inst < SFVec3f > _bottomRight,
										Inst < UpdateBottomLeft > _bottomLeft,
										Inst < UpdateNormal > _normal,
										Inst < UpdateUp > _up ) 
										: 
	Plane ( _metadata, _topLeft, _topRight, _bottomRight, _bottomLeft, _normal, _up )
{
	type_name = "ColocationDisplay";
	database.initFields( this );
}