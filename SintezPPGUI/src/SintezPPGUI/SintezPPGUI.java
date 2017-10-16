package SintezPPGUI;

import javafx.application.*;
import javafx.scene.*;
import javafx.stage.*;
import javafx.scene.layout.*;
import javafx.scene.control.*;
import javafx.event.*;
import javafx.geometry.*;

public class SintezPPGUI extends Application {

	TextField tf;
	Label response;

	public static void main(String[] args) {
	// ��������� ���������� JavaFX, ������ ����� launch()
	launch(args);
	// �������������� ����� start()
	}
	
	public void start(Stage myStage) {
	// ������ ��������� ���� ����������
	myStage.setTitle("Demonstrate � TextField");
	// ������������ FlowPane ��� ��������� ����. � ������
	// ������ �������� ������������� � ��������������� �������
	// ���������� 10.
	FlowPane rootNode = new FlowPane(10, 10);
	// ������������ �������� ���������� �� �����
	rootNode.setAlignment(Pos.CENTER);
	// ������� �����
	Scene myScene = new Scene(rootNode, 230, 140);
	// ���������� ����� �� ���������
	myStage.setScene(myScene);
	// ������� �����, ���������� � ��������� ���������� ������
	response = new Label("Enter Narne: ");
	// ������� ������, ����������� ���������� ������
	Button �tnGetText = new Button("Get Narne");
	// ������� ��������� ����
	tf = new TextField();
	// ������ ���������
	tf.setPromptText("Enter � name."); 
	// ������ ���������������� ���������� ��������
	tf. setPrefColumnCount ( 15) ;
	// ������������ ������-���������, �������������� ������� ��������
	// ��� ���������� ����. ������� �������� ������������ ��� �������
	// ������� <ENTER> � �� �����, ����� ����� ����� ��������� �
	// ��������� ����. � ������ ������ ��������� �������
	// ����������� � ��������� � ����������� ������.
	tf.setOnAction( (��) -> response.setText("Enter pressed. Narne is: " +
	tf. getText () ) ) ; 
	// ������������ ������-��������� ��� ��������� ������ �� �������� �n�
	// ���������� ���� ��� ������� ������
	�tnGetText.setOnAction((ae) ->
	response.setText("Button pressed. Narne is: " +
	tf. getText () ) ) ;
	// ������������ ����������� ��� ������ ����������� ������
	Separator separator = new Separator();
	separator.setPrefWidth(180);

	// �������� �������� ���������� � ���� �����
	rootNode.getChildren().addAll(tf, �tnGetText, separator, response);
	// ���������� ��������� � �� �����
	myStage.show();
	}

}
