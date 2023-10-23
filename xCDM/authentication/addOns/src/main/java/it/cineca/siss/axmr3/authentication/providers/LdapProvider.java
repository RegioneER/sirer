package it.cineca.siss.axmr3.authentication.providers;

import it.cineca.siss.axmr3.authentication.services.SissUserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.dao.IncorrectResultSizeDataAccessException;
import org.springframework.ldap.core.DirContextOperations;
import org.springframework.ldap.core.support.DefaultDirObjectFactory;
import org.springframework.ldap.support.LdapUtils;
import org.springframework.security.authentication.*;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.security.ldap.SpringSecurityLdapTemplate;
import org.springframework.security.ldap.authentication.AbstractLdapAuthenticationProvider;
import org.springframework.util.Assert;
import org.springframework.util.StringUtils;

import javax.naming.AuthenticationException;
import javax.naming.Context;
import javax.naming.NamingException;
import javax.naming.OperationNotSupportedException;
import javax.naming.directory.DirContext;
import javax.naming.directory.SearchControls;
import javax.naming.ldap.InitialLdapContext;
import java.util.Collection;
import java.util.Hashtable;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Created by gdelsignore on 27/04/2015.
 */
public class LdapProvider extends AbstractLdapAuthenticationProvider {
    private static final Pattern SUB_ERROR_CODE = Pattern.compile(".*data\\s([0-9a-f]{3,4}).*");

    // Error codes
    private static final int USERNAME_NOT_FOUND = 0x525;
    private static final int INVALID_PASSWORD = 0x52e;
    private static final int NOT_PERMITTED = 0x530;
    private static final int PASSWORD_EXPIRED = 0x532;
    private static final int ACCOUNT_DISABLED = 0x533;
    private static final int ACCOUNT_EXPIRED = 0x701;
    private static final int PASSWORD_NEEDS_RESET = 0x773;
    private static final int ACCOUNT_LOCKED = 0x775;

    private final String domain;
    private final String rootDn;
    private final String url;
    private boolean convertSubErrorCodesToExceptions;


    private SissUserService userDao;

    // Only used to allow tests to substitute a mock LdapContext
    ContextFactory contextFactory = new ContextFactory();


    /**
     * @param domain the domain name (may be null or empty)
     * @param url    an LDAP url (or multiple URLs)
     */
    @Autowired
    public LdapProvider(String domain, String url, SissUserService userDao) {
        Assert.isTrue(StringUtils.hasText(url), "Url cannot be empty");
        this.domain = StringUtils.hasText(domain) ? domain.toLowerCase() : null;
        //this.url = StringUtils.hasText(url) ? url : null;
        this.url = url;
        this.userDao = userDao;
        rootDn = this.domain == null ? null : rootDnFromDomain(this.domain);
    }

    @Override
    protected DirContextOperations doAuthentication(UsernamePasswordAuthenticationToken auth) {
        String username = auth.getName();
        String password = (String) auth.getCredentials();

        DirContext ctx = bindAsUser(username, password);

        try {
            return searchForUser(ctx, username);

        } catch (NamingException e) {
            logger.error("Failed to locate directory entry for authenticated user: " + username, e);
            throw badCredentials(e);
        } finally {
            LdapUtils.closeContext(ctx);
        }
    }

    /**
     * Creates the user authority list from the values of the role associated with the user. The standard implementation made use of the {@code memberOf} attribute obtained from the user's
     * Active Directory entry.
     */
    @Override
    protected Collection<? extends GrantedAuthority> loadUserAuthorities(DirContextOperations userData, String username, String password) {
        UserDetails udetails = userDao.loadUserByUsername(username);
        return udetails.getAuthorities();
    }

    private DirContext bindAsUser(String username, String password) {
        // TODO. add DNS lookup based on domain
        final String bindUrl = url;
        Hashtable<String, String> env = new Hashtable<String, String>();
        env.put(Context.SECURITY_AUTHENTICATION, "simple");
        String bindPrincipal = createBindPrincipal(username);
        env.put(Context.SECURITY_PRINCIPAL, bindPrincipal);
        env.put(Context.PROVIDER_URL, bindUrl);
        env.put(Context.SECURITY_CREDENTIALS, password);
        env.put(Context.INITIAL_CONTEXT_FACTORY, "com.sun.jndi.ldap.LdapCtxFactory");
        env.put(Context.OBJECT_FACTORIES, DefaultDirObjectFactory.class.getName());

        try {
            return contextFactory.createContext(env);
        } catch (NamingException e) {
            if ((e instanceof AuthenticationException) || (e instanceof OperationNotSupportedException)) {
                handleBindException(bindPrincipal, e);
                throw badCredentials(e);
            } else {
                throw LdapUtils.convertLdapException(e);
            }
        }
    }

