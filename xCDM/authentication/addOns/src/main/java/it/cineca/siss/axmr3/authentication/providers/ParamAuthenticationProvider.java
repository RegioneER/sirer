package it.cineca.siss.axmr3.authentication.providers;

import it.cineca.siss.axmr3.authentication.services.SissUserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.authentication.AuthenticationServiceException;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.authentication.dao.AbstractUserDetailsAuthenticationProvider;
import org.springframework.security.core.AuthenticationException;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UsernameNotFoundException;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 25/10/13
 * Time: 12:53
 * To change this template use File | Settings | File Templates.
 */
public class ParamAuthenticationProvider extends AbstractUserDetailsAuthenticationProvider {

    @Autowired
    protected SissUserService userDetailsService;

    public void setUserDetailsService(SissUserService userDetailsService) {
        this.userDetailsService = userDetailsService;
    }

    public SissUserService getUserDetailsService() {
        return userDetailsService;
    }

    @Override
    protected void additionalAuthenticationChecks(UserDetails userDetails, UsernamePasswordAuthenticationToken authentication) throws AuthenticationException {
    }

    @Override
    protected UserDetails retrieveUser(String username, UsernamePasswordAuthenticationToken authentication) throws AuthenticationException {
        UserDetails loadedUser;
        logger.debug("Esecuzione retrieveUser di "+this.getClass().getName());
        try {
            loadedUser = this.getUserDetailsService().loadUserByUsername(username);
        } catch (UsernameNotFoundException notFound) {
            throw notFound;
        } catch (Exception repositoryProblem) {
            throw new AuthenticationServiceException(repositoryProblem.getMessage(), repositoryProblem);
        }
        logger.debug("Utente "+username+" autenticato con successo!!!");
        return loadedUser;
    }



}