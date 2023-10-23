package it.cineca.siss.axmr3.doc.json;

import it.cineca.siss.axmr3.doc.entities.AuditMetadata;
import it.cineca.siss.axmr3.doc.entities.DataManagementAction;

import java.util.LinkedList;
import java.util.List;

/**
 * Created by vmazzeo on 13/01/2016.
 */
public class DmActionJSON {

    private DataManagementAction action;
    private List<AuditMetadata> actionMdAudit;

    public DmActionJSON(DataManagementAction action) {
        this.action = action;
    }

    public Long getActionId() {
        return action.getId();
    }

    public DataManagementAction getAction() {
        return action;
    }

    public void setAction(DataManagementAction action) {
        this.action = action;
    }

    public List<AuditMetadata> getActionMdAudit() {
        return actionMdAudit;
    }

    public void setActionMdAudit(List<AuditMetadata> actionMdAudit) {
        this.actionMdAudit = actionMdAudit;
    }

    public void addMdAudit(AuditMetadata amd){
        if (actionMdAudit==null) {
            actionMdAudit=new LinkedList<AuditMetadata>();
        }
        actionMdAudit.add(amd);
    }

}
