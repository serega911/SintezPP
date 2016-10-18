#include "System.h"

#include "../Libraries/TSingletons.h"

NS_ARI_USING


void System::addDefinedChain( const NS_CORE TChain& chain, const VariableValue & value, const NS_CORE TGearNumber& gear )
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

void System::addUndefinedChain( const NS_CORE TChain& chain, const VariableValue & value, const NS_CORE TGearNumber& gear )
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

bool System::addGearChains( const NS_CORE TChainArray& chains, const NS_CORE TGearNumber& gear, const NS_CORE TIValue i )
{
	for ( auto& chain : chains )
	{
		if ( chain.find( NS_CORE TElement::INPUT ) && chain.find( NS_CORE TElement::BRAKE ) )
		{
			return false;
		}
		else if ( chain.find( NS_CORE TElement::BRAKE ) && chain.find( NS_CORE TElement::OUTPUT ) )
		{
			return false;
		}
		else if ( chain.find( NS_CORE TElement::INPUT ) && chain.find( NS_CORE TElement::OUTPUT ) && i != NS_CORE TIValue( 1 ) )
		{
			return false;
		}
	}

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

VariablesSet & System::getVariablesSet( const NS_CORE TGearNumber & gearN, const int & gearSetN )
{
	return m_sets.at( gearN.getValue() ).at( gearSetN );
}

const VariablesSet & System::getVariablesSet( const NS_CORE TGearNumber & gearN, const int & gearSetN ) const
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
		m_unknowns.emplace_back( UnknownVariable( initialKValues[planetaryGear].getValue() ) );
		auto& unknown = m_unknowns[m_unknowns.size() - 1];

		for ( size_t gear = 0; gear < numberOfGears; gear++ )
		{
			unknown.addListener( &( m_sets[gear].at( planetaryGear )[NS_CORE eMainElement::EMPTY] ) );
			m_sets[gear].at( planetaryGear )[NS_CORE eMainElement::EMPTY].setDefined( false );
			m_sets[gear].at( planetaryGear )[NS_CORE eMainElement::EMPTY].setElement( NS_CORE TElement( NS_CORE eMainElement::EMPTY, planetaryGear + 1 ), NS_CORE TGearNumber( gear + 1 ) );
		}
	}
}
