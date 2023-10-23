package it.cineca.siss.axmr3.authentication;

import org.codehaus.jackson.annotate.JsonIgnore;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.ldap.ppolicy.PasswordPolicyData;
import org.springframework.security.ldap.userdetails.LdapUserDetails;

import java.io.Serializable;
import java.util.Collection;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 24/10/13
 * Time: 13:19
 * To change this template use File | Settings | File Templates.
 */
public interface IUser extends LdapUserDetails, PasswordPolicyData, Serializable {
    String getFirstName();

    void setFirstName(String firstName);

    String getLastName();

    void setLastName(String lastName);

    String getEmail();

    void setEmail(String email);

    Collection<? extends IAuthority> getAuthorities();

    void setAuthorities(Collection<? extends IAuthority> authorities);

    @JsonIgnore
    String getPassword();

    void setPassword(String password);

    String getUsername();

    Long getEmeSessionId();

    void setUsername(String username);

    void setEmeRootElementId(Long emeRootElementId);

    Long getEmeRootElementId();

    void setEmeSessionId(Long emeSessionId);

    boolean isAccountNonExpired();

    void setAccountNonExpired(boolean accountNonExpired);

    boolean isAccountNonLocked();

    void setAccountNonLocked(boolean accountNonLocked);

    boolean isCredentialsNonExpired();

    void setCredentialsNonExpired(boolean credentialsNonExpired);

    boolean isEnabled();

    void setEnabled(boolean enabled);

    boolean hasRole(String roleName);

    void setEnte(String ente);

    String getEnte();

    List<Integer> getSitesID();

    Integer getFirstSiteID();

    List<String> getSitesCodes();

    String getFirstSiteCode();

    List<String> getUoCodes();

    void fromUserDetails(UserDetails ud);

    String getLoggedUserid();

}
