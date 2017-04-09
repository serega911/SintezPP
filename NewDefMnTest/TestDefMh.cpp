#include <map>

#include "TestDefMh.h"
#include "MappedSystem.h"
#include "Function.h"
#include "SolveFunctionDiv.h"
#include "Types.h"
#include "../Libraries/Gaus.h"
#include "../Libraries/Code.h"
#include "../Libraries/Singletons.h"
#include "../Libraries/GearBox.h"

NS_ARI_USING

N ari::TestDefMh::calcN( const W& w, const M& m )
{
	N ret;
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

	std::vector < NS_CORE TLinkArray> schemes = {
		{ NS_CORE Link( NS_CORE Element::INPUT, sun ), NS_CORE Link( in2, epy ), NS_CORE Link( NS_CORE Element::OUTPUT, car ) },
		{ NS_CORE Link( NS_CORE Element::INPUT, sun ), NS_CORE Link( in2, car ), NS_CORE Link( NS_CORE Element::OUTPUT, epy ) },
		{ NS_CORE Link( NS_CORE Element::INPUT, epy ), NS_CORE Link( in2, car ), NS_CORE Link( NS_CORE Element::OUTPUT, sun ) }
	};

	std::vector<NS_CORE InternalGearRatioValue> internalGearRatios =
	{
		NS_CORE InternalGearRatioValue( -2 ),
		NS_CORE InternalGearRatioValue( -3.5 ),
		NS_CORE InternalGearRatioValue( -5 ),
	};

	std::vector < W > inputVelocities = {
		{ { NS_CORE Element::INPUT, 2 }, { in2, 1 } },
		{ { NS_CORE Element::INPUT, 1 }, { in2, 2 } },
		{ { NS_CORE Element::INPUT, 7 }, { in2, 1 } },
		{ { NS_CORE Element::INPUT, 1 }, { in2, 7 } },
		{ { NS_CORE Element::INPUT, -5 }, { in2, 5 } },
		{ { NS_CORE Element::INPUT, 5 }, { in2, -5 } },
		{ { NS_CORE Element::INPUT, -5 }, { in2, 2 } },
		{ { NS_CORE Element::INPUT, 2 }, { in2, -5 } },
		{ { NS_CORE Element::INPUT, 5 }, { in2, -2 } },
		{ { NS_CORE Element::INPUT, -2 }, { in2, 5 } }
	};

	const std::vector <double> mIn0 = { 
		1,
		-1
	};

	for ( const auto& links : schemes )
		for ( const auto& k : internalGearRatios )
			for ( const auto& w : inputVelocities )
				for ( const auto& m : mIn0 )
				{
					NS_CORE Log::log( "=====================================", true, NS_CORE eColor::GREEN );
					NS_CORE Log::showValue( "input torque = ", m );
					NS_CORE Log::showValue( "k = ", k.getValue() );

					for ( const auto &link : links )
					{
						link.print();
						NS_CORE Log::log( " ", false );
					}
					NS_CORE Log::log( "" );

					NS_CORE Log::log( "w initial:", true, NS_CORE eColor::AQUA );
					printCharacteristicsLine( w );

					

					doTest( links, k, w, m );
				}


}

bool ari::TestDefMh::checkRequirements() const
{
	return true;
}

ari::M ari::TestDefMh::calcMn( const NS_CORE ChainArray& chains, const N& n, const NS_CORE InternalGearRatioValue& k, const double mIn0, const IFunction_p func )
{
	const double kpdB = SolveFunctionDiv::create()->calc( func, 0.8, 1.0 );
	const double kpdA = 2 * kpdB - 1;
	const double kpdAstep = pow( kpdA, -Function::sign( n.at( sun ) ) );
	const double kpdBstep = pow( kpdB, -Function::sign( n.at( epy ) ) );

	NS_CORE Log::showValue( "kpdA", kpdA );
	NS_CORE Log::showValue( "kpdB", kpdB );

	NS_CORE MappedSystem_p systemMn = MappedSystemTest::createMhTest( chains, mIn0, k, kpdAstep, kpdBstep );
	NS_CORE Gaus::solve( systemMn );
	M mn = systemMn->getSolution();

	//check
	const double torque1 = mn.at( sun ) * kpdAstep + mn.at( epy ) * kpdBstep + mn.at( car );
	NS_CORE Log::warning( abs( torque1 ) > 0.0002, "Failed. torque1kpd = " + std::to_string( torque1 ), NS_CORE Log::NON_CRITICAL, HERE );

	const double torque2 = k.getValue() * mn.at( sun ) * kpdAstep + mn.at( epy ) * kpdBstep;
	NS_CORE Log::warning( abs( torque2 ) > 0.0002, "Failed. torque2kpd = " + std::to_string( torque2 ), NS_CORE Log::NON_CRITICAL, HERE );


	return mn;
}

