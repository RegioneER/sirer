package it.cineca.siss.axmr3.doc.controls.json;

import java.io.Serializable;
import java.util.List;

/**
 * Created by Carlo on 12/09/2016.
 */
public class SubmitButton implements Serializable {

    protected String name;
    protected List<String> fields;
    protected String label;
    protected String faIcon;
    protected Integer[] bkgrgb;
    protected Integer[] txtrgb;
    protected String[] forms;

    public String getLabel() {
        return label;
    }

    public String[] getForms() {
        return forms;
    }

    public void setForms(String[] forms) {
        this.forms = forms;
    }

    public void setLabel(String label) {
        this.label = label;
    }

    public String getFaIcon() {
        return faIcon;
    }

    public void setFaIcon(String faIcon) {
        this.faIcon = faIcon;
    }

    public Integer[] getBkgrgb() {
        return bkgrgb;
    }

    public void setBkgrgb(Integer[] bkgrgb) {
        this.bkgrgb = bkgrgb;
    }

    public Integer[] getTxtrgb() {
        return txtrgb;
    }

    public void setTxtrgb(Integer[] txtrgb) {
        this.txtrgb = txtrgb;
    }

    public SubmitButton(String name, List<String> fields) {
        this.name = name;
        this.fields = fields;
    }

    public SubmitButton() {
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public List<String> getFields() {
        return fields;
    }

    public void setFields(List<String> fields) {
        this.fields = fields;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        SubmitButton that = (SubmitButton) o;

        if (name != null ? !name.equals(that.name) : that.name != null) return false;
        return fields != null ? fields.equals(that.fields) : that.fields == null;

    }

    @Override
    public int hashCode() {
        int result = name != null ? name.hashCode() : 0;
        result = 31 * result + (fields != null ? fields.hashCode() : 0);
        return result;
    }
}
