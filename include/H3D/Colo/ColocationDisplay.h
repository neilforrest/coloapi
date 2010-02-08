#ifndef __COLOCATIONDISPLAY_H__
#define __COLOCATIONDISPLAY_H__

#include <H3D/Colo/Colo.h>
#include <H3D/Colo/Plane.h>

namespace H3D
{
	/// \brief Represents a visual display used for colocation
	/// \details Serves as a base class for all colocation displays
	/// Currently adds nothing to Plane base class appart from implementing defaultXMLContainerField()
	class COLO_API ColocationDisplay : public Plane
	{
	public:
		typedef TypedSFNode < ColocationDisplay > SFColocationDisplay;

		/// Constructor
		ColocationDisplay (	Inst < SFNode>  _metadata = 0,
							Inst < SFVec3f > _topLeft = 0,
							Inst < SFVec3f > _topRight = 0,
							Inst < SFVec3f > _bottomRight = 0,
							Inst < UpdateBottomLeft > _bottomLeft = 0,
							Inst < UpdateNormal > _normal = 0,
							Inst < UpdateUp > _up = 0 );

		/// Returns the default container field
		virtual string defaultXMLContainerField() {
		  return "display";
		}

		/// Add this node to the H3DNodeDatabase system.
		static H3DNodeDatabase database;
	};
}

#endif