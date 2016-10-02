#include "../Libraries/GlobalDefines.h"
#include "../Libraries/TGearBox.h"

NS_ARI_START

class TGearBox : public NS_CORE TGearBox
{
	typedef NS_CORE TGearBox Parent;
public:

	enum eCheckObject
	{
		IN_OUT_CONNECTION,
		ONE_PM_CONNECTION,
		ALL
	};


	TGearBox( const NS_CORE TCode& code );

	void										setLinksToCode( const NS_CORE TLinkArray& links );						//	Установка связей
	void										setFrictionsToCode( const NS_CORE TLinkArray& frictions );				//	Установка фрикционов
	void										setBrakesToCode( const NS_CORE TLinkArray& brakes );					//	Установка тормозов

	NS_CORE TElementArray						getElementsForFrictions() const;
	NS_CORE TElementArray						getElementsForBrakes() const;

	bool										checkFree() const;
	bool										check( const eCheckObject target ) const;

};

NS_ARI_END