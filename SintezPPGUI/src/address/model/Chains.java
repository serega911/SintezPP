package address.model;

class Chains {
	Element[][] chains = { { new Element(eElement.INPUT, 0), new Element(eElement.CARRIER, 1) },
			{ new Element(eElement.OUTPUT, 0), new Element(eElement.CARRIER, 2) },
			{ new Element(eElement.BRAKE, 0), new Element(eElement.EPY_GEAR, 1) },
			{ new Element(eElement.SUN_GEAR, 1), new Element(eElement.SUN_GEAR, 2) }, };

	Chains() {

	}
}