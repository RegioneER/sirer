package it.cineca.siss.axmr3.doc.web.controllers.admin.rest;


import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.authentication.impl.UserImpl;
import it.cineca.siss.axmr3.doc.entities.ElementType;
import it.cineca.siss.axmr3.doc.entities.ElementTypeAssociatedTemplate;
import it.cineca.siss.axmr3.doc.helpers.ConfigurationComparisonResult;
import it.cineca.siss.axmr3.doc.helpers.ConfigurationUtils;
import it.cineca.siss.axmr3.doc.types.PostResult;
import it.cineca.siss.axmr3.doc.web.exceptions.RestException;
import it.cineca.siss.axmr3.doc.web.services.AdminService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.multipart.MultipartHttpServletRequest;
import org.xml.sax.SAXException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.*;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Properties;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 01/08/13
 * Time: 15.15
 * To change this template use File | Settings | File Templates.
 */
@Controller
public class RestAdminController {

    @Autowired
    @Qualifier("messagesFolder")
    protected String messagesFolder;

    @Autowired
    protected AdminService admService;

    public AdminService getAdmService() {
        return admService;
    }

    public void setAdmService(AdminService admService) {
        this.admService = admService;
    }

    @RequestMapping(value = "/rest/admin/messages/{locale}", method = RequestMethod.POST)
    @ResponseBody
    public PostResult updateMessage(@PathVariable(value = "locale") String locale, HttpServletRequest req) throws FileNotFoundException, IOException {
        Properties adHocProps = new Properties();
        FileInputStream fis = new FileInputStream(messagesFolder + "/messages/" + locale + ".properties");
        adHocProps.load(fis);
        fis.close();
        String propName = req.getParameter("propName");
        String value = req.getParameter("value");
        adHocProps.put(propName, value);
        adHocProps.store(new FileOutputStream(messagesFolder + "/messages/" + locale + ".properties"), "webUpdate");
        return new PostResult("OK");
    }

    @RequestMapping(value = "/rest/admin/exportcfg", method = RequestMethod.GET)

    public void exportCfg(HttpServletRequest req, HttpServletResponse resp) throws FileNotFoundException, IOException, ParserConfigurationException, TransformerException {
        resp.setContentType("text/xml;charset=UTF-8");
        ConfigurationUtils exp = new ConfigurationUtils();
        exp.setAdmService(admService);
        exp.getFullExportXml(resp.getOutputStream());
        resp.getOutputStream().close();
    }

    @RequestMapping(value = "/rest/admin/loadCfgToSession", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult loadCfgToSession(HttpServletRequest request, HttpServletResponse resp) throws IOException {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        byte[] file = null;
        String fileName = null;
        if (request instanceof MultipartHttpServletRequest) {
            MultipartFile mfile = ((MultipartHttpServletRequest) request).getFile("file");
            file = mfile.getBytes();
            fileName = mfile.getOriginalFilename();
        }
        String pathDest = messagesFolder + "/uploads";
        /*if (Files.notExists(Paths.get(pathDest))) {
            Files.createDirectory(Paths.get(pathDest));
            String groupName = "devj";
            UserPrincipalLookupService lookupService = FileSystems.getDefault().getUserPrincipalLookupService();
            GroupPrincipal group = lookupService.lookupPrincipalByGroupName(groupName);
            Set<PosixFilePermission> perms = new HashSet<PosixFilePermission>();
            perms.add(PosixFilePermission.GROUP_EXECUTE);
            perms.add(PosixFilePermission.GROUP_READ);
            perms.add(PosixFilePermission.GROUP_WRITE);
            perms.add(PosixFilePermission.OWNER_EXECUTE);
            perms.add(PosixFilePermission.OWNER_READ);
            perms.add(PosixFilePermission.OWNER_WRITE);
            Files.setPosixFilePermissions(Paths.get(pathDest), perms);
            Files.getFileAttributeView(Paths.get(pathDest), PosixFileAttributeView.class).setGroup(group);
        }*/
        String fileDest = pathDest + "/cfgImport-" + user.getUsername() + ".xml";
        try (FileOutputStream fout = new FileOutputStream(fileDest)) {
            fout.write(file);
        }
        request.getSession().setAttribute("cfg", readFile(pathDest));
        it.cineca.siss.axmr3.log.Log.info(getClass(), "File di configurazione caricato in sessione");
        return new PostResult("OK");
    }

    @RequestMapping(value = "/rest/admin/doCompare", method = RequestMethod.GET)
    public
    @ResponseBody
    ConfigurationComparisonResult doCompare(HttpServletRequest req, HttpServletResponse resp) throws IOException, ParserConfigurationException, SAXException {
        ConfigurationUtils exp = new ConfigurationUtils();
        exp.setAdmService(admService);
        String xmlContent = (String) req.getSession().getAttribute("cfg");
        return exp.doCompare(xmlContent);
    }

    private String readFile(String file) throws IOException {
        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String line = null;
            StringBuilder stringBuilder = new StringBuilder();
            String ls = System.getProperty("line.separator");
            while ((line = reader.readLine()) != null) {
                stringBuilder.append(line);
                stringBuilder.append(ls);
            }
            return stringBuilder.toString();
        }
    }

