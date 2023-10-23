package it.cineca.siss.axmr3.doc.web.controllers.rest;

import it.cineca.siss.axmr3.authentication.IAuthority;
import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.authentication.impl.UserImpl;
import it.cineca.siss.axmr3.doc.elk.*;
import it.cineca.siss.axmr3.doc.json.JqGridJSON;
import it.cineca.siss.axmr3.doc.types.PostResult;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.http.HttpEntity;
import org.springframework.http.HttpHeaders;
import org.springframework.http.MediaType;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.stereotype.Controller;
import org.springframework.util.LinkedMultiValueMap;
import org.springframework.util.MultiValueMap;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.client.RestTemplate;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import java.util.Arrays;
import java.util.Enumeration;
import java.util.List;

/**
 * Created by Carlo on 29/01/2016.
 */


@Controller
public class RestElasticController {

    @Autowired
    protected ElkService service;

    public ElkService getService() {
        return service;
    }

    public void setService(ElkService service) {
        this.service = service;
    }


    protected String externalIndexerUrl;

    @Autowired
    @Qualifier("externalIndexerUrl")
    public String getExternalIndexerUrl() {
        return externalIndexerUrl;
    }

    public void setExternalIndexerUrl(String externalIndexerUrl) {
        this.externalIndexerUrl = externalIndexerUrl;
    }

    /**
     * Resitiuisce lo ok se il controller è presente
     * @return
     */
    @RequestMapping(value="/rest/elk/status", method= RequestMethod.GET)
    public @ResponseBody
    PostResult getStatus(){
        return new PostResult("OK");
    }

    @RequestMapping(value="/rest/elk/getAll/{typeId}", method= RequestMethod.GET, produces = "application/json")
    public @ResponseBody
    String getAll(@PathVariable(value = "typeId") String type){
        RestTemplate restTemplate = new RestTemplate();
        return restTemplate.getForObject(this.service.externalIndexerUrl+"/rest/elk/getAll/"+type, String.class);
    }


    @RequestMapping(value="/rest/elk/index/{typeId}", method= RequestMethod.GET, produces = "application/json")
    public @ResponseBody
    String indexType(@PathVariable(value = "typeId") String type){
        return service.doSimpleIndex(type);
    }

    @RequestMapping(value="/rest/elk/fullIndex/{typeId}", method= RequestMethod.GET, produces = "application/json")
    public @ResponseBody
    String fullIndexType(@PathVariable(value = "typeId") String type){
        return service.doFullIndex(type);
        
    }

    @RequestMapping(value="/rest/elk/fieldsIndex/{typeId}", method= RequestMethod.GET, produces = "application/json")
    public @ResponseBody
    String fieldsIndexType(@PathVariable(value = "typeId") String type){
        return service.doFieldIndex(type);
    }

    @RequestMapping(value="/rest/elk/fieldsIndexById/{elId}", method= RequestMethod.GET, produces = "application/json")
    public @ResponseBody
    String fieldsIndexById(@PathVariable(value = "elId") Long elId){
        return service.fieldIndex(elId);
    }

    @RequestMapping(value="/rest/elk/elementIdxUpdate/{elId}", method= RequestMethod.GET, produces = "application/json")
    public @ResponseBody
    String elementIdxUpdate(@PathVariable(value = "elId") Long elId){
        RestTemplate restTemplate = new RestTemplate();
        return restTemplate.getForObject(this.service.externalIndexerUrl+"/rest/elk/elementIdxUpdate/"+elId, String.class);
    }

    @RequestMapping(value="/rest/elk/fullIndexById/{elId}", method= RequestMethod.GET, produces = "application/json")
    public @ResponseBody
    String fullIndexById(@PathVariable(value = "elId") Long elId){
        return service.fullIndex(elId);
    }

    @RequestMapping(value="/rest/elk/simpleIndexById/{elId}", method= RequestMethod.GET, produces = "application/json")
    public @ResponseBody
    String simpleIndexById(@PathVariable(value = "elId") Long elId){
        return service.simpleIndex(elId);
    }

    @RequestMapping(value="/rest/elk/allIndexsById/{elId}", method= RequestMethod.GET, produces = "application/json")
    public @ResponseBody
    String allIndexsById(@PathVariable(value = "elId") Long elId){
        RestTemplate restTemplate = new RestTemplate();
        return restTemplate.getForObject(this.service.externalIndexerUrl+"/rest/elk/allIndexsById/"+elId, String.class);
    }

