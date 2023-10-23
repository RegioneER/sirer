package it.cineca.siss.axmr3.activiti;

import org.activiti.engine.impl.interceptor.Session;
import org.activiti.engine.impl.interceptor.SessionFactory;
import org.activiti.engine.impl.persistence.entity.MembershipIdentityManager;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 20/10/13
 * Time: 10:47
 * To change this template use File | Settings | File Templates.
 */
public class SpringSecurityMembershipFactory implements SessionFactory {

    protected SpringSecurityConfigurator configurator;

    public SpringSecurityMembershipFactory(SpringSecurityConfigurator configurator){
        this.configurator=configurator;
    }

    
    public Class<?> getSessionType() {
        return MembershipIdentityManager.class;
    }

    
    public Session openSession() {
        return new SpringSecurityMembershipManager(configurator);
    }


}
