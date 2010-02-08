#ifndef __H3DMARKER_H__
#define __H3DMARKER_H__

#include <H3D/Colo/Colo.h>
#include <H3D/X3DChildNode.h>
#include <H3D/SFVec3f.h>
#include <H3D/MFVec3f.h>
#include <H3D/SFRotation.h>
#include <H3D/MFRotation.h>
#include <H3D/MFInt32.h>

namespace H3D
{
	/// Represents an abstract AR Marker in a tracking system
	class COLO_API H3DMarker : public X3DChildNode
	{
	public:
		
		/// Field used to update average translation from all translations
		class COLO_API UpdateTranslation : public TypedField < SFVec3f, MFVec3f >
		{
			virtual void update ();
		};
		
		/// Field used to update average rotation from all rotations
		class COLO_API UpdateRotation : public TypedField < SFRotation, MFRotation >
		{
			virtual void update ();
		};
		
		/// Constructor
		H3DMarker ( Inst< SFNode>		_metadata= 0,
					Inst< UpdateTranslation >		_translation= 0,
				    Inst< UpdateRotation >	_rotation= 0,
					Inst< MFInt32 >		_useCameras= 0,
					Inst< MFVec3f >	    _translationPerCamera= 0,
				    Inst< MFRotation >	_rotationPerCamera= 0,
					Inst< MFInt32 >		_camerasUsed= 0
		);

		/// Returns the default container field
		virtual string defaultXMLContainerField() {
		  return "marker";
		}

		/// Override traverseSG in order to update the markers transforms from the cameras
		virtual void traverseSG ( TraverseInfo& ti );
		
		/// The translation of the marker in world coordinates
		/// Averaged from all cameras
		auto_ptr < UpdateTranslation > translation;

		/// The rotation of the marker in world coordinates
		/// Averaged from all cameras
		auto_ptr < UpdateRotation > rotation;

		/// \brief List of indices of cameras in the CameraInfo node to use to
		/// evaluate the position of this marker. If empty then all possible cameras will be used.
		auto_ptr < MFInt32 > useCameras;

		/// The translation of the marker in world coordinates as calculated by each camera
		/// In the same order as camerasUsed field, which contains the indices of cameras used during evaluation
		auto_ptr < MFVec3f > translationPerCamera;

		/// The rotation of the marker in world coordinates as calculated by each camera
		/// In the same order as camerasUsed field, which contains the indices of cameras used during evaluation
		auto_ptr < MFRotation > rotationPerCamera;
		
		/// List of indices of cameras actually used to to evaluate the position of this marker
		auto_ptr < MFInt32 > camerasUsed;

		/// Add this node to the H3DNodeDatabase system.
		static H3DNodeDatabase database;

	protected:

		/// Helper function to update the marker using the indexed camera
		void updateMarker ( H3DInt32 camera, 
						    MFVec3f::vector_type& translations,
						    MFRotation::vector_type& rotations,
						    MFInt32::vector_type& cameras );

		/*/// Re-calculate the markers world transformation using the per camera transforms
		void updateTransform ();*/
	};

}

#endif