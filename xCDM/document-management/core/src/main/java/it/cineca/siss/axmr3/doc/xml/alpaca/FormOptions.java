package it.cineca.siss.axmr3.doc.xml.alpaca;

import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;

public class FormOptions {

    protected FormOptionsForm form;

    protected String helper;

    protected LinkedHashMap<String, FormOptionsField> fields;

    public FormOptions() {
        form=new FormOptionsForm();
        fields=new LinkedHashMap<String, FormOptionsField>();
    }

    public FormOptionsForm getForm() {
        return form;
    }

    public void setForm(FormOptionsForm form) {
        this.form = form;
    }

    public String getHelper() {
        return helper;
    }

    public void setHelper(String helper) {
        this.helper = helper;
    }

    public LinkedHashMap<String, FormOptionsField> getFields() {
        return fields;
    }

    public void setFields(LinkedHashMap<String, FormOptionsField> fields) {
        this.fields = fields;
    }
}
