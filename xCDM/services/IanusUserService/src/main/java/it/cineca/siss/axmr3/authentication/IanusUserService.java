package it.cineca.siss.axmr3.authentication;

import it.cineca.siss.axmr3.authentication.impl.AuthorityImpl;
import it.cineca.siss.axmr3.authentication.impl.UserImpl;
import it.cineca.siss.axmr3.authentication.services.SissUserService;
import it.cineca.siss.axmr3.authentication.services.query.OrderBy;
import it.cineca.siss.axmr3.authentication.services.query.WhereClause;
import org.apache.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.security.authentication.AuthenticationServiceException;
import org.springframework.security.authentication.encoding.PasswordEncoder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UsernameNotFoundException;

import javax.sql.DataSource;
import java.sql.*;
import java.util.*;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 24/10/13
 * Time: 15:14
 * To change this template use File | Settings | File Templates.
 */
public class IanusUserService extends SissUserService {

    @Autowired
    @Qualifier(value = "idServizio")
    protected String idServizio;

    protected String prefix;

    protected String userANAQuery;
    protected String userSITEQuery;

    static final Logger log = Logger.getLogger(IanusUserService.class);

    public String getPrefix() {
        return prefix;
    }

    @Autowired
    @Qualifier(value = "xCdmPrefix")
    public void setPrefix(String prefix) {
        this.prefix = prefix;
        userQuery = "select " +
                "a.nome firstName, " +
                "a.cognome lastName, " +
                "a.email email, " +
                "u.password password, " +
                "u.userid username, " +
                "1 enabled,\n" +
                "0 inactive, \n" +
                "1 credentialNonExpired, \n" +
                "a.azienda_ente ente " +
                "from ana_utenti a, utenti u\n" +
                "where a.userid=u.userid";
        userANAQuery = "select " +
                "a.*, " +
                "u.userid username, " +
                "1 enabled,\n" +
                "0 inactive, \n" +
                "1 credentialNonExpired\n" +
                "from ana_utenti a, utenti u\n" +
                "where a.userid=u.userid";
        userSITEQuery = "select u.userid,s.* " +
                "from sites s, ana_utenti u  where s.code=u.COD_AZIENDA";
        groupQuery = "select id_gruppou, SUBSTR(nome_gruppo, LENGTH('" + prefix + "')+2, LENGTH(nome_gruppo)) authority, descrizione description from ana_gruppiu where replace(nome_gruppo,'_','#') like '" + prefix + "#%'";
        fromJoined = "from (\n" +
                "select a.nome firstName, a.cognome lastName, a.email email, u.password password, u.userid username, \n" +
                "1 enabled,\n" +
                "0 inactive,\n" +
                "1 credentialNonExpired\n" +
                "from ana_utenti a, utenti u\n" +
                "where a.userid=u.userid) users,\n" +
                "(" + groupQuery + ") authorities,\n" +
                "utenti_gruppiu ug\n" +
                "where ug.id_gruppou=authorities.id_gruppou and ug.userid=users.username and ug.abilitato=1";
    }

    public String getIdServizio() {
        return idServizio;
    }

    public void setIdServizio(String idServizio) {
        this.idServizio = idServizio;
    }

    protected String userQuery;

    protected String groupQuery;

    protected String fromJoined;

    @Autowired
    @Qualifier(value = "UserDataSource")
    protected DataSource dataSource;

    public DataSource getDataSource() {
        return dataSource;
    }

    public void setDataSource(DataSource dataSource) {
        this.dataSource = dataSource;
    }


    @Override
    @Autowired
    public void setPasswordEncoder(PasswordEncoder passwordEncoder) {
        this.passwordEncoder = passwordEncoder;
    }

    @Override
    public UserDetails loadUserByUsernameNotLogout(String username) {
        return getUser(username);
    }

    public IanusUserService() {
    }

