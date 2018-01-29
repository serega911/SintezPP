package address.model;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map.Entry;

import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.LineTo;
import javafx.scene.shape.MoveTo;
import javafx.scene.shape.Path;

public class SchemeDraw {

	HashMap<String, Path> pathes = new HashMap<String, Path>();;
	Pane pane = null;
	DrawData dData = null;

	public SchemeDraw(Pane pane, DrawData drawData) {
		this.pane = pane;
		this.dData = drawData;

		for (Entry<String, LinkedList<Cord>> entry : drawData.getCords().entrySet()) {
			final String key = entry.getKey();
			Path path = new Path();

			for (Cord temp : entry.getValue()) {
				if (temp.isStarted() == true) {
					path.getElements().add(new MoveTo(temp.getX(), temp.getY()));
				} else {
					path.getElements().add(new LineTo(temp.getX(), temp.getY()));
				}
			}

			pathes.put(key, path);
		}
	}

	public void draw() {
		pane.getChildren().clear();

		drawGearSets();

		int i = 0;
		Color[] colors = { Color.BLUE, Color.RED, Color.DARKGREEN, Color.DARKVIOLET, Color.DARKBLUE };

		for (Entry<String, Path> entry : pathes.entrySet()) {
			entry.getValue().setStroke(colors[i++ % 5]);
			pane.getChildren().add(entry.getValue());
		}
	}

	private void drawGearSets() {
		LinkedList<eGearSetType> types = dData.getSetsTypes();

		Path path = new Path();
		final Cord stepX = new Cord(4, 0);
		final Cord stepGearSet = new Cord(1, 0);
		Cord center = new Cord(0, 6);

		for (eGearSetType type : types) {
			center.addToMe(stepX);

			Cord left = new Cord(-1, 0);
			Cord right = new Cord(+1, 0);

			switch (type) {
			case TUPE_DEFAULT: {
				final Cord top = new Cord(0, +2);
				final Cord bot = new Cord(0, -2);
				path.getElements().add(new MoveTo(center.getX(), center.add(bot).getY()));
				path.getElements().add(new LineTo(center.getX(), center.add(top).getY()));
				break;
			}
			case TYPE_P:
			case TYPE_P_REVERSE: {
				final Cord top = new Cord(0, +2);
				final Cord bot = new Cord(0, -1);
				path.getElements().add(new MoveTo(center.add(left).getX(), center.add(top).getY()));
				path.getElements().add(new LineTo(center.add(left).getX(), center.add(bot).getY()));
				path.getElements().add(new LineTo(center.add(right).getX(), center.add(bot).getY()));
				path.getElements().add(new LineTo(center.add(right).getX(), center.add(top).getY()));
				break;
			}
			case TYPE_U:
			case TYPE_U_REVERSE: {
				final Cord top = new Cord(0, +1);
				final Cord bot = new Cord(0, -2);
				path.getElements().add(new MoveTo(center.add(left).getX(), center.add(bot).getY()));
				path.getElements().add(new LineTo(center.add(left).getX(), center.add(top).getY()));
				path.getElements().add(new LineTo(center.add(right).getX(), center.add(top).getY()));
				path.getElements().add(new LineTo(center.add(right).getX(), center.add(bot).getY()));
				break;
			}
			default:
				break;
			}

			center.addToMe(stepX.add(stepGearSet));
		}
		path.setStrokeWidth(5);
		path.setStroke(Color.BLACK);
		pane.getChildren().add(path);
	}
}
