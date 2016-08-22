#include <algorithm>

#include "TCode.h"
#include "func_lib.h"
#include "TSingletons.h"
#include "TLog.h"


NS_CORE_USING

TCode::TCode()
	: m_links( 0 )
	, m_frictions( 0 )
	, m_brakes( 0 )
{
	m_code.resize( 2 );
}

TCode::~TCode()
{
}

void TCode::setIn(const TElement & in)
{
	m_code[0] = TLink(in, TElement::INPUT);
}

void TCode::setOut(const TElement & out)
{
	m_code[1] = TLink(out, TElement::OUTPUT);
}

void TCode::setLinks( const TLinks& links )
{
	if (m_links)
	{
		m_code.erase(m_code.begin() + 2, m_code.begin() + m_links + 2);	
	}
	m_code.insert(m_code.begin()+2,links.begin(), links.end());
	m_links = links.size();
}

void TCode::setFrictions( const TLinks& frictions )
{
	if (m_frictions)
	{
		m_code.erase(m_code.begin() + 2 + m_links, m_code.begin() + 2 + m_links + m_frictions);
	}
	m_code.insert(m_code.begin() + 2 + m_links, frictions.begin(), frictions.end());
	m_frictions = frictions.size();
}

void TCode::setBrakes( const TLinks& brakes )
{
	if (m_brakes)
	{
		m_code.erase(m_code.begin() + 2 + m_links + m_frictions, m_code.begin() + 2 + m_links + m_frictions + m_brakes);
	}
	m_code.insert(m_code.begin() + 2 + m_links + m_frictions, brakes.begin(), brakes.end());
	m_brakes = brakes.size();
}

void TCode::print() const
{
	SetColor(15, 2);
	TLog::log( "==================================================" );
	SetColor(15, 0);
	TLog::log( "Длина вектора кода:			" + std::to_string( m_code.size() ) );
	TLog::log( "--------------------------------------------------" );

	const auto& generalData = TSingletons::getInstance()->getGeneralData();

	for (auto i = 0; i < m_code.size(); i++)
	{
		if ( i == 1 || i == 2 || i == 2 + generalData._numberOfLinks || i == 2 + generalData._numberOfLinks + generalData._numberOfFrictions )
			TLog::log( "|", false );
		m_code[i].print();
		TLog::log( " ", false );
	}
	TLog::log( "\n--------------------------------------------------" );
}

size_t TCode::size() const
{
	return m_code.size();
}

void TCode::writeToFile(std::ostream& file) const
{
	for ( auto i = 0; i < m_code.size(); i++ )
	{
		m_code[i].writeTofile( file );
		file << ' ';
	}	
}

bool TCode::loadFromFile(std::istream& file)
{
	const auto& generalData = TSingletons::getInstance()->getGeneralData();

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

const std::vector<TLink>& TCode::getCode() const
{
	return m_code;
}




