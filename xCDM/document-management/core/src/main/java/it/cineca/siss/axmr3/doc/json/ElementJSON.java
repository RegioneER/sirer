package it.cineca.siss.axmr3.doc.json;
import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.doc.entities.*;
import it.cineca.siss.axmr3.doc.types.MetadataFieldType;
import org.codehaus.jackson.annotate.JsonIgnore;
import org.codehaus.jackson.map.annotate.JsonView;

import java.util.*;

/**
 * Created with IntelliJ IDEA.
 * User: giorgio
 * Date: 20/09/13
 * Time: 13.09
 * To change this template use File | Settings | File Templates.
 */
public class  ElementJSON {
    protected Element element=null;
    protected String rule="";
    protected int level=1;
    protected IUser user=null;
    protected Calendar creationDt;
    protected Calendar lastUpdateDt;
    protected String createUser;
    protected String lastUpdateUser;
    protected HashMap<String, Object[]> metadataPlus;

    public ElementJSON(Element baseElement,IUser currUser,String option){
        this(baseElement, currUser, option, 1);
    }


    public String getRule() {
        return rule;
    }

    public void setRule(String rule) {
        this.rule = rule;
    }

    public int getLevel() {
        return level;
    }

    public void setLevel(int level) {
        this.level = level;
    }

    public ElementJSON(Element baseElement, IUser currUser, String option, int maxLevel){
        element=baseElement;
        rule=option;
        user=currUser;
        level=maxLevel;
        createUser= element.getCreateUser();
        lastUpdateUser= element.getLastUpdateUser();
        lastUpdateDt=element.getLastUpdateDt();
        creationDt=element.getCreationDt();
    }

    public ElementJSON getParent(){
        if (rule.equals("complete-without-parent")) return null;
        if (rule.equals("single")) return null;
        //if (!rule.equals("single-with-parent") && !rule.equals("complete")) return null;
        if (element.getParent()!=null)
        return new ElementJSON(element.getParent(), user, "single-with-parent");
        else return null;
    }

    @JsonView(ViewFilterJSON.Core.class)
    public String getParentId(){
        if(element.getParent()!=null){
            return element.getParent().getId().toString();
        }
        else{
            return "";
        }
    }
    @JsonView(ViewFilterJSON.Core.class)
    public String getParentTypeId(){
        if(element.getParent()!=null){
            return element.getParent().getType().getTypeId().toString();
        }
        else{
            return "";
        }
    }

    public Calendar getCreationDt() {
        return creationDt;
    }

    public void setCreationDt(Calendar creationDt) {
        this.creationDt = creationDt;
    }

    public Calendar getLastUpdateDt() {
        return lastUpdateDt;
    }

    public void setLastUpdateDt(Calendar lastUpdateDt) {
        this.lastUpdateDt = lastUpdateDt;
    }

    public String getCreateUser() {
        return createUser;
    }

    public void setCreateUser(String createUser) {
        this.createUser = createUser;
    }

    public String getLastUpdateUser() {
        return lastUpdateUser;
    }

    public void setLastUpdateUser(String lastUpdateUser) {
        this.lastUpdateUser = lastUpdateUser;
    }


