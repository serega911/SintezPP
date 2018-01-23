package address.model;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.InputStreamReader;

import javafx.beans.property.ObjectProperty;
import javafx.beans.property.SimpleObjectProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class Scheme {

	//private ObjectProperty<Chains> chains = new SimpleObjectProperty<Chains>();
	private StringProperty         code = new SimpleStringProperty();
	private SchemeData             data = new SchemeData();

	public Scheme(final String code)
	{
		this.code.set(code);
		
	}

	public boolean loadFromFile(FileInputStream fstream)
	{
		final String elemRegex = "([a-zA-Z][0-9])";
		final String linkRegex = elemRegex + elemRegex;
		final String frictionRegex = elemRegex + elemRegex + "F[0-9]";
		final String codeRegex = "(("+ linkRegex + "|" + frictionRegex + ")\\s*)+";
		final String chainRegex = "(" + elemRegex + "+\\s*)+";
		final String velocityRgex = "w:\\s*";
		final String torqueRgex = "M:\\s*";
		final String torqueKpdRgex = "M_KPD:\\s*";
		final String powerRegex = "N:\\s*";
		final String toothRgex = "Z:\\s*";
		final String traceRegex = "((" + elemRegex + ")*:(\\s*\\d*,\\d*)*;\\s*)+";
		final String gearSetsTypesRegex = "(\\s*[D|U|P|(U_R)|(P_R)]\\s*)+";
		final String numericValuesRegex = "([-+]*\\d+\\.*\\d*\\s*)+";
		final String powerValuesRegex = "([+-0]\\s*)+";
		final String headerRegex = "(\\s*" + elemRegex + "[0-9]*\\s+)+";
		
		
		 try {
	            DataInputStream in = new DataInputStream(fstream);
	            BufferedReader br = new BufferedReader(new InputStreamReader(in));
	            String strLine;
	            while ((strLine = br.readLine()) != null) {
	            	
	            	System.out.print(strLine);
	            	if(strLine.matches(codeRegex))
	            	{
	            		System.out.println(" - code");
	            	}
	            	else if(strLine.matches(headerRegex))
	            	{
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
	            	else if(strLine.matches(numericValuesRegex))
	            	{
	            		System.out.println(" - numeric values");
	            	}
	            	else if(strLine.matches(powerValuesRegex))
	            	{
	            		System.out.println(" - power values");
	            	}
	            	else if(strLine.matches(velocityRgex))
	            	{
	            		System.out.println(" - velocity");
	            	}
	            	else if(strLine.matches(torqueRgex))
	            	{
	            		System.out.println(" - torque");
	            	}
	            	else if(strLine.matches(torqueKpdRgex))
	            	{
	            		System.out.println(" - torqueKpd");
	            	}
	            	else if(strLine.matches(powerRegex))
	            	{
	            		System.out.println(" - power");
	            	}
	            	else if(strLine.matches(toothRgex))
	            	{
	            		System.out.println(" - tooth");
	            	}
	            	
	            	/*if (Pattern.matches(input, strLine)) {
	                    Pattern p = Pattern.compile("'(.*?)'");
	                    Matcher m = p.matcher(strLine);
	                    while (m.find()) {
	                        String b = m.group(1);
	                        String c = b.toString() + ".*";
	                        System.out.println(b);

	                        if (Pattern.matches(c, strLine)) {
	                            Pattern pat = Pattern.compile("<(.*?)>");
	                            Matcher mat = pat.matcher(strLine);
	                            while (mat.find()) {
	                                System.out.println(m.group(1));

	                            }
	                        } else {
	                            System.out.println("Not found");
	                        }
	                    }
	                }*/
	            }
	        } catch (Exception e) {
	            System.err.println("Error: " + e.getMessage());
	        }
		 return true;/*TODO*/
	}

	public StringProperty codeProperty()
	{
		return code;
	}
	/*
	public ObjectProperty<Chains> chainsProperty()
	{
		return chains;
	}
	*/
}

	
	
	