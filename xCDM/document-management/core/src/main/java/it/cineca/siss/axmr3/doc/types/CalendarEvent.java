package it.cineca.siss.axmr3.doc.types;

import it.cineca.siss.axmr3.doc.entities.CalendarEntity;
import it.cineca.siss.axmr3.doc.entities.Element;
import org.codehaus.jackson.annotate.JsonIgnore;

import java.text.SimpleDateFormat;
import java.util.Calendar;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 23/09/13
 * Time: 11:35
 * To change this template use File | Settings | File Templates.
 */
public class CalendarEvent {

    protected Long id;
    protected String title;
    protected boolean allDay;
    protected Calendar startDate;
    protected Calendar endDate;
    protected String url;
    private String backgroundColor;

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public boolean isAllDay() {
        return allDay;
    }

    public void setAllDay(boolean allDay) {
        this.allDay = allDay;
    }

    @JsonIgnore
    public Calendar getStartDate() {
        return startDate;
    }

    public String getStart() {
        SimpleDateFormat fmt = null;
        fmt = new SimpleDateFormat("yyyy-MM-dd HH:mm");
        return fmt.format(startDate.getTime());
    }

    public void setStartDate(Calendar startDate) {
        this.startDate = startDate;
    }

    @JsonIgnore
    public Calendar getEndDate() {
        return endDate;
    }

    public String getEnd() {
        if (endDate != null) {
            SimpleDateFormat fmt = new SimpleDateFormat("yyyy-MM-dd HH:mm");
            return fmt.format(endDate.getTime());
        } else
            return null;
    }

    public void setEndDate(Calendar endDate) {
        this.endDate = endDate;
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public void setBackgroundColor(String backgroundColor) {
        this.backgroundColor = backgroundColor;
    }

    public String getBackgroundColor() {
        return backgroundColor;
    }

    public static CalendarEvent build(CalendarEntity c, Element e) {
        CalendarEvent evt = new CalendarEvent();
        evt.setTitle(e.applyRegexString(c.getTitleRegex()));
        evt.setUrl("documents/detail/" + e.getId());
        evt.setId(c.getId());
        if (e.getFieldDataDates(c.getStartDateField().getTemplate().getName(), c.getStartDateField().getName()).size() == 0)
            return null;
        Calendar startDt = e.getFieldDataDates(c.getStartDateField().getTemplate().getName(), c.getStartDateField().getName()).get(0);
        if (startDt == null) return null;
        evt.setStartDate(startDt);
        if (c.getEndDateField() == null) evt.setAllDay(true);
        else {
            evt.setAllDay(false);
            if (e.getFieldDataDates(c.getEndDateField().getTemplate().getName(), c.getEndDateField().getName()).size() == 0)
                return null;
            Calendar endDate = e.getFieldDataDates(c.getEndDateField().getTemplate().getName(), c.getEndDateField().getName()).get(0);
            if (endDate == null) return null;
            evt.setEndDate(e.getFieldDataDates(c.getEndDateField().getTemplate().getName(), c.getEndDateField().getName()).get(0));
        }
        evt.setBackgroundColor("#" + c.getBackgroundColor());
        return evt;
    }

}
