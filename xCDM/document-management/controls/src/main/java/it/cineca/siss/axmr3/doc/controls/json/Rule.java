package it.cineca.siss.axmr3.doc.controls.json;

import java.io.Serializable;
import java.util.LinkedList;
import java.util.List;
import java.util.Objects;

/**
 * Created by Carlo on 12/09/2016.
 */
public class Rule implements Serializable {

    protected String rule;
    protected List<String> fields;
    protected List<String> buttons;
    protected CriteriaContainer criteria;

    public Rule() {
        this.fields=new LinkedList<String>();
        this.buttons=new LinkedList<String>();
    }

    public String getRule() {
        return rule;
    }

    public void setRule(String rule) {
        this.rule = rule;
    }

    public List<String> getFields() {
        return fields;
    }

    public void setFields(List<String> fields) {
        this.fields = fields;
    }

    public List<String> getButtons() {
        return buttons;
    }

    public void setButtons(List<String> buttons) {
        this.buttons = buttons;
    }

    public CriteriaContainer getCriteria() {
        return criteria;
    }

    public void setCriteria(CriteriaContainer criteria) {
        this.criteria = criteria;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Rule rule1 = (Rule) o;
        return Objects.equals(rule, rule1.rule) &&
                Objects.equals(fields, rule1.fields) &&
                Objects.equals(buttons, rule1.buttons) &&
                Objects.equals(criteria, rule1.criteria);
    }

    @Override
    public int hashCode() {
        int result = rule != null ? rule.hashCode() : 0;
        result = 31 * result + (fields != null ? fields.hashCode() : 0);
        result = 31 * result + (buttons != null ? buttons.hashCode() : 0);
        result = 31 * result + (criteria != null ? criteria.hashCode() : 0);
        return result;
    }

    public String toJs(String lang){
        String js="";
        for (String field:fields){
            js+="\n\t/*Inizio controlli per campo "+field+"*/\n";

            if (criteria.confirm!=null) {
                if (criteria.confirm.getConditions()!=null)
                    js+="\n\tthis.confirmControls['"+rule+"']['"+field+"']=function(){"+criteria.confirm.toJs("confirm", field, "it")+"\n\treturn true;\n};";
            }
            if (criteria.warning!=null) {
                if (criteria.warning.getConditions()!=null)
                    js+="\n\tthis.warningControls['"+rule+"']['"+field+"']=function(){"+criteria.warning.toJs("warning", field, "it")+"\n\treturn true;\n};";
            }
            if (criteria.empty!=null) {
                if (criteria.empty.getConditions()!=null)
                    js+="\n\tthis.emptyControls['"+rule+"']['"+field+"']=function(){"+criteria.empty.toJs("empty", field, "it")+"\n\treturn true;\n};";
            }
            if (criteria.mandatory!=null) {
                if (criteria.mandatory.getConditions()!=null) {
                    js += "\n\tthis.mandatoryControls['" + rule + "']['" + field + "']=function(){" + criteria.mandatory.toJs("mandatory", field, "it") + "\n\treturn true;\n};";
                }
                if (criteria.mandatory.isAlways()){
                    js+="\n\tthis.mandatoryControls['"+rule+"']['"+field+"']=function(){"+criteria.mandatory.toJs("mandatory", field, "it")+"\n\treturn true;\n};";
                }
            }
            if (criteria.validity!=null) {
                if (criteria.validity.getConditions()!=null)
                    js+="\n\tthis.validityControls['"+rule+"']['"+field+"']=function(){"+criteria.validity.toJs("validity", field, "it")+"\n\treturn true;\n};";
            }
            if (criteria.disable!=null) {
                if (criteria.disable.getConditions()!=null)
                    js+="\n\tthis.disableControls['"+rule+"']['"+field+"']=function(){"+criteria.disable.toJs("disable", field, "it")+"\n\treturn true;\n};";
            }
            js+="\n\t/*Fine controlli per campo "+field+"*/\n";
        }
        return js;
    }

    public List<String> getEmptyImpactedFields(){
        if (criteria.empty.getConditions()!=null) return criteria.empty.getImpactedFields();
        else return null;
    }

    public List<String> getConfirmImpactedFields(){
        if (criteria.confirm.getConditions()!=null) return criteria.confirm.getImpactedFields();
        else return null;
    }

    public List<String> getWarningImpactedFields(){
        if (criteria.warning.getConditions()!=null) return criteria.warning.getImpactedFields();
        else return null;
    }

    public List<String> getValidityImpactedFields(){
        if (criteria.validity.getConditions()!=null) return criteria.empty.getImpactedFields();
        else return null;
    }

    public List<String> getDisableImpactedFields(){
        if (criteria.disable.getConditions()!=null) return criteria.disable.getImpactedFields();
        else return null;
    }

    public List<String> getMandatoryImpactedFields(){
        if (criteria.mandatory.getConditions()!=null) return criteria.mandatory.getImpactedFields();
        else return null;
    }
}
