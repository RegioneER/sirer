package it.cineca.siss.axmr3.doc.web.controllers.rest;

import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.authentication.services.SissUserService;
import it.cineca.siss.axmr3.common.mvc.handlers.ControllerHandler;
import it.cineca.siss.axmr3.doc.acl.Policy;
import it.cineca.siss.axmr3.doc.acl.TemplatePolicy;
import it.cineca.siss.axmr3.doc.beans.InternalServiceBean;
import it.cineca.siss.axmr3.doc.entities.*;
import it.cineca.siss.axmr3.doc.json.DmSessionDetailsJSON;
import it.cineca.siss.axmr3.doc.json.ElementJSON;
import it.cineca.siss.axmr3.doc.json.ElementJSONDM;
import it.cineca.siss.axmr3.doc.types.PostResult;
import it.cineca.siss.axmr3.doc.web.exceptions.RestException;
import it.cineca.siss.axmr3.doc.web.services.DocumentService;
import it.cineca.siss.axmr3.exceptions.AxmrGenericException;

import org.activiti.engine.runtime.ProcessInstance;
import org.apache.ibatis.annotations.Param;
import org.apache.log4j.Logger;
import org.dom4j.DocumentException;
import org.restlet.resource.Post;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.multipart.MultipartHttpServletRequest;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.*;

/**
 * Created by cin0562a on 06/10/15.
 */
@Controller
public class RestDmController {

    protected static final String NOT_AUTHORIZED = "NON_AUTHORIZED";
    protected static final String SESSION_NOT_PRESENT = "SESSION_NOT_PRESENT";
    protected static final Logger log = Logger.getLogger(RestDmController.class);
    @Autowired
    protected DocumentService docService;

    public DocumentService getDocService() {
        return docService;
    }

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

    @Autowired
    protected InternalServiceBean isb;

    public InternalServiceBean getIsb() {
        return isb;
    }

    public void setIsb(InternalServiceBean isb) {
        this.isb = isb;
    }

    public void elementIdxUpdate(Element el) {
        if (isb.isActive()) {
            isb.doInternalAsyncRequest("/rest/elk/elementIdxUpdate/" + el.getId());
        }
    }

    @RequestMapping(value = "/rest/dm/getActiveSession", method = RequestMethod.GET)
    public @ResponseBody
    DataManagementSession getActiveSession(HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        return docService.getActiveDmSession(user);
    }

