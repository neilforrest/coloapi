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
#ifndef __COLOCATIONMIRROREDDISPLAY_H__
#define __COLOCATIONMIRROREDDISPLAY_H__

#include "ColocationDisplay.h"
#include "Mirror.h"

namespace H3D
{
	/// \brief Represents a visual display used for colocation which uses a mirror to reflect the image.
	/// \details The parameters of the 'virtual'/reflected display are calculated from the position
	/// of the 'real' display and mirror
	class COLO_API ColocationMirroredDisplay : public ColocationDisplay
	{
	public:
		typedef TypedSFNode < Mirror > SFMirror;

		/// Field used to calculate a point on the virtual screen, from the parameters of the real screen and the mirror
		class COLO_API ReflectPoint : public TypedField< SFVec3f,
												Types< SFVec3f, /* the point to reflect */
													   SFVec3f, /* a point on the mirror */
													   SFVec3f  /* the mirror normal */
														        > > {
			virtual void update();
		};

		/// Constructor
		ColocationMirroredDisplay (	Inst < SFNode>  _metadata = 0,
									Inst < ReflectPoint > _topLeft = 0,
									Inst < ReflectPoint > _topRight = 0,
									Inst < ReflectPoint > _bottomRight = 0,
									Inst < UpdateBottomLeft > _bottomLeft = 0,
									Inst < UpdateNormal > _normal = 0,
									Inst < SFColocationDisplay > _display = 0,
									Inst < SFMirror > _mirror = 0 );
		
		/// Initializes the node
		virtual void initialize();

		/// The actual display, before it is reflected by the mirror
		auto_ptr < SFColocationDisplay > display;

		/// The mirror which reflects the actual display to produce the virtual display
		auto_ptr < SFMirror > mirror;

		/// Add this node to the H3DNodeDatabase system.
		static H3DNodeDatabase database;
	};

	/// Write information about the ColocationDisplay node to a stream
    ostream& operator<<( ostream &os, const ColocationMirroredDisplay &cd );

}

#endif