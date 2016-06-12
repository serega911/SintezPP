#include "VariablesSet.h"

using namespace pss;


Variable& pss::VariablesSet::operator[]( const eMainElement & element )
{
	return m_set[element];
}

const Variable& pss::VariablesSet::operator[]( const eMainElement & element ) const
{
	return m_set.at(element);
}
