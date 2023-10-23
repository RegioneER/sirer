package it.cineca.siss.axmr3.doc.types;

import org.activiti.engine.history.HistoricProcessInstance;

import java.io.Serializable;
import java.util.LinkedList;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 13/12/13
 * Time: 14.12
 * To change this template use File | Settings | File Templates.
 */
public class HistoryProcessInstance implements Serializable {


    private HistoricProcessInstance instance;

    public HistoryProcessInstance(HistoricProcessInstance d){
        instance=d;
    }

    public String getKey(){
        return instance.getId();
    }

    public String getBusinessKey(){
        return instance.getBusinessKey();
    }

    public static List<HistoryProcessInstance> fromList(List<HistoricProcessInstance> list){
        List<HistoryProcessInstance> ret=new LinkedList<HistoryProcessInstance>();
        for (HistoricProcessInstance d:list){
            ret.add(new HistoryProcessInstance(d));
        }
        return ret;
    }

}
