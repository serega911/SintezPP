#include "VariablesSet.h"

NS_ARI_USING


Variable& VariablesSet::operator[]( const NS_CORE eMainElement & element )
{
	return m_set[element];
}

const Variable& VariablesSet::operator[]( const NS_CORE eMainElement & element ) const
{
	return m_set.at(element);
}
