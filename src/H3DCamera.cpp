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