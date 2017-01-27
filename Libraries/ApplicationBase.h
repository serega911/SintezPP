#include "GlobalDefines.h"

#include <vector>

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

	struct UISpecialData
	{
		std::vector<std::pair<float, float>>	_ranges;
		std::vector<float>						_i;
	};

	void										readUIGeneralData();
	void										readUISpecialData();
	void										setUIGeneralData( const UIGeneralData& data );
	void										setUISpecialData( const UISpecialData& data );

	void										showParams();

	virtual void								run() = 0;
	virtual bool								checkRequirements() const  = 0;

};

NS_CORE_END