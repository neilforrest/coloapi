#ifndef __MARKERVIEWPOINT_H__
#define __MARKERVIEWPOINT_H__

#include <H3D/Colo/Colo.h>
#include <H3D/Colo/H3DMarker.h>
#include "ColocationViewpoint.h"

namespace H3D
{
	/// \brief Represents a viewpoint used for colocation of haptics and 
	/// graphics with a viewpoint marker tracking system
	///
	/// The position of the viewpoint is determined by the specified tracking marker
	class COLO_API MarkerViewpoint : public ColocationViewpoint
	{
	public:

		/// Field type to set up routes for marker node when it is changed
		class COLO_API UpdateMarker:
		public AutoUpdate< OnNewValueSRefCountedField < TypedSFNode < H3DMarker > > > 
		{
			/// This function is called just before the value in the field is about to change 
			virtual void onPreValueChange( H3DMarker* new_value );
		};
		
		/// Constructor
		MarkerViewpoint (		Inst< SFSetBind >  _set_bind         = 0,
								Inst< SFVec3f   >  _centerOfRotation = 0,
								Inst< SFString  >  _description      = 0,
								Inst< SFFloat   >  _fieldOfView      = 0,
								Inst< SFBool    >  _jump             = 0,
								Inst< SFNode    >  _metadata         = 0,
								Inst< UpdateOrientation >  _orientation   = 0,
								Inst< SFPosition >  _position         = 0,
								Inst< SFBool    >  _retainUserOffsets = 0,
								Inst< SFTime    >  _bindTime         = 0,
								Inst< SFBool    >  _isBound          = 0,
								Inst< SFMatrix4f > _accForwardMatrix = 0,
								Inst< SFMatrix4f > _accInverseMatrix = 0,
								Inst< UpdateDisplay >	_display = 0,
								Inst< UpdateMarker >	_marker			 = 0 );

		/// Override traverseSG() in order to traverse the contained marker and update position
		virtual void traverseSG ( TraverseInfo& ti );

		/// The H3DMarker node used to represent the position of the viewpoint
		auto_ptr < UpdateMarker > marker;

		/// Add this node to the H3DNodeDatabase system.
		static H3DNodeDatabase database;
	};

}

#endif