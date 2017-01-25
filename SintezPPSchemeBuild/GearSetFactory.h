#pragma once

#include <memory>
#include <map>

#include "../Libraries/InternalGearRatios.h"
#include "../Libraries/GearSetNumber.h"


#include "GearSet.h"
#include "Cordinate.h"
#include "eGearSetType.h"


NS_ARI_START


class CircleList
{
private:
	typedef eGearSetType Type;

	std::vector<Type>							m_container;
	std::vector<Type>::iterator					m_iterator;

public:

	void										add( const Type& elem )
	{
		m_container.emplace_back( elem );
		m_iterator = m_container.begin();
	}

	const Type&									get() const 
	{
		return *m_iterator;
	}

	bool										next()
	{
		m_iterator++;
		if ( m_iterator == m_container.end() )
		{
			m_iterator = m_container.begin();
			return false;
		}
		return true;
	};

};


class GearSetFactory;

typedef std::unique_ptr<GearSetFactory> GearSetFactory_p;

class GearSetFactory
{
private:

	std::map<NS_CORE GearSetNumber, CircleList> m_options;

	eGearSetType								getType( const NS_CORE GearSetNumber & num );
	GearSet_p									createStandart( const Cordinate& anchor, const NS_CORE GearSetNumber & num );
	GearSet_p									createCustom( const Cordinate& anchor, const NS_CORE GearSetNumber & num, const bool flipX, const bool flipY );

public:

	static GearSetFactory_p&					getInstance();

	void										init( const NS_CORE InternalGearRatios ratio );
	bool										next();
	GearSet_p									createGearSet( const NS_CORE GearSetNumber & num, const Cordinate& anchor );

};

NS_CORE_END