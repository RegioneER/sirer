package it.cineca.siss.axmr3.doc.entities;

import javax.persistence.*;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 28/11/13
 * Time: 19:47
 * To change this template use File | Settings | File Templates.
 */
@Entity
@Table (name = "DOC_CALENDAR")
public class CalendarEntity extends BaseHibernateEntity{

    @OneToOne(fetch = FetchType.EAGER)
    @JoinColumn(name = "ELEMENT_TYPE_ID")
    private ElementType elementType;
    @Column (name = "TITLE_REGEX")
    private String titleRegex;
    @OneToOne(fetch = FetchType.EAGER)
    @JoinColumn(name = "START_DATE_FIELD_ID")
    private MetadataField startDateField;
    @OneToOne(fetch = FetchType.EAGER)
    @JoinColumn(name = "END_DATE_FIELD_ID")
    private MetadataField endDateField;
    @Column (name = "BACKGROUND_COLOR")
    private String backgroundColor;
    @Column (name="CAL_NAME")
    private String name;


    public ElementType getElementType() {
        return elementType;
    }

    public void setElementType(ElementType elementType) {
        this.elementType = elementType;
    }

    public String getTitleRegex() {
        return titleRegex;
    }

    public void setTitleRegex(String titleRegex) {
        this.titleRegex = titleRegex;
    }

    public MetadataField getStartDateField() {
        return startDateField;
    }

    public void setStartDateField(MetadataField startDateField) {
        this.startDateField = startDateField;
    }

    public MetadataField getEndDateField() {
        return endDateField;
    }

    public void setEndDateField(MetadataField endDateField) {
        this.endDateField = endDateField;
    }

    public String getBackgroundColor() {
        return backgroundColor;
    }

    public void setBackgroundColor(String backgroundColor) {
        this.backgroundColor = backgroundColor;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

}
