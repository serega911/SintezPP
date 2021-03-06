#pragma once

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/IIOItem.h"

#include "IScheme.h"
#include "GearSet.h"
#include "Link.h"

NS_ARI_START

class Scheme;

typedef std::shared_ptr<Scheme> Scheme_p;

class Scheme : public IScheme, public NS_CORE IIOItem
{
private:

	static const int s_setWidth;
	static const int s_height;

	int											m_width;
	std::vector<Link_p>							m_links;
	std::vector<ISchemeElement_p>				m_staticElements;

	void										mergeLinks();

	Scheme();

public:

	static Scheme_p								create();

	virtual void								print( const IDisplay_p& disp, const std::string & message ) const override;

	virtual void								clear() override;
	virtual void								addLink( const std::vector<Cordinate>& trace, const NS_CORE Link& link ) override;
	virtual void								addFriction( const std::vector<Cordinate>& trace, const NS_CORE Link& link ) override;

	virtual size_t								getWidth() const override;
	virtual size_t								getHeight() const override;

	virtual std::vector<ISchemeElement_p>		getAllElements() const override;

	virtual void								writeToFile( std::ostream& ) const override;
	virtual bool								loadFromFile( std::istream& ) override;
};



NS_ARI_END