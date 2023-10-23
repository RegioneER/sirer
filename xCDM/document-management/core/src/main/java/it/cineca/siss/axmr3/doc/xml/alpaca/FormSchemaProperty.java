package it.cineca.siss.axmr3.doc.xml.alpaca;

import java.util.LinkedList;

public class FormSchemaProperty {

    protected String type;
    protected String title;
    protected LinkedList<String> enumList;
    protected Boolean required;


    public FormSchemaProperty() {
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public LinkedList<String> getEnum() {
        return enumList;
    }

    public void setEnum(LinkedList<String> enumList) {
        this.enumList = enumList;
    }

    public Boolean getRequired() {
        return required;
    }

    public void setRequired(Boolean required) {
        this.required = required;
    }


}
