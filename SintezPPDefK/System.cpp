#include "System.h"

#include "../Libraries/TSingletons.h"

NS_ARI_USING


void System::addDefinedChain( const NS_CORE TChain& chain, const VariableValue & value, const int gear )
{
	const auto & elements = chain.getElements();

	for ( auto & elem : elements )
	{
		if ( elem != NS_CORE TElement::INPUT && elem != NS_CORE TElement::OUTPUT && elem != NS_CORE TElement::BRAKE )
		{
			auto& variable = m_sets[m_addedSetCount][elem.getGearSetN() - 1][elem.getElemN()];
			variable.setDefined( true );
			variable.setElement( elem, gear );
			variable.setValue( value );
		}
	}
}

void System::addUndefinedChain( const NS_CORE TChain& chain, const VariableValue & value, const int gear )
{
	m_unknowns.emplace_back( UnknownVariable( value ) );
	auto& unknown = m_unknowns[m_unknowns.size() - 1];
	const auto & elements = chain.getElements();

	for ( auto & elem : elements )
	{
		if ( elem != NS_CORE TElement::INPUT && elem != NS_CORE TElement::OUTPUT && elem != NS_CORE TElement::BRAKE )
		{
			auto& variable = m_sets[m_addedSetCount][elem.getGearSetN() - 1][elem.getElemN()];
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

void System::addGearChains( const NS_CORE TChainArray& chains, const int gear, const double i )
{
	for ( auto& chain : chains )
	{
		if ( chain.find( NS_CORE TElement::INPUT ) )
		{
			addDefinedChain( chain, 1.0f, gear );
		}
		else if ( chain.find( NS_CORE TElement::BRAKE ) )
		{
			addDefinedChain( chain, 0.0f, gear );
		}
		else if ( chain.find( NS_CORE TElement::OUTPUT ) )
		{
			addDefinedChain( chain, 1 / i, gear );
		}
		else
		{
			addUndefinedChain( chain, 1.0f, gear );
		}
	}
	m_addedSetCount++;
}

VariablesSet & System::getVariablesSet( const int & gearN, const int & gearSetN )
{
	return m_sets.at( gearN ).at( gearSetN );
}

const VariablesSet & System::getVariablesSet( const int & gearN, const int & gearSetN ) const
{
	return m_sets.at( gearN ).at( gearSetN );
}

UnknownVariableArray & System::getUnknownVariables()
{
	return m_unknowns;
}

const UnknownVariableArray & System::getUnknownVariables() const
{
	return m_unknowns;
}

void System::init( const NS_CORE TK& initialKValues )
{
	auto numberOfPlanetaryGears = NS_CORE TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears;
	auto numberOfGears = NS_CORE TSingletons::getInstance()->getInitialData()._numberOfGears;

	m_sets.resize( numberOfGears );
	for ( auto&it : m_sets )
	{
		it.resize( numberOfPlanetaryGears );
	}

	for ( size_t planetaryGear = 0; planetaryGear < numberOfPlanetaryGears; planetaryGear++ )
	{
		m_unknowns.emplace_back( UnknownVariable( initialKValues[planetaryGear] ) );
		auto& unknown = m_unknowns[m_unknowns.size() - 1];

		for ( size_t gear = 0; gear < numberOfGears; gear++ )
		{
			unknown.addListener( &( m_sets[gear].at( planetaryGear )[NS_CORE eMainElement::EMPTY] ) );
			m_sets[gear].at( planetaryGear )[NS_CORE eMainElement::EMPTY].setDefined( false );
			m_sets[gear].at( planetaryGear )[NS_CORE eMainElement::EMPTY].setElement( NS_CORE TElement( NS_CORE eMainElement::EMPTY, planetaryGear + 1 ), gear + 1 );
		}
	}
}
