package it.cineca.siss.axmr3.doc.entities;

import it.cineca.siss.axmr3.authentication.IAuthority;
import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.doc.acl.Policy;
import it.cineca.siss.axmr3.doc.json.ElementJSON;
import it.cineca.siss.axmr3.exceptions.AxmrGenericException;
import org.apache.commons.codec.binary.Base64;
import org.codehaus.jackson.annotate.JsonIgnore;
import org.codehaus.jackson.map.ObjectMapper;

import javax.persistence.*;
import java.io.IOException;
import java.util.*;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 31/07/13
 * Time: 17.32
 * To change this template use File | Settings | File Templates.
 */
@Entity
@Table(name = "DOC_TYPE")
public class ElementType extends BaseModelEntity {

    @Column (name="TYPE_NAME")
    private String typeId;
    @Column (name="CAN_BE_ROOT")
    private boolean rootAble;
    @Column (name="IS_CONTAINER")
    private boolean container;
    @Column (name="IS_SELF_RECURSIVE")
    private boolean selfRecursive;
    @Column (name="CAN_HAVE_FILE")
    private boolean hasFileAttached;
    @Column (name="CHECK_OUT_ENABLED")
    private boolean checkOutEnabled;

    @ManyToMany (fetch = FetchType.LAZY)
    @JoinTable(name="DOC_TYPE_DOC_TYPE",
            joinColumns=@JoinColumn(name="DOC_TYPE_ID", referencedColumnName="id"),
            inverseJoinColumns=@JoinColumn(name="ALLOWEDCHILDS_ID", referencedColumnName="id"))
    private Collection<ElementType> allowedChilds;
    /*,
            joinColumns=@JoinColumn(name="DOC_TYPE", referencedColumnName="id"),
            inverseJoinColumns=@JoinColumn(name="ALLOWED_CHILDS", referencedColumnName="id")*/
    @OneToMany (fetch = FetchType.LAZY)
    @JoinColumn(name = "TYPE_ID")
    @OrderBy("id asc")
    private Collection<ElementTypeAssociatedTemplate> associatedTemplates;
    @OneToMany (fetch = FetchType.LAZY)
    @JoinColumn(name = "TYPE_ID")
    @OrderBy("id asc")
    private Collection<ElementTypeAssociatedWorkflow> associatedWorkflows;
    @OneToMany (fetch = FetchType.LAZY, mappedBy = "type")
    private Collection<Acl> acls;
    @Lob
    @Column (name="IMG_BINARY")
    private byte[] img;
    @Column (name = "FTL_ROW")
    private String ftlRowTemplate;
    @Column (name = "FTL_DETAIL")
    private String ftlDetailTemplate;
    @Column (name = "FTL_FORM")
    private String ftlFormTemplate;
    @OneToOne(fetch = FetchType.EAGER)
    @JoinColumn(name = "TITLE_FIELD_ID")
    private MetadataField titleField;
    @Column (name = "DELETED")
    private boolean deleted=false;
    @Column (name = "DRAFTABLE")
    private boolean draftable=false;
    @Column (name="SEARCHABLE")
    private boolean searchable=false;
    @Column (name="TITLE_REGEX", nullable = true)
    private String titleRegex;
    @Column (name="NO_FILE_INFO", nullable = true)
    private boolean noFileinfo=false;
    @Column (name = "HASH")
    private String hashBack="";
    @Column (name = "GROUP_UP_LEVEL")
    private Long groupUpLevel=new Long(0);
    @Column(name = "sortable")
    private boolean sortable;
    @Column(name = "FILE_ON_FS", nullable = true,  columnDefinition = "NUMBER(1,0) DEFAULT 0")
    private Boolean fileOnFS;

    public Boolean getFileOnFS() {
        return fileOnFS;
    }

    public void setFileOnFS(Boolean fileOnFS) {
        this.fileOnFS = fileOnFS;
    }

    public boolean isSortable() {
        return sortable;
    }

    public void setSortable(boolean sortable) {
        this.sortable = sortable;
    }

    public Long getGroupUpLevel() {
        return groupUpLevel;
    }

