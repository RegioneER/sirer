package it.cineca.siss.axmr3.activiti.implementations;

import it.cineca.siss.axmr3.activiti.SpringSecurityUserBridge;
import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.authentication.services.SissUserService;
import it.cineca.siss.axmr3.authentication.services.query.OrderBy;
import it.cineca.siss.axmr3.authentication.services.query.WhereClause;
import org.activiti.engine.identity.User;
import org.activiti.engine.identity.UserQuery;
import org.hibernate.criterion.Criterion;
import org.hibernate.criterion.DetachedCriteria;
import org.hibernate.criterion.Restrictions;

import java.util.LinkedList;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 20/10/13
 * Time: 15:36
 * To change this template use File | Settings | File Templates.
 */

public class SpringSecurityUserQuery extends BaseQuery<User> implements UserQuery {

    public SpringSecurityUserQuery(SissUserService userService) {
        super(userService);
    }

    public SpringSecurityUserQuery(BaseQuery parent, WhereClause crit, OrderBy order) {
        super(parent, crit, order);
    }

    public SpringSecurityUserQuery() {
    }

    
    public UserQuery userId(String s) {
        return new SpringSecurityUserQuery(this, new WhereClause("username", s, "eq"), null);
    }

    
    public UserQuery userFirstName(String s) {
        return new SpringSecurityUserQuery(this, new WhereClause("firstName", s, "eq"), null);
    }

    
    public UserQuery userFirstNameLike(String s) {
        return new SpringSecurityUserQuery(this, new WhereClause("firstName", s, "ilike"), null);
    }

    
    public UserQuery userLastName(String s) {
        return new SpringSecurityUserQuery(this, new WhereClause("lastName", s, "eq"), null);
    }

    
    public UserQuery userLastNameLike(String s) {
        return new SpringSecurityUserQuery(this, new WhereClause("lastName", s, "ilike"), null);
    }

    
    public UserQuery userFullNameLike(String s) {
        return new SpringSecurityUserQuery(this, new WhereClause("username", s, "ilike"), null);
    }

    
    public UserQuery userEmail(String s) {
        return new SpringSecurityUserQuery(this, new WhereClause("email", s, "eq"), null);
    }

    
    public UserQuery userEmailLike(String s) {
        return new SpringSecurityUserQuery(this, new WhereClause("email", s, "ilike"), null);
    }

    
    public UserQuery memberOfGroup(String s) {
        return new SpringSecurityUserQuery(this, new WhereClause("authorities.authority", s, "eq"), null);  //To change body of implemented methods use File | Settings | File Templates.
    }

    
    public UserQuery potentialStarter(String s) {
        return new SpringSecurityUserQuery(this, null, null);  //To change body of implemented methods use File | Settings | File Templates.
    }

    
    public UserQuery orderByUserId() {
        return new SpringSecurityUserQuery(this,null,new OrderBy("username", "asc"));
    }

    
    public UserQuery orderByUserFirstName() {
        return new SpringSecurityUserQuery(this,null,new OrderBy("firstName", "asc"));
    }

    
    public UserQuery orderByUserLastName() {
        return new SpringSecurityUserQuery(this,null,new OrderBy("lastName", "asc"));
    }

    
    public UserQuery orderByUserEmail() {
        return new SpringSecurityUserQuery(this,null,new OrderBy("email", "asc"));
    }


    
    public String getObject() {
        return "User";
    }

    
    public User toSingleReturn(Object obj) {
        return new SpringSecurityUserBridge((IUser) obj);

    }

    
    public List<User> toReturnList(List<Object> list) {
        List<User> res=new LinkedList<User>();
        for (Object u:list){
            res.add(new SpringSecurityUserBridge((IUser) u));
        }
        return res;

    }

    public UserQuery asc() {
        return this;
    }

    public UserQuery desc() {
        return this;
    }

    public void addAlias(){
        this.aliases.put("authorities", "authorities");
    }


}
