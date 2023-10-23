package it.cineca.siss.axmr3.hibernate;

import javax.persistence.*;
import java.io.Serializable;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 26/07/13
 * Time: 14.18
 * To change this template use File | Settings | File Templates.
 */
@MappedSuperclass
public abstract class BaseEntity implements Serializable{

    public abstract Long getId();

    public abstract void setId(Long id);

    @Override
    public String toString() {
        return "it.cineca.siss.axmr3.BaseEntity{" +
                "id=" + getId() +
                '}';
    }


    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof BaseEntity)) return false;

        BaseEntity that = (BaseEntity) o;

        if (getId() != null) return getId().equals(that.getId());

        return false;
    }

    @Override
    public int hashCode() {
        return getId() != null ? getId().hashCode() : 0;
    }
}
