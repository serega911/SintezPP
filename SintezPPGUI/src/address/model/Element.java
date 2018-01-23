package address.model;

class Element
{
	private eElement elem = null;
	private Integer  gearSet = null;
	
	Element(eElement elem, Integer  gearSet)
	{
		this.elem =  elem;
		this.gearSet = gearSet;
	}

	/*	
	Element(final eElement elem) throws Exception
	{
		switch (elem)
		{
		case SUN_GEAR:
		case EPY_GEAR:
		case CARRIER:
			this.elem =  elem;
			this.gearSet = 0;
			break;
		default:
			throw new Exception();
		}
	}
	*/
}