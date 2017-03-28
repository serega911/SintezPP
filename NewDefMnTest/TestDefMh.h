#pragma once

#include "../Libraries/GlobalDefines.h"
#include "../Libraries/ApplicationBase.h"
#include "../Libraries/InternalGearRatios.h"
#include "../Libraries/ChainArray.h"

#include "Types.h"
#include "IFunction.h"


NS_ARI_START

class TestDefMh
	: public NS_CORE ApplicationBase
{
private:

	typedef std::pair<NS_CORE Element, double>	Minit;
	
	N											calcN( const W& w, const M& m );

	M											calcMn( const NS_CORE ChainArray& chains, const N& n, const NS_CORE InternalGearRatioValue& k, const double mIn0, const IFunction_p func );

	double										calcKpd( const N& n, const M& m );

	void										doTest( const NS_CORE TLinkArray& links, const NS_CORE InternalGearRatioValue& k, const W& w, const double mIn );

	NS_CORE ChainArray							createChains( const NS_CORE TLinkArray & links );

	template <class T>
	void printCharacteristicsLine( std::map<NS_CORE Element, T> map )
	{
		for ( const auto& elem : map )
		{
			if ( elem.first != NS_CORE Element::EMPTY )
			{
				elem.first.print();
				std::cout << "      ";
			}
		}
		std::cout << std::endl;
		for ( const auto& elem : map )
		{
			if ( elem.first != NS_CORE Element::EMPTY )
			{
				std::cout.width( 8 );
				std::cout.precision( 5 );
				std::cout << std::left << elem.second;
			}
		}
		std::cout << std::endl;
	}

public:

	void										run() override;
	virtual bool								checkRequirements() const override;

};

NS_ARI_END