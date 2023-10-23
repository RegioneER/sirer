package it.cineca.siss.axmr3.doc.xml.alpaca;

import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.Map;

public class FormSchema {

    protected String title;
    protected String description;
    protected String type;
    protected LinkedHashMap<String, FormSchemaProperty> properties;
    protected LinkedHashMap<String, Object> dependencies;



    public FormSchema() {
        dependencies=new LinkedHashMap<String, Object>();
        properties=new LinkedHashMap<String, FormSchemaProperty>();
    }


    public LinkedHashMap<String, Object> getDependencies() {
        return dependencies;
    }

    public void setDependencies(LinkedHashMap<String, Object> dependencies) {
        this.dependencies = dependencies;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public LinkedHashMap<String, FormSchemaProperty> getProperties() {
        return properties;
    }

    public void setProperties(LinkedHashMap<String, FormSchemaProperty> properties) {
        this.properties = properties;
    }
}
