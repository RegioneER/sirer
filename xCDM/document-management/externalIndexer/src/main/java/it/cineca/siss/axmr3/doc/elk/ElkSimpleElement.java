package it.cineca.siss.axmr3.doc.elk;

import com.google.gson.annotations.Expose;
import it.cineca.siss.axmr3.authentication.IAuthority;
import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.doc.entities.*;
import it.cineca.siss.axmr3.doc.types.MetadataFieldType;
import it.cineca.siss.axmr3.log.Log;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.logging.Logger;
import java.util.regex.Pattern;

/**
 * Created by Carlo on 29/01/2016.
 */
public class ElkSimpleElement {

    @Expose
    private Long id;

    @Expose
    private List<String> viewableByUsers;

    @Expose
    private List<String> viewableByGroups;

    @Expose
    private String createdBy;

    @Expose
    private String createdOn;

    @Expose
    private String updatedBy;

    @Expose
    private String updatedOn;

    @Expose
    private long position;

    @Expose
    private HashMap<String, ElkMetadataTemplate> metadata;

    @Expose
    public ElkSimpleElement parent;

    @Expose
    public String title;

    @Expose
    public String type;

    public long getPosition() {
        return position;
    }

    public void setPosition(long position) {
        this.position = position;
    }

    //@Expose(serialize = false)
    //private HashMap<String,ElkMapping> mapping;

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
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

    public String getCreatedBy() {
        return createdBy;
    }

    public void setCreatedBy(String createdBy) {
        this.createdBy = createdBy;
    }

    public HashMap<String, ElkMetadataTemplate> getMetadata() {
        return metadata;
    }

    public void setMetadata(HashMap<String, ElkMetadataTemplate> metadata) {
        this.metadata = metadata;
    }

    public ElkSimpleElement getParent() {
        return parent;
    }

    public void setParent(ElkSimpleElement parent) {
        this.parent = parent;
    }


