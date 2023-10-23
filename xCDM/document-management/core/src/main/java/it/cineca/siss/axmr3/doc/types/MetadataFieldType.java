package it.cineca.siss.axmr3.doc.types;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 31/07/13
 * Time: 12.37
 * To change this template use File | Settings | File Templates.
 */
public enum MetadataFieldType {

    TEXTBOX(1), RICHTEXT(2), TEXTAREA(3), SELECT(4), RADIO(5), CHECKBOX(6), DATE(7), ELEMENT_LINK(8), EXT_DICTIONARY(8), PLACE_HOLDER(9);
    private int value;

    private MetadataFieldType(int value) {
        this.value = value;
    }

    public static MetadataFieldType valueOfIgnoreCase(String name) {
        Class<MetadataFieldType> enumeration = MetadataFieldType.class;
        for (MetadataFieldType enumValue : enumeration.getEnumConstants()) {
            if (enumValue.name().equalsIgnoreCase(name)) {
                return enumValue;
            }
        }
        throw new IllegalArgumentException("There is no value with name '" + name + " in Enum " + enumeration.getClass().getName());
    }
}
