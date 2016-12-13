#pragma once
#include <vector>

#include "GlobalDefines.h"
#include "IIOItem.h"
#include "InternalGearRatioValue.h"
#include "InternalGearRatioValueArray.h"

NS_CORE_START

class InternalGearRatios : public IIOItem
{
private:

protected:

	InternalGearRatioValueArray					m_K;

public:

	InternalGearRatios( const InternalGearRatioValueArray& k );
	InternalGearRatios( const size_t size );
	InternalGearRatios();

	const InternalGearRatioValue								operator[]( size_t i ) const;

	void										print() const;
	size_t										size() const;

	void										writeToFile( std::ostream& file ) const override;
	bool										loadFromFile( std::istream& file ) override;

	void										setValues( const InternalGearRatioValueArray& values );
	bool										check() const;

};

NS_CORE_END