    @JsonView(ViewFilterJSON.Core.class)
    public HashMap<String, Object[]> getMetadata(){
        HashMap<String, Object[]> ret=new HashMap<String, Object[]>();
        String ruleLink="";

        for (ElementMetadata d:element.getData()){
            boolean canView=false;
            for (ElementTemplate et:element.getElementTemplates()){
                if (et.getMetadataTemplate().equals(d.getTemplate())){
                    if (user==null) canView=true;
                    else {
                        if (et.getUserPolicy(user, element).isCanView()) canView=true;
                        else canView=false;
                    }
                }
            }
            if (!canView) continue;
        	List<Object> datas=d.getVals();
        	Object[] dd=null;
        	if (d.getField().getType().equals(MetadataFieldType.ELEMENT_LINK)){
        		//it.cineca.siss.axmr3.log.Log.info(getClass(),"Link----");
                if(!rule.equals("single")){
                    dd=new Object[datas.size()];
                    for (int i=0;i<datas.size();i++){
                        if (((Element) datas.get(i)).getUserPolicy(user).isCanView()) dd[i]=new ElementJSON((Element) datas.get(i), user, "single",0);
                        else
                        dd[i]=null;
                    }
                }
                else{
                    if(!rule.equals("single-with-parent")){
                        if(rule.equals("complete-without-parent")) {
                            ruleLink="single";
                        }else{
                            ruleLink="single-with-parent";
                        }
                        dd=new Object[datas.size()];
                        for (int i=0;i<datas.size();i++){
                            if (((Element) datas.get(i)).getUserPolicy(user).isCanView()) dd[i]=new ElementJSON((Element) datas.get(i), user, ruleLink,0);
                            else
                                dd[i]=null;
                        }
                    }else{
                        dd=new Object[1];
                        for (int i=0;i<datas.size();i++){
                            if (((Element) datas.get(i)).getUserPolicy(user).isCanView()) dd[0] =  ((Element) datas.get(i)).getId();
                        }
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


    public Collection<? extends ElementJSON> getChildren(){
        if (rule.equals("single")) return null;
        if (rule.equals("single-with-parent")) return null;
        if(level>0){
            LinkedList<ElementJSON> ret=new LinkedList<ElementJSON>();
            ElementJSON currElement = null;
            for (Element d:element.getChildren()){
                currElement= new ElementJSON(d,user,rule,level-1);
                ret.add(currElement);
            }
            return ret;
        }else{
            return null;
        }
    }

    public String getTitle(){
    	try{
        MetadataField titleField=element.getType().getTitleField();
        if(titleField!=null){
            for (ElementMetadata md:element.getData()){
                if (md!=null && md.getField()!=null && md.getField().getId()!=null && titleField.getId()!=null && md.getField().getId().equals(titleField.getId()) && md.getVals()!=null && md.getVals().get(0)!=null){
                    //it.cineca.siss.axmr3.log.Log.info(getClass(),(String) md.getVals().get(0));
                    return (String) md.getVals().get(0);
                }
            }
        }
        }catch(Exception ex){
        }
        return "";
    }

    @JsonView(ViewFilterJSON.Core.class)
    public String getTitleString(){
        try{
        return element.getTitleString();
        }catch(Exception ex){
        }
        return "";
    }

    @JsonView(ViewFilterJSON.Core.class)
    public Long getId(){
        return element.getId();
    }

    @JsonView(ViewFilterJSON.Core.class)
    public Long getPosition() {
        return element.getPosition();
    }


    @JsonView(ViewFilterJSON.Core.class)
    public HashMap<String, String> getType(){
        HashMap<String, String> ret=new HashMap<String, String>();
        ElementType type = element.getType();
        ret.put("typeId",type.getTypeId());
        ret.put("id",type.getId().toString());
        return ret;
    }

    @JsonIgnore
    public Collection<ElementJSON> getHistory(){
        LinkedList<ElementJSON> ret=new LinkedList<ElementJSON>();
        ElementJSON currElement = null;
        for (Element d:element.getChilds()){
        	if (d.getUserPolicy(user).isCanView()) {
        		currElement= new ElementJSON(d,user,rule);
            	ret.add(currElement);
        	}
        }
        return ret;
    }

    public FileJSON getFile(){
        if (element.getType().isHasFileAttached() && element.getFile()!=null) return new FileJSON(element.getFile());
        else return null;
    }

    public List<AuditFileJSON> getAuditFiles(){
        List<AuditFileJSON> ret=new LinkedList<AuditFileJSON>();

        if (element.getType().isHasFileAttached() && element.getAuditFiles()!=null && element.getAuditFiles().size()>0) {
            for (AuditFile f:element.getAuditFiles()){
                ret.add(new AuditFileJSON(f));
            }
        }
        return ret;
    }

    public void pushMetadata(String key, Object[] values) {
        if (this.metadataPlus == null) this.metadataPlus = new HashMap<String, Object[]>();
        this.metadataPlus.put(key, values);
    }
    /*
    public Policy getUserPolicy(){
        return element.getUserPolicy(user);
    }
    public Long getId(){
        return element.getId();
    }
    */
}
