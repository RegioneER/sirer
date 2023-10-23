package it.cineca.siss.axmr3.doc.scheduler;

import it.cineca.siss.axmr3.doc.scheduler.dbTables.Oracle;
import org.apache.log4j.Logger;
import org.springframework.jdbc.datasource.init.DatabasePopulator;

import java.sql.Connection;
import java.sql.SQLException;
import java.sql.Statement;

/**
 * Created by Carlo on 14/02/2016.
 */
public class DbPopulator implements DatabasePopulator {

    private String prefix;
    private String jdbcDriverClassName;

    public String getJdbcDriverClassName() {
        return jdbcDriverClassName;
    }

    public void setJdbcDriverClassName(String jdbcDriverClassName) {
        this.jdbcDriverClassName = jdbcDriverClassName;
    }

    public String getPrefix() {
        return prefix;
    }

    public void setPrefix(String prefix) {
        this.prefix = prefix;
    }

    public void populate(Connection connection) throws SQLException {
        if (jdbcDriverClassName.equals("oracle.jdbc.driver.OracleDriver")){
            Oracle o=new Oracle(prefix);
            for (String stmt:o.getStmts()){
                try{
                    Statement stmt1 = connection.createStatement();
                    stmt1.execute(stmt);
                }catch (Exception ex){
                    if (!ex.getMessage().startsWith("ORA-00955")) {
                        Logger.getLogger(this.getClass()).error("Errore dbPopulator: " + ex.getMessage());
                        Logger.getLogger(this.getClass()).error(ex.getMessage(), ex);
                    }
                }
            }
        }
    }

}
