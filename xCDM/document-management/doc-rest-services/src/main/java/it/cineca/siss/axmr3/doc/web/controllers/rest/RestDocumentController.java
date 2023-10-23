package it.cineca.siss.axmr3.doc.web.controllers.rest;

import com.google.gson.Gson;
import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.authentication.impl.UserImpl;
import it.cineca.siss.axmr3.authentication.services.SissUserService;
import it.cineca.siss.axmr3.common.mvc.handlers.ControllerHandler;
import it.cineca.siss.axmr3.doc.acl.Policy;
import it.cineca.siss.axmr3.doc.acl.TemplatePolicy;
import it.cineca.siss.axmr3.doc.beans.InternalServiceBean;
import it.cineca.siss.axmr3.doc.entities.*;
import it.cineca.siss.axmr3.doc.entities.File;
import it.cineca.siss.axmr3.doc.json.ElementJSON;
import it.cineca.siss.axmr3.doc.json.JqGridJSON;
import it.cineca.siss.axmr3.doc.types.PostResult;
import it.cineca.siss.axmr3.doc.utils.AuditJSON;
import it.cineca.siss.axmr3.doc.utils.FormSpecification;
import it.cineca.siss.axmr3.doc.web.exceptions.RestException;
import it.cineca.siss.axmr3.doc.web.services.DocumentService;
import it.cineca.siss.axmr3.doc.xml.CheckResult;
import it.cineca.siss.axmr3.doc.xml.Form;
import it.cineca.siss.axmr3.exceptions.AxmrGenericException;
import org.activiti.engine.runtime.ProcessInstance;
import org.apache.commons.fileupload.FileUploadException;
import org.apache.commons.lang.StringEscapeUtils;
import org.apache.log4j.Logger;
import org.dom4j.DocumentException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.multipart.MultipartHttpServletRequest;
import org.xml.sax.SAXException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.xml.parsers.ParserConfigurationException;
import java.io.*;
import java.math.BigInteger;
import java.util.*;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 01/08/13
 * Time: 14.32
 * To change this template use File | Settings | File Templates.
 */
@Controller
public class RestDocumentController {

    static final Logger log = Logger.getLogger(RestDmController.class);
    @Autowired
    private SissUserService uService;

    public SissUserService getuService() {
        return uService;
    }

    public void setuService(SissUserService uService) {
        this.uService = uService;
    }

    @Autowired
    protected DocumentService docService;

    public DocumentService getDocService() {
        return docService;
    }

    public void setDocService(DocumentService docService) {
        this.docService = docService;
    }

    @Autowired
    protected InternalServiceBean isb;

    public InternalServiceBean getIsb() {
        return isb;
    }

    public void setIsb(InternalServiceBean isb) {
        this.isb = isb;
    }

    public void elementIdxUpdate(Element el, boolean fieldsToo) {
        if (isb.isActive()) {
            isb.doInternalAsyncRequest("/rest/elk/elementIdxUpdate/" + el.getId());
        }
    }

    @RequestMapping(value = "/rest/documents/status", method = RequestMethod.GET)
    public @ResponseBody
    PostResult getStatus() {
        return new PostResult("OK");
    }

    /**
     *
     */
    @RequestMapping(value = "/rest/documents/emendamento/activate/{idEme}/{idCentro}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult activateEmendamento(@PathVariable(value = "idEme") Long emeId, @PathVariable(value = "idCentro") Long centroId, HttpServletRequest request, HttpServletResponse response, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        //Verifico la "sessione" in EmendamentoSession.
        //Se ho già una sessione aperta per lo stesso emendamentoId e lo stesso centroId, la uso.
        //Se è già stata chiusa (ho il parere e ho già allineato le modifiche), ritorno errore.
        //Se non ho la riga in DB, la creo e mi attivo nella sessione rest il mio identificativo.
        //Long emeSessionId = 0L;

        //response.setHeader("cache-Control","no-cache,no-store,must-revalidate");
        //response.setHeader("Pragma","no-cache");
        //response.setHeader("Expires","0");

        request.getSession().removeAttribute("EME_SESSION_ID");
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        try {
            Long emeSessionId = docService.getEmendamentoSessionId(user, emeId, centroId);
            if (emeSessionId > 0) {
                request.getSession().setAttribute("EME_SESSION_ID", emeSessionId);
                return new PostResult("OK");
            } else {
                return new PostResult("ERROR");
            }
        } catch (AxmrGenericException ex) {
            log.error(ex.getMessage(), ex);
            return new PostResult("ERROR");
        }
    }


    /**
     *
     */
    @RequestMapping(value = "/rest/documents/emendamento/approve/{idEme}/{idCentro}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult approveEmendamento(@PathVariable(value = "idEme") Long emeId, @PathVariable(value = "idCentro") Long centroId, HttpServletRequest request, HttpServletResponse response, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        //Verifico la "sessione" in EmendamentoSession.
        //Se ho già una sessione aperta per lo stesso emendamentoId e lo stesso centroId, la uso.
        //Se è già stata chiusa (ho il parere e ho già allineato le modifiche), ritorno errore.


        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        try {
            Long emeSessionId = docService.getEmendamentoSessionId(user, emeId, centroId);

            if (emeSessionId > 0) {
                EmendamentoSession dataEme = docService.getActiveEmeSession(emeSessionId);
                if (dataEme.getEndDt() == null) {
                    List dataChange = docService.approveEmendamentoChanges(emeSessionId, user);

                    return new PostResult("OK approvato");
                } else {
                    return new PostResult("ERROR EME GIA CHIUSO");
                }
            } else {
                return new PostResult("ERROR");
            }
        } catch (AxmrGenericException ex) {
            log.error(ex.getMessage(), ex);
            return new PostResult(ex);
        }
    }


    /**
     *
     */
    @RequestMapping(value = "/rest/documents/emendamento/reject/{idEme}/{idCentro}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult rejectEmendamento(@PathVariable(value = "idEme") Long emeId, @PathVariable(value = "idCentro") Long centroId, HttpServletRequest request, HttpServletResponse response, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        //Verifico la "sessione" in EmendamentoSession.
        //Se ho già una sessione aperta per lo stesso emendamentoId e lo stesso centroId, la uso.
        //Se è già stata chiusa (ho il parere e ho già allineato le modifiche), ritorno errore.


        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        try {
            Long emeSessionId = docService.getEmendamentoSessionId(user, emeId, centroId);

            if (emeSessionId > 0) {
                EmendamentoSession dataEme = docService.getActiveEmeSession(emeSessionId);
                if (dataEme.getEndDt() == null) {
                    List dataChange = docService.rejectEmendamentoChanges(emeSessionId);

                    return new PostResult("OK rifiutato");
                } else {
                    return new PostResult("ERROR EME GIA CHIUSO");
                }
            } else {
                return new PostResult("ERROR");
            }
        } catch (AxmrGenericException ex) {
            log.error(ex.getMessage(), ex);
            return new PostResult(ex);
        }
    }


    /**
     *
     */
    @RequestMapping(value = "/rest/documents/emendamento/deactivate", method = RequestMethod.GET)
    public @ResponseBody
    PostResult deactivateEmendamento(HttpServletRequest request, HttpServletResponse response, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {

        //response.setHeader("cache-Control","no-cache,no-store,must-revalidate");
        //response.setHeader("Pragma","no-cache");
        //response.setHeader("Expires","0");

        //request.getSession().removeAttribute("EME_SESSION_ID");
        request.getSession().invalidate();
        //request.getSession().setAttribute("EME_SESSION_ID", null );
        return new PostResult("OK disattivato");
    }

    /**
     * Salva l'elemento
     * @param docTypeS
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     */
    @RequestMapping(value = "/rest/documents/save/{docTypeId}", method = RequestMethod.POST)
    public @ResponseBody
    PostResult saveNewDoc(@PathVariable(value = "docTypeId") String docTypeS, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        Long docType = docService.getTypeIdByNameOrId(docTypeS);
        ElementType elType = docService.getDocDefinition(docType);

        return saveNewDoc(request, elType);
    }

    /**
     * Salva l'elemento
     * @param docTypeS
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     */
    @RequestMapping(value = "/rest/documents/saveEme/{docTypeId}", method = RequestMethod.POST)
    public @ResponseBody
    PostResult saveNewEme(@PathVariable(value = "docTypeId") String docTypeS, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        Long docType = docService.getTypeIdByNameOrId(docTypeS);
        ElementType elType = docService.getDocDefinition(docType);

        return saveNewEme(null, request, elType);
    }
    @RequestMapping(value="/rest/documents/saveEmeAlpaca/{xmlForm}", method= RequestMethod.POST)
    public @ResponseBody
    PostResult saveNewEmeAlpaca(@PathVariable(value = "xmlForm") String xmlForm, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException, SAXException, ParserConfigurationException {
        Form form=docService.loadXmlForm(xmlForm);
        ElementType elType = docService.getDocDefinitionByName(form.getObject());

        return saveNewEme(xmlForm, request, elType);
    }

    protected PostResult saveNewDoc(HttpServletRequest request, ElementType elType) throws IOException {
        HashMap<String, String[]> data = new HashMap<String, String[]>();
        HashMap<String, String> dataSingle = new HashMap<String, String>();
        Enumeration paramNames = request.getParameterNames();
        boolean onlySingleValue = true;
        while (paramNames.hasMoreElements()) {
            String paramName = (String) paramNames.nextElement();
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Trovato: "+paramName+": "+request.getParameter(paramName));
            String[] values = request.getParameterValues(paramName);
            String paramNameMultiple = paramName.replaceAll("\\[\\]", "");
            if (values.length > 1) {
                onlySingleValue = false;
            } else {
                dataSingle.put(paramNameMultiple, request.getParameter(paramName));
            }
            data.put(paramNameMultiple, request.getParameterValues(paramName));
            /*
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Effettuo put di request:"+paramName+" - "+request.getParameter(paramName));
            String[] values = request.getParameterValues(paramName);
            data.put(paramName,values[values.length-1]);
            */
        }
        Element parent = null;
        if (data.containsKey("parentId") && data.get("parentId") != null) {
            parent = docService.getElement(Long.parseLong((String) dataSingle.get("parentId")));
            data.remove("parentId");
        }
        byte[] file = null;
        String fileName = null;
        Long fileSize = null;
        if (elType.isHasFileAttached() && request instanceof MultipartHttpServletRequest) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Sono qui!!!!! - MultipartHttpServletRequest - ");
            MultipartFile mfile = ((MultipartHttpServletRequest) request).getFile("file");
            file = mfile.getBytes();
            fileName = mfile.getOriginalFilename();
            fileSize = mfile.getSize();
        }
        String version = "";
        if (request.getParameter("version") != null) {
            version = request.getParameter("version");
            if (version.equals("auto")) {
                version = "1";
            }
        }
        String date = "";
        if (request.getParameter("data") != null) date = request.getParameter("data");
        String note = "";
        if (request.getParameter("note") != null) note = request.getParameter("note");
        String autore = "";
        if (request.getParameter("autore") != null) autore = request.getParameter("autore");
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        try {
            Element el = null;
            if (onlySingleValue) {
                el = docService.saveElement(user, elType, dataSingle, file, fileName, fileSize, version, date, note, autore, parent);
            } else {
                el = docService.saveElementArray(user, elType, data, file, fileName, fileSize, version, date, note, autore, parent);
            }
            elementIdxUpdate(el, true);
            /*
            if (isb.isActive()){
                isb.doInternalAsyncRequest("/rest/elk/allIndexsById/"+el.getId());
            }
            */
            PostResult res = new PostResult("OK");
            res.setRet(el.getId());
            res.setRedirect(ControllerHandler.getBaseUrl(request) + "/app/documents/detail/" + el.getId());
            return res;
        } catch (RestException e) {
            log.error(e.getMessage(), e);
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            res.setErrorCode(e.getCode());
            return res;
        }
    }

    protected PostResult saveNewEme(String xmlForm, HttpServletRequest request, ElementType elType) throws IOException {
        HashMap<String, String[]> data = new HashMap<String, String[]>();
        HashMap<String, String> dataSingle = new HashMap<String, String>();
        Enumeration paramNames = request.getParameterNames();
        boolean onlySingleValue = true;
        while (paramNames.hasMoreElements()) {
            String paramName = (String) paramNames.nextElement();
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Trovato: "+paramName+": "+request.getParameter(paramName));
            String[] values = request.getParameterValues(paramName);
            String paramNameMultiple = paramName.replaceAll("\\[\\]", "");
            if (values.length > 1) {
                onlySingleValue = false;
            } else {
                dataSingle.put(paramNameMultiple, request.getParameter(paramName));
            }
            data.put(paramNameMultiple, request.getParameterValues(paramName));
            /*
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Effettuo put di request:"+paramName+" - "+request.getParameter(paramName));
            String[] values = request.getParameterValues(paramName);
            data.put(paramName,values[values.length-1]);
            */
        }
        Element parent = null;
        if (data.containsKey("parentId") && data.get("parentId") != null) {
            parent = docService.getElement(Long.parseLong((String) dataSingle.get("parentId")));
            data.remove("parentId");
        }
        byte[] file = null;
        String fileName = null;
        Long fileSize = null;
        if (elType.isHasFileAttached() && request instanceof MultipartHttpServletRequest) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Sono qui!!!!! - MultipartHttpServletRequest - ");
            MultipartFile mfile = ((MultipartHttpServletRequest) request).getFile("file");
            file = mfile.getBytes();
            fileName = mfile.getOriginalFilename();
            fileSize = mfile.getSize();
        }
        String version = "";
        if (request.getParameter("version") != null) {
            version = request.getParameter("version");
            if (version.equals("auto")) {
                version = "1";
            }
        }
        String date = "";
        if (request.getParameter("data") != null) date = request.getParameter("data");
        String note = "";
        if (request.getParameter("note") != null) note = request.getParameter("note");
        String autore = "";
        if (request.getParameter("autore") != null) autore = request.getParameter("autore");
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        try {
            Element el = null;
            CheckResult result;
            if (onlySingleValue) {
                if (xmlForm != null && !xmlForm.isEmpty()){
                    result=docService.xmlChecks(user, request, xmlForm, dataSingle, el);
                    if (!result.isPassed()){
                        PostResult res=new PostResult("ERROR");
                        res.setRet(result);
                        return res;
                    }
                    dataSingle=docService.fixParametersSingle(user, request, xmlForm, dataSingle, el);
                }
                el = docService.saveElement(user, elType, dataSingle, file, fileName, fileSize, version, date, note, autore, parent);
            } else {
                if (xmlForm != null && !xmlForm.isEmpty()){
                    result=docService.xmlChecks(user, request, xmlForm, data, el);
                    if (!result.isPassed()){
                        PostResult res=new PostResult("ERROR");
                        res.setRet(result);
                        return res;
                    }
                    data=docService.fixParameters(user, request, xmlForm, data, el);
                }
                el = docService.saveElementArray(user, elType, data, file, fileName, fileSize, version, date, note, autore, parent);
            }
            elementIdxUpdate(el, true);
            /*
            if (isb.isActive()){
                isb.doInternalAsyncRequest("/rest/elk/allIndexsById/"+el.getId());
            }
            */
            PostResult res = new PostResult("OK");
            res.setRet(el.getId());
            res.setRedirect(ControllerHandler.getBaseUrl(request) + "/app/documents/detail/" + el.getId());
            return res;
        } catch (Exception e) {
            log.error(e.getMessage(), e);
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            if (e instanceof RestException){
                res.setErrorCode(((RestException)e).getCode());
            }else{
                res.setErrorCode(503);
            }
            return res;
        }
    }

    @RequestMapping(value = "/rest/documents/updateFile/{elementId}", method = RequestMethod.POST)
    public @ResponseBody
    PostResult updateFile(@PathVariable(value = "elementId") Long elementId, HttpServletRequest request) {
        PostResult res = new PostResult("OK");
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        String filename = null;
        String rev = null;
        String author = null;
        if (request.getParameter("filename") != null) {
            filename = request.getParameter("filename");
        }
        if (request.getParameter("version") != null) {
            rev = request.getParameter("version");
        }
        if (request.getParameter("author") != null) {
            author = request.getParameter("author");
        }
        try {
            docService.updateFile(user, elementId, filename, rev, author);
        } catch (AxmrGenericException ex) {
            return new PostResult(new RestException(ex.getMessage(), 2));
        }
        return res;
    }


