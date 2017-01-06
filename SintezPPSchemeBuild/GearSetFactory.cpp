#include "GearSetFactory.h"
#include "GearSet.h"


NS_ARI_USING


/*  > - x
	^ - y
	*/

GearSet_p GearSetFactory::createGearSet( const NS_CORE InternalGearRatioValue ratio, const NS_CORE GearSetNumber & num, const Cordinate& anchor )
{
	eGearSetType type = getType( ratio );

	switch ( type )
	{
	case eGearSetType::TYPE_N:			return createCustom( anchor, num, false, false );	break;
	case eGearSetType::TYPE_N_REVERSE:	return createCustom( anchor, num, true, false );	break;
	case eGearSetType::TYPE_U:			return createCustom( anchor, num, false, true );	break;
	case eGearSetType::TYPE_U_REVERSE:	return createCustom( anchor, num, true, true );		break;
	case eGearSetType::TYPE_DEFAULT:	return createStandart( anchor, num );				break;
	default:																				break;
	}
}

ari::eGearSetType ari::GearSetFactory::getType( const NS_CORE InternalGearRatioValue ratio )
{
	return ratio.getAbs().getValue() < 2 ? eGearSetType::TYPE_N : eGearSetType::TYPE_DEFAULT;
}

GearSet_p GearSetFactory::createStandart( const Cordinate& anchor, const NS_CORE GearSetNumber & num )
{
	GearSet_p set( new GearSet( anchor ) );

	set->addCord( Cordinate( 0, -2 ), NS_CORE Element( NS_CORE eMainElement::SUN_GEAR, num ) );
	set->addCord( Cordinate( 0, 2 ), NS_CORE Element( NS_CORE eMainElement::EPICYCLIC_GEAR, num ) );
	
	for ( int x = -1; x <= 1; x++ )
		set->addCord( Cordinate( x, 0 ), NS_CORE Element( NS_CORE eMainElement::CARRIER, num ) );

	set->addCord( Cordinate( 0, -1 ), NS_CORE Element( NS_CORE eMainElement::EMPTY, num ) );
	set->addCord( Cordinate( 0, 1 ), NS_CORE Element( NS_CORE eMainElement::EMPTY, num ) );

	return set;
}

GearSet_p GearSetFactory::createCustom( const Cordinate& anchor, const NS_CORE GearSetNumber & num, const bool flipX, const bool flipY )
{
	GearSet_p set( new GearSet( anchor ) );

	int xK = flipX ? -1 : 1;
	int yK = flipY ? -1 : 1;

	set->addCord( Cordinate( xK * ( -1 ), yK * ( -2 ) ), NS_CORE Element( NS_CORE eMainElement::SUN_GEAR, num ) );
	set->addCord( Cordinate( xK * ( 1 ), yK * ( -2 ) ), NS_CORE Element( NS_CORE eMainElement::EPICYCLIC_GEAR, num ) );

	for ( int x = -1; x <= 1; x++ )
		set->addCord( Cordinate( x, yK * 2 ), NS_CORE Element( NS_CORE eMainElement::CARRIER, num ) );

	for ( int y = -1; y <= 1; y++ )
	{
		set->addCord( Cordinate( -1, y ), NS_CORE Element( NS_CORE eMainElement::EMPTY, num ) );
		set->addCord( Cordinate( 1, y ), NS_CORE Element( NS_CORE eMainElement::EMPTY, num ) );
	}
	
	return set;
}