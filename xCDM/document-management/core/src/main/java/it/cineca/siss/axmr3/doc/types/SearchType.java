package it.cineca.siss.axmr3.doc.types;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 05/12/13
 * Time: 19.56
 * To change this template use File | Settings | File Templates.
 */
public enum SearchType {
    EQ(1), LIKE(2), STARTSWITH(3),ENDSWITH(4),GT(5),GTEQ(6),LT(7),LTEQ(8), ISNULL(9), ISNOTNULL(10), IN(11), NE(12);
    private int value;

    private SearchType(int value){
        this.value=value;
    }


    public static SearchType valueOfIgnoreCase(String name) {
        Class<SearchType> enumeration=SearchType.class;
        for(SearchType enumValue : enumeration.getEnumConstants()) {
            if(enumValue.name().equalsIgnoreCase(name)) {
                return enumValue;
            }
        }
        throw new IllegalArgumentException("There is no value with name '" + name + " in Enum " + enumeration.getClass().getName());
    }
    
}
