package it.cineca.siss.axmr3.doc.utils;

import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.authentication.services.SissUserService;
import it.cineca.siss.axmr3.doc.entities.AuditMetadata;
import it.cineca.siss.axmr3.doc.entities.AuditValue;
import it.cineca.siss.axmr3.doc.entities.Element;

import java.util.Calendar;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by Carlo on 27/03/2017.
 */
public class AuditJSON {

    protected Calendar auditDate;
    protected Long auditId;
    protected List<Object> oldValues;
    protected List<Object> newValues;
    protected String dataType;
    protected String actionType;
    protected String userid;
    protected String userFullName;
    protected String templateFieldName;

    public String getUserFullName() {
        return userFullName;
    }

    public void setUserFullName(String userFullName) {
        this.userFullName = userFullName;
    }

    public String getUserid() {
        return userid;
    }

    public void setUserid(String userid) {
        this.userid = userid;
    }

    public String getActionType() {
        return actionType;
    }

    public void setActionType(String actionType) {
        this.actionType = actionType;
    }

    public String getDataType() {
        return dataType;
    }

    public void setDataType(String dataType) {
        this.dataType = dataType;
    }

    public AuditJSON(AuditMetadata amd, SissUserService uservice){
        auditDate=amd.getModDt();
        auditId=amd.getId();
        actionType=amd.getAction();
        userid=amd.getUsername();
        templateFieldName = amd.getTemplateFieldName();
        if (amd.getDmAction()!=null){
            userid="Data Manager";
            userFullName="Data Manager";
            actionType="Data management session: "+amd.getDmAction().getDmSession().getId()+" ("+amd.getDmAction().getDmSession().getIssueCode()+")";
        }else {
            IUser user = uservice.getUser(userid);
            if (user!=null) {
                userFullName=user.getFirstName()+" "+user.getLastName();
            }
        }
        dataType=amd.getField().getType().name();
        for (Object val:amd.getOldVals()){
            if (oldValues==null) oldValues=new LinkedList<Object>();
            if (val instanceof Element){
                oldValues.add(((Element) val).getId()+"###"+((Element) val).getTitleString());
            }else {
            oldValues.add(val);
        }

        }
        for (Object val:amd.getNewVals()){
            if (newValues==null) newValues=new LinkedList<Object>();
            if (val instanceof Element){
                newValues.add(((Element) val).getId()+"###"+((Element) val).getTitleString());
            }else {
            newValues.add(val);
        }
    }
    }

    public Calendar getAuditDate() {
        return auditDate;
    }

    public void setAuditDate(Calendar auditDate) {
        this.auditDate = auditDate;
    }

    public Long getAuditId() {
        return auditId;
    }

    public void setAuditId(Long auditId) {
        this.auditId = auditId;
    }

    public List<Object> getOldValues() {
        return oldValues;
    }

    public void setOldValues(List<Object> oldValues) {
        this.oldValues = oldValues;
    }

    public List<Object> getNewValues() {
        return newValues;
    }

    public void setNewValues(List<Object> newValues) {
        this.newValues = newValues;
    }

    public String getTemplateFieldName() {
        return templateFieldName;
    }

    public void setTemplateFieldName(String templateFieldName) {
        this.templateFieldName = templateFieldName;
    }
}
