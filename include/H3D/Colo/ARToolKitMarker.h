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
#ifndef __ARTOOLKITMARKER_H__
#define __ARTOOLKITMARKER_H__

#include <H3D/Colo/H3DMarker.h>
#include <H3D/X3DChildNode.h>
#include <H3D/SFString.h>
#include <H3D/SFFloat.h>
#include <H3D/SFVec2f.h>

namespace H3D
{
	/// \brief Represents a trackable marker in the ARToolKit
	/// \details To enable tracking there must be one or more active instances of ARToolKitCamera
	class COLO_API ARToolKitMarker : public H3DMarker 
	{
	public:
		/// Constructor
		ARToolKitMarker (	Inst< SFNode>				_metadata= 0,
							Inst< UpdateTranslation >	_translation= 0,
							Inst< UpdateRotation >		_rotation= 0,
							Inst< MFInt32 >				_useCameras= 0,
							Inst< MFVec3f >				_translationPerCamera= 0,
							Inst< MFRotation >			_rotationPerCamera= 0,
							Inst< MFInt32 >				_camerasUsed= 0,
							Inst< SFString >			_patternFilename= 0,
							Inst< SFFloat >				_patternWidth= 0,
							Inst< SFVec2f >				_patternCentre= 0 );

		/// Destructor
		virtual ~ARToolKitMarker ();
			
		/// Initialise the marker
		virtual void initialize ();

		/// Get the pattern id used by the ARToolKit for this marker
		/// \return The pattern id of this marker
		int getPatternId () const;

		/// Path to pattern file used to recognise this marker
		auto_ptr < SFString > patternFilename;

		/// Width of the pattern
		auto_ptr < SFFloat > patternWidth;

		/// The center of the pattern
		auto_ptr < SFVec2f > patternCentre;

		/// Add this node to the H3DNodeDatabase system.
		static H3DNodeDatabase database;

	protected:

		/// Patern id used by ARToolKit
		int m_patternId;
	};
}

#endif