    public PreparedStatement createQueryByWhereAndOrder(Connection conn, String object, List<WhereClause> crits, List<OrderBy> orders, HashMap<String, String> aliases, int first, int last) throws SQLException {
        last = first + last;
        String sqlQuery = "";
        if (object == "User") sqlQuery = "select users.username " + fromJoined;
        if (object == "Authority") sqlQuery = "select authorities.id_gruppou " + fromJoined;
        if (crits != null)
            for (WhereClause c : crits) {
                if (c.getClauseType().equals("eq")) sqlQuery += " and UPPER(" + c.getFieldName() + ")=?";
                if (c.getClauseType().equals("ilike")) sqlQuery += " and UPPER(" + c.getFieldName() + ") like ?";
            }


        if (object == "User") sqlQuery = "select * from (" + userQuery + ") q where q.username in (" + sqlQuery + ")";
        if (object == "Authority")
            sqlQuery = "select * from (" + groupQuery + ") q where q.id_gruppou in (" + sqlQuery + ")";
        if (orders != null && orders.size() > 0) {
            sqlQuery += " order by";
            int i = 0;
            for (OrderBy o : orders) {
                if (i > 0) sqlQuery += ", ";
                sqlQuery += " " + o.getFieldName() + " " + o.getOrderType();
                i++;
            }
        }
        if (last > 0) {
            sqlQuery = "select * from (select t.*, rownum nr from (" + sqlQuery + ") t) where nr between " + first + " and " + last;
        }
        PreparedStatement stmt = conn.prepareStatement(sqlQuery);
        if (crits != null)
            for (int i = 0; i < crits.size(); i++) {
                stmt.setString(i + 1, crits.get(i).getPattern());
            }
        return stmt;
    }

    public List<Object> getUsersByJoinQueryResultSet(ResultSet rset) throws SQLException {
        List<Object> ret = new LinkedList<Object>();
        HashMap<String, UserImpl> users = new HashMap<String, UserImpl>();
        while (rset.next()) {
            String username = rset.getString(5);
            if (!users.containsKey(username)) {
                UserImpl user = new UserImpl();
                user.setFirstName(rset.getString(1));
                user.setLastName(rset.getString(2));
                user.setEmail(rset.getString(3));
                user.setPassword(rset.getString(4));

                user.setEnte(rset.getString(9));
                user.setUsername(username);
                if (rset.getInt(6) == 1) user.setEnabled(true);
                else user.setEnabled(false);
                //A questo livello non faccio mai scadere l'utenza, delle due è il CAS che mi blocca
                user.setAccountNonExpired(true);
                user.setCredentialsNonExpired(true);
                //if (rset.getInt(7) == 1) user.setAccountNonExpired(false);
                //else user.setAccountNonExpired(true);
                //if (rset.getInt(8) == 1) user.setCredentialsNonExpired(true);
                //else user.setCredentialsNonExpired(false);
                users.put(username, user);
            }
        }
        Iterator<String> it = users.keySet().iterator();
        while (it.hasNext()) {
            String username = it.next();
            ret.add(users.get(username));
        }
        return ret;
    }


    public List<Object> getGroupsByJoinQueryResultSet(ResultSet rset) throws SQLException {

        List<Object> ret = new LinkedList<Object>();
        HashMap<String, AuthorityImpl> auths = new HashMap<String, AuthorityImpl>();
        while (rset.next()) {
            String authority = rset.getString(2);
            if (!auths.containsKey(authority)) {
                AuthorityImpl auth = new AuthorityImpl();
                auth.setId(rset.getLong(1));
                auth.setAuthority(rset.getString(2));
                auth.setDescription(rset.getString(3));
                auths.put(authority, auth);
            }
        }
        Iterator<String> it = auths.keySet().iterator();
        while (it.hasNext()) {
            String authority = it.next();
            ret.add(auths.get(authority));
        }
        return ret;
    }

