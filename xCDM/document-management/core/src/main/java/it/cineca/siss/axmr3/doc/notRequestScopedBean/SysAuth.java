package it.cineca.siss.axmr3.doc.notRequestScopedBean;

import it.cineca.siss.axmr3.authentication.IAuthority;
import it.cineca.siss.axmr3.authentication.IUser;

import java.util.Collection;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 12/12/13
 * Time: 17.39
 * To change this template use File | Settings | File Templates.
 */
public class SysAuth implements IAuthority {

    public Collection<? extends IUser> getUsers() {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    public void setUsers(Collection<? extends IUser> users) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    public String getAuthority() {
        return "System";  //To change body of implemented methods use File | Settings | File Templates.
    }

    public void setAuthority(String authority) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    public String getDescription() {
        return "System Authority";  //To change body of implemented methods use File | Settings | File Templates.
    }

    public void setDescription(String description) {
        //To change body of implemented methods use File | Settings | File Templates.
    }
}
