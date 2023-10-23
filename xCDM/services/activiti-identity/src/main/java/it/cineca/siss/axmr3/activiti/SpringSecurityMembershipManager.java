package it.cineca.siss.axmr3.activiti;

import org.activiti.engine.impl.interceptor.Session;
import org.activiti.engine.impl.persistence.AbstractManager;
import org.activiti.engine.impl.persistence.entity.GroupIdentityManager;
import org.activiti.engine.impl.persistence.entity.MembershipIdentityManager;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 23/10/13
 * Time: 14:33
 * To change this template use File | Settings | File Templates.
 */
public class SpringSecurityMembershipManager extends AbstractManager implements MembershipIdentityManager {

    protected it.cineca.siss.axmr3.authentication.services.SissUserService userService;

    protected SpringSecurityConfigurator configurator;

    public SpringSecurityMembershipManager(SpringSecurityConfigurator configurator) {
         this.configurator=configurator;
    }

    
    public void createMembership(String s, String s2) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    
    public void deleteMembership(String s, String s2) {
        //To change body of implemented methods use File | Settings | File Templates.
    }
}
