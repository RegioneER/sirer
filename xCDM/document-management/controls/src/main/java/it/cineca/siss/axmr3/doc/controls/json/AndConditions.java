package it.cineca.siss.axmr3.doc.controls.json;

import java.io.Serializable;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by Carlo on 12/09/2016.
 */
public class AndConditions implements Serializable{

    protected List<Condition> and;

    public List<Condition> getAnd() {
        return and;
    }

    public void setAnd(List<Condition> and) {
        this.and = and;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        AndConditions that = (AndConditions) o;

        return and != null ? and.equals(that.and) : that.and == null;

    }

    @Override
    public int hashCode() {
        return and != null ? and.hashCode() : 0;
    }

    public String toJs(){
        String js="";
        for(Condition cnd:getAnd()){
            if (!js.isEmpty()) js+=" && ";
                js+=cnd.toJs();
        }
        return "("+js+")";
    }

    public List<String> getImpactedFields(){
        List<String> ifs=new LinkedList<String>();
        for (Condition cnd:getAnd()){
            for (String f:cnd.getImpactedFields()){
                if (!ifs.contains(f)) ifs.add(f);
            }
        }
        return ifs;
    }


}
