package it.cineca.siss.axmr3.authentication.entities;

import it.cineca.siss.axmr3.authentication.IAuthority;
import it.cineca.siss.axmr3.authentication.IUser;
import org.codehaus.jackson.annotate.JsonIgnore;
import org.hibernate.annotations.Fetch;
import org.hibernate.annotations.FetchMode;
import org.hibernate.annotations.LazyCollection;
import org.hibernate.annotations.LazyCollectionOption;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.userdetails.UserDetails;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Collection;
import java.util.LinkedList;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 31/05/13
 * Time: 10.55
 * To change this template use File | Settings | File Templates.
 */
@Entity
@Table(name="USERS",uniqueConstraints = {
        @UniqueConstraint(columnNames = {"USERNAME"})
})
public class User implements IUser {
    @Id @GeneratedValue
    @Column (name="ID")
    private Long id;
    @Column (name="USERNAME")
    private String username;
    @Column (name="PASSWORD")
    private String password;
    @Column (name="NOT_EXPIRED")
    private boolean accountNonExpired;
    @Column (name="NOT_LOCKED")
    private boolean accountNonLocked;
    @Column (name="CRED_NOT_EXPIRED")
    private boolean credentialsNonExpired;
    @Column (name="ENABLED")
    private boolean enabled;
    @ManyToMany(fetch = FetchType.EAGER)
    private Collection<Authority> authorities;
    @Column (name="FIRST_NAME") private String firstName;
    @Column (name="LAST_NAME") private String lastName;
    @Column (name="EMAIL") private String email;
    private String ente;
    @Transient
    private Long emeSessionId;
    @Transient
    private Long emeRootElementId;

    private String loggedUserid;

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public Collection<Authority> getAuthorities() {
        return authorities;
    }

    public void setAuthorities(Collection<?extends IAuthority> authorities) {
        this.authorities = (Collection<Authority>) authorities;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getPassword() {
        return this.password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getUsername() {
        return this.username;
    }

    public Long getEmeSessionId()  {
        return emeSessionId;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public void setEmeSessionId(Long emeSessionId) {
        this.emeSessionId = emeSessionId;
    }

    public void setEmeRootElementId(Long emeRootElementId) {
        this.emeRootElementId = emeRootElementId;
    }

    public Long getEmeRootElementId()  {
        return emeRootElementId;
    }

    public boolean isAccountNonExpired() {
        return this.accountNonExpired;
    }

    public void setAccountNonExpired(boolean accountNonExpired) {

        this.accountNonExpired = accountNonExpired;
    }

    public boolean isAccountNonLocked() {
        return this.accountNonLocked;
    }

    public void setAccountNonLocked(boolean accountNonLocked) {
        this.accountNonLocked = accountNonLocked;
    }

    public boolean isCredentialsNonExpired() {
        return this.credentialsNonExpired;
    }

    public void setCredentialsNonExpired(boolean credentialsNonExpired) {
        this.credentialsNonExpired = credentialsNonExpired;
    }

    public boolean isEnabled() {
        return this.enabled;
    }

    public void setEnabled(boolean enabled) {
        this.enabled = enabled;
    }

    public Long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof User)) return false;

        User user = (User) o;

        if (!username.equals(user.username)) return false;

        return true;
    }

    @Override
    public int hashCode() {
        return username.hashCode();
    }

    @Override
    public String toString() {
        return "it.cineca.siss.axmr3.authentication.entities.User{" +
                "accountNonExpired=" + accountNonExpired +
                ", id=" + id +
                ", username='" + username + '\'' +
                ", password='" + password + '\'' +
                ", accountNonLocked=" + accountNonLocked +
                ", credentialsNonExpired=" + credentialsNonExpired +
                ", enabled=" + enabled +
                ", authorities=" + getAuthorities() +
                '}';
    }

    public boolean hasRole(String roleName) {
        boolean hasRole=false;
        for (Authority a:getAuthorities()){
            if (a.getAuthority().equals(roleName)){
                hasRole=true;
            }
        }
        return hasRole;
    }

    public void setEnte(String ente) {
        this.ente=ente;
    }

    public String getEnte() {
        return this.ente;
    }

    @Override
    public List<Integer> getSitesID() {
        return null;
    }

    @Override
    public Integer getFirstSiteID() {
        return null;
    }

    @Override
    public List<String> getSitesCodes() {
        return null;
    }

    @Override
    public String getFirstSiteCode() {
        return null;
    }

    @Override
    public List<String> getUoCodes() {
        return null;
    }

    public void fromUserDetails(UserDetails ud) {
        this.setUsername(ud.getUsername());
        this.password = ud.getPassword();
        this.setAccountNonExpired(true); //Sempre attivi a questo punto. La gestione del blocco o scadenza e' effettuata a livello superiore //ud.isAccountNonExpired());
        this.setAccountNonLocked(true); //ud.isAccountNonLocked());
        this.setEnabled(ud.isEnabled());
        String[] split = ud.getUsername().split(" ");
        try {
            this.setFirstName(split[0]);
        }
        catch (Exception ex){
            this.setFirstName("");
        }
        try {
            this.setLastName(split[1]);
        }catch (Exception ex){
            this.setLastName("");
        }



        LinkedList<Authority> auths = new LinkedList<Authority>();
        for (GrantedAuthority a : ud.getAuthorities()) {
            Authority auth = new Authority();
            auth.setDescription(a.getAuthority());
            auth.setAuthority(a.getAuthority());
            auths.add(auth);
        }
        this.authorities = auths;

    }

    public String getLoggedUserid() {
        return this.loggedUserid;
    }

    public String loggedUserid() {
        return this.loggedUserid;
    }

    public void setLoggedUserid(String loggedUserid) {
        this.loggedUserid = loggedUserid;
    }

    @JsonIgnore
    public int getTimeBeforeExpiration() {
        return 0;
    }

    @JsonIgnore
    public int getGraceLoginsRemaining() {
        return 0;
    }

    @JsonIgnore
    public String getDn() {
        return null;
    }
}
