#include "../Libraries/GlobalDefines.h"
#include "../Libraries/TGearBox.h"

NS_ARI_START

class TGearBox : public NS_CORE TGearBox
{
	typedef NS_CORE TGearBox Parent;
public:

	TGearBox( const NS_CORE TCode& code );

	void										setLinksToCode( const NS_CORE TLinks& links );						//	��������� ������
	void										setFrictionsToCode( const NS_CORE TLinks& frictions );				//	��������� ����������
	void										setBrakesToCode( const NS_CORE TLinks& brakes );					//	��������� ��������

	NS_CORE TElements							getElementsForFrictions() const;
	NS_CORE TElements							getElementsForBrakes() const;

	bool										checkFree() const;
	bool										check() const;

};

NS_ARI_END