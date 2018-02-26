package address.view;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

import address.MainApp;
import address.model.Scheme;
import address.model.SchemeDraw;
import address.model.eType;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextArea;
import javafx.scene.control.cell.MapValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.stage.DirectoryChooser;

public class MainFormController {

	private MainApp mainApp;

	@FXML
	private TableView<Scheme> schemeTable;
	@FXML
	private TableColumn<Scheme, String> nameColumn;
	@FXML
	private TableView<Map<String, String>> angVelocityTable;
	@FXML
	private TableView<Map<String, String>> powerTable;
	@FXML
	private TableView<Map<String, String>> torqueKpdTable;
	@FXML
	private TableView<Map<String, String>> torqueTable;
	@FXML
	private TableView<Map<String, String>> qcTable;
	@FXML
	private Label testLabel;
	@FXML
	private AnchorPane drawPane;
	@FXML
	private TextArea commonData;

	Map<eType, TableView<Map<String, String>>> tables = new HashMap<eType, TableView<Map<String, String>>>();

	@FXML
	private void initialize() {

		tables.put(eType.ANG_VELOCITY, angVelocityTable);
		tables.put(eType.POWER, powerTable);
		tables.put(eType.TORQUE, torqueTable);
		tables.put(eType.TORQUE_KPD, torqueKpdTable);
		tables.put(eType.QC, qcTable);

		nameColumn.setCellValueFactory(cellData -> cellData.getValue().codeProperty());

		// Слушаем изменения выбора, и при изменении отображаем
		schemeTable.getSelectionModel().selectedItemProperty()
				.addListener((observable, oldValue, newValue) -> showSchemeDetails(newValue));
	}

	@FXML
	private void LoadSchemes() throws FileNotFoundException {
		load("data_tmp");
	}
	
	private void load(final String pathToDir) throws FileNotFoundException
	{
		boolean isLoaded = false;
		// Load schemes from file
		FileInputStream file = new FileInputStream(pathToDir + "/result.pkp");
		DataInputStream in = new DataInputStream(file);
		BufferedReader br = new BufferedReader(new InputStreamReader(in));
		do {
			Scheme scheme = new Scheme();

			try {
				isLoaded = scheme.loadFromFile(br);
			} catch (Exception e) {
				System.err.println("Error: " + e.getMessage());
				e.printStackTrace();
			}

			if (isLoaded == true)
				mainApp.getSchemes().add(scheme);
		} while (isLoaded);
	}

	@FXML
	private void addColumnTest() throws InterruptedException, IOException {
/*
		Runtime runtime = Runtime.getRuntime(); 

		try
		{
			Process proc = runtime.exec("../Release/SintezPPGenerate.exe w=2 n=3 d=4");
			proc.waitFor();   
			proc = runtime.exec("../Release/SintezPPDefK.exe w=2 n=3 d=4 rb=-8 re=-2 rb=2 re=8 i=1 i=2 i=3 i=4");
			proc.waitFor();  
			proc = runtime.exec("../Release/SintezPPSchemeBuild.exe w=2 n=3 d=4 rb=-8 re=-2 rb=2 re=8 i=1 i=2 i=3 i=4");
			proc.waitFor();
			proc = runtime.exec("../Release/SintezPPKinCharacteristics.exe w=2 n=3 d=4 rb=-8 re=-2 rb=2 re=8 i=1 i=2 i=3 i=4");
			proc.waitFor();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
*/
	}

	@FXML
	private void openFolder() throws FileNotFoundException {
		DirectoryChooser dc = new DirectoryChooser();
		File dir = dc.showDialog(null);
		
		final String path = dir == null ? null : dir.getAbsolutePath();
		
		if (path != null)
			load(path);

	}
	
	private void showSchemeDetails(Scheme scheme) {
		// https://docs.oracle.com/javafx/2/ui_controls/table-view.htm
		for (Entry<eType, TableView<Map<String, String>>> entry : tables.entrySet()) {
			Set<String> headers = scheme.getData().getColumnHeaders(entry.getKey());
			entry.getValue().getColumns().clear();
			for (String header : headers) {
				TableColumn<Map<String, String>, String> column = new TableColumn<>();
				column.setText(header);
				column.setCellValueFactory(new MapValueFactory(header));
				entry.getValue().getColumns().add(column);
			}
			entry.getValue().setItems(scheme.getData().getValue(entry.getKey()));
		}

		SchemeDraw draw = new SchemeDraw(drawPane, scheme.getDrawData());
		draw.draw();
		
		commonData.setText("K:\n" + scheme.getData().getInternalRatios() + "\n"
				+ "Chains:\n" + scheme.getData().getChains());
		
	}

	public void setMainApp(MainApp mainApp) {
		this.mainApp = mainApp;
		schemeTable.setItems(mainApp.getSchemes());
	}
}
