#include "GearSetCell.h"

NS_ARI_USING

ari::GearSetCell::GearSetCell( const Cordinate& cord, NS_CORE eMainElement elem )
	: m_cord( cord ), m_element( elem )
{

}

bool ari::GearSetCell::isConsist( const NS_CORE eMainElement& obj ) const
{
	return m_element == obj;
}

const Cordinate& ari::GearSetCell::getCord() const
{
	return m_cord;
}
