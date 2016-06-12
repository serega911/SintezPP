#include "System.h"

#include "../Libraries/TSingletons.h"

using namespace pss;


void pss::System::addDefinedChain( const TChain& chain, const VariableValue & value )
{
	const auto & elements = chain.getElements();

	for ( auto & elem : elements )
	{
		if ( elem != pss::TElement::INPUT && elem != pss::TElement::OUTPUT && elem != pss::TElement::BRAKE )
		{
			auto& variable = m_sets[m_addedSetCount][elem.getGearSetN() - 1][elem.getElemN()];
			variable.setDefined( true );
			variable.setElement( elem );
			variable.setValue( value );
		}
	}
}

void pss::System::addUndefinedChain( const TChain& chain, const VariableValue & value )
{
	m_unknowns.emplace_back( UnknownVariable( value ) );
	auto& unknown = m_unknowns[m_unknowns.size() - 1];
	const auto & elements = chain.getElements();

	for ( auto & elem : elements )
	{
		if ( elem != pss::TElement::INPUT && elem != pss::TElement::OUTPUT && elem != pss::TElement::BRAKE )
		{
			auto& variable = m_sets[m_addedSetCount][elem.getGearSetN() - 1][elem.getElemN()];
			variable.setDefined( false );
			variable.setElement( elem );
			unknown.addListener( &variable );
		}
	}
}

pss::System::System() : m_addedSetCount( 0 )
{
	init();
}

void pss::System::addGearChains( const std::vector<TChain>& chains, const TElement& brake, double i )
{
	for ( auto& chain : chains )
	{
		if ( chain.find( pss::TElement::INPUT ) )
		{
			addDefinedChain( chain, 1.0f );
		}
		else if ( chain.find( brake ) )
		{
			addDefinedChain( chain, 0.0f );
		}
		else if ( chain.find( pss::TElement::OUTPUT ) )
		{
			addDefinedChain( chain, i );
		}
		else
		{
			addUndefinedChain( chain, -2.0f );
		}
	}
	m_addedSetCount++;
}

VariablesSet & pss::System::getVariablesSet( const int & gearN, const int & gearSetN )
{
	return m_sets.at( gearN ).at( gearSetN );
}

const VariablesSet & pss::System::getVariablesSet( const int & gearN, const int & gearSetN ) const
{
	return m_sets.at( gearN ).at( gearSetN );
}

std::vector<UnknownVariable> & pss::System::getUnknownVariables()
{
	return m_unknowns;
}

const std::vector<UnknownVariable> & pss::System::getUnknownVariables() const
{
	return m_unknowns;
}

void pss::System::init()
{
	auto N = TSingletons::getInstance()->getNumberOfPlanetaryGears();

	m_sets.resize( TSingletons::getInstance()->getNumberOfGears() );

	for ( auto setNumber = 0; setNumber < m_sets.size( ); setNumber++ )
	{
		m_unknowns.emplace_back( UnknownVariable( -2.0 ) );
		auto& unknown = m_unknowns[m_unknowns.size( ) - 1];

		m_sets[setNumber].resize( N );
		for ( auto i = 0; i < N; i++ )
		{
			unknown.addListener( &( m_sets[setNumber].at( i )[eMainElement::EMPTY] ) );
			m_sets[setNumber].at( i )[eMainElement::EMPTY].setDefined( false );
			m_sets[setNumber].at( i )[eMainElement::EMPTY].setElement( TElement( eMainElement::EMPTY, setNumber + 1 ) );
		}
		
	}
}
