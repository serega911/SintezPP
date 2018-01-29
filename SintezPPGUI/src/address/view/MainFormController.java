package address.view;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
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
import javafx.scene.control.cell.MapValueFactory;
import javafx.scene.layout.AnchorPane;

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
	private Label testLabel;
	@FXML
	private AnchorPane drawPane;

	Map<eType, TableView<Map<String, String>>> tables = new HashMap<eType, TableView<Map<String, String>>>();

	@FXML
	private void initialize() {

		tables.put(eType.ANG_VELOCITY, angVelocityTable);
		tables.put(eType.POWER, powerTable);
		tables.put(eType.TORQUE, torqueTable);
		tables.put(eType.TORQUE_KPD, torqueKpdTable);

		nameColumn.setCellValueFactory(cellData -> cellData.getValue().codeProperty());

		// Слушаем изменения выбора, и при изменении отображаем
		schemeTable.getSelectionModel().selectedItemProperty()
				.addListener((observable, oldValue, newValue) -> showSchemeDetails(newValue));
	}

	@FXML
	private void LoadSchemes() throws FileNotFoundException {
		boolean isLoaded = false;
		// Load schemes from file
		FileInputStream file = new FileInputStream("data_tmp/result.pkp");
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
	private void addColumnTest() throws FileNotFoundException {
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
	}

	public void setMainApp(MainApp mainApp) {
		this.mainApp = mainApp;
		schemeTable.setItems(mainApp.getSchemes());
	}
}
