package it.cineca.siss.axmr3.doc.controls.json;

import java.io.Serializable;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by Carlo on 12/09/2016.
 */
public class OrConditions implements Serializable{

    protected List<AndConditions> or;

    public List<AndConditions> getOr() {
        return or;
    }

    public void setOr(List<AndConditions> or) {
        this.or = or;
    }

    public String toJs(){
        String js="";
        for(AndConditions cnd:getOr()){
            if (!js.isEmpty()) js+=" || ";
            js+=cnd.toJs();
        }
        return "("+js+")";
    }

    public List<String> getImpactedFields(){
        List<String> ifs=new LinkedList<String>();
        for (AndConditions cnd:getOr()){
            for (String f:cnd.getImpactedFields()){
                if (!ifs.contains(f)) ifs.add(f);
            }
        }
        return ifs;
    }

}
