#pragma once

#include <vector>

#include "IIOItem.h"
#include "GlobalDefines.h"
#include "InternalGearRatioValue.h"

NS_CORE_START

class Range : public IIOItem
{
private:

	typedef InternalGearRatioValue T;

	static const T								s_eps;

	T											m_begin;
	T											m_end;

public:

	Range() = delete;
	Range( const T beg, const T end );

	T											getBegin() const;
	T											getEnd() const;
	T											getMid() const;
	bool										isInRange( const T value ) const;

	virtual void								writeToFile( std::ostream& file ) const override;
	virtual bool								loadFromFile( std::istream& file ) override;

	bool										operator==( const Range& obj ) const;
	
};

NS_CORE_END
