package address.model;

import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

public class SchemeData {

	private ObservableList<Map<String, String>> velocity = FXCollections.observableArrayList();
	private ObservableList<Map<String, String>> power = FXCollections.observableArrayList();
	private ObservableList<Map<String, String>> torque = FXCollections.observableArrayList();
	private ObservableList<Map<String, String>> torque_kpd = FXCollections.observableArrayList();
	private ObservableList<Map<String, String>> qualityCriteria = FXCollections.observableArrayList();

	private String 								internalRatios;
	private List<String>						chains = new LinkedList<String>();

	public void add(final String header, final String values, final eType type) throws Exception {
		String[] parsedValues = values.split("[ ]{1,}", 0);
		String[] parsedKeys = header.split("[ ]{1,}", 0);

		if (parsedValues.length != parsedKeys.length)
			throw new Exception("keys and values not matched \n" + header + "\n" + values);

		Map<String, String> dataRow = new HashMap<>();

		if(type != eType.QC) {
			final Integer n = getValue(type).size() + 1;
			dataRow.put("#Gear", n.toString());
		}

		for (Integer i = 0; i < parsedValues.length; i++)
			dataRow.put(parsedKeys[i], parsedValues[i]);

		getValue(type).add(dataRow);
	}

	public void setGearRatios(final String ratios) {
		internalRatios = ratios;
	}

	public void addChain(final String chain) {
		chains.add(chain);
	}

	public String getChains() {
		String ret = "";
		for (String str: chains) {
			ret += str + "\n";
		}
		return ret;
	}

	public String getInternalRatios() {
		return internalRatios;
	}

	public ObservableList<Map<String, String>> getValue(eType type) {
		switch (type) {
		case ANG_VELOCITY:
			return velocity;
		case TORQUE:
			return torque;
		case TORQUE_KPD:
			return torque_kpd;
		case POWER:
			return power;
		case QC:
			return qualityCriteria;
		default:
			return null;
		}
	}

	public Set<String> getColumnHeaders(eType key) {
		Set<String> ret = new HashSet<String>();

		for (Map<String, String> entry : getValue(key))
			for (String key1 : entry.keySet())
				ret.add(key1);

		return ret;
	}
}
