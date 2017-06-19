#pragma once
#include <vector>

#include "GlobalDefines.h"
#include "Code.h"
#include "MultiLink.h"

#include "GearNumber.h"
#include "MultiLinkArray.h"

NS_CORE_START

class GearBox
{
private:

	Code										m_code;
	MultiLinkArray									m_chains;

protected:

	void										makeChains( MultiLinkArray &chains ) const;
	Code&										getRefferenceToCode();

public:

	GearBox( const Code& code );

	void										createChains();

	const Code&									getCode() const;
	const MultiLinkArray&							getChains() const;

};

NS_CORE_END
