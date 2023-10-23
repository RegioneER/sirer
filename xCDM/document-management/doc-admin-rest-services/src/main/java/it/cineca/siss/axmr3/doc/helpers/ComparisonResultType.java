package it.cineca.siss.axmr3.doc.helpers;

/**
 * Created by cin0562a on 06/10/14.
 */
public enum ComparisonResultType {
    EQ(1), ADDED(2), UPDATED(3), DELETED(4);
    private int value;

    private ComparisonResultType(int value) {
        this.value = value;
    }


    public static ComparisonResultType valueOfIgnoreCase(String name) {
        Class<ComparisonResultType> enumeration = ComparisonResultType.class;
        for (ComparisonResultType enumValue : enumeration.getEnumConstants()) {
            if (enumValue.name().equalsIgnoreCase(name)) {
                return enumValue;
            }
        }
        throw new IllegalArgumentException("There is no value with name '" + name + " in Enum " + enumeration.getClass().getName());
    }
}
