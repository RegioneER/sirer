package it.cineca.siss.axmr3.doc.entities;

import javax.persistence.*;
import java.util.Calendar;

/**
 * Created by cin0562a on 06/10/15.
 */
@Entity
@Table(name = "DOC_DM_SESSION")
public class DataManagementSession extends BaseDMSessionEntity {


    @Lob
    @Column(name="COMMENTO")
    private String comment;
    @Column(name="USERID")
    private String userid;
    @Temporal(value = TemporalType.TIMESTAMP)
    @Column (name="START_DT")
    private Calendar startDt;
    @Temporal(value = TemporalType.TIMESTAMP)
    @Column (name="END_DT")
    private Calendar endDt;
    private String issueCode;

    public String getComment() {
        return comment;
    }

    public void setComment(String comment) {
        this.comment = comment;
    }

    public String getUserid() {
        return userid;
    }

    public void setUserid(String userid) {
        this.userid = userid;
    }

    public Calendar getStartDt() {
        return startDt;
    }

    public void setStartDt(Calendar startDt) {
        this.startDt = startDt;
    }

    public Calendar getEndDt() {
        return endDt;
    }

    public void setEndDt(Calendar endDt) {
        this.endDt = endDt;
    }

    public String getIssueCode() {
        return issueCode;
    }

    public void setIssueCode(String issueCode) {
        this.issueCode = issueCode;
    }
}
