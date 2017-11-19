package address.view;

import address.MainApp;
import address.model.Scheme;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
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
    private void buttonTest()
    {
    	
    	mainApp.getSchemes().add(new Scheme("added scheme"));
    	
    	TableColumn<Scheme, String> column = new TableColumn<Scheme, String>();
    	//column.setText("1245");
    	angVelocityTable.getColumns().add(column);
    }
    
    private void showSchemeDetails(Scheme scheme)
    {
    	testLabel.setText(scheme.codeProperty().get() + " selected");
    }
    
    public void setMainApp(MainApp mainApp) {
        this.mainApp = mainApp;
        schemeTable.setItems(mainApp.getSchemes());
    }
}
