package it.cineca.siss.axmr3.doc.web.controllers.admin.rest;

import it.cineca.siss.axmr3.doc.web.services.AdminService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 10/09/13
 * Time: 11.45
 * To change this template use File | Settings | File Templates.
 */
@Controller
@RequestMapping(value = "/rest/admin/workflow/")
public class RestAdminWorkflowController {

    @Autowired
    protected AdminService admService;

    public AdminService getAdmService() {
        return admService;
    }

    public void setAdmService(AdminService admService) {
        this.admService = admService;
    }

    /*
    @RequestMapping(value = "getAll", method= RequestMethod.GET)
    public @ResponseBody
    List<WorkflowDefinition> getAll(HttpServletRequest request, HttpServletResponse response){
        return admService.getWfs();
    }

    @RequestMapping(value = "get/{id}", method = RequestMethod.GET)
    public @ResponseBody
    WorkflowDefinition getSingle(@PathVariable(value = "id") Long id,HttpServletRequest request, HttpServletResponse response){
        return admService.getWf(id);
    }

    @RequestMapping(value = "save", method = RequestMethod.POST)
    public @ResponseBody
    PostResult save(HttpServletRequest request, HttpServletResponse response){
        Long wfId=null;
        if (request.getParameter("id")!=null){
            wfId=Long.parseLong(request.getParameter("id"));
            try {
                admService.wfUpdate(wfId,request.getParameter("name"));
            } catch (RestException e) {
                return new PostResult(e);
            }
        }else {
            WorkflowDefinition def= null;
            try {
                def = admService.wfCreate(request.getParameter("name"));
            } catch (RestException e) {
                return new PostResult(e);
            }
            wfId=def.getId();
        }
        PostResult res=new PostResult("OK");
        res.setRedirect(ControllerHandler.getBaseUrl(request)+"/app/admin/editWorkflow/"+wfId);
        return res;
    }

    @RequestMapping(value = "{id}/step/save", method = RequestMethod.POST)
    public @ResponseBody
    PostResult saveStep (@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response){
        Long idStep=null;
        WorkflowDefinition def=admService.getWf(id);
        String name=request.getParameter("name");
        if (request.getParameter("id")!=null && !request.getParameter("id").isEmpty()){
            idStep=Long.parseLong(request.getParameter("id"));
            try {
                admService.wfStepUpdate(def, idStep, name);
            } catch (RestException e) {
                return new PostResult(e);
            }
        }else {
            try {
                admService.wfStepCreate(def, name);
            } catch (RestException e) {
                return new PostResult(e);
            }
        }
        PostResult res=new PostResult("OK");
        res.setRedirect(ControllerHandler.getBaseUrl(request)+"/app/admin/editWorkflow/"+id);
        return res;
    }

    @RequestMapping(value = "{id}/step/getAll", method = RequestMethod.GET)
    public @ResponseBody
    List<WorkflowStep> getSteps(@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response){
        WorkflowDefinition def=admService.getWf(id);
        return (List<WorkflowStep>) def.getSteps();
    }

    @RequestMapping(value = "{id}/step/get/{idStep}", method = RequestMethod.GET)
    public @ResponseBody
    WorkflowStep getStep(@PathVariable(value = "id") Long id,@PathVariable(value = "idStep") Long idStep, HttpServletRequest request, HttpServletResponse response){
        WorkflowDefinition def=admService.getWf(id);
        return admService.getStep(def, idStep);
    }

    @RequestMapping(value = "{id}/step/unSetStart/{idStep}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult unSetStart(@PathVariable(value = "id") Long id,@PathVariable(value = "idStep") Long idStep, HttpServletRequest request, HttpServletResponse response){
        WorkflowDefinition def=admService.getWf(id);
        try {
            admService.wfUnSetStartPoint(def, admService.getStep(def, idStep));
        } catch (RestException e) {
            return new PostResult(e);
        }
        PostResult res=new PostResult("OK");
        //res.setRedirect(ControllerHandler.getBaseUrl(request)+"/app/admin/editWorkflow/"+id);
        return res;
    }

    @RequestMapping(value = "{id}/step/setStart/{idStep}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult setStart(@PathVariable(value = "id") Long id,@PathVariable(value = "idStep") Long idStep, HttpServletRequest request, HttpServletResponse response){
        WorkflowDefinition def=admService.getWf(id);
        try {
            admService.wfSetStartPoint(def, admService.getStep(def, idStep));
        } catch (RestException e) {
            return new PostResult(e);
        }
        PostResult res=new PostResult("OK");
        //res.setRedirect(ControllerHandler.getBaseUrl(request)+"/app/admin/editWorkflow/"+id);
        return res;
    }

    @RequestMapping(value = "{id}/step/setEnd/{idStep}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult setEnd(@PathVariable(value = "id") Long id,@PathVariable(value = "idStep") Long idStep, HttpServletRequest request, HttpServletResponse response){
        WorkflowDefinition def=admService.getWf(id);
        try {
            admService.wfSetEndPoint(def, admService.getStep(def, idStep));
        } catch (RestException e) {
            return new PostResult(e);
        }
        PostResult res=new PostResult("OK");
        //res.setRedirect(ControllerHandler.getBaseUrl(request)+"/app/admin/editWorkflow/"+id);
        return res;
    }

    @RequestMapping(value = "{id}/step/unSetEnd/{idStep}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult unSetEnd(@PathVariable(value = "id") Long id,@PathVariable(value = "idStep") Long idStep, HttpServletRequest request, HttpServletResponse response){
        WorkflowDefinition def=admService.getWf(id);
        try {
            admService.wfUnSetEndPoint(def, admService.getStep(def, idStep));
        } catch (RestException e) {
            return new PostResult(e);
        }
        PostResult res=new PostResult("OK");
        //res.setRedirect(ControllerHandler.getBaseUrl(request)+"/app/admin/editWorkflow/"+id);
        return res;
    }

    @RequestMapping(value = "{id}/step/delete/{idStep}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult deleteStep(@PathVariable(value = "id") Long id,@PathVariable(value = "idStep") Long idStep, HttpServletRequest request, HttpServletResponse response){
        WorkflowDefinition def=admService.getWf(id);
        try {
            admService.wfDeleteStep(def, idStep);
        } catch (RestException e) {
            return new PostResult(e);
        }
        PostResult res=new PostResult("OK");
        //res.setRedirect(ControllerHandler.getBaseUrl(request)+"/app/admin/editWorkflow/"+id);
        return res;
    }

    @RequestMapping(value = "{id}/flow/save", method = RequestMethod.POST)
    public @ResponseBody
    PostResult saveFlow (@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response){
        Long idFlow=null;
        if (request.getParameter("id")!=null && !request.getParameter("id").isEmpty()) idFlow=Long.parseLong(request.getParameter("id"));
        WorkflowDefinition def=admService.getWf(id);
        String name=request.getParameter("name");
        it.cineca.siss.axmr3.log.Log.info(getClass(),request.getParameter("source"));
        it.cineca.siss.axmr3.log.Log.info(getClass(),request.getParameter("target"));
        Long source=Long.parseLong(request.getParameter("source"));
        Long target=Long.parseLong(request.getParameter("target"));
        String setStatus=request.getParameter("setStatus");
        WorkflowStep s=admService.getStep(def,source);
        WorkflowStep d=admService.getStep(def, target);
        try {
            admService.wfAddFlow(name, def, s, d,setStatus,idFlow);
        } catch (RestException e) {
            return new PostResult(e);
        }
        PostResult res=new PostResult("OK");
        return res;
    }

    @RequestMapping(value = "{id}/flow/getAll", method = RequestMethod.GET)
    public @ResponseBody
    List<WorkflowSequenceFlow> getFlows(@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response){
        WorkflowDefinition def=admService.getWf(id);
        return (List<WorkflowSequenceFlow>) def.getFlows();
    }

    @RequestMapping(value = "{id}/flow/get/{idFlow}", method = RequestMethod.GET)
    public @ResponseBody
    WorkflowSequenceFlow getFlow(@PathVariable(value = "id") Long id,@PathVariable(value = "idFlow") Long idFlow, HttpServletRequest request, HttpServletResponse response){
        WorkflowDefinition def=admService.getWf(id);
        return admService.getFlow(def, idFlow);
    }

    @RequestMapping(value = "{id}/flow/delete/{idFlow}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult deleteFlow(@PathVariable(value = "id") Long id,@PathVariable(value = "idFlow") Long idFlow, HttpServletRequest request, HttpServletResponse response){
        WorkflowDefinition def=admService.getWf(id);
        try {
            admService.wfDeleteFlow(def, idFlow);
        } catch (RestException e) {
            return new PostResult(e);
        }
        PostResult res=new PostResult("OK");
        //res.setRedirect(ControllerHandler.getBaseUrl(request)+"/app/admin/editWorkflow/"+id);
        return res;
    }

    @RequestMapping(value = "{id}/field/save", method = RequestMethod.POST)
    public @ResponseBody
    PostResult saveFlowField (@PathVariable(value = "id") Long id, HttpServletRequest request, HttpServletResponse response){
        Long idFlow=Long.parseLong(request.getParameter("idFlow"));
        Long idField=null;
        if (request.getParameter("id")!=null && !request.getParameter("id").isEmpty()){
            idField=Long.parseLong(request.getParameter("id"));
        }
        String name=request.getParameter("name");
        String type=request.getParameter("type");
        boolean mandatory=false;
        if (request.getParameter("mandatory")!=null && !request.getParameter("mandatory").isEmpty()){
            it.cineca.siss.axmr3.log.Log.info(getClass(),"Trovo il parametro mandatory");
            mandatory=true;
        }
        WorkflowDefinition def=admService.getWf(id);
        WorkflowSequenceFlow flow=null;
        for (WorkflowSequenceFlow f:def.getFlows()){
            if (f.getId().equals(idFlow)) flow=f;
        }
        try {
            admService.addFlowField(def, flow, name, type, mandatory, idField);
        } catch (RestException e) {
            return new PostResult(e);
        }
        PostResult res=new PostResult("OK");
        return res;
    }

    @RequestMapping(value = "{id}/field/getAll", method = RequestMethod.GET)
    public @ResponseBody
    List<WorkflowMetadataField> getFields(@PathVariable(value = "id") Long id,HttpServletRequest request, HttpServletResponse response){
        WorkflowDefinition def=admService.getWf(id);
        WorkflowSequenceFlow flow=null;
        List<WorkflowMetadataField> ret=new LinkedList<WorkflowMetadataField>();
        if (def.getFlows()!=null) for (WorkflowSequenceFlow f:def.getFlows()){
            if (f.getFields()!=null) for (WorkflowMetadataField f1:f.getFields()){
                f1.setFlow(f);
                ret.add(f1);
            }
        }
        return ret;
    }

    @RequestMapping(value = "{id}/field/get/{idField}", method = RequestMethod.GET)
    public @ResponseBody
    WorkflowMetadataField getField(@PathVariable(value = "id") Long id,@PathVariable(value = "idField") Long idField, HttpServletRequest request, HttpServletResponse response){
        WorkflowDefinition def=admService.getWf(id);
        WorkflowSequenceFlow flow=null;
        WorkflowMetadataField field=null;
        for (WorkflowSequenceFlow f:def.getFlows()){
            for (WorkflowMetadataField f1:f.getFields()){
                if (f1.getId().equals(idField)) {
                    flow=f;
                    field=f1;
                    field.setFlow(f);
                }
            }
        }
        return field;
    }

    @RequestMapping(value = "{id}/field/delete/{idField}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult deleteFlowField(@PathVariable(value = "id") Long id,@PathVariable(value = "idField") Long idField, HttpServletRequest request, HttpServletResponse response){
        WorkflowDefinition def=admService.getWf(id);
        WorkflowSequenceFlow flow=null;
        for (WorkflowSequenceFlow f:def.getFlows()){
            for (WorkflowMetadataField f1:f.getFields()){
                if (f1.getId().equals(idField)) {
                    flow=f;
                }
            }
        }
        try {
            admService.deleteFlowField(def, flow, idField);
        } catch (RestException e) {
            return new PostResult(e);
        }
        PostResult res=new PostResult("OK");
        return res;
    }

    @RequestMapping(value = "{id}/action/save", method = RequestMethod.POST)
    public @ResponseBody
        PostResult createAction(@PathVariable(value = "id") Long id, HttpServletRequest request){
        WorkflowDefinition def=admService.getWf(id);
        Enumeration paramNames = request.getParameterNames();
        HashMap<String, String> data=new HashMap<String, String>();
        while (paramNames.hasMoreElements()){
            String paramName= (String) paramNames.nextElement();
            if (!request.getParameter(paramName).isEmpty() && !paramName.equals("idFlow") && !paramName.equals("actionType") && !paramName.equals("id"))
            data.put(paramName,request.getParameter(paramName));
        }
        Long idFlow=Long.parseLong(request.getParameter("idFlow"));
        String actionType=request.getParameter("actionType");
        try{
        admService.createAction(def, admService.getFlow(def,idFlow), actionType, data);
        }catch (RestException ex){
            return new PostResult(ex);
        }
        return new PostResult("OK");
    }

    @RequestMapping (value = "{id}/action/getWfAll")
    public @ResponseBody
    List<WorkFlowAction> getAllWfActions(@PathVariable(value = "id") Long id) throws RestException {
       return admService.getAllWfActions(admService.getWf(id));
    }

    @RequestMapping (value = "{id}/action/getAll/{idFlow}")
    public @ResponseBody
    List<WorkFlowAction> getAllActions(@PathVariable(value = "id") Long id,@PathVariable(value = "idFlow") Long idFlow) throws RestException {
        return admService.getFlowActions(admService.getFlow(admService.getWf(id), idFlow));
    }

    @RequestMapping (value = "{id}/action/delete/{idAction}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult deleteAction(@PathVariable(value = "id") Long id, @PathVariable(value = "idAction") Long idAction) throws RestException {
        admService.deleteWfAction(admService.getWf(id), idAction);
        return new PostResult("OK");
    }
         */

}
