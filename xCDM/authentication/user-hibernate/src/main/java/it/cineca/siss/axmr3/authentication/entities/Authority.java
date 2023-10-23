package it.cineca.siss.axmr3.authentication.entities;

import it.cineca.siss.axmr3.authentication.IAuthority;
import it.cineca.siss.axmr3.authentication.IUser;
import org.codehaus.jackson.annotate.JsonIgnore;
import org.springframework.security.core.GrantedAuthority;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Collection;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 31/05/13
 * Time: 10.57
 * To change this template use File | Settings | File Templates.
 */
@Entity
@Table(name = "AUTHORITIES",uniqueConstraints = {
        @UniqueConstraint(columnNames = {"AUTH"})
})
public class Authority implements IAuthority {

    @Id @GeneratedValue
    @Column (name="ID")
    private Long id;
    @Column (name="AUTH")
    private String authority;
    @Column (name="DESCRIPTION")
    private String description;
    @ManyToMany(fetch = FetchType.LAZY)
    @JoinTable (name = "USERS_AUTHORITIES")
    private Collection<User> users;


    @JsonIgnore
    public Collection<User> getUsers() {
        return users;
    }

    public void setUsers(Collection<? extends IUser> users) {
        this.users = (Collection<User>) users;
    }

    public String getAuthority() {
        return authority;
    }

    public void setAuthority(String authority) {
        this.authority = authority;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public Long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    @Override
    public String toString() {
        return "it.cineca.siss.axmr3.authentication.entities.Authority{" +
                "authority='" + authority + '\'' +
                ", id=" + id +
                ", description='" + description + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Authority)) return false;

        Authority authority1 = (Authority) o;

        if (id != authority1.id) return false;
        if (!authority.equals(authority1.authority)) return false;
        if (description != null ? !description.equals(authority1.description) : authority1.description != null)
            return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = (int) (id ^ (id >>> 32));
        result = 31 * result + authority.hashCode();
        result = 31 * result + (description != null ? description.hashCode() : 0);
        return result;
    }
}
