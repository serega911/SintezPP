#pragma once
#include <vector>

#include "GlobalDefines.h"
#include "GlobalTypes.h"
#include "IContainer.h"

NS_CORE_START

class TK : public IContainer
{
private:

protected:
	std::vector<TKValue>						m_K;

public:

	TK( const std::vector<double>& k );
	TK( const size_t size );
	TK();

	const TKValue								operator[]( size_t i ) const;

	void										print() const;
	size_t										size() const override;

	void										writeToFile( std::ostream& file ) const override;
	bool										loadFromFile( std::istream& file ) override;

	void										setValues( const std::vector<TKValue>& values );
	bool										check() const;

};

NS_CORE_END