    @RequestMapping(value = "/rest/elk/query/jqgrid/{index}/{type}", method = RequestMethod.POST, produces = "application/json")
    public
    @ResponseBody
    String elkFilteredQuery(@PathVariable(value = "index") String index, @PathVariable(value = "type") String type, HttpServletRequest request, HttpServletResponse resp) {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        RestTemplate restTemplate= new RestTemplate();
        HttpHeaders headers = new HttpHeaders();
        headers.setContentType(MediaType.APPLICATION_FORM_URLENCODED);
        headers.add("x-username", user.getUsername());
        headers.add("x-firstname", user.getFirstName());
        headers.add("x-lastname", user.getLastName());
        headers.add("x-tenant", "crms");
        headers.add("x-email", user.getEmail());
        String roles="";
        for (IAuthority  auth:user.getAuthorities()){
            if (!roles.isEmpty()){
                roles+=",";
            }
            roles+=auth.getAuthority();
        }
        headers.add("x-roles", roles);
        MultiValueMap<String, String> map= new LinkedMultiValueMap<String, String>();
        
        for (Enumeration<?> e = request.getParameterNames(); e.hasMoreElements();) {
            String paramName = (String) e.nextElement();
            String paramValue = request.getParameter(paramName);
            System.out.println("Aggiungo header: "+paramName+" - "+paramValue);
            map.add(paramName, paramValue);
        }
        HttpEntity<MultiValueMap<String, String>> requestHeaders = new HttpEntity<MultiValueMap<String, String>>(map, headers);
        try{
        System.out.println(service.externalIndexerUrl);
        String var = restTemplate.postForObject(service.externalIndexerUrl+"/rest/elk/query/jqgrid/"+index+"/"+type, requestHeaders, String.class);
        System.out.println("RISPOSTA OTTENUTA: "+var);
        return var;
        }catch(Exception ex){
            ex.printStackTrace();
            return null;
        }
    }

    @RequestMapping(value = "/rest/elk/getElement/{type}/{elementId}", method = RequestMethod.GET, produces = "application/json")
    public
    @ResponseBody
    String getElement(@PathVariable(value = "type") String type, @PathVariable(value = "elementId") Long elementId, HttpServletRequest request, HttpServletResponse resp) {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        RestTemplate restTemplate= new RestTemplate();
        HttpHeaders headers = new HttpHeaders();
        headers.setContentType(MediaType.APPLICATION_FORM_URLENCODED);
        headers.add("x-username", user.getUsername());
        headers.add("x-firstname", user.getFirstName());
        headers.add("x-lastname", user.getLastName());
        headers.add("x-tenant", "crms");
        headers.add("x-email", user.getEmail());
        String roles="";
        for (IAuthority  auth:user.getAuthorities()){
            if (!roles.isEmpty()){
                roles+=",";
            }
            roles+=auth.getAuthority();
        }
        headers.add("x-roles", roles);
        String params="";
        for (Enumeration<?> e = request.getParameterNames(); e.hasMoreElements();) {
            if (!params.isEmpty()){
                params+="&";
            }
            String paramName = (String) e.nextElement();
            String paramValue = request.getParameter(paramName);
            params+=paramName+"="+paramValue;
        }

        if (!params.isEmpty()){
            params="?"+params;
        }
        HttpEntity<MultiValueMap<String, String>> requestHeaders = new HttpEntity<MultiValueMap<String, String>>(null, headers);
        return restTemplate.postForObject(service.externalIndexerUrl+"/rest/elk/getElement/"+type+"/"+elementId+params, requestHeaders, String.class);
    }


