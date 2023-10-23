package it.cineca.siss.axmr3.doc.entities.base;

import it.cineca.siss.axmr3.doc.entities.BaseHibernateEntity;
import it.cineca.siss.axmr3.doc.entities.BaseMDValueEntity;
import org.codehaus.jackson.annotate.JsonIgnore;

import javax.persistence.*;
import java.util.Calendar;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 09/09/13
 * Time: 14.02
 * To change this template use File | Settings | File Templates.
 */
@MappedSuperclass
public class BaseFile<T extends BaseFileContent> extends BaseMDValueEntity {

    @Column (name="FILE_NAME")
    private String fileName;
    @Column (name="FILE_SIZE")
    private Long size;
    @OneToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "CONTENT_ID")
    private T content;
    @Temporal(value = TemporalType.TIMESTAMP)
    @Column (name="UPLOAD_DT")
    private Calendar uploadDt;
    @Column (name="UPLOAD_USER")
    private String uploadUser;
    @Column (name = "INDEXABLE")
    private boolean indexable;
    @Column (name = "INDEXED")
    private boolean indexed;
    @Column (name ="INDEX_ID")
    private Long indexId;
    @Column (name = "VER")
    private String version;
    @Column (name = "DATA_FILE")
    @Temporal(TemporalType.TIMESTAMP)
    private Calendar date;
    @Column (name = "NOTE")
    private String note;
    @Column (name="AUTORE")
    private String autore;
    @Column (name="FS_FULL_PATH")
    private String fsFullPath;

    public String getFsFullPath() {
        return fsFullPath;
    }

    public void setFsFullPath(String fsFullPath) {
        this.fsFullPath = fsFullPath;
    }

    public String getVersion() {
        return version;
    }

    public void setVersion(String version) {
        this.version = version;
    }

    public Calendar getDate() {
        return date;
    }

    public void setDate(Calendar date) {
        this.date = date;
    }

    public String getNote() {
        return note;
    }

    public void setNote(String note) {
        this.note = note;
    }

    public String getAutore() {
        return autore;
    }

    public void setAutore(String autore) {
        this.autore = autore;
    }

    public Long getIndexId() {
        return indexId;
    }

    public void setIndexId(Long indexId) {
        this.indexId = indexId;
    }

    public boolean isIndexable() {
        return indexable;
    }

    public void setIndexable(boolean indexable) {
        this.indexable = indexable;
    }

    public boolean isIndexed() {
        return indexed;
    }

    public void setIndexed(boolean indexed) {
        this.indexed = indexed;
    }

    public String getUploadUser() {
        return uploadUser;
    }

    public void setUploadUser(String uploadUser) {
        this.uploadUser = uploadUser;
    }

    public Calendar getUploadDt() {

        return uploadDt;
    }

    public void setUploadDt(Calendar uploadDt) {
        this.uploadDt = uploadDt;
    }

    @JsonIgnore
    public T getContent() {
        return content;
    }

    public void setContent(T content) {
        this.content = content;
    }

    public String getFileName() {
        return fileName;
    }

    public void setFileName(String fileName) {
        this.fileName = fileName;
    }

    public Long getSize() {
        return size;
    }

    public void setSize(Long size) {
        this.size = size;
    }

}
