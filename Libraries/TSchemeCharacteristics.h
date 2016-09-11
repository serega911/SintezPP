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

	void										setKinematicScheneData( size_t radial, size_t axial );

	virtual size_t								size() const override;
	virtual void								writeToFile( std::ostream& file ) const override;
	virtual bool								loadFromFile( std::istream& file ) override;

};

NS_CORE_END