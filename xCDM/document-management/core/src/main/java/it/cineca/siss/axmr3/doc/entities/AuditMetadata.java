package it.cineca.siss.axmr3.doc.entities;

import it.cineca.siss.axmr3.doc.entities.base.BaseMetadata;
import org.codehaus.jackson.annotate.JsonIgnore;

import javax.persistence.*;
import java.util.Calendar;
import java.util.LinkedList;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 09/09/13
 * Time: 12.00
 * To change this template use File | Settings | File Templates.
 */
@Entity
@Table (name = "DOC_AUDIT_MD")
public class AuditMetadata extends BaseMetadata<AuditValue, MetadataField> {



    @OneToOne(fetch = FetchType.EAGER)
    @JoinColumn(name = "FIELD_ID")
    private MetadataField field;
    @Column (name="USERNAME")
    private String username;
    @Temporal(value = TemporalType.TIMESTAMP)
    @Column (name="MOD_DT")
    private Calendar modDt;
    @Column (name="ACTION")
    private String action;
    @OneToOne(fetch = FetchType.EAGER)
    @JoinColumn(name = "TEMPLATE_ID")
    private MetadataTemplate template;
    @OneToOne(fetch = FetchType.EAGER)
    @JoinColumn(name = "DM_SESSION_ID", nullable = true)
    private DataManagementSession dmSession;
    @OneToOne(fetch = FetchType.EAGER)
    @JoinColumn(name = "DM_ACTION_ID", nullable = true)
    private DataManagementAction dmAction;


    @JsonIgnore
    public DataManagementAction getDmAction() {
        return dmAction;
    }

    public Long getDmActionId(){
        return this.dmAction.getId();
    }
    public void setDmAction(DataManagementAction dmAction) {
        this.dmAction = dmAction;
    }

    @JsonIgnore
    public MetadataField getField() {
        return field;
    }
    public String getFieldName() {
        return field.getName();
    }

    public Long getFieldId() {
        return field.getId();
    }

    public void setField(MetadataField field) {
        this.field = field;
    }

    @JsonIgnore
    public DataManagementSession getDmSession() {
        return dmSession;
    }

    public void setDmSession(DataManagementSession dmSession) {
        this.dmSession = dmSession;
    }

    public String getTemplateName(){
        return template.getName();
    }

    public Long getTemplateId(){
        return template.getId();
    }

    @JsonIgnore
    public MetadataTemplate getTemplate() {
        return template;
    }

    public void setTemplate(MetadataTemplate template) {
        this.template = template;
    }

    public String getAction() {
        return action;
    }

    public void setAction(String action) {
        this.action = action;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public Calendar getModDt() {
        return modDt;
    }

    public void setModDt(Calendar modDt) {
        this.modDt = modDt;
    }

    @Override
    @JsonIgnore
    public AuditValue getMetadataValueInstance() {
        return new AuditValue();
    }

    public List<Object> getNewVals(){
        LinkedList<Object> ret=new LinkedList<Object>();
        for (AuditValue v:this.getValues()){
            if (!v.isOld()) ret.add(v.getValue(this.getField().getType()));
        }
        return ret;
    }

    public List<Object> getOldVals(){
        LinkedList<Object> ret=new LinkedList<Object>();
        for (AuditValue v:this.getValues()){
            if (v.isOld()) ret.add(v.getValue(this.getField().getType()));
        }
        return ret;
    }

    public String getTemplateFieldName(){
        return this.getTemplateName()+"_"+this.getFieldName();
    }

}