NS_CORE ChainArray ari::TestDefMh::createChains( const NS_CORE TLinkArray & links )
{
	NS_CORE ChainArray chains;

	for ( const auto link : links )
	{
		NS_CORE Chain chain;
		chain.addLinkToChain(link );
		chains.emplace_back( chain );
	}
	
	return chains;
}

void ari::TestDefMh::doTest( const NS_CORE TLinkArray& links, const NS_CORE InternalGearRatioValue& k, const W& w, const double mIn )
{
	NS_CORE ChainArray chains = createChains( links );

	NS_CORE MappedSystem_p systemW = MappedSystemTest::createWTest( chains, w, k );
	NS_CORE Gaus::solve( systemW );
	W wn = systemW->getSolution();

	NS_CORE Log::log( "w:", true, NS_CORE eColor::AQUA );
	printCharacteristicsLine( wn );

	NS_CORE MappedSystem_p systemM = MappedSystemTest::createMTest( chains, mIn, k );
	NS_CORE Gaus::solve( systemM );
	M m = systemM->getSolution();

	NS_CORE Log::log( "m:", true, NS_CORE eColor::AQUA );
	printCharacteristicsLine( m );

	N n = calcN( wn, m );

	NS_CORE Log::log( "n:", true, NS_CORE eColor::AQUA );
	printCharacteristicsLine( n );

	Function_p func = Function::create( k, wn, n );

	M mn = calcMn( chains, n, k, mIn, func );

	NS_CORE Log::log( "mn:", true, NS_CORE eColor::AQUA );
	printCharacteristicsLine( mn );

	const double factKpd = calcKpd( n, mn, wn );
	NS_CORE Log::showValue( "KPD fact: ", factKpd );

	//check
	const double delta = func->getKpdSum() - factKpd;
	NS_CORE Log::warning( abs( delta ) > 0.0005, "Failed. Delta = " + std::to_string(delta), NS_CORE Log::NON_CRITICAL, HERE );

	const double wyllys = wn.at( sun ) - wn.at( epy ) *k.getValue() + wn.at( car )*( k.getValue() - 1.0f );
	NS_CORE Log::warning( abs( wyllys ) > 0.0002, "Failed. Wyllys = " + std::to_string( wyllys ), NS_CORE Log::NON_CRITICAL, HERE );

	const double torque1 = m.at( sun ) + m.at( epy ) + m.at( car );
	NS_CORE Log::warning( abs( torque1 ) > 0.0002, "Failed. torque1 = " + std::to_string( torque1 ), NS_CORE Log::NON_CRITICAL, HERE );

	const double torque2 = k.getValue() * m.at( sun ) + m.at( epy );
	NS_CORE Log::warning( abs( torque2 ) > 0.0002, "Failed. torque2 = " + std::to_string( torque2 ), NS_CORE Log::NON_CRITICAL, HERE );
}

double ari::TestDefMh::calcKpd( const N& n, const M& m, const W& w )
{
	const int signA = Function::sign( n.at( sun ) );
	const int signB = Function::sign( n.at( epy ) );
	const int signH = Function::sign( n.at( car ) );

	double kpd = 0;

	const double nA = m.at( sun ) * w.at( sun );
	const double nB = m.at( epy ) * w.at( epy );
	const double nC = m.at( car ) * w.at( car );

	if ( signA * signB > 0 && signA * signH < 0 )
	{
		kpd = pow( nA + nB, signA ) * pow( nC, signH );
		NS_CORE Log::log( "verifyed type AD" );
	}
	else if ( signA * signH > 0 && signA * signB < 0 )
	{
		kpd = pow( nA + nC, signA ) * pow( nB, signB );
		NS_CORE Log::log( "verifyed type BE" );
	}
	else if ( signB * signH > 0 && signA * signB < 0 )
	{
		kpd = pow( nB + nC, signB ) * pow( nA, signA );
		NS_CORE Log::log( "verifyed type CF" );
	}
	else
		NS_CORE Log::warning( true, "Cant calculate KPD", NS_CORE Log::CRITICAL, HERE );

	return abs(kpd);
}

