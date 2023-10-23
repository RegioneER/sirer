package it.cineca.siss.axmr3.doc.types;

import it.cineca.siss.axmr3.doc.web.services.DocumentService;

import java.io.Serializable;
import java.util.LinkedList;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 13/12/13
 * Time: 14.03
 * To change this template use File | Settings | File Templates.
 */
public class ProcessInstance implements Serializable {

    private org.activiti.engine.runtime.ProcessInstance instance;

    private ProcessDefinition definition;

    public ProcessInstance(org.activiti.engine.runtime.ProcessInstance p){
        instance=p;

    }

    public String getBusinessKey(){
        return instance.getBusinessKey();
    }

    public boolean isEnded(){
        return instance.isEnded();
    }

    public String getId(){
        return instance.getId();
    }

    public static List<ProcessInstance> fromList(List<org.activiti.engine.runtime.ProcessInstance> list, DocumentService service){
        List<ProcessInstance> ret=new LinkedList<ProcessInstance>();
        for (org.activiti.engine.runtime.ProcessInstance p:list){
            ProcessInstance pi=new ProcessInstance(p);
            pi.setDefinition(service.getProcessDefinition(p.getProcessDefinitionId()));
            ret.add(pi);
        }
        return ret;

    }

    public ProcessDefinition getDefinition() {
        return definition;
    }

    public void setDefinition(ProcessDefinition definition) {
        this.definition = definition;
    }
}
