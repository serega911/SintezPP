package address.model;

import java.util.HashMap;
import java.util.LinkedList;

public class DrawData {

	private LinkedList<eGearSetType> gearSetsTypes = new LinkedList<eGearSetType>();
	private HashMap<String, LinkedList<Cord>> chainsTraces = new HashMap<String, LinkedList<Cord>>();

	public void setTypes(final String types) {
		for (String value : types.trim().split("[ ]{1,}", 0)) {
			gearSetsTypes.add(eGearSetType.fromString(value));
		}
	}

	public void setTraces(final String traces) {
		for (String records : traces.trim().split(";")) {
			String[] values = records.split(":");
			final String key = values[0].trim();
			boolean isFirst = true;

			LinkedList<Cord> cords = chainsTraces.get(key);
			if (cords == null)
				cords = new LinkedList<Cord>();

			for (String cord : values[1].trim().split(" ")) {
				cords.add(new Cord(cord, isFirst));
				isFirst = false;
			}
			chainsTraces.put(key, cords);
		}
	}

	public HashMap<String, LinkedList<Cord>> getCords() {
		return chainsTraces;
	}

	public LinkedList<eGearSetType> getSetsTypes() {
		return gearSetsTypes;
	}
}
