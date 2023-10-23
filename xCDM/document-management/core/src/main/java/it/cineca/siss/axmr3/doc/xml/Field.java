package it.cineca.siss.axmr3.doc.xml;

import com.google.gson.Gson;
import it.cineca.siss.axmr3.doc.utils.FormSpecification;
import it.cineca.siss.axmr3.doc.utils.FormSpecificationField;
import it.cineca.siss.axmr3.exceptions.AxmrGenericException;
import org.apache.log4j.Logger;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

import static it.cineca.siss.axmr3.doc.StdUtils.parseDate;

public class Field {

    private String type;
    private String var;
    private String varType;
    private Integer varSize;
    private Integer cols;
    private Integer colspan;
    private Map<String, String> attributes;
    private Map<String, String> values;
    private String label;

    public Field(){}

    public Field(Node node) {
        attributes = new HashMap<String, String>();
        values = new HashMap<String, String>();
        cols = 1;
        colspan = 1;
        if (node.hasAttributes()) {
            NamedNodeMap nodeMap = node.getAttributes();
            for (int i = 0; i < nodeMap.getLength(); i++) {
                Node attr = nodeMap.item(i);
                attributes.put(attr.getNodeName().toLowerCase(), attr.getNodeValue());
                if (attr.getNodeName().toLowerCase().equals("type")) type = attr.getNodeValue();
                if (attr.getNodeName().toLowerCase().equals("var_type")) varType = attr.getNodeValue();
                if (attr.getNodeName().toLowerCase().equals("var_size"))
                    varSize = Integer.parseInt(attr.getNodeValue());
                if (attr.getNodeName().toLowerCase().equals("var")) var = attr.getNodeValue();
                if (attr.getNodeName().toLowerCase().equals("cols")) cols = Integer.parseInt(attr.getNodeValue());
                if (attr.getNodeName().toLowerCase().equals("colspan")) colspan = Integer.parseInt(attr.getNodeValue());
            }
        }
        if (node.hasChildNodes()) {
            for (int i = 0; i < node.getChildNodes().getLength(); i++) {
                Node child = node.getChildNodes().item(i);
                if (child.getNodeName().toLowerCase().equals("value")) {
                    values.put(child.getAttributes().getNamedItem("val").getTextContent(), child.getTextContent());
                }
                if (child.getNodeName().toLowerCase().equals("txt_value")) {
                    label = child.getTextContent();
                }
            }

        }

    }

    public String getAvailableValues() {
        if (values != null && values.size() > 0) {
            return new Gson().toJson(values);
        }
        if (this.attributes.containsKey("bytb")) {
            String sqlQuery = "select " + this.attributes.get("bytbcode") + ", " + this.attributes.get("bytbdecode");
            sqlQuery += " from " + this.attributes.get("bytb");
            if (this.attributes.containsKey("bytbwhere") && this.attributes.get("bytbwhere")!=null)
                sqlQuery += " where " + this.attributes.get("bytbwhere");

            return sqlQuery;
        }
        return null;
    }

