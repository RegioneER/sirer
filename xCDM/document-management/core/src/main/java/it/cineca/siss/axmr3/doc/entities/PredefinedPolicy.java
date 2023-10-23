package it.cineca.siss.axmr3.doc.entities;

import it.cineca.siss.axmr3.doc.acl.Policy;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Table;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 29/08/13
 * Time: 11.24
 * To change this template use File | Settings | File Templates.
 */
@Entity
@Table (name = "DOC_POLICY")
public class PredefinedPolicy extends BaseModelEntity {

    @Column(name="NAME")
    private String name;
    @Column (name="DESCRIPTION")
    private String description;
    @Column (name="POLICY_VALUE")
    private int policyValue;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof PredefinedPolicy)) return false;
        if (!super.equals(o)) return false;

        PredefinedPolicy that = (PredefinedPolicy) o;

        if (policyValue != that.policyValue) return false;
        if (description != null ? !description.equals(that.description) : that.description != null) return false;
        if (name != null ? !name.equals(that.name) : that.name != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = super.hashCode();
        result = 31 * result + (name != null ? name.hashCode() : 0);
        result = 31 * result + (description != null ? description.hashCode() : 0);
        result = 31 * result + policyValue;
        return result;
    }

    public String getDescription() {

        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getPolicyValue() {
        return policyValue;
    }

    public void setPolicyValue(int policyValue) {
        this.policyValue = policyValue;
    }

    public Policy getPolicy(){
        return new Policy(this.policyValue);
    }
}
