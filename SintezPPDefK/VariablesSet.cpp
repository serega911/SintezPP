#include "VariablesSet.h"

NS_PSS_USING


Variable& VariablesSet::operator[]( const eMainElement & element )
{
	return m_set[element];
}

const Variable& VariablesSet::operator[]( const eMainElement & element ) const
{
	return m_set.at(element);
}
