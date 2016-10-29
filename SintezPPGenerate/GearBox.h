#include "../Libraries/GlobalDefines.h"
#include "../Libraries/GearBox.h"
#include "../Libraries/ElementArray.h"

NS_ARI_START

class GearBox : public NS_CORE GearBox
{
	typedef NS_CORE GearBox Parent;
public:

	enum eCheckTarget
	{
		IN_OUT_CONNECTION,
		ONE_PM_CONNECTION,
		ALL
	};


	GearBox( const NS_CORE Code& code );

	void										setLinksToCode( const NS_CORE TLinkArray& links );						//	Установка связей
	void										setFrictionsToCode( const NS_CORE TLinkArray& frictions );				//	Установка фрикционов
	void										setBrakesToCode( const NS_CORE TLinkArray& brakes );					//	Установка тормозов

	NS_CORE ElementArray						getElementsForFrictions() const;
	NS_CORE ElementArray						getElementsForBrakes() const;

	bool										checkFree() const;
	bool										check( const eCheckTarget target ) const;

};

NS_ARI_END