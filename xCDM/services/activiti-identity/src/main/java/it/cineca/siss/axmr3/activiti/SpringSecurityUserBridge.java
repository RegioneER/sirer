package it.cineca.siss.axmr3.activiti;

import org.activiti.engine.identity.User;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 20/10/13
 * Time: 14:36
 * To change this template use File | Settings | File Templates.
 */
public class SpringSecurityUserBridge implements User {

    private String id;
    private String firstName;
    private String lastName;
    private String email;
    private String password;


    public SpringSecurityUserBridge(it.cineca.siss.axmr3.authentication.IUser u) {
        if (u!=null){
            this.setId(u.getUsername());
            this.setPassword(u.getPassword());
            this.setFirstName(u.getFirstName());
            this.setLastName(u.getLastName());
            this.setEmail(u.getEmail());

        }
    }


    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

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

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }
}
