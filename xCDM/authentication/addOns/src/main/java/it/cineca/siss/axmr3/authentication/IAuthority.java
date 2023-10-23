package it.cineca.siss.axmr3.authentication;

import org.springframework.security.core.GrantedAuthority;

import java.io.Serializable;
import java.util.Collection;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 24/10/13
 * Time: 13:17
 * To change this template use File | Settings | File Templates.
 */
public interface IAuthority extends GrantedAuthority, Serializable {
    Collection<? extends IUser> getUsers();

    void setUsers(Collection<? extends IUser> users);

    String getAuthority();

    void setAuthority(String authority);

    String getDescription();

    void setDescription(String description);
}
