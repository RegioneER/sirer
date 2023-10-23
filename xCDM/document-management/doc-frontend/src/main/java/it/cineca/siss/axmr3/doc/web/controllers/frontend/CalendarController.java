package it.cineca.siss.axmr3.doc.web.controllers.frontend;

import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.authentication.impl.UserImpl;
import it.cineca.siss.axmr3.doc.web.services.DocumentService;
import org.dom4j.DocumentException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

import javax.servlet.http.HttpServletRequest;
import java.io.IOException;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 23/09/13
 * Time: 10:48
 * To change this template use File | Settings | File Templates.
 */
@Controller
public class CalendarController {

    @Autowired
    protected DocumentService docService;

    public DocumentService getDocService() {
        return docService;
    }

    public void setDocService(DocumentService docService) {
        this.docService = docService;
    }

    @RequestMapping(value = "/calendar", method = RequestMethod.GET)
    public String index(HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        model.put("rootBrowse", docService.getRootBrowsableElementTypes(user));
        model.put("hasCalendars", docService.isAvailablesCalendars(user));
        model.put("area", "calendar");
        model.put("calendars", docService.getAvailablesCalendars(user));
        model.put("getCreatableRootElementTypes", docService.getCreatableRootElementTypes(user));
        return "documents/calendar";
    }
}
