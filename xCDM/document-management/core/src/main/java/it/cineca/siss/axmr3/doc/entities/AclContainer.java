package it.cineca.siss.axmr3.doc.entities;

import org.codehaus.jackson.annotate.JsonIgnore;

import javax.persistence.*;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 29/08/13
 * Time: 11.48
 * To change this template use File | Settings | File Templates.
 */
@Entity
@Table (name = "DOC_ACL_CONTAINER")
public class AclContainer extends BaseAclEntity{

    @ManyToOne
    @JoinColumn(name = "ACL_DI", nullable = true)
    private Acl acl;

    @JsonIgnore
    public Acl getAcl() {
        return acl;
    }

    public void setAcl(Acl acl) {
        this.acl = acl;
    }

    @Column(name = "AUTHORITY", nullable = false)
    private boolean authority;
    @Column(name = "CONTAINER", nullable = false)
    private String container;

    @Override
    public String toString() {
        return "AclContainer{" +
                "authority=" + authority +
                ", container='" + container + '\'' +
                '}';
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
        if (!(o instanceof AclContainer)) return false;
        if (!super.equals(o)) return false;

        AclContainer that = (AclContainer) o;

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
