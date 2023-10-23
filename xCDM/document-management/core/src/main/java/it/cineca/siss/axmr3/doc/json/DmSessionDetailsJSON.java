package it.cineca.siss.axmr3.doc.json;

import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.doc.entities.AuditMetadata;
import it.cineca.siss.axmr3.doc.entities.DataManagementAction;
import it.cineca.siss.axmr3.doc.entities.DataManagementSession;

import java.util.*;

/**
 * Created by vmazzeo on 13/01/2016.
 */
public class DmSessionDetailsJSON {

    private DataManagementSession dm;
    private HashMap<Long,List<DmActionJSON>> elementActions;
    private HashMap<Long,ElementJSON> elements;
    private HashMap<String,String> fieldLabels;
    private HashMap<String,String> fieldTypes;

    public HashMap<String, String> getFieldTypes() {
        return fieldTypes;
    }

    public void setFieldTypes(HashMap<String, String> fieldTypes) {
        this.fieldTypes = fieldTypes;
    }

    public HashMap<String, String> getFieldLabels() {
        return fieldLabels;
    }

    public void setFieldLabels(HashMap<String, String> fieldLabels) {
        this.fieldLabels = fieldLabels;
    }

    public DataManagementSession getDm() {
        return dm;
    }

    public void setDm(DataManagementSession dm) {
        this.dm = dm;
    }

    public Long getSessionId(){
        return this.dm.getId();
    }

    public HashMap<Long,List<DmActionJSON>> getElementActions(){
        return elementActions;
    }

    public HashMap<Long, ElementJSON> getElements() {
        return elements;
    }

    public void setElements(HashMap<Long, ElementJSON> elements) {
        this.elements = elements;
    }

    public void addElementAction(DataManagementAction action, IUser user){
        if(elementActions==null){
            elementActions=new HashMap<Long, List<DmActionJSON>>();
        }

        if(elementActions.containsKey(action.getElementId())){
            elementActions.get(action.getElementId()).add(new DmActionJSON(action));
        }
        else{
            LinkedList<DmActionJSON> actions=new LinkedList<DmActionJSON>();
            actions.add(new DmActionJSON(action));
            elementActions.put(action.getElementId(),actions);

            ElementJSON ej=new ElementJSON(action.getObjId(),user,"single");
            if(elements==null){
                elements=new HashMap<Long,ElementJSON>();
                elements.put(action.getElementId(),ej);
            }
            else{
                if(!elements.containsKey(action.getElementId())){
                    elements.put(action.getElementId(),ej);
                }
            }
        }
    }

    public void addElementActionAudit(AuditMetadata amd, Properties props){

        Iterator<Long> it=elementActions.keySet().iterator();
        while (it.hasNext()){
            Long elId=it.next();
            for (DmActionJSON dm:elementActions.get(elId)){
                if (dm.getActionId()==amd.getDmActionId()){
                    if (fieldLabels==null){
                        fieldLabels=new HashMap<String, String>();
                    }
                    if (fieldTypes==null){
                        fieldTypes=new HashMap<String, String>();
                    }
                    String fieldId=amd.getField().getTemplate().getName()+"_"+amd.getField().getName();
                    if (!getFieldLabels().containsKey(fieldId)){
                        if (props.get(amd.getField().getTemplate().getName()+"."+amd.getField().getName())!=null){
                            fieldLabels.put(fieldId, (String) props.get(amd.getField().getTemplate().getName()+"."+amd.getField().getName()));
                            fieldTypes.put(fieldId,amd.getField().getType().name());
                        }else {
                            fieldLabels.put(fieldId, fieldId);
                            fieldTypes.put(fieldId,amd.getField().getType().name());
                        }

                    }
                    dm.addMdAudit(amd);
                }
            }
        }
    }

}
