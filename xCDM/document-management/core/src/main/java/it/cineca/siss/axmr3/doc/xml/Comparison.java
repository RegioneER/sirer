package it.cineca.siss.axmr3.doc.xml;

import it.cineca.siss.axmr3.doc.types.MetadataFieldType;

import java.util.Calendar;

public enum Comparison {

    EQ(1),
    NE(2),
    MIN_EQ(3),
    MIN(4),
    MAX_EQ(5),
    MAX(6),
    STARTSWITH(7),
    ENDSWITH(8),
    MATCH(9);
    private int value;

    private Comparison(int value) {
        this.value = value;
    }

    public static Comparison valueOfIgnoreCase(String name) {
        Class<Comparison> enumeration = Comparison.class;
        for (Comparison enumValue : enumeration.getEnumConstants()) {
            if (enumValue.name().equalsIgnoreCase(name)) {
                return enumValue;
            }
        }
        throw new IllegalArgumentException("There is no value with name '" + name + " in Enum " + enumeration.getClass().getName());
    }

    public static boolean doCheck(Comparison cmp, Object rightHand, Object leftHand){
        if (leftHand instanceof Object[]){
            if (rightHand instanceof String) return doCheck(cmp, (String) rightHand, (String[]) leftHand);
            if (rightHand instanceof Integer) return doCheck(cmp, (Integer) rightHand, (Integer[]) leftHand);
            if (rightHand instanceof Float) return doCheck(cmp, (Float) rightHand, (Float[]) leftHand);
            if (rightHand instanceof Calendar) return doCheck(cmp, (Calendar) rightHand, (Calendar[]) leftHand);
        }else {
            if (rightHand instanceof String) return doCheck(cmp, (String) rightHand, (String) leftHand);
            if (rightHand instanceof Integer) return doCheck(cmp, (Integer) rightHand, (Integer) leftHand);
            if (rightHand instanceof Float) return doCheck(cmp, (Float) rightHand, (Float) leftHand);
            if (rightHand instanceof Calendar) return doCheck(cmp, (Calendar) rightHand, (Calendar) leftHand);
        }
        return false;
    }

    public static boolean doCheck(Comparison cmp, String rightHand, String leftHand){
        switch (cmp){
            case EQ:
                return leftHand.equals(rightHand);
            case MIN:
                return leftHand.compareTo(rightHand)<0;
            case MAX:
                return leftHand.compareTo(rightHand)>0;
            case MIN_EQ:
                return leftHand.compareTo(rightHand)<=0;
            case MAX_EQ:
                return leftHand.compareTo(rightHand)>=0;
            case ENDSWITH:
                return leftHand.endsWith(rightHand);
            case STARTSWITH:
                return leftHand.startsWith(rightHand);
            case MATCH:
                return leftHand.matches(rightHand);
        }
        return true;
    }

    public static boolean doCheck(Comparison cmp, String rightHand, String[] leftHand){
        for (int i=0;i<leftHand.length;i++){
            if (!doCheck(cmp, rightHand, leftHand[i])) return false;
        }
        return true;
    }

    public static boolean doCheck(Comparison cmp, Integer rightHand, Integer leftHand){
        switch (cmp){
            case EQ:
                return leftHand.equals(rightHand);
            case MIN:
                return leftHand<rightHand;
            case MAX:
                return leftHand>rightHand;
            case MIN_EQ:
                return leftHand<=rightHand;
            case MAX_EQ:
                return leftHand>=rightHand;
            case ENDSWITH:
                return false;
            case STARTSWITH:
                return false;
            case MATCH:
                return false;
        }
        return false;
    }

    public static boolean doCheck(Comparison cmp, Integer rightHand, Integer[] leftHand){
        for (int i=0;i<leftHand.length;i++){
            if (!doCheck(cmp, rightHand, leftHand[i])) return false;
        }
        return true;
    }


    public static boolean doCheck(Comparison cmp, Float rightHand, Float leftHand){
        switch (cmp){
            case EQ:
                return leftHand.equals(rightHand);
            case MIN:
                return leftHand<rightHand;
            case MAX:
                return leftHand>rightHand;
            case MIN_EQ:
                return leftHand<=rightHand;
            case MAX_EQ:
                return leftHand>=rightHand;
            case ENDSWITH:
                return false;
            case STARTSWITH:
                return false;
            case MATCH:
                return false;
        }
        return false;
    }

    public static boolean doCheck(Comparison cmp, Float rightHand, Float[] leftHand){
        for (int i=0;i<leftHand.length;i++){
            if (!doCheck(cmp, rightHand, leftHand[i])) return false;
        }
        return true;
    }


    public static boolean doCheck(Comparison cmp, Calendar rightHand, Calendar leftHand){
        switch (cmp){
            case EQ:
                return leftHand.equals(rightHand);
            case MIN:
                return leftHand.before(rightHand);
            case MAX:
                return leftHand.after(rightHand);
            case MIN_EQ:
                return leftHand.before(rightHand) || leftHand.equals(rightHand);
            case MAX_EQ:
                return leftHand.after(rightHand) || leftHand.equals(rightHand);
            case ENDSWITH:
                return false;
            case STARTSWITH:
                return false;
            case MATCH:
                return false;
        }
        return false;
    }

    public static boolean doCheck(Comparison cmp, Calendar rightHand, Calendar[] leftHand){
        for (int i=0;i<leftHand.length;i++){
            if (!doCheck(cmp, rightHand, leftHand[i])) return false;
        }
        return true;
    }


}
