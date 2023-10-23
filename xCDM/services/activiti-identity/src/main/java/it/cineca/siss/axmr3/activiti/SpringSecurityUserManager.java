package it.cineca.siss.axmr3.activiti;

import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.authentication.services.SissUserService;
import org.activiti.engine.ActivitiException;
import org.activiti.engine.ActivitiIllegalArgumentException;
import org.activiti.engine.identity.Group;
import org.activiti.engine.identity.User;
import org.activiti.engine.identity.UserQuery;
import org.activiti.engine.impl.Page;
import org.activiti.engine.impl.UserQueryImpl;
import org.activiti.engine.impl.context.Context;
import org.activiti.engine.impl.persistence.AbstractManager;
import org.activiti.engine.impl.persistence.entity.IdentityInfoEntity;
import org.activiti.engine.impl.persistence.entity.UserEntity;
import org.activiti.engine.impl.persistence.entity.UserIdentityManager;

import javax.naming.NamingException;
import javax.naming.directory.SearchControls;
import javax.naming.directory.SearchResult;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 20/10/13
 * Time: 10:04
 * To change this template use File | Settings | File Templates.
 */
public class SpringSecurityUserManager extends AbstractManager implements UserIdentityManager {

    protected it.cineca.siss.axmr3.authentication.services.SissUserService userService;

    protected SpringSecurityConfigurator configurator;

    public SpringSecurityUserManager(SpringSecurityConfigurator configurator) {
        this.configurator=configurator;

    }

    public SissUserService getUserService() {
        return userService;
    }

    public void setUserService(SissUserService userService) {
        this.userService = userService;
    }

    
    public User createNewUser(String userId) {
        throw new ActivitiException("LDAP user manager doesn't support creating a new user");
    }


    
    public void insertUser(User user) {
        throw new ActivitiException("LDAP user manager doesn't support inserting a new user");
    }


    
    public void updateUser(UserEntity updatedUser) {
        throw new ActivitiException("LDAP user manager doesn't support updating a user");
    }


    
    public UserEntity findUserById(final String userId) {
        IUser user=(IUser) userService.loadUserByUsername(userId);
        UserEntity u=new UserEntity();
        u.setId(user.getUsername());
        u.setEmail(user.getEmail());
        u.setFirstName(user.getFirstName());
        u.setLastName(user.getLastName());
        u.setPassword(user.getPassword());
        return u;
    }


    
    public void deleteUser(String userId) {
        throw new ActivitiException("LDAP user manager doesn't support deleting a user");
    }


    
    public List<User> findUserByQueryCriteria(final UserQueryImpl query, final Page page) {

        if (query.getId() != null) {
            List<User> result = new ArrayList<User>();
            result.add(findUserById(query.getId()));
            return result;
        } else if (query.getFullNameLike() != null){
                    //TODO: da fare
            return null;

        } else {
            throw new ActivitiIllegalArgumentException("Query is currently not supported by LDAPUserManager.");
        }

    }

    protected void mapSearchResultToUser( SearchResult result, UserEntity user) throws NamingException {
        user.setId(result.getAttributes().get(configurator.getUserIdAttribute()).get().toString());
    }


    
    public long findUserCountByQueryCriteria(UserQueryImpl query) {
        return findUserByQueryCriteria(query, null).size(); // Is there a generic way to do counts in ldap?
    }


    
    public List<Group> findGroupsByUser(String userId) {
        throw new ActivitiException("LDAP user manager doesn't support querying");
    }


    
    public UserQuery createNewUserQuery() {
        return new UserQueryImpl(Context.getProcessEngineConfiguration().getCommandExecutor());
    }


    
    public IdentityInfoEntity findUserInfoByUserIdAndKey(String userId, String key) {
        throw new ActivitiException("LDAP user manager doesn't support querying");
    }


    
    public List<String> findUserInfoKeysByUserIdAndType(String userId, String type) {
        throw new ActivitiException("LDAP user manager doesn't support querying");
    }


    
    public List<User> findPotentialStarterUsers(String proceDefId) {
        throw new ActivitiException("LDAP user manager doesn't support querying");
    }


    
    public List<User> findUsersByNativeQuery(Map<String, Object> parameterMap, int firstResult, int maxResults) {
        throw new ActivitiException("LDAP user manager doesn't support querying");
    }


    
    public long findUserCountByNativeQuery(Map<String, Object> parameterMap) {
        throw new ActivitiException("LDAP user manager doesn't support querying");
    }

    
    public Boolean checkPassword(final String userId, final String password) {
        try {
            IUser user=(IUser) userService.loadUserByUsername(userId);
            return userService.isPasswordValid(user.getPassword(), password, null);
        } catch (ActivitiException e) {
            return false;
        }
    }

    protected SearchControls createSearchControls() {
        SearchControls searchControls = new SearchControls();
        searchControls.setSearchScope(SearchControls.SUBTREE_SCOPE);
        searchControls.setTimeLimit(configurator.getSearchTimeLimit());
        return searchControls;
    }


}
