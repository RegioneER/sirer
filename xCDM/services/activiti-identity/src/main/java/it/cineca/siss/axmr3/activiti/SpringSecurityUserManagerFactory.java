package it.cineca.siss.axmr3.activiti;

import org.activiti.engine.impl.interceptor.Session;
import org.activiti.engine.impl.interceptor.SessionFactory;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 20/10/13
 * Time: 09:59
 * To change this template use File | Settings | File Templates.
 */
public class SpringSecurityUserManagerFactory implements SessionFactory {

    protected SpringSecurityConfigurator configurator;

    public SpringSecurityConfigurator getConfigurator() {
        return configurator;
    }

    public void setConfigurator(SpringSecurityConfigurator configurator) {
        this.configurator = configurator;
    }

    public SpringSecurityUserManagerFactory(SpringSecurityConfigurator Configurator) {
        this.configurator = configurator;
    }

    
    public Class<?> getSessionType() {
        return SpringSecurityUserManager.class;
    }

    
    public Session openSession() {
        return new SpringSecurityUserManager(configurator);
    }
}
