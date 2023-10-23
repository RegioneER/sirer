package it.cineca.siss.axmr3.authentication.ldap;

import org.springframework.ldap.core.ContextSource;
import org.springframework.ldap.core.DirContextOperations;
import org.springframework.security.core.GrantedAuthority;

import java.util.Set;

/**
 * Created by gdelsignore on 19/06/2015.
 */
public class DefaultAuthoritiesPopulator extends org.springframework.security.ldap.userdetails.DefaultLdapAuthoritiesPopulator {

    public DefaultAuthoritiesPopulator(ContextSource contextSource, String groupSearchBase) {
        super(contextSource, groupSearchBase);
    }

    @Override
    protected Set<GrantedAuthority> getAdditionalRoles(DirContextOperations user, String username) {
        Set<GrantedAuthority> uos = super.getAdditionalRoles(user, username);
        return uos;
    }

    @Override
    public void setGroupRoleAttribute(String groupRoleAttribute) {
        super.setGroupRoleAttribute(groupRoleAttribute);
    }

    @Override
    public void setGroupSearchFilter(String groupSearchFilter) {
        super.setGroupSearchFilter(groupSearchFilter);
    }
}
