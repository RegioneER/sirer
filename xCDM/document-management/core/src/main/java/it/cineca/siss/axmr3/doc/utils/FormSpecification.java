package it.cineca.siss.axmr3.doc.utils;

import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.doc.acl.Policy;
import it.cineca.siss.axmr3.doc.acl.TemplatePolicy;
import it.cineca.siss.axmr3.doc.entities.Element;
import it.cineca.siss.axmr3.doc.entities.MetadataField;
import it.cineca.siss.axmr3.doc.types.MetadataFieldType;
import it.cineca.siss.axmr3.doc.web.services.DocumentService;
import org.codehaus.jackson.annotate.JsonIgnore;

import java.util.*;

/**
 * Created by Carlo on 15/12/2015.
 */
public class FormSpecification {
    protected List<FormSpecificationField> fieldList;
    protected String typeId;
    protected Long id;
    protected Policy elementPolicy;
    protected HashMap<String, TemplatePolicy> templatePolicies;
    protected boolean hasFile;
    protected boolean fileInfo;

    public boolean isHasFile() {
        return hasFile;
    }

    public void setHasFile(boolean hasFile) {
        this.hasFile = hasFile;
    }

    public boolean isFileInfo() {
        return fileInfo;
    }

    public void setFileInfo(boolean fileInfo) {
        this.fileInfo = fileInfo;
    }

    public Policy getElementPolicy() {
        return elementPolicy;
    }

    public void setElementPolicy(Policy elementPolicy) {
        this.elementPolicy = elementPolicy;
    }

    public HashMap<String, TemplatePolicy> getTemplatePolicies() {
        return templatePolicies;
    }

    public void addTemplatePolicy(String tName, TemplatePolicy tp){
        if (templatePolicies==null) templatePolicies=new HashMap<String, TemplatePolicy>();
        templatePolicies.put(tName, tp);
    }

    public void setTemplatePolicies(HashMap<String, TemplatePolicy> templatePolicies) {
        this.templatePolicies = templatePolicies;
    }

    @JsonIgnore
    public HashMap<String, FormSpecificationField> getFields(){
        HashMap<String, FormSpecificationField> fields=new HashMap<String, FormSpecificationField>();
        for (FormSpecificationField field:this.fieldList){
            fields.put(field.getTemplateName().toUpperCase() + "_" + field.getFieldName().toUpperCase(), field);
        }
        return fields;
    }

    public String getTypeId() {
        return typeId;
    }

    public void setTypeId(String typeId) {
        this.typeId = typeId;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public FormSpecification() {
        fieldList=new LinkedList<FormSpecificationField>();
    }

    public void addField(FormSpecificationField field){
        fieldList.add(field);
    }

    public List<FormSpecificationField> getFieldList() {
        return fieldList;
    }

    public void setFieldList(List<FormSpecificationField> fieldList) {
        this.fieldList = fieldList;
    }

    public void addField(MetadataField field, Properties prop, DocumentService service, IUser user) {
        addField(field, prop, service, user, null);
    }

    public void addField(MetadataField field, Properties prop, DocumentService service, IUser user, Element el) {
        FormSpecificationField f=FormSpecificationField.build(field, prop, service, user, el);
        this.addField(f);
    }
}
