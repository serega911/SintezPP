#include "GearSet.h"
#include "GearSetCell.h"

NS_ARI_USING

ari::GearSet::GearSet( const Cordinate& anchor )
	: m_anchor(anchor)
{
}

void ari::GearSet::addCord( const Cordinate& cord, NS_CORE eMainElement elem )
{
	ISchemeCell_p cell( new GearSetCell( cord + m_anchor, elem ) );
	m_cords.push_back( cell );
}

const GearSet::Cordinates& ari::GearSet::getCordsWorldSpace() const
{
	return m_cords;
}

GearSet::~GearSet()
{
}

