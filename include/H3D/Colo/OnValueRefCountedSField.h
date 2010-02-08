#ifndef __ONVALUEREFCOUNTEDSFIELD_H__
#define __ONVALUEREFCOUNTEDSFIELD_H__

#include <H3D/Colo/Colo.h>
#include <H3D/RefCountSField.h>
#include <H3D/X3DShapeNode.h>

namespace H3D
{

	/// \ingroup FieldTemplateModifiers
	/// Field template modifier to call onValueChange() when field value changes
	/// Equivalent to OnNewValueSField for RefCountedSField derived field types
	template < typename RefCountedSFieldType >
	class COLO_API OnNewValueSRefCountedField : public RefCountedSFieldType
	{
	public:
		/// Override setValue to call onValueChange() when a new value is set
		virtual void setValue( typename RefCountedSFieldType::value_type v, int id = 0  )
		{
			typename RefCountedSFieldType::value_type old_value = this->value.get();
			
			if ( v != old_value )
				onPreValueChange ( static_cast<typename RefCountedSFieldType::typed_value_type>(v) );
			
			RefCountedSFieldType::setValue( v, id );
			
			if( this->value.get() != old_value )
				onValueChange( static_cast<typename RefCountedSFieldType::typed_value_type>(this->value.get()) );
		}
		
	protected:
		/// This function is called when the value in the field has changed. 
		virtual void onValueChange( typename RefCountedSFieldType::typed_value_type new_value ) {}
		
		/// This function is called just before the value in the field is about to change
		virtual void onPreValueChange ( typename RefCountedSFieldType::typed_value_type new_value ) {}
		
		/// Override update() to call onValueChange() when a new value is set
		virtual void update() 
		{
			typename RefCountedSFieldType::value_type old_value = this->value.get();
			typename RefCountedSFieldType::value_type new_value = 
			static_cast< RefCountedSFieldType* >(this->event.ptr)->getValue();
			
			if ( new_value != old_value )
				onPreValueChange ( static_cast<typename RefCountedSFieldType::typed_value_type>(new_value) );
			
			RefCountedSFieldType::update();
			
			if( this->value.get() != old_value )
				onValueChange( static_cast<typename RefCountedSFieldType::typed_value_type>(this->value.get()) );
		}
	};
	
}

#endif