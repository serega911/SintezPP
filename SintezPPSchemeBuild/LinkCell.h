#pragma once

#include <memory>

#include "ISchemeCell.h"
#include "Link_fwd.h"

NS_ARI_START

class LinkCell;

typedef std::shared_ptr<LinkCell> LinkCell_p;

class LinkCell : public ISchemeCell
{
private:

	Link*										m_parent;
	Cordinate									m_cord;

	LinkCell( const Cordinate& cord, Link* parent );
	LinkCell() = delete;

public:

	static LinkCell_p							create( const Cordinate& cord, Link* parent );

	virtual const Cordinate&					getCord() const override;
	virtual bool								isConsist( const NS_CORE eMainElement& elem ) const override;

};



NS_ARI_END