    @RequestMapping(value = "/rest/elk/query/{index}/{type}", method = RequestMethod.POST, produces = "application/json")
    public
    @ResponseBody
    String elkFilteredQueryNative(@PathVariable(value = "index") String index, @PathVariable(value = "type") String type, HttpServletRequest request, HttpServletResponse resp) {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        RestTemplate restTemplate= new RestTemplate();
        HttpHeaders headers = new HttpHeaders();
        headers.setContentType(MediaType.APPLICATION_FORM_URLENCODED);
        headers.add("x-username", user.getUsername());
        headers.add("x-firstname", user.getFirstName());
        headers.add("x-lastname", user.getLastName());
        headers.add("x-tenant", "crms");
        headers.add("x-email", user.getEmail());
        String roles="";
        for (IAuthority  auth:user.getAuthorities()){
            if (!roles.isEmpty()){
                roles+=",";
            }
            roles+=auth.getAuthority();
        }
        headers.add("x-roles", roles);
        MultiValueMap<String, String> map= new LinkedMultiValueMap<String, String>();
        for (Enumeration<?> e = request.getParameterNames(); e.hasMoreElements();) {
            String paramName = (String) e.nextElement();
            String paramValue = request.getParameter(paramName);
            System.out.println("Aggiungo header: "+paramName+" - "+paramValue);
            map.add(paramName, paramValue);
        }

        
        HttpEntity<MultiValueMap<String, String>> requestHeaders = new HttpEntity<MultiValueMap<String, String>>(map, headers);
        return restTemplate.postForEntity(service.externalIndexerUrl+"/rest/elk/query/"+index+"/"+type, requestHeaders, String.class).getBody();
    }

    @RequestMapping(value = "/rest/elk/querycount/{index}/{type}", method = RequestMethod.POST, produces = "application/json")
    public
    @ResponseBody
    String elkFilteredQueryCount(@PathVariable(value = "index") String index, @PathVariable(value = "type") String type, HttpServletRequest request) {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        RestTemplate restTemplate= new RestTemplate();
        HttpHeaders headers = new HttpHeaders();
        headers.setContentType(MediaType.APPLICATION_FORM_URLENCODED);
        headers.add("x-username", user.getUsername());
        headers.add("x-firstname", user.getFirstName());
        headers.add("x-lastname", user.getLastName());
        headers.add("x-tenant", "crms");
        headers.add("x-email", user.getEmail());
        String roles="";
        for (IAuthority  auth:user.getAuthorities()){
            if (!roles.isEmpty()){
                roles+=",";
            }
            roles+=auth.getAuthority();
        }
        headers.add("x-roles", roles);
        MultiValueMap<String, String> map= new LinkedMultiValueMap<String, String>();
        for (Enumeration<?> e = request.getParameterNames(); e.hasMoreElements();) {
            String paramName = (String) e.nextElement();
            String paramValue = request.getParameter(paramName);
            System.out.println("Aggiungo header: "+paramName+" - "+paramValue);
            map.add(paramName, paramValue);
        }

        HttpEntity<MultiValueMap<String, String>> requestHeaders = new HttpEntity<MultiValueMap<String, String>>(map, headers);
        return restTemplate.postForEntity(service.externalIndexerUrl+"/rest/elk/querycount/"+index+"/"+type, requestHeaders, String.class).getBody();
    }

    @RequestMapping(value= "/rest/elk/fullsearch", method = RequestMethod.GET, produces = "application/json")
    public @ResponseBody
    String fullSearch(HttpServletRequest request){
        String pattern=request.getParameter("pattern");
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        RestTemplate restTemplate= new RestTemplate();
        HttpHeaders headers = new HttpHeaders();
        headers.setContentType(MediaType.APPLICATION_FORM_URLENCODED);
        headers.add("x-username", user.getUsername());
        headers.add("x-firstname", user.getFirstName());
        headers.add("x-lastname", user.getLastName());
        headers.add("x-tenant", "crms");
        headers.add("x-email", user.getEmail());
        String roles="";
        for (IAuthority  auth:user.getAuthorities()){
            if (!roles.isEmpty()){
                roles+=",";
            }
            roles+=auth.getAuthority();
        }
        headers.add("x-roles", roles);
        String params="";
        for (Enumeration<?> e = request.getParameterNames(); e.hasMoreElements();) {
            if (!params.isEmpty()){
                params+="&";
            }
            String paramName = (String) e.nextElement();
            String paramValue = request.getParameter(paramName);
            params+=paramName+"="+paramValue;
        }

        if (!params.isEmpty()){
            params="?"+params;
        }
        HttpEntity<MultiValueMap<String, String>> requestHeaders = new HttpEntity<MultiValueMap<String, String>>(null, headers);
        return restTemplate.postForEntity(service.externalIndexerUrl+"/rest/elk/fullsearch", requestHeaders, String.class).getBody();

    }
}
