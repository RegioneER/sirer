package it.cineca.siss.axmr3.doc.web.controllers.rest;

import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.doc.entities.CalendarEntity;
import it.cineca.siss.axmr3.doc.entities.Element;
import it.cineca.siss.axmr3.doc.types.CalendarEvent;
import it.cineca.siss.axmr3.doc.web.services.DocumentService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.servlet.http.HttpServletRequest;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 23/09/13
 * Time: 11:40
 * To change this template use File | Settings | File Templates.
 */
@Controller
public class RestCalendarController {

    @Autowired
    protected DocumentService docService;

    public DocumentService getDocService() {
        return docService;
    }

    public void setDocService(DocumentService docService) {
        this.docService = docService;
    }

    /*
    @RequestMapping(value="/rest/calendar/getEvents", method= RequestMethod.GET)
    public @ResponseBody
    List<CalendarEvent> getEvents (HttpServletRequest request){
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Calendar start=new GregorianCalendar();
        start.setTimeInMillis(Long.parseLong(request.getParameter("start"))*1000);
        Calendar end=new GregorianCalendar();
        end.setTimeInMillis(Long.parseLong(request.getParameter("end"))*1000);
        SimpleDateFormat fmt = new SimpleDateFormat("dd-MMM-yyyy");
        it.cineca.siss.axmr3.log.Log.info(getClass(),fmt.format(start.getTime()));
        it.cineca.siss.axmr3.log.Log.info(getClass(),fmt.format(end.getTime()));
        return docService.getCalendarEvents(user, start, end);
    }

    @RequestMapping(value="/rest/calendar/getEventsOfElement/{elementId}", method= RequestMethod.GET)
    public @ResponseBody
    List<CalendarEvent> getEventsOfElement (@PathVariable(value = "elementId") Long elementId, HttpServletRequest request){
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Element el=docService.getElement(elementId);
        Calendar start=new GregorianCalendar();
        start.setTimeInMillis(Long.parseLong(request.getParameter("start"))*1000);
        Calendar end=new GregorianCalendar();
        end.setTimeInMillis(Long.parseLong(request.getParameter("end"))*1000);
        SimpleDateFormat fmt = new SimpleDateFormat("dd-MMM-yyyy");
        it.cineca.siss.axmr3.log.Log.info(getClass(),fmt.format(start.getTime()));
        it.cineca.siss.axmr3.log.Log.info(getClass(),fmt.format(end.getTime()));
        return docService.getCalendarEventsByElement(user, el, start, end);
    }
    */

    @RequestMapping(value="/rest/calendar/getEvents", method= RequestMethod.GET)
    public @ResponseBody
    List<CalendarEvent> getEvents (HttpServletRequest request){
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Calendar start=new GregorianCalendar();
        start.setTimeInMillis(Long.parseLong(request.getParameter("start"))*1000);
        Calendar end=new GregorianCalendar();
        end.setTimeInMillis(Long.parseLong(request.getParameter("end"))*1000);
        return docService.getAllCalendarEvents(user, start, end);
    }

    @RequestMapping(value="/rest/calendar/getEventsOfCalendar/{calendarId}", method= RequestMethod.GET)
    public @ResponseBody
    List<CalendarEvent> getEventsOfElement (@PathVariable(value = "calendarId") Long calendarId, HttpServletRequest request){
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        CalendarEntity cal=docService.getCalendar(calendarId);
        Calendar start=new GregorianCalendar();
        start.setTimeInMillis(Long.parseLong(request.getParameter("start"))*1000);
        Calendar end=new GregorianCalendar();
        end.setTimeInMillis(Long.parseLong(request.getParameter("end"))*1000);
        return docService.getCalendarEvents(user, start, end, cal);
    }

}
