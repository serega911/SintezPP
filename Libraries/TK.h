#pragma once
#include <vector>

#include "GlobalDefines.h"
#include "IContainer.h"
#include "TKValue.h"
#include "TKValueArray.h"

NS_CORE_START

class TK : public IContainer
{
private:

protected:

	TKValueArray								m_K;

public:

	TK( const TKValueArray& k );
	TK( const size_t size );
	TK();

	const TKValue								operator[]( size_t i ) const;

	void										print() const;
	size_t										size() const override;

	void										writeToFile( std::ostream& file ) const override;
	bool										loadFromFile( std::istream& file ) override;

	void										setValues( const TKValueArray& values );
	bool										check() const;

};

NS_CORE_END