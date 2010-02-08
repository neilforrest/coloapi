#include <H3D/Colo/Plane.h>

using namespace H3D;

// Add this node to the H3DNodeDatabase system.
H3DNodeDatabase Plane::database( "Plane", 
								   &(newInstance<Plane>), 
								   typeid( Plane ),
								   &X3DNode::database );

// Add the x3d field interface.
namespace PlaneInternals 
{
	FIELDDB_ELEMENT( Plane, topLeft, INPUT_OUTPUT );
	FIELDDB_ELEMENT( Plane, topRight, INPUT_OUTPUT );
	FIELDDB_ELEMENT( Plane, bottomRight, INPUT_OUTPUT );
	FIELDDB_ELEMENT( Plane, bottomLeft, OUTPUT_ONLY );
	FIELDDB_ELEMENT( Plane, normal, OUTPUT_ONLY );
	FIELDDB_ELEMENT( Plane, up, OUTPUT_ONLY );
}

// Update display normal field value from inputs
void Plane::UpdateNormal::update ()
{
	// The three corners of the screen (points on the plane)
	const Vec3f &topLeft		= static_cast< SFVec3f * >( routes_in[0] )->getValue();
	const Vec3f &topRight		= static_cast< SFVec3f * >( routes_in[1] )->getValue();
	const Vec3f &bottomRight	= static_cast< SFVec3f * >( routes_in[2] )->getValue();

	Vec3f normal= (topLeft-topRight).crossProduct ( bottomRight-topRight );
	normal.normalizeSafe();

	value= normal;
}

// Update bottom left corner field value from inputs
void Plane::UpdateBottomLeft::update ()
{
	// The three corners of the screen (points on the plane)
	const Vec3f &topLeft		= static_cast< SFVec3f * >( routes_in[0] )->getValue();
	const Vec3f &topRight		= static_cast< SFVec3f * >( routes_in[1] )->getValue();
	const Vec3f &bottomRight	= static_cast< SFVec3f * >( routes_in[2] )->getValue();

	Vec3f centre= (topLeft+bottomRight)/2.0;

	// bottomLeft= Twice the distance from topRight to centre
	value= topRight + (centre-topRight)*2.0;
}

// Update the display up vector field value from inputs
void Plane::UpdateUp::update ()
{
	// The two corners of the screen
	const Vec3f &topRight		= static_cast< SFVec3f * >( routes_in[0] )->getValue();
	const Vec3f &bottomRight	= static_cast< SFVec3f * >( routes_in[1] )->getValue();

	// Calculate the up vector from the display parameters
	value= topRight - bottomRight;
	value.normalizeSafe();
}

Plane::Plane ( 
				Inst< SFNode   >  _metadata,
				Inst < SFVec3f > _topLeft,
				Inst < SFVec3f > _topRight,
				Inst < SFVec3f > _bottomRight,
				Inst < UpdateBottomLeft > _bottomLeft,
				Inst < UpdateNormal > _normal,
				Inst < UpdateUp > _up ) 
										: 
	X3DNode ( _metadata ),
	topLeft ( _topLeft ),
	topRight ( _topRight ),
	bottomRight ( _bottomRight ),
	bottomLeft ( _bottomLeft ),
	normal ( _normal ),
	up ( _up )
{
	type_name = "Plane";
	database.initFields( this );

	// Internal routes to update normal
	topLeft->route ( normal, id );
	topRight->route ( normal, id );
	bottomRight->route ( normal, id );

	// Internal routes to update bottom left corner
	topLeft->route ( bottomLeft, id );
	topRight->route ( bottomLeft, id );
	bottomRight->route ( bottomLeft, id );

	// Internal routes to update display up vector
	topRight->route ( up, id );
	bottomRight->route ( up, id );
	
	// Set default values for display
	topLeft->setValue ( Vec3f ( -0.5, 0.0, -0.5 ) );
	topRight->setValue ( Vec3f ( 0.5, 0.0, -0.5 ) );
	bottomRight->setValue ( Vec3f ( 0.5, 0.0, 0.5 ) );
}

// Write information about the Plane node to a stream
ostream& H3D::operator<<( ostream &os, const Plane &p )
{
	os << "topLeft(" << p.topLeft->getValue() << "), topRight(" << p.topRight->getValue() << ")" << endl <<
		  "bottomLeft(" << p.bottomLeft->getValue() << "), bottomRight(" << p.bottomRight->getValue() << ")" << endl <<
		  "normal(" << p.normal->getValue() << ")";
	return os;
} 