#include "GearSetFactory.h"



NS_ARI_USING


/*  > - x
	^ - y
	*/
GearSetFactory::GearSetFactory()
{
}


GearSetFactory::~GearSetFactory()
{
}

ari::GearSet ari::GearSetFactory::createGearSet( eGearSetType type )
{
	switch ( type )
	{
	case ari::eGearSetType::TYPE_N:			return createCustom( false, false );	break;
	case ari::eGearSetType::TYPE_N_REVERSE:	return createCustom( true, false );		break;
	case ari::eGearSetType::TYPE_U:			return createCustom( false, true );		break;
	case ari::eGearSetType::TYPE_U_REVERSE:	return createCustom( true, true );		break;
	case ari::eGearSetType::TYPE_DEFAULT:	return createStandart();				break;
	default:																			break;
	}
}

GearSet ari::GearSetFactory::createStandart()
{
	GearSet set;

	set.addCord( Cordinate(0, -2), NS_CORE eMainElement::SUN_GEAR );
	set.addCord( Cordinate( 0, 2 ), NS_CORE eMainElement::EPICYCLIC_GEAR );
	
	for ( int x = -1; x <= 1; x++ )
		set.addCord( Cordinate( x, 0 ), NS_CORE eMainElement::CARRIER );

	set.addCord( Cordinate( 0, -1 ), NS_CORE eMainElement::EMPTY );
	set.addCord( Cordinate( 0, 1 ), NS_CORE eMainElement::EMPTY );

	return set;
}

ari::GearSet ari::GearSetFactory::createCustom( const bool flipX, const bool flipY )
{
	GearSet set;

	int xK = flipX ? -1 : 1;
	int yK = flipY ? -1 : 1;

	set.addCord( Cordinate( xK * ( -1 ), yK * ( -2 ) ), NS_CORE eMainElement::SUN_GEAR );
	set.addCord( Cordinate( xK * ( 1 ), yK * ( -2 ) ), NS_CORE eMainElement::EPICYCLIC_GEAR );

	for ( int x = -1; x <= 1; x++ )
		set.addCord( Cordinate(  x, yK * 2 ), NS_CORE eMainElement::CARRIER );

	for ( int y = -1; y <= 1; y++ )
	{
		set.addCord( Cordinate( -1, y ), NS_CORE eMainElement::EMPTY );
		set.addCord( Cordinate( 1, y ), NS_CORE eMainElement::EMPTY );
	}
	
	return set;
}