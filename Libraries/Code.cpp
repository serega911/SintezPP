#include <algorithm>

#include "Code.h"
#include "Singletons.h"
#include "Log.h"



NS_CORE_USING

Code::Code()
{

}

Code::~Code()
{
}

void Code::setIn(const Element & in)
{
	m_input = Link(in, Element::INPUT);
}

void Code::setOut(const Element & out)
{
	m_output = Link(out, Element::OUTPUT);
}

void Code::setLinks( const TLinkArray& links )
{
	m_links = links;
}

void Code::setFrictions( const TLinkArray& frictions )
{
	m_frictions = frictions;
}

void Code::setBrakes( const TLinkArray& brakes )
{
	m_brakes = brakes;
}

const TLinkArray& core::Code::getLinks() const
{
	return m_links;
}

const Link& core::Code::getOut() const
{
	return m_output;
}

const Link& core::Code::getIn() const
{
	return m_input;
}

const TLinkArray& core::Code::getFrictions() const
{
	return m_frictions;
}

const TLinkArray& core::Code::getBrakes() const
{
	return m_brakes;
}

bool core::Code::isArrayContain( const TLinkArray& array, const Element& elem ) const
{
	for ( const auto & it : array )
		if ( it.isContain( elem ) )
			return true;

	return false;
}

bool core::Code::isContain( const Element& elem ) const
{
	return m_input.isContain( elem ) 
		|| m_output.isContain( elem ) 
		|| isArrayContain( m_links, elem ) 
		|| isArrayContain( m_frictions, elem ) 
		|| isArrayContain( m_brakes, elem );
}

void Code::print() const
{
	Log::log( "==================================================", true, eColor::WHITE, eColor::GREEN );

	const auto& generalData = Singletons::getInstance()->getGeneralData();

	m_input.print();
	Log::log( " | ", false );
	m_output.print();
	Log::log( " | ", false );
	for ( const auto& it : m_links )
	{
		it.print();
		Log::log( " ", false );
	}
	Log::log( " | ", false );
	for ( const auto& it : m_frictions )
	{
		it.print();
		Log::log( " ", false );
	}
	Log::log( " | ", false );
	for ( const auto& it : m_brakes )
	{
		it.print();
		Log::log( " ", false );
	}
	Log::log( "\n--------------------------------------------------" );
}

void Code::writeToFile(std::ostream& file) const
{
	m_input.writeTofile( file );
	file << ' ';
	m_output.writeTofile( file );
	file << ' ';
	for ( const auto& it : m_links )
	{
		it.writeTofile( file );
		file << ' ';
	}
	for ( const auto& it : m_frictions )
	{
		it.writeTofile( file );
		file << ' ';
	}
	for ( const auto& it : m_brakes )
	{
		it.writeTofile( file );
		file << ' ';
	}
	
}

bool Code::loadFromFile(std::istream& file)
{
	const auto& generalData = Singletons::getInstance()->getGeneralData();

	m_links.resize( generalData._numberOfLinks );
	m_frictions.resize( generalData._numberOfFrictions );
	m_brakes.resize( generalData._numberOfBrakes );

	bool ret = true;

	ret = ret && m_input.loadFromFile( file );
	ret = ret && m_output.loadFromFile( file );
	for (auto& it : m_links)
		ret = ret && it.loadFromFile( file );
	for ( auto& it : m_frictions )
		ret = ret && it.loadFromFile( file );
	for ( auto& it : m_brakes )
		ret = ret && it.loadFromFile( file );

	return ret;
}




