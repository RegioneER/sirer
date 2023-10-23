package it.cineca.siss.axmr3.authentication.filters;

import it.cineca.siss.axmr3.authentication.exceptions.TrustedUserNotFoundException;
import org.apache.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;

import javax.servlet.ServletRequest;
import javax.servlet.http.HttpServletRequest;
import java.util.Enumeration;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 25/10/13
 * Time: 11:39
 * To change this template use File | Settings | File Templates.
 */
public class HeaderAuthenticationFilter extends
        AbstractTrustedAuthenticationFilter {
    private String principalRequestHeader = "REMOTE_USERID";
    protected static final Logger log=Logger.getLogger(HeaderAuthenticationFilter.class);

    public void setPrincipalRequestHeader(String principalRequestHeader) {
        this.principalRequestHeader = principalRequestHeader;
    }

    @Autowired
    @Qualifier(value = "idServizio")
    protected String idServizio;

    public String getIdServizio() {
        return idServizio;
    }

    public void setIdServizio(String idServizio) {
        this.idServizio = idServizio;
    }

    @Override
    public String getTrustedUsername(ServletRequest request)
            throws TrustedUserNotFoundException {
        HttpServletRequest httpRequest = (HttpServletRequest) request;
        if (httpRequest.getHeader(principalRequestHeader)!=null && !httpRequest.getHeader(principalRequestHeader).isEmpty()){
            String username = httpRequest.getHeader(principalRequestHeader).replace("@"+idServizio, "");
            log.debug("Trovato header: "+principalRequestHeader+": "+username);
            return username;
        }
        if (httpRequest.getHeader("authz-uid")!=null && !httpRequest.getHeader("authz-uid").isEmpty()){
            String username=httpRequest.getHeader("authz-uid").replaceAll("@"+idServizio+"(.*)", "");
            log.debug("Trovato header AUTHZ-UID: "+username);
            return username;
        }
        log.warn("NON SONO RIUSCITO A TROVARE USERNAME VALIDO!");
        throw new TrustedUserNotFoundException("Header "+ principalRequestHeader + "/auhz-uid non presente o vuoto");
    }

}
