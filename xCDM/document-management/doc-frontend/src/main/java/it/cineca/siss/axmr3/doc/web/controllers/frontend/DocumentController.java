package it.cineca.siss.axmr3.doc.web.controllers.frontend;


import com.itextpdf.text.Document;
import com.itextpdf.text.PageSize;
import com.itextpdf.text.Rectangle;
import com.itextpdf.text.pdf.PdfReader;
import com.itextpdf.text.pdf.PdfWriter;
import com.itextpdf.tool.xml.Pipeline;
import com.itextpdf.tool.xml.XMLWorker;
import com.itextpdf.tool.xml.XMLWorkerFontProvider;
import com.itextpdf.tool.xml.XMLWorkerHelper;
import com.itextpdf.tool.xml.css.CssFilesImpl;
import com.itextpdf.tool.xml.css.StyleAttrCSSResolver;
import com.itextpdf.tool.xml.html.CssAppliersImpl;
import com.itextpdf.tool.xml.html.HTML;
import com.itextpdf.tool.xml.html.TagProcessorFactory;
import com.itextpdf.tool.xml.html.Tags;
import com.itextpdf.tool.xml.parser.XMLParser;
import com.itextpdf.tool.xml.pipeline.css.CssResolverPipeline;
import com.itextpdf.tool.xml.pipeline.end.PdfWriterPipeline;
import com.itextpdf.tool.xml.pipeline.html.HtmlPipeline;
import com.itextpdf.tool.xml.pipeline.html.HtmlPipelineContext;
import freemarker.template.Template;
import freemarker.template.TemplateException;
import it.cineca.siss.axmr3.authentication.IAuthority;
import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.authentication.impl.UserImpl;
import it.cineca.siss.axmr3.authentication.services.SissUserService;
import it.cineca.siss.axmr3.common.mvc.handlers.ControllerHandler;
import it.cineca.siss.axmr3.doc.acl.Policy;
import it.cineca.siss.axmr3.doc.entities.*;
import it.cineca.siss.axmr3.doc.entities.File;
import it.cineca.siss.axmr3.doc.itext.addons.HeaderFooterEvent;
import it.cineca.siss.axmr3.doc.itext.addons.ImageTagProcessor;
import it.cineca.siss.axmr3.doc.web.exceptions.RestException;
import it.cineca.siss.axmr3.doc.web.services.DocumentService;
import it.cineca.siss.axmr3.exceptions.AxmrGenericException;
import it.cineca.siss.axmr3.log.Log;
import it.cineca.siss.axmr3.web.freemarker.AxmrFreemarkerConfigurer;
import jxl.CellView;
import jxl.Workbook;
import jxl.read.biff.BiffException;
import jxl.write.Label;
import jxl.write.WritableSheet;
import jxl.write.WritableWorkbook;
import jxl.write.WriteException;
import org.apache.commons.io.FileUtils;
import org.apache.http.HttpResponse;
import org.apache.log4j.Logger;
import org.dom4j.DocumentException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.beans.factory.config.PropertyPlaceholderConfigurer;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

import javax.imageio.ImageIO;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.sql.DataSource;
import java.awt.image.BufferedImage;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.*;
import static org.apache.commons.lang3.StringEscapeUtils.escapeHtml4;
import org.apache.commons.codec.binary.Base64;


/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 31/07/13
 * Time: 17.00
 * To change this template use File | Settings | File Templates.
 */
@Controller
public class DocumentController {

    @Autowired
    protected DocumentService docService;

    protected static final Logger log = Logger.getLogger(DocumentController.class);

    public void setDocService(DocumentService docService) {
        this.docService = docService;
    }

    @Autowired
    protected SissUserService userService;

    public SissUserService getUserService() {
        return userService;
    }

    public void setUserService(SissUserService userService) {
        this.userService = userService;
    }

    public DocumentService getDocService() {
        return docService;
    }

    public Properties getConfiguration(HttpSession session) {
        return getConfiguration(session, false);
    }

    public Properties getConfiguration(HttpSession session, boolean forceReload) {
        String adHocConfigurationFilePath = fmCfg.getAddOnPath() + "/configuration.properties";
        Properties adHocProps = new Properties();
        Logger.getLogger(this.getClass()).debug("Cerco il file properties "+adHocConfigurationFilePath);
        if (session.getAttribute("configurationProperties") == null || forceReload) {
            try {
                java.io.File file = new java.io.File(adHocConfigurationFilePath);
                if (file.exists()) {
                    Logger.getLogger(this.getClass()).debug("File properties trovato!!!");
                    FileInputStream fis = new FileInputStream(file);
                    adHocProps.load(fis);
                    session.setAttribute("configurationProperties", adHocProps);
                    fis.close();
                } else {
                    Logger.getLogger(this.getClass()).debug("File properties NON trovato!!!");
                    session.setAttribute("configurationProperties", adHocProps);
                }
            } catch (Exception e) {
                Logger.getLogger(this.getClass()).debug("File properties NON trovato!!!");
                session.setAttribute("configurationProperties", adHocProps);
            }
        }
        return (Properties) session.getAttribute("configurationProperties");
    }


    private void initModel(HttpServletRequest request, ModelMap model, IUser user, DocumentService service, HttpServletResponse response) throws DocumentException, IOException {
        Cookie[] cookiesArray = request.getCookies();
        //Collection<? extends IAuthority> auths = user.getAuthorities();
        HashMap<String, Cookie> cookiesMap = new HashMap<String, Cookie>();
        Long sessionId;
        Long coockiedmsession = new Long(0);
        boolean dmcookie = false;

        /*for(IAuthority auth:auths){
            if(auth.getDescription().equals("AZIENDA_ENTE")){
                model.put("centro",auth.getAuthority());
            }
        }*/
        String sqlQuery = "select ID_VISIBILITY_CNTR,codice_fiscale from ana_utenti_1 where UPPER(userid)=?";
        try {
            try (Connection conn = getDocService().getDataSource().getConnection()) {
                try (PreparedStatement stmt = conn.prepareStatement(sqlQuery)) {
                    stmt.setString(1, user.getUsername().toUpperCase());
                    try (ResultSet rset = stmt.executeQuery()) {
                        String ente = "";
                        String cf = "";
                        while (rset.next()) {
                            ente = rset.getString(1);
                            cf = rset.getString(2);
                        }
                        model.put("centro", ente);
                    }
                }
            }

        } catch (SQLException e) {

        }

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
        HashMap<String, String> data = new HashMap<String, String>();
        Enumeration paramNames = request.getParameterNames();
        while (paramNames.hasMoreElements()) {
            String paramName = (String) paramNames.nextElement();
            data.put(paramName, request.getParameter(paramName));
        }
        model.put("parameters", data);
    }

    @RequestMapping(value = "/reloadConfig", method = RequestMethod.GET)
    public void reloadAdHocConfig(HttpSession session, HttpServletResponse response) {
        getConfiguration(session, true);
        try {
            response.getOutputStream().print("DONE");
            response.getOutputStream().close();
        } catch (IOException e) {
            log.error(e.getMessage(), e);
        }
    }

    /**
     * Home Page
     *
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     */
    @RequestMapping(value = "/documents", method = RequestMethod.GET)
    public String index(HttpServletRequest request, @ModelAttribute("model") ModelMap model, HttpServletResponse response, HttpSession session) throws DocumentException, IOException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        initModel(request, model, user, docService, response);
        if (session.getAttribute("rootBrowse") == null) {
            session.setAttribute("rootBrowse", docService.getRootBrowsableElementTypes(user));
        }
        model.put("rootBrowse", session.getAttribute("rootBrowse"));

