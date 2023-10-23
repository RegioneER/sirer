package it.cineca.siss.axmr3.doc.elk;

import it.cineca.siss.axmr3.doc.entities.*;
import it.cineca.siss.axmr3.doc.types.MetadataFieldType;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by Carlo on 30/01/2016.
 */
public class ElkValue {

    private String id;
    private Long objId;
    private String objType;
    private String objTitle;
    private String fieldName;
    private String templateName;
    private String dataType;
    private List<String> stringValue;
    private List<String> stringValue_NOTANALYZED;
    private List<String> dateValue;
    private List<Float> floatValue;
    private HashMap<String, HashMap<String, Object>> parents;
    private List<String> viewableByUsers;
    private List<String> viewableByGroups;
    private List<String> objViewableByUsers;
    private List<String> objViewableByGroups;

    public List<String> getObjViewableByUsers() {
        return objViewableByUsers;
    }

    public void setObjViewableByUsers(List<String> objViewableByUsers) {
        this.objViewableByUsers = objViewableByUsers;
    }

    public List<String> getObjViewableByGroups() {
        return objViewableByGroups;
    }

    public void setObjViewableByGroups(List<String> objViewableByGroups) {
        this.objViewableByGroups = objViewableByGroups;
    }

    public String getObjTitle() {
        return objTitle;
    }

    public void setObjTitle(String objTitle) {
        this.objTitle = objTitle;
    }

    public String getFieldName() {
        return fieldName;
    }

    public void setFieldName(String fieldName) {
        this.fieldName = fieldName;
    }

    public String getTemplateName() {
        return templateName;
    }

    public void setTemplateName(String templateName) {
        this.templateName = templateName;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }



    public Long getObjId() {
        return objId;
    }

    public void setObjId(Long objId) {
        this.objId = objId;
    }

    public String getObjType() {
        return objType;
    }

    public void setObjType(String objType) {
        this.objType = objType;
    }

    public String getDataType() {
        return dataType;
    }

    public void setDataType(String dataType) {
        this.dataType = dataType;
    }

    public HashMap<String, HashMap<String, Object>> getParents() {
        return parents;
    }

    public void setParents(HashMap<String, HashMap<String, Object>> parents) {
        this.parents = parents;
    }

    public List<String> getViewableByUsers() {
        return viewableByUsers;
    }

    public void setViewableByUsers(List<String> viewableByUsers) {
        this.viewableByUsers = viewableByUsers;
    }

    public List<String> getViewableByGroups() {
        return viewableByGroups;
    }

    public void setViewableByGroups(List<String> viewableByGroups) {
        this.viewableByGroups = viewableByGroups;
    }

    public List<String> getStringValue() {
        return stringValue;
    }

    public void setStringValue(List<String> stringValue) {
        this.stringValue = stringValue;
    }

    public List<String> getDateValue() {
        return dateValue;
    }

    public void setDateValue(List<String> dateValue) {
        this.dateValue = dateValue;
    }

    public List<Float> getFloatValue() {
        return floatValue;
    }

    public void setFloatValue(List<Float> floatValue) {
        this.floatValue = floatValue;
    }

    public void addDate(String value) {
        if (this.dateValue == null) this.dateValue = new LinkedList<String>();
        this.dateValue.add(value);
    }

    public void addString(String value) {
        if (this.stringValue == null) this.stringValue = new LinkedList<String>();
        this.stringValue.add(value);
    }

    public void addValue(String value){
        Object val=ElkSimpleElement.getValue(value);
        if (val instanceof Float) {
            if (this.floatValue==null) {
                this.floatValue=new LinkedList<Float>();
                this.stringValue=new LinkedList<String>();
                this.stringValue_NOTANALYZED=new LinkedList<String>();
            }
            this.floatValue.add((Float)val);
            this.stringValue.add(value);
            if (value != null) {
                this.stringValue_NOTANALYZED.add(value.toLowerCase());
            }else{
                this.stringValue_NOTANALYZED.add(value);
            }
        }
        else {
            if (this.stringValue==null){
                this.stringValue=new LinkedList<String>();
                this.stringValue_NOTANALYZED=new LinkedList<String>();
            }
            this.stringValue.add((String) val);
            if (val != null) {
                this.stringValue_NOTANALYZED.add(((String) val).toLowerCase());
            }else{
                this.stringValue_NOTANALYZED.add((String) val);
            }
        }
    }

