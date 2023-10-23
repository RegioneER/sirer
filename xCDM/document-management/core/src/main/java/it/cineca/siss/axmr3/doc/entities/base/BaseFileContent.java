package it.cineca.siss.axmr3.doc.entities.base;

import it.cineca.siss.axmr3.doc.entities.BaseHibernateEntity;
import it.cineca.siss.axmr3.doc.entities.BaseMDValueEntity;

import javax.persistence.Column;
import javax.persistence.Lob;
import javax.persistence.MappedSuperclass;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 09/09/13
 * Time: 14.02
 * To change this template use File | Settings | File Templates.
 */
@MappedSuperclass
public class BaseFileContent extends BaseMDValueEntity {

    @Lob
    @Column(name="BINARY_CONTENT")
    private byte[] content;

    public byte[] getContent() {
        return content;
    }

    public void setContent(byte[] content) {
        this.content = content;
    }

}
