#pragma once

#include "ISchemeCell.h"

NS_ARI_START


class GearSetCell : public ISchemeCell
{
private:

	NS_CORE eMainElement						m_element;
	Cordinate									m_cord;

public:

	GearSetCell( const Cordinate& cord, NS_CORE eMainElement elem );

	virtual const Cordinate&					getCord() const override;
	virtual bool								isConsist( const NS_CORE eMainElement& obj ) const override;

};

NS_ARI_END