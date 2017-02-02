#include "GearSetFactory.h"
#include "GearSet.h"

#include "../Libraries/Singletons.h"

NS_ARI_USING


/*  > - x
	^ - y
	*/

GearSetFactory_p& ari::GearSetFactory::getInstance()
{
	static  GearSetFactory_p ret( new GearSetFactory );
	return ret;
}

void ari::GearSetFactory::init( const NS_CORE InternalGearRatios ratio )
{
	const int size = ratio.size();
	m_options.clear();
	for ( int i = 0; i < size; i++ )
	{
		if ( ratio[i].getAbs().getValue() < 2 )
		{
			m_options[NS_CORE GearSetNumber( i + 1 )].add( NS_CORE eGearSetType::TYPE_N );
			m_options[NS_CORE GearSetNumber( i + 1 )].add( NS_CORE eGearSetType::TYPE_N_REVERSE );
		}
		else
		{
			m_options[NS_CORE GearSetNumber( i + 1 )].add( NS_CORE eGearSetType::TYPE_DEFAULT );
			m_options[NS_CORE GearSetNumber( i + 1 )].add( NS_CORE eGearSetType::TYPE_U );
			m_options[NS_CORE GearSetNumber( i + 1 )].add( NS_CORE eGearSetType::TYPE_U_REVERSE );
		}
	}
}

bool ari::GearSetFactory::next()
{
	for ( NS_CORE GearSetNumber i(NS_CORE Singletons::getInstance()->getInitialData()._numberOfPlanetaryGears); i.getValue() > 0; i-- )
	{
		if ( m_options[i].next() )
			return true;
	}

	return false;
}

GearSet_p GearSetFactory::createGearSet( const NS_CORE GearSetNumber & num, const Cordinate& anchor )
{
	NS_CORE eGearSetType type = getType( num );

	switch ( type )
	{
	case NS_CORE eGearSetType::TYPE_N:			return createCustom( anchor, num, false, false );	break;
	case NS_CORE eGearSetType::TYPE_N_REVERSE:	return createCustom( anchor, num, true, false );	break;
	case NS_CORE eGearSetType::TYPE_U:			return createCustom( anchor, num, false, true );	break;
	case NS_CORE eGearSetType::TYPE_U_REVERSE:	return createCustom( anchor, num, true, true );		break;
	case NS_CORE eGearSetType::TYPE_DEFAULT:	return createStandart( anchor, num );				break;
	default:																				break;
	}
}

NS_CORE GearSetTypes ari::GearSetFactory::getTypes() const
{
	NS_CORE GearSetTypes ret;

	for ( const auto& it : m_options )
		ret.add( it.first, it.second.get() );

	return ret;

}

NS_CORE eGearSetType ari::GearSetFactory::getType( const NS_CORE GearSetNumber & num )
{
	return  m_options[num].get();
}

GearSet_p GearSetFactory::createStandart( const Cordinate& anchor, const NS_CORE GearSetNumber & num )
{
	GearSet_p set( new GearSet( anchor ) );

	set->addCord( Cordinate( 0, 2 ), NS_CORE Element( NS_CORE eMainElement::SUN_GEAR, num ) );
	set->addCord( Cordinate( 0, -2 ), NS_CORE Element( NS_CORE eMainElement::EPICYCLIC_GEAR, num ) );
	
	//for ( int x = -1; x <= 1; x++ )
	//	set->addCord( Cordinate( x, 0 ), NS_CORE Element( NS_CORE eMainElement::CARRIER, num ) );
	set->addCord( Cordinate( 0, 0 ), NS_CORE Element( NS_CORE eMainElement::CARRIER, num ) );

	set->addCord( Cordinate( 0, -1 ), NS_CORE Element( NS_CORE eMainElement::EMPTY, num ) );
	set->addCord( Cordinate( 0, 1 ), NS_CORE Element( NS_CORE eMainElement::EMPTY, num ) );

	return set;
}

GearSet_p GearSetFactory::createCustom( const Cordinate& anchor, const NS_CORE GearSetNumber & num, const bool flipX, const bool flipY )
{
	GearSet_p set( new GearSet( anchor ) );

	int xK = flipX ? -1 : 1;
	int yK = flipY ? -1 : 1;

	set->addCord( Cordinate( xK * ( -1 ), yK * ( 2 ) ), NS_CORE Element( NS_CORE eMainElement::SUN_GEAR, num ) );
	set->addCord( Cordinate( xK * ( 1 ), yK * ( 2 ) ), NS_CORE Element( NS_CORE eMainElement::EPICYCLIC_GEAR, num ) );

	//for ( int x = -1; x <= 1; x++ )
	//	set->addCord( Cordinate( x, yK * -2 ), NS_CORE Element( NS_CORE eMainElement::CARRIER, num ) );
	set->addCord( Cordinate( 0, yK * -1 ), NS_CORE Element( NS_CORE eMainElement::CARRIER, num ) );

	for ( int y = -1; y <= 1; y++ )
	{
		set->addCord( Cordinate( -1, y ), NS_CORE Element( NS_CORE eMainElement::EMPTY, num ) );
		set->addCord( Cordinate( 1, y ), NS_CORE Element( NS_CORE eMainElement::EMPTY, num ) );
	}
	
	return set;
}