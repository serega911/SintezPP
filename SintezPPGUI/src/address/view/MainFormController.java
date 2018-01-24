package address.view;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.Map.Entry;

import address.MainApp;
import address.model.Scheme;
import address.model.eType;
import address.model.SchemeData.Data;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.MapValueFactory;


public class MainFormController {

	private MainApp mainApp;
	 
	@FXML
    private TableView<Scheme> schemeTable;
    @FXML
    private TableColumn<Scheme, String> nameColumn;
    @FXML
    private TableView<Map> angVelocityTable;
    @FXML
    private TableView<Map> powerTable;
    @FXML
    private TableView<Map> torqueKpdTable;
    @FXML
    private TableView<Map> torqueTable;
    @FXML   
    private Label testLabel;
    
    @FXML
    private void initialize() {
    	nameColumn.setCellValueFactory(cellData -> cellData.getValue().codeProperty());
    	
    	// —лушаем изменени€ выбора, и при изменении отображаем
        // дополнительную информацию об адресате.
    	schemeTable.getSelectionModel().selectedItemProperty().addListener(
                (observable, oldValue, newValue) -> showSchemeDetails(newValue));
    }

    @FXML
    private void LoadSchemes() throws FileNotFoundException
    {
    	boolean isLoaded = false;
    	//Load schemes from file
    	FileInputStream file = new FileInputStream("data_tmp/result.pkp");
    	DataInputStream in = new DataInputStream(file);
        BufferedReader br = new BufferedReader(new InputStreamReader(in));
    	do {
    		Scheme scheme = new Scheme();
    		isLoaded = scheme.loadFromFile(br);
    		if (isLoaded == true)
    			mainApp.getSchemes().add(scheme);
    	} while (isLoaded);   
    }
    
    @FXML
    private void addColumnTest() throws FileNotFoundException
    {
    	//TableColumn<TreeMap<String, Double>, String> column = new TableColumn<TreeMap<String, Double>, String>();
    	//column.setText("1245");
    	//angVelocityTable.getColumns().add(column);
   
    }
    


    
    private void showSchemeDetails(Scheme scheme)
    {
    	//https://docs.oracle.com/javafx/2/ui_controls/table-view.htm
    	Map<eType, TableView<Map>> tables = new HashMap<eType, TableView<Map>>();
    	tables.put(eType.ANG_VELOCITY, angVelocityTable);
    	tables.put(eType.POWER, powerTable);
    	tables.put(eType.TORQUE, torqueTable);
    	tables.put(eType.TORQUE_KPD, torqueKpdTable);

    	for (Entry<eType, TableView<Map>> entry : tables.entrySet())
    	{
	    	Set<String> headers = scheme.getColumnHeaders(entry.getKey());
	    	entry.getValue().getColumns().clear();
	    	for (String header: headers)
	    	{
	    		TableColumn<Map, String> column = new TableColumn<>();
	    		column.setText(header);	
	    		column.setCellValueFactory(new MapValueFactory(header));
	    		entry.getValue().getColumns().add(column);
	    	}
	    	entry.getValue().setItems(scheme.generateDataInMap(entry.getKey()));
	    }
    	
    }
    
    public void setMainApp(MainApp mainApp) {
        this.mainApp = mainApp;
        schemeTable.setItems(mainApp.getSchemes());
    }
}
