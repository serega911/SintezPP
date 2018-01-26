package address.model;

import java.util.HashMap;
import java.util.LinkedList;

import com.sun.javafx.collections.MappingChange.Map;

public class DrawData {

	class Cord {
		private Integer x;
		private Integer y;

		Cord(final String str) {
			String[] values = str.split(",");
			x = Integer.parseInt(values[0]);
			y = Integer.parseInt(values[1]);
		}
	}

	enum eGearSetType {
		TUPE_DEFAULT("D"), TYPE_U("U"), TYPE_U_REVERSE("U_R"), TYPE_P("P"), TYPE_P_REVERSE("P_R");

		private String text;

		eGearSetType(String text) {
			this.text = text;
		};

		public String getText() {
			return this.text;
		}

		public static eGearSetType fromString(String text) {
			for (eGearSetType b : eGearSetType.values()) {
				if (b.text.equalsIgnoreCase(text)) {
					return b;
				}
			}
			return null;
		}
	}

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
			LinkedList<Cord> cords = new LinkedList<Cord>();
			for (String cord : values[1].trim().split(" ")) {
				cords.add(new Cord(cord));
			}
			chainsTraces.put(key, cords);
		}
	}
}
