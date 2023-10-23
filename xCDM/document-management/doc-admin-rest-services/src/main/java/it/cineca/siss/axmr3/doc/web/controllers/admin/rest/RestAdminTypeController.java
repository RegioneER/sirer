package it.cineca.siss.axmr3.doc.web.controllers.admin.rest;

import it.cineca.siss.axmr3.common.mvc.handlers.ControllerHandler;
import it.cineca.siss.axmr3.doc.acl.Policy;
import it.cineca.siss.axmr3.doc.acl.TemplatePolicy;
import it.cineca.siss.axmr3.doc.entities.*;
import it.cineca.siss.axmr3.doc.json.ElementTypeTreeJSON;
import it.cineca.siss.axmr3.doc.types.PostResult;
import it.cineca.siss.axmr3.doc.web.exceptions.RestException;
import it.cineca.siss.axmr3.doc.web.services.AdminService;
import it.cineca.siss.axmr3.exceptions.AxmrGenericException;
import org.apache.commons.fileupload.FileUploadException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.multipart.MultipartHttpServletRequest;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Arrays;
import java.util.Collection;
import java.util.LinkedList;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 10/09/13
 * Time: 11.29
 * To change this template use File | Settings | File Templates.
 */
@Controller
@RequestMapping(value = "/rest/admin/type/")
public class RestAdminTypeController {

    @Autowired
    protected AdminService admService;

    public AdminService getAdmService() {
        return admService;
    }

    public void setAdmService(AdminService admService) {
        this.admService = admService;
    }

    @RequestMapping(value = "{typeId}/acl/get/{aclId}", method = RequestMethod.GET)
    public
    @ResponseBody
    Acl getAcl(@PathVariable(value = "typeId") Long typeId, @PathVariable(value = "aclId") Long aclId, HttpServletRequest request, HttpServletResponse response) {
        return admService.getAcl(typeId, aclId);
    }

    @RequestMapping(value = "{typeId}/acl/getAll", method = RequestMethod.GET)
    public
    @ResponseBody
    List<Acl> getAcls(@PathVariable(value = "typeId") Long typeId, HttpServletRequest request, HttpServletResponse response) {
        ElementType t = admService.getElementType(typeId);
        return (List<Acl>) t.getAcls();
    }

    @RequestMapping(value = "{typeId}/acl/save", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult saveACL(@PathVariable(value = "typeId") Long typeId, HttpServletRequest request, HttpServletResponse response) throws IOException, FileUploadException {
        Long id = null;
        if (request.getParameter("id") != null && !request.getParameter("id").isEmpty()) {
            id = Long.parseLong(request.getParameter("id"));
        }
        String detailTemplate = null;
        if (request.getParameter("detailTemplate") != null && !request.getParameter("detailTemplate").isEmpty())
            detailTemplate = request.getParameter("detailTemplate");
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
            pp = admService.getPolicy(Long.parseLong(request.getParameter("policy")));
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
            admService.saveAcl(typeId, groups, users, pol, pp, detailTemplate, templateRef, id);
        } catch (RestException e) {
            return new PostResult(e);
        }
        PostResult res = new PostResult("OK");
        return res;
    }


    @RequestMapping(value = "{typeId}/acl/delete/{id}", method = RequestMethod.GET)
    public
    @ResponseBody
    PostResult deleteACL(@PathVariable(value = "typeId") Long typeId, @PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response) throws IOException, FileUploadException {
        try {
            admService.deleteAcl(typeId, id);
        } catch (RestException e) {
            return new PostResult(e);
        }
        return new PostResult("OK");
    }

    /**
     * Restituisce l'oggetto ElementType identificato da id
     *
     * @param id
     * @param request
     * @param response
     * @return
     */
    @RequestMapping(value = "get/{id}", method = RequestMethod.GET)
    public
    @ResponseBody
    ElementType getElement(@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response) {
        return admService.getElementType(id);
    }

