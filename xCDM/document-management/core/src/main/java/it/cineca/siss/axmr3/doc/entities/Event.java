package it.cineca.siss.axmr3.doc.entities;

import javax.persistence.*;
import java.util.Calendar;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 09/09/13
 * Time: 10.58
 * To change this template use File | Settings | File Templates.
 */
@Entity
@Table (name = "DOC_EVENTS")
public class Event extends BaseHibernateEntity{

    @OneToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "ELEMENT_ID", nullable = true)
    private Element element;
    @Column (name="USERNAME")
    private String username;
    @Temporal(value = TemporalType.TIMESTAMP)
    @Column (name="EVT_DT")
    private Calendar evDt;
    @Column (name="EVT_TYPE")
    private String evType;

    @Override
    public String toString() {
        return "Event{" +
                "element=" + element +
                ", username='" + username + '\'' +
                ", evDt=" + evDt +
                ", evType='" + evType + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;

        Event event = (Event) o;

        if (!element.equals(event.element)) return false;
        if (evDt != null ? !evDt.equals(event.evDt) : event.evDt != null) return false;
        if (evType != null ? !evType.equals(event.evType) : event.evType != null) return false;
        if (username != null ? !username.equals(event.username) : event.username != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = super.hashCode();
        result = 31 * result + element.hashCode();
        result = 31 * result + (username != null ? username.hashCode() : 0);
        result = 31 * result + (evDt != null ? evDt.hashCode() : 0);
        result = 31 * result + (evType != null ? evType.hashCode() : 0);
        return result;
    }

    public Element getElement() {

        return element;
    }

    public void setElement(Element element) {
        this.element = element;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public Calendar getEvDt() {
        return evDt;
    }

    public void setEvDt(Calendar evDt) {
        this.evDt = evDt;
    }

    public String getEvType() {
        return evType;
    }

    public void setEvType(String evType) {
        this.evType = evType;
    }
}
