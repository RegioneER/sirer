package it.cineca.siss.axmr3.doc.web.controllers.admin.rest;

import it.cineca.siss.axmr3.common.mvc.handlers.ControllerHandler;
import it.cineca.siss.axmr3.doc.entities.CalendarEntity;
import it.cineca.siss.axmr3.doc.entities.PredefinedPolicy;
import it.cineca.siss.axmr3.doc.types.PostResult;
import it.cineca.siss.axmr3.doc.web.exceptions.RestException;
import it.cineca.siss.axmr3.doc.web.services.AdminService;
import org.apache.commons.fileupload.FileUploadException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 29/11/13
 * Time: 09:27
 * To change this template use File | Settings | File Templates.
 */
@Controller
@RequestMapping(value = "/rest/admin/calendar/")
public class RestAdminCalendarController {

    @Autowired
    protected AdminService admService;

    public AdminService getAdmService() {
        return admService;
    }

    public void setAdmService(AdminService admService) {
        this.admService = admService;
    }


    /**
     * Restituiesce il template dei metadati
     *
     * @param id
     * @param request
     * @param response
     * @return
     */
    @RequestMapping(value = "get/{id}", method = RequestMethod.GET)
    public
    @ResponseBody
    CalendarEntity getCalendar(@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response) {
        return admService.getCalendar(id);
    }

    /**
     * Restituisce tutti i template definiti
     *
     * @param request
     * @param response
     * @return
     */
    @RequestMapping(value = "getAll", method = RequestMethod.GET)
    public
    @ResponseBody
    List<CalendarEntity> getCalendars(HttpServletRequest request, HttpServletResponse response) {
        return admService.getCalendars();
    }

    /**
     * Salva il template
     *
     * @param request
     * @param response
     * @return
     * @throws java.io.IOException
     * @throws org.apache.commons.fileupload.FileUploadException
     */
    @RequestMapping(value = "save", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult save(HttpServletRequest request, HttpServletResponse response) throws IOException, FileUploadException {
        String name = request.getParameter("name");
        String backgroundColor = request.getParameter("backgroundColor");
        if (backgroundColor.startsWith("#")) backgroundColor = backgroundColor.replaceFirst("#", "");
        String titleRegex = request.getParameter("titleRegex");
        Long elementId = Long.parseLong(request.getParameter("elId"));
        Long startField = Long.parseLong(request.getParameter("startField"));
        Long endField = null;
        if (request.getParameter("endField") != null && !request.getParameter("endField").isEmpty()) {
            endField = Long.parseLong(request.getParameter("endField"));
        }
        Long id = null;
        if (request.getParameter("id") != null && !request.getParameter("id").isEmpty()) {
            id = Long.parseLong(request.getParameter("id"));
        }
        CalendarEntity t = null;
        try {
            t = admService.saveCalendar(name, titleRegex, backgroundColor, elementId, startField, endField, id);
        } catch (RestException e) {
            return new PostResult(e);
        }
        PostResult res = new PostResult("OK");
        res.setRedirect(ControllerHandler.getBaseUrl(request) + "/app/admin/editCalendar/" + t.getId());
        return res;
    }

    /**
     * Elimina il template
     *
     * @param id
     * @param request
     * @param response
     * @return
     * @throws IOException
     * @throws FileUploadException
     */
    @RequestMapping(value = "delete/{id}", method = RequestMethod.GET)
    public
    @ResponseBody
    PostResult delete(@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response) throws IOException, FileUploadException {
        try {
            admService.deleteCalendar(id);
        } catch (RestException e) {
            return new PostResult(e);
        }
        return new PostResult("OK");
    }


}
