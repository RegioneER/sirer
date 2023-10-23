package it.cineca.siss.axmr3.doc.xml.alpaca;

import it.cineca.siss.axmr3.doc.utils.FormSpecification;
import it.cineca.siss.axmr3.doc.utils.FormSpecificationField;
import it.cineca.siss.axmr3.doc.xml.Field;
import it.cineca.siss.axmr3.doc.xml.Form;

import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;

public class FormView {

    protected String parent = "bootstrap-edit";

    protected FormViewLayout layout;

    protected LinkedHashMap<String, String> templates;

    private boolean displayReadonly = false;

    public FormView() {
        layout=new FormViewLayout();
        layout.template="generatedLayout";
        templates=new LinkedHashMap<String, String>();
        templates.put("generatedLayout","");
    }

    public void setLayoutHtml(String html){
        templates.put("generatedLayout", html);
    }

    public String getParent() {
        return parent;
    }

    public void setParent(String parent) {
        this.parent = parent;
    }

    public FormViewLayout getLayout() {
        return layout;
    }

    public void setLayout(FormViewLayout layout) {
        this.layout = layout;
    }

    public LinkedHashMap<String, String> getTemplates() {
        return templates;
    }

    public void setTemplates(LinkedHashMap<String, String> templates) {
        this.templates = templates;
    }

    public static FormView generateTemplateAndBinding(Form xmlForm, HashMap<String, FormSpecificationField> fields, boolean editable){
        FormView view=new FormView();
        String html="<div class=\"row\">{{#if options.label}}<h2>{{options.label}}</h2><span></span>{{/if}}{{#if options.helper}}<p>{{options.helper}}</p>{{/if}}";
        html+="<div class=\"row\">";
        int bsColForRow=0;
        for (Field f:xmlForm.getFields()){
            int bsCol=12/f.getCols();
            bsColForRow+=bsCol;
            if (bsColForRow>12){
                bsColForRow=bsCol;
                html+="</div><div class=\"row\">";
            }
            if (!f.getType().equals("hidden")){
                FormSpecificationField fs = fields.get(f.getVar().toUpperCase());
                if (fs!=null){
                    html+="<div class=\"col-md-"+bsCol+"\"><div id=\"BIND_"+fields.get(f.getVar().toUpperCase()).getUniqueFieldName()+"\" style=\"width:100%\"></div></div>";
                    view.layout.getBindings().put(fields.get(f.getVar().toUpperCase()).getUniqueFieldName(), "BIND_"+fields.get(f.getVar().toUpperCase()).getUniqueFieldName());
                }else {
                    html+="<div class=\"col-md-"+bsCol+"\"><div id=\"BIND_"+f.getVar().toUpperCase()+"\" style=\"width:100%\">"+f.getLabel()+"</div></div>";
                }
            }
        }
        html+="</div><div class=\"clearfix\"></div>";
        //if (editable) {
        //    html += "<button id=\"salvaForm-" + xmlForm.getFname() + "\" class=\"btn btn-warning\" name=\"salvaForm-" + xmlForm.getFname() + "\" data-rel=\"#form-" + xmlForm.getFname() + "\">";
        //    html += "<i class=\"icon-save bigger-160\"></i><b>Salva</b>";
        //    html += "</button>";
        //}
        html+="</div>";
        view.templates.put("generatedLayout", html);
        if (!editable){
            view.parent="bootstrap-display";
            view.displayReadonly=true;
        }
        //visualizzazione orizzontale (gestita lato ftl)
        //view.parent+="-horizontal";
        return view;
    }

    public boolean isDisplayReadonly() {
        return displayReadonly;
    }

    public void setDisplayReadonly(boolean displayReadonly) {
        this.displayReadonly = displayReadonly;
    }
}
