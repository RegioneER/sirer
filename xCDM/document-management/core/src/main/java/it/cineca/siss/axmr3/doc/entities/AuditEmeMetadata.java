package it.cineca.siss.axmr3.doc.entities;

import it.cineca.siss.axmr3.doc.entities.base.BaseMetadata;
import org.codehaus.jackson.annotate.JsonIgnore;

import javax.persistence.*;
import java.util.Calendar;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by lverri on 12/09/2018.
 */


@Entity
@Table(name = "DOC_AUDIT_EME")
public class AuditEmeMetadata extends BaseMetadata<AuditEmeValue, MetadataField>{



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
    @JoinColumn(name = "EME_ID", nullable = true)
    private EmendamentoSession emeSession;
    @OneToOne(fetch = FetchType.EAGER)
    @JoinColumn(name = "EME_ACTION_ID", nullable = true)
    private EmendamentoAction emeAction;


    @JsonIgnore
    public EmendamentoAction getDmAction() {
        return emeAction;
    }

    public Long getEmeActionId(){
        return this.emeAction.getId();
    }
    public void setEmeAction(EmendamentoAction emeAction) {
        this.emeAction = emeAction;
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
    public EmendamentoSession getEmendamento() {
        return emeSession;
    }

    public void setEmendamento(EmendamentoSession emeSession) {
        this.emeSession = emeSession;
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
    public AuditEmeValue getMetadataValueInstance() {
        return new AuditEmeValue();
    }

    public List<Object> getNewVals(){
        LinkedList<Object> ret=new LinkedList<Object>();
        for (AuditEmeValue v:this.getValues()){
            if (!v.isOld()) ret.add(v.getValue(this.getField().getType()));
        }
        return ret;
    }

    public List<Object> getOldVals(){
        LinkedList<Object> ret=new LinkedList<Object>();
        for (AuditEmeValue v:this.getValues()){
            if (v.isOld()) ret.add(v.getValue(this.getField().getType()));
        }
        return ret;
    }

}
