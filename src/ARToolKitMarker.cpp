#include <H3D/Colo/Colo.h>
#ifdef HAVE_ARTOOLKIT

#include <H3D/Colo/ARToolKitMarker.h>
#include <AR/ar.h>

using namespace H3D;

// Add this node to the H3DNodeDatabase system.
H3DNodeDatabase ARToolKitMarker::database( "ARToolKitMarker", 
										   &(newInstance<ARToolKitMarker>), 
										   typeid( ARToolKitMarker ),
										   &H3DMarker::database );

// Add the x3d field interface.
namespace ARToolKitCameraInternals 
{
	FIELDDB_ELEMENT( ARToolKitMarker, patternFilename, INITIALIZE_ONLY );
	FIELDDB_ELEMENT( ARToolKitMarker, patternWidth, INPUT_OUTPUT );
	FIELDDB_ELEMENT( ARToolKitMarker, patternCentre, INPUT_OUTPUT );
}

// Constructor
ARToolKitMarker::ARToolKitMarker (	Inst< SFNode>		_metadata,
									Inst< UpdateTranslation >	_translation,
									Inst< UpdateRotation >		_rotation,
									Inst< MFInt32 >		_useCameras,
									Inst< MFVec3f >	    _translationPerCamera,
									Inst< MFRotation >	_rotationPerCamera,
									Inst< MFInt32 >		_camerasUsed,
									Inst< SFString >	_patternFilename,
									Inst< SFFloat >		_patternWidth,
									Inst< SFVec2f >		_patternCentre )
									:
	 H3DMarker ( _metadata, _translation, _rotation, _useCameras, _translationPerCamera, _rotationPerCamera, _camerasUsed ),
	 patternFilename ( _patternFilename ),
	 patternWidth ( _patternWidth ), 
	 patternCentre ( _patternCentre ),
	 m_patternId ( -1 )
{
	type_name = "ARToolKitMarker";
	database.initFields( this );

	// Set default pattern parameters
	patternFilename->setValue ( "ARData/patt.hiro" );
	patternWidth->setValue ( 80.0f );
	patternCentre->setValue ( Vec2f ( 0.0f, 0.0f ) );
}

// Destructor
ARToolKitMarker::~ARToolKitMarker ()
{
	// Free the pattern id
	arFreePatt ( m_patternId );
}

void ARToolKitMarker::initialize ()
{
	H3DMarker::initialize();

	// Load the pattern file for this marker
	m_patternId= arLoadPatt ( patternFilename->getValue().c_str() );

	if ( m_patternId == -1 )
	{
		Console(3) << "ARToolKitMarker: Failed to load pattern: " << patternFilename->getValue();
	}
}

// Get the pattern id used by the ARToolKit for this marker
// \return The pattern id of this marker
int ARToolKitMarker::getPatternId () const
{
	return m_patternId;
}

#endif //HAVE_ARTOOLKIT