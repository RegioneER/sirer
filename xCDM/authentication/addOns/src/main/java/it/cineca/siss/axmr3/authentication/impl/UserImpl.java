package it.cineca.siss.axmr3.authentication.impl;

import it.cineca.siss.axmr3.authentication.IAuthority;
import it.cineca.siss.axmr3.authentication.IUser;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.userdetails.UserDetails;

import java.util.*;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 24/10/13
 * Time: 15:46
 * To change this template use File | Settings | File Templates.
 */
public class UserImpl implements IUser {

    private String username;
    private Long emeSessionId;
    private Long emeRootElementId;
    private String firstName;
    private String lastName;
    private String email;
    private String password;
    private String ente;
    private Collection<AuthorityImpl> authorities=new LinkedList<AuthorityImpl>();
    private boolean accountNonExpired=true;
    private boolean accountNonLocked=true;
    private boolean credentialsNonExpired=true;
    private boolean enabled=true;
    private String loggedUserid;

    public String getLoggedUserid() {
        return loggedUserid;
    }

    public void setLoggedUserid(String loggedUserid) {
        this.loggedUserid = loggedUserid;
    }

    private HashMap<String, String> anaData = new LinkedHashMap<String, String>();
    private HashMap<String,String> anaDataLoggedUser=new LinkedHashMap<String, String>();
    private HashMap<String, String> siteData=new LinkedHashMap<>();

    private List<Integer> sitesID = new LinkedList<Integer>();

    private List<String> siteCodes = new LinkedList<String>();

    private List<String> uoCodes = new LinkedList<String>();

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public void setEmeSessionId(Long emeSessionId) {
        this.emeSessionId = emeSessionId;
    }

    public Long getEmeSessionId() {
        return emeSessionId;
    }

    public void setEmeRootElementId(Long emeRootElementId) {
        this.emeRootElementId = emeRootElementId;
    }

    public Long getEmeRootElementId()  {
        return emeRootElementId;
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

    public Collection<AuthorityImpl> getAuthorities() {
        return authorities;
    }

    public void setAuthorities(Collection<? extends IAuthority> authorities) {
        this.authorities = (Collection<AuthorityImpl>) authorities;
    }

    public boolean isAccountNonExpired() {
        return accountNonExpired;
    }

    public void setAccountNonExpired(boolean accountNonExpired) {
        this.accountNonExpired = accountNonExpired;
    }

    public boolean isAccountNonLocked() {
        return accountNonLocked;
    }

    public void setAccountNonLocked(boolean accountNonLocked) {
        this.accountNonLocked = accountNonLocked;
    }

    public boolean isCredentialsNonExpired() {
        return credentialsNonExpired;
    }

    public void setCredentialsNonExpired(boolean credentialsNonExpired) {
        this.credentialsNonExpired = credentialsNonExpired;
    }

    public boolean isEnabled() {
        return enabled;
    }

    public void setEnabled(boolean enabled) {
        this.enabled = enabled;
    }

    public boolean hasRole(String roleName) {
        boolean hasRole = false;
        for (AuthorityImpl a : getAuthorities()) {
            if (a.getAuthority().equals(roleName)) {
                hasRole = true;
            }
        }
        return hasRole;
    }

    public void setEnte(String ente) {
        this.ente=ente;
    }

    public String getEnte() {
        return this.ente;
    }

    @Override
    public String toString() {
        return "UserImpl{" +
                "username='" + username + '\'' +
                ", firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' +
                ", email='" + email + '\'' +
                ", password='" + password + '\'' +
                ", authorities=" + authorities +
                ", accountNonExpired=" + accountNonExpired +
                ", accountNonLocked=" + accountNonLocked +
                ", credentialsNonExpired=" + credentialsNonExpired +
                ", enabled=" + enabled +
                '}';
    }

    public HashMap<String, String> getAnaData() {
        return anaData;
    }

    public void setAnaData(HashMap<String, String> anaData) {
        this.anaData = anaData;
    }

    public String getAnaDataValue(String key) {
        String retval = "";
        if (this.anaData.containsKey(key)) {
            retval = this.anaData.get(key);
        }
        return retval;
    }

    public HashMap<String, String> getAnaDataLoggedUser() {
        return anaDataLoggedUser;
    }

    public void setAnaDataLoggedUser(HashMap<String, String> anaDataLoggedUser) {
        this.anaDataLoggedUser = anaDataLoggedUser;
    }

    public String getAnaDataLoggedUser(String key){
        String retval = "";
        if (this.anaDataLoggedUser.containsKey(key)){
            retval = this.anaDataLoggedUser.get(key);
        }
        return retval;
    }

    public HashMap<String, String> getSiteData() {
        return siteData;
    }

    public void setSiteData(HashMap<String, String> siteData) {
        this.siteData = siteData;
    }

    public String getSiteDataValue(String key) {
        String retval = "";
        if (this.siteData.containsKey(key)) {
            retval = this.siteData.get(key);
        }
        return retval;
    }

    @Override
    public List<Integer> getSitesID() {
        return sitesID;
    }

    public void setSitesID(List<Integer> sList) {
        this.sitesID = sList;
    }

    @Override
    public Integer getFirstSiteID() {
        Integer retval = 0;
        if (this.sitesID.size() > 0) {
            retval = this.sitesID.get(0);
        }
        return retval;
    }

    @Override
    public List<String> getSitesCodes() {
        return siteCodes;
    }

    public void setSitesCodes(List<String> sList) {
        this.siteCodes = sList;
    }

    @Override
    public String getFirstSiteCode() {
        String retval = "";
        if (this.siteCodes.size() > 0) {
            retval = this.siteCodes.get(0);
        }
        return retval;
    }

    @Override
    public List<String> getUoCodes(){
        return uoCodes;
    }

    public void setUOCodes(List<String> sList) {
        this.uoCodes = sList;
    }

    public String getFirstUOCode() {
        String retval = "";
        if (this.uoCodes.size() > 0) {
            retval = this.uoCodes.get(0);
        }
        return retval;
    }

    public void fromUserDetails(UserDetails ud) {
        this.setUsername(ud.getUsername());
        this.password = ud.getPassword();
        this.setAccountNonExpired(true); //Sempre attivi a questo punto. La gestione del blocco o scadenza e' effettuata a livello superiore //ud.isAccountNonExpired());
        this.setAccountNonLocked(true); //ud.isAccountNonLocked());
        this.setEnabled(ud.isEnabled());
        String[] split = ud.getUsername().split(" ");
        try {
            this.setFirstName(split[0]);
        } catch (Exception ex) {
            this.setFirstName("");
        }
        try {
            this.setLastName(split[1]);
        } catch (Exception ex) {
            this.setLastName("");
        }


        LinkedList<AuthorityImpl> auths = new LinkedList<AuthorityImpl>();
        for (GrantedAuthority a : ud.getAuthorities()) {
            AuthorityImpl auth = new AuthorityImpl();
            auth.setDescription(a.getAuthority());
            auth.setAuthority(a.getAuthority());
            auths.add(auth);
        }
        this.authorities = auths;

    }

    public int getTimeBeforeExpiration() {
        return 0;
    }

    public int getGraceLoginsRemaining() {
        return 0;
    }

    public String getDn() {
        return null;
    }
}
