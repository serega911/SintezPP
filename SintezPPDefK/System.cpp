#include "System.h"

#include "../Libraries/TSingletons.h"

NS_PSS_USING


void System::addDefinedChain( const TChain& chain, const VariableValue & value, const int gear )
{
	const auto & elements = chain.getElements();

	for ( auto & elem : elements )
	{
		if ( elem != TElement::INPUT && elem != TElement::OUTPUT && elem != TElement::BRAKE )
		{
			auto& variable = m_sets[m_addedSetCount][elem.getGearSetN() - 1][elem.getElemN()];
			variable.setDefined( true );
			variable.setElement( elem, gear );
			variable.setValue( value );
		}
	}
}

void System::addUndefinedChain( const TChain& chain, const VariableValue & value, const int gear )
{
	m_unknowns.emplace_back( UnknownVariable( value ) );
	auto& unknown = m_unknowns[m_unknowns.size() - 1];
	const auto & elements = chain.getElements();

	for ( auto & elem : elements )
	{
		if ( elem != TElement::INPUT && elem != TElement::OUTPUT && elem != TElement::BRAKE )
		{
			auto& variable = m_sets[m_addedSetCount][elem.getGearSetN() - 1][elem.getElemN()];
			variable.setDefined( false );
			variable.setElement( elem, gear );
			unknown.addListener( &variable );
		}
	}
}

System::System() : m_addedSetCount( 0 )
{
}

void pss::System::addGearChains( const std::vector<TChain>& chains, const std::vector<TLink>& drivingElements, const int gear, const double i )
{
	for ( auto& chain : chains )
	{
		if ( chain.find( TElement::INPUT ) )
		{
			addDefinedChain( chain, 1.0f, gear );
		}
		else if ( chain.find( drivingElements[0].getElem1() ) )
		{
			addDefinedChain( chain, 0.0f, gear );
		}
		else if ( chain.find( TElement::OUTPUT ) )
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

std::vector<UnknownVariable> & System::getUnknownVariables()
{
	return m_unknowns;
}

const std::vector<UnknownVariable> & System::getUnknownVariables() const
{
	return m_unknowns;
}

void System::init( const TK& initialKValues )
{
	auto N = TSingletons::getInstance()->getInitialData()._numberOfPlanetaryGears;

	m_sets.resize( TSingletons::getInstance()->getInitialData()._numberOfGears );

	for ( auto setNumber = 0; setNumber < m_sets.size( ); setNumber++ )
	{
		m_unknowns.emplace_back( UnknownVariable( initialKValues[setNumber] ) );
		auto& unknown = m_unknowns[m_unknowns.size( ) - 1];

		m_sets[setNumber].resize( N );
		for ( auto i = 0; i < N; i++ )
		{
			unknown.addListener( &( m_sets[setNumber].at( i )[eMainElement::EMPTY] ) );
			m_sets[setNumber].at( i )[eMainElement::EMPTY].setDefined( false );
			m_sets[setNumber].at( i )[eMainElement::EMPTY].setElement( TElement( eMainElement::EMPTY, setNumber + 1 ), i + 1 );
		}
		
	}
}
