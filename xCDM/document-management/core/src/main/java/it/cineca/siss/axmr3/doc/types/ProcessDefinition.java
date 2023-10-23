package it.cineca.siss.axmr3.doc.types;

import java.io.Serializable;
import java.util.LinkedList;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 13/12/13
 * Time: 14.09
 * To change this template use File | Settings | File Templates.
 */
public class ProcessDefinition implements Serializable {

    private org.activiti.engine.repository.ProcessDefinition instance;

    public ProcessDefinition(org.activiti.engine.repository.ProcessDefinition d){
        instance=d;
    }

    public String getKey(){
        return instance.getKey();
    }


    public static List<ProcessDefinition> fromList(List<org.activiti.engine.repository.ProcessDefinition> list){
        List<ProcessDefinition> ret=new LinkedList<ProcessDefinition>();
        for (org.activiti.engine.repository.ProcessDefinition d:list){
            ret.add(new ProcessDefinition(d));
        }
        return ret;
    }


}
