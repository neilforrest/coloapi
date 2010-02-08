#ifndef __PLANE_H__
#define __PLANE_H__

#include <H3D/Colo/Colo.h>
#include <H3D/X3DNode.h>
#include <H3D/SFVec3f.h>

namespace H3D
{
	/// Represents a fintite square plane
	/// A common base class for nodes that represent a plane, providing a mechanism to calculate
	/// the normal and up vectors and 4th corner based on the provision of 3 points/corners
	class COLO_API Plane : public X3DNode
	{
	public:

		/// Field to update the screen normal from three corners
		class COLO_API UpdateNormal : public TypedField < SFVec3f,
												 Types < SFVec3f, SFVec3f, SFVec3f > >
		{
		public:
			/// Update the field value from inputs
			virtual void update ();
		};

		/// Field to update the bottom left corner of the screen from the other three corners
		class COLO_API UpdateBottomLeft : public TypedField < SFVec3f,
													 Types < SFVec3f, SFVec3f, SFVec3f > >
		{
			/// Update the field value from inputs
			virtual void update ();
		};

		/// Field to update the up vector of the display from other properties of the screen
		class COLO_API UpdateUp : public TypedField < SFVec3f,
												Types < SFVec3f,		// Top right
														SFVec3f > >		// Bottom right
		{
			/// Update the field value from inputs
			virtual void update ();
		};

		/// Constructor
		Plane (	Inst < SFNode>  _metadata = 0,
				Inst < SFVec3f > _topLeft = 0,
				Inst < SFVec3f > _topRight = 0,
				Inst < SFVec3f > _bottomRight = 0,
				Inst < UpdateBottomLeft > _bottomLeft = 0,
				Inst < UpdateNormal > _normal = 0,
				Inst < UpdateUp > _up = 0 );

		/// Top left corner of the display
		/// 
		/// <b>Access type:</b> inputOutput
		auto_ptr < SFVec3f > topLeft;

		/// Top right corner of the display
		/// 
		/// <b>Access type:</b> inputOutput
		auto_ptr < SFVec3f > topRight;

		/// Bottom right corner of the display
		/// 
		/// <b>Access type:</b> inputOutput
		auto_ptr < SFVec3f > bottomRight;

		/// Bottom left corner of the display, derived from topLeft and bottomRight
		/// 
		/// <b>Access type:</b> outputOnly
		auto_ptr < UpdateBottomLeft > bottomLeft;

		/// Normal to screen, derived from screen corners
		/// 
		/// <b>Access type:</b> outputOnly
		auto_ptr < UpdateNormal > normal;

		/// Screen up vector, derived from screen corners
		/// 
		/// <b>Access type:</b> outputOnly
		auto_ptr < UpdateUp > up;

		/// Add this node to the H3DNodeDatabase system.
		static H3DNodeDatabase database;
	};

	/// Write information about the Plane node to a stream
    ostream& operator<<( ostream &os, const Plane &p );

}

#endif