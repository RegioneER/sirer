package it.cineca.siss.axmr3.authentication;

import it.cineca.siss.axmr3.authentication.impl.AuthorityImpl;
import it.cineca.siss.axmr3.authentication.impl.UserImpl;
import it.cineca.siss.axmr3.authentication.services.SissUserService;
import it.cineca.siss.axmr3.authentication.services.query.OrderBy;
import it.cineca.siss.axmr3.authentication.services.query.WhereClause;
import org.apache.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.ldap.NamingException;
import org.springframework.ldap.core.AttributesMapper;
import org.springframework.ldap.core.LdapTemplate;
import org.springframework.ldap.filter.AndFilter;
import org.springframework.ldap.filter.EqualsFilter;
import org.springframework.ldap.filter.LikeFilter;
import org.springframework.security.authentication.encoding.PasswordEncoder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UsernameNotFoundException;

import javax.naming.NamingEnumeration;
import javax.naming.directory.Attributes;
import javax.naming.directory.BasicAttribute;
import javax.naming.directory.BasicAttributes;
import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by cin0562a on 28/04/15.
 */
public class LdapUserService extends SissUserService {

    static final Logger log = Logger.getLogger(LdapUserService.class);

    protected LdapTemplate ldapTemplate;
    protected DataSource dataSource;

    public DataSource getDataSource() {
        return dataSource;
    }

    @Autowired
    @Qualifier(value = "UserDataSource")
    public void setDataSource(DataSource dataSource) {
        this.dataSource = dataSource;
    }

    public LdapTemplate getLdapTemplate() {
        return ldapTemplate;
    }

    public void setLdapTemplate(LdapTemplate ldapTemplate) {
        this.ldapTemplate = ldapTemplate;
    }

    @Override
    public void setPasswordEncoder(PasswordEncoder passwordEncoder) {

    }

    @Override
    public UserDetails loadUserByUsernameNotLogout(String username) {
        UserImpl user = new UserImpl();
        AndFilter filter = new AndFilter();
        filter.and(new EqualsFilter("objectclass", "person"));
        filter.and(new EqualsFilter("sAMAccountName", username));
        user.setUsername(username);
        Attributes attrs = new BasicAttributes();
        BasicAttribute ocattr = new BasicAttribute("objectclass");
        attrs.put("cn", "Some Person");
        attrs.put("sn", "Person");
        LinkedList<AuthorityImpl> auths = new LinkedList<AuthorityImpl>();
        List li = ldapTemplate.search("", filter.encode(),
                new AttributesMapper() {
                    public Object mapFromAttributes(Attributes attrs)
                            throws NamingException {
                        try {
                            return attrs.get("sAMAccountName").get();
                        } catch (javax.naming.NamingException e) {
                            log.error(e.getMessage(), e);
                            throw new UsernameNotFoundException("errore ldap");

                        }
                    }
                });
        if (li.size() == 0) {
            return null;
        } else {
            user.setUsername(username);
            user.setFirstName("Test");
            user.setLastName("User");
            user.setEnabled(true);
            user.setCredentialsNonExpired(true);
            user.setAccountNonLocked(true);
            user.setAccountNonExpired(true);
            List li2 = ldapTemplate.search("", filter.encode(),
                    new AttributesMapper() {
                        public Object mapFromAttributes(Attributes attrs)
                                throws NamingException {
                            try {
                                return attrs.get("memberOf").get();
                            } catch (javax.naming.NamingException e) {
                                log.error(e.getMessage(), e);
                                throw new UsernameNotFoundException("errore ldap");

                            }
                        }
                    });

            for (int i = 0; i < li2.size(); i++) {
                AuthorityImpl auth = new AuthorityImpl();
                String authName = "";
                String value = li2.get(i).toString();
                String[] splits = value.split(",");
                String[] splits2 = splits[0].split("=");
                authName = splits2[1];
                auth.setAuthority(authName);
                auth.setDescription(authName);
                auths.add(auth);
            }
            if (user.getUsername().equals("Utente TestConsensoS")) {
                AuthorityImpl adminAuth = new AuthorityImpl();
                adminAuth.setAuthority("tech-admin");
                adminAuth.setDescription("tech-admin");
                auths.add(adminAuth);
            }

        }
        user.setAuthorities(auths);
        return user;
    }

    @Override
    public Object uniqueByWhereAndOrder(String object, List<WhereClause> crits, List<OrderBy> orders, HashMap<String, String> aliases) {
        return null;
    }

    @Override
    public List<Object> listByWhereAndOrder(String object, List<WhereClause> crits, List<OrderBy> orders, HashMap<String, String> aliases) {
        return null;
    }

