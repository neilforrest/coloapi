#include <H3D/Colo/H3DMarker.h>
#include <H3D/Colo/CameraInfo.h>

using namespace H3D;

// Add this node to the H3DNodeDatabase system.
H3DNodeDatabase H3DMarker::database(	"H3DMarker", 
										 NULL, 
										 typeid( H3DMarker ),
										 &X3DChildNode::database );

// Add the x3d field interface.
namespace H3DMarkerInternals 
{
	FIELDDB_ELEMENT( H3DMarker, translation, OUTPUT_ONLY );
	FIELDDB_ELEMENT( H3DMarker, rotation, OUTPUT_ONLY );
	FIELDDB_ELEMENT( H3DMarker, useCameras, INPUT_OUTPUT );
	FIELDDB_ELEMENT( H3DMarker, translationPerCamera, OUTPUT_ONLY );
	FIELDDB_ELEMENT( H3DMarker, rotationPerCamera, OUTPUT_ONLY );
	FIELDDB_ELEMENT( H3DMarker, camerasUsed, OUTPUT_ONLY );
}


// Field used to update average translation from all translations
void H3DMarker::UpdateTranslation::update ()
{
	H3DMarker* owner= static_cast<H3DMarker*> (getOwner());
	const MFVec3f::vector_type& translations= 
		static_cast< MFVec3f * >( routes_in[0] )->getValue();
	
	if ( translations.size() > 0 )
	{
		Vec3f average;
		for ( size_t i= 0; i < translations.size(); ++i )
		{
			H3DCamera* cam= static_cast<H3DCamera*>((*CameraInfo::getActive ()->camera)[(*owner->camerasUsed)[i]]);
			
			average+= cam->getLocalToWorldMatrix() * translations[i];
		}
		
		value= average/translations.size();
	}
}

// Field used to update average rotation from all rotations
void H3DMarker::UpdateRotation::update ()
{
	//const MFRotation::vector_type& rotations= 
	//	static_cast< MFRotation * >( routes_in[0] )->getValue();
	
	// TODO: Calculate average rotation from rotations
}

// Constructor
H3DMarker::H3DMarker (	Inst< SFNode>		_metadata,
					    Inst< UpdateTranslation >		_translation,
					    Inst< UpdateRotation >	_rotation,
						Inst< MFInt32 >		_useCameras,
					    Inst< MFVec3f >	    _translationPerCamera,
					    Inst< MFRotation >	_rotationPerCamera,
						Inst< MFInt32 >		_camerasUsed ) :
		X3DChildNode ( _metadata ), 
			translation ( _translation ),
			rotation ( _rotation ),
			useCameras ( _useCameras ), 
			translationPerCamera ( _translationPerCamera ), 
			rotationPerCamera ( _rotationPerCamera ), 
			camerasUsed ( _camerasUsed )
{
	type_name = "H3DMarker";
	database.initFields( this );
	
	translationPerCamera->route ( translation, id );
	rotationPerCamera->route ( rotation, id );
}

// Override traverseSG in order to update the markers transforms from the cameras
void H3DMarker::traverseSG ( TraverseInfo& ti )
{
	X3DChildNode::traverseSG ( ti );
	
	// Check that an active camera info node exists
	if ( CameraInfo::getActive () )
	{
		MFVec3f::vector_type translations;
		MFRotation::vector_type rotations;
		MFInt32::vector_type cameras;
		
		if ( useCameras->size() == 0 )
		{
			for ( size_t i= 0; i < CameraInfo::getActive ()->camera->size(); i++ )
				updateMarker ( i, translations, rotations, cameras );
		}
		else
		{
			for ( MFInt32::const_iterator i= useCameras->begin(); i != useCameras->end(); ++i )
				updateMarker ( *i, translations, rotations, cameras );
		}

		// Re-calculate the markers world transformation using the per camera transforms
		translationPerCamera->setValue ( translations, id );
		rotationPerCamera->setValue ( rotations, id );
		camerasUsed->setValue ( cameras, id );
	}
}

// Helper function to update the marker using the indexed camera
void H3DMarker::updateMarker ( H3DInt32 camera, 
							   MFVec3f::vector_type& translations,
							   MFRotation::vector_type& rotations,
							   MFInt32::vector_type& cameras )
{
	Vec3f translation;
	Rotation rotation;
	
	bool useCamera= 
		static_cast<H3DCamera*>((*CameraInfo::getActive ()->camera)[camera])->updateMarker ( *this, translation, rotation );

	if ( useCamera )
	{
		translations.push_back ( translation );
		rotations.push_back ( rotation );
		cameras.push_back ( camera );
	}
}