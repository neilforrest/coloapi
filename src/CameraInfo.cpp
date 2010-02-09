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
#include <H3D/Colo/CameraInfo.h>

using namespace H3D;

// Add this node to the H3DNodeDatabase system.
H3DNodeDatabase CameraInfo::database( "CameraInfo", 
                                      &(newInstance<CameraInfo>), 
                                      typeid( CameraInfo ),
                                      &X3DBindableNode::database  );

namespace CameraInfoInternals 
{
  FIELDDB_ELEMENT( CameraInfo, camera, INITIALIZE_ONLY );
}

CameraInfo::CameraInfo( 
                       Inst<   SFSetBind >  _set_bind,
                       Inst< SFNode    >  _metadata,
                       Inst<  SFTime    >  _bindTime,
                       Inst<  SFBool    >  _isBound,
                       Inst< MFCamera >  _camera ) :
  X3DBindableNode( "CameraInfo", _set_bind, _metadata, _bindTime, _isBound ),
  camera        ( _camera         ) {

  type_name = "CameraInfo";
  database.initFields( this );
}

void CameraInfo::traverseSG ( TraverseInfo& ti )
{
	for ( MFCamera::const_iterator i= camera->begin(); i != camera->end(); ++i )
	{
		static_cast < H3DCamera* > (*i)->updateCamera ();
	}
}