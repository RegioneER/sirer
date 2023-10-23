package it.cineca.siss.axmr3.doc.entities;

import javax.persistence.*;
import java.util.Calendar;

/**
 * Created by cin0562a on 06/10/15.
 */
@Entity
@Table(name = "DOC_EME_SESSION")
public class EmendamentoSession extends BaseEmeSessionEntity {

    @Lob
    @Column(name="NOTE_EME")
    private String noteEme;
    @Column(name="USERID")
    private String userid;
    @Temporal(value = TemporalType.TIMESTAMP)
    @Column (name="START_DT")
    private Calendar startDt;
    @Temporal(value = TemporalType.TIMESTAMP)
    @Column (name="END_DT")
    private Calendar endDt;

    @Column(name="EME_ID")
    private Long emeId;
    @Column(name="CENTRO_ID")
    private Long centroId;

    public String getNoteEme() {
        return noteEme;
    }

    public void setNoteEme(String comment) {
        this.noteEme = comment;
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

    public Long getEmeId() {
        return emeId;
    }

    public void setEmeId(Long emeId) {
        this.emeId = emeId;
    }

    public Long getCentroId() {
        return centroId;
    }

    public void setCentroId(Long centroId) {
        this.centroId = centroId;
    }

}
