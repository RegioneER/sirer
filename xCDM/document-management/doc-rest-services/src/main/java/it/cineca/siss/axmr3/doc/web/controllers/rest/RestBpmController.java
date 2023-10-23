package it.cineca.siss.axmr3.doc.web.controllers.rest;

import it.cineca.siss.axmr3.authentication.IAuthority;
import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.common.mvc.handlers.ControllerHandler;
import it.cineca.siss.axmr3.doc.entities.Element;
import it.cineca.siss.axmr3.doc.entities.ElementTypeAssociatedWorkflow;
import it.cineca.siss.axmr3.doc.types.HistoryProcessInstance;
import it.cineca.siss.axmr3.doc.types.PostResult;
import it.cineca.siss.axmr3.doc.web.exceptions.RestException;
import it.cineca.siss.axmr3.doc.web.services.DocumentService;
import org.activiti.engine.ProcessEngine;
import org.activiti.engine.task.Task;
import org.apache.log4j.Logger;
import org.dom4j.DocumentException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.*;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;


/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 17/10/13
 * Time: 14:09
 * To change this template use File | Settings | File Templates.
 */
@Controller
public class RestBpmController {

protected static final Logger log=Logger.getLogger(RestBpmController.class);

    @Autowired
    protected ProcessEngine processEngine;

    public ProcessEngine getProcessEngine() {
        return processEngine;
    }

    public void setProcessEngine(ProcessEngine processEngine) {
        this.processEngine = processEngine;
    }

    @Autowired
    protected DocumentService docService;

    public DocumentService getDocService() {
        return docService;
    }

    public void setDocService(DocumentService docService) {
        this.docService = docService;
    }

    /**
     * Richiesta di avvio processo
     *
     * @param elId
     * @param processKey
     * @param request
     * @param model
     * @return
     * @throws DocumentException
     * @throws IOException
     */
    @RequestMapping(value="/rest/documents/startProcess/{elId}/{processKey}", method= RequestMethod.GET)
    public @ResponseBody
    PostResult startProcess(@PathVariable(value = "elId") Long elId,@PathVariable(value = "processKey") String processKey, HttpServletRequest request, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Element el=docService.getElement(elId);
        String pId="";
        try {
            pId=docService.startProcess(user, el, processKey);
        } catch (RestException e) {
            PostResult res=new PostResult("ERROR");
            res.setErrorMessage(e.getMessage());
        }
        PostResult res=new PostResult("OK");
        res.setRet(pId);
        res.setRedirect(ControllerHandler.getBaseUrl(request)+"/app/documents/detail/"+elId);
        return res;
    }

    @RequestMapping(value="/rest/documents/activeProcesses/{elId}", method= RequestMethod.GET)
    public @ResponseBody
    List<it.cineca.siss.axmr3.doc.types.ProcessInstance> activeProcesses(@PathVariable(value = "elId") Long elId, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Element el=docService.getElement(elId);
        String pId="";
        return it.cineca.siss.axmr3.doc.types.ProcessInstance.fromList(docService.getActiveProcesses(user, el),docService);
    }

    @RequestMapping(value="/rest/documents/availableProcesses/{elId}", method= RequestMethod.GET)
    public @ResponseBody
    List<it.cineca.siss.axmr3.doc.types.ProcessDefinition> availableProcesses(@PathVariable(value = "elId") Long elId, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Element el=docService.getElement(elId);
        String pId="";
        return it.cineca.siss.axmr3.doc.types.ProcessDefinition.fromList(docService.getAvailableProcessess(user, el));
    }

    @RequestMapping(value="/rest/documents/terminatedProcesses/{elId}", method= RequestMethod.GET)
    public @ResponseBody
    List<HistoryProcessInstance> teminatedProcesses(@PathVariable(value = "elId") Long elId, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Element el=docService.getElement(elId);
        String pId="";
        return HistoryProcessInstance.fromList(docService.getTerminatedProcesses(user, el));
    }

    @RequestMapping(value="/rest/documents/tasks/{elId}", method= RequestMethod.GET)
    public @ResponseBody
    List<it.cineca.siss.axmr3.doc.types.Task> getTasks(@PathVariable(value = "elId") Long elId, @ModelAttribute("model") ModelMap model) throws DocumentException, IOException {
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Element el=docService.getElement(elId);
        String pId="";
        List<org.activiti.engine.runtime.ProcessInstance> activeProcesses=docService.getActiveProcesses(user, el);
        List<it.cineca.siss.axmr3.doc.types.Task> activeTasks=docService.getActiveTask(user, el, activeProcesses);

        //CRPMS-603 ordino i task attivi alla creazione in base all'ordinamento in Configurazione per id (DOC_TYPE_WF)
        List<it.cineca.siss.axmr3.doc.types.Task> reorderedActiveTasks=new LinkedList<it.cineca.siss.axmr3.doc.types.Task>();
        for(ElementTypeAssociatedWorkflow awf: el.getType().getAssociatedWorkflows()){
            for (int i = 0; i < activeTasks.size(); i++) {
                if (activeTasks.get(i).getProcessKey().equals(awf.getProcessKey())){
                    reorderedActiveTasks.add(activeTasks.get(i));
                }
            }
        }
        //metto in coda tutti gli altri non attivati alla creazione
        for (int i = 0; i < activeTasks.size(); i++) {
            if (!reorderedActiveTasks.contains(activeTasks.get(i))){
                reorderedActiveTasks.add(activeTasks.get(i));
            }
        }

        return reorderedActiveTasks;
    }

