#pragma once

#include "ISchemeCell.h"
#include "Link_fwd.h"

NS_ARI_START


class LinkCell : public ISchemeCell
{
private:

	Link*										m_parent;
	Cordinate									m_cord;

public:

	LinkCell( const Cordinate& cord, Link* parent );

	virtual const Cordinate&					getCord() const override;
	virtual bool								isConsist( const NS_CORE eMainElement& elem ) const override;

};

NS_ARI_END