    @RequestMapping(value = "/rest/documents/saveByTypeName/{docTypeIdString}", method = RequestMethod.POST)
    public @ResponseBody
    PostResult saveNewDocString(@PathVariable(value = "docTypeIdString") String docTypeIdString, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        ElementType elType = docService.getDocDefinitionByName(docTypeIdString);
        return saveNewDoc(request, elType);
    }


    @RequestMapping(value = "/rest/documents/getDummy/{docTypeId}", method = RequestMethod.GET)
    public @ResponseBody
    ElementJSON getDummy(@PathVariable(value = "docTypeId") Long docType, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"getDummy");
        ElementType elType = docService.getDocDefinition(docType);
        HashMap<String, Object> data = new HashMap<String, Object>();
        Enumeration paramNames = request.getParameterNames();
        while (paramNames.hasMoreElements()) {
            String paramName = (String) paramNames.nextElement();
            data.put(paramName, request.getParameter(paramName));
        }
        Element parent = null;
        if (data.containsKey("parentId") && data.get("parentId") != null) {
            parent = docService.getElement(Long.parseLong((String) data.get("parentId")));
            data.remove("parentId");
        }
        Element example= null;
        try {
            example = elType.getDummy();
        } catch (AxmrGenericException e) {
            log.error(e.getMessage(), e);
            return null;
        }
        if (parent != null) example.setParent(parent);

