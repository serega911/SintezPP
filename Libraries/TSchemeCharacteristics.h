#pragma once

#include "GlobalDefines.h"
#include "IContainer.h"
#include "KinematicSchemeData.h"

NS_CORE_START

class TSchemeCharacteristics
	: public IContainer
{
private:

	KinematicSchemeData							m_kinematicSchemeData;

public:

	void										setKinematicScheneData( const KinematicSchemeData& data );

	virtual size_t								size() const override;
	virtual void								writeToFile( std::ostream& file ) const override;
	virtual bool								loadFromFile( std::istream& file ) override;

};

NS_CORE_END