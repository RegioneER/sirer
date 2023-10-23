package it.cineca.siss.axmr3.doc.entities;

import it.cineca.siss.axmr3.doc.acl.TemplatePolicy;
import org.codehaus.jackson.annotate.JsonIgnore;

import javax.persistence.*;
import java.util.Collection;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 18/11/13
 * Time: 10:15
 * To change this template use File | Settings | File Templates.
 */
@Entity
@Table (name = "DOC_TPL_ACL")
public class TemplateAcl extends BaseAclEntity{

    @OneToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "ELEMENT_TEMPLATE_ID", nullable = true)
    private ElementTemplate elementTemplate;
    @OneToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "ELEMENT_TYPE_ASSOC_TPL_ID", nullable = true)
    private ElementTypeAssociatedTemplate elementTypeAssociatedTemplate;
    @Column(name="POLICY_VALE",nullable = true)
    private Integer policyValue;
    @Column (name="POSITIONAL_ACE")
    private String positionalAce;
    @OneToMany(fetch = FetchType.EAGER)
    @JoinColumn(name = "ACL_ID")
    private Collection<TemplateAclContainer> containers;

    public String getPositionalAce() {
        return positionalAce;
    }

    public void setPositionalAce(String positionalAce) {
        this.positionalAce = positionalAce;
    }

    public TemplatePolicy getPolicy(){
        return new TemplatePolicy(policyValue);
    }

    public Collection<TemplateAclContainer> getContainers() {
        return containers;
    }

    public void setContainers(Collection<TemplateAclContainer> containers) {
        this.containers = containers;
    }

    public Integer getPolicyValue() {
        return policyValue;
    }

    public void setPolicyValue(Integer policyValue) {
        this.policyValue = policyValue;
        this.positionalAce=Integer.toBinaryString(policyValue);
    }

    @JsonIgnore
    public ElementTemplate getElementTemplate() {
        return elementTemplate;
    }

    public void setElementTemplate(ElementTemplate elementTemplate) {
        this.elementTemplate = elementTemplate;
    }

    @JsonIgnore
    public ElementTypeAssociatedTemplate getElementTypeAssociatedTemplate() {
        return elementTypeAssociatedTemplate;
    }

    public void setElementTypeAssociatedTemplate(ElementTypeAssociatedTemplate elementTypeAssociatedTemplate) {
        this.elementTypeAssociatedTemplate = elementTypeAssociatedTemplate;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        //if (!super.equals(o)) return false;

        TemplateAcl that = (TemplateAcl) o;

        if (!containers.equals(that.containers)) return false;
        if (elementTemplate != null ? !elementTemplate.equals(that.elementTemplate) : that.elementTemplate != null)
            return false;
        if (elementTypeAssociatedTemplate != null ? !elementTypeAssociatedTemplate.equals(that.elementTypeAssociatedTemplate) : that.elementTypeAssociatedTemplate != null)
            return false;
        if (!policyValue.equals(that.policyValue)) return false;
        if (positionalAce != null ? !positionalAce.equals(that.positionalAce) : that.positionalAce != null)
            return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = super.hashCode();
        result = 31 * result + (elementTemplate != null ? elementTemplate.hashCode() : 0);
        result = 31 * result + (elementTypeAssociatedTemplate != null ? elementTypeAssociatedTemplate.hashCode() : 0);
        result = 31 * result + policyValue.hashCode();
        result = 31 * result + (positionalAce != null ? positionalAce.hashCode() : 0);
        result = 31 * result + containers.hashCode();
        return result;
    }
}
