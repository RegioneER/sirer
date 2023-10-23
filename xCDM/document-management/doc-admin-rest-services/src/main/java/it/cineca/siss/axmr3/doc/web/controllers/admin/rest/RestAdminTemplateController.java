package it.cineca.siss.axmr3.doc.web.controllers.admin.rest;


import it.cineca.siss.axmr3.common.mvc.handlers.ControllerHandler;
import it.cineca.siss.axmr3.doc.entities.MetadataField;
import it.cineca.siss.axmr3.doc.entities.MetadataTemplate;
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
import java.util.Collection;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 10/09/13
 * Time: 11.37
 * To change this template use File | Settings | File Templates.
 */
@Controller
@RequestMapping(value = "/rest/admin/template/")
public class RestAdminTemplateController {

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
     * @param id
     * @param request
     * @param response
     * @return
     */
    @RequestMapping(value = "get/{id}", method = RequestMethod.GET)
    public @ResponseBody
    MetadataTemplate getTemplate(@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response) {
        return admService.getMd(id);
    }

    /**
     * Restituisce tutti i template definiti
     * @param request
     * @param response
     * @return
     */
    @RequestMapping(value = "getAll", method = RequestMethod.GET)
    public @ResponseBody
    List<MetadataTemplate> getTemplates(HttpServletRequest request, HttpServletResponse response) {
        return admService.getMds();
    }

