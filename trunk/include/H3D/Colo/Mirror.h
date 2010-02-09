//  Copyright 2010, Neil Forrest
//
//  This file is part of ColoAPI.
//
//  ColoAPI is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  ColoAPI is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with ColoAPI.  If not, see <http://www.gnu.org/licenses/>.
//
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