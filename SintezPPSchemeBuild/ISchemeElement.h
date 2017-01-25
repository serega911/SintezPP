#pragma once

#include <vector>
#include <memory>

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/eMainElement.h"

#include "ISchemeCell.h"

NS_ARI_START

class ISchemeElement
{
public:

	typedef std::vector<ISchemeCell_p> Cordinates;

	virtual const Cordinates&					getCordsWorldSpace() const = 0;
};

typedef std::shared_ptr<ISchemeElement> ISchemeElement_p;

NS_ARI_END

