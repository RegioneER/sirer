package it.cineca.siss.axmr3.authentication.providers;

import it.cineca.siss.axmr3.authentication.services.SissUserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.authentication.BadCredentialsException;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.authentication.dao.AbstractUserDetailsAuthenticationProvider;
import org.springframework.security.core.AuthenticationException;
import org.springframework.security.core.userdetails.UserDetails;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 31/05/13
 * Time: 15.17
 * To change this template use File | Settings | File Templates.
 */
public class UsernamePasswordProvider extends
        AbstractUserDetailsAuthenticationProvider {

    @Autowired
    protected SissUserService userDetailsService;

    @Override
    protected void doAfterPropertiesSet() throws Exception {
        super.doAfterPropertiesSet();
        if (this.userDetailsService==null) throw new Exception("Bisogna impostare un UserDetailService");
    }

    @Override
    protected void additionalAuthenticationChecks(UserDetails userDetails,
                                                  UsernamePasswordAuthenticationToken authentication)
            throws AuthenticationException {
        logger.info(" --> Inizio autenticazione per: "+userDetails.getUsername()+"");
        if (authentication.getCredentials() == null) {
            logger.debug("Authentication failed: no credentials provided");
            throw new BadCredentialsException("Credenziali non presenti");
        }

        String presentedPassword = authentication.getCredentials().toString();
        if (!userDetailsService.isPasswordValid(userDetails.getPassword(), presentedPassword,null)) {
            logger.debug("La password non coincide");
            throw new BadCredentialsException("Credenziali errate");
        }
        logger.info("Utente "+userDetails.getUsername()+" autenticato con successo!!!");
        userDetailsService.setLoggedUser(userDetails.getUsername());
    }

    @Override
    protected UserDetails retrieveUser(String username,
                                       UsernamePasswordAuthenticationToken authToken)
            throws AuthenticationException {
        return this.getUserDetailsService().loadUserByUsername(username);
    }

    public SissUserService getUserDetailsService() {
        return userDetailsService;
    }

    public void setUserDetailsService(SissUserService userDetailsService) {
        this.userDetailsService = userDetailsService;
    }
}
