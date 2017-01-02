#pragma once

#include <vector>
#include <set>
#include <memory>

#include "../Libraries/GlobalDefines.h"

#include "ISchemeElement.h"
#include "LinkCell.h"

NS_ARI_START

class Link;

typedef std::shared_ptr<Link> Link_p;

class Link : public ISchemeElement
{
private:

	std::set<NS_CORE eMainElement>				m_elements;
	std::vector<ISchemeCell_p>					m_cells;

public:

	static Link_p								create();

	void										addCord( const Cordinate& cord );
	void										addElem( const NS_CORE eMainElement& elem );

	bool										isConsist( const NS_CORE eMainElement& elem );

	virtual const Cordinates&					getCordsWorldSpace() const override;

};



NS_ARI_END