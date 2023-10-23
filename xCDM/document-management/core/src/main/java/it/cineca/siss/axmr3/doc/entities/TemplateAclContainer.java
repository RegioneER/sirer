package it.cineca.siss.axmr3.doc.entities;

import org.codehaus.jackson.annotate.JsonIgnore;

import javax.persistence.*;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 18/11/13
 * Time: 10:22
 * To change this template use File | Settings | File Templates.
 */
@Entity
@Table(name = "DOC_TPL_ACL_CONTAINER")
public class TemplateAclContainer extends BaseAclEntity{

    @ManyToOne
    @JoinColumn(name = "ACL_ID", nullable = true)
    private TemplateAcl acl;
    @Column(name = "AUTHORITY", nullable = false)
    private boolean authority;
    @Column(name = "CONTAINER", nullable = false)
    private String container;

    @JsonIgnore
    public TemplateAcl getAcl() {
        return acl;
    }

    public void setAcl(TemplateAcl acl) {
        this.acl = acl;
    }

    public String getContainer() {
        return container;
    }

    public void setContainer(String container) {
        this.container = container;
    }

    public boolean isAuthority() {
        return authority;
    }

    public void setAuthority(boolean authority) {
        this.authority = authority;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof TemplateAclContainer)) return false;
        //if (!super.equals(o)) return false;

        TemplateAclContainer that = (TemplateAclContainer) o;

        if (authority != that.authority) return false;
        if (!container.equals(that.container)) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = super.hashCode();
        result = 31 * result + (authority ? 1 : 0);
        result = 31 * result + container.hashCode();
        return result;
    }

}
