#include "../Libraries/Singletons.h"
#include "../Libraries/Log.h"

#include "MappedSystem.h"

NS_ARI_USING

std::vector<double> solveSquare( const double a, const double b, const double c )
{
	std::vector<double> ret;
	double d = b*b - 4 * a*c;

	if ( d > 0 )
	{
		ret.emplace_back( 
			( -b + pow( d, 0.5 ) ) / ( 2.0*a ) 
			);
		ret.emplace_back( 
			( -b - pow( d, 0.5 ) ) / ( 2.0*a ) 
			);
	}
	else if ( d == 0 )
	{
		ret.emplace_back( 
			-b / ( 2.0*a )
			);
	}

	return ret;
}

bool verifyKpd( const double kpd, const char stepSign )
{
	bool ret;
	if ( kpd > 0 )
	{
		if ( kpd > 1 && stepSign == '-' )
			ret = true;
		else if ( kpd < 1 && stepSign == '+' )
			ret = true;
	}
	else
	{
		ret = false;
	}

	return ret;
}

double choseKpd( const std::vector<double> &kpds, const char stepSign )
{
	std::vector<double> acceptable;

	for ( const auto& kpd: kpds )
	{
		if ( verifyKpd( kpd, stepSign ) )
		{
			acceptable.emplace_back( kpd );
		}
	}

	const int count = acceptable.size();

	NS_CORE Log::warning( count == 0, "no one solution is acceptable", NS_CORE Log::CRITICAL, HERE );

	
	bool condition = count > 1;
	NS_CORE Log::warning( condition, "more than one solution is acceptable", NS_CORE Log::NON_CRITICAL, HERE );

	double ret = acceptable[0];

	if ( condition )
	{
		double delta = abs( 1 - ret );
		
		for ( int i = 1; i < count; i++ )
		{
			const double newDelta = abs( 1 - acceptable[i] );
			if ( newDelta < delta )
				ret = acceptable[i];
		}
	}


	return ret;
}

int sign( char c )
{
	switch ( c ){
	case '+': return 1;
	case '-': return -1;
	case '0': return 0;
	default: NS_CORE Log::warning( true, "wrong signum", NS_CORE Log::CRITICAL, HERE );
	}
}

NS_CORE MappedSystem_p MappedSystemTest::createMhTest_a_d( const NS_CORE ChainArray& chains, const double &mIn0, const N &n, const W &w, const NS_CORE InternalGearRatioValue& k, const double kpdSum )
{
	const NS_CORE GearSetNumber setN( 1 );

	const NS_CORE Element sun = NS_CORE Element( NS_CORE eMainElement::SUN_GEAR, setN );
	const NS_CORE Element epy = NS_CORE Element( NS_CORE eMainElement::EPICYCLIC_GEAR, setN );
	const NS_CORE Element car = NS_CORE Element( NS_CORE eMainElement::CARRIER, setN );

	const double wa = w.at( sun );
	const double wb = w.at( epy );
	const double wh = w.at( car );

	double kpdSumStep = pow( kpdSum, sign( n.at( car ) ) );

	const double a = 2 * ( wb - wa / k.getValue() );
	const double b = wa / k.getValue() * ( 1 + kpdSumStep ) - wb * ( 1 + 2 * kpdSumStep );
	const double c = kpdSumStep * wb;

	const auto kpds = solveSquare( a, b, c );
	const double kpdB = choseKpd( kpds , n.at( car ) );
	const double kpdA = 2 * kpdB - 1;

	NS_CORE InternalGearRatioValueArray ratios;
	ratios.emplace_back( k );

	NS_CORE MappedSystem_p ret = NS_CORE MappedSystem::createM( chains, NS_CORE InternalGearRatios( ratios ), mIn0 );

	MappedSystemTest* ptr = ( (MappedSystemTest*)ret.get() );

	ptr->m_system[0][sun] *= kpdA;
	ptr->m_system[0][NS_CORE Element( NS_CORE eMainElement::EPICYCLIC_GEAR, setN )] *= kpdB;

	ptr->m_system[1][sun] *= kpdA;
	ptr->m_system[1][NS_CORE Element( NS_CORE eMainElement::EPICYCLIC_GEAR, setN )] *= kpdB;

	return ret;
}


NS_CORE MappedSystem_p MappedSystemTest::createMTest( const NS_CORE ChainArray& chains, const double &mIn0, const NS_CORE InternalGearRatioValue& k )
{
	NS_CORE InternalGearRatioValueArray ratios;
	ratios.emplace_back( k );

	NS_CORE MappedSystem_p ret = NS_CORE MappedSystem::createM( chains, NS_CORE InternalGearRatios( ratios ), mIn0 );

	MappedSystemTest* ptr = ( (MappedSystemTest*)ret.get() );


	return ret;
}

NS_CORE MappedSystem_p MappedSystemTest::createWTest( const NS_CORE ChainArray& chains, const W &w, const NS_CORE InternalGearRatioValue& k )
{
	NS_CORE InternalGearRatioValueArray ratios;
	ratios.emplace_back( k );

	NS_CORE MappedSystem_p ret = NS_CORE MappedSystem::createW( chains, NS_CORE InternalGearRatios( ratios ), NS_CORE RatioValue( w.begin()->second ) );
	
	MappedSystemTest* ptr = ( (MappedSystemTest*)ret.get() );

	

	for ( const auto& it : w )
	{
		if ( it.first != w.begin()->first )
		{
			const int pos = ptr->m_system.size();
			ptr->m_system.resize( pos + 1 );

			ptr->m_system[pos][it.first] = 1;
			ptr->m_system[pos][NS_CORE Element::EMPTY] = it.second;

		}
	}

	


	return ret;
}