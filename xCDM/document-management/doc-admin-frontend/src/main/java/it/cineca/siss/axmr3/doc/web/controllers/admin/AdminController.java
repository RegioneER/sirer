package it.cineca.siss.axmr3.doc.web.controllers.admin;

import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.doc.entities.ElementType;
import it.cineca.siss.axmr3.doc.entities.MetadataTemplate;
import it.cineca.siss.axmr3.doc.web.exceptions.RestException;
import it.cineca.siss.axmr3.doc.web.services.AdminService;
import it.cineca.siss.axmr3.doc.xml.Form;
import it.cineca.siss.axmr3.exceptions.AxmrGenericException;
import org.dom4j.DocumentException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

import javax.servlet.ServletContext;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.List;
import java.util.Properties;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 01/08/13
 * Time: 15.00
 * To change this template use File | Settings | File Templates.
 */
@Controller
public class AdminController {
	
	@Autowired
    @Qualifier ("messagesFolder")
    protected String messagesFolder;


	@Autowired
    protected AdminService admService;

    public AdminService getAdmService() {
        return admService;
    }

    public void setAdmService(AdminService admService) {
        this.admService = admService;
    }

    private void initModel(HttpServletRequest request, ModelMap model, IUser user, AdminService service) throws DocumentException, IOException {

        Cookie[] cookiesArray = request.getCookies();
        HashMap<String,Cookie> cookiesMap=new HashMap<String, Cookie>();
        for(Cookie cookie:cookiesArray){
            cookiesMap.put(cookie.getName(), cookie );
        }
        model.put("requestCookies", cookiesMap);
    }

    private boolean isAdmin(IUser user){
        if(user.hasRole("tech-admin")){
            return true;
        }else{
            return false;
        }
    }

    /**
     * Home Page
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     *
     *
     */
    @RequestMapping(value="/admin", method= RequestMethod.GET)
    public String index(HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
    	IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if(!isAdmin(user)){
            return "documents/NotPermitted";
        }
        initModel(request, model, user, admService);
    	model.put("hasCalendars", admService.isAvailablesCalendars(user));
        model.put("rootBrowse", admService.getRootBrowsableElementTypes(user));
        model.put("area","admin");
        model.put("elTypes", admService.getTypes());
        model.put("templates", admService.getMds());
        return "admin/home";
    }
    
    /**
     * Home Page
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     *
     *
     */
    @RequestMapping(value="/admin/messages/{locale}", method= RequestMethod.GET)
    public String messages(@PathVariable(value="locale") String locale, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
    	IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if(!isAdmin(user)){
            return "documents/NotPermitted";
        }
        initModel(request, model, user, admService);
        model.put("hasCalendars", admService.isAvailablesCalendars(user));
        model.put("rootBrowse", admService.getRootBrowsableElementTypes(user));
        model.put("area","admin");
        model.put("elTypes", admService.getTypes());
        model.put("templates", admService.getMds());
        ServletContext context = request.getSession().getServletContext();
        InputStream stream = context.getResourceAsStream("/WEB-INF/messages/general.properties");
        Properties messProps=new Properties();
        messProps.load(stream);
        HashMap<String, String> messages=new HashMap<String, String>();
        Enumeration e = messProps.propertyNames();
        while (e.hasMoreElements()) {
            String key = (String) e.nextElement();
            messages.put(key,messProps.getProperty(key));
        }
        Properties adHocProps=new Properties();
        FileInputStream fis=new FileInputStream(messagesFolder+"/messages/"+locale+".properties");
        adHocProps.load(fis);
        fis.close();

        Enumeration e1 = adHocProps.propertyNames();
        while (e1.hasMoreElements()) {
            String key = (String) e1.nextElement();
            //it.cineca.siss.axmr3.log.Log.info(getClass(),key+": "+adHocProps.getProperty(key));
            messages.put(key,adHocProps.getProperty(key));
        }
        model.put("props", messages);
        return "admin/messages";
    }

    /**
     * Pagina di modifica della tipologia di elemento
     * @param id
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     *
     *
     */
    @RequestMapping(value="/admin/editType/{id}", method= RequestMethod.GET)
    public String editType(@PathVariable(value = "id") Long id,HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
    	IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if(!isAdmin(user)){
            return "documents/NotPermitted";
        }
        initModel(request, model, user, admService);
        model.put("rootBrowse", admService.getRootBrowsableElementTypes(user));
        model.put("hasCalendars", admService.isAvailablesCalendars(user));
    	model.put("area","admin");
        ElementType t=admService.getElementType(id);
        model.put("elType", t);
        List<ElementType> types=admService.getTypes();
        List<MetadataTemplate> templates=admService.getMds();
        model.put("elTypes", types);
        model.put("templates", templates);
        model.put("policies", admService.getPolicies());
        return "admin/typeEditForm";
    }

