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