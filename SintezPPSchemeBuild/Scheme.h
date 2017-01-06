#pragma once

#include "../Libraries/GlobalDefines.h"

#include "IScheme.h"
#include "GearSet.h"
#include "Link.h"
#include "../Libraries/InternalGearRatios.h"

NS_ARI_START

class Scheme;

typedef std::shared_ptr<Scheme> Scheme_p;

class Scheme : public IScheme
{
private:

	static const int s_setWidth;
	static const int s_height;

	int											m_width;
	std::vector<Link_p>							m_links;
	std::vector<ISchemeElement_p>				m_staticElements;

	void										printElement( NS_ARI ISchemeElement_p set, const IDisplay_p& disp ) const;
	void										addElementsToLink( Link_p & link, const NS_CORE Link& elements );

	Scheme( const NS_CORE InternalGearRatios k );

public:

	static Scheme_p								create( const NS_CORE InternalGearRatios k );

	virtual void								print( const IDisplay_p& disp ) const override;

	virtual void								clear() override;
	virtual void								addLink( const std::vector<Cordinate>& trace, const NS_CORE Link& link ) override;
	virtual void								addFriction( const std::vector<Cordinate>& trace, const NS_CORE Link& link ) override;

	virtual size_t								getWidth() const override;
	virtual size_t								getHeight() const override;

	virtual std::vector<ISchemeElement_p>		getAllElements() const override; 

};



NS_ARI_END