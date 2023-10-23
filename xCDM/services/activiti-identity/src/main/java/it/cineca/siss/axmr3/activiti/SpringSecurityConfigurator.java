package it.cineca.siss.axmr3.activiti;

import org.activiti.engine.impl.cfg.ProcessEngineConfigurationImpl;
import org.activiti.engine.impl.cfg.ProcessEngineConfigurator;
import org.activiti.engine.impl.interceptor.SessionFactory;

import java.util.HashMap;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 20/10/13
 * Time: 09:57
 * To change this template use File | Settings | File Templates.
 */
public class SpringSecurityConfigurator implements ProcessEngineConfigurator{



    public SpringSecurityConfigurator() {

        userManagerFactory=new SpringSecurityUserManagerFactory(this);
        groupManagerFactory=new SpringSecurityGroupManagerFactory(this);
    }

    // Query configuration
    protected int searchTimeLimit = 0; // Default '0' == wait forever

    protected String queryUserByUserId;
    protected String queryGroupsForUser;
    protected String queryUserByFullNameLike;

    // Attribute names
    protected String userIdAttribute;
    protected String userFirstNameAttribute;
    protected String userLastNameAttribute;
    protected String userEmailAttribute;

    protected String groupIdAttribute;
    protected String groupNameAttribute;
    protected String groupTypeAttribute;

    protected SpringSecurityUserManagerFactory userManagerFactory;
    protected SpringSecurityGroupManagerFactory groupManagerFactory;

    public SpringSecurityUserManagerFactory getUserManagerFactory() {
        return userManagerFactory;
    }

    public void setUserManagerFactory(SpringSecurityUserManagerFactory userManagerFactory) {
        this.userManagerFactory = userManagerFactory;
    }

    public SpringSecurityGroupManagerFactory getGroupManagerFactory() {
        return groupManagerFactory;
    }

    public void setGroupManagerFactory(SpringSecurityGroupManagerFactory groupManagerFactory) {
        this.groupManagerFactory = groupManagerFactory;
    }

    public void configure(ProcessEngineConfigurationImpl processEngineConfiguration) {
        SpringSecurityUserManagerFactory userManagerFactory = getUserManagerFactory();
        if (processEngineConfiguration.getSessionFactories()==null) processEngineConfiguration.setSessionFactories(new HashMap< Class<?> , SessionFactory>());
        processEngineConfiguration.getSessionFactories().put(userManagerFactory.getSessionType(), userManagerFactory);

        SpringSecurityGroupManagerFactory groupManagerFactory = getGroupManagerFactory();
        processEngineConfiguration.getSessionFactories().put(groupManagerFactory.getSessionType(), groupManagerFactory);

    }


    public int getSearchTimeLimit() {
        return searchTimeLimit;
    }

    public void setSearchTimeLimit(int searchTimeLimit) {
        this.searchTimeLimit = searchTimeLimit;
    }

    public String getQueryUserByUserId() {
        return queryUserByUserId;
    }

    public void setQueryUserByUserId(String queryUserByUserId) {
        this.queryUserByUserId = queryUserByUserId;
    }

    public String getQueryGroupsForUser() {
        return queryGroupsForUser;
    }

    public void setQueryGroupsForUser(String queryGroupsForUser) {
        this.queryGroupsForUser = queryGroupsForUser;
    }

    public String getQueryUserByFullNameLike() {
        return queryUserByFullNameLike;
    }

    public void setQueryUserByFullNameLike(String queryUserByFullNameLike) {
        this.queryUserByFullNameLike = queryUserByFullNameLike;
    }

    public String getUserIdAttribute() {
        return userIdAttribute;
    }

    public void setUserIdAttribute(String userIdAttribute) {
        this.userIdAttribute = userIdAttribute;
    }

    public String getUserFirstNameAttribute() {
        return userFirstNameAttribute;
    }

    public void setUserFirstNameAttribute(String userFirstNameAttribute) {
        this.userFirstNameAttribute = userFirstNameAttribute;
    }

    public String getUserLastNameAttribute() {
        return userLastNameAttribute;
    }

    public void setUserLastNameAttribute(String userLastNameAttribute) {
        this.userLastNameAttribute = userLastNameAttribute;
    }

    public String getUserEmailAttribute() {
        return userEmailAttribute;
    }

    public void setUserEmailAttribute(String userEmailAttribute) {
        this.userEmailAttribute = userEmailAttribute;
    }

    public String getGroupIdAttribute() {
        return groupIdAttribute;
    }

    public void setGroupIdAttribute(String groupIdAttribute) {
        this.groupIdAttribute = groupIdAttribute;
    }

    public String getGroupNameAttribute() {
        return groupNameAttribute;
    }

    public void setGroupNameAttribute(String groupNameAttribute) {
        this.groupNameAttribute = groupNameAttribute;
    }

    public String getGroupTypeAttribute() {
        return groupTypeAttribute;
    }

    public void setGroupTypeAttribute(String groupTypeAttribute) {
        this.groupTypeAttribute = groupTypeAttribute;
    }



}
