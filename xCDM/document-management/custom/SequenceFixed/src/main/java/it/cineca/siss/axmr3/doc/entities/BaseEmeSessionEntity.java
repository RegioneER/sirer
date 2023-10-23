package it.cineca.siss.axmr3.doc.entities;

import it.cineca.siss.axmr3.hibernate.BaseEntity;

import javax.persistence.*;
import java.io.Serializable;

/**
 * Created by Carlo on 30/05/2016.
 */
@MappedSuperclass
public class BaseEmeSessionEntity extends BaseEntity implements Serializable {
    @Id
    @SequenceGenerator(initialValue = 1, name = "eme_session_seq", sequenceName = "XCDM_EME_SESSION_SEQ", allocationSize = 1)
    @GeneratedValue(strategy = GenerationType.SEQUENCE, generator = "eme_session_seq")
    @Column(name="ID")
    protected Long id;

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }
}