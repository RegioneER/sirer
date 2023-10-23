package it.cineca.siss.axmr3.activiti.implementations;

import it.cineca.siss.axmr3.activiti.SpringSecurityGroupBridge;
import it.cineca.siss.axmr3.authentication.IAuthority;
import it.cineca.siss.axmr3.authentication.services.SissUserService;
import it.cineca.siss.axmr3.authentication.services.query.OrderBy;
import it.cineca.siss.axmr3.authentication.services.query.WhereClause;
import org.activiti.engine.identity.Group;
import org.activiti.engine.identity.GroupQuery;
import org.hibernate.criterion.Criterion;
import org.hibernate.criterion.DetachedCriteria;
import org.hibernate.criterion.Order;
import org.hibernate.criterion.Restrictions;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 20/10/13
 * Time: 18:35
 * To change this template use File | Settings | File Templates.
 */
public class SpringSecurityGroupQuery extends BaseQuery<Group> implements GroupQuery {

    public GroupQuery asc() {
        return this;
    }

    public GroupQuery desc() {
        return this;
    }

    public SpringSecurityGroupQuery(SissUserService userService) {
        super(userService);
    }

    public SpringSecurityGroupQuery(BaseQuery parent, WhereClause crit, OrderBy order) {
        super(parent, crit, order);
    }

    public SpringSecurityGroupQuery() {
    }

    
    public GroupQuery groupId(String s) {
        return new SpringSecurityGroupQuery(this, new WhereClause("authority", s, "eq"), null);
    }

    
    public GroupQuery groupName(String s) {
        return new SpringSecurityGroupQuery(this, new WhereClause("authority", s, "eq"), null);
    }

    
    public GroupQuery groupNameLike(String s) {
        return new SpringSecurityGroupQuery(this, new WhereClause("authority", s, "ilike"), null);
    }

    
    public GroupQuery groupType(String s) {
        return new SpringSecurityGroupQuery(this, new WhereClause("authority", s, "eq"), null);
    }

    
    public GroupQuery groupMember(String s) {
        return new SpringSecurityGroupQuery(this, new WhereClause("users.username", s, "eq"), null);  //To change body of implemented methods use File | Settings | File Templates.
    }

    
    public GroupQuery potentialStarter(String s) {
        return new SpringSecurityGroupQuery(this, null, null);  //To change body of implemented methods use File | Settings | File Templates.
    }

    
    public GroupQuery orderByGroupId() {
        return new SpringSecurityGroupQuery(this, null, new OrderBy("authority", "asc"));  //To change body of implemented methods use File | Settings | File Templates.
    }

    
    public GroupQuery orderByGroupName() {
        return new SpringSecurityGroupQuery(this, null, new OrderBy("authority", "asc"));  //To change body of implemented methods use File | Settings | File Templates.
    }

    
    public GroupQuery orderByGroupType() {
        return new SpringSecurityGroupQuery(this, null, new OrderBy("authority", "asc"));  //To change body of implemented methods use File | Settings | File Templates.
    }

    
    public String getObject() {
        return "Authority";
    }

    
    public Group toSingleReturn(Object obj) {
        return new SpringSecurityGroupBridge((IAuthority) obj);
    }

    
    public List toReturnList(List<Object> list) {
        List<Group> res=new LinkedList<Group>();
        for (Object u:list){
            res.add(new SpringSecurityGroupBridge((IAuthority) u));
        }
        return res;
    }

    public void addAlias(){
        this.aliases.put("users", "users");
    }


}
