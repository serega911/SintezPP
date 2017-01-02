#include "LinkCell.h"
#include "Link.h"

NS_ARI_USING

const Cordinate& ari::LinkCell::getCord() const
{
	return m_cord;
}

bool ari::LinkCell::isConsist( const NS_CORE eMainElement& elem ) const
{
	return m_parent->isConsist( elem );
}

ari::LinkCell::LinkCell( const Cordinate& cord, Link* parent )
	: m_cord(cord), m_parent(parent)
{
}
