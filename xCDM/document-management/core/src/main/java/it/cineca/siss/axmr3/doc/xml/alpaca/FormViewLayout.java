package it.cineca.siss.axmr3.doc.xml.alpaca;

import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;

public class FormViewLayout {

    protected String template;
    protected LinkedHashMap<String, String> bindings;

    public FormViewLayout() {
        bindings=new LinkedHashMap<String, String>();
    }

    public String getTemplate() {
        return template;
    }

    public void setTemplate(String template) {
        this.template = template;
    }

    public LinkedHashMap<String, String> getBindings() {
        return bindings;
    }

    public void setBindings(LinkedHashMap<String, String> bindings) {
        this.bindings = bindings;
    }
}
