package it.cineca.siss.axmr3.activiti;

import it.cineca.siss.axmr3.authentication.IAuthority;
import it.cineca.siss.axmr3.authentication.IUser;
import org.activiti.engine.ActivitiException;
import org.activiti.engine.ActivitiIllegalArgumentException;
import org.activiti.engine.identity.Group;
import org.activiti.engine.identity.GroupQuery;
import org.activiti.engine.impl.GroupQueryImpl;
import org.activiti.engine.impl.Page;
import org.activiti.engine.impl.context.Context;
import org.activiti.engine.impl.persistence.AbstractManager;
import org.activiti.engine.impl.persistence.entity.GroupEntity;
import org.activiti.engine.impl.persistence.entity.GroupIdentityManager;

import javax.naming.directory.SearchControls;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 20/10/13
 * Time: 10:04
 * To change this template use File | Settings | File Templates.
 */
public class SpringSecurityGroupManager extends AbstractManager implements GroupIdentityManager {

    protected it.cineca.siss.axmr3.authentication.services.SissUserService userService;

    protected SpringSecurityConfigurator configurator;

    public SpringSecurityGroupManager(SpringSecurityConfigurator configurator) {
        this.configurator=configurator;
    }

    public Group createNewGroup(String groupId) {
        throw new ActivitiException("LDAP group manager doesn't support creating a new group");
    }

    public void insertGroup(Group group) {
        throw new ActivitiException("LDAP group manager doesn't support inserting a group");
    }

    public void updateGroup(GroupEntity updatedGroup) {
        throw new ActivitiException("LDAP group manager doesn't support updating a group");
    }

    public void deleteGroup(String groupId) {
        throw new ActivitiException("LDAP group manager doesn't support deleting a group");
    }

    public GroupQuery createNewGroupQuery() {
        return new GroupQueryImpl(Context.getProcessEngineConfiguration().getCommandExecutor());
    }

    public List<Group> findGroupByQueryCriteria(GroupQueryImpl query, Page page) {
        // Only support for groupMember() at the moment
        if (query.getUserId() != null) {
            return findGroupsByUser(query.getUserId());
        } else {
            throw new ActivitiIllegalArgumentException("This query is not supported by the LDAPGroupManager");
        }
    }

    public long findGroupCountByQueryCriteria(GroupQueryImpl query) {
        return findGroupByQueryCriteria(query, null).size(); // Is there a generic way to do a count(*) in ldap?
    }

    public List<Group> findGroupsByUser(final String userId) {
        IUser user=(IUser) userService.loadUserByUsername(userId);
        List<Group> groups=new LinkedList<Group>();
        for (IAuthority auth:user.getAuthorities()){
            groups.add(new SpringSecurityGroupBridge(auth));
        }
        return groups;
    }

    public List<Group> findGroupsByNativeQuery(Map<String, Object> parameterMap, int firstResult, int maxResults) {
        throw new ActivitiException("LDAP group manager doesn't support querying");
    }

    public long findGroupCountByNativeQuery(Map<String, Object> parameterMap) {
        throw new ActivitiException("LDAP group manager doesn't support querying");
    }

    protected SearchControls createSearchControls() {
        SearchControls searchControls = new SearchControls();
        searchControls.setSearchScope(SearchControls.SUBTREE_SCOPE);
        searchControls.setTimeLimit(configurator.getSearchTimeLimit());
        return searchControls;
    }

}
