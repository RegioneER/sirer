package it.cineca.siss.axmr3.authentication;

import it.cineca.siss.axmr3.authentication.entities.Authority;
import it.cineca.siss.axmr3.authentication.entities.User;
import it.cineca.siss.axmr3.authentication.impl.UserImpl;
import it.cineca.siss.axmr3.authentication.services.SissUserService;
import it.cineca.siss.axmr3.authentication.services.query.OrderBy;
import it.cineca.siss.axmr3.authentication.services.query.WhereClause;
import org.apache.log4j.Logger;
import org.hibernate.Criteria;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.criterion.DetachedCriteria;
import org.hibernate.criterion.Order;
import org.hibernate.criterion.Restrictions;
import org.springframework.beans.factory.InitializingBean;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.security.authentication.encoding.PasswordEncoder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.transaction.annotation.Transactional;

import java.io.Serializable;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 31/05/13
 * Time: 11.07
 * To change this template use File | Settings | File Templates.
 */
@Transactional(value = "userTransactionManager")
public class UserService extends SissUserService implements InitializingBean, Serializable {

    protected static Logger log = Logger.getLogger(UserService.class);

    @Autowired
    @Qualifier(value = "userSessionFactory")
    protected SessionFactory sessionFactory;
    private UserDAO dao;

    public SessionFactory getSessionFactory() {
        return sessionFactory;
    }

    public void setSessionFactory(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }

    public User loadUserByUsername(String username) throws UsernameNotFoundException {
        try {
            User user = this.getUserByUsername(username);
            if (user == null) throw new UsernameNotFoundException("Utente " + username + " non trovato");
            else return user;
        } catch (Exception ex) {
            throw new UsernameNotFoundException(ex.getMessage());
        }
    }

    public User getUserByUsername(String username) {
        User user = dao.getByUsername(username);
        return user;
    }

    public void afterPropertiesSet() throws Exception {
        try {
            Session session = sessionFactory.openSession();
            if (!session.isOpen()) throw new ExceptionInInitializerError("Non riesco ad aprire la sessione");
        } catch (Exception ex) {
            throw new ExceptionInInitializerError("Non riesco ad aprire la sessione");
        }
        dao = new UserDAO(sessionFactory);
    }

    @Override
    public List<User> searchUserByUsername(String pattern) {
        return dao.searchUserByUsername(pattern);
    }

    @Override
    public List<Authority> searchAuthorityByName(String pattern) {
        return dao.searchAuthorityByName(pattern);
    }

    @Override
    public List<Object> listByWhereAndOrderPaged(String object, List<WhereClause> crits, List<OrderBy> orders, HashMap<String, String> aliases, int i, int i2) {
        return listByWhereAndOrder(object, crits, orders, aliases);  //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public void setLoggedUser(String username) {

    }

    public List<? extends IUser> searchUsersByAuthorityName(String authorityName) {
        Criteria c = dao.getSession().createCriteria(User.class);
        c.createAlias("authorities", "auths");
        authorityName = authorityName.toUpperCase();
        c.add(Restrictions.eq("auths.authority", authorityName).ignoreCase());
        return c.list();
    }

    public IUser getUser(String username) {
        try {
            IUser user = dao.getByUsername(username);
            return user;
        } catch (Exception ex) {
            return null;
        }
    }

    @Override
    @Autowired
    public void setPasswordEncoder(PasswordEncoder passwordEncoder) {
        this.passwordEncoder = passwordEncoder;
    }

    public UserDetails loadUserByUsernameNotLogout(String username) {
        try {
            IUser user = dao.getByUsername(username);
            return user;
        } catch (Exception ex) {
            return null;
        }
    }

    public Criteria createCriteria(String object, List<WhereClause> crits, List<OrderBy> orders, HashMap<String, String> aliases) {
        Criteria c = null;
        if (object.equals("User")) c = dao.getSession().createCriteria(User.class);
        if (object.equals("Authority")) c = dao.getSession().createCriteria(Authority.class);
        Iterator<String> aKeys = aliases.keySet().iterator();
        while (aKeys.hasNext()) {
            String key = aKeys.next();
            if (c != null) {
                c.createAlias(key, aliases.get(key));
            }
        }
        for (WhereClause clause : crits) {
            if (clause.getClauseType().equals("eq") && c != null)
                c.add(Restrictions.eq(clause.getFieldName(), clause.getPattern()));
            if (clause.getClauseType().equals("ilike") && c != null)
                c.add(Restrictions.like(clause.getFieldName(), clause.getPattern()).ignoreCase());
        }
        for (OrderBy o : orders) {
            if (o.getOrderType().equals("asc") && c != null) c.addOrder(Order.asc(o.getFieldName()));
            if (o.getOrderType().equals("desc") && c != null) c.addOrder(Order.desc(o.getFieldName()));
        }
        return c;
    }

    @Override
    public Object uniqueByWhereAndOrder(String object, List<WhereClause> crits, List<OrderBy> orders, HashMap<String, String> aliases) {
        Criteria c = createCriteria(object, crits, orders, aliases);
        return c.uniqueResult();
    }

    @Override
    public List<Object> listByWhereAndOrder(String object, List<WhereClause> crits, List<OrderBy> orders, HashMap<String, String> aliases) {
        Criteria c = createCriteria(object, crits, orders, aliases);
        return c.list();
    }


}
