package it.cineca.siss.axmr3.doc.controls.json;

import java.io.Serializable;

/**
 * Created by Carlo on 12/09/2016.
 */
public class CriteriaContainer implements Serializable{


    protected EmptyAndHideCriteria empty;
    protected StdCriteria disable;
    protected StdCriteria mandatory;
    protected StdCriteria confirm;
    protected StdCriteria warning;
    protected StdCriteria validity;

    public EmptyAndHideCriteria getEmpty() {
        return empty;
    }

    public void setEmpty(EmptyAndHideCriteria empty) {
        this.empty = empty;
    }

    public StdCriteria getDisable() {
        return disable;
    }

    public void setDisable(StdCriteria disable) {
        this.disable = disable;
    }

    public StdCriteria getMandatory() {
        return mandatory;
    }

    public void setMandatory(StdCriteria mandatory) {
        this.mandatory = mandatory;
    }

    public StdCriteria getConfirm() {
        return confirm;
    }

    public void setConfirm(StdCriteria confirm) {
        this.confirm = confirm;
    }

    public StdCriteria getWarning() {
        return warning;
    }

    public void setWarning(StdCriteria warning) {
        this.warning = warning;
    }

    public StdCriteria getValidity() {
        return validity;
    }

    public void setValidity(StdCriteria validity) {
        this.validity = validity;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        CriteriaContainer that = (CriteriaContainer) o;

        if (empty != null ? !empty.equals(that.empty) : that.empty != null) return false;
        if (disable != null ? !disable.equals(that.disable) : that.disable != null) return false;
        if (mandatory != null ? !mandatory.equals(that.mandatory) : that.mandatory != null) return false;
        if (confirm != null ? !confirm.equals(that.confirm) : that.confirm != null) return false;
        if (warning != null ? !warning.equals(that.warning) : that.warning != null) return false;
        return validity != null ? validity.equals(that.validity) : that.validity == null;

    }

    @Override
    public int hashCode() {
        int result = empty != null ? empty.hashCode() : 0;
        result = 31 * result + (disable != null ? disable.hashCode() : 0);
        result = 31 * result + (mandatory != null ? mandatory.hashCode() : 0);
        result = 31 * result + (confirm != null ? confirm.hashCode() : 0);
        result = 31 * result + (warning != null ? warning.hashCode() : 0);
        result = 31 * result + (validity != null ? validity.hashCode() : 0);
        return result;
    }
}
