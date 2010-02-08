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
		markerViewpoint->marker->getValue()->translation->unroute ( markerViewpoint->position );
	
	if ( new_value )
		new_value->translation->route ( markerViewpoint->position );
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