    /**
     * Restituisce l'oggetto ElementType identificato da typeId
     *
     * @param typeId
     * @param request
     * @param response
     * @return
     */
    @RequestMapping(value = "getByTypeId/{typeId}", method = RequestMethod.GET)
    public
    @ResponseBody
    ElementType getElementByTypeId(@PathVariable(value = "typeId") String typeId, HttpServletRequest request, HttpServletResponse response) {
        return admService.getElementTypeByTypeId(typeId).get(0);
    }

    /**
     * Restituisce tutte le tipologie di elementi presenti
     *
     * @param request
     * @param response
     * @return
     */
    @RequestMapping(value = "getAll", method = RequestMethod.GET)
    public
    @ResponseBody
    List<ElementType> getTypes(HttpServletRequest request, HttpServletResponse response) {
        return admService.getTypes();
    }

    @RequestMapping(value = "getAllTree", method = RequestMethod.GET)
    public
    @ResponseBody
    List<ElementTypeTreeJSON> getTypesTree(HttpServletRequest request, HttpServletResponse response) {
        List<ElementType> all = admService.getTypes();
        LinkedList<ElementTypeTreeJSON> ret = new LinkedList<ElementTypeTreeJSON>();
        for(ElementType currType:all){
            ret.add(new ElementTypeTreeJSON(currType));
        }
        return ret;
    }


