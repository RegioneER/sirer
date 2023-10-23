package it.cineca.siss.axmr3.authentication.tests;

import it.cineca.siss.axmr3.authentication.UserDAO;
import it.cineca.siss.axmr3.authentication.entities.Authority;
import it.cineca.siss.axmr3.authentication.entities.User;
import junit.framework.Assert;
import org.hibernate.SessionFactory;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;
import org.springframework.test.context.transaction.TransactionConfiguration;
import org.springframework.transaction.annotation.Transactional;

import java.util.Collection;
import java.util.LinkedList;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 31/05/13
 * Time: 19.54
 * To change this template use File | Settings | File Templates.
 */
@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration(locations = {"classpath:test-applicationContext.xml", "classpath*:applicationContext.xml"})
@TransactionConfiguration(transactionManager = "userTransactionManager")
@Transactional
public class userDAOTest {

    @Autowired
    public SessionFactory sessionFactory;

    @Before
    @Transactional
    public void setUp(){
        Authority a=new Authority();
        a.setAuthority("ADMIN");
        User user=new User();
        user.setAccountNonExpired(true);
        user.setAccountNonLocked(true);
        user.setCredentialsNonExpired(true);
        user.setEnabled(true);
        user.setUsername("testUser");
        user.setPassword("xxx");
        UserDAO d=new UserDAO(sessionFactory);
        if (user.getAuthorities()==null) user.setAuthorities(new LinkedList<Authority>());
        user.getAuthorities().add(a);
        d.save(user);
    }

    @After
    @Transactional
    public void deleteUser(){
        UserDAO d=new UserDAO();
        d.setSessionFactory(sessionFactory);
        sessionFactory.getCurrentSession().delete(d.getByUsername("testUser"));
    }

    @Test
    public void testGetUser(){
        UserDAO d=new UserDAO();
        d.setSessionFactory(sessionFactory);
        User user=d.getByUsername("testUser");
        Assert.assertEquals("Controllo username", "testUser", user.getUsername());
        boolean found=false;
        for (Authority a:(Collection<Authority>)user.getAuthorities()){
            if (a.getAuthority().equals("ADMIN")) found=true;
        }
        Assert.assertTrue("Controllo presenza policy", found);
        found=false;
        Assert.assertTrue("Controllo presenza policy", found);
    }

}
