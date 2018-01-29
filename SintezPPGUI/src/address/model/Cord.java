package address.model;

class Cord {
	private Integer x;
	private Integer y;
	private boolean isStarted;

	Cord(final String str) {
		this(str, false);
	}

	Cord(final String str, boolean isStarted) {
		String[] values = str.split(",");
		this.x = Integer.parseInt(values[0]);
		this.y = Integer.parseInt(values[1]);
		this.isStarted = isStarted;
	}

	public Cord(int x, int y) {
		this.x = x;
		this.y = y;
	}

	final Integer getX() {
		return x * 20 + 20;
	}

	final Integer getY() {
		return y * 20 + 20;
	}

	final boolean isStarted() {
		return isStarted;
	}

	Cord add(Cord anotherCord) {
		return new Cord(this.x + anotherCord.x, this.y + anotherCord.y);
	}

	Cord addToMe(Cord anotherCord) {
		this.x += anotherCord.x;
		this.y += anotherCord.y;

		return this;
	}
}