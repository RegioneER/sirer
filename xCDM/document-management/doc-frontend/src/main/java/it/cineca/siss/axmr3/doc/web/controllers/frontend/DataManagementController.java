package it.cineca.siss.axmr3.doc.web.controllers.frontend;

import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.authentication.impl.UserImpl;
import it.cineca.siss.axmr3.doc.acl.Policy;
import it.cineca.siss.axmr3.doc.entities.DataManagementSession;
import it.cineca.siss.axmr3.doc.entities.Element;
import it.cineca.siss.axmr3.doc.entities.ElementType;
import it.cineca.siss.axmr3.doc.web.exceptions.RestException;
import it.cineca.siss.axmr3.doc.web.services.DocumentService;
import org.activiti.engine.runtime.ProcessInstance;
import org.dom4j.DocumentException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.HashMap;
import java.util.List;

/**
 * Created by cin0562a on 06/10/15.
 */
@Controller
public class DataManagementController {

    @Autowired
    protected DocumentService docService;

    public DocumentService getDocService() {
        return docService;
    }

    public void setDocService(DocumentService docService) {
        this.docService = docService;
    }

    private void initModel(HttpServletRequest request, ModelMap model, IUser user, DocumentService service, HttpServletResponse response) throws DocumentException, IOException {
        Cookie[] cookiesArray = request.getCookies();
        HashMap<String, Cookie> cookiesMap = new HashMap<String, Cookie>();
        Long sessionId;
        Long coockiedmsession = new Long(0);
        boolean dmcookie = false;

        if (cookiesArray != null && cookiesArray.length > 0) {
            for (Cookie cookie : cookiesArray) {
                cookiesMap.put(cookie.getName(), cookie);
                if (cookie.getName().equals("xcdm.dm.session")) {
                    dmcookie = true;
                    coockiedmsession = Long.parseLong(cookie.getValue());
                }
            }
        }
        if (docService.isDm(user)) {
            DataManagementSession dms = docService.getActiveDmSession(user);
            if (dms != null) {
                sessionId = dms.getId();
                if (dmcookie) {
                    if (!coockiedmsession.equals(sessionId)) {
                        Cookie myCookie = new Cookie("xcdm.dm.session", sessionId.toString());
                        response.addCookie(myCookie);
                        cookiesMap.put("xcdm.dm.session", myCookie);
                    }
                } else {
                    Cookie myCookie = new Cookie("xcdm.dm.session", sessionId.toString());
                    response.addCookie(myCookie);
                    cookiesMap.put("xcdm.dm.session", myCookie);
                }
            } else {
                Cookie myCookie = new Cookie("xcdm.dm.session", "");
                myCookie.setMaxAge(0);
                response.addCookie(myCookie);
                cookiesMap.remove("xcdm.dm.session");
            }
        }
        model.put("requestCookies", cookiesMap);
    }