    public void setGroupUpLevel(Long groupUpLevel) {
        this.groupUpLevel = groupUpLevel;
    }

    public String getHashBack() {
        return hashBack;
    }

    public void setHashBack(String hashBack) {
        this.hashBack = hashBack;
    }

    public boolean isNoFileinfo() {
        return noFileinfo;
    }

    public void setNoFileinfo(boolean noFileinfo) {
        this.noFileinfo = noFileinfo;
    }

    public String getTitleRegex() {
        return titleRegex;
    }

    public void setTitleRegex(String titleRegex) {
        this.titleRegex = titleRegex;
    }

    public boolean isSearchable() {
        return searchable;
    }

    public void setSearchable(boolean searchable) {
        this.searchable = searchable;
    }

    public boolean isDraftable() {
        return draftable;
    }

    public void setDraftable(boolean draftable) {
        this.draftable = draftable;
    }

    public boolean isDeleted() {
        return deleted;
    }

    public void setDeleted(boolean deleted) {
        this.deleted = deleted;
    }

    @JsonIgnore
    public MetadataField getTitleField() {
        return titleField;
    }

    public String getTitleTemplateName(){
        if (titleField!=null){
            return titleField.getTemplate().getName();
        }
        else return "";
    }

    public String getTitleFieldName(){
        if (titleField!=null){
            return titleField.getName();
        }
        else return "";
    }

    public void setTitleField(MetadataField titleField) {
        this.titleField = titleField;
    }

    public String getFtlDetailTemplate() {
        return ftlDetailTemplate;
    }

    public void setFtlDetailTemplate(String ftlDetailTemplate) {
        this.ftlDetailTemplate = ftlDetailTemplate;
    }

    public String getFtlFormTemplate() {
        return ftlFormTemplate;
    }

    public void setFtlFormTemplate(String ftlFormTemplate) {
        this.ftlFormTemplate = ftlFormTemplate;
    }

    public String getFtlRowTemplate() {
        return ftlRowTemplate;
    }

    public void setFtlRowTemplate(String ftlRowTemplate) {
        this.ftlRowTemplate = ftlRowTemplate;
    }

    public Collection<ElementTypeAssociatedWorkflow> getAssociatedWorkflows() {
        return associatedWorkflows;
    }

    public void setAssociatedWorkflows(Collection<ElementTypeAssociatedWorkflow> associatedWorkflows) {
        this.associatedWorkflows = associatedWorkflows;
    }

    public Collection<ElementTypeAssociatedTemplate> getAssociatedTemplates() {
        return associatedTemplates;
    }

    public void setAssociatedTemplates(Collection<ElementTypeAssociatedTemplate> associatedTemplates) {
        this.associatedTemplates = associatedTemplates;
    }

    public Collection<Acl> getAcls() {
        return acls;
    }

    public void setAcls(Collection<Acl> acls) {
        this.acls = acls;
    }

    public boolean isCheckOutEnabled() {
        return checkOutEnabled;
    }

    public void setCheckOutEnabled(boolean checkOutEnabled) {
        this.checkOutEnabled = checkOutEnabled;
    }

    @Override
    public String toString() {
        return "it.cineca.siss.axmr3.doc.entities.ElementType{" +
                "container=" + container +
                ", hasFileAttached=" + hasFileAttached +
                ", rootAble=" + rootAble +
                ", selfRecursive=" + selfRecursive +
                ", typeId='" + typeId + '\'' +
                '}';
    }

    @JsonIgnore
    public byte[] getImg() {
        return img;
    }

    public void setImg(byte[] img) {
        this.img = img;
    }

    public boolean isHasFileAttached() {
        return hasFileAttached;
    }

    public void setHasFileAttached(boolean hasFileAttached) {
        this.hasFileAttached = hasFileAttached;
    }

    @JsonIgnore
    public Collection<MetadataTemplate> getEnabledTemplates() {
        List<MetadataTemplate> ret=new LinkedList<MetadataTemplate>();
        if (this.associatedTemplates==null || this.associatedTemplates.size()==0) return ret;
        for (ElementTypeAssociatedTemplate md:this.associatedTemplates){
            if (md.isEnabled()) ret.add(md.getMetadataTemplate());
        }
        return ret;
    }

