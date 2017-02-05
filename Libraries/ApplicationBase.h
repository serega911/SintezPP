#include "GlobalDefines.h"

#include <vector>
#include "UIGeneralData.h"
#include "UISpecialData.h"

NS_CORE_START

class ApplicationBase
{
public:

	void										readUIGeneralData();
	void										readUISpecialData();
	void										setUIGeneralData( const UIGeneralData_p& data );
	void										setUISpecialData( const UISpecialData_p& data );

	void										showParams();

	static void									parseOptions( int argc, char* argv[], NS_CORE UISpecialData_p sData, NS_CORE UIGeneralData_p gData );

	virtual void								run() = 0;
	virtual bool								checkRequirements() const  = 0;

};

NS_CORE_END