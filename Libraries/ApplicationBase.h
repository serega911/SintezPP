#include "GlobalDefines.h"


NS_CORE_START

class ApplicationBase
{
public:

	struct UIGeneralData
	{
		size_t _w;
		size_t _n;
		size_t _d;
	};

	void										readUIGeneralData();
	void										setUIGeneralData( const UIGeneralData& data );

	void										showParams();

	virtual void								run() = 0;



};

NS_CORE_END