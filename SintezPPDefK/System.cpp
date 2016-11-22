#include "System.h"

#include "../Libraries/Singletons.h"

NS_ARI_USING


void System::addDefinedChain( const NS_CORE Chain& chain, const VariableValue & value, const NS_CORE GearNumber& gear )
{
	const auto & elements = chain.getElements();

	for ( auto & elem : elements )
	{
		if ( elem != NS_CORE Element::INPUT && elem != NS_CORE Element::OUTPUT && elem != NS_CORE Element::BRAKE )
		{
			auto& variable = m_sets[m_addedSetCount][elem.getGearSetN().getValue() - 1][elem.getElemN()];
			variable.setDefined( true );
			variable.setElement( elem, gear );
			variable.setValue( value );
		}
	}
}

void System::addUndefinedChain( const NS_CORE Chain& chain, const VariableValue & value, const NS_CORE GearNumber& gear )
{
	m_unknowns.emplace_back( UnknownVariable( value ) );
	auto& unknown = m_unknowns[m_unknowns.size() - 1];
	const auto & elements = chain.getElements();

	for ( auto & elem : elements )
	{
		if ( elem != NS_CORE Element::INPUT && elem != NS_CORE Element::OUTPUT && elem != NS_CORE Element::BRAKE )
		{
			auto& variable = m_sets[m_addedSetCount][elem.getGearSetN().getValue() - 1][elem.getElemN()];
			variable.setDefined( false );
			variable.setElement( elem, gear );
			unknown.addListener( &variable );
		}
	}
}

System::System()
	: m_addedSetCount( 0 )
{
}

bool System::addGearChains( const NS_CORE ChainArray& chains, const NS_CORE GearNumber& gear, const NS_CORE RatioValue i )
{
	for ( auto& chain : chains )
	{
		if ( chain.find( NS_CORE Element::INPUT ) && chain.find( NS_CORE Element::BRAKE ) )
		{
			return false;
		}
		else if ( chain.find( NS_CORE Element::BRAKE ) && chain.find( NS_CORE Element::OUTPUT ) )
		{
			return false;
		}
		else if ( chain.find( NS_CORE Element::INPUT ) && chain.find( NS_CORE Element::OUTPUT ) && i != NS_CORE RatioValue( 1 ) )
		{
			return false;
		}
	}

	for ( auto& chain : chains )
	{
		if ( chain.find( NS_CORE Element::INPUT ) )
		{
			addDefinedChain( chain, 1.0f, gear );
		}
		else if ( chain.find( NS_CORE Element::BRAKE ) )
		{
			addDefinedChain( chain, 0.0f, gear );
		}
		else if ( chain.find( NS_CORE Element::OUTPUT ) )
		{
			addDefinedChain( chain, 1.0f / i.getValue(), gear );
		}
		else
		{
			addUndefinedChain( chain, 1.0f, gear );
		}
	}
	m_addedSetCount++;
	return true;
}

VariablesSet & System::getVariablesSet( const NS_CORE GearNumber & gearN, const int & gearSetN )
{
	return m_sets.at( gearN.getValue() ).at( gearSetN );
}

const VariablesSet & System::getVariablesSet( const NS_CORE GearNumber & gearN, const int & gearSetN ) const
{
	return m_sets.at( gearN.getValue() ).at( gearSetN );
}

UnknownVariableArray & System::getUnknownVariables()
{
	return m_unknowns;
}

const UnknownVariableArray & System::getUnknownVariables() const
{
	return m_unknowns;
}

void System::init( const NS_CORE InternalGearRatios& initialKValues )
{
	auto numberOfPlanetaryGears = NS_CORE Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
	auto numberOfGears = NS_CORE Singletons::getInstance()->getInitialData()._realNumberOfGears;

	m_sets.resize( numberOfGears );
	for ( auto&it : m_sets )
	{
		it.resize( numberOfPlanetaryGears );
	}

	for ( size_t planetaryGear = 0; planetaryGear < numberOfPlanetaryGears; planetaryGear++ )
	{
		m_unknowns.emplace_back( UnknownVariable( initialKValues[planetaryGear].getValue() ) );
		auto& unknown = m_unknowns[m_unknowns.size() - 1];

		for ( size_t gear = 0; gear < numberOfGears; gear++ )
		{
			unknown.addListener( &( m_sets[gear].at( planetaryGear )[NS_CORE eMainElement::EMPTY] ) );
			m_sets[gear].at( planetaryGear )[NS_CORE eMainElement::EMPTY].setDefined( false );
			m_sets[gear].at( planetaryGear )[NS_CORE eMainElement::EMPTY].setElement( NS_CORE Element( NS_CORE eMainElement::EMPTY, NS_CORE GearSetNumber(planetaryGear + 1) ), NS_CORE GearNumber( gear + 1 ) );
		}
	}
}