    public static ElkSimpleElement elementToSimple(Element el) {
        ElkFullElement sel = new ElkFullElement();
        sel.setId(el.getId());
        if (el.getTitleString() != null) sel.setTitle(el.getTitleString());
        sel.setType(el.getType().getTypeId());
        HashMap<String, ElkMetadataTemplate> templateTmp = new HashMap<String, ElkMetadataTemplate>();
        for (ElementTemplate et : el.getElementTemplates()) {
            ElkMetadataTemplate smd = new ElkMetadataTemplate();
            LinkedList<String> usersList = new LinkedList<String>();
            LinkedList<String> groupsList = new LinkedList<String>();
            if (et.getTemplateAcls().size() == 0) usersList.add("*");
            for (TemplateAcl acl : et.getTemplateAcls()) {
                if (acl.getPolicy().isCanView()) {
                    for (TemplateAclContainer ac : acl.getContainers()) {
                        if (ac.isAuthority()) groupsList.add(ElkService.escape(ac.getContainer()));
                        else {
                            if (ac.getContainer().equals("*")) usersList.add(ElkService.escape("all_users"));
                            else usersList.add(ElkService.escape(ac.getContainer()));
                        }
                    }
                }
            }
            smd.setViewableByUsers(usersList);
            smd.setViewableByGroups(groupsList);
            smd.setName(et.getMetadataTemplate().getName());
            templateTmp.put(et.getMetadataTemplate().getName(), smd);
        }
        DateFormat df = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm");
        HashMap<String, ElkMetadataTemplate> templateTmp2 = new HashMap<String, ElkMetadataTemplate>();
        //HashMap<String, ElkMapping> mappingTmpl = new HashMap<String, ElkMapping>();
        for (ElementMetadata emd : el.getData()) {
            HashMap<String, Object> vals = new HashMap<String, Object>();
            ElkMetadataTemplate smd = null;
            if (templateTmp2.containsKey(emd.getTemplateName())) {
                smd = templateTmp2.get(emd.getTemplateName());
            } else {
                smd = templateTmp.get(emd.getTemplateName());
            }
            if (emd.getField().getType().equals(MetadataFieldType.TEXTBOX) || emd.getField().getType().equals(MetadataFieldType.TEXTAREA) || emd.getField().getType().equals(MetadataFieldType.RICHTEXT)) {
                List<Object> valList = new LinkedList<Object>();
                List<Object> valList1 = new LinkedList<Object>();
                List<Object> valListLC = new LinkedList<Object>();
                for (ElementMetadataValue emv : emd.getValues()) {
                    String value = null;
                    if (emv.getTextValue() != null) value = emv.getTextValue();
                    if (emv.getLongTextValue() != null) value = emv.getLongTextValue();
                    Object valueParsed = ElkSimpleElement.getValue(value);
                    if (valueParsed instanceof Float) {
                        valList1.add(valueParsed);
                    }
                    valList.add(value);
                    if (value != null) {
                        valListLC.add(value.toLowerCase());
                    } else {
                        valListLC.add(value);
                    }
                }
                if (valList1.size() > 0) {
                    if (valList1.size() == 1) {
                        vals.put(emd.getFieldName() + "_FLOATVALUE", valList1.get(0));
                    } else {
                        vals.put(emd.getFieldName() + "_FLOATVALUE", valList1);
                    }
                }
                //mappingTmpl.put(emd.getFieldName() + "_NOTANALYZED", new ElkMapping("string","not_analyzed"));
                if (valList.size() == 0) {
                    vals.put(emd.getFieldName(), null);
                    vals.put(emd.getFieldName() + "_NOTANALYZED", null);
                } else if (valList.size() == 1) {
                    vals.put(emd.getFieldName(), valList.get(0));
                    vals.put(emd.getFieldName() + "_NOTANALYZED", valListLC.get(0));
                } else {
                    vals.put(emd.getFieldName(), valList);
                    vals.put(emd.getFieldName() + "_NOTANALYZED", valListLC);
                }
            }
            if (emd.getField().getType().equals(MetadataFieldType.DATE)) {
                List<Object> valList = new LinkedList<Object>();
                List<Object> valList1 = new LinkedList<Object>();
                for (ElementMetadataValue emv : emd.getValues()) {
                    Calendar dt = emv.getDate();

                    if (dt != null) {
                        valList.add(df.format(dt.getTime()));
                        valList1.add(dt.getTimeInMillis());
                    }
                }
                vals.put(emd.getFieldName(), valList);
                vals.put(emd.getFieldName() + "_TS", valList1);
            }
            if (emd.getField().getType().equals(MetadataFieldType.SELECT) || emd.getField().getType().equals(MetadataFieldType.CHECKBOX) || emd.getField().getType().equals(MetadataFieldType.RADIO) || emd.getField().getType().equals(MetadataFieldType.EXT_DICTIONARY)) {
                List<Object> valList = new LinkedList<Object>();
                List<Object> valList1 = new LinkedList<Object>();
                List<Object> valListLC = new LinkedList<Object>();
                for (ElementMetadataValue emv : emd.getValues()) {
                    if (emv.getDecode() != null) {
                        valList.add(ElkSimpleElement.getValue(emv.getDecode()));
                        valListLC.add(ElkSimpleElement.getValue(emv.getDecode()).toString().toLowerCase());
                    }
                    if (emv.getCode() != null) {
                        valList1.add(ElkSimpleElement.getValue(emv.getCode()));
                    }
                }
                //mappingTmpl.put(emd.getFieldName() + "_NOTANALYZED", new ElkMapping("string","not_analyzed"));
                if (valList.size() == 0) {
                    vals.put(emd.getFieldName(), null);
                    vals.put(emd.getFieldName() + "_NOTANALYZED", null);
                } else if (valList.size() == 1) {
                    vals.put(emd.getFieldName(), valList.get(0));
                    vals.put(emd.getFieldName() + "_NOTANALYZED", valListLC.get(0));
                } else {
                    vals.put(emd.getFieldName(), valList);
                    vals.put(emd.getFieldName() + "_NOTANALYZED", valListLC);
                }

                if (valList1.size() > 0) {
                    for (Object o : valList1) {
                        if (o instanceof String && o.equals("null")) {
                            valList1.remove(o);
                        }
                        if (o == null) valList1.remove(o);
                    }
                }

                if (valList1.size() > 0) {
                    if (valList1.size() == 1) {
                        if (valList1.get(0) instanceof Double ||
                                valList1.get(0) instanceof Float ||
                                valList1.get(0) instanceof Integer
                        ) {
                            vals.put(emd.getFieldName() + "_CODE", valList1.get(0));
                        }
                        vals.put(emd.getFieldName() + "_CODESTRING", valList1.get(0) + "");

                    } else {
                        Object valueParsed = valList1;
                        if (valueParsed instanceof Double ||
                                valueParsed instanceof Float ||
                                valueParsed instanceof Integer
                        ) {
                            vals.put(emd.getFieldName() + "_CODE", valList1);
                        }
                        vals.put(emd.getFieldName() + "_CODESTRING", valList1 + "");
                    }
                }
            }
            if (emd.getField().getType().equals(MetadataFieldType.ELEMENT_LINK)) {
                List<Object> valList = new LinkedList<Object>();
                List<Object> valList1 = new LinkedList<Object>();
                for (ElementMetadataValue emv : emd.getValues()) {
                    if (emv.getElement_link() != null) {
                        valList.add(emv.getElement_link().getTitleString());
                        valList1.add(emv.getElement_link().getId());
                    }
                }
                //vals.put(emd.getFieldName(), valList);
                if (valList.size() == 0) {
                    vals.put(emd.getFieldName(), null);
                    vals.put(emd.getFieldName() + "_NOTANALYZED", null);
                } else if (valList.size() == 1) {
                    vals.put(emd.getFieldName(), valList.get(0));
                    vals.put(emd.getFieldName() + "_NOTANALYZED", valList.get(0));
                } else {
                    vals.put(emd.getFieldName(), valList);
                    vals.put(emd.getFieldName() + "_NOTANALYZED", valList);
                }
                vals.put(emd.getFieldName() + "_ELID", valList1);
            }
            try {
                smd.addValues(vals);
                templateTmp2.put(emd.getTemplateName(), smd);
            } catch (Exception ex) {

            }
        }
        sel.setMetadata(templateTmp2);
        LinkedList<String> usersList = new LinkedList<String>();
        LinkedList<String> groupsList = new LinkedList<String>();
        for (Acl acl : el.getAcls()) {
            if (acl.getPolicy().isCanView()) {
                for (AclContainer ac : acl.getContainers()) {
                    if (ac.isAuthority()) groupsList.add(ElkService.escape(ac.getContainer()));
                    else usersList.add(ElkService.escape(ac.getContainer()));
                }
            }
        }
        sel.setViewableByUsers(usersList);
        sel.setViewableByGroups(groupsList);
        sel.setCreatedBy(el.getCreateUser());
        sel.setCreatedOn(df.format(el.getCreationDt().getTime()));
        if (el.getPosition() == null) sel.setPosition(0);
        else sel.setPosition(el.getPosition());
        if (el.getLastUpdateUser() != null) {
            sel.setUpdatedBy(el.getLastUpdateUser());
            sel.setUpdatedOn(df.format(el.getLastUpdateDt().getTime()));
        }
        //sel.setMapping(mappingTmpl);
        return sel;
    }

