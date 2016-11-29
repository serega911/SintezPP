#include <algorithm>

#include "Code.h"
#include "Singletons.h"
#include "Log.h"


NS_CORE_USING

Code::Code()
	: m_links( 0 )
	, m_frictions( 0 )
	, m_brakes( 0 )
{
	m_code.resize( 2 );
}

Code::~Code()
{
}

void Code::setIn(const Element & in)
{
	m_code[0] = Link(in, Element::INPUT);
}

void Code::setOut(const Element & out)
{
	m_code[1] = Link(out, Element::OUTPUT);
}

void Code::setLinks( const TLinkArray& links )
{
	if (m_links)
	{
		m_code.erase(m_code.begin() + 2, m_code.begin() + m_links + 2);	
	}
	m_code.insert(m_code.begin()+2,links.begin(), links.end());
	m_links = links.size();
}

void Code::setFrictions( const TLinkArray& frictions )
{
	if (m_frictions)
	{
		m_code.erase(m_code.begin() + 2 + m_links, m_code.begin() + 2 + m_links + m_frictions);
	}
	m_code.insert(m_code.begin() + 2 + m_links, frictions.begin(), frictions.end());
	m_frictions = frictions.size();
}

void Code::setBrakes( const TLinkArray& brakes )
{
	if (m_brakes)
	{
		m_code.erase(m_code.begin() + 2 + m_links + m_frictions, m_code.begin() + 2 + m_links + m_frictions + m_brakes);
	}
	m_code.insert(m_code.begin() + 2 + m_links + m_frictions, brakes.begin(), brakes.end());
	m_brakes = brakes.size();
}

void Code::print() const
{
	Log::log( "==================================================", true, Log::WHITE, Log::GREEN );
	Log::log( "Длина вектора кода:			" + std::to_string( m_code.size() ) );
	Log::log( "--------------------------------------------------" );

	const auto& generalData = Singletons::getInstance()->getGeneralData();

	const size_t size = m_code.size();
	for ( size_t i = 0; i < size; i++ )
	{
		if ( i == 1 || i == 2 || i == 2 + generalData._numberOfLinks || i == 2 + generalData._numberOfLinks + generalData._numberOfFrictions )
			Log::log( "|", false );
		m_code[i].print();
		Log::log( " ", false );
	}
	Log::log( "\n--------------------------------------------------" );
}

size_t Code::size() const
{
	return m_code.size();
}

void Code::writeToFile(std::ostream& file) const
{
	for ( size_t i = 0; i < m_code.size(); i++ )
	{
		m_code[i].writeTofile( file );
		file << ' ';
	}	
}

bool Code::loadFromFile(std::istream& file)
{
	const auto& generalData = Singletons::getInstance()->getGeneralData();

	auto codeSize = 2 + generalData._numberOfLinks + generalData._numberOfFrictions + generalData._numberOfBrakes;
	m_code.resize(codeSize);

	bool ret = true;

	for (auto& it : m_code)
	{
		ret = ret && it.loadFromFile( file );
	}

	m_links = generalData._numberOfLinks;
	m_frictions = generalData._numberOfFrictions;
	m_brakes = generalData._numberOfBrakes;

	return ret;
}

const TLinkArray& Code::getCode() const
{
	return m_code;
}




