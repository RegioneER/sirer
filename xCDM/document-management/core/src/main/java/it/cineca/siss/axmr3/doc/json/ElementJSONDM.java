package it.cineca.siss.axmr3.doc.json;

import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.doc.entities.Element;
import it.cineca.siss.axmr3.doc.entities.ElementMetadata;
import it.cineca.siss.axmr3.doc.entities.ElementTemplate;
import it.cineca.siss.axmr3.doc.types.MetadataFieldType;
import org.codehaus.jackson.map.annotate.JsonView;

import java.util.*;

/**
 * Created by vmazzeo on 15/03/2016.
 */
public class ElementJSONDM extends ElementJSON {
    public ElementJSONDM(Element baseElement, IUser currUser, String option, int maxLevel) {
        super(baseElement, currUser, option, maxLevel);
    }

    public ElementJSONDM(Element baseElement, IUser currUser, String option) {
        super(baseElement, currUser, option);
    }

    @JsonView(ViewFilterJSON.Core.class)
    public HashMap<String, Object[]> getMetadata(){
        if(rule.equals("no-data")){
            return null;
        }
        HashMap<String, Object[]> ret=new HashMap<String, Object[]>();
        String ruleLink="";

        for (ElementMetadata d:element.getData()){
            boolean canView=false;
            /*for (ElementTemplate et:element.getElementTemplates()){
                if (et.getMetadataTemplate().equals(d.getTemplate())){
                    if (user==null) canView=true;
                    else {
                        if (et.getUserPolicy(user, element).isCanView()) canView=true;
                        else canView=false;
                    }
                }
            }*/
            /*if (!canView) continue;*/
            List<Object> datas=d.getVals();
            Object[] dd=null;
            if (d.getField().getType().equals(MetadataFieldType.ELEMENT_LINK)){
                //it.cineca.siss.axmr3.log.Log.info(getClass(),"Link----");
                if(!rule.equals("single")){
                    dd=new Object[datas.size()];
                    for (int i=0;i<datas.size();i++){
                        dd[i]=new ElementJSONDM((Element) datas.get(i), user, "single",0);
                    }
                }
                else{
                    dd=new Object[1];
                    for (int i=0;i<datas.size();i++){
                        dd[0] =  ((Element) datas.get(i)).getId();
                    }
                }
            }else {
                dd=datas.toArray();
            }
            ret.put(d.getTemplateName()+"_"+d.getFieldName(), dd);
        }
        if (this.metadataPlus != null && this.metadataPlus.size() > 0) {
            Iterator<String> itPlus = this.metadataPlus.keySet().iterator();
            while (itPlus.hasNext()) {
                String key = itPlus.next();
                ret.put(key, this.metadataPlus.get(key));
            }
        }
        return ret;
    }

    public ElementJSONDM getParent(){
        return null;
    }


    public Collection<ElementJSONDM> getChildren(){
        if(level>0){
            LinkedList<ElementJSONDM> ret=new LinkedList<ElementJSONDM>();
            ElementJSONDM currElement = null;
            for (Element d:element.getChildren()){
                currElement= new ElementJSONDM(d,user,"no-data",level-1);
                ret.add(currElement);
            }
            return ret;
        }else{
            return null;
        }
    }
}
