#pragma once

#include "ISchemeCell.h"

NS_ARI_START

class GearSetCell;

typedef std::shared_ptr<GearSetCell> GearSetCell_p;

class GearSetCell : public ISchemeCell
{
private:

	NS_CORE Element								m_element;
	Cordinate									m_cord;

	GearSetCell( const Cordinate& cord, NS_CORE Element elem );

public:

	static GearSetCell_p						create( const Cordinate& cord, NS_CORE Element elem );

	virtual const Cordinate&					getCord() const override;
	virtual bool								isConsist( const NS_CORE Element& obj ) const override;

};

NS_ARI_END