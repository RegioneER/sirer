package it.cineca.siss.axmr3.activiti;

import it.cineca.siss.axmr3.authentication.IAuthority;
import it.cineca.siss.axmr3.authentication.IUser;
import org.activiti.engine.identity.Group;
import org.activiti.engine.identity.User;
import org.activiti.explorer.identity.LoggedInUserImpl;
import org.restlet.Request;
import org.restlet.Response;
import org.springframework.security.core.context.SecurityContextHolder;

import java.util.LinkedList;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 21/10/13
 * Time: 14:29
 * To change this template use File | Settings | File Templates.
 */
public class ActivitiRestServicesApplication extends org.activiti.rest.service.application.ActivitiRestServicesApplication{

    @Override
    public String authenticate(Request request, Response response) {
        if (SecurityContextHolder.getContext().getAuthentication().getPrincipal() instanceof IUser){
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
            return loggedInUser.getId();
        }
        else return null;

    }
}
