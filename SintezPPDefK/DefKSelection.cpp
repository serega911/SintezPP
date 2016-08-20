#include "DefKSelection.h"
#include "../Libraries/TGaus.h"
#include "../Libraries/TCombinations.h"
#include "../Libraries/TGearChanger.h"
#include "../Libraries/TSingletons.h"

NS_ARI_USING

TK DefKSelection::calculate( const NS_CORE TCode& Code )
{
	NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::DONE_K_SELECTION, Code );
	
	TK K( 0.1 );
	bool isFinded = false;
	do{
		if ( podModul( Code, K ) )
		{
			isFinded = true;
			NS_CORE TSingletons::getInstance()->getIOFileManager()->writeToFile( NS_CORE TIOFileManager::eOutputFileType::DONE_K_SELECTION, K );
			//break;
		}
	} while ( K.next() );

	if ( !isFinded )
		K.setValues( {} );

	return K;
}

bool DefKSelection::podModul( const NS_CORE TCode & code, const TK &k )
{
	NS_CORE TGearChanger gearChanger( code );
	NS_CORE TI tmpI( {}, 0.001 );	//вектор для полученных передаточных отношений при данном наборе K
	do
	{
		NS_CORE TGaus gaus;
		gaus.createSystem( code, k );
		gaus.createSystemDrivers( gearChanger.getDrivingElementsForGear() );
		gaus.solve();
		if ( gaus.getSolution().size() == 0 )
		{
			return false;
		}
		const auto codeValues = code.getCode();
		double calculatedI = gaus.getSolution()[codeValues[1].getElem1().getSerialNumber()];
		if ( abs( calculatedI ) > 0.001 && core::TSingletons::getInstance()->getInitialData()._i.findIn( 1.0 / calculatedI ) )
		{
			tmpI.push_back( 1.0 / calculatedI );
		}
		else
		{
			return false;
		}

	} while ( gearChanger.next() );
	//сравниваем полученные передаточные отношения с искомыми
	if ( core::TSingletons::getInstance()->getInitialData()._i == tmpI )
	{
		m_iReal = tmpI;
		return true;
	}
	else
		return false;
}
