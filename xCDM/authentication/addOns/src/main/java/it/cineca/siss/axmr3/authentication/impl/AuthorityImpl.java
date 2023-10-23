package it.cineca.siss.axmr3.authentication.impl;

import it.cineca.siss.axmr3.authentication.IAuthority;
import it.cineca.siss.axmr3.authentication.IUser;

import java.util.Collection;
import java.util.LinkedList;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 24/10/13
 * Time: 15:43
 * To change this template use File | Settings | File Templates.
 */
public class AuthorityImpl implements IAuthority {

    private Collection<UserImpl> users=new LinkedList<UserImpl>();
    private String authority;
    private String description;
    private Long id;

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public Collection<UserImpl> getUsers() {
        return users;
    }

    public void setUsers(Collection<? extends IUser> users) {
        this.users = (Collection<UserImpl>) users;
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

    @Override
    public String toString() {
        return "AuthorityImpl{" +
                "users=" + users +
                ", authority='" + authority + '\'' +
                ", description='" + description + '\'' +
                '}';
    }
}