    @JsonIgnore
    public Collection<ElementType> getAllowedChilds() {
        return allowedChilds;
    }

    public List<String> getAllowedChildNames(){
        List<String> names=new LinkedList<String>();
        for (ElementType t:allowedChilds){
            names.add(t.getTypeId());
        }
        return names;
    }

    public void setAllowedChilds(Collection<ElementType> allowedChilds) {
        this.allowedChilds = allowedChilds;
    }

    public boolean isContainer() {
        return container;
    }

    public void setContainer(boolean container) {
        this.container = container;
    }

    public boolean isRootAble() {
        return rootAble;
    }

    public void setRootAble(boolean rootAble) {
        this.rootAble = rootAble;
    }

    public boolean isSelfRecursive() {
        return selfRecursive;
    }

    public void setSelfRecursive(boolean selfRecursive) {
        this.selfRecursive = selfRecursive;
    }

    public String getTypeId() {
        return typeId;
    }

    public void setTypeId(String typeId) {
        this.typeId = typeId;
    }

    public String getImageBase64(){
        if (img==null || img.length==0) return "";
        byte[] imgBytesAsBase64 = Base64.encodeBase64(this.img);
        String imgDataAsBase64 = new String(imgBytesAsBase64);
        String imgAsBase64 = "data:image/png;base64," + imgDataAsBase64;
        return imgAsBase64;
    }

    @JsonIgnore
    public Policy getUserPolicy(IUser user){
        List<String> userAuths=new LinkedList<String>();
        for (IAuthority auth:user.getAuthorities()){
            userAuths.add(auth.getAuthority());
        }
        Policy pol=new Policy();
        for (Acl acl:acls){
            boolean isApplicable=false;
            for (AclContainer container:acl.getContainers()){
                if (!container.isAuthority() && container.getContainer().equals("*")) isApplicable=true;
                if (container.isAuthority()){
                    for (String auth:userAuths) if (container.getContainer().equals(auth)) {
                        isApplicable=true;
                    }
                }
                if (!container.isAuthority() && user.getUsername().equals(container.getContainer())) isApplicable=true;
            }
            if (isApplicable){
                Policy thisPol=new Policy(acl.getPolicyValue());
                if (!pol.isCanCreate()) pol.setCanCreate(thisPol.isCanCreate());
                if (!pol.isCanAddChild())  pol.setCanAddChild(thisPol.isCanAddChild());
                if (!pol.isCanAddComment()) pol.setCanAddComment(thisPol.isCanAddComment());
                if (!pol.isCanChangePermission()) pol.setCanChangePermission(thisPol.isCanChangePermission());
                if (!pol.isCanDelete()) pol.setCanDelete(thisPol.isCanDelete());
                if (!pol.isCanModerate()) pol.setCanModerate(thisPol.isCanModerate());
                if (!pol.isCanRemoveCheckOut()) pol.setCanRemoveCheckOut(thisPol.isCanRemoveCheckOut());
                if (!pol.isCanUpdate()) pol.setCanUpdate(thisPol.isCanUpdate());
                if (!pol.isCanView()) pol.setCanView(thisPol.isCanView());
                if (!pol.isCanLaunchProcess()) pol.setCanLaunchProcess(thisPol.isCanLaunchProcess());
                if (!pol.isCanEnableTemplate()) pol.setCanEnableTemplate(thisPol.isCanEnableTemplate());
                if (!pol.isCanBrowse()) pol.setCanBrowse(thisPol.isCanBrowse());
                if (acl.getDetailTemplate()!=null){
                    if (pol.getFtlTemplates()==null) pol.setFtlTemplates(new LinkedList<String>());
                    pol.getFtlTemplates().add(acl.getDetailTemplate());
                }
            }
        }
        return pol;
    }

