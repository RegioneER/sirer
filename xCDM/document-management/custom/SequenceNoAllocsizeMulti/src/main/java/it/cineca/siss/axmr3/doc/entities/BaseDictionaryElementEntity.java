package it.cineca.siss.axmr3.doc.entities;

import it.cineca.siss.axmr3.hibernate.BaseEntity;

import javax.persistence.*;
import java.io.Serializable;

/**
 * Created by Carlo on 30/05/2016.
 */
@MappedSuperclass
public class BaseDictionaryElementEntity extends BaseEntity implements Serializable {

    @Id
    @SequenceGenerator(initialValue = 1, name = "dict_seq", sequenceName = "DOC_DICTIONARY_SEQUENCE", allocationSize = 50)
    @GeneratedValue(strategy = GenerationType.SEQUENCE, generator = "dict_seq")
    @Column(name="ID")
    protected Long id;

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

}
