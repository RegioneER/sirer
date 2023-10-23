package it.cineca.siss.axmr3.hibernate;

import it.cineca.siss.axmr3.exceptions.AxmrGenericException;
import it.cineca.siss.axmr3.transactions.MultiSessionTXManager;
import org.hibernate.Criteria;
import org.hibernate.Session;
import org.hibernate.criterion.DetachedCriteria;
import org.hibernate.criterion.Projections;
import org.hibernate.criterion.Restrictions;

import java.lang.reflect.ParameterizedType;
import java.util.LinkedList;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 26/07/13
 * Time: 14.30
 * To change this template use File | Settings | File Templates.
 */
public class BaseDao<T extends BaseEntity> {

    protected Session session;

    public BaseDao(MultiSessionTXManager tx, String name) {
        setSession(tx, name);
    }

    public BaseDao(MultiSessionTXManager tx, String name, Class<T> persistentClass) {
        setSession(tx, name);
        this.persistentClass = persistentClass;
    }

    public Session getSession() {
        return session;
    }

    public void setSession(Session session) {
        this.session = session;
    }

    public void setSession(MultiSessionTXManager tx, String name) {
        this.session = tx.getSession(name);
    }


    private Class<T> persistentClass;

    public void setPersistentClass(Class<T> persistentClass) {
        this.persistentClass = persistentClass;
    }

    public Class<T> getPersistentClass() {
        if (persistentClass == null) {
            this.persistentClass = (Class<T>) ((ParameterizedType) getClass().getGenericSuperclass()).getActualTypeArguments()[0];
        }
        return persistentClass;
    }

    public T getById(Long id) {
        return (T) session.get(getPersistentClass(), id);
    }

    public List<T> getAll() {
        Criteria c = getSession().createCriteria(getPersistentClass());
        return c.list();
    }

    public Criteria getCriteria() {
        return getSession().createCriteria(getPersistentClass());
    }

    public DetachedCriteria getDetachedCriteria() {
        return DetachedCriteria.forClass(getPersistentClass());
    }

    public DetachedCriteria getDetachedCriteria(String alias) {
        return DetachedCriteria.forClass(getPersistentClass(), alias);
    }

    public Criteria getCriteria(String alias) {
        return getSession().createCriteria(getPersistentClass(), alias);
    }

    public void save(T obj) throws AxmrGenericException {
        try {
            getSession().save(obj);
        } catch (Exception ex) {
            throw new AxmrGenericException(ex.getMessage());
        }
    }

    public void saveOrUpdate(T obj) throws AxmrGenericException {
        try {
            getSession().saveOrUpdate(obj);
        } catch (Exception ex) {
            throw new AxmrGenericException(ex.getMessage());
        }
    }

    public void delete(T obj) throws AxmrGenericException {
        try {
            getSession().delete(obj);
        } catch (org.hibernate.exception.ConstraintViolationException ex1) {
            throw new AxmrGenericException(ex1.getMessage());
        } catch (Exception ex) {
            throw new AxmrGenericException(ex.getMessage());
        }
    }

    public void persist(T obj) throws AxmrGenericException {
        try {
            getSession().persist(obj);
        } catch (Exception ex) {
            throw new AxmrGenericException(ex.getMessage());
        }
    }

    public void merge(T obj) throws AxmrGenericException {
        try {
            getSession().merge(obj);
        } catch (Exception ex) {
            throw new AxmrGenericException(ex.getMessage());
        }
    }

    public List<T> getCriteriaList(DetachedCriteria c) {
        return c.getExecutableCriteria(getSession()).list();
    }

    public Object getCriteriaUniqueResult(DetachedCriteria c) {
        return c.getExecutableCriteria(getSession()).uniqueResult();
    }

    public List<T> getFixedResultSize(DetachedCriteria dcriteria, int start, int limit, int total) {
        it.cineca.siss.axmr3.log.Log.info(getClass(),"Sono in getFixedResultSize");
        it.cineca.siss.axmr3.log.Log.info(getClass(),"start = "+String.valueOf(start));
        it.cineca.siss.axmr3.log.Log.info(getClass(),"limit = "+String.valueOf(limit));
        it.cineca.siss.axmr3.log.Log.info(getClass(),"total = "+String.valueOf(total));
        Criteria criteria = dcriteria.getExecutableCriteria(getSession());
        criteria.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);
        criteria.setProjection(Projections.property("id"));
        List<Long> ids = criteria.list();
        List<Long> pagedIds = new LinkedList<Long>();
        List<Long> appoggio = new LinkedList<Long>();
        int i = 0;
        for (i = 0; i < ids.size(); i++) {
            if (!appoggio.contains(ids.get(i))) appoggio.add(ids.get(i));
        }
        for (i = start; i < appoggio.size(); i++) {
            Long id = appoggio.get(i);
            if (i < start + limit) {
                pagedIds.add(id);
            }
        }
        criteria.setProjection(null);
        if (pagedIds.size() == 0) return new LinkedList<T>();
        criteria.add(Restrictions.in("id", pagedIds));
        criteria.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);
        return criteria.list();
        /* Rotta
        Criteria criteria = dcriteria.getExecutableCriteria(getSession());
        int margin=limit;
        int difference=limit;
        int limitForQuery=limit+margin;
        criteria.setProjection(null);
        criteria.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);
        criteria.setFirstResult(start);
        List<T> results=new LinkedList<T>();
        while(total>0 && difference>0 && limitForQuery<=(total+difference+margin)){
            it.cineca.siss.axmr3.log.Log.info(getClass(),"getFixedResultSize limit "+String.valueOf(limitForQuery));
            results = (List<T>) criteria.setMaxResults(limitForQuery).list();
            if(results.size()==0){
                break;
            }else if(results.size()>limit){
                results=results.subList(0,limit);
            }
            difference=limit-results.size();
            limitForQuery=limitForQuery+difference+margin;
        }
        return results;
        */
    }


}
