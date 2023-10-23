package it.cineca.siss.axmr3.activiti;

import it.cineca.siss.axmr3.activiti.implementations.SpringSecurityGroupQuery;
import it.cineca.siss.axmr3.activiti.implementations.SpringSecurityUserQuery;
import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.authentication.services.SissUserService;
import org.activiti.engine.IdentityService;
import org.activiti.engine.identity.*;
import org.activiti.engine.impl.identity.Authentication;
import org.springframework.beans.factory.annotation.Autowired;

import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 20/10/13
 * Time: 13:49
 * To change this template use File | Settings | File Templates.
 */
public class SpringSecurityIdentity implements IdentityService {

    @Autowired
    protected SissUserService userService;

    public SissUserService getUserService() {
        return userService;
    }

    public void setUserService(SissUserService userService) {
        this.userService = userService;
    }

    public User newUser(String s) {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    
    public void saveUser(User user) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    
    public UserQuery createUserQuery() {
        return new SpringSecurityUserQuery(userService);  //To change body of implemented methods use File | Settings | File Templates.
    }

    
    public NativeUserQuery createNativeUserQuery() {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    
    public void deleteUser(String s) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    
    public Group newGroup(String s) {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    
    public GroupQuery createGroupQuery() {
        return new SpringSecurityGroupQuery(userService);  //To change body of implemented methods use File | Settings | File Templates.
    }

    
    public NativeGroupQuery createNativeGroupQuery() {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    
    public void saveGroup(Group group) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    
    public void deleteGroup(String s) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    
    public void createMembership(String s, String s2) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    
    public void deleteMembership(String s, String s2) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    
    public boolean checkPassword(String userId, String password) {
        IUser u=(IUser)userService.loadUserByUsername(userId);
        return userService.isPasswordValid(u.getPassword(), password, null);
    }

    
    public void setAuthenticatedUserId(String s) {
        Authentication.setAuthenticatedUserId(s);
    }

    
    public void setUserPicture(String s, Picture picture) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    
    public Picture getUserPicture(String s) {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    
    public void setUserInfo(String s, String s2, String s3) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    
    public String getUserInfo(String s, String s2) {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    
    public List<String> getUserInfoKeys(String s) {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    
    public void deleteUserInfo(String s, String s2) {
        //To change body of implemented methods use File | Settings | File Templates.
    }
}