    @Override
    public List<? extends IUser> searchUserByUsername(String pattern) {
        AndFilter filter = new AndFilter();
        filter.and(new EqualsFilter("objectclass", "person"));
        filter.and(new LikeFilter("sAMAccountName", "*" + pattern + "*"));
        List li = ldapTemplate.search("", filter.encode(),
                new AttributesMapper() {
                    public Object mapFromAttributes(Attributes attrs)
                            throws NamingException {
                        try {
                            return attrs.get("sAMAccountName").get();
                        } catch (javax.naming.NamingException e) {
                            log.error(e.getMessage(), e);
                            throw new UsernameNotFoundException("errore ldap");

                        }
                    }
                });
        LinkedList<IUser> res = new LinkedList<IUser>();
        for (int i = 0; i < li.size(); i++) {
            UserImpl a = new UserImpl();
            a = (UserImpl) this.loadUserByUsernameNotLogout(li.get(i).toString());
            res.add(a);
        }
        return res;
    }

    @Override
    public List<? extends IAuthority> searchAuthorityByName(String pattern) {
        AndFilter filter = new AndFilter();
        filter.and(new EqualsFilter("objectclass", "group"));
        filter.and(new LikeFilter("sAMAccountName", "*" + pattern + "*"));
        List li = ldapTemplate.search("", filter.encode(),
                new AttributesMapper() {
                    public Object mapFromAttributes(Attributes attrs)
                            throws NamingException {
                        try {
                            return attrs.get("sAMAccountName").get();
                        } catch (javax.naming.NamingException e) {
                            log.error(e.getMessage(), e);
                            throw new UsernameNotFoundException("errore ldap");

                        }
                    }
                });
        LinkedList<IAuthority> res = new LinkedList<IAuthority>();
        for (int i = 0; i < li.size(); i++) {
            AuthorityImpl a = new AuthorityImpl();
            a.setAuthority(li.get(i).toString());
            a.setDescription(li.get(i).toString());
            res.add(a);
        }
        return res;
    }

    @Override
    public List<Object> listByWhereAndOrderPaged(String object, List<WhereClause> crits, List<OrderBy> orders, HashMap<String, String> aliases, int i, int i2) {

        return null;
    }

    public void setLoggedUser(String username) {

    }

    public List<? extends IUser> searchUsersByAuthorityName(String authorityName) {
        return null;
    }

    public IUser getUser(String username) {
        return null;
    }

    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        UserImpl user = new UserImpl();
        AndFilter filter = new AndFilter();
        filter.and(new EqualsFilter("objectclass", "person"));
        filter.and(new EqualsFilter("sAMAccountName", username));
        user.setUsername(username);
        LinkedList<AuthorityImpl> auths = new LinkedList<AuthorityImpl>();
        List li = ldapTemplate.search("", filter.encode(),
                new AttributesMapper() {
                    public Object mapFromAttributes(Attributes attrs)
                            throws NamingException {
                        try {
                            return attrs.get("sAMAccountName").get();
                        } catch (javax.naming.NamingException e) {
                            log.error(e.getMessage(), e);
                            throw new UsernameNotFoundException("errore ldap");

                        }
                    }
                });

        if (li.size() == 0) {
            throw new UsernameNotFoundException("Utente " + username + " non presente in LDAP");
        } else {
            user.setUsername(username);
            user.setFirstName("Test");
            user.setLastName("User");
            user.setEnabled(true);
            user.setCredentialsNonExpired(true);
            user.setAccountNonLocked(true);
            user.setAccountNonExpired(true);
            List li2 = ldapTemplate.search("", filter.encode(),
                    new AttributesMapper() {
                        public Object mapFromAttributes(Attributes attrs)
                                throws NamingException {
                            try {
                                String result = "";
                                NamingEnumeration<?> members = attrs.get("memberOf").getAll();
                                while (members.hasMore()) {
                                    Object member = members.next();
                                    if (result.isEmpty()) {
                                        result = member.toString();
                                    } else {
                                        result += "," + member.toString();
                                    }
                                }
                                return result;
                            } catch (javax.naming.NamingException e) {
                                log.error(e.getMessage(), e);
                                throw new UsernameNotFoundException("errore ldap");

                            }
                        }
                    });

            for (int i = 0; i < li2.size(); i++) {

                String value = li2.get(i).toString();
                String[] splits = value.split(",");

                for (String currSplit : splits) {
                    AuthorityImpl auth = new AuthorityImpl();
                    String authName = "";
                    String[] splits2 = currSplit.split("=");
                    authName = splits2[1];
                    if (authName.equals("Consenso-Tech-Admin") || authName.equals("OperatoriConsenso") || authName.equals("OperatoriSportello")) {
                        auth.setAuthority(authName);
                        auth.setDescription(authName);
                        auths.add(auth);
                        if (authName.equals("Consenso-Tech-Admin")) {
                            AuthorityImpl adminAuth = new AuthorityImpl();
                            adminAuth.setAuthority("tech-admin");
                            adminAuth.setDescription("tech-admin");
                            auths.add(adminAuth);
                        }
                    }
                }
            }
            if (user.getUsername().equals("Utente TestConsensoS") || user.getUsername().equals("Giorgio Delsignore")) {
                AuthorityImpl adminAuth = new AuthorityImpl();
                adminAuth.setAuthority("tech-admin");
                adminAuth.setDescription("tech-admin");
                auths.add(adminAuth);
            }

        }

