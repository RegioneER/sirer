package it.cineca.siss.axmr3.authentication;

import it.cineca.siss.axmr3.authentication.entities.Authority;
import it.cineca.siss.axmr3.authentication.entities.User;
import org.apache.log4j.Logger;
import org.hibernate.Criteria;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.criterion.DetachedCriteria;
import org.hibernate.criterion.Projections;
import org.hibernate.criterion.Restrictions;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 31/05/13
 * Time: 19.49
 * To change this template use File | Settings | File Templates.
 */
@Transactional("userTransactionManager")
public class UserDAO {

    protected static Logger log=Logger.getLogger(UserDAO.class);

    protected SessionFactory sessionFactory;

    public UserDAO() {
    }

    public UserDAO(SessionFactory sessionFactory) {

        this.sessionFactory = sessionFactory;
    }

    public SessionFactory getSessionFactory() {
        return sessionFactory;
    }

    public void setSessionFactory(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }

    public Session getSession(){
          return sessionFactory.getCurrentSession();
    }

    public User getByUsername(String username){
        try{
            Criteria c=getSession().createCriteria(User.class);
            c.add(Restrictions.eq("username",username));
            return (User) c.uniqueResult();
        }catch (Exception ex){
            log.error(ex.getMessage(), ex);
            return null;
        }
    }

    public void delete(Object obj){
        getSession().delete(obj);
    }

    public void delete(String username){
        getSession().delete(getByUsername(username));
    }

    public Object save(Object obj){
        getSession().saveOrUpdate(obj);
        return obj;
    }

    public Authority getAuthByName(String name){
        Criteria c=getSession().createCriteria(Authority.class);
        c.add(Restrictions.eq("authority", name));
        return (Authority) c.uniqueResult();
    }

    public Authority saveAuthority(String name, String description){
        Authority auth=getAuthByName(name);
        if (auth==null){
            auth=new Authority();
            auth.setAuthority(name);
        }
        auth.setDescription(description);
        auth= (Authority) save(auth);
        return auth;
    }

    public void deleteAuthority(String name){
        delete(getAuthByName(name));
    }

    public List<User> searchUserByUsername(String pattern){
        Criteria c=getSession().createCriteria(User.class);
        c.add(Restrictions.like("username", '%'+pattern+'%').ignoreCase());
        return c.list();
    }

    public List<Authority> searchAuthorityByName(String pattern){
        Criteria c=getSession().createCriteria(Authority.class);
        c.add(Restrictions.like("authority", "%"+pattern+"%").ignoreCase());
        return c.list();
    }


    public List<Object> listByCriteria(DetachedCriteria crit) {
        return crit.getExecutableCriteria(getSession()).list();

    }

    public Object uniqueByCriteria(DetachedCriteria crit) {
        return crit.getExecutableCriteria(getSession()).uniqueResult();
    }

    public long countByCriteria(DetachedCriteria crit){
        return (Long) crit.getExecutableCriteria(getSession()).setProjection(Projections.rowCount()).uniqueResult();
    }

    public List<Object> listByCriteriaPaging(DetachedCriteria crit, int i, int i2) {
        Criteria c=crit.getExecutableCriteria(getSession());
        c.setFirstResult(i);
        c.setMaxResults(i2);
        return crit.getExecutableCriteria(getSession()).list();

    }


}
