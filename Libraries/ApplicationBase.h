#include "GlobalDefines.h"


NS_CORE_START

class ApplicationBase
{
private:

	virtual void								readInitialData() = 0;

public:

	virtual void								run() = 0;

protected:

	void										readWND();

};

NS_CORE_END