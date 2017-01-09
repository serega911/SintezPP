#pragma once

#include <vector>
#include <set>
#include <memory>

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/Chain.h"

#include "ISchemeElement.h"
#include "LinkCell.h"

NS_ARI_START

class Link;

typedef std::shared_ptr<Link> Link_p;

class Link : public ISchemeElement
{
private:

	NS_CORE Chain								m_elements;
	std::vector<ISchemeCell_p>					m_cells;

public:

	static Link_p								create();

	void										addCord( const Cordinate& cord );
	void										addElem( const NS_CORE Element& elem );
	void										addLink( const NS_CORE Link& link );
	void										addChain( const NS_CORE Chain& chain );

	bool										isConsist( const NS_CORE Element& elem );

	const NS_CORE Chain&						getElements() const;
	virtual const Cordinates&					getCordsWorldSpace() const override;

};



NS_ARI_END