    @RequestMapping(value="/rest/documents/submitTask/{taskId}", method=RequestMethod.POST)
    public @ResponseBody
    PostResult submitTask(@PathVariable(value = "taskId") String taskId, HttpServletRequest request){
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        List<String> groups=new LinkedList<String>();
        for (IAuthority auth:user.getAuthorities()) groups.add(auth.getAuthority());
        HashMap<String, String> data=new HashMap<String, String>();
        Enumeration paramNames = request.getParameterNames();
        while (paramNames.hasMoreElements()){
            String paramName= (String) paramNames.nextElement();
            data.put(paramName,request.getParameter(paramName));
        }
        try{
            Task t=processEngine.getTaskService().createTaskQuery().active().includeProcessVariables().includeTaskLocalVariables().taskInvolvedUser(user.getUsername()).taskId(taskId).singleResult();
            if (t==null) t=processEngine.getTaskService().createTaskQuery().active().includeProcessVariables().includeTaskLocalVariables().taskCandidateGroupIn(groups) .taskId(taskId).singleResult();
            if (t==null) throw new RestException("Task not found", 404);
            processEngine.getTaskService().claim(t.getId(), user.getUsername()) ;
            try{
                if(!user.getUsername().isEmpty()){
                    processEngine.getRuntimeService().setVariable(t.getProcessInstanceId(), "lastUserid", user.getUsername());
                }
                processEngine.getFormService().submitTaskFormData(t.getId(), data) ;
                PostResult res=new PostResult("OK");
                return res;
            }catch (Exception ex){
                PostResult res=new PostResult("ERROR");
                res.setErrorMessage(ex.getMessage());
                log.error(ex.getMessage(),ex);
                processEngine.getTaskService().unclaim(t.getId());
                return res;
            }
        }catch (Exception ex){
            PostResult res=new PostResult("ERROR");
            res.setErrorMessage(ex.getMessage());
            log.error(ex.getMessage(),ex);
            return res;
        }
    }

    @RequestMapping(value="/rest/documents/submitTask/{elId}/{processKey}/{taskKey}", method=RequestMethod.POST)
    public @ResponseBody
    PostResult submitTaskByKey(@PathVariable(value = "elId") Long elId, @PathVariable(value = "processKey") String processKey, @PathVariable(value = "taskKey") String taskKey, HttpServletRequest request, HttpServletResponse response) throws IOException {
        IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Element el=docService.getElement(elId);
        List<String> groups=new LinkedList<String>();
        String pId="";
        List<org.activiti.engine.runtime.ProcessInstance> activeProcesses=docService.getActiveProcesses(user, el);
        boolean processExists=false;
        for (org.activiti.engine.runtime.ProcessInstance pi:activeProcesses){
            if (pi.getProcessDefinitionId().equals(processKey)){
                processExists=true;
            }
        }
        try{
            if (!processExists){
                throw new RestException("Process not found", 404);
            }
            List<it.cineca.siss.axmr3.doc.types.Task> activeTasks=docService.getActiveTask(user, el, activeProcesses);
            String taskId=null;
            for (it.cineca.siss.axmr3.doc.types.Task task:activeTasks){
                if (task.getTaskKey().equals(taskKey)){
                    taskId=task.getId();
                }
            }
            if (taskId==null){
                throw new RestException("Task not found", 404);
            }
            for (IAuthority auth:user.getAuthorities()) groups.add(auth.getAuthority());
            HashMap<String, String> data=new HashMap<String, String>();
            Enumeration paramNames = request.getParameterNames();
            while (paramNames.hasMoreElements()){
                String paramName= (String) paramNames.nextElement();
                data.put(paramName,request.getParameter(paramName));
            }

            Task t=processEngine.getTaskService().createTaskQuery().active().includeProcessVariables().includeTaskLocalVariables().taskInvolvedUser(user.getUsername()).taskId(taskId).singleResult();
            if (t==null) t=processEngine.getTaskService().createTaskQuery().active().includeProcessVariables().includeTaskLocalVariables().taskCandidateGroupIn(groups) .taskId(taskId).singleResult();
            if (t==null) throw new RestException("Task not found", 404);
            processEngine.getTaskService().claim(t.getId(), user.getUsername()) ;
            try{
                if(!user.getUsername().isEmpty()){
                    processEngine.getRuntimeService().setVariable(t.getProcessInstanceId(), "lastUserid", user.getUsername());
                }
                processEngine.getFormService().submitTaskFormData(t.getId(), data) ;
                PostResult res=new PostResult("OK");
                return res;
            }catch (Exception ex){
                PostResult res=new PostResult("ERROR");
                res.setErrorMessage(ex.getMessage());
                log.error(ex.getMessage(),ex);
                processEngine.getTaskService().unclaim(t.getId());
                return res;
            }
        }catch (Exception ex){
            PostResult res=new PostResult("ERROR");
            res.setErrorMessage(ex.getMessage());
            log.error(ex.getMessage(),ex);
            return res;
        }
    }





}
