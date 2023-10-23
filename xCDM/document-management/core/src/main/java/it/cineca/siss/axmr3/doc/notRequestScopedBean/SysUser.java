package it.cineca.siss.axmr3.doc.notRequestScopedBean;

import it.cineca.siss.axmr3.authentication.IAuthority;
import it.cineca.siss.axmr3.authentication.IUser;
import org.springframework.security.core.userdetails.UserDetails;

import java.util.Collection;
import java.util.LinkedList;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 12/12/13
 * Time: 17.39
 * To change this template use File | Settings | File Templates.
 */
public class SysUser implements IUser {

    private Long emeSessionId;
    private Long emeRootElementId;

    public String getFirstName() {
        return "System";  //To change body of implemented methods use File | Settings | File Templates.
    }

    public void setFirstName(String firstName) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    public String getLastName() {
        return "System";  //To change body of implemented methods use File | Settings | File Templates.
    }

    public void setLastName(String lastName) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    public String getEmail() {
        return "System@system.com";  //To change body of implemented methods use File | Settings | File Templates.
    }

    public void setEmail(String email) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    public Collection<? extends IAuthority> getAuthorities() {
        List<SysAuth> auths = new LinkedList<SysAuth>();
        auths.add(new SysAuth());
        return auths;  //To change body of implemented methods use File | Settings | File Templates.
    }

    public void setAuthorities(Collection<? extends IAuthority> authorities) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    public String getPassword() {
        return "";  //To change body of implemented methods use File | Settings | File Templates.
    }

    public void setPassword(String password) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    public String getUsername() {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    public Long getEmeSessionId() {
        return emeSessionId;
    }

    public void setUsername(String username) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    public void setEmeSessionId(Long emeSessionId) {
        this.emeSessionId = emeSessionId;
    }

    public void setEmeRootElementId(Long emeRootElementId) {
        this.emeRootElementId = emeRootElementId;
    }

    public Long getEmeRootElementId()  {
        return emeRootElementId;
    }

    public boolean isAccountNonExpired() {
        return false;  //To change body of implemented methods use File | Settings | File Templates.
    }

    public void setAccountNonExpired(boolean accountNonExpired) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    public boolean isAccountNonLocked() {
        return false;  //To change body of implemented methods use File | Settings | File Templates.
    }

    public void setAccountNonLocked(boolean accountNonLocked) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    public boolean isCredentialsNonExpired() {
        return false;  //To change body of implemented methods use File | Settings | File Templates.
    }

    public void setCredentialsNonExpired(boolean credentialsNonExpired) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    public boolean isEnabled() {
        return false;  //To change body of implemented methods use File | Settings | File Templates.
    }

    public void setEnabled(boolean enabled) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    public boolean hasRole(String roleName) {
        return false;  //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public void setEnte(String ente) {

    }

    @Override
    public String getEnte() {
        return "";
    }

    @Override
    public List<Integer> getSitesID() {
        return null;
    }

    @Override
    public Integer getFirstSiteID() {
        return null;
    }

    @Override
    public List<String> getSitesCodes() {
        return null;
    }

    @Override
    public String getFirstSiteCode() {
        return null;
    }

    @Override
    public List<String> getUoCodes() {
        return null;
    }

    @Override
    public void fromUserDetails(UserDetails ud) {

    }

    public String getLoggedUserid() {
        return null;
    }

    @Override
    public int getTimeBeforeExpiration() {
        return 0;
    }

    @Override
    public int getGraceLoginsRemaining() {
        return 0;
    }

    @Override
    public String getDn() {
        return null;
    }
}
