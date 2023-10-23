package it.cineca.siss.axmr3.authentication.filters;

import it.cineca.siss.axmr3.authentication.exceptions.TrustedUserNotFoundException;
import org.apache.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;

import javax.servlet.ServletRequest;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ParamAuthenticationFilter extends AbstractTrustedAuthenticationFilter {

    private static Logger log = Logger.getLogger(ParamAuthenticationFilter.class);

    protected DataSource dataSource;

    public DataSource getDataSource() {
        return dataSource;
    }

    @Autowired
    @Qualifier(value = "UserDataSource")
    public void setDataSource(DataSource dataSource) {
        this.dataSource = dataSource;
    }

    public void checkAuthTokenConfig(Connection conn) throws SQLException {
        String conto = "";
        String sql1 = "select count(*) conto from user_tables where table_name='AUTH_TOKENS' ";
        try (PreparedStatement stmt = conn.prepareStatement(sql1)) {
            try (ResultSet rset = stmt.executeQuery()) {
                if (rset.getFetchSize() > 0) {
                    rset.next();
                    conto = rset.getString("conto");
                    if (conto.isEmpty() || conto.equals("0")) {
                        sql1 = "  CREATE TABLE AUTH_TOKENS \n" +
                                "   (USERID VARCHAR2(255 CHAR), \n" +
                                "TOKEN VARCHAR2(255 CHAR), \n" +
                                "EXPIRATION DATE,\n" +
                                " CONSTRAINT AUTH_TOKENS_PK PRIMARY KEY (TOKEN) \n" +
                                "   )";
                        try (PreparedStatement stmt2 = conn.prepareStatement(sql1)) {
                            stmt2.executeQuery();
                        }

                    }
                }
            }
        }
    }

    public boolean checkToken(String token, String username) {
        try {
            try (Connection conn = dataSource.getConnection()) {
                this.checkAuthTokenConfig(conn);
                String sql1 = "";

                String conto = "";
                sql1 = "select count(*) conto from auth_tokens where lower(userid)=lower(?) and token=? and expiration>=sysdate ";
                try (PreparedStatement stmt = conn.prepareStatement(sql1)) {
                    stmt.setString(1, username);
                    stmt.setString(2, token);
                    try (ResultSet rset = stmt.executeQuery()) {
                        if (rset.getFetchSize() > 0) {
                            rset.next();
                            conto = rset.getString("conto");
                            if (conto.isEmpty() || conto.equals("0")) {
                                return false;
                            }
                        }
                    }
                }
            }
        } catch (SQLException e) {
            log.error(e.getMessage(), e);
            return false;
        }
        return true;
    }

    @Override
    public String getTrustedUsername(ServletRequest request) throws TrustedUserNotFoundException {
        HttpSession session = ((HttpServletRequest) request).getSession();
        String token = (String) request.getParameter("TOKEN");
        String username = (String) request.getParameter("USER");
        try {
            username = java.net.URLDecoder.decode(username, "UTF-8");
        } catch (Exception ex) {
            username = (String) request.getParameter("USER");
        }
        if (token != null && !token.isEmpty()) {
            if (!checkToken(token, username)) {
                username = "";
            }
        } else if (username != null && !username.isEmpty()) {
            session.setAttribute("username", username);
        } else {
            username = (String) session.getAttribute("username");
            Cookie[] cookies = ((HttpServletRequest) request).getCookies();
            if ((username == null || username.isEmpty()) && cookies != null) {
                for (Cookie myCookie : cookies) {
                    if (myCookie.getName().equals("username")) {
                        username = myCookie.getValue();
                    }
                }
            }
            if (username == null || username.isEmpty()) {
                throw new TrustedUserNotFoundException("Not found");
            }
        }
        return username;
    }
}