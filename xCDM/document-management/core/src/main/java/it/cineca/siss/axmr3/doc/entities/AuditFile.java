package it.cineca.siss.axmr3.doc.entities;

import it.cineca.siss.axmr3.doc.entities.base.BaseFile;
import org.codehaus.jackson.annotate.JsonIgnore;

import javax.persistence.*;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 09/09/13
 * Time: 14.00
 * To change this template use File | Settings | File Templates.
 */
@Entity
@Table (name = "DOC_AUDIT_FILE")
public class AuditFile extends BaseFile<AuditFileContent> {

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "AUDIT_FILE_ID")
    private Element elRef;

    @Column (name="FILE_UNIQUE_ID")
    private Long uniqueId;

    @JsonIgnore
    public Element getElRef() {
        return elRef;
    }

    public void setElRef(Element elRef) {
        this.elRef = elRef;
    }

    public void setUniqueId(Long uniqueId) {
        this.uniqueId = uniqueId;
    }

    public Long getUniqueId() {
        return uniqueId;
    }
}
