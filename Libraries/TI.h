#pragma once

#include <vector>

#include "IContainer.h"
#include "GlobalDefines.h"
#include "TIValue.h"
#include "TIValueArray.h"

NS_CORE_START

//typedef std::vector<TIValue> TIValueArray;		// контейнер передаточных отношений ПКП

class TI : public IContainer
{
private:

	TIValueArray								m_i;
	static TIValue								m_eps;

public:

	TI();
	TI( const TIValueArray& i, TIValue eps );

	const TIValue &								operator[]( size_t i ) const;
	bool										operator==(const TI& obj) const; // outdated
	void										operator=(const TI& obj);

	void										push_back( TIValue value );

	void										print() const;

	bool										findIn( TIValue value ) const;

	size_t										size() const override;

	void										writeToFile( std::ostream& file ) const override;
	bool										loadFromFile( std::istream& file ) override;

};

NS_CORE_END
