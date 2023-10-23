package it.cineca.siss.axmr3.authentication.services;

import it.cineca.siss.axmr3.authentication.IAuthority;
import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.authentication.services.query.OrderBy;
import it.cineca.siss.axmr3.authentication.services.query.WhereClause;
import org.apache.log4j.Logger;
import org.springframework.security.authentication.encoding.PasswordEncoder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;

import java.util.HashMap;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 01/06/13
 * Time: 12.53
 * To change this template use File | Settings | File Templates.
 */
public abstract class SissUserService implements UserDetailsService {

    protected static Logger log=Logger.getLogger(SissUserService.class);

    protected PasswordEncoder passwordEncoder;

    public PasswordEncoder getPasswordEncoder(){
        return this.passwordEncoder;
    }

    public abstract void setPasswordEncoder(PasswordEncoder passwordEncoder);

    public boolean isPasswordValid(String encPass, String rawPass, Object salt){

        return passwordEncoder.isPasswordValid(encPass, rawPass, salt);
    }

    public String encodePassword(String rawPass, Object salt){
       return passwordEncoder.encodePassword(rawPass, salt);
    }

    public abstract UserDetails loadUserByUsernameNotLogout(String username);

    public abstract Object uniqueByWhereAndOrder(String object, List<WhereClause> crits, List<OrderBy> orders, HashMap<String, String> aliases);

    public abstract List<Object> listByWhereAndOrder(String object, List<WhereClause> crits, List<OrderBy> orders, HashMap<String, String> aliases);

    public abstract List<? extends IUser> searchUserByUsername(String pattern);

    public abstract List<? extends IAuthority> searchAuthorityByName(String pattern);

    public abstract List<Object> listByWhereAndOrderPaged(String object, List<WhereClause> crits, List<OrderBy> orders, HashMap<String, String> aliases, int i, int i2);

    public abstract void setLoggedUser(String username);

    public abstract List<? extends IUser> searchUsersByAuthorityName(String authorityName);

    public abstract IUser getUser(String username);
}
