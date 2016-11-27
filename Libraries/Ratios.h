#pragma once

#include <vector>

#include "IIOItem.h"
#include "GlobalDefines.h"
#include "RatioValue.h"
#include "RatioValueArray.h"

NS_CORE_START


class Ratios : public IIOItem
{
private:

	RatioValueArray								m_i;
	static RatioValue							m_eps;

public:

	Ratios();
	Ratios( const RatioValueArray& i, RatioValue eps );

	const RatioValue &							operator[]( size_t i ) const;
	bool										operator==(const Ratios& obj) const; // outdated
	void										operator=(const Ratios& obj);

	void										push_back( RatioValue value );

	void										print() const;

	bool										findIn( RatioValue value ) const;

	size_t										size() const;

	void										writeToFile( std::ostream& file ) const override;
	bool										loadFromFile( std::istream& file ) override;

};

NS_CORE_END
