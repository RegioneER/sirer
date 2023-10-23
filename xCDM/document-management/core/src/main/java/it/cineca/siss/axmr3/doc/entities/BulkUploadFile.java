package it.cineca.siss.axmr3.doc.entities;

import javax.persistence.*;
import java.util.Calendar;

@Entity
@Table (name="DOC_BULK_UPLOAD")
public class BulkUploadFile extends BaseHibernateEntity {
	
	@Column(name="FILE_NAME")
	private String fileName;
	@Column(name="UP_USER")
	private String uploadUser;
	@Column(name="UP_DT")
	@Temporal(TemporalType.TIMESTAMP)
	private Calendar uploadDt;
	@Lob
	private byte[] content;
	public String getFileName() {
		return fileName;
	}
	public void setFileName(String fileName) {
		this.fileName = fileName;
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
	public byte[] getContent() {
		return content;
	}
	public void setContent(byte[] content) {
		this.content = content;
	}
}
