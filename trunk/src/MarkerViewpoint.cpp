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
#include <H3D/Colo/MarkerViewpoint.h>
#include <GL/glew.h>

using namespace H3D;

// Add this node to the H3DNodeDatabase system.
H3DNodeDatabase MarkerViewpoint::database(	"MarkerViewpoint", 
											&(newInstance<MarkerViewpoint>), 
											typeid( MarkerViewpoint ),
											&ColocationViewpoint::database );

// Add the x3d field interface.
namespace MarkerViewpointInternals 
{
	FIELDDB_ELEMENT( MarkerViewpoint, marker, INPUT_OUTPUT );
}

// Field type to set up routes for marker node when it is changed
void MarkerViewpoint::UpdateMarker::onPreValueChange( H3DMarker* new_value )
{
	MarkerViewpoint* markerViewpoint= static_cast<MarkerViewpoint*>(getOwner());
	
	if ( markerViewpoint->marker->getValue() )
	{
		markerViewpoint->marker->getValue()->translation->unroute ( markerViewpoint->position );
		new_value->rotation->unroute ( markerViewpoint->headOrientation );
	}
	
	if ( new_value )
	{
		new_value->translation->route ( markerViewpoint->position );
		new_value->rotation->route ( markerViewpoint->headOrientation );
	}
}

// Constructor
MarkerViewpoint::MarkerViewpoint (	Inst< SFSetBind >  _set_bind,
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
									Inst< UpdateDisplay >	_display,
									Inst< UpdateMarker >	_marker ) :
ColocationViewpoint ( _set_bind,_centerOfRotation,
		   _description,_fieldOfView,_jump,_metadata,
		   _orientation,_position,_retainUserOffsets,
		   _bindTime,_isBound,_accForwardMatrix,_accInverseMatrix, _display ),
		   marker ( _marker )
{
	type_name = "MarkerViewpoint";
	database.initFields( this );
}

// Override traverseSG() in order to traverse the contained marker
void MarkerViewpoint::traverseSG ( TraverseInfo& ti )
{
	Viewpoint::traverseSG ( ti );
	if ( marker->getValue() )
		marker->getValue()->traverseSG ( ti );
}