    @RequestMapping(value = "/rest/dm/startSession", method = RequestMethod.POST)
    public @ResponseBody
    PostResult createSession(HttpServletRequest request,
                             @RequestParam(value = "comment", required = true, defaultValue = "") String comment,
                             @RequestParam(value = "issueCode", required = true, defaultValue = "") String issueCode
    ) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if (docService.isDm(user)) {
            if (docService.getActiveDmSession(user) == null) {
                try {
                    DataManagementSession dm = new DataManagementSession();
                    dm.setStartDt(new GregorianCalendar());
                    dm.setUserid(user.getUsername());
                    dm.setComment(comment);
                    dm.setIssueCode(issueCode);
                    docService.saveDmSession(dm);
                    PostResult pr = new PostResult("OK");
                    HashMap<String, Object> ret = new HashMap<String, Object>();
                    ret.put("sessionId", dm);
                    pr.setResultMap(ret);
                    return pr;
                } catch (Exception ex) {
                    return new PostResult(ex.getMessage());
                }
            } else {
                return new PostResult("SESSION_ALREADY_PRESENT");
            }
        } else {
            return new PostResult(NOT_AUTHORIZED);
        }
    }

    @RequestMapping(value = "/rest/dm/updateSession", method = RequestMethod.POST)
    public @ResponseBody
    PostResult updateSession(HttpServletRequest request,
                             @RequestParam(value = "comment", required = false) String comment,
                             @RequestParam(value = "issueCode", required = false) String issueCode
    ) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if (docService.isDm(user)) {
            DataManagementSession dm = docService.getActiveDmSession(user);
            if (dm == null) {
                return new PostResult(SESSION_NOT_PRESENT);
            }
            if (comment != null) dm.setComment(comment);
            if (issueCode != null) dm.setIssueCode(issueCode);
            try {
                docService.saveDmSession(dm);
            } catch (AxmrGenericException e) {
                return new PostResult(e.getMessage());
            }
            return new PostResult("OK");
        } else {
            return new PostResult(NOT_AUTHORIZED);
        }
    }

    @RequestMapping(value = "/rest/dm/closeSession", method = RequestMethod.POST)
    public @ResponseBody
    PostResult closeSession(HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if (docService.isDm(user)) {
            DataManagementSession dm = docService.getActiveDmSession(user);
            if (dm == null) {
                return new PostResult(SESSION_NOT_PRESENT);
            }
            dm.setEndDt(new GregorianCalendar());
            try {
                docService.saveDmSession(dm);
            } catch (AxmrGenericException e) {
                return new PostResult(e.getMessage());
            }
            PostResult ps = new PostResult("OK");
            ps.setRet(dm.getId());
            return ps;
        } else {
            return new PostResult(NOT_AUTHORIZED);
        }
    }

    @RequestMapping(value = "/rest/dm/updateMetadataFromTable/{tableName}", method = RequestMethod.POST)
    public @ResponseBody
    PostResult updateMetadataFromTable(HttpServletRequest request, @PathVariable(value = "tableName") String tableName) {

        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Sono dentro updateMetadataFromTable");

        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if (!docService.isDm(user)) {
            return new PostResult(NOT_AUTHORIZED);
        }
        DataManagementSession dm = docService.getActiveDmSession(user);
        if (dm == null) {
            return new PostResult(SESSION_NOT_PRESENT);
        }
        try {
            String sqlTableExists = "select count(*) as n from user_tables where upper(table_name)=upper(?)";
            try (Connection conn = docService.getDataSource().getConnection()) {
                try (PreparedStatement stmt = conn.prepareStatement(sqlTableExists)) {
                    stmt.setString(1, tableName);
                    try (ResultSet rset = stmt.executeQuery()) {
                        String sqlBatchUpdates;
                        String elId;
                        String name;
                        String tname;
                        String fname;
                        String[] myArrayValue = new String[1];
                        boolean recordPresent = rset.next();
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "\n\ncontrollo esistenza tabella di appoggio=" + sqlTableExists);
                        if (recordPresent) {
                            it.cineca.siss.axmr3.log.Log.debug(getClass(), "\n\nTabella " + tableName + " esistente");
                            sqlBatchUpdates = "select * from " + tableName + "";
                            try (PreparedStatement stmtBatchUpdates = conn.prepareStatement(sqlBatchUpdates)) {
                                try (ResultSet rsetBatchUpdates = stmtBatchUpdates.executeQuery()) {
                                    while (rsetBatchUpdates.next()) {
                                        elId = rsetBatchUpdates.getString("ELEMENT_ID");
                                        tname = rsetBatchUpdates.getString("TEMPLATENAME");
                                        fname = rsetBatchUpdates.getString("FIELDNAME");
                                        name = tname + "_" + fname;
                                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "\n\naggiorno " + elId + " - "+name+" : "+rsetBatchUpdates.getString("VALUE"));
                                        myArrayValue[0] = rsetBatchUpdates.getString("VALUE");
                                        try {
                                            Element el = docService.getElement(elId);
                                            for (MetadataTemplate t : el.getTemplates()) {
                                                if (t.getName().toUpperCase().equals(tname.toUpperCase())) {
                                                    for (MetadataField f : t.getFields()) {
                                                        if (f.getName().toUpperCase().equals(fname.toUpperCase())) {
                                                            docService.dmUpdateMetadata(user, Long.parseLong(elId), f.getId(), myArrayValue);
                                                        }
                                                    }
                                                }
                                            }
                                        } catch (AxmrGenericException e) {
                                            return new PostResult(e.getMessage());
                                        }
                                    }
                                    return new PostResult("OK");
                                }
                            }
                        } else {
                            return new PostResult("TABLE_NOT_PRESENT");
                        }
                    }


                }


            }

        } catch (SQLException e) {
            return new PostResult("TABLE_NOT_PRESENT");
        }
    }


    @RequestMapping(value = "/rest/dm/updateMetdataField/{elId}", method = RequestMethod.POST)
    public @ResponseBody
    PostResult updateMetadata(HttpServletRequest request, @PathVariable(value = "elId") Long elId, @Param(value = "name") String name, @Param(value = "value") String value) {

        it.cineca.siss.axmr3.log.Log.debug(getClass(),"Sono dentro updateMetdataField");

        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if (!docService.isDm(user)) {
            return new PostResult(NOT_AUTHORIZED);
        }
        DataManagementSession dm = docService.getActiveDmSession(user);
        if (dm == null) {
            return new PostResult(SESSION_NOT_PRESENT);
        }
        try {
            Element el = docService.getElement(elId);
            Iterator<ElementMetadata> it = el.getData().iterator();
            while (it.hasNext()) {
                ElementMetadata emd = it.next();
                String fieldName = emd.getTemplateName() + "_" + emd.getFieldName();
                if (fieldName.equals(name)) {
                    docService.dmUpdateMetadata(user, elId, emd.getField().getId(), request.getParameterValues("value"));
                    return new PostResult("OK");
                }
            }
            PostResult pres = new PostResult("ERROR");
            pres.setErrorMessage("FIELD_NOT_FOUND");
            elementIdxUpdate(el);
            return pres;
        } catch (AxmrGenericException e) {
            return new PostResult(e.getMessage());
        }
    }

    @RequestMapping(value = "/rest/dm/updateMetdata/{elId}/{mdId}", method = RequestMethod.POST)
    public @ResponseBody
    PostResult updateMetadata(HttpServletRequest request, @PathVariable(value = "elId") Long elId, @PathVariable(value = "mdId") Long mdId) {


        it.cineca.siss.axmr3.log.Log.debug(getClass(),"Sono dentro updateMetadata");

        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if (!docService.isDm(user)) {
            return new PostResult(NOT_AUTHORIZED);
        }
        DataManagementSession dm = docService.getActiveDmSession(user);
        if (dm == null) {
            return new PostResult(SESSION_NOT_PRESENT);
        }
        try {

            docService.dmUpdateMetadata(user , elId, mdId, request.getParameterValues("value"));
            elementIdxUpdate(docService.getElement(elId));
            return new PostResult("OK");
        } catch (AxmrGenericException e) {
            return new PostResult(e.getMessage());
        }
    }
    /**
     * Allega un file all'elemento
     *
     * POST Parameters:
     * - version (String)
     * - data (String): dd/MM/yyyy
     * - note (String)
     * - autore (String)
     * - file (Multipart)
     *
     * @param id
     * @param request
     * @return

     */
    @RequestMapping(value = "/rest/dm/attachFile/{id}", method = RequestMethod.POST)
    public @ResponseBody
    PostResult attach( HttpServletRequest request, @PathVariable(value = "id") Long id) throws IOException {
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"Sono dentro updateMetadata");
        PostResult res;
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if (!docService.isDm(user)) {
            return new PostResult(NOT_AUTHORIZED);
        }
        DataManagementSession dm = docService.getActiveDmSession(user);
        if (dm == null) {
            return new PostResult(SESSION_NOT_PRESENT);
        }
        try {
            List<File> ret = new LinkedList<File>();
            Integer versionAuto = 0;
            Element el = docService.getElement(id);
            byte[] file = null;
            String fileName = null;
            Long fileSize = null;
            String version = "";
            if (request.getParameter("version") != null) {
                version = request.getParameter("version");
                if (version.equals("auto")) {
                    versionAuto = el.getAuditFiles().size() + 2;
                    version = versionAuto.toString();
                }
            }
            String date = "";
            if (request.getParameter("date") != null) date = request.getParameter("date");
            String note = "";
            if (request.getParameter("note") != null) note = request.getParameter("note");
            String autore = "";
            if (request.getParameter("autore") != null) autore = request.getParameter("autore");
            if (request instanceof MultipartHttpServletRequest) {
                MultipartFile mfile = ((MultipartHttpServletRequest) request).getFile("file");
                if(mfile!=null) {
                    file = mfile.getBytes();
                    fileName = mfile.getOriginalFilename();
                    fileSize = mfile.getSize();
                }
            }
            try {
                docService.dmAttachFile(user, el, file, fileName, fileSize, version, date, note, autore);
            } catch (RestException e) {
                log.error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
                res = new PostResult("ERROR");
                res.setErrorMessage(e.getMessage());
                res.setErrorCode(e.getCode());
                return res;
            }
            res = new PostResult("OK");
            res.setRedirect(ControllerHandler.getBaseUrl(request) + "/app/documents/detail/" + el.getId());
        } catch (AxmrGenericException e) {
            return new PostResult(e.getMessage());
        }
        return res;
    }
    @RequestMapping(value = "/rest/dm/get/details/", method = RequestMethod.GET)
    public @ResponseBody
    PostResult getActiveSessionDetails(HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if (!docService.isDm(user)) {
            return new PostResult(NOT_AUTHORIZED);
        }
        DataManagementSession dm = docService.getActiveDmSession(user);
        if (dm == null) {
            return new PostResult(SESSION_NOT_PRESENT);
        }
        return this.dmSessionDetails(request, dm, user);
    }

    @RequestMapping(value = "/rest/dm/get/details/{sessionId}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult getSessionDetailsById(HttpServletRequest request, @PathVariable(value = "sessionId") Long sessionId) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if (!docService.isDm(user)) {
            return new PostResult(NOT_AUTHORIZED);
        }
        DataManagementSession dm = docService.getDmSession(sessionId);
        return this.dmSessionDetails(request, dm, user);

    }

    @RequestMapping(value = "/rest/dm/get/details/{userid}/{sessionId}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult getSessionDetailsById(HttpServletRequest request, @PathVariable(value = "userid") String userid, @PathVariable(value = "sessionId") Long sessionId) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if (!userid.equals("CE_EME_DM") && !docService.isDm(user)) {
            return new PostResult(NOT_AUTHORIZED);
        }
        DataManagementSession dm = docService.getDmSession(sessionId);
        return this.dmSessionDetails(request, dm, user);

    }


    @Autowired
    @Qualifier("messagesFolder")
    protected String messagesFolder;

    /**
     * costruisce oggetto di dettaglio della sessione di data management
     * @param dm sessione di data management
     * @return
     */
    private PostResult dmSessionDetails(HttpServletRequest request, DataManagementSession dm, IUser user) {
        PostResult ret = new PostResult("OK");
        HashMap<String, Object> hmap = new HashMap<String, Object>();
        DmSessionDetailsJSON dms = new DmSessionDetailsJSON();
        dms.setDm(dm);
        for (DataManagementAction a : docService.getDmActions(dm)) {
            dms.addElementAction(a, user);
        }
        Properties adHocProps = new Properties();
        try {
            FileInputStream fis = new FileInputStream(messagesFolder + "/messages/" + ControllerHandler.getLocale(request).getLanguage() + "_" + ControllerHandler.getLocale(request).getCountry() + ".properties");
            adHocProps.load(fis);
            fis.close();
        } catch (IOException e) {
            log.error(e.getMessage(), e);
        }
        for (AuditMetadata a : docService.getDmAudits(dm)) {
            dms.addElementActionAudit(a, adHocProps);
        }
        hmap.put("DM_SESSION", dms);
        ret.setResultMap(hmap);
        return ret;
    }

    @RequestMapping(value = "/rest/dm/startProcess", method = RequestMethod.POST)
    public @ResponseBody
    PostResult startProcess(HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        String processKey = request.getParameter("pKey");
        Long elId = Long.parseLong(request.getParameter("elId"));
        Element el = docService.getElement(elId);
        String username = null;
        if (request.getParameter("overrideUser") != null) {
            List<? extends IUser> searchRes = userService.searchUserByUsername(request.getParameter("overrideUser"));
            for (IUser u : searchRes) {
                if (u.getUsername().toLowerCase().equals(request.getParameter("overrideUser").toLowerCase())) {
                    username = u.getUsername();
                }
            }
            if (username == null) {
                PostResult res = new PostResult("ERROR");
                res.setErrorMessage("USERNAME NON TROVATO");
                return res;
            }
        } else {
            username = user.getUsername();
        }
        String pId = "";
        try {
            pId = docService.startProcess(username, el, processKey);
            docService.registerDmAction(user, el, "START_PROCESS", "processKey: " + processKey + " process Instance Id: " + pId);
        } catch (AxmrGenericException e) {
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
        }
        PostResult res = new PostResult("OK");
        res.setRet(pId);
        return res;
    }

    @RequestMapping(value = "/rest/dm/terminateProcess", method = RequestMethod.POST)
    public @ResponseBody
    PostResult terminateProcess(HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        String processKey = request.getParameter("pKey");
        Long elId = Long.parseLong(request.getParameter("elId"));
        Element el = docService.getElement(elId);
        String processId = request.getParameter("pId");
        try {
            docService.terminateProcess(user, processId);
            docService.registerDmAction(user, el, "TERMINATE_PROCESS", "processKey: " + processKey + " process Instance Id: " + processId);
        } catch (AxmrGenericException e) {
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
        }
        PostResult res = new PostResult("OK");
        return res;
    }
    @RequestMapping(value = "/rest/dm/terminateAllProcesses", method = RequestMethod.POST)
    public @ResponseBody
    PostResult terminateAllProcesses(HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Long elId = Long.parseLong(request.getParameter("elId"));
        Element el = docService.getElement(elId);
        try {
            List<ProcessInstance> activeProcesses;//
            activeProcesses = docService.getActiveProcesses(el);
            //it.cineca.siss.axmr3.log.Log.debug(getClass(),"CERCO IL WF "+processDefinition+": ASSOCIATO ALL'elemento= "+elId);
            for(ProcessInstance process:activeProcesses){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"HO TROVATO = "+process.getProcessDefinitionId());
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"PROVO A TERMINARE = "+process.getProcessDefinitionId());
                docService.terminateProcess(user ,process.getProcessInstanceId());
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"HO TERMINATO = "+process.getProcessDefinitionId());
                docService.registerDmAction(user, el, "TERMINATE_PROCESS", "processKey: " + process.getProcessDefinitionId() + " process Instance Id: " + process.getProcessInstanceId());
            }

        } catch (AxmrGenericException e) {
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
        }
        PostResult res = new PostResult("OK");
        return res;
    }

    @RequestMapping(value="/rest/dm/terminateProcessByDefinition", method= RequestMethod.POST)
    public @ResponseBody
    PostResult terminateProcessByDefinition(HttpServletRequest request){
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        String processDefinition=request.getParameter("pDefinition");
        Long elId=Long.parseLong(request.getParameter("elId"));
        Element el=docService.getElement(elId);
        List<ProcessInstance> activeProcesses;
        activeProcesses = docService.getActiveProcesses(el);
        try {
            for(ProcessInstance process:activeProcesses){
                if(process.getProcessDefinitionId().startsWith(processDefinition+":")){
                    docService.terminateProcess(user ,process.getProcessInstanceId());
                    docService.registerDmAction(user,el,"TERMINATE_PROCESS","processDefinition: "+processDefinition+" process Instance Id: "+process.getProcessInstanceId());
                }
            }
        } catch (AxmrGenericException e) {
            PostResult res=new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
        }
        PostResult res=new PostResult("OK");
        return res;
    }



    @RequestMapping(value = "/rest/dm/addChild/{parentElementId}/{childTypeId}/{userId}", method = RequestMethod.POST)
    public @ResponseBody
    PostResult addChild(@PathVariable(value = "parentElementId") Long parentElementId, @PathVariable(value = "childTypeId") Long childTypeId, @PathVariable(value = "userId") String userId, HttpServletRequest request, HttpServletResponse resp) throws RestException {
        IUser userInstance = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        String user = userInstance.getUsername();
        try {
            Element el = docService.dmAddChild(parentElementId, childTypeId, userId, user);
            docService.registerDmAction(userInstance, el, "CREATE CHILD", "child Id: " + el.getId() + " - child Type Id: " + childTypeId + " - parent Id: " + parentElementId);
            PostResult res = new PostResult("OK");
            ElementJSON myJsonElement = new ElementJSON(el, userInstance, "single");
            res.setRet(myJsonElement);
            elementIdxUpdate(el);
            return res;
        } catch (AxmrGenericException e) {
            log.error(e.getMessage(), e);
            throw new RestException(e.getMessage(), docService.getTxManager());
        }
    }

    @RequestMapping(value = "/rest/dm/{parentElementId}/acl/delete/{aclId}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult aclRemove(@PathVariable(value = "parentElementId") Long parentElementId, @PathVariable(value = "aclId") Long aclId, HttpServletRequest request, HttpServletResponse resp) throws RestException {
        IUser userInstance = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        String user = userInstance.getUsername();
        Element el = docService.getElement(parentElementId);
        docService.loadCustomGroupsForUser(userInstance, el);
        try {
            docService.deleteAcl(userInstance, el, aclId);
            docService.registerDmAction(userInstance, el, "REMOVE POLICY", "Element Id: " + el.getId() + " - ACL Id: " + aclId);

        } catch (AxmrGenericException e) {
            log.error(e.getMessage(), e);
            return new PostResult("KO");
            //throw new RestException(e.getMessage(), docService.getTxManager());
        }
        elementIdxUpdate(el);
        return new PostResult("OK");
    }

    @RequestMapping(value = "/rest/dm/{elementId}/acl/edit/{aclId}/{field}", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult editACL(@PathVariable(value = "elementId") Long elementId, @PathVariable(value = "aclId") Long aclId, @PathVariable(value = "field") String field, HttpServletRequest request, HttpServletResponse response) throws RestException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Long id = aclId;
        Element el = docService.getElement(elementId);
        Acl acl = docService.getAcl(el, id);
        boolean value = false;
        Long policyId = null;
        if (request.getParameter("value") != null) {
            value = Boolean.parseBoolean(request.getParameter("value"));
        }
        if (request.getParameter("policyId") != null) {
            policyId = Long.parseLong(request.getParameter("policyId"));
        }
        try {
            docService.setAclValue(user, acl, field, value, policyId);
            if (policyId != null) {
                docService.registerDmAction(user, el, "MODIFIED POLICY", "Element Id: " + el.getId() + " - ACL Id: " + aclId + " - Modified Field: " + field + " - Value: " + value);
            } else {
                docService.registerDmAction(user, el, "MODIFIED POLICY", "Element Id: " + el.getId() + " - ACL Id: " + aclId + " - Added Predefined Policy: " + policyId);
            }
        } catch (AxmrGenericException e) {
            log.error(e.getMessage(), e);
        }
        elementIdxUpdate(el);
        PostResult res = new PostResult("OK");
        return res;
    }


    @RequestMapping(value = "/rest/dm/{elementId}/acl/edit/{aclId}/removeContainer/{containerId}", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult removeContainerFromACL(@PathVariable(value = "elementId") Long elementId, @PathVariable(value = "aclId") Long aclId, @PathVariable(value = "containerId") Long containerId, HttpServletRequest request, HttpServletResponse response) throws RestException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Long id = aclId;
        Element el = docService.getElement(elementId);
        Acl acl = docService.getAcl(el, id);
        boolean value = false;
        Long policyId = null;
        if (request.getParameter("value") != null) {
            value = Boolean.parseBoolean(request.getParameter("value"));
        }
        if (request.getParameter("policyId") != null) {
            policyId = Long.parseLong(request.getParameter("policyId"));
        }
        try {
            docService.removeContainerFromACL(user, acl, containerId);
            docService.registerDmAction(user, el, "MODIFIED POLICY", "Element Id: " + el.getId() + " - ACL Id: " + aclId + " - Removed Container: " + containerId);
        } catch (AxmrGenericException e) {
            log.error(e.getMessage(), e);
        }
        elementIdxUpdate(el);
        PostResult res = new PostResult("OK");
        return res;
    }

    @RequestMapping(value = "/rest/dm/{elementId}/acl/edit/{aclId}/addContainer", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult addContainerToACL(@PathVariable(value = "elementId") Long elementId, @PathVariable(value = "aclId") Long aclId, HttpServletRequest request, HttpServletResponse response) throws RestException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Long id = aclId;
        Element el = docService.getElement(elementId);
        Acl acl = docService.getAcl(el, id);
        List<String> groups = new LinkedList<String>();
        List<String> users = new LinkedList<String>();
        if (request.getParameter("groups") != null && !request.getParameter("groups").isEmpty())
            groups = new LinkedList<String>(Arrays.asList(request.getParameter("groups").split(",")));
        if (request.getParameter("users") != null && !request.getParameter("users").isEmpty())
            users = new LinkedList<String>(Arrays.asList(request.getParameter("users").split(",")));
        if (request.getParameter("cgroup") != null && !request.getParameter("cgroup").isEmpty()) {
            groups.add(new String("cgroup"));
        }
        if (request.getParameter("cuser") != null && !request.getParameter("cuser").isEmpty()) {
            users.add(new String("cuser"));
        }
        if (request.getParameter("allUsers") != null && !request.getParameter("allUsers").isEmpty()) {
            users.add(new String("*"));
        }

        try {
            docService.addContainerToACL(user, acl, groups, users);//todo: modifica return metodo: id containers aggiunti
            docService.registerDmAction(user, el, "ADDED Container", "Acl Id: " + id);//todo: aggiungere id containers aggiunti
        } catch (AxmrGenericException e) {
            log.error(e.getMessage(), e);
        }
        elementIdxUpdate(el);
        PostResult res = new PostResult("OK");
        return res;
    }

    @RequestMapping(value = "/rest/dm/{elementId}/acl/edit/{aclId}/addTemplatePolicy", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult addTemplateToACL(@PathVariable(value = "elementId") Long elementId, @PathVariable(value = "aclId") Long aclId, HttpServletRequest request, HttpServletResponse response) throws RestException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Long id = aclId;
        Element el = docService.getElement(elementId);
        Acl acl = docService.getAcl(el, id);
        String templateToAdd = "";
        if (request.getParameter("templateToAdd") != null && !request.getParameter("templateToAdd").isEmpty()) {
            templateToAdd = request.getParameter("templateToAdd");
        }

        try {
            docService.addTemplateToACL(user, acl, templateToAdd);
            docService.registerDmAction(user, el, "ADDED ad hoc template to ACL", "Acl Id: " + id + " ad hoc template: " + templateToAdd);
        } catch (AxmrGenericException e) {
            log.error(e.getMessage(), e);
        }
        elementIdxUpdate(el);
        PostResult res = new PostResult("OK");
        return res;
    }

    @RequestMapping(value = "/rest/dm/{elementId}/acl/edit/{aclId}/removeTemplatePolicy", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult removeTemplateFromACL(@PathVariable(value = "elementId") Long elementId, @PathVariable(value = "aclId") Long aclId, HttpServletRequest request, HttpServletResponse response) throws RestException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Long id = aclId;
        Element el = docService.getElement(elementId);
        Acl acl = docService.getAcl(el, id);
        String templateToRemove = "";
        if (request.getParameter("templateToRemove") != null && !request.getParameter("templateToRemove").isEmpty()) {
            templateToRemove = request.getParameter("templateToRemove");
        }

        try {
            docService.removeTemplateFromACL(user, acl);
            docService.registerDmAction(user, el, "REMOVED ad hoc template from ACL", "Acl Id: " + id + " ad hoc template: " + templateToRemove);
        } catch (AxmrGenericException e) {
            log.error(e.getMessage(), e);
        }
        elementIdxUpdate(el);
        PostResult res = new PostResult("OK");
        return res;
    }

    @RequestMapping(value = "/rest/dm/{elementId}/acl/create", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult createACL(@PathVariable(value = "elementId") Long elementId, HttpServletRequest request, HttpServletResponse response) throws RestException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Element el = docService.getElement(elementId);
        Long id = null;
        String detailTemplate = null;
        PredefinedPolicy pp = null;
        Policy pol = new Policy();

        if (request.getParameter("policyId").equals("0") || request.getParameter("policyId").isEmpty()) {
            boolean view = false;
            boolean create = false;
            boolean update = false;
            boolean addComment = false;
            boolean moderate = false;
            boolean delete = false;
            boolean changePermission = false;
            boolean addChild = false;
            boolean removeCheckOut = false;
            boolean launchProcess = false;
            boolean enableTemplate = false;
            boolean canBrowse = false;
            pol.setCanCreate(create);
            pol.setCanView(view);
            pol.setCanUpdate(update);
            pol.setCanAddComment(addComment);
            pol.setCanModerate(moderate);
            pol.setCanDelete(delete);
            pol.setCanChangePermission(changePermission);
            pol.setCanAddChild(addChild);
            pol.setCanRemoveCheckOut(removeCheckOut);
            pol.setCanLaunchProcess(launchProcess);
            pol.setCanEnableTemplate(enableTemplate);
            pol.setCanBrowse(canBrowse);
        } else {
            pp = docService.getPolicy(Long.parseLong(request.getParameter("policyId")));
            pol = pp.getPolicy();
        }
        List<String> groups = new LinkedList<String>();
        List<String> users = new LinkedList<String>();
        if (request.getParameter("groups") != null && !request.getParameter("groups").isEmpty())
            groups = Arrays.asList(request.getParameter("groups").split(","));
        if (request.getParameter("users") != null && !request.getParameter("users").isEmpty())
            users = Arrays.asList(request.getParameter("users").split(","));
        if (request.getParameter("cgroup") != null && !request.getParameter("cgroup").isEmpty()) {
            groups.add("cgroup");
        }
        if (request.getParameter("cuser") != null && !request.getParameter("cuser").isEmpty()) {
            users.add("cuser");
        }
        if (request.getParameter("allUsers") != null && !request.getParameter("allUsers").isEmpty()) {
            users.add("*");
        }
        String templateRef = null;
        if (request.getParameter("templateRef") != null && !request.getParameter("templateRef").isEmpty()) {
            templateRef = request.getParameter("templateRef");
        }
        try {
            docService.saveAcl(user, el, groups, users, pol, pp, null, null);
            docService.registerDmAction(user, el, "ADDED POLICY", "Element Id: " + el.getId());
        } catch (AxmrGenericException e) {
            log.error(e.getMessage(), e);
        }
        elementIdxUpdate(el);
        PostResult res = new PostResult("OK");
        return res;
    }

    /**
     * Aggiunge il template
     *
     * @param elId
     * @param templateId
     * @param request
     * @return
     * @throws RestException
     */
    @RequestMapping(value = "/rest/dm/{elId}/addTemplate/{templateId}", method = RequestMethod.POST)
    public @ResponseBody
    PostResult addTemplate(@PathVariable(value = "elId") Long elId, @PathVariable(value = "templateId") String templateId, HttpServletRequest request) throws RestException, AxmrGenericException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Element el = docService.getElement(elId);
        docService.loadCustomGroupsForUser(user, el);
        try {
            docService.addTemplate(user, el, templateId);
            docService.registerDmAction(user, el, "ADDED Template", "Element Id: " + elId + " Template Id:" + templateId);
        } catch (RestException e) {
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            return res;
        }
        PostResult res = new PostResult("OK");
        elementIdxUpdate(el);
        res.setRedirect(ControllerHandler.getBaseUrl(request) + "/app/documents/dm/edit/" + elId);
        return res;
    }


    @RequestMapping(value = "/rest/dm/{elId}/aclTemplate/{aclId}", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult updateAclTemplate(@PathVariable(value = "elId") Long elId, @PathVariable(value = "aclId") Long aclId,
                                 @RequestParam(value = "create") boolean create,
                                 @RequestParam(value = "update") boolean update,
                                 @RequestParam(value = "delete") boolean delete,
                                 @RequestParam(value = "view") boolean view) throws RestException, AxmrGenericException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();

        Element el = docService.getElement(elId);
        TemplatePolicy pol = new TemplatePolicy();
        if (create) pol.setCanCreate(true);
        else pol.setCanCreate(false);
        if (update) pol.setCanUpdate(true);
        else pol.setCanUpdate(false);
        if (delete) pol.setCanDelete(true);
        else pol.setCanDelete(false);
        if (view) pol.setCanView(true);
        else pol.setCanView(false);
        try {
            String oldACLvalueToPrint = docService.updateTemplateAclDM(aclId, pol);
            docService.registerDmAction(user, el, "Updated ACL Template", "Element Id: " + elId + " Acl Id:" + aclId + " Old Value: " + oldACLvalueToPrint);
            elementIdxUpdate(el);
            return new PostResult("OK");
        } catch (RestException e) {
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            return res;
        }
    }

    @RequestMapping(value = "/rest/dm/{elId}/templateAcl/addContainers/{assocId}", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult addContainerToAclTemplate(@PathVariable(value = "elId") Long elId, @PathVariable(value = "assocId") Long assocId,
                                         @RequestParam(value = "groups", required = false, defaultValue = "") String groups,
                                         @RequestParam(value = "users", required = false, defaultValue = "") String users,
                                         @RequestParam(value = "cuser", required = false, defaultValue = "") String cuser,
                                         @RequestParam(value = "allUsers", required = false, defaultValue = "") String allUsers) throws RestException, AxmrGenericException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Element el = docService.getElement(elId);
        List<String> usersList = new LinkedList<String>();
        if (!users.isEmpty()) {
            String[] usersArray = users.split(",");
            for (int i = 0; i < usersArray.length; i++) {
                usersList.add(usersArray[i]);
            }
        }
        if (!cuser.isEmpty()) {
            usersList.add("cuser");
        }
        if (!allUsers.isEmpty()) {
            usersList.add("*");
        }
        List<String> groupsList = new LinkedList<String>();
        if (!groups.isEmpty()) {
            String[] groupsArray = groups.split(",");
            for (int i = 0; i < groupsArray.length; i++) {
                groupsList.add(groupsArray[i]);
            }
        }

        try {
            String newContainers = docService.addContainersToTemplateAcl(assocId, usersList, groupsList);
            docService.registerDmAction(user, el, "Added container to ACL Template", "Element Id: " + elId + " Assoc Id:" + assocId + " New containers: " + newContainers);
            elementIdxUpdate(el);
            return new PostResult("OK");
        } catch (RestException e) {
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            return res;
        }
    }

    @RequestMapping(value = "/rest/dm/{elId}/templateAcl/{aclId}/removeContainer/{containerId}", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult removeContainerFromAclTemplate(@PathVariable(value = "elId") Long elId, @PathVariable(value = "aclId") Long aclId, @PathVariable(value = "containerId") Long containerId, HttpServletRequest request, HttpServletResponse response) throws RestException, AxmrGenericException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Element el = docService.getElement(elId);
        try {
            String container = docService.removeContainerFromTemplateAcl(user, aclId, containerId);
            docService.registerDmAction(user, el, "removed container from ACL Template", "Element Id: " + elId + " Container Id: " + containerId + " Acl Id:" + aclId + " removed container " + container);
            return new PostResult("OK");
        } catch (RestException e) {
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            elementIdxUpdate(el);
            return res;
        }
    }

    @RequestMapping(value = "/rest/dm/{elId}/templateAcl/remove/{aclId}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult deleteTemplateAclDM(@PathVariable(value = "elId") Long elId, @PathVariable(value = "aclId") Long aclId) throws RestException, AxmrGenericException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Element el = docService.getElement(elId);
        try {
            String oldACLvalueToPrint = docService.deleteTemplateAclDM(user, elId, aclId);
            docService.registerDmAction(user, el, "removed ACL Template", "Element Id: " + elId + " Acl Id:" + aclId + " Old Value:" + oldACLvalueToPrint);
            elementIdxUpdate(el);
            return new PostResult("OK");
        } catch (RestException e) {
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            return res;
        }

    }

    @RequestMapping(value = "/rest/dm/getElementACL/{elId}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult getElementACL(@PathVariable(value = "elId") Long elId) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        try {
            Element el = docService.getElement(elId);
            HashMap<String, List<Acl>> acls = new HashMap<String, List<Acl>>();
            acls.put("acls", (List<Acl>) el.getAcls());
            PostResult ret = new PostResult("OK");
            HashMap<String, Object> rs = new HashMap<String, Object>();
            rs.put("acls", acls);
            ret.setResultMap(rs);
            return ret;
        } catch (Exception ex) {
            return new PostResult(ex);
        }
    }

    @RequestMapping(value = "/rest/dm/recursiveAcl/{elId}", method = RequestMethod.POST)
    public @ResponseBody
    PostResult recursiveAcl(
            @PathVariable(value = "elId") Long elId,
            @RequestParam(value = "acltype", required = true) String aclType,
            @RequestParam(value = "isGroup", required = true) String isGroup,
            @RequestParam(value = "container", required = true) String container
    ) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        try {
            TemplatePolicy basePolicy = TemplatePolicy.createPolicyByCommaSeparatedString(aclType);
            if (isGroup.equals("1") || isGroup.toLowerCase().equals("true")) {
                docService.recursivePermissions(user, elId, basePolicy, container, true);
            } else {
                docService.recursivePermissions(user, elId, basePolicy, container, false);
            }
            return new PostResult("OK");
        } catch (Exception ex) {
            return new PostResult(ex);
        }
    }

    @RequestMapping(value = "/rest/dm/getElementTemplatesACL/{elId}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult getElementTemplatesACL(@PathVariable(value = "elId") Long elId) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        try {
            HashMap<String, List<TemplateAcl>> templatesACL = docService.getElementTemplatesACL(user, elId);
            PostResult ret = new PostResult("OK");
            HashMap<String, Object> rs = new HashMap<String, Object>();
            rs.put("acls", templatesACL);
            ret.setResultMap(rs);
            return ret;
        } catch (RestException ex) {
            return new PostResult(ex);
        }

    }

    @RequestMapping(value = "/rest/dm/{elId}/aclTemplate/newAcl/{templateName}", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult updateAclTemplate(@PathVariable(value = "elId") Long elId, @PathVariable(value = "templateName") String templateName) throws RestException, AxmrGenericException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Element el = docService.getElement(elId);
        try {
            Long aclId = docService.newTemplateAclDM(user, elId, templateName);
            docService.registerDmAction(user, el, "added new ACL to Template", "Element Id: " + elId + " Template Name:" + templateName + " new Acl Id:" + aclId);
            return new PostResult("OK");
        } catch (RestException e) {
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            return res;
        }
    }

    /**
     * Restituisce l'elemento objID (json)
     * @param objId
     * @param option
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     */
    @RequestMapping(value = "/rest/dm/getElementJSON/{objId}", method = RequestMethod.GET)
    public @ResponseBody
    ElementJSON getJSONDM(@PathVariable(value = "objId") Long objId, @RequestParam(value = "mode", required = false) String option, @RequestParam(value = "level", required = false) Integer level, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if (option == null) option = "complete-without-parent";
        if (level == null) level = 1;
        ElementJSON json = new ElementJSONDM(docService.getElement(objId), user, option, level);
        return json;
    }

    /**
     * Elimina l'elemento DM
     * @param elId
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     */
    @RequestMapping(value = "/rest/dm/deleteElement/{elId}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult deleteElementDM(@PathVariable(value = "elId") Long elId, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException, AxmrGenericException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Element el = docService.getElement(elId);
        PostResult res = new PostResult("OK");
        try {
            docService.deleteElementDM(user, docService.getElement(elId));
            docService.registerDmAction(user, el, "Element removed ", "Element Id: " + elId);
            res.setRedirect(ControllerHandler.getBaseUrl(request) + "/app/documents");
            elementIdxUpdate(el);
        } catch (RestException e) {
            res.setResult("ERROR");
            res.setErrorMessage(e.getMessage());
        }
        return res;
    }
}
