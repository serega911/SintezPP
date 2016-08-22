#include "TGearChanger.h"
#include "TSingletons.h"

NS_CORE_USING

TLinkArray TGearChanger::createVector( const TCombinations & replacer ) const
{
	TLinkArray ret;

	for (int i = 0; i < replacer.size(); i++)
		ret.push_back(m_drivingElements[replacer[i]]);

	return ret;
}

TGearChanger::TGearChanger(const TCode& code)
{
	const auto& generalData = TSingletons::getInstance()->getGeneralData();

	size_t startPos = 2 + generalData._numberOfLinks;

	if ( startPos < code.getCode().size() )
	{
		m_drivingElements.insert( m_drivingElements.begin(), code.getCode().begin() + startPos, code.getCode().end() );
		m_replacer.init( generalData._numberOfActuatedDrivingElements );
	}

}

TLinkArray TGearChanger::getDrivingElementsForGear() const
{
	return createVector(m_replacer);
}

bool TGearChanger::next()
{
	const auto& generalData = TSingletons::getInstance()->getGeneralData();

	return m_replacer.nextReplace( generalData._numberOfFrictions + generalData._numberOfBrakes - 1 );
}
