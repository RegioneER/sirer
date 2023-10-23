package it.cineca.siss.axmr3.doc.xml.alpaca;

import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.common.mvc.handlers.ControllerHandler;
import it.cineca.siss.axmr3.doc.entities.*;
import it.cineca.siss.axmr3.doc.utils.FormSpecification;
import it.cineca.siss.axmr3.doc.utils.FormSpecificationField;
import it.cineca.siss.axmr3.doc.web.services.DocumentService;
import it.cineca.siss.axmr3.doc.xml.Field;
import it.cineca.siss.axmr3.log.Log;
import org.apache.log4j.Logger;
import org.xml.sax.SAXException;

import javax.servlet.http.HttpServletRequest;
import javax.xml.parsers.ParserConfigurationException;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Form {

    protected LinkedHashMap<String, Object> data;

    protected FormSchema schema;

    protected FormOptions options;

    protected String postRenderFunction;

    protected Object view;

    public String getPostRenderFunction() {
        return postRenderFunction;
    }

    public void setPostRenderFunction(String postRenderFunction) {
        this.postRenderFunction = postRenderFunction;
    }

    public Form() {
        data=new LinkedHashMap<String, Object>();
        schema=new FormSchema();
        options=new FormOptions();
        view=new FormView();
    }

    public static Form fromXmlFile(IUser user, HttpServletRequest request,  DocumentService service, String formFile, Element el, String mode) throws ParserConfigurationException, SAXException, IOException {
        it.cineca.siss.axmr3.doc.xml.Form xmlForm=service.loadXmlForm(formFile);
        FormSpecification fspec=service.getFormScpecification(xmlForm.getObject(), user, el, request);
        HashMap<String, FormSpecificationField> fields=fspec.getFields();
        String baseUrl = ControllerHandler.getBaseUrl(request);
        Form form=new Form();
        boolean editable = true;
        if (el != null) {
            editable = el.getUserPolicy(user).isCanCreate() || el.getUserPolicy(user).isCanUpdate();
        }
        if (mode != null){
            if (mode.equalsIgnoreCase("forceEdit")) {
                editable = true;
            }else if (mode.equalsIgnoreCase("viewMode")){
                editable = false;
            }else if (mode.equalsIgnoreCase("editMode")){
                editable = true;
            }
        }
        //verifico i permessi per l'elemento corrente
        form.schema.setTitle(xmlForm.getTitolo());
        form.schema.setDescription(xmlForm.getTitolo());
        form.schema.setType("object");
        form.postRenderFunction="var fields={};";
        String postRenderAddScript = "";
        HashMap<String, String> onChangeActions=new HashMap<>();

        List<Field> extFields = new LinkedList<Field>();
        List<FormSpecificationField> extFSpecFields = new LinkedList<FormSpecificationField>();

        for(Field f:xmlForm.getFields()){
            FormSpecificationField fs=fields.get(f.getVar().toUpperCase());
            if (fs!=null) {
                String fieldName = fs.getTemplateName() + "_" + fs.getFieldName();
                FormOptionsField fof = new FormOptionsField();
                FormSchemaProperty fsp = new FormSchemaProperty();

                String fieldType = f.getType().toLowerCase();
                Logger.getLogger(Form.class).info(f.getVar());
                if (fieldType.equals("textbox")) fieldType = "text";
                fof.setType(fieldType);
                if (fieldType.equals("select")) fof.setSize(1);
                else fof.setSize(f.getVarSize());
                fof.setHelper(f.getVar());
                fsp.setType("string");
                fsp.setTitle(f.getLabel());

                ElementType docType = service.getType(service.getTypeIdByNameOrId(xmlForm.getObject()));
                MetadataTemplate mt = docType.byTemplateName(fs.templateName);

                if (mt.isAuditable() && !editable && el!=null) {
                    //String appendATLink = " <a hidefocus = \"hidefocus\" href = \"#"+fs.templateName+"_"+fs.fieldName+"_audit\" class=\"btn-link\" role = \"button\" data-toggle = \"modal\" title = \"Mostra audit trail\"  id = \""+fs.templateName+"_"+fs.fieldName+"_audit_btn\" > <i class=\"icon-time\" ></i></a> ";
                    String addCss = "";
                    String appendATLink = "\t\t<a hidefocus=\"hidefocus\" class=\"btn-link\" role=\"button\" title=\"Mostra audit trail\"\n" +
                            "\t    style=\""+addCss+"\" \n" +
                            "           href=\"#\"\n" +
                            "           data-audit-id=\""+fs.templateName+"_"+fs.fieldName+"_"+el.getId()+"\"\n" +
                            "           data-el-id=\""+el.getId()+"\" data-template-name=\""+fs.templateName+"\" data-field-name=\""+fs.fieldName+"\">\n" +
                            "\n" +
                            "            <i class=\"icon-time\"></i> </a>\n";
                    postRenderAddScript += "" +
                            "\t\t$('a[data-audit-id=\""+fs.templateName+"_"+fs.fieldName+"_"+el.getId()+"\"]').unbind('click');\n" +
                            "\t\t$('a[data-audit-id=\""+fs.templateName+"_"+fs.fieldName+"_"+el.getId()+"\"]').click(function(){\n" +
                            "\t\t\tshowAuditData("+el.getId()+", '"+fs.templateName+"', '"+fs.fieldName+"');\n" +
                            "\t\t});\n";
                    fsp.setTitle(fsp.getTitle()+appendATLink);
                }
                if (f.getAttributes().containsKey("el_link_types")) {
                    String types=f.getAttributes().get("el_link_types");
                    fof.setDataSourceFunction("elementLinkDatasource('"+types+"', callback)");
                }
                if (f.getAttributes().containsKey("ext_script")) {
                    extFields.add(f);
                    extFSpecFields.add(fs);
                    String script=f.getAttributes().get("ext_script");
                    String params="";
                    if (f.getAttributes().containsKey("ext_params")) {
                        params=f.getAttributes().get("ext_params");
                        fof.setDataSourceFunction("dictionaryDatasource('"+script+"','"+params+"', callback)");
                        String pattern="\\[(.*?)\\]";
                        Pattern r=Pattern.compile(pattern);
                        Matcher m=r.matcher(params);
                        while(m.find()) {
                            String conditioningField=m.group(1);
                            String action="\nfields['"+fieldName+"'].refresh();$('select[name="+fieldName+"]').select2();";
                            if (onChangeActions.containsKey(conditioningField)){
                                action=onChangeActions.get(conditioningField)+action;
                            }
                            onChangeActions.put(conditioningField, action);
                        }
                    }else {
                        fof.setDataSourceFunction("dictionaryDatasource('"+script+"',null, callback)");
                    }
                }


                fof.setRemoveDefaultNone(true);
                if (f.getAttributes().containsKey("mandatory") && (f.getAttributes().get("mandatory").toLowerCase().equals("true") || f.getAttributes().get("mandatory").toLowerCase().equals("send") || f.getAttributes().get("mandatory").toLowerCase().equals("yes"))) {
                    fsp.setRequired(true);

                }
                if (f.getAttributes().containsKey("condition")) { //editable &&
                    form.schema.dependencies.put(fieldName, f.getConditionField(fspec));
                    fof.dependencies.put(f.getConditionField(fspec), f.getConditionValues());
                }
                if (fs.getPossibleValues().size() > 0) {
                    Iterator<String> it = fs.getPossibleValues().keySet().iterator();
                    fsp.setEnum(new LinkedList<String>());
                    while (it.hasNext()) {
                        String key = it.next();
                        String value = fs.getPossibleValues().get(key);
                        fsp.getEnum().add(key);
                        fof.getOptionLabels().add(value);
                    }
                }
                if (fs.getValues() != null) {
                    if (fs.getValues().size() > 1) {
                        LinkedList<Object> dataList = new LinkedList<Object>();
                        if (!editable){
                            //Se non posso modificare la form, tanto vale che abbia direttamente i valori da mostrare come stringhe
                            for (Object o : fs.getValues()) {
                                if (o.toString().contains("###")) {
                                    if (extFSpecFields.contains(fs)){
                                        dataList.add(o.toString().split("###")[1]);
                                    }else{
                                        //Log.info(Form.class,"AGGIUNGO NOT EDITABLE (CONTAINS): "+fieldName+" - "+o);
                                        dataList.add(o.toString().split("###")[0]);
                                    }
                                }else{
                                    //Log.info(Form.class,"AGGIUNGO NOT EDITABLE (NOT CONTAINS): "+fieldName+" - "+o);
                                    dataList.add(o.toString());
                                }
                            }

                        }else {
                            //List<Object> values = fs.getValues();
                            for (Object o : fs.getValues()) {
                                if (o instanceof String) {
                                    //Log.info(Form.class,"AGGIUNGO EDITABLE: "+fieldName+" - "+o);
                                    dataList.add(o.toString().split("###")[0]);
                                }
                            }
                        }
                        //Log.info(Form.class,"FIELD MULTIVALUE: "+fieldName+" - "+dataList.size());
                        form.data.put(fieldName, dataList);
                    } else {
                        if (fs.getValues().size() == 1) {
                            String dataObj = null;
                            if (fs.getValues().get(0) instanceof String) {
                                if (!editable){
                                    //Se non posso modificare la form, tanto vale che abbia direttamente i valori da mostrare come stringhe
                                    String txtval = ((String) fs.getValues().get(0));
                                    if (txtval.contains("###")) {
                                        if (extFSpecFields.contains(fs)){
                                            dataObj = txtval.split("###")[1];
                                        }else{
                                            dataObj = txtval.split("###")[0];
                                        }
                                    }else{
                                        dataObj = txtval;
                                    }
                                }else {
                                    dataObj = ((String) fs.getValues().get(0)).split("###")[0];
                                    //fs.getValues().add(0, ((String) fs.getValues().get(0)).split("###")[0]);
                                }
                            } else if (fs.getValues().get(0) instanceof Date) {
                                SimpleDateFormat simpleDateFormat = new SimpleDateFormat("dd/MM/yyyy");
                                if (fs.getValues().get(0) != null) {
                                    dataObj = simpleDateFormat.format(fs.getValues().get(0));
                                }
                            } else if (fs.getValues().get(0) instanceof Calendar) {
                                Calendar cal = ((Calendar) fs.getValues().get(0));
                                Date tmpdate = cal.getTime();
                                SimpleDateFormat simpleDateFormat = new SimpleDateFormat("dd/MM/yyyy");
                                if (tmpdate != null) {
                                    dataObj = simpleDateFormat.format(tmpdate);
                                }
                            }
                            if (dataObj != null && !dataObj.equalsIgnoreCase("null")) {
                                form.data.put(fieldName, dataObj);
                            }
                        }
                    }
                }
                form.options.getFields().put(fieldName, fof);
                form.schema.properties.put(fieldName, fsp);
                form.postRenderFunction+="\nfields['"+fieldName+"']=control.childrenByPropertyId['"+fieldName+"'];";
            }else{
                Log.warn(Form.class,"Field Not Found: "+f.getVar().toUpperCase());
            }
        }
        form.postRenderFunction+=postRenderAddScript;

        for(Field f:xmlForm.getFields()) {
            FormSpecificationField fs = fields.get(f.getVar().toUpperCase());
            if (fs != null) {
                String fieldName = fs.getTemplateName() + "_" + fs.getFieldName();
                Iterator<String> it=onChangeActions.keySet().iterator();
                while (it.hasNext()){
                    String field=it.next();
                    if (field.toUpperCase().equals(fieldName.toUpperCase())){
                        form.postRenderFunction+="\nfields['"+fieldName+"'].on('change',function(){"+onChangeActions.get(field)+"});";
                    }
                }
                if (!editable && extFSpecFields.contains(fs)) {
                    String fieldNameBis = fs.getTemplateName() + "_" + fs.getFieldName();
                    form.options.getFields().get(fieldNameBis).setType("text");
                    form.options.getFields().get(fieldNameBis).setSize(4000);
                    form.schema.getProperties().get(fieldNameBis).setEnum(null);
                    fs.setType("text");
                    f.setType("text");
                }

            }
        }



        form.options.setHelper(xmlForm.getTitolo());
        form.options.getForm().getAttributes().setAction(baseUrl+"/app/rest/documents/update/");
        form.options.getForm().getAttributes().setOnSubmit("return false;");
        form.options.getForm().getAttributes().setMethod("post");
        form.view=FormView.generateTemplateAndBinding(xmlForm, fields, editable);
        return form;
    }

    public LinkedHashMap<String, Object> getData() {
        return data;
    }

    public void setData(LinkedHashMap<String, Object> data) {
        this.data = data;
    }

    public FormSchema getSchema() {
        return schema;
    }

    public void setSchema(FormSchema schema) {
        this.schema = schema;
    }

    public FormOptions getOptions() {
        return options;
    }

    public void setOptions(FormOptions options) {
        this.options = options;
    }

    public Object getView() {
        return view;
    }

    public void setView(Object view) {
        this.view = view;
    }



}
