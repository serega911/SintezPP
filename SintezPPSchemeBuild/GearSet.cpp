#include "GearSet.h"

NS_ARI_USING

GearSet::GearSet()
{
}

void GearSet::addCord( const Cordinate& cord, NS_CORE eMainElement elem )
{
	m_cords.push_back( { elem, cord } );
}

const GearSet::Cordinates& ari::GearSet::get() const
{
	return m_cords;
}

void ari::GearSet::setAnchor( const Cordinate& cord )
{
	m_anchor = cord;
}

const Cordinate& ari::GearSet::getAnchor() const
{
	return m_anchor;
}

GearSet::~GearSet()
{
}
