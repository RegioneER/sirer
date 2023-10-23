package it.cineca.siss.axmr3.doc.entities;

import org.apache.commons.lang.StringEscapeUtils;

import javax.persistence.*;
import java.util.Calendar;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 02/08/13
 * Time: 15.27
 * To change this template use File | Settings | File Templates.
 */
@Entity
@Table (name = "DOC_COMMENT")
public class Comment extends BaseMDValueEntity {

    @Lob
    @Column (name="COMMENT_TEXT")
    private String comment;
    @Temporal(TemporalType.TIMESTAMP)
    @Column (name="INS_DT")
    private Calendar insDt;
    @Column (name="USERNAME")
    private String userId;

    public String getComment() {
        if(comment!=null){
            return StringEscapeUtils.escapeHtml(comment);
        }
        return comment;
    }

    public void setComment(String comment) {
        this.comment = comment;
    }

    public Calendar getInsDt() {
        return insDt;
    }

    public void setInsDt(Calendar insDt) {
        this.insDt = insDt;
    }

    public String getUserId() {
        return userId;
    }

    public void setUserId(String userId) {
        this.userId = userId;
    }
}
