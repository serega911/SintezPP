#pragma once

#include <vector>

#include "Link.h"
#include "Code.h"
#include "GlobalDefines.h"

NS_CORE_START

class GearChanger
{
private:

	
	struct DrivingElementPosition
	{
		enum eType { BRAKE, FRICTION };

		eType	_type;
		size_t				_pos;
		DrivingElementPosition( const eType& type, const size_t& position ) : _type( type ), _pos( position ){}
	};

	TLinkArray									m_drivingElements;
	std::vector<TLinkArray>						m_drivingElementsForAllGears;
	size_t										m_gear;

	static std::vector<std::vector<DrivingElementPosition>>		m_driveElemPostions;

	void										initDriveElemPositions();

public:

	GearChanger() = delete;
	GearChanger(const Code& code);

	TLinkArray									getDrivingElementsForGear() const;
	bool										next();

};

NS_CORE_END