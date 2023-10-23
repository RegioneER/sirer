package it.cineca.siss.axmr3.doc.entities;

import it.cineca.siss.axmr3.doc.acl.Policy;
import org.codehaus.jackson.annotate.JsonIgnore;

import javax.persistence.*;
import java.util.Collection;
import java.util.HashMap;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 29/08/13
 * Time: 11.28
 * To change this template use File | Settings | File Templates.
 */
@Entity
@Table(name = "DOC_ACL")
public class Acl extends BaseAclEntity {

    @OneToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "TYPE_ID", nullable = true)
    private ElementType type;
    @OneToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "ELEMENT_ID", nullable = true)
    private Element element;
    @OneToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "PREDIFINED_POLICY_ID", nullable = true)
    private PredefinedPolicy predifinedPolicy;
    @Column(name = "POLICY_VALE", nullable = true)
    private Integer policyValue;
    @Column(name = "POSITIONAL_ACE")
    private String positionalAce;
    @OneToMany(fetch = FetchType.EAGER)
    @JoinColumn(name = "ACL_DI")
    private Collection<AclContainer> containers;
    @Column(name = "TEMPLATE_FTL", nullable = true)
    private String detailTemplate;
    @Column(name = "ID_REF", nullable = true)
    private Long idRef;


    public Long getIdRef() {
        return idRef;
    }

    public void setIdRef(Long idRef) {
        this.idRef = idRef;
    }

    public String getDetailTemplate() {
        return detailTemplate;
    }

    public void setDetailTemplate(String detailTemplate) {
        this.detailTemplate = detailTemplate;
    }

    public String getPositionalAce() {
        return positionalAce;
    }

    public void setPositionalAce(String positionalAce) {
        this.positionalAce = positionalAce;
    }

    public Policy getPolicy() {
        if (predifinedPolicy == null) return new Policy(policyValue);
        else return predifinedPolicy.getPolicy();
    }

    public Collection<AclContainer> getContainers() {
        return containers;
    }

    public void setContainers(Collection<AclContainer> containers) {
        this.containers = containers;
    }

    @JsonIgnore
    public Element getElement() {
        return element;
    }

    public void setElement(Element element) {
        this.element = element;
    }

    public Integer getPolicyValue() {
        return policyValue;
    }

    public void setPolicyValue(Integer policyValue) {
        this.policyValue = policyValue;
        this.positionalAce = Integer.toBinaryString(policyValue);
    }

    @JsonIgnore
    public PredefinedPolicy getPredifinedPolicy() {
        return predifinedPolicy;
    }

    public void setPredifinedPolicy(PredefinedPolicy predifinedPolicy) {
        this.predifinedPolicy = predifinedPolicy;
    }

    public HashMap<String, String> getPredPolicy() {
        if (predifinedPolicy == null) return null;
        HashMap<String, String> ret = new HashMap<String, String>();
        ret.put("id", predifinedPolicy.getId() + "");
        ret.put("name", predifinedPolicy.getName());
        return ret;
    }

    @JsonIgnore
    public ElementType getType() {
        return type;
    }

    public void setType(ElementType type) {
        this.type = type;
    }

    @Override
    public String toString() {
        return "Acl{" +
                "type=" + type +
                ", element=" + element +
                ", predifinedPolicy=" + predifinedPolicy +
                ", policyValue=" + policyValue +
                ", positionalAce='" + positionalAce + '\'' +
                ", containers=" + containers +
                ", detailTemplate='" + detailTemplate + '\'' +
                ", idRef=" + idRef +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        //if (!super.equals(o)) return false;

        Acl acl = (Acl) o;

        if (containers != null ? !containers.equals(acl.containers) : acl.containers != null) return false;
        if (detailTemplate != null ? !detailTemplate.equals(acl.detailTemplate) : acl.detailTemplate != null)
            return false;
        if (element != null ? !element.equals(acl.element) : acl.element != null) return false;
        if (idRef != null ? !idRef.equals(acl.idRef) : acl.idRef != null) return false;
        if (!policyValue.equals(acl.policyValue)) return false;
        if (positionalAce != null ? !positionalAce.equals(acl.positionalAce) : acl.positionalAce != null) return false;
        if (predifinedPolicy != null ? !predifinedPolicy.equals(acl.predifinedPolicy) : acl.predifinedPolicy != null)
            return false;
        if (type != null ? !type.equals(acl.type) : acl.type != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = super.hashCode();
        result = 31 * result + (type != null ? type.hashCode() : 0);
        result = 31 * result + (element != null ? element.hashCode() : 0);
        result = 31 * result + (predifinedPolicy != null ? predifinedPolicy.hashCode() : 0);
        result = 31 * result + policyValue.hashCode();
        result = 31 * result + (containers != null ? containers.hashCode() : 0);
        result = 31 * result + (detailTemplate != null ? detailTemplate.hashCode() : 0);
        result = 31 * result + (idRef != null ? idRef.hashCode() : 0);
        return result;
    }
}
