#include <map>

#include "TestDefMh.h"
#include "MappedSystem.h"
#include "../Libraries/Gaus.h"
#include "../Libraries/Code.h"
#include "../Libraries/Singletons.h"
#include "../Libraries/GearBox.h"
NS_ARI_USING

TestDefMh::N ari::TestDefMh::calcN( const W& w, const M& m )
{
	TestDefMh::N ret;
	NS_CORE Log::warning( w.size() != m.size(), "wrpng size", NS_CORE Log::CRITICAL, HERE );

	const auto gearsCount = w.size();


		for ( auto&it : m )
		{
			const NS_CORE Element elem = it.first;
			const auto torque = it.second;
			const auto angSpeed = w.at( elem );

			if ( torque == 0 )
				ret[elem] = '0';
			else if ( torque*angSpeed < 0 )
				ret[elem] = '-';
			else
				ret[elem] = '+';
		}

	return ret;
}

void ari::TestDefMh::run()
{
	NS_CORE Singletons::getInstance()->setGlobalParameters( 2, 1, 0 );

	NS_CORE InternalGearRatioValue k( -3 );
	const NS_CORE GearSetNumber setN( 1 );

	const NS_CORE Element sun = NS_CORE Element( NS_CORE eMainElement::SUN_GEAR, setN );
	const NS_CORE Element epy = NS_CORE Element( NS_CORE eMainElement::EPICYCLIC_GEAR, setN );
	const NS_CORE Element car = NS_CORE Element( NS_CORE eMainElement::CARRIER, setN );
	const NS_CORE Element in2 = NS_CORE Element( NS_CORE eMainElement::INPUT, setN );

	NS_CORE ChainArray chains;
	NS_CORE Chain chain1( sun );
	chain1.addLinkToChain( NS_CORE Link( NS_CORE Element::INPUT, sun ) );
	NS_CORE Chain chain2( epy );
	chain2.addLinkToChain( NS_CORE Link( in2, epy ) );
	NS_CORE Chain chain3( car );
	chain3.addLinkToChain( NS_CORE Link( NS_CORE Element::OUTPUT, car ) );

	chains.emplace_back( chain1 );
	chains.emplace_back( chain2 );
	chains.emplace_back( chain3 );

	W w;
	const double mIn0 = 1;

	w[ NS_CORE Element::INPUT ] = 3;
	w[ in2] = 1;



	NS_CORE MappedSystem_p systemW = MappedSystemTest::createWTest( chains, w, k );
	NS_CORE Gaus::solve( systemW );
	w = systemW->getSolution();

	NS_CORE MappedSystem_p systemM = MappedSystemTest::createMTest( chains, mIn0, k );
	NS_CORE Gaus::solve( systemM );
	M m = systemM->getSolution();

	N n = calcN( w, m );

	const double ksi_a_c = 0.02;
	const double ksi_b_c = 0.01;
	const double kpdSum = 1 - abs(
		( w[sun] - w[car] ) / ( ( k.getValue() - 1 ) * w[car] )
		) * ( ksi_a_c + ksi_b_c );

	NS_CORE MappedSystem_p systemMn = MappedSystemTest::createMhTest_a_d( chains, mIn0, n, w, k, kpdSum );
	NS_CORE Gaus::solve( systemMn );
	M mn = systemMn->getSolution();

	const double mIn1 = mn[NS_CORE Element::INPUT];
	const double mIn2 = mn[in2];
	const double mOut = mn[NS_CORE Element::OUTPUT];
	const double delta = mIn1 + mIn2 + mOut / kpdSum;
	NS_CORE Log::warning( abs( delta ) > 0.01, "Failed", NS_CORE Log::NON_CRITICAL, HERE );

}

bool ari::TestDefMh::checkRequirements() const
{
	return true;
}

