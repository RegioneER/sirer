package it.cineca.siss.axmr3.activiti.implementations;

import it.cineca.siss.axmr3.authentication.services.SissUserService;
import it.cineca.siss.axmr3.authentication.services.query.OrderBy;
import it.cineca.siss.axmr3.authentication.services.query.WhereClause;
import org.hibernate.Criteria;
import org.hibernate.criterion.Criterion;
import org.hibernate.criterion.DetachedCriteria;
import org.hibernate.criterion.Restrictions;

import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 20/10/13
 * Time: 19:11
 * To change this template use File | Settings | File Templates.
 */
public abstract class BaseQuery<T>{

    protected SissUserService service;

    public BaseQuery(SissUserService userService) {
        this.service=userService;
    }

    public SissUserService getService() {
        return service;
    }

    public void setService(SissUserService service) {
        this.service = service;
    }

    private List<WhereClause> crits=new LinkedList<WhereClause>();
    private List<OrderBy> orders=new LinkedList<OrderBy>();
    protected HashMap<String, String> aliases=new HashMap<String, String>();

    public BaseQuery(BaseQuery<T> parent, WhereClause crit, OrderBy order) {
        if (parent.crits.size()>0){
            for (WhereClause c:parent.crits){
                crits.add(c);
            }
        }
        if (crit!=null) crits.add(crit);
        if (parent.orders!=null) {
            for (OrderBy o:parent.orders){
                orders.add(o);
            }
        }
        Iterator<String> it=parent.aliases.keySet().iterator();
        while (it.hasNext()){
            String key=it.next();
            this.aliases.put(key, parent.aliases.get(key));
        }
        this.addAlias();
        if (order!=null) orders.add(order);
        this.service=parent.service;
    }

    public BaseQuery(){}

    public abstract String getObject();

    public Criterion listToAndCriterion(List<Criterion> list){
        if (list.size()==1) return list.get(0);
        if (list.size()==2) return Restrictions.and(list.get(0), list.get(1));
        else {
            Criterion c=list.get(0);
            list.remove(0);
            return Restrictions.and(c, listToAndCriterion(list));
        }

    }

    public abstract void addAlias();


    /*
    public DetachedCriteria getDetachedCriteria(){
        it.cineca.siss.axmr3.log.Log.info(getClass(),"passo da "+new Object(){}.getClass().getEnclosingMethod().getName());
        DetachedCriteria c=DetachedCriteria.forClass(getEntityClass());
        c.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);
        c=addAlias(c);
        if (crits.size()>0) c.add(listToAndCriterion(crits));
        return c;
    }
    */







    public long count() {
        return list().size();
    }

    public T singleResult() {
        return toSingleReturn(service.uniqueByWhereAndOrder(getObject(), crits, orders, this.aliases));
    }

    public abstract T toSingleReturn(Object obj);

    public abstract List<T> toReturnList(List<Object> list);

    public List<T> list() {

        return toReturnList(service.listByWhereAndOrder(getObject(), crits, orders, this.aliases));
    }

    public List<T> listPage(int i, int i2) {
        List<Object> users=service.listByWhereAndOrderPaged(getObject(), crits, orders, this.aliases, i, i2);
        return toReturnList(users);
    }


}
