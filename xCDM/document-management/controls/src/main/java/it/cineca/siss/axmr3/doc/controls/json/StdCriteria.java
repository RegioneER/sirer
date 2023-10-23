package it.cineca.siss.axmr3.doc.controls.json;

import java.io.Serializable;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by Carlo on 12/09/2016.
 */
public class StdCriteria implements iCriteria, Serializable {

    protected OrConditions conditions;
    protected boolean always;
    protected HashMap<String, String> message;

    public boolean isAlways() {
        return always;
    }

    public void setAlways(boolean always) {
        this.always = always;
    }

    public OrConditions getConditions() {
        return conditions;
    }

    public void setConditions(OrConditions conditions) {
        this.conditions = conditions;
    }

    public HashMap<String, String> getMessage() {
        return message;
    }

    public String toJs() {
        return getConditions().toJs();
    }

    public void setMessage(HashMap<String, String> message) {
        this.message = message;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        StdCriteria criteria = (StdCriteria) o;

        if (conditions != null ? !conditions.equals(criteria.conditions) : criteria.conditions != null) return false;
        return message != null ? message.equals(criteria.message) : criteria.message == null;

    }

    @Override
    public int hashCode() {
        int result = conditions != null ? conditions.hashCode() : 0;
        result = 31 * result + (message != null ? message.hashCode() : 0);
        return result;
    }

    public List<String> getImpactedFields(){
        return getConditions().getImpactedFields();
    }

    public String getLocalizedMessage(String criteriaType, String lang){
        lang=lang.toLowerCase();
        if (message==null || message.size()==0 || !message.containsKey(lang)) {
            if (criteriaType.equals("mandatory")) {
                if (lang.equals("it")) {
                    return "Attenzione, il campo ... deve essere compilato";
                }else {
                    return "Attention, please fill in the field ...";
                }
            }
            if (criteriaType.equals("validity")) {
                if (lang.equals("it")) {
                    return "Attenzione, il campo ... non è corretto";
                }else {
                    return "Attention, the field ... is not valid";
                }
            }
            if (criteriaType.equals("confirm")) {
                if (lang.equals("it")) {
                    return "Sei sicuro del valore del campo ... ?";
                }else {
                    return "Are you sure of the valu of field ... ?";
                }
            }
            if (criteriaType.equals("warning")) {
                if (lang.equals("it")) {
                    return "Avviso su campo ...";
                }else {
                    return "Warning on field ...";
                }
            }
            return null;
        }else {
            return message.get(lang);
        }
    }

    public String toJs(String criteriaType, String fieldId, String lang){
        if (this.conditions==null && !criteriaType.equals("mandatory")) return "";
        String jsCheck="";
        if (criteriaType.equals("mandatory")){
            jsCheck+="\n\t\t\tif (getValueCode(that,'"+fieldId+"')=='' || getValueCode(that,'"+fieldId+"')==undefined  || getValueCode(that,'"+fieldId+"')==null){";
                jsCheck += "\n\t\t\t\tshowMessage(that,'"+getLocalizedMessage(criteriaType, lang)+"');";
            jsCheck += "\n\t\t\t\tfocusOn(that,'" + fieldId + "');\n\t\t\treturn false;";
            jsCheck+="\n\t\t\t}";
        }

        if (criteriaType.equals("warning")){
            jsCheck+= "\n\talert('"+getLocalizedMessage(criteriaType, lang)+"');";
        }

        if (criteriaType.equals("confirm")){
            jsCheck+= "\n\tif (!confirm('"+getLocalizedMessage(criteriaType, lang)+"')){" +
                    "\n\tfocusOn(this,'" + fieldId + "');\nreturn false;" +
                    "\n\t}";
        }

        if (criteriaType.equals("disable")){
            jsCheck+= "\n\tdisableField(this,'"+fieldId+"');";
        }

        if (criteriaType.equals("validity")){
                jsCheck += "\n\t\t\tshowMessage(that,'"+getLocalizedMessage(criteriaType, lang)+"');";

        }

        String js="\n\t/*Controllo "+criteriaType+"*/";
        if (!criteriaType.equals("validity") && !this.isAlways()) {
            js += "\n\t\tif " + getConditions().toJs() + " {";
        }
        if (criteriaType.equals("validity")){
           js += "\n\t\tif (!" + getConditions().toJs() + ") {";
        }
        js+=jsCheck;
        if (!this.isAlways()) js+="\n\t\t}";
        js=js.replaceAll("\\.\\.\\.", "'+getLabelOfField(that,'"+fieldId+"')+'");
        js=js.replaceAll("\\[", "'+getLabelOfField(that,'");
        js=js.replaceAll("\\]", "')+'");
        return js;
    }

}