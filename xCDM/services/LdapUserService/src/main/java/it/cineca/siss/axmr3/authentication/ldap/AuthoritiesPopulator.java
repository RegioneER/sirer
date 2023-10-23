package it.cineca.siss.axmr3.authentication.ldap;

import it.cineca.siss.axmr3.authentication.services.SissUserService;
import org.springframework.ldap.core.DirContextOperations;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;

import java.util.Collection;

/**
 * Created by cin0562a on 19/06/15.
 */
public class AuthoritiesPopulator extends org.springframework.security.ldap.authentication.UserDetailsServiceLdapAuthoritiesPopulator {
    private SissUserService ldapUserDetailsService;

    public AuthoritiesPopulator(SissUserService userService) {
        super(userService);
        ldapUserDetailsService = userService;
    }

    public UserDetailsService getLdapUserDetailsService() {
        return ldapUserDetailsService;
    }

    public void setLdapUserDetailsService(UserDetailsService ldapUserDetailsService) {
        this.ldapUserDetailsService = (SissUserService) ldapUserDetailsService;
    }

    @Override
    public Collection<? extends GrantedAuthority> getGrantedAuthorities(DirContextOperations userData, String username) {
        UserDetails user = ldapUserDetailsService.loadUserByUsernameNotLogout(username);
        return user.getAuthorities();
    }
}
