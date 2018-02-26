package address.model;

import java.io.BufferedReader;

import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class Scheme {

	// private ObjectProperty<Chains> chains = new SimpleObjectProperty<Chains>();
	private StringProperty code = new SimpleStringProperty();
	private SchemeData schemeData = new SchemeData();
	private DrawData drawData = new DrawData();

	private static final String elemRegex = "([a-zA-Z][0-9])";
	private static final String linkRegex = "(" + elemRegex + elemRegex + ")";
	private static final String frictionRegex = "(" + elemRegex + elemRegex + "F[0-9])";
	private static final String codeRegex = "(" + linkRegex + "\\s+)*(" + frictionRegex + "\\s+)+(" + linkRegex
			+ "\\s+)*";
	private static final String chainRegex = "(" + elemRegex + "+\\s*)+";
	private static final String velocityRgex = "W:\\s*";
	private static final String torqueRgex = "M:\\s*";
	private static final String torqueKpdRgex = "M_KPD:\\s*";
	private static final String powerRegex = "N:\\s*";
	private static final String toothRegex = "Z:\\s*";
	private static final String qcRegex = "QK:\\s*";
	private static final String traceRegex = "((" + elemRegex + ")*:(\\s*\\d*,\\d*)*;\\s*)+";
	private static final String gearSetsTypesRegex = "(\\s*[D|U|N|(U_R)|(N_R)]\\s*)+";
	private static final String numericValuesRegex = "([-+]*\\d+\\.*\\d*(e-)*\\d*\\s*)+";
	private static final String powerValuesRegex = "([+-0]\\s*)+";
	private static final String headerRegex = "(\\s*" + elemRegex + "[0-9]*\\s+)+";
	private static final String qcHeaderRegex = "(\\s*K\\d(_\\d)*\\s*)+";

	public Scheme() {
	}

	public boolean loadFromFile(BufferedReader br) throws Exception {
		String header = "";
		eType type = null;

		String strLine;
		while ((strLine = br.readLine()) != null) {

			System.out.print(strLine);
			if (strLine.matches(codeRegex)) {
				this.code.set(strLine);
				System.out.println(" - code");
			} else if (strLine.matches(headerRegex) || strLine.matches(qcHeaderRegex)) {
				header = strLine;
				System.out.println(" - header");
			} else if (strLine.matches(chainRegex)) {
				schemeData.addChain(strLine);
				System.out.println(" - chain");
			} else if (strLine.matches(traceRegex)) {
				drawData.setTraces(strLine);
				System.out.println(" - trace");
			} else if (strLine.matches(gearSetsTypesRegex)) {
				drawData.setTypes(strLine);
				System.out.println(" - gear sets types");
			} else if (strLine.matches(numericValuesRegex) || strLine.matches(powerValuesRegex)) {
				if (type != null)
					schemeData.add(header, strLine, type);
				else
					schemeData.setGearRatios(strLine);
				System.out.println(" - data values");
			} else if (strLine.matches(velocityRgex)) {
				type = eType.ANG_VELOCITY;
				System.out.println(" - velocity");
			} else if (strLine.matches(torqueRgex)) {
				type = eType.TORQUE;
				System.out.println(" - torque");
			} else if (strLine.matches(torqueKpdRgex)) {
				type = eType.TORQUE_KPD;
				System.out.println(" - torqueKpd");
			} else if (strLine.matches(powerRegex)) {
				type = eType.POWER;
				System.out.println(" - power");
			} else if (strLine.matches(qcRegex)) {
				type = eType.QC;
				System.out.println(" - qc");
			} else if (strLine.matches(toothRegex)) {
				type = null;
				System.out.println(" - tooth");
			} else if (strLine.matches("end\\s*")) {
				System.out.println("+++++++++++++++++++++++++++++END+++++++++++++++++++++++++++");
				return true;
			}
		}

		return false;
	}

	public StringProperty codeProperty() {
		return code;
	}

	public final SchemeData getData() {
		return schemeData;
	}

	public final DrawData getDrawData() {
		return drawData;
	}
}