    @RequestMapping(value = "/rest/admin/configuration", method = RequestMethod.GET)
    public
    @ResponseBody
    HashMap<String, Object> getConfiguration(HttpServletRequest req, HttpServletResponse resp) throws IOException, ParserConfigurationException, SAXException {
        HashMap<String, Object> ret = new HashMap<String, Object>();
        try {
            ret.put("types", admService.getTypes());
            ret.put("templates", admService.getMds());
            ret.put("policies", admService.getPolicies());
            ret.put("calendars", admService.getCalendars());
            ret.put("processes", admService.getAllActiveProcessDefinition());
        } catch (RestException e) {
            ret = new HashMap<String, Object>();
            ret.put("STATUS", "ERROR");
        }
        return ret;
    }

    @RequestMapping(value = "/rest/admin/getJsonConfiguration", method = RequestMethod.GET)
    public
    @ResponseBody
    HashMap<String, Object> getJsonConfiguration(HttpServletRequest req, HttpServletResponse resp) throws IOException, ParserConfigurationException, SAXException {
        HashMap<String, Object> ret = new HashMap<String, Object>();
        try {
            ret.put("types", admService.getTypes());
            ret.put("templates", admService.getMds());
            ret.put("policies", admService.getPolicies());
            ret.put("calendars", admService.getCalendars());
            //    ret.put("processes",admService.getAllActiveProcessDefinition());
        } catch (Exception e) {
            ret = new HashMap<String, Object>();
            ret.put("STATUS", "ERROR");
        }
        return ret;
    }

    @RequestMapping(value = "/rest/admin/types/getJsonConfiguration", method = RequestMethod.GET)
    public
    @ResponseBody
    HashMap<String, Object> getJsonConfigurationTypes(HttpServletRequest req, HttpServletResponse resp) throws IOException, ParserConfigurationException, SAXException {
        HashMap<String, Object> ret = new HashMap<String, Object>();
        try {
            ret.put("types", admService.getTypes());
        } catch (Exception e) {
            ret = new HashMap<String, Object>();
            ret.put("STATUS", "ERROR");
        }
        return ret;
    }

    @RequestMapping(value = "/rest/admin/templates/getJsonConfiguration", method = RequestMethod.GET)
    public
    @ResponseBody
    HashMap<String, Object> getJsonConfigurationTemplates(HttpServletRequest req, HttpServletResponse resp) throws IOException, ParserConfigurationException, SAXException {
        HashMap<String, Object> ret = new HashMap<String, Object>();
        try {
            ret.put("templates", admService.getMds());
        } catch (Exception e) {
            ret = new HashMap<String, Object>();
            ret.put("STATUS", "ERROR");
        }
        return ret;
    }

    @RequestMapping(value = "/rest/admin/policies/getJsonConfiguration", method = RequestMethod.GET)
    public
    @ResponseBody
    HashMap<String, Object> getJsonConfigurationPolicies(HttpServletRequest req, HttpServletResponse resp) throws IOException, ParserConfigurationException, SAXException {
        HashMap<String, Object> ret = new HashMap<String, Object>();
        try {
            ret.put("policies", admService.getPolicies());
        } catch (Exception e) {
            ret = new HashMap<String, Object>();
            ret.put("STATUS", "ERROR");
        }
        return ret;
    }

    @RequestMapping(value = "/rest/admin/calendars/getJsonConfiguration", method = RequestMethod.GET)
    public
    @ResponseBody
    HashMap<String, Object> getJsonConfigurationCalendars(HttpServletRequest req, HttpServletResponse resp) throws IOException, ParserConfigurationException, SAXException {
        HashMap<String, Object> ret = new HashMap<String, Object>();
        try {
            ret.put("calendars", admService.getCalendars());
        } catch (Exception e) {
            ret = new HashMap<String, Object>();
            ret.put("STATUS", "ERROR");
        }
        return ret;
    }

    @RequestMapping(value = "/rest/admin/processes/getJsonConfiguration", method = RequestMethod.GET)
    public
    @ResponseBody
    HashMap<String, Object> getJsonConfigurationProcesses(HttpServletRequest req, HttpServletResponse resp) throws IOException, ParserConfigurationException, SAXException {
        HashMap<String, Object> ret = new HashMap<String, Object>();
        try {
            ret.put("processes", admService.getAllActiveProcessDefinition());
        } catch (Exception e) {
            ret = new HashMap<String, Object>();
            ret.put("STATUS", "ERROR");
        }
        return ret;
    }

}
