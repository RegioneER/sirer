package it.cineca.siss.axmr3.authentication;

import it.cineca.siss.axmr3.authentication.entities.User;
import org.apache.http.auth.AuthScope;
import org.apache.http.auth.UsernamePasswordCredentials;
import org.apache.http.impl.client.BasicCredentialsProvider;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.client.ClientHttpRequestFactory;
import org.springframework.http.client.HttpComponentsClientHttpRequestFactory;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.web.client.RestTemplate;

import java.net.URI;
import java.net.URISyntaxException;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 31/05/13
 * Time: 15.10
 * To change this template use File | Settings | File Templates.
 */
public class UserServiceRestClient implements UserDetailsService {

    protected static Logger log=Logger.getLogger(UserServiceRestClient.class);

    @Autowired
    protected AuthServerBean service;

    public AuthServerBean getService() {
        return service;
    }

    public void setService(AuthServerBean service) {
        this.service = service;
    }

    public User loadUserByUsername(String username) throws UsernameNotFoundException {
        UsernamePasswordCredentials cred = new UsernamePasswordCredentials(this.service.getAdminUsername(), this.service.getAdminPassword());
        BasicCredentialsProvider cp = new BasicCredentialsProvider();
        cp.setCredentials(AuthScope.ANY, cred);
        DefaultHttpClient client = new DefaultHttpClient();
        client.setCredentialsProvider(cp);
        ClientHttpRequestFactory factory = new HttpComponentsClientHttpRequestFactory(client);
        RestTemplate restTemplate = new RestTemplate(factory);
        try {
            User user= restTemplate.getForObject(new URI(this.service.getUrl()+"/userService/getUserDetail/"+username), User.class);
            if (user==null) throw new UsernameNotFoundException("User not found");
            else return user;
        } catch (URISyntaxException e) {
            log.error(e.getMessage(),e);
            throw new UsernameNotFoundException("Host not found");
        }

    }
}
