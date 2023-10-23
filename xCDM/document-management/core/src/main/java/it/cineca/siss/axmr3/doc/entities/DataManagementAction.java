package it.cineca.siss.axmr3.doc.entities;

import org.codehaus.jackson.annotate.JsonIgnore;

import javax.persistence.*;
import java.util.Calendar;

/**
 * Created by cin0562a on 06/10/15.
 */
@Entity
@Table(name = "DOC_DM_ACTION")
public class DataManagementAction extends BaseDMActionEntity {

    @ManyToOne
    @JoinColumn(name="DM_SESSION_ID")
    private DataManagementSession dmSession;
    @Column(name="ACTION_TYPE")
    private String action;
    @ManyToOne
    @JoinColumn(name="OBJ_ID")
    private Element objId;
    @Temporal(value = TemporalType.TIMESTAMP)
    @Column (name="ACT_DT")
    private Calendar actionDt;
    @Lob
    @Column(name="ACTION_SPEC")
    private String specification;


    @JsonIgnore
    public DataManagementSession getDmSession() {
        return dmSession;
    }

    public void setDmSession(DataManagementSession dmSession) {
        this.dmSession = dmSession;
    }

    public String getAction() {
        return action;
    }

    public void setAction(String action) {
        this.action = action;
    }

    @JsonIgnore
    public Element getObjId() {
        return objId;
    }

    public Long getElementId(){
        return objId.getId();
    }

    public void setObjId(Element objId) {
        this.objId = objId;
    }

    public Calendar getActionDt() {
        return actionDt;
    }

    public void setActionDt(Calendar actionDt) {
        this.actionDt = actionDt;
    }

    public String getSpecification() {
        return specification;
    }

    public void setSpecification(String specification) {
        this.specification = specification;
    }
}