    public String getCreatedOn() {
        return createdOn;
    }

    public void setCreatedOn(String createdOn) {
        this.createdOn = createdOn;
    }

    public String getUpdatedBy() {
        return updatedBy;
    }

    public void setUpdatedBy(String updatedBy) {
        this.updatedBy = updatedBy;
    }

    public String getUpdatedOn() {
        return updatedOn;
    }

    public void setUpdatedOn(String updatedOn) {
        this.updatedOn = updatedOn;
    }

    public static ElkSimpleElement elementToSimpleWithParents(Element el) {
        ElkSimpleElement sel = ElkSimpleElement.elementToSimple(el);
        if (el.getParent() != null) {
            sel.setParent(ElkSimpleElement.elementToSimpleWithParents(el.getParent()));
        }
        return sel;
    }

    public static Object getValue(String value) {
        if (value == null || value.isEmpty()) return "";
        String intPattern = "([0-9]*)";
        boolean match0 = Pattern.matches(intPattern, value);
        if (match0) {
            return Float.parseFloat(value);
        } else {
            try {
                String decimalPattern = "([0-9]*)\\.([0-9]*)";

                boolean match = Pattern.matches(decimalPattern, value);
                if (match) {
                    return Float.parseFloat(value);
                } else {
                    String decimalPatternComma = "([0-9]*),([0-9]*)";
                    if (Pattern.matches(decimalPatternComma, value)) {
                        return Float.parseFloat(value.replace(",", "."));
                    } else {
                        return value;
                    }
                }
            } catch (NumberFormatException ex) {
                return (String) value;
            }
        }
    }

