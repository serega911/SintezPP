#include "Function.h"
#include "Types.h"


NS_ARI_USING

ari::Function::Function( const N& n )
{
	m_na = sign( n.at( sun ) );
	m_nb = sign( n.at( epy ) );
	m_nh = sign( n.at( car ) );
}

int Function::sign( char c )
{
	switch ( c ){
	case '+': return 1;
	case '-': return -1;
	case '0': return 0;
	default: NS_CORE Log::warning( true, "wrong signum", NS_CORE Log::CRITICAL, HERE );
	}
}

ari::Function_p ari::Function::create( const NS_CORE InternalGearRatioValue& k, const W& w, const N& n )
{
	const int signA = sign( n.at( sun ) );
	const int signB = sign( n.at( epy ) );
	const int signH = sign( n.at( car ) );
	
	if ( signA * signB > 0 && signA * signH < 0 )
		return createAD( k, w, n );
	if ( signA * signH > 0 && signA * signB < 0 )
		return createBE( k, w, n );
	if ( signB * signH > 0 && signA * signB < 0 )
		return createCF( k, w, n );
	else
		NS_CORE Log::warning( true, "Cant create function", NS_CORE Log::CRITICAL, HERE );

}

Function_p Function::createAD( const NS_CORE InternalGearRatioValue& k, const W& w, const N& n )
{
	Function_p ret( new Function(n) );

	const double ksi_a_c = 0.02;
	const double ksi_b_c = 0.01;
	ret->m_kpdSum = 1 - abs(
		( w.at(sun) - w.at(car) ) / ( ( k.getValue() - 1 ) * w.at(car) )
		) * ( ksi_a_c + ksi_b_c );

	ret->m_a = w.at(epy);
	ret->m_b = - w.at( sun ) / k.getValue();
	ret->m_c = pow( ret->m_kpdSum, -ret->m_nh ) * ( w.at( sun ) / k.getValue() - w.at( epy ) );

	NS_CORE Log::showValue( "kpdSum", ret->m_kpdSum );
	NS_CORE Log::log( "created type AD" );

	return ret;
}

ari::Function_p ari::Function::createBE( const NS_CORE InternalGearRatioValue& k, const W& w, const N& n)
{
	Function_p ret( new Function( n ) );

 	const double ksi_a_c = 0.02;
 	const double ksi_b_c = 0.01;
 	ret->m_kpdSum = 1 - abs(
 		( w.at( epy ) - w.at( car ) ) /  w.at( epy )
 		) * ( ksi_a_c + ksi_b_c );
 
	ret->m_a = pow( ret->m_kpdSum, ret->m_na ) * ( w.at( car ) * ( 1 - k.getValue() ) - w.at( sun ) );
 	ret->m_b = w.at( sun );
	ret->m_c = - w.at( car ) * ( 1 - k.getValue() );

	NS_CORE Log::showValue( "kpdSum", ret->m_kpdSum );
	NS_CORE Log::log( "created type BE" );

	return ret;
}

ari::Function_p ari::Function::createCF( const NS_CORE InternalGearRatioValue& k, const W& w, const N& n)
{
	Function_p ret( new Function( n ) );

 	const double ksi_a_c = 0.02;
 	const double ksi_b_c = 0.01;
 	ret->m_kpdSum = 1 - abs(
 		( w.at( sun ) - w.at( car ) ) / w.at( sun )
 		) * ( ksi_a_c + ksi_b_c );
 
	ret->m_a = k.getValue() * w.at( epy );
	ret->m_b = pow( -ret->m_kpdSum, -ret->m_na ) * ( k.getValue() * w.at( epy ) + w.at( car ) *( 1 - k.getValue() ) );
	ret->m_c = w.at( car ) * ( 1 - k.getValue() );

	NS_CORE Log::showValue( "kpdSum", ret->m_kpdSum );
	NS_CORE Log::log( "created type CF" );

	return ret;
}

double ari::Function::getKpdSum()
{
	return m_kpdSum;
}

double Function::calc( double kpdb ) const
{
	return pow( kpdb, m_nb ) * m_a + pow( 2 * kpdb - 1, m_na ) * m_b + m_c;
}

