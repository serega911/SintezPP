#include "../Libraries/TGearChanger.h"
#include "../Libraries/TSingletons.h"

std::vector<pss::TLink> pss::TGearChanger::createVector(const pss::TReplace & replacer) const
{
	std::vector<pss::TLink> ret;
	for (int i = 0; i < replacer.size(); i++)
		ret.push_back(m_drivingElements[replacer[i]]);
	return ret;
}

pss::TGearChanger::TGearChanger(const pss::TCode& code)
{
	m_drivingElements.insert(m_drivingElements.begin(), code.getCode().begin() + 2 + pss::TSingletons::getInstance()->getNumberOfLinks(), code.getCode().end());
	m_replacer.init(pss::TSingletons::getInstance()->getNumberOfActuatedDrivingElements());
}

std::vector<pss::TLink> pss::TGearChanger::getDrivingElementsForGear() const
{
	return createVector(m_replacer);
}

std::vector<pss::TLink> pss::TGearChanger::getDrivingElementsForGear(int gear) const
{
	pss::TReplace replacer;
		replacer.init(m_replacer.size());
	for (int i = 1; i < gear; i++)
		replacer.nextReplace(pss::TSingletons::getInstance()->getNumberOfFrictions() + pss::TSingletons::getInstance()->getNumberOfBrakes() - 1);
	return createVector(replacer);
}

bool pss::TGearChanger::next()
{
	return m_replacer.nextReplace(pss::TSingletons::getInstance()->getNumberOfFrictions() + pss::TSingletons::getInstance()->getNumberOfBrakes() - 1);
}
