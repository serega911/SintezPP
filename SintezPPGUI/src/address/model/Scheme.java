package address.model;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

public class Scheme {

	//private ObjectProperty<Chains> chains = new SimpleObjectProperty<Chains>();
	private StringProperty         code = new SimpleStringProperty();
	private SchemeData             data = new SchemeData();

	public Scheme()
	{
	}

	public boolean loadFromFile(BufferedReader br)
	{
		final String elemRegex = "([a-zA-Z][0-9])";
		final String linkRegex = "(" + elemRegex + elemRegex + ")";
		final String frictionRegex = "(" + elemRegex + elemRegex + "F[0-9])";
		final String codeRegex = "(" + linkRegex + "\\s+)*(" + frictionRegex + "\\s+)+(" + linkRegex + "\\s+)*";
		final String chainRegex = "(" + elemRegex + "+\\s*)+";
		final String velocityRgex = "W:\\s*";
		final String torqueRgex = "M:\\s*";
		final String torqueKpdRgex = "M_KPD:\\s*";
		final String powerRegex = "N:\\s*";
		final String toothRgex = "Z:\\s*";
		final String traceRegex = "((" + elemRegex + ")*:(\\s*\\d*,\\d*)*;\\s*)+";
		final String gearSetsTypesRegex = "(\\s*[D|U|P|(U_R)|(P_R)]\\s*)+";
		final String numericValuesRegex = "([-+]*\\d+\\.*\\d*(e-)*\\d*\\s*)+";
		final String powerValuesRegex = "([+-0]\\s*)+";
		final String headerRegex = "(\\s*" + elemRegex + "[0-9]*\\s+)+";

		Integer gear = 0;
		String header = "";
		eType type = null;
		
		 try {
	            String strLine;
	            while ((strLine = br.readLine()) != null) {
	            	
	            	System.out.print(strLine);
	            	if(strLine.matches(codeRegex))
	            	{
	            		this.code.set(strLine);
	            		System.out.println(" - code");
	            	}
	            	else if(strLine.matches(headerRegex))
	            	{
	            		header = strLine;
	            		System.out.println(" - header");
	            	}
	            	else if(strLine.matches(chainRegex))
	            	{
	            		System.out.println(" - chain");
	            	}
	            	else if(strLine.matches(traceRegex))
	            	{
	            		System.out.println(" - trace");
	            	}
	            	else if(strLine.matches(gearSetsTypesRegex))
	            	{
	            		System.out.println(" - gear sets types");
	            	}
	            	else if(strLine.matches(numericValuesRegex) || strLine.matches(powerValuesRegex))
	            	{
	            		if (type != null)
	            			data.add(header, strLine, ++gear, type);
	            		System.out.println(" - data values");
	            	}
	            	else if(strLine.matches(velocityRgex))
	            	{
	            		gear = 0;
	            		type = eType.ANG_VELOCITY;
	            		System.out.println(" - velocity");
	            	}
	            	else if(strLine.matches(torqueRgex))
	            	{
	            		gear = 0;
	            		type = eType.TORQUE;
	            		System.out.println(" - torque");
	            	}
	            	else if(strLine.matches(torqueKpdRgex))
	            	{
	            		gear = 0;
	            		type = eType.TORQUE_KPD;
	            		System.out.println(" - torqueKpd");
	            	}
	            	else if(strLine.matches(powerRegex))
	            	{
	            		gear = 0;
	            		type = eType.POWER;
	            		System.out.println(" - power");
	            	}
	            	else if(strLine.matches(toothRgex))
	            	{
	            		type = null;
	            		System.out.println(" - tooth");
	            	}
	            	else if (strLine.matches("end\\s*"))
	            	{
	            		System.out.println("+++++++++++++++++++++++++++++END+++++++++++++++++++++++++++");
	            		return true;
	            	}
	            }
	        } catch (Exception e) {
	            System.err.println("Error: " + e.getMessage());
	        }
		 return false;
	}

	public StringProperty codeProperty()
	{
		return code;
	}
	
	public Set<String> getColumnHeaders(eType type)
	{
		return data.getColumnHeaders(type);
	}
	
    public ObservableList<Map> generateDataInMap(eType type) {
        return data.getValue(type);
    }
	/*
	public ObjectProperty<Chains> chainsProperty()
	{
		return chains;
	}
	*/
}

	
	
	