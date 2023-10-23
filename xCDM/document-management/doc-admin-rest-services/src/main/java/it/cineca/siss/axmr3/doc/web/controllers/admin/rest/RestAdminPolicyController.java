package it.cineca.siss.axmr3.doc.web.controllers.admin.rest;

import it.cineca.siss.axmr3.common.mvc.handlers.ControllerHandler;
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
 * User: Carlo
 * Date: 10/09/13
 * Time: 11.42
 * To change this template use File | Settings | File Templates.
 */
@Controller
@RequestMapping(value="/rest/admin/policy/")
public class RestAdminPolicyController {

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
    @RequestMapping(value="get/{id}", method= RequestMethod.GET)
    public @ResponseBody
    PredefinedPolicy getPolicy(@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response){
        return admService.getPolicy(id);
    }

    /**
     * Restituisce tutti i template definiti
     * @param request
     * @param response
     * @return
     */
    @RequestMapping(value="getAll", method= RequestMethod.GET)
    public @ResponseBody
    List<PredefinedPolicy> getPolicies(HttpServletRequest request, HttpServletResponse response){
        return admService.getPolicies();
    }

    /**
     * Salva il template
     * @param request
     * @param response
     * @return
     * @throws java.io.IOException
     * @throws org.apache.commons.fileupload.FileUploadException
     */
    @RequestMapping(value="save", method= RequestMethod.POST)
    public
    @ResponseBody
    PostResult savePolicy(HttpServletRequest request, HttpServletResponse response) throws IOException, FileUploadException {
        String name=request.getParameter("name");
        String desc=request.getParameter("description");
        boolean view=false;
        if (request.getParameter("view")!=null) view=true;
        boolean create=false;
        if (request.getParameter("create")!=null) create=true;
        boolean update=false;
        if (request.getParameter("update")!=null) update=true;
        boolean addComment=false;
        if (request.getParameter("addComment")!=null) addComment=true;
        boolean moderate=false;
        if (request.getParameter("moderate")!=null) moderate=true;
        boolean delete=false;
        if (request.getParameter("delete")!=null) delete=true;
        boolean changePermission=false;
        if (request.getParameter("changePermission")!=null) changePermission=true;
        boolean addChild=false;
        if (request.getParameter("addChild")!=null) addChild=true;
        boolean removeCheckOut=false;
        if (request.getParameter("removeCheckOut")!=null) removeCheckOut=true;
        boolean launchProcess=false;
        if (request.getParameter("launchProcess")!=null) launchProcess=true;
        boolean enableTemplate=false;
        if (request.getParameter("enableTemplate")!=null) enableTemplate=true;
        boolean canBrowse=false;
        if (request.getParameter("canBrowse")!=null) canBrowse=true;
        Long id=null;
        if (request.getParameter("id")!=null && !request.getParameter("id").isEmpty()){
            id=Long.parseLong(request.getParameter("id"));
        }
        PredefinedPolicy t= null;
        try {
            t = admService.savePolicy(name, desc, view, create, update, addComment, moderate, delete, changePermission, addChild, removeCheckOut,launchProcess, enableTemplate,canBrowse,id);
        } catch (RestException e) {
            return new PostResult(e);
        }
        PostResult res=new PostResult("OK");
        res.setRedirect(ControllerHandler.getBaseUrl(request)+"/app/admin/editTemplate/"+t.getId());
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
    @RequestMapping(value="delete/{id}", method= RequestMethod.GET)
    public
    @ResponseBody
    PostResult deletePolicy(@PathVariable(value = "id") Long id,HttpServletRequest request, HttpServletResponse response) throws IOException, FileUploadException {
        try {
            admService.deletePolicy(id);
        } catch (RestException e) {
            return new PostResult(e);
        }
        return new PostResult("OK");
    }







}
