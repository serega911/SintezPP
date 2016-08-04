#include "TGearChanger.h"
#include "TSingletons.h"

NS_CORE_USING

std::vector<TLink> TGearChanger::createVector(const TCombinations & replacer) const
{
	std::vector<TLink> ret;

	for (int i = 0; i < replacer.size(); i++)
		ret.push_back(m_drivingElements[replacer[i]]);

	return ret;
}

TGearChanger::TGearChanger(const TCode& code)
{
	const auto& generalData = TSingletons::getInstance()->getGeneralData();

	auto startPos = 2 + generalData._numberOfLinks;

	if ( startPos < code.getCode().size() )
	{
		m_drivingElements.insert( m_drivingElements.begin(), code.getCode().begin() + startPos, code.getCode().end() );
		m_replacer.init( generalData._numberOfActuatedDrivingElements );
	}

}

std::vector<TLink> TGearChanger::getDrivingElementsForGear() const
{
	return createVector(m_replacer);
}

// std::vector<TLink> TGearChanger::getDrivingElementsForGear(int gear) const
// {
// 	TCombinations replacer;
// 	
// 	replacer.init(m_replacer.size());
// 	
// 	const auto& generalData = TSingletons::getInstance()->getGeneralData();
// 	
// 	for (int i = 1; i < gear; i++)
// 		replacer.nextReplace( generalData._numberOfFrictions + generalData._numberOfBrakes - 1 );
// 	return createVector(replacer);
// }

bool TGearChanger::next()
{
	const auto& generalData = TSingletons::getInstance()->getGeneralData();

	return m_replacer.nextReplace( generalData._numberOfFrictions + generalData._numberOfBrakes - 1 );
}
