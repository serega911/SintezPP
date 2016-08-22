#include "GlobalDefines.h"

NS_CORE_START

class IApplication
{
private:

	virtual void								readInitialData() = 0;

public:

	virtual void								run() = 0;

};

NS_CORE_END