#ifndef __MIRROR_H__
#define __MIRROR_H__

#include <H3D/Colo/Colo.h>
#include <H3D/Colo/Plane.h>

namespace H3D
{
	/// Represents a plannar mirror for reflecting a point
	class COLO_API Mirror : public Plane
	{
	public:
		/// Constructor
		Mirror (	Inst < SFNode>  _metadata = 0,
					Inst < SFVec3f > _topLeft = 0,
					Inst < SFVec3f > _topRight = 0,
					Inst < SFVec3f > _bottomRight = 0,
					Inst < UpdateBottomLeft > _bottomLeft = 0,
					Inst < UpdateNormal > _normal = 0,
					Inst < UpdateUp > _up = 0 );

		/// Returns the default container field
		virtual string defaultXMLContainerField() {
		  return "mirror";
		}

		/// Relfects the specified point in the mirror
		/// \param[in] p the point to reflect
		/// \return the reflected point
		virtual Vec3f reflect ( const Vec3f& p ) const;

		/// Add this node to the H3DNodeDatabase system.
		static H3DNodeDatabase database;
	};
}

#endif