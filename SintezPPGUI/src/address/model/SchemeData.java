package address.model;

import java.util.TreeMap;

import com.sun.javafx.collections.MappingChange.Map;

public class SchemeData {

	enum eType
	{
		ANG_VELOCITY,
		TORQUE,
		POWER,
		TORQUE_KPD,		
	}
	
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
}
