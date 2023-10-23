package it.cineca.siss.axmr3.doc.entities;

import it.cineca.siss.axmr3.doc.entities.base.BaseMetadataValue;

import javax.persistence.*;

/**
 * Created by lverri on 12/09/2018.
 */

@Entity
@Table(name="DOC_AUDIT_EME_VAL")
public class AuditEmeValue extends BaseMetadataValue {

    @Column (name="OLD")
    private boolean old;

    @OneToOne(fetch = FetchType.EAGER)
    @JoinColumn(name = "EME_ID", nullable = true)
    private EmendamentoSession emeSession;

    public EmendamentoSession getEmendamento() {
        return emeSession;
    }

    public void setEmendamento(EmendamentoSession emeSession) {
        this.emeSession = emeSession;
    }

    public boolean isOld() {
        return old;
    }

    public void setOld(boolean old) {
        this.old = old;
    }

}
