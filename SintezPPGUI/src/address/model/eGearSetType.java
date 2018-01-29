package address.model;

enum eGearSetType {
	TUPE_DEFAULT("D"), TYPE_U("U"), TYPE_U_REVERSE("U_R"), TYPE_P("P"), TYPE_P_REVERSE("P_R");

	private String text;

	eGearSetType(String text) {
		this.text = text;
	};

	public String getText() {
		return this.text;
	}

	public static eGearSetType fromString(String text) {
		for (eGearSetType b : eGearSetType.values()) {
			if (b.text.equalsIgnoreCase(text)) {
				return b;
			}
		}
		return null;
	}
}