    /**
     * Salva il template
     * @param request
     * @param response
     * @return
     * @throws java.io.IOException
     * @throws org.apache.commons.fileupload.FileUploadException
     */
    @RequestMapping(value = "save", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult saveTemplate(HttpServletRequest request, HttpServletResponse response) throws IOException, FileUploadException {
        String name = request.getParameter("name");
        String desc = request.getParameter("description");
        boolean calendarized = false;
        String calendarName = "";
        Long id = null;
        if (request.getParameter("id") != null && !request.getParameter("id").isEmpty()) {
            id = Long.parseLong(request.getParameter("id"));
        }
        boolean auditable = false;
        if (request.getParameter("auditable") != null && !request.getParameter("auditable").isEmpty()) {
            auditable = true;
        }
        boolean wfManaged = false;
        if (request.getParameter("wfManaged") != null && !request.getParameter("wfManaged").isEmpty()) {
            wfManaged = true;
        }
        Long startDateId = null;
        Long endDateId = null;
        if (request.getParameter("calendarized") != null && !request.getParameter("calendarized").isEmpty()) {
            calendarized = true;
            calendarName = request.getParameter("calendarName");
            if (request.getParameter("startDateId") != null && !request.getParameter("startDateId").isEmpty())
                startDateId = Long.parseLong(request.getParameter("startDateId"));
            if (request.getParameter("endDateId") != null && !request.getParameter("endDateId").isEmpty())
                endDateId = Long.parseLong(request.getParameter("endDateId"));
        }
        String calendarColor = "";
        if (request.getParameter("calendarColor") != null && !request.getParameter("calendarColor").isEmpty())
            calendarColor = request.getParameter("calendarColor");
        MetadataTemplate t = null;
        try {
            t = admService.saveTemplate(name, desc, auditable, wfManaged, calendarized, calendarName, calendarColor, startDateId, endDateId, id);
        } catch (RestException e) {
            return new PostResult(e);
        }
        PostResult res = new PostResult("OK");
        res.setRet(t.getId().toString());
        res.setRedirect(ControllerHandler.getBaseUrl(request) + "/app/admin/editTemplate/" + t.getId());
        return res;
    }

    /**
     * Elimina il template
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
    PostResult deleteTemplate(@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response) throws IOException, FileUploadException {
        try {
            admService.deleteTemplate(id);
        } catch (RestException e) {
            return new PostResult(e);
        }
        return new PostResult("OK");
    }

    @RequestMapping(value = "{id}/field/{idField}/moveUp", method = RequestMethod.GET)
    public @ResponseBody
    PostResult moveUp(@PathVariable(value = "id") Long id, @PathVariable(value = "idField") Long idField) {
        try {
            admService.moveFieldUp(admService.getMd(id), idField);
        } catch (RestException e) {
            return new PostResult(e);
        }
        return new PostResult("OK");
    }

    @RequestMapping(value = "{id}/field/{idField}/moveDown", method = RequestMethod.GET)
    public @ResponseBody
    PostResult moveDown(@PathVariable(value = "id") Long id, @PathVariable(value = "idField") Long idField) {
        try {
            admService.moveFieldDown(admService.getMd(id), idField);
        } catch (RestException e) {
            return new PostResult(e);
        }
        return new PostResult("OK");
    }

    @RequestMapping(value = "{id}/field/{idField}/moveTop", method = RequestMethod.GET)
    public @ResponseBody
    PostResult moveTop(@PathVariable(value = "id") Long id, @PathVariable(value = "idField") Long idField) {
        try {
            admService.moveFieldTop(admService.getMd(id), idField);
        } catch (RestException e) {
            return new PostResult(e);
        }
        return new PostResult("OK");
    }

    @RequestMapping(value = "{id}/field/{idField}/moveBottom", method = RequestMethod.GET)
    public @ResponseBody
    PostResult moveBottom(@PathVariable(value = "id") Long id, @PathVariable(value = "idField") Long idField) {
        try {
            admService.moveFieldBottom(admService.getMd(id), idField);
        } catch (RestException e) {
            return new PostResult(e);
        }
        return new PostResult("OK");
    }


    /**
     * Salva il campo metadato
     * @param id
     * @param request
     *      parametri post:
     *                 name nome del campo
     *                 type tipologia(TEXTBOX, TEXTAREA, DATE, SELECT, RADIO, CHECKBOX, EXT_DICTIONARY, ELEMENT_LINK")
     *                 externalDictionary link dizionario
     *                 addFilterFields campi di filtro per dizionario
     *                 typefilters tipologia di filtri
     *                 availableValues valori possibili
     *                 macro macro specifica
     *                 macroView macro di visualizzazione ad-hoc
     *                 size lunghezza campo
     *                 mandatory obbligatorietà (true/false)
     *                 baseNameOra boooo
     *                 id
     * @param response
     * @return
     */
    @RequestMapping(value = "{id}/saveField", method = RequestMethod.POST)
    public @ResponseBody
    PostResult saveField(@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response) {
        String name = request.getParameter("name");
        String type = request.getParameter("type");
        String externalDictionary = "";
        String addFilterFields = "";
        if (request.getParameter("externalDictionary") != null && !request.getParameter("externalDictionary").isEmpty()) {
            externalDictionary = request.getParameter("externalDictionary");
        }
        if (request.getParameter("addFilterFields") != null && !request.getParameter("addFilterFields").isEmpty()) {
            addFilterFields = request.getParameter("addFilterFields");
        }
        String typefilters = request.getParameter("typefilters");
        String availableValues = "";
        if (request.getParameter("availableValues") != null && !request.getParameter("availableValues").isEmpty()) {
            availableValues = request.getParameter("availableValues");
        }
        String macro = "";
        if (request.getParameter("macro") != null && !request.getParameter("macro").isEmpty()) {
            macro = request.getParameter("macro");
        }
        String macroView = "";
        if (request.getParameter("macroView") != null && !request.getParameter("macroView").isEmpty()) {
            macroView = request.getParameter("macroView");
        }
        Integer size = null;
        if (request.getParameter("size") != null && !request.getParameter("size").isEmpty()) {
            size = Integer.parseInt(request.getParameter("size"));
        }
        boolean mandatory = false;
        if (request.getParameter("mandatory") != null && !request.getParameter("mandatory").isEmpty()) {
            it.cineca.siss.axmr3.log.Log.info(getClass(), "Trovo il parametro mandatory");
            mandatory = true;
        }
        String baseNameOra = "";
        if (request.getParameter("baseNameOra") != null && !request.getParameter("baseNameOra").isEmpty()) {
            baseNameOra = request.getParameter("baseNameOra");
        }
        String regexpCheck = "";
        if (request.getParameter("regexpCheck") != null && !request.getParameter("regexpCheck").isEmpty()) {
            regexpCheck = request.getParameter("regexpCheck");
        }
        Long idField = null;
        if (request.getParameter("id") != null && !request.getParameter("id").isEmpty()) {
            idField = Long.parseLong(request.getParameter("id"));
        }
        try {
            admService.addField(admService.getMd(id), name, type, mandatory, typefilters, availableValues, externalDictionary, addFilterFields, idField, size, macro, macroView, baseNameOra, regexpCheck);
        } catch (RestException e) {
            return new PostResult(e);
        }
        return new PostResult("OK");
    }

    /**
     * Restituisce i campi metadati presenti nel template id
     * @param id
     * @param request
     * @param response
     * @return
     */
    @RequestMapping(value = "{id}/getFields", method = RequestMethod.GET)
    public @ResponseBody
    Collection<MetadataField> getFields(@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response) {
        MetadataTemplate t = admService.getMd(id);
        return t.getFields();
    }

    /**
     * Restituisce i campi metadati presenti nel template id
     * @param id
     * @param request
     * @param response
     * @return
     */
    @RequestMapping(value = "{id}/updateFieldsOra", method = RequestMethod.GET)
    public @ResponseBody
    Collection<MetadataField> updateFieldsOra(@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response) {
        MetadataTemplate t = admService.getMd(id);
        Collection<MetadataField> fields = t.getFields();
        for (MetadataField field : fields) {

        }


        return fields;
    }

    /**
     * Restituisce il campo metadato del template id e metadato idField
     * @param id
     * @param idField
     * @param request
     * @param response
     * @return
     */
    @RequestMapping(value = "{id}/getField/{idField}", method = RequestMethod.GET)
    public @ResponseBody
    MetadataField getField(@PathVariable(value = "id") Long id, @PathVariable(value = "idField") Long idField, HttpServletRequest request, HttpServletResponse response) {
        MetadataTemplate t = admService.getMd(id);
        MetadataField f = null;
        for (MetadataField f1 : t.getFields()) {
            if (f1.getId().equals(idField)) f = f1;
        }
        return f;
    }

    /**
     * Elimina il campo metadato
     * @param id
     * @param idField
     * @param request
     * @param response
     * @return
     */
    @RequestMapping(value = "{id}/deleteField/{idField}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult deleteField(@PathVariable(value = "id") Long id, @PathVariable(value = "idField") Long idField, HttpServletRequest request, HttpServletResponse response) {
        MetadataTemplate t = admService.getMd(id);
        try {
            admService.deleteField(t, idField);
        } catch (RestException e) {
            return new PostResult(e);
        }
        return new PostResult("OK");
    }

    @RequestMapping(value = "/searchTemplate", method = RequestMethod.GET)
    public @ResponseBody
    List<MetadataTemplate> searchTemplate(HttpServletRequest request) {
        return admService.searchTemplate(request.getParameter("term"));
    }

    @RequestMapping(value = "/searchTemplateField", method = RequestMethod.GET)
    public @ResponseBody
    List<MetadataField> searchTemplateField(HttpServletRequest request) {
        return admService.searchTemplateField(request.getParameter("term"));
    }

}
