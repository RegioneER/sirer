package it.cineca.siss.axmr3.doc.xml;

import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.doc.entities.Element;
import it.cineca.siss.axmr3.doc.utils.FormSpecification;
import it.cineca.siss.axmr3.doc.utils.FormSpecificationField;
import org.apache.log4j.Logger;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import java.util.Collection;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;

public class Form {

    private static Logger log = Logger.getLogger(Form.class);
    private String fname;
    private String titolo;
    private String object;
    private String jsOnLoad;
    private int cols;
    private Map<String, String> attributes;
    private Collection<Field> fields;
    private Collection<Action> actions;

    public Form(org.w3c.dom.Document doc, String fileName){
        attributes=new HashMap<String, String>();
        fields=new LinkedList<Field>();
        actions=new LinkedList<Action>();
        cols=1;
        Logger.getLogger(this.getClass()).info(doc.getDocumentElement().getNodeName());
        if (doc.getDocumentElement().hasAttributes()) {
            NamedNodeMap nodeMap = doc.getDocumentElement().getAttributes();
            for (int i = 0; i < nodeMap.getLength(); i++) {
                Node node = nodeMap.item(i);
                attributes.put(node.getNodeName(), node.getNodeValue());
                if (node.getNodeName().toLowerCase().equals("fname")) fname=node.getNodeValue();
                if (node.getNodeName().toLowerCase().equals("titolo")) titolo=node.getNodeValue();
                if (node.getNodeName().toLowerCase().equals("object")) object=node.getNodeValue();
                if (node.getNodeName().toLowerCase().equals("cols")) cols=Integer.parseInt(node.getNodeValue());
            }
        }
        if (fname == null || fname.isEmpty()){
            log.info(fileName);
            if (fileName.lastIndexOf(".")>0){
                fileName = fileName.substring(0,fileName.lastIndexOf("."));
            }
            fname=fileName;
        }
        if (doc.getDocumentElement().hasChildNodes()) {
            NodeList nodeList = doc.getDocumentElement().getChildNodes();
            for (int count = 0; count < nodeList.getLength(); count++) {
                Node node = nodeList.item(count);
                if (node.getNodeType() == Node.ELEMENT_NODE) {
                    if (node.getNodeName().toLowerCase().equals("field")) {
                        fields.add(new Field(node));
                    }
                }
            }


        }
    }

    @Override
    public String toString() {
        return "Form{" +
                "fname='" + fname + '\'' +
                ", titolo='" + titolo + '\'' +
                ", object='" + object + '\'' +
                ", jsOnLoad='" + jsOnLoad + '\'' +
                ", cols=" + cols +
                ", attributes=" + attributes +
                ", fields=" + fields +
                ", actions=" + actions +
                '}';
    }

    public String getFname() {
        return fname;
    }

    public void setFname(String fname) {
        this.fname = fname;
    }

    public String getTitolo() {
        return titolo;
    }

    public void setTitolo(String titolo) {
        this.titolo = titolo;
    }

    public String getObject() {
        return object;
    }

    public void setObject(String object) {
        this.object = object;
    }

    public String getJsOnLoad() {
        return jsOnLoad;
    }

    public void setJsOnLoad(String jsOnLoad) {
        this.jsOnLoad = jsOnLoad;
    }

    public Map<String, String> getAttributes() {
        return attributes;
    }

    public void setAttributes(Map<String, String> attributes) {
        this.attributes = attributes;
    }

    public Collection<Field> getFields() {
        return fields;
    }

    public void setFields(Collection<Field> fields) {
        this.fields = fields;
    }

    public Collection<Action> getActions() {
        return actions;
    }

    public void setActions(Collection<Action> actions) {
        this.actions = actions;
    }

    public CheckResult doChecks(IUser user, FormSpecification fspec, Map data, Element el) {
        CheckResult result=new CheckResult();
        result.setPassed(true);

        for(Field f:fields){
            FormSpecificationField fsf=fspec.getFields().get(f.getVar().toUpperCase());
            if (!f.doCheck(fsf, data)){
                result.errors.put(fsf.getUniqueFieldName(), "Errore validazione campo "+fsf.getUniqueFieldName());
                result.setPassed(false);
            }
        }
        return result;
    }


    public void appendField(Field newField){
        fields.add(newField);
    }


}
