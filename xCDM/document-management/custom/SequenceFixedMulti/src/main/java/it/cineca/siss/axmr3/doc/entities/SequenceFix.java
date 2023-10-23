package it.cineca.siss.axmr3.doc.entities;

import it.cineca.siss.axmr3.log.Log;
import org.apache.log4j.Logger;
import org.springframework.beans.factory.InitializingBean;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;

import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by Carlo on 16/02/2016.
 */
public class SequenceFix implements InitializingBean {


    @Autowired
    @Qualifier(value = "UserDataSource")
    protected DataSource dataSource;

    public DataSource getDataSource() {
        return dataSource;
    }

    public void setDataSource(DataSource dataSource) {
        this.dataSource = dataSource;
    }

    public void fixSequences() throws SQLException {
        String sqlQuery1 = "select table_name from user_tables where table_name like 'DOC_%'";
        try (Connection conn = dataSource.getConnection()) {
            try (PreparedStatement stmt = conn.prepareStatement(sqlQuery1)) {
                try (ResultSet rset = stmt.executeQuery()) {
                    String hibernateMaxValQuery = "";
                    String elementMaxValQuery = "";
                    String xCdmSessionMaxValQuery = "";
                    String xCdmActionMaxValQuery = "";

                    String modelMaxValQuery = "";
                    String mdvalMaxValQuery = "";
                    String aclMaxValQuery = "";
                    //String dictionaryMaxValQuery="";

                    List<String> hibTablesList = new LinkedList<String>();
                    List<String> modelTablesList = new LinkedList<String>();
                    List<String> mdvalTablesList = new LinkedList<String>();
                    List<String> aclTablesList = new LinkedList<String>();
                    //List<String> dictionaryTablesList=new LinkedList<String>();
                    aclTablesList.add("DOC_ACL");
                    aclTablesList.add("DOC_ACL_CONTAINER");
                    hibTablesList.add("DOC_AUDIT_FILE");
                    hibTablesList.add("DOC_AUDIT_FILE_CONTENT");
                    hibTablesList.add("DOC_AUDIT_MD");
                    hibTablesList.add("DOC_AUDIT_MD_VAL");
                    hibTablesList.add("DOC_BULK_UPLOAD");
                    hibTablesList.add("DOC_CALENDAR");
                    mdvalTablesList.add("DOC_COMMENT");
                    mdvalTablesList.add("DOC_EL_PROCESS");
                    hibTablesList.add("DOC_EVENTS");
                    modelTablesList.add("DOC_MD_FIELD");
                    modelTablesList.add("DOC_MD_TEMPLATE");
                    mdvalTablesList.add("DOC_OBJ_FILE");
                    mdvalTablesList.add("DOC_OBJ_FILE_CONTENT");
                    mdvalTablesList.add("DOC_OBJ_GROUP");
                    mdvalTablesList.add("DOC_OBJ_MD");
                    mdvalTablesList.add("DOC_OBJ_MD_VAL");
                    mdvalTablesList.add("DOC_OBJ_TEMPLATE");
                    modelTablesList.add("DOC_POLICY");
                    aclTablesList.add("DOC_TPL_ACL");
                    aclTablesList.add("DOC_TPL_ACL_CONTAINER");
                    modelTablesList.add("DOC_TYPE");
                    modelTablesList.add("DOC_TYPE_MD_TEMPLATE");
                    modelTablesList.add("DOC_TYPE_WF");

                    while (rset.next()) {
                        String table_name = rset.getString(1);
                        if (table_name.equals("DOC_OBJ")) {
                            elementMaxValQuery = "select max(id)+1 from DOC_OBJ";
                            continue;
                        }
                        if (table_name.equals("DOC_DM_ACTION")) {
                            xCdmActionMaxValQuery = "select max(id)+1 from DOC_DM_ACTION";
                            continue;
                        }
                        if (table_name.equals("DOC_DM_SESSION")) {
                            xCdmSessionMaxValQuery = "select max(id)+1 from DOC_DM_SESSION";
                            continue;
                        }
                        if (table_name.equals("DOC_TYPE_DOC_TYPE") || table_name.equals("DOC_OBJ_DOC_OBJ_TEMPLATE") || table_name.equals("DOC_OBJ_DOC_MD_TEMPLATE")) {
                            continue;
                        }
                        if (hibTablesList.contains(table_name)) {
                            boolean isFirst = false;
                            if (hibernateMaxValQuery.isEmpty()) {
                                isFirst = true;
                            }
                            if (!isFirst) hibernateMaxValQuery += "union all\n";
                            hibernateMaxValQuery += "select nvl(max(id),0) as id from " + table_name + "\n";
                        }
                        if (modelTablesList.contains(table_name)) {
                            boolean isFirst = false;
                            if (modelMaxValQuery.isEmpty()) {
                                isFirst = true;
                            }
                            if (!isFirst) modelMaxValQuery += "union all\n";
                            modelMaxValQuery += "select nvl(max(id),0) as id from " + table_name + "\n";
                        }
                        if (mdvalTablesList.contains(table_name)) {
                            boolean isFirst = false;
                            if (mdvalMaxValQuery.isEmpty()) {
                                isFirst = true;
                            }
                            if (!isFirst) mdvalMaxValQuery += "union all\n";
                            mdvalMaxValQuery += "select nvl(max(id),0) as id from " + table_name + "\n";
                        }
                        if (aclTablesList.contains(table_name)) {
                            boolean isFirst = false;
                            if (aclMaxValQuery.isEmpty()) {
                                isFirst = true;
                            }
                            if (!isFirst) aclMaxValQuery += "union all\n";
                            aclMaxValQuery += "select nvl(max(id),0) as id from " + table_name + "\n";
                        }
                    }
                    hibernateMaxValQuery = "select max(id)+1 from (select 0 as id from dual union all " + hibernateMaxValQuery + "\n)";
                    elementMaxValQuery = "select max(id)+1 from (select 0 as id from dual union all " + elementMaxValQuery + "\n)";

                    modelMaxValQuery = "select max(id)+1 from (select 0 as id from dual union all " + modelMaxValQuery + "\n)";
                    mdvalMaxValQuery = "select max(id)+1 from (select 0 as id from dual union all " + mdvalMaxValQuery + "\n)";
                    aclMaxValQuery = "select max(id)+1 from (select 0 as id from dual union all " + aclMaxValQuery + "\n)";
                    //dictionaryMaxValQuery="select max(id)+1 from (select 0 as id from dual union all "+dictionaryMaxValQuery+"\n)";

                    Log.info(this.getClass(), "######################################################################");

                    Log.info(this.getClass(), hibernateMaxValQuery);

                    try (PreparedStatement stmt1 = conn.prepareStatement(hibernateMaxValQuery)) {
                        try (ResultSet rset1 = stmt1.executeQuery()) {
                            rset1.next();
                            String dropHibernateSeq = "drop sequence HIBERNATE_SEQUENCE";
                            String createHibernateSeq = "CREATE SEQUENCE  HIBERNATE_SEQUENCE MINVALUE 1 INCREMENT BY 1 START WITH " + rset1.getString(1) + " NOCACHE NOORDER  NOCYCLE";
                            Log.info(this.getClass(), dropHibernateSeq + ";");
                            try (PreparedStatement stmt2 = conn.prepareStatement(dropHibernateSeq)) {
                                stmt2.execute();
                            }
                            Log.info(this.getClass(), createHibernateSeq + ";");
                            try (PreparedStatement stmt2 = conn.prepareStatement(createHibernateSeq)) {
                                stmt2.execute();
                            }
                        }
                    }
                    try (PreparedStatement stmt1 = conn.prepareStatement(elementMaxValQuery)) {
                        try (ResultSet rset1 = stmt1.executeQuery()) {
                            rset1.next();
                            String dropElementSeq = "drop sequence ELEMENT_SEQUENCE";
                            String createElementSeq = "CREATE SEQUENCE ELEMENT_SEQUENCE MINVALUE 1 INCREMENT BY 1 START WITH " + rset1.getString(1) + " NOCACHE NOORDER  NOCYCLE";
                            Log.info(this.getClass(), dropElementSeq + ";");
                            try (PreparedStatement stmt2 = conn.prepareStatement(dropElementSeq)) {
                                stmt2.execute();
                            }
                            Log.info(this.getClass(), createElementSeq + ";");
                            try (PreparedStatement stmt2 = conn.prepareStatement(createElementSeq)) {
                                stmt2.execute();
                            }
                        }
                    }

                    Log.info(this.getClass(), modelMaxValQuery);
                    try (PreparedStatement stmt1 = conn.prepareStatement(modelMaxValQuery)) {
                        try (ResultSet rset1 = stmt1.executeQuery()) {
                            rset1.next();
                            String dropModelSeq = "drop sequence DOC_MODEL_SEQUENCE";
                            String createModelSeq = "CREATE SEQUENCE  DOC_MODEL_SEQUENCE MINVALUE 1 INCREMENT BY 1 START WITH " + rset1.getString(1) + " NOCACHE NOORDER  NOCYCLE";
                            Log.info(this.getClass(), dropModelSeq + ";");
                            try (PreparedStatement stmt2 = conn.prepareStatement(dropModelSeq)) {
                                stmt2.execute();
                            }
                            Log.info(this.getClass(), createModelSeq + ";");
                            try (PreparedStatement stmt2 = conn.prepareStatement(createModelSeq)) {
                                stmt2.execute();
                            }
                        }
                    }


                    Log.info(this.getClass(), mdvalMaxValQuery);
                    try (PreparedStatement stmt1 = conn.prepareStatement(mdvalMaxValQuery)) {
                        try (ResultSet rset1 = stmt1.executeQuery()) {
                            rset1.next();
                            String dropMdvalSeq = "drop sequence DOC_MDVAL_SEQUENCE";
                            String createMdvalSeq = "CREATE SEQUENCE  DOC_MDVAL_SEQUENCE MINVALUE 1 INCREMENT BY 1 START WITH " + rset1.getString(1) + " NOCACHE NOORDER  NOCYCLE";

                            Log.info(this.getClass(), dropMdvalSeq + ";");
                            try (PreparedStatement stmt2 = conn.prepareStatement(dropMdvalSeq)) {
                                stmt2.execute();
                            }
                            Log.info(this.getClass(), createMdvalSeq + ";");
                            try (PreparedStatement stmt2 = conn.prepareStatement(createMdvalSeq)) {
                                stmt2.execute();
                            }
                        }
                    }


                    Log.info(this.getClass(), aclMaxValQuery);
                    try (PreparedStatement stmt1 = conn.prepareStatement(aclMaxValQuery)) {
                        try (ResultSet rset1 = stmt1.executeQuery()) {
                            rset1.next();
                            String dropAclSeq = "drop sequence DOC_ACL_SEQUENCE";
                            String createAclSeq = "CREATE SEQUENCE  DOC_ACL_SEQUENCE MINVALUE 1 INCREMENT BY 1 START WITH " + rset1.getString(1) + " NOCACHE NOORDER  NOCYCLE";

                            Log.info(this.getClass(), dropAclSeq + ";");
                            try (PreparedStatement stmt2 = conn.prepareStatement(dropAclSeq)) {
                                stmt2.execute();
                            }
                            Log.info(this.getClass(), createAclSeq + ";");
                            try (PreparedStatement stmt2 = conn.prepareStatement(createAclSeq)) {
                                stmt2.execute();
                            }
                        }
                    }


                    if (!xCdmSessionMaxValQuery.isEmpty()) {
                        xCdmSessionMaxValQuery = "select max(id)+1 from (select 0 as id  from dual union all " + xCdmSessionMaxValQuery + "\n)";
                        try (PreparedStatement stmt1 = conn.prepareStatement(xCdmSessionMaxValQuery)) {
                            try (ResultSet rset1 = stmt1.executeQuery()) {
                                rset1.next();
                                String dropXcdmSessionSeq = "drop sequence XCDM_DM_SESSION_SEQ";
                                String createXcdmSessionSeq = "CREATE SEQUENCE XCDM_DM_SESSION_SEQ MINVALUE 1 INCREMENT BY 1 START WITH " + rset1.getString(1) + " NOCACHE NOORDER  NOCYCLE";
                                Log.info(this.getClass(), dropXcdmSessionSeq + ";");
                                try (PreparedStatement stmt2 = conn.prepareStatement(dropXcdmSessionSeq)) {
                                    stmt2.execute();
                                }
                                Log.info(this.getClass(), createXcdmSessionSeq + ";");
                                try (PreparedStatement stmt2 = conn.prepareStatement(createXcdmSessionSeq)) {
                                    stmt2.execute();
                                }
                            }
                        }
                    }
                    if (!xCdmActionMaxValQuery.isEmpty()) {
                        xCdmActionMaxValQuery = "select max(id)+1 from (select 0 as id  from dual union all " + xCdmActionMaxValQuery + "\n)";
                        try (PreparedStatement stmt1 = conn.prepareStatement(xCdmActionMaxValQuery)) {
                            try (ResultSet rset1 = stmt1.executeQuery()) {
                                rset1.next();
                                String dropXcdmActionSeq = "drop sequence XCDM_DM_ACTION_SEQ";
                                String createXcdmActionSeq = "CREATE SEQUENCE XCDM_DM_ACTION_SEQ MINVALUE 1 INCREMENT BY 1 START WITH " + rset1.getString(1) + " NOCACHE NOORDER  NOCYCLE";

                                Log.info(this.getClass(), dropXcdmActionSeq + ";");
                                try (PreparedStatement stmt2 = conn.prepareStatement(dropXcdmActionSeq)) {
                                    stmt2.execute();
                                }
                                Log.info(this.getClass(), createXcdmActionSeq + ";");
                                try (PreparedStatement stmt2 = conn.prepareStatement(createXcdmActionSeq)) {
                                    stmt2.execute();
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    public void afterPropertiesSet() throws Exception {
        Logger.getLogger(this.getClass()).info("\n\n\n - - - SEQUENCE FIX MODE MULTI - - - \n\n\n");
        //fixSequences();
        Logger.getLogger(this.getClass()).info("\n\n\n - - - SEQUENCES FIXED - - - \n\n\n");
    }


}
