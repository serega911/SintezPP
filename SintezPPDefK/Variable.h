#pragma once

#include "Fumction.h"

#include "../Libraries/TElement.h"

namespace pss
{
	class Variable
	{
	private:

		VariableValue							m_value;
		bool									m_isDefined;
		TElement								m_element;

	public:

		void									setDefined( bool isDefined );
		void									setValue( const VariableValue & value );
		void									setElement( const TElement & element );

		TElement								getElement() const;
		bool									getDefined( ) const;
		VariableValue							getValue( ) const;

		void									onChangeUnknownVariableValue( const VariableValue & newValue );

	};

}