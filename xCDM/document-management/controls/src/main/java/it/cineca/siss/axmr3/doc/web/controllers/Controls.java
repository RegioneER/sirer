package it.cineca.siss.axmr3.doc.web.controllers;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.authentication.impl.UserImpl;
import it.cineca.siss.axmr3.common.mvc.handlers.ControllerHandler;
import it.cineca.siss.axmr3.doc.controls.json.Configuration;
import it.cineca.siss.axmr3.doc.entities.Element;
import it.cineca.siss.axmr3.doc.entities.ElementType;
import it.cineca.siss.axmr3.doc.types.PostResult;
import it.cineca.siss.axmr3.doc.web.exceptions.RestException;
import it.cineca.siss.axmr3.doc.web.services.DocumentService;
import org.apache.commons.io.FileUtils;
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

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.File;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;

/**
 * Created by Carlo on 23/09/2016.
 */
@Controller
public class Controls {

    @Autowired
    protected DocumentService docService;

    public DocumentService getDocService() {
        return docService;
    }

    public void setDocService(DocumentService docService) {
        this.docService = docService;
    }

    @Autowired
    @Qualifier(value = "controlsSpecificationFolder")
    protected String controlsPath;

    public String getControlsPath() {
        return controlsPath;
    }

    public void setControlsPath(String controlsPath) {
        this.controlsPath = controlsPath;
    }


    @RequestMapping(value = "/documents/jsControls/{typeId}/{formId}", method = RequestMethod.GET)
    public void index(@PathVariable(value = "typeId") String typeId, @PathVariable(value = "formId") String formId, HttpServletRequest request, HttpServletResponse response) throws DocumentException, IOException {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Locale locale = ControllerHandler.getLocale(request);
        String jsControls = "";
        try {
            String json = readFile(controlsPath + "/" + typeId + ".json", Charset.defaultCharset());
            Gson gson = new Gson();
            Configuration jsonCfg = gson.fromJson(json, Configuration.class);
            jsControls = jsonCfg.toJs(locale.getLanguage().toLowerCase(), typeId)+"\nif (jsControls==undefined) {var jsControls=new Object();}\njsControls['"+typeId+"']=new "+typeId+"Controls('"+formId+"');";
        }catch (IOException ex){
            Logger.getLogger(this.getClass()).info("Controlli per oggetto di tipo "+typeId+" non trovati");
        }
        response.getOutputStream().print(jsControls);
        response.getOutputStream().close();
    }

    @RequestMapping(value = "/documents/getJsonControls/{typeId}", method = RequestMethod.GET)
    public void getControls(@PathVariable(value = "typeId") String typeId, HttpServletRequest request, HttpServletResponse response) throws DocumentException, IOException {
        String json = "";
        try {
            json = readFile(controlsPath + "/" + typeId + ".json", Charset.defaultCharset());
        }catch (IOException ex){
            Logger.getLogger(this.getClass()).info("Controlli per oggetto di tipo "+typeId+" non trovati (file: "+controlsPath + "/" + typeId + ".json)");
        }
        response.getOutputStream().print(json);
        response.getOutputStream().close();
    }