    public static HashMap<String, HashMap<String, Object>> getParents(Element el){
        HashMap<String, HashMap<String, Object>> ps=null;
        if (el.getParent()==null){
            HashMap<String, Object> pData = new HashMap<String, Object>();
            ps=new HashMap<String, HashMap<String, Object>>();
            pData.put("id", el.getId());
            pData.put("title", el.getTitleString());
            ps.put(el.getTypeName(), pData);
        }else {
            ps = getParents(el.getParent());
            HashMap<String, Object> pData = new HashMap<String, Object>();
            pData.put("id", el.getId());
            pData.put("title", el.getTitleString());
            ps.put(el.getTypeName(), pData);
        }
        return ps;
    }

    public static List<ElkValue> buildValues(Element el){
        String typeName=el.getTypeName();
        String title=el.getTitleString();
        List<ElkValue> ret=new LinkedList<ElkValue>();
        LinkedList<String> elGroupsList = new LinkedList<String>();
        LinkedList<String> elUsersList = new LinkedList<String>();
        for(Acl acl:el.getAcls()){
            if (acl.getPolicy().isCanView()){
                for(AclContainer ac:acl.getContainers()){
                    if (ac.isAuthority()) elGroupsList.add(ElkService.escape(ac.getContainer()));
                    else {
                        if (ac.getContainer().equals("*")) elUsersList.add(ElkService.escape("all_users"));
                        else elUsersList.add(ElkService.escape(ac.getContainer()));
                    }
                }
            }
        }
        HashMap<String, HashMap<String, Object>> ps=null;
        if (el.getParent()!=null){
            ps = getParents(el.getParent());
        }
        for (ElementTemplate et:el.getElementTemplates()){
            LinkedList<String> templateUsersList = new LinkedList<String>();
            LinkedList<String> templateGroupsList = new LinkedList<String>();
            if (et.getTemplateAcls().size()==0) {
                for (int i=0;i<elGroupsList.size();i++) templateGroupsList.add(ElkService.escape(elGroupsList.get(i)));
                for (int i=0;i<elUsersList.size();i++) templateUsersList.add(ElkService.escape(elUsersList.get(i)));
            }else {
                for (TemplateAcl acl : et.getTemplateAcls()) {
                    if (acl.getPolicy().isCanView()) {
                        for (TemplateAclContainer ac : acl.getContainers()) {
                            if (ac.isAuthority()) templateGroupsList.add(ElkService.escape(ac.getContainer()));
                            else {
                                if (ac.getContainer().equals("*")) templateUsersList.add(ElkService.escape("all_users"));
                                else templateUsersList.add(ElkService.escape(ac.getContainer()));
                            }
                        }
                    }
                }
            }
            String templateName=et.getMetadataTemplate().getName();
            for (MetadataField f:et.getMetadataTemplate().getFields()){
                String fieldName=f.getName();
                String fieldType=f.getType().name();
                ElkValue v1=new ElkValue();
                v1.setId(el.getTypeName()+"_"+el.getId()+"_"+templateName+"_"+fieldName);
                v1.setTemplateName(templateName);
                v1.setFieldName(fieldName);
                v1.setDataType(fieldType);
                v1.setObjId(el.getId());
                v1.setObjType(typeName);
                v1.setObjTitle(title);
                v1.setViewableByUsers(templateUsersList);
                v1.setViewableByGroups(templateGroupsList);
                v1.setObjViewableByGroups(elGroupsList);
                v1.setObjViewableByUsers(elUsersList);
                v1.setParents(ps);
                if (f.getType().equals(MetadataFieldType.TEXTBOX) || f.getType().equals(MetadataFieldType.TEXTAREA) ||f.getType().equals(MetadataFieldType.RICHTEXT)){
                    if (el.getFieldDataStrings(templateName, fieldName).size()>0) {
                        for (int idx = 0; idx < el.getFieldDataStrings(templateName, fieldName).size(); idx++) {
                            v1.addValue(el.getFieldDataStrings(templateName, fieldName).get(idx));
                        }
                        ret.add(v1);
                    }
                }
                if (f.getType().equals(MetadataFieldType.SELECT) || f.getType().equals(MetadataFieldType.CHECKBOX) || f.getType().equals(MetadataFieldType.RADIO) || f.getType().equals(MetadataFieldType.EXT_DICTIONARY)) {
                    if (el.getFieldDataDecodes(templateName, fieldName).size()>0) {
                        for (int idx = 0; idx < el.getFieldDataDecodes(templateName, fieldName).size(); idx++) {
                            v1.addValue(el.getFieldDataDecodes(templateName, fieldName).get(idx));
                        }
                        ElkValue v2 = new ElkValue();
                        v2.setId(el.getTypeName() + "_" + el.getId() + "_" + templateName + "_" + fieldName + "_CODE");
                        v2.setTemplateName(templateName);
                        v2.setFieldName(fieldName);
                        v2.setDataType(fieldType);
                        v2.setObjId(el.getId());
                        v2.setObjType(typeName);
                        v2.setObjTitle(title);
                        v2.setViewableByUsers(templateUsersList);
                        v2.setViewableByGroups(templateGroupsList);
                        v2.setParents(ps);
                        for (int idx = 0; idx < el.getFieldDataCodes(templateName, fieldName).size(); idx++) {
                            v2.addValue(el.getFieldDataCodes(templateName, fieldName).get(idx));
                        }
                        ret.add(v1);
                        ret.add(v2);
                    }
                }
                if (f.getType().equals(MetadataFieldType.ELEMENT_LINK)) {
                    ElkValue v2=new ElkValue();
                    v2.setId(el.getTypeName()+"_"+el.getId()+"_"+templateName+"_"+fieldName+"_ELID");
                    v2.setTemplateName(templateName);
                    v2.setFieldName(fieldName);
                    v2.setDataType(fieldType);
                    v2.setObjId(el.getId());
                    v2.setObjType(typeName);
                    v2.setObjTitle(title);
                    v2.setViewableByUsers(templateUsersList);
                    v2.setViewableByGroups(templateGroupsList);
                    v2.setParents(ps);
                    if (el.getFieldDataElement(templateName, fieldName).size()>0) {
                        for (int idx = 0; idx < el.getFieldDataElement(templateName, fieldName).size(); idx++) {
                            v2.addValue(el.getFieldDataElement(templateName, fieldName).get(idx).getId() + "");
                            v1.addValue(el.getFieldDataElement(templateName, fieldName).get(idx).getTitleString());
                        }
                        ret.add(v1);
                        ret.add(v2);
                    }
                }
                if (f.getType().equals(MetadataFieldType.DATE)){
                    if (el.getFieldDataDates(templateName, fieldName).size()>0) {
                        for (int idx = 0; idx < el.getFieldDataDates(templateName, fieldName).size(); idx++) {
                            Calendar dt = el.getFieldDataDates(templateName, fieldName).get(idx);
                            DateFormat df = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm");
                            DateFormat df2 = new SimpleDateFormat("dd/MM/yyyy");
                            if (dt != null) {
                                v1.addDate(df.format(dt.getTime()));
                                v1.addString(df2.format(dt.getTime()));
                            }
                        }
                        ret.add(v1);
                    }
                }
            }
        }
        return ret;
    }

}
