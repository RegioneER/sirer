import it.cineca.siss.axmr3.authentication.IanusUserService;
import it.cineca.siss.axmr3.authentication.impl.AuthorityImpl;
import it.cineca.siss.axmr3.authentication.services.SissUserService;
import org.junit.runner.RunWith;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.authentication.encoding.PasswordEncoder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

import java.util.List;

import static org.junit.Assert.*;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 24/10/13
 * Time: 15:56
 * To change this template use File | Settings | File Templates.
 */
@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration(locations = {"classpath:test-applicationContext.xml", "classpath*:applicationContext.xml"})
public class IanusUserServiceTest {

    @Autowired
    protected PasswordEncoder passwordEncoder;

    public PasswordEncoder getPasswordEncoder() {
        return passwordEncoder;
    }

    public void setPasswordEncoder(PasswordEncoder passwordEncoder) {
        this.passwordEncoder = passwordEncoder;
    }

    @Autowired
    protected SissUserService service;

    public SissUserService getService() {
        return service;
    }

    public void setService(SissUserService service) {
        this.service = service;
    }
    /*
    @Test
    public void getUserTest(){
        UserDetails user = service.loadUserByUsername("aiello");
        it.cineca.siss.axmr3.log.Log.info(getClass(),user);
    }
    */

    @Test
    public void passTest(){
        String encoded="$2a$12$IKpC/6GD42E4RBynoOwr5.XmPLqs4I5wJn7294F5FLydxLnFCz5iO";
        String plain="test123;";
        assertTrue(passwordEncoder.isPasswordValid(encoded, plain, null));
    }

    @Test
    public void passTest1(){
        String encoded="$apr1$i9u.....$DxX1fN.uTUk49i5B3EaX7.";
        String plain="TeST";
        assertTrue(passwordEncoder.isPasswordValid(encoded, plain, null));
    }

    @Test
    public void passTest2(){
        String encoded="$apr1$i9u.....$DxX1fN.uTUk49i5B3EaX7.";
        String plain="xxx";
        assertFalse(passwordEncoder.isPasswordValid(encoded, plain, null));
    }

    @Test
    public void getGroupsTest(){
        List<Object> ret;
        ret = service.listByWhereAndOrder("Authority", null, null, null);
        for (Object r:ret){
        }
    }

    @Test
    public void testClearUsername(){
    }

}
