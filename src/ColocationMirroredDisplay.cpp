#include <H3D/Colo/ColocationMirroredDisplay.h>

using namespace H3D;

// Add this node to the H3DNodeDatabase system.
H3DNodeDatabase ColocationMirroredDisplay::database( "ColocationMirroredDisplay", 
													 &(newInstance<ColocationMirroredDisplay>), 
													 typeid( ColocationMirroredDisplay ),
													 &ColocationDisplay::database );

// Add the x3d field interface.
namespace ColocationMirroredDisplayInternals 
{
	FIELDDB_ELEMENT( ColocationMirroredDisplay, display, INITIALIZE_ONLY );
	FIELDDB_ELEMENT( ColocationMirroredDisplay, mirror, INITIALIZE_ONLY );
}

void ColocationMirroredDisplay::ReflectPoint::update()
{
	// The point to reflect
	const Vec3f &point = static_cast< SFVec3f * >( routes_in[0] )->getValue();


	// The owner/mirrored display node
	const ColocationMirroredDisplay* mirroredDisplay= static_cast < ColocationMirroredDisplay* > ( owner );
		
	// Reflect the point in the mirror
	if ( mirroredDisplay->mirror->getValue() )
		value= mirroredDisplay->mirror->getValue()->reflect ( point );
}

ColocationMirroredDisplay::ColocationMirroredDisplay ( 
										Inst < SFNode>  _metadata,
										Inst < ReflectPoint > _topLeft,
										Inst < ReflectPoint > _topRight,
										Inst < ReflectPoint > _bottomRight,
										Inst < UpdateBottomLeft > _bottomLeft,
										Inst < UpdateNormal > _normal,
										Inst < SFColocationDisplay > _display,
										Inst < SFMirror > _mirror )
										:
	ColocationDisplay ( _metadata, _topLeft, _topRight, _bottomRight, _bottomLeft, _normal ),
		display ( _display ), mirror ( _mirror )
{
	type_name = "ColocationMirroredDisplay";
	database.initFields( this );
}

// Initializes the node
void ColocationMirroredDisplay::initialize()
{
	if ( !display->getValue() )
	{
	    Console(3) << "Warning: No display value set for ColocationMirroredDisplay node ("
           << getName() << "). Colocation will not function correctly. " << endl;
		return;
	}

	if ( !mirror->getValue() )
	{
	    Console(3) << "Warning: No display value set for ColocationMirroredDisplay node ("
           << getName() << "). Colocation will not function correctly. " << endl;
		return;
	}

	// Set up routes to update virtual display properties
	
	// When routing we flip the screen over in y.
	// i.e. the top corners become the bottom corners,
	// as a result the normal is correctly reflected.
	// The up vector is also inverted, which is corrected for
	// when the y-axis is reflected as required when using 
	// a mirror display.

	display->getValue()->bottomLeft->route ( topLeft );	
	mirror->getValue()->topLeft->route ( topLeft );
	mirror->getValue()->normal->route ( topLeft );
	

	display->getValue()->bottomRight->route ( topRight );
	mirror->getValue()->topLeft->route ( topRight );
	mirror->getValue()->normal->route ( topRight );

	display->getValue()->topRight->route ( bottomRight );
	mirror->getValue()->topLeft->route ( bottomRight );
	mirror->getValue()->normal->route ( bottomRight );

	ColocationDisplay::initialize();
}

/// Write information about the ColocationDisplay node to a stream
ostream& H3D::operator<<( ostream &os, const ColocationMirroredDisplay &cd )
{
	os << "ColocationMirroredDisplay: " << endl
		<< *static_cast < const ColocationDisplay* > ( &cd ) << endl << endl

		<< "Display: " << endl
		<< *cd.display->getValue() << endl << endl

		<< "Mirror: " << endl
		<< *cd.mirror->getValue();

	return os;
}