    public boolean conditionPassed(FormSpecification fspec, Map data){
        if (!isConditioned()) return true;
        else{
            if (!data.containsKey(getConditionField(fspec))){
                return false;
            }else {
                Object dataField=data.get(getConditionField(fspec));
                if (dataField instanceof String){
                    String[] conditionValues=getConditionValues();
                    for (int i=0;i<conditionValues.length;i++){
                        if (conditionValues[i].equals(dataField)){
                            return true;
                        }
                    }
                }
                if (dataField instanceof String[]){
                    for (int k=0;k<((String[]) dataField).length;k++){
                        String[] conditionValues=getConditionValues();
                        for (int i=0;i<conditionValues.length;i++){
                            if (conditionValues[i].equals(dataField)){
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    public boolean isConditioned(){
        if (this.getAttributes().containsKey("condition") && !this.getAttributes().get("condition").isEmpty()) {
            return true;
        }
        return false;
    }

    public boolean isMandatory(){

        return true;
    }

    public boolean doCheck(FormSpecificationField fsf, Map data){
        Iterator<String> attributeIt=this.attributes.keySet().iterator();
        while (attributeIt.hasNext()){
            String attr=attributeIt.next();
            try {
                Comparison cmp = Comparison.valueOfIgnoreCase(attr);
                if (!comparisonCheck(cmp, fsf, data)) return false;
            }catch (IllegalArgumentException ex){

            } catch (AxmrGenericException e) {
                Logger.getLogger(this.getClass()).error(e.getMessage(), e);
                return false;
            }
        }
        return true;
    }

    public boolean comparisonCheck(Comparison cmp, FormSpecificationField fsf, Map data) throws AxmrGenericException {
        String dataType="String";
        dataType=fsf.getType();
        String checkValueString=this.getAttributes().get(cmp.name().toLowerCase());
        Object rightHand=checkValueString;
        Object leftHandParam=data.get(fsf.getUniqueFieldName());
        Object leftHand=leftHandParam;
        if (dataType.equals("integer")) {
            if (leftHandParam instanceof String){
                leftHand=Integer.parseInt((String) leftHandParam);
            }
            if (leftHandParam instanceof String[]){
                leftHand=new Integer[((String[]) leftHandParam).length];
                for (int i=0;i<((String[]) leftHandParam).length;i++){
                    ((Integer[]) leftHand)[i]=Integer.parseInt(((String[]) leftHandParam)[i]);
                }
            }
            rightHand=Integer.parseInt(checkValueString);
        }
        if (dataType.equals("float")) {

            if (leftHandParam instanceof String){
                leftHand=Float.parseFloat((String) leftHandParam);
            }
            if (leftHandParam instanceof String[]){
                leftHand=new Float[((String[]) leftHandParam).length];
                for (int i=0;i<((String[]) leftHandParam).length;i++){
                    ((Float[]) leftHand)[i]=Float.parseFloat(((String[]) leftHandParam)[i]);
                }
            }
            rightHand=Float.parseFloat(checkValueString);
        }
        if (dataType.equals("date")) {
            if (leftHandParam instanceof String){
                leftHand=parseDate((String) leftHandParam);
            }
            if (leftHandParam instanceof String[]){
                leftHand=new Calendar[((String[]) leftHandParam).length];
                for (int i=0;i<((String[]) leftHandParam).length;i++){
                    ((Calendar[]) leftHand)[i]=parseDate(((String[]) leftHandParam)[i]);
                }
            }
            rightHand=parseDate(checkValueString);
        }
        return Comparison.doCheck(cmp, rightHand, leftHand);
    }

    @Override
    public String toString() {
        return "Field{" +
                "type='" + type + '\'' +
                ", var='" + var + '\'' +
                ", varType='" + varType + '\'' +
                ", varSize='" + varSize + '\'' +
                ", cols=" + cols +
                ", colspan=" + colspan +
                ", attributes=" + attributes +
                ", values=" + values +
                ", label='" + label + '\'' +
                '}';
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getVar() {
        return var;
    }

    public void setVar(String var) {
        this.var = var;
    }

    public String getVarType() {
        return varType;
    }

    public void setVarType(String varType) {
        this.varType = varType;
    }

    public Integer getVarSize() {
        return varSize;
    }

    public void setVarSize(Integer varSize) {
        this.varSize = varSize;
    }

    public Integer getCols() {
        return cols;
    }

    public void setCols(Integer cols) {
        this.cols = cols;
    }

    public Integer getColspan() {
        return colspan;
    }

    public void setColspan(Integer colspan) {
        this.colspan = colspan;
    }

    public Map<String, String> getAttributes() {
        return attributes;
    }

    public void setAttributes(Map<String, String> attributes) {
        this.attributes = attributes;
    }

    public Map<String, String> getValues() {
        return values;
    }

    public void setValues(Map<String, String> values) {
        this.values = values;
    }

    public String getLabel() {
        return label;
    }

    public void setLabel(String label) {
        this.label = label;
    }

    public String getConditionField(FormSpecification fspec) {
        return fspec.getFields().get(this.getAttributes().get("condition").toUpperCase()).getUniqueFieldName();
    }

    public String[] getConditionValues() {
        return this.getAttributes().get("condition_value").split(",");
    }
}