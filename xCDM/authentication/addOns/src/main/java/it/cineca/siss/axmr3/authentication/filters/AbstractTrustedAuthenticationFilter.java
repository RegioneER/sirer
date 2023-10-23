package it.cineca.siss.axmr3.authentication.filters;

import it.cineca.siss.axmr3.authentication.exceptions.TrustedUserNotFoundException;
import org.springframework.context.ApplicationEventPublisher;
import org.springframework.context.ApplicationEventPublisherAware;
import org.springframework.security.authentication.AuthenticationDetailsSource;
import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.authentication.event.InteractiveAuthenticationSuccessEvent;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.AuthenticationException;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.web.WebAttributes;
import org.springframework.security.web.authentication.WebAuthenticationDetailsSource;
import org.springframework.util.Assert;
import org.springframework.web.filter.GenericFilterBean;

import javax.servlet.FilterChain;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 25/10/13
 * Time: 11:38
 * To change this template use File | Settings | File Templates.
 */
public abstract class AbstractTrustedAuthenticationFilter extends GenericFilterBean
        implements ApplicationEventPublisherAware {

    private ApplicationEventPublisher eventPublisher = null;
    private AuthenticationDetailsSource<HttpServletRequest, ?> authenticationDetailsSource = new WebAuthenticationDetailsSource();
    protected AuthenticationManager authenticationManager = null;
    private boolean continueFilterChainOnUnsuccessfulAuthentication = true;
    private boolean continueFilterChainOnSuccessfulAuthentication = true;
    private boolean checkForPrincipalChanges;
    private boolean invalidateSessionOnPrincipalChange = true;
    protected String username;

    public boolean isCheckForPrincipalChanges() {
        return checkForPrincipalChanges;
    }

    public ApplicationEventPublisher getEventPublisher() {
        return eventPublisher;
    }

    public void setEventPublisher(ApplicationEventPublisher eventPublisher) {
        this.eventPublisher = eventPublisher;
    }

    /**
     * Check whether all required properties have been set.
     */
    @Override
    public void afterPropertiesSet() {
        Assert.notNull(authenticationManager, "An AuthenticationManager must be set");
    }

    public abstract String getTrustedUsername(ServletRequest request) throws TrustedUserNotFoundException;

    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws IOException, ServletException {
        try {
            username = getTrustedUsername(request);
            if (requiresAuthentication((HttpServletRequest) request)) {
                doAuthenticate((HttpServletRequest) request, (HttpServletResponse) response);
            }
        } catch (TrustedUserNotFoundException e) {
        } finally {
            chain.doFilter(request, response);
        }
    }

    private void doAuthenticate(HttpServletRequest request,
                                HttpServletResponse response) {
        Authentication authResult;

        Object principal = username;
        if (principal == null) {
            logger.debug("No pre-authenticated principal found in request");
            return;
        }
        logger.debug("preAuthenticatedPrincipal = " + principal+ ", trying to authenticate");
        try {
            UsernamePasswordAuthenticationToken authRequest = new UsernamePasswordAuthenticationToken(principal, null, null);
            authRequest.setDetails(authenticationDetailsSource.buildDetails(request));
            authResult = authenticationManager.authenticate(authRequest);
            logger.debug("Utente "+principal+" autenticato con successo da "+this.getClass().getCanonicalName());
            successfulAuthentication(request, response, authResult);
        } catch (AuthenticationException failed) {
            logger.info("Utente "+principal+" NON autenticato con successo da "+this.getClass().getCanonicalName(), failed);
            unsuccessfulAuthentication(request, response, failed);
            if (!continueFilterChainOnUnsuccessfulAuthentication) {
                throw failed;
            }
        }
    }

    private boolean requiresAuthentication(HttpServletRequest request) {
        Authentication currentUser = SecurityContextHolder.getContext().getAuthentication();
        if (currentUser == null) {
            return true;
        }

        Object principal = username;

        logger.debug("---requiresAuthentication: " + currentUser.getName() + " -> " + principal);
        if (currentUser.getName().equals(principal)) {
            return false;
        }

        logger.debug("Pre-authenticated principal has changed to " + principal + " and will be reauthenticated");

        if (invalidateSessionOnPrincipalChange) {
            HttpSession session = request.getSession(false);
            if (session != null) {
                logger.debug("Invalidating existing session");
                session.invalidate();
                request.getSession();
            }
        }
        return true;
    }

    protected void successfulAuthentication(HttpServletRequest request,
                                            HttpServletResponse response, Authentication authResult) {
        logger.debug("Authentication success: " + authResult);
        SecurityContextHolder.getContext().setAuthentication(authResult);
        if (this.eventPublisher != null) {
            eventPublisher.publishEvent(new InteractiveAuthenticationSuccessEvent(authResult, this.getClass()));
        }
    }

    protected void unsuccessfulAuthentication(HttpServletRequest request,
                                              HttpServletResponse response, AuthenticationException failed) {
        SecurityContextHolder.clearContext();
        logger.debug("Cleared security context due to exception", failed);
        request.setAttribute(WebAttributes.AUTHENTICATION_EXCEPTION, failed);
    }

    public void setApplicationEventPublisher(
            ApplicationEventPublisher anApplicationEventPublisher) {
        this.eventPublisher = anApplicationEventPublisher;
    }

    public void setAuthenticationDetailsSource(
            AuthenticationDetailsSource<HttpServletRequest, ?> authenticationDetailsSource) {
        Assert.notNull(authenticationDetailsSource, "AuthenticationDetailsSource required");
        this.authenticationDetailsSource = authenticationDetailsSource;
    }

    protected AuthenticationDetailsSource<HttpServletRequest, ?> getAuthenticationDetailsSource() {
        return authenticationDetailsSource;
    }

    public void setAuthenticationManager(
            AuthenticationManager authenticationManager) {
        this.authenticationManager = authenticationManager;
    }

    public void setContinueFilterChainOnUnsuccessfulAuthentication(
            boolean shouldContinue) {
        continueFilterChainOnUnsuccessfulAuthentication = shouldContinue;
    }

    public void setCheckForPrincipalChanges(boolean checkForPrincipalChanges) {
        this.checkForPrincipalChanges = checkForPrincipalChanges;
    }

    public void setInvalidateSessionOnPrincipalChange(
            boolean invalidateSessionOnPrincipalChange) {
        this.invalidateSessionOnPrincipalChange = invalidateSessionOnPrincipalChange;
    }

    public boolean isContinueFilterChainOnSuccessfulAuthentication() {
        return continueFilterChainOnSuccessfulAuthentication;
    }

    public void setContinueFilterChainOnSuccessfulAuthentication(
            boolean continueFilterChainOnSuccessfulAuthentication) {
        this.continueFilterChainOnSuccessfulAuthentication = continueFilterChainOnSuccessfulAuthentication;
    }

}