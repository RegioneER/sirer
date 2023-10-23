package it.cineca.siss.axmr3.activiti;

import it.cineca.siss.axmr3.authentication.IAuthority;
import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.authentication.services.SissUserService;
import org.activiti.engine.IdentityService;
import org.activiti.engine.identity.Group;
import org.activiti.engine.identity.User;
import org.activiti.engine.impl.identity.Authentication;
import org.activiti.explorer.identity.LoggedInUser;
import org.activiti.explorer.identity.LoggedInUserImpl;
import org.activiti.explorer.ui.login.LoginHandler;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.context.SecurityContextHolder;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.LinkedList;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 20/10/13
 * Time: 14:34
 * To change this template use File | Settings | File Templates.
 */
public class ActivitiLoginHandler implements LoginHandler {

    private transient IdentityService identityService;

    @Autowired
    protected SissUserService userService;



    public LoggedInUserImpl authenticate(String userName, String password) {
        IUser springAuthUser =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if (springAuthUser==null) return null;
        User user = new SpringSecurityUserBridge(springAuthUser);
        LoggedInUserImpl loggedInUser = new LoggedInUserImpl(user, null);
        List<IAuthority> auths= (List<IAuthority>) springAuthUser.getAuthorities();
        List<Group> groups = new LinkedList<Group>();
        loggedInUser.setAdmin(false);
        for (IAuthority auth:auths){
            if (auth.getAuthority().equals("tech-admin")) loggedInUser.setAdmin(true);
            loggedInUser.addGroup(new SpringSecurityGroupBridge(auth));
        }
        loggedInUser.setUser(true);
        return loggedInUser;
    }

    public void onRequestStart(HttpServletRequest request, HttpServletResponse response) {
    }

    public void onRequestEnd(HttpServletRequest request, HttpServletResponse response) {
        // Noting to do here
    }

    public LoggedInUser authenticate(HttpServletRequest request, HttpServletResponse response) {

        IUser springAuthUser =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if (springAuthUser==null) return null;
        User user = new SpringSecurityUserBridge(springAuthUser);
        LoggedInUserImpl loggedInUser = new LoggedInUserImpl(user, null);
        List<IAuthority> auths= (List<IAuthority>) springAuthUser.getAuthorities();
        loggedInUser.setAdmin(false);
        for (IAuthority auth:auths){
            if (auth.getAuthority().equals("tech-admin")) loggedInUser.setAdmin(true);
            loggedInUser.addGroup(new SpringSecurityGroupBridge(auth));
        }
        loggedInUser.setUser(true);
        return loggedInUser;
    }

    public void logout(LoggedInUser userToLogout) {
        Authentication.setAuthenticatedUserId(null);
    }

    public void setIdentityService(IdentityService identityService) {
        this.identityService = identityService;
    }

    public IdentityService getIdentityService() {
        return identityService;
    }

    public SissUserService getUserService() {
        return userService;
    }

    public void setUserService(SissUserService userService) {
        this.userService = userService;
    }
}
