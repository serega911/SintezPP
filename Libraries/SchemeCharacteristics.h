#pragma once

#include "GlobalDefines.h"
#include "IIOItem.h"
#include "KinematicSchemeData.h"

NS_CORE_START

class SchemeCharacteristics
	: public IIOItem
{
private:

	KinematicSchemeData							m_kinematicSchemeData;

public:

	void										setKinematicScheneData( const KinematicSchemeData& data );

	size_t										size() const;
	virtual void								writeToFile( std::ostream& file ) const override;
	virtual bool								loadFromFile( std::istream& file ) override;

};

NS_CORE_END