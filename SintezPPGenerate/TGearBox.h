#include "../Libraries/GlobalDefines.h"
#include "../Libraries/TGearBox.h"

NS_ARI_START

class TGearBox : public NS_CORE TGearBox
{
	typedef NS_CORE TGearBox Parent;
public:

	TGearBox( const NS_CORE TCode& code );

	void										setLinksToCode( const NS_CORE TLinks& links );						//	Установка связей
	void										setFrictionsToCode( const NS_CORE TLinks& frictions );				//	Установка фрикционов
	void										setBrakesToCode( const NS_CORE TLinks& brakes );					//	Установка тормозов

	NS_CORE TElements							getElementsForFrictions() const;
	NS_CORE TElements							getElementsForBrakes() const;

	bool										checkFree() const;
	bool										check() const;

};

NS_ARI_END