    public void adjustScope(IUser user) {
        Iterator<String> it = this.getMetadata().keySet().iterator();
        List<String> elToRemove = new LinkedList<String>();
        while (it.hasNext()) {
            String tName = it.next();
            Logger.getLogger(this.getClass().getName()).warning("ElementId: "+this.id+" - Inizio imposto entrambe a false");
            boolean groupAuthPassed = false;
            boolean userAuthPassed = false;
            ElkMetadataTemplate mt = this.getMetadata().get(tName);
            if (mt.getViewableByGroups().size() == 0 && mt.getViewableByUsers().size() == 0) {
                Logger.getLogger(this.getClass().getName()).warning("ElementId: "+this.id+" - NON trovo permessi specifici per template "+mt.getName()+", imposto entrambe a true");
                userAuthPassed = true;
                groupAuthPassed = true;
            } else {
                Logger.getLogger(this.getClass().getName()).warning("ElementId: "+this.id+" - TROVO permessi specifici per template "+mt.getName());
                if (mt.getViewableByGroups().size() > 0) {
                    Logger.getLogger(this.getClass().getName()).warning("ElementId: "+this.id+" - ci sono "+mt.getViewableByGroups().size()+" gruppi che hanno visibilità sul template "+mt.getName());
                    for (int i = 0; i < user.getAuthorities().size(); i++) {
                        String authLowerCase = ((List<IAuthority>) user.getAuthorities()).get(i).getAuthority().toLowerCase();
                        Logger.getLogger(this.getClass().getName()).warning("ElementId: "+this.id+" - Ciclo gruppi utente :"+authLowerCase);
                        for (int g=0; g<mt.getViewableByGroups().size(); g++) {
                            String g1=mt.getViewableByGroups().get(g);
                            Logger.getLogger(this.getClass().getName()).warning("ElementId: "+this.id+" - Controllo gruppo "+authLowerCase+" con "+g1.toLowerCase()+" per metadati "+mt.getName());
                            if (g1.toLowerCase().equals(authLowerCase)) {
                                Logger.getLogger(this.getClass().getName()).warning("ElementId: "+this.id+" - Trovo gruppo "+authLowerCase+" per metadati "+mt.getName());
                                groupAuthPassed = true;
                        }
                        }
                    }
                }
                if (mt.getViewableByUsers().size() > 0) {
                    String username = user.getUsername().toLowerCase();
                    for (int u=0;u<mt.getViewableByUsers().size();u++) {
                        String u1 = mt.getViewableByUsers().get(u).toLowerCase();
                        Logger.getLogger(this.getClass().getName()).warning("ElementId: "+this.id+" - Trovo permessi a livello di utente "+u1+" per metadati "+mt.getName());
                        if (u1.equals(username) || u1.equals("all_users") || u1.equals("*")) {
                            Logger.getLogger(this.getClass().getName()).warning("ElementId: "+this.id+" - Trovo utente "+username+" o all_users o * per metadati "+mt.getName());
                            userAuthPassed = true;
                    }
                    }
                }
            }
            if (!userAuthPassed && !groupAuthPassed) {
                Logger.getLogger(this.getClass().getName()).warning("ElementId: "+this.id+" - entrambi i flag gruppo e utenti falsi rimuovo metadati");
                elToRemove.add(tName);

            }
        }
        for (String tName : elToRemove) {
            this.getMetadata().remove(tName);
        }

    }

    /*
    public HashMap<String, ElkMapping> getMapping() {
        return mapping;
    }

    public void setMapping(HashMap<String, ElkMapping> mapping) {
        this.mapping = mapping;
    }
    */

}
