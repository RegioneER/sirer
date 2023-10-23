package it.cineca.siss.axmr3.doc.controls.json;

import java.io.Serializable;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by Carlo on 12/09/2016.
 */
public class Condition implements Serializable {

    protected String leftHandField;
    protected String check;
    protected List<String> rightHandFields;
    protected List<Object> rightHandValues;

    public Condition() {}

    public Condition(String leftHandField, String check, List<String> rightHandFields, List<Object> rightHandValues) {
        this.leftHandField = leftHandField;
        this.check = check;
        this.rightHandFields = rightHandFields;
        this.rightHandValues = rightHandValues;
    }

    public void addRightHandField(String rightHandField){
        if (rightHandFields==null) rightHandFields=new LinkedList<String>();
        rightHandFields.add(rightHandField);
    }

    public void addRightHandValue(Object value){
        if (rightHandValues==null) rightHandValues=new LinkedList<Object>();
        rightHandValues.add(value);
    }

    public String getLeftHandField() {
        return leftHandField;
    }

    public void setLeftHandField(String leftHandField) {
        this.leftHandField = leftHandField;
    }

    public String getCheck() {
        return check;
    }

    public void setCheck(String check) {
        this.check = check;
    }

    public List<String> getRightHandFields() {
        return rightHandFields;
    }

    public void setRightHandFields(List<String> rightHandFields) {
        this.rightHandFields = rightHandFields;
    }

    public List<Object> getRightHandValues() {
        return rightHandValues;
    }

    public void setRightHandValues(List<Object> rightHandValues) {
        this.rightHandValues = rightHandValues;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Condition condition = (Condition) o;

        if (leftHandField != null ? !leftHandField.equals(condition.leftHandField) : condition.leftHandField != null)
            return false;
        if (check != condition.check) return false;
        if (rightHandFields != null ? !rightHandFields.equals(condition.rightHandFields) : condition.rightHandFields != null)
            return false;
        return rightHandValues != null ? rightHandValues.equals(condition.rightHandValues) : condition.rightHandValues == null;

    }

    @Override
    public int hashCode() {
        int result = leftHandField != null ? leftHandField.hashCode() : 0;
        result = 31 * result + (check != null ? check.hashCode() : 0);
        result = 31 * result + (rightHandFields != null ? rightHandFields.hashCode() : 0);
        result = 31 * result + (rightHandValues != null ? rightHandValues.hashCode() : 0);
        return result;
    }

    public List<String> getImpactedFields(){
        List<String> ifs=new LinkedList<String>();
        ifs.add(getLeftHandField());
        if (rightHandFields!=null && rightHandFields.size()>0){
            for (String f:rightHandFields){
                if (!ifs.contains(f)) ifs.add(f);
            }
        }
        return ifs;
    }

    public String toJs(){
        String js="";
        if (check.equals("isNumeric") || check.equals("isFloat") || check.equals("isInt") || check.equals("isString")){
            js += check+"Check(that, '" + leftHandField + "')";
        }
        if (check.equals("gt") || check.equals("ge") || check.equals("ne") || check.equals("lt") || check.equals("le")){
            if (rightHandFields!=null && rightHandFields.size()>0){
                for(String rf:getRightHandFields()) {
                    if (!js.isEmpty()) js += " && ";
                    js += check+"Check(that, '" + leftHandField + "', '"+rf+"')";
                }
            }
            if (rightHandValues!=null && rightHandValues.size()>0){
                for(Object lv:getRightHandValues()) {
                    if (!js.isEmpty()) js += " && ";
                    if (lv instanceof Double || lv instanceof Float || lv instanceof Integer){
                        js += check+"Check(that, '" + leftHandField + "', "+lv+")";
                    } else {
                        js += check+"Check(that, '" + leftHandField + "', '"+lv+"')";
                    }
                }
            }
        }
        if (check.equals("eq")){
            if (rightHandFields!=null && rightHandFields.size()>0){
                for(String rf:getRightHandFields()) {
                    if (!js.isEmpty()) js += " || ";
                    js += check+"Check('" + leftHandField + "', '"+rf+"')";
                }
            }
            if (rightHandValues!=null && rightHandValues.size()>0){
                for(Object lv:getRightHandValues()) {
                    if (!js.isEmpty()) js += " || ";
                    if (lv instanceof Double || lv instanceof Float || lv instanceof Integer){
                        js += check+"Check(that, '" + leftHandField + "', "+lv+")";
                    } else {
                        js += check+"Check(that, '" + leftHandField + "', '"+lv+"')";
                    }
                }
            }
            return js;
        }
        return js;
    }
}
