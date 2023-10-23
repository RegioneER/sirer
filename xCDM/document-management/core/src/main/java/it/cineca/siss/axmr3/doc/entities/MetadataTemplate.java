package it.cineca.siss.axmr3.doc.entities;

import it.cineca.siss.axmr3.hibernate.BaseDao;
import org.codehaus.jackson.annotate.JsonIgnore;
import org.hibernate.criterion.Restrictions;

import javax.persistence.*;
import java.util.Collection;
import java.util.HashMap;
import java.util.LinkedList;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 31/07/13
 * Time: 12.35
 * To change this template use File | Settings | File Templates.
 */
@Entity
@Table (name="DOC_MD_TEMPLATE")
public class MetadataTemplate extends BaseModelEntity {

    @Column (name="NAME")
    private String name;
    @Column (name="DESCRIPTION")
    private String description;
    @Column (name="IS_AUDITABLE")
    private boolean auditable;
    @OneToMany(fetch = FetchType.LAZY)
    @JoinColumn(name = "TEMPLATE_ID")
    @OrderBy("position asc")
    private Collection<MetadataField> fields;
    @Column (name = "CALENDARIZED")
    private boolean calendarized;
    @Column (name = "CALENDAR_NAME")
    private String calendarName;
    @OneToOne (fetch = FetchType.EAGER)
    @JoinColumn(name = "CAL_START_FIELD", nullable = true)
    private MetadataField startDateField;
    @OneToOne (fetch = FetchType.EAGER)
    @JoinColumn(name = "CAL_END_FIELD", nullable = true)
    private MetadataField endDateField;
    @Column(name = "DELETED", nullable = false)
    private boolean deleted;

    public boolean isDeleted() {
        return deleted;
    }

    public void setDeleted(boolean deleted) {
        this.deleted = deleted;
    }

    public String getCalendarColor() {
        return calendarColor;
    }

    public void setCalendarColor(String calendarColor) {
        this.calendarColor = calendarColor;
    }

    @Column (name = "CAL_COLOR")
    private String calendarColor;

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

    public boolean isCalendarized() {
        return calendarized;
    }

    public void setCalendarized(boolean calendarized) {
        this.calendarized = calendarized;
    }

    public String getCalendarName() {
        return calendarName;
    }

    public void setCalendarName(String calendarName) {
        this.calendarName = calendarName;
    }

    public boolean isAuditable() {
        return auditable;
    }

    public void setAuditable(boolean auditable) {
        this.auditable = auditable;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }


    public Collection<MetadataField> getFields() {
        Collection<MetadataField> filteredFields = new LinkedList<MetadataField>();
        if (fields!=null) {
        for (MetadataField f : fields) {
            if (!f.isDeleted()) filteredFields.add(f);
        }
        }
        return filteredFields;
    }

    public void setFields(Collection<MetadataField> fields) {
        this.fields = fields;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    @JsonIgnore
    public MetadataField byFieldName(String name){
        String iName=name.toLowerCase();
        for (MetadataField f:getFields()){
            if (!f.isDeleted() && f.getName().toLowerCase().equals(iName)) return f;
        }
        return null;
    }

    @JsonIgnore
    static public MetadataTemplate getTemplateByName(BaseDao<MetadataTemplate> dao, String templateName){
        it.cineca.siss.axmr3.log.Log.info(MetadataTemplate.class, "Cercare il template dal nome " + templateName);
        return (MetadataTemplate) dao.getCriteria().add(Restrictions.eq("name", templateName).ignoreCase()).uniqueResult();
    }


    @JsonIgnore
    public HashMap<String,MetadataField> getFieldsMap(){
        HashMap<String, MetadataField> ret = new HashMap<String, MetadataField>();
        for(MetadataField field:getFields()){
            if (!field.isDeleted()) {
                ret.put(field.getName(), field);
            }
        }
        return ret;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        //if (!super.equals(o)) return false;

        MetadataTemplate that = (MetadataTemplate) o;

        if (auditable != that.auditable) return false;
        if (calendarized != that.calendarized) return false;
        if (calendarColor != null ? !calendarColor.equals(that.calendarColor) : that.calendarColor != null)
            return false;
        if (calendarName != null ? !calendarName.equals(that.calendarName) : that.calendarName != null) return false;
        if (description != null ? !description.equals(that.description) : that.description != null) return false;
        if (endDateField != null ? !endDateField.equals(that.endDateField) : that.endDateField != null) return false;
        if (name != null ? !name.equals(that.name) : that.name != null) return false;
        if (startDateField != null ? !startDateField.equals(that.startDateField) : that.startDateField != null)
            return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = super.hashCode();
        result = 31 * result + (name != null ? name.hashCode() : 0);
        return result;
    }
}