        if (session.getAttribute("hasCalendars") == null) {
            session.setAttribute("hasCalendars", docService.isAvailablesCalendars(user));
        }
        model.put("hasCalendars", session.getAttribute("hasCalendars"));
        int limit = 20;
        model.put("area", "documents");
        Properties config = getConfiguration(session);
        if (config.getProperty("performance.home.disableLoadElements") == null || !config.getProperty("performance.home.disableLoadElements").toLowerCase().equals("true")) {
            model.put("numChilds", docService.getNumRootChilds(user));
            int page = 1;
            if (request.getParameter("p") != null && !request.getParameter("p").isEmpty())
                page = Integer.parseInt(request.getParameter("p"));
            String orderBy = "";
            String orderType = "";
            if (request.getParameter("orderBy") != null && !request.getParameter("orderBy").isEmpty())
                orderBy = request.getParameter("orderBy");
            if (request.getParameter("orderType") != null && !request.getParameter("orderType").isEmpty())
                orderType = request.getParameter("orderType");
            model.put("rootElements", docService.getRootElementsLimit(user, page, limit, orderBy, orderType));
            model.put("page", page);
            model.put("rpp", limit);
        }
        if (session.getAttribute("getCreatableRootElementTypes") == null) {
            session.setAttribute("getCreatableRootElementTypes", docService.getCreatableRootElementTypes(user));
        }
        model.put("getCreatableRootElementTypes", session.getAttribute("getCreatableRootElementTypes"));
        return "documents/home";
    }


    /**
     * Home Page
     *
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     */
    @RequestMapping(value = "/documents/{typeId}", method = RequestMethod.GET)
    public String indexType(@PathVariable(value = "typeId") String docTypeS, HttpServletRequest request, @ModelAttribute("model") ModelMap model, HttpServletResponse response, HttpSession session) throws DocumentException, IOException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        Long typeId = docService.getTypeIdByNameOrId(docTypeS);
        initModel(request, model, user, docService, response);
        model.put("typeId", typeId);
        if (session.getAttribute("rootBrowse") == null) {
            session.setAttribute("rootBrowse", docService.getRootBrowsableElementTypes(user));
        }
        model.put("rootBrowse", session.getAttribute("rootBrowse"));

        if (session.getAttribute("hasCalendars") == null) {
            session.setAttribute("hasCalendars", docService.isAvailablesCalendars(user));
        }
        model.put("hasCalendars", session.getAttribute("hasCalendars"));

        int limit = 20;
        model.put("numChilds", docService.getNumRootChildsByType(user, typeId));
        int page = 1;
        if (request.getParameter("p") != null && !request.getParameter("p").isEmpty())
            page = Integer.parseInt(request.getParameter("p"));
        String orderBy = "";
        String orderType = "";
        if (request.getParameter("orderBy") != null && !request.getParameter("orderBy").isEmpty())
            orderBy = request.getParameter("orderBy");
        if (request.getParameter("orderType") != null && !request.getParameter("orderType").isEmpty())
            orderType = request.getParameter("orderType");
        if (request.getParameter("noLimit") != null && request.getParameter("noLimit").isEmpty()) {
            model.put("rootElements", docService.getRootElementsByTypeId(user, typeId));
        } else
            model.put("rootElements", docService.getRootElementsLimitById(user, typeId, page, limit, orderBy, orderType));
        model.put("page", page);
        model.put("rpp", limit);
        List<ElementType> rootEls = new LinkedList<ElementType>();
        rootEls.add(docService.getType(typeId));
        //model.put("getCreatableRootElementTypes", rootEls);//  .getCreatableRootElementTypes(user));
        if (session.getAttribute("getCreatableRootElementTypes") == null) {
            session.setAttribute("getCreatableRootElementTypes", docService.getCreatableRootElementTypes(user));
        }
        model.put("getCreatableRootElementTypes", session.getAttribute("getCreatableRootElementTypes"));
        return "documents/filtered-home";
    }

    /**
     * Pagina di dettaglio dell'elemento
     *
     * @param elementId
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     */
    @RequestMapping(value = "/documents/detail/{elementId}", method = RequestMethod.GET)
    public String editElement(@PathVariable(value = "elementId") Long elementId, HttpServletRequest request, HttpServletResponse resp, @ModelAttribute("model") ModelMap model, HttpSession session) throws DocumentException, IOException {
        Properties config = getConfiguration(session);
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        initModel(request, model, user, docService, resp);
        //Verificare sessione emendamento e iniettare metadati modificati
        Long emeSessionId = user.getEmeSessionId();
        Element el = docService.getElement(elementId, emeSessionId);
        if (el.isDeleted()) {
            throw new DocumentException("Elemento non più disponibile");
        }
        String propkey = "performance.detail." + el.getTypeName().toLowerCase() + ".redirect";
        if (config.get(propkey) != null && !((String) config.get(propkey)).isEmpty()) {
            resp.sendRedirect(config.get(propkey) + "/" + elementId);
            resp.getOutputStream().close();
            return "documents/blank";
        }
        model.put("docService", docService);
        model.put("userService", userService);
        if (session.getAttribute("rootBrowse") == null) {
            session.setAttribute("rootBrowse", docService.getRootBrowsableElementTypes(user));
        }
        model.put("rootBrowse", session.getAttribute("rootBrowse"));
        if (session.getAttribute("hasCalendars") == null) {
            session.setAttribute("hasCalendars", docService.isAvailablesCalendars(user));
        }
        model.put("hasCalendars", session.getAttribute("hasCalendars"));

        int limit = 20;
        docService.loadCustomGroupsForUser(user, el);

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
            Logger.getLogger(this.getClass()).info("COOKIE TEMPLATE: "+request.getParameter("t"));
        }
        model.put("cookies", cookies);
        if (session.getAttribute("events-" + elementId) == null) {
            session.setAttribute("events-" + elementId, docService.getEvents(user, el));
        }
        model.put("events-" + elementId, session.getAttribute("events-" + elementId));
        if (session.getAttribute("policies") == null) {
            session.setAttribute("policies", docService.getPolicies());
        }
        model.put("policies", session.getAttribute("policies"));
        boolean disableInjectChild = getPerformanceValue(config, "disableLoadElementChilds", el.getTypeName());
        if (!disableInjectChild) {
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
        }
        for (MetadataTemplate at : el.getTemplates()) {
            for (MetadataField field : at.getFields()) {
                field.setAvailableValuesMap(docService.getFieldsValues(field, user, el));
            }
        }
        model.put("element", el);
        if (!pol.isCanView()) return "documents/NotPermitted";
        if (pol.isCanAddChild()) {
            model.put("getCreatableElementTypes", docService.getCreatableElementTypes(el, user));
        }
        model.put("docDefinition", el.getType());
        boolean disableInjectProcessInfos = getPerformanceValue(config, "disableLoadProcessInfos", el.getTypeName());
        if (!disableInjectProcessInfos) {
            List<org.activiti.engine.runtime.ProcessInstance> activeProcesses = docService.getActiveProcesses(user, el);
            List<org.activiti.engine.history.HistoricProcessInstance> terminatedProcesses = docService.getTerminatedProcesses(user, el);
            List<org.activiti.engine.repository.ProcessDefinition> availableProcesses = docService.getAvailableProcessess(user, el);
            HashMap<String, org.activiti.engine.repository.ProcessDefinition> activeProcDefs = docService.getActiveProcessDefinition(user, el, activeProcesses);
            List<it.cineca.siss.axmr3.doc.types.Task> activeTasks = docService.getActiveTask(user, el, activeProcesses);

            model.put("activeProcesses", activeProcesses);
            model.put("terminatedProcesses", terminatedProcesses);
            model.put("availableProcesses", availableProcesses);
            model.put("activeTasks", activeTasks);
            model.put("activeProcDefs", activeProcDefs);
        }
        if (session.getAttribute("getCreatableRootElementTypes") == null) {
            session.setAttribute("getCreatableRootElementTypes", docService.getCreatableRootElementTypes(user));
        }
        model.put("getCreatableRootElementTypes", session.getAttribute("getCreatableRootElementTypes"));
        return "documents/detail/dispatcher";
    }


    public boolean getPerformanceValue(Properties config, String property, String eltype) {
        if (eltype != null) eltype = eltype.toLowerCase();
        boolean globalValue = false;

        if (
                config.getProperty("performance.detail." + property) != null
                        &&
                        config.getProperty("performance.detail." + property).equals("true")
        ) {
            globalValue = true;
        }
        boolean adhocValuePresent = false;
        boolean adHocValue = false;
        if (eltype != null && config.getProperty("performance.detail." + eltype + "." + property) != null) {
            adhocValuePresent = true;
            if (config.getProperty("performance.detail." + eltype + "." + property).equals("true")) {
                adHocValue = true;
            } else {
                adHocValue = false;
            }
        }
        if (!adhocValuePresent) {
            Log.debug(this.getClass(), "Valore performance "+property+": "+globalValue);
            return globalValue;
        } else {
            Log.debug(this.getClass(), "Valore performance "+property+" per "+eltype+": "+adHocValue);
            return adHocValue;
        }
    }

    /**
     * Pagina di dettaglio dell'elemento
     *
     * @param typeId
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     */
    @RequestMapping(value = "/documents/area/detail/{typeId}", method = RequestMethod.GET)
    public String editElement(@PathVariable(value = "typeId") String typeId, HttpSession session, HttpServletRequest request, HttpServletResponse resp, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        HashMap<String, Object> data = new HashMap<String, Object>();
        Enumeration paramNames = request.getParameterNames();
        while (paramNames.hasMoreElements()) {
            String paramName = (String) paramNames.nextElement();

            String lastChars = paramName.substring(paramName.length() - 2);
            it.cineca.siss.axmr3.log.Log.debug(getClass(),paramName+" - "+lastChars);
            if (lastChars.equals("[]")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Effettuo put di request []:"+paramName.substring(0, paramName.length()-2)+" - "+request.getParameterValues(paramName));
                data.put(paramName.substring(0, paramName.length() - 2), request.getParameterValues(paramName));
            } else {
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Effettuo put di request:"+paramName+" - "+request.getParameter(paramName));
                data.put(paramName, request.getParameter(paramName));
            }
        }
        initModel(request, model, user, docService, resp);
        model.put("rootBrowse", docService.getRootBrowsableElementTypes(user));
        model.put("hasCalendars", docService.isAvailablesCalendars(user));
        int limit = 20;
        List<Element> els = docService.advancedSearch(user, typeId, data);
        Element el = els.get(0);
        //Verificare sessione emendamento e iniettare metadati modificati
        Long emeSessionId = (Long) request.getAttribute("EME_SESSION_ID");
        if (emeSessionId != null && emeSessionId > 0) {
            el = docService.mergeEmendamentoChanges(el, emeSessionId);
        }
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
        if (!pol.isCanView()) return "documents/NotPermitted";
        if (pol.isCanAddChild()) {
            model.put("getCreatableElementTypes", docService.getCreatableElementTypes(el, user));
        }
        List<org.activiti.engine.runtime.ProcessInstance> activeProcesses = docService.getActiveProcesses(user, el);
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
        if (session.getAttribute("getCreatableRootElementTypes") == null) {
            session.setAttribute("getCreatableRootElementTypes", docService.getCreatableRootElementTypes(user));
        }
        model.put("getCreatableRootElementTypes", session.getAttribute("getCreatableRootElementTypes"));
        //model.put("groupItems",docService.getGrouppedElements(el.getId(),user));
        return "documents/detail/dispatcher";
    }

    @Autowired
    public AxmrFreemarkerConfigurer fmCfg;

    @RequestMapping(value = "/documents/pdf/{ftlTemplate}/{elementId}/images/{image:.+}", method = RequestMethod.GET)
    public void buildPdfTestImage(@PathVariable(value = "ftlTemplate") String ftlTemplate, @PathVariable(value = "elementId") Long elementId, @PathVariable(value = "image") String image, HttpServletRequest request, HttpServletResponse response, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException, TemplateException, com.itextpdf.text.DocumentException {
        response.setContentType("image/jpeg");
        String pathToWeb = fmCfg.getAddOnPath() + "/templates/documents/pdf/images/" + image;
        java.io.File f = new java.io.File(pathToWeb);
        BufferedImage bi = ImageIO.read(f);
        OutputStream out = response.getOutputStream();
        ImageIO.write(bi, "jpg", out);
        out.close();
    }

    @RequestMapping(value = "/documents/pdf/{ftlTemplate}/{elementId}/test", method = RequestMethod.GET)
    public void buildPdfTest(@PathVariable(value = "ftlTemplate") String ftlTemplate, @PathVariable(value = "elementId") Long elementId, HttpServletRequest request, HttpServletResponse resp, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException, TemplateException, com.itextpdf.text.DocumentException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        initModel(request, model, user, docService, resp);
        Element el = docService.getElement(elementId);
        docService.loadCustomGroupsForUser(user, el);
        Policy pol = el.getUserPolicy(user);
        StringWriter output = new StringWriter();
        model.put("element", el);
        resp.setCharacterEncoding("UTF-8");
        if (!pol.isCanView()) {
            resp.setStatus(403);
            resp.getOutputStream().close();
        } else {
            //resp.setContentType("application/force-download");
            //resp.setHeader("Content-Transfer-Encoding", "binary");
            //resp.setHeader("Content-Disposition", "attachment; filename=\"" + ftlTemplate + ".pdf\"");//fileName);
            Template tpl = fmCfg.getConfiguration().getTemplate("documents/pdf/" + ftlTemplate + ".ftl");
            tpl.process(model, output);
            resp.setStatus(200);
            resp.setContentType("text/html");
            resp.getOutputStream().print(output.toString());
            resp.getOutputStream().close();
        }
        /*
        Document document = new Document();
        PdfWriter writer = PdfWriter.getInstance(document, resp.getOutputStream());
        document.open();
        XMLWorkerHelper.getInstance().parseXHtml(writer, document, new StringInputStream(output.toString()));
        document.close();
        resp.getOutputStream().close();
        return "documents/detail/none";
        */
    }


    @RequestMapping(value = "/documents/pdf/{ftlTemplate}/{elementId}", method = RequestMethod.GET)
    public void buildPdf(@PathVariable(value = "ftlTemplate") String ftlTemplate, @PathVariable(value = "elementId") Long elementId, HttpServletRequest request, HttpServletResponse resp, @ModelAttribute("model") ModelMap model) throws Exception {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        initModel(request, model, user, docService, resp);
        Element el = docService.getElement(elementId);
        docService.loadCustomGroupsForUser(user, el);
        Policy pol = el.getUserPolicy(user);
        StringWriter output = new StringWriter();
        model.put("element", el);
        if (!pol.isCanView()) {
            resp.setStatus(403);
            resp.getOutputStream().close();
        } else {
            resp.setContentType("application/force-download");
            resp.setHeader("Content-Transfer-Encoding", "binary");
            resp.setHeader("Content-Disposition", "attachment; filename=\"" + ftlTemplate + ".pdf\"");//fileName);
            Template tpl = fmCfg.getConfiguration().getTemplate("documents/pdf/" + ftlTemplate + ".ftl");
            tpl.process(model, output);
            FileOutputStream fo = new FileOutputStream("/tmp/tmp.pdf");
            Document docTemp = generatePdf(ftlTemplate, model, output, fo, 0);
            docTemp.close();
            fo.close();
            PdfReader reader = new PdfReader("/tmp/tmp.pdf");
            int totalPages = reader.getNumberOfPages();
            reader.close();
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Pagine totali: " + totalPages);
            Document document = generatePdf(ftlTemplate, model, output, resp.getOutputStream(), totalPages);
            document.close();
            resp.getOutputStream().close();
        }
    }

    private Document generatePdf(String ftlTemplate, ModelMap model, StringWriter sw, OutputStream out, int totalPages) throws Exception {
        Properties messProps = new Properties();
        FileInputStream fis = new FileInputStream(fmCfg.getAddOnPath() + "/messages/it_IT.properties");
        messProps.load(fis);
        fis.close();
        String header = "";
        String footer = "";
        if (messProps.getProperty(ftlTemplate + ".header") != null)
            header = messProps.getProperty(ftlTemplate + ".header");
        if (messProps.getProperty(ftlTemplate + ".footer") != null)
            footer = messProps.getProperty(ftlTemplate + ".footer");
        Document document = new Document(PageSize.A4, 30, 30, 54, 54);
        PdfWriter writer = PdfWriter.getInstance(document, out);
        writer.setBoxSize("art", new Rectangle(36, 54, 559, 788));
        HeaderFooterEvent event = new HeaderFooterEvent();
        XMLWorkerFontProvider fontProvider = new XMLWorkerFontProvider(XMLWorkerFontProvider.DONTLOOKFORFONTS);
        fontProvider.register("/fonts/Arial.ttf");
        fontProvider.register("/fonts/Arial Bold.ttf");
        fontProvider.register("/fonts/Arial Bold Italic.ttf");
        fontProvider.register("/fonts/Arial Italic.ttf");
        fontProvider.register("/fonts/Times New Roman.ttf");
        fontProvider.register("/fonts/Times New Roman Bold.ttf");
        fontProvider.register("/fonts/Times New Roman Bold Italic.ttf");
        fontProvider.register("/fonts/Times New Roman Italic.ttf");
        fontProvider.register("/fonts/Verdana.ttf");
        fontProvider.register("/fonts/Verdana Bold.ttf");
        fontProvider.register("/fonts/Verdana Bold Italic.ttf");
        fontProvider.register("/fonts/Verdana Italic.ttf");
        writer.setPageEvent(event);
        document.open();
        TagProcessorFactory tagProcessorFactory = Tags.getHtmlTagProcessorFactory();
        tagProcessorFactory.removeProcessor(HTML.Tag.IMG);
        ImageTagProcessor imgProcessor = new ImageTagProcessor();
        it.cineca.siss.axmr3.log.Log.debug(getClass(),fmCfg.getAddOnPath());
        imgProcessor.setImagePath(fmCfg.getAddOnPath());
        tagProcessorFactory.addProcessor(imgProcessor, HTML.Tag.IMG);
        CssFilesImpl cssFiles = new CssFilesImpl();
        cssFiles.add(XMLWorkerHelper.getInstance().getDefaultCSS());
        StyleAttrCSSResolver cssResolver = new StyleAttrCSSResolver(cssFiles);
        HtmlPipelineContext hpc = new HtmlPipelineContext(new CssAppliersImpl(fontProvider));
        hpc.setAcceptUnknown(true).autoBookmark(true).setTagFactory(tagProcessorFactory);
        HtmlPipeline htmlPipeline = new HtmlPipeline(hpc, new PdfWriterPipeline(document, writer));
        Pipeline<?> pipeline = new CssResolverPipeline(cssResolver, htmlPipeline);
        XMLWorker worker = new XMLWorker(pipeline, true);
        XMLParser xmlParser = new XMLParser(true, worker);
        event.init(header, footer, totalPages, fontProvider);
        xmlParser.parse(new StringReader(sw.toString()));
        return document;
    }


    @RequestMapping(value = "/documents/hardDelete/{elementId}", method = RequestMethod.GET)
    public void hardDelete(@PathVariable(value = "elementId") Long elementId, HttpServletRequest request, HttpServletResponse resp, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        if (!user.hasRole("tech-admin")) {
            ServletOutputStream out = resp.getOutputStream();
            out.write("Errore permessi insufficienti.".getBytes());
        }
        Element el = docService.getElement(elementId);
        docService.loadCustomGroupsForUser(user, el);
        Long parentId = null;
        if (el.getParent() != null) parentId = el.getParent().getId();
        try {
            docService.hardDelete(el);
        } catch (AxmrGenericException e) {
            log.error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
        }
        if (parentId != null)
            resp.sendRedirect(ControllerHandler.getBaseUrl(request) + "/app/documents/detail/" + parentId);
        resp.sendRedirect(ControllerHandler.getBaseUrl(request) + "/app/documents/");
    }

    @RequestMapping(value = "/documents/bulk/{parentId}/{destType}/{idBulk}", method = RequestMethod.GET)
    public String bulk(@PathVariable(value = "parentId") Long parentId, @PathVariable(value = "destType") Long destType, @PathVariable(value = "idBulk") Long idBulk, HttpServletRequest request, @ModelAttribute("model") ModelMap model, HttpServletResponse resp) throws DocumentException, IOException, RestException {
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
        Element el = docService.getElement(parentId);
        ElementType dest = null;
        for (ElementType t : el.getType().getAllowedChilds()) {
            if (t.getId().equals(destType)) dest = t;
        }
        model.put("destType", dest);
        model.put("bulkId", idBulk);
        model.put("parentId", parentId);
        Policy pol = el.getUserPolicy(user);
        if (pol.isCanAddChild()) {
            model.put("getCreatableElementTypes", docService.getCreatableElementTypes(el, user));
        }
        model.put("columns", docService.getBulkFileColumns(idBulk));
        return "documents/bulk";
    }

    @RequestMapping(value = "/documents/bulk/load", method = RequestMethod.POST)
    public String bulkLoad(HttpServletRequest request, @ModelAttribute("model") ModelMap model, HttpServletResponse resp) throws DocumentException, IOException, RestException, BiffException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        initModel(request, model, user, docService, resp);
        model.put("hasCalendars", docService.isAvailablesCalendars(user));
        Long parentId = Long.parseLong(request.getParameter("parentId"));
        String sheetName = request.getParameter("sheetName");
        Long destId = Long.parseLong(request.getParameter("destId"));
        Long bulkId = Long.parseLong(request.getParameter("bulkId"));
        HashMap<Integer, Long> data = new HashMap<Integer, Long>();
        Enumeration paramNames = request.getParameterNames();
        while (paramNames.hasMoreElements()) {
            String paramName = (String) paramNames.nextElement();
            if (paramName.startsWith("col_")) {
                if (request.getParameter(paramName) != null && !request.getParameter(paramName).isEmpty())
                    data.put(Integer.parseInt(paramName.replace("col_", "")), Long.parseLong(request.getParameter(paramName)));
            }
        }
        data.remove("parentId");
        data.remove("destId");
        data.remove("bulkId");
        docService.bulkLoad(user, parentId, destId, bulkId, sheetName, data);
        model.put("parentId", parentId);
        return "documents/bulkLoaded";
    }


    @RequestMapping(value = "/documents/search", method = RequestMethod.GET)
    public String search(HttpServletRequest request, @ModelAttribute("model") ModelMap model, HttpServletResponse resp) throws DocumentException, IOException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        initModel(request, model, user, docService, resp);
        String pattern = request.getParameter("pattern");
        model.put("rootElements", docService.search(user, pattern));
        model.put("getCreatableRootElementTypes", docService.getCreatableRootElementTypes(user));
        return "documents/search";
    }


    /**
     * pagina di creazione nuovo elemento
     *
     * @param docTypeS
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     */
    @RequestMapping(value = "/documents/new/{docTypeId}", method = RequestMethod.GET)
    public String newDoc(@PathVariable(value = "docTypeId") String docTypeS, HttpServletRequest request, @ModelAttribute("model") ModelMap model, HttpServletResponse resp) throws DocumentException, IOException {
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
        Policy pol = new Policy();
        pol.setCanCreate(true);
        ElementType type = docService.getDocDefinition(docService.getTypeIdByNameOrId(docTypeS));
        Long docType = docService.getTypeIdByNameOrId(docTypeS);
        if (!docService.checkElementTypePolicy(pol, user, docType)) return "documents/NotPermitted";
        for (ElementTypeAssociatedTemplate at : type.getAssociatedTemplates()) {
            if (at.isEnabled() && at.getUserPolicy(user, type).isCanCreate()) {
                for (MetadataField field : at.getMetadataTemplate().getFields()) {
                    field.setAvailableValuesMap(docService.getFieldsValues(field, user, null));
                }
            }
        }
        model.put("docDefinition", type);
        model.put("getCreatableRootElementTypes", docService.getCreatableRootElementTypes(user));
        return "documents/form";
    }

    @RequestMapping(value = "/documents/addChild/{parentId}/{docTypeId}", method = RequestMethod.GET)
    public String newDoc(@PathVariable(value = "parentId") Long parentId, @PathVariable(value = "docTypeId") String docTypeS, HttpServletRequest request, @ModelAttribute("model") ModelMap model, HttpServletResponse resp) throws DocumentException, IOException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        initModel(request, model, user, docService, resp);
        Long docType = docService.getTypeIdByNameOrId(docTypeS);
        model.put("rootBrowse", docService.getRootBrowsableElementTypes(user));
        model.put("hasCalendars", docService.isAvailablesCalendars(user));
        model.put("getCreatableRootElementTypes", docService.getCreatableRootElementTypes(user));
        Element el = docService.getElement(parentId);
        Policy pol = el.getUserPolicy(user);
        if (!pol.isCanView()) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Non ho i permessi di lettura");
            return "documents/NotPermitted";
        }
        if (pol.isCanAddChild()) {
            List<ElementType> permittedChilds = docService.getCreatableElementTypes(el, user);
            boolean canAdd = false;
            for (ElementType t : permittedChilds) {
                if (t.getId().equals(docType)) canAdd = true;
            }
            if (!canAdd) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Non posso aggiungere elementi");
                return "documents/NotPermitted";
            }
            model.put("parentId", el.getId());
            model.put("parent", el);
            ElementType type = docService.getDocDefinition(docService.getTypeIdByNameOrId(docTypeS));
            //if (!docService.checkElementTypePolicy(pol, user, docType,parentId)) return "documents/NotPermitted";
            model.put("docDefinition", docService.getDocDefinition(docType));
            for (ElementTypeAssociatedTemplate at : type.getAssociatedTemplates()) {
                if (at.isEnabled() && at.getUserPolicy(user, type).isCanCreate()) {
                    for (MetadataField field : at.getMetadataTemplate().getFields()) {
                        Element fake = new Element();
                        fake.setParent(el);
                        field.setAvailableValuesMap(docService.getFieldsValues(field, user, fake));
                    }
                }
            }
            model.put("docDefinition", type);
        } else {
            return "documents/NotPermitted";
        }

        return "documents/form";
    }

    @RequestMapping(value = "/documents/download/excel/{id}", method = RequestMethod.GET)
    public void budgetExcel(@PathVariable(value = "id") Long elementId, HttpServletRequest request, HttpServletResponse response, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException, WriteException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        initModel(request, model, user, docService, response);
        ServletOutputStream out = response.getOutputStream();
        String name = "budget_clinico_";
        Element el = docService.getElement(elementId);
        docService.loadCustomGroupsForUser(user, el);
        Element center = el.getParent();
        Element studio = center.getParent();
        name += studio.getFieldDataString("UniqueIdStudio", "id") + "_";
        name += center.getFieldDataDecode("IdCentro", "PI") + "_";
        if (!studio.getFieldDataElement("datiPromotore", "promotore").isEmpty()) {
            name += ((Element) studio.getFieldDataElement("datiPromotore", "promotore").get(0)).getTitleString();
        }
        name += ".xls";
        Policy pol = el.getUserPolicy(user);
        if (!pol.isCanView()) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Non ho i permessi di lettura");
            out.write("Errore permessi insufficienti.".getBytes());
            return;
        }

        Collection<Element> xElements;
        Collection<Element> yElements;
        Collection<Element> xyElements;
        Collection<Element> pxpElements;
        Collection<Element> pxsElements;
        Collection<Element> bracciElements;


        HashMap<Long, HashMap<String, String>> xMap;
        HashMap<Long, HashMap<String, String>> yMap;
        HashMap<Integer, String> headers = new HashMap<Integer, String>();
        List<WritableSheet> flowcharts;
        Iterator<WritableSheet> iter;

        int c;
        CellView cell = new CellView();

        if (el != null && el.getType().getTypeId().equals("Budget")) {

            xElements = el.getChildrenByType("FolderTimePoint").get(0).getChildren();
            yElements = el.getChildrenByType("FolderPrestazioni").get(0).getChildren();
            xyElements = el.getChildrenByType("FolderTpxp").get(0).getChildren();
            pxpElements = el.getChildrenByType("FolderPXP").get(0).getChildren();
            pxsElements = el.getChildrenByType("FolderPXS").get(0).getChildren();
            bracciElements = el.getChildrenByType("FolderBracci").get(0).getChildren();

            headers.put(0, "Descrizione");
            headers.put(1, "Prezzo (euro)");


            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            response.setHeader("Content-Disposition", "attachment; filename=\"" + name + "\"");
            out = response.getOutputStream();
            WritableWorkbook workbook = Workbook.createWorkbook(out);


            WritableSheet sheet1 = workbook.createSheet("Riassunto visite", 0);
            WritableSheet sheet2 = workbook.createSheet("Prestazioni a richiesta", 1);
            WritableSheet sheet3 = workbook.createSheet("Prestazioni studio", 2);
            WritableSheet sheet0 = workbook.createSheet("Flowchart", 4);

            xMap = docService.createGridAxisMap(xElements, "TimePoint_col");
            yMap = docService.createGridAxisMap(yElements, "Prestazioni_row", "Prestazioni_UOC");

            cell.setSize(10000);
            flowcharts = docService.populateGridSheets(workbook, sheet0, xMap, yMap, xyElements, "tp-p_TimePoint", "tp-p_Prestazione", "Costo_TransferPrice");
            iter = flowcharts.iterator();
            while (iter.hasNext()) {
                WritableSheet currSheet = iter.next();
                docService.sumGrid(currSheet);
                currSheet.setColumnView(0, cell);
            }
            //docService.sumGrid(sheet0);
            docService.summarizeGrid(sheet0, sheet1);

            docService.populateTableSheet(sheet2, headers, pxpElements, "Costo_TransferPrice");
            docService.populateTableSheet(sheet3, headers, pxsElements, "Costo_TransferPrice");

            //gestione bracci

            if (bracciElements.size() > 0) {
                for (Element currBraccio : bracciElements) {
                    String braccioString = currBraccio.getFieldDataString("Base", "Nome");
                    WritableSheet sheetA = workbook.createSheet("Riassunto visite " + braccioString, workbook.getNumberOfSheets());
                    WritableSheet sheetB = workbook.createSheet("Flowchart " + braccioString, workbook.getNumberOfSheets());
                    docService.populateGridSheets(workbook, sheetB, xMap, yMap, xyElements, "tp-p_TimePoint", "tp-p_Prestazione", "Costo_TransferPrice", "", braccioString);
                    docService.sumGrid(sheetB);
                    docService.summarizeGrid(sheetB, sheetA);
                    sheetA.setColumnView(0, cell);
                    sheetB.setColumnView(0, cell);
                }
            }

            //fine gestione bracci


            sheet1.setColumnView(0, cell);
            sheet2.setColumnView(0, cell);
            sheet3.setColumnView(0, cell);

            workbook.write();
            workbook.close();
        } else {

            out.write("Errore oggetto non corretto.".getBytes());
            //throw new RestException(e.getMessage(), txManager);
        }

    }

    @RequestMapping(value = "/documents/download/excel2/{id}", method = RequestMethod.GET)
    public void budgetExcel2(@PathVariable(value = "id") Long elementId, HttpServletRequest request, HttpServletResponse response, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException, WriteException, AxmrGenericException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        String name = "budget_";
        initModel(request, model, user, docService, response);
        Element el = docService.getElement(elementId);
        docService.loadCustomGroupsForUser(user, el);
        Element center = el.getParent();
        Element studio = center.getParent();
        name += studio.getFieldDataString("UniqueIdStudio", "id") + "_";
        name += center.getFieldDataDecode("IdCentro", "PI") + "_";
        name += ((Element) studio.getFieldDataElement("datiPromotore", "promotore").get(0)).getTitleString() + ".xls";
        ServletOutputStream out = response.getOutputStream();
        Policy pol = el.getUserPolicy(user);
        if (!pol.isCanView()) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Non ho i permessi di lettura");
            out.write("Errore permessi insufficienti.".getBytes());
            return;
        }

        Collection<Element> xElements;
        Collection<Element> yElements;
        Collection<Element> xyElements;
        Collection<Element> pxpElements;
        Collection<Element> pxpCTCElements;
        Collection<Element> pxsElements;
        Collection<Element> passthroughElements;
        Collection<Element> bracciElements;
        String totalePaziente = "";
        Label label;
        int rows = 0;
        Double totalCol;

        List<Element> budgets;
        Element budget;
        ElementType elType;

        Element budgetFolder;
        HashMap<String, Object> data = new HashMap<String, Object>();

        HashMap<Long, HashMap<String, String>> xMap;
        HashMap<Long, HashMap<String, String>> yMap;
        HashMap<Integer, String> headers = new HashMap<Integer, String>();

        int c;
        CellView cell = new CellView();

        if (el != null && el.getType().getTypeId().equals("Budget")) {

            xElements = el.getChildrenByType("FolderTimePoint").get(0).getChildren();
            yElements = el.getChildrenByType("FolderPrestazioni").get(0).getChildren();
            bracciElements = el.getChildrenByType("FolderBracci").get(0).getChildren();

            budgetFolder = el.getChildrenByType("FolderBudgetStudio").get(0);
            elType = budgetFolder.getChildren().iterator().next().getType();
            data.put("BudgetCTC_Definitivo", "1");
            budgets = docService.searchByExample(user, budgetFolder.getId().toString(), elType, data);
            budget = budgets.get(0);
            for (Element currBudget : budgets) {

                if (currBudget.getFieldDataString("BudgetCTC", "Definitivo").equals("1")) {
                    budget = currBudget;
                    break;
                }
            }
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Budget studio definitivo: " + budget.getId().toString());

            xyElements = budget.getChildrenByType("FolderPrezzi").get(0).getChildren();
            pxpElements = xyElements;
            pxpCTCElements = budget.getChildrenByType("FolderPXPCTC").get(0).getChildren();
            pxsElements = budget.getChildrenByType("FolderPXSCTC").get(0).getChildren();
            passthroughElements = budget.getChildrenByType("FolderPassthroughCTC").get(0).getChildren();

            //pxpElements.addAll(xyElements);
            pxsElements.addAll(xyElements);


            headers.put(0, "Descrizione");
            headers.put(1, "Prezzo (euro)");

            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            response.setHeader("Content-Disposition", "attachment; filename=\"" + name + "\"");
            out = response.getOutputStream();
            WritableWorkbook workbook = Workbook.createWorkbook(out);


            WritableSheet sheet1 = workbook.createSheet("Riassunto visite", 0);
            WritableSheet sheet2 = workbook.createSheet("Prestazioni a richiesta", 1);
            WritableSheet sheet3 = workbook.createSheet("Prestazioni studio", 2);
            WritableSheet sheet4 = workbook.createSheet("Passthrough", 3);
            WritableSheet sheet0 = workbook.createSheet("Flowchart", 4);


            xMap = docService.createGridAxisMap(xElements, "TimePoint_col");
            yMap = docService.createGridAxisMap(yElements, "Prestazioni_row");

            docService.populateGridSheets(workbook, sheet0, xMap, yMap, xyElements, "tp-p_TimePoint", "tp-p_Prestazione", "PrezzoFinale_Prezzo", "PrezzoFinale_Prestazione");

            docService.sumGrid(sheet0);
            docService.summarizeGrid(sheet0, sheet1, budget.getFieldDataString("BudgetCTC", "TotalePazienteCTC"));


            totalePaziente = budget.getFieldDataString("BudgetCTC", "TotalePazienteCTC");
            rows = sheet1.getRows();
            if (totalePaziente != null && !totalePaziente.isEmpty()) {
                label = new Label(0, rows + 1, "Totale a preventivo per paziente (euro)");
                sheet1.addCell(label);
                try {
                    totalCol = Double.parseDouble(totalePaziente);
                    label = new Label(1, rows + 1, String.format(Locale.ITALIAN, "%.2f", totalCol));
                    sheet1.addCell(label);
                } catch (Exception ex) {
                    label = new Label(1, rows + 1, totalePaziente);
                    sheet1.addCell(label);
                }

            }


            docService.populateTableSheet(sheet2, headers, pxpElements, "Costo_Prezzo", "PrestazioneXPaziente", "PrezzoFinale_Prezzo", "PrezzoFinale_Prestazione");
            docService.populateTableSheet(sheet3, headers, pxsElements, "Costo_Prezzo", "PrestazioneXStudio", "PrezzoFinale_Prezzo", "PrezzoFinale_Prestazione");
            docService.populateTableSheet(sheet4, headers, passthroughElements, "Costo_Prezzo");


            if (pxpCTCElements.size() > 0) {
                headers.put(0, "Prestazioni non cliniche");
                docService.appendTableSheet(sheet2.getRows() + 1, sheet2, headers, pxpCTCElements, "Costo_Prezzo");
            }


            cell.setSize(10000);


            //gestione bracci

            if (bracciElements.size() > 0) {
                for (Element currBraccio : bracciElements) {
                    String braccioString = currBraccio.getFieldDataString("Base", "Nome");
                    WritableSheet sheetA = workbook.createSheet("Riassunto visite " + braccioString, workbook.getNumberOfSheets());
                    WritableSheet sheetB = workbook.createSheet("Flowchart " + braccioString, workbook.getNumberOfSheets());
                    docService.populateGridSheets(workbook, sheetB, xMap, yMap, xyElements, "tp-p_TimePoint", "tp-p_Prestazione", "PrezzoFinale_Prezzo", "PrezzoFinale_Prestazione", braccioString);
                    docService.sumGrid(sheetB);
                    docService.summarizeGrid(sheetB, sheetA, currBraccio.getFieldDataString("Braccio", "TotaleBudgetPaziente "));
                    sheetA.setColumnView(0, cell);
                    sheetB.setColumnView(0, cell);
                }
            }


            sheet0.setColumnView(0, cell);
            sheet1.setColumnView(0, cell);
            sheet2.setColumnView(0, cell);
            sheet3.setColumnView(0, cell);
            sheet4.setColumnView(0, cell);

            workbook.write();
            workbook.close();
        } else {
            out = response.getOutputStream();
            out.write("Errore oggetto non corretto.".getBytes());
            //throw new RestException(e.getMessage(), txManager);
        }

    }

    @RequestMapping(value = "/documents/download/excelStudio/{id}", method = RequestMethod.GET)
    public void budgetExcelStudio(@PathVariable(value = "id") Long elementId, HttpServletRequest request, HttpServletResponse response, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException, WriteException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        String name = "budget_";
        initModel(request, model, user, docService, response);
        Element budget = docService.getElement(elementId);
        Element el = budget.getParent().getParent();
        Element center = el.getParent();
        Element studio = center.getParent();
        name += studio.getFieldDataString("UniqueIdStudio", "id") + "_";
        name += center.getFieldDataDecode("IdCentro", "PI") + "_";
        if (!studio.getFieldDataElement("datiPromotore", "promotore").isEmpty()) {
            name += ((Element) studio.getFieldDataElement("datiPromotore", "promotore").get(0)).getTitleString();
        }
        name += ".xls";
        ServletOutputStream out = response.getOutputStream();
        Policy pol = el.getUserPolicy(user);
        if (!pol.isCanView()) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Non ho i permessi di lettura");
            out.write("Errore permessi insufficienti.".getBytes());
            return;
        }

        Collection<Element> xElements;
        Collection<Element> yElements;
        Collection<Element> xyElements;
        Collection<Element> pxpElements;
        Collection<Element> pxpCTCElements;
        Collection<Element> pxsElements;
        Collection<Element> passthroughElements;
        Collection<Element> bracciElements;
        String totalePaziente = "";
        Label label;
        int rows = 0;
        Double totalCol;

        HashMap<Long, HashMap<String, String>> xMap;
        HashMap<Long, HashMap<String, String>> yMap;
        HashMap<Integer, String> headers = new HashMap<Integer, String>();

        int c;
        CellView cell = new CellView();

        if (el != null && el.getType().getTypeId().equals("Budget")) {

            xElements = el.getChildrenByType("FolderTimePoint").get(0).getChildren();
            yElements = el.getChildrenByType("FolderPrestazioni").get(0).getChildren();
            bracciElements = el.getChildrenByType("FolderBracci").get(0).getChildren();

            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Budget studio definitivo: " + budget.getId().toString());

            xyElements = budget.getChildrenByType("FolderPrezzi").get(0).getChildren();
            pxpElements = xyElements;
            pxpCTCElements = budget.getChildrenByType("FolderPXPCTC").get(0).getChildren();
            pxsElements = budget.getChildrenByType("FolderPXSCTC").get(0).getChildren();
            passthroughElements = budget.getChildrenByType("FolderPassthroughCTC").get(0).getChildren();

            //pxpElements.addAll(xyElements);
            pxsElements.addAll(xyElements);


            headers.put(0, "Descrizione");
            headers.put(1, "Prezzo (euro)");

            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            response.setHeader("Content-Disposition", "attachment; filename=\"" + name + "\"");
            out = response.getOutputStream();
            WritableWorkbook workbook = Workbook.createWorkbook(out);


            WritableSheet sheet1 = workbook.createSheet("Riassunto visite", 0);
            WritableSheet sheet2 = workbook.createSheet("Prestazioni a richiesta", 1);
            WritableSheet sheet3 = workbook.createSheet("Prestazioni studio", 2);
            WritableSheet sheet4 = workbook.createSheet("Passthrough", 3);
            WritableSheet sheet0 = workbook.createSheet("Flowchart", 4);


            xMap = docService.createGridAxisMap(xElements, "TimePoint_col");
            yMap = docService.createGridAxisMap(yElements, "Prestazioni_row");

            docService.populateGridSheets(workbook, sheet0, xMap, yMap, xyElements, "tp-p_TimePoint", "tp-p_Prestazione", "PrezzoFinale_Prezzo", "PrezzoFinale_Prestazione");

            docService.sumGrid(sheet0);
            docService.summarizeGrid(sheet0, sheet1, budget.getFieldDataString("BudgetCTC", "TotalePazienteCTC"));


            totalePaziente = budget.getFieldDataString("BudgetCTC", "TotalePazienteCTC");
            rows = sheet1.getRows();
            if (totalePaziente != null && !totalePaziente.isEmpty()) {
                label = new Label(0, rows + 1, "Totale a preventivo per paziente (euro)");
                sheet1.addCell(label);
                try {
                    totalCol = Double.parseDouble(totalePaziente);
                    label = new Label(1, rows + 1, String.format(Locale.ITALIAN, "%.2f", totalCol));
                    sheet1.addCell(label);
                } catch (Exception ex) {
                    label = new Label(1, rows + 1, totalePaziente);
                    sheet1.addCell(label);
                }

            }


            docService.populateTableSheet(sheet2, headers, pxpElements, "Costo_Prezzo", "PrestazioneXPaziente", "PrezzoFinale_Prezzo", "PrezzoFinale_Prestazione");
            docService.populateTableSheet(sheet3, headers, pxsElements, "Costo_Prezzo", "PrestazioneXStudio", "PrezzoFinale_Prezzo", "PrezzoFinale_Prestazione");
            docService.populateTableSheet(sheet4, headers, passthroughElements, "Costo_Prezzo");


            if (pxpCTCElements.size() > 0) {
                headers.put(0, "Prestazioni non cliniche");
                docService.appendTableSheet(sheet2.getRows() + 1, sheet2, headers, pxpCTCElements, "Costo_Prezzo");
            }


            cell.setSize(10000);

            //gestione bracci

            if (bracciElements.size() > 0) {
                for (Element currBraccio : bracciElements) {
                    String braccioString = currBraccio.getFieldDataString("Base", "Nome");
                    WritableSheet sheetA = workbook.createSheet("Riassunto visite " + braccioString, workbook.getNumberOfSheets());
                    WritableSheet sheetB = workbook.createSheet("Flowchart " + braccioString, workbook.getNumberOfSheets());
                    docService.populateGridSheets(workbook, sheetB, xMap, yMap, xyElements, "tp-p_TimePoint", "tp-p_Prestazione", "PrezzoFinale_Prezzo", "PrezzoFinale_Prestazione", braccioString);
                    docService.sumGrid(sheetB);
                    docService.summarizeGrid(sheetB, sheetA, currBraccio.getFieldDataString("Braccio", "TotaleBudgetPaziente "));
                    sheetA.setColumnView(0, cell);
                    sheetB.setColumnView(0, cell);
                }
            }

            //fine gestione bracci


            sheet0.setColumnView(0, cell);
            sheet1.setColumnView(0, cell);
            sheet2.setColumnView(0, cell);
            sheet3.setColumnView(0, cell);
            sheet4.setColumnView(0, cell);

            workbook.write();
            workbook.close();
        } else {
            out = response.getOutputStream();
            out.write("Errore oggetto non corretto.".getBytes());
            //throw new RestException(e.getMessage(), txManager);
        }

    }


    @RequestMapping(value = "/documents/getAttach/{elementId}", method = RequestMethod.GET)
    public void getAttach(@PathVariable(value = "elementId") Long elementId, HttpServletRequest request, HttpServletResponse response, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        Element el = docService.getElement(elementId);
        File file = el.getFile();
        docService.loadCustomGroupsForUser(user, el);
        ServletOutputStream out = response.getOutputStream();
        Policy pol = el.getUserPolicy(user);
        if (!pol.isCanView()) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Non ho i permessi di lettura");
            out.write("Errore permessi insufficienti.".getBytes());
            return;
        }
        out = response.getOutputStream();
        response.setHeader("Content-Disposition", "attachment; filename=\"" + file.getFileName() + "\"");
        if (el.getType().getFileOnFS()) {
            String fname = el.getFile().getFsFullPath();
            try (FileInputStream fis = new FileInputStream(fname)) {
                int BUFF_SIZE = 1024;
                byte[] buffer = new byte[BUFF_SIZE];
                int byteRead = 0;
                while ((byteRead = fis.read(buffer)) != -1) {
                    out.write(buffer, 0, byteRead);
                }
            }
        } else {
            FileContent fc = file.getContent();
            response.setContentLength((int) fc.getContent().length);
            out.write(fc.getContent());
        }
        out.close();
    }
    @RequestMapping(value = "/documents/getAttachBase64/{elementId}", method = RequestMethod.GET)
    public void getAttachBase64(@PathVariable(value = "elementId") Long elementId, HttpServletRequest request, HttpServletResponse response, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        Element el = docService.getElement(elementId);
        File file = el.getFile();
        docService.loadCustomGroupsForUser(user, el);
        ServletOutputStream out = response.getOutputStream();
        Policy pol = el.getUserPolicy(user);
        if (!pol.isCanView()) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Non ho i permessi di lettura");
            out.write("Errore permessi insufficienti.".getBytes());
            return;
        }
        String output = "";
        out = response.getOutputStream();
        //response.setHeader("Content-Disposition", "attachment; filename=\"" + file.getFileName() + "\"");
        if (el.getType().getFileOnFS()) {
            String fname = el.getFile().getFsFullPath();
            java.io.File fileHandler = new java.io.File(fname);
            byte[] encoded = Base64.encodeBase64(FileUtils.readFileToByteArray(fileHandler));
            output = new String(encoded, StandardCharsets.US_ASCII);
        } else {
            FileContent fc = file.getContent();
            byte[] encoded = Base64.encodeBase64(fc.getContent());
            output = new String(encoded, StandardCharsets.US_ASCII);
        }
        byte[] toWrite = output.getBytes(StandardCharsets.US_ASCII);
        response.setContentLength(toWrite.length);
        out.write(toWrite);
        out.close();
    }


    //TODO:controlli sui permessi utente?
    @RequestMapping(value = "/documents/getAttach/old/{attachId}", method = RequestMethod.GET)
    public void getAttachOld(@PathVariable(value = "attachId") Long attachId, HttpServletRequest request, HttpServletResponse response, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        AuditFile file = docService.getOldVersion(attachId);
        Element el = file.getElRef();
        Policy pol = el.getUserPolicy(user);
        ServletOutputStream out = response.getOutputStream();
        if (!pol.isCanView()) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Non ho i permessi di lettura");
            out.write("Errore permessi insufficienti.".getBytes());
            return;
        }
        response.setHeader("Content-Disposition", "attachment; filename=\"" + file.getFileName() + "\"");
        if (el.getType().getFileOnFS()) {
            String fname = el.getFile().getFsFullPath();
            try (FileInputStream fis = new FileInputStream(fname)) {
                int BUFF_SIZE = 1024;
                byte[] buffer = new byte[BUFF_SIZE];
                int byteRead = 0;
                while ((byteRead = fis.read(buffer)) != -1) {
                    out.write(buffer, 0, byteRead);
                }
            }

        } else {
            AuditFileContent fc = file.getContent();
            response.setContentLength((int) fc.getContent().length);
            out.write(fc.getContent());
        }
        out.close();
    }

    @RequestMapping(value = "/documents/custom/{template}/{elementId}", method = RequestMethod.GET)
    public String customPageElement(@PathVariable(value = "template") String templateName, @PathVariable(value = "elementId") Long elementId, HttpServletRequest request, HttpSession session, HttpServletResponse resp, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        templateName=escapeHtml4(templateName);
        initModel(request, model, user, docService, resp);
        if (session.getAttribute("rootBrowse") == null) {
            session.setAttribute("rootBrowse", docService.getRootBrowsableElementTypes(user));
        }
        model.put("rootBrowse", session.getAttribute("rootBrowse"));


        if (session.getAttribute("hasCalendars") == null) {
            session.setAttribute("hasCalendars", docService.isAvailablesCalendars(user));
        }
        model.put("hasCalendars", session.getAttribute("hasCalendars"));

        if (session.getAttribute("getCreatableRootElementTypes") == null) {
            session.setAttribute("getCreatableRootElementTypes", docService.getCreatableRootElementTypes(user));
        }
        model.put("getCreatableRootElementTypes", session.getAttribute("getCreatableRootElementTypes"));


        int limit = 20;
        HashMap<String, String> data = new HashMap<String, String>();
        Enumeration paramNames = request.getParameterNames();
        while (paramNames.hasMoreElements()) {
            String paramName = (String) paramNames.nextElement();
            data.put(paramName, request.getParameter(paramName));
        }
        model.put("parameters", data);
        //Verificare sessione emendamento e iniettare metadati modificati
        Long emeSessionId = user.getEmeSessionId();
        Element el = docService.getElement(elementId, emeSessionId);
        docService.loadCustomGroupsForUser(user, el);
        Policy pol = el.getUserPolicy(user);
        if (session.getAttribute("events-" + elementId) == null) {
            session.setAttribute("events-" + elementId, docService.getEvents(user, el));
        }
        model.put("events-" + elementId, session.getAttribute("events-" + elementId));
        if (session.getAttribute("policies") == null) {
            session.setAttribute("policies", docService.getPolicies());
        }
        model.put("policies", session.getAttribute("policies"));

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
        }        */
        if (!pol.isCanView()) return "documents/NotPermitted";
        if (pol.isCanAddChild()) {
            model.put("getCreatableElementTypes", docService.getCreatableElementTypes(el, user));
        }
        List<org.activiti.engine.runtime.ProcessInstance> activeProcesses = docService.getActiveProcesses(user, el);
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
        //model.put("groupItems",docService.getGrouppedElements(el.getId(),user));
        return "documents/custom/" + templateName;
    }

    @RequestMapping(value = "/documents/ajaxCustom/{template}/{elementId}", method = RequestMethod.GET)
    public String ajaxCustomPageElement(@PathVariable(value = "template") String templateName, @PathVariable(value = "elementId") Long elementId, HttpServletRequest request, HttpServletResponse resp, HttpSession session, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        templateName=escapeHtml4(templateName);
        initModel(request, model, user, docService, resp);
        if (session.getAttribute("rootBrowse") == null) {
            session.setAttribute("rootBrowse", docService.getRootBrowsableElementTypes(user));
        }
        model.put("rootBrowse", session.getAttribute("rootBrowse"));


        if (session.getAttribute("hasCalendars") == null) {
            session.setAttribute("hasCalendars", docService.isAvailablesCalendars(user));
        }
        model.put("hasCalendars", session.getAttribute("hasCalendars"));

        if (session.getAttribute("getCreatableRootElementTypes") == null) {
            session.setAttribute("getCreatableRootElementTypes", docService.getCreatableRootElementTypes(user));
        }
        model.put("getCreatableRootElementTypes", session.getAttribute("getCreatableRootElementTypes"));

        int limit = 20;
        HashMap<String, String> data = new HashMap<String, String>();
        Enumeration paramNames = request.getParameterNames();
        while (paramNames.hasMoreElements()) {
            String paramName = (String) paramNames.nextElement();
            data.put(paramName, request.getParameter(paramName));
        }
        model.put("parameters", data);
        Element el = docService.getElement(elementId);
        docService.loadCustomGroupsForUser(user, el);
        Policy pol = el.getUserPolicy(user);

        if (session.getAttribute("policies") == null) {
            session.setAttribute("policies", docService.getPolicies());
        }
        model.put("policies", session.getAttribute("policies"));

        if (!pol.isCanView()) return "documents/NotPermitted";
        return "documents/custom/" + templateName;
    }


    @RequestMapping(value = "/documents/getAttach/uniqueId/{elementId}/{uniqueId}", method = RequestMethod.GET)
    public void getAttachUniqueId(@PathVariable(value = "elementId") Long elementId, @PathVariable(value = "uniqueId") Long uniqueId, HttpServletRequest request, HttpServletResponse response, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        /*
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        initModel(request, model, user, docService, response);
        Element el = docService.getElement(elementId);
        docService.loadCustomGroupsForUser(user,el);
        if (el.getUserPolicy(user).isCanView()) {
            BaseFile f = null;
            String filePath="";
            if (el.getFile().getContent().getId().equals(uniqueId)) f = el.getFile();
            if (f == null) {
                for (AuditFile f1 : el.getAuditFiles()) {
                    if (f1.getUniqueId().equals(uniqueId)) {
                        f = f1;
                    }
                }
            }
            if (f != null) {
                response.setHeader("Content-Disposition", "attachment; filename=\"" + f.getFileName() + "\"");
                ServletOutputStream out = response.getOutputStream();
                if (el.getType().getFileOnFS()){
                    FileInputStream fis = new FileInputStream(f.getFsFullPath());
                    int BUFF_SIZE = 1024;
                    byte[] buffer = new byte[BUFF_SIZE];
                    int byteRead = 0;
                    while ((byteRead = fis.read(buffer)) != -1) {
                        out.write(buffer, 0, byteRead);
                    }
                }else {
                    BaseFileContent fc = f.getContent();
                    response.setContentLength((int) fc.getContent().length);
                    out.write(fc.getContent());
                }
                out.close();
            }
        }
        */
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        AuditFile file = docService.getOldVersion(uniqueId);
        Element el = file.getElRef();
        Policy pol = el.getUserPolicy(user);
        ServletOutputStream out = response.getOutputStream();
        if (!elementId.equals(el.getId())) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Errore richiesta inconsistente");
            out.write("Errore richiesta inconsistente.".getBytes());
            return;

        }
        if (!pol.isCanView()) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Non ho i permessi di lettura");
            out.write("Errore permessi insufficienti.".getBytes());
            return;
        }
        response.setHeader("Content-Disposition", "attachment; filename=\"" + file.getFileName() + "\"");
        if (el.getType().getFileOnFS()) {
            String fname = el.getFile().getFsFullPath();
            try (FileInputStream fis = new FileInputStream(fname)) {
                int BUFF_SIZE = 1024;
                byte[] buffer = new byte[BUFF_SIZE];
                int byteRead = 0;
                while ((byteRead = fis.read(buffer)) != -1) {
                    out.write(buffer, 0, byteRead);
                }
            }

        } else {
            AuditFileContent fc = file.getContent();
            response.setContentLength((int) fc.getContent().length);
            out.write(fc.getContent());
        }
        out.close();
    }

    @RequestMapping(value = "/documents/custom/{template}", method = RequestMethod.GET)
    public String customPage(@PathVariable(value = "template") String templateName, HttpServletRequest request, HttpServletResponse resp, @ModelAttribute("model") ModelMap model, HttpSession session) throws DocumentException, IOException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        templateName=escapeHtml4(templateName);
        initModel(request, model, user, docService, resp);
        if (session.getAttribute("hasCalendars") == null) {
            session.setAttribute("hasCalendars", docService.isAvailablesCalendars(user));
        }
        model.put("hasCalendars", session.getAttribute("hasCalendars"));
        if (session.getAttribute("rootBrowse") == null) { //TOSCANA-197
            session.setAttribute("rootBrowse", docService.getRootBrowsableElementTypes(user));
        }
        model.put("rootBrowse", session.getAttribute("rootBrowse"));
        //model.put("rootBrowse", docService.getRootBrowsableElementTypes(user));
        //model.put("getCreatableRootElementTypes", docService.getCreatableRootElementTypes(user));

        int limit = 20;
        HashMap<String, String> data = new HashMap<String, String>();
        Enumeration paramNames = request.getParameterNames();
        while (paramNames.hasMoreElements()) {
            String paramName = (String) paramNames.nextElement();
            data.put(paramName, request.getParameter(paramName));
        }
        model.put("parameters", data);
        model.put("area", "documents");

        //model.put("numChilds", docService.getNumRootChilds(user));
        //int page = 1;
        //if (request.getParameter("p") != null && !request.getParameter("p").isEmpty())
        //    page = Integer.parseInt(request.getParameter("p"));
        //String orderBy = "";
        //String orderType = "";
        //if (request.getParameter("orderBy") != null && !request.getParameter("orderBy").isEmpty())
        //    orderBy = request.getParameter("orderBy");
        //if (request.getParameter("orderType") != null && !request.getParameter("orderType").isEmpty())
        //    orderType = request.getParameter("orderType");
        //model.put("rootElements", docService.getRootElementsLimit(user, page, limit, orderBy, orderType));
        //model.put("page", page);
        //model.put("rpp", limit);
        if (session.getAttribute("getCreatableRootElementTypes") == null) {
            session.setAttribute("getCreatableRootElementTypes", docService.getCreatableRootElementTypes(user));
        }
        model.put("getCreatableRootElementTypes", session.getAttribute("getCreatableRootElementTypes"));
        return "documents/custom/" + templateName;
    }


}
