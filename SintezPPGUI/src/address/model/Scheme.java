package address.model;

import javafx.beans.property.ObjectProperty;
import javafx.beans.property.SimpleObjectProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class Scheme {

	//private ObjectProperty<Chains> chains = new SimpleObjectProperty<Chains>();
	private StringProperty         code = new SimpleStringProperty();
	
	public Scheme(final String code)
	{
		this.code.set(code);
	}
	
	public StringProperty codeProperty()
	{
		return code;
	}
}

	
	
	