    @RequestMapping(value = "/rest/admin/getControls", method = RequestMethod.GET)
    public
    @ResponseBody
    PostResult getControls(HttpServletRequest request, HttpServletResponse resp) throws IOException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        File folder = new File(controlsPath);
        File[] listOfFiles = folder.listFiles();
        List<String> files=new LinkedList<String>();
        for (int i = 0; i < listOfFiles.length; i++) {
            if (listOfFiles[i].isFile()) {
                files.add(listOfFiles[i].getName());
            }
        }
        PostResult res=new PostResult("OK");
        HashMap<String, Object> resMap=new HashMap<String, Object>();
        resMap.put("files", files);
        res.setResultMap(resMap);
        return res;
    }

    @RequestMapping(value = "/rest/admin/saveControls/{typeId}", method = RequestMethod.POST)
    public @ResponseBody
    PostResult saveControls(@RequestBody String rbody, @PathVariable(value = "typeId") String typeId, HttpServletRequest request, HttpServletResponse response) throws DocumentException, IOException {
        try {
            Logger.getLogger(this.getClass()).info("Test - setJsonControls");
            Logger.getLogger(this.getClass()).info(rbody);
            Gson gson = new Gson();
            Configuration jsonCfg = gson.fromJson(rbody, Configuration.class);
            Gson gsonPrint = new GsonBuilder().setPrettyPrinting().create();
            String json = gsonPrint.toJson(jsonCfg);
            File f=new File(controlsPath + "/" + typeId + ".json");
            FileUtils.writeStringToFile(f,json);
            PostResult res=new PostResult("OK");
            return res;
            //json = readFile(controlsPath + "/" + typeId + ".json", Charset.defaultCharset());
        }catch (Exception ex){
            return new PostResult(new RestException(ex.getMessage(), 1));
            //Logger.getLogger(this.getClass()).info("Controlli per oggetto di tipo "+typeId+" non trovati (file: "+controlsPath + "/" + typeId + ".json)");
        }
    }

    static String readFile(String path, Charset encoding)
            throws IOException
    {
        byte[] encoded = Files.readAllBytes(Paths.get(path));
        return new String(encoded, encoding);
    }

    @RequestMapping(value="/rest/documents/checkAndSave/{docTypeId}", method= RequestMethod.POST)
    public @ResponseBody
    PostResult saveNewDoc(@PathVariable(value = "docTypeId") String docTypeS, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        Long docType = docService.getTypeIdByNameOrId(docTypeS);
        ElementType elType=docService.getDocDefinition(docType);
        HashMap<String, String[]> data=new HashMap<String, String[]>();
        HashMap<String, String> dataSingle=new HashMap<String, String>();
        Enumeration paramNames = request.getParameterNames();
        boolean onlySingleValue=true;
        while (paramNames.hasMoreElements()){
            String paramName= (String) paramNames.nextElement();
            it.cineca.siss.axmr3.log.Log.info(getClass(),"Trovato: "+paramName+": "+request.getParameter(paramName));
            String[] values=request.getParameterValues(paramName);
            String paramNameMultiple=paramName.replaceAll("\\[\\]", "");
            if (values.length>1){
                onlySingleValue=false;
            }else {
                dataSingle.put(paramNameMultiple,request.getParameter(paramName));
            }
            data.put(paramNameMultiple,request.getParameterValues(paramName));
            /*
            it.cineca.siss.axmr3.log.Log.info(getClass(),"Effettuo put di request:"+paramName+" - "+request.getParameter(paramName));
            String[] values = request.getParameterValues(paramName);
            data.put(paramName,values[values.length-1]);
            */
        }
        Element parent=null;
        if (data.containsKey("parentId") && data.get("parentId")!=null){
            parent=docService.getElement(Long.parseLong((String) dataSingle.get("parentId")));
            data.remove("parentId");
        }
        byte[] file=null;
        String fileName=null;
        Long fileSize=null;
        if (elType.isHasFileAttached() && request instanceof MultipartHttpServletRequest){
            it.cineca.siss.axmr3.log.Log.info(getClass(),"Sono qui!!!!! - MultipartHttpServletRequest - ");
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
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        try {
            Element el=null;
            if (onlySingleValue) {
                el = docService.saveElement(user, elType, dataSingle, file, fileName, fileSize, version, date, note, autore, parent);
            }else {
                el = docService.saveElementArray(user, elType, data, file, fileName, fileSize, version, date, note, autore, parent);
            }
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


    @RequestMapping(value="/rest/documents/checkAndUpdate/{elId}", method= RequestMethod.POST)
    public @ResponseBody
    PostResult updateMetadata(@PathVariable(value = "elId") Long elId, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        HashMap<String, String[]> data=new HashMap<String, String[]>();
        HashMap<String, String> dataSingle=new HashMap<String, String>();
        Enumeration paramNames = request.getParameterNames();
        try {
            boolean onlySingleValue=true;
            while (paramNames.hasMoreElements()){
                String paramName= (String) paramNames.nextElement();
                it.cineca.siss.axmr3.log.Log.info(getClass(),"Trovato: "+paramName+": "+request.getParameter(paramName));
                String[] values=request.getParameterValues(paramName);
                String paramNameMultiple=paramName.replaceAll("\\[\\]", "");
                if (values.length>1){
                    onlySingleValue=false;

                }else {
                    dataSingle.put(paramNameMultiple,request.getParameter(paramName));
                }
                data.put(paramNameMultiple,request.getParameterValues(paramName));
            }
            if (onlySingleValue) {
                docService.updateElementMetaData(user, elId, dataSingle);
            }else {
                docService.updateElementMetaDataArray(user, elId, data);
            }
        } catch (RestException e) {
            Logger.getLogger(this.getClass()).error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
            PostResult res=new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
            return res;
        }
        PostResult res=new PostResult("OK");
        res.setRet(elId);
        return res;
    }

}
