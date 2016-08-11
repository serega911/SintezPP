#pragma once
#include <vector>

#include "GlobalDefines.h"
#include "GlobalTypes.h"
#include "IContainer.h"

NS_CORE_START

class TK : public IContainer
{
private:

	bool										m_isFinded;

protected:
	std::vector<TKValue>						m_K;

public:

	const TKValue								operator[]( size_t i ) const;

	void										print() const;
	size_t										size() const override;
	void										setFinded( const bool finded );
	bool										getFinded() const;

	void										writeToFile( std::ostream& file ) const override;
	bool										loadFromFile( std::istream& file ) override;

	void										setValues( const std::vector<TKValue>& values );
	bool										check() const;

};

NS_CORE_END