    void handleBindException(String bindPrincipal, NamingException exception) {
        if (logger.isDebugEnabled()) {
            logger.debug("Authentication for " + bindPrincipal + " failed:" + exception);
        }

        int subErrorCode = parseSubErrorCode(exception.getMessage());

        if (subErrorCode > 0) {
            logger.debug("Active Directory authentication failed: " + subCodeToLogMessage(subErrorCode));

            if (convertSubErrorCodesToExceptions) {
                raiseExceptionForErrorCode(subErrorCode, exception);
            }
        } else {
            logger.debug("Failed to locate AD-specific sub-error code in message");
        }
    }

    int parseSubErrorCode(String message) {
        Matcher m = SUB_ERROR_CODE.matcher(message);

        if (m.matches()) {
            return Integer.parseInt(m.group(1), 16);
        }

        return -1;
    }

    void raiseExceptionForErrorCode(int code, NamingException exception) {
        String hexString = Integer.toHexString(code);
        Throwable cause = new Exception("ldap excception");
        switch (code) {
            case PASSWORD_EXPIRED:
                throw new CredentialsExpiredException(messages.getMessage("LdapAuthenticationProvider.credentialsExpired",
                        "User credentials have expired"), cause);
            case ACCOUNT_DISABLED:
                throw new DisabledException(messages.getMessage("LdapAuthenticationProvider.disabled",
                        "User is disabled"), cause);
            case ACCOUNT_EXPIRED:
                throw new AccountExpiredException(messages.getMessage("LdapAuthenticationProvider.expired",
                        "User account has expired"), cause);
            case ACCOUNT_LOCKED:
                throw new LockedException(messages.getMessage("LdapAuthenticationProvider.locked",
                        "User account is locked"), cause);
            default:
                throw badCredentials(cause);
        }
    }

    String subCodeToLogMessage(int code) {
        switch (code) {
            case USERNAME_NOT_FOUND:
                return "User was not found in directory";
            case INVALID_PASSWORD:
                return "Supplied password was invalid";
            case NOT_PERMITTED:
                return "User not permitted to logon at this time";
            case PASSWORD_EXPIRED:
                return "Password has expired";
            case ACCOUNT_DISABLED:
                return "Account is disabled";
            case ACCOUNT_EXPIRED:
                return "Account expired";
            case PASSWORD_NEEDS_RESET:
                return "User must reset password";
            case ACCOUNT_LOCKED:
                return "Account locked";
        }

        return "Unknown (error code " + Integer.toHexString(code) + ")";
    }

    private BadCredentialsException badCredentials() {
        return new BadCredentialsException(messages.getMessage(
                "LdapAuthenticationProvider.badCredentials", "Bad credentials"));
    }

    private BadCredentialsException badCredentials(Throwable cause) {
        return (BadCredentialsException) badCredentials().initCause(cause);
    }

    @SuppressWarnings("deprecation")
    private DirContextOperations searchForUser(DirContext ctx, String username) throws NamingException {
        SearchControls searchCtls = new SearchControls();
        searchCtls.setSearchScope(SearchControls.SUBTREE_SCOPE);

        String searchFilter = "(&(objectClass=user)(userPrincipalName={0}))";

        final String bindPrincipal = createBindPrincipal(username);

        String searchRoot = rootDn != null ? rootDn : searchRootFromPrincipal(bindPrincipal);

        try {
            return SpringSecurityLdapTemplate.searchForSingleEntryInternal(ctx, searchCtls, searchRoot, searchFilter,
                    new Object[]{bindPrincipal});
        } catch (IncorrectResultSizeDataAccessException incorrectResults) {
            if (incorrectResults.getActualSize() == 0) {
                UsernameNotFoundException userNameNotFoundException = new UsernameNotFoundException("User " + username + " not found in directory.", username);
                userNameNotFoundException.initCause(incorrectResults);
                throw badCredentials(userNameNotFoundException);
            }
            throw incorrectResults;
        }
    }

    private String searchRootFromPrincipal(String bindPrincipal) {
        int atChar = bindPrincipal.lastIndexOf('@');

        if (atChar < 0) {
            logger.debug("User principal '" + bindPrincipal + "' does not contain the domain, and no domain has been configured");
            throw badCredentials();
        }

        return rootDnFromDomain(bindPrincipal.substring(atChar + 1, bindPrincipal.length()));
    }

    private String rootDnFromDomain(String domain) {
        String[] tokens = StringUtils.tokenizeToStringArray(domain, ".");
        StringBuilder root = new StringBuilder();

        for (String token : tokens) {
            if (root.length() > 0) {
                root.append(',');
            }
            root.append("dc=").append(token);
        }

        return root.toString();
    }

    String createBindPrincipal(String username) {
        if (domain == null || username.toLowerCase().endsWith(domain)) {
            return username;
        }

        return username + "@" + domain;
    }

    public void setConvertSubErrorCodesToExceptions(boolean convertSubErrorCodesToExceptions) {
        this.convertSubErrorCodesToExceptions = convertSubErrorCodesToExceptions;
    }

    static class ContextFactory {
        DirContext createContext(Hashtable<?, ?> env) throws NamingException {
            return new InitialLdapContext(env, null);
        }
    }
}