    @RequestMapping(value="/admin/editControls/{id}", method= RequestMethod.GET)
    public String editControls(@PathVariable(value = "id") String id,HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if(!isAdmin(user)){
            return "documents/NotPermitted";
        }
        initModel(request, model, user, admService);
        model.put("rootBrowse", admService.getRootBrowsableElementTypes(user));
        model.put("area","admin");
        model.put("controlId", id);
        return "admin/editControls";
    }

    /**
     * Pagina di allineamento di configurazione su ambienti diversi

     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     *
     *
     */
    @RequestMapping(value="/admin/allinea", method= RequestMethod.GET)
    public String allineaCheck(HttpServletRequest request, HttpServletResponse response,  @ModelAttribute("model") ModelMap model) throws Exception {
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        String out = "";
        if(!isAdmin(user)){
            out+= "Errore permessi insufficienti";
            model.put("body",out);
            return  "admin/allinea";
        }
        initModel(request, model, user, admService);

        out+= "Allineo verificare i log...\n";
        out+=admService.allinea();
        model.put("body",out);
        return "admin/allinea";
    }

    @RequestMapping(value="/admin/apply/type/{target}", method= RequestMethod.GET)
    public void allineaApplyType(@PathVariable(value = "target") String target, HttpServletRequest request, HttpServletResponse response,  @ModelAttribute("model") ModelMap model) throws Exception {
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();

        ServletOutputStream out = response.getOutputStream();
        if(!isAdmin(user)){
            out.write("Errore permessi insufficienti".getBytes());
            return;
        }
        initModel(request, model, user, admService);

        out.write("Allineo verificare i log...\n".getBytes());
        admService.allineaType(out,target);

    }

    @RequestMapping(value="/admin/bpm", method= RequestMethod.GET)
    public void bpm(HttpServletRequest request, HttpServletResponse response,  @ModelAttribute("model") ModelMap model) throws Exception {
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        ServletOutputStream out = response.getOutputStream();
        if(!isAdmin(user)){
            out.write("Errore permessi insufficienti".getBytes());
            return;
        }
        response.setHeader("Content-Type", "application/zip");
        response.setHeader("Content-Transfer-Encoding", "Binary");
        response.setHeader("Content-Disposition", "attachment; filename=\"exp_bpm.zip\"");
        admService.zipBpm(out);
        out.close();
    }

    /**
     * Pagina di modifica del template di metadati
     * @param id
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     *
     *
     */
    @RequestMapping(value="/admin/editTemplate/{id}", method= RequestMethod.GET)
    public String editTemplate(@PathVariable(value = "id") Long id, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if(!isAdmin(user)){
            return "documents/NotPermitted";
        }
        initModel(request, model, user, admService);
        model.put("rootBrowse", admService.getRootBrowsableElementTypes(user));
        model.put("hasCalendars", admService.isAvailablesCalendars(user));
    	model.put("area","admin");
        model.put("elTypes", admService.getTypes());
        model.put("template", admService.getMd(id));
        return "admin/editTemplate";
    }

    @RequestMapping(value="/admin/xml/edit/{xmlFile}", method= RequestMethod.GET)
    public String editXml(@PathVariable(value = "xmlFile") String xmlFile, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException, AxmrGenericException {
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if(!isAdmin(user)){
            return "documents/NotPermitted";
        }
        initModel(request, model, user, admService);
        model.put("rootBrowse", admService.getRootBrowsableElementTypes(user));
        model.put("hasCalendars", admService.isAvailablesCalendars(user));
        model.put("area","admin");
        model.put("xmlFile", xmlFile);
        model.put("xmlFileContent", admService.getXmlContent(xmlFile));
        return "admin/editXml";
    }


    @RequestMapping(value="/admin/editCalendar/{id}", method= RequestMethod.GET)
    public String editCalendar(@PathVariable(value = "id") Long id, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if(!isAdmin(user)){
            return "documents/NotPermitted";
        }
        initModel(request, model, user, admService);
        model.put("rootBrowse", admService.getRootBrowsableElementTypes(user));
        model.put("hasCalendars", admService.isAvailablesCalendars(user));
        model.put("area","admin");
        model.put("elTypes", admService.getTypes());
        model.put("calendar", admService.getCalendar(id));
        return "admin/editCalendar";
    }

    @RequestMapping(value="/admin/compareConfigurations", method= RequestMethod.GET)
    public String compareConfig(HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        if(!isAdmin(user)){
            return "documents/NotPermitted";
        }
        initModel(request, model, user, admService);
        return "admin/compareConfig";
    }





}
