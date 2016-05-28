#include "WSet.h"

pss::WSet::Var& pss::WSet::operator[]( size_t i )
{
	return m_set[i];
}
