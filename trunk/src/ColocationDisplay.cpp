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