    @JsonIgnore
    public Element getDummy() throws AxmrGenericException {
        /*
        Element parent=null;
        if (data.containsKey("parentId") && data.get("parentId")!=null){
            parent=docService.getElement(Long.parseLong((String) data.get("parentId")));
            data.remove("parentId");
        }
        */
        Element example=new Element();
        //if(parent!=null)example.setParent(parent);
        example.setType(this);
        //example.setTemplates(new LinkedList<MetadataTemplate>());
        example.setElementTemplates(new LinkedList<ElementTemplate>());
        for (ElementTypeAssociatedTemplate t:this.getAssociatedTemplates()){
            //it.cineca.siss.axmr3.log.Log.info(getClass(),"template -- "+t.toString());
            ElementTemplate et=new ElementTemplate();
            et.setMetadataTemplate(t.getMetadataTemplate());
            et.setEnabled(true);
            et.setTemplateAcls(t.getTemplateAcls());
            example.getElementTemplates().add(et);
        }
        Iterator<MetadataTemplate> dataIt = example.getTemplates().iterator();
        while (dataIt.hasNext()){

            MetadataTemplate t=dataIt.next();

            for (MetadataField f:t.getFields()){
                ElementMetadata md=new ElementMetadata();
                md.setField(f);
                md.setTemplate(t);
                md.setVal("");
                if(md!=null) {
                    example.getData().add(md);
                }
            }

        }
        return example;
    }

    @JsonIgnore
    public List<String> getFtlTemplates(){
        LinkedList<String> result=new LinkedList<String>();

        if(ftlDetailTemplate!=null &&!ftlDetailTemplate.equals("")) {
            result.add(ftlDetailTemplate) ;
        }
        for(Acl acl:acls){
            if(acl.getDetailTemplate()!=null && !acl.getDetailTemplate().equals("")){
                result.add(acl.getDetailTemplate()) ;
            }
        }

        return result;
    }

    @JsonIgnore
    public String getDummyJson() throws IOException, AxmrGenericException {
        ObjectMapper mapper = new ObjectMapper();
        ElementJSON json = new ElementJSON(getDummy(),null,"single");
        return mapper.writeValueAsString(json);
    }

    @JsonIgnore
    public MetadataTemplate byTemplateName(String name){
        //it.cineca.siss.axmr3.log.Log.info(getClass(),"\n\n Cerco il template "+name);
        for (ElementTypeAssociatedTemplate at:getAssociatedTemplates()){
            //it.cineca.siss.axmr3.log.Log.info(getClass(),"\n\n Trovo il template "+at.getMetadataTemplate().getName()+" e cerco il template "+name);
            if (at.getMetadataTemplate().getName().equals(name)) return at.getMetadataTemplate();
        }
        return null;
    }

    @JsonIgnore
    public HashMap<String, ElementTypeAssociatedTemplate> getAssociatedTemplateMap(){
        HashMap<String, ElementTypeAssociatedTemplate> ret=new HashMap<String, ElementTypeAssociatedTemplate>();
        //it.cineca.siss.axmr3.log.Log.info(getClass(),"\n\n Cerco il template "+name);
        for (ElementTypeAssociatedTemplate at:getAssociatedTemplates()){
            //it.cineca.siss.axmr3.log.Log.info(getClass(),"\n\n Trovo il template "+at.getMetadataTemplate().getName()+" e cerco il template "+name);
            ret.put(at.getMetadataTemplate().getName(),at);
        }
        return ret;
    }


    public HashMap<String, ElementTypeAssociatedWorkflow> getAssociatedWorkflowMap(){
        HashMap<String, ElementTypeAssociatedWorkflow> ret=new HashMap<String, ElementTypeAssociatedWorkflow>();
        for (ElementTypeAssociatedWorkflow aWF:getAssociatedWorkflows()){
            ret.put(aWF.getProcessKey(),aWF);
        }
        return ret;
    }

    @JsonIgnore
    public HashMap<String, ElementType> getAllowedChildrenMap(){
        HashMap<String, ElementType> ret=new HashMap<String, ElementType>();
        //it.cineca.siss.axmr3.log.Log.info(getClass(),"\n\n Cerco il template "+name);
        for (ElementType child:getAllowedChilds()){
            //it.cineca.siss.axmr3.log.Log.info(getClass(),"\n\n Trovo il template "+at.getMetadataTemplate().getName()+" e cerco il template "+name);
            ret.put(child.getTypeId(),child);
        }
        return ret;
    }

