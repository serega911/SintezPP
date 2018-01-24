package address.model;

import java.util.HashSet;
import java.util.Map.Entry;
import java.util.Set;
import java.util.TreeMap;

import javafx.beans.property.StringProperty;

public class SchemeData {

	public class Data{
		TreeMap<String, Double> velocity = new TreeMap<String, Double>();
		TreeMap<String, Double> torque = new TreeMap<String, Double>();
		TreeMap<String, String> power = new TreeMap<String, String>();
		TreeMap<String, Double> torqu_kpd = new TreeMap<String, Double>();
	}
	
	TreeMap<Integer, Data> data = new TreeMap<Integer, Data>();
	
	
	public void add(final String header, final String values, Integer gear, eType type) throws Exception
	{
		String[] parsedValues = values.split("[ ]{1,}", 0);
		String[] parsedKeys = header.split("[ ]{1,}", 0);
		
		if (parsedValues.length != parsedKeys.length)
			throw new Exception("keys and values not matched");

		Data gearData = data.get(gear);
		if (gearData == null)
		{
			gearData = new Data();
			data.put(gear, gearData);
		}
		
		int length = parsedValues.length;
		
		for (Integer i = 0; i < length; i++)
		{
			switch (type)
			{
			case ANG_VELOCITY:
				gearData.velocity.put(parsedKeys[i], Double.parseDouble(parsedValues[i]));
				break;
			case TORQUE:
				gearData.torque.put(parsedKeys[i], Double.parseDouble(parsedValues[i]));
				break;
			case TORQUE_KPD:
				gearData.torqu_kpd.put(parsedKeys[i], Double.parseDouble(parsedValues[i]));
				break;
			case POWER:
				gearData.power.put(parsedKeys[i], parsedValues[i]);
				break;
			}
		}
	}
	
	public Set<String> getColumnHeaders(eType type)
	{
		Set<String> ret = new HashSet<String>();
		
		for (Entry<Integer, Data> entry : data.entrySet())
		{
			switch (type)
			{
			case ANG_VELOCITY:
				for (String key : entry.getValue().velocity.keySet())
					ret.add(key);
				break;
			case TORQUE:
				for (String key : entry.getValue().torque.keySet())
					ret.add(key);
				break;
			case TORQUE_KPD:
				for (String key : entry.getValue().torqu_kpd.keySet())
					ret.add(key);
				break;
			case POWER:
				for (String key : entry.getValue().power.keySet())
					ret.add(key);
				break;
			}
		}
		
		
		return ret;
	}

	public String getValue(eType type, Integer gear, String elem) {
		switch (type)
		{
		case ANG_VELOCITY:	return data.get(gear).velocity.get(elem).toString();
		case TORQUE:		return data.get(gear).torque.get(elem).toString();
		case TORQUE_KPD:	return data.get(gear).torqu_kpd.get(elem).toString();
		case POWER:			return data.get(gear).power.get(elem).toString();
		default:			return null;
		}
		
	}
}