    @RequestMapping(value = "/documents/dm/edit/{elementId}", method = RequestMethod.GET)
    public String dmEditElement(@PathVariable(value = "elementId") Long elementId, HttpServletRequest request, HttpServletResponse resp, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException, RestException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        initModel(request, model, user, docService, resp);
        model.put("rootBrowse", docService.getRootBrowsableElementTypes(user));
        model.put("hasCalendars", docService.isAvailablesCalendars(user));
        int limit = 20;
        Element el = docService.getElement(elementId);
        Policy pol = el.getUserPolicy(user);
        HashMap<String, String> cookies = new HashMap<String, String>();
        for (Cookie c : request.getCookies()) {
            cookies.put(c.getName(), c.getValue());
        }
        if (request.getParameter("t") != null && !request.getParameter("t").isEmpty()) {
            Cookie c = new Cookie("ftlTemplate", request.getParameter("t"));
            resp.addCookie(c);
            if (cookies.containsKey("ftlTemplate")) {
                cookies.put("ftlTemplate", request.getParameter("t"));
            }
        }
        model.put("cookies", cookies);
        model.put("events", docService.getEvents(user, el));
        model.put("policies", docService.getPolicies());
        if ((el.getType().getAllowedChilds() != null && el.getType().getAllowedChilds().size() > 0) || el.getType().isSelfRecursive()) {
            model.put("numChilds", docService.getNumChilds(user, el));
            int page = 1;
            if (request.getParameter("p") != null && !request.getParameter("p").isEmpty())
                page = Integer.parseInt(request.getParameter("p"));
            el.setService(docService);
            el.setPage(page);
            if (request.getParameter("noLimit") != null && request.getParameter("noLimit").isEmpty()) {
                //non so cosa fare!!!
            } else el.setLimit(limit);
            el.setUser(user);
            model.put("page", page);
            model.put("rpp", limit);
        }
        model.put("element", el);
        /*if ((el.getType().getAllowedChilds() != null && el.getType().getAllowedChilds().size() > 0) || el.getType().isSelfRecursive()) {
            model.put("numChilds", docService.getNumChilds(user, el));
            int page = 1;
            if (request.getParameter("p") != null && !request.getParameter("p").isEmpty())
                page = Integer.parseInt(request.getParameter("p"));
            List<Element> childs = docService.getChilds(user, el, page, limit);
            it.cineca.siss.axmr3.log.Log.info(getClass(),"push childs!!!!");
            model.put("childs", childs);
            model.put("page", page);
            model.put("rpp", limit);
        } */
        /*if (!pol.isCanView()) return "documents/NotPermitted";
        if (pol.isCanAddChild()) {
            model.put("getCreatableElementTypes", docService.getCreatableElementTypes(el, user));
        }
        */
        List<ElementType> creatableElements = docService.getCreatableElementTypes(el, user);
        model.put("getCreatableElementTypes", creatableElements);

        List<ProcessInstance> activeProcesses = docService.getActiveProcesses(user, el);
        List<org.activiti.engine.history.HistoricProcessInstance> terminatedProcesses = docService.getTerminatedProcesses(user, el);
        List<org.activiti.engine.repository.ProcessDefinition> availableProcesses = docService.getAvailableProcessess(user, el);
        HashMap<String, org.activiti.engine.repository.ProcessDefinition> activeProcDefs = docService.getActiveProcessDefinition(user, el, activeProcesses);

        List<it.cineca.siss.axmr3.doc.types.Task> activeTasks = docService.getActiveTask(user, el, activeProcesses);
        model.put("activeProcesses", activeProcesses);
        model.put("terminatedProcesses", terminatedProcesses);
        model.put("availableProcesses", availableProcesses);
        model.put("docDefinition", el.getType());
        model.put("activeTasks", activeTasks);
        model.put("activeProcDefs", activeProcDefs);
        model.put("getCreatableRootElementTypes", docService.getCreatableRootElementTypes(user));
        return "documents/detail/data-management";
    }

    @RequestMapping(value = "/documents/dm/session", method = RequestMethod.GET)
    public String dmSessionDetail(HttpServletRequest request, HttpServletResponse resp, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException, RestException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        if (!docService.isDm(user)) return "documents/NotPermitted";
        initModel(request, model, user, docService, resp);
        DataManagementSession dm = docService.getActiveDmSession(user);
        if (dm != null) {
            model.put("dmsession", dm);
        }
        return "documents/dm-session";
    }

    @RequestMapping(value = "/documents/dm/session/{sessionId}", method = RequestMethod.GET)
    public String dmSessionDetail(@PathVariable(value = "sessionId") Long sessionId, HttpServletRequest request, HttpServletResponse resp, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException, RestException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        if (!docService.isDm(user)) return "documents/NotPermitted";
        initModel(request, model, user, docService, resp);
        DataManagementSession dm = docService.getDmSessionById(sessionId);
        if (dm != null) {
            model.put("dmsession", dm);
        }
        return "documents/dm-session";
    }

}
