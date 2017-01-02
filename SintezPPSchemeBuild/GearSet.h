#pragma once

#include <vector>
#include <memory>

#include "ISchemeElement.h"
#include "eGearSetType.h"

NS_ARI_START

class GearSet: public ISchemeElement
{
private:

	friend class GearSetFactory;

	Cordinates									m_cords;
	Cordinate									m_anchor;
	eGearSetType								m_type;

	GearSet( const Cordinate& anchor );
	GearSet() = delete;

	void										addCord( const Cordinate& cord, NS_CORE eMainElement elem );

public:
	
	virtual const Cordinates&					getCordsWorldSpace() const override;

	~GearSet();
};

typedef std::shared_ptr<GearSet> GearSet_p;

NS_ARI_END

