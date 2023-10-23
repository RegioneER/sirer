package it.cineca.siss.axmr3.authentication.providers;

import it.cineca.siss.axmr3.authentication.impl.UserImpl;
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
public class TrustedAuthenticationProvider extends AbstractUserDetailsAuthenticationProvider {

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
    /*Nessun controllo ulteriore da gestire*/
    }

    @Override
    protected UserDetails retrieveUser(String username, UsernamePasswordAuthenticationToken authentication) throws AuthenticationException {
        UserDetails loadedUser;
        logger.debug("Esecuzione retrieveUser di "+this.getClass().getName());
        logger.warn("TRUSTED AUTH PROVIDER - RETRIEVE USER - "+username);
        try {
            loadedUser = this.getUserDetailsService().loadUserByUsername(username);
        } catch (UsernameNotFoundException notFound) {
            logger.error(notFound.getMessage(), notFound);
            throw notFound;
        } catch (Exception repositoryProblem) {
            logger.error(repositoryProblem.getMessage(), repositoryProblem);
            throw new AuthenticationServiceException(repositoryProblem.getMessage(), repositoryProblem);
        }
        logger.warn("TRUSTEDAUTH: Utente "+username+" autenticato con successo!!!");
        userDetailsService.setLoggedUser(username);
        logger.warn("USERNAME LOGGATO INSERITO IN USERDETAIL SERVICE, TORNO LOADED USER!");
        ((UserImpl)loadedUser).setCredentialsNonExpired(true);
        return loadedUser;
    }



}