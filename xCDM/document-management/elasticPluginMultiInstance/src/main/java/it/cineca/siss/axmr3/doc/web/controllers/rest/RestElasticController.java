package it.cineca.siss.axmr3.doc.web.controllers.rest;

import com.google.gson.Gson;
import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.authentication.impl.UserImpl;
import it.cineca.siss.axmr3.doc.elk.*;
import it.cineca.siss.axmr3.doc.entities.Element;
import it.cineca.siss.axmr3.doc.json.JqGridJSON;
import it.cineca.siss.axmr3.doc.types.PostResult;
import it.cineca.siss.axmr3.doc.web.exceptions.RestException;
import it.cineca.siss.axmr3.doc.web.services.DocumentService;
import org.apache.log4j.Logger;
import org.elasticsearch.action.search.SearchResponse;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by Carlo on 29/01/2016.
 */


@Controller
public class RestElasticController {

    static final Logger log=Logger.getLogger(RestElasticController.class);

    @Autowired
    protected DocumentService docService;


    public DocumentService getDocService() {
        return docService;
    }

    public void setDocService(DocumentService docService) {
        this.docService = docService;
    }

    @Autowired
    protected ElkService service;

    public ElkService getService() {
        return service;
    }
    public void setService(ElkService service) {
        this.service = service;
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

    @RequestMapping(value="/rest/elk/getAll/{typeId}", method= RequestMethod.GET)
    public @ResponseBody
    List<ElkSimpleElement> getAll(@PathVariable(value = "typeId") String type){
        return service.getAll(type);
    }


    @RequestMapping(value="/rest/elk/index/{typeId}", method= RequestMethod.GET)
    public @ResponseBody
    PostResult indexType(@PathVariable(value = "typeId") String type){
        try {
            service.doSimpleIndex(type);
            PostResult ret=new PostResult("OK");
            return ret;
        } catch (Exception e) {
            log.error(e.getMessage(),e);
            return new PostResult(new RestException(e.getMessage(),2));
        }
    }

    @RequestMapping(value="/rest/elk/saveIdxStatus/{indexName}/{typeId}/{objId}", method=RequestMethod.GET)
    public @ResponseBody
    PostResult saveIdxStatus(@PathVariable(value = "indexName") String indexName , @PathVariable(value = "typeId") String type, @PathVariable(value = "objId") Long objId ){
        try {
            service.saveIdxStatusWriteDB(indexName, type, objId);
            PostResult ret=new PostResult("OK");
            return ret;
        } catch (Exception e) {
            log.error(e.getMessage(),e);
            return new PostResult(new RestException(e.getMessage(),2));
        }
    }


    @RequestMapping(value="/rest/elk/fullIndex/{typeId}", method= RequestMethod.GET)
    public @ResponseBody
    PostResult fullIndexType(@PathVariable(value = "typeId") String type){
        try {
            service.doFullIndex(type);
            PostResult ret=new PostResult("OK");
            return ret;
        } catch (Exception e) {
            log.error(e.getMessage(),e);
            return new PostResult(new RestException(e.getMessage(),2));
        }
    }

    @RequestMapping(value="/rest/elk/fieldsIndex/{typeId}", method= RequestMethod.GET)
    public @ResponseBody
    PostResult fieldsIndexType(@PathVariable(value = "typeId") String type){
        try {
            service.doFieldIndex(type);
            PostResult ret=new PostResult("OK");
            return ret;
        } catch (Exception e) {
            return new PostResult(new RestException(e.getMessage(),2));
        }
    }

    @RequestMapping(value="/rest/elk/fieldsIndexById/{elId}", method= RequestMethod.GET)
    public @ResponseBody
    PostResult fieldsIndexById(@PathVariable(value = "elId") Long elId){
        try {
            service.fieldIndex(docService.getElement(elId));
            PostResult ret=new PostResult("OK");
            return ret;
        } catch (Exception e) {
            return new PostResult(new RestException(e.getMessage(),2));
        }
    }

    @RequestMapping(value="/rest/elk/elementIdxUpdate/{elId}", method= RequestMethod.GET)
    public @ResponseBody
    PostResult elementIdxUpdate(@PathVariable(value = "elId") Long elId){
        try {
            service.elementIdxUpdate(docService.getElement(elId));
            PostResult ret=new PostResult("OK");
            return ret;
        } catch (Exception e) {
            return new PostResult(new RestException(e.getMessage(),2));
        }
    }

    @RequestMapping(value="/rest/elk/fullIndexById/{elId}", method= RequestMethod.GET)
    public @ResponseBody
    PostResult fullIndexById(@PathVariable(value = "elId") Long elId){
        try {
            service.fullIndex(docService.getElement(elId));
            PostResult ret=new PostResult("OK");
            return ret;
        } catch (Exception e) {
            log.error(e.getMessage(),e);
            return new PostResult(new RestException(e.getMessage(),2));
        }
    }

    @RequestMapping(value="/rest/elk/simpleIndexById/{elId}", method= RequestMethod.GET)
    public @ResponseBody
    PostResult simpleIndexById(@PathVariable(value = "elId") Long elId){
        try {
            service.simpleIndex(docService.getElement(elId));
            PostResult ret=new PostResult("OK");
            return ret;
        } catch (Exception e) {
            return new PostResult(new RestException(e.getMessage(),2));
        }
    }

    @RequestMapping(value="/rest/elk/allIndexsById/{elId}", method= RequestMethod.GET)
    public @ResponseBody
    PostResult allIndexsById(@PathVariable(value = "elId") Long elId){
        try {
            Element el=docService.getElement(elId);
            if (el.getType().isSearchable()) {
                service.fullIndex(el);
                service.fieldIndex(el);
            }
            PostResult ret=new PostResult("OK");
            return ret;
        } catch (Exception e) {
            return new PostResult(new RestException(e.getMessage(),2));
        }
    }

    @RequestMapping(value = "/rest/elk/query/jqgrid/{index}/{type}", method = RequestMethod.POST)
    public
    @ResponseBody
    JqGridJSON elkFilteredQuery(@PathVariable(value = "index") String index, @PathVariable(value = "type") String type, HttpServletRequest request, HttpServletResponse resp) {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        try {
            String filter=request.getParameter("filter");
            int page=1;
            int rpp=20;
            if (request.getParameter("page")!=null){
                page=Integer.parseInt(request.getParameter("page"));
            }
            if (request.getParameter("rows")!=null){
                rpp=Integer.parseInt(request.getParameter("rows"));
            }
            String sidx="";
            String sord="asc";
            if (request.getParameter("sidx")!=null){
                sidx=request.getParameter("sidx");
            }
            if (request.getParameter("sord")!=null){
                sord=request.getParameter("sord");
            }
            SearchResponse response = service.doElkQuery(user, index.toLowerCase(), type.toLowerCase(), filter,sidx,sord, page, rpp, true);
            JqGridJSON res = new JqGridJSON();
            res.setTotal(Integer.parseInt(response.getHits().getTotalHits()+""));
            res.setPage(page);
            res.setRows(rpp);
            List<Object> resList=new LinkedList<Object>();
            for (int i=0;i<response.getHits().getHits().length;i++){
                ElkFullElement elkEl=new Gson().fromJson(response.getHits().getHits()[i].getSourceAsString(), ElkFullElement.class);
                elkEl.adjustScope(user);
                resList.add(elkEl);
            }
            res.setRootObjects(resList);
            return res;
        } catch (Exception e) {
            log.error(e.getMessage(),e);
            return null;
        }
    }

    @RequestMapping(value = "/rest/elk/getElement/{type}/{elementId}", method = RequestMethod.GET)
    public
    @ResponseBody
    ElkFullElement getElement(@PathVariable(value = "type") String type, @PathVariable(value = "elementId") Long elementId, HttpServletRequest request, HttpServletResponse resp) {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        try {
            String filter="{match: {\"id\": \""+elementId+"\"}}";
            int page=1;
            int rpp=20;
            String sidx="id";
            String sord="asc";
            SearchResponse response = service.doElkQuery(user, "full", type.toLowerCase(), filter,sidx,sord, page, rpp, true);
            List<Object> resList=new LinkedList<Object>();
            if (response.getHits().getHits().length==0) return null;
            else {
                ElkFullElement elkEl=new Gson().fromJson(response.getHits().getHits()[0].getSourceAsString(), ElkFullElement.class);
                elkEl.adjustScope(user);
                return elkEl;
            }
        } catch (Exception e) {
            log.error(e.getMessage(),e);
            return null;
        }
    }

    /*
    @RequestMapping(value = "/rest/elk/test/{index}/{type}", method = RequestMethod.GET)
    public
    @ResponseBody
    JqGridJSON elkFilteredQueryTest(@PathVariable(value = "index") String index, @PathVariable(value = "type") String type, HttpServletRequest request, HttpServletResponse resp) {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        try {
            String filter=" {\n" +
                    "            \"exists\" : { \"field\" : \"children.ArruolamentoPrimoPaz.metadata.DatiArrPrimoPaz.values.dataAperturaCentro\" }\n" +
                    "          },\n" +
                    "          {\n" +
                    "            \"missing\" : { \"field\" : \"metadata.DatiChiusuraWF.values.dataChiusuraAmm\" }\n" +
                    "          }";

            int page=1;
            int rpp=20;
            if (request.getParameter("page")!=null){
                page=Integer.parseInt(request.getParameter("page"));
            }
            if (request.getParameter("rows")!=null){
                rpp=Integer.parseInt(request.getParameter("rows"));
            }
            SearchResponse response = service.doElkQuery(user, index.toLowerCase(), type.toLowerCase(), filter,null, null, page, rpp, true);
            JqGridJSON res = new JqGridJSON();
            res.setTotal(Integer.parseInt(response.getHits().getTotalHits()+""));
            res.setPage(page);
            res.setRows(rpp);
            List<Object> resList=new LinkedList<Object>();
            for (int i=0;i<response.getHits().getHits().length;i++){
                ElkFullElement elkEl=new Gson().fromJson(response.getHits().getHits()[i].getSourceAsString(), ElkFullElement.class);
                elkEl.scopeClear(user);
                resList.add(elkEl);
            }
            res.setRootObjects(resList);
            return res;
        } catch (Exception e) {
            log.error(e.getMessage(),e);
            return null;
        }
    }
    */

    @RequestMapping(value = "/rest/elk/query/{index}/{type}", method = RequestMethod.POST)
    public
    @ResponseBody
    PostResult elkFilteredQueryNative(@PathVariable(value = "index") String index, @PathVariable(value = "type") String type, HttpServletRequest request, HttpServletResponse resp) {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        try {
            String filter=request.getParameter("filter");
            int page=1;
            int rpp=20;
            if (request.getParameter("page")!=null){
                page=Integer.parseInt(request.getParameter("page"));
            }
            if (request.getParameter("rows")!=null){
                rpp=Integer.parseInt(request.getParameter("rows"));
            }
            String sidx="";
            String sord="asc";
            if (request.getParameter("sidx")!=null){
                sidx=request.getParameter("sidx");
            }
            if (request.getParameter("sord")!=null){
                sord=request.getParameter("sord");
            }
            SearchResponse response = service.doElkQuery(user, index.toLowerCase(), type.toLowerCase(), filter, sidx, sord, page, rpp, true);

            List<ElkFullElement> resList=new LinkedList<ElkFullElement>();
            for (int i=0;i<response.getHits().getHits().length;i++){
                ElkFullElement elkEl=new Gson().fromJson(response.getHits().getHits()[i].getSourceAsString(), ElkFullElement.class);
                elkEl.adjustScope(user);
                resList.add(elkEl);
            }
            PostResult ret = new PostResult("OK");
            HashMap<String, Object> retMap=new HashMap<String, Object>();
            retMap.put("list", resList);
            ret.setResultMap(retMap);
            return ret;
        } catch (Exception e) {
            log.error(e.getMessage(),e);
            return new PostResult(e);
        }
    }

    @RequestMapping(value = "/rest/elk/querycount/{index}/{type}", method = RequestMethod.POST)
    public
    @ResponseBody
    Long elkFilteredQueryCount(@PathVariable(value = "index") String index, @PathVariable(value = "type") String type, HttpServletRequest request) {
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        try {
            String filter=request.getParameter("filter");
            SearchResponse response = service.doElkQuery(user, index.toLowerCase(), type.toLowerCase(), filter,null, null, 1, 10, false);
            return response.getHits().getTotalHits();
        }catch (Exception ex){
            return null;
        }
    }

    @RequestMapping(value= "/rest/elk/fullsearch", method = RequestMethod.GET)
    public @ResponseBody
    PostResult fullSearch(HttpServletRequest request){
        String pattern=request.getParameter("pattern");
        IUser user = null;
        try {
            user = (UserImpl) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        } catch (java.lang.ClassCastException ex) {
            user = new UserImpl();
            user.fromUserDetails((UserDetails) SecurityContextHolder.getContext().getAuthentication().getPrincipal());
        }
        try{
            PostResult ret=new PostResult("OK");
            List<FieldSearchResult> ret1 = service.fullsearch(user, pattern);
            LinkedHashMap<String, Object> ret2=new LinkedHashMap<String, Object>();
            ret2.put("results", ret1);
            ret.setResultMap(ret2);
            return ret;
        }catch (RestException ex){
            return new PostResult(ex);
        }

    }

    @RequestMapping(value="/rest/elk/idxStatus", method = RequestMethod.GET)
    public @ResponseBody
    PostResult getIdxStatus(){
        List<ElkIdxStatus> result=service.IdxStatuses();
        PostResult ret = new PostResult("OK");
        HashMap<String, Object> res=new HashMap<String, Object>();
        res.put("lista", result);
        ret.setResultMap(res);
        return ret;
    }

}
