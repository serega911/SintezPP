#pragma once

#include <memory>
#include <vector>

#include "../Libraries/GlobalDefines.h"


#include "IDisplay.h"
#include "ISchemeElement.h"
#include "Cordinate.h"
#include "../Libraries/Link.h"


NS_ARI_START

class IScheme
{
public:
	virtual void								print( const IDisplay_p& disp ) const = 0;

	virtual void								clear() = 0;
	virtual void								addLink( const std::vector<Cordinate>& trace, const NS_CORE Link& link ) = 0;
	virtual void								addFriction( const std::vector<Cordinate>& trace, const NS_CORE Link& link ) = 0;

	virtual size_t								getWidth() const = 0;
	virtual size_t								getHeight() const = 0;

	virtual std::vector<ISchemeElement_p>		getAllElements() const = 0;

};

typedef std::shared_ptr<IScheme> IScheme_p;

NS_ARI_END