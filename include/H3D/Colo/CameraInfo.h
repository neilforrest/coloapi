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
#ifndef __CAMERAINFO_H__
#define __CAMERAINFO_H__

#include <H3D/Colo/Colo.h>
#include <H3D/Colo/H3DCamera.h>
#include <H3D/X3DBindableNode.h>
#include <H3D/MFNode.h>

namespace H3D
{

	/// A bindable node containing all AR cameras, providing an explicit and predictable way of indexing them
	class COLO_API CameraInfo : public X3DBindableNode
	{
	public:
		typedef TypedMFNode< H3DCamera > MFCamera;

		/// Constructor
		CameraInfo ( Inst< SFSetBind >  _set_bind        = 0,
					 Inst< SFNode    >  _metadata        = 0,
					 Inst< SFTime    >  _bindTime        = 0,
					 Inst< SFBool    >  _isBound         = 0,
					 Inst< MFCamera  >  _camera          = 0);

		/// Convenience function to get the top of the CameraInfo stack.
		static inline CameraInfo *getActive() {
		  return static_cast< CameraInfo * >( X3DBindableNode::getActive( "CameraInfo" ) );
		}

		virtual void traverseSG ( TraverseInfo& ti );

		/// Contains the cameras in this node
		auto_ptr< MFCamera >  camera;

		/// Add this node to the H3DNodeDatabase system.
		static H3DNodeDatabase database;

	};

}

#endif