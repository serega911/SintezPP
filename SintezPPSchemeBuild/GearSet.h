#pragma once

#include <vector>

#include "ISchemeElement.h"

NS_ARI_START

class GearSet: public ISchemeElement
{
private:

	friend class GearSetFactory;

	Cordinates									m_cords;
	Cordinate									m_anchor;

	GearSet( const Cordinate& anchor );
	GearSet() = delete;

	void										addCord( const Cordinate& cord, NS_CORE eMainElement elem );

public:
	
	virtual const Cordinates&					getCordsWorldSpace() const override;

	~GearSet();
};

NS_ARI_END

