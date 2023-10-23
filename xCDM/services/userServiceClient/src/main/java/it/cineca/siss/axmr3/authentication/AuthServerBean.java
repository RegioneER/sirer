package it.cineca.siss.axmr3.authentication;

import org.apache.log4j.Logger;
import org.springframework.beans.factory.InitializingBean;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 31/05/13
 * Time: 15.31
 * To change this template use File | Settings | File Templates.
 */
public class AuthServerBean implements InitializingBean {

    protected static Logger log=Logger.getLogger(AuthServerBean.class);

    private String url;
    private String adminUsername;
    private String adminPassword;

    public String getAdminPassword() {
        return adminPassword;
    }

    public void setAdminPassword(String adminPassword) {
        this.adminPassword = adminPassword;
    }

    public String getAdminUsername() {
        return adminUsername;
    }

    public void setAdminUsername(String adminUsername) {
        this.adminUsername = adminUsername;
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public void afterPropertiesSet() throws Exception {


    }
}