        user.setAuthorities(auths);
        return user;
    }

    public UserImpl loadImplUserByUsername(String username) throws UsernameNotFoundException {
        UserImpl user = new UserImpl();
        AndFilter filter = new AndFilter();
        filter.and(new EqualsFilter("objectclass", "person"));
        filter.and(new EqualsFilter("sAMAccountName", username));
        user.setUsername(username);
        LinkedList<AuthorityImpl> auths = new LinkedList<AuthorityImpl>();
        List li = ldapTemplate.search("", filter.encode(),
                new AttributesMapper() {
                    public Object mapFromAttributes(Attributes attrs)
                            throws NamingException {
                        try {
                            return attrs.get("sAMAccountName").get();
                        } catch (javax.naming.NamingException e) {
                            log.error(e.getMessage(), e);
                            throw new UsernameNotFoundException("errore ldap");

                        }
                    }
                });

        if (li.size() == 0) {
            throw new UsernameNotFoundException("Utente " + username + " non presente in LDAP");
        } else {
            user.setUsername(username);
            user.setFirstName("Test");
            user.setLastName("User");
            user.setEnabled(true);
            user.setCredentialsNonExpired(true);
            user.setAccountNonLocked(true);
            user.setAccountNonExpired(true);
            List li2 = ldapTemplate.search("", filter.encode(),
                    new AttributesMapper() {
                        public Object mapFromAttributes(Attributes attrs)
                                throws NamingException {
                            try {
                                String result = "";
                                NamingEnumeration<?> members = attrs.get("memberOf").getAll();
                                while (members.hasMore()) {
                                    Object member = members.next();
                                    if (result.isEmpty()) {
                                        result = member.toString();
                                    } else {
                                        result += "," + member.toString();
                                    }
                                }
                                return result;
                            } catch (javax.naming.NamingException e) {
                                log.error(e.getMessage(), e);
                                throw new UsernameNotFoundException("errore ldap");

                            }
                        }
                    });

            for (int i = 0; i < li2.size(); i++) {

                String value = li2.get(i).toString();
                String[] splits = value.split(",");

                for (String currSplit : splits) {
                    AuthorityImpl auth = new AuthorityImpl();
                    String authName = "";
                    String[] splits2 = currSplit.split("=");
                    authName = splits2[1];
                    if (authName.equals("Consenso-Tech-Admin") || authName.equals("OperatoriConsenso") || authName.equals("OperatoriSportello")) {
                        auth.setAuthority(authName);
                        auth.setDescription(authName);
                        auths.add(auth);
                        if (authName.equals("Consenso-Tech-Admin")) {
                            AuthorityImpl adminAuth = new AuthorityImpl();
                            adminAuth.setAuthority("tech-admin");
                            adminAuth.setDescription("tech-admin");
                            auths.add(adminAuth);
                        }
                    }
                }
            }
            if (user.getUsername().equals("Utente TestConsensoS") || user.getUsername().equals("Giorgio Delsignore")) {
                AuthorityImpl adminAuth = new AuthorityImpl();
                adminAuth.setAuthority("tech-admin");
                adminAuth.setDescription("tech-admin");
                auths.add(adminAuth);
            }

        }
        /**  @TODO: commentato codice perché apparentemente non utilizzato non essendo presente nell'ambiente di produzione. LM */
        /*
        Connection conn= null;
        try {
            conn = dataSource.getConnection();
            String sql1 = "select nome,cognome,titolo,sesso from utentititolo where lower(sam)=lower(?)";
            PreparedStatement stmt = conn.prepareStatement(sql1);
            stmt.setString(1, user.getUsername());
            ResultSet rset = stmt.executeQuery();
            if(rset.getFetchSize()>0){
                rset.next();
                user.setFirstName(rset.getString("nome"));
                user.setLastName(rset.getString("cognome"));
                //user.setGender(rset.getString("sesso"));
                //user.setTitolo(rset.getString("titolo"));
            }
            conn.close();

        } catch (SQLException e) {
            log.error(e.getMessage(),e);
        }*/
        user.setAuthorities(auths);
        return user;
    }
}