    /**
     * Salva la tipologia di elemento
     *
     * @param request
     * @param response
     * @return
     * @throws IOException
     * @throws FileUploadException
     */
    @RequestMapping(value = "save", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult saveType(HttpServletRequest request, HttpServletResponse response) throws IOException, FileUploadException {
        boolean isContainer = false;
        if (request.getParameter("container") != null && !request.getParameter("container").isEmpty()) {
            isContainer = true;
        }
        Long id = null;
        if (request.getParameter("id") != null && !request.getParameter("id").isEmpty()) {
            id = Long.parseLong(request.getParameter("id"));
        }
        boolean hasFile = false;
        if (request.getParameter("hasFile") != null && !request.getParameter("hasFile").isEmpty()) {
            hasFile = true;
        }
        boolean noFileinfo = false;
        if (request.getParameter("noFileinfo") != null && !request.getParameter("noFileinfo").isEmpty()) {
            noFileinfo = true;
        }
        boolean selfRecursive = false;
        if (request.getParameter("selfRecursive") != null && !request.getParameter("selfRecursive").isEmpty()) {
            selfRecursive = true;
        }
        boolean rootAble = false;
        if (request.getParameter("rootAble") != null && !request.getParameter("rootAble").isEmpty()) {
            rootAble = true;
        }
        boolean checkOutEnabled = false;
        if (request.getParameter("checkOutEnabled") != null && !request.getParameter("checkOutEnabled").isEmpty()) {
            checkOutEnabled = true;
        }
        boolean draftable = false;
        if (request.getParameter("draftable") != null && !request.getParameter("draftable").isEmpty()) {
            draftable = true;
        }
        boolean fileOnFs=false;
        if (request.getParameter("fileOnFS") != null && !request.getParameter("fileOnFS").isEmpty()) {
            fileOnFs = true;
        }
        byte[] img = null;
        String typeId = request.getParameter("typeId");
        if (request instanceof MultipartHttpServletRequest) {
            MultipartFile imgFile = ((MultipartHttpServletRequest) request).getFile("img");
            if (imgFile != null) img = imgFile.getBytes();
        }
        String templateRow = "";
        String templateDetail = "";
        String templateForm = "";
        String hashBack = "";
        Long groupUpLevel = new Long(0);
        Long titleField = null;
        if (request.getParameter("ftlRowTemplate") != null && !request.getParameter("ftlRowTemplate").isEmpty()) {
            templateRow = request.getParameter("ftlRowTemplate");
        }
        if (request.getParameter("ftlDetailTemplate") != null && !request.getParameter("ftlDetailTemplate").isEmpty()) {
            templateDetail = request.getParameter("ftlDetailTemplate");
        }
        if (request.getParameter("ftlFormTemplate") != null && !request.getParameter("ftlFormTemplate").isEmpty()) {
            templateForm = request.getParameter("ftlFormTemplate");
        }
        if (request.getParameter("hashBack") != null && !request.getParameter("hashBack").isEmpty()) {
            hashBack = request.getParameter("hashBack");
        }
        if (request.getParameter("groupUpLevel") != null && !request.getParameter("groupUpLevel").isEmpty()) {
            groupUpLevel = Long.parseLong(request.getParameter("groupUpLevel"));
        }
        if (request.getParameter("titleField") != null && !request.getParameter("titleField").isEmpty()) {
            titleField = Long.parseLong(request.getParameter("titleField"));
        }
        String titleRegex = null;
        if (request.getParameter("titleRegex") != null && !request.getParameter("titleRegex").isEmpty()) {
            titleRegex = request.getParameter("titleRegex");
        }
        boolean searchable = false;
        if (request.getParameter("searchable") != null && !request.getParameter("searchable").isEmpty()) {
            searchable = true;
        }
        boolean sortable = false;
        if (request.getParameter("sortable") != null && !request.getParameter("sortable").isEmpty()) {
            sortable = true;
        }
        ElementType el = null;
        try {
            el = admService.saveElementType(typeId, isContainer, hasFile, selfRecursive, rootAble, checkOutEnabled, img, id, templateRow, templateDetail, templateForm, titleField, draftable, searchable, titleRegex, noFileinfo, hashBack, groupUpLevel, sortable, fileOnFs);
        } catch (RestException e) {
            return new PostResult(e);
        }
        PostResult ret = new PostResult("OK");
        ret.setRet(el.getId());
        ret.setRedirect(ControllerHandler.getBaseUrl(request) + "/app/admin/editType/" + el.getId());
        return ret;
    }

    /**
     * Elimina l'elemento
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
    PostResult deleteType(@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response) throws IOException, FileUploadException {
        try {
            admService.deleteType(id);
        } catch (RestException e) {
            return new PostResult(e);
        }
        return new PostResult("OK");
    }

    @RequestMapping(value = "{id}/{template}/changeStatus", method = RequestMethod.GET)
    public
    @ResponseBody
    PostResult changeStatus(@PathVariable(value = "id") Long id, @PathVariable(value="template") String templateName, HttpServletRequest request, HttpServletResponse response) {
        try {
            admService.changeTemplateStatusForElement(id, templateName);
        } catch (RestException e) {
            return new PostResult(e);
        } catch (AxmrGenericException e) {
            return new PostResult(e);
        }
        return new PostResult("OK");
    }

    /**
     * Associa un template ad una tipologia di elemento
     *
     * @param id
     * @param request
     * @param response
     * @return
     */
    @RequestMapping(value = "{id}/assocTemplate", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult saveTemplate(@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response) {
        Long templateId = Long.parseLong(request.getParameter("templateId"));
        boolean enabled = false;
        if (request.getParameter("enabled") != null && request.getParameter("enabled").equals("1")) enabled = true;
        try {
            admService.assocTemplate(admService.getElementType(id), templateId, enabled);
        } catch (RestException e) {
            return new PostResult(e);
        }
        return new PostResult("OK");
    }

    /**
     * Restituisce i template associati alla tipologia di elemento id
     *
     * @param id
     * @param request
     * @param response
     * @return
     */
    @RequestMapping(value = "{id}/getTemplates", method = RequestMethod.GET)
    public
    @ResponseBody
    Collection<ElementTypeAssociatedTemplate> getTemplates(@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response) {
        ElementType t = admService.getElementType(id);
        return t.getAssociatedTemplates();
    }

    /**
     * Elimina l'associazione del template alla tipologia di elemento
     *
     * @param id
     * @param idAssoc
     * @param request
     * @param response
     * @return
     */
    @RequestMapping(value = "{id}/deAssocTemplate/{idAssoc}", method = RequestMethod.GET)
    public
    @ResponseBody
    PostResult deleteTemplate(@PathVariable(value = "id") Long id, @PathVariable(value = "idAssoc") Long idAssoc, HttpServletRequest request, HttpServletResponse response) {
        ElementType t = admService.getElementType(id);
        try {
            admService.deAssocTemplate(t, idAssoc);
        } catch (RestException e) {
            return new PostResult(e);
        }
        return new PostResult("OK");
    }

    /**
     * Aggiunge un figlio alla tipologia di elemento id
     *
     * @param id
     * @param request
     * @param response
     * @return
     */
    @RequestMapping(value = "{id}/addChild", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult addChild(@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response) {
        Long elementId = Long.parseLong(request.getParameter("elementId"));
        try {
            admService.addChild(admService.getElementType(id), elementId);
        } catch (RestException e) {
            return new PostResult(e);
        }
        return new PostResult("OK");
    }

    /**
     * Restituisce i figlie della tipologia di elemento id
     *
     * @param id
     * @param request
     * @param response
     * @return
     */
    @RequestMapping(value = "{id}/getChilds", method = RequestMethod.GET)
    public
    @ResponseBody
    Collection<ElementType> getChilds(@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response) {
        ElementType t = admService.getElementType(id);
        return t.getAllowedChilds();
    }

    /**
     * Elimina il figlio dalla tipologia di elemento
     *
     * @param id
     * @param idChild
     * @param request
     * @param response
     * @return
     */
    @RequestMapping(value = "{id}/delChild/{idChild}", method = RequestMethod.GET)
    public
    @ResponseBody
    PostResult delChild(@PathVariable(value = "id") Long id, @PathVariable(value = "idChild") Long idChild, HttpServletRequest request, HttpServletResponse response) {
        ElementType t = admService.getElementType(id);
        try {
            admService.deleteChild(t, idChild);
        } catch (RestException e) {
            return new PostResult(e);
        }
        return new PostResult("OK");
    }


    @RequestMapping(value = "{id}/assocWorkflow", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult assocWorkflow(
            @PathVariable(value = "id") Long id,
            @RequestParam(value = "enabled", defaultValue = "0", required = false) String enabled,
            @RequestParam(value = "startOnCreate", defaultValue = "0", required = false) String startOnCreate,
            @RequestParam(value = "startOnUpdate", defaultValue = "0", required = false) String startOnUpdate,
            @RequestParam(value = "startOnDelete", defaultValue = "0", required = false) String startOnDelete,
            @RequestParam(value = "wfId") String wfId) {
        boolean bEnabled = false;
        if (enabled != null && enabled.equals("1")) bEnabled = true;
        boolean bStartOnCreate = false;
        if (startOnCreate != null && startOnCreate.equals("1")) bStartOnCreate = true;
        boolean bStartOnUpdate = false;
        if (startOnUpdate != null && startOnUpdate.equals("1")) bStartOnUpdate = true;
        boolean bStartOnDelete = false;
        if (startOnDelete != null && startOnDelete.equals("1")) bStartOnDelete = true;
        try {
            admService.assocWorkflow(admService.getElementType(id), wfId, bEnabled, bStartOnCreate, bStartOnUpdate, bStartOnDelete);
        } catch (RestException e) {
            return new PostResult(e);
        }
        return new PostResult("OK");
    }

    /**
     * Restituisce i template associati alla tipologia di elemento id
     *
     * @param id
     * @param request
     * @param response
     * @return
     */
    @RequestMapping(value = "{id}/getWorkflows", method = RequestMethod.GET)
    public
    @ResponseBody
    Collection<ElementTypeAssociatedWorkflow> getWorkflows(@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response) {
        ElementType t = admService.getElementType(id);
        return t.getAssociatedWorkflows();
    }

    /**
     * Elimina l'associazione del template alla tipologia di elemento
     *
     * @param id
     * @param idAssoc
     * @param request
     * @param response
     * @return
     */
    @RequestMapping(value = "{id}/deAssocWorkflow/{idAssoc}", method = RequestMethod.GET)
    public
    @ResponseBody
    PostResult deAssocWorkflow(@PathVariable(value = "id") Long id, @PathVariable(value = "idAssoc") Long idAssoc, HttpServletRequest request, HttpServletResponse response) {
        ElementType t = admService.getElementType(id);
        try {
            admService.deAssocWorkflows(t, idAssoc);
        } catch (RestException e) {
            return new PostResult(e);
        }
        return new PostResult("OK");
    }

    @RequestMapping(value = "/searchElType", method = RequestMethod.GET)
    public
    @ResponseBody
    List<ElementType> searchElType(HttpServletRequest request) {
        return admService.searchElementType(request.getParameter("term"));
    }

    @RequestMapping(value = "{id}/template/{assocId}/acl", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult setAclToTemplate(@PathVariable(value = "id") Long id, @PathVariable(value = "assocId") Long assocId,
                                @RequestParam(value = "create", required = false, defaultValue = "0") String create,
                                @RequestParam(value = "update", required = false, defaultValue = "0") String update,
                                @RequestParam(value = "delete", required = false, defaultValue = "0") String delete,
                                @RequestParam(value = "view", required = false, defaultValue = "0") String view,
                                @RequestParam(value = "groups", required = false, defaultValue = "") String groups,
                                @RequestParam(value = "users", required = false, defaultValue = "") String users,
                                @RequestParam(value = "cuser", required = false, defaultValue = "") String cuser,
                                @RequestParam(value = "allUsers", required = false, defaultValue = "") String allUsers) {
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
            admService.setDocTypeTemplateAcl(id, assocId, pol, usersList, groupsList);
            return new PostResult("OK");
        } catch (RestException ex) {
            return new PostResult(ex);
        }
    }

    @RequestMapping(value = "{id}/template/{assocId}/acl", method = RequestMethod.GET)
    public
    @ResponseBody
    List<TemplateAcl> getTemplateAcls(@PathVariable(value = "id") Long id, @PathVariable(value = "assocId") Long assocId) {
        ElementType t = admService.getElementType(id);
        for (ElementTypeAssociatedTemplate tpl : t.getAssociatedTemplates()) {
            if (tpl.getId().equals(assocId)) return (List<TemplateAcl>) tpl.getTemplateAcls();
        }
        return new LinkedList<TemplateAcl>();
    }

    @RequestMapping(value = "{id}/template/{assocId}/acl/{aclId}", method = RequestMethod.GET)
    public
    @ResponseBody
    TemplateAcl getTemplateAcl(@PathVariable(value = "id") Long id, @PathVariable(value = "assocId") Long assocId, @PathVariable(value = "aclId") Long aclId) {
        ElementType t = admService.getElementType(id);
        for (ElementTypeAssociatedTemplate tpl : t.getAssociatedTemplates()) {
            if (tpl.getId().equals(assocId)) {
                for (TemplateAcl acl : tpl.getTemplateAcls()) {
                    if (acl.getId().equals(aclId)) return acl;
                }
            }
        }
        return null;
    }

    @RequestMapping(value = "{id}/template/{assocId}/acl/{aclId}/delete", method = RequestMethod.GET)
    public
    @ResponseBody
    PostResult deleteTemplateAcl(@PathVariable(value = "id") Long id, @PathVariable(value = "assocId") Long assocId, @PathVariable(value = "aclId") Long aclId) {
        try {
            admService.deleteTemplateAcl(id, assocId, aclId);
            return new PostResult("OK");
        } catch (RestException ex) {
            return new PostResult(ex);
        }

    }
}
