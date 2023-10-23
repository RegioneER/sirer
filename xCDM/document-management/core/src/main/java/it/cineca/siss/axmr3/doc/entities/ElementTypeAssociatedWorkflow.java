package it.cineca.siss.axmr3.doc.entities;

import org.codehaus.jackson.annotate.JsonIgnore;

import javax.persistence.*;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 11/09/13
 * Time: 10.53
 * To change this template use File | Settings | File Templates.
 */
@Entity
@Table (name = "DOC_TYPE_WF")
public class ElementTypeAssociatedWorkflow extends BaseModelEntity {

    @ManyToOne
    @JoinColumn(name = "TYPE_ID", nullable = false)
    private ElementType type;
    @Column(name = "PROCESS_KEY", nullable = false)
    private String processKey;
    @Column(name="ENABLED")
    private boolean enabled;
    @Column(name="START_ON_CREATE")
    private boolean startOnCreate;
    @Column(name="START_ON_UPDATE")
    private boolean startOnUpdate;

    @JsonIgnore
    public ElementType getType() {
        return type;
    }

    public void setType(ElementType type) {
        this.type = type;
    }

    public boolean isStartOnDelete() {
        return startOnDelete;
    }

    public void setStartOnDelete(boolean startOnDelete) {
        this.startOnDelete = startOnDelete;
    }

    public boolean isStartOnUpdate() {
        return startOnUpdate;
    }

    public void setStartOnUpdate(boolean startOnUpdate) {
        this.startOnUpdate = startOnUpdate;
    }

    @Column(name="START_ON_DELETE")
    private boolean startOnDelete;

    public boolean isStartOnCreate() {
        return startOnCreate;
    }

    public void setStartOnCreate(boolean startOnCreate) {
        this.startOnCreate = startOnCreate;
    }

    public boolean isEnabled() {
        return enabled;
    }

    public void setEnabled(boolean enabled) {
        this.enabled = enabled;
    }

    public String getProcessKey() {
        return processKey;
    }

    public void setProcessKey(String processKey) {
        this.processKey = processKey;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        //if (!super.equals(o)) return false;

        ElementTypeAssociatedWorkflow that = (ElementTypeAssociatedWorkflow) o;

        if (enabled != that.enabled) return false;
        if (startOnCreate != that.startOnCreate) return false;
        if (startOnDelete != that.startOnDelete) return false;
        if (startOnUpdate != that.startOnUpdate) return false;
        if (processKey != null ? !processKey.equals(that.processKey) : that.processKey != null) return false;
        //if (type != null ? !type.equals(that.type) : that.type != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = super.hashCode();
        result = 31 * result + (type != null ? type.hashCode() : 0);
        result = 31 * result + (processKey != null ? processKey.hashCode() : 0);
        result = 31 * result + (enabled ? 1 : 0);
        result = 31 * result + (startOnCreate ? 1 : 0);
        result = 31 * result + (startOnUpdate ? 1 : 0);
        result = 31 * result + (startOnDelete ? 1 : 0);
        return result;
    }
}
