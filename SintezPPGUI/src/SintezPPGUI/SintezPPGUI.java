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
	// Запустить приложение JavaFX, вызвав метод launch()
	launch(args);
	// Переопределить метод start()
	}
	
	public void start(Stage myStage) {
	// Задать заголовок окна приложения
	myStage.setTitle("Demonstrate а TextField");
	// Использовать FlowPane для корневого узла. В данном
	// случае значение вертикального и горизонтального зазоров
	// составляет 10.
	FlowPane rootNode = new FlowPane(10, 10);
	// Центрировать элементы управления на сцене
	rootNode.setAlignment(Pos.CENTER);
	// Создать сцену
	Scene myScene = new Scene(rootNode, 230, 140);
	// Установить сцену на платформе
	myStage.setScene(myScene);
	// Создать метку, извещающую о состоянии выбранного флажка
	response = new Label("Enter Narne: ");
	// Создать кнопку, управляющую получением текста
	Button ЬtnGetText = new Button("Get Narne");
	// Создать текстовое поле
	tf = new TextField();
	// Задать подсказку
	tf.setPromptText("Enter а name."); 
	// Задать предпочтительное количество столбцов
	tf. setPrefColumnCount ( 15) ;
	// Использовать лямбда-выражение, обрабатывающее события действий
	// для текстового поля. События действий генерируются при нажатии
	// клавиши <ENTER> в то время, когда фокус ввода находится в
	// текстовом поле. В данном случае обработка события
	// заключается в получении и отображении текста.
	tf.setOnAction( (ае) -> response.setText("Enter pressed. Narne is: " +
	tf. getText () ) ) ; 
	// Использовать лямбда-выражение для получения текста из действий дnя
	// текстового поля при нажатии кнопки
	ЬtnGetText.setOnAction((ae) ->
	response.setText("Button pressed. Narne is: " +
	tf. getText () ) ) ;
	// Использовать разделитель для лучшей организации вывода
	Separator separator = new Separator();
	separator.setPrefWidth(180);

	// Добавить элементы управления в граф сцены
	rootNode.getChildren().addAll(tf, ЬtnGetText, separator, response);
	// Отобразить платформу и ее сцену
	myStage.show();
	}

}
