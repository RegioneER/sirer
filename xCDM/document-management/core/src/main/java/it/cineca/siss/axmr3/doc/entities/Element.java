package it.cineca.siss.axmr3.doc.entities;

import it.cineca.siss.axmr3.authentication.IAuthority;
import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.doc.acl.Policy;
import it.cineca.siss.axmr3.doc.json.ElementJSON;
import it.cineca.siss.axmr3.doc.json.ViewFilterJSON;
import it.cineca.siss.axmr3.doc.types.MetadataFieldType;
import it.cineca.siss.axmr3.doc.web.services.DocumentService;
import org.codehaus.jackson.annotate.JsonIgnore;
import org.codehaus.jackson.map.ObjectMapper;
import org.codehaus.jackson.map.SerializationConfig;
import org.hibernate.annotations.BatchSize;

import javax.persistence.*;
import java.io.IOException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 31/07/13
 * Time: 12.22
 * To change this template use File | Settings | File Templates.
 */
@Entity
@Table (name = "DOC_OBJ")
public class Element extends BaseElementEntity {


    @OneToOne(fetch = FetchType.EAGER)
    @JoinColumn(name = "TYPE_ID")
    private ElementType type;
    @OneToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "FILE_ID", nullable = true)
    private File file;

    @OneToMany(fetch = FetchType.LAZY)
    @JoinColumn(name="AUDIT_FILE_ID")
    @OrderBy(value = "uploadDt desc")
    private Collection<AuditFile> auditFiles;

    @ManyToMany(fetch = FetchType.LAZY)
    @JoinTable(name="DOC_OBJ_DOC_OBJ_TEMPLATE",
    joinColumns=@JoinColumn(name="DOC_OBJ_ID", referencedColumnName="id"),
    inverseJoinColumns=@JoinColumn(name="ELEMENTTEMPLATES_ID", referencedColumnName="id"))
    private Collection<ElementTemplate> elementTemplates;
    /*,
            joinColumns=@JoinColumn(name="DOC_OBJ_ID", referencedColumnName="id"),
            inverseJoinColumns=@JoinColumn(name="ELEMENTTEMPLATES_ID", referencedColumnName="id")*/

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "PARENT_ID")
    private Element parent;

    @OneToMany (fetch = FetchType.LAZY, mappedBy = "parent")
    @OrderBy(value = "id")
    @BatchSize(size = 10)
    private Collection<Element> childs;
    @OneToMany(fetch = FetchType.LAZY)
    @JoinColumn(name="ELEMENT_ID")
    @OrderBy(value = "id")
    @BatchSize(size = 500)
    private Collection<ElementMetadata> data;
    @BatchSize(size = 10)
    @OneToMany (fetch = FetchType.LAZY, mappedBy = "element")
    private Collection<Acl> acls;
    @OneToMany(fetch = FetchType.LAZY)
    @JoinColumn(name="AUDIT_ID")
    @OrderBy(value = "modDt")
    private Collection<AuditMetadata> auditData;
    @OneToMany (fetch = FetchType.LAZY, mappedBy = "element")
    @OrderBy(value = "evDt")
    private Collection<Event> evs;
    @OneToMany(fetch = FetchType.LAZY)
    @JoinColumn(name="ELEMENT_ID")
    @OrderBy(value = "id")
    private Collection<Comment> comments;
    @Temporal(value = TemporalType.TIMESTAMP)
    @Column (name="INS_DT")
    private Calendar creationDt;
    @Temporal(value = TemporalType.TIMESTAMP)
    @Column (name="UPD_DT")
    private Calendar lastUpdateDt;
    @Column (name="INS_USERNAME")
    private String createUser;
    @Column (name="UPD_USERNAME")
    private String lastUpdateUser;
    @Column (name="IS_LOCKED")
    private boolean locked=false;
    @Column(name="LOCKED_BY",nullable = true)
    private String lockedFromUser;
    @Column(name="LOCK_DT",nullable = true)
    @Temporal(value = TemporalType.TIMESTAMP)
    private Calendar lockDt;
    @Column (name = "DELETED")
    private boolean deleted=false;
    @Column (name = "DELETE_DT")
    @Temporal(value = TemporalType.TIMESTAMP)
    private Calendar deleteDt;
    @Column (name = "DELETED_BY")
    private String deletedBy;
    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "ORIG_ID")
    private Element original;
    @Column (name = "DRAFT")
    private boolean draft=false;
    @Column(name = "POS", nullable = true)
    private Long position;
    @Transient
    private boolean inEmendamento = false;
    @Transient
    private boolean fallbackTemplatePolicy = false;
    @Transient
    private boolean templateFTLOverride = false;


    public Long getPosition() {
        return position;
    }

    public void setPosition(Long position) {
        this.position = position;
    }


    @Transient
    private DocumentService service;

    @Transient
    private int page;

    @Transient
    private int limit;

    @Transient
    private IUser user;


    public void setService(DocumentService service) {
        this.service = service;
    }

    public void setLimit(int limit) {
        this.limit = limit;
    }

    public void setPage(int page) {
        this.limit = page;
    }

    public void setUser(IUser user) {
        this.user = user;
    }

    @JsonIgnore
    public Long getNumChildren() {
        if(service!=null){
            return service.getNumChilds(user,this);
        }else{
            return null;
        }
    }

    @JsonIgnore
    public List<Element> getPagedChildren() {
        if(service!=null){
            return service.getChilds(user, this, page, limit);
        }else{
            return null;
        }
    }

    /*
    @OneToMany (fetch = FetchType.LAZY, mappedBy = "element")
    private Collection<ElementProcessInstance> processInstances;
     */
    public Collection<ElementTemplate> getElementTemplates() {
        return elementTemplates;
    }

    @JsonIgnore
    public ElementTypeAssociatedTemplate getAvailableTemplate(String template) {
        for(ElementTypeAssociatedTemplate currTpl:type.getAssociatedTemplates()){
            MetadataTemplate result = currTpl.getMetadataTemplate();
            if(result.getName().equals(template)){
                return currTpl;
            }
        }
        return null;
    }



    public void setElementTemplates(Collection<ElementTemplate> elementTemplates) {
        this.elementTemplates = elementTemplates;
    }

    /*
    public Collection<ElementProcessInstance> getProcessInstances() {
        return processInstances;
    }

    public void setProcessInstances(Collection<ElementProcessInstance> processInstances) {
        this.processInstances = processInstances;
    }
    */

    public String getTypeName() {
        return type.getTypeId();
    }
    public Long getTypeId() {
        return type.getId();
    }

    public boolean isDraft() {
        return draft;
    }

    public void setDraft(boolean draft) {
        this.draft = draft;
    }

    public Element getOriginal() {
		return original;
	}

	public void setOriginal(Element original) {
		this.original = original;
	}

	public boolean isDeleted() {
        return deleted;
    }

    public void setDeleted(boolean deleted) {
        this.deleted = deleted;
    }

    public Calendar getDeleteDt() {
        return deleteDt;
    }

    public void setDeleteDt(Calendar deleteDt) {
        this.deleteDt = deleteDt;
    }

    public String getDeletedBy() {
        return deletedBy;
    }

    public void setDeletedBy(String deletedBy) {
        this.deletedBy = deletedBy;
    }

    /*
    @JsonIgnore
    public Collection<WorkFlowInstance> getWfInstances() {
        return wfInstances;
    }

    public void setWfInstances(Collection<WorkFlowInstance> wfInstances) {
        this.wfInstances = wfInstances;
    }

    @OneToMany (fetch = FetchType.LAZY, mappedBy = "element")
    private Collection<WorkFlowInstance> wfInstances;
    */

    public Collection<AuditFile> getAuditFiles() {
        return auditFiles;
    }

    public void setAuditFiles(Collection<AuditFile> auditFiles) {
        this.auditFiles = auditFiles;
    }

    @JsonIgnore
    public Collection<Event> getEvs() {
        return evs;
    }

    public void setEvs(Collection<Event> evs) {
        this.evs = evs;
    }

    public Collection<AuditMetadata> getAuditData() {
        return auditData;
    }

    public void setAuditData(Collection<AuditMetadata> auditData) {
        this.auditData = auditData;
    }

    public String getLockedFromUser() {
        return lockedFromUser;
    }

    public void setLockedFromUser(String lockedFromUser) {
        this.lockedFromUser = lockedFromUser;
    }

    public Calendar getLockDt() {

        return lockDt;
    }

    public void setLockDt(Calendar lockDt) {
        this.lockDt = lockDt;
    }

    public boolean isLocked() {
        return locked;
    }

    public void setLocked(boolean locked) {
        this.locked = locked;
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

    @Override
    public String toString() {
        /*
        return "Element{" +
                "type=" + type +
                ", file=" + file +
                ", auditFiles=" + auditFiles +
                ", elementTemplates=" + elementTemplates +
                ", parent=" + parent +
                ", childs=" + childs +
                ", data=" + data +
                ", acls=" + acls +
                '}';
        */
        return "Element[id="+id.toString()+"]";
    }

    public Policy getUserPolicy(IUser user){
        return this.getUserPolicy(user, true);
    }

    public Policy getUserPolicy(IUser user, boolean goDeep){
        List<String> userAuths=new LinkedList<String>();
        for (IAuthority auth:user.getAuthorities()){
            userAuths.add(auth.getAuthority());
        }
        Policy pol=new Policy();
        for (Acl acl:acls){
            boolean isApplicable=false;
            for (AclContainer container:acl.getContainers()){
                if (container.getContainer()==null) continue;
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
                    if (this.isTemplateFTLOverride()){
                        pol.getFtlTemplates().clear();
                    }
                	pol.getFtlTemplates().add(acl.getDetailTemplate());
                }
            }
        }

        if (goDeep){
            Element parent=this.getParent();
            while (parent!=null){
                if (!parent.getUserPolicy(user, false).isCanView()){
                    pol.setCanView(false);
                }
                if (!parent.getUserPolicy(user, false).isCanBrowse()){
                    pol.setCanBrowse(false);
                }
                parent=parent.getParent();
            }
        }


        return pol;
    }

    public Collection<String> getAuthorities(){
        List<String> elAuths=new LinkedList<String>();


        for (Acl acl:acls){
            boolean isApplicable=false;
            for (AclContainer container:acl.getContainers()){

                if (container.isAuthority()){
                    elAuths.add(container.getContainer());
                }

            }

        }
        return elAuths;
    }

    public Collection<String> getUsers(){
        List<String> elAuths=new LinkedList<String>();


        for (Acl acl:acls){
            boolean isApplicable=false;
            for (AclContainer container:acl.getContainers()){

                if (!container.isAuthority()){
                    elAuths.add(container.getContainer());
                }

            }

        }
        return elAuths;
    }

    public Collection<Acl> getAcls() {
        if (acls == null) {
            acls = new LinkedHashSet<Acl>();
        }
        return acls;
    }

    public void setAcls(Collection<Acl> acls) {
        this.acls = acls;
    }

    public Collection<Comment> getComments() {
        return comments;
    }

    public void setComments(Collection<Comment> comments) {
        this.comments = comments;
    }


    public Collection<Element> getChilds() {
        if(childs==null){
            return new LinkedList<Element>();
        }
        return childs;
    }

    public Collection<Element> getChildren(){
        List<Element> children=new LinkedList<Element>();
        for (Element el:this.getChilds()){
            if (!el.isDeleted()) {
                //Check Fallback policy template
                if (service != null && service.getTemplatePolicyFallbackObjs() != null && service.getTemplatePolicyFallbackObjs().equalsIgnoreCase("ALL")){
                    el.setFallbackTemplatePolicy(true);
                }else if (service != null && service.getTemplatePolicyFallbackObjs() != null && !service.getTemplatePolicyFallbackObjs().equalsIgnoreCase("NONE")){
                    for(String s:service.getTemplatePolicyFallbackObjsList()){
                        if (el.getType().getTypeId().equalsIgnoreCase(s)){
                            el.setFallbackTemplatePolicy(true);
                            break;
                        }
                    }
                }
                //Check FTL Override policy template
                if (service != null && service.getTemplateFTLOverrideObjs() != null && service.getTemplateFTLOverrideObjs().equalsIgnoreCase("ALL")){
                    el.setTemplateFTLOverride(true);
                }else if (service != null && service.getTemplateFTLOverrideObjs() != null && !service.getTemplateFTLOverrideObjs().equalsIgnoreCase("NONE")){
                    for(String s:service.getTemplateFTLOverrideObjsList()){
                        if (el.getType().getTypeId().equalsIgnoreCase(s)){
                            el.setTemplateFTLOverride(true);
                            break;
                        }
                    }
                }
                children.add(el);
            }
        }
        return children;
    }

    public void setChilds(Collection<Element> childs) {
        this.childs = childs;
    }

    @JsonIgnore
    public Element getParent() {
        return parent;
    }



    public Element getAncient() {
        Element ancient=null;
        try {
            String ancientId=service.getElementIdStudio(this.getId().toString());
            ancient=service.getElement(ancientId);
        }
        catch (Exception e){
            e.printStackTrace();
        }
        return ancient;

    }
    public void setParent(Element parent) {
        this.parent = parent;
    }

    public Collection<ElementMetadata> getData() {
        if(data==null)  {
            data=new LinkedList<ElementMetadata>();
        }
        return data;
    }

    public void setData(Collection<ElementMetadata> data) {
        this.data = data;
    }

    @JsonIgnore
    public Collection<MetadataTemplate> getTemplates() {
        List<MetadataTemplate> ret=new LinkedList<MetadataTemplate>();
        for (ElementTemplate et:getElementTemplates()){
            if (et.isEnabled()) ret.add(et.getMetadataTemplate());
        }
        return ret;
    }

    /*
    public void setTemplates(Collection<MetadataTemplate> templates) {
        this.templates = templates;
    }
    */

    @JsonIgnore
    public List<Object> getfieldData(String template, String field){
        List<Object> ret=new LinkedList<Object>();
        for (ElementMetadata m:this.getData()){
            if (m.getTemplate().getName().equals(template) && m.getField().getName().equals(field)) ret = m.getVals();
        }
        return ret;
    }


    @JsonIgnore
    public List<String> getFieldDataCodes(String template, String field){
        List<String> ret=new LinkedList<String>();
        for (ElementMetadata m:this.getData()){
            if (m.getTemplate().getName().equals(template) && m.getField().getName().equals(field)) {
                for (ElementMetadataValue v:m.getValues()){
                    ret.add(v.getCode());
                }
            }
        }
        return ret;
    }

    @JsonIgnore
    public String getFieldDataCode(String template, String field){
        String ret="";
        Collection<ElementMetadataValue> values;
        if (this.getData()!=null && this.getData().size()>0) {
            for (ElementMetadata m : this.getData()) {
                if (m.getTemplate().getName().equals(template) && m.getField().getName().equals(field)) {
                    values = m.getValues();
                    if (values != null && !values.isEmpty()) {
                        String temp=values.iterator().next().getCode();
                        if(temp!=null)ret =temp;
                    }
                }
            }
        }
        return ret;
    }

    @JsonIgnore
    public String getFieldDataCode(String templateAndField){
        String[] split = templateAndField.split("_");
        String template=split[0];
        String field=split[1];
        return getFieldDataCode(template,field);
    }


    @JsonIgnore
    public String getFieldDataDecode(String template, String field){
        String ret="";
        Collection<ElementMetadataValue> values;
        for (ElementMetadata m:this.getData()){
            if (m.getTemplate().getName().equals(template) && m.getField().getName().equals(field)) {
                values = m.getValues();
                if (values!=null && !values.isEmpty()){
                    String temp=values.iterator().next().getDecode();
                    if(temp!=null)ret=temp;
                }
            }
        }
        return ret;
    }

    @JsonIgnore
    public List<String> getFieldDataDecodes(String template, String field){
        List<String> ret=new LinkedList<String>();
        for (ElementMetadata m:this.getData()){
            if (m.getTemplate().getName().equals(template) && m.getField().getName().equals(field)) {
                for (ElementMetadataValue v:m.getValues()){
                    ret.add(v.getDecode());
                }
            }
        }
        return ret;
    }

    @JsonIgnore
    public List<String> getFieldDataStrings(String template, String field){
        List<String> ret=new LinkedList<String>();
        for (ElementMetadata m:this.getData()){
            if (m.getTemplate().getName().equals(template) && m.getField().getName().equals(field)) {
                for (ElementMetadataValue v:m.getValues()){
                    if (v.getTextValue()!=null)
                        ret.add(v.getTextValue());
                    if (v.getLongTextValue()!=null)
                        ret.add(v.getLongTextValue());
                }
            }
        }
        return ret;
    }

    @JsonIgnore
    public String getFieldDataString(String template, String field){

        List<String> ret = getFieldDataStrings(template,field);
        String retStr="";
        if(ret!=null && ret.size()>0 && ret.get(0)!=null){
            retStr=ret.get(0);
        }
        return retStr;
    }

    @JsonIgnore
    public String getFieldDataString(String templateAndField){
        String[] split = templateAndField.split("_");
        String template=split[0];
        String field=split[1];
        return getFieldDataString(template,field);

    }

    @JsonIgnore
    public List<Calendar> getFieldDataDates(String template, String field){
        List<Calendar> ret=new LinkedList<Calendar>();
        for (ElementMetadata m:this.getData()){
            if (m.getTemplate().getName().equals(template) && m.getField().getName().equals(field)) {
                for (ElementMetadataValue v:m.getValues()){
                    ret.add(v.getDate());
                }
            }
        }
        return ret;
    }

    @JsonIgnore
    public Calendar getFieldDataDate(String template, String field){
        Calendar ret= new GregorianCalendar(1000,00,01);
        loopData:
        for (ElementMetadata m:this.getData()){
            if (m.getTemplate().getName().equals(template) && m.getField().getName().equals(field)) {
                for (ElementMetadataValue v:m.getValues()){
                    ret=v.getDate();
                    break loopData;
                }
            }
        }
        return ret;
    }


    @JsonIgnore
    public List<String> getFieldDataFormattedDates(String template, String field, String format){
        List<String> ret=new LinkedList<String>();
        for (ElementMetadata m:this.getData()){
            if (m.getTemplate().getName().equals(template) && m.getField().getName().equals(field)) {
                for (ElementMetadataValue v:m.getValues()){
                    DateFormat df = new SimpleDateFormat(format);
                    if (v.getDate()!=null) ret.add(df.format(v.getDate().getTime()));
                }
            }
        }
        return ret;
    }

    @JsonIgnore
    public List<Element> getFieldDataElement(String template, String field){
        List<Element> ret=new LinkedList<Element>();
        for (ElementMetadata m:this.getData()){
            if (m.getTemplate().getName().equals(template) && m.getField().getName().equals(field)) {
                for (ElementMetadataValue v:m.getValues()){
                    if (v.getElement_link()!=null) ret.add(v.getElement_link());
                }
            }
        }
        return ret;
    }

    @JsonIgnore
    public List<Element> getFieldDataElement(String templateAndField){
        String[] split = templateAndField.split("_");
        String template=split[0];
        String field=split[1];

        it.cineca.siss.axmr3.log.Log.info(getClass(),template + "     " + field);

        return getFieldDataElement(template,field);

    }


    @JsonIgnore
    public File getFile() {
        return file;
    }

    public void setFile(File file) {
        this.file = file;
    }

    @JsonIgnore
    public ElementType getType() {
        return type;
    }

    public void setType(ElementType type) {
        this.type = type;
    }

    public List<Element> getChildrenByType(String typeId){
        List<Element> childs=new LinkedList<Element>();
        for (Element el:this.getChilds()){
            if (el.getType().getTypeId().equals(typeId) && !el.isDeleted()) childs.add(el);
        }
        return childs;
    }



    @JsonIgnore
    public String getElementJsonToString(IUser user) throws IOException {
        ObjectMapper mapper = new ObjectMapper();
        ElementJSON json = new ElementJSON(this,user,"complete",4);
        return mapper.writeValueAsString(json);
    }

    @JsonIgnore
    public String getElementJsonToString(IUser user, int level) throws IOException {
        ObjectMapper mapper = new ObjectMapper();
        ElementJSON json = new ElementJSON(this,user,"complete",level);
        return mapper.writeValueAsString(json);
    }

    @JsonIgnore
    public String getElementCoreJsonToString(IUser user) throws IOException {
        ObjectMapper mapper = new ObjectMapper();
        ElementJSON json = new ElementJSON(this,user,"complete");
        return mapper.configure(SerializationConfig.Feature.DEFAULT_VIEW_INCLUSION, false).writerWithView(ViewFilterJSON.Core.class).writeValueAsString(json);
    }

    public MetadataField getField(String templateName, String fieldName){
        MetadataField f=null;
        for (ElementMetadata md:this.getData()){
            if (md.getTemplateName().equals(templateName) && md.getFieldName().equals(fieldName)) f = md.getField();
        }
        return f;
    }

    public String getTitleString(){
        String title="";
        if (this.getType().getTitleRegex()!=null && !this.getType().getTitleRegex().isEmpty()){
            title=this.getType().getTitleRegex();
            String pattern="\\[(.*?)\\]";
            Pattern r=Pattern.compile(pattern);
            Matcher m=r.matcher(title);
            while(m.find()) {
                String[] fSpec=m.group(1).split("\\.");
                title=title.replaceAll("\\["+m.group(1)+"\\]", Matcher.quoteReplacement(buildTitleFromRegex(fSpec)));
            }

        }else if (this.getType().getTitleField()!=null){
            MetadataField tf = this.getType().getTitleField();
            title=getFirstTxtValue(tf);
        }
        return title;
    }

    protected String buildTitleFromRegex(String[] splitted){
        String replacement="";
        if (splitted.length>2){
            if (splitted[0].equals("parent")){
                String[] s2=new String[splitted.length-1];
                for (int i=1;i<splitted.length;i++){
                    s2[i-1]=splitted[i];
                }
                replacement=this.getParent().buildTitleFromRegex(s2);
            }
        }else {
            if (splitted.length==1){
                if (splitted[0].equals("id")){
                    replacement=this.getId()+"";
                }
                if (splitted[0].equals("position")){
                    replacement=this.getPosition()+"";
                }
            }else {
                String templateName=splitted[0];
                String fieldName=splitted[1];
                if (templateName.equals("file")){
                    if (this.getFile()!=null){
                        if (fieldName.equals("version") && this.getFile().getVersion()!=null) replacement=this.getFile().getVersion();
                        if (fieldName.equals("autore") && this.getFile().getAutore()!=null) replacement=this.getFile().getAutore();
                        if (fieldName.equals("note") && this.getFile().getNote()!=null) replacement=this.getFile().getNote();
                        if (fieldName.equals("name") && this.getFile().getFileName()!=null) replacement=this.getFile().getFileName();
                        if (fieldName.equals("date") && this.getFile().getDate()!=null) {
                            DateFormat df = new SimpleDateFormat("dd/MM/yyyy");
                            replacement=df.format(this.getFile().getDate());
                        }
                    }
                }else {
                    replacement=getFirstTxtValue(getField(templateName, fieldName));
                }
            }

        }
        return replacement;
    }

    public String getFirstTxtValue(MetadataField tf){
        if(tf==null) return "";
        if (tf.getType().equals(MetadataFieldType.EXT_DICTIONARY) || tf.getType().equals(MetadataFieldType.RADIO) || tf.getType().equals(MetadataFieldType.CHECKBOX) || tf.getType().equals(MetadataFieldType.SELECT)) {
            return getFieldDataDecode(tf.getTemplate().getName(), tf.getName());
        }else if (tf.getType().equals(MetadataFieldType.ELEMENT_LINK)) {
            return ((Element) getfieldData(tf.getTemplate().getName(), tf.getName()).get(0)).getTitleString();
        }else if (tf.getType().equals(MetadataFieldType.DATE)) {
            if (getFieldDataFormattedDates(tf.getTemplate().getName(), tf.getName(), "dd/MM/yyyy").size()>0)
                return getFieldDataFormattedDates(tf.getTemplate().getName(), tf.getName(), "dd/MM/yyyy").get(0);
            else return "";
        }else {
            return getFieldDataString(tf.getTemplate().getName(), tf.getName());
        }
    }

    public String applyRegexString(String regexString){
        String ret=regexString;
        String pattern="\\[(.*?)\\]";
        Pattern r=Pattern.compile(pattern);
        Matcher m=r.matcher(ret);
        while(m.find()) {
            String[] fSpec=m.group(1).split("\\.");
            ret=ret.replaceAll("\\["+m.group(1)+"\\]", buildTitleFromRegex(fSpec));
        }
        return ret;
    }


    public boolean getInEmendamento() {
        return inEmendamento;
    }

    public void setInEmendamento(boolean inEmendamento) {
        this.inEmendamento = inEmendamento;
    }

    public boolean isFallbackTemplatePolicy() {
        return fallbackTemplatePolicy;
    }

    public void setFallbackTemplatePolicy(boolean fallbackTemplatePolicy) {
        this.fallbackTemplatePolicy = fallbackTemplatePolicy;
    }

    public boolean isTemplateFTLOverride() {
        return templateFTLOverride;
    }

    public void setTemplateFTLOverride(boolean templateFTLOverride) {
        this.templateFTLOverride = templateFTLOverride;

    }

}