        ElementJSON json = new ElementJSON(example, user, "single");
        return json;

    }


    /**
     * Restituisce gli elementi in formato Json delle tipologie passate nel parametro get ids (comma-separated)
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     */
    @RequestMapping(value = "/rest/documents/getElementsByType", method = RequestMethod.GET)
    public @ResponseBody
    List<ElementJSON> getJSON(HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        List<String> typeIds = new LinkedList<String>();
        String[] ids = request.getParameter("ids").split(",");
        typeIds = Arrays.asList(ids);
        List<Element> els = docService.getElementsByTypes(user, typeIds);
        List<ElementJSON> elsRet = new LinkedList<ElementJSON>();
        for (Element el : els) {
            ElementJSON json = new ElementJSON(el, user, "complete");
            elsRet.add(json);
        }
        return elsRet;
    }

    /**
     * Restituisce la lista degli elementi(json) collegabili al campo idField
     * @param idField
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     */
    @RequestMapping(value = "/rest/documents/getLinkableElements/{idField}", method = RequestMethod.GET)
    public @ResponseBody
    List<ElementJSON> getLinkableElements(@PathVariable(value = "idField") Long idField, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        String term = request.getParameter("term");
        Element parent = null;
        if (request.getParameter("parent") != null && !request.getParameter("parent").isEmpty()) {
            parent = docService.getElement(Long.parseLong(request.getParameter("parent")));
        }
        List<Element> els = docService.getLinkableElements(user, idField, term, parent);
        List<ElementJSON> elsRet = new LinkedList<ElementJSON>();
        for (Element el : els) {
            ElementJSON json = new ElementJSON(el, user, "single");
            elsRet.add(json);
        }
        return elsRet;
    }


    @RequestMapping(value = "/rest/documents/searchByExample/{docTypeId}", method = RequestMethod.POST)
    public @ResponseBody
    List<ElementJSON> searchByExample(@PathVariable(value = "docTypeId") String docTypeS, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException, AxmrGenericException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Long docType = docService.getTypeIdByNameOrId(docTypeS);
        //ElementType elType=docService.getDocDefinition(docType);
        HashMap<String, Object> data = new HashMap<String, Object>();
        Enumeration paramNames = request.getParameterNames();
        while (paramNames.hasMoreElements()) {
            String paramName = (String) paramNames.nextElement();
            data.put(paramName, request.getParameter(paramName));
        }
        String parent = null;
        if (data.containsKey("parentId") && data.get("parentId") != null) {
            parent = (String) data.get("parentId");
            data.remove("parentId");
        }


        List<Element> els = docService.searchByExample(user, parent, docType, data);
        List<ElementJSON> elsRet = new LinkedList<ElementJSON>();
        for (Element el : els) {
            ElementJSON json = new ElementJSON(el, user, "single");
            elsRet.add(json);
        }
        return elsRet;
    }


    /**
     * Restituisce l'elemento objId
     * @param objId
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     */
    @RequestMapping(value = "/rest/documents/getElement/{objId}", method = RequestMethod.GET)
    public @ResponseBody
    Element get(@PathVariable(value = "objId") Long objId, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        return docService.getElement(objId);
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
    @RequestMapping(value = "/rest/documents/getElementJSON/{objId}", method = RequestMethod.GET)
    public @ResponseBody
    ElementJSON getJSON(@PathVariable(value = "objId") Long objId, @RequestParam(value = "mode", required = false) String option, @RequestParam(value = "level", required = false) Integer level, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if (option == null) option = "complete-without-parent";
        if (level == null) level = 1;
        if (docService.getElement(objId).isDeleted()) {
            throw new DocumentException("Elemento non più disponibile");
        }
        ElementJSON json = new ElementJSON(docService.getElement(objId), user, option, level);
        return json;
    }

    /**
     * Elimina l'elemento
     * @param elId
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     */
    @RequestMapping(value = "/rest/documents/delete/{elId}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult deleteElement(@PathVariable(value = "elId") Long elId, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        PostResult res = new PostResult("OK");
        try {
            Element el = docService.getElement(elId);
            docService.deleteElement(user, el);
            elementIdxUpdate(el, false);
            res.setRedirect(ControllerHandler.getBaseUrl(request) + "/app/documents");
        } catch (RestException e) {
            res.setResult("ERROR");
            res.setErrorMessage(e.getMessage());
        }
        return res;
    }

    /**
     * Aggiunge un commento
     * @param docId
     * @param request
     * @return
     */
    @RequestMapping(value = "/rest/documents/{docId}/addComment", method = RequestMethod.POST)
    public @ResponseBody
    PostResult addComment(@PathVariable(value = "docId") Long docId, HttpServletRequest request) {
        Element el = docService.getElement(docId);
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if (!el.getUserPolicy(user).isCanAddComment()) {
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage("Operazione non permessa");
            return res;
        }
        String comment = request.getParameter("comment");
        try {
            docService.addComment(el, comment, user);
        } catch (RestException e) {
            return new PostResult(e);
        }
        return new PostResult("OK");
    }

    /**
     * Elimina il commento
     * @param docId
     * @param commentId
     * @param request
     * @return
     */
    @RequestMapping(value = "/rest/documents/{docId}/deleteComment/{commentId}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult deleteComment(@PathVariable(value = "docId") Long docId, @PathVariable(value = "commentId") Long commentId, HttpServletRequest request) {
        Element el = docService.getElement(docId);
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if (!el.getUserPolicy(user).isCanModerate()) {
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage("Operazione non permessa");
            return res;
        }
        try {
            docService.deleteComment(user, el, commentId);
        } catch (RestException e) {
            return new PostResult(e);
        }
        return new PostResult("OK");
    }

    @RequestMapping(value = "/rest/documents/{typeId}/createFormSpec", method = RequestMethod.GET)
    public @ResponseBody
    FormSpecification getFormSpec(@PathVariable(value = "typeId") String typeId, HttpServletRequest request, HttpServletResponse response) {
        FormSpecification fspec = new FormSpecification();
        fspec.setTypeId(typeId);
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        ElementType type = docService.getType(docService.getTypeIdByNameOrId(typeId));
        Properties adHocProps = new Properties();
        fspec.setElementPolicy(type.getUserPolicy(user));
        try {
            FileInputStream fis = new FileInputStream(messagesFolder + "/messages/" + "it_IT.properties");
            adHocProps.load(fis);
            fis.close();
        } catch (IOException e) {
            log.error(e.getMessage(), e);
        }
        fspec.setHasFile(type.isHasFileAttached());
        fspec.setFileInfo(!type.isNoFileinfo());
        for (ElementTypeAssociatedTemplate at : type.getAssociatedTemplates()) {
            if (at.isEnabled() && at.getUserPolicy(user, type).isCanCreate()) {
                for (MetadataField field : at.getMetadataTemplate().getFields()) {
                    fspec.addField(field, adHocProps, docService, user);
                }
            }
        }
        return fspec;
    }

    @RequestMapping(value = "/rest/documents/{typeId}/loadFormSpecAssocTemplates", method = RequestMethod.GET)
    public @ResponseBody
    FormSpecification getFormSpecAssocTemplates(@PathVariable(value = "typeId") String typeId, HttpServletRequest request, HttpServletResponse response) {
        FormSpecification fspec = new FormSpecification();
        fspec.setTypeId(typeId);
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        ElementType type = docService.getType(docService.getTypeIdByNameOrId(typeId));
        Properties adHocProps = new Properties();
        fspec.setElementPolicy(type.getUserPolicy(user));
        try {

            FileInputStream fis = new FileInputStream(messagesFolder + "/messages/" + "it_IT.properties");
            adHocProps.load(fis);
            fis.close();

        } catch (IOException e) {
            log.error(e.getMessage(), e);
        }
        for (ElementTypeAssociatedTemplate at : type.getAssociatedTemplates()) {
            for (MetadataField field : at.getMetadataTemplate().getFields()) {
                fspec.addField(field, adHocProps, docService, user);
            }
        }
        return fspec;
    }

    /*
    @RequestMapping(value="/rest/documents/{templateName}/createFormSpecTemplate", method = RequestMethod.GET)
    public @ResponseBody
    FormSpecification getFormSpecTemplate(@PathVariable(value = "templateName") String templateName, HttpServletRequest request, HttpServletResponse response) {
        FormSpecification fspec=new FormSpecification();
        //fspec.setTypeId(typeId);
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        //ElementType type = docService.getType(docService.getTypeIdByNameOrId(typeId));
        Properties adHocProps=new Properties();
        //fspec.setElementPolicy(type.getUserPolicy(user));
        try {
            adHocProps.load(new FileInputStream(messagesFolder + "/messages/" + "it_IT.properties"));
        } catch (IOException e) {
            log.error(e.getMessage(),e);
        }
        //getDocService()
        adminservice.getTemplateByName(templateName);
        for (ElementTypeAssociatedTemplate at:type.getAssociatedTemplates()){
            if (at.isEnabled() && at.getUserPolicy(user, type).isCanCreate()){
                for (MetadataField field:at.getMetadataTemplate().getFields()){
                    fspec.addField(field, adHocProps, docService, user);
                }
            }
        }
        return fspec;
    }
    */

    @Autowired
    @Qualifier("messagesFolder")
    protected String messagesFolder;

    @RequestMapping(value = "/rest/documents/messages", method = RequestMethod.GET)
    public @ResponseBody
    PostResult getLocalizedMessages(HttpServletRequest request) {
        Properties adHocProps = new Properties();

        Locale locale = ControllerHandler.getLocale(request);
        try {
            PostResult res = new PostResult("OK");


            FileInputStream fis = new FileInputStream(messagesFolder + "/messages/" + ControllerHandler.getLocale(request).getLanguage() + "_" + ControllerHandler.getLocale(request).getCountry() + ".properties");
            adHocProps.load(fis);
            fis.close();

            Set<String> propEnum = adHocProps.stringPropertyNames();
            Map<String, Object> properties = new HashMap<String, Object>();
            for (String key : propEnum) {
                properties.put(key, adHocProps.getProperty(key));
                properties.put(key.replace(".", "_"), adHocProps.getProperty(key));
            }
            res.setResultMap(properties);
            return res;
        } catch (IOException e) {
            return new PostResult(new RestException(e.getMessage(), 1));
        }
    }

    @RequestMapping(value = "/rest/documents/messages/{locale}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult getMessages(@PathVariable(value = "locale") String locale, HttpServletRequest request) {
        Properties adHocProps = new Properties();
        try {
            PostResult res = new PostResult("OK");


            FileInputStream fis = new FileInputStream(messagesFolder + "/messages/" + locale.toLowerCase() + "_" + locale.toUpperCase() + ".properties");
            adHocProps.load(fis);
            fis.close();

            Set<String> propEnum = adHocProps.stringPropertyNames();
            Map<String, Object> properties = new HashMap<String, Object>();
            for (String key : propEnum) {
                properties.put(key, adHocProps.getProperty(key));
            }
            res.setResultMap(properties);
            return res;
        } catch (IOException e) {
            return new PostResult(new RestException(e.getMessage(), 1));
        }
    }

    @RequestMapping(value = "/rest/documents/{elementId}/createFormSpecByElementId", method = RequestMethod.GET)
    public @ResponseBody
    FormSpecification getFormSpecByElementId(@PathVariable(value = "elementId") Long elementId, HttpServletRequest request, HttpServletResponse response) {
        FormSpecification fspec = new FormSpecification();
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        Element el = docService.getElement(elementId);
        fspec.setTypeId(el.getType().getTypeId());
        fspec.setId(el.getId());
        fspec.setElementPolicy(el.getUserPolicy(user));
        fspec.setHasFile(el.getType().isHasFileAttached());
        fspec.setFileInfo(!el.getType().isNoFileinfo());

        Properties adHocProps = new Properties();
        try {
            FileInputStream fis = new FileInputStream(messagesFolder + "/messages/" + ControllerHandler.getLocale(request).getLanguage() + "_" + ControllerHandler.getLocale(request).getCountry() + ".properties");
            adHocProps.load(fis);
            fis.close();
        } catch (IOException e) {
            log.error(e.getMessage(), e);
        }
        Iterator<ElementTemplate> it = el.getElementTemplates().iterator();
        while (it.hasNext()) {
            ElementTemplate et = it.next();
            fspec.addTemplatePolicy(et.getMetadataTemplate().getName(), et.getUserPolicy(user, el));
        }
        for (MetadataTemplate at : el.getTemplates()) {
            for (MetadataField field : at.getFields()) {
                fspec.addField(field, adHocProps, docService, user, el);

            }
        }
        return fspec;
    }

    /**
     * Restituisce tutti i commenti dell'elemento id
     * @param id
     * @param request
     * @param response
     * @return
     */
    @RequestMapping(value = "/rest/documents/{id}/getComments", method = RequestMethod.GET)
    public @ResponseBody
    List<Comment> getComments(@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response) {
        Element t = docService.getElement(id);
        if (t.getComments() == null) return null;
        return (List<Comment>) t.getComments();
    }


    /**
     * Restituisce gli elementi associati al gruppo
     * @param id
     * @param request
     * @param response
     * @return
     */
    @RequestMapping(value = "/rest/documents/{id}/getGrouppedElements", method = RequestMethod.GET)
    public @ResponseBody
    String getGrouppedElements(@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setCharacterEncoding("UTF-8");
        response.addHeader("Content-Type", "application/json; charset=utf-8");

        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        List<Element> t = docService.getGrouppedElements(id, user);
        String result = "[";
        for (Element el : t) {
            result += el.getElementCoreJsonToString(user) + ", ";
        }
        result = result.replaceAll(", $", "");
        result += "]";
        result = StringEscapeUtils.escapeHtml(result);
        result = result.replace("&quot;", "\"");
        return result;
    }

    @RequestMapping(value = "/rest/loggedUserDetails", method = RequestMethod.GET)
    public @ResponseBody
    IUser getLoggedUserDetils() throws IOException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        return user;
    }

    @RequestMapping(value = "/rest/documents/creatableRootElementTypes", method = RequestMethod.GET)
    public @ResponseBody
    List<String> getCreatableRootElementTypes() {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        List<ElementType> rootEls = docService.getCreatableRootElementTypes(user);
        List<String> ret = new LinkedList<String>();
        for (ElementType et : rootEls) {
            ret.add(et.getTypeId());
        }
        return ret;
    }

    @RequestMapping(value = "/rest/documents/availablesCalendars", method = RequestMethod.GET)
    public @ResponseBody
    List<CalendarEntity> getAvailablesCalendars() {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        return docService.getAvailablesCalendars(user);
    }

    @RequestMapping(value = "/rest/documents/{elementId}/creatableElementTypes", method = RequestMethod.GET)
    public @ResponseBody
    List<String> getCreatableElementTypes(@PathVariable(value = "elementId") Long elementId) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Element el = docService.getElement(elementId);
        List<ElementType> cEls = docService.getCreatableElementTypes(el, user);
        List<String> ret = new LinkedList<String>();
        for (ElementType et : cEls) {
            ret.add(et.getTypeId());
        }
        return ret;
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
     * @param response
     * @return
     * @throws IOException
     */
    @RequestMapping(value = "/rest/documents/{id}/attach", method = RequestMethod.POST)
    public @ResponseBody
    PostResult attach(@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response) throws IOException {
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
        if (request.getParameter("data") != null) date = request.getParameter("data");
        String note = "";
        if (request.getParameter("note") != null) note = request.getParameter("note");
        String autore = "";
        if (request.getParameter("autore") != null) autore = request.getParameter("autore");
        if (request instanceof MultipartHttpServletRequest) {
            MultipartFile mfile = ((MultipartHttpServletRequest) request).getFile("file");
            file = mfile.getBytes();
            fileName = mfile.getOriginalFilename();
            fileSize = mfile.getSize();
        }
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        try {
            docService.attachFile(user, el, file, fileName, fileSize, version, date, note, autore, "UPDATE");
        } catch (RestException e) {
            log.error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            res.setErrorCode(e.getCode());
            return res;
        }
        PostResult res = new PostResult("OK");
        res.setRedirect(ControllerHandler.getBaseUrl(request) + "/app/documents/detail/" + el.getId());
        return res;
    }

    /**
     * Aggiorna l'elemento elId
     *
     * POST parameters:
     * - [templateName]_[fieldName] (String) (+)
     *
     * @param elId
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     */
    @RequestMapping(value = "/rest/documents/update/{elId}", method = RequestMethod.POST)
    public @ResponseBody
    PostResult updateMetadata(@PathVariable(value = "elId") Long elId, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        HashMap<String, String[]> data = new HashMap<String, String[]>();
        HashMap<String, String> dataSingle = new HashMap<String, String>();
        Enumeration paramNames = request.getParameterNames();
        try {
            boolean onlySingleValue = true;
            while (paramNames.hasMoreElements()) {
                String paramName = (String) paramNames.nextElement();
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Trovato: "+paramName+": "+request.getParameter(paramName));
                String[] values = request.getParameterValues(paramName);
                String paramNameMultiple = paramName.replaceAll("\\[\\]", "");
                if (values.length > 1) {
                    onlySingleValue = false;

                } else {
                    dataSingle.put(paramNameMultiple, request.getParameter(paramName));
                }
                data.put(paramNameMultiple, request.getParameterValues(paramName));
            }
            if (onlySingleValue) {
                docService.updateElementMetaData(user, elId, dataSingle);
            } else {
                docService.updateElementMetaDataArray(user, elId, data);
            }
        } catch (RestException e) {
            log.error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            return res;
        }
        elementIdxUpdate(docService.getElement(elId), true);

        //res.setRedirect(ControllerHandler.getBaseUrl(request)+"/app/documents/detail/"+elId);
        PostResult res = new PostResult("OK");
        res.setRet(elId);
        //Redirect spento, nel caso valutare se impostare un valore nella request per lanciare il redirect
        //res.setRedirect(ControllerHandler.getBaseUrl(request)+"/app/documents/detail/"+elId); //Meglio fare il redirect, in modo da prendere il nuovo stato di work-flow in ogni caso?
        return res;
    }
    /**
     * Termina il processo processKey per l'elemento elId
     *
     *
     * @param elId
     * @param processDefinition
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     */
    @RequestMapping(value="/rest/documents/terminateProcess/{elId}/{processDefinition}", method= RequestMethod.POST)
    public @ResponseBody
    PostResult terminateProcess(@PathVariable(value = "elId") Long elId,@PathVariable(value = "processDefinition") String processDefinition, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        try {

            Element element=docService.getElement(elId);
            List<ProcessInstance> activeProcesses;
            activeProcesses = docService.getActiveProcesses(element);
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"CERCO IL WF "+processDefinition+": ASSOCIATO ALL'elemento= "+elId);
            for(ProcessInstance process:activeProcesses){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"HO TROVATO = "+process.getProcessDefinitionId());
                if(process.getProcessDefinitionId().startsWith(processDefinition+":")){
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"PROVO A TERMINARE = "+process.getProcessDefinitionId());
                    docService.terminateProcess(user ,process.getProcessInstanceId());
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"HO TERMINATO = "+process.getProcessDefinitionId());
                }
            }

        } catch (RestException e) {
            log.error(e.getMessage(),e);  //To change body of catch statement use File | Settings | File Templates.
            PostResult res=new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            return res;
        } catch (AxmrGenericException e) {
            log.error(e.getMessage(),e);  //To change body of catch statement use File | Settings | File Templates.
            PostResult res=new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            return res;
        }
        elementIdxUpdate(docService.getElement(elId), true);

        //res.setRedirect(ControllerHandler.getBaseUrl(request)+"/app/documents/detail/"+elId);
        PostResult res=new PostResult("OK");
        res.setRet(elId);
        //Redirect spento, nel caso valutare se impostare un valore nella request per lanciare il redirect
        //res.setRedirect(ControllerHandler.getBaseUrl(request)+"/app/documents/detail/"+elId); //Meglio fare il redirect, in modo da prendere il nuovo stato di work-flow in ogni caso?
        return res;
    }
    /**
     * Termina il processo processKey per l'elemento elId
     *
     *
     * @param elId
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     */
    @RequestMapping(value="/rest/documents/terminateAllProcesses/{elId}", method= RequestMethod.POST)
    public @ResponseBody
    PostResult terminateProcess(@PathVariable(value = "elId") Long elId, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        try {

            Element element=docService.getElement(elId);
            List<ProcessInstance> activeProcesses;
            activeProcesses = docService.getActiveProcesses(element);
            //it.cineca.siss.axmr3.log.Log.debug(getClass(),"CERCO IL WF "+processDefinition+": ASSOCIATO ALL'elemento= "+elId);
            for(ProcessInstance process:activeProcesses){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"HO TROVATO = "+process.getProcessDefinitionId());
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"PROVO A TERMINARE = "+process.getProcessDefinitionId());
                docService.terminateProcess(user ,process.getProcessInstanceId());
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"HO TERMINATO = "+process.getProcessDefinitionId());
            }

        } catch (RestException e) {
            log.error(e.getMessage(),e);  //To change body of catch statement use File | Settings | File Templates.
            PostResult res=new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            return res;
        } catch (AxmrGenericException e) {
            log.error(e.getMessage(),e);  //To change body of catch statement use File | Settings | File Templates.
            PostResult res=new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            return res;
        }
        elementIdxUpdate(docService.getElement(elId), true);

        //res.setRedirect(ControllerHandler.getBaseUrl(request)+"/app/documents/detail/"+elId);
        PostResult res=new PostResult("OK");
        res.setRet(elId);
        //Redirect spento, nel caso valutare se impostare un valore nella request per lanciare il redirect
        //res.setRedirect(ControllerHandler.getBaseUrl(request)+"/app/documents/detail/"+elId); //Meglio fare il redirect, in modo da prendere il nuovo stato di work-flow in ogni caso?
        return res;
    }
    /**
     * Modifica i permessi per il template
     *
     *
     * @param elId
     * @param templateName
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     */
    @RequestMapping(value="/rest/documents/changeTemplatePermissionToGroup/{elId}/{templateName}", method= RequestMethod.POST)
    public @ResponseBody
    PostResult changeTemplatePermissionToGroup(@PathVariable(value = "elId") Long elId,@PathVariable(value = "templateName") String templateName, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        try {
            String permissions=request.getParameter("permissions");
            String group=request.getParameter("group");
            docService.setTemplatePolicy(elId, templateName, permissions, true, group);

        } catch (RestException e) {
            log.error(e.getMessage(),e);  //To change body of catch statement use File | Settings | File Templates.
            PostResult res=new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            return res;
        } catch (AxmrGenericException e) {
            log.error(e.getMessage(),e);  //To change body of catch statement use File | Settings | File Templates.
            PostResult res=new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            return res;
        }
        elementIdxUpdate(docService.getElement(elId), true);

        //res.setRedirect(ControllerHandler.getBaseUrl(request)+"/app/documents/detail/"+elId);
        PostResult res=new PostResult("OK");
        res.setRet(elId);
        //Redirect spento, nel caso valutare se impostare un valore nella request per lanciare il redirect
        //res.setRedirect(ControllerHandler.getBaseUrl(request)+"/app/documents/detail/"+elId); //Meglio fare il redirect, in modo da prendere il nuovo stato di work-flow in ogni caso?
        return res;
    }

    /**
     * Aggiorna l'elemento elId in emendamento
     *
     * POST parameters:
     * - [templateName]_[fieldName] (String) (+)
     *
     * @param elId
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     */
    @RequestMapping(value = "/rest/documents/updateEme/{elId}", method = RequestMethod.POST)
    public @ResponseBody
    PostResult updateMetadataEme(@PathVariable(value = "elId") Long elId, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        return updateEmendamento(elId,null,request,model);
    }
    @RequestMapping(value="/rest/documents/updateEmeAlpaca/{xmlForm}/{elId}", method= RequestMethod.POST)
    public @ResponseBody
    PostResult updateMetadataEme(@PathVariable(value = "elId") Long elId, @PathVariable(value = "xmlForm") String xmlForm, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        return updateEmendamento(elId,xmlForm,request,model);
    }

    protected PostResult updateEmendamento(Long elId, String xmlForm, HttpServletRequest request, ModelMap model) throws IOException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        HashMap<String, String[]> data = new HashMap<String, String[]>();
        HashMap<String, String> dataSingle = new HashMap<String, String>();
        //Long emeId = (Long)request.getSession().getAttribute("EME_ID");
        //Long emeCentroId = (Long)request.getSession().getAttribute("EME_CENTRO_ID");
        Long emeSessionId = (Long) request.getSession().getAttribute("EME_SESSION_ID");
        Logger.getLogger(this.getClass()).debug("###########EMENDAMENTO SESSION ID RECUPERATO: "+emeSessionId);
        //////////////////
        Enumeration paramNames = request.getParameterNames();
        try {
            boolean onlySingleValue = true;
            while (paramNames.hasMoreElements()) {
                String paramName = (String) paramNames.nextElement();
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Trovato: "+paramName+": "+request.getParameter(paramName));
                String[] values = request.getParameterValues(paramName);
                String paramNameMultiple = paramName.replaceAll("\\[\\]", "");
                if (values.length > 1) {
                    onlySingleValue = false;

                } else {
                    dataSingle.put(paramNameMultiple, request.getParameter(paramName));
                }
                data.put(paramNameMultiple, request.getParameterValues(paramName));
            }
            CheckResult result;
            if (onlySingleValue) {
                if (xmlForm != null && !xmlForm.isEmpty()){
                    Element el=docService.getElement(elId);
                    result=docService.xmlChecks(user, request, xmlForm, dataSingle, el);
                    if (!result.isPassed()){
                        PostResult res=new PostResult("ERROR");
                        res.setRet(result);
                        return res;
                    }
                    dataSingle=docService.fixParametersSingle(user, request, xmlForm, dataSingle, el);
                }
                docService.updateElementMetaDataEme(user, elId, dataSingle, emeSessionId);
            } else {
                if (xmlForm != null && !xmlForm.isEmpty()) {
                    Element el = docService.getElement(elId);
                    result=docService.xmlChecks(user, request, xmlForm, data, el);
                    if (!result.isPassed()){
                        PostResult res=new PostResult("ERROR");
                        res.setRet(result);
                        return res;
                    }
                    data=docService.fixParameters(user, request, xmlForm, data, el);
                }
                docService.updateElementMetaDataArrayEme(user, elId, data, emeSessionId);
            }
        } catch (Exception e) {
            log.error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            return res;
        }
        elementIdxUpdate(docService.getElement(elId), true);

        //res.setRedirect(ControllerHandler.getBaseUrl(request)+"/app/documents/detail/"+elId);
        PostResult res = new PostResult("OK");
        res.setRet(elId);
        //Redirect spento, nel caso valutare se impostare un valore nella request per lanciare il redirect
        //res.setRedirect(ControllerHandler.getBaseUrl(request)+"/app/documents/detail/"+elId); //Meglio fare il redirect, in modo da prendere il nuovo stato di work-flow in ogni caso?
        return res;
    }


    @RequestMapping(value = "/rest/documents/updateField/{elId}", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult updateMetadataField(@PathVariable(value = "elId") Long elId, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        HashMap<String, String> data = new HashMap<String, String>();
        Enumeration paramNames = request.getParameterNames();
        try {
            if (request.getParameter("name") != null) {
                data.put(request.getParameter("name"), request.getParameter("value"));

            } else {
                while (paramNames.hasMoreElements()) {
                    String paramName = (String) paramNames.nextElement();
                    data.put(paramName, request.getParameter(paramName));
                }
                docService.updateElementMetaData(user, elId, data);
            }
            docService.updateElementMetaData(user, elId, data);
        } catch (RestException e) {
            log.error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            return res;
        }
        elementIdxUpdate(docService.getElement(elId), true);

        //res.setRedirect(ControllerHandler.getBaseUrl(request)+"/app/documents/detail/"+elId);
        PostResult res = new PostResult("OK");
        res.setRet(elId);
        return res;
    }

    @RequestMapping(value = "/rest/documents/updateGrid", method = RequestMethod.POST)
    public @ResponseBody
    PostResult updateGrid(HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        PostResult resOk = new PostResult("OK");
        LinkedList<Long> saved = new LinkedList<Long>();

        it.cineca.siss.axmr3.log.Log.debug(getClass(),"grid SAVE");
        Map<String, Object> grid = new Gson().fromJson(request.getParameter("grid"), Map.class);
        ArrayList<Object> rows = (ArrayList<Object>) grid.get("layout");
        Map<String, Object> elementsMap = (Map<String, Object>) grid.get("elements");
        Map<String, String> parents = (Map<String, String>) grid.get("folders");
        Map<String, String> coordinates = (Map<String, String>) grid.get("coordinates");
        Map<String, Object> additional = (Map<String, Object>) grid.get("additionals");
        Integer updatedElementsCount = 100;
        String x = coordinates.get("x");
        String y = coordinates.get("y");
        String rowField = coordinates.get("row");
        String colField = coordinates.get("col");
        HashMap<Integer, Element> linkX = new HashMap<Integer, Element>();
        HashMap<Integer, Element> linkY = new HashMap<Integer, Element>();
        Set<String> myElements = elementsMap.keySet();
        Map currElementMap;

        if (grid.get("updatedElementsCount") != null && !((String) grid.get("updatedElementsCount")).equals("")) {
            updatedElementsCount = Integer.parseInt((String) grid.get("updatedElementsCount"));
        }
        for (String guid : myElements) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"grid guid "+guid);
        }

        int rowIdx = 0;
        int colIdx = 0;
        for (Object row : rows) {
            rowIdx++;
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"grid row "+String.valueOf(rowIdx));
            colIdx = 0;
            try {
                ArrayList<Object> cols = (ArrayList<Object>) row;
                int colAddendum = 0;
                int rowAddendum = 0;
                for (Object cell : cols) {
                    colIdx++;
                   it.cineca.siss.axmr3.log.Log.debug(getClass(),"grid col "+String.valueOf(colIdx));
                    String uid = String.valueOf(cell);
                   it.cineca.siss.axmr3.log.Log.debug(getClass(),"grid cell "+String.valueOf(cell));

                    if (elementsMap.containsKey(uid)) {

                       it.cineca.siss.axmr3.log.Log.debug(getClass(),"grid in elements map ");
                        currElementMap = (Map) elementsMap.get(uid);
                        if (currElementMap.containsKey("id")) {

                           it.cineca.siss.axmr3.log.Log.debug(getClass(),"grid element has id: -"+currElementMap.get("id").toString()+"- ");
                            if (!currElementMap.get("id").toString().equals("") && Long.parseLong(currElementMap.get("id").toString()) > 0 && !saved.contains(Long.parseLong(currElementMap.get("id").toString()))) {
                                Long currId = Long.parseLong(currElementMap.get("id").toString());

                                Map<String, String> metadata = (Map<String, String>) currElementMap.get("metadata");
                                //TODO:se ci sono visioni che possono inserire righe o colonne ma non visualizzano tutte le righe/colonne possono ingenerarsi problemi
                                if (rowIdx == 1) {
                                    if (!metadata.containsKey(colField) || metadata.get(colField).equals("")) {
                                        metadata.put(colField, String.valueOf(colIdx));
                                        colAddendum++;
                                    } else if (colAddendum > 0) {
                                        metadata.put(colField, String.valueOf(colIdx));
                                    }
                                } else if (colIdx == 1) {
                                    if (!metadata.containsKey(rowField) || metadata.get(rowField).equals("")) {
                                        metadata.put(rowField, String.valueOf(rowIdx));
                                        rowAddendum++;
                                    } else if (rowAddendum > 0) {
                                        metadata.put(rowField, String.valueOf(rowIdx));
                                    }
                                }
                                Set<String> parameters = metadata.keySet();
                               it.cineca.siss.axmr3.log.Log.debug(getClass(),"grid beforeUpdate "+String.valueOf(currId));
                                if (currElementMap.get("updateCheck") != null && currElementMap.get("updateCheck").toString().equals("1"))
                                    docService.updateElementMetaData(user, currId, metadata);
                               /*
                               for(String paramName:parameters){
                                    docService.updateElementMetaData(user, currId, paramName, String.valueOf(metadata.get(paramName)));
                               }
                               */
                               it.cineca.siss.axmr3.log.Log.debug(getClass(),"grid beforeLink "+String.valueOf(currId));
                                if (rowIdx == 1) {
                                    Element currElement = docService.getElement(currId);
                                    linkX.put(colIdx, currElement);
                                } else if (colIdx == 1) {
                                    Element currElement = docService.getElement(currId);
                                    linkY.put(rowIdx, currElement);
                                } else {
                                    String currTp = linkX.get(colIdx).getId().toString();
                                    String currPrestazione = linkY.get(rowIdx).getId().toString();
                                    HashMap<String, String> sd = new HashMap<String, String>();
                                    sd.put(x, currTp);
                                    sd.put(y, currPrestazione);
                                   /*
                                   docService.updateElementMetaData(user, currId, x, currTp);
                                   docService.updateElementMetaData(user, currId, y, currPrestazione);
                                   */
                                    docService.updateElementMetaData(user, currId, sd);
                                }
                               it.cineca.siss.axmr3.log.Log.debug(getClass(),"grid afterUpdate&Link "+String.valueOf(currId));
                                saved.add(currId);
                            } else {
                                Map<String, String> metadata = (Map<String, String>) currElementMap.get("metadata");
                                if (rowIdx == 1) {
                                    if (!metadata.containsKey(colField) || metadata.get(colField).equals("")) {
                                        metadata.put(colField, String.valueOf(colIdx));
                                    }
                                } else if (colIdx == 1) {
                                    if (!metadata.containsKey(rowField) || metadata.get(rowField).equals("")) {
                                        metadata.put(rowField, String.valueOf(rowIdx));
                                    }
                                }
                                Map<String, String> typeMap = (Map) currElementMap.get("type");
                                Long docType = Long.parseLong(typeMap.get("id"));
                                ElementType elType = docService.getDocDefinition(docType);
                                HashMap<String, String> data = new HashMap<String, String>();

                                Set<String> parameters = metadata.keySet();
                                for (String paramName : parameters) {

                                    data.put(paramName, metadata.get(paramName));
                                }
                                if (colIdx > 1 && rowIdx > 1) {
                                    String currTp = linkX.get(colIdx).getId().toString();
                                    String currPrestazione = linkY.get(rowIdx).getId().toString();
                                    data.put(x, currTp);
                                    data.put(y, currPrestazione);
                                }

                                Element parent = docService.getElement(Long.parseLong(parents.get(docType.toString())));
                                if (data.containsKey("parentId") && data.get("parentId") != null) {
                                    data.remove("parentId");
                                }
                                byte[] file = null;
                                String fileName = null;
                                Long fileSize = null;
                                if (elType.isHasFileAttached() && request instanceof MultipartHttpServletRequest) {
                                   it.cineca.siss.axmr3.log.Log.debug(getClass(),"Sono qui!!!!! - MultipartHttpServletRequest - ");
                                    MultipartFile mfile = ((MultipartHttpServletRequest) request).getFile("file");
                                    file = mfile.getBytes();
                                    fileName = mfile.getOriginalFilename();
                                    fileSize = mfile.getSize();
                                }
                                String version = "";

                                String date = "";

                                String note = "";

                                String autore = "";


                                try {
                                   it.cineca.siss.axmr3.log.Log.debug(getClass(),"grid beforeSave ");
                                    Element el = docService.saveElement(user, elType, data, file, fileName, fileSize, version, date, note, autore, parent);
                                    Long currId = el.getId();
                                    resOk.getResultMap().put(uid, currId.toString());
                                   it.cineca.siss.axmr3.log.Log.debug(getClass(),"grid beforeLink "+String.valueOf(currId));
                                    if (rowIdx == 1) {
                                        Element currElement = docService.getElement(currId);
                                        linkX.put(colIdx, currElement);
                                    } else if (colIdx == 1) {
                                        Element currElement = docService.getElement(currId);
                                        linkY.put(rowIdx, currElement);
                                    }
                                   it.cineca.siss.axmr3.log.Log.debug(getClass(),"grid after Save&link "+String.valueOf(currId));
                                    saved.add(el.getId());
                                } catch (RestException e) {
                                    log.error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
                                    PostResult res = new PostResult("ERROR");
                                    res.setErrorMessage(e.getMessage());
                                    res.setErrorCode(e.getCode());
                                    return res;
                                }

                            }

                        }
                    }
                }
                if (updatedElementsCount > 50) {
                   it.cineca.siss.axmr3.log.Log.debug(getClass(),"committo in anticipo perche updatedElementsCount="+updatedElementsCount.toString());
                   docService.commitTXSessionAndKeepAlive(); //getAxmr3txManager().commitAndKeepAlive();
                }
            } catch (Exception ex) {
                log.error(ex.getMessage(), ex);  //To change body of catch statement use File | Settings | File Templates.
                PostResult res = new PostResult("ERROR");
                res.setErrorMessage(ex.getMessage());
                return res;
            }
        }
        try {
            Collection<Object> startingElements = elementsMap.values();
            for (Object currElement : startingElements) {
                Map examiningElement = (Map) currElement;
                if (examiningElement.containsKey("id") && !examiningElement.get("id").toString().equals("") && Long.parseLong(examiningElement.get("id").toString()) > 0 && !saved.contains(Long.parseLong(examiningElement.get("id").toString()))) {
                    //TODO: bisogna avere l'eliminazione anche a partire da un id in stringa
                    Element toBeDeleted = docService.getElement(Long.parseLong(examiningElement.get("id").toString()));
                    docService.deleteElement(user, toBeDeleted);
                }
            }
            if (additional != null && !additional.isEmpty())
                for (String currGuid : additional.keySet()) {
                    currElementMap = (Map) additional.get(currGuid);
                    if (currElementMap.containsKey("id") && !currElementMap.get("id").toString().equals("") && Long.parseLong(currElementMap.get("id").toString()) > 0 && !currElementMap.containsKey("deleted")) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"additional update "+currElementMap.get("id").toString());
                        Long currId = Long.parseLong(currElementMap.get("id").toString());

                        Map<String, String> metadata = (Map<String, String>) currElementMap.get("metadata");
                        //TODO:se ci sono visioni che possono inserire righe o colonne ma non visualizzano tutte le righe/colonne possono ingenerarsi problemi

                        Set<String> parameters = metadata.keySet();
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"grid additional beforeUpdate "+String.valueOf(currId));
                        if (currElementMap.get("updateCheck") != null && currElementMap.get("updateCheck").toString().equals("1"))
                            docService.updateElementMetaData(user, currId, metadata);
                               /*
                               for(String paramName:parameters){
                                    docService.updateElementMetaData(user, currId, paramName, String.valueOf(metadata.get(paramName)));
                               }
                               */


                    } else if (!currElementMap.containsKey("deleted")) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"additional create "+currGuid);
                        Map<String, String> metadata = (Map<String, String>) currElementMap.get("metadata");

                        Map<String, String> typeMap = (Map) currElementMap.get("type");
                        Long docType = Long.parseLong(typeMap.get("id"));
                        ElementType elType = docService.getDocDefinition(docType);
                        HashMap<String, String> data = new HashMap<String, String>();

                        Set<String> parameters = metadata.keySet();
                        for (String paramName : parameters) {

                            data.put(paramName, metadata.get(paramName));
                        }


                        Element parent = docService.getElement(Long.parseLong(currElementMap.get("parent").toString()));
                        if (data.containsKey("parentId") && data.get("parentId") != null) {
                            data.remove("parentId");
                        }
                        byte[] file = null;
                        String fileName = null;
                        Long fileSize = null;
                        if (elType.isHasFileAttached() && request instanceof MultipartHttpServletRequest) {
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"Sono qui!!!!! - MultipartHttpServletRequest - ");
                            MultipartFile mfile = ((MultipartHttpServletRequest) request).getFile("file");
                            file = mfile.getBytes();
                            fileName = mfile.getOriginalFilename();
                            fileSize = mfile.getSize();
                        }
                        String version = "";

                        String date = "";

                        String note = "";

                        String autore = "";


                        try {
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"grid additional beforeSave ");
                            Element el = docService.saveElement(user, elType, data, file, fileName, fileSize, version, date, note, autore, parent);
                            Long currId = el.getId();
                            resOk.getResultMap().put(currGuid, currId.toString());


                            saved.add(el.getId());
                        } catch (RestException e) {
                            log.error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
                            PostResult res = new PostResult("ERROR");
                            res.setErrorMessage(e.getMessage());
                            res.setErrorCode(e.getCode());
                            return res;
                        }

                    } else if (currElementMap.containsKey("id") && !currElementMap.get("id").toString().equals("") && Long.parseLong(currElementMap.get("id").toString()) > 0 && currElementMap.containsKey("deleted")) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"additional delete "+currElementMap.get("id").toString());
                        Element elementDeleted = docService.getElement(currElementMap.get("id").toString());
                        docService.deleteElement(user, elementDeleted);
                    } else {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"additional ignoto "+currGuid);
                    }
                }
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);  //To change body of catch statement use File | Settings | File Templates.
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(ex.getMessage());
            return res;
        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"grid ended ");
        //res.setRedirect(ControllerHandler.getBaseUrl(request)+"/app/documents/detail/"+elId);


        return resOk;
    }

    /**
     * Effettua CheckOut dell'elemento
     *
     * @param elId
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     */
    @RequestMapping(value = "/rest/documents/checkOut/{elId}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult checkOut(@PathVariable(value = "elId") Long elId, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Element el = docService.getElement(elId);
        try {
            docService.elementCheckOut(el, user);
        } catch (RestException e) {
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
        }
        PostResult res = new PostResult("OK");
        res.setRedirect(ControllerHandler.getBaseUrl(request) + "/app/documents/detail/" + elId);
        return res;
    }

    /**
     * Effettua il Check-In
     *
     * @param elId
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     */
    @RequestMapping(value = "/rest/documents/checkIn/{elId}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult checkIn(@PathVariable(value = "elId") Long elId, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Element el = docService.getElement(elId);
        try {
            docService.elementCheckIn(el, user);
        } catch (RestException e) {
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
        }
        PostResult res = new PostResult("OK");
        res.setRedirect(ControllerHandler.getBaseUrl(request) + "/app/documents/detail/" + elId);
        return res;
    }


    /**
     * Aggiunge il template
     *
     * @param elId
     * @param templateId
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     */
    @RequestMapping(value = "/rest/documents/addTemplate/{elId}/{templateId}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult addTemplate(@PathVariable(value = "elId") Long elId, @PathVariable(value = "templateId") Long templateId, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Element el = docService.getElement(elId);
        docService.loadCustomGroupsForUser(user, el);
        try {
            docService.addTemplate(user, el, templateId);
        } catch (RestException e) {
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
        }
        PostResult res = new PostResult("OK");
        res.setRedirect(ControllerHandler.getBaseUrl(request) + "/app/documents/detail/" + elId);
        return res;
    }

    @RequestMapping(value = "/rest/documents/addTemplate/{elId}/{templateName}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult addTemplate(@PathVariable(value = "elId") Long elId, @PathVariable(value = "templateName") String templateName, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Element el = docService.getElement(elId);
        docService.loadCustomGroupsForUser(user, el);
        try {
            docService.addTemplate(user, el, templateName);
        } catch (Exception e) {
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
        }
        PostResult res = new PostResult("OK");
        res.setRedirect(ControllerHandler.getBaseUrl(request) + "/app/documents/detail/" + elId);
        return res;
    }

    @RequestMapping(value = "/rest/documents/bulkUpload/{parentId}", method = RequestMethod.POST)
    public @ResponseBody
    PostResult bulkUpload(@PathVariable(value = "parentId") Long parentId, HttpServletRequest request, HttpServletResponse response) throws IOException {
        byte[] file = null;
        String fileName = null;
        if (request instanceof MultipartHttpServletRequest) {
            MultipartFile mfile = ((MultipartHttpServletRequest) request).getFile("file");
            file = mfile.getBytes();
            fileName = mfile.getOriginalFilename();
        }
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        try {
            Long idBulk = docService.bulkFileUpload(user, file, fileName);
            PostResult res = new PostResult("OK");
            Long destType = Long.parseLong(request.getParameter("destType"));
            res.setRedirect(ControllerHandler.getBaseUrl(request) + "/app/documents/bulk/" + parentId + "/" + destType + "/" + idBulk + "?" + new BigInteger(130, new Random()).toString(32));
            return res;
        } catch (RestException e) {
            log.error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            res.setErrorCode(e.getCode());
            return res;
        }

    }

    /**
     * Clona l'element
     *
     * @param id
     * @param request
     * @param response
     * @return
     * @throws IOException
     */
    @RequestMapping(value = "/rest/documents/{id}/defaultClone", method = RequestMethod.GET)
    public @ResponseBody
    PostResult defaultClone(@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response) throws IOException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        try {
            Element el = docService.getElement(id);
            docService.loadCustomGroupsForUser(user, el);
            el = docService.defaultClone(user, id);
            HashMap<String, String> data = new HashMap<String, String>();
            Enumeration paramNames = request.getParameterNames();
            try {
                while (paramNames.hasMoreElements()) {
                    String paramName = (String) paramNames.nextElement();
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Trovato: "+paramName+": "+request.getParameter(paramName));
                    data.put(paramName, request.getParameter(paramName));
                }
                docService.updateElementMetaData(user, el, data, "CREATE");

            } catch (RestException e) {
                log.error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
                PostResult res = new PostResult("ERROR");
                res.setErrorMessage(e.getMessage());
                return res;
            }

            elementIdxUpdate(el, true);

            PostResult res = new PostResult("OK");
            res.setRet(el.getId());
            res.setRedirect(ControllerHandler.getBaseUrl(request) + "/app/documents/detail/" + el.getId());
            return res;
        } catch (RestException e) {
            log.error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            res.setErrorCode(e.getCode());
            return res;
        }
    }

    /**
     * Clona l'element
     *
     * @param id
     * @param request
     * @param response
     * @return
     * @throws IOException
     */
    @RequestMapping(value = "/rest/documents/{id}/newBudgetClone", method = RequestMethod.GET)
    public @ResponseBody
    PostResult newBudgetClone(@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response) throws Exception {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        try {
            Element el = docService.getElement(id);
            PostResult res = new PostResult("OK");
            return res;
            /*
            docService.loadCustomGroupsForUser(user,el);



            HashMap<String, String> data=new HashMap<String, String>();
            HashMap<String,Object> cloneParams=new HashMap<String, Object>();

            List<String> types=new LinkedList<String>();
            types.add("BudgetCTC");
            types.add("ReviewBudgetPI");
            cloneParams.put("skipTypes",types);
            data.put("Budget_Origine",id.toString());
            data.put("Budget_ClonazioneInCorso","1"); //CRPMS-441
            Enumeration paramNames = request.getParameterNames();
            try {
                while (paramNames.hasMoreElements()){
                    String paramName= (String) paramNames.nextElement();
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Trovato: "+paramName+": "+request.getParameter(paramName));
                    data.put(paramName,request.getParameter(paramName));
                }

                el = docService.budgetClone(user.getUsername(), id, cloneParams,data);
            } catch (RestException e) {
                log.error(e.getMessage(),e);  //To change body of catch statement use File | Settings | File Templates.
                PostResult res=new PostResult("ERROR");
                res.setErrorMessage(e.getMessage());
                return res;
            }


            elementIdxUpdate(el, true);

            PostResult res=new PostResult("OK");
            res.setRet(el.getId());
            res.setRedirect(ControllerHandler.getBaseUrl(request)+"/app/documents/detail/"+el.getId());
            return res;
             */
        } catch (Exception e) {
            log.error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            res.setErrorCode(1);
            return res;
        }

    }

    /**
     * Clona l'element
     *
     * @param id
     * @param request
     * @param response
     * @return
     * @throws IOException
     */
    @RequestMapping(value = "/rest/documents/{id}/budgetClone", method = RequestMethod.GET)
    public @ResponseBody
    PostResult budgetClone(@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response) throws Exception {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        try {
            Element el = docService.getElement(id);
            docService.loadCustomGroupsForUser(user, el);
            HashMap<String, String> data = new HashMap<String, String>();
            HashMap<String, Object> cloneParams = new HashMap<String, Object>();

            List<String> types = new LinkedList<String>();
            types.add("ReviewBudgetPI");
            cloneParams.put("skipTypes", types);
            data.put("Budget_Origine", id.toString());
            data.put("Budget_ClonazioneInCorso", "1"); //CRPMS-441
            Enumeration paramNames = request.getParameterNames();
            boolean skipBudgetCTC = true; //SIRER-80 se clono budget allora mi porto dietro anche budgetCTC(valido solo per SIRER)
            try {
                while (paramNames.hasMoreElements()) {
                    String paramName = (String) paramNames.nextElement();
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Trovato: "+paramName+": "+request.getParameter(paramName));
                    if (paramName.equals("noSkipBudgetCTC")) {
                        skipBudgetCTC = false;
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"skipBudgetCTC: "+skipBudgetCTC);
                    }
                    else{
                        data.put(paramName, request.getParameter(paramName));
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"skipBudgetCTC: "+skipBudgetCTC);
                    }
                }
                if (skipBudgetCTC) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Aggiungo BudgetCTC a skip type: "+skipBudgetCTC);
                    types.add("BudgetCTC");
                }
                el = docService.budgetClone(user.getUsername(), id, cloneParams, data);
            } catch (RestException e) {
                log.error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
                PostResult res = new PostResult("ERROR");
                res.setErrorMessage(e.getMessage());
                return res;
            }


            elementIdxUpdate(el, true);

            PostResult res = new PostResult("OK");
            res.setRet(el.getId());
            res.setRedirect(ControllerHandler.getBaseUrl(request) + "/app/documents/detail/" + el.getId());
            return res;
        } catch (RestException e) {
            log.error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            res.setErrorCode(e.getCode());
            return res;
        }
    }

    /**
     * Clona l'element
     *
     * @param id
     * @param request
     * @param response
     * @return
     * @throws IOException
     */
    @RequestMapping(value = "/rest/documents/{id}/budgetClone/{toId}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult budgetClone(@PathVariable(value = "id") Long id, @PathVariable(value = "toId") Long toId, HttpServletRequest request, HttpServletResponse response) throws Exception {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        try {
            Element el = docService.getElement(id);
            docService.loadCustomGroupsForUser(user, el);
            HashMap<String, String> data = new HashMap<String, String>();
            HashMap<String, Object> cloneParams = new HashMap<String, Object>();

            List<String> types = new LinkedList<String>();
            types.add("ReviewBudgetPI");

            data.put("Budget_Origine", id.toString());
            data.put("Budget_ClonazioneInCorso", "1"); //CRPMS-441
            Enumeration paramNames = request.getParameterNames();
            boolean skipBudgetCTC = true; //SIRER-80 se clono budget allora mi porto dietro anche budgetCTC(valido solo per SIRER)
            try {
                while (paramNames.hasMoreElements()) {
                    String paramName = (String) paramNames.nextElement();
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Trovato: "+paramName+": "+request.getParameter(paramName));
                    if (paramName.equals("noSkipBudgetCTC")) {
                        skipBudgetCTC = false;
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"skipBudgetCTC: "+skipBudgetCTC);
                    }
                    else{
                        data.put(paramName, request.getParameter(paramName));
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"skipBudgetCTC: "+skipBudgetCTC);
                    }
                }
                if (skipBudgetCTC) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Aggiungo BudgetCTC a skip type: "+skipBudgetCTC);
                    types.add("BudgetCTC");
                }
                el = docService.budgetCloneOtherCenter(user.getUsername(), id, toId, cloneParams, data, false);
            } catch (RestException e) {
                log.error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
                PostResult res = new PostResult("ERROR");
                res.setErrorMessage(e.getMessage());
                return res;
            }

            cloneParams.put("skipTypes", types);
            elementIdxUpdate(el, true);

            PostResult res = new PostResult("OK");
            res.setRet(el.getId());
            res.setRedirect(ControllerHandler.getBaseUrl(request) + "/app/documents/detail/" + el.getId());
            return res;
        } catch (RestException e) {
            log.error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            res.setErrorCode(e.getCode());
            return res;
        }
    }

    /**
     * Restituisce l'ACL (aclId)
     *
     * @param id
     * @param aclId
     * @param request
     * @param response
     * @return
     */
    @RequestMapping(value = "/rest/documents/{id}/acl/get/{aclId}", method = RequestMethod.GET)
    public @ResponseBody
    Acl getAcl(@PathVariable(value = "id") Long id, @PathVariable(value = "aclId") Long aclId, HttpServletRequest request, HttpServletResponse response) {
        return docService.getAcl(docService.getElement(id), aclId);
    }

    /**
     * Restituisce tutte le ACL associate all'elemento
     *
     * @param id
     * @param request
     * @param response
     * @return
     */
    @RequestMapping(value = "/rest/documents/{id}/acl/getAll", method = RequestMethod.GET)
    public @ResponseBody
    List<Acl> getAcls(@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response) {
        Element el = docService.getElement(id);
        return (List<Acl>) el.getAcls();
    }

    /**
     * Salva le ACL
     * POST parameters:
     * - id (Long): id acl in caso di aggiornamento
     * - policy (Long): id policy predefinita
     * - ...
     *
     * @param elId
     * @param request
     * @param response
     * @return
     * @throws IOException
     * @throws FileUploadException
     */
    @RequestMapping(value = "/rest/documents/{elId}/acl/save", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult saveACL(@PathVariable(value = "elId") Long elId, HttpServletRequest request, HttpServletResponse response) throws IOException, FileUploadException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Long id = null;
        Element el = docService.getElement(elId);
        docService.loadCustomGroupsForUser(user, el);
        if (request.getParameter("id") != null && !request.getParameter("id").isEmpty()) {
            id = Long.parseLong(request.getParameter("id"));
        }
        PredefinedPolicy pp = null;
        Policy pol = new Policy();
        if (request.getParameter("policy").equals("0") || request.getParameter("policy").isEmpty()) {
            boolean view = false;
            if (request.getParameter("view") != null) view = true;
            boolean create = false;
            if (request.getParameter("create") != null) create = true;
            boolean update = false;
            if (request.getParameter("update") != null) update = true;
            boolean addComment = false;
            if (request.getParameter("addComment") != null) addComment = true;
            boolean moderate = false;
            if (request.getParameter("moderate") != null) moderate = true;
            boolean delete = false;
            if (request.getParameter("delete") != null) delete = true;
            boolean changePermission = false;
            if (request.getParameter("changePermission") != null) changePermission = true;
            boolean addChild = false;
            if (request.getParameter("addChild") != null) addChild = true;
            boolean removeCheckOut = false;
            if (request.getParameter("removeCheckOut") != null) removeCheckOut = true;
            boolean launchProcess = false;
            if (request.getParameter("launchProcess") != null) launchProcess = true;
            boolean enableTemplate = false;
            if (request.getParameter("enableTemplate") != null) enableTemplate = true;
            boolean canBrowse = false;
            if (request.getParameter("canBrowse") != null) canBrowse = true;
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
            pp = docService.getPolicy(Long.parseLong(request.getParameter("policy")));
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
        try {
            docService.saveAcl(user, el, groups, users, pol, pp, id, null);
        } catch (RestException e) {
            return new PostResult(e);
        }
        elementIdxUpdate(el, true);

        PostResult res = new PostResult("OK");
        return res;
    }


    /**
     * Elimina la policy aclId dall'elemento
     *
     * @param id
     * @param aclId
     * @param request
     * @param response
     * @return
     * @throws IOException
     * @throws FileUploadException
     */
    @RequestMapping(value = "/rest/documents/{id}/acl/delete/{aclId}", method = RequestMethod.GET)
    public
    @ResponseBody
    PostResult deleteACL(@PathVariable(value = "id") Long id, @PathVariable(value = "aclId") Long aclId, HttpServletRequest request, HttpServletResponse response) throws IOException, FileUploadException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Element el = docService.getElement(id);
        docService.loadCustomGroupsForUser(user, el);
        try {
            docService.deleteAcl(user, el, aclId);
        } catch (RestException e) {
            return new PostResult(e);
        }
        elementIdxUpdate(el, true);

        return new PostResult("OK");
    }


    @RequestMapping(value = "/rest/documents/{id}/createDraft", method = RequestMethod.POST)
    public @ResponseBody
    PostResult createDraft(@PathVariable(value = "id") Long id, HttpServletRequest request) {
        try {
            IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
            Element el = docService.createDraft(user, id);
            PostResult res = new PostResult("OK");
            res.setRedirect(ControllerHandler.getBaseUrl(request) + "/app/documents/detail/" + el.getId());
            return res;
        } catch (RestException e) {
            return new PostResult(e);
        }
    }
    
    /*
    @RequestMapping(value="/rest/documents/{id}/fullClone", method=RequestMethod.POST)
    public @ResponseBody
    PostResult fullClone(@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response) throws IOException {
        List<File> ret=new LinkedList<File>();
        Element el=docService.getElement(id);
        return new PostResult("OK");
    }
    */


    /**
     * Recupera gli elementi della root del tipo typeId
     *
     * @param docTypeS
     * @param request
     * @return
     */
    @RequestMapping(value = "/rest/documents/getRootElementsByType/{typeId}", method = RequestMethod.GET)
    public
    @ResponseBody
    List<ElementJSON> getRootElementsByType(@PathVariable(value = "typeId") String docTypeS, HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Long typeId = docService.getTypeIdByNameOrId(docTypeS);
        int limit = 20;
        int page = 1;
        if (request.getParameter("p") != null && !request.getParameter("p").isEmpty())
            page = Integer.parseInt(request.getParameter("p"));
        if (request.getParameter("limit") != null && !request.getParameter("limit").isEmpty())
            limit = Integer.parseInt(request.getParameter("limit"));
        String orderBy = "";
        String orderType = "";
        if (request.getParameter("orderBy") != null && !request.getParameter("orderBy").isEmpty())
            orderBy = request.getParameter("orderBy");
        if (request.getParameter("orderType") != null && !request.getParameter("orderType").isEmpty())
            orderType = request.getParameter("orderType");
        List<Element> els = docService.getRootElementsLimitById(user, typeId, page, limit, orderBy, orderType);
        List<ElementJSON> ret = new LinkedList<ElementJSON>();
        for (Element el : els) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Elemento trovato: "+el.getId().toString());
            ret.add(new ElementJSON(el, user, "single"));
        }
        return ret;
    }

    @RequestMapping(value = "/rest/documents/jqgrid/getElementsByTypePaged/{typeId}", method = RequestMethod.GET)
    public @ResponseBody
    JqGridJSON getElementsByTypeId(@PathVariable(value = "typeId") String typeId, HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        int limit = 20;
        int page = 1;
        String rule = "single-without-parent";
        int level = 0;
        JqGridJSON grid = new JqGridJSON();
        if (request.getParameter("page") != null && !request.getParameter("page").isEmpty())
            page = Integer.parseInt(request.getParameter("page"));
        if (request.getParameter("rows") != null && !request.getParameter("rows").isEmpty())
            limit = Integer.parseInt(request.getParameter("rows"));
        String orderBy = "";
        String orderType = "";
        if (!request.getParameter("rule").isEmpty()) {
            rule = request.getParameter("rule");
        }
        if (!request.getParameter("level").isEmpty()) {
            level = Integer.parseInt(request.getParameter("level"));
        }
        if (request.getParameter("orderBy") != null && !request.getParameter("orderBy").isEmpty())
            orderBy = request.getParameter("orderBy");
        if (request.getParameter("orderType") != null && !request.getParameter("orderType").isEmpty())
            orderType = request.getParameter("orderType");
        List<Element> els = docService.getElementsLimitByTypeId(user, typeId, page, limit, orderBy, orderType, grid);
        List<ElementJSON> ret = new LinkedList<ElementJSON>();
        for (Element el : els) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Elemento trovato: "+el.getId().toString());
            ret.add(new ElementJSON(el, user, rule, level));
        }
        grid.setRoot(ret);
        return grid;
    }


    @RequestMapping(value = "/rest/documents/jqgrid/getRootElementsByTypePaged/{typeId}", method = RequestMethod.GET)
    public @ResponseBody
    JqGridJSON getRootElementsByTypeId(@PathVariable(value = "typeId") String typeId, HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        int limit = 20;
        int page = 1;
        String rule = "single-without-parent";
        int level = 0;
        JqGridJSON grid = new JqGridJSON();
        if (request.getParameter("page") != null && !request.getParameter("page").isEmpty())
            page = Integer.parseInt(request.getParameter("page"));
        if (request.getParameter("rows") != null && !request.getParameter("rows").isEmpty())
            limit = Integer.parseInt(request.getParameter("rows"));
        String orderBy = "";
        String orderType = "";
        if (request.getParameter("rule") != null && !request.getParameter("rule").isEmpty()) {
            rule = request.getParameter("rule");
        }
        if (request.getParameter("rule") != null && !request.getParameter("level").isEmpty()) {
            level = Integer.parseInt(request.getParameter("level"));
        }
        if (request.getParameter("orderBy") != null && !request.getParameter("orderBy").isEmpty())
            orderBy = request.getParameter("orderBy");
        if (request.getParameter("orderType") != null && !request.getParameter("orderType").isEmpty())
            orderType = request.getParameter("orderType");
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"page "+String.valueOf(page)+" limit "+String.valueOf(limit));
        List<Element> els = docService.getRootElementsLimitByTypeId(user, typeId, page, limit, orderBy, orderType, grid);
        List<ElementJSON> ret = new LinkedList<ElementJSON>();
        for (Element el : els) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Elemento trovato: "+el.getId().toString());
            ret.add(new ElementJSON(el, user, rule, level));
        }
        grid.setRoot(ret);
        return grid;
    }


    /**
     * Recupera gli elementi  del tipo typeId
     *
     * @param docTypeS
     * @param request
     * @return
     */
    @RequestMapping(value = "/rest/documents/getElementsByType/{typeId}", method = RequestMethod.GET)
    public
    @ResponseBody
    List<ElementJSON> getElementsByType(@PathVariable(value = "typeId") String docTypeS, HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Long typeId = docService.getTypeIdByNameOrId(docTypeS);
        int limit = 20;
        int page = 1;
        if (request.getParameter("p") != null && !request.getParameter("p").isEmpty())
            page = Integer.parseInt(request.getParameter("p"));
        if (request.getParameter("limit") != null && !request.getParameter("limit").isEmpty())
            limit = Integer.parseInt(request.getParameter("limit"));
        String orderBy = "";
        String orderType = "";
        if (request.getParameter("orderBy") != null && !request.getParameter("orderBy").isEmpty())
            orderBy = request.getParameter("orderBy");
        if (request.getParameter("orderType") != null && !request.getParameter("orderType").isEmpty())
            orderType = request.getParameter("orderType");
        List<Element> els = docService.getElementsLimitById(user, typeId, page, limit, orderBy, orderType);
        List<ElementJSON> ret = new LinkedList<ElementJSON>();
        for (Element el : els) {
            ret.add(new ElementJSON(el, user, "single-with-parent"));
        }
        return ret;
    }

    /*
    @RequestMapping(value="/rest/documents/getElementsByTypeId/{typeId}", method = RequestMethod.GET)
    public @ResponseBody List<ElementJSON> getElementsByType(@PathVariable(value = "typeId") String typeId, HttpServletRequest request){
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        int limit=20;
        int page=1;
        if (request.getParameter("p")!=null && !request.getParameter("p").isEmpty()) page=Integer.parseInt(request.getParameter("p"));
        if (request.getParameter("limit")!=null && !request.getParameter("limit").isEmpty()) limit=Integer.parseInt(request.getParameter("limit"));
        String orderBy="";
        String orderType="";
        if (request.getParameter("orderBy")!=null && !request.getParameter("orderBy").isEmpty()) orderBy=request.getParameter("orderBy");
        if (request.getParameter("orderType")!=null && !request.getParameter("orderType").isEmpty()) orderType=request.getParameter("orderType");
        List<Element> els=docService.getElementsLimitByTypeId(user, typeId, page, limit, orderBy, orderType);
        List<ElementJSON> ret=new LinkedList<ElementJSON>();
        for (Element el:els){
            ret.add(new ElementJSON(el, user, "single-with-parent"));
        }
        return ret;
    }
*/
    @RequestMapping(value = "/rest/documents/getElementsByTypeFiltered/{typeId}", method = RequestMethod.GET)
    public
    @ResponseBody
    List<ElementJSON> getElementsByTypeFiltered(@PathVariable(value = "typeId") String docTypeS, HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Long typeId = docService.getTypeIdByNameOrId(docTypeS);
        int limit = 20;
        int page = 1;
        if (request.getParameter("p") != null && !request.getParameter("p").isEmpty())
            page = Integer.parseInt(request.getParameter("p"));
        if (request.getParameter("limit") != null && !request.getParameter("limit").isEmpty())
            limit = Integer.parseInt(request.getParameter("limit"));
        String orderBy = "";
        String orderType = "";
        if (request.getParameter("orderBy") != null && !request.getParameter("orderBy").isEmpty())
            orderBy = request.getParameter("orderBy");
        if (request.getParameter("orderType") != null && !request.getParameter("orderType").isEmpty())
            orderType = request.getParameter("orderType");
        String pattern = request.getParameter("pattern");
        boolean exact = false;
        if (request.getParameter("exact") != null && !request.getParameter("exact").isEmpty()) exact = true;
        String field = request.getParameter("pattern");
        List<Element> els = docService.getElementsLimitByIdFiltered(user, typeId, page, limit, orderBy, orderType, field, pattern, exact);
        List<ElementJSON> ret = new LinkedList<ElementJSON>();
        for (Element el : els) {
            ret.add(new ElementJSON(el, user, "single-with-parent"));
        }
        return ret;
    }


    @RequestMapping(value = "/rest/documents/{elementId}/getChildren/{typeId}/maxdepth/{level}", method = RequestMethod.GET)
    public
    @ResponseBody
    List<ElementJSON> getChildrenOfTypeByParentWithMaxDepth(
            @PathVariable(value = "elementId") Long elementId,
            @PathVariable(value = "typeId") String docTypeS,
            @PathVariable(value = "level") int level,
            HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Element dad = docService.getElement(elementId);
        List<Element> els = dad.getChildrenByType(docTypeS);
        List<ElementJSON> ret = new LinkedList<ElementJSON>();
        for (Element el : els) {
            ret.add(new ElementJSON(el, user, "complete-without-parent", level));
        }
        return ret;
    }

    @RequestMapping(value = "/rest/documents/getRootElements/{typeId}", method = RequestMethod.GET)
    public @ResponseBody
    List<ElementJSON> getRootElements(@PathVariable(value = "typeId") Long typeId, HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        int limit = 20;
        int page = 1;
        if (request.getParameter("p") != null && !request.getParameter("p").isEmpty())
            page = Integer.parseInt(request.getParameter("p"));
        if (request.getParameter("limit") != null && !request.getParameter("limit").isEmpty())
            limit = Integer.parseInt(request.getParameter("limit"));
        String orderBy = "";
        String orderType = "";
        if (request.getParameter("orderBy") != null && !request.getParameter("orderBy").isEmpty())
            orderBy = request.getParameter("orderBy");
        if (request.getParameter("orderType") != null && !request.getParameter("orderType").isEmpty())
            orderType = request.getParameter("orderType");
        List<Element> els = docService.getRootElementsLimit(user, page, limit, orderBy, orderType);
        List<ElementJSON> ret = new LinkedList<ElementJSON>();
        for (Element el : els) {
            ret.add(new ElementJSON(el, user, "single"));
        }
        return ret;
    }

    @RequestMapping(value = "/rest/documents/test/{objId}", method = RequestMethod.GET)
    public @ResponseBody
    List<Object> test(@PathVariable(value = "objId") Long objId, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        Element el = docService.getElement(Long.parseLong("187240"));
        List<Element> tpxp = (List<Element>) ((Element) el.getChildrenByType("FolderTpxp").get(0)).getChildren();
        List<Object> data = null;
        for (Element currPrestazione : tpxp) {
            data = currPrestazione.getfieldData("tp-p", "Prestazione");
            it.cineca.siss.axmr3.log.Log.debug(getClass(),data.toString());
        }
        return data;
    }


    @RequestMapping(value = "/rest/documents/{id}/template/{assocId}/acl", method = RequestMethod.POST)
    public @ResponseBody
    PostResult setAclToTemplate(@PathVariable(value = "id") Long id, @PathVariable(value = "assocId") Long assocId,
                                @RequestParam(value = "create", required = false, defaultValue = "0") String create,
                                @RequestParam(value = "update", required = false, defaultValue = "0") String update,
                                @RequestParam(value = "delete", required = false, defaultValue = "0") String delete,
                                @RequestParam(value = "view", required = false, defaultValue = "0") String view,
                                @RequestParam(value = "groups", required = false, defaultValue = "") String groups,
                                @RequestParam(value = "users", required = false, defaultValue = "") String users,
                                @RequestParam(value = "cuser", required = false, defaultValue = "") String cuser,
                                @RequestParam(value = "allUsers", required = false, defaultValue = "") String allUsers) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        TemplatePolicy pol = new TemplatePolicy();
        if (create.equals("1")) pol.setCanCreate(true);
        else pol.setCanCreate(false);
        if (update.equals("1")) pol.setCanUpdate(true);
        else pol.setCanUpdate(false);
        if (delete.equals("1")) pol.setCanDelete(true);
        else pol.setCanDelete(false);
        if (view.equals("1")) pol.setCanView(true);
        else pol.setCanView(false);
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
            docService.addTemplateAcl(user, id, assocId, pol, usersList, groupsList);
            return new PostResult("OK");
        } catch (RestException ex) {
            return new PostResult(ex);
        }
    }

    @RequestMapping(value = "/rest/documents/{id}/template/{assocId}/acl", method = RequestMethod.GET)
    public @ResponseBody
    List<TemplateAcl> getTemplateAcls(@PathVariable(value = "id") Long id, @PathVariable(value = "assocId") Long assocId) {
        Element t = docService.getElement(id);
        for (ElementTemplate tpl : t.getElementTemplates()) {
            if (tpl.getId().equals(assocId)) return (List<TemplateAcl>) tpl.getTemplateAcls();
        }
        return new LinkedList<TemplateAcl>();
    }

    @RequestMapping(value = "/rest/documents/{id}/template/{assocId}/acl/{aclId}", method = RequestMethod.GET)
    public @ResponseBody
    TemplateAcl getTemplateAcl(@PathVariable(value = "id") Long id, @PathVariable(value = "assocId") Long assocId, @PathVariable(value = "aclId") Long aclId) {
        Element t = docService.getElement(id);
        for (ElementTemplate tpl : t.getElementTemplates()) {
            if (tpl.getId().equals(assocId)) {
                for (TemplateAcl acl : tpl.getTemplateAcls()) {
                    if (acl.getId().equals(aclId)) return acl;
                }
            }
        }
        return null;
    }

    @RequestMapping(value = "/rest/documents/{id}/template/{assocId}/acl/{aclId}/delete", method = RequestMethod.GET)
    public @ResponseBody
    PostResult deleteTemplateAcl(@PathVariable(value = "id") Long id, @PathVariable(value = "assocId") Long assocId, @PathVariable(value = "aclId") Long aclId) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        try {
            docService.deleteTemplateAcl(user, id, assocId, aclId);
            return new PostResult("OK");
        } catch (RestException ex) {
            return new PostResult(ex);
        }

    }

    @RequestMapping(value = "/rest/documents/getElementsByParent/{parentId}", method = RequestMethod.GET)
    public @ResponseBody
    List<ElementJSON> getElementsByParent(@PathVariable(value = "parentId") Long parentId) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        List<Element> els = docService.getElementsByParent(user, parentId);
        List<ElementJSON> ret = new LinkedList<ElementJSON>();
        for (Element el : els) {
            ret.add(new ElementJSON(el, user, "single-with-parent"));
        }
        return ret;
    }

    @RequestMapping(value = "/rest/documents/getElementsByParentWithChilds/{parentId}", method = RequestMethod.GET)
    public
    @ResponseBody
    List<ElementJSON> getElementsByParentWithChilds(@PathVariable(value = "parentId") Long parentId) {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        List<Element> els = docService.getElementsByParent(user, parentId);
        List<ElementJSON> ret = new LinkedList<ElementJSON>();
        for (Element el : els) {
            ret.add(new ElementJSON(el, user, "complete-without-parent"));
        }
        return ret;
    }

    @RequestMapping(value = "/rest/documents/getElementsByParentAndType/{parentId}/{typeId}", method = RequestMethod.GET)
    public @ResponseBody
    List<ElementJSON> getElementsByParent(@PathVariable(value = "parentId") Long parentId, @PathVariable(value = "typeId") String typeId) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        List<Element> els = docService.getElementsByParent(user, parentId);
        List<ElementJSON> ret = new LinkedList<ElementJSON>();
        for (Element el : els) {
            if (el.getType().getTypeId().equals(typeId)) ret.add(new ElementJSON(el, user, "single-with-parent"));
        }
        return ret;
    }

    @RequestMapping(value = "/rest/documents/advancedSearch/{typeId}", method = RequestMethod.GET)
    public @ResponseBody
    List<ElementJSON> advancedSearch(@PathVariable(value = "typeId") String typeId, HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        HashMap<String, Object> data = new HashMap<String, Object>();
        Enumeration paramNames = request.getParameterNames();
        while (paramNames.hasMoreElements()) {
            String paramName = (String) paramNames.nextElement();
            if (paramName.length() > 2) {
                String lastChars = paramName.substring(paramName.length() - 2);
                it.cineca.siss.axmr3.log.Log.debug(getClass(),paramName+" - "+lastChars);
                if (lastChars.equals("[]")) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Effettuo put di request []:"+paramName.substring(0, paramName.length()-2)+" - "+request.getParameterValues(paramName));
                    data.put(paramName.substring(0, paramName.length() - 2), request.getParameterValues(paramName));
                } else {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Effettuo put di request:"+paramName+" - "+request.getParameter(paramName));
                    data.put(paramName, request.getParameter(paramName));
                }
            } else {
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Effettuo put di request:"+paramName+" - "+request.getParameter(paramName));
                data.put(paramName, request.getParameter(paramName));
            }
        }
        List<Element> els = docService.advancedSearch(user, typeId, data);
        List<ElementJSON> ret = new LinkedList<ElementJSON>();
        String mode = "single";
        if (request.getParameter("mode") != null && !request.getParameter("mode").isEmpty()) {
            mode = request.getParameter("mode");
        }
        for (Element el : els) {
            ret.add(new ElementJSON(el, user, mode));
        }
        return ret;
    }

    @RequestMapping(value = "/rest/documents/advancedSearchDictionary/{typeId}", method = RequestMethod.GET)
    public @ResponseBody
    List<HashMap<String, String>> advancedSearchDictionary(@PathVariable(value = "typeId") String typeId, HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        HashMap<String, Object> data = new HashMap<String, Object>();
        Enumeration paramNames = request.getParameterNames();
        HashMap<String, String> currItem;
        while (paramNames.hasMoreElements()) {
            String paramName = (String) paramNames.nextElement();
            if (paramName.length() > 2) {
                String lastChars = paramName.substring(paramName.length() - 2);
                it.cineca.siss.axmr3.log.Log.debug(getClass(),paramName+" - "+lastChars);
                if (lastChars.equals("[]")) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Effettuo put di request []:"+paramName.substring(0, paramName.length()-2)+" - "+request.getParameterValues(paramName));
                    data.put(paramName.substring(0, paramName.length() - 2), request.getParameterValues(paramName));
                } else {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Effettuo put di request:"+paramName+" - "+request.getParameter(paramName));
                    data.put(paramName, request.getParameter(paramName));
                }
            } else {
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Effettuo put di request:"+paramName+" - "+request.getParameter(paramName));
                data.put(paramName, request.getParameter(paramName));
            }
        }
        List<Element> els = docService.advancedSearch(user, typeId, data);
        List<HashMap<String, String>> ret = new LinkedList<HashMap<String, String>>();
        for (Element el : els) {
            currItem = new HashMap<String, String>();
            currItem.put("id", el.getId().toString());
            currItem.put("title", el.getTitleString());
            ret.add(currItem);
        }
        return ret;
    }

    @RequestMapping(value = "/rest/documents/searchBracci", method = RequestMethod.GET)
    public @ResponseBody
    List<HashMap<String, String>> searchBracci(HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        HashMap<String, Object> data = new HashMap<String, Object>();
        Enumeration paramNames = request.getParameterNames();
        HashMap<String, String> currItem;
        String center = request.getParameter("center");
        Element centerEl = docService.getElement(center);
        String budgetType = centerEl.getFieldDataString("statoValidazioneCentro", "typeBudgetApproved");
        String budgetId = centerEl.getFieldDataString("statoValidazioneCentro", "idBudgetApproved");
        Element budget;
        List<HashMap<String, String>> ret = new LinkedList<HashMap<String, String>>();
        if (budgetType.equals("BudgetBracci")) {
            try {
                budget = docService.getElement(budgetId);
                List<Element> folders = budget.getChildrenByType("FolderSingoloBraccio");
                if (!folders.isEmpty()) {
                    Element folder = folders.get(0);
                    Collection<Element> els = folder.getChildren();

                    for (Element el : els) {
                        currItem = new HashMap<String, String>();
                        currItem.put("id", el.getId().toString());
                        currItem.put("title", el.getTitleString());
                        ret.add(currItem);
                    }
                }
            } catch (Exception ex) {
                log.error(ex.getMessage(), ex);
            }
        }
        return ret;
    }


    @RequestMapping(value = "/rest/documents/fullSearch", method = RequestMethod.GET)
    public
    @ResponseBody
    List<ElementJSON> fullSearch(HttpServletRequest request) {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        String pattern = request.getParameter("pattern");
        List<Element> els = docService.search(user, pattern);
        List<ElementJSON> ret = new LinkedList<ElementJSON>();
        for (Element el : els) {
            ret.add(new ElementJSON(el, user, "single"));
        }
        return ret;
    }

    @RequestMapping(value = "/rest/documents/jqgrid/advancedSearch/{typeId}", method = RequestMethod.GET)
    public
    @ResponseBody
    JqGridJSON advancedSearchJqGrid(@PathVariable(value = "typeId") String typeId, HttpServletRequest request) {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        HashMap<String, Object> data = new HashMap<String, Object>();
        Enumeration paramNames = request.getParameterNames();
        int page = 1;
        int rows = 5;
        while (paramNames.hasMoreElements()) {
            String paramName = (String) paramNames.nextElement();
            if (paramName.equalsIgnoreCase("page") || paramName.equalsIgnoreCase("rows") || paramName.equalsIgnoreCase("sidx") || paramName.equalsIgnoreCase("sord")) {
                if (paramName.equalsIgnoreCase("page")) {
                    page = Integer.parseInt(request.getParameter(paramName));
                }
                if (paramName.equalsIgnoreCase("rows")) {
                    rows = Integer.parseInt(request.getParameter(paramName));
                } else {
                    data.put(paramName, request.getParameter(paramName));
                }
            } else {
                String lastChars = paramName.substring(paramName.length() - 2);
                it.cineca.siss.axmr3.log.Log.debug(getClass(),paramName + " - " + lastChars);
                if (lastChars.equals("[]")) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Effettuo put di request []:" + paramName.substring(0, paramName.length() - 2) + " - " + request.getParameterValues(paramName));
                    data.put(paramName.substring(0, paramName.length() - 2), request.getParameterValues(paramName));
                } else {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Effettuo put di request:" + paramName + " - " + request.getParameter(paramName));
                    data.put(paramName, request.getParameter(paramName));
                }
            }
        }


        JqGridJSON res = new JqGridJSON();
        List<Element> els = docService.advancedSearch(user, typeId, data, page, rows, res);
        List<ElementJSON> ret = new LinkedList<ElementJSON>();
        for (Element el : els) {
            ret.add(new ElementJSON(el, user, "single-with-parent"));
        }
        res.setRoot(ret);
        return res;
    }

    @RequestMapping(value = "/rest/documents/advancedSearchCount/{typeId}", method = RequestMethod.GET)
    public @ResponseBody
    Long advancedSearchCount(@PathVariable(value = "typeId") String typeId, HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        HashMap<String, Object> data = new HashMap<String, Object>();
        Enumeration paramNames = request.getParameterNames();
        while (paramNames.hasMoreElements()) {
            String paramName = (String) paramNames.nextElement();

            String lastChars = paramName.substring(paramName.length() - 2);
            it.cineca.siss.axmr3.log.Log.debug(getClass(),paramName + " - " + lastChars);
            if (lastChars.equals("[]")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Effettuo put di request []:"+paramName.substring(0, paramName.length()-2)+" - "+request.getParameterValues(paramName));
                data.put(paramName.substring(0, paramName.length() - 2), request.getParameterValues(paramName));
            } else {
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Effettuo put di request:"+paramName+" - "+request.getParameter(paramName));
                data.put(paramName, request.getParameter(paramName));
            }
        }
        return docService.advancedSearchCount(user, typeId, data);
    }

    @RequestMapping(value = "/rest/documents/getReferralCascade/{elementId}", method = RequestMethod.GET)
    public @ResponseBody
    List<ElementJSON> getReferralCascade(@PathVariable(value = "elementId") Long elementId) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        List<Element> els = docService.getReferralCascade(elementId);
        List<ElementJSON> ret = new LinkedList<ElementJSON>();
        for (Element el : els) {
            ret.add(new ElementJSON(el, user, "single"));
        }
        return ret;
    }

    @RequestMapping(value = "/rest/documents/DumpObject/{typeId}/{tableName}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult persistObject(@PathVariable(value = "typeId") String typeId, @PathVariable(value = "tableName") String tableName) {
        //IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        try {
            docService.persistObjects(typeId, tableName);
            return new PostResult("OK");
        } catch (RestException ex) {
            return new PostResult(ex);
        }
    }

    @RequestMapping(value = "/rest/documents/DumpAllObjects/{prefix}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult persistObject(@PathVariable(value = "prefix") String prefix) {
        try {
            docService.persistAllObjects(prefix);
            return new PostResult("OK");
        } catch (RestException ex) {
            return new PostResult(ex);
        }
    }


    @RequestMapping(value = "/rest/documents/move/{objId}/up", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult moveUp(@PathVariable(value = "objId") Long objId, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        Element el = docService.getElement(objId);
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        PostResult res = new PostResult("OK");
        try {
            docService.moveUp(user.getUsername(), el);
        } catch (RestException e) {
            res.setResult("ERROR");
            res.setErrorMessage(e.getMessage());
        }
        return res;
    }

    @RequestMapping(value = "/rest/documents/move/{objId}/down", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult moveDown(@PathVariable(value = "objId") Long objId, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        Element el = docService.getElement(objId);
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        PostResult res = new PostResult("OK");
        try {
            docService.moveDown(user.getUsername(), el);
        } catch (RestException e) {
            res.setResult("ERROR");
            res.setErrorMessage(e.getMessage());
        }
        return res;
    }

    @RequestMapping(value = "/rest/documents/move/{objId}/top", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult moveTop(@PathVariable(value = "objId") Long objId, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        Element el = docService.getElement(objId);
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        PostResult res = new PostResult("OK");
        try {
            docService.moveToTop(user.getUsername(), el);
        } catch (RestException e) {
            res.setResult("ERROR");
            res.setErrorMessage(e.getMessage());
        }
        return res;
    }

    @RequestMapping(value = "/rest/documents/move/{objId}/bottom", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult moveBottom(@PathVariable(value = "objId") Long objId, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        Element el = docService.getElement(objId);
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        PostResult res = new PostResult("OK");
        try {
            docService.moveToBottom(user.getUsername(), el);
        } catch (RestException e) {
            res.setResult("ERROR");
            res.setErrorMessage(e.getMessage());
        }
        return res;
    }

    @RequestMapping(value = "/rest/documents/move/{objId}/to/{pos}", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult moveToPos(@PathVariable(value = "objId") Long objId, @PathVariable(value = "pos") Long pos, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        Element el = docService.getElement(objId);
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        PostResult res = new PostResult("OK");
        try {
            docService.moveToPosition(user.getUsername(), el, pos);
        } catch (RestException e) {
            res.setResult("ERROR");
            res.setErrorMessage(e.getMessage());
        }
        return res;
    }

    @RequestMapping(value = "/rest/documents/move/{objId}/to/{pos}/parent/{newParentId}", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult moveToPosAndParent(@PathVariable(value = "objId") Long objId, @PathVariable(value = "pos") Long pos, @PathVariable(value = "newParentId") Long newParentId, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        Element el = docService.getElement(objId);
        Element newParent = docService.getElement(newParentId);
        Element oldParent = el.getParent();
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        PostResult res = new PostResult("OK");
        try {
            docService.moveToPositionAndParent(user.getUsername(), el, newParent, pos);
            docService.clearBlankPosition(oldParent);
        } catch (RestException e) {
            res.setResult("ERROR");
            res.setErrorMessage(e.getMessage());
        }
        return res;
    }

    @RequestMapping(value = "/rest/documents/values/fieldId/{fieldId}", method = RequestMethod.GET)
    public
    @ResponseBody
    PostResult getFieldAvailableValues(@PathVariable(value = "fieldId") Long fieldId) {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        PostResult res = new PostResult("OK");
        try {
            HashMap<String, Object> ret = new HashMap<String, Object>();
            HashMap<String, String> ret1 = docService.getFieldsValues(fieldId, user, null);
            Iterator<String> it = ret1.keySet().iterator();
            while (it.hasNext()) {
                String key = it.next();
                ret.put(key, ret1.get(key));
            }
            res.setResultMap(ret);
        } catch (Exception e) {
            res.setResult("ERROR");
            res.setErrorMessage(e.getMessage());
        }
        return res;
    }

    @RequestMapping(value = "/rest/documents/values/fieldname/{fieldName}", method = RequestMethod.GET)
    public
    @ResponseBody
    PostResult getFieldAvailableValuesByString(@PathVariable(value = "fieldName") String fieldName) {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        PostResult res = new PostResult("OK");
        try {
            HashMap<String, Object> ret = new HashMap<String, Object>();
            HashMap<String, String> ret1 = docService.getFieldsValues(fieldName, user, null);
            Iterator<String> it = ret1.keySet().iterator();
            while (it.hasNext()) {
                String key = it.next();
                ret.put(key, ret1.get(key));
            }
            res.setResultMap(ret);
        } catch (Exception e) {
            res.setResult("ERROR");
            res.setErrorMessage(e.getMessage());
        }
        return res;
    }


    @RequestMapping(value = "/rest/i18n/{lang}", method = RequestMethod.GET)
    public @ResponseBody
    HashMap<String, String> getI18n(@PathVariable(value = "lang") String lang) throws RestException {
        Properties adHocProps = new Properties();
        HashMap<String, String> messages = new HashMap<String, String>();
        String filename = messagesFolder + "/messages/" + lang.toLowerCase() + "_" + lang.toUpperCase() + ".properties";
        try {
            java.io.File file = new java.io.File(filename);
            if (file.exists()) {

                FileInputStream fis = new FileInputStream(file);
                adHocProps.load(fis);
                fis.close();

            } else {
                filename = messagesFolder + "/messages/it_IT.properties";
                if (file.exists()) {
                    FileInputStream fis = new FileInputStream(file);
                    adHocProps.load(fis);
                    fis.close();
                }
            }
            Enumeration e1 = adHocProps.propertyNames();
            while (e1.hasMoreElements()) {
                String key = (String) e1.nextElement();
                messages.put(key, adHocProps.getProperty(key));
            }
            return messages;
        } catch (Exception ex) {
            throw new RestException(ex.getMessage(), 10);
        }
    }


    @RequestMapping(value = "/rest/documents/audit/{elementId}/{templateName}/{templateField}", method = RequestMethod.GET)
    public @ResponseBody
    List<AuditJSON> getFieldAudit(@PathVariable(value = "elementId") Long elementId, @PathVariable(value = "templateName") String templateName, @PathVariable(value = "templateField") String templateField) throws RestException {
        Element el = docService.getElement(elementId);
        List<AuditJSON> ret = new LinkedList<AuditJSON>();
        for (AuditMetadata data : el.getAuditData()) {
            if (data.getTemplateName().toLowerCase().equals(templateName.toLowerCase()) && data.getFieldName().toLowerCase().equals(templateField.toLowerCase())) {
                ret.add(new AuditJSON(data, uService));
            }
        }
        return ret;
    }

    @RequestMapping(value = "/rest/documents/policy/{elementId}/set/{container}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult assignPolicyToGroup(
            @PathVariable(value = "elementId") Long elementId,
            @PathVariable(value = "container") String container,
            HttpServletRequest request) throws RestException {
        Element el = docService.getElement(elementId);
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        if (el.getUserPolicy(user).isCanChangePermission()) {
            try {
                String policy = request.getParameter("policy");
                boolean recursive = false;
                boolean isGroup = false;
                if (request.getParameter("isGroup") != null) {
                    String isGroupString = request.getParameter("isGroup");
                    if (isGroupString.toLowerCase().equals("true")) isGroup = true;
                }
                if (request.getParameter("recursive") != null) {
                    String recursiveString = request.getParameter("recursive");
                    if (recursiveString.toLowerCase().equals("true")) recursive = true;
                }
                String ftl = null;
                if (request.getParameter("ftl") != null) ftl = request.getParameter("ftl");
                docService.setElementPolicy(el, ftl, policy, isGroup, container, recursive);
                return new PostResult("OK");
            } catch (AxmrGenericException e) {
                return new PostResult(e);
            }
        } else {
            return new PostResult("NOT_PERMITTED");
        }
    }


    @RequestMapping(value="/rest/documents/gemelli/modificaPermessiStudioPI/{studioId}", method = RequestMethod.GET)
    public @ResponseBody PostResult modificaPermessiStudioPI(@PathVariable(value = "studioId") Long studioId){
        docService.modificaPermessiStudioPI(studioId);
        return new PostResult("OK");
    }


    @RequestMapping(value="/rest/documents/xml/{xmlform}/alpaca", method = RequestMethod.GET)
    public @ResponseBody
    it.cineca.siss.axmr3.doc.xml.alpaca.Form alpacaForm(@PathVariable(value = "xmlform") String xmlform, HttpServletRequest request, HttpServletResponse response) throws RestException {
        return alpacaFormByElementId(xmlform,null,request,response);
    }

    @RequestMapping(value="/rest/documents/xml/{xmlform}/{elementId}/alpaca", method = RequestMethod.GET)
    public @ResponseBody
    it.cineca.siss.axmr3.doc.xml.alpaca.Form alpacaFormByElementId(@PathVariable(value = "xmlform") String xmlform, @PathVariable(value = "elementId") Long elId, HttpServletRequest request, HttpServletResponse response) throws RestException {
        return alpacaFormByElementId(xmlform,elId,null,request,response);
    }

    @RequestMapping(value="/rest/documents/xml/{xmlform}/{elementId}/alpaca/{mode}", method = RequestMethod.GET)
    public @ResponseBody
    it.cineca.siss.axmr3.doc.xml.alpaca.Form alpacaFormByElementId(@PathVariable(value = "xmlform") String xmlform, @PathVariable(value = "elementId") Long elId, @PathVariable(value = "mode") String mode, HttpServletRequest request, HttpServletResponse response) throws RestException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }

        try{
            return docService.getAlpacaJson(user, request, xmlform, elId, mode);
        }catch (Exception ex){
            Logger.getLogger(this.getClass()).error(ex.getMessage(), ex);
            throw new RestException(ex.getMessage(), 1);
        }
    }

    @RequestMapping(value="/rest/documents/xml/update/{xmlform}/{elementId}", method = RequestMethod.POST)
    public @ResponseBody PostResult xmlUpdateElement(@PathVariable(value = "xmlform") String xmlform, @PathVariable(value = "elementId") Long elId, HttpServletRequest request, HttpServletResponse response) throws RestException{

        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        HashMap<String, String[]> data=new HashMap<String, String[]>();
        HashMap<String, String> dataSingle=new HashMap<String, String>();
        Enumeration paramNames = request.getParameterNames();
        try {
            Element el=docService.getElement(elId);
            boolean onlySingleValue=true;
            while (paramNames.hasMoreElements()){
                String paramName= (String) paramNames.nextElement();
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Trovato: "+paramName+": "+request.getParameter(paramName));
                String[] values=request.getParameterValues(paramName);
                String paramNameMultiple=paramName.replaceAll("\\[\\]", "");
                if (values.length>1){
                    onlySingleValue=false;

                }else {
                    dataSingle.put(paramNameMultiple,request.getParameter(paramName));
                }
                data.put(paramNameMultiple,request.getParameterValues(paramName));
            }
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"SingleValue?: "+onlySingleValue+"");
            CheckResult result;
            if (onlySingleValue) {
                result=docService.xmlChecks(user, request, xmlform, dataSingle, el);
                if (!result.isPassed()){
                    PostResult res=new PostResult("ERROR");
                    res.setRet(result);
                    return res;
                }
                dataSingle=docService.fixParametersSingle(user, request, xmlform, dataSingle, el);
                docService.updateElementMetaData(user, elId, dataSingle);
            }else {
                result=docService.xmlChecks(user, request, xmlform, data, el);
                if (!result.isPassed()){
                    PostResult res=new PostResult("ERROR");
                    res.setRet(result);
                    return res;
                }
                data=docService.fixParameters(user, request, xmlform, data, el);
                docService.updateElementMetaDataArray(user, elId, data);
            }
        } catch (Exception e) {
            Logger.getLogger(this.getClass()).error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
            PostResult res=new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            return res;
        }
        elementIdxUpdate(docService.getElement(elId), true);
        PostResult res=new PostResult("OK");
        res.setRet(elId);
        return res;
    }

    @RequestMapping(value="/rest/documents/xml/save/{xmlform}", method = RequestMethod.POST)
    public @ResponseBody PostResult xmlSaveElement(@PathVariable(value = "xmlform") String xmlform, HttpServletRequest request, HttpServletResponse response) throws RestException, ParserConfigurationException, SAXException, IOException {

        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        HashMap<String, String[]> data=new HashMap<String, String[]>();
        HashMap<String, String> dataSingle=new HashMap<String, String>();
        Enumeration paramNames = request.getParameterNames();
        boolean onlySingleValue=true;
        while (paramNames.hasMoreElements()){
            String paramName= (String) paramNames.nextElement();
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Trovato: "+paramName+": "+request.getParameter(paramName));
            String[] values=request.getParameterValues(paramName);
            String paramNameMultiple=paramName.replaceAll("\\[\\]", "");
            if (values.length>1){
                 onlySingleValue=false;
            }else {
                 dataSingle.put(paramNameMultiple,request.getParameter(paramName));
            }
            data.put(paramNameMultiple,request.getParameterValues(paramName));
        }
        Element parent=null;
        Form form=docService.loadXmlForm(xmlform);
        ElementType elType = docService.getDocDefinitionByName(form.getObject());
        if (data.containsKey("parentId") && data.get("parentId")!=null){
            parent=docService.getElement(Long.parseLong((String) dataSingle.get("parentId")));
            data.remove("parentId");
        }
        byte[] file=null;
        String fileName=null;
        Long fileSize=null;
        if (elType.isHasFileAttached() && request instanceof MultipartHttpServletRequest){
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Sono qui!!!!! - MultipartHttpServletRequest - ");
            MultipartFile mfile = ((MultipartHttpServletRequest) request).getFile("file");
            file=mfile.getBytes();
            fileName=mfile.getOriginalFilename();
            fileSize=mfile.getSize();
        }
        String version="";
        if (request.getParameter("version")!=null) {
            version=request.getParameter("version");
            if(version.equals("auto")){
                version="1";
            }
        }
        String date="";
        if (request.getParameter("data")!=null) date=request.getParameter("data");
        String note="";
        if (request.getParameter("note")!=null) note=request.getParameter("note");
        String autore="";
        if (request.getParameter("autore")!=null) autore=request.getParameter("autore");
        try {
            Element el=null;
            CheckResult result;
            if (onlySingleValue) {
                result=docService.xmlChecks(user, request, xmlform, dataSingle, el);
                if (!result.isPassed()){
                    PostResult res=new PostResult("ERROR");
                    res.setRet(result);
                    return res;
                }
                dataSingle=docService.fixParametersSingle(user, request, xmlform, dataSingle, el);
                el = docService.saveElement(user, elType, dataSingle, file, fileName, fileSize, version, date, note, autore, parent);
            }else {
                result=docService.xmlChecks(user, request, xmlform, data, el);
                if (!result.isPassed()){
                    PostResult res=new PostResult("ERROR");
                    res.setRet(result);
                    return res;
                }
                data=docService.fixParameters(user, request, xmlform, data, el);
                el = docService.saveElementArray(user, elType, data, file, fileName, fileSize, version, date, note, autore, parent);
            }
            elementIdxUpdate(el, true);
            PostResult res=new PostResult("OK");
            res.setRet(el.getId());
            res.setRedirect(ControllerHandler.getBaseUrl(request)+"/app/documents/detail/"+el.getId());
            return res;
        } catch (RestException e) {
            Logger.getLogger(this.getClass()).error(e.getMessage(), e);
            PostResult res=new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            res.setErrorCode(e.getCode());
            return res;
        }
    }

    @RequestMapping(value="/rest/documents/getelementidstudio/{elementId}", method= RequestMethod.GET)
    public @ResponseBody
    PostResult getElementIdStudio(@PathVariable(value = "elementId") String elementId) throws DocumentException, IOException {
        try {
            String idStudio = docService.getElementIdStudio(elementId);
            PostResult res= new PostResult("OK");
            res.setRet(idStudio);
            return res;
        } catch (Exception e) {
            Logger.getLogger(this.getClass()).error(e.getMessage(), e);
            PostResult res=new PostResult("ERROR");
            return res;
        }
    }


    @RequestMapping(value = "/rest/documents/zipUpload/{parentId}/{typeId}", method = RequestMethod.POST)
    public @ResponseBody
    PostResult uploadZip(
            @PathVariable(value = "parentId") Long parentId,
            @PathVariable(value = "typeId") String typeId,
            HttpServletRequest request) throws RestException, IOException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        Element el = docService.getElement(parentId);
        boolean elTypeFound = false;
        for (ElementType elType : el.getType().getAllowedChilds()) {
            if (elType.getTypeId().toUpperCase().equals(typeId.toUpperCase())) {
                elTypeFound = true;
                if (elType.isHasFileAttached() && request instanceof MultipartHttpServletRequest) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Sono qui!!!!! - MultipartHttpServletRequest - ");
                    MultipartFile mfile = ((MultipartHttpServletRequest) request).getFile("file");
                    ZipInputStream zis = new ZipInputStream(mfile.getInputStream());
                    LinkedList<String> files = new LinkedList<String>();
                    String destination = System.getProperty("java.io.tmpdir") + "/" + request.getSession().getId() + ".zip";
                    Logger.getLogger(this.getClass()).debug("Salvo il file nella cartella temporanea "+destination);
                    java.io.File file = new java.io.File(destination);
                    mfile.transferTo(file);
                    ZipEntry zipEntry = zis.getNextEntry();
                    while (zipEntry != null) {
                        files.add(zipEntry.getName());
                        zipEntry = zis.getNextEntry();
                    }
                    zis.closeEntry();
                    zis.close();
                    PostResult res = new PostResult("OK");
                    HashMap<String, Object> results = new HashMap<>();
                    results.put("files", files);
                    results.put("sessionId", request.getSession().getId());
                    res.setResultMap(results);
                    return res;
                } else {
                    return new PostResult("TYPE_NOT_FOUND");
                }
            }
        }
        if (!elTypeFound) {
            return new PostResult("TYPE_NOT_FOUND");
        }
        return null;
    }

    @RequestMapping(value = "/rest/documents/zipEntry/{parentId}/{typeId}", method = RequestMethod.POST)
    protected @ResponseBody
    PostResult createChildFromZipEntry(
            @PathVariable(value = "parentId") Long parentId,
            @PathVariable(value = "typeId") String typeId,
            HttpServletRequest request
    ) throws IOException {
        HashMap<String, String[]> data = new HashMap<String, String[]>();
        HashMap<String, String> dataSingle = new HashMap<String, String>();
        Enumeration paramNames = request.getParameterNames();
        boolean onlySingleValue = true;
        Element parent = docService.getElement(parentId);
        ElementType elType = null;
        for (ElementType elT : parent.getType().getAllowedChilds()) {
            if (elT.getTypeId().toUpperCase().equals(typeId.toUpperCase())) {
                elType = elT;
            }
        }
        byte[] file = null;
        String fileName = null;
        Long fileSize = null;
        while (paramNames.hasMoreElements()) {
            String paramName = (String) paramNames.nextElement();
            if (paramName.equals("zipEntryName")) {
                Logger.getLogger(this.getClass()).debug("### - ZipEntry - ["+request.getParameter(paramName)+"]###");
                String destination = System.getProperty("java.io.tmpdir") + "/" + request.getSession().getId() + ".zip";

                java.io.FileInputStream fis = new FileInputStream(destination);
                ZipInputStream zis = new ZipInputStream(fis);
                ZipEntry zipEntry = zis.getNextEntry();
                while (zipEntry != null) {
                    Logger.getLogger(this.getClass()).debug("### - ZipEntry -cycle ["+zipEntry.getName()+"] - ["+request.getParameter(paramName)+"]###");

                    if (zipEntry.getName().equals(request.getParameter(paramName))) {
                        Logger.getLogger(this.getClass()).debug("### - ZipEntry - trovato file  - ###");
                        byte[] buffer = new byte[1024];
                        ByteArrayOutputStream bos = new ByteArrayOutputStream();
                        fileName = zipEntry.getName();
                        fileSize = zipEntry.getSize();
                        int len;
                        while ((len = zis.read(buffer)) > 0) {
                            bos.write(buffer, 0, len);
                        }
                        bos.close();
                        file = bos.toByteArray();

                        Logger.getLogger(this.getClass()).debug("### - ZipEntry - trovato file dimensione array "+file.length+"  - ###");
                    }
                    zipEntry = zis.getNextEntry();
                }
                zis.closeEntry();
                zis.close();
            } else {
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Trovato: "+paramName+": "+request.getParameter(paramName));
                String[] values = request.getParameterValues(paramName);
                String paramNameMultiple = paramName.replaceAll("\\[\\]", "");
                if (values.length > 1) {
                    onlySingleValue = false;
                } else {
                    dataSingle.put(paramNameMultiple, request.getParameter(paramName));
                }
                data.put(paramNameMultiple, request.getParameterValues(paramName));
            }
        }

        if (data.containsKey("parentId") && data.get("parentId") != null) {
            parent = docService.getElement(Long.parseLong((String) dataSingle.get("parentId")));
            data.remove("parentId");
        }

        String version = "";
        if (request.getParameter("version") != null) {
            version = request.getParameter("version");
            if (version.equals("auto")) {
                version = "1";
            }
        }
        String date = "";
        if (request.getParameter("data") != null) date = request.getParameter("data");
        String note = "";
        if (request.getParameter("note") != null) note = request.getParameter("note");
        String autore = "";
        if (request.getParameter("autore") != null) autore = request.getParameter("autore");
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        try {
            Element el = null;
            if (onlySingleValue) {
                el = docService.saveElement(user, elType, dataSingle, file, fileName, fileSize, version, date, note, autore, parent);
            } else {
                el = docService.saveElementArray(user, elType, data, file, fileName, fileSize, version, date, note, autore, parent);
            }
            elementIdxUpdate(el, true);
            PostResult res = new PostResult("OK");
            res.setRet(el.getId());
            res.setRedirect(ControllerHandler.getBaseUrl(request) + "/app/documents/detail/" + el.getId());
            return res;
        } catch (RestException e) {
            log.error(e.getMessage(), e);
            PostResult res = new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            res.setErrorCode(e.getCode());
            return res;
        }
    }


    /**
     * Restituisce la lista delle opzioni per il campo idField
     * @param idField
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     */
    @RequestMapping(value="/rest/documents/getAvailableOptions/{idField}", method= RequestMethod.GET)
    public @ResponseBody
    HashMap<String,String> getAvailableOptions(@PathVariable(value = "idField") Long idField, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        String term=request.getParameter("term");
        if (term == null){
            term = "";
        }
        term = term.trim();
        LinkedHashMap<String,String> retval = new LinkedHashMap<>();
        HashMap<String,String> els=docService.getFieldsValues(idField, user, null);
        for (String k:els.keySet()){
            String val = els.get(k);
            if (val != null && val.toLowerCase().contains(term.toLowerCase())){
                retval.put(k,val);
            }
        }
        return retval;
    }


    @RequestMapping(value="/rest/documents/emechanges_center_id/{emeId}/{centroId}", method = RequestMethod.GET)
    public @ResponseBody List<AuditJSON> getEmeChangesEmeIdCentroId(@PathVariable(value = "emeId") Long emeId, @PathVariable(value = "centroId") Long centroId) throws RestException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Long emeSessionId = 0L;
        try {
            emeSessionId = docService.getEmendamentoSessionId(user, emeId, centroId);
        }catch (AxmrGenericException ex){
            log.error(ex.getMessage(),ex);
            return new LinkedList<AuditJSON>();
        }
        return getEmeChanges(emeSessionId);
    }

    @RequestMapping(value="/rest/documents/emechanges/{emeSessionId}", method = RequestMethod.GET)
    public @ResponseBody List<AuditJSON> getEmeChanges(@PathVariable(value = "emeSessionId") Long emeSessionId) throws RestException {
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        List<AuditJSON> ret=new LinkedList<AuditJSON>();
        try {
            EmendamentoSession emeSession = docService.getEmendamentoSession(emeSessionId);
            if (emeSession != null) {
                List<Element> changedEls = docService.getElementsFromEmeSession(emeSessionId, user.getUsername());
                for (Element el : changedEls) {
                    //Element el = docService.getElement(elementId);
                    List<ElementMetadata> changes = docService.getEmendamentoChanges(emeSessionId, el);

                    LinkedHashMap<String, ElementMetadata> metadataDiz = new LinkedHashMap<String, ElementMetadata>();
                    for (ElementMetadata emd : el.getData()) {
                        metadataDiz.put(emd.getTemplateName() + "_" + emd.getFieldName(), emd);
                    }

                    for (ElementMetadata cemd : changes) {
                        String mdkey = cemd.getTemplateName() + "_" + cemd.getFieldName();
                        ElementMetadata orig = metadataDiz.get(mdkey);
                        List<Object> origVals = new LinkedList<Object>();
                        if (orig != null) {
                            origVals = orig.getVals();
                        }
                        List<Object> destVals = cemd.getVals();
                        boolean toShow = false;
                        if (origVals.size() != destVals.size()) {
                            toShow = true;
                        } else {
                            //Ciclo tutti i valori
                            for (int i = 0; i < origVals.size(); i++) {
                                if (!origVals.get(i).equals(destVals.get(i))) {
                                    toShow = true;
                                    break;
                                }
                            }
                        }
                        if (toShow) {
                            //Aggiungo audit di modifica
                            AuditMetadata amd = new AuditMetadata();
                            //Indicazione dell'oggetto modificato inserita in action
                            amd.setAction(el.getTypeName()+" - "+el.getId()+"<br/>"+el.getTitleString());
                            amd.setUsername(emeSession.getUserid());
                            amd.setField(cemd.getField());
                            amd.setTemplate(cemd.getTemplate());
                            amd.setModDt(cemd.getEmeAction().getActionDt());
                            LinkedList<AuditValue> avalList = new LinkedList<AuditValue>();
                            if (orig != null) {
                                for (ElementMetadataValue emdval : orig.getValues()) {
                                    AuditValue av = new AuditValue();
                                    av.setOld(true);
                                    av.setCode(emdval.getCode());
                                    av.setDate(emdval.getDate());
                                    av.setDecode(emdval.getDecode());
                                    av.setElement_link(emdval.getElement_link());
                                    av.setLongTextValue(emdval.getLongTextValue());
                                    av.setTextValue(emdval.getTextValue());
                                    av.setId(emdval.getId());
                                    avalList.add(av);
                                }
                            }
                            for (ElementMetadataValue emdval : cemd.getValues()) {
                                AuditValue av = new AuditValue();
                                av.setOld(false);
                                av.setCode(emdval.getCode());
                                av.setDate(emdval.getDate());
                                av.setDecode(emdval.getDecode());
                                av.setElement_link(emdval.getElement_link());
                                av.setLongTextValue(emdval.getLongTextValue());
                                av.setTextValue(emdval.getTextValue());
                                av.setId(emdval.getId());
                                avalList.add(av);
                            }
                            amd.setValues(avalList);
                            ret.add(new AuditJSON(amd, uService));
                        }
                    }
                }
            }
        }catch (AxmrGenericException ex){
            log.error(ex.getMessage(),ex);
            return new LinkedList<AuditJSON>();
        }
        return ret;
    }


    @RequestMapping(value = "/rest/documents/updateFileInfo/{elementId}", method = RequestMethod.POST)
    protected @ResponseBody PostResult updateFileInfo(
            @PathVariable(value="elementId") Long elementId,
            HttpServletRequest request
    ) throws IOException {
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        try {
            Element el=null;
            el=docService.getElement(elementId);
            String version="";
            if (request.getParameter("version")!=null) {
                version=request.getParameter("version");
                if(version.equals("auto")){
                    version="1";
                }
            }
            String date=null;
            if (request.getParameter("data")!=null) date=request.getParameter("data");
            String note=null;
            if (request.getParameter("note")!=null) note=request.getParameter("note");
            String autore=null;
            if (request.getParameter("autore")!=null) autore=request.getParameter("autore");
            docService.updateFileInfo(el, autore, note, date, version);
            elementIdxUpdate(el, true);
            PostResult res=new PostResult("OK");
            res.setRet(el.getId());
            res.setRedirect(ControllerHandler.getBaseUrl(request)+"/app/documents/detail/"+el.getId());
            return res;
        } catch (RestException e) {
            log.error(e.getMessage(),e);
            PostResult res=new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            res.setErrorCode(e.getCode());
            return res;
        }
    }

    @RequestMapping(value="/rest/documents/getIdCentroFromAnyChild/{childId}", method = RequestMethod.GET)
    public @ResponseBody String getIdCentroFromAnyChild(@PathVariable(value = "childId") String childId) throws RestException {
        String retval = "";
        try {
            retval = docService.getIdCentroFromAnyChild(childId);
        } catch (Exception e){
            log.error(e.getMessage(),e);
        }
        return retval;
    }

}
