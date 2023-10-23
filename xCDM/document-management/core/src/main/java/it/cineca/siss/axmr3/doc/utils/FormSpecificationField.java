package it.cineca.siss.axmr3.doc.utils;

import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.doc.entities.Element;
import it.cineca.siss.axmr3.doc.entities.MetadataField;
import it.cineca.siss.axmr3.doc.types.MetadataFieldType;
import it.cineca.siss.axmr3.doc.web.services.DocumentService;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Properties;

/**
 * Created by Carlo on 15/12/2015.
 */
public class FormSpecificationField {

    public String templateName;
    public String fieldName;
    public boolean multiple;
    public boolean mandatory;
    public HashMap<String, String> possibleValues;
    public String type;
    public Long id;
    public String label;
    public String templateLabel;
    public List<Object> values;
    public String extDicLink;
    public String extDicAddFilters;
    protected String macro;


    public boolean isMandatory() {
        return mandatory;
    }

    public void setMandatory(boolean mandatory) {
        this.mandatory = mandatory;
    }

    public String getExtDicLink() {
        return extDicLink;
    }

    public void setExtDicLink(String extDicLink) {
        this.extDicLink = extDicLink;
    }

    public String getExtDicAddFilters() {
        return extDicAddFilters;
    }

    public void setExtDicAddFilters(String extDicAddFilters) {
        this.extDicAddFilters = extDicAddFilters;
    }

    public String getTemplateLabel() {
        return templateLabel;
    }

    public void setTemplateLabel(String templateLabel) {
        this.templateLabel = templateLabel;
    }

    public String getLabel() {
        return label;
    }

    public void setLabel(String label) {
        this.label = label;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public FormSpecificationField() {
        multiple=false;
        possibleValues=new HashMap<String, String>();
    }

    public List<Object> getValues() {
        if (values !=null && values.size()>0){
            String className=values.get(0).getClass().getSimpleName();
            if (className.startsWith("Element")){
                LinkedList<Object> vals=new LinkedList<Object>();
                for(Object val:values){
                    Element elVal=(Element) val;
                    FormSpecElementLinkValue fsval=new FormSpecElementLinkValue();
                    fsval.setId(elVal.getId());
                    fsval.setValue(elVal.getTitleString());
                    vals.add(fsval);
                }
                return vals;
            }
        }
        return values;
    }

    public void setValues(List<Object> values) {
        this.values = values;
    }

    public String getTemplateName() {
        return templateName;
    }

    public void setTemplateName(String templateName) {
        this.templateName = templateName;
    }

    public String getFieldName() {
        return fieldName;
    }

    public void setFieldName(String fieldName) {
        this.fieldName = fieldName;
    }

    public boolean isMultiple() {
        return multiple;
    }

    public void setMultiple(boolean multiple) {
        this.multiple = multiple;
    }

    public HashMap<String, String> getPossibleValues() {
        return possibleValues;
    }

    public void setPossibleValues(HashMap<String, String> possibleValues) {
        this.possibleValues = possibleValues;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public static FormSpecificationField build(MetadataField field, Properties prop, DocumentService service, IUser user){
        return build(field, prop, service, user, null);
    }

    public String getUniqueFieldName(){
        return this.getTemplateName()+"_"+this.getFieldName();
    }

    public String getMacro() { return macro; }

    public void setMacro(String macro) { this.macro = macro; }

    public static FormSpecificationField build(MetadataField field, Properties prop, DocumentService service, IUser user, Element el){
        FormSpecificationField f=new FormSpecificationField();
        f.setId(field.getId());
        f.setFieldName(field.getName());
        if (field.getExternalDictionary()!=null){
            f.setExtDicLink(field.getExternalDictionary());
        }
        if (field.getAddFilterFields()!=null){
            f.setExtDicAddFilters(field.getAddFilterFields());
        }
        f.setTemplateName(field.getTemplate().getName());
        if (field.getAvailableValues()!=null && !field.getAvailableValues().isEmpty()){
            HashMap<String, String> mappa = (HashMap<String, String>) service.getFieldsValues(field, user, el);
            f.setPossibleValues(mappa);
        }
        if (field.getType().equals(MetadataFieldType.CHECKBOX)) f.setMultiple(true);
        f.setType(field.getType().name());
        if (prop.containsKey(field.getTemplate().getName()+"."+field.getName())){
            f.setLabel((String)prop.get(field.getTemplate().getName()+"."+field.getName()));
        }else {
            f.setLabel(field.getTemplate().getName()+"_"+field.getName());
        }
        if (prop.containsKey("template."+field.getTemplate().getName())){
            f.setTemplateLabel((String)prop.get("template."+field.getTemplate().getName()));
        }else {
            f.setTemplateLabel(field.getTemplate().getName());
        }
        if (el!=null){
            //System.out.println("RETRIEVE FIELD VALUES: " + field.getTemplate().getName()+"_"+field.getName());
            if (el.getfieldData(field.getTemplate().getName(), field.getName()).size()>0) {
                //System.out.println("FSF - EL VALUES: " + el.getfieldData(field.getTemplate().getName(), field.getName()).get(0));
            }
            f.setValues(el.getfieldData(field.getTemplate().getName(), field.getName()));
        }
        if (field.isMandatory()) f.setMandatory(true);
        else f.setMandatory(false);
        f.setMacro(field.getMacro());
        return f;
    }
}
