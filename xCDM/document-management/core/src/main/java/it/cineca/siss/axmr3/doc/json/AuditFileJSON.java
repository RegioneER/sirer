package it.cineca.siss.axmr3.doc.json;

import it.cineca.siss.axmr3.doc.entities.AuditFile;

import java.util.Calendar;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 06/12/13
 * Time: 15.26
 * To change this template use File | Settings | File Templates.
 */
public class AuditFileJSON {

    private String fileName;
    private Calendar uploadDt;
    private String uploadUser;
    private String version;
    private Calendar date;
    private String note;
    private String autore;
    private Long fileContentId;
    private Long id;
    private Long uniqueId;

    public Long getUniqueId() {
        return uniqueId;
    }

    public void setUniqueId(Long uniqueId) {
        this.uniqueId = uniqueId;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }


    public AuditFileJSON(AuditFile f){
        fileName=f.getFileName();
        uploadDt=f.getUploadDt();
        uploadUser=f.getUploadUser();
        version=f.getVersion();
        date=f.getDate();
        note=f.getNote();
        autore=f.getAutore();
        if (f.getContent()!=null)
        fileContentId = f.getContent().getId();
        id=f.getId();
        uniqueId=f.getUniqueId();
    }

    public Long getFileContentId() {
        return fileContentId;
    }

    public void setFileContentId(Long fileContentId) {
        this.fileContentId = fileContentId;
    }

    public String getFileName() {
        return fileName;
    }

    public void setFileName(String fileName) {
        this.fileName = fileName;
    }

    public Calendar getUploadDt() {
        return uploadDt;
    }

    public void setUploadDt(Calendar uploadDt) {
        this.uploadDt = uploadDt;
    }

    public String getUploadUser() {
        return uploadUser;
    }

    public void setUploadUser(String uploadUser) {
        this.uploadUser = uploadUser;
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
}
