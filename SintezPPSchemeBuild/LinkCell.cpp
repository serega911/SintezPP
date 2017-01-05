#include "LinkCell.h"
#include "Link.h"

NS_ARI_USING

const Cordinate& ari::LinkCell::getCord() const
{
	return m_cord;
}

bool ari::LinkCell::isConsist( const NS_CORE Element& elem ) const
{
	return m_parent->isConsist( elem );
}

ari::LinkCell::LinkCell( const Cordinate& cord, Link* parent )
	: m_cord(cord), m_parent(parent)
{
}

ari::LinkCell_p ari::LinkCell::create( const Cordinate& cord, Link* parent )
{
	return LinkCell_p( new LinkCell( cord, parent ) );
}