    @Override
    public Object uniqueByWhereAndOrder(String object, List<WhereClause> crits, List<OrderBy> orders, HashMap<String, String> aliases) {
        Connection conn = null;
        try {
            conn = dataSource.getConnection();
            if (object.equals("User")) {
                ResultSet rset = createQueryByWhereAndOrder(conn, object, crits, orders, aliases, 0, 0).executeQuery();
                List<Object> usersList = getUsersByJoinQueryResultSet(rset);
                if (usersList != null && usersList.size() > 0) {
                    return usersList.get(0);
                } else return null;
            }
            if (object.equals("Authority")) {
                ResultSet rset = createQueryByWhereAndOrder(conn, object, crits, orders, aliases, 0, 0).executeQuery();
                List<Object> usersList = getGroupsByJoinQueryResultSet(rset);
                if (usersList != null && usersList.size() > 0) {
                    return usersList.get(0);
                } else return null;
            }
        } catch (SQLException e) {
            log.error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
        } finally {
            if (conn != null) {
                try {
                    Logger.getLogger(this.getClass()).debug("IanusService (uniqueByWhereAndOrder) - Chiudo connessione IanusService");
                    conn.close();
                } catch (SQLException e) {
                    Logger.getLogger(this.getClass()).debug("IanusService (uniqueByWhereAndOrder) - Errore chiusura connessione");
                }
            } else {
                Logger.getLogger(this.getClass()).debug("IanusService (uniqueByWhereAndOrder) - Non trovo connessione aperta");
            }
        }
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    @Override
    public List<Object> listByWhereAndOrder(String object, List<WhereClause> crits, List<OrderBy> orders, HashMap<String, String> aliases) {
        Connection conn = null;
        try {
            conn = dataSource.getConnection();
            if (object.equals("User")) {
                ResultSet rset = createQueryByWhereAndOrder(conn, object, crits, orders, aliases, 0, 0).executeQuery();
                List<Object> usersList = getUsersByJoinQueryResultSet(rset);
                return usersList;
            }
            if (object.equals("Authority")) {
                ResultSet rset = createQueryByWhereAndOrder(conn, object, crits, orders, aliases, 0, 0).executeQuery();
                List<Object> usersList = getGroupsByJoinQueryResultSet(rset);
                return usersList;
            }
        } catch (SQLException e) {
            log.error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
        } finally {
            if (conn != null) {
                try {
                    Logger.getLogger(this.getClass()).debug("IanusService (listByWhereAndOrder) - Chiudo connessione IanusService");
                    conn.close();
                } catch (SQLException e) {
                    Logger.getLogger(this.getClass()).debug("IanusService (listByWhereAndOrder) - Errore chiusura connessione");
                }
            } else {
                Logger.getLogger(this.getClass()).debug("IanusService (listByWhereAndOrder) - Non trovo connessione aperta");
            }
        }
        return null;
    }

    @Override
    public List<? extends IUser> searchUserByUsername(String pattern) {
        try {
            List<IUser> users = new LinkedList<IUser>();
            String sqlQuery = "select * from (" + userQuery + ") where UPPER(username) like '%'||?||'%'";
            try (Connection conn = dataSource.getConnection()) {
                try (PreparedStatement stmt = conn.prepareStatement(sqlQuery)) {
                    stmt.setString(1, pattern.toUpperCase());
                    try (ResultSet rset = stmt.executeQuery()) {
                        List<Object> res = getUsersByJoinQueryResultSet(rset);
                        for (Object o : res) {
                            users.add((IUser) o);
                        }
                    }

                }

            }
            return users;
        } catch (SQLException e) {
            log.error(e);
        }
        return null;
    }

    @Override
    public List<? extends IAuthority> searchAuthorityByName(String pattern) {
        try {
            List<IAuthority> auths = new LinkedList<IAuthority>();
            String sqlQuery = "select * from (" + groupQuery + ") where UPPER(authority) like '%'||?||'%'";
            try (Connection conn = dataSource.getConnection()) {
                try (PreparedStatement stmt = conn.prepareStatement(sqlQuery)) {
                    stmt.setString(1, pattern.toUpperCase());
                    try (ResultSet rset = stmt.executeQuery()) {
                        List<Object> res = getGroupsByJoinQueryResultSet(rset);
                        for (Object o : res) {
                            auths.add((IAuthority) o);
                        }
                        return auths;
                    }
                }
            }
        } catch (SQLException e) {
            log.error(e);
        }
        return null;
    }

    @Override
    public List<Object> listByWhereAndOrderPaged(String object, List<WhereClause> crits, List<OrderBy> orders, HashMap<String, String> aliases, int i, int i2) {
        Connection conn = null;
        try {
            conn = dataSource.getConnection();
            if (object.equals("User")) {
                ResultSet rset = createQueryByWhereAndOrder(conn, object, crits, orders, aliases, i, i2).executeQuery();
                List<Object> usersList = getUsersByJoinQueryResultSet(rset);
                return usersList;
            }
            if (object.equals("Authority")) {
                ResultSet rset = createQueryByWhereAndOrder(conn, object, crits, orders, aliases, i, i2).executeQuery();
                List<Object> usersList = getGroupsByJoinQueryResultSet(rset);
                return usersList;
            }
        } catch (SQLException e) {
            log.error(e.getMessage(), e);
        } finally {
            if (conn != null) {
                try {
                    Logger.getLogger(this.getClass()).debug("IanusService (listByWhereAndOrderPaged) - Chiudo connessione IanusService");
                    conn.close();
                } catch (SQLException e) {
                    Logger.getLogger(this.getClass()).debug("IanusService (listByWhereAndOrderPaged) - Errore chiusura connessione");
                }
            } else {
                Logger.getLogger(this.getClass()).debug("IanusService (listByWhereAndOrderPaged) - Non trovo connessione aperta");
            }
        }
        return null;
    }

    @Override
    public void setLoggedUser(String username) {
        String update = "update utenti set DTTM_ULTIMOACCESSO=sysdate where userid=?";
        try {
            try (Connection conn = dataSource.getConnection()) {
                try (PreparedStatement stmt = conn.prepareStatement(update)) {
                    stmt.setString(1, username);
                    stmt.executeUpdate();
                    conn.commit();
                }
            }
        } catch (SQLException e) {
            throw new AuthenticationServiceException("Errore impostazione data di ultimo accesso");
        }
    }


    public UserImpl userFromRsetRow(ResultSet rset) throws SQLException {
        UserImpl user = new UserImpl();
        user.setFirstName(rset.getString(1));
        user.setLastName(rset.getString(2));
        user.setEmail(rset.getString(3));
        user.setPassword(rset.getString(4));
        user.setUsername(rset.getString(5));
        user.setEnte(rset.getString(9));
        if (rset.getInt(6) == 1) user.setEnabled(true);
        else user.setEnabled(false);
        //if (rset.getInt(7) == 1) user.setAccountNonExpired(false);
        //else user.setAccountNonExpired(true);
        //if (rset.getInt(8) == 1) user.setCredentialsNonExpired(true);
        //else user.setCredentialsNonExpired(false);
        //A questo livello non faccio mai scadere l'utenza, delle due è il CAS che mi blocca
        user.setAccountNonExpired(true);
        user.setCredentialsNonExpired(true);
        String sqlDelegationActive = "select count(*) as C from user_tables where table_name='USER_DELEGATION'";
        try (Connection conn = dataSource.getConnection()) {
            user.setAuthorities(loadGroupsForUser(user, conn));
            try {
                user.setAnaData(loadAnaDataForUser(user, conn));
            } catch (Exception ex) {
                log.error(ex.getMessage(), ex);
            }
            try {
                user.setSitesID(loadSitesForUser(user, conn));
                user.setSitesCodes(loadSitesCodesForUser(user, conn));
                user.setUOCodes(loadUOCodesForUser(user,conn));
            } catch (Exception ex) {
                log.error(ex.getMessage(), ex);
            }
            try {
                user.setSiteData(loadSiteDataForUser(user, conn));
            } catch (Exception ex) {
                log.error(ex.getMessage(), ex);
            }
            try (PreparedStatement stmt = conn.prepareStatement(sqlDelegationActive)) {
                try (ResultSet rset1 = stmt.executeQuery()) {
                    rset1.next();
                    if (rset1.getInt(1) == 1) {
                        String sqlDelegatedUser = "select * from (" + userQuery + ") users where UPPER(users.username)=(select ud.DELEGATED_BY from USER_DELEGATION ud where UPPER(ud.userid)=?)";
                        try (PreparedStatement stmt2 = conn.prepareStatement(sqlDelegatedUser)) {
                            stmt2.setString(1, user.getUsername().toUpperCase());
                            try (ResultSet rset2 = stmt2.executeQuery()) {
                                if (rset2.next()) {
                                    String loggedUserid = user.getUsername();
                                    //user.setFirstName(rset2.getString(1));
                                    //user.setLastName(rset2.getString(2));
                                    //user.setEmail(rset2.getString(3));
                                    //user.setPassword(rset2.getString(4));
                                    user.setUsername(rset2.getString(5));
                                    user.setEnte(rset2.getString(9));
                                    user.setLoggedUserid(loggedUserid);
                                    if (rset2.getInt(6) == 1) user.setEnabled(true);
                                    else user.setEnabled(false);
                                    //A questo livello non faccio mai scadere l'utenza, delle due è il CAS che mi blocca
                                    //if (rset2.getInt(7) == 1) user.setAccountNonExpired(false);
                                    //else user.setAccountNonExpired(true);
                                    //if (rset2.getInt(8) == 1) user.setCredentialsNonExpired(true);
                                    //else user.setCredentialsNonExpired(false);
                                    user.setAuthorities(loadGroupsForUser(user, conn));
                                    try {
                                        user.setAnaData(loadAnaDataForUser(user, conn));
                                    } catch (Exception ex) {
                                        log.error(ex.getMessage(), ex);
                                    }

                                }
                            }

                        }

                    }
                }

            }
            try {
                user.setSitesID(loadSitesForUser(user, conn));
                user.setSitesCodes(loadSitesCodesForUser(user,conn));
                user.setUOCodes(loadUOCodesForUser(user,conn));
            } catch (Exception ex) {
                log.error(ex.getMessage(), ex);
            }
        }
        return user;
    }

    public List<AuthorityImpl> loadGroupsForUser(UserImpl user, Connection conn) throws SQLException {
        String sqlQuery = "select * from (" + groupQuery + ") groups where ID_GRUPPOU in (select ID_GRUPPOU from utenti_gruppiu where UPPER(userid)=? and abilitato=1)";
        try (PreparedStatement stmt = conn.prepareStatement(sqlQuery)) {
            stmt.setString(1, user.getUsername().toUpperCase());
            try (ResultSet rset = stmt.executeQuery()) {
                List<AuthorityImpl> auths = new LinkedList<AuthorityImpl>();
                while (rset.next()) {
                    Logger.getLogger(this.getClass()).error(" -- loadGroupsForUser -- "+sqlQuery+" -- "+rset.getString(3));
                    AuthorityImpl a = new AuthorityImpl();
                    a.setId(rset.getLong(1));
                    a.setAuthority(rset.getString(2));
                    a.setDescription(rset.getString(3));
                    auths.add(a);
                }
                return auths;
            }
        }

    }

    public HashMap<String, String> loadAnaDataForUser(UserImpl user, Connection conn) throws SQLException {
        HashMap<String, String> keyValuePairs = new LinkedHashMap<String, String>();
        String sqlQuery = "select * from (" + userANAQuery + ") ana where UPPER(userid)=?";
        //System.out.println(sqlQuery+" -- USERNAME = "+user.toString());
        try (PreparedStatement stmt = conn.prepareStatement(sqlQuery)) {
            stmt.setString(1, user.getUsername().toUpperCase());
            try (ResultSet rset = stmt.executeQuery()) {
                ResultSetMetaData rsetmeta = rset.getMetaData();
                if (rset.next()) {
                    for (int i = 1; i <= rsetmeta.getColumnCount(); i++) {
                        keyValuePairs.put(rsetmeta.getColumnLabel(i), rset.getString(i));
                    }
                }
                Logger.getLogger(this.getClass()).debug("loadAnaDataForUser -> KVP" + keyValuePairs.toString());
            }
        }
                return keyValuePairs;
            }

    /**
     * restituisce le informazioni del sito associato all'utente in acm (ANA_UTENTI.COD_AZ)
     * @param user
     * @param conn
     * @return
     * @throws SQLException
     */
    public HashMap<String, String> loadSiteDataForUser(UserImpl user, Connection conn) throws SQLException {
        String sqlQuery = "select * from (" + userSITEQuery + ") ana where UPPER(userid)=?";
        System.out.println(sqlQuery+" -- USERNAME = "+user.toString());
        try (PreparedStatement stmt = conn.prepareStatement(sqlQuery)) {
            stmt.setString(1, user.getUsername().toUpperCase());
            try (ResultSet rset = stmt.executeQuery()) {
                ResultSetMetaData rsetmeta = rset.getMetaData();
                HashMap<String, String> keyValuePairs = new LinkedHashMap<String, String>();
                if (rset.next()) {
                    for (int i = 1; i <= rsetmeta.getColumnCount(); i++) {
                        keyValuePairs.put(rsetmeta.getColumnLabel(i), rset.getString(i));
                    }
                }
                Logger.getLogger(this.getClass()).info("loadSiteDataForUser -> KVP" + keyValuePairs.toString());
                return keyValuePairs;
            }
        }
    }

    public List<Integer> loadSitesForUser(UserImpl user, Connection conn) throws SQLException {
        String sqlQuery = "select * from USERS_SITES where UPPER(userid)=?";
        //System.out.println(sqlQuery+" -- USERNAME = "+user.toString());
        try (PreparedStatement stmt = conn.prepareStatement(sqlQuery)) {
            stmt.setString(1, user.getUsername().toUpperCase());
            try (ResultSet rset = stmt.executeQuery()) {
                ResultSetMetaData rsetmeta = rset.getMetaData();
                List<Integer> retList = new LinkedList<Integer>();
                while (rset.next()) {
                    retList.add(rset.getInt("SITE_ID"));
                }
                Logger.getLogger(this.getClass()).debug("loadSitesForUser -> LIST" + retList.toString());
                return retList;
            }

        }

    }

    public List<String> loadSitesCodesForUser(UserImpl user, Connection conn) throws SQLException {
        String sqlQuery = "select DISTINCT s.ID, s.CODE, s.ACTIVE, s.DESCR from USERS_SITES us, SITES s where us.SITE_ID = s.ID AND UPPER(userid)=?";
        //Logger.getLogger(this.getClass()).debug(sqlQuery+" -- USERNAME = "+user.toString());
        try (PreparedStatement stmt = conn.prepareStatement(sqlQuery)) {
            stmt.setString(1, user.getUsername().toUpperCase());
            try (ResultSet rset = stmt.executeQuery()) {
                ResultSetMetaData rsetmeta = rset.getMetaData();
                List<String> retList = new LinkedList<String>();
                while (rset.next()) {
                    retList.add(rset.getString("CODE"));
                }
                Logger.getLogger(this.getClass()).debug("loadSitesCodesForUser -> LIST"+retList.toString());
                return retList;
            }

        }

    }

    public List<String> loadUOCodesForUser(UserImpl user, Connection conn) throws SQLException {
        String sqlUsersUOActive = "select count(*) as C from user_tables where table_name='USERS_UO'";
        System.out.println("\n\n\n"+sqlUsersUOActive+"\n\n\n");
        List<String> retList = new LinkedList<String>();

        try (PreparedStatement stmt = conn.prepareStatement(sqlUsersUOActive)) {
            try (ResultSet rset1 = stmt.executeQuery()) {
                rset1.next();
                if (rset1.getInt(1) == 1) {

                    String sqlQuery = "SELECT distinct o.ID as CODE ,o.DESCRIZIONE AS DENOMINAZIONE_UO FROM ANA_UO o, USERS_UO u WHERE u.UO_ID=o.ID AND u.USERID=?";
                    System.out.println("\n\n\n"+sqlQuery+"\n\n\n");
                    //Logger.getLogger(this.getClass()).debug(sqlQuery+" -- USERNAME = "+user.toString());
                    try (PreparedStatement stmt2 = conn.prepareStatement(sqlQuery)) {
                        stmt2.setString(1, user.getUsername().toUpperCase());
                        try (ResultSet rset = stmt2.executeQuery()) {
                            ResultSetMetaData rsetmeta = rset.getMetaData();
                            while (rset.next()) {
                                retList.add(rset.getString("CODE"));
                            }
                            System.out.println("\n\n\nloadUOCodesForUser -> LIST" + retList.toString());
                            return retList;
                        }

                    }
                }
            }
        }
        catch (Exception ex) {
            log.error(ex.getMessage(), ex);
        }
        return retList;
    }

    public String usernameClear(String username) {
        username = username.toUpperCase();
        if (username.contains("@")) username = username.replace("@" + idServizio, "");
        return username;
    }

    public IUser getUser(String username) {
        username = usernameClear(username);
        String sqlQuery = "select * from (" + userQuery + ") users where UPPER(users.username)=UPPER(?)";
        UserImpl user = null;
        Logger.getLogger(this.getClass()).debug(sqlQuery+" -- getUser USERNAME = "+username);
        try {
            try (Connection conn = dataSource.getConnection()) {
                try (PreparedStatement stmt = conn.prepareStatement(sqlQuery)) {
                    stmt.setString(1, username.toUpperCase());
                    try (ResultSet rset = stmt.executeQuery()) {
                        while (rset.next()) {
                            user = userFromRsetRow(rset);
                        }
                    }
                }
            }
        } catch (SQLException e) {
            log.error(e.getMessage(), e);
        }
        if (user == null) return null;
        return user;
    }

    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        username = usernameClear(username);
        String sqlQuery = "select * from (" + userQuery + ") users where UPPER(users.username)=UPPER(?)";
        UserImpl user = null;
        Logger.getLogger(this.getClass()).debug(sqlQuery+" -- loadUserByUsername USERNAME = "+username);
        try {
            try (Connection conn = dataSource.getConnection()) {
                try (PreparedStatement stmt = conn.prepareStatement(sqlQuery)) {
                    stmt.setString(1, username.toUpperCase());
                    try (ResultSet rset = stmt.executeQuery()) {
                        while (rset.next()) {
                            //Logger.getLogger(this.getClass()).debug("IanusService (loggedUserByUsername) - UTENTE TROVATO PRE");
                            user = userFromRsetRow(rset);
                            //Logger.getLogger(this.getClass()).debug("IanusService (loggedUserByUsername) - UTENTE TROVATO POST");
                        }
                    }
                }
            }

        } catch (SQLException e) {
            log.error(e.getMessage(), e);
        }
        if (user == null) {
            Logger.getLogger(this.getClass()).debug("IanusService (loggedUserByUsername) - USER = NULL");
            throw new UsernameNotFoundException("Not Found");
        }
        //Logger.getLogger(this.getClass()).debug("IanusService (loggedUserByUsername) - RITORNO USER: "+user);
        //Thread.dumpStack();
        return user;
    }


    public List<? extends IUser> searchUsersByAuthorityName(String authorityName) {
        try {
            try (Connection conn = dataSource.getConnection()) {
                String sqlQuery = "select * from (" + userQuery + ") users where users.username in (select userid from utenti_gruppiu where id_gruppou in (select id_gruppou from (" + groupQuery + ") groups where UPPER(groups.authority) like '%'||?||'%'))";
                try (PreparedStatement stmt = conn.prepareStatement(sqlQuery)) {
                    stmt.setString(1, authorityName);
                    Logger.getLogger(this.getClass()).debug(sqlQuery + " -- AUTHNAME = " + authorityName);
                    try (ResultSet rset = stmt.executeQuery()) {
                        List<IUser> users = new LinkedList<IUser>();
                        List<Object> res = getUsersByJoinQueryResultSet(rset);
                        for (Object o : res) {
                            users.add((IUser) o);
                        }
                        return users;
                    }

                }

            }

        } catch (SQLException e) {
            log.error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
        }
        return null;
    }
}