    @Override
    public boolean equals(Object o) {
        it.cineca.siss.axmr3.log.Log.info(getClass(),"DEBUG -- equals type 1");
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        //if (!super.equals(o)) return false;

        ElementType that = (ElementType) o;
        it.cineca.siss.axmr3.log.Log.info(getClass(),"DEBUG -- equals type 2");
        if (checkOutEnabled != that.checkOutEnabled) return false;
        it.cineca.siss.axmr3.log.Log.info(getClass(),"DEBUG -- equals type 3");
        if (container != that.container) return false;
        it.cineca.siss.axmr3.log.Log.info(getClass(),"DEBUG -- equals type 4");
        if (deleted != that.deleted) return false;
        it.cineca.siss.axmr3.log.Log.info(getClass(),"DEBUG -- equals type 5");
        if (draftable != that.draftable) return false;
        it.cineca.siss.axmr3.log.Log.info(getClass(),"DEBUG -- equals type 6");
        if (hasFileAttached != that.hasFileAttached) return false;
        it.cineca.siss.axmr3.log.Log.info(getClass(),"DEBUG -- equals type 7");
        if (noFileinfo != that.noFileinfo) return false;
        it.cineca.siss.axmr3.log.Log.info(getClass(),"DEBUG -- equals type 8");
        if (rootAble != that.rootAble) return false;
        it.cineca.siss.axmr3.log.Log.info(getClass(),"DEBUG -- equals type 9");
        if (searchable != that.searchable) return false;
        it.cineca.siss.axmr3.log.Log.info(getClass(),"DEBUG -- equals type 10");
        if (selfRecursive != that.selfRecursive) return false;
        it.cineca.siss.axmr3.log.Log.info(getClass(),"DEBUG -- equals type 11");
        if (ftlDetailTemplate != null ? !ftlDetailTemplate.equals(that.ftlDetailTemplate) : that.ftlDetailTemplate != null)
            return false;
        it.cineca.siss.axmr3.log.Log.info(getClass(),"DEBUG -- equals type 12");
        if (ftlFormTemplate != null ? !ftlFormTemplate.equals(that.ftlFormTemplate) : that.ftlFormTemplate != null)
            return false;
        it.cineca.siss.axmr3.log.Log.info(getClass(),"DEBUG -- equals type 13");
        if (ftlRowTemplate != null ? !ftlRowTemplate.equals(that.ftlRowTemplate) : that.ftlRowTemplate != null)
            return false;
        it.cineca.siss.axmr3.log.Log.info(getClass(),"DEBUG -- equals type 14");
        if (hashBack != null ? !hashBack.equals(that.hashBack) : that.hashBack != null) return false;
        it.cineca.siss.axmr3.log.Log.info(getClass(),"DEBUG -- equals type 15");
        if (!Arrays.equals(img, that.img)) return false;
        it.cineca.siss.axmr3.log.Log.info(getClass(),"DEBUG -- equals type 16");
        /*if (titleField != null ? !titleField.equals(that.titleField) : that.titleField != null) return false;
        it.cineca.siss.axmr3.log.Log.info(getClass(),"DEBUG -- equals type 17");*/
        if (titleRegex != null ? !titleRegex.equals(that.titleRegex) : that.titleRegex != null) return false;
        it.cineca.siss.axmr3.log.Log.info(getClass(),"DEBUG -- equals type 18");
        if (groupUpLevel != null ? !groupUpLevel.equals(that.groupUpLevel) : that.groupUpLevel != null) return false;
        it.cineca.siss.axmr3.log.Log.info(getClass(),"DEBUG -- equals type 19");
        if (typeId != null ? !typeId.equals(that.typeId) : that.typeId != null) return false;
        it.cineca.siss.axmr3.log.Log.info(getClass(),"DEBUG -- equals type 20");

        return true;
    }

    @Override
    public int hashCode() {
        int result = super.hashCode();
        result = 31 * result + (typeId != null ? typeId.hashCode() : 0);
        return result;
    }
}
