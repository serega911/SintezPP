package address.view;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStreamReader;
import java.util.Set;

import address.MainApp;
import address.model.Scheme;
import address.model.eType;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableRow;
import javafx.scene.control.TableView;


public class MainFormController {

	private MainApp mainApp;
	 
	@FXML
    private TableView<Scheme> schemeTable;
    @FXML
    private TableColumn<Scheme, String> nameColumn;
    @FXML
    private TableView<Scheme> angVelocityTable;
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
    	TableColumn<Scheme, String> column = new TableColumn<Scheme, String>();
    	column.setText("1245");
    	angVelocityTable.getColumns().add(column);
   
    }
    
    private void showSchemeDetails(Scheme scheme)
    {
    	testLabel.setText(scheme.codeProperty().get() + " selected");
    	
    	//TableRow<Integer> row = new TableRow<Integer>();
    	//angVelocityTable.getRowFactory().
    	
    	Set<String> headers = scheme.getColumnHeaders(eType.TORQUE);
    	
    	angVelocityTable.getColumns().clear();
    	for (String header: headers)
    	{
    		TableColumn<Scheme, String> column = new TableColumn<Scheme, String>();
    		column.setText(header);
    		//column.setCellValueFactory(cellData -> cellData.getValue().getValue(eType.TORQUE, 1, header));
    		
    		angVelocityTable.getColumns().add(column);
    	}
    }
    
    public void setMainApp(MainApp mainApp) {
        this.mainApp = mainApp;
        schemeTable.setItems(mainApp.getSchemes());
    }
}
