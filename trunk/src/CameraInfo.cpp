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