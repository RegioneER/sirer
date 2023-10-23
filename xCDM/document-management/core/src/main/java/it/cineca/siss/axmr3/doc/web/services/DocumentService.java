package it.cineca.siss.axmr3.doc.web.services;

import it.cineca.siss.axmr3.authentication.IAuthority;
import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.authentication.impl.AuthorityImpl;
import it.cineca.siss.axmr3.authentication.impl.UserImpl;
import it.cineca.siss.axmr3.common.mvc.handlers.ControllerHandler;
import it.cineca.siss.axmr3.doc.acl.Policy;
import it.cineca.siss.axmr3.doc.acl.TemplatePolicy;
import it.cineca.siss.axmr3.doc.beans.InternalServiceBean;
import it.cineca.siss.axmr3.doc.entities.File;
import it.cineca.siss.axmr3.doc.entities.*;
import it.cineca.siss.axmr3.doc.json.JqGridJSON;
import it.cineca.siss.axmr3.doc.types.CalendarEvent;
import it.cineca.siss.axmr3.doc.types.MetadataFieldType;
import it.cineca.siss.axmr3.doc.types.SearchType;
import it.cineca.siss.axmr3.doc.utils.FormSpecification;
import it.cineca.siss.axmr3.doc.utils.FormSpecificationField;
import it.cineca.siss.axmr3.doc.web.exceptions.RestException;
import it.cineca.siss.axmr3.doc.xml.CheckResult;
import it.cineca.siss.axmr3.doc.xml.Field;
import it.cineca.siss.axmr3.doc.xml.Form;
import it.cineca.siss.axmr3.exceptions.AxmrGenericException;
import it.cineca.siss.axmr3.hibernate.BaseDao;
import it.cineca.siss.axmr3.transactions.Axmr3TXManager;
import it.cineca.siss.axmr3.transactions.MultiSessionTXManager;
import it.cineca.siss.axmr3.web.freemarker.AxmrFreemarkerConfigurer;
import jxl.Cell;
import jxl.Sheet;
import jxl.Workbook;
import jxl.read.biff.BiffException;
import jxl.write.Label;
import jxl.write.WritableSheet;
import jxl.write.WritableWorkbook;
import jxl.write.WriteException;
import org.activiti.engine.ProcessEngine;
import org.activiti.engine.history.HistoricProcessInstance;
import org.activiti.engine.repository.ProcessDefinition;
import org.activiti.engine.runtime.ProcessInstance;
import org.activiti.engine.task.Task;
import org.apache.log4j.Logger;
import org.hibernate.Criteria;
import org.hibernate.SQLQuery;
import org.hibernate.criterion.*;
import org.hibernate.internal.util.SerializationHelper;
import org.springframework.beans.factory.InitializingBean;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.security.core.context.SecurityContextHolder;
import org.w3c.dom.Document;
import org.xml.sax.SAXException;

import javax.servlet.http.HttpServletRequest;
import javax.sql.DataSource;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.*;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 01/08/13
 * Time: 11.05
 * To change this template use File | Settings | File Templates.
 */
//TODO: trasformare tutte le eccezioni in RestException
public class DocumentService implements InitializingBean {
    private MultiSessionTXManager txManager;
    @Autowired
    @Qualifier(value = "UserDataSource")
    protected DataSource dataSource;
    @Autowired
    protected Axmr3TXManager Axmr3txManager;

    @Autowired
    @Qualifier("messagesFolder")
    public String getMessagesFolder() {
        return messagesFolder;
    }

    public void setMessagesFolder(String messagesFolder) {
        this.messagesFolder = messagesFolder;
    }

    protected String messagesFolder;
    private BaseDao<Element> docDAO;
    private BaseDao<ElementGroup> groupDAO;
    private BaseDao<ElementType> docTypeDAO;
    private BaseDao<ElementMetadata> elMdDAO;
    private BaseDao<ElementMetadataValue> elMdValueDAO;
    private BaseDao<FileContent> fileContentDAO;
    private BaseDao<File> fileSpecDAO;
    private BaseDao<Comment> commentDAO;
    private BaseDao<Acl> aclDAO;
    private BaseDao<AclContainer> aclContainerDAO;
    private BaseDao<Event> evDAO;
    private BaseDao<AuditMetadata> aMdDAO;
    private BaseDao<AuditValue> aMdValDAO;
    private BaseDao<AuditFile> aFileDAO;
    private BaseDao<AuditFileContent> aFileContentDAO;
    private BaseDao<ElementProcessInstance> elPInstanceDAO;
    private BaseDao<CalendarEntity> calDAO;
    private BaseDao<DataManagementSession> dmSessionDAO;
    private HashMap<String, String> cloning; // orig -> dest
    private HashMap<String, HashMap<Element, String>> linkCloning; // linked subject metadata
    private HashMap<Long, Boolean> updateElIds;

    private static Logger log = Logger.getLogger(DocumentService.class);
    private BaseDao<DataManagementAction> dmActionDAO;

    private BaseDao<EmendamentoSession> emeSessionDAO;
    private BaseDao<EmendamentoAction> emeActionDAO;
    private BaseDao<AuditEmeMetadata> aEmeMdDAO;
    private BaseDao<AuditEmeValue> aEmeMdValDAO;

    protected String templatePolicyFallbackObjs;
    protected List<String> templatePolicyFallbackObjsList;

    protected String templateFTLOverrideObjs;
    protected List<String> templateFTLOverrideObjsList;

    protected String baseNameOraStrategy;

    @Autowired
    protected InternalServiceBean isb;

    public InternalServiceBean getIsb() {
        return isb;
    }

    public void setIsb(InternalServiceBean isb) {
        this.isb = isb;
    }


    public String getTemplatePolicyFallbackObjs() {
        return templatePolicyFallbackObjs;
    }

    public void setTemplatePolicyFallbackObjs(String templatePolicyFallbackObjs) {
        this.templatePolicyFallbackObjs = templatePolicyFallbackObjs;
    }

    public List<String> getTemplatePolicyFallbackObjsList() {
        return templatePolicyFallbackObjsList;
    }

    public void setTemplatePolicyFallbackObjsList(List<String> templatePolicyFallbackObjsList) {
        this.templatePolicyFallbackObjsList = templatePolicyFallbackObjsList;
    }

    public String getTemplateFTLOverrideObjs() {
        return templateFTLOverrideObjs;
    }

    public void setTemplateFTLOverrideObjs(String templateFTLOverrideObjs) {
        this.templateFTLOverrideObjs = templateFTLOverrideObjs;
    }

    public List<String> getTemplateFTLOverrideObjsList() {
        return templateFTLOverrideObjsList;
    }

    public void setTemplateFTLOverrideObjsList(List<String> templateFTLOverrideObjsList) {
        this.templateFTLOverrideObjsList = templateFTLOverrideObjsList;
    }

    public String getBaseNameOraStrategy() {
        return baseNameOraStrategy;
    }

    public void setBaseNameOraStrategy(String baseNameOraStrategy) {
        this.baseNameOraStrategy = baseNameOraStrategy;
    }


    public void addElidToBeUpdeated(Long id, boolean fieldsToo){
        if (updateElIds==null) updateElIds=new HashMap<Long, Boolean>();
        if (!updateElIds.containsKey(id)) updateElIds.put(id, fieldsToo);
    }

    public HashMap<Long, Boolean> getUpdateElIds() {
        return updateElIds;
    }

    protected String fileOnFsPath;

    public String getFileOnFsPath() {
        return fileOnFsPath;
    }

    @Autowired
    public AxmrFreemarkerConfigurer fmCfg;

    public AxmrFreemarkerConfigurer getFmCfg() {
        return fmCfg;
    }

    public void setFmCfg(AxmrFreemarkerConfigurer fmCfg) {
        this.fmCfg = fmCfg;
    }

    @Autowired
    @Qualifier(value = "FileStoragePath")
    public void setFileOnFsPath(String fileOnFsPath) {
        this.fileOnFsPath = fileOnFsPath;
    }

    private HashMap<String, String> getCloning() {
        return cloning;
    }

    private void setCloning(HashMap<String, String> cloning) {
        this.cloning = cloning;
    }

    public DataSource getDataSource() {
        return dataSource;
    }

    public void setDataSource(DataSource dataSource) {
        this.dataSource = dataSource;
    }

    private void resetCloning() {
        this.cloning = new HashMap<String, String>();
    }

    private void addCloning(Element orig, Element dest) {
        cloning.put(orig.getId().toString(), dest.getId().toString());
    }

    private HashMap<String, HashMap<Element, String>> getLinkCloning() {
        return linkCloning;
    }

    private void setLinkCloning(HashMap<String, HashMap<Element, String>> linkCloning) {
        this.linkCloning = linkCloning;
    }

    private void resetLinkCloning() {
        this.linkCloning = new HashMap<String, HashMap<Element, String>>();
    }

    private void addLinkCloning(String element, Element subject, String metadata) {
        HashMap<Element, String> links;
        if (linkCloning.containsKey(element)) {
            links = linkCloning.get(element);
        } else {
            links = new HashMap<Element, String>();
        }
        links.put(subject, metadata);
        linkCloning.put(element, links);
    }

    public BaseDao<TemplateAcl> getTplAclDAO() {
        return tplAclDAO;
    }

    public BaseDao<TemplateAclContainer> getTplAclContainerDAO() {
        return tplAclContainerDAO;
    }

    public BaseDao<ElementTemplate> getElTplDAO() {
        return elTplDAO;
    }

    public BaseDao<Element> getDocDAO() {
        return docDAO;
    }

    public void setDocDAO(BaseDao<Element> docDAO) {
        this.docDAO = docDAO;
    }

    public BaseDao<ElementType> getDocTypeDAO() {
        return docTypeDAO;
    }

    public void setDocTypeDAO(BaseDao<ElementType> docTypeDAO) {
        this.docTypeDAO = docTypeDAO;
    }

    public BaseDao<ElementMetadata> getElMdDAO() {
        return elMdDAO;
    }

    public void setElMdDAO(BaseDao<ElementMetadata> elMdDAO) {
        this.elMdDAO = elMdDAO;
    }

    public BaseDao<ElementMetadataValue> getElMdValueDAO() {
        return elMdValueDAO;
    }

    public void setElMdValueDAO(BaseDao<ElementMetadataValue> elMdValueDAO) {
        this.elMdValueDAO = elMdValueDAO;
    }

    public BaseDao<FileContent> getFileContentDAO() {
        return fileContentDAO;
    }

    public void setFileContentDAO(BaseDao<FileContent> fileContentDAO) {
        this.fileContentDAO = fileContentDAO;
    }

    public BaseDao<File> getFileSpecDAO() {
        return fileSpecDAO;
    }

    public void setFileSpecDAO(BaseDao<File> fileSpecDAO) {
        this.fileSpecDAO = fileSpecDAO;
    }

    public BaseDao<Comment> getCommentDAO() {
        return commentDAO;
    }

    public void setCommentDAO(BaseDao<Comment> commentDAO) {
        this.commentDAO = commentDAO;
    }

    public BaseDao<Acl> getAclDAO() {
        return aclDAO;
    }

    public void setAclDAO(BaseDao<Acl> aclDAO) {
        this.aclDAO = aclDAO;
    }

    public BaseDao<AclContainer> getAclContainerDAO() {
        return aclContainerDAO;
    }

    public void setAclContainerDAO(BaseDao<AclContainer> aclContainerDAO) {
        this.aclContainerDAO = aclContainerDAO;
    }

    public BaseDao<Event> getEvDAO() {
        return evDAO;
    }

    public void setEvDAO(BaseDao<Event> evDAO) {
        this.evDAO = evDAO;
    }

    public BaseDao<AuditMetadata> getaMdDAO() {
        return aMdDAO;
    }

    public void setaMdDAO(BaseDao<AuditMetadata> aMdDAO) {
        this.aMdDAO = aMdDAO;
    }

    public BaseDao<AuditValue> getaMdValDAO() {
        return aMdValDAO;
    }

    public void setaMdValDAO(BaseDao<AuditValue> aMdValDAO) {
        this.aMdValDAO = aMdValDAO;
    }

    public BaseDao<AuditFile> getaFileDAO() {
        return aFileDAO;
    }

    public void setaFileDAO(BaseDao<AuditFile> aFileDAO) {
        this.aFileDAO = aFileDAO;
    }

    public BaseDao<AuditFileContent> getaFileContentDAO() {
        return aFileContentDAO;
    }

    public void setaFileContentDAO(BaseDao<AuditFileContent> aFileContentDAO) {
        this.aFileContentDAO = aFileContentDAO;
    }

    public BaseDao<ElementProcessInstance> getElPInstanceDAO() {
        return elPInstanceDAO;
    }

    public void setElPInstanceDAO(BaseDao<ElementProcessInstance> elPInstanceDAO) {
        this.elPInstanceDAO = elPInstanceDAO;
    }

    public BaseDao<MetadataTemplate> getTemplateDAO() {
        return templateDAO;
    }

    public void setTemplateDAO(BaseDao<MetadataTemplate> templateDAO) {
        this.templateDAO = templateDAO;
    }

    public BaseDao<MetadataField> getMdFieldDAO() {
        return mdFieldDAO;
    }

    public void setMdFieldDAO(BaseDao<MetadataField> mdFieldDAO) {
        this.mdFieldDAO = mdFieldDAO;
    }

    public BaseDao<BulkUploadFile> getBfDAO() {
        return bfDAO;
    }

    public void setBfDAO(BaseDao<BulkUploadFile> bfDAO) {
        this.bfDAO = bfDAO;
    }

    public BaseDao<PredefinedPolicy> getPolDAO() {
        return polDAO;
    }

    public void setPolDAO(BaseDao<PredefinedPolicy> polDAO) {
        this.polDAO = polDAO;
    }


    private BaseDao<MetadataTemplate> templateDAO;
    private BaseDao<MetadataField> mdFieldDAO;
    private BaseDao<BulkUploadFile> bfDAO;
    private BaseDao<PredefinedPolicy> polDAO;
    private BaseDao<TemplateAcl> tplAclDAO;
    private BaseDao<TemplateAclContainer> tplAclContainerDAO;
    private BaseDao<ElementTemplate> elTplDAO;


    public Axmr3TXManager getAxmr3txManager() {
        return Axmr3txManager;
    }

    public void setAxmr3txManager(Axmr3TXManager axmr3txManager) {
        Axmr3txManager = axmr3txManager;
    }

    public MultiSessionTXManager getTxManager() {
        return txManager;
    }

    public void setTxManager(MultiSessionTXManager txManager) {
        this.txManager = txManager;
    }

    public void afterPropertiesSet() throws Exception {
        if (getAxmr3txManager() != null) txManager = getAxmr3txManager();
        String txName = "doc";
        docDAO = new BaseDao<Element>(txManager, txName, Element.class);
        groupDAO = new BaseDao<ElementGroup>(txManager, txName, ElementGroup.class);
        docTypeDAO = new BaseDao<ElementType>(txManager, txName, ElementType.class);
        templateDAO = new BaseDao<MetadataTemplate>(txManager, txName, MetadataTemplate.class);
        elMdDAO = new BaseDao<ElementMetadata>(txManager, txName, ElementMetadata.class);
        elMdValueDAO = new BaseDao<ElementMetadataValue>(txManager, txName, ElementMetadataValue.class);
        fileContentDAO = new BaseDao<FileContent>(txManager, txName, FileContent.class);
        fileSpecDAO = new BaseDao<File>(txManager, txName, File.class);
        commentDAO = new BaseDao<Comment>(txManager, txName, Comment.class);
        aclDAO = new BaseDao<Acl>(txManager, txName, Acl.class);
        aclContainerDAO = new BaseDao<AclContainer>(txManager, txName, AclContainer.class);
        evDAO = new BaseDao<Event>(txManager, txName, Event.class);
        aMdDAO = new BaseDao<AuditMetadata>(txManager, txName, AuditMetadata.class);
        aMdValDAO = new BaseDao<AuditValue>(txManager, txName, AuditValue.class);
        aFileDAO = new BaseDao<AuditFile>(txManager, txName, AuditFile.class);
        aFileContentDAO = new BaseDao<AuditFileContent>(txManager, txName, AuditFileContent.class);
        mdFieldDAO = new BaseDao<MetadataField>(txManager, txName, MetadataField.class);
        bfDAO = new BaseDao<BulkUploadFile>(txManager, txName, BulkUploadFile.class);
        polDAO = new BaseDao<PredefinedPolicy>(txManager, txName, PredefinedPolicy.class);
        elPInstanceDAO = new BaseDao<ElementProcessInstance>(txManager, txName, ElementProcessInstance.class);
        tplAclDAO = new BaseDao<TemplateAcl>(txManager, txName, TemplateAcl.class);
        tplAclContainerDAO = new BaseDao<TemplateAclContainer>(txManager, txName, TemplateAclContainer.class);
        elTplDAO = new BaseDao<ElementTemplate>(txManager, txName, ElementTemplate.class);
        calDAO = new BaseDao<CalendarEntity>(txManager, txName, CalendarEntity.class);
        dmSessionDAO = new BaseDao<DataManagementSession>(txManager, txName, DataManagementSession.class);
        dmActionDAO = new BaseDao<DataManagementAction>(txManager, txName, DataManagementAction.class);

        emeSessionDAO = new BaseDao<EmendamentoSession>(txManager, txName, EmendamentoSession.class);
        emeActionDAO = new BaseDao<EmendamentoAction>(txManager, txName, EmendamentoAction.class);
        aEmeMdDAO = new BaseDao<AuditEmeMetadata>(txManager, txName, AuditEmeMetadata.class);
        aEmeMdValDAO = new BaseDao<AuditEmeValue>(txManager, txName, AuditEmeValue.class);

        //Verifico stringa fallback policy oggetti
        templatePolicyFallbackObjsList=new LinkedList<String>();
        if (templatePolicyFallbackObjs==null){
            templatePolicyFallbackObjs="NONE";
        }
        if (!templatePolicyFallbackObjs.isEmpty()){
            templatePolicyFallbackObjsList=Arrays.asList(templatePolicyFallbackObjs.toLowerCase().split(","));
        }
        //Verifico stringa override FTL template
        templateFTLOverrideObjsList=new LinkedList<String>();
        if (templateFTLOverrideObjs==null){
            templateFTLOverrideObjs="NONE";
        }
        if (!templateFTLOverrideObjs.isEmpty()){
            templateFTLOverrideObjsList=Arrays.asList(templateFTLOverrideObjs.toLowerCase().split(","));
        }
    }

    public ElementType getDocDefinition(Long id) {
        return docTypeDAO.getById(id);
    }

    public List<MetadataField> approveEmendamentoChanges(Long emeSessionId, String username) throws AxmrGenericException {
        LinkedList<MetadataField> retval = new LinkedList<MetadataField>();
        if (emeSessionId!= null && emeSessionId>0){

            IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
            //LUIGI: ricavo la sessione
            EmendamentoSession dataEme = emeSessionDAO.getById(emeSessionId);

            //LinkedList<Long> objIds = new LinkedList<Long>();
            List<Element> objEls = this.getElementsFromEmeSession(emeSessionId,username);

            Element emeEl = this.getElement(dataEme.getEmeId());

            //Ciclo gli oggetti da aggiornare
            for(Element el:objEls) { //Long objId: objIds
                HashMap<String, String[]> data = new HashMap<String, String[]>();
                List<ElementMetadata> elMds = this.getEmendamentoChanges(emeSessionId, el);

                for (ElementMetadata md : elMds) {
                    LinkedList<String> values = new LinkedList<String>();
                    String mdKey = md.getTemplateName()+"_"+md.getFieldName();
                    for(Object o:md.getVals()){
                        if (o == null){
                            //Nulla
                        } else if (o instanceof Calendar) {
                            DateFormat simpleDF = new SimpleDateFormat("dd/MM/yyyy");
                            Calendar c = (Calendar)o;
                            values.add(simpleDF.format(c.getTime()));
                        } else if (o instanceof Date) {
                            DateFormat simpleDF = new SimpleDateFormat("dd/MM/yyyy");
                            Date c = (Date)o;
                            values.add(simpleDF.format(c));
                        } else if (o instanceof Element){
                            values.add(((Element)o).getId().toString());
                        } else {
                            values.add(o.toString());
                        }
                    }
                    log.info("(approvaEME) -- "+mdKey+": "+values.size());
                    if (values.size()>0){
                        data.put(mdKey,values.toArray(new String[values.size()]));
                    }else{
                        data.put(mdKey,null);
                    }
                }
                updateElementMetaDataArray(user, el, data, "EMENDAMENTO"+"###"+emeEl.getFieldDataString("DatiEmendamento_CodiceEme"));
            }

            /*
            //LUIGI: ricavo le actions
            Criteria emeActionCriteria=emeActionDAO.getCriteria();
            emeActionCriteria.add(Restrictions.eq("emeSession", dataEme));
            emeActionCriteria.addOrder(Order.asc("id"));
            List<EmendamentoAction> actionsEme=emeActionCriteria.list();

            //LUIGI: ciclo le actions e ricavo i valori
            for(EmendamentoAction actionEme:actionsEme ){

                Element el = actionEme.getObjId();
                IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();

                Criteria emeMdsCriteria = aEmeMdDAO.getCriteria();

                List<AuditEmeMetadata> emeMds=.add(Restrictions.eq("emeAction", actionEme)).list();

                HashMap<String, String> data=new HashMap<String, String>();

                //LUIGI: ciclo i metadati collegai alla action
                for(AuditEmeMetadata emeMd: emeMds){

                    String template= emeMd.getTemplateName();
                    String field= emeMd.getFieldName();
                    String templateField= template+"_"+field;

                    Collection<AuditEmeValue> emeValues=emeMd.getValues();
                    //LUIGI: ciclo i valori e costruisco la hashmap simile alle POST
                    for (AuditEmeValue emeValue:emeValues) {
                        String value= "";

                        if (emeValue.getCode() != null ) {value= emeValue.getCode()+"###"+emeValue.getDecode();}
                        if (emeValue.getTextValue() != null ) {value= emeValue.getTextValue();}
                        if (emeValue.getLongTextValue() != null ) {value= emeValue.getLongTextValue();}
                        if (emeValue.getElement_link() != null ) {value= emeValue.getElement_link().getId().toString();}

                        DateFormat simpleDF = new SimpleDateFormat("dd/MM/yyyy");
                        if (emeValue.getDate() != null) {value = simpleDF.format(emeValue.getDate().getTime());}

                        data.put(templateField, value);


                    }

                }

                updateElementMetaData(user, el, data, "EMENDAMENTO");

            }
            */

            Calendar calendar = Calendar.getInstance(TimeZone.getTimeZone("Europe/Rome"),Locale.ITALY);
            dataEme.setEndDt(calendar);
            emeSessionDAO.saveOrUpdate(dataEme);
        }
        return retval;
    }

    public List<MetadataField> approveEmendamentoChanges(Long emeSessionId, IUser user) throws AxmrGenericException {
        return approveEmendamentoChanges(emeSessionId, user.getUsername());
    }


    public List<MetadataField> rejectEmendamentoChanges(Long emeSessionId) throws AxmrGenericException {
        LinkedList<MetadataField> retval = new LinkedList<MetadataField>();
        if (emeSessionId!= null && emeSessionId>0){

            //LUIGI: ricavo la sessione
            EmendamentoSession dataEme = emeSessionDAO.getById(emeSessionId);

            Calendar calendar = Calendar.getInstance(TimeZone.getTimeZone("Europe/Rome"),Locale.ITALY);
            dataEme.setEndDt(calendar);
            emeSessionDAO.saveOrUpdate(dataEme);
        }
        return retval;
    }

    public List<ElementMetadata> getEmendamentoChanges(Long emeSessionId, Long elId){
        return getEmendamentoChanges(emeSessionId,this.getElement(elId));
    }
    public List<ElementMetadata> getEmendamentoChanges(Long emeSessionId, Element el){
        LinkedList<ElementMetadata> retval = new LinkedList<ElementMetadata>();
        if (emeSessionId!= null && emeSessionId>0){
            // ricavo la sessione
            EmendamentoSession dataEme = emeSessionDAO.getById(emeSessionId);

            //ricavo le actions
            Criteria emeActionCriteria=emeActionDAO.getCriteria();
            emeActionCriteria.add(Restrictions.eq("emeSession", dataEme));
            emeActionCriteria.add(Restrictions.eq("objId", el));
            emeActionCriteria.addOrder(Order.asc("id")); //modDt
            List<EmendamentoAction> actionsEme=emeActionCriteria.list();

            LinkedHashMap<String, ElementMetadata> metadataDiz = new LinkedHashMap<String, ElementMetadata>();
            //ciclo le actions e ricavo i valori
            for(EmendamentoAction actionEme:actionsEme ){
                Criteria emeMdCriteria=aEmeMdDAO.getCriteria();
                emeMdCriteria.add(Restrictions.eq("emeAction", actionEme));
                emeMdCriteria.addOrder(Order.asc("id")); //modDt
                List<AuditEmeMetadata> emeMds=emeMdCriteria.list();
                for(AuditEmeMetadata emeMd: emeMds){
                    String mdkey = emeMd.getTemplateName() + "_" + emeMd.getFieldName();
                    LinkedList<ElementMetadataValue> emdval = new LinkedList<ElementMetadataValue>();
                    //Criteria emeMdValCriteria=aEmeMdValDAO.getCriteria();
                    //emeMdValCriteria.add(Restrictions.eq("emeAction", actionEme));
                    //emeMdValCriteria.addOrder(Order.asc("id"));
                    //List<AuditEmeValue> emeMdVals=emeMdValCriteria.list();
                    for (AuditEmeValue v: emeMd.getValues()){
                        ElementMetadataValue eval = new ElementMetadataValue();
                        eval.setCode(v.getCode());
                        eval.setDate(v.getDate());
                        eval.setDecode(v.getDecode());
                        eval.setElement_link(v.getElement_link());
                        eval.setLongTextValue(v.getLongTextValue());
                        eval.setTextValue(v.getTextValue());
                        eval.setId(v.getId());
                        emdval.add(eval);
                    }
                    ElementMetadata emd = new ElementMetadata();
                    MetadataTemplate t = new MetadataTemplate();
                    emd.setField(emeMd.getField());
                    emd.setTemplate(emeMd.getTemplate());
                    emd.setValues(emdval);
                    emd.setEmeAction(actionEme);
                    if (metadataDiz.containsKey(mdkey)){
                        metadataDiz.remove(mdkey);
                }
                    metadataDiz.put(mdkey, emd);
                    //retval.add(emd);
                }
            }
            for (ElementMetadata emd : metadataDiz.values()) {
                retval.add(emd);
            }
        }
        return retval;
    }

    public Element mergeEmendamentoChanges(Element el, Long emeSessionId){
        //TODO: LUIGI: Verificare sessione emendamento e iniettare metadati modificati
        List<ElementMetadata> changes = getEmendamentoChanges(emeSessionId, el);
        for(ElementMetadata f:changes){

        }
        return el;
    }


    public List<Element> getElementsFromEmeSession(Long emeSessionId, String username) throws AxmrGenericException {
        LinkedList<Element> objEls = new LinkedList<Element>();
        if (emeSessionId != null && emeSessionId > 0) {
            IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
            //LUIGI: ricavo la sessione
            EmendamentoSession dataEme = emeSessionDAO.getById(emeSessionId);
            Criteria emeActionCriteria = emeActionDAO.getCriteria();
            emeActionCriteria.add(Restrictions.eq("emeSession", dataEme));
            emeActionCriteria.addOrder(Order.asc("objId"));
            List<EmendamentoAction> actionsEme = emeActionCriteria.list();
            //Dalle actions, ricavo gli elementi da aggiornare (in ordine di ID Oggetto)
            for (EmendamentoAction actionEme : actionsEme) {
                if (!objEls.contains(actionEme.getObjId())) {
                    objEls.add(actionEme.getObjId());
                }
            }
        }
        return objEls;
    }
    public EmendamentoSession getEmendamentoSession(Long emeSessionId){
        EmendamentoSession emeSession = null;
        if (emeSessionId != null && emeSessionId > 0) {
            IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
            //LUIGI: ricavo la sessione
            emeSession = emeSessionDAO.getById(emeSessionId);
        }
        return emeSession;
    }

    public Element getElement(Long id) {
        return this.getElement(id, null);
    }
    public Element getElement(Long id, Long emeSessionId) {
        Element tmpEl = docDAO.getById(id);

        //Check Fallback policy template
        if (templatePolicyFallbackObjs.equalsIgnoreCase("ALL")){
            tmpEl.setFallbackTemplatePolicy(true);
        }else if (!templatePolicyFallbackObjs.equalsIgnoreCase("NONE")){
            for(String s:templatePolicyFallbackObjsList){
                if (tmpEl.getType().getTypeId().equalsIgnoreCase(s)){
                    tmpEl.setFallbackTemplatePolicy(true);
                    break;
                }
            }
        }
        //Check FTL Override policy template
        if (templateFTLOverrideObjs.equalsIgnoreCase("ALL")){
            tmpEl.setTemplateFTLOverride(true);
        }else if (!templateFTLOverrideObjs.equalsIgnoreCase("NONE")){
            for(String s:templateFTLOverrideObjsList){
                if (tmpEl.getType().getTypeId().equalsIgnoreCase(s)){
                    tmpEl.setTemplateFTLOverride(true);
                    break;
                }
            }
        }

        //TODO: LUIGI: Verificare sessione emendamento e iniettare metadati modificati
        if (emeSessionId!= null && emeSessionId>0){

            //LUIGI settare inMendamento se nella docemesession c'è quell'elemento
            EmendamentoSession dataEme = emeSessionDAO.getById(emeSessionId);
            Long emeId = dataEme.getEmeId();
            Long centroId = dataEme.getCentroId();
            log.warn("ATTENZIONE CENTROID:"+centroId);
            Element emeElement = docDAO.getById(emeId);
            Element studioElement = emeElement.getParent();
            Long studioId = studioElement.getId();

            if (id.equals(studioId) || id.equals(centroId)) {
                tmpEl.setInEmendamento(true);
            }

            LinkedHashMap<String,ElementMetadata> metadataDiz = new LinkedHashMap<String,ElementMetadata>();
            for(ElementMetadata emd: tmpEl.getData()){
                metadataDiz.put(emd.getTemplateName()+"_"+emd.getFieldName(),emd);
            }

            List<ElementMetadata> changes = getEmendamentoChanges(emeSessionId, tmpEl);
            for(ElementMetadata f:changes){
                //tmpEl.getData().
                log.info("CICLO MODIFICA EME: "+f.getTemplateName()+"_"+f.getFieldName()+"");
                for(Object o : f.getVals()){
                    log.info("VAL: "+o.toString());
                }
                if (metadataDiz.containsKey(f.getTemplateName()+"_"+f.getFieldName())) {
                    metadataDiz.get(f.getTemplateName() + "_" + f.getFieldName()).setValues(f.getValues());
                }else{
                    tmpEl.getData().add(f);
                }
            }
            //[...]

        }
        //tmpEl.getData().
        return tmpEl;
    }

    public Element getElement(String id) {
        return this.getElement(Long.parseLong(id));
    }

    public void registerEvent(IUser user, Element el, String type) throws RestException {
        registerEvent(user.getUsername(), el, type);
    }

    public void registerEvent(String user, Element el, String type) throws RestException {

        Event ev = new Event();
        ev.setUsername(user);
        ev.setEvDt(new GregorianCalendar());
        ev.setEvType(type);
        ev.setElement(el);
        if (el.getEvs() == null) el.setEvs(new LinkedList<Event>());
        try {
            evDAO.saveOrUpdate(ev);
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        }
        el.getEvs().add(ev);
        try {
            docDAO.saveOrUpdate(el);
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        }
    }

    public void setDefaultPermissionOnElement(Element el) throws AxmrGenericException {
        setDefaultPermissionOnElement(el.getCreateUser(), el, el.getType());
    }

    private void setDefaultPermissionOnElement(IUser user, Element el, ElementType type) throws AxmrGenericException {
        setDefaultPermissionOnElement(user.getUsername(), el, type);
    }

    private void setDefaultPermissionOnElement(String user, Element el, ElementType type) throws AxmrGenericException {
        for (Acl acl : type.getAcls()) {
            Acl elAcl = new Acl();
            elAcl.setPredifinedPolicy(acl.getPredifinedPolicy());
            elAcl.setElement(el);
            elAcl.setPolicyValue(acl.getPolicyValue());
            elAcl.setPositionalAce(acl.getPositionalAce());
            elAcl.setContainers(new LinkedList<AclContainer>());
            elAcl.setDetailTemplate(acl.getDetailTemplate());
            aclDAO.saveOrUpdate(elAcl);
            for (AclContainer container : acl.getContainers()) {
                AclContainer c1 = new AclContainer();
                c1.setAuthority(container.isAuthority());
                if (!container.isAuthority() && container.getContainer().equals("cuser")) c1.setContainer(user);
                else c1.setContainer(container.getContainer());
                c1.setAcl(elAcl);
                elAcl.getContainers().add(c1);
                aclContainerDAO.saveOrUpdate(c1);
            }
            aclDAO.saveOrUpdate(elAcl);
            commitTXSessionAndKeepAlive();
        }
    }

    private void addMetadataTemplateToNewElement(IUser user, Element el, ElementType type) throws AxmrGenericException {
        addMetadataTemplateToNewElement(user.getUsername(), el, type);
    }

    private void addMetadataTemplateToNewElement(String user, Element el, ElementType type) throws AxmrGenericException {
        el.setElementTemplates(new LinkedList<ElementTemplate>());
        for (ElementTypeAssociatedTemplate t : type.getAssociatedTemplates()) {
            ElementTemplate et = new ElementTemplate();
            et.setMetadataTemplate(t.getMetadataTemplate());
            et.setEnabled(t.isEnabled());
            et.setTemplateAcls(new LinkedList<TemplateAcl>());
            elTplDAO.save(et);
            for (TemplateAcl acl : t.getTemplateAcls()) {
                TemplateAcl elAcl = new TemplateAcl();
                elAcl.setElementTemplate(et);
                elAcl.setPolicyValue(acl.getPolicyValue());
                elAcl.setPositionalAce(acl.getPositionalAce());
                tplAclDAO.saveOrUpdate(elAcl);
                elAcl.setContainers(new LinkedList<TemplateAclContainer>());
                for (TemplateAclContainer container : acl.getContainers()) {
                    TemplateAclContainer c1 = new TemplateAclContainer();
                    c1.setAuthority(container.isAuthority());
                    if (!container.isAuthority() && container.getContainer().equals("cuser")) c1.setContainer(user);
                    else c1.setContainer(container.getContainer());
                    elAcl.getContainers().add(c1);
                    c1.setAcl(acl);
                    tplAclContainerDAO.saveOrUpdate(c1);
                }
                tplAclDAO.saveOrUpdate(elAcl);
            }
            el.getElementTemplates().add(et);
        }
        docDAO.saveOrUpdate(el);
        commitTXSessionAndKeepAlive();
    }


    public ElementTemplate addAvailableTemplateToElement(Element el, String template) throws AxmrGenericException {
        return addAvailableTemplateToElement(el, template, true);
    }


    public ElementTemplate addAvailableTemplateToElement(Element el, String template, boolean enabled) throws AxmrGenericException {
        ElementTypeAssociatedTemplate templateObj = el.getAvailableTemplate(template);
        if (templateObj != null) {
            ElementTemplate et = new ElementTemplate();
            et.setMetadataTemplate(templateObj.getMetadataTemplate());
            et.setEnabled(enabled);
            et.setTemplateAcls(new LinkedList<TemplateAcl>());
            elTplDAO.save(et);
            for (TemplateAcl acl : templateObj.getTemplateAcls()) {
                TemplateAcl elAcl = new TemplateAcl();
                elAcl.setElementTemplate(et);
                elAcl.setPolicyValue(acl.getPolicyValue());
                elAcl.setPositionalAce(acl.getPositionalAce());
                tplAclDAO.saveOrUpdate(elAcl);
                elAcl.setContainers(new LinkedList<TemplateAclContainer>());
                for (TemplateAclContainer container : acl.getContainers()) {
                    TemplateAclContainer c1 = new TemplateAclContainer();
                    c1.setAuthority(container.isAuthority());
                    if (!container.isAuthority() && container.getContainer().equals("cuser"))
                        c1.setContainer(el.getCreateUser());
                    else c1.setContainer(container.getContainer());
                    elAcl.getContainers().add(c1);
                    c1.setAcl(acl);
                    tplAclContainerDAO.saveOrUpdate(c1);
                }
                tplAclDAO.saveOrUpdate(elAcl);
            }
            el.getElementTemplates().add(et);
            docDAO.saveOrUpdate(el);
            commitTXSessionAndKeepAlive();
            return et;
        }
        return null;
    }

    private void attachFileToElement(IUser user, Element el, byte[] file, String fileName, Long fileSize, String version, String date, String note, String autore) throws AxmrGenericException {
        DateFormat df = new SimpleDateFormat("dd/MM/yyyy");
        Date parsed = null;
        Calendar data_ = null;
        if (!date.isEmpty()) {
            try {
                parsed = df.parse(date.toString());
                data_ = Calendar.getInstance();
                data_.setTime(parsed);
            } catch (java.text.ParseException e) {
                log.error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
            }
        }
        if (file != null && file.length > 0) {
            FileContent fc = new FileContent();
            fc.setContent(file);
            fileContentDAO.saveOrUpdate(fc);
            File f = new File();
            if (fileName.endsWith(".pdf")
                    || fileName.endsWith(".xls")
                    || fileName.endsWith(".xlsx")
                    || fileName.endsWith(".doc")
                    || fileName.endsWith(".docx"))
                f.setIndexable(true);
            else f.setIndexable(false);
            f.setIndexed(false);
            f.setNote(note);
            f.setDate(data_);
            f.setAutore(autore);
            f.setVersion(version);
            f.setContent(fc);
            f.setFileName(fileName);
            f.setSize(fileSize);
            f.setUploadDt(new GregorianCalendar());
            f.setUploadUser(user.getUsername());
            fileSpecDAO.saveOrUpdate(f);
            el.setFile(f);
            docDAO.saveOrUpdate(el);
            addElidToBeUpdeated(el.getId(),true);
            commitTXSessionAndKeepAlive();
        }
    }

    public Element saveElement(IUser user, ElementType type, Map<String, String> data, byte[] file, String fileName, Long fileSize, String version, String date, String note, String autore, Element parent) throws RestException {
        return saveElement(user, type, data, file, fileName, fileSize, version, date, note, autore, parent, false);
    }


    public Element saveElement(String user, ElementType type, Map<String, String> data, byte[] file, String fileName, Long fileSize, String version, String date, String note, String autore, Element parent) throws RestException {
        return saveElement(user, type, data, file, fileName, fileSize, version, date, note, autore, parent, false);
    }

    public Element saveElement(IUser user, ElementType type, Map<String, String> data, byte[] file, String fileName, Long fileSize, String version, String date, String note, String autore, Element parent, boolean cloning) throws RestException {
        Policy pol = new Policy();
        if (parent == null) {
            if (!this.checkElementTypePolicy(pol, user, type.getId())) throw new RestException("NotPermitted", 1);
        }
        return saveElement(user.getUsername(), user, type, data, file, fileName, fileSize, version, date, note, autore, parent, cloning);
    }

    public Element saveElement(String user, ElementType type, Map<String, String> data, byte[] file, String fileName, Long fileSize, String version, String date, String note, String autore, Element parent, boolean cloning) throws RestException {
        return saveElement(user, null, type, data, file, fileName, fileSize, version, date, note, autore, parent, cloning);
    }

    public void checkSaveElement(String user, IUser userInstance, Element el, Map<String, String> data, String ElementAction) throws RestException {
        Iterator<String> dataIt = data.keySet().iterator();
        boolean fromWF = (userInstance == null);
        /*faccio ciclo preventivo per trovare eventuali errori e lanciare eccezioni prima di passare al salvataggio effettivo del dato*/
        while (dataIt.hasNext()){
            String paramName = dataIt.next();
            String parameter = data.get(paramName);
            it.cineca.siss.axmr3.log.Log.info(getClass(),"Ciclo il valore: "+paramName+" - "+parameter);
            String[] fieldSpec = paramName.split("_");
            if (fieldSpec.length < 2) continue;
            String templateName = fieldSpec[0];
            String fieldName = fieldSpec[1];
            if (fieldName.endsWith("-altro") || fieldName.endsWith("-select")) continue;

            if (userInstance == null && !fromWF) {
                throw new RestException("User or Workflow not defined 1", txManager);
            }
            MetadataTemplate template = null;
            for (MetadataTemplate template_ : el.getType().getEnabledTemplates()) {
                if (template_.getName().equals(templateName)) {
                    template = template_;
                }
            }
            MetadataField field = null;
            if(template!=null) {
                for (MetadataField f : template.getFields()) {
                    if (f.getName().equals(fieldName)) field = f;
                }
                if (field == null)
                    throw new RestException("FieldNotFound: " + template.getName() + "_" + fieldName, txManager);
                parameter = parameter.trim();
                if (field.getRegexpCheck() != null && !field.getRegexpCheck().isEmpty() && !parameter.isEmpty()) {//VMAZZEO AGGIUNGO CHE IL CONTROLLO PARTA SOLO SE IL FIELD E' COMPILATO
                    if (!parameter.matches(field.getRegexpCheck())) {
                        throw new RestException("RegexpCheckFailed: " + template.getName() + "_" + fieldName, txManager);
                    }
                }
            }
        }
    }

    public Element saveElement(String user, IUser userInstance, ElementType type, Map<String, String> data, byte[] file, String fileName, Long fileSize, String version, String date, String note, String autore, Element parent, boolean cloning) throws RestException {
        try {
            Long groupId = null;
            Element looking4Group = null;
            ElementGroup itemInGroup = null;
            Long groupLevel = type.getGroupUpLevel();
            Element el = new Element();
            Policy pol = new Policy();
            pol.setCanCreate(true);
            long position = 1;
            Criteria c = docDAO.getCriteria();
            c.add(Restrictions.eq("deleted", false));
            c.add(Restrictions.eq("type", type));
            if (parent != null) {
                el.setParent(parent);
                c.add(Restrictions.eq("parent", parent));
                el.setDraft(parent.isDraft());
                registerEvent(user, parent, "AddChild");
                recurseUpdateDt(parent, user, new GregorianCalendar());
            }
            c.setProjection(Projections.max("position"));
            if (type.isSortable()) {
                try {
                    long lastPos = (Long) c.uniqueResult();
                    position += lastPos;
                } catch (java.lang.NullPointerException ex) {
                    log.info(ex.getMessage());
                }
            }
            el.setPosition(position);
            el.setType(type);
            el.setData(new LinkedList<ElementMetadata>());
            el.setCreationDt(new GregorianCalendar());
            el.setCreateUser(user);
            docDAO.saveOrUpdate(el);
            this.checkSaveElement(user, userInstance, el, data, "CREATE");
            addMetadataTemplateToNewElement(user, el, type);
            registerEvent(user, el, "CreateElement");
            setDefaultPermissionOnElement(user, el, type);
            Iterator<String> dit = data.keySet().iterator();
            while (dit.hasNext()) {
                String key = dit.next();
                //it.cineca.siss.axmr3.log.Log.info(getClass(),"SaveElement - "+key+" - "+data.get(key));
            }

            updateElementMetaData(user, userInstance, el, data, "CREATE");

            attachFile(user, el, file, fileName, fileSize, version, date, note, autore, "CREATE");
            if (!cloning) {
                for (ElementTypeAssociatedWorkflow awf : el.getType().getAssociatedWorkflows()) {
                    if (awf.isEnabled() && awf.isStartOnCreate()) {
                        Long elId = el.getId();
                        txManager.getTxs().get("doc").commit();
                        if (!txManager.getSessions().get("doc").isOpen()) {
                            //it.cineca.siss.axmr3.log.Log.info(getClass(),"La sessione è chiusa, la riapro");
                            it.cineca.siss.axmr3.log.Log.info(getClass(), "Apro la sessione 4 " + this.getClass().getCanonicalName());
                            txManager.getSessions().put("doc", txManager.getSessionFactories().get("doc").openSession());
                            it.cineca.siss.axmr3.log.Log.info(getClass(), "Begin Transaction 7 " + this.getClass().getCanonicalName());
                            txManager.getTxs().put("doc", txManager.getSessions().get("doc").beginTransaction());
                        } else {
                            //it.cineca.siss.axmr3.log.Log.info(getClass(),"La sessione è aperta, controllo la transazione");
                            if (!txManager.getTxs().get("doc").isActive()) {
                                //it.cineca.siss.axmr3.log.Log.info(getClass(),"La transazione non è attiva 1");
                                it.cineca.siss.axmr3.log.Log.info(getClass(), "Begin Transaction 8 " + this.getClass().getCanonicalName());
                                txManager.getTxs().put("doc", txManager.getSessions().get("doc").beginTransaction());
                            }
                        }
                        el = this.getElement(elId);
                        this.startProcess(user, el, awf.getProcessKey());

                    }
                }
            }
            if (groupLevel != null && groupLevel > 0) {

                looking4Group = el;
                for (int i = 1; i <= groupLevel; i++) {
                    looking4Group = looking4Group.getParent();
                }
                if (!isInGroup(looking4Group.getId(), el.getId())) {
                    itemInGroup = new ElementGroup();
                    itemInGroup.setGroupId(looking4Group.getId());
                    itemInGroup.setItem(el.getId());
                    groupDAO.save(itemInGroup);
                }
            }
            addElidToBeUpdeated(el.getId(),true);
            if (!cloning) {
                commitTXSessionAndKeepAlive();
            }
            return el;
        } catch (AxmrGenericException e) {
            log.error(e.getMessage(),e);
            throw new RestException(e.getMessage(), txManager);
        }
    }

    public boolean checkElementTypePolicy(Policy pol, IUser user, Long typeId) {
        return checkElementTypePolicy(pol, user, typeId, null);
    }

    public boolean checkElementTypePolicy(Policy pol, IUser user, Long typeId, Long parentElementId) {
        //TODO: controllare le chiamate a questa funzione in quanto ricerca se esistono singole policy con i permessi ricercati e non considera casi in cui la somma delle policy risponda alle esigenze
        Criteria c = docTypeDAO.getCriteria();
        if (parentElementId == null) {
            c.createAlias("acls", "acls")
                    .createAlias("acls.containers", "aclContainers")
                    .add(Restrictions.eq("id", typeId))
                    .setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY)
                    .add(Restrictions.eq("rootAble", true))
                    .add(pol.checkCriterion("acls", "aclContainers", user));
            return (c.list().size() > 0);
        } else {
            c.createAlias("acls", "acls")
                    .createAlias("acls.containers", "aclContainers")
                    .add(Restrictions.eq("id", typeId))
                    .setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY)
                    .add(pol.checkCriterion("acls", "aclContainers", user));
            return (c.list().size() > 0);
        }
        //return false;
    }

    public List<Element> getRootElements(IUser user) {
        Policy pol = new Policy();
        //TODO: sono corrette questi permessi? Come gestire il caso in cui i permessi siano in policy differenti?
        pol.setCanView(true);
        pol.setCanBrowse(true);
        DetachedCriteria c = docDAO.getDetachedCriteria();
        c.add(Restrictions.isNull("parent"))
                .setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY)
                .createAlias("acls", "acls")
                .createAlias("acls.containers", "aclContainers")
                .add(Restrictions.eq("deleted", false))
                .add(pol.checkCriterion("acls", "aclContainers", user));
        return docDAO.getCriteriaList(c);
    }

    public List<Element> getRootElementsByTypeId(IUser user, Long typeId) {
        Policy pol = new Policy();
        //TODO: sono corrette questi permessi? Come gestire il caso in cui i permessi siano in policy differenti?
        pol.setCanView(true);
        pol.setCanBrowse(true);
        DetachedCriteria c = docDAO.getDetachedCriteria();
        c.add(Restrictions.isNull("parent"))
                .setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY)
                .createAlias("acls", "acls")
                .createAlias("acls.containers", "aclContainers")
                .add(Restrictions.eq("type", docTypeDAO.getById(typeId)))
                .add(Restrictions.eq("deleted", false))
                .add(pol.checkCriterion("acls", "aclContainers", user));
        return docDAO.getCriteriaList(c);
    }

    protected DetachedCriteria getViewableElementsCriteria(IUser user) {
        Policy pol = new Policy();
        pol.setCanView(true);

        DetachedCriteria c = docDAO.getDetachedCriteria();
        c.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY)
                .createAlias("acls", "acls")
                .createAlias("acls.containers", "aclContainers")
                .add(Restrictions.eq("deleted", false))
                .add(pol.checkCriterion("acls", "aclContainers", user));
        return c;
    }

    public DetachedCriteria getViewableElementsCriteria(IUser user, String alias) {
        Policy pol = new Policy();
        pol.setCanView(true);
        DetachedCriteria c = docDAO.getDetachedCriteria(alias);
        c.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY)
                .createAlias(alias + ".acls", alias + "acls")
                .createAlias(alias + ".acls.containers", alias + "aclContainers")
                .add(Restrictions.eq(alias + ".deleted", false))
                .add(pol.checkCriterion(alias + "acls", alias + "aclContainers", user));
        return c;
    }

    protected DetachedCriteria getViewableElementsDetachedCriteria(IUser user) {
        Policy pol = new Policy();
        pol.setCanView(true);

        DetachedCriteria c = DetachedCriteria.forClass(Element.class);
        c.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY)
                .createAlias("acls", "acls")
                .createAlias("acls.containers", "aclContainers")
                .add(Restrictions.eq("deleted", false))
                .add(pol.checkCriterion("acls", "aclContainers", user));
        return c;
    }

    protected DetachedCriteria getViewableElementsDetachedCriteria(IUser user, String alias) {
        Policy pol = new Policy();
        pol.setCanView(true);
        DetachedCriteria c = DetachedCriteria.forClass(Element.class, alias);
        c.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY)
                .createAlias("acls", "acls")
                .createAlias("acls.containers", "aclContainers")
                .add(Restrictions.eq("deleted", false))
                .add(pol.checkCriterion("acls", "aclContainers", user));
        return c;
    }

    protected DetachedCriteria getBrowsableElementsCriteria(IUser user) {
        Policy pol = new Policy();
        //TODO: verificare se il controllo è corretto e se come gestire i casi in cui i due permessi siano in policy distinte
        pol.setCanView(true);
        pol.setCanBrowse(true);
        DetachedCriteria c = docDAO.getDetachedCriteria();
        c.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY)
                .createAlias("acls", "acls")
                .createAlias("acls.containers", "aclContainers")
                .add(Restrictions.eq("deleted", false))
                .add(pol.checkCriterion("acls", "aclContainers", user));
        return c;
    }

    protected DetachedCriteria getSearchableElementsCriteria(IUser user) {
        Policy pol = new Policy();
        //TODO: sono corrette questi permessi? Come gestire il caso in cui i permessi siano in policy differenti?
        pol.setCanView(true);
        pol.setCanBrowse(true);
        DetachedCriteria c = docDAO.getDetachedCriteria();
        c.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY)
                .createAlias("acls", "acls")
                .createAlias("type", "type")
                .createAlias("acls.containers", "aclContainers")
                .add(Restrictions.eq("deleted", false))
                .add(Restrictions.eq("type.searchable", true))
                .add(pol.checkCriterion("acls", "aclContainers", user));
        return c;
    }

    protected DetachedCriteria getAllElementsCriteria() {
        return getAllElementsCriteria("nonegivenalias");
    }

    public DetachedCriteria getAllElementsCriteria(String alias) {
        Policy pol = new Policy();
        pol.setCanView(true);

        DetachedCriteria c = docDAO.getDetachedCriteria(alias);
        c.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY)

                .add(Restrictions.eq("deleted", false));

        return c;
    }

    public DetachedCriteria getAllElementsByTypeCriteria(String typeId) {
        Policy pol = new Policy();
        pol.setCanView(true);

        DetachedCriteria c = docDAO.getDetachedCriteria();
        c.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY)
                .createAlias("type", "type")
                .add(Restrictions.eq("type.typeId", typeId))
                .add(Restrictions.eq("deleted", false));

        return c;
    }

    public List<Element> search(IUser user, String pattern) {
        DetachedCriteria baseSearch = getSearchableElementsCriteria(user);
        baseSearch.createAlias("data", "data")
                .createAlias("data.values", "dataValues");
        baseSearch.add(
                Restrictions.or(
                        Restrictions.like("dataValues.textValue", "%" + pattern + "%").ignoreCase(),
                        Restrictions.or(
                                Restrictions.like("dataValues.longTextValue", "%" + pattern + "%").ignoreCase(),
                                Restrictions.like("dataValues.decode", "%" + pattern + "%").ignoreCase()
                        )
                )
        );
        List<Element> firtFilter = docDAO.getCriteriaList(baseSearch);
        List<Element> allEls = docDAO.getCriteriaList(getSearchableElementsCriteria(user));
        List<Long> ids = new LinkedList<Long>();
        HashMap<Long, Element> idsRef = new HashMap<Long, Element>();
        for (int i = 0; i < allEls.size(); i++) {
            Element el = allEls.get(i);
            if (el.getFile() != null && el.getFile().isIndexed()) {
                ids.add(el.getFile().getIndexId());
                idsRef.put(el.getFile().getIndexId(), el);
            }
        }
        ;
        if (firtFilter == null) firtFilter = new LinkedList<Element>();

        return firtFilter;
    }

    public List<Element> searchByExample(String typeId, HashMap<String, Object> data) throws AxmrGenericException {
        return searchByExample(null, null, typeId, data);
    }

    public List<Element> searchByExample(String parent, String typeId, HashMap<String, Object> data) throws AxmrGenericException {
        return searchByExample(null, parent, typeId, data);
    }

    public List<Element> searchByExample(IUser user, String parent, String typeId, HashMap<String, Object> data) throws AxmrGenericException {
        ElementType elType = getDocDefinitionByName(typeId);
        return searchByExample(user, parent, elType, data);
    }

    public List<Element> searchByExample(Long docType, HashMap<String, Object> data) throws AxmrGenericException {
        return searchByExample(null, null, docType, data);
    }

    public List<Element> searchByExample(String parent, Long docType, HashMap<String, Object> data) throws AxmrGenericException {
        return searchByExample(null, parent, docType, data);
    }

    public List<Element> searchByExample(IUser user, String parent, Long docType, HashMap<String, Object> data) throws AxmrGenericException {
        ElementType elType = getDocDefinition(docType);
        return searchByExample(user, parent, elType, data);
    }

    public List<Element> searchByExample(IUser user, String parent, ElementType elType, HashMap<String, Object> data) throws AxmrGenericException {
        Element example = new Element();
        if (parent != null && !parent.isEmpty()) {
            Element parentEl = getElement(Long.parseLong(parent));
            if (parentEl != null) example.setParent(parentEl);
        }
        example.setType(elType);

        example.setElementTemplates(new LinkedList<ElementTemplate>());
        for (ElementTypeAssociatedTemplate t : elType.getAssociatedTemplates()) {
            ElementTemplate t1 = new ElementTemplate();
            t1.setMetadataTemplate(t.getMetadataTemplate());
            t1.setTemplateAcls(t.getTemplateAcls());
            example.getElementTemplates().add(t1);
        }
        Iterator<String> dataIt = data.keySet().iterator();
        while (dataIt.hasNext()) {
            String key = dataIt.next();
            String[] keySplit = key.split("_");
            it.cineca.siss.axmr3.log.Log.info(getClass(), "Ciclo il parametro " + key + " numero template: " + String.valueOf(example.getTemplates().size()));
            //TODO: verificare perchè non ho template associati e correggere
            for (ElementTypeAssociatedTemplate t1 : example.getType().getAssociatedTemplates()) {
                MetadataTemplate t = t1.getMetadataTemplate();
                if (t.getName().equals(keySplit[0])) {
                    MetadataField f = null;
                    for (MetadataField f1 : t.getFields()) {
                        if (f1.getName().equals(keySplit[1])) f = f1;
                    }

                    //it.cineca.siss.axmr3.log.Log.info(getClass(),"Template: "+t.getName()+" - Campo:"+f.getName());
                    if (data.get(key) != null)
                        it.cineca.siss.axmr3.log.Log.info(getClass(), " - valore da inserire: " + data.get(key));
                    ElementMetadata md = new ElementMetadata();
                    md.setField(f);
                    md.setTemplate(t);

                    if (f != null) {
                        if (md.getField().getType().equals(MetadataFieldType.ELEMENT_LINK)) {
                           /* Element linkedEl=null;
                            if (!(data.get(key) instanceof Element)) {
                                if(!data.get(key).equals("")) linkedEl=docDAO.getById(Long.parseLong((String)data.get(key)));
                            }else {
                                linkedEl=(Element) data.get(key);
                            }
                            md.setVal(linkedEl);     */
                        } else md.setVal(data.get(key));


                        if (md != null) {
                            example.getData().add(md);
                        }
                    }
                }
            }
        }

        return searchByExample(user, example);

    }

    public List<Element> searchByExample(IUser user, Element example) {
        Collection<ElementMetadataValue> valCollection = null;
        DetachedCriteria baseSearch = null;
        if (user == null) {
            baseSearch = getAllElementsCriteria();
        } else {
            baseSearch = getViewableElementsCriteria(user);
        }
        baseSearch.createAlias("type", "type")
                .add(Restrictions.eq("type.id", example.getType().getId()));


        baseSearch.createAlias("data", "data")
                .createAlias("data.values", "dataValues");
        Element parent = example.getParent();
        if (parent != null) {
            baseSearch.createAlias("parent", "parent");
            baseSearch.add(Restrictions.eq("parent.id", parent.getId()));
        }
        baseSearch.createAlias("data.field", "field");
        baseSearch.createAlias("data.template", "template");
        it.cineca.siss.axmr3.log.Log.info(getClass(), "ciclo data examples");
        for (ElementMetadata md : example.getData()) {
            it.cineca.siss.axmr3.log.Log.info(getClass(), "md");
            if (!(md.getVals().isEmpty()) && !(md.getVals().get(0).equals(""))) {
                it.cineca.siss.axmr3.log.Log.info(getClass(), "fieldname " + md.getFieldName() + " template " + md.getTemplateName());
                baseSearch.add(Restrictions.eq("field.name", md.getFieldName())).add(Restrictions.eq("template.name", md.getTemplateName()));
                if (md.isType(MetadataFieldType.SELECT) || md.isType(MetadataFieldType.RADIO) || md.isType(MetadataFieldType.CHECKBOX) || md.isType(MetadataFieldType.EXT_DICTIONARY)) {
                    valCollection = md.getValues();
                    baseSearch.add(
                            Restrictions.eq("dataValues.code", valCollection.iterator().next().getCode())
                    );
                } else if (md.isType(MetadataFieldType.TEXTBOX)) {
                    baseSearch.add(
                            Restrictions.eq("dataValues.textValue", md.getVals().get(0))
                    );
                } else if (md.isType(MetadataFieldType.TEXTAREA)) {
                    baseSearch.add(
                            Restrictions.eq("dataValues.longTextValue", md.getVals().get(0))
                    );
                }
            }
        }


        return docDAO.getCriteriaList(baseSearch);

    }

    public List<Element> searchByExample(Element example) {

        DetachedCriteria baseSearch = getAllElementsCriteria();
        baseSearch.createAlias("type", "type")
                .add(Restrictions.eq("type.id", example.getType().getId()));


        baseSearch.createAlias("data", "data")
                .createAlias("data.values", "dataValues");
        Element parent = example.getParent();
        if (parent != null) {
            baseSearch.createAlias("parent", "parent");
            baseSearch.add(Restrictions.eq("parent.id", parent.getId()));
        }
        baseSearch.createAlias("data.field", "field");
        baseSearch.createAlias("data.template", "template");
        for (ElementMetadata md : example.getData()) {
            if (!(md.getVals().isEmpty()) && !(md.getVals().get(0).equals(""))) {
                baseSearch.add(Restrictions.eq("field.name", md.getFieldName())).add(Restrictions.eq("template.name", md.getTemplateName()));
                baseSearch.add(Restrictions.or(
                        Restrictions.eq("dataValues.textValue", md.getVals().get(0)),
                        Restrictions.eq("dataValues.longTextValue", md.getVals().get(0))));
            }
        }


        return docDAO.getCriteriaList(baseSearch);

    }

    public void addComment(Element el, String comment, IUser user) throws RestException {
        Comment c = new Comment();
        c.setInsDt(new GregorianCalendar());
        c.setComment(comment);
        c.setUserId(user.getUsername());
        if (el.getComments() == null) el.setComments(new LinkedList<Comment>());
        try {
            commentDAO.saveOrUpdate(c);
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        }
        el.getComments().add(c);
        try {
            docDAO.saveOrUpdate(el);
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        }
        //addElidToBeUpdeated(el.getId(),true);
        registerEvent(user, el, "AddComment");
    }

    public List<ElementType> getCreatableRootElementTypes(IUser auth) {
        Criteria c = docTypeDAO.getCriteria();
        Policy pCheck = new Policy();
        pCheck.setCanCreate(true);
        //pCheck.setCanBrowse(true);
        //it.cineca.siss.axmr3.log.Log.info(getClass(),"Policy to check:" +pCheck.toLikeClause());
        c.createAlias("acls", "acls")
                .createAlias("acls.containers", "aclContainers")
                .add(Restrictions.eq("rootAble", true))
                .add(Restrictions.eq("deleted", false))
                .setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY)
                .add(pCheck.checkCriterion("acls", "aclContainers", auth));
        return c.list();
    }

    public List<ElementType> getCreatableElementTypes(Element el, IUser user) {
        Criteria c = docTypeDAO.getCriteria();
        Policy pCheck = new Policy();
        pCheck.setCanCreate(true);
        //pCheck.setCanBrowse(true);
        List<Long> childTypeIds = new LinkedList<Long>();
        for (ElementType t : el.getType().getAllowedChilds()) {
            childTypeIds.add(t.getId());
        }
        if (el.getType().isSelfRecursive()) childTypeIds.add(el.getType().getId());
        for (int i = 0; i < childTypeIds.size(); i++) {
            //it.cineca.siss.axmr3.log.Log.info(getClass(),"Child ammessi: "+childTypeIds.get(i));
        }
        if (childTypeIds.size() == 0) return null;
        //it.cineca.siss.axmr3.log.Log.info(getClass(),"Policy to check:" +pCheck.toLikeClause());
        c.createAlias("acls", "acls")
                .createAlias("acls.containers", "aclContainers")
                .add(Restrictions.in("id", childTypeIds))
                .add(Restrictions.eq("deleted", false))
                .setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY)
                .add(pCheck.checkCriterion("acls", "aclContainers", user));
        return c.list();

    }

    public void attachFile(IUser user, Element el, byte[] file, String fileName, Long fileSize, String version, String date, String note, String autore, String elementAction) throws RestException {
        if (elementAction.equals("CREATE")) {
            if (!el.getType().getUserPolicy(user).isCanCreate()) throw new RestException("NOTPERMITTED", 1);
        } else if (!el.getUserPolicy(user).isCanUpdate()) throw new RestException("NOTPERMITTED", 1);
        attachFile(user.getUsername(), el, file, fileName, fileSize, version, date, note, autore, elementAction);

    }

    public void dmAttachFile(IUser user, Element el, byte[] file, String fileName, Long fileSize, String version, String date, String note, String autore) throws  AxmrGenericException  {
            try {
                DateFormat df = new SimpleDateFormat("dd/MM/yyyy");
                Date parsed = null;
                Calendar data = null;
                if (!date.isEmpty()) {
                    try {
                        parsed = df.parse(date.toString());
                        data = Calendar.getInstance();
                        data.setTime(parsed);
                    } catch (java.text.ParseException e) {
                        log.error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
                    }
                }
                registerEvent(user, el, "dmAttachFile");
                if (file != null) {
                    if (el.getFile() == null) {
                        FileContent fc = null;
                        String filenameOnFs = "";
                        if (el.getType().getFileOnFS()) {
                            if (fileName.lastIndexOf('.') >= 0) {
                                String ext = fileName.substring(fileName.lastIndexOf('.'));
                                filenameOnFs = fileOnFsPath + "/" + "file_" + el.getId() + ext;
                            } else {
                                filenameOnFs = fileOnFsPath + "/" + "file_" + el.getId();
                            }
                            try (FileOutputStream fos = new FileOutputStream(filenameOnFs)) {
                                fos.write(file);
                            }

                        } else {
                            fc = new FileContent();
                            fc.setContent(file);
                            try {
                                fileContentDAO.saveOrUpdate(fc);
                            } catch (AxmrGenericException e) {
                                throw new RestException(e.getMessage(), txManager);
                            }
                        }
                        File f = new File();
                        if (!date.isEmpty()) {
                            f.setDate(data);
                        }
                        if (!autore.isEmpty()) {
                            f.setAutore(autore);
                        }
                        if (!version.isEmpty()) {
                            f.setVersion(version);
                        }
                        if (!note.isEmpty()) {
                            f.setNote(note);
                        }
                        if (fileName.endsWith(".pdf")
                                || fileName.endsWith(".xls")
                                || fileName.endsWith(".xlsx")
                                || fileName.endsWith(".doc")
                                || fileName.endsWith(".docx"))
                            f.setIndexable(true);
                        else f.setIndexable(false);
                        f.setIndexed(false);
                        if (!el.getType().getFileOnFS()) f.setContent(fc);
                        else f.setFsFullPath(filenameOnFs);
                        f.setFileName(fileName);
                        f.setSize(fileSize);
                        f.setUploadDt(new GregorianCalendar());
                        f.setUploadUser(user.getUsername());
                        fileSpecDAO.saveOrUpdate(f);
                        el.setFile(f);
                        IUser userInstance = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
                        registerDmAction(user, el, "Added new file ", " File name: " + fileName);
                    } else {
                        File f = el.getFile();
                        registerAuditFile(user.getUsername(), el, "dmNewFileAttached");
                        if (!date.isEmpty()) {
                            f.setDate(data);
                        }
                        if (!autore.isEmpty()) {
                            f.setAutore(autore);
                        }
                        if (!version.isEmpty()) {
                            f.setVersion(version);
                        }
                        if (!note.isEmpty()) {
                            f.setNote(note);
                        }
                        if (fileName.endsWith(".pdf")
                                || fileName.endsWith(".xls")
                                || fileName.endsWith(".xlsx")
                                || fileName.endsWith(".doc")
                                || fileName.endsWith(".docx"))
                            f.setIndexable(true);
                        else f.setIndexable(false);
                        f.setIndexed(false);
                        f.setIndexId(null);
                        String filenameOnFs = "";
                        if (el.getType().getFileOnFS()) {
                            if (fileName.lastIndexOf('.') >= 0) {
                                String ext = fileName.substring(fileName.lastIndexOf('.'));
                                filenameOnFs = fileOnFsPath + "/" + "file_" + el.getId() + ext;
                            } else {
                                filenameOnFs = fileOnFsPath + "/" + "file_" + el.getId();
                            }
                            try (FileOutputStream fos = new FileOutputStream(filenameOnFs)) {
                                fos.write(file);
                            }
                            f.setFsFullPath(filenameOnFs);
                        } else {
                            fileContentDAO.delete(f.getContent());
                            FileContent fc = new FileContent();
                            fc.setContent(file);
                            fileContentDAO.save(fc);
                            if (!el.getType().getFileOnFS()) f.setContent(fc);
                        }
                        f.setFileName(fileName);
                        f.setSize(fileSize);
                        f.setUploadDt(new GregorianCalendar());
                        f.setUploadUser(user.getUsername());
                        fileSpecDAO.saveOrUpdate(f);
                        registerDmAction(user, el, "Added new file ", " File name: " + fileName);
                    }
                }
                else{
                    if (el.getFile() != null) {
                        File f = el.getFile();
                        registerAuditFile(user.getUsername(), el, "dmModifiedFileAttached");
                        if (!date.isEmpty()) {
                            f.setDate(data);
                        }
                        if (!autore.isEmpty()) {
                            f.setAutore(autore);
                        }
                        if (!version.isEmpty()) {
                            f.setVersion(version);
                        }
                        if (!note.isEmpty()) {
                            f.setNote(note);
                        }
                        f.setUploadUser(user.getUsername());
                        fileSpecDAO.saveOrUpdate(f);
                        registerDmAction(user, el, "dmModifiedFileAttached", " File name: " + fileName);
                    }
                }
                el.setLastUpdateDt(new GregorianCalendar());
                el.setLastUpdateUser(user.getUsername());
                docDAO.saveOrUpdate(el);
                addElidToBeUpdeated(el.getId(),true);
                commitTXSessionAndKeepAlive();
                registerEvent(user, el, "dmAttachFile");
            } catch (Exception e) {
                log.error(e.getMessage(), e);
                throw new RestException(e.getMessage(), txManager);
            }

    }
    public void attachFile(String user, Element el, byte[] file, String fileName, Long fileSize, String version, String date, String note, String autore, String elementAction) throws RestException{
        attachFile(user,el,file,fileName,fileSize,version,date,note,autore,elementAction,false);
    }
    public void attachFile(String user, Element el, byte[] file, String fileName, Long fileSize, String version, String date, String note, String autore, String elementAction, boolean forceNoVersion) throws RestException {
       /* StackTraceElement[] stackTraceElements = Thread.currentThread().getStackTrace();
        it.cineca.siss.axmr3.log.Log.info(getClass(), "SONO STATO CHIAMATO DA (stackTrace): ");
        int i =0;
        for (StackTraceElement traceElement :stackTraceElements) {
            it.cineca.siss.axmr3.log.Log.info(getClass(), i++ +" "+traceElement.getClassName()+" "+traceElement.getMethodName()+" "+traceElement.getLineNumber()+" "+traceElement.getFileName());
        }*/
        if (file != null) {
            try {
                if (el.isLocked() && !el.getLockedFromUser().equals(user)) throw new RestException("LOCKED_OBJ", 2);

                DateFormat df = new SimpleDateFormat("dd/MM/yyyy");
                Date parsed = null;
                Calendar data = null;
                if (!date.isEmpty()) {
                    try {
                        parsed = df.parse(date.toString());
                        data = Calendar.getInstance();
                        data.setTime(parsed);
                    } catch (java.text.ParseException e) {
                        log.error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
                    }
                }
                registerEvent(user, el, "attachFile");
                if (el.getFile() == null || forceNoVersion) {
                    FileContent fc = null;
                    String filenameOnFs = "";
                    if (el.getType().getFileOnFS()) {
                        if (fileName.lastIndexOf('.') >= 0) {
                            String ext = fileName.substring(fileName.lastIndexOf('.'));
                            filenameOnFs = fileOnFsPath + "/" + "file_" + el.getId() + ext;
                        } else {
                            filenameOnFs = fileOnFsPath + "/" + "file_" + el.getId();
                        }
                        try (FileOutputStream fos = new FileOutputStream(filenameOnFs)) {
                            fos.write(file);
                        }

                    } else {
                        fc = new FileContent();
                        fc.setContent(file);
                        try {
                            fileContentDAO.saveOrUpdate(fc);
                        } catch (AxmrGenericException e) {
                            throw new RestException(e.getMessage(), txManager);
                        }
                    }
                    File f = new File();
                    f.setDate(data);
                    f.setAutore(autore);
                    f.setVersion(version);
                    f.setNote(note);
                    if (fileName.endsWith(".pdf")
                            || fileName.endsWith(".xls")
                            || fileName.endsWith(".xlsx")
                            || fileName.endsWith(".doc")
                            || fileName.endsWith(".docx"))
                        f.setIndexable(true);
                    else f.setIndexable(false);
                    f.setIndexed(false);
                    if (!el.getType().getFileOnFS()) f.setContent(fc);
                    else f.setFsFullPath(filenameOnFs);
                    f.setFileName(fileName);
                    f.setSize(fileSize);
                    f.setUploadDt(new GregorianCalendar());
                    f.setUploadUser(user);
                    fileSpecDAO.saveOrUpdate(f);
                    el.setFile(f);
                } else {
                    File f = el.getFile();
                    registerAuditFile(user, el, "newFileAttached");
                    f.setDate(data);
                    f.setAutore(autore);
                    f.setVersion(version);
                    f.setNote(note);
                    if (fileName.endsWith(".pdf")
                            || fileName.endsWith(".xls")
                            || fileName.endsWith(".xlsx")
                            || fileName.endsWith(".doc")
                            || fileName.endsWith(".docx"))
                        f.setIndexable(true);
                    else f.setIndexable(false);
                    f.setIndexed(false);
                    f.setIndexId(null);
                    String filenameOnFs = "";
                    if (el.getType().getFileOnFS()) {
                        if (fileName.lastIndexOf('.') >= 0) {
                            String ext = fileName.substring(fileName.lastIndexOf('.'));
                            filenameOnFs = fileOnFsPath + "/" + "file_" + el.getId() + ext;
                        } else {
                            filenameOnFs = fileOnFsPath + "/" + "file_" + el.getId();
                        }
                        try (FileOutputStream fos = new FileOutputStream(filenameOnFs)) {
                            fos.write(file);
                        }
                        f.setFsFullPath(filenameOnFs);
                    } else {
                        fileContentDAO.delete(f.getContent());
                        FileContent fc = new FileContent();
                        fc.setContent(file);
                        fileContentDAO.save(fc);
                        if (!el.getType().getFileOnFS()) f.setContent(fc);
                    }
                    f.setFileName(fileName);
                    f.setSize(fileSize);
                    f.setUploadDt(new GregorianCalendar());
                    f.setUploadUser(user);
                    fileSpecDAO.saveOrUpdate(f);
                }
                el.setLastUpdateDt(new GregorianCalendar());
                el.setLastUpdateUser(user);
                docDAO.saveOrUpdate(el);
                //TOSCANA-168 se aggiungo una nuova versione non parte il processo invia al ce che è abilitato anche in modifica
                //PERMETTE DI FAR RIPARTIRE GLI EVENTUALI PROCESSI DA ATTIVARE IN MODIFICA
                for (ElementTypeAssociatedWorkflow wf : el.getType().getAssociatedWorkflows()) {
                    if (wf.isStartOnUpdate()) {
                        startProcess(el, wf.getProcessKey());
                    }
                }
                addElidToBeUpdeated(el.getId(),true);
                commitTXSessionAndKeepAlive();
                registerEvent(user, el, "AttachFile");
            } catch (Exception e) {
                log.error(e.getMessage(), e);
                throw new RestException(e.getMessage(), txManager);
            }
        }
    }
    //TODO: Parametro user non utilizzato si può eliminare?
    private void registerAuditFile(IUser user, Element el, String newFileAttached) throws RestException {
        registerAuditFile(user.getUsername(), el, newFileAttached);
    }

    //TODO: Parametro user non utilizzato si può eliminare?
    private void registerAuditFile(String user, Element el, String newFileAttached) throws RestException {
        try {
            AuditFile f = new AuditFile();
            f.setIndexId(el.getFile().getIndexId());
            f.setIndexed(el.getFile().isIndexed());
            f.setIndexable(el.getFile().isIndexable());
            f.setAutore(el.getFile().getAutore());
            f.setNote(el.getFile().getNote());
            f.setDate(el.getFile().getDate());
            f.setVersion(el.getFile().getVersion());
            if (!el.getType().getFileOnFS()) {
                AuditFileContent fc = new AuditFileContent();
                fc.setContent(el.getFile().getContent().getContent());
                aFileContentDAO.save(fc);
                f.setContent(fc);
                f.setUniqueId(el.getFile().getContent().getId());
            } else {
                String revAttach = ".rev-";
                if (el.getAuditFiles() == null || el.getAuditFiles().size() == 0) revAttach += "0";
                else revAttach += el.getAuditFiles().size();
                java.io.File file = new java.io.File(el.getFile().getFsFullPath());
                boolean renamed = file.renameTo(new java.io.File(el.getFile().getFsFullPath() + revAttach));
                if (!renamed) {
                    throw new RestException("RENAME_ERROR", txManager);
                }
                f.setFsFullPath(el.getFile().getFsFullPath() + revAttach);
                f.setUniqueId(new Long(-1));
            }
            f.setFileName(el.getFile().getFileName());
            f.setSize(el.getFile().getSize());
            f.setUploadDt(el.getFile().getUploadDt());
            f.setUploadUser(el.getFile().getUploadUser());
            f.setUniqueId(el.getFile().getContent().getId());
            aFileDAO.save(f);
            if (el.getAuditFiles() == null) el.setAuditFiles(new LinkedList<AuditFile>());
            el.getAuditFiles().add(f);
            docDAO.saveOrUpdate(el);
            addElidToBeUpdeated(el.getId(),true);
            commitTXSessionAndKeepAlive();
        } catch (Exception e) {
            log.error(e.getMessage(), e);
            throw new RestException(e.getMessage(), txManager);
        }
    }

    public void deleteComment(IUser user, Element el, Long commentId) throws RestException {
        Comment c = commentDAO.getById(commentId);
        el.getComments().remove(c);
        try {
            commentDAO.delete(c);
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        }
        registerEvent(user, el, "deleteComment");
    }

    protected void setMetadataValue(IUser user, Element el, String templateName, String fieldName, String value, boolean fromWf, String elementAction) throws RestException, AxmrGenericException {
        if (user == null && !fromWf) {
            throw new RestException("User or Workflow not defined 2", txManager);
        }
        if (user != null) {
            if (elementAction.equals("CREATE")) {
                if (!el.getType().getUserPolicy(user).isCanCreate()) {
                    throw new RestException("NOTPERMITTED", txManager);
                }
            } else {
                if (!el.getUserPolicy(user).isCanUpdate() || (el.isLocked() && !el.getLockedFromUser().equals(user.getUsername()))) {
                    throw new RestException("NOTPERMITTED", txManager);
                }
            }
        }
        if (user != null) {
            setMetadataValue(user.getUsername(), user, el, templateName, fieldName, value, fromWf, elementAction);
        }
    }

    protected void setMetadataValue(String user, Element el, String templateName, String fieldName, String value, boolean fromWf, String elementAction) throws RestException, AxmrGenericException {
        setMetadataValue(user, null, el, templateName, fieldName, value, fromWf, elementAction);
    }

    protected void setMetadataValue(String user, IUser userInstance, Element el, String templateName, String fieldName, String value, boolean fromWf, String elementAction) throws RestException, AxmrGenericException {
        setMetadataValue(user, userInstance, el, templateName, fieldName, value, fromWf, elementAction, false);
    }

    protected void setMetadataValue(String user, IUser userInstance, Element el, String templateName, String fieldName, String value, boolean fromWf, String elementAction, boolean cloning) throws RestException, AxmrGenericException {
        HashMap<String, String> data;
        if (userInstance == null && !fromWf) {
            throw new RestException("User or Workflow not defined 1", txManager);
        }
        ElementTemplate et = null;
        MetadataTemplate template = null;
        for (ElementTemplate et_ : el.getElementTemplates()) {
            if (et_.getMetadataTemplate().getName().equals(templateName)) {
                et = et_;
            }
        }
        if (et == null) {
            try {
                if (user != null) {
                    et = addTemplate(user, el, templateName);
                } else {
                    et = addTemplate(el, templateName);
                }
                if (et == null) {
                    et = addAvailableTemplateToElement(el, templateName);
                }
            } catch (RestException e) {
                et = addAvailableTemplateToElement(el, templateName);
                //throw new RestException("Template " + templateName + " non associato all'elemnto", txManager);
            }
        }
        if (et == null) throw new RestException("Template " + templateName + " non associato all'elemnto", txManager);
        template = et.getMetadataTemplate();
        MetadataField field = null;
        for (MetadataField f : template.getFields()) {
            if (f.getName().equals(fieldName)) field = f;
        }
        if (field == null) throw new RestException("FieldNotFound: " + template.getName() + "_" + fieldName, txManager);
        if (value == null){
            value = "";
        }
        value=value.trim();
        if (field.getRegexpCheck()!=null && !field.getRegexpCheck().isEmpty() && !value.isEmpty()){//VMAZZEO AGGIUNGO CHE IL CONTROLLO PARTA SOLO SE IL FIELD E' COMPILATO
            if (!value.matches(field.getRegexpCheck())){
                throw new RestException("RegexpCheckFailed: " + template.getName() + "_" + fieldName, txManager);
            }
        }
        ElementMetadata metaData = null;
        for (ElementMetadata md : el.getData()) {
            if (md.getTemplate().equals(template) && md.getField().equals(field)) metaData = md;
        }
        if (metaData != null) {
            for (ElementMetadataValue val : metaData.getValues()) {
                elMdValueDAO.delete(val);
            }
            elMdDAO.delete(metaData);
        }

        if (metaData != null && !elementAction.equals("CREATE")) {
            /*Aggiornamento metadato*/
            if (userInstance != null && !elementAction.startsWith("EMENDAMENTO")) {
                if (!et.getUserPolicy(userInstance, el).isCanUpdate())
                    throw new AxmrGenericException("L'utente non può aggiornare il campo:" + templateName + "." + fieldName);
            }
            //it.cineca.siss.axmr3.log.Log.info(getClass(),"Il metadato "+templateName+"."+fieldName+" è definito, lo aggiorno");
            if (template.isAuditable()) {
                if (elementAction.startsWith("EMENDAMENTO")){
                    registerAudit(user, el, value, metaData, elementAction);
                } else {
                registerAudit(user, el, value, metaData, "update");
            }
            }
            if (hasChanged(value, metaData, "update")) {
                for (ElementTypeAssociatedWorkflow awf : el.getType().getAssociatedWorkflows()) {
                    if (awf.isEnabled() && awf.isStartOnUpdate()) {
                        Long elId = el.getId();
                        txManager.getTxs().get("doc").commit();
                        if (!txManager.getSessions().get("doc").isOpen()) {
                            //it.cineca.siss.axmr3.log.Log.info(getClass(),"La sessione è chiusa, la riapro");
                            it.cineca.siss.axmr3.log.Log.info(getClass(), "Apro la sessione 4 " + this.getClass().getCanonicalName());
                            txManager.getSessions().put("doc", txManager.getSessionFactories().get("doc").openSession());
                            it.cineca.siss.axmr3.log.Log.info(getClass(), "Begin Transaction 7 " + this.getClass().getCanonicalName());
                            txManager.getTxs().put("doc", txManager.getSessions().get("doc").beginTransaction());
                        } else {
                            //it.cineca.siss.axmr3.log.Log.info(getClass(),"La sessione è aperta, controllo la transazione");
                            if (!txManager.getTxs().get("doc").isActive()) {
                                //it.cineca.siss.axmr3.log.Log.info(getClass(),"La transazione non è attiva 1");
                                it.cineca.siss.axmr3.log.Log.info(getClass(), "Begin Transaction 8 " + this.getClass().getCanonicalName());
                                txManager.getTxs().put("doc", txManager.getSessions().get("doc").beginTransaction());
                            }
                        }
                        el = this.getElement(elId);
                        data = new HashMap<String, String>();
                        data.put("templateName", templateName);
                        data.put("fieldName", fieldName);
                        data.put("fieldValue", value);
                        this.startProcess(user, el, awf.getProcessKey(), data);

                    }
                }
            }

            //it.cineca.siss.axmr3.log.Log.info(getClass(),"Il metadato "+templateName+"."+fieldName+" è definito, lo aggiorno");

        } else {
            /*Aggiunta metadato*/

            if (userInstance != null) {
                if (elementAction.equals("CREATE")) {
                    ElementTypeAssociatedTemplate ett_ = null;
                    for (ElementTypeAssociatedTemplate ett : el.getType().getAssociatedTemplates()) {
                        if (ett.getMetadataTemplate().getName().equals(templateName)) ett_ = ett;
                    }
                    if (ett_ != null) if (!ett_.getUserPolicy(userInstance, el.getType()).isCanCreate())
                        throw new AxmrGenericException("L'utente non può creare il campo:" + templateName + "." + fieldName);

                } else if (!elementAction.startsWith("EMENDAMENTO") && !et.getUserPolicy(userInstance, el).isCanCreate())
                    throw new AxmrGenericException("L'utente non può creare il campo:" + templateName + "." + fieldName);
            }
            metaData = new ElementMetadata();
            metaData.setTemplate(template);
            metaData.setField(field);
            if (template.isAuditable()) {
                if (elementAction.startsWith("EMENDAMENTO")){
                    registerAudit(user, el, value, metaData, elementAction);
                }else {
                registerAudit(user, el, value, metaData, "create");
            }
            }
            //it.cineca.siss.axmr3.log.Log.info(getClass(),"Il metadato "+templateName+"."+fieldName+" non è definito, lo creo");
        }
        metaData = new ElementMetadata();
        metaData.setTemplate(template);
        metaData.setField(field);
        if (field.getType().equals(MetadataFieldType.ELEMENT_LINK)) {
            if (value.isEmpty()) metaData.setVal(null);
            else metaData.setVal(this.getElement(Long.parseLong(value)));
        } else {
            metaData.setVal(value);
        }
        for (ElementMetadataValue val : metaData.getValues()) {
            elMdValueDAO.save(val);
        }
        elMdDAO.save(metaData);
        el.getData().add(metaData);

        recurseUpdateDt(el, user, new GregorianCalendar(), cloning);
        //el.setLastUpdateUser(user.getUsername());
        //el.setLastUpdateDt(new GregorianCalendar());

        docDAO.saveOrUpdate(el);
        addElidToBeUpdeated(el.getId(),true);
        if (!cloning) {
            commitTXSessionAndKeepAlive();
        }
    }

    protected void setMetadataValueArray(String user, IUser userInstance, Element el, String templateName, String fieldName, String[] value, boolean fromWf, String elementAction) throws RestException, AxmrGenericException {
        setMetadataValueArray(user, userInstance, el, templateName, fieldName, value, fromWf, elementAction, false);
    }

    protected void setMetadataValueArray(String user, IUser userInstance, Element el, String templateName, String fieldName, String[] value, boolean fromWf, String elementAction, boolean cloning) throws RestException, AxmrGenericException {
        HashMap<String, String> data;
        if (userInstance == null && !fromWf) {
            throw new RestException("User or Workflow not defined 1", txManager);
        }
        ElementTemplate et = null;
        MetadataTemplate template = null;
        for (ElementTemplate et_ : el.getElementTemplates()) {
            if (et_.getMetadataTemplate().getName().equals(templateName)) {
                et = et_;
            }
        }
        if (et == null) {
            try {
                if (user != null) {
                    addTemplate(user, el, templateName);
                } else {
                    addTemplate(el, templateName);
                }
            } catch (RestException e) {
                throw new RestException("Template " + templateName + " non associato all'elemnto", txManager);
            }
        }
        if (et == null) throw new RestException("Template " + templateName + " non associato all'elemnto", txManager);
        template = et.getMetadataTemplate();
        MetadataField field = null;
        for (MetadataField f : template.getFields()) {
            if (f.getName().equals(fieldName)) field = f;
        }
        if (field == null) throw new RestException("FieldNotFound: " + template.getName() + "_" + fieldName, txManager);
        ElementMetadata metaData = null;
        for (ElementMetadata md : el.getData()) {
            if (md.getTemplate().equals(template) && md.getField().equals(field)) metaData = md;
        }
        if (metaData != null) {
            for (ElementMetadataValue val : metaData.getValues()) {
                elMdValueDAO.delete(val);
            }
            elMdDAO.delete(metaData);
        }

        if (metaData != null && !elementAction.equals("CREATE")) {
            /*Aggiornamento metadato*/
            if (userInstance != null && !elementAction.startsWith("EMENDAMENTO")) {
                if (!et.getUserPolicy(userInstance, el).isCanUpdate())
                    throw new AxmrGenericException("L'utente non può aggiornare il campo:" + templateName + "." + fieldName);
            }
            //it.cineca.siss.axmr3.log.Log.info(getClass(),"Il metadato "+templateName+"."+fieldName+" è definito, lo aggiorno");
            if (template.isAuditable()) {
                if (elementAction.startsWith("EMENDAMENTO")){
                    registerAuditArray(user, el, value, metaData, elementAction);
                }else{
                registerAuditArray(user, el, value, metaData, "update");
            }
            }
            if (hasChangedArray(value, metaData, "update")) {
                for (ElementTypeAssociatedWorkflow awf : el.getType().getAssociatedWorkflows()) {
                    if (awf.isEnabled() && awf.isStartOnUpdate()) {
                        Long elId = el.getId();
                        txManager.getTxs().get("doc").commit();
                        if (!txManager.getSessions().get("doc").isOpen()) {
                            it.cineca.siss.axmr3.log.Log.info(getClass(), "Apro la sessione 4 " + this.getClass().getCanonicalName());
                            txManager.getSessions().put("doc", txManager.getSessionFactories().get("doc").openSession());
                            it.cineca.siss.axmr3.log.Log.info(getClass(), "Begin Transaction 7 " + this.getClass().getCanonicalName());
                            txManager.getTxs().put("doc", txManager.getSessions().get("doc").beginTransaction());
                        } else {
                            if (!txManager.getTxs().get("doc").isActive()) {
                                it.cineca.siss.axmr3.log.Log.info(getClass(), "Begin Transaction 8 " + this.getClass().getCanonicalName());
                                txManager.getTxs().put("doc", txManager.getSessions().get("doc").beginTransaction());
                            }
                        }
                        el = this.getElement(elId);
                        data = new HashMap<String, String>();
                        data.put("templateName", templateName);
                        //data.put("fieldName",fieldName);
                        //data.put("fieldValue",value);
                        this.startProcess(user, el, awf.getProcessKey(), data);
                    }
                }
            }
        } else {
            if (userInstance != null) {
                if (elementAction.equals("CREATE")) {
                    ElementTypeAssociatedTemplate ett_ = null;
                    for (ElementTypeAssociatedTemplate ett : el.getType().getAssociatedTemplates()) {
                        if (ett.getMetadataTemplate().getName().equals(templateName)) ett_ = ett;
                    }
                    if (ett_ != null) if (!ett_.getUserPolicy(userInstance, el.getType()).isCanCreate())
                        throw new AxmrGenericException("L'utente non può creare il campo:" + templateName + "." + fieldName);

                } else if (!elementAction.startsWith("EMENDAMENTO") && !et.getUserPolicy(userInstance, el).isCanCreate())
                    throw new AxmrGenericException("L'utente non può creare il campo:" + templateName + "." + fieldName);
            }
            metaData = new ElementMetadata();
            metaData.setTemplate(template);
            metaData.setField(field);
            if (template.isAuditable()) {
                if (elementAction.startsWith("EMENDAMENTO")){
                    registerAuditArray(user, el, value, metaData, elementAction);
                }else {
                registerAuditArray(user, el, value, metaData, "create");
            }
            }
            //it.cineca.siss.axmr3.log.Log.info(getClass(),"Il metadato "+templateName+"."+fieldName+" non è definito, lo creo");
        }
        metaData = new ElementMetadata();
        metaData.setTemplate(template);
        metaData.setField(field);
        if (field.getType().equals(MetadataFieldType.ELEMENT_LINK)) {
            if (value.length == 0) metaData.setVal(null);
            else {
                for (int i = 0; i < value.length; i++) {
                    metaData.setVal(this.getElement(Long.parseLong(value[i])));
                }
            }
        } else {
            for (int i = 0; i < value.length; i++) {
                metaData.setVal(value[i]);
            }
        }
        for (ElementMetadataValue val : metaData.getValues()) {
            elMdValueDAO.save(val);
        }
        elMdDAO.save(metaData);
        el.getData().add(metaData);
        if (elementAction.equals("UPDATE")) {
            recurseUpdateDt(el, user, new GregorianCalendar());
            //el.setLastUpdateUser(user.getUsername());
            //el.setLastUpdateDt(new GregorianCalendar());
        }
        docDAO.saveOrUpdate(el);
        addElidToBeUpdeated(el.getId(),true);
        if (!cloning) {
            commitTXSessionAndKeepAlive();
        }
    }

    protected void recurseUpdateDt(Element el, IUser user, GregorianCalendar date) throws AxmrGenericException {
        recurseUpdateDt(el, user.getUsername(), date);
    }

    protected void recurseUpdateDt(Element el, String user, GregorianCalendar date) throws AxmrGenericException {
        recurseUpdateDt(el, user, date, false);
    }

    protected void recurseUpdateDt(Element el, String user, GregorianCalendar date, boolean cloning) throws AxmrGenericException {
        if (el != null) {
            el.setLastUpdateUser(user);
            el.setLastUpdateDt(date);
            docDAO.saveOrUpdate(el);
            addElidToBeUpdeated(el.getId(),true);
            if (!cloning) {
                commitTXSessionAndKeepAlive();
            }
            recurseUpdateDt(el.getParent(), user, date);
        }
    }

    protected void setMetadataValue(IUser user, Long elId, String templateName, String fieldName, String value, boolean fromWf, String ElementAction) throws AxmrGenericException {
        setMetadataValue(user.getUsername(), elId, templateName, fieldName, value, fromWf, ElementAction);
    }

    protected void setMetadataValue(String user, Long elId, String templateName, String fieldName, String value, boolean fromWf, String ElementAction) throws AxmrGenericException {
        Element el = getElement(elId);
        setMetadataValue(user, el, templateName, fieldName, value, fromWf, ElementAction);
    }

    public void updateElementMetaData(IUser user, Element el, Map<String, String> data, String ElementAction) throws RestException {
        try {
            if (!ElementAction.equals("CREATE") &&  !ElementAction.startsWith("EMENDAMENTO")) {
                if (!el.getUserPolicy(user).isCanUpdate() || (el.isLocked() && !el.getLockedFromUser().equals(user.getUsername())))
                    throw new RestException("NOTPERMITTED", txManager);
            }
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        } catch (org.hibernate.HibernateException ex) {
            log.error(ex.getMessage(), ex);
        }
        updateElementMetaData(user.getUsername(), user, el, data, ElementAction);
    }

    public void updateElementMetaData(String user, Element el, Map<String, String> data, String ElementAction) throws RestException {
        updateElementMetaData(user, null, el, data, ElementAction);
    }

    public void updateElementMetaData(String user, IUser userInstance, Element el, Map<String, String> data, String ElementAction) throws RestException {
        updateElementMetaData(user, userInstance, el, data, ElementAction, false);
    }

    //TODO: do per scontato che se manca lo user sia giunto qui da bpm. Aggiungere un percorso che me lo possa garantire
    //TODO: controllo processi all'update del singolo metadato ma se inserisco un nuovo elemento o aggiorno molteplici metadati finisco per farlo n volte ?
    public void updateElementMetaData(String user, IUser userInstance, Element el, Map<String, String> data, String ElementAction, boolean cloning) throws RestException {
        try {

            Iterator<String> dataIt = data.keySet().iterator();
            boolean fromWF = (userInstance == null);

            while (dataIt.hasNext()) {
                String paramName = dataIt.next();
                String parameter = data.get(paramName);
                //it.cineca.siss.axmr3.log.Log.info(getClass(),"Ciclo il valore: "+paramName+" - "+parameter);
                String[] fieldSpec = paramName.split("_");
                if (fieldSpec.length < 2) continue;
                String templateName = fieldSpec[0];
                String fieldName = fieldSpec[1];
                if (fieldName.endsWith("-altro") || fieldName.endsWith("-select")) continue;

                setMetadataValue(user, userInstance, el, templateName, fieldName, parameter, fromWF, ElementAction, cloning);
            }
            /*if (ElementAction.equals("UPDATE")){
                for (ElementTypeAssociatedWorkflow awf:el.getType().getAssociatedWorkflows()){
                    if (awf.isStartOnUpdate()){
                        startProcess(user, el, awf.getProcessKey());
                    }
                }
            }*/
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        } catch (org.hibernate.HibernateException ex) {
            log.error(ex.getMessage(), ex);
        }
    }

    public void updateElementMetaData(IUser user, Long elId, Map<String, String> data) throws RestException {
        Element el = getElement(elId);
        updateElementMetaData(user, el, data, "UPDATE");
    }

    public void updateElementMetaDataEme(IUser user, Long elId, Map<String, String> data, Long emeSessionId) throws RestException {
        Element el = getElement(elId);
        updateElementMetaDataEme(user, el, data, "UPDATE", emeSessionId);
    }

    public void updateElementMetaDataEme(IUser user, Element el, Map<String, String> data, String ElementAction, Long emeSessionId) throws RestException {
        /*
        try {
            if (!ElementAction.equals("CREATE")) {

                //if (!el.getUserPolicy(user).isCanUpdate() || (el.isLocked() && !el.getLockedFromUser().equals(user.getUsername())))
                //    throw new RestException("NOTPERMITTED", txManager);
            }
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        } catch (org.hibernate.HibernateException ex) {
            log.error(ex.getMessage(),ex);
        }
        */
        updateElementMetaDataEme(user.getUsername(), user, el, data, ElementAction, emeSessionId);
    }

    public void updateElementMetaDataEme(String user, IUser userInstance, Element el, Map<String, String> data, String ElementAction, Long emeSessionId) throws RestException {
        updateElementMetaDataEme(user, userInstance, el, data, ElementAction, emeSessionId, false);
    }

    public void updateElementMetaDataEme(String user, IUser userInstance, Element el, Map<String, String> data, String ElementAction, Long emeSessionId, boolean cloning) throws RestException {
        try {

            Iterator<String> dataIt = data.keySet().iterator();
            boolean fromWF = (userInstance == null);

            Collection<ElementMetadata> dataSaved = el.getData();
            HashMap<String, ElementMetadata> emvalues=new HashMap<String, ElementMetadata>();
            for (ElementMetadata emd:dataSaved) {
                emvalues.put(emd.getTemplateName()+"_"+emd.getFieldName(), emd);
                //emd.getVals().get(0)
                //cioè emvalues.get('paramName').getVals().get(0)
            }

            while (dataIt.hasNext()) {
                String paramName = dataIt.next();
                String parameter = data.get(paramName);
                //it.cineca.siss.axmr3.log.Log.info(getClass(),"Ciclo il valore: "+paramName+" - "+parameter);
                String[] fieldSpec = paramName.split("_");
                if (fieldSpec.length < 2) continue;
                String templateName = fieldSpec[0];
                String fieldName = fieldSpec[1];
                if (fieldName.endsWith("-altro") || fieldName.endsWith("-select")) continue;

                boolean goon=true;

                if (emvalues.get(paramName)!=null) {
                    if (emvalues.get(paramName).getVals().size() == 0) {
                        if (parameter == null || parameter == "") goon = false;
                    } else if (emvalues.get(paramName).getVals().get(0).equals(parameter)) {
                        goon = false;
                    }
                }else if (parameter == null || parameter == ""){
                    goon = false;
                }

                if (goon==true){

                    //setMetadataValue(user, userInstance, el, templateName, fieldName, parameter, fromWF, ElementAction, cloning);

                    String specification = "";
                    specification = "update"; //quindi aggiorniamo il metadato

                    EmendamentoAction action = new EmendamentoAction();
                    //Recupero la "sessione" corrente a partire dall'id in sessione rest
                    EmendamentoSession currentEmeSession = getActiveEmeSession(emeSessionId);
                    action.setEmendamento(currentEmeSession);
                    action.setAction("UPDATE_METADATA");
                    action.setObjId(el);
                    action.setActionDt(new GregorianCalendar());
                    action.setSpecification(specification);
                    emeActionDAO.save(action);

                    ElementTemplate et = null;
                    MetadataTemplate template = null;
                    for (ElementTemplate et_ : el.getElementTemplates()) {
                        if (et_.getMetadataTemplate().getName().equals(templateName)) {
                            et = et_;
                        }
                    }
                    if (et == null) {
                        try {
                            if (user != null) {
                                addTemplate(user, el, templateName);
                            } else {
                                addTemplate(el, templateName);
                            }
                        } catch (RestException e) {
                            throw new RestException("Template " + templateName + " non associato all'elemnto", txManager);
                        }
                    }
                    if (et == null) throw new RestException("Template " + templateName + " non associato all'elemnto", txManager);
                    template = et.getMetadataTemplate();


                    MetadataField field = null;
                    for (MetadataField f : template.getFields()) {
                        if (f.getName().equals(fieldName)) field = f;
                    }

                    if (field == null) throw new RestException("FieldNotFound: " + template.getName() + "_" + fieldName, txManager);
                    AuditEmeMetadata amd = new AuditEmeMetadata(); //creo record di Audit
                    amd.setField(field);
                    amd.setModDt(new GregorianCalendar());
                    amd.setTemplate(template);
                    amd.setUsername(user);
                    amd.setAction("DM_UPDATE");
                    amd.setEmendamento(currentEmeSession);
                    amd.setEmeAction(action);
                    if (el.getAuditData() == null) {
                        el.setAuditData(new LinkedList<AuditMetadata>());
                    }
                    if (amd.getField().getType().equals(MetadataFieldType.ELEMENT_LINK)) {
                        try {
                            Element lel = this.getElement(Long.parseLong((String) parameter));
                            amd.setVal(lel);
                        } catch (NumberFormatException ex) {
                            //it.cineca.siss.axmr3.log.Log.info(getClass(),"Valore "+parameter+" non numerico per campo "+amd.getField().getTemplate().getName()+"."+amd.getField().getName());
                            amd.setVal(null);
                        }

                    } else amd.setVal(parameter);

                    for (AuditEmeValue val : amd.getValues()) {
                        val.setOld(false);
                        try {
                            aEmeMdValDAO.save(val);
                        } catch (AxmrGenericException e) {
                            throw new RestException(e.getMessage(), txManager);
                        }
                    }

                    try {
                        aEmeMdDAO.save(amd);
                    } catch (AxmrGenericException e) {
                        throw new RestException(e.getMessage(), txManager);
                    }
                }
            }
            /*if (ElementAction.equals("UPDATE")){
                for (ElementTypeAssociatedWorkflow awf:el.getType().getAssociatedWorkflows()){
                    if (awf.isStartOnUpdate()){
                        startProcess(user, el, awf.getProcessKey());
                    }
                }
            }*/
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        } catch (org.hibernate.HibernateException ex) {
            log.error(ex.getMessage(),ex);
        }
    }



    public void updateElementMetaDataArray(IUser user, Element el, Map<String, String[]> data, String ElementAction) throws RestException {
        try {
            if (!ElementAction.equals("CREATE") && !ElementAction.startsWith("EMENDAMENTO")) {
                if (!el.getUserPolicy(user).isCanUpdate() || (el.isLocked() && !el.getLockedFromUser().equals(user.getUsername())))
                    throw new RestException("NOTPERMITTED", txManager);
            }
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        } catch (org.hibernate.HibernateException ex) {
            log.error(ex.getMessage(), ex);
        }
        updateElementMetaDataArray(user.getUsername(), user, el, data, ElementAction);
    }

    public void updateElementMetaDataArray(String user, Element el, Map<String, String[]> data, String ElementAction) throws RestException {
        updateElementMetaDataArray(user, null, el, data, ElementAction);
    }

    //TODO: do per scontato che se manca lo user sia giunto qui da bpm. Aggiungere un percorso che me lo possa garantire
    //TODO: controllo processi all'update del singolo metadato ma se inserisco un nuovo elemento o aggiorno molteplici metadati finisco per farlo n volte ?
    public void updateElementMetaDataArray(String user, IUser userInstance, Element el, Map<String, String[]> data, String ElementAction) throws RestException {
        try {

            Iterator<String> dataIt = data.keySet().iterator();
            boolean fromWF = (userInstance == null);

            while (dataIt.hasNext()) {
                String paramName = dataIt.next();
                String[] parameter = data.get(paramName);

                //it.cineca.siss.axmr3.log.Log.info(getClass(),"Ciclo il valore: "+paramName+" - "+parameter);
                String[] fieldSpec = paramName.split("_");
                if (fieldSpec.length < 2) continue;
                String templateName = fieldSpec[0];
                String fieldName = fieldSpec[1];
                if (fieldName.endsWith("-altro") || fieldName.endsWith("-select")) continue;
                log.info("(updateElementMetaDataArray) -- TEMPLATE: "+templateName+" - FIELD: "+fieldName);
                if (parameter == null || parameter.length==0) {
                    setMetadataValue(user, userInstance, el, templateName, fieldName, null, fromWF, ElementAction);
                } else {
                    if (parameter.length > 1) {
                        setMetadataValueArray(user, userInstance, el, templateName, fieldName, parameter, fromWF, ElementAction);
                    } else {
                        setMetadataValue(user, userInstance, el, templateName, fieldName, parameter[0], fromWF, ElementAction);

                    }
                }

            }
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        } catch (org.hibernate.HibernateException ex) {
            log.error(ex.getMessage(), ex);
        }
    }

    public void updateElementMetaDataArray(IUser user, Long elId, Map<String, String[]> data) throws RestException {
        updateElementMetaDataArray(user, elId, data, "UPDATE");
    }
    public void updateElementMetaDataArray(IUser user, Long elId, Map<String, String[]> data, String ElementAction) throws RestException {
        Element el = getElement(elId);
        updateElementMetaDataArray(user, el, data, ElementAction);
    }

    public void updateElementMetaDataArrayEme(IUser user, Long elId, Map<String, String[]> data, Long emeSessionId) throws RestException {
        Element el = getElement(elId);
        updateElementMetaDataArrayEme(user, el, data, "UPDATE", emeSessionId);
    }

    public void updateElementMetaDataArrayEme(IUser user, Element el, Map<String, String[]> data, String ElementAction, Long emeSessionId) throws RestException {
        /*
        try {
            if (!ElementAction.equals("CREATE")) {
                if (!el.getUserPolicy(user).isCanUpdate() || (el.isLocked() && !el.getLockedFromUser().equals(user.getUsername())))
                    throw new RestException("NOTPERMITTED", txManager);
            }
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        } catch (org.hibernate.HibernateException ex) {
            log.error(ex.getMessage(),ex);
        }
        */
        updateElementMetaDataArrayEme(user.getUsername(), user, el, data, ElementAction, emeSessionId);
    }


    public void updateElementMetaDataArrayEme(String user, IUser userInstance, Element el, Map<String, String[]> data, String ElementAction, Long emeSessionId) throws RestException {
        try {

            Iterator<String> dataIt = data.keySet().iterator();
            boolean fromWF = (userInstance == null);


            Collection<ElementMetadata> dataSaved = el.getData();
            HashMap<String, ElementMetadata> emvalues=new HashMap<String, ElementMetadata>();
            for (ElementMetadata emd:dataSaved) {
                emvalues.put(emd.getTemplateName()+"_"+emd.getFieldName(), emd);
                //emd.getVals().get(0)
                //cioè emvalues.get('paramName').getVals().get(0)
            }

            while (dataIt.hasNext()) {
                String paramName = dataIt.next();
                String[] parameter = data.get(paramName);

                //it.cineca.siss.axmr3.log.Log.info(getClass(),"Ciclo il valore: "+paramName+" - "+parameter);
                String[] fieldSpec = paramName.split("_");
                if (fieldSpec.length < 2) continue;
                String templateName = fieldSpec[0];
                String fieldName = fieldSpec[1];
                if (fieldName.endsWith("-altro") || fieldName.endsWith("-select")) continue;


                if (parameter == null) {
                    if (!(emvalues.get(paramName)!=null && emvalues.get(paramName).getVals().size() == 0)) {

                        //LUIGI: esegui salvataggio per valore parameter nullo

                        String specification = "";
                        specification = "update"; //quindi aggiorniamo il metadato

                        EmendamentoAction action = new EmendamentoAction();
                        //Recupero la "sessione" corrente a partire dall'id in sessione rest
                        EmendamentoSession currentEmeSession = getActiveEmeSession(emeSessionId);
                        action.setEmendamento(currentEmeSession);
                        action.setAction("UPDATE_METADATA");
                        action.setObjId(el);
                        action.setActionDt(new GregorianCalendar());
                        action.setSpecification(specification);
                        emeActionDAO.save(action);

                        ElementTemplate et = null;
                        MetadataTemplate template = null;
                        for (ElementTemplate et_ : el.getElementTemplates()) {
                            if (et_.getMetadataTemplate().getName().equals(templateName)) {
                                et = et_;
                            }
                        }
                        if (et == null) {
                            try {
                                if (user != null) {
                                    addTemplate(user, el, templateName);
                                } else {
                                    addTemplate(el, templateName);
                                }
                            } catch (RestException e) {
                                throw new RestException("Template " + templateName + " non associato all'elemnto", txManager);
                            }
                        }
                        if (et == null) throw new RestException("Template " + templateName + " non associato all'elemnto", txManager);
                        template = et.getMetadataTemplate();


                        MetadataField field = null;
                        for (MetadataField f : template.getFields()) {
                            if (f.getName().equals(fieldName)) field = f;
                        }

                        if (field == null) throw new RestException("FieldNotFound: " + template.getName() + "_" + fieldName, txManager);
                        AuditEmeMetadata amd = new AuditEmeMetadata(); //creo record di Audit
                        amd.setField(field);
                        amd.setModDt(new GregorianCalendar());
                        amd.setTemplate(template);
                        amd.setUsername(user);
                        amd.setAction("DM_UPDATE");
                        amd.setEmendamento(currentEmeSession);
                        amd.setEmeAction(action);
                        if (el.getAuditData() == null) {
                            el.setAuditData(new LinkedList<AuditMetadata>());
                        }
                        amd.setVal(null);

                        for (AuditEmeValue val : amd.getValues()) {
                            val.setOld(false);
                            try {
                                aEmeMdValDAO.save(val);
                            } catch (AxmrGenericException e) {
                                throw new RestException(e.getMessage(), txManager);
                            }
                        }

                        try {
                            aEmeMdDAO.save(amd);
                        } catch (AxmrGenericException e) {
                            throw new RestException(e.getMessage(), txManager);
                        }

                    }
                } else if (parameter.length ==1) {
                    if (!(emvalues.get(paramName) != null && emvalues.get(paramName).getVals().size() == 1 && emvalues.get(paramName).getVals().get(0).equals(parameter[0]))) {
                        //LUIGI: esegui salvataggio per valore parameter[0]

                        String specification = "";
                        specification = "update"; //quindi aggiorniamo il metadato

                        EmendamentoAction action = new EmendamentoAction();
                        //Recupero la "sessione" corrente a partire dall'id in sessione rest
                        EmendamentoSession currentEmeSession = getActiveEmeSession(emeSessionId);
                        action.setEmendamento(currentEmeSession);
                        action.setAction("UPDATE_METADATA");
                        action.setObjId(el);
                        action.setActionDt(new GregorianCalendar());
                        action.setSpecification(specification);
                        emeActionDAO.save(action);

                        ElementTemplate et = null;
                        MetadataTemplate template = null;
                        for (ElementTemplate et_ : el.getElementTemplates()) {
                            if (et_.getMetadataTemplate().getName().equals(templateName)) {
                                et = et_;
                            }
                        }
                        if (et == null) {
                            try {
                                if (user != null) {
                                    addTemplate(user, el, templateName);
                                } else {
                                    addTemplate(el, templateName);
                                }
                            } catch (RestException e) {
                                throw new RestException("Template " + templateName + " non associato all'elemnto", txManager);
                            }
                        }
                        if (et == null) throw new RestException("Template " + templateName + " non associato all'elemnto", txManager);
                        template = et.getMetadataTemplate();


                        MetadataField field = null;
                        for (MetadataField f : template.getFields()) {
                            if (f.getName().equals(fieldName)) field = f;
                        }

                        if (field == null) throw new RestException("FieldNotFound: " + template.getName() + "_" + fieldName, txManager);
                        AuditEmeMetadata amd = new AuditEmeMetadata(); //creo record di Audit
                        amd.setField(field);
                        amd.setModDt(new GregorianCalendar());
                        amd.setTemplate(template);
                        amd.setUsername(user);
                        amd.setAction("DM_UPDATE");
                        amd.setEmendamento(currentEmeSession);
                        amd.setEmeAction(action);
                        if (el.getAuditData() == null) {
                            el.setAuditData(new LinkedList<AuditMetadata>());
                        }
                        if (amd.getField().getType().equals(MetadataFieldType.ELEMENT_LINK)) {
                            try {
                                Element lel = this.getElement(Long.parseLong((String) parameter[0]));
                                amd.setVal(lel);
                            } catch (NumberFormatException ex) {
                                //it.cineca.siss.axmr3.log.Log.info(getClass(),"Valore "+parameter+" non numerico per campo "+amd.getField().getTemplate().getName()+"."+amd.getField().getName());
                                amd.setVal(null);
                            }

                        } else amd.setVal(parameter[0]);

                        for (AuditEmeValue val : amd.getValues()) {
                            val.setOld(false);
                            try {
                                aEmeMdValDAO.save(val);
                            } catch (AxmrGenericException e) {
                                throw new RestException(e.getMessage(), txManager);
                            }
                        }

                        try {
                            aEmeMdDAO.save(amd);
                        } catch (AxmrGenericException e) {
                            throw new RestException(e.getMessage(), txManager);
                        }
                    }
                } else if (parameter.length >1) {
                    //LUIGI: esegui salvataggio di tutti i parameter con ciclo
                        String specification = "";
                        specification = "update"; //quindi aggiorniamo il metadato

                        EmendamentoAction action = new EmendamentoAction();
                        //Recupero la "sessione" corrente a partire dall'id in sessione rest
                        EmendamentoSession currentEmeSession = getActiveEmeSession(emeSessionId);
                        action.setEmendamento(currentEmeSession);
                        action.setAction("UPDATE_METADATA");
                        action.setObjId(el);
                        action.setActionDt(new GregorianCalendar());
                        action.setSpecification(specification);
                        emeActionDAO.save(action);

                        ElementTemplate et = null;
                        MetadataTemplate template = null;
                        for (ElementTemplate et_ : el.getElementTemplates()) {
                            if (et_.getMetadataTemplate().getName().equals(templateName)) {
                                et = et_;
                            }
                        }
                        if (et == null) {
                            try {
                                if (user != null) {
                                    addTemplate(user, el, templateName);
                                } else {
                                    addTemplate(el, templateName);
                                }
                            } catch (RestException e) {
                                throw new RestException("Template " + templateName + " non associato all'elemnto", txManager);
                            }
                        }
                        if (et == null)
                            throw new RestException("Template " + templateName + " non associato all'elemnto", txManager);
                        template = et.getMetadataTemplate();


                        MetadataField field = null;
                        for (MetadataField f : template.getFields()) {
                            if (f.getName().equals(fieldName)) field = f;
                        }

                        if (field == null)
                            throw new RestException("FieldNotFound: " + template.getName() + "_" + fieldName, txManager);
                        AuditEmeMetadata amd = new AuditEmeMetadata(); //creo record di Audit
                        amd.setField(field);
                        amd.setModDt(new GregorianCalendar());
                        amd.setTemplate(template);
                        amd.setUsername(user);
                        amd.setAction("DM_UPDATE");
                        amd.setEmendamento(currentEmeSession);
                        amd.setEmeAction(action);
                        if (el.getAuditData() == null) {
                            el.setAuditData(new LinkedList<AuditMetadata>());
                        }

                    LinkedList<AuditEmeValue> auditVals = new LinkedList<AuditEmeValue>();

                    for (String parameterIt:parameter) {

                        if (amd.getField().getType().equals(MetadataFieldType.ELEMENT_LINK)) {
                            try {
                                Element lel = this.getElement(Long.parseLong((String) parameterIt));
                                AuditEmeValue aVal = new AuditEmeValue();
                                aVal.setOld(false);
                                aVal.setElement_link(lel);
                                auditVals.add(aVal);
                            } catch (NumberFormatException ex) {
                                //it.cineca.siss.axmr3.log.Log.info(getClass(),"Valore "+parameter+" non numerico per campo "+amd.getField().getTemplate().getName()+"."+amd.getField().getName());
                                amd.setVal(null);
                                log.error(ex.getMessage(),ex);  //To change body of catch statement use File | Settings | File Templates.
                            }

                        } else if (amd.getField().getType().equals(MetadataFieldType.DATE)) {
                            try {
                                DateFormat df = new SimpleDateFormat("dd/MM/yyyy");
                                Date parsed = null;
                                parsed = df.parse(parameterIt);
                                Calendar calValue = Calendar.getInstance();
                                calValue.setTime(parsed);
                                AuditEmeValue aVal = new AuditEmeValue();
                                aVal.setOld(false);
                                aVal.setDate(calValue);
                                auditVals.add(aVal);
                            } catch (java.text.ParseException ex) {
                                amd.setVal(null);
                                log.error(ex.getMessage(),ex);  //To change body of catch statement use File | Settings | File Templates.
                            }
                        } else if (amd.getField().getType().equals(MetadataFieldType.TEXTAREA) || amd.getField().getType().equals(MetadataFieldType.RICHTEXT)) {
                            //Long text
                            AuditEmeValue aVal = new AuditEmeValue();
                            aVal.setOld(false);
                            aVal.setLongTextValue(parameterIt);
                            auditVals.add(aVal);
                        } else {
                            if (parameterIt.contains("###")){
                                //Code/decode
                                String[] spl = parameterIt.split("###");
                                AuditEmeValue aVal = new AuditEmeValue();
                                aVal.setOld(false);
                                aVal.setCode(spl[0]);
                                aVal.setDecode(spl[1]);
                                auditVals.add(aVal);
                            }else{
                                //Value normale
                                AuditEmeValue aVal = new AuditEmeValue();
                                aVal.setOld(false);
                                aVal.setTextValue(parameterIt);
                                auditVals.add(aVal);
                            }
                        }

                    }
                    amd.setValues(auditVals);

                        for (AuditEmeValue val : amd.getValues()) {
                            val.setOld(false);
                            try {
                                aEmeMdValDAO.save(val);
                            } catch (AxmrGenericException e) {
                                throw new RestException(e.getMessage(), txManager);
                            }
                        }

                        try {
                            aEmeMdDAO.save(amd);
                        } catch (AxmrGenericException e) {
                            throw new RestException(e.getMessage(), txManager);
                        }

                }


            }
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        } catch (org.hibernate.HibernateException ex) {
            log.error(ex.getMessage(),ex);
        }
    }



    private void registerAudit(IUser user, Element el, Object parameter, ElementMetadata oldMetaData, String action) throws AxmrGenericException {
        registerAudit(user.getUsername(), el, parameter, oldMetaData, action);
    }


    private void registerAudit(String user, Element el, Object parameter, ElementMetadata oldMetaData, String action) throws AxmrGenericException {
        boolean sameValue = hasChanged(parameter, oldMetaData, action);
        if (oldMetaData.getVals() == null || oldMetaData.getVals().size() == 0) {
            action = "create";
        }


        if (!sameValue) {
            AuditMetadata amd = new AuditMetadata();
            if (user == null) amd.setUsername("WorkFlow");
            else amd.setUsername(user);
            amd.setAction(action);
            amd.setModDt(new GregorianCalendar());
            amd.setField(oldMetaData.getField());
            amd.setTemplate(oldMetaData.getTemplate());
            if (amd.getField().getType().equals(MetadataFieldType.ELEMENT_LINK)) {
                try {
                    Element lel = this.getElement(Long.parseLong((String) parameter));
                    amd.setVal(lel);
                } catch (NumberFormatException ex) {
                    //it.cineca.siss.axmr3.log.Log.info(getClass(),"Valore "+parameter+" non numerico per campo "+amd.getField().getTemplate().getName()+"."+amd.getField().getName());
                    amd.setVal(null);
                }

            } else amd.setVal(parameter);
            for (AuditValue val : amd.getValues()) {
                val.setOld(false);
                try {
                    aMdValDAO.save(val);
                } catch (AxmrGenericException e) {
                    throw new RestException(e.getMessage(), txManager);
                }
            }

            if (!action.equals("create")) {
                for (ElementMetadataValue val : oldMetaData.getValues()) {
                    AuditValue adv = new AuditValue();
                    adv.setCode(val.getCode());
                    adv.setDate(val.getDate());
                    adv.setDecode(val.getDecode());
                    adv.setElement_link(val.getElement_link());
                    adv.setLongTextValue(val.getLongTextValue());
                    adv.setTextValue(val.getTextValue());
                    adv.setOld(true);
                    try {
                        aMdValDAO.saveOrUpdate(adv);
                    } catch (AxmrGenericException e) {
                        throw new RestException(e.getMessage(), txManager);
                    }
                    amd.getValues().add(adv);
                }

            }
            try {
                aMdDAO.save(amd);
            } catch (AxmrGenericException e) {
                throw new RestException(e.getMessage(), txManager);
            }
            if (el.getAuditData() == null) el.setAuditData(new LinkedList<AuditMetadata>());
            el.getAuditData().add(amd);
            try {
                docDAO.saveOrUpdate(el);
            } catch (AxmrGenericException e) {
                throw new RestException(e.getMessage(), txManager);
            }
            addElidToBeUpdeated(el.getId(),true);
            commitTXSessionAndKeepAlive();
        }

    }

    private void registerAuditArray(String user, Element el, Object[] parameters, ElementMetadata oldMetaData, String action) throws AxmrGenericException {
        boolean sameValue = hasChangedArray((String[]) parameters, oldMetaData, action);
        if (oldMetaData.getVals() == null || oldMetaData.getVals().size() == 0) {
            action = "create";
        }


        if (!sameValue) {
            AuditMetadata amd = new AuditMetadata();
            if (user == null) amd.setUsername("WorkFlow");
            else amd.setUsername(user);
            amd.setAction(action);
            amd.setModDt(new GregorianCalendar());
            amd.setField(oldMetaData.getField());
            amd.setTemplate(oldMetaData.getTemplate());
            for (Object parameter : parameters) {
                if (amd.getField().getType().equals(MetadataFieldType.ELEMENT_LINK)) {
                    try {
                        Element lel = this.getElement(Long.parseLong((String) parameter));
                        amd.setVal(lel);
                    } catch (NumberFormatException ex) {
                        //it.cineca.siss.axmr3.log.Log.info(getClass(),"Valore "+parameter+" non numerico per campo "+amd.getField().getTemplate().getName()+"."+amd.getField().getName());
                        amd.setVal(null);
                    }

                } else amd.setVal(parameter);
            }
            for (AuditValue val : amd.getValues()) {
                val.setOld(false);
                try {
                    aMdValDAO.save(val);
                } catch (AxmrGenericException e) {
                    throw new RestException(e.getMessage(), txManager);
                }
            }

            if (!action.equals("create")) {
                for (ElementMetadataValue val : oldMetaData.getValues()) {
                    AuditValue adv = new AuditValue();
                    adv.setCode(val.getCode());
                    adv.setDate(val.getDate());
                    adv.setDecode(val.getDecode());
                    adv.setElement_link(val.getElement_link());
                    adv.setLongTextValue(val.getLongTextValue());
                    adv.setTextValue(val.getTextValue());
                    adv.setOld(true);
                    try {
                        aMdValDAO.saveOrUpdate(adv);
                    } catch (AxmrGenericException e) {
                        throw new RestException(e.getMessage(), txManager);
                    }
                    amd.getValues().add(adv);
                }

            }
            try {
                aMdDAO.save(amd);
            } catch (AxmrGenericException e) {
                throw new RestException(e.getMessage(), txManager);
            }
            if (el.getAuditData() == null) el.setAuditData(new LinkedList<AuditMetadata>());
            el.getAuditData().add(amd);
            try {
                docDAO.saveOrUpdate(el);
            } catch (AxmrGenericException e) {
                throw new RestException(e.getMessage(), txManager);
            }
            addElidToBeUpdeated(el.getId(),true);
            commitTXSessionAndKeepAlive();
        }

    }

    private boolean hasChangedArray(String[] parameter, ElementMetadata oldMetaData, String action) {
        boolean sameValue = false;
        if (!action.equals("create") && oldMetaData.getVals() != null && oldMetaData.getVals().size() > 0) {
            if (parameter != null && parameter.length > 0) {
                if (parameter.length != oldMetaData.getVals().size()) return true;
                for (int i = 0; i < oldMetaData.getVals().size(); i++) {
                    boolean found = false;
                    for (int c = 0; c < parameter.length; c++) {
                        if (oldMetaData.getField().getType().equals(MetadataFieldType.ELEMENT_LINK)) {
                            if (((Element) oldMetaData.getVals().get(i)).getId().equals(Long.parseLong(parameter[c])))
                                found = true;
                        } else {
                            if (parameter[c].equals(oldMetaData.getVals().get(i))) found = true;
                        }
                    }
                    if (!found) return true;
                }
                return false;
            }
        } else {
            action = "create";
            if (parameter == null || parameter.length == 0) {
                sameValue = true;
            }
        }
        return sameValue;
    }

    private boolean hasChanged(Object parameter, ElementMetadata oldMetaData, String action) {
        boolean sameValue = false;
        if (!action.equals("create") && oldMetaData.getVals() != null && oldMetaData.getVals().size() > 0) {
            if (parameter != null && !((String) parameter).isEmpty()) {
                if (oldMetaData.getField().getType().equals(MetadataFieldType.ELEMENT_LINK)) {
                    sameValue = ((Element) oldMetaData.getVals().get(0)).getId().equals(Long.parseLong((String) parameter));
                } else {
                    sameValue = parameter.equals(oldMetaData.getVals().get(0));
                }
            }
        } else {
            action = "create";
            if (parameter == null || ((String) parameter).isEmpty()) {
                sameValue = true;
            }
        }
        return sameValue;
    }

    public void elementCheckOut(Element el, IUser user) throws RestException {
        Policy myElPolicy = el.getUserPolicy(user);
        if (el.getType().isCheckOutEnabled() && myElPolicy.isCanUpdate() && !el.isLocked()) {
            el.setLocked(true);
            el.setLockedFromUser(user.getUsername());
            el.setLockDt(new GregorianCalendar());
            try {
                docDAO.saveOrUpdate(el);
            } catch (AxmrGenericException e) {
                throw new RestException(e.getMessage(), txManager);
            }
            commitTXSessionAndKeepAlive();
            registerEvent(user, el, "CheckOut");
        } else {
            throw new RestException("NOTPERMITTED", txManager);
        }
    }

    public void elementCheckIn(Element el, IUser user) throws RestException {
        Policy myElPolicy = el.getUserPolicy(user);
        if (
                el.getType().isCheckOutEnabled() && el.isLocked() &&
                        (
                                (
                                        myElPolicy.isCanUpdate() && el.getLockedFromUser().equals(user.getUsername())
                                )
                                        ||
                                        (
                                                myElPolicy.isCanRemoveCheckOut()
                                        )
                        )

        ) {
            el.setLocked(false);
            el.setLockedFromUser(null);
            el.setLockDt(null);
            try {
                docDAO.saveOrUpdate(el);
            } catch (AxmrGenericException e) {
                throw new RestException(e.getMessage(), txManager);
            }
            commitTXSessionAndKeepAlive();
            registerEvent(user, el, "CheckIn");
        } else {
            throw new RestException("NOTPERMITTED", txManager);
        }
    }

    public ElementTemplate addTemplate(Element el, String templateName) throws AxmrGenericException {
        for (ElementTemplate et : el.getElementTemplates()) {
            if (et.getMetadataTemplate().getName().equals(templateName) && !et.isEnabled()) {
                et.setEnabled(true);
                elTplDAO.save(et);
                return et;
            }
        }
        return null;
    }

    public ElementTemplate addTemplate(Element el, MetadataTemplate template) throws AxmrGenericException {
        for (ElementTemplate et : el.getElementTemplates()) {
            if (et.getMetadataTemplate().equals(template) && !et.isEnabled()) {
                et.setEnabled(true);
                elTplDAO.save(et);
                return et;
            }
        }
        return null;
    }

    public void addTemplate(IUser user, Element el, String templateName) throws AxmrGenericException {
        Policy userPolicy = el.getUserPolicy(user);
        if ((userPolicy.isCanEnableTemplate() && !el.isLocked()) || (userPolicy.isCanEnableTemplate() && el.isLocked() && el.getLockedFromUser() == user.getUsername())) {
            for (ElementTemplate et : el.getElementTemplates()) {
                if (et.getMetadataTemplate().getName().equals(templateName) && !et.isEnabled()) {
                    if (et.getUserPolicy(user, el).isCanCreate()) {
                        et.setEnabled(true);
                        elTplDAO.save(et);
                    } else {
                        throw new AxmrGenericException("L'utente non può creare template " + templateName);
                    }
                }
            }
        } else {
            throw new AxmrGenericException("L'utente non può aggiungere template all'elemento " + el.getId());
        }
    }

    private ElementTemplate addTemplate(String user, Element el, String templateName) throws AxmrGenericException {
        for (ElementTemplate et : el.getElementTemplates()) {
            if (et.getMetadataTemplate().getName().equals(templateName) && !et.isEnabled()) {
                et.setEnabled(true);
                elTplDAO.save(et);
                return et;
            }
        }
        return null;
    }

    public ElementTemplate addTemplate(IUser user, Element el, MetadataTemplate template) throws AxmrGenericException {
        Policy userPolicy = el.getUserPolicy(user);
        if ((userPolicy.isCanEnableTemplate() && !el.isLocked()) || (userPolicy.isCanEnableTemplate() && el.isLocked() && el.getLockedFromUser() == user.getUsername())) {
            for (ElementTemplate et : el.getElementTemplates()) {
                if (et.getMetadataTemplate().equals(template) && !et.isEnabled()) {
                    if (et.getUserPolicy(user, el).isCanCreate()) {
                        et.setEnabled(true);
                        elTplDAO.save(et);
                        return et;
                    } else {
                        throw new AxmrGenericException("L'utente non può creare template " + template.getName());
                    }
                }
            }
        } else {
            throw new AxmrGenericException("L'utente non può aggiungere template all'elemento " + el.getId());
        }
        return null;
    }

    public void addTemplate(IUser user, Element el, Long templateId) throws RestException {
        try {
            Policy userPolicy = el.getUserPolicy(user);
            MetadataTemplate template = null;
            for (ElementTypeAssociatedTemplate t : el.getType().getAssociatedTemplates()) {
                if (t.getMetadataTemplate().getId().equals(templateId)) template = t.getMetadataTemplate();
            }
            if (template != null) {
                addTemplate(user, el, template);
            } else {
                throw new RestException("Template non disponibile per l'elemento " + el.getId(), txManager);
            }
        } catch (AxmrGenericException ex) {
            throw new RestException(ex.getMessage(), txManager);
        }

    }

    public List<File> getNotIndexed() {
        Criteria c = fileSpecDAO.getCriteria();
        c.add(Restrictions.eq("indexable", true))
                .add(Restrictions.eq("indexed", false));
        return c.list();
    }

    public List<AuditFile> getAuditNotIndexed() {
        Criteria c = aFileDAO.getCriteria();
        c.add(Restrictions.eq("indexable", true))
                .add(Restrictions.eq("indexed", false));
        return c.list();
    }


    public List<Event> getEvents(IUser user, Element el) {
        Criteria c = evDAO.getCriteria();
        if (el != null) {
            c.add(Restrictions.eq("element", el));
        } else {
            List<Element> els = docDAO.getCriteriaList(getBrowsableElementsCriteria(user));
            if (els == null || els.size() == 0) return null;
            c.add(Restrictions.in("element", els));
        }
        //c.setMaxResults(10);
        c.addOrder(Order.desc("evDt"));
        return c.list();
    }

    public void deleteElement(IUser user, Element el) throws RestException {
        try {
            Policy userPolicy = el.getUserPolicy(user);
            if (userPolicy.isCanDelete()) {
                el.setDeleted(true);
                el.setDeletedBy(user.getUsername());
                el.setDeleteDt(new GregorianCalendar());
                el.setLastUpdateDt(new GregorianCalendar());
                registerEvent(user, el, "delete");
                for (Element child : el.getChildren()) {
                    deleteElement(user, child);
                }
                docDAO.saveOrUpdate(el);
                if (el.getParent() != null) {
                    recurseUpdateDt(el.getParent(), user, new GregorianCalendar());
                }
                addElidToBeUpdeated(el.getId(),true);
                commitTXSessionAndKeepAlive();
                for (ElementTypeAssociatedWorkflow awf : el.getType().getAssociatedWorkflows()) {
                    if (awf.isStartOnDelete()) startProcess(user, el, awf.getProcessKey());
                }
            }
        } catch (AxmrGenericException e) {
            throw new RestException("ERROR", txManager);
        }
    }


    public void deleteElement(Element el) throws RestException {
        try {

            el.setDeleted(true);
            for (Element child : el.getChildren()) {
                deleteElement(child);
            }
            docDAO.saveOrUpdate(el);
            if (el.getParent() != null) {
                recurseUpdateDt(el.getParent(), "SYSTEM", new GregorianCalendar());
            }
            addElidToBeUpdeated(el.getId(),true);
            commitTXSessionAndKeepAlive();


        } catch (AxmrGenericException e) {
            throw new RestException("ERROR", txManager);
        }
    }


    public void addTemplateAction(Long elId, String templateName) throws AxmrGenericException {
        Element el = this.getElement(elId);
        Criteria c = templateDAO.getCriteria();
        c.add(Restrictions.eq("name", templateName));
        MetadataTemplate template = (MetadataTemplate) c.uniqueResult();
        boolean present = false;
        for (MetadataTemplate t : el.getTemplates()) {
            if (t.getName().equals(templateName)) present = true;
        }
        if (!present) {
            addTemplate(el, template);
        }
    }

    public Element sync(Element el) {
        docDAO = new BaseDao<Element>(txManager, "doc", Element.class);
        return getElement(el.getId());
    }

    public void addMetadataValueActions(Long elId, String templateName, String fieldName, Object value) throws AxmrGenericException {
        addMetadataValueActions("SYSTEM", elId, templateName, fieldName, value);
    }

    public void addMetadataValueActions(String userid, Long elId, String templateName, String fieldName, Object value) throws AxmrGenericException {
        Element el = this.getElement(elId);
        //it.cineca.siss.axmr3.log.Log.info(getClass(),"Campo in cui inserire: "+templateName+"."+fieldName);
        //it.cineca.siss.axmr3.log.Log.info(getClass(),"Valore da inserire:"+value);
        MetadataTemplate template = null;
        for (MetadataTemplate t : el.getTemplates()) {
            if (t.getName().equals(templateName)) template = t;
        }
        if (template == null) {
            addTemplate(el, templateName);
        }
        ElementMetadata d = null;
        if (value == null) {
            value = "";
        }
        setMetadataValue(userid, el, templateName, fieldName, value.toString(), true, "PROCESS");
    }

    public static <T> T clone(Class<T> clazz, T dtls) {
        T clonedObject = (T) SerializationHelper.clone((Serializable) dtls);
        return clonedObject;
    }

    public List<CalendarEvent> getCalendarEvents(IUser user, Calendar start, Calendar end) {
        Criteria ct = templateDAO.getCriteria();
        ct.add(Restrictions.eq("calendarized", true));
        List<MetadataTemplate> cts = ct.list();
        if (cts == null || cts.size() == 0) return null;
        List<MetadataField> fields = new LinkedList<MetadataField>();
        for (MetadataTemplate t : cts) {
            fields.add(t.getStartDateField());
            if (t.getEndDateField() != null) fields.add(t.getEndDateField());
        }
        DetachedCriteria baseSearch = getBrowsableElementsCriteria(user);
        baseSearch.createAlias("data", "data")
                .createAlias("data.values", "dataValues");
        baseSearch.add(Restrictions.and(
                Restrictions.between("dataValues.date", start, end),
                Restrictions.in("data.field", fields)
        ));
        List<Element> els = docDAO.getCriteriaList(baseSearch);
        List<CalendarEvent> evs = new LinkedList<CalendarEvent>();
        for (Element el : els) {
            for (MetadataTemplate t : el.getTemplates()) {
                if (t.isCalendarized()) {
                    Calendar elementStartDate = (Calendar) getData(el, t.getStartDateField());
                    Calendar elementEndDate = null;
                    if (t.getEndDateField() != null) elementEndDate = (Calendar) getData(el, t.getEndDateField());
                    if (
                            (elementStartDate.before(end) && elementStartDate.after(start))
                                    || (elementEndDate != null && elementEndDate.before(end) && elementEndDate.after(start))
                    ) {
                        CalendarEvent c = new CalendarEvent();
                        c.setTitle(getElementTitle(el));
                        c.setStartDate(elementStartDate);
                        c.setEndDate(elementEndDate);
                        if (t.getStartDateField().getType().equals(MetadataFieldType.DATE)) c.setAllDay(true);
                        else c.setAllDay(false);
                        c.setId(t.getId());
                        c.setBackgroundColor("#" + t.getCalendarColor());
                        c.setUrl("documents/detail/" + el.getId());
                        evs.add(c);
                    }

                }
            }

        }
        return evs;
    }

    public List<CalendarEvent> getCalendarEventsByElement(IUser user, Element el, Calendar start, Calendar end) {
        List<CalendarEvent> evs = new LinkedList<CalendarEvent>();
        for (MetadataTemplate t : el.getTemplates()) {
            if (t.isCalendarized()) {
                Calendar elementStartDate = (Calendar) getData(el, t.getStartDateField());
                Calendar elementEndDate = null;
                if (t.getEndDateField() != null) elementEndDate = (Calendar) getData(el, t.getEndDateField());
                if (
                        (elementStartDate.before(end) && elementStartDate.after(start))
                                || (elementEndDate != null && elementEndDate.before(end) && elementEndDate.after(start))
                ) {
                    CalendarEvent c = new CalendarEvent();
                    c.setTitle(getElementTitle(el));
                    c.setStartDate(elementStartDate);
                    c.setEndDate(elementEndDate);
                    if (t.getStartDateField().getType().equals(MetadataFieldType.DATE)) c.setAllDay(true);
                    else c.setAllDay(false);
                    c.setId(t.getId());
                    c.setBackgroundColor("#" + t.getCalendarColor());
                    c.setUrl("documents/detail/" + el.getId());
                    evs.add(c);
                }

            }
        }

        return evs;
    }

    public List<CalendarEntity> getAvailablesCalendars(IUser user) {
        Criteria c = calDAO.getCriteria();
        return c.list();
    }

    public boolean isAvailablesCalendars(IUser user) {
        Criteria c = calDAO.getCriteria();
        if (c.list().size() > 0) return true;
        else return false;
    }

    public Object getData(Element el, MetadataField f) {
        for (ElementMetadata d : el.getData()) {
            if (d.getField().getId().equals(f.getId())) return d.getVals().get(0);
        }
        return null;
    }

    public String getElementTitle(Element el) {
        for (ElementMetadata d : el.getData()) {
            if (d.getField().getId().equals(el.getType().getTitleField().getId())) return (String) d.getVals().get(0);
        }
        return "";
    }

    public List<Element> getElementsByType(IUser user, Long typeId) {
        DetachedCriteria baseSearch = getViewableElementsCriteria(user);
        baseSearch.createAlias("type", "type")
                .add(Restrictions.eq("type.id", typeId));
        return docDAO.getCriteriaList(baseSearch);

    }

    public List<Element> getElementsByType(String typeId) {
        DetachedCriteria baseSearch = getAllElementsCriteria();
        baseSearch.createAlias("type", "type")
                .add(Restrictions.eq("type.typeId", typeId));
        return docDAO.getCriteriaList(baseSearch);

    }

    public List<Element> getElementsByTypes(IUser user, List<String> typeIds) {
        DetachedCriteria baseSearch = getViewableElementsCriteria(user);
        baseSearch.createAlias("type", "type")
                .add(Restrictions.in("type.typeId", typeIds));
        return docDAO.getCriteriaList(baseSearch);

    }

    public List<Element> getLinkableElements(IUser user, Long idField, String term, Element parentEl) {

        MetadataField f = mdFieldDAO.getById(idField);
        String[] ids = f.getTypefilters().split(",");
        List<Long> lids = new LinkedList<Long>();
        for (String id : ids) {
            lids.add(Long.parseLong(id));
        }
        DetachedCriteria baseSearch = getViewableElementsCriteria(user);
        baseSearch.createAlias("type", "type")
                .add(Restrictions.in("type.id", lids));

        baseSearch.createAlias("data", "data")
                .createAlias("data.values", "dataValues");
        baseSearch.add(Restrictions.or(
                Restrictions.like("dataValues.textValue", "%" + term + "%").ignoreCase(),
                Restrictions.like("dataValues.longTextValue", "%" + term + "%").ignoreCase()));
        baseSearch.add(Restrictions.eqProperty("type.titleField", "data.field"));
        if (parentEl != null) baseSearch.add(Restrictions.eq("parent", parentEl));
        return docDAO.getCriteriaList(baseSearch);

    }

    public Long bulkFileUpload(IUser user, byte[] file, String fileName) throws RestException {
        try {
            BulkUploadFile f = new BulkUploadFile();

            f.setFileName(fileName);
            f.setContent(file);
            f.setUploadUser(user.getUsername());
            f.setUploadDt(new GregorianCalendar());
            bfDAO.save(f);
            commitTXSessionAndKeepAlive();
            return f.getId();
        } catch (AxmrGenericException ex) {
            throw new RestException(ex.getMessage(), txManager);
        }

    }

    public HashMap<String, List<String>> getBulkFileColumns(Long idBulk) throws RestException {
        try {
            HashMap<String, List<String>> ret = new HashMap<String, List<String>>();
            BulkUploadFile bf = bfDAO.getById(idBulk);
            Workbook w = Workbook.getWorkbook(new ByteArrayInputStream(bf.getContent()));
            for (Sheet sheet : w.getSheets()) {
                List<String> cols = new LinkedList<String>();
                for (int j = 0; j < sheet.getColumns(); j++) {
                    Cell cell = sheet.getCell(j, 0);
                    cols.add(cell.getContents());
                }
                ret.put(sheet.getName(), cols);
            }
            return ret;
        } catch (Exception ex) {
            throw new RestException(ex.getMessage(), txManager);
        }
    }

    public void bulkLoad(IUser user, Long parentId, Long destId, Long bulkId, String sheetName, HashMap<Integer, Long> data) throws BiffException, IOException, RestException {
        ElementType type = docTypeDAO.getById(destId);
        HashMap<Integer, String> mappingField = new HashMap<Integer, String>();
        Iterator<Integer> dataIt = data.keySet().iterator();
        while (dataIt.hasNext()) {
            int idxCol = dataIt.next();
            for (MetadataTemplate t : type.getEnabledTemplates()) {
                for (MetadataField f : t.getFields()) {
                    if (f.getId().equals(data.get(idxCol))) {
                        mappingField.put(idxCol, t.getName() + "_" + f.getName());
                    }
                }
            }
        }
        BulkUploadFile bf = bfDAO.getById(bulkId);
        Workbook w = Workbook.getWorkbook(new ByteArrayInputStream(bf.getContent()));
        Sheet sheet = null;
        for (Sheet s : w.getSheets()) {
            if (s.getName().equals(sheetName)) sheet = s;
        }

        for (int j = 1; sheet != null && j < sheet.getRows(); j++) {
            HashMap<String, String> rowData = new HashMap<String, String>();
            for (int i = 0; i < sheet.getColumns(); i++) {
                if (mappingField.containsKey(i)) {
                    rowData.put(mappingField.get(i), sheet.getCell(i, j).getContents());
                }
            }
            saveElement(user, type, rowData, null, null, null, "", "", "", "", this.getElement(parentId));
        }
    }

    public List<Element> getChilds(IUser user, Element el, int page, int limit) {
        int rowPerPage = limit;
        int start = (page - 1) * rowPerPage;
        int total = 0;
        DetachedCriteria c = getBrowsableElementsCriteria(user);
        c.add(Restrictions.eq("parent", el));
        c.add(Restrictions.eq("deleted", false));
        //c.setMaxResults(rowPerPage);
        c.setProjection(Projections.countDistinct("id"));
        total = ((Long) docDAO.getCriteriaUniqueResult(c)).intValue();
        return docDAO.getFixedResultSize(c, start, rowPerPage, total);
    }

    public Long getNumChilds(IUser user, Element el) {
        DetachedCriteria c = getBrowsableElementsCriteria(user);
        c.add(Restrictions.eq("parent", el));
        c.setProjection(Projections.rowCount());
        return (Long) docDAO.getCriteriaUniqueResult(c);
    }

    public Long getNumRootChilds(IUser user) {
        DetachedCriteria c = getBrowsableElementsCriteria(user);
        c.add(Restrictions.isNull("parent"));
        c.setProjection(Projections.rowCount());
        return (Long) docDAO.getCriteriaUniqueResult(c);
    }

    public Long getNumRootChildsByType(IUser user, Long typeId) {
        DetachedCriteria c = getBrowsableElementsCriteria(user);
        c.add(Restrictions.isNull("parent"));
        c.add(Restrictions.eq("type", docTypeDAO.getById(typeId)));
        c.setProjection(Projections.rowCount());
        return (Long) docDAO.getCriteriaUniqueResult(c);
    }

    public List<Element> getRootElementsLimit(IUser user, int page, int limit, String orderBy, String orderType) {
        int rowPerPage = limit;
        int start = (page - 1) * rowPerPage;
        int total = 0;
        DetachedCriteria c = getBrowsableElementsCriteria(user);
        //TODO:verificare le prestazioni con il commento dell riga seguente
        c.add(Restrictions.isNull("parent"));
        //c.setMaxResults(rowPerPage);
        //it.cineca.siss.axmr3.log.Log.info(getClass(),"\n\n\n\n\nOrders: "+orderBy+" - "+orderType+"\n\n\n\n\n\n");
        c.setProjection(Projections.countDistinct("id"));
        total = ((Long) docDAO.getCriteriaUniqueResult(c)).intValue();

        if (!orderType.isEmpty() && !orderBy.isEmpty()) {
            if (orderBy.equals("createDt")) {
                if (orderType.equals("asc")) c.addOrder(Order.asc("creationDt"));
                if (orderType.equals("desc")) c.addOrder(Order.desc("creationDt"));
            } else if (orderBy.equals("updateDt")) {
                if (orderType.equals("asc")) c.addOrder(Order.asc("lastUpdateDt"));
                if (orderType.equals("desc")) c.addOrder(Order.desc("lastUpdateDt"));
            } else {

            }
        }
        return docDAO.getFixedResultSize(c, start, rowPerPage, total);
    }

    public List<Element> getRootElementsLimitById(IUser user, Long typeId, int page, int limit, String orderBy, String orderType) {
        int rowPerPage = limit;
        int start = (page - 1) * rowPerPage;
        int total = 0;
        DetachedCriteria c = getBrowsableElementsCriteria(user);
        c.add(Restrictions.isNull("parent"));
        ElementType type = docTypeDAO.getById(typeId);
        c.add(Restrictions.eq("type", type));
        //c.setMaxResults(rowPerPage);
        c.setProjection(Projections.countDistinct("id"));
        total = ((Long) docDAO.getCriteriaUniqueResult(c)).intValue();
        //it.cineca.siss.axmr3.log.Log.info(getClass(),"\n\n\n\n\nOrders: " + orderBy + " - " + orderType + "\n\n\n\n\n\n");
        if (!orderType.isEmpty() && !orderBy.isEmpty()) {
            if (orderBy.equals("createDt")) {
                if (orderType.equals("asc")) c.addOrder(Order.asc("creationDt"));
                if (orderType.equals("desc")) c.addOrder(Order.desc("creationDt"));
            } else if (orderBy.equals("updateDt")) {
                if (orderType.equals("asc")) c.addOrder(Order.asc("lastUpdateDt"));
                if (orderType.equals("desc")) c.addOrder(Order.desc("lastUpdateDt"));
            } else {

            }
        } else {
            if (type.isSortable()) c.addOrder(Order.asc("position"));
            c.addOrder(Order.desc("creationDt"));
        }
        return docDAO.getFixedResultSize(c, start, rowPerPage, total);
    }

    public List<Element> getRootElementsLimitByTypeId(IUser user, String typeId, int page, int limit, String orderBy, String orderType) {
        return getRootElementsLimitByTypeId(user, typeId, page, limit, orderBy, orderType, null);
    }

    public List<Element> getRootElementsLimitByTypeId(IUser user, String typeId, int page, int limit, String orderBy, String orderType, JqGridJSON result) {
        int start = (page - 1) * limit;
        int total = 0;
        Long singleResult = new Long(0);
        List<Element> list;
        it.cineca.siss.axmr3.log.Log.info(getClass(), "getRootElementsLimitByTypeId rowPerPage: " + String.valueOf(limit) + " start: " + String.valueOf(start));
        DetachedCriteria c = getBrowsableElementsCriteria(user);
        c.createAlias("type", "type")
                .add(Restrictions.isNull("parent"))
                .add(Restrictions.eq("type.typeId", typeId));


        //c.setMaxResults(rowPerPage);
        c.setProjection(Projections.countDistinct("id"));
        singleResult = (Long) docDAO.getCriteriaUniqueResult(c);
        if (singleResult != null) {
            total = singleResult.intValue();
        }
        //it.cineca.siss.axmr3.log.Log.info(getClass(),"\n\n\n\n\nOrders: " + orderBy + " - " + orderType + "\n\n\n\n\n\n");
        if (!orderType.isEmpty() && !orderBy.isEmpty()) {
            if (orderBy.equals("createDt")) {
                if (orderType.equals("asc")) c.addOrder(Order.asc("creationDt"));
                if (orderType.equals("desc")) c.addOrder(Order.desc("creationDt"));
            } else if (orderBy.equals("updateDt")) {
                if (orderType.equals("asc")) c.addOrder(Order.asc("lastUpdateDt"));
                if (orderType.equals("desc")) c.addOrder(Order.desc("lastUpdateDt"));
            } else {

            }
        } else {
            c.addOrder(Order.desc("creationDt"));
        }
        it.cineca.siss.axmr3.log.Log.info(getClass(), "getRootElementsLimitById row start: " + String.valueOf(start));
        list = docDAO.getFixedResultSize(c, start, limit, total);
        if (result != null) {
            result.setPage(page);
            result.setRows(limit);
            result.setTotal(total);
        }
        return list;
    }


    public Element budgetClone(String user, Long fromId, HashMap<String, Object> params, HashMap<String, String> metadata) throws Exception {

        Element el = defaultClone(user, fromId, null, params, metadata);

        Element orig = getElement(fromId);
        String origType = orig.getType().getTypeId();
        List<Element> all = orig.getParent().getChildrenByType(origType);
        Collection<String> gruppi = orig.getAuthorities();
        Collection<String> users = orig.getAuthorities();

        for (Element currEl : all) {

            if (currEl.getId() < el.getId()) {
                gruppi = currEl.getAuthorities();
                users = currEl.getUsers();
                if (origType.equals("Budget")) {
                    for (String currAuthority : gruppi) {
                        if (!currAuthority.equals("CTC") && !currAuthority.equals("PI"))
                            changePermissionToGroup(currEl, "V,B", "budget_UO", currAuthority);
                    }
                    for (String currUser : users) {
                        changePermissionToUser(currEl.getId().toString(), "V,B", "budget_PI_RO", currUser);
                    }
                    changePermissionToGroup(currEl, "V,B", "budget_CTC_close", "CTC");
                    changePermissionToGroup(currEl, "", "", "PI");
                } else if (origType.equals("BudgetBracci")) {
                    for (String currAuthority : gruppi) {
                        if (!currAuthority.equals("CTC") && !currAuthority.equals("PI"))
                            changePermissionToGroup(currEl, "V,B", "B_budget_UO", currAuthority);
                    }
                    for (String currUser : users) {
                        changePermissionToUser(currEl.getId().toString(), "V,B", "B_budget_PI_RO", currUser);
                    }
                    changePermissionToGroup(currEl, "V,B", "B_budget_CTC_close", "CTC");
                    changePermissionToGroup(currEl, "", "", "PI");
                    try {
                        for (Element currSingoloBudget : currEl.getChildrenByType("FolderSingoloBraccio").get(0).getChildren()) {
                            for (String currAuthority : gruppi) {
                                if (!currAuthority.equals("CTC") && !currAuthority.equals("PI"))
                                    changePermissionToGroup(currSingoloBudget, "V,B", "SB_budget_UO", currAuthority);
                            }
                            for (String currUser : users) {
                                changePermissionToUser(currSingoloBudget.getId().toString(), "V,B", "SB_budget_PI_RO", currUser);
                            }
                            changePermissionToGroup(currSingoloBudget, "V,B", "SB_budget_CTC_close", "CTC");
                            changePermissionToGroup(currSingoloBudget, "", "", "PI");
                        }
                    } catch (Exception ex) {

                    }
                } else if (origType.equals("BudgetSingoloBraccio")) {
                    /*for (String currAuthority : gruppi) {
                        if (!currAuthority.equals("CTC") && !currAuthority.equals("PI"))
                            changePermissionToGroup(currEl, "V,B", "SB_budget_UO", currAuthority);
                    }
                    for (String currUser : users) {
                        changePermissionToUser(currEl.getId().toString(), "V,B", "SB_budget_PI_RO", currUser);
                    }
                    changePermissionToGroup(currEl, "V,B", "SB_budget_CTC_close", "CTC");
                    changePermissionToGroup(currEl, "", "", "PI");*/
                } else {
                    for (String currAuthority : gruppi) {
                        changePermissionToGroup(currEl, "V,B", "", currAuthority);
                    }
                }
            }

        }

        updateElementMetaData(user, el, metadata, "CREATE");
        HashMap<String, String> clonaFinito = new HashMap<String, String>();//CRPMS-441
        clonaFinito.put("Budget_ClonazioneInCorso", ""); //CRPMS-441
        updateElementMetaData(user, el, clonaFinito, "UPDATE");//CRPMS-441
        return el;
    }

    public Element budgetCloneOtherCenter(String user, Long fromId, Long toId, HashMap<String, Object> params, HashMap<String, String> metadata, boolean closeOrig) throws Exception {

        Element el = defaultClone(user, fromId, toId, params, metadata);

        Element orig = getElement(fromId);
        String origType = orig.getType().getTypeId();
        List<Element> all = orig.getParent().getChildrenByType(origType);
        Collection<String> gruppi = orig.getAuthorities();
        Collection<String> users = orig.getAuthorities();
        if (closeOrig) {
            for (Element currEl : all) {

                if (currEl.getId() < el.getId()) {
                    gruppi = currEl.getAuthorities();
                    users = currEl.getUsers();
                    if (origType.equals("Budget")) {
                        for (String currAuthority : gruppi) {
                            if (!currAuthority.equals("CTC") && !currAuthority.equals("PI"))
                                changePermissionToGroup(currEl, "V,B", "budget_UO", currAuthority);
                        }
                        for (String currUser : users) {
                            changePermissionToUser(currEl.getId().toString(), "V,B", "budget_PI_RO", currUser);
                        }
                        changePermissionToGroup(currEl, "V,B", "budget_CTC_close", "CTC");
                        changePermissionToGroup(currEl, "", "", "PI");
                    } else if (origType.equals("BudgetBracci")) {
                        for (String currAuthority : gruppi) {
                            if (!currAuthority.equals("CTC") && !currAuthority.equals("PI"))
                                changePermissionToGroup(currEl, "V,B", "B_budget_UO", currAuthority);
                        }
                        for (String currUser : users) {
                            changePermissionToUser(currEl.getId().toString(), "V,B", "B_budget_PI_RO", currUser);
                        }
                        changePermissionToGroup(currEl, "V,B", "B_budget_CTC_close", "CTC");
                        changePermissionToGroup(currEl, "", "", "PI");
                        try {
                            for (Element currSingoloBudget : currEl.getChildrenByType("FolderSingoloBraccio").get(0).getChildren()) {
                                for (String currAuthority : gruppi) {
                                    if (!currAuthority.equals("CTC") && !currAuthority.equals("PI"))
                                        changePermissionToGroup(currSingoloBudget, "V,B", "SB_budget_UO", currAuthority);
                                }
                                for (String currUser : users) {
                                    changePermissionToUser(currSingoloBudget.getId().toString(), "V,B", "SB_budget_PI_RO", currUser);
                                }
                                changePermissionToGroup(currSingoloBudget, "V,B", "SB_budget_CTC_close", "CTC");
                                changePermissionToGroup(currSingoloBudget, "", "", "PI");
                            }
                        } catch (Exception ex) {

                        }
                    } else if (origType.equals("BudgetSingoloBraccio")) {
                    /*for (String currAuthority : gruppi) {
                        if (!currAuthority.equals("CTC") && !currAuthority.equals("PI"))
                            changePermissionToGroup(currEl, "V,B", "SB_budget_UO", currAuthority);
                    }
                    for (String currUser : users) {
                        changePermissionToUser(currEl.getId().toString(), "V,B", "SB_budget_PI_RO", currUser);
                    }
                    changePermissionToGroup(currEl, "V,B", "SB_budget_CTC_close", "CTC");
                    changePermissionToGroup(currEl, "", "", "PI");*/
                    } else {
                        for (String currAuthority : gruppi) {
                            changePermissionToGroup(currEl, "V,B", "", currAuthority);
                        }
                    }
                }

            }
        }

        updateElementMetaData(user, el, metadata, "CREATE");
        HashMap<String, String> clonaFinito = new HashMap<String, String>();//CRPMS-441
        clonaFinito.put("Budget_ClonazioneInCorso", ""); //CRPMS-441
        updateElementMetaData(user, el, clonaFinito, "UPDATE");//CRPMS-441
        return el;
    }

    public Element defaultClone(IUser user, Long id) throws RestException {
        return defaultClone(user.getUsername(), id);
    }

    public Element defaultClone(String user, Long fromId) throws RestException {
        return defaultClone(user, fromId, null, null);
    }

    public Element defaultClone(String user, Long fromId, HashMap<String, Object> params) throws RestException {
        return defaultClone(user, fromId, null, params);
    }

    public Element defaultClone(String user, Long fromId, Long toId) throws RestException {
        return defaultClone(user, fromId, toId, null);
    }

    public Element defaultClone(String user, Long fromId, Long toId, HashMap<String, Object> params) throws RestException {
        return defaultClone(user, fromId, toId, params, null);
    }

    public Element defaultClone(String user, Long fromId, Long toId, HashMap<String, Object> params, HashMap<String, String> dataToUpdate) throws RestException {
        resetCloning();
        resetLinkCloning();
        Element orig = getElement(fromId);
        Element targetParent;

        if (toId == null) {
            targetParent = orig.getParent();
        } else {
            targetParent = getElement(toId);
        }

        HashMap<String, String> links = new HashMap<String, String>();  // metadata linkedElement
        HashMap<String, String> data = new HashMap<String, String>();
        for (ElementMetadata m : orig.getData()) {
            if (m.getVals().size() > 0) {
                if (m.getField().getType().equals(MetadataFieldType.ELEMENT_LINK)) {
                    links.put(m.getTemplateName() + "_" + m.getFieldName(), ((Element) m.getVals().get(0)).getId().toString());
                    data.put(m.getTemplateName() + "_" + m.getFieldName(), ((Element) m.getVals().get(0)).getId().toString());
                } else data.put(m.getTemplateName() + "_" + m.getFieldName(), m.getVals().get(0).toString());
            }
        }
        if (dataToUpdate != null && !dataToUpdate.isEmpty()) {
            data.putAll(dataToUpdate);
        }
        byte[] file = null;
        String fileName = null;
        Long fileSize = null;
        String version = "";
        String date = "";
        String note = "";
        String autore = "";
        if (orig.getFile() != null) {
            fileName = orig.getFile().getFileName();
            fileSize = orig.getFile().getSize();
            file = orig.getFile().getContent().getContent();
            autore = orig.getFile().getAutore();
            note = orig.getFile().getNote();
            version = orig.getFile().getVersion();
        }
        Element dest = saveElement(user, orig.getType(), data, file, fileName, fileSize, version, date, note, autore, targetParent, true);
        getAxmr3txManager().commitAndKeepAlive();//CRPMS-441
        addCloning(orig, dest);
        Set<String> metadataList = links.keySet();
        for (String metadata : metadataList) {
            addLinkCloning(links.get(metadata), dest, metadata);
        }
        if (orig.getChildren() != null && orig.getChildren().size() > 0)
            defaultDeepChildrenCopy(user, orig, dest, params);
        Set<String> clonedList = cloning.keySet();
        for (String cloned : clonedList) {
            if (linkCloning.containsKey(cloned)) {
                HashMap<Element, String> linksToUpdate = linkCloning.get(cloned);
                Set<Element> elementsList = linksToUpdate.keySet();
                for (Element currElement : elementsList) {
                    HashMap<String, String> linkData = new HashMap<String, String>();
                    linkData.put(linksToUpdate.get(currElement), cloning.get(cloned));


                    updateElementMetaData(user, null, currElement, linkData, "CREATE", true);
                }
            }

        }
        for (ElementTypeAssociatedWorkflow awf : dest.getType().getAssociatedWorkflows()) {
            if (awf.isEnabled() && awf.isStartOnCreate()) {
                /*Long elId = dest.getId();
                txManager.getTxs().get("doc").commit();
                if (!txManager.getSessions().get("doc").isOpen()) {
                    it.cineca.siss.axmr3.log.Log.info(getClass(),"La sessione è chiusa, la riapro");
                    it.cineca.siss.axmr3.log.Log.info(getClass(),"Apro la sessione 3 " + this.getClass().getCanonicalName());
                    txManager.getSessions().put("doc", txManager.getSessionFactories().get("doc").openSession());
                    it.cineca.siss.axmr3.log.Log.info(getClass(),"Begin Transaction 5 " + this.getClass().getCanonicalName());
                    txManager.getTxs().put("doc", txManager.getSessions().get("doc").beginTransaction());
                } else {
                    it.cineca.siss.axmr3.log.Log.info(getClass(),"La sessione è aperta, controllo la transazione");
                    if (!txManager.getTxs().get("doc").isActive()) {
                        it.cineca.siss.axmr3.log.Log.info(getClass(),"La transazione non è attiva 1");
                        it.cineca.siss.axmr3.log.Log.info(getClass(),"Begin Transaction 6 " + this.getClass().getCanonicalName());
                        txManager.getTxs().put("doc", txManager.getSessions().get("doc").beginTransaction());
                    }
                }*/
                dest = sync(dest);
                this.startProcess(user, dest, awf.getProcessKey());

            }
        }
        return dest;
    }

    public void setDraftRef(IUser user, Element orig, Element dest) throws RestException {
        try {
            for (Acl c : dest.getAcls()) {
                for (AclContainer container : c.getContainers()) {
                    aclContainerDAO.delete(container);
                }
                aclDAO.delete(c);
            }
            Policy pol = new Policy();
            pol.setCanAddChild(true);
            pol.setCanAddComment(true);
            pol.setCanBrowse(true);
            pol.setCanCreate(true);
            pol.setCanDelete(true);
            pol.setCanEnableTemplate(true);
            pol.setCanLaunchProcess(false);
            pol.setCanModerate(false);
            pol.setCanChangePermission(false);
            pol.setCanUpdate(true);
            pol.setCanView(true);
            pol.setCanBrowse(true);
            Acl c = new Acl();
            AclContainer container = new AclContainer();
            container.setAuthority(false);
            container.setContainer(user.getUsername());
            c.setContainers(new LinkedList<AclContainer>());
            c.setPolicyValue(pol.toInt());
            c.setPositionalAce(pol.toBinary());
            aclDAO.save(c);
            container.setAcl(c);
            aclContainerDAO.save(container);
            c.getContainers().add(container);
            aclDAO.saveOrUpdate(c);
            dest.setAcls(new LinkedList<Acl>());
            dest.getAcls().add(c);
            dest.setOriginal(orig);
            docDAO.saveOrUpdate(dest);
            addElidToBeUpdeated(dest.getId(),true);
            commitTXSessionAndKeepAlive();
        } catch (Exception ex) {
            throw new RestException(ex.getMessage(), txManager);
        }
    }

    public void loadCustomGroupsForUser(IUser iUser, Element currElement) {

        UserImpl user = null;
        try {
            List<Element> centri = getElementCentro(currElement);
            user = (UserImpl) iUser;
            String pi = "";
            String sqlQuery = "select progr_princ_inv from ana_utenti_1 where UPPER(userid)=?";
            try (Connection conn = dataSource.getConnection()) {
                try (PreparedStatement stmt = conn.prepareStatement(sqlQuery)) {
                    stmt.setString(1, user.getUsername().toUpperCase());
                    try (ResultSet rset = stmt.executeQuery()) {
                        String progr = "";
                        while (rset.next()) {
                            progr = rset.getString(1);
                        }
                        AuthorityImpl auth = new AuthorityImpl();
                        Collection<AuthorityImpl> auths = user.getAuthorities();
                        for (AuthorityImpl currAuth : auths) {
                            if (currAuth.getAuthority().equals("CURRENT_PI")) {
                                auths.remove(currAuth);
                            }
                        }
                        for (Element centro : centri) {
                            if (centro != null) {
                                try {
                                    pi = centro.getFieldDataCode("IdCentro", "PI");
                                } catch (Exception ex) {
                                    log.error(ex.getMessage(), ex);
                                    pi = "errato";
                                }
                                if (progr != null && progr.equals(pi)) {
                                    //auth.setId(Long.parseLong(progr));
                                    auth.setAuthority("CURRENT_PI");
                                    auth.setDescription("PI");
                                    auths.add(auth);
                                }
                            }
                        }
                    }
                }
            }
        } catch (Exception ex) {
            //log.error(ex.getMessage(),ex);
        }
        try {
            user = (UserImpl) iUser;
            String pi = "";
            String sqlQuery = "select ID_VISIBILITY_CNTR,codice_fiscale from ana_utenti_1 where UPPER(userid)=?";
            try (Connection conn = dataSource.getConnection()) {
                try (PreparedStatement stmt = conn.prepareStatement(sqlQuery)) {
                    stmt.setString(1, user.getUsername().toUpperCase());
                    try (ResultSet rset = stmt.executeQuery()) {
                        String ente = "";
                        String cf = "";
                        while (rset.next()) {
                            ente = rset.getString(1);
                            cf = rset.getString(2);
                        }
                        AuthorityImpl auth = new AuthorityImpl();
                        AuthorityImpl auth2 = new AuthorityImpl();
                        Collection<AuthorityImpl> auths = user.getAuthorities();
                        Boolean dont1 = false;
                        Boolean dont2 = false;
                        for (AuthorityImpl currAuth : auths) {
                            if (currAuth.getAuthority().equals(ente)) {
                                dont1 = true;
                            }
                            if (currAuth.getAuthority().equals(cf)) {
                                dont2 = true;
                            }
                        }
                        if (!dont1 && ente != null && ente != "") {
                            auth.setAuthority(ente);
                            auth.setDescription("AZIENDA_ENTE");
                            auths.add(auth);
                        }
                        if (!dont2 && cf != null && cf != "") {
                            auth2.setAuthority(cf);
                            auth2.setDescription("CODICE_FISCALE");
                            auths.add(auth2);
                        }
                    }

                }

            }

        } catch (Exception ex) {
            //log.error(ex.getMessage(),ex);

        }
        return;
    }

    public List<Element> getElementCentro(Element el) {
        LinkedList<Element> res = new LinkedList<Element>();

        try {
            if (el.getTypeName().equals("Studio")) {

                return el.getChildrenByType("Centro");
            }
            if (el.getTypeName().equals("Centro")) {
                res.add(el);
            } else {
                return getElementCentro(el.getParent());
            }
        } catch (Exception ex) {
            return null;
        }

        return res;
    }


    public Element createDraft(IUser user, Long id) throws RestException {
        try {
            Element orig = getElement(id);
            HashMap<String, String> data = new HashMap<String, String>();
            for (ElementMetadata m : orig.getData()) {
                data.put(m.getTemplateName() + "_" + m.getFieldName(), m.getVals().get(0).toString());
            }
            byte[] file = null;
            String fileName = null;
            Long fileSize = null;
            String version = "";
            String date = "";
            String note = "";
            String autore = "";
            if (orig.getFile() != null) {
                fileName = orig.getFile().getFileName();
                fileSize = orig.getFile().getSize();
                file = orig.getFile().getContent().getContent();
                autore = orig.getFile().getAutore();
                note = orig.getFile().getNote();
                version = orig.getFile().getVersion();
            }
            Element dest = saveElement(user, orig.getType(), data, file, fileName, fileSize, version, date, note, autore, orig.getParent());
            setDraftRef(user, orig, dest);
            if (orig.getChilds() != null && orig.getChilds().size() > 0) createChildrenDraft(user, orig, dest);
            return dest;
        } catch (Exception ex) {
            throw new RestException(ex.getMessage(), txManager);
        }
    }

    public void createChildrenDraft(IUser user, Element orig, Element dest) throws RestException {
        try {
            for (Element child : orig.getChilds()) {
                HashMap<String, String> data = new HashMap<String, String>();
                for (ElementMetadata m : child.getData()) {
                    data.put(m.getTemplateName() + "_" + m.getFieldName(), m.getVals().get(0).toString());
                }
                byte[] file = null;
                String fileName = null;
                Long fileSize = null;
                String version = "";
                String date = "";
                String note = "";
                String autore = "";
                if (orig.getFile() != null) {
                    fileName = orig.getFile().getFileName();
                    fileSize = orig.getFile().getSize();
                    file = orig.getFile().getContent().getContent();
                    autore = orig.getFile().getAutore();
                    note = orig.getFile().getNote();
                    version = orig.getFile().getVersion();
                }
                Element destChild = saveElement(user, child.getType(), data, file, fileName, fileSize, version, date, note, autore, dest);
                setDraftRef(user, orig, destChild);
                if (child.getChilds() != null && child.getChilds().size() > 0)
                    createChildrenDraft(user, child, destChild);
            }
        } catch (Exception ex) {
            throw new RestException(ex.getMessage(), txManager);
        }
    }

    public void defaultDeepChildrenCopy(IUser user, Element orig, Element dest) throws RestException {
        defaultDeepChildrenCopy(user.getUsername(), orig, dest);
    }

    public void defaultDeepChildrenCopy(String user, Element orig, Element dest) throws RestException {
        defaultDeepChildrenCopy(user, orig, dest, null);
    }

    public void defaultDeepChildrenCopy(String user, Element orig, Element dest, HashMap<String, Object> params) throws RestException {
        List<String> skipTypes = new LinkedList<String>();
        if (params != null && params.containsKey("skipTypes")) {
            skipTypes = (List<String>) params.get("skipTypes");

        }
        it.cineca.siss.axmr3.log.Log.info(getClass(), "defaultDeepChildrenCopy: " + orig.getType().getTypeId() + " " + orig.getId().toString());
        loopToContinue:
        for (Element child : orig.getChildren()) {
            //for(String type:skipTypes){
            if (skipTypes.contains(child.getType().getTypeId())) {
                it.cineca.siss.axmr3.log.Log.info(getClass(), "Skipping " + child.getType().getTypeId());
                continue loopToContinue;
            } else {
                it.cineca.siss.axmr3.log.Log.info(getClass(), "No skipping " + child.getType().getTypeId());
                //}
                HashMap<String, String> links = new HashMap<String, String>();  // metadata linkedElement
                HashMap<String, String> data = new HashMap<String, String>();
                for (ElementMetadata m : child.getData()) {
                    if (m.getVals().size() > 0) {
                        if (m.getField().getType().equals(MetadataFieldType.ELEMENT_LINK)) {
                            links.put(m.getTemplateName() + "_" + m.getFieldName(), ((Element) m.getVals().get(0)).getId().toString());
                            data.put(m.getTemplateName() + "_" + m.getFieldName(), ((Element) m.getVals().get(0)).getId().toString());
                        } else data.put(m.getTemplateName() + "_" + m.getFieldName(), m.getVals().get(0).toString());
                    }
                }
                byte[] file = null;
                String fileName = null;
                Long fileSize = null;
                String version = "";
                String date = "";
                String note = "";
                String autore = "";
                if (orig.getFile() != null) {
                    fileName = orig.getFile().getFileName();
                    fileSize = orig.getFile().getSize();
                    file = orig.getFile().getContent().getContent();
                    autore = orig.getFile().getAutore();
                    note = orig.getFile().getNote();
                    version = orig.getFile().getVersion();
                }
                Element destChild = saveElement(user, child.getType(), data, file, fileName, fileSize, version, date, note, autore, dest, true);
                addCloning(child, destChild);
                Set<String> metadataList = links.keySet();
                for (String metadata : metadataList) {
                    addLinkCloning(links.get(metadata), destChild, metadata);
                }
                if (child.getChildren() != null && child.getChildren().size() > 0) {
                    it.cineca.siss.axmr3.log.Log.info(getClass(), "defaultDeepChildrenCopy: procedi con i figli: " + child.getType().getTypeId() + " from:" + child.getId().toString() + " to:" + destChild.getId().toString());
                    defaultDeepChildrenCopy(user, child, destChild, params);
                } else {
                    it.cineca.siss.axmr3.log.Log.info(getClass(), "defaultDeepChildrenCopy: non ha figli:  " + child.getType().getTypeId() + " from:" + child.getId().toString() + " to:" + destChild.getId().toString());
                }

            }
        }

    }

    public List<PredefinedPolicy> getPolicies() {
        Criteria c = polDAO.getCriteria();
        return c.list();

    }

    public Acl getAcl(Element element, Long aclId) {
        Acl acl = null;
        for (Acl a : element.getAcls()) {
            if (a.getId().equals(aclId)) acl = a;
        }
        return acl;
    }

    public PredefinedPolicy getPolicy(long parseLong) {
        return polDAO.getById(parseLong);
    }


    public void saveAcl(IUser user2, Element element, List<String> groups,
                        List<String> users, Policy pol, PredefinedPolicy pp, Long id, Long id_ref) throws RestException {
        try {
            Policy appliedPol = element.getUserPolicy(user2);
            boolean datamanager = false;
            for (IAuthority a : user2.getAuthorities()) {
                if (a.getAuthority().equals("DATAMANAGER")) {
                    datamanager = true;
                }
            }
            if (!datamanager && !appliedPol.isCanChangePermission()) throw new RestException("FORBIDDEN", txManager);
            if (id == null && id_ref == null) {
                Acl acl = new Acl();
                acl.setPolicyValue(pol.toInt());
                acl.setElement(element);
                aclDAO.save(acl);
                acl.setContainers(new LinkedList<AclContainer>());
                if (groups != null && groups.size() > 0) for (String group : groups) {
                    AclContainer c = new AclContainer();
                    c.setContainer(group);
                    c.setAcl(acl);
                    c.setAuthority(true);
                    aclContainerDAO.saveOrUpdate(c);
                    acl.getContainers().add(c);
                }
                if (users != null && users.size() > 0) for (String user : users) {
                    AclContainer c = new AclContainer();
                    c.setContainer(user);
                    c.setAcl(acl);
                    c.setAuthority(false);
                    aclContainerDAO.saveOrUpdate(c);
                    acl.getContainers().add(c);
                }
                if (pp != null) {
                    acl.setPredifinedPolicy(pp);
                }

                aclDAO.saveOrUpdate(acl);
                if (element.getAcls() == null) element.setAcls(new LinkedList<Acl>());
                element.getAcls().add(acl);
                docDAO.saveOrUpdate(element);
                addElidToBeUpdeated(element.getId(),true);
                for (Element child : element.getChildren()) {
                    saveAcl(user2, child, groups, users, pol, pp, null, acl.getId());
                }
            } else {
                if (id == null && id_ref != null) {
                    Acl acl = null;
                    for (Acl a : element.getAcls()) {
                        if (a.getIdRef() != null && a.getIdRef().equals(id_ref)) acl = a;
                    }
                    if (acl == null) {
                        acl = new Acl();
                        if (element.getAcls() == null) element.setAcls(new LinkedList<Acl>());
                        element.getAcls().add(acl);
                    }
                    if (acl.getContainers() != null) for (AclContainer c : acl.getContainers()) {
                        aclContainerDAO.delete(c);
                    }
                    acl.setPolicyValue(pol.toInt());
                    acl.setElement(element);
                    acl.setIdRef(id_ref);
                    aclDAO.save(acl);
                    acl.setContainers(new LinkedList<AclContainer>());
                    if (groups != null && groups.size() > 0) for (String group : groups) {
                        AclContainer c = new AclContainer();
                        c.setContainer(group);
                        c.setAcl(acl);
                        c.setAuthority(true);
                        aclContainerDAO.saveOrUpdate(c);
                        acl.getContainers().add(c);
                    }
                    if (users != null && users.size() > 0) for (String user : users) {
                        AclContainer c = new AclContainer();
                        c.setContainer(user);
                        c.setAcl(acl);
                        c.setAuthority(false);
                        aclContainerDAO.saveOrUpdate(c);
                        acl.getContainers().add(c);
                    }
                    if (pp != null) {
                        acl.setPredifinedPolicy(pp);
                    }

                    aclDAO.saveOrUpdate(acl);
                    docDAO.saveOrUpdate(element);
                    addElidToBeUpdeated(element.getId(),true);
                    for (Element child : element.getChildren()) {
                        saveAcl(user2, child, groups, users, pol, pp, null, acl.getId());
                    }
                } else {
                    Acl acl = null;
                    for (Acl a : element.getAcls()) {
                        if (a.getId().equals(id)) acl = a;
                    }
                    if (acl == null) {
                        acl = new Acl();
                        if (element.getAcls() == null) element.setAcls(new LinkedList<Acl>());
                        element.getAcls().add(acl);
                    }
                    if (acl.getContainers() != null) for (AclContainer c : acl.getContainers()) {
                        aclContainerDAO.delete(c);
                    }
                    acl.setPolicyValue(pol.toInt());
                    acl.setElement(element);
                    acl.setIdRef(id_ref);
                    aclDAO.save(acl);
                    acl.setContainers(new LinkedList<AclContainer>());
                    if (groups != null && groups.size() > 0) for (String group : groups) {
                        AclContainer c = new AclContainer();
                        c.setContainer(group);
                        c.setAcl(acl);
                        c.setAuthority(true);
                        aclContainerDAO.saveOrUpdate(c);
                        acl.getContainers().add(c);
                    }
                    if (users != null && users.size() > 0) for (String user : users) {
                        AclContainer c = new AclContainer();
                        c.setContainer(user);
                        c.setAcl(acl);
                        c.setAuthority(false);
                        aclContainerDAO.saveOrUpdate(c);
                        acl.getContainers().add(c);
                    }
                    if (pp != null) {
                        acl.setPredifinedPolicy(pp);
                    }
                    aclDAO.saveOrUpdate(acl);
                    docDAO.saveOrUpdate(element);
                    addElidToBeUpdeated(element.getId(),true);
                    for (Element child : element.getChildren()) {
                        saveAcl(user2, child, groups, users, pol, pp, null, acl.getId());
                    }
                }
            }
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        }
    }

    public void deleteAcl(IUser user2, Element element, Long aclId) throws RestException {
        try {
            Policy appliedPol = element.getUserPolicy(user2);
            boolean datamanager = false;
            for (IAuthority a : user2.getAuthorities()) {
                if (a.getAuthority().equals("DATAMANAGER")) {
                    datamanager = true;
                }
            }
            if (!datamanager && !appliedPol.isCanChangePermission()) throw new RestException("FORBIDDEN", txManager);
            Acl a = aclDAO.getById(aclId);
            for (AclContainer c : a.getContainers()) {
                it.cineca.siss.axmr3.log.Log.info(getClass(), "Elimino il container per " + c.getContainer());
                aclContainerDAO.delete(c);
            }
            it.cineca.siss.axmr3.log.Log.info(getClass(), "Elimino l'acl con id " + a.getId());
            aclContainerDAO.getSession().flush();
            aclDAO.delete(a);

            Criteria c = aclDAO.getCriteria();
            c.add(Restrictions.eq("idRef", aclId));
            List<Acl> res = c.list();
            for (Acl a1 : res) {
                for (AclContainer c1 : a1.getContainers()) {
                    aclContainerDAO.delete(c1);
                }
                aclContainerDAO.getSession().flush();
                aclDAO.delete(a1);
            }

        } catch (Exception ex) {
            throw new RestException(ex.getMessage(), txManager);
        }
    }

    public List<ElementType> getRootBrowsableElementTypes(IUser user) {
        DetachedCriteria c = docTypeDAO.getDetachedCriteria();
        Policy pCheck = new Policy();
        pCheck.setCanBrowse(true);
        //it.cineca.siss.axmr3.log.Log.info(getClass(),"Policy to check:" +pCheck.toLikeClause());
        c.createAlias("acls", "acls")
                .createAlias("acls.containers", "aclContainers")
                .add(Restrictions.eq("rootAble", true))
                .add(Restrictions.eq("deleted", false))
                .setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY)
                .add(pCheck.checkCriterion("acls", "aclContainers", user));
        return docTypeDAO.getCriteriaList(c);
    }


    public ElementType getType(Long typeId) {
        return docTypeDAO.getById(typeId);
    }

    @Autowired
    protected ProcessEngine processEngine;

    public ProcessEngine getProcessEngine() {
        return processEngine;
    }

    public void setProcessEngine(ProcessEngine processEngine) {
        this.processEngine = processEngine;
    }

    public String startProcess(IUser user, Element el, String processKey) throws RestException {
        return startProcess(user.getUsername(), el.getId().toString(), processKey);
    }

    public String startProcess(String user, Element el, String processKey, HashMap<String, String> data) throws RestException {
        return startProcess(user, el.getId().toString(), processKey, data);

    }

    public String startProcess(String user, Element el, String processKey) throws RestException {
        return startProcess(user, el.getId().toString(), processKey);

    }

    public String startProcess(String user, Element el, String processKey, boolean force) throws RestException {
        return startProcess(user, el.getId().toString(), processKey, new HashMap<String, String>(), force);

    }

    public String startProcess(Element el, String processKey) throws RestException {
        return startProcess("", el.getId().toString(), processKey);

    }

    public String startProcess(String user, String elementId, String processKey) throws RestException {
        return startProcess(user, elementId, processKey, new HashMap<String, String>());
    }

    public String startProcess(String user, String elementId, String processKey, HashMap<String, String> data) throws RestException {
        return startProcess(user, elementId, processKey, data, false);
    }

    public String startProcess(String user, String elementId, String processKey, HashMap<String, String> data, boolean force) throws RestException {
        try {
            it.cineca.siss.axmr3.log.Log.info(getClass(), "controllo che il processo " + processKey + " non sia già presente");
            boolean alreadyStarted = false;
            String pInstanceId = "";
            for (ProcessInstance pi : getActiveProcesses(getElement(elementId))) { //TOSCANA-185 controllo che il processo non esista prima di farne partire un altro
                it.cineca.siss.axmr3.log.Log.info(getClass(), "---> processDefinition: " + pi.getProcessDefinitionId());
                String myProcessId = pi.getProcessDefinitionId();
                String myProcessKey = processEngine.getRepositoryService().getProcessDefinition(myProcessId).getKey();
                if (myProcessKey.equals(processKey)) {
                    alreadyStarted = true;
                    pInstanceId = pi.getProcessInstanceId();
                    it.cineca.siss.axmr3.log.Log.info(getClass(), "------> TROVATA !!! <------ processDefinition: " + pi.getProcessDefinitionId());
                }
            }
            if (!alreadyStarted || force) {
                /* effettuol il commit della sessione pendente per permettere alla connessione in mano al WF di avere accesso ai dati appena modificati*/
                if (txManager.getSessions().get("doc").isOpen()) txManager.getTxs().get("doc").commit();
                if (!txManager.getSessions().get("doc").isOpen()) {
                    it.cineca.siss.axmr3.log.Log.info(getClass(), "Apro la sessione 6 " + this.getClass().getCanonicalName());
                    txManager.getSessions().put("doc", txManager.getSessionFactories().get("doc").openSession());
                    it.cineca.siss.axmr3.log.Log.info(getClass(), "Begin Transaction 11 " + this.getClass().getCanonicalName());
                    txManager.getTxs().put("doc", txManager.getSessions().get("doc").beginTransaction());
                } else {
                    if (!txManager.getTxs().get("doc").isActive()) {
                        //it.cineca.siss.axmr3.log.Log.info(getClass(),"La transazione non è attiva 2");
                        it.cineca.siss.axmr3.log.Log.info(getClass(), "Begin Transaction 12 " + this.getClass().getCanonicalName());
                        txManager.getTxs().put("doc", txManager.getSessions().get("doc").beginTransaction());
                    }
                }
                HashMap<String, Object> vars = new HashMap<String, Object>();
                if (!data.isEmpty()) {
                    vars.putAll(data);
                }
                vars.put("elementId", elementId);
                if (!user.equals("")) {
                    vars.put("startedBy", user);
                    vars.put("lastUserid", user);
                }
                ProcessInstance pInstance = processEngine.getRuntimeService().startProcessInstanceByKey(processKey, vars);
                pInstanceId = pInstance.getProcessInstanceId();

            }
            return pInstanceId;
        } catch (Exception ex) {
            throw new RestException(ex.getMessage(), txManager);
        }
    }


    public List<ProcessInstance> getActiveProcesses(Element el) {
        it.cineca.siss.axmr3.log.Log.info(getClass(), "Cerco le istanze di processo attive per l'elemento " + el.getId());
        return getActiveProcesses(el.getId().toString());
    }

    public List<ProcessInstance> getActiveProcesses(String elementId) {
        it.cineca.siss.axmr3.log.Log.info(getClass(), "Cerco le istanze di processo attive per l'elemento " + elementId);
        return processEngine.getRuntimeService().createProcessInstanceQuery().active().variableValueEquals("elementId", elementId).list();
    }

    public List<ProcessInstance> getActiveProcesses(IUser user, Element el) {
        return getActiveProcesses(el);
        /*
        List<ProcessInstance> ret=new LinkedList<ProcessInstance>();
        for (ElementProcessInstance p:el.getProcessInstances()) {
            String instanceId=p.getProcessInstanceId();
            if (processEngine.getRuntimeService().createProcessInstanceQuery().processInstanceId(instanceId).count()>0){
                ret.add(processEngine.getRuntimeService().createProcessInstanceQuery().processInstanceId(instanceId).singleResult());
            }
        }
        //processEngine.getTaskService().createTaskQuery().active().list();
        return ret;
        */
    }

    public List<HistoricProcessInstance> getTerminatedProcesses(Element element) {
        return getTerminatedProcesses(element.getId().toString());
    }

    public List<HistoricProcessInstance> getTerminatedProcesses(String elementId) {
        return processEngine.getHistoryService().createHistoricProcessInstanceQuery().includeProcessVariables().variableValueEquals("elementId", elementId).list();
    }

    public List<HistoricProcessInstance> getTerminatedProcesses(IUser user, Element element) {
        return getTerminatedProcesses(element.getId().toString());
        /*
        List<HistoricProcessInstance> ret=new LinkedList<HistoricProcessInstance>();
        for (ElementProcessInstance p:el.getProcessInstances()) {
            String instanceId=p.getProcessInstanceId();
            if (processEngine.getHistoryService().createHistoricProcessInstanceQuery().processInstanceId(instanceId).finished().count()>0){
                ret.add(processEngine.getHistoryService().createHistoricProcessInstanceQuery().processInstanceId(instanceId).singleResult());
                HistoricProcessInstance hip = processEngine.getHistoryService().createHistoricProcessInstanceQuery().processInstanceId(instanceId).singleResult();

            }

        }
        return ret;
        */
    }

    public void deleteProcessInstance(String id, String text) {
        processEngine.getRuntimeService().deleteProcessInstance(id, text);
    }

    public List<ProcessDefinition> getAvailableProcessess(IUser user, Element el) {
        List<ProcessDefinition> ret = new LinkedList<ProcessDefinition>();
        for (ElementTypeAssociatedWorkflow wf : el.getType().getAssociatedWorkflows()) {
            if (wf.isEnabled()) {
                ret.add(processEngine.getRepositoryService().createProcessDefinitionQuery().processDefinitionKey(wf.getProcessKey()).active().latestVersion().singleResult());
            }
        }
        return ret;
    }

    public List<it.cineca.siss.axmr3.doc.types.Task> getActiveTask(IUser user, Element el, List<ProcessInstance> instances) {
        List<String> groups = new LinkedList<String>();
        for (IAuthority auth : user.getAuthorities()) groups.add(auth.getAuthority());
        List<Task> tasks = new LinkedList<Task>();
        for (ProcessInstance pInst : instances) {
            List<Task> mines = processEngine.getTaskService().createTaskQuery().active().processInstanceId(pInst.getId()).taskInvolvedUser(user.getUsername()).includeProcessVariables().includeTaskLocalVariables().list();
            List<Task> condidateGroups = processEngine.getTaskService().createTaskQuery().active().processInstanceId(pInst.getId()).taskCandidateGroupIn(groups).includeProcessVariables().includeTaskLocalVariables().list();
            for (Task t : mines) {
                if (!tasks.contains(t)) tasks.add(t);
            }
            for (Task t : condidateGroups) {
                boolean alreadyPresent = false;
                for (Task t1 : mines) {
                    if (t1.getId().equals(t.getId())) alreadyPresent = true;
                }
                if (!alreadyPresent) tasks.add(t);
            }
        }
        return it.cineca.siss.axmr3.doc.types.Task.fromActivitiTaskLisk(tasks, processEngine);
    }

    public HashMap<String, ProcessDefinition> getActiveProcessDefinition(IUser user, Element el, List<ProcessInstance> activeProcesses) {
        HashMap<String, ProcessDefinition> ret = new HashMap<String, ProcessDefinition>();
        for (ProcessInstance pInst : activeProcesses) {
            ret.put(pInst.getProcessDefinitionId(), processEngine.getRepositoryService().createProcessDefinitionQuery().processDefinitionId(pInst.getProcessDefinitionId()).singleResult());
        }
        return ret;
    }

    public List<Element> getElementsLimitById(IUser user, Long typeId, int page, int limit, String orderBy, String orderType) {
        int rowPerPage = limit;
        int start = (page - 1) * rowPerPage;
        int total = 0;
        DetachedCriteria c = getBrowsableElementsCriteria(user);
        ElementType type = docTypeDAO.getById(typeId);
        c.add(Restrictions.eq("type", type));
        //c.setMaxResults(rowPerPage);
        c.setProjection(Projections.countDistinct("id"));
        total = ((Long) docDAO.getCriteriaUniqueResult(c)).intValue();
        //it.cineca.siss.axmr3.log.Log.info(getClass(),"\n\n\n\n\nOrders: " + orderBy + " - " + orderType + "\n\n\n\n\n\n");
        if (!orderType.isEmpty() && !orderBy.isEmpty()) {
            if (orderBy.equals("createDt")) {
                if (orderType.equals("asc")) c.addOrder(Order.asc("creationDt"));
                if (orderType.equals("desc")) c.addOrder(Order.desc("creationDt"));
            } else if (orderBy.equals("updateDt")) {
                if (orderType.equals("asc")) c.addOrder(Order.asc("lastUpdateDt"));
                if (orderType.equals("desc")) c.addOrder(Order.desc("lastUpdateDt"));
            } else {

            }
        } else {
            if (type.isSortable()) c.addOrder(Order.asc("position"));
            else c.addOrder(Order.desc("creationDt"));
        }
        return docDAO.getFixedResultSize(c, start, rowPerPage, total);
    }


    public List<Element> getElementsLimitByIdFiltered(IUser user, Long typeId, int page, int limit, String orderBy, String orderType, String field, String filterPattern, boolean exact) {
        int rowPerPage = limit;
        int start = (page - 1) * rowPerPage;
        int total = 0;
        DetachedCriteria c = getBrowsableElementsCriteria(user);
        ElementType type = docTypeDAO.getById(typeId);
        c.add(Restrictions.eq("type", type));
        //c.setMaxResults(rowPerPage);
        c.setProjection(Projections.countDistinct("id"));
        total = ((Long) docDAO.getCriteriaUniqueResult(c)).intValue();
        //it.cineca.siss.axmr3.log.Log.info(getClass(),"\n\n\n\n\nOrders: " + orderBy + " - " + orderType + "\n\n\n\n\n\n");
        if (!orderType.isEmpty() && !orderBy.isEmpty()) {
            if (orderBy.equals("createDt")) {
                if (orderType.equals("asc")) c.addOrder(Order.asc("creationDt"));
                if (orderType.equals("desc")) c.addOrder(Order.desc("creationDt"));
            } else if (orderBy.equals("updateDt")) {
                if (orderType.equals("asc")) c.addOrder(Order.asc("lastUpdateDt"));
                if (orderType.equals("desc")) c.addOrder(Order.desc("lastUpdateDt"));
            } else {

            }
        } else {
            if (type.isSortable()) c.addOrder(Order.asc("position"));
            else c.addOrder(Order.desc("creationDt"));
        }
        return docDAO.getFixedResultSize(c, start, rowPerPage, total);
    }

    public void hardDelete(Acl a) throws AxmrGenericException {
        for (AclContainer c : a.getContainers()) {
            aclContainerDAO.delete(c);
        }
        aclDAO.delete(a);
    }

    public void hardDelete(AuditMetadata a) throws AxmrGenericException {
        for (AuditValue c : a.getValues()) {
            aMdValDAO.delete(c);
        }
        aMdDAO.delete(a);
    }

    public void hardDelete(AuditFile a) throws AxmrGenericException {
        aFileContentDAO.delete(a.getContent());
        aFileDAO.delete(a);
    }

    public void hardDelete(Comment a) throws AxmrGenericException {
        commentDAO.delete(a);
    }

    public void hardDelete(ElementMetadata a) throws AxmrGenericException {
        for (ElementMetadataValue c : a.getValues()) {
            elMdValueDAO.delete(c);
        }
        elMdDAO.delete(a);
    }

    public void hardDelete(Event a) throws AxmrGenericException {
        evDAO.delete(a);
    }

    public void hardDelete(ElementProcessInstance a) throws AxmrGenericException {
        elPInstanceDAO.delete(a);
    }

    public void hardDelete(Element el) throws AxmrGenericException {
        try {
            for (Acl a : el.getAcls()) hardDelete(a);
            for (AuditMetadata a : el.getAuditData()) hardDelete(a);
            for (AuditFile a : el.getAuditFiles()) hardDelete(a);
            for (Element a : el.getChildren()) hardDelete(a);
            for (Comment a : el.getComments()) hardDelete(a);
            for (ElementMetadata a : el.getData()) hardDelete(a);
            for (ElementTemplate a : el.getElementTemplates()) hardDelete(a);
            for (Event a : el.getEvs()) hardDelete(a);
            //for (ElementProcessInstance a:el.getProcessInstances()) hardDelete(a);
            docDAO.delete(el);
        } catch (Exception e) {
            throw new RestException(e.getMessage(), txManager);
        }
    }

    private void hardDelete(ElementTemplate a) throws AxmrGenericException {
        for (TemplateAcl acl : a.getTemplateAcls()) {
            for (TemplateAclContainer c : acl.getContainers()) {
                tplAclContainerDAO.delete(c);
            }
            tplAclDAO.delete(acl);
        }
        elTplDAO.delete(a);
    }

    public AuditFile getOldVersion(Long attachId) {
        return aFileDAO.getById(attachId);

    }

    public void addTemplateAcl(Element el, ElementTemplate tpl, TemplatePolicy pol, List<String> users, List<String> groups) throws AxmrGenericException {
        TemplateAcl acl = new TemplateAcl();
        acl.setElementTemplate(tpl);
        acl.setPolicyValue(pol.toInt());
        acl.setPositionalAce(pol.toBinary());
        tplAclDAO.saveOrUpdate(acl);
        acl.setContainers(new LinkedList<TemplateAclContainer>());
        if (groups != null && groups.size() > 0) for (String group : groups) {
            TemplateAclContainer c = new TemplateAclContainer();
            c.setContainer(group);
            c.setAuthority(true);
            c.setAcl(acl);
            tplAclContainerDAO.saveOrUpdate(c);
            acl.getContainers().add(c);
        }
        if (users != null && users.size() > 0) for (String user : users) {
            TemplateAclContainer c = new TemplateAclContainer();
            c.setContainer(user);
            c.setAuthority(false);
            c.setAcl(acl);
            tplAclContainerDAO.saveOrUpdate(c);
            acl.getContainers().add(c);
        }
        tplAclDAO.saveOrUpdate(acl);
    }

    public void addTemplateAcl(IUser user, Long id, Long assocId, TemplatePolicy pol, List<String> users, List<String> groups) throws RestException {
        try {
            Element el = getElement(id);
            if (!el.getUserPolicy(user).isCanChangePermission()) throw new RestException("FORBIDDEN", txManager);
            ElementTemplate tpl = null;
            for (ElementTemplate tpl_ : el.getElementTemplates()) {
                if (tpl_.getId().equals(assocId)) tpl = tpl_;
            }
            if (tpl == null) throw new RestException("ElementTemplate not found", txManager);
            addTemplateAcl(el, tpl, pol, users, groups);
        } catch (AxmrGenericException ex) {
            throw new RestException(ex.getMessage(), txManager);
        }
    }

    public void deleteTemplateAcl(IUser user, Long id, Long assocId, Long aclId) throws RestException {
        try {
            Element el = getElement(id);
            if (!el.getUserPolicy(user).isCanChangePermission()) throw new RestException("FORBIDDEN", txManager);
            TemplateAcl acl = null;
            ElementTemplate tpl = null;
            for (ElementTemplate tpl_ : el.getElementTemplates()) {
                if (tpl_.getId().equals(assocId)) {
                    tpl = tpl_;
                    for (TemplateAcl acl1 : tpl_.getTemplateAcls()) {
                        if (acl1.getId().equals(aclId)) acl = acl1;
                    }
                }

            }
            if (acl == null) throw new RestException("ElementTemplate ACL not found", txManager);
            deleteTemplateAcl(el, tpl, acl);
        } catch (AxmrGenericException ex) {
            throw new RestException(ex.getMessage(), txManager);
        }
    }

    private void deleteTemplateAcl(Element el, ElementTemplate tpl, TemplateAcl acl) throws AxmrGenericException {
        for (TemplateAclContainer c : acl.getContainers()) tplAclContainerDAO.delete(c);
        tpl.getTemplateAcls().remove(acl);
        tplAclDAO.delete(acl);
        elTplDAO.saveOrUpdate(tpl);
    }


    public List<Element> getElementsByParent(IUser user, Long parentId) {
        DetachedCriteria c = getBrowsableElementsCriteria(user);
        Element parent = getElement(parentId);
        c.add(Restrictions.eq("parent", parent));
        c.addOrder(Order.asc("position"));
        return docDAO.getCriteriaList(c);
    }

    public List<CalendarEvent> getCalendarEvents(IUser user, Calendar start, Calendar end, Long idCalendar) {
        CalendarEntity c = calDAO.getById(idCalendar);
        return getCalendarEvents(user, start, end, c);
    }

    public List<CalendarEvent> getCalendarEvents(IUser user, Calendar start, Calendar end, CalendarEntity c) {
        List<ElementType> elTypes = new LinkedList<ElementType>();
        List<MetadataField> fields = new LinkedList<MetadataField>();
        fields.add(c.getStartDateField());
        if (c.getEndDateField() != null) fields.add(c.getEndDateField());
        DetachedCriteria baseSearch = getBrowsableElementsCriteria(user);
        baseSearch.createAlias("data", "data")
                .createAlias("data.values", "dataValues");
        baseSearch.add(Restrictions.eq("type", c.getElementType()));
        baseSearch.add(Restrictions.and(
                Restrictions.between("dataValues.date", start, end),
                Restrictions.in("data.field", fields)
        ));
        List<Element> els = docDAO.getCriteriaList(baseSearch);
        List<CalendarEvent> evs = new LinkedList<CalendarEvent>();
        for (Element el : els) {
            CalendarEvent evt = CalendarEvent.build(c, el);
            if (evt != null) evs.add(evt);
        }
        return evs;
    }

    public List<CalendarEvent> getAllCalendarEvents(IUser user, Calendar start, Calendar end) {
        Criteria crit = calDAO.getCriteria();
        List<CalendarEntity> cs = crit.list();
        List<CalendarEvent> evts = new LinkedList<CalendarEvent>();
        for (CalendarEntity c : cs) {
            List<CalendarEvent> evsPartial = getCalendarEvents(user, start, end, c);
            evts.addAll(evsPartial);
        }
        return evts;
    }

    public CalendarEntity getCalendar(Long id) {
        return calDAO.getById(id);
    }

    public List<Element> getElementsLimitByTypeId(IUser user, String typeId, int page, int limit, String orderBy, String orderType) {
        return getElementsLimitByTypeId(user, typeId, page, limit, orderBy, orderType, null);

    }


    public List<Element> getElementsLimitByTypeId(IUser user, String typeId, int page, int limit, String orderBy, String orderType, JqGridJSON result) {

        int start = (page - 1) * limit;
        int total;
        DetachedCriteria c = getBrowsableElementsCriteria(user);
        c.createAlias("type", "type");
        c.add(Restrictions.eq("type.typeId", typeId));
        //c.setMaxResults(rowPerPage);
        c.setProjection(Projections.countDistinct("id"));
        total = ((Long) docDAO.getCriteriaUniqueResult(c)).intValue();
        //it.cineca.siss.axmr3.log.Log.info(getClass(),"\n\n\n\n\nOrders: " + orderBy + " - " + orderType + "\n\n\n\n\n\n");
        if (!orderType.isEmpty() && !orderBy.isEmpty()) {
            if (orderBy.equals("createDt")) {
                if (orderType.equals("asc")) c.addOrder(Order.asc("creationDt"));
                if (orderType.equals("desc")) c.addOrder(Order.desc("creationDt"));
            } else if (orderBy.equals("updateDt")) {
                if (orderType.equals("asc")) c.addOrder(Order.asc("lastUpdateDt"));
                if (orderType.equals("desc")) c.addOrder(Order.desc("lastUpdateDt"));
            } else {

            }
        } else {
            c.addOrder(Order.desc("creationDt"));
        }
        if (result != null) {
            result.setPage(page);
            result.setRows(limit);
            result.setTotal(total);
        }
        return docDAO.getFixedResultSize(c, start, limit, total);
    }

    public List<Element> advancedSearch(String typeId, HashMap<String, Object> data) {
        return advancedSearch(null, typeId, data);
    }

    public List<Element> advancedSearch(IUser user, String typeId, HashMap<String, Object> data) {
        return docDAO.getCriteriaList(advancedSearchCriteria(user, typeId, data));
    }

    public List<Element> advancedSearch(IUser user, String typeId, HashMap<String, Object> data, int page, int limit, JqGridJSON result) {
        DetachedCriteria c = advancedSearchCriteria(user, typeId, data);
        int start = (page - 1) * limit;
        int total;
        c.setProjection(Projections.countDistinct("id"));
        total = ((Long) docDAO.getCriteriaUniqueResult(c)).intValue();
        if (result != null) {
            result.setPage(page);
            result.setRows(limit);
            result.setTotal(total);
        }
        return docDAO.getFixedResultSize(c, start, limit, total);
    }

    public Long advancedSearchCount(IUser user, String typeId, HashMap<String, Object> data) {
        DetachedCriteria c = advancedSearchCriteria(user, typeId, data);
        c.setProjection(Projections.countDistinct("id"));
        Long resultCount = (Long) docDAO.getCriteriaUniqueResult(c);
        return resultCount;
    }

    public Criterion templateEnabledCriterion(String templateName, String criteriaAlias) {
        return templateEnablingCheckCriterion(templateName, true, criteriaAlias);
    }

    public Criterion templateDisabledCriterion(String templateName, String criteriaAlias) {
        return templateEnablingCheckCriterion(templateName, false, criteriaAlias);
    }

    public Criterion templatesEnabledCriterion(String[] templateName, String criteriaAlias) {
        return templatesEnablingCheckCriterion(templateName, true, criteriaAlias);
    }

    public Criterion templatesDisabledCriterion(String[] templateName, String criteriaAlias) {
        return templatesEnablingCheckCriterion(templateName, false, criteriaAlias);
    }

    public Criterion templateEnablingCheckCriterion(String templateName, boolean enabled, String criteriaAlias) {
        DetachedCriteria subQuery1 = DetachedCriteria.forClass(Element.class, "sq");
        subQuery1.createAlias("sq.elementTemplates", "sqelementTemplates");
        subQuery1.createAlias("sq.elementTemplates.metadataTemplate", "sqmetadataTemplate");
        subQuery1.add(Restrictions.eq("sqmetadataTemplate.name", templateName).ignoreCase());
        subQuery1.add(Restrictions.eq("sqelementTemplates.enabled", enabled));
        subQuery1.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);
        subQuery1.setProjection(Projections.property("sq.id"));
        if (criteriaAlias != null && !criteriaAlias.isEmpty())
            subQuery1.add(Restrictions.eqProperty(criteriaAlias + ".id", "sq.id"));
        else subQuery1.add(Restrictions.eqProperty("id", "sq.id"));
        return Subqueries.exists(subQuery1);
    }

    public Criterion templatesEnablingCheckCriterion(String[] templatesName, boolean check, String criteriaAlias) {
        Criterion crit = null;
        for (int i = 0; i < ((String[]) templatesName).length; i++) {
            String templateName = ((String[]) templatesName)[i];
            if (crit == null) crit = templateEnablingCheckCriterion(templatesName[i], check, criteriaAlias);
            else {
                crit = Restrictions.and(crit, templateEnablingCheckCriterion(templatesName[i], check, criteriaAlias));
            }
        }
        return crit;
    }

    public Criterion metadataFieldSearchCriterion(String idEqField, String template, String fieldName, String filterType, Object value) {
        DetachedCriteria subQuery = DetachedCriteria.forClass(Element.class, "sq");
        MetadataTemplate t = MetadataTemplate.getTemplateByName(templateDAO, template);
        if (t == null) {
            it.cineca.siss.axmr3.log.Log.warn(getClass(), "Non trovo il template " + template);
            return null;
        } else {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Trovato il template dal nome " + template + " con id:" + t.getId());
        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Sto per cercare il campo " + fieldName);
        MetadataField f = t.byFieldName(fieldName);
        if (f == null) {
            it.cineca.siss.axmr3.log.Log.warn(getClass(), "Non trovo il campo " + fieldName);
            return null;
        } else {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Trovato campo " + fieldName + " con id: " + f.getId());
        }
        MetadataFieldType type = f.getType();
        Criterion fieldNameCrit = Restrictions.eq("sqfield.name", fieldName);
        Criterion templateNameCrit = Restrictions.eq("sqtemplate.name", template);

        Criterion searchCrit = null;
        String fieldProperty = null;
        List<Object> valuesIn = new LinkedList<Object>();
        SearchType sType = SearchType.valueOfIgnoreCase(filterType);
        if (type.equals(MetadataFieldType.TEXTBOX)) {
            fieldProperty = "sqdataValues.textValue";
        }
        if (type.equals(MetadataFieldType.TEXTAREA) || type.equals(MetadataFieldType.RICHTEXT)) {
            fieldProperty = "sqdataValues.longTextValue";
        }
        if (type.equals(MetadataFieldType.CHECKBOX) || type.equals(MetadataFieldType.RADIO) || type.equals(MetadataFieldType.SELECT) || type.equals(MetadataFieldType.EXT_DICTIONARY)) {
            fieldProperty = "sqdataValues.code";
        }
        if (type.equals(MetadataFieldType.DATE)) {
            try {
                DateFormat df = new SimpleDateFormat("dd/MM/yyyy");
                Date parsed = null;
                fieldProperty = "sqdataValues.date";
                if (value instanceof String) {
                    parsed = df.parse(value.toString());
                    value = Calendar.getInstance();
                    ((Calendar) value).setTime(parsed);
                }
                if (value instanceof String[]) {
                    for (int i = 0; i < ((String[]) value).length; i++) {
                        parsed = df.parse(((String[]) value)[i].toString());
                        Calendar v = Calendar.getInstance();
                        ((Calendar) v).setTime(parsed);
                        valuesIn.add(v);
                    }
                }
            } catch (java.text.ParseException e) {
                value = null;
                log.error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
            }
        } else {
            if (value instanceof String[]) {
                for (int i = 0; i < ((String[]) value).length; i++) {
                    valuesIn.add(((String[]) value)[i]);
                }
            }
        }
        if (type.equals(MetadataFieldType.ELEMENT_LINK)) {
            fieldProperty = "sqdataValues.element_link";
            if (value instanceof String) {
                value = this.getElement(Long.parseLong((String) value));
            }
            if (value instanceof String[]) {
                for (int i = 0; i < ((String[]) value).length; i++) {
                    valuesIn.add(this.getElement(Long.parseLong(((String[]) value)[i])));
                }
            }
        }
        if (value != null) {
            switch (sType) {
                case EQ:
                    if (type.equals(MetadataFieldType.DATE)) {
                        searchCrit = Restrictions.eq(fieldProperty, (Calendar) value);
                    } else {
                        if (type.equals(MetadataFieldType.ELEMENT_LINK)) {
                            searchCrit = Restrictions.like(fieldProperty, (Element) value);
                        } else searchCrit = Restrictions.like(fieldProperty, (String) value);
                    }
                    break;
                case NE:
                    if (type.equals(MetadataFieldType.DATE)) {
                        searchCrit = Restrictions.ne(fieldProperty, (Calendar) value);
                    } else {
                        if (type.equals(MetadataFieldType.ELEMENT_LINK)) {
                            searchCrit = Restrictions.ne(fieldProperty, (Element) value);
                        } else searchCrit = Restrictions.ne(fieldProperty, (String) value);
                    }
                    break;
                case STARTSWITH:
                    searchCrit = Restrictions.like(fieldProperty, value.toString() + "%").ignoreCase();
                    break;
                case ENDSWITH:
                    searchCrit = Restrictions.like(fieldProperty, "%" + value.toString()).ignoreCase();
                    break;
                case LIKE:
                    searchCrit = Restrictions.ilike(fieldProperty, value.toString(), MatchMode.ANYWHERE);
                    break;
                case LT:
                    searchCrit = Restrictions.lt(fieldProperty, value);
                    break;
                case LTEQ:
                    if (value instanceof Calendar) {
                        ((Calendar) value).add(Calendar.DATE, 1);
                    }
                    searchCrit = Restrictions.le(fieldProperty, value);
                    break;
                case GT:
                    searchCrit = Restrictions.gt(fieldProperty, value);
                    break;
                case GTEQ:
                    searchCrit = Restrictions.ge(fieldProperty, value);
                    break;
                case ISNULL:
                    searchCrit = Restrictions.isNull(fieldProperty);
                    break;
                case ISNOTNULL:
                    searchCrit = Restrictions.isNotNull(fieldProperty);
                    break;
                case IN:
                    searchCrit = Restrictions.in(fieldProperty, valuesIn);
                    break;
            }
            it.cineca.siss.axmr3.log.Log.info(getClass(), "Assemblo query");
            subQuery.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);
            subQuery.createAlias("sq.data", "sqdata");
            subQuery.createAlias("sq.data.values", "sqdataValues");
            subQuery.createAlias("sq.data.template", "sqtemplate");
            subQuery.createAlias("sq.data.field", "sqfield");
            subQuery.add(fieldNameCrit);
            subQuery.add(templateNameCrit);
            subQuery.add(searchCrit);
            subQuery.setProjection(Projections.property("sq.id"));
            subQuery.add(Restrictions.eqProperty("root.id", idEqField));
            return Subqueries.exists(subQuery);
        } else {
            return null;
        }
    }

    public Criterion buildCriterion(SearchType sType, String fieldProperty, Object value, Class propertyClass) {
        Criterion searchCrit = null;
        switch (sType) {
            case EQ:
                if (propertyClass.equals(Calendar.class)) {
                    searchCrit = Restrictions.eq(fieldProperty, (Calendar) value);
                } else {
                    if (propertyClass.equals(Element.class)) {
                        searchCrit = Restrictions.like(fieldProperty, (Element) value);
                    } else {
                        searchCrit = Restrictions.like(fieldProperty, (String) value);
                    }
                }
                /*
                if (type.equals(MetadataFieldType.DATE)) {
                    searchCrit = Restrictions.eq(fieldProperty, (Calendar) value);
                } else {
                    if (type.equals(MetadataFieldType.ELEMENT_LINK)) {
                        searchCrit = Restrictions.like(fieldProperty, (Element) value);
                    } else searchCrit = Restrictions.like(fieldProperty, (String) value);
                }
                */
                break;
            case NE:
                if (propertyClass.equals(Calendar.class)) {
                    searchCrit = Restrictions.ne(fieldProperty, (Calendar) value);
                } else {
                    if (propertyClass.equals(Element.class)) {
                        searchCrit = Restrictions.ne(fieldProperty, (Element) value);
                    } else {
                        searchCrit = Restrictions.ne(fieldProperty, (String) value);
                    }
                }
                /*
                if (type.equals(MetadataFieldType.DATE)) {
                    searchCrit = Restrictions.ne(fieldProperty, (Calendar) value);
                } else {
                    if (type.equals(MetadataFieldType.ELEMENT_LINK)) {
                        searchCrit = Restrictions.ne(fieldProperty, (Element) value);
                    } else searchCrit = Restrictions.ne(fieldProperty, (String) value);
                }
                */
                break;
            case STARTSWITH:
                searchCrit = Restrictions.like(fieldProperty, value.toString() + "%").ignoreCase();
                break;
            case ENDSWITH:
                searchCrit = Restrictions.like(fieldProperty, "%" + value.toString()).ignoreCase();
                break;
            case LIKE:
                searchCrit = Restrictions.ilike(fieldProperty, value.toString(), MatchMode.ANYWHERE);
                break;
            case LT:
                searchCrit = Restrictions.lt(fieldProperty, value);
                break;
            case LTEQ:
                if (value instanceof Calendar) {
                    ((Calendar) value).add(Calendar.DATE, 1);
                }
                searchCrit = Restrictions.le(fieldProperty, value);
                break;
            case GT:
                searchCrit = Restrictions.gt(fieldProperty, value);
                break;
            case GTEQ:
                searchCrit = Restrictions.ge(fieldProperty, value);
                break;
            case ISNULL:
                searchCrit = Restrictions.isNull(fieldProperty);
                break;
            case ISNOTNULL:
                searchCrit = Restrictions.isNotNull(fieldProperty);
                break;
            case IN:
                searchCrit = Restrictions.in(fieldProperty, (Collection) value);
                break;
        }
        return searchCrit;
    }


    public DetachedCriteria advancedSearchCriteria(IUser user, String typeId, HashMap<String, Object> data) {
        DetachedCriteria c;
        boolean standardOrder = true;
        Object value = null;
        String template = "";
        String fieldName = "";
        String filterType = "";
        String key = "";
        String idEqField = "sq.id";
        String[] searchFilterSplitted = null;
        if (data.containsKey("_")) data.remove("_");
        if (user == null) {
            c = getAllElementsCriteria("root");
        } else {
            c = getViewableElementsCriteria(user, "root");
        }
        Criteria ctype = docTypeDAO.getCriteria();
        ctype.add(Restrictions.eq("typeId", typeId));
        ElementType etype = (ElementType) ctype.uniqueResult();
        if (data.containsKey("sidx") && !data.get("sidx").toString().isEmpty()) {
            standardOrder = false;
            key = data.get("sidx").toString();
            searchFilterSplitted = key.split("_");
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Sto per ordinare per " + key + " split " + String.valueOf(searchFilterSplitted.length));
            if (searchFilterSplitted.length >= 2) {
                template = searchFilterSplitted[0];
                fieldName = searchFilterSplitted[1];

            }
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Sto per cercare il template dal nome " + template);
            MetadataTemplate t = MetadataTemplate.getTemplateByName(templateDAO, template);
            if (t == null) {
                it.cineca.siss.axmr3.log.Log.warn(getClass(), "Non trovo il template " + template);
                standardOrder = true;
            } else {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Trovato il template dal nome " + template + " con id:" + t.getId());
                String fieldProperty = "";
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Sto per cercare il campo " + fieldName);
                MetadataField f = t.byFieldName(fieldName);
                if (f == null) {
                    it.cineca.siss.axmr3.log.Log.warn(getClass(), "Non trovo il campo " + fieldName);
                    standardOrder = true;
                } else {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "Trovato campo " + fieldName + " con id: " + f.getId());

                    MetadataFieldType type = f.getType();
                    Criterion fieldNameCrit = Restrictions.eq("sqfield.name", fieldName);
                    Criterion templateNameCrit = Restrictions.eq("sqtemplate.name", template);

                    Criterion searchCrit = null;

                    List<Object> valuesIn = new LinkedList<Object>();

                    if (type.equals(MetadataFieldType.TEXTBOX)) {
                        fieldProperty = "sqdataValuesOrd.textValue";
                    }
                    if (type.equals(MetadataFieldType.TEXTAREA) || type.equals(MetadataFieldType.RICHTEXT)) {
                        fieldProperty = "sqdataValuesOrd.longTextValue";
                    }
                    if (type.equals(MetadataFieldType.CHECKBOX) || type.equals(MetadataFieldType.RADIO) || type.equals(MetadataFieldType.SELECT) || type.equals(MetadataFieldType.EXT_DICTIONARY)) {
                        fieldProperty = "sqdataValuesOrd.code";
                    }
                    if (type.equals(MetadataFieldType.DATE)) {

                        DateFormat df = new SimpleDateFormat("dd/MM/yyyy");
                        Date parsed = null;
                        fieldProperty = "sqdataValuesOrd.date";

                    }
                    if (type.equals(MetadataFieldType.ELEMENT_LINK)) {
                        fieldProperty = "sqdataValuesOrd.element_link";

                    }


                    it.cineca.siss.axmr3.log.Log.info(getClass(), "Assemblo query");

                    c.createAlias("root.data", "sqdataOrd");
                    c.createAlias("sqdataOrd.values", "sqdataValuesOrd");
                    c.createAlias("sqdataOrd.template", "sqtemplateOrd");
                    c.createAlias("sqdataOrd.field", "sqfieldOrd");
                    //c.createAlias(fieldProperty, data.get("sidx").toString());
                    c.add(Restrictions.eq("sqfieldOrd.name", fieldName));
                    c.add(Restrictions.eq("sqtemplateOrd.name", template));
                }
                if (data.containsKey("sord") && data.get("sord").equals("asc")) {
                    c.addOrder(Order.asc(fieldProperty));
                } else {
                    c.addOrder(Order.desc(fieldProperty));
                }
            }
        }

        if (data.containsKey("sidx2") && !data.get("sidx2").toString().isEmpty()) {
            standardOrder = false;
            key = data.get("sidx2").toString();
            searchFilterSplitted = key.split("_");
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Sto per ordinare per " + key + " split " + String.valueOf(searchFilterSplitted.length));
            if (searchFilterSplitted.length >= 2) {
                template = searchFilterSplitted[0];
                fieldName = searchFilterSplitted[1];

            }
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Sto per cercare il template dal nome " + template);
            MetadataTemplate t = MetadataTemplate.getTemplateByName(templateDAO, template);
            if (t == null) {
                it.cineca.siss.axmr3.log.Log.warn(getClass(), "Non trovo il template " + template);
                standardOrder = true;
            } else {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Trovato il template dal nome " + template + " con id:" + t.getId());
                String fieldProperty = "";
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Sto per cercare il campo " + fieldName);
                MetadataField f = t.byFieldName(fieldName);
                if (f == null) {
                    it.cineca.siss.axmr3.log.Log.warn(getClass(), "Non trovo il campo " + fieldName);
                    standardOrder = true;
                } else {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "Trovato campo " + fieldName + " con id: " + f.getId());

                    MetadataFieldType type = f.getType();
                    Criterion fieldNameCrit = Restrictions.eq("sqfield.name", fieldName);
                    Criterion templateNameCrit = Restrictions.eq("sqtemplate.name", template);

                    Criterion searchCrit = null;

                    List<Object> valuesIn = new LinkedList<Object>();

                    if (type.equals(MetadataFieldType.TEXTBOX)) {
                        fieldProperty = "sqdataValuesOrd2.textValue";
                    }
                    if (type.equals(MetadataFieldType.TEXTAREA) || type.equals(MetadataFieldType.RICHTEXT)) {
                        fieldProperty = "sqdataValuesOrd2.longTextValue";
                    }
                    if (type.equals(MetadataFieldType.CHECKBOX) || type.equals(MetadataFieldType.RADIO) || type.equals(MetadataFieldType.SELECT) || type.equals(MetadataFieldType.EXT_DICTIONARY)) {
                        fieldProperty = "sqdataValuesOrd2.code";
                    }
                    if (type.equals(MetadataFieldType.DATE)) {

                        DateFormat df = new SimpleDateFormat("dd/MM/yyyy");
                        Date parsed = null;
                        fieldProperty = "sqdataValuesOrd2.date";

                    }
                    if (type.equals(MetadataFieldType.ELEMENT_LINK)) {
                        fieldProperty = "sqdataValuesOrd2.element_link";

                    }


                    it.cineca.siss.axmr3.log.Log.info(getClass(), "Assemblo query");

                    c.createAlias("root.data", "sqdataOrd2");
                    c.createAlias("sqdataOrd2.values", "sqdataValuesOrd2");
                    c.createAlias("sqdataOrd2.template", "sqtemplateOrd2");
                    c.createAlias("sqdataOrd2.field", "sqfieldOrd2");
                    //c.createAlias(fieldProperty, data.get("sidx").toString());
                    c.add(Restrictions.eq("sqfieldOrd2.name", fieldName));
                    c.add(Restrictions.eq("sqtemplateOrd2.name", template));
                }
                if (data.containsKey("sord2") && data.get("sord2").equals("asc")) {
                    c.addOrder(Order.asc(fieldProperty));
                } else {
                    c.addOrder(Order.desc(fieldProperty));
                }
            }
        }


        if (standardOrder) {
            c.addOrder(Order.desc("root.creationDt"));
        }
        data.remove("sidx");
        data.remove("sord");
        data.remove("sidx2");
        data.remove("sord2");

        Iterator<String> keys = data.keySet().iterator();


        while (keys.hasNext()) {
            key = keys.next();
            value = data.get(key);
            it.cineca.siss.axmr3.log.Log.info(getClass(), value.getClass().getSimpleName());
            if ((value instanceof String) && ((String) value).isEmpty()) continue;
            if ((value instanceof String[]) && ((String[]) value).length == 0) continue;
            searchFilterSplitted = key.split("_");

            DetachedCriteria subQuery = DetachedCriteria.forClass(Element.class, "sq");
            if (searchFilterSplitted.length < 3) {
                if (key.equals("obj_enabledTemplate")) {
                    if (value instanceof String) {
                        c.add(templateEnabledCriterion((String) value, c.getAlias()));
                        /*
                        DetachedCriteria subQuery1 = DetachedCriteria.forClass(Element.class, "sq");
                        subQuery1.createAlias("sq.elementTemplates", "sqelementTemplates");
                        subQuery1.createAlias("sq.elementTemplates.metadataTemplate", "sqmetadataTemplate");
                        subQuery1.add(Restrictions.eq("sqmetadataTemplate.name", value).ignoreCase());
                        subQuery1.add(Restrictions.eq("sqelementTemplates.enabled", true));
                        subQuery1.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);
                        subQuery1.setProjection(Projections.property("sq.id"));
                        subQuery1.add(Restrictions.eqProperty("root.id", idEqField));
                        c.add(Subqueries.exists(subQuery1));
                        */
                    }
                    if (value instanceof String[]) {
                        c.add(templatesEnabledCriterion((String[]) value, c.getAlias()));
                        /*
                        for (int i = 0; i < ((String[]) value).length; i++) {
                            String templateName = ((String[]) value)[i];
                            DetachedCriteria subQuery1 = DetachedCriteria.forClass(Element.class, "sq");
                            subQuery1.createAlias("sq.elementTemplates", "sqelementTemplates");
                            subQuery1.createAlias("sq.elementTemplates.metadataTemplate", "sqmetadataTemplate");
                            subQuery1.add(Restrictions.eq("sqmetadataTemplate.name", templateName).ignoreCase());
                            subQuery1.add(Restrictions.eq("sqelementTemplates.enabled", true));
                            subQuery1.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);
                            subQuery1.setProjection(Projections.property("sq.id"));
                            subQuery1.add(Restrictions.eqProperty("root.id", idEqField));
                            c.add(Subqueries.exists(subQuery1));
                        }
                        */
                    }
                }
                if (key.equals("obj_disabledTemplate")) {
                    if (value instanceof String) {
                        c.add(templateDisabledCriterion((String) value, c.getAlias()));
                        /*
                        DetachedCriteria subQuery1 = DetachedCriteria.forClass(Element.class, "sq");
                        subQuery1.createAlias("sq.elementTemplates", "sqelementTemplates");
                        subQuery1.createAlias("sq.elementTemplates.metadataTemplate", "sqmetadataTemplate");
                        subQuery1.add(Restrictions.eq("sqmetadataTemplate.name", value).ignoreCase());
                        subQuery1.add(Restrictions.eq("sqelementTemplates.enabled", false));
                        subQuery1.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);
                        subQuery1.setProjection(Projections.property("sq.id"));
                        subQuery1.add(Restrictions.eqProperty("root.id", idEqField));
                        c.add(Subqueries.exists(subQuery1));
                        */
                    }
                    if (value instanceof String[]) {
                        c.add(templatesDisabledCriterion((String[]) value, c.getAlias()));
                        /*
                        for (int i = 0; i < ((String[]) value).length; i++) {
                            String templateName = ((String[]) value)[i];
                            DetachedCriteria subQuery1 = DetachedCriteria.forClass(Element.class, "sq");
                            subQuery1.createAlias("sq.elementTemplates", "sqelementTemplates");
                            subQuery1.createAlias("sq.elementTemplates.metadataTemplate", "sqmetadataTemplate");
                            subQuery1.add(Restrictions.eq("sqmetadataTemplate.name", templateName).ignoreCase());
                            subQuery1.add(Restrictions.eq("sqelementTemplates.enabled", false));
                            subQuery1.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);
                            subQuery1.setProjection(Projections.property("sq.id"));
                            subQuery1.add(Restrictions.eqProperty("root.id", idEqField));
                            c.add(Subqueries.exists(subQuery1));
                        }
                        */
                    }
                }
                continue;
            }

            boolean parentSearch = false;
            String parentAlias = "";
            if (searchFilterSplitted.length > 3) {
                parentSearch = true;
                parentAlias = "";
                for (int i = 0; i < searchFilterSplitted.length; i++) {
                    if (i < searchFilterSplitted.length - 3) {
                        if (parentAlias.isEmpty()) subQuery.createAlias("sq.parent", "sqParent_" + i);
                        else subQuery.createAlias(parentAlias + ".parent", "sqParent_" + i);
                        parentAlias = "sqParent_" + i;
                    }
                    if (i == searchFilterSplitted.length - 3) template = searchFilterSplitted[i];
                    if (i == searchFilterSplitted.length - 2) fieldName = searchFilterSplitted[i];
                    if (i == searchFilterSplitted.length - 1) filterType = searchFilterSplitted[i];
                }
                idEqField = parentAlias + ".id";
            } else {
                template = searchFilterSplitted[0];
                fieldName = searchFilterSplitted[1];
                filterType = searchFilterSplitted[2];
            }
            it.cineca.siss.axmr3.log.Log.info(getClass(), "idEqField:" + idEqField);
            if (template.equals("obj")) {
                String fieldProperty = "";
                Object fValue = null;
                List<Object> valuesIn = new LinkedList<Object>();
                if (fieldName.equals("creationDt")) {
                    fieldProperty = "creationDt";
                    try {
                        DateFormat df = new SimpleDateFormat("dd/MM/yyyy");
                        Date parsed = null;
                        if (value instanceof String) {
                            parsed = df.parse(value.toString());
                            fValue = Calendar.getInstance();
                            ((Calendar) fValue).setTime(parsed);
                        }
                        if (value instanceof String[]) {
                            for (int i = 0; i < ((String[]) value).length; i++) {
                                parsed = df.parse(((String[]) value)[i].toString());
                                Calendar v = Calendar.getInstance();
                                ((Calendar) v).setTime(parsed);
                                valuesIn.add(v);
                            }
                        }
                    } catch (java.text.ParseException e) {
                        fValue = null;
                        log.error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
                    }
                }
                if (fieldName.equals("lastUpdateDt")) {
                    fieldProperty = "lastUpdateDt";
                }
                if (fieldName.equals("createUser")) {
                    fieldProperty = "createUser";
                    if (value instanceof String) {
                        fValue = (String) value;
                    }
                    if (value instanceof String[]) {
                        for (int i = 0; i < ((String[]) value).length; i++) {
                            valuesIn.add(((String[]) value)[i]);
                        }
                    }
                }
                if (fieldName.equals("lastUpdateUser")) {
                    fieldProperty = "lastUpdateUser";
                    if (value instanceof String) {
                        fValue = (String) value;
                    }
                    if (value instanceof String[]) {
                        for (int i = 0; i < ((String[]) value).length; i++) {
                            valuesIn.add(((String[]) value)[i]);
                        }
                    }
                }
                if (fieldName.equals("position")) {
                    it.cineca.siss.axmr3.log.Log.info(getClass(), "Devo controllare la position");
                    fieldProperty = "position";
                    if (value instanceof String) {
                        it.cineca.siss.axmr3.log.Log.info(getClass(), "Value è un valore singolo");
                        fValue = Long.parseLong((String) value);
                    }
                    if (value instanceof String[]) {
                        it.cineca.siss.axmr3.log.Log.info(getClass(), "Value è un valore multiplo");
                        for (int i = 0; i < ((String[]) value).length; i++) {
                            valuesIn.add(Long.parseLong(((String[]) value)[i]));
                        }
                    }
                }
                if (fieldName.equals("id")) {
                    it.cineca.siss.axmr3.log.Log.info(getClass(), "Devo controllare l'ID");
                    fieldProperty = "id";
                    if (value instanceof String) {
                        it.cineca.siss.axmr3.log.Log.info(getClass(), "Value è un valore singolo");
                        fValue = Long.parseLong((String) value);
                    }
                    if (value instanceof String[]) {
                        it.cineca.siss.axmr3.log.Log.info(getClass(), "Value è un valore multiplo");
                        for (int i = 0; i < ((String[]) value).length; i++) {
                            valuesIn.add(Long.parseLong(((String[]) value)[i]));
                        }
                    }
                }
                if (parentSearch) fieldProperty = parentAlias + "." + fieldProperty;
                SearchType sType = SearchType.valueOfIgnoreCase(filterType);
                Criterion searchCrit = null;
                it.cineca.siss.axmr3.log.Log.info(getClass(), "\n\n\n\n Sto per costruire la clausola per il campo " + fieldProperty + " " + filterType);
                if (fValue != null || valuesIn.size() > 0) {
                    switch (sType) {
                        case EQ:
                            searchCrit = Restrictions.eq(fieldProperty, fValue);
                            break;
                        case NE:
                            searchCrit = Restrictions.ne(fieldProperty, fValue);
                            break;
                        case STARTSWITH:
                            if (fValue != null) {
                                searchCrit = Restrictions.like(fieldProperty, fValue.toString() + "%").ignoreCase();
                            }
                            break;
                        case ENDSWITH:
                            if (fValue != null) {
                                searchCrit = Restrictions.like(fieldProperty, "%" + fValue.toString()).ignoreCase();
                            }
                            break;
                        case LIKE:
                            if (fValue != null) {
                                searchCrit = Restrictions.ilike(fieldProperty, fValue.toString(), MatchMode.ANYWHERE);
                            }
                            break;
                        case LT:
                            searchCrit = Restrictions.lt(fieldProperty, fValue);
                            break;
                        case LTEQ:
                            if (fValue instanceof Calendar) {
                                ((Calendar) fValue).add(Calendar.DATE, 1);
                            }
                            searchCrit = Restrictions.le(fieldProperty, fValue);
                            break;
                        case GT:
                            searchCrit = Restrictions.gt(fieldProperty, fValue);
                            break;
                        case GTEQ:
                            searchCrit = Restrictions.ge(fieldProperty, fValue);
                            break;
                        case ISNULL:
                            searchCrit = Restrictions.isNull(fieldProperty);
                            break;
                        case ISNOTNULL:
                            searchCrit = Restrictions.isNotNull(fieldProperty);
                            break;
                        case IN:
                            searchCrit = Restrictions.in(fieldProperty, valuesIn);
                            break;
                    }
                    if (!parentSearch) {
                        it.cineca.siss.axmr3.log.Log.info(getClass(), "\n\n\n\n Applico la clausola al criteria base \n\n\n\n");
                        c.add(searchCrit);
                    } else {
                        subQuery.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);
                        subQuery.add(searchCrit);
                        subQuery.setProjection(Projections.property("sq.id"));
                        subQuery.add(Restrictions.eqProperty("root.id", "sq.id"));
                        it.cineca.siss.axmr3.log.Log.info(getClass(), "\n\n\n\n Applico la clausola tramite subcriteria base \n\n\n\n");
                        //c.add(Subqueries.propertyIn("root.id",subQuery));
                        c.add(Subqueries.exists(subQuery));
                    }
                }
            } else {
                it.cineca.siss.axmr3.log.Log.info(getClass(), "Sto per cercare il template dal nome " + template);
                MetadataTemplate t = MetadataTemplate.getTemplateByName(templateDAO, template);
                if (t == null) {
                    it.cineca.siss.axmr3.log.Log.info(getClass(), "Non trovo il template " + template);
                    continue;
                } else {
                    it.cineca.siss.axmr3.log.Log.info(getClass(), "Trovato il template dal nome " + template + " con id:" + t.getId());
                }
                it.cineca.siss.axmr3.log.Log.info(getClass(), "Sto per cercare il campo " + fieldName);
                MetadataField f = t.byFieldName(fieldName);
                if (f == null) {
                    it.cineca.siss.axmr3.log.Log.info(getClass(), "Non trovo il campo " + fieldName);
                    continue;
                } else {
                    it.cineca.siss.axmr3.log.Log.info(getClass(), "Trovato campo " + fieldName + " con id: " + f.getId());
                }
                MetadataFieldType type = f.getType();
                Criterion fieldNameCrit = Restrictions.eq("sqfield.name", fieldName);
                Criterion templateNameCrit = Restrictions.eq("sqtemplate.name", template);

                Criterion searchCrit = null;
                String fieldProperty = null;
                List<Object> valuesIn = new LinkedList<Object>();
                SearchType sType = SearchType.valueOfIgnoreCase(filterType);
                if (type.equals(MetadataFieldType.TEXTBOX)) {
                    fieldProperty = "sqdataValues.textValue";
                }
                if (type.equals(MetadataFieldType.TEXTAREA) || type.equals(MetadataFieldType.RICHTEXT)) {
                    fieldProperty = "sqdataValues.longTextValue";
                }
                if (type.equals(MetadataFieldType.CHECKBOX) || type.equals(MetadataFieldType.RADIO) || type.equals(MetadataFieldType.SELECT) || type.equals(MetadataFieldType.EXT_DICTIONARY)) {
                    fieldProperty = "sqdataValues.code";
                }
                if (type.equals(MetadataFieldType.DATE)) {
                    try {
                        DateFormat df = new SimpleDateFormat("dd/MM/yyyy");
                        Date parsed = null;
                        fieldProperty = "sqdataValues.date";
                        if (value instanceof String) {
                            parsed = df.parse(value.toString());
                            value = Calendar.getInstance();
                            ((Calendar) value).setTime(parsed);
                        }
                        if (value instanceof String[]) {
                            for (int i = 0; i < ((String[]) value).length; i++) {
                                parsed = df.parse(((String[]) value)[i].toString());
                                Calendar v = Calendar.getInstance();
                                ((Calendar) v).setTime(parsed);
                                valuesIn.add(v);
                            }
                        }
                    } catch (java.text.ParseException e) {
                        value = null;
                        log.error(e.getMessage(), e);  //To change body of catch statement use File | Settings | File Templates.
                    }
                } else {
                    if (value instanceof String[]) {
                        for (int i = 0; i < ((String[]) value).length; i++) {
                            valuesIn.add(((String[]) value)[i]);
                        }
                    }
                }
                if (type.equals(MetadataFieldType.ELEMENT_LINK)) {
                    fieldProperty = "sqdataValues.element_link";
                    if (value instanceof String) {
                        value = this.getElement(Long.parseLong((String) value));
                    }
                    if (value instanceof String[]) {
                        for (int i = 0; i < ((String[]) value).length; i++) {
                            valuesIn.add(this.getElement(Long.parseLong(((String[]) value)[i])));
                        }
                    }
                }
                if (value != null) {
                    switch (sType) {
                        case EQ:
                            if (type.equals(MetadataFieldType.DATE)) {
                                searchCrit = Restrictions.eq(fieldProperty, (Calendar) value);
                            } else {
                                if (type.equals(MetadataFieldType.ELEMENT_LINK)) {
                                    searchCrit = Restrictions.like(fieldProperty, (Element) value);
                                } else searchCrit = Restrictions.like(fieldProperty, (String) value);
                            }
                            break;
                        case NE:
                            if (type.equals(MetadataFieldType.DATE)) {
                                searchCrit = Restrictions.ne(fieldProperty, (Calendar) value);
                            } else {
                                if (type.equals(MetadataFieldType.ELEMENT_LINK)) {
                                    searchCrit = Restrictions.ne(fieldProperty, (Element) value);
                                } else searchCrit = Restrictions.ne(fieldProperty, (String) value);
                            }
                            break;
                        case STARTSWITH:
                            searchCrit = Restrictions.like(fieldProperty, value.toString() + "%").ignoreCase();
                            break;
                        case ENDSWITH:
                            searchCrit = Restrictions.like(fieldProperty, "%" + value.toString()).ignoreCase();
                            break;
                        case LIKE:
                            searchCrit = Restrictions.ilike(fieldProperty, value.toString(), MatchMode.ANYWHERE);
                            break;
                        case LT:
                            searchCrit = Restrictions.lt(fieldProperty, value);
                            break;
                        case LTEQ:
                            if (value instanceof Calendar) {
                                ((Calendar) value).add(Calendar.DATE, 1);
                            }
                            searchCrit = Restrictions.le(fieldProperty, value);
                            break;
                        case GT:
                            searchCrit = Restrictions.gt(fieldProperty, value);
                            break;
                        case GTEQ:
                            searchCrit = Restrictions.ge(fieldProperty, value);
                            break;
                        case ISNULL:
                            searchCrit = Restrictions.isNull(fieldProperty);
                            break;
                        case ISNOTNULL:
                            searchCrit = Restrictions.isNotNull(fieldProperty);
                            break;
                        case IN:
                            searchCrit = Restrictions.in(fieldProperty, valuesIn);
                            break;
                    }
                    it.cineca.siss.axmr3.log.Log.info(getClass(), "Assemblo query");
                    subQuery.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);
                    subQuery.createAlias("sq.data", "sqdata");
                    subQuery.createAlias("sq.data.values", "sqdataValues");
                    subQuery.createAlias("sq.data.template", "sqtemplate");
                    subQuery.createAlias("sq.data.field", "sqfield");
                    subQuery.add(fieldNameCrit);
                    subQuery.add(templateNameCrit);
                    subQuery.add(searchCrit);
                    subQuery.setProjection(Projections.property("sq.id"));
                    subQuery.add(Restrictions.eqProperty("root.id", idEqField));
                    c.add(Subqueries.exists(subQuery));
                }
            }
        }
        c.add(Restrictions.eq("root.type", etype));

        it.cineca.siss.axmr3.log.Log.info(getClass(), " \n\n\n\n\n\n ---------------------- \n\n\n\n\n\n");
        return c;
    }

    public List<Element> getReferralCascade(Long elemntId) {
        DetachedCriteria c = getAllElementsCriteria("root");
        c.createAlias("root.data", "sqdata");
        c.createAlias("root.data.values", "sqdataValues");
        c.createAlias("root.data.template", "sqtemplate");
        c.createAlias("root.data.field", "sqfield");
        c.add(Restrictions.eq("root.deleted", false));
        c.add(Restrictions.eq("sqdataValues.element_link", elemntId));
        c.add(Restrictions.eq("sqfield.cascadeDelete", true));
        it.cineca.siss.axmr3.log.Log.info(getClass(), " \n\n\n\n\n\n ---------------------- \n\n\n\n\n\n");
        return docDAO.getCriteriaList(c);
    }


    public ElementType getDocDefinitionByName(String docTypeIdString) {
        Criteria c = docTypeDAO.getCriteria();
        c.add(Restrictions.eq("typeId", docTypeIdString).ignoreCase());
        return (ElementType) c.uniqueResult();
    }

    public String getBaseNameOra(MetadataTemplate template, MetadataField field) {
        if (field.getBaseNameOra() != null && !field.getBaseNameOra().isEmpty()) {
            return field.getBaseNameOra().toUpperCase();
        }
        String baseName = template.getName() + "_" + field.getName();
        baseName = baseName.replaceAll(" ", "");
        baseName = baseName.replaceAll("-", "");
        baseName = baseName.toLowerCase();
        if (baseName.length() > 28) {
            baseName = baseName.replaceAll("_", "");
        }
        if (!baseNameOraStrategy.equalsIgnoreCase("NOVOCALI")) {
            if (baseName.length() > 28) {
                baseName = baseName.replaceAll("a", "");
                baseName = baseName.replaceAll("e", "");
                baseName = baseName.replaceAll("i", "");
                baseName = baseName.replaceAll("o", "");
                baseName = baseName.replaceAll("u", "");
            }
        }
        if (baseName.length() > 28) {
            baseName = "T" + template.getId() + "_" + "F" + field.getId();
        }
        return baseName.toUpperCase();
    }

    public void persistObjects(String objectType, String tableName) throws RestException {
        tableName = tableName.toUpperCase();
        boolean updating = false;
        log.info("Esportazione " + objectType + " in corso ...");
        it.cineca.siss.axmr3.log.Log.info(getClass(), "Esportazione " + objectType + " in corso ...");
        try {
            String queryString = "select 1 from USER_TABLES where table_name ='" + tableName + "'";
            SQLQuery sqlQUery = docTypeDAO.getSession().createSQLQuery(queryString);
            List res = sqlQUery.list();
            if (!res.isEmpty()) {
                String queryString2 = "select 1 from user_tab_columns where table_name ='" + tableName + "' and column_name='LAST_REFRESH'";
                SQLQuery sqlQUery2 = docTypeDAO.getSession().createSQLQuery(queryString2);
                List res2 = sqlQUery2.list();
                if (res2.isEmpty()) {
                    sqlQUery = docTypeDAO.getSession().createSQLQuery("DROP TABLE " + tableName);
                    sqlQUery.executeUpdate();
                } else {
                    updating = true;
                }
            }
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
        }
        Criteria ctype = docTypeDAO.getCriteria();
        ctype.add(Restrictions.eq("typeId", objectType));
        ctype.add(Restrictions.eq("deleted", false));
        ElementType etype = (ElementType) ctype.uniqueResult();
        List<MetadataField> availableFields = new LinkedList<MetadataField>();
        String fieldsList = "ID number";
        String queryFieldsList = "ID";
        LinkedList<String> fieldNames = new LinkedList<String>();
        for (ElementTypeAssociatedTemplate assocTemplate : etype.getAssociatedTemplates()) {
            MetadataTemplate t = assocTemplate.getMetadataTemplate();

            for (MetadataField f : t.getFields()) {
                availableFields.add(f);
                String baseName = getBaseNameOra(t, f);
                if (!fieldsList.isEmpty()) {
                    queryFieldsList += ", \n";
                    fieldsList += ", \n";
                }
                switch (f.getType()) {
                    case ELEMENT_LINK:
                        fieldsList += baseName + " number";
                        fieldsList += ", " + baseName + "_T varchar2(200 char)";
                        fieldNames.add(baseName);
                        fieldNames.add(baseName + "_T");
                        queryFieldsList += baseName;
                        queryFieldsList += ", " + baseName + "_T ";
                        break;
                    case DATE:
                        fieldsList += baseName + " date";
                        fieldNames.add(baseName);
                        queryFieldsList += baseName;
                        break;
                    case EXT_DICTIONARY:
                    case SELECT:
                    case CHECKBOX:
                    case RADIO:
                        fieldsList += baseName + "_C varchar2(200 char)";
                        fieldsList += ", " + baseName + "_D varchar2(4000 char)";
                        fieldNames.add(baseName);
                        fieldNames.add(baseName + "_C");
                        fieldNames.add(baseName + "_D");
                        queryFieldsList += baseName + "_C";
                        queryFieldsList += ", " + baseName + "_D ";
                        break;

                    case RICHTEXT:
                    case TEXTAREA:
                        fieldsList += baseName + " clob";
                        fieldNames.add(baseName);
                        queryFieldsList += baseName;
                        break;
                    case TEXTBOX:
                        fieldsList += baseName + " varchar2(4000 char)";
                        fieldNames.add(baseName);
                        queryFieldsList += baseName;
                        break;
                    default:
                        fieldsList += baseName + " varchar2(4000 char)";
                        fieldNames.add(baseName);
                        queryFieldsList += baseName;
                        break;
                }
            }
        }
        fieldsList += ",PARENT_ID number, PARENT_TYPE varchar2(100 char), CHILDSTYPE varchar2(4000 char), LAST_REFRESH date";
        queryFieldsList += ",PARENT_ID , PARENT_TYPE , CHILDSTYPE, LAST_REFRESH ";
        SQLQuery sqlQUery;
        if (updating) {
            try {
                String queryString2 = "select " + queryFieldsList + " from " + tableName + " where rownum=1";
                log.info("Esportazione " + objectType + " query " + queryString2);
                SQLQuery sqlQUery2 = docTypeDAO.getSession().createSQLQuery(queryString2);
                List res2 = sqlQUery2.list();
                if (res2.isEmpty()) {
                    sqlQUery = docTypeDAO.getSession().createSQLQuery("DROP TABLE " + tableName);
                    sqlQUery.executeUpdate();
                    updating = false;
                } else {
                    updating = true;
                }
            } catch (Exception ex) {
                try {
                    sqlQUery = docTypeDAO.getSession().createSQLQuery("DROP TABLE " + tableName);
                    sqlQUery.executeUpdate();
                } catch (Exception ex2) {

                }
                updating = false;
            }
        }
        if (!updating) {
            String createTable = "CREATE TABLE " + tableName + " (\n" + fieldsList.toUpperCase() + "," +
                    "  CONSTRAINT " + tableName + "_pk PRIMARY KEY (id))";
            sqlQUery = docTypeDAO.getSession().createSQLQuery(createTable);
            sqlQUery.executeUpdate();
        } else {
            String deleteQuery = "delete from " + tableName + " dump_t where last_refresh<=(select decode(deleted,1,sysdate,nvl(upd_dt,ins_dt)) from DOC_OBJ d where d.id=dump_t.id) ";
            sqlQUery = docTypeDAO.getSession().createSQLQuery(deleteQuery);
            sqlQUery.executeUpdate();
        }
        DetachedCriteria c = getAllElementsCriteria("root");
        c.add(Restrictions.eq("root.type", etype));
        c.add(Restrictions.sqlRestriction("{alias}.id not in (select id from " + tableName + " )"));
        List<Element> els = docDAO.getCriteriaList(c);
        int counter = 0;
        for (Element el : els) {
            List<String> types = new LinkedList<String>();
            List<Object> dataValues = new LinkedList<Object>();
            HashMap<String, Map.Entry<String, Object>> dataVals = new HashMap<String, Map.Entry<String, Object>>();
            String fields = "ID";
            String values = ":ID";
            for (ElementMetadata emd : el.getData()) {
                if (!availableFields.contains(emd.getField())) continue;
                if (emd.getValues().size() == 0) continue;
                ElementMetadataValue firstValue = emd.getValues().iterator().next();
                MetadataField f = emd.getField();
                MetadataTemplate t = emd.getTemplate();
                String baseName = getBaseNameOra(t, f);
                if (fieldNames.contains(baseName)) {
                    if (firstValue.getValue(f.getType()) == null) continue;
                    if (firstValue.getDate() == null && firstValue.getTextValue() == null && firstValue.getLongTextValue() == null && firstValue.getElement_link() == null && firstValue.getCode() == null && firstValue.getDecode() == null)
                        continue;
                    if (dataVals.containsKey(baseName + "_C") || dataVals.containsKey(baseName + "_D") || dataVals.containsKey(baseName))
                        continue;
                    String code = "";
                    String decode = "";
                    values += ",";
                    fields += ",";
                    switch (emd.getField().getType()) {

                        case ELEMENT_LINK:
                            fields += baseName + "";
                            fields += "," + baseName + "_T";
                            values += ":" + baseName;
                            values += ",:" + baseName + "_T";
                            types.add("Number");
                            types.add("String");
                            dataVals.put(baseName, new AbstractMap.SimpleEntry<String, Object>("Number", firstValue.getElement_link().getId()));
                            dataVals.put(baseName + "_T", new AbstractMap.SimpleEntry<String, Object>("String", firstValue.getElement_link().getType().getTypeId()));
                            dataValues.add(firstValue.getElement_link().getId());
                            dataValues.add(firstValue.getElement_link().getType().getTypeId());
                            break;
                        case DATE:
                            fields += baseName;
                            values += ":" + baseName;
                            types.add("Date");
                            dataValues.add(firstValue.getDate().getTime());
                            dataVals.put(baseName, new AbstractMap.SimpleEntry<String, Object>("Date", firstValue.getDate()));
                            break;

                        case EXT_DICTIONARY:
                        case CHECKBOX:
                        case RADIO:
                        case SELECT:
                            fields += baseName + "_C";
                            fields += ", " + baseName + "_D";
                            values += ":" + baseName + "_C";
                            values += ",:" + baseName + "_D";
                            types.add("String");
                            types.add("String");
                            for (ElementMetadataValue v : emd.getValues()) {
                                if (!code.isEmpty()) code += "|";
                                if (!decode.isEmpty()) decode += "|";
                                code += v.getCode();
                                decode += v.getDecode();
                            }
                            dataValues.add(code);
                            dataValues.add(decode);
                            dataVals.put(baseName + "_C", new AbstractMap.SimpleEntry<String, Object>("String", code));
                            dataVals.put(baseName + "_D", new AbstractMap.SimpleEntry<String, Object>("String", decode));
                            break;
                        case RICHTEXT:
                        case TEXTAREA:

                            // Questi campi sono dei blob, quindi non devo troncare nulla
                            fields += baseName;
                            values += ":" + baseName;
                            types.add("String");
                            dataValues.add(firstValue.getLongTextValue());
                            dataVals.put(baseName, new AbstractMap.SimpleEntry<String, Object>("String", firstValue.getLongTextValue()));
                            break;
                        case TEXTBOX:
                            fields += baseName;
                            values += ":" + baseName;
                            types.add("String");

                            boolean trunked = false;
                            for (MetadataField availableField : availableFields) {

                                if (availableField.getName().equalsIgnoreCase(baseName)) {

                                    /*
                                     * Se il tipo del dato è textbox, devo assicurarmi di eseguire il troncamento del
                                     * testo al massimo valore consentito da Oracle (4.000 caratteri).
                                     */
                                    if (availableField.getType().equals(MetadataFieldType.TEXTBOX) && this.textDimensionExceedOracleStandard(firstValue.getTextValue())) {

                                        dataValues.add(firstValue.getTextValue().substring(0, 4000));
                                        trunked = true;
                                        log.info("Troncato field [" + baseName + "] a 4.000 caratteri, lunghezza precedente [" + firstValue.getTextValue().length() + "]");
                                        break;
                                    }
                                }
                            }

                            if (!trunked) {

                                dataValues.add(firstValue.getTextValue());
                            }
                            dataVals.put(baseName, new AbstractMap.SimpleEntry<String, Object>("String", firstValue.getTextValue()));
                            break;
                    }
                }
            }
            if (el.getParent() != null) {
                fields += ",PARENT_ID, PARENT_TYPE";
                values += "," + el.getParent().getId() + ",'" + el.getParent().getType().getTypeId() + "'";
            }
            if (el.getType().getAllowedChilds().size() > 0) {
                String childsValue = "";
                if (el.getType().getAllowedChilds().size() > 0) {
                    fields += ",CHILDSTYPE";
                    for (ElementType tchild : el.getType().getAllowedChilds()) {
                        childsValue += tchild.getTypeId() + "|";
                    }
                    values += ",'" + childsValue + "'";
                }
            }
            fields += ", LAST_REFRESH";
            values += ", sysdate";
            String insertQuery = "insert into " + tableName + " (" + fields + ") values (" + values + ")";

            log.info("Preparing query: [" + insertQuery + "]");
            sqlQUery = docTypeDAO.getSession().createSQLQuery(insertQuery);
            sqlQUery.setLong("ID", el.getId());
            log.info("ID is [" + el.getId() + "]");
            Iterator<String> fieldsIt = dataVals.keySet().iterator();
            int i = 1;
            while (fieldsIt.hasNext()) {
                String fieldName = fieldsIt.next();
                if (fieldNames.contains(fieldName)) {
                    i++;
                    Map.Entry<String, Object> t = dataVals.get(fieldName);

                    if (t.getKey().equals("String")) sqlQUery.setString(fieldName, (String) t.getValue());
                    if (t.getKey().equals("Number")) sqlQUery.setLong(fieldName, (Long) t.getValue());
                    if (t.getKey().equals("Date")) sqlQUery.setCalendarDate(fieldName, (Calendar) t.getValue());
                }
            }
            sqlQUery.executeUpdate();
            counter++;
            if (counter >= 100) {
                commitTXSessionAndKeepAlive();
                counter = 0;
            }
        }
        commitTXSessionAndKeepAlive();
        log.info("Esportazione " + objectType + " terminata");
        it.cineca.siss.axmr3.log.Log.info(getClass(), "Esportazione " + objectType + " terminata");
    }

    /**
     * Restituisce <code>true</code> nel momento in cui la dimensione della stringa supera lo standard di Oracle fissato
     * a 4.000 caratteri.
     *
     * @param textValue è il valore stringa
     * @return <code>true</code> se è necessario un troncamento del field
     */
    private boolean textDimensionExceedOracleStandard(String textValue) {

        if (textValue == null || textValue.isEmpty()) {

            return false;
        }

        return textValue.length() > 4000;
    }

    public void persistAllObjects(String prefix) throws RestException {
        List<ElementType> types = docTypeDAO.getAll();
        for (ElementType t : types) {
            String tableName = prefix + "_" + t.getTypeId();
            persistObjects(t.getTypeId(), tableName);
        }

    }

    public List<Element> getGrouppedElements(Long groupId, IUser user) {
        DetachedCriteria items = DetachedCriteria.forClass(ElementGroup.class)
                .add(Restrictions.eq("groupId", groupId))
                .setProjection(Property.forName("item"));
        DetachedCriteria criteria = getViewableElementsCriteria(user)
                .add(Subqueries.propertyIn("id", items));
        return docDAO.getCriteriaList(criteria);

    }

    public boolean isInGroup(Long groupId, Long id) {
        Criteria items = groupDAO.getCriteria()
                .add(Restrictions.eq("groupId", groupId))
                .add(Restrictions.eq("item", id));

        return !items.list().isEmpty();
    }

    public WritableSheet populateGridSheet(WritableSheet sheet, Collection<Element> xElements, Collection<Element> yElements, Collection<Element> xyElements, String xMDCol, String yMDRow, String xyMDCol, String xyMDRow, String xyMD) throws WriteException {
        int xCount = 1;
        int yCount = 1;
        HashMap<Long, Integer> xMap = new HashMap<Long, Integer>();
        HashMap<Long, Integer> yMap = new HashMap<Long, Integer>();
        String template;

        for (Element el : xElements) {
            Label label = new Label(xCount, 0, el.getFieldDataString(xMDCol));
            sheet.addCell(label);
            xMap.put(el.getId(), xCount);
            xCount++;
        }

        for (Element el : yElements) {
            Label label = new Label(0, yCount, el.getFieldDataString(yMDRow));
            sheet.addCell(label);
            yMap.put(el.getId(), yCount);
            yCount++;
        }

        for (Long key : xMap.keySet()) {
            it.cineca.siss.axmr3.log.Log.info(getClass(), "xMap keyl: " + key.toString());
        }

        for (Long key : yMap.keySet()) {
            it.cineca.siss.axmr3.log.Log.info(getClass(), "yMap keyl: " + key.toString());
        }

        for (Element el : xyElements) {
            try {
                xCount = xMap.get(el
                        .getFieldDataElement(xyMDCol)
                        .get(0)
                        .getId());
                yCount = yMap.get(el.getFieldDataElement(xyMDRow).get(0).getId());
                //TODO: valutare se fare l'inserimento come numerico
                //jxl.write.Number number = new jxl.write.Number(3, 4, 3.1459);
                //sheet.addCell(number);
                Label label = new Label(xCount, yCount, el.getFieldDataString(xyMD));
                sheet.addCell(label);
            } catch (Exception ex) {
                it.cineca.siss.axmr3.log.Log.info(getClass(), "Eccezione grid el: " + el.getId().toString() + " md " + xyMDCol + " stringValue " + el
                        .getFieldDataElement(xyMDCol)
                        .get(0)
                        .getId().toString());

                //log.error(ex.getMessage(),ex);
            }
        }

        return sheet;
    }

    public List<WritableSheet> populateGridSheets(WritableWorkbook workbook, WritableSheet sheet, HashMap<Long, HashMap<String, String>> xMap, HashMap<Long, HashMap<String, String>> yMap, Collection<Element> xyElements, String xyMDCol, String xyMDRow, String xyMD) throws WriteException {
        return populateGridSheets(workbook, sheet, xMap, yMap, xyElements, xyMDCol, xyMDRow, xyMD, "");
    }

    public List<WritableSheet> populateGridSheets(WritableWorkbook workbook, WritableSheet stdSheet, HashMap<Long, HashMap<String, String>> xMap, HashMap<Long, HashMap<String, String>> yMap, Collection<Element> xyElements, String xyMDCol, String xyMDRow, String xyMD, String referenceMD) throws WriteException {
        return populateGridSheets(workbook, stdSheet, xMap, yMap, xyElements, xyMDCol, xyMDRow, xyMD, referenceMD, "");
    }

    public List<WritableSheet> populateGridSheets(WritableWorkbook workbook, WritableSheet stdSheet, HashMap<Long, HashMap<String, String>> xMap, HashMap<Long, HashMap<String, String>> yMap, Collection<Element> xyElements, String xyMDCol, String xyMDRow, String xyMD, String referenceMD, String braccio) throws WriteException {
        int xAxis = 0;
        int yAxis = 0;
        Double value = 0.0;
        String valueStr = "";
        Element reference;
        HashMap<String, WritableSheet> subSheets = new HashMap<String, WritableSheet>();
        HashMap<Integer, HashMap<WritableSheet, Integer>> assocSheets = new HashMap<Integer, HashMap<WritableSheet, Integer>>();
        String info = "";
        String sheetName = stdSheet.getName();
        WritableSheet currSheet;
        Integer stdRow = 0;
        Integer assocRow = 0;
        HashMap<WritableSheet, Integer> association = new HashMap<WritableSheet, Integer>();
        List<WritableSheet> ret = new LinkedList<WritableSheet>();
        String regexBraccio = "\\|" + braccio + "\\|";
        double number = 0.0;
        ret.add(stdSheet);

        Collection<HashMap<String, String>> yLabels = yMap.values();
        for (HashMap<String, String> yLabel : yLabels) {
            it.cineca.siss.axmr3.log.Log.info(getClass(), "yAxis: " + yLabel.get("Position") + " Label: " + yLabel.get("Label"));
            stdRow = (Integer.parseInt(yLabel.get("Position")) - 1);
            Label label = new Label(0, stdRow, yLabel.get("Label"));
            stdSheet.addCell(label);
            if (yLabel.containsKey("Info") && !yLabel.get("Info").isEmpty()) {
                info = yLabel.get("Info");
                it.cineca.siss.axmr3.log.Log.info(getClass(), "contengo info per " + String.valueOf(stdRow));
                if (!subSheets.containsKey(info)) {
                    currSheet = workbook.createSheet(sheetName + " " + info, workbook.getNumberOfSheets());
                    subSheets.put(info, currSheet);
                    ret.add(currSheet);
                }
                currSheet = subSheets.get(info);
                assocRow = currSheet.getRows() + 1;
                association = new HashMap<WritableSheet, Integer>();
                association.put(currSheet, assocRow);
                assocSheets.put(stdRow, association);
                label = new Label(0, assocRow, yLabel.get("Label"));
                currSheet.addCell(label);
            }
        }

        Collection<HashMap<String, String>> xLabels = xMap.values();
        for (HashMap<String, String> xLabel : xLabels) {
            it.cineca.siss.axmr3.log.Log.info(getClass(), "xAxis: " + xLabel.get("Position") + " Label: " + xLabel.get("Label"));
            Label label = new Label((Integer.parseInt(xLabel.get("Position")) - 1), 0, xLabel.get("Label"));
            stdSheet.addCell(label);
            for (String key : subSheets.keySet()) {
                label = new Label((Integer.parseInt(xLabel.get("Position")) - 1), 0, xLabel.get("Label"));
                subSheets.get(key).addCell(label);
            }
        }


        for (Element el : xyElements) {
            if (!referenceMD.isEmpty()) {
                reference = el.getFieldDataElement(referenceMD).get(0);
            } else {
                reference = el;
            }
            try {

                //TODO:togliere if di debug
                if (!xMap.containsKey(reference.getFieldDataElement(xyMDCol).get(0).getId())) {
                    it.cineca.siss.axmr3.log.Log.info(getClass(), "Match non trovato: cercato: " + reference.getFieldDataElement(xyMDCol).get(0).getId().toString() + " tra:");
                    for (Long key : xMap.keySet()) {
                        it.cineca.siss.axmr3.log.Log.info(getClass(), "key: " + key.toString());
                    }
                } else {

                    xAxis = Integer.parseInt(xMap.get(reference.getFieldDataElement(xyMDCol).get(0).getId()).get("Position")) - 1;
                    //TODO:togliere if di debug
                    if (!yMap.containsKey(reference.getFieldDataElement(xyMDRow).get(0).getId())) {
                        it.cineca.siss.axmr3.log.Log.info(getClass(), "Match non trovato: cercato: " + reference.getFieldDataElement(xyMDRow).get(0).getId().toString() + " tra:");
                        for (Long key : yMap.keySet()) {
                            it.cineca.siss.axmr3.log.Log.info(getClass(), "key: " + key.toString());
                        }
                    } else {
                        yAxis = Integer.parseInt(yMap.get(reference.getFieldDataElement(xyMDRow).get(0).getId()).get("Position")) - 1;

                        //TODO: valutare se fare l'inserimento come numerico
                        //jxl.write.Number number = new jxl.write.Number(3, 4, 3.1459);
                        //sheet.addCell(number);
                        try {
                            String currBraccio = reference.getFieldDataString("Costo", "Braccio");
                            it.cineca.siss.axmr3.log.Log.info(getClass(), "per braccio " + currBraccio + " la regex " + regexBraccio);
                            if (braccio.isEmpty() || currBraccio.isEmpty() || currBraccio.matches(regexBraccio)) {
                                value = Double.parseDouble(el.getFieldDataString(xyMD));
                                if (!value.isNaN()) {
                                    valueStr = el.getFieldDataString(xyMD);
                                    Label label = new Label(xAxis, yAxis, valueStr);
                                    stdSheet.addCell(label);

                                    if (assocSheets.containsKey(yAxis)) {

                                        association = assocSheets.get(yAxis);
                                        currSheet = association.keySet().iterator().next();
                                        it.cineca.siss.axmr3.log.Log.info(getClass(), "contengo info per " + String.valueOf(yAxis) + " value " + valueStr + " sheet " + currSheet.getName() + " row " + String.valueOf(assocRow) + " col " + String.valueOf(xAxis));
                                        assocRow = association.values().iterator().next();
                                        if (valueStr.isEmpty()) {
                                            label = new Label(xAxis, assocRow, valueStr);
                                            currSheet.addCell(label);
                                        } else {
                                            number = Double.parseDouble(valueStr);
                                            currSheet.addCell(new jxl.write.Number(xAxis, assocRow, number));
                                        }
                                    } else {
                                        it.cineca.siss.axmr3.log.Log.info(getClass(), "non contengo info per " + String.valueOf(yAxis));
                                    }
                                }
                            }
                        } catch (NumberFormatException ex) {
                            Label label = new Label(xAxis, yAxis, "0");
                            stdSheet.addCell(label);
                            if (assocSheets.containsKey(yAxis)) {
                                association = assocSheets.get(yAxis);
                                currSheet = association.keySet().iterator().next();
                                assocRow = association.values().iterator().next();
                                label = new Label(xAxis, assocRow, "0");
                                currSheet.addCell(label);
                            }
                        }

                    }
                }
            } catch (Exception ex) {
                it.cineca.siss.axmr3.log.Log.info(getClass(), "Eccezione grid el: " + el.getId().toString() + " mdCol " + xyMDCol + " mdRow " + xyMDRow + " col " + reference
                        .getId().toString()

                );
                log.error(ex.getMessage(), ex);
            }
        }

        return ret;
    }

    public HashMap<Long, HashMap<String, String>> createGridAxisMap(Collection<Element> elements, String mdAxis) {
        return createGridAxisMap(elements, mdAxis, "");
    }

    public HashMap<Long, HashMap<String, String>> createGridAxisMap(Collection<Element> elements, String mdAxis, String mdExtraInfo) {
        HashMap<Long, HashMap<String, String>> map = new HashMap<Long, HashMap<String, String>>();
        HashMap<String, String> dataMap;

        for (Element el : elements) {
            dataMap = new HashMap<String, String>();
            try {
                dataMap.put("Label", el.getTitleString());
            } catch (Exception ex) {
                it.cineca.siss.axmr3.log.Log.info(getClass(), "No title id: " + el.getId().toString());
            }
            dataMap.put("Position", el.getFieldDataString(mdAxis));
            if (!mdExtraInfo.isEmpty()) {
                dataMap.put("Info", el.getFieldDataString(mdExtraInfo));
            }
            map.put(el.getId(), dataMap);
        }

        return map;
    }

    public WritableSheet sumGrid(WritableSheet sheet) throws WriteException {
        int cols = sheet.getColumns();
        int rows = sheet.getRows();
        int colOccurencies = 0;
        double totalCol = 0.0;
        double totalRow = 0.0;
        double totalAll = 0.0;
        double value = 0.0;

        Double currValue = 0.0;
        Label label;

        label = new Label(cols, 0, "Totale per prestazione (euro)");
        sheet.addCell(label);
        label = new Label(cols + 1, 0, "Totale occorrenze");
        sheet.addCell(label);
        label = new Label(0, rows, "Totale per visita (euro)");
        sheet.addCell(label);

        for (int i = 1; i < cols; i++) {
            value = 0.0;
            for (int k = 1; k < rows; k++) {
                try {
                    currValue = Double.parseDouble(sheet.getCell(i, k).getContents());
                    if (!currValue.isNaN()) {

                        value += currValue;
                        totalAll += currValue;

                    }
                } catch (NumberFormatException ex) {

                }
            }
            label = new Label(i, rows, String.format(Locale.ITALIAN, "%.2f", value));
            sheet.addCell(label);
        }
        label = new Label((cols), (rows), String.format(Locale.ITALIAN, "%.2f", totalAll));
        sheet.addCell(label);

        for (int k = 1; k < rows; k++) {
            value = 0.0;
            colOccurencies = 0;
            for (int i = 1; i < cols; i++) {
                try {
                    currValue = Double.parseDouble(sheet.getCell(i, k).getContents());
                    if (!currValue.isNaN()) {
                        value += currValue;
                        colOccurencies++;
                        label = new Label(i, k, String.format(Locale.ITALIAN, "%.2f", currValue));
                        sheet.addCell(label);
                    }

                } catch (NumberFormatException ex) {

                }
            }
            label = new Label(cols, k, String.format(Locale.ITALIAN, "%.2f", value));
            sheet.addCell(label);
            label = new Label(cols + 1, k, String.valueOf(colOccurencies));
            sheet.addCell(label);
        }

        return sheet;
    }

    public WritableSheet summarizeGrid(WritableSheet sheet, WritableSheet summary) throws WriteException {
        return summarizeGrid(sheet, summary, "");
    }

    public WritableSheet summarizeGrid(WritableSheet sheet, WritableSheet summary, String totalePaziente) throws WriteException {
        int cols = sheet.getColumns();
        int rows = sheet.getRows();
        int totalRow = rows - 1;
        int colOccurencies = 0;
        double totalCol = 0.0;

        double totalAll = 0.0;
        double value = 0.0;
        String currValue = "";
        Label label;

        label = new Label(0, 0, "Visite");
        summary.addCell(label);
        label = new Label(1, 0, "Totale (euro)");
        summary.addCell(label);

        if (sheet.getCell(cols - 1, 0).getContents().equals("Totale occorrenze")) {
            cols -= 2;
        }

        for (int i = 1; i < cols; i++) {
            currValue = sheet.getCell(i, 0).getContents();
            label = new Label(0, i, currValue);
            summary.addCell(label);

            currValue = sheet.getCell(i, totalRow).getContents();
            label = new Label(1, i, currValue);
            summary.addCell(label);
        }

        /*if(totalePaziente!=null && !totalePaziente.isEmpty()){
            label = new Label(0, cols+1, "Totale a preventivo per paziente (euro)");
            summary.addCell(label);
            try{
                totalCol=Double.parseDouble(totalePaziente);
                label = new Label(1, cols+1, String.format(Locale.ITALIAN,"%.2f",totalCol));
                summary.addCell(label);
            }
            catch(Exception ex){
                label = new Label(1, cols+1, totalePaziente);
                summary.addCell(label);
            }

        }           */

        return summary;
    }

    public WritableSheet sumTable(WritableSheet sheet) throws WriteException {
        int cols = sheet.getColumns();
        int rows = sheet.getRows();

        double totalCol = 0.0;
        double totalRow = 0.0;
        double totalAll = 0.0;
        double value = 0.0;
        Double currValue = 0.0;
        Label label;


        label = new Label(0, rows, "Totale");
        sheet.addCell(label);


        for (int k = 1; k < rows; k++) {
            try {
                currValue = Double.parseDouble(sheet.getCell(1, k).getContents());
                if (!currValue.isNaN()) {
                    value += Double.parseDouble(sheet.getCell(1, k).getContents());
                    label = new Label(1, rows, String.format(Locale.ITALIAN, "%.2f", value));
                }

            } catch (NumberFormatException ex) {

            }
        }
        label = new Label(1, rows, String.format(Locale.ITALIAN, "%.2f", value));
        sheet.addCell(label);

        return sheet;
    }

    public WritableSheet populateTableSheet(WritableSheet sheet, HashMap<Integer, String> headers, Collection<Element> elements, String md) throws WriteException {
        return populateTableSheet(sheet, headers, elements, md, "", "", "");
    }

    public WritableSheet populateTableSheet(WritableSheet sheet, HashMap<Integer, String> headers, Collection<Element> elements, String valueMD, String refType, String refValueMD, String referenceMD) throws WriteException {
        return appendTableSheet(0, sheet, headers, elements, valueMD, refType, refValueMD, referenceMD);
    }

    public WritableSheet appendTableSheet(int yAxis, WritableSheet sheet, HashMap<Integer, String> headers, Collection<Element> elements, String valueMD) throws WriteException {
        return appendTableSheet(yAxis, sheet, headers, elements, valueMD, "", "", "");
    }

    public WritableSheet appendTableSheet(int yAxis, WritableSheet sheet, HashMap<Integer, String> headers, Collection<Element> elements, String valueMD, String refType, String refValueMD, String referenceMD) throws WriteException {


        Double value = 0.0;
        Element reference;
        Label label;
        String currValueMD = "";

        for (Integer key : headers.keySet()) {
            label = new Label(key, yAxis, headers.get(key));
            sheet.addCell(label);
        }
        yAxis++;

        for (Element el : elements) {
            if (!referenceMD.isEmpty()) {
                if (!refType.isEmpty() && el.getType().getTypeId().equals(refType)) {
                    reference = el;
                    currValueMD = valueMD;
                } else {
                    reference = el.getFieldDataElement(referenceMD).get(0);
                    currValueMD = refValueMD;
                    if (!refType.isEmpty() && !reference.getType().getTypeId().equals(refType)) {
                        continue;
                    }
                }
            } else {
                reference = el;
                currValueMD = valueMD;
            }
            try {
                label = new Label(0, yAxis, reference.getTitleString());
                sheet.addCell(label);
                value = Double.parseDouble(el.getFieldDataString(currValueMD));
                if (!value.isNaN()) {
                    label = new Label(1, yAxis, String.format(Locale.ITALIAN, "%.2f", value));
                    sheet.addCell(label);
                }

                yAxis++;
            } catch (NumberFormatException ex) {
                label = new Label(1, yAxis, "0");
                sheet.addCell(label);
                yAxis++;
            }
        }

        return sheet;
    }

    public Long getTypeIdByNameOrId(String s) {
        Long docType = null;
        try {
            docType = Long.parseLong(s);
        } catch (Exception ex) {
            ElementType elType = getDocDefinitionByName(s);
            docType = elType.getId();
        }
        return docType;
    }

    public void moveUp(String userid, Element el) throws RestException {
        Long[] minMax = getMinMaxPosition(el);
        long actualPos = el.getPosition();
        long pos = actualPos;
        if (actualPos > minMax[0]) pos -= 1;
        _moveToPosition(userid, el, pos);
    }

    public void moveDown(String userid, Element el) throws RestException {
        Long[] minMax = getMinMaxPosition(el);
        long actualPos = el.getPosition();
        long pos = actualPos;
        if (actualPos < minMax[1]) pos += 1;
        _moveToPosition(userid, el, pos);
    }

    public void moveToTop(String userid, Element el) throws RestException {
        Long[] minMax = getMinMaxPosition(el);
        long actualPos = el.getPosition();
        long pos = minMax[0];
        _moveToPosition(userid, el, pos);
    }

    public void moveToBottom(String userid, Element el) throws RestException {
        Long[] minMax = getMinMaxPosition(el);
        long actualPos = el.getPosition();
        long pos = minMax[1];
        _moveToPosition(userid, el, pos);
    }

    public Long[] getMinMaxPosition(Element el) {
        Criteria c = docDAO.getCriteria();
        Criteria c1 = docDAO.getCriteria();
        c.add(Restrictions.eq("deleted", false));
        c.add(Restrictions.eq("type", el.getType()));
        c1.add(Restrictions.eq("deleted", false));
        c1.add(Restrictions.eq("type", el.getType()));
        if (el.getParent() != null) {
            c.add(Restrictions.eq("parent", el.getParent()));
            c1.add(Restrictions.eq("parent", el.getParent()));
        }
        c.setProjection(Projections.min("position"));
        c1.setProjection(Projections.max("position"));
        Long[] minMax = new Long[2];
        minMax[0] = (Long) c.uniqueResult();
        minMax[1] = (Long) c1.uniqueResult();
        return minMax;
    }

    public void moveToPosition(String userid, Element el, long pos) throws RestException {
        Long[] minMax = getMinMaxPosition(el);
        long maxPos = minMax[1];
        long minPos = minMax[0];
        if (pos < minPos) pos = minPos;
        if (pos > maxPos) pos = maxPos;
        _moveToPosition(userid, el, pos);
    }

    public void clearBlankPosition(Element el) throws RestException {
        HashMap<Long, Element> sortableList = new HashMap<Long, Element>();
        LinkedList<Long> positions = new LinkedList<Long>();
        for (Element e : el.getChildren()) {
            sortableList.put(e.getPosition(), e);
            positions.add(e.getPosition());
        }
        Collections.sort(positions);
        int pos = 1;
        for (pos = 1; pos <= positions.size(); pos++) {
            Element thisEl = sortableList.get(positions.get(pos - 1));
            thisEl.setPosition(new Long(pos));
            try {
                docDAO.saveOrUpdate(thisEl);
            } catch (AxmrGenericException e1) {
                throw new RestException(e1.getMessage(), this.txManager);
            }
        }
    }

    protected void _moveToPosition(String userid, Element el, long pos) throws RestException {
        Criteria c = docDAO.getCriteria();
        c.add(Restrictions.eq("deleted", false));
        c.add(Restrictions.eq("type", el.getType()));
        if (el.getParent() != null) {
            c.add(Restrictions.eq("parent", el.getParent()));
        }
        c.addOrder(Order.asc("position"));
        long actualPos = el.getPosition();
        boolean upMode = true;
        if (actualPos < pos) upMode = false;
        it.cineca.siss.axmr3.log.Log.info(getClass(), "Sposto l'elemento: " + el.getId() + " dalla posizione: " + actualPos + " a " + pos);
        if (upMode) it.cineca.siss.axmr3.log.Log.info(getClass(), "Spostamento in alto");
        else it.cineca.siss.axmr3.log.Log.info(getClass(), "Spostamento in basso");
        List<Element> els = c.list();
        for (Element e : els) {
            long newPos = 1;
            if (e.getId().equals(el.getId())) newPos = pos;
            else {
                long elPos = e.getPosition();
                newPos = elPos;
                if (upMode) {
                    if (elPos >= pos && elPos <= actualPos) {
                        newPos = elPos + 1;
                        it.cineca.siss.axmr3.log.Log.info(getClass(), " -3698 - elemento " + e.getId() + ": " + elPos + " -> " + newPos);
                    }
                } else {
                    if (elPos >= actualPos && elPos <= pos) {
                        newPos = elPos - 1;
                        it.cineca.siss.axmr3.log.Log.info(getClass(), " - 3703 - elemento " + e.getId() + ": " + elPos + " -> " + newPos);
                    }
                }
            }
            if (newPos != e.getPosition()) {
                try {
                    it.cineca.siss.axmr3.log.Log.info(getClass(), " - Preparo update - elemento " + e.getId() + ": " + e.getPosition() + " -> " + newPos);
                    e.setPosition(newPos);
                    e.setLastUpdateDt(new GregorianCalendar());
                    e.setLastUpdateUser(userid);
                    docDAO.saveOrUpdate(e);
                    it.cineca.siss.axmr3.log.Log.info(getClass(), " - Update done - elemento " + e.getId());
                } catch (AxmrGenericException e1) {
                    throw new RestException(e1.getMessage(), this.txManager);
                }
            }

        }
    }

    public void moveToPositionAndParent(String username, Element el, Element newParent, Long pos) throws RestException {
        el.setParent(newParent);
        long startPos = 1;
        el.setPosition(startPos);
        try {
            docDAO.saveOrUpdate(el);
            moveToPosition(username, el, pos);
        } catch (AxmrGenericException e1) {
            throw new RestException(e1.getMessage(), this.txManager);
        }
    }

    public void changePermissionToGroup(Element el, String permissions, String ftl, String group) throws Exception {

        if (group != null && !group.isEmpty()) {
            Policy pol = Policy.createPolicyByCommaSeparatedString(permissions);
            this.setElementPolicy(el, ftl, pol, true, group);
        }

    }

    public void removePermissionToGroup(Element el, String ftl, String group) throws Exception {

        if (group != null && !group.isEmpty()) {
            this.removeElementPolicy(el, ftl, true, group);
        }

    }

    public Element createChild(String elementId, String userid, String typeId, HashMap<String, String> data) throws Exception {
        //IUser user= (IUser) userService.loadUserByUsername(userid);
        Element parent = getElement(Long.parseLong(elementId));
        ElementType type = null;
        Element el = null;
        it.cineca.siss.axmr3.log.Log.info(getClass(), "parent type " + parent.getType().getTypeId());
        for (ElementType t : parent.getType().getAllowedChilds()) {
            it.cineca.siss.axmr3.log.Log.info(getClass(), "allowed child " + t.getTypeId());
            if (t.getTypeId().equals(typeId)) type = t;
        }
        if (type != null) {
            el = saveElement(userid, type, data, null, null, null, "", "", "", "", parent);
        }
        return el;
    }

    public void changePermissionToUser(String elementId, String permissions, String ftl, String username) throws Exception {
        Policy pol = Policy.createPolicyByCommaSeparatedString(permissions);
        Element el = getElement(Long.parseLong(elementId));
        this.setElementPolicy(el, ftl, pol, false, username);
    }


    public boolean isDm(IUser user) {
        boolean isDm = false;
        try {
            for (IAuthority a : user.getAuthorities()) {
                if (a.getAuthority().equals("DATAMANAGER")) isDm = true;
            }
        } catch (Exception ex) {

        }

        return isDm;
    }

    public EmendamentoSession getActiveEmeSession(Long emeSessionId) {
        Criteria c = emeSessionDAO.getCriteria();
        c.add(Restrictions.eq("id", emeSessionId));
        //TODO: (!!!!!!!!!!!!) DEFINIRE COME RECUPERARE LA SESSIONE CORRENTE DI EMENDAMENTO TRA QUELLE APERTE
        //c.add(Restrictions.isNull("endDt")).add(Restrictions.eq("userid", user.getUsername()));
        return (EmendamentoSession) c.uniqueResult();
    }

    public DataManagementSession getActiveDmSession(IUser user) {
        Criteria c = dmSessionDAO.getCriteria();
        c.add(Restrictions.isNull("endDt")).add(Restrictions.eq("userid", user.getUsername()));
        return (DataManagementSession) c.uniqueResult();
    }

    public DataManagementSession getDmSessionById(Long id) {
        return dmSessionDAO.getById(id);
    }


    public void saveDmSession(DataManagementSession dm) throws AxmrGenericException {
        dmSessionDAO.save(dm);
    }

    public Long getEmendamentoSessionId(IUser user, Long emeObjId, Long centroObjId) throws AxmrGenericException {
        Long retval = 0L;
        Criteria c = emeSessionDAO.getCriteria();
        c.add(Restrictions.eq("emeId",emeObjId)).add(Restrictions.eq("centroId", centroObjId));
        if (c.list().size()>0){
            EmendamentoSession tmpSession = (EmendamentoSession) c.uniqueResult();
            if (tmpSession.getEndDt()==null || tmpSession.getEndDt().before(new GregorianCalendar(2000,0,1))){
                retval = tmpSession.getId();
            }
        }else{
            //Creo nuova sessione emendamento e torno il mio ID
            EmendamentoSession newSession = new EmendamentoSession();
            newSession.setCentroId(centroObjId);
            newSession.setEmeId(emeObjId);
            newSession.setStartDt(new GregorianCalendar());
            newSession.setUserid(user.getUsername());
            emeSessionDAO.save(newSession);
            retval = newSession.getId();
        }
        log.info("TORNO EME SESSION ID: "+retval);
        return retval;
    }

    /**
     * modifica il/i valore/i di un singolo campo in data management session
     *
     * @param user  user data manager
     * @param elId  id elemento in modifica
     * @param mdId  id metadata dell'elemento in modifica
     * @param value valore/i dell'elemento in modifica
     * @throws AxmrGenericException
     */
    public void dmUpdateMetadata(IUser user, Long elId, Long mdId, String[] value) throws AxmrGenericException {
        Element el = this.getElement(elId);
        ElementType type = el.getType();
        MetadataTemplate template = null;
        MetadataField field = null;
        for (ElementTypeAssociatedTemplate at : type.getAssociatedTemplates()) {
            MetadataTemplate t = at.getMetadataTemplate();
            for (MetadataField f : t.getFields()) {
                Long myFieldId = f.getId();
                if (myFieldId.longValue() == mdId.longValue()) {
                    template = t;
                    field = f;
                }
            }
        }
        String modifiedField = "";
        String oldValue = "";
        String newValue = value[0];
        if (mdId < 0) { //VAXMR-306
            if (mdId == -1) { //lastUpdateDt
                modifiedField = "lastUpdateDt";
                Calendar calendar = el.getLastUpdateDt();
                SimpleDateFormat fmt = new SimpleDateFormat("dd/MM/yyyy");
                fmt.setCalendar(calendar);
                oldValue = fmt.format(calendar.getTime());
                Date parsed = null;
                Object val = value[0];
                if (val instanceof String) {
                    if (((String) val).isEmpty()) {
                        el.setLastUpdateDt(null);
                    } else {
                        List<DateFormat> dfs = new LinkedList<DateFormat>();
                        dfs.add(new SimpleDateFormat("dd/MM/yyyy"));
                        dfs.add(new SimpleDateFormat("EEE MMM dd hh:mm:ss z yyyy", Locale.US));
                        boolean parsedOk = false;
                        for (DateFormat df : dfs) {
                            try {
                                parsed = df.parse(val.toString());
                                //it.cineca.siss.axmr3.log.Log.info(getClass(),"parsed date: " + parsed);
                                Calendar newCalendar = Calendar.getInstance();
                                newCalendar.setTime(parsed);
                                el.setLastUpdateDt(newCalendar);
                                parsedOk = true;
                            } catch (ParseException e) {
                                //it.cineca.siss.axmr3.log.Log.info(getClass(),"Data "+val.toString()+" formato non accettato");
                            }
                        }
                        if (!parsedOk) {
                            try {
                                Long unixTime = Long.parseLong(val.toString());
                                Calendar newCalendar = Calendar.getInstance();
                                newCalendar.setTime(new Date(unixTime));
                                el.setLastUpdateDt(newCalendar);
                            } catch (Exception e) {
                                //it.cineca.siss.axmr3.log.Log.info(getClass(),"Data "+val.toString()+" formato non accettato");
                            }

                        }
                    }
                } else {

                }

                if (val instanceof GregorianCalendar) {
                    el.setLastUpdateDt((GregorianCalendar) val);
                }
            } else if (mdId == -2) { //creationDt
                modifiedField = "creationDt";
                Calendar calendar = el.getCreationDt();
                SimpleDateFormat fmt = new SimpleDateFormat("dd/MM/yyyy");
                fmt.setCalendar(calendar);
                oldValue = fmt.format(calendar.getTime());
                Date parsed = null;
                Object val = value[0];
                if (val instanceof String) {
                    if (((String) val).isEmpty()) {
                        el.setCreationDt(null);
                    } else {
                        List<DateFormat> dfs = new LinkedList<DateFormat>();
                        dfs.add(new SimpleDateFormat("dd/MM/yyyy"));
                        dfs.add(new SimpleDateFormat("EEE MMM dd hh:mm:ss z yyyy", Locale.US));
                        boolean parsedOk = false;
                        for (DateFormat df : dfs) {
                            try {
                                parsed = df.parse(val.toString());
                                //it.cineca.siss.axmr3.log.Log.info(getClass(),"parsed date: " + parsed);
                                Calendar newCalendar = Calendar.getInstance();
                                newCalendar.setTime(parsed);
                                el.setCreationDt(newCalendar);
                                parsedOk = true;
                            } catch (ParseException e) {
                                //it.cineca.siss.axmr3.log.Log.info(getClass(),"Data "+val.toString()+" formato non accettato");
                            }
                        }
                        if (!parsedOk) {
                            try {
                                Long unixTime = Long.parseLong(val.toString());
                                Calendar newCalendar = Calendar.getInstance();
                                newCalendar.setTime(new Date(unixTime));
                                el.setCreationDt(newCalendar);
                            } catch (Exception e) {
                                //it.cineca.siss.axmr3.log.Log.info(getClass(),"Data "+val.toString()+" formato non accettato");
                            }

                        }
                    }
                } else {

                }

                if (val instanceof GregorianCalendar) {
                    el.setCreationDt((GregorianCalendar) val);
                }
            } else if (mdId == -3) { //createUser
                modifiedField = "createUser";
                oldValue = el.getCreateUser();
                el.setCreateUser(value[0]);
            } else if (mdId == -4) { //lastUpdateUser
                modifiedField = "lastUpdateUser";
                oldValue = el.getLastUpdateUser();
                el.setLastUpdateUser(value[0]);
            }

            //AGGIORNO LA DATA DI ULTIMA MODIFICA PER FAR REINDICIZZARE L'ELEMENTO
            it.cineca.siss.axmr3.log.Log.info(getClass(), "AGGIORNO LA DATA DI ULTIMA MODIFICA PER FAR REINDICIZZARE L'ELEMENTO " + new GregorianCalendar());
            recurseUpdateDt(el, user, new GregorianCalendar());
            docDAO.saveOrUpdate(el); //salvo l'oggetto
            addElidToBeUpdeated(el.getId(),true);
            //TODO: GESTIRE AUDIT TRAIL!
            registerDmAction(user, el, "Modified " + modifiedField, "Old value: " + oldValue + " - New value: " + newValue);

        } else {
            if (field == null || template == null) {
                throw new AxmrGenericException("Campo non trovato");
            }
            boolean templateEnabled = false; //template attivo?
            boolean fieldValueExists = false; //campo già valorizzato?
            ElementMetadata mdata = null;
            for (ElementTemplate et : el.getElementTemplates()) {
                if (!templateEnabled && template.getId() == et.getMetadataTemplate().getId()) {
                    templateEnabled = true;
                }
            }
            for (ElementMetadata md : el.getData()) {
                if (!fieldValueExists && md.getField().getId().longValue() == mdId.longValue()) {
                    fieldValueExists = true;
                    mdata = md;
                }
            }
            String specification = "";
            if (mdata != null) { //esiste un metadato valorizzato
                specification = "update"; //quindi aggiorniamo il metadato

                DataManagementAction action = new DataManagementAction();
                action.setDmSession(getActiveDmSession(user));
                action.setAction("UPDATE_METADATA");
                action.setObjId(el);
                action.setActionDt(new GregorianCalendar());
                action.setSpecification(specification);
                dmActionDAO.save(action);

                AuditMetadata amd = new AuditMetadata(); //creo record di Audit
                amd.setField(mdata.getField());
                amd.setModDt(new GregorianCalendar());
                amd.setTemplate(mdata.getTemplate());
                amd.setUsername(user.getUsername());
                amd.setAction("DM_UPDATE");
                amd.setDmSession(getActiveDmSession(user));
                amd.setDmAction(action);
                aMdDAO.save(amd);
                if (el.getAuditData() == null) {
                    el.setAuditData(new LinkedList<AuditMetadata>());
                }
                el.getAuditData().add(amd);
                //AGGIORNO LA DATA DI ULTIMA MODIFICA PER FAR REINDICIZZARE L'ELEMENTO
                it.cineca.siss.axmr3.log.Log.info(getClass(), "AGGIORNO LA DATA DI ULTIMA MODIFICA PER FAR REINDICIZZARE L'ELEMENTO " + new GregorianCalendar());
                recurseUpdateDt(el, user, new GregorianCalendar());

                for (ElementMetadataValue emdv : mdata.getValues()) { //per ogni valore presente precedentemente alla modifica, salvo un record in Audit
                    AuditValue av = new AuditValue();
                    av.setOld(true);

                    av.setDmSession(getActiveDmSession(user));
                    try {
                        av.setCode(emdv.getCode());
                    } catch (NullPointerException ex) {
                    }
                    try {
                        av.setDecode(emdv.getDecode());
                    } catch (NullPointerException ex) {
                    }
                    try {
                        av.setDate(emdv.getDate());
                    } catch (NullPointerException ex) {
                    }
                    try {
                        av.setElement_link(emdv.getElement_link());
                    } catch (NullPointerException ex) {
                    }
                    try {
                        av.setLongTextValue(emdv.getLongTextValue());
                    } catch (NullPointerException ex) {
                    }
                    try {
                        av.setTextValue(emdv.getTextValue());
                    } catch (NullPointerException ex) {
                    }

                    if (amd.getValues() != null) {
                        amd.getValues().add(av);
                    } else {
                        LinkedList<AuditValue> values = new LinkedList<AuditValue>();
                        values.add(av);
                        amd.setValues(values);
                    }
                    aMdValDAO.save(av);
                    elMdValueDAO.delete(emdv); //elimino il riferimento al vecchio valore dal metadato
                }
                aMdDAO.saveOrUpdate(amd); //aggiorno il record di Audit del metadato
                mdata.getValues().clear(); //svuoto i valori precedenti alla modifica nel metadato ed inserisco i nuovi
                if (field.getType().equals(MetadataFieldType.ELEMENT_LINK)) {
                    if (value.length == 0) mdata.setVal(null);
                    else {
                        for (int i = 0; i < value.length; i++) {
                            mdata.setVal(this.getElement(Long.parseLong(value[i])));
                        }
                    }
                } else {
                    for (int i = 0; i < value.length; i++) {
                        mdata.setVal(value[i]);
                    }
                }
                for (ElementMetadataValue val : mdata.getValues()) { //per ogni nuovo valore salvo un record in Audit
                    elMdValueDAO.save(val);
                    AuditValue av = new AuditValue();
                    av.setOld(false); //discrimina valore vecchio con valore nuovo (nel blocco precedente era true)
                    av.setDmSession(getActiveDmSession(user));
                    try {
                        av.setCode(val.getCode());
                    } catch (NullPointerException ex) {
                    }
                    try {
                        av.setDecode(val.getDecode());
                    } catch (NullPointerException ex) {
                    }
                    try {
                        av.setDate(val.getDate());
                    } catch (NullPointerException ex) {
                    }
                    try {
                        av.setElement_link(val.getElement_link());
                    } catch (NullPointerException ex) {
                    }
                    try {
                        av.setLongTextValue(val.getLongTextValue());
                    } catch (NullPointerException ex) {
                    }
                    try {
                        av.setTextValue(val.getTextValue());
                    } catch (NullPointerException ex) {
                    }
                    if (amd.getValues() != null) {
                        amd.getValues().add(av);
                    } else {
                        LinkedList<AuditValue> values = new LinkedList<AuditValue>();
                        values.add(av);
                        amd.setValues(values);
                    }
                    aMdValDAO.save(av);
                }
                aMdDAO.saveOrUpdate(amd);
            } else { //valore precedente non esistente, creazione nuovo valore metadato
                specification = "Create";

                DataManagementAction action = new DataManagementAction();
                action.setDmSession(getActiveDmSession(user));
                action.setAction("CREATE_METADATA");
                action.setObjId(el);
                action.setActionDt(new GregorianCalendar());
                action.setSpecification(specification);
                dmActionDAO.save(action);

                //creo l'audit del metadato
                AuditMetadata amd = new AuditMetadata();
                amd.setUsername(user.getUsername());
                amd.setAction("DM_CREATE");
                amd.setModDt(new GregorianCalendar());
                amd.setField(field);
                amd.setTemplate(template);
                amd.setDmSession(getActiveDmSession(user));
                amd.setDmAction(action);
                aMdDAO.save(amd);
                if (el.getAuditData() == null) {
                    el.setAuditData(new LinkedList<AuditMetadata>());
                }
                el.getAuditData().add(amd);

                //creo audit dei valori del metadato
                if (amd.getField().getType().equals(MetadataFieldType.ELEMENT_LINK)) {
                    try {
                        for (int i = 0; i < value.length; i++) {
                            Element lel = this.getElement(Long.parseLong((String) value[i]));
                            amd.setVal(lel);
                        }
                    } catch (NumberFormatException ex) {
                        //it.cineca.siss.axmr3.log.Log.info(getClass(),"Valore "+parameter+" non numerico per campo "+amd.getField().getTemplate().getName()+"."+amd.getField().getName());
                        amd.setVal(null);
                    }

                } else {
                    for (int i = 0; i < value.length; i++) {
                        amd.setVal(value[i]);
                    }
                }
                for (AuditValue val : amd.getValues()) {
                    val.setOld(false);
                    try {
                        aMdValDAO.save(val);
                    } catch (AxmrGenericException e) {
                        throw new RestException(e.getMessage(), txManager);
                    }
                }
                //creo il metadato
                mdata = new ElementMetadata();
                mdata.setField(field);
                mdata.setTemplate(template);
                if (field.getType().equals(MetadataFieldType.ELEMENT_LINK)) {
                    if (value.length == 0) mdata.setVal(null);
                    else {
                        for (int i = 0; i < value.length; i++) {
                            mdata.setVal(this.getElement(Long.parseLong(value[i])));
                        }
                    }
                } else {
                    for (int i = 0; i < value.length; i++) {
                        mdata.setVal(value[i]);
                    }
                }
                for (ElementMetadataValue val : mdata.getValues()) {
                    elMdValueDAO.save(val);
                    AuditValue av = new AuditValue();
                    av.setOld(false);
                    av.setDmSession(getActiveDmSession(user));
                    try {
                        av.setCode(val.getCode());
                    } catch (NullPointerException ex) {
                    }
                    try {
                        av.setDecode(val.getDecode());
                    } catch (NullPointerException ex) {
                    }
                    try {
                        av.setDate(val.getDate());
                    } catch (NullPointerException ex) {
                    }
                    try {
                        av.setElement_link(val.getElement_link());
                    } catch (NullPointerException ex) {
                    }
                    try {
                        av.setLongTextValue(val.getLongTextValue());
                    } catch (NullPointerException ex) {
                    }
                    try {
                        av.setTextValue(val.getTextValue());
                    } catch (NullPointerException ex) {
                    }
                    if (amd.getValues() != null) {
                        amd.getValues().add(av);
                    } else {
                        LinkedList<AuditValue> values = new LinkedList<AuditValue>();
                        values.add(av);
                        amd.setValues(values);
                    }
                    aMdValDAO.save(av);
                }
                aMdDAO.saveOrUpdate(amd); //salvo l'audit del metadato creato
                elMdDAO.save(mdata); //salvo il metadato
                el.getData().add(mdata); //aggiungo il metadato all'elemento
                //AGGIORNO LA DATA DI ULTIMA MODIFICA PER FAR REINDICIZZARE L'ELEMENTO
                it.cineca.siss.axmr3.log.Log.info(getClass(), "AGGIORNO LA DATA DI ULTIMA MODIFICA PER FAR REINDICIZZARE L'ELEMENTO " + new GregorianCalendar());
                recurseUpdateDt(el, user, new GregorianCalendar());
                docDAO.saveOrUpdate(el); //salvo l'oggetto
                addElidToBeUpdeated(el.getId(),true);
            }
        }
        commitTXSessionAndKeepAlive();
    }

    public DataManagementSession getDmSession(Long sessionId) {
        return dmSessionDAO.getById(sessionId);
    }

    public List<DataManagementAction> getDmActions(DataManagementSession dm) {
        Criteria c = dmActionDAO.getCriteria();
        c.add(Restrictions.eq("dmSession", dm)).addOrder(Order.desc("actionDt"));
        return c.list();
    }

    /**
     * ritorna tutti i record di audit relativi ad una sessione data management
     *
     * @param dm sessione data management
     * @return record di audit
     */
    public List<AuditMetadata> getDmAudits(DataManagementSession dm) {
        Criteria c = aMdDAO.getCriteria();
        c.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY).add(Restrictions.eq("dmSession", dm));
        return c.list();
    }

    public it.cineca.siss.axmr3.doc.types.ProcessDefinition getProcessDefinition(String processDefinitionId) {
        return new it.cineca.siss.axmr3.doc.types.ProcessDefinition(processEngine.getRepositoryService().getProcessDefinition(processDefinitionId));
    }

    public void terminateProcess(IUser user, String processInstanceId) throws AxmrGenericException {
        try {
            processEngine.getRuntimeService().deleteProcessInstance(processInstanceId, "DM_DELETE " + user.getUsername());
        } catch (Exception ex) {
            throw new AxmrGenericException("Errore nella terminazione del processo " + processInstanceId);
        }
    }

    public void registerDmAction(IUser user, Element el, String actionType, String specification) throws AxmrGenericException {
        DataManagementAction action = new DataManagementAction();
        action.setDmSession(getActiveDmSession(user));
        action.setAction(actionType);
        action.setObjId(el);
        action.setActionDt(new GregorianCalendar());
        action.setSpecification(specification);
        dmActionDAO.save(action);
    }

    /**
     * @param parentElementId id elemento padre
     * @param childTypeId     tipo elemento figlio da creare
     * @param userId          userid dell'utente da associare come creatore del figlio
     * @param user            user corrente
     * @return
     */
    public Element dmAddChild(Long parentElementId, Long childTypeId, String userId, String user) throws RestException {
        ElementType type = getDocDefinition(childTypeId);
        Element el = new Element();
        long position = 1;
        Criteria c = getDocDAO().getCriteria();
        c.add(Restrictions.eq("deleted", false));
        c.add(Restrictions.eq("type", type));
        Element parent = getElement(parentElementId);
        if (parent != null) {
            el.setParent(parent);
            c.add(Restrictions.eq("parent", parent));
            el.setDraft(parent.isDraft());
            registerEvent(user, parent, "AddChild");
        }
        c.setProjection(Projections.max("position"));
        if (type.isSortable()) {
            try {
                long lastPos = (Long) c.uniqueResult();
                position += lastPos;
            } catch (java.lang.NullPointerException ex) {
                it.cineca.siss.axmr3.log.Log.info(getClass(), ex.getMessage());
            }
        }
        el.setPosition(position);
        el.setType(type);
        el.setData(new LinkedList<ElementMetadata>());
        el.setCreationDt(new GregorianCalendar());
        el.setCreateUser(user);
        try {
            getDocDAO().saveOrUpdate(el);
            registerEvent(user, el, "DmCreateElement");
            setDefaultPermissionOnElement(user, el, type);
            addMetadataTemplateToNewElement(user, el, type);
        } catch (AxmrGenericException ex) {
            it.cineca.siss.axmr3.log.Log.info(getClass(), ex.getMessage());
            throw new RestException(ex.getMessage(), getTxManager());
        }
        return el;
    }

    /**
     * @param user  utente
     * @param acl   acl da modificare
     * @param field campo da modificare
     * @param value valore (true/false)
     * @throws AxmrGenericException
     */
    public void setAclValue(IUser user, Acl acl, String field, boolean value, Long policyId) throws AxmrGenericException {
        Policy pol = acl.getPolicy();
        PredefinedPolicy pp = null;
        if (!field.equals("removePolicy") && !field.equals("addPolicy")) {
            if (field.equals("canView")) {
                pol.setCanView(value);
            }
            if (field.equals("canCreate")) {
                pol.setCanCreate(value);
            }
            if (field.equals("canUpdate")) {
                pol.setCanUpdate(value);
            }
            if (field.equals("canAddComment")) {
                pol.setCanAddComment(value);
            }
            if (field.equals("canModerate")) {
                pol.setCanModerate(value);
            }
            if (field.equals("canDelete")) {
                pol.setCanDelete(value);
            }
            if (field.equals("canChangePermission")) {
                pol.setCanChangePermission(value);
            }
            if (field.equals("canAddChild")) {
                pol.setCanAddChild(value);
            }
            if (field.equals("canRemoveCheckOut")) {
                pol.setCanRemoveCheckOut(value);
            }
            if (field.equals("canLaunchProcess")) {
                pol.setCanLaunchProcess(value);
            }
            if (field.equals("canEnableTemplate")) {
                pol.setCanEnableTemplate(value);
            }
            if (field.equals("canBrowse")) {
                pol.setCanBrowse(value);
            }
            acl.setPolicyValue(pol.toInt());
        } else if (field.equals("addPolicy")) {
            pp = getPolicy(policyId);
            acl.setPredifinedPolicy(pp); //aggiungo la policy
        } else {
            acl.setPredifinedPolicy(null); //rimuovo la policy
        }
        try {
            aclDAO.saveOrUpdate(acl);
        } catch (AxmrGenericException e) {
            log.error(e.getMessage(), e);
        }
    }

    public void removeContainerFromACL(IUser user, Acl acl, Long containerId) throws AxmrGenericException {
        Collection<AclContainer> containers = acl.getContainers();
        List<AclContainer> found = new LinkedList<AclContainer>();
        for (AclContainer container : containers) {
            if (container.getId().equals(containerId)) {
                aclContainerDAO.delete(container);
            }
        }
    }

    //todo: modifica return metodo: id containers aggiunti
    public void addContainerToACL(IUser user, Acl acl, List<String> groups, List<String> users) throws AxmrGenericException {
        if (acl.getContainers() == null) {
            acl.setContainers(new LinkedList<AclContainer>());
            aclDAO.saveOrUpdate(acl);
        }
        for (String group : groups) {
            AclContainer cont = new AclContainer();
            cont.setAuthority(true);
            cont.setContainer(group);
            cont.setAcl(acl);
            aclContainerDAO.save(cont);
            acl.getContainers().add(cont);
        }
        for (String u : users) {
            AclContainer cont = new AclContainer();
            cont.setAuthority(false);
            cont.setContainer(u);
            cont.setAcl(acl);
            aclContainerDAO.save(cont);
            acl.getContainers().add(cont);
        }
        aclDAO.saveOrUpdate(acl);
    }

    public void addTemplateToACL(IUser user, Acl acl, String templateToAdd) throws AxmrGenericException {
        acl.setDetailTemplate(templateToAdd);
        aclDAO.saveOrUpdate(acl);
    }

    public void removeTemplateFromACL(IUser user, Acl acl) throws AxmrGenericException {
        acl.setDetailTemplate(null);
        aclDAO.saveOrUpdate(acl);
    }

    public String updateTemplateAclDM(Long aclId, TemplatePolicy pol) throws RestException {
        String retOldValues = "";
        try {
            TemplateAcl acl = tplAclDAO.getById((aclId));
            retOldValues += acl.getPolicy().tostring();
            acl.setPolicyValue(pol.toInt());
            acl.setPositionalAce(pol.toBinary());
            tplAclDAO.saveOrUpdate(acl);
            return retOldValues;
        } catch (AxmrGenericException ex) {
            throw new RestException(ex.getMessage(), txManager);
        }
    }

    public String addContainersToTemplateAcl(Long aclId, List<String> users, List<String> groups) throws RestException {
        String retNewValues = "";
        try {
            TemplateAcl acl = tplAclDAO.getById((aclId));
            Collection<TemplateAclContainer> containers = acl.getContainers();
            acl.setContainers(new LinkedList<TemplateAclContainer>());
            if (groups != null && groups.size() > 0) for (String group : groups) {
                boolean alreadyPresent = false;
                for (TemplateAclContainer c1 : containers) {
                    if (c1.getContainer().equals(group) && c1.isAuthority()) alreadyPresent = true;
                }
                if (!alreadyPresent) {
                    TemplateAclContainer c = new TemplateAclContainer();
                    c.setContainer(group);
                    c.setAuthority(true);
                    c.setAcl(acl);
                    tplAclContainerDAO.saveOrUpdate(c);
                    acl.getContainers().add(c);
                    retNewValues += c.isAuthority() ? "g:" : "u:";
                    retNewValues += c.getContainer() + ", ";

                }
            }
            if (users != null && users.size() > 0) for (String user : users) {
                boolean alreadyPresent = false;
                for (TemplateAclContainer c1 : containers) {
                    if (c1.getContainer().equals(user) && !c1.isAuthority()) alreadyPresent = true;
                }
                if (!alreadyPresent) {
                    TemplateAclContainer c = new TemplateAclContainer();
                    c.setContainer(user);
                    c.setAuthority(false);
                    c.setAcl(acl);
                    tplAclContainerDAO.saveOrUpdate(c);
                    acl.getContainers().add(c);
                    retNewValues += c.isAuthority() ? "g:" : "u:";
                    retNewValues += c.getContainer() + ", ";
                }
            }
            tplAclDAO.saveOrUpdate(acl);
            return retNewValues;
        } catch (AxmrGenericException ex) {
            throw new RestException(ex.getMessage(), txManager);
        }
    }

    public String removeContainerFromTemplateAcl(IUser user, Long aclId, Long containerId) throws RestException {
        String removedContainer = "";
        try {
            TemplateAcl acl = tplAclDAO.getById((aclId));
            Collection<TemplateAclContainer> containers = acl.getContainers();
            List<TemplateAclContainer> found = new LinkedList<TemplateAclContainer>();
            for (TemplateAclContainer container : containers) {
                if (container.getId().equals(containerId)) {
                    removedContainer += container.isAuthority() ? "g:" : "u:";
                    removedContainer += container.getContainer() + ", ";
                    tplAclContainerDAO.delete(container);
                }
            }
            return removedContainer;
        } catch (AxmrGenericException ex) {
            throw new RestException(ex.getMessage(), txManager);
        }
    }


    public String deleteTemplateAclDM(IUser user, Long elId, Long aclId) throws RestException {
        String retOldValues = "";
        try {
            Element el = getElement(elId);
            //if (!el.getUserPolicy(user).isCanChangePermission()) throw new RestException("FORBIDDEN", txManager);
            TemplateAcl acl = tplAclDAO.getById((aclId));
            for (TemplateAclContainer c : acl.getContainers()) {
                retOldValues += c.isAuthority() ? "g:" : "u:";
                retOldValues += c.getContainer() + ", ";
                tplAclContainerDAO.delete(c);

            }
            tplAclContainerDAO.getSession().flush();
            retOldValues += " " + acl.getPolicy().tostring();
            tplAclDAO.delete(acl);
            return retOldValues;
        } catch (AxmrGenericException ex) {
            throw new RestException(ex.getMessage(), txManager);
        }

    }

    public void recursivePermissions(IUser user, Long elId, TemplatePolicy basePolicy, String container, boolean isGroup) throws AxmrGenericException {
        Element el = this.getElement(elId);
        recursivePermissions(user, el, basePolicy, container, isGroup);
    }

    public void recursivePermissions(IUser user, Element el, TemplatePolicy basePolicy, String container, boolean isGroup) throws AxmrGenericException {
        if (!isDm(user)) {
            throw new RestException("User not allowed", txManager);
        }
        if (getActiveDmSession(user) == null) {
            throw new RestException("Data Management Session not active", txManager);
        }
        DataManagementSession dmSession = getActiveDmSession(user);
        log.warn("Assegno permessi ad elemento: " + el.getId());
        boolean setCanView = basePolicy.isCanView();
        boolean setCanUpdate = basePolicy.isCanUpdate();
        if (setCanUpdate) setCanView = true;
        String aclSpecification = "di tipo";
        if (setCanView) {
            aclSpecification += " V";
        }
        if (setCanUpdate) {
            aclSpecification += "M";
        }
        if (isGroup) {
            aclSpecification += " per gruppo ";
        } else {
            aclSpecification += " per utente ";
        }
        aclSpecification += container;

        boolean newAclNeeded = true;
        for (Acl acl : el.getAcls()) {
            boolean isContained = false;
            for (AclContainer ac : acl.getContainers()) {
                if (!ac.isAuthority() && ac.getContainer().equals("*")) {
                    isContained = true;
                }
                if (ac.isAuthority() == isGroup && ac.getContainer().toLowerCase().equals(container.toLowerCase())) {
                    isContained = true;
                }
            }
            if (isContained && acl.getPolicy().isCanView() == setCanView && acl.getPolicy().isCanUpdate() == setCanUpdate && acl.getPolicy().isCanBrowse() == setCanView) {
                newAclNeeded = false;
            }
        }
        if (newAclNeeded) {
            Acl newAcl = new Acl();
            newAcl.setElement(el);
            Policy p = new Policy();
            p.setCanView(setCanView);
            p.setCanUpdate(setCanUpdate);
            p.setCanBrowse(setCanView);
            newAcl.setPolicyValue(p.toInt());
            newAcl.setPositionalAce(p.toBinary());
            aclDAO.saveOrUpdate(newAcl);
            AclContainer ac = new AclContainer();
            ac.setAuthority(isGroup);
            ac.setContainer(container);
            ac.setAcl(newAcl);
            aclContainerDAO.saveOrUpdate(ac);
            el.setLastUpdateDt(new GregorianCalendar());
            el.setLastUpdateUser(user.getUsername());
            docDAO.saveOrUpdate(el);
            addElidToBeUpdeated(el.getId(),true);
            DataManagementAction dma = new DataManagementAction();
            dma.setDmSession(dmSession);
            dma.setAction("NEW_ACL");
            dma.setObjId(el);
            dma.setSpecification("Aggiunta ACL ricorsiva " + aclSpecification);
            dma.setActionDt(new GregorianCalendar());
            dmActionDAO.saveOrUpdate(dma);

        }
        boolean newTaclNeeded = true;
        for (ElementTemplate et : el.getElementTemplates()) {
            if (et.getTemplateAcls().size() > 0) {
                for (TemplateAcl tacl : et.getTemplateAcls()) {
                    boolean isContained = false;
                    for (TemplateAclContainer tac : tacl.getContainers()) {
                        if (!tac.isAuthority() && tac.getContainer().equals("*")) {
                            isContained = true;
                        }
                        if (tac.isAuthority() == isGroup && tac.getContainer().toLowerCase().equals(container.toLowerCase())) {
                            isContained = true;
                        }
                        if (isContained) log.warn(" - trovato templateAclContainer compatibile");
                    }
                    if (isContained && tacl.getPolicy().isCanView() == setCanView && tacl.getPolicy().isCanUpdate() == setCanUpdate) {
                        newTaclNeeded = false;
                    }
                }
                if (newTaclNeeded) {
                    TemplateAcl tacl = new TemplateAcl();
                    tacl.setElementTemplate(et);
                    TemplatePolicy tp = new TemplatePolicy();
                    tp.setCanView(setCanView);
                    tp.setCanUpdate(setCanUpdate);
                    tacl.setPolicyValue(tp.toInt());
                    tacl.setPositionalAce(tp.toBinary());
                    tplAclDAO.saveOrUpdate(tacl);
                    TemplateAclContainer tac = new TemplateAclContainer();
                    tac.setAcl(tacl);
                    tac.setAuthority(isGroup);
                    tac.setContainer(container);
                    tplAclContainerDAO.saveOrUpdate(tac);
                    DataManagementAction dma = new DataManagementAction();
                    dma.setDmSession(dmSession);
                    dma.setAction("NEW_TEMPLATE_ACL");
                    dma.setObjId(el);
                    dma.setSpecification("Aggiunta ACL ricorsiva per template " + et.getMetadataTemplate().getName() + " " + aclSpecification);
                    dma.setActionDt(new GregorianCalendar());
                    dmActionDAO.saveOrUpdate(dma);
                    el.setLastUpdateDt(new GregorianCalendar());
                    el.setLastUpdateUser(user.getUsername());
                    docDAO.saveOrUpdate(el);
                    addElidToBeUpdeated(el.getId(),true);
                }
            }
        }
        log.warn("permessi ASSEGNATI ad elemento: " + el.getId());
        for (Element child : el.getChildren()) {
            if (!child.isDeleted()) {
                log.warn("Assegno permessi al figlio: " + child.getId() + " elemento: " + el.getId());
                recursivePermissions(user, child, basePolicy, container, isGroup);
            }
        }
    }

    public HashMap<String, List<TemplateAcl>> getElementTemplatesACL(IUser user, Long elId) throws RestException {
        HashMap<String, List<TemplateAcl>> myTemplateAclList = new HashMap<String, List<TemplateAcl>>();
        boolean datamanager = false;
        for (IAuthority a : user.getAuthorities()) {
            if (a.getAuthority().equals("DATAMANAGER")) {
                datamanager = true;
            }
        }
        if (!datamanager) {
            throw new RestException("User not allowed", txManager);
        }

        Element el = this.getElement(elId);
        for (ElementTemplate et : el.getElementTemplates()) {
            if (!myTemplateAclList.containsKey(et.getMetadataTemplate().getId())) {
                myTemplateAclList.put(et.getMetadataTemplate().getName(), new LinkedList<TemplateAcl>());
            }
            myTemplateAclList.get(et.getMetadataTemplate().getName()).addAll(et.getTemplateAcls());
        }
        return myTemplateAclList;
    }

    public Long newTemplateAclDM(IUser user, Long elId, String templateName) throws RestException {
        try {
            Element el = getElement(elId);
            ElementTemplate tpl = null;
            for (ElementTemplate et : el.getElementTemplates()) {
                if (et.getMetadataTemplate().getName().equals(templateName)) {
                    tpl = et;
                }
            }
            //if (!el.getUserPolicy(user).isCanChangePermission()) throw new RestException("FORBIDDEN", txManager);
            TemplateAcl acl = new TemplateAcl();
            TemplatePolicy pol = new TemplatePolicy();
            pol.setCanCreate(false);
            pol.setCanDelete(false);
            pol.setCanUpdate(false);
            pol.setCanView(false);
            acl.setPolicyValue(pol.toInt());
            acl.setPositionalAce(pol.toBinary());
            acl.setElementTemplate(tpl);
            tplAclDAO.saveOrUpdate(acl);
            return acl.getId();
        } catch (AxmrGenericException ex) {
            throw new RestException(ex.getMessage(), txManager);
        }
    }

    public void deleteElementDM(IUser user, Element el) throws RestException {
        try {
            el.setDeleted(true);
            el.setDeletedBy(user.getUsername());
            el.setDeleteDt(new GregorianCalendar());
            registerEvent(user, el, "delete");
            for (Element child : el.getChildren()) {
                deleteElementDM(user, child);
            }
            docDAO.saveOrUpdate(el);
            addElidToBeUpdeated(el.getId(),true);
            if (el.getParent() != null) {
                recurseUpdateDt(el.getParent(), user, new GregorianCalendar());
            }
        } catch (AxmrGenericException e) {
            throw new RestException("ERROR", txManager);
        }
    }

    public HashMap<String, String> getFieldsValues(String fieldTotName, IUser user, Element el) {
        String[] split = fieldTotName.split("_");
        String templateName = split[0];
        String fieldName = split[1];
        Criteria c1 = this.getTemplateDAO().getCriteria();
        c1.add(Restrictions.eq("name", templateName));
        MetadataTemplate t = (MetadataTemplate) c1.uniqueResult();
        Criteria c2 = getMdFieldDAO().getCriteria();
        c2.add(Restrictions.eq("template", t));
        c2.add(Restrictions.eq("name", fieldName));
        MetadataField f = (MetadataField) c2.uniqueResult();
        return getFieldsValues(f, user, el);
    }

    public HashMap<String, String> getFieldsValues(Long fieldId, IUser user, Element el) {
        return getFieldsValues(getMdFieldDAO().getById(fieldId), user, el);
    }

    public LinkedHashMap<String, String> getFieldsValues(MetadataField field, IUser user, Element el) {
        if (field.isJson()) {
            return field.getAvailableValuesMap();
        } else {
            LinkedHashMap<String, String> result = new LinkedHashMap<String, String>();
            String sqlQuery = field.getAvailableValues();
            String pattern = "\\[(.*?)\\]";
            Pattern r = Pattern.compile(pattern);
            Matcher m = r.matcher(sqlQuery);
            while (m.find()) {
                if (m.group(1).toLowerCase().equals("userid")) {
                    sqlQuery = sqlQuery.replaceAll("\\[" + m.group(1) + "\\]", user.getUsername().toUpperCase());
                }
                if (m.group(1).toLowerCase().startsWith("obj") && el != null){
                    Element lp = el;
                    String[] levels = m.group(1).split("\\.");
                    //log.warn("LEVELS: "+levels.length);
                    for (int i = 1; i < levels.length; i++) {
                        //log.warn("CICLO I: "+i);
                        lp = lp.getParent();
                        if (i == levels.length - 1) {
                            //log.warn("SOSTITUISCO");
                            sqlQuery = sqlQuery.replaceAll("\\[" + m.group(1) + "\\]", lp.getId().toString());
                        }
                    }
                    log.warn("Query OBJ PARENT FINALE: " + sqlQuery);
                }
            }

            log.info("GETFIELDSVALUES_FIELD: "+field.getTemplateName()+"_"+field.getName());
            log.info("GETFIELDSVALUES_QUERY: "+sqlQuery);
            SQLQuery query = this.getAxmr3txManager().getSession("doc").createSQLQuery(sqlQuery);
            List<Object[]> rows = query.list();
            for (Object[] row : rows) {
                if (row[1] == null) result.put(row[0].toString(), "");
                else result.put(row[0].toString(), row[1].toString());
            }
            return result;
        }

    }

    public Element saveElementArray(IUser user, ElementType type, Map<String, String[]> data, byte[] file, String fileName, Long fileSize, String version, String date, String note, String autore, Element parent) throws RestException {
        return saveElementArray(user, type, data, file, fileName, fileSize, version, date, note, autore, parent, false);
    }


    public Element saveElementArray(String user, ElementType type, Map<String, String[]> data, byte[] file, String fileName, Long fileSize, String version, String date, String note, String autore, Element parent) throws RestException {
        return saveElementArray(user, type, data, file, fileName, fileSize, version, date, note, autore, parent, false);
    }

    public Element saveElementArray(IUser user, ElementType type, Map<String, String[]> data, byte[] file, String fileName, Long fileSize, String version, String date, String note, String autore, Element parent, boolean cloning) throws RestException {
        Policy pol = new Policy();
        if (parent == null) {
            if (!this.checkElementTypePolicy(pol, user, type.getId())) throw new RestException("NotPermitted", 1);
        }
        return saveElementArray(user.getUsername(), user, type, data, file, fileName, fileSize, version, date, note, autore, parent, cloning);
    }

    public Element saveElementArray(String user, ElementType type, Map<String, String[]> data, byte[] file, String fileName, Long fileSize, String version, String date, String note, String autore, Element parent, boolean cloning) throws RestException {
        return saveElementArray(user, null, type, data, file, fileName, fileSize, version, date, note, autore, parent, cloning);
    }

    public Element saveElementArray(String user, IUser userInstance, ElementType type, Map<String, String[]> data, byte[] file, String fileName, Long fileSize, String version, String date, String note, String autore, Element parent, boolean cloning) throws RestException {
        try {
            Long groupId = null;
            Element looking4Group = null;
            ElementGroup itemInGroup = null;
            Long groupLevel = type.getGroupUpLevel();
            Element el = new Element();
            Policy pol = new Policy();
            pol.setCanCreate(true);
            long position = 1;
            Criteria c = docDAO.getCriteria();
            c.add(Restrictions.eq("deleted", false));
            c.add(Restrictions.eq("type", type));
            if (parent != null) {
                el.setParent(parent);
                c.add(Restrictions.eq("parent", parent));
                el.setDraft(parent.isDraft());
                registerEvent(user, parent, "AddChild");
                recurseUpdateDt(parent, user, new GregorianCalendar());
            }
            c.setProjection(Projections.max("position"));
            if (type.isSortable()) {
                try {
                    long lastPos = (Long) c.uniqueResult();
                    position += lastPos;
                } catch (java.lang.NullPointerException ex) {
                    log.info(ex.getMessage());
                }
            }
            el.setPosition(position);
            el.setType(type);
            el.setData(new LinkedList<ElementMetadata>());
            el.setCreationDt(new GregorianCalendar());
            el.setCreateUser(user);
            docDAO.saveOrUpdate(el);
            addElidToBeUpdeated(el.getId(),true);
            registerEvent(user, el, "CreateElement");
            setDefaultPermissionOnElement(user, el, type);
            addMetadataTemplateToNewElement(user, el, type);
            Iterator<String> dit = data.keySet().iterator();
            while (dit.hasNext()) {
                String key = dit.next();
                //it.cineca.siss.axmr3.log.Log.info(getClass(),"SaveElement - "+key+" - "+data.get(key));
            }

            updateElementMetaDataArray(user, userInstance, el, data, "CREATE");

            attachFile(user, el, file, fileName, fileSize, version, date, note, autore, "CREATE");
            if (!cloning) {
                for (ElementTypeAssociatedWorkflow awf : el.getType().getAssociatedWorkflows()) {
                    if (awf.isEnabled() && awf.isStartOnCreate()) {
                        Long elId = el.getId();
                        txManager.getTxs().get("doc").commit();
                        if (!txManager.getSessions().get("doc").isOpen()) {
                            //it.cineca.siss.axmr3.log.Log.info(getClass(),"La sessione è chiusa, la riapro");
                            it.cineca.siss.axmr3.log.Log.info(getClass(), "Apro la sessione 4 " + this.getClass().getCanonicalName());
                            txManager.getSessions().put("doc", txManager.getSessionFactories().get("doc").openSession());
                            it.cineca.siss.axmr3.log.Log.info(getClass(), "Begin Transaction 7 " + this.getClass().getCanonicalName());
                            txManager.getTxs().put("doc", txManager.getSessions().get("doc").beginTransaction());
                        } else {
                            //it.cineca.siss.axmr3.log.Log.info(getClass(),"La sessione è aperta, controllo la transazione");
                            if (!txManager.getTxs().get("doc").isActive()) {
                                //it.cineca.siss.axmr3.log.Log.info(getClass(),"La transazione non è attiva 1");
                                it.cineca.siss.axmr3.log.Log.info(getClass(), "Begin Transaction 8 " + this.getClass().getCanonicalName());
                                txManager.getTxs().put("doc", txManager.getSessions().get("doc").beginTransaction());
                            }
                        }
                        el = this.getElement(elId);
                        this.startProcess(user, el, awf.getProcessKey());

                    }
                }
            }
            if (groupLevel != null && groupLevel > 0) {

                looking4Group = el;
                for (int i = 1; i <= groupLevel; i++) {
                    looking4Group = looking4Group.getParent();
                }
                if (!isInGroup(looking4Group.getId(), el.getId())) {
                    itemInGroup = new ElementGroup();
                    itemInGroup.setGroupId(looking4Group.getId());
                    itemInGroup.setItem(el.getId());
                    groupDAO.save(itemInGroup);
                }
            }
            commitTXSessionAndKeepAlive();
            return el;
        } catch (AxmrGenericException e) {
            log.error(e.getMessage(), e);
            throw new RestException(e.getMessage(), txManager);
        }
    }


    /*Gestione set ACL elemento*/

    public void setElementPolicy(IUser requestor, Long id, String ftl, String permissionCommaSeparated, boolean isAuthority, String container) throws AxmrGenericException {
        Element el = this.getElement(id);
        setElementPolicy(requestor, el, ftl, permissionCommaSeparated, isAuthority, container);
    }

    public void setElementPolicy(IUser requestor, Element el, String ftl, String permissionCommaSeparated, boolean isAuthority, String container) throws AxmrGenericException {
        setElementPolicy(requestor, el, ftl, Policy.createPolicyByCommaSeparatedString(permissionCommaSeparated), isAuthority, container);
    }

    public void setElementPolicy(IUser requestor, Long id, String ftl, Policy pol, boolean isAuthority, String container) throws AxmrGenericException {
        Element el = this.getElement(id);
        setElementPolicy(requestor, el, ftl, pol, isAuthority, container);
    }

    public void setElementPolicy(IUser requestor, Element el, String ftl, Policy pol, boolean isAuthority, String container) throws AxmrGenericException {
        if (el.getUserPolicy(requestor).isCanChangePermission()) {
            setElementPolicy(el, ftl, pol, isAuthority, container);
        } else {
            throw new AxmrGenericException("FORBIDDEN");
        }
    }

    public void setElementPolicy(Element el, String ftl, Policy pol, boolean isAuthority, String container) throws AxmrGenericException {
        setElementPolicy(el, ftl, pol, isAuthority, container, false);
    }

    public void setElementPolicy(Element el, String ftl, String permissionCommaSeparated, boolean isAuthority, String container) throws AxmrGenericException {
        setElementPolicy(el, ftl, Policy.createPolicyByCommaSeparatedString(permissionCommaSeparated), isAuthority, container);
    }

    public void setElementPolicy(Long id, String ftl, String permissionCommaSeparated, boolean isAuthority, String container) throws AxmrGenericException {
        Element el = this.getElement(id);
        setElementPolicy(el, ftl, Policy.createPolicyByCommaSeparatedString(permissionCommaSeparated), isAuthority, container);
    }

    public void setElementPolicy(IUser requestor, Long id, String ftl, String permissionCommaSeparated, boolean isAuthority, String container, boolean recursive) throws AxmrGenericException {
        Element el = this.getElement(id);
        setElementPolicy(requestor, el, ftl, permissionCommaSeparated, isAuthority, container, recursive);
    }

    public void setElementPolicy(IUser requestor, Element el, String ftl, String permissionCommaSeparated, boolean isAuthority, String container, boolean recursive) throws AxmrGenericException {
        setElementPolicy(requestor, el, ftl, Policy.createPolicyByCommaSeparatedString(permissionCommaSeparated), isAuthority, container);
    }

    public void setElementPolicy(IUser requestor, Long id, String ftl, Policy pol, boolean isAuthority, String container, boolean recursive) throws AxmrGenericException {
        Element el = this.getElement(id);
        setElementPolicy(requestor, el, ftl, pol, isAuthority, container, recursive);
    }

    public void setElementPolicy(IUser requestor, Element el, String ftl, Policy pol, boolean isAuthority, String container, boolean recursive) throws AxmrGenericException {
        if (el.getUserPolicy(requestor).isCanChangePermission()) {
            setElementPolicy(el, ftl, pol, isAuthority, container, recursive);
        } else {
            throw new AxmrGenericException("FORBIDDEN");
        }
    }

    /**
     * Metodo per gestione dei permessi per gli elementi
     *
     * La logica da implemetare deve essere la seguente:
     * - cercare il Container da attivare in quelli che sono già definiti per l'oggetto (per ogni occorenza)
     * - se presente controllare che la regola di accesso sia la stessa che si vuole definire
     * - se la regola è la stessa NON FARE NULLA ma marcare la regola-associata da inserire come già presente
     * - se la regola è diversa disassociare il container dalla regola
     * - se la regola-associata è già presente uscire, altrimenti
     * - cercare regola ACL già definita sull'oggetto con stessa policy
     * - se trovo regola associo container a regola esistente
     * - se non trovo regola la creo ed associo container a regola appena creata
     * Bisogna cercare una ACL già definita sull'oggetto
     *
     * @param el
     * @param ftl
     * @param pol
     * @param isAuthority
     * @param container
     * @param recursive
     * @throws AxmrGenericException
     */
    public void setElementPolicy(Element el, String ftl, Policy pol, boolean isAuthority, String container, boolean recursive) throws AxmrGenericException {
        Logger.getLogger(this.getClass()).info("Devo impostare i permessi per "+el.getId()+" al container: "+container);
        boolean sameRuleAssoc = false;
        boolean isFtl = (ftl != null && !ftl.isEmpty());
        if (container != null && !container.isEmpty()) {
            LinkedList<AclContainer> containerToBeDeleted = new LinkedList<AclContainer>();
            LinkedList<Acl> aclToBeDeleted = new LinkedList<Acl>();
            LinkedList<Acl> aclToBeUpdated = new LinkedList<Acl>();
            for (Acl a : el.getAcls()) {
                boolean aclContainerFound = false;
                AclContainer aclContainer = null;

                for (AclContainer c : a.getContainers()) {
                    if (c.isAuthority() == isAuthority && c.getContainer().equals(container)) {
                        Logger.getLogger(this.getClass()).info("---[setElementPolicy - debug 1] Trovato Acl Container " + container + " con id:" + c.getId());
                        /* Trovo container già associato ad una regola esistente*/
                        aclContainerFound = true;
                        Logger.getLogger(this.getClass()).info("---[setElementPolicy] Trovato Acl Container " + container + " con id:" + c.getId() + " per elId:" + el.getId());
                        aclContainer = c;
                    }
                }
                if (aclContainerFound) {
                    Logger.getLogger(this.getClass()).info("---[setElementPolicy - debug 2] aclContainerFound:true aclContainerId:"+aclContainer.getId()+" per elId:"+el.getId());
                    boolean aclHasFtl = (a.getDetailTemplate() != null && !a.getDetailTemplate().isEmpty());
                    boolean checkFtl = false;
                    if (aclHasFtl && isFtl && a.getDetailTemplate().equals(ftl)) {
                        checkFtl = true;
                    }
                    if (!aclHasFtl && !isFtl) {
                        checkFtl = true;
                    }
                    if (a.getPositionalAce().equals(pol.toBinary()) && checkFtl) {
                        Logger.getLogger(this.getClass()).info("---[setElementPolicy - debug 3] permessi uguali e ftl uguale, non faccio nulla per elId:"+el.getId());
                        /* La regola a cui è associato il container è uguale a quella che devo applicare, quindi non facio nulla e imposto flag per non fare nulla*/
                        sameRuleAssoc = true;
                    } else {
                        /* Il container è associato ad una regola diversa, quindi disassocio il container dalla regola, per evitare conflitti con i nuovi permessi che devo impostare*/
                        //getAclContainerDAO().delete(aclContainer);
                        Logger.getLogger(this.getClass()).info("---[setElementPolicy - debug 4] regola diversa associata, la flaggo da eliminare se contiene un solo container");
                        containerToBeDeleted.add(aclContainer);
                        if (a.getContainers().size() == 1) {
                            if (!aclToBeDeleted.contains(a)) {
                                Logger.getLogger(this.getClass()).info("---[setElementPolicy - debug 4.1] regola diversa associata, la flaggo da ELIMINARE se contiene un solo container (true) "+a.getId()+" per elId:"+el.getId());
                                for (AclContainer ac : a.getContainers()) {
                                    Logger.getLogger(this.getClass()).info("---[setElementPolicy - debug 4.2] Elimino il container associato");
                                    getAclContainerDAO().delete(ac);
                                }
                                a.setContainers(new LinkedList<AclContainer>());
                                aclToBeDeleted.add(a);
                            }
                        } else {
                            Logger.getLogger(this.getClass()).info("---[setElementPolicy - debug 5] regola diversa associata, la flaggo da AGGIORNARE se contiene un solo container (true) "+a.getId()+" per elId:"+el.getId());

                            if (!aclToBeUpdated.contains(a)) aclToBeUpdated.add(a);
                        }
                    }
                }
            }
            for (AclContainer c : containerToBeDeleted) {
                getAclContainerDAO().delete(c);
            }

            for (Acl a : aclToBeDeleted) {
                el.getAcls().remove(a);
                getAclDAO().delete(a);
            }
            docDAO.saveOrUpdate(el);
            addElidToBeUpdeated(el.getId(),true);
            el=this.getElement(el.getId());
            for (Acl a : aclToBeUpdated) {
                getAclDAO().saveOrUpdate(a);
            }

            if (!sameRuleAssoc) {
                /*Non ho trovato combinazione regole/container uguali a quelle da settare, quindi cerco regole uguali a cui aggiungere il container*/
                boolean sameRuleFound = false;
                for (Acl a : el.getAcls()) {
                    boolean aclHasFtl = (a.getDetailTemplate() != null && !a.getDetailTemplate().isEmpty());
                    boolean checkFtl = false;
                    if (aclHasFtl && isFtl && a.getDetailTemplate().equals(ftl)) {
                        checkFtl = true;
                    }
                    if (!aclHasFtl && !isFtl) {
                        checkFtl = true;
                    }
                    if (!sameRuleFound && a.getPositionalAce().equals(pol.toBinary()) && checkFtl) {
                        /*Ho trovato una regola uguale, quindi ci associo il container e imposto flag per non rifarlo con eventuali altre regole simili*/
                        Logger.getLogger(this.getClass()).info("---[setElementPolicy - debug 6] trovata regola uguale "+a.getId()+" e ci creo nuovo container per elId:"+el.getId());
                        sameRuleFound = true;
                        AclContainer c = new AclContainer();
                        c.setAuthority(isAuthority);
                        c.setContainer(container);
                        c.setAcl(a);
                        getAclContainerDAO().saveOrUpdate(c);
                        if (a.getContainers() == null) a.setContainers(new LinkedList<AclContainer>());
                        a.getContainers().add(c);
                        getAclDAO().saveOrUpdate(a);
                        Logger.getLogger(this.getClass()).info("---[setElementPolicy - debug 6.1] nuovo container "+c.getId()+" per regola "+a.getId()+" per elId:"+el.getId());
                    }
                }
                if (!sameRuleFound) {
                    Logger.getLogger(this.getClass()).info("---[setElementPolicy - debug 7] NON trovata regola uguale creo regola e contasiner per elId:"+el.getId());
                    /* non ho trovato regole uguali, quindi creo sia acl che container da associare*/
                    Acl a = new Acl();
                    a.setPolicyValue(pol.toInt());
                    a.setPositionalAce(pol.toBinary());
                    a.setElement(el);
                    if (isFtl) {
                        a.setDetailTemplate(ftl);
                    }
                    getAclDAO().saveOrUpdate(a);
                    Logger.getLogger(this.getClass()).info("---[setElementPolicy - debug 7.1] nuova regola "+a.getId()+" per elId:"+el.getId());

                    a.setContainers(new LinkedList<AclContainer>());
                    AclContainer c = new AclContainer();
                    c.setAuthority(isAuthority);
                    c.setContainer(container);
                    c.setAcl(a);
                    getAclContainerDAO().saveOrUpdate(c);
                    a.getContainers().add(c);
                    getAclDAO().saveOrUpdate(a);
                    Logger.getLogger(this.getClass()).info("---[setElementPolicy - debug 7.2] nuovo container "+c.getId()+" per nuova regola "+a.getId()+" per elId:"+el.getId());
                }
            }
            if (recursive) {
                for (Element child : el.getChildren()) {
                    setElementPolicy(child, null, pol, isAuthority, container, recursive);
                }
            }
        }
    }

    public void removeElementPolicy(Element el, String ftl, boolean isAuthority, String container) throws AxmrGenericException {
        removeElementPolicy(el, ftl, isAuthority, container, false);
    }

    public void removeElementPolicy(Element el, String ftl, boolean isAuthority, String container, boolean recursive) throws AxmrGenericException {
        Logger.getLogger(this.getClass()).info("Devo revocare i permessi per "+el.getId()+" al container: "+container);
        boolean sameRuleAssoc = false;
        boolean isFtl = (ftl != null && !ftl.isEmpty());
        if (container != null && !container.isEmpty()) {
            LinkedList<AclContainer> containerToBeDeleted = new LinkedList<AclContainer>();
            LinkedList<Acl> aclToBeDeleted = new LinkedList<Acl>();
            LinkedList<Acl> aclToBeUpdated = new LinkedList<Acl>();
            for (Acl a : el.getAcls()) {
                boolean aclContainerFound = false;
                AclContainer aclContainer = null;

                for (AclContainer c : a.getContainers()) {
                    if (c.isAuthority() == isAuthority && c.getContainer().equals(container)) {
                        Logger.getLogger(this.getClass()).info("---[removeElementPolicy - debug 1] Trovato Acl Container " + container + " con id:" + c.getId());
                        /* Trovo container già associato ad una regola esistente*/
                        aclContainerFound = true;
                        Logger.getLogger(this.getClass()).info("---[removeElementPolicy] Trovato Acl Container " + container + " con id:" + c.getId() + " per elId:" + el.getId());
                        aclContainer = c;
                    }
                }
                if (aclContainerFound) {
                    Logger.getLogger(this.getClass()).info("---[removeElementPolicy - debug 2] aclContainerFound:true aclContainerId:"+aclContainer.getId()+" per elId:"+el.getId());
                    boolean aclHasFtl = (a.getDetailTemplate() != null && !a.getDetailTemplate().isEmpty());

                    /* Devo comunque disassociare il container dalla regola, per eliminare i permessi*/
                    //getAclContainerDAO().delete(aclContainer);
                    Logger.getLogger(this.getClass()).info("---[removeElementPolicy - debug 4] la flaggo da eliminare se contiene un solo container");
                    containerToBeDeleted.add(aclContainer);
                    if (a.getContainers().size() == 1) {
                        if (!aclToBeDeleted.contains(a)) {
                            Logger.getLogger(this.getClass()).info("---[removeElementPolicy - debug 4.1] regola diversa associata, la flaggo da ELIMINARE se contiene un solo container (true) "+a.getId()+" per elId:"+el.getId());
                            for (AclContainer ac : a.getContainers()) {
                                Logger.getLogger(this.getClass()).info("---[removeElementPolicy - debug 4.2] Elimino il container associato");
                                getAclContainerDAO().delete(ac);
                            }
                            a.setContainers(new LinkedList<AclContainer>());
                            aclToBeDeleted.add(a);
                        }
                    } else {
                        Logger.getLogger(this.getClass()).info("---[removeElementPolicy - debug 5] la flaggo da AGGIORNARE se contiene più container (true) "+a.getId()+" per elId:"+el.getId());

                        if (!aclToBeUpdated.contains(a)) aclToBeUpdated.add(a);
                    }
                }
            }
            for (AclContainer c : containerToBeDeleted) {
                getAclContainerDAO().delete(c);
            }

            for (Acl a : aclToBeDeleted) {
                el.getAcls().remove(a);
                getAclDAO().delete(a);
            }
            docDAO.saveOrUpdate(el);
            addElidToBeUpdeated(el.getId(),true);
            el=this.getElement(el.getId());
            for (Acl a : aclToBeUpdated) {
                getAclDAO().saveOrUpdate(a);
            }

            if (recursive) {
                for (Element child : el.getChildren()) {
                    removeElementPolicy(child, null, isAuthority, container, recursive);
                }
            }
        }
    }


    public void setElementPolicyOld(Element el, String ftl, Policy pol, boolean isAuthority, String container, boolean recursive) throws AxmrGenericException {
        if (container != null && !container.isEmpty()) {
            boolean aclContainerFound = false;
            boolean toCreate = true;
            for (Acl a : el.getAcls()) {
                aclContainerFound = false;
                AclContainer aclContainer = null;
                for (AclContainer c : a.getContainers()) {
                    if (c.isAuthority() == isAuthority && c.getContainer().equals(container)) {
                        aclContainerFound = true;
                        Logger.getLogger(this.getClass()).info("---Trovato Acl Container " + container + " con id:" + c.getId());
                        aclContainer = c;
                    }
                }
                if (aclContainerFound) {
                    if (a.getContainers().size() == 1) {
                        Logger.getLogger(this.getClass()).info("---Acl con id: " + a.getId() + " contiene il solo container con id: " + aclContainer.getId() + " quindi reimposto i permessi");
                        a.setPolicyValue(pol.toInt());
                        a.setPositionalAce(pol.toBinary());
                        if (ftl != null) {
                            a.setDetailTemplate(ftl);
                        }
                        getAclDAO().saveOrUpdate(a);
                        toCreate = false;
                    } else {
                        Logger.getLogger(this.getClass()).info("---Acl con id: " + a.getId() + " contiene anche altri container, quindi elimino il solo container con id: " + aclContainer.getId());
                        getAclContainerDAO().delete(aclContainer);
                    }
                }
            }
            if (toCreate) {
                Logger.getLogger(this.getClass()).info("---Acl e container con da creare per elemento: " + el.getId() + " - Container: " + container + " - Permessi: " + pol.toInt() + ")");
                Acl a = new Acl();
                a.setPolicyValue(pol.toInt());
                a.setPositionalAce(pol.toBinary());
                a.setElement(el);
                getAclDAO().saveOrUpdate(a);
                a.setContainers(new LinkedList<AclContainer>());
                AclContainer c = new AclContainer();
                c.setAuthority(isAuthority);
                c.setContainer(container);
                c.setAcl(a);
                getAclContainerDAO().saveOrUpdate(c);
                a.getContainers().add(c);
                getAclDAO().saveOrUpdate(a);
            }
            if (recursive) {
                for (Element child : el.getChildren()) {
                    setElementPolicy(child, null, pol, isAuthority, container, recursive);
                }
            }
        }
    }

    public void setElementPolicy(Element el, String ftl, String permissionCommaSeparated, boolean isAuthority, String container, boolean recursive) throws AxmrGenericException {
        setElementPolicy(el, ftl, Policy.createPolicyByCommaSeparatedString(permissionCommaSeparated), isAuthority, container, recursive);
    }

    public void setElementPolicy(Long id, String ftl, String permissionCommaSeparated, boolean isAuthority, String container, boolean recursive) throws AxmrGenericException {
        Element el = this.getElement(id);
        setElementPolicy(el, ftl, Policy.createPolicyByCommaSeparatedString(permissionCommaSeparated), isAuthority, container, recursive);
    }

















    /*Gestione set ACL template*/

    public void setTemplatePolicy(IUser requestor, Long id, String templateName, String permissionCommaSeparated, boolean isAuthority, String container) throws AxmrGenericException {
        Element el = this.getElement(id);
        setTemplatePolicy(requestor, el, templateName, permissionCommaSeparated, isAuthority, container);
    }

    public void setTemplatePolicy(IUser requestor, Element el, String templateName, String permissionCommaSeparated, boolean isAuthority, String container) throws AxmrGenericException {
        setTemplatePolicy(requestor, el, templateName, TemplatePolicy.createPolicyByCommaSeparatedString(permissionCommaSeparated), isAuthority, container);
    }

    public void setTemplatePolicy(IUser requestor, Long id, String templateName, TemplatePolicy pol, boolean isAuthority, String container) throws AxmrGenericException {
        Element el = this.getElement(id);
        setTemplatePolicy(requestor, el, templateName, pol, isAuthority, container);
    }

    public void setTemplatePolicy(IUser requestor, Element el, String templateName, TemplatePolicy pol, boolean isAuthority, String container) throws AxmrGenericException {
        if (el.getUserPolicy(requestor).isCanChangePermission()) {
            setTemplatePolicy(el, templateName, pol, isAuthority, container);
        } else {
            throw new AxmrGenericException("FORBIDDEN");
        }
    }

    public void setTemplatePolicy(IUser requestor, Element el, MetadataTemplate t, String permissionCommaSeparated, boolean isAuthority, String container) throws AxmrGenericException {
        setTemplatePolicy(requestor, el, t.getName(), permissionCommaSeparated, isAuthority, container);
    }

    public void setTemplatePolicy(IUser requestor, Element el, MetadataTemplate t, TemplatePolicy pol, boolean isAuthority, String container) throws AxmrGenericException {
        setTemplatePolicy(requestor, el, t.getName(), pol, isAuthority, container);
    }

    public void setTemplatePolicy(Element el, MetadataTemplate t, TemplatePolicy pol, boolean isAuthority, String container) throws AxmrGenericException {
        setTemplatePolicy(el, t.getName(), pol, isAuthority, container);
    }

    public void setTemplatePolicy(Element el, String templateName, TemplatePolicy pol, boolean isAuthority, String container) throws AxmrGenericException {
        if (container != null && !container.isEmpty()) {
            ElementTemplate et = null;
            for (ElementTemplate et_ : el.getElementTemplates()) {
                if (et_.getMetadataTemplate().getName().equals(templateName)) et = et_;
            }
            if (et != null) {
                boolean aclContainerFound = false;
                boolean toCreate = true;
                for (TemplateAcl a : et.getTemplateAcls()) {
                    aclContainerFound = false;
                    TemplateAclContainer aclContainer = null;
                    for (TemplateAclContainer c : a.getContainers()) {
                        if (c.isAuthority() == isAuthority && c.getContainer().equals(container)) {
                            aclContainerFound = true;
                            Logger.getLogger(this.getClass()).info("--Trovato ACL Container " + container + " con id:" + c.getId());
                            aclContainer = c;
                        }
                    }
                    if (aclContainerFound) {
                        if (a.getContainers().size() == 1) {
                            Logger.getLogger(this.getClass()).info("---Acl con id: " + a.getId() + " contiene il solo container con id: " + aclContainer.getId() + " quindi reimposto i permessi");
                            a.setPolicyValue(pol.toInt());
                            a.setPositionalAce(pol.toBinary());
                            getTplAclDAO().saveOrUpdate(a);
                            toCreate = false;
                        } else {
                            Logger.getLogger(this.getClass()).info("---Acl con id: " + a.getId() + " contiene anche altri container, quindi elimino il solo container con id: " + aclContainer.getId());
                            getTplAclContainerDAO().delete(aclContainer);
                        }
                    }
                }
                if (toCreate) {
                    Logger.getLogger(this.getClass()).info("---Acl e container con da creare template: " + templateName + " - Container: " + container + " - Permessi: " + pol.toInt());
                    TemplateAcl a = new TemplateAcl();
                    a.setPolicyValue(pol.toInt());
                    a.setPositionalAce(pol.toBinary());
                    a.setElementTemplate(et);
                    getTplAclDAO().saveOrUpdate(a);
                    a.setContainers(new LinkedList<TemplateAclContainer>());
                    TemplateAclContainer c = new TemplateAclContainer();
                    c.setAuthority(isAuthority);
                    c.setContainer(container);
                    c.setAcl(a);
                    getTplAclContainerDAO().saveOrUpdate(c);
                    a.getContainers().add(c);
                    getTplAclDAO().saveOrUpdate(a);
                }
            }
        }
    }

    public void setTemplatePolicy(Element el, String templateName, String permissionCommaSeparated, boolean isAuthority, String container) throws AxmrGenericException {
        setTemplatePolicy(el, templateName, TemplatePolicy.createPolicyByCommaSeparatedString(permissionCommaSeparated), isAuthority, container);
    }

    public void setTemplatePolicy(Long id, MetadataTemplate t, String permissionCommaSeparated, boolean isAuthority, String container) throws AxmrGenericException {
        Element el = this.getElement(id);
        setTemplatePolicy(el, t.getName(), TemplatePolicy.createPolicyByCommaSeparatedString(permissionCommaSeparated), isAuthority, container);
    }

    public void setTemplatePolicy(Long id, String templateName, String permissionCommaSeparated, boolean isAuthority, String container) throws AxmrGenericException {
        Element el = this.getElement(id);
        setTemplatePolicy(el, templateName, TemplatePolicy.createPolicyByCommaSeparatedString(permissionCommaSeparated), isAuthority, container);
    }

    public void removeTemplatePolicy(Element el, String templateName, boolean isAuthority, String container) throws AxmrGenericException {
        if (container != null && !container.isEmpty()) {
            ElementTemplate et = null;
            for (ElementTemplate et_ : el.getElementTemplates()) {
                if (et_.getMetadataTemplate().getName().equals(templateName)) et = et_;
            }
            if (et != null) {
                LinkedList<TemplateAcl> tplAclToBeRemoved = new LinkedList<TemplateAcl>();
                for (TemplateAcl a : et.getTemplateAcls()) {
                    boolean aclContainerFound = false;
                    TemplateAclContainer aclContainer = null;
                    for (TemplateAclContainer c : a.getContainers()) {
                        if (c.isAuthority() == isAuthority && c.getContainer().equals(container)) {
                            aclContainerFound = true;
                            Logger.getLogger(this.getClass()).info("--[removeTemplatePolicy] Trovato ACL Container " + container + " con id:" + c.getId());
                            aclContainer = c;
                        }
                    }
                    if (aclContainerFound) {
                        if (a.getContainers().size() == 1) {
                            Logger.getLogger(this.getClass()).info("---[removeTemplatePolicy] Acl con id: " + a.getId() + " contiene il solo container con id: " + aclContainer.getId() + " quindi reimposto i permessi");
                            tplAclToBeRemoved.add(a);
                        }
                        getTplAclContainerDAO().delete(aclContainer);
                    }
                }

                for (TemplateAcl a : tplAclToBeRemoved) {
                    et.getTemplateAcls().remove(a);
                    getTplAclDAO().delete(a);
                }
                getElTplDAO().saveOrUpdate(et);
            }
        }
    }


    public void updateFile(IUser user, Long elementId, String filename, String version, String author) throws AxmrGenericException {
        Element el = this.getElement(elementId);
        if (el.getUserPolicy(user).isCanUpdate()) {
            File file = el.getFile();
            if (filename != null) file.setFileName(filename);
            if (version != null) file.setVersion(version);
            if (author != null) file.setAutore(author);
            fileSpecDAO.saveOrUpdate(file);
        } else {
            throw new AxmrGenericException("Operazione non permessa");
        }
    }

    /*Aggiunte per compatibilità CTC*/
    public Boolean ordDetachedCriteria(DetachedCriteria c, String field, String order) {
        String regexParent = "^parent.*$";
        String regexParent2 = "^parent\\.";
        it.cineca.siss.axmr3.log.Log.info(getClass(), "Sto per cercare il template dal nome " + field);
        Boolean parent = field.matches(regexParent);
        String parentPrefix = "";
        if (parent) {
            it.cineca.siss.axmr3.log.Log.info(getClass(), "riconosco che è sul padre ");
            parentPrefix = "parent.";
        } else {
            it.cineca.siss.axmr3.log.Log.info(getClass(), "NON riconosco che è sul padre ");
        }
        String key = field.replaceAll(regexParent2, "");
        String template = "";
        String fieldName = "";
        String[] searchFilterSplitted = key.split("_");
        it.cineca.siss.axmr3.log.Log.info(getClass(), "Sto per ordinare per " + key + " split " + String.valueOf(searchFilterSplitted.length));
        if (searchFilterSplitted.length >= 2) {
            template = searchFilterSplitted[0];
            fieldName = searchFilterSplitted[1];

        }
        it.cineca.siss.axmr3.log.Log.info(getClass(), "Sto per cercare il template dal nome " + template);
        MetadataTemplate t = MetadataTemplate.getTemplateByName(templateDAO, template);
        if (t == null) {
            it.cineca.siss.axmr3.log.Log.info(getClass(), "Non trovo il template " + template);
            return false;
        } else {
            it.cineca.siss.axmr3.log.Log.info(getClass(), "Trovato il template dal nome " + template + " con id:" + t.getId());
            String fieldProperty = "";
            it.cineca.siss.axmr3.log.Log.info(getClass(), "Sto per cercare il campo " + fieldName);
            MetadataField f = t.byFieldName(fieldName);
            if (f == null) {
                it.cineca.siss.axmr3.log.Log.info(getClass(), "Non trovo il campo " + fieldName);
                return false;
            } else {
                it.cineca.siss.axmr3.log.Log.info(getClass(), "Trovato campo " + fieldName + " con id: " + f.getId());

                MetadataFieldType type = f.getType();


                if (type.equals(MetadataFieldType.TEXTBOX)) {
                    fieldProperty = "sqdataValuesOrd.textValue";
                }
                if (type.equals(MetadataFieldType.TEXTAREA) || type.equals(MetadataFieldType.RICHTEXT)) {
                    fieldProperty = "sqdataValuesOrd.longTextValue";
                }
                if (type.equals(MetadataFieldType.CHECKBOX) || type.equals(MetadataFieldType.RADIO) || type.equals(MetadataFieldType.SELECT) || type.equals(MetadataFieldType.EXT_DICTIONARY)) {
                    fieldProperty = "sqdataValuesOrd.code";
                }
                if (type.equals(MetadataFieldType.DATE)) {

                    DateFormat df = new SimpleDateFormat("dd/MM/yyyy");
                    Date parsed = null;
                    fieldProperty = "sqdataValuesOrd.date";

                }
                if (type.equals(MetadataFieldType.ELEMENT_LINK)) {
                    fieldProperty = "sqdataValuesOrd.element_link";

                }


                it.cineca.siss.axmr3.log.Log.info(getClass(), "Assemblo query");
                if (parent) {
                    c.createAlias("root.parent", "sqparentOrd");
                    c.createAlias("sqparentOrd.data", "sqdataOrd");
                    c.createAlias("sqparentOrd.data.values", "sqdataValuesOrd");
                    c.createAlias("sqparentOrd.data.template", "sqtemplateOrd");
                    c.createAlias("sqparentOrd.data.field", "sqfieldOrd");
                } else {
                    c.createAlias("root.data", "sqdataOrd");
                    c.createAlias("root.data.values", "sqdataValuesOrd");
                    c.createAlias("root.data.template", "sqtemplateOrd");
                    c.createAlias("root.data.field", "sqfieldOrd");
                }
                c.add(Restrictions.eq("sqfieldOrd.name", fieldName));
                c.add(Restrictions.eq("sqtemplateOrd.name", template));
            }
            if (order.equals("asc")) {
                c.addOrder(Order.asc(fieldProperty));
            } else {
                c.addOrder(Order.desc(fieldProperty));
            }
        }
        return true;
    }

    /**
     * controlla che userToCheck appartenga allo stesso gruppo dell'utente che ha creato l'elemento
     * @param firstUser   l'utente da cui prendere il gruppo che inizia con groupPrefix
     * @param userToCheck l'utente da controllare
     * @param groupPrefix prefisso del gruppo
     * @return true se userToCheck appartiene allo stesso gruppo dell'utente che ha creato l'elemento
     */
    public boolean checkUsersSameGroupByPrefix(IUser firstUser, IUser userToCheck, String groupPrefix) {
        boolean ret = false;
        for (IAuthority firstAuth : firstUser.getAuthorities()) {
            if (firstAuth.getAuthority().startsWith(groupPrefix)) {
                for (IAuthority authToCheck : userToCheck.getAuthorities()) {
                    if (!ret && firstAuth.getAuthority().equals(authToCheck.getAuthority())) {
                        ret = true;
                    }
                }
            }
        }
        return ret;
    }


    public boolean modificaPermessiStudioPI(Long studioId) {
        Element studio = this.getElement(studioId);
        try {
            changePermissionToGroup(studio, "V,AC,A,B", "", "PI");
        } catch (Exception e) {
            Logger.getLogger(this.getClass()).error(e.getMessage(), e);
        }
        return true;
    }

    public Form loadXmlForm(String xmlform) throws IOException, SAXException, ParserConfigurationException {
        java.io.File file = new java.io.File(fmCfg.getAddOnPath()+"/xml/"+xmlform+".xml");
        DocumentBuilder dBuilder = DocumentBuilderFactory.newInstance().newDocumentBuilder();
        Document doc = dBuilder.parse(file);
        Form f=new Form(doc, file.getName());
        return f;

    }

    public Properties getMessages(HttpServletRequest request){
        Properties adHocProps=new Properties();
        try {
            FileInputStream fis=null;
            if (request!=null) {
                Locale l= ControllerHandler.getLocale(request);
                fis=new FileInputStream(fmCfg.getAddOnPath()+ "/messages/" + l.getLanguage()+"_"+l.getCountry()+".properties");
            }else {
                fis=new FileInputStream(fmCfg.getAddOnPath()+ "/messages/" + "it_IT.properties");
            }
            adHocProps.load(fis);
            fis.close();
        } catch (IOException e) {
            Logger.getLogger(this.getClass()).error(e.getMessage(), e);
        }
        return adHocProps;
    }

    public it.cineca.siss.axmr3.doc.xml.alpaca.Form getAlpacaJson(IUser user, HttpServletRequest request, String xmlform, Long elId, String mode) throws ParserConfigurationException, SAXException, IOException {
        Element el = null;
        if (elId != null) {
            Long emeSessionId=user.getEmeSessionId();
            log.info("ALPACAJSON - GetEmeSessionId: "+emeSessionId);
            el = this.getElement(elId, emeSessionId);
        }
        it.cineca.siss.axmr3.doc.xml.alpaca.Form form= it.cineca.siss.axmr3.doc.xml.alpaca.Form.fromXmlFile(user, request, this, xmlform, el, mode);
        return form;

    }

    public FormSpecification getFormScpecification(String typeId, HttpServletRequest request, IUser user){
        return getFormSpecification(this.getType(this.getTypeIdByNameOrId(typeId)), user, null, request);
    }

    public FormSpecification getFormScpecification(ElementType type, IUser user, HttpServletRequest request){
        return getFormSpecification(type, user, null, request);
    }

    public FormSpecification getFormScpecification(IUser user, Element el, HttpServletRequest request){
        return getFormSpecification(el.getType(), user, el, request);
    }

    public FormSpecification getFormScpecification(String typeId, IUser user, Element el, HttpServletRequest request){
        return getFormSpecification(this.getType(this.getTypeIdByNameOrId(typeId)), user, el, request);
    }

    public FormSpecification getFormSpecification(ElementType type, IUser user, Element el, HttpServletRequest request){
        FormSpecification fspec = new FormSpecification();
        Properties adHocProps=this.getMessages(request);
        fspec.setElementPolicy(type.getUserPolicy(user));

        fspec.setHasFile(type.isHasFileAttached());
        fspec.setFileInfo(!type.isNoFileinfo());
        for (ElementTypeAssociatedTemplate at:type.getAssociatedTemplates()){
            if ( (el==null && at.getUserPolicy(user, type).isCanCreate()) || (el!=null) ) {
                for (MetadataField field : at.getMetadataTemplate().getFields()) {
                    FormSpecificationField f = FormSpecificationField.build(field, adHocProps, this, user, el);
                    fspec.addField(f);
                }
            }
        }
        return fspec;
    }

    public CheckResult xmlChecks(IUser user, HttpServletRequest request, String formFile, Map data, Element el) throws ParserConfigurationException, SAXException, IOException {
        Form xmlForm=this.loadXmlForm(formFile);
        FormSpecification fspec=this.getFormScpecification(xmlForm.getObject(), user, el, request);
        return xmlForm.doChecks(user, fspec, data, el);
    }

    public HashMap<String, String> fixParametersSingle(IUser user, HttpServletRequest request, String formFile, HashMap<String, String> dataSingle, Element el) throws ParserConfigurationException, SAXException, IOException {
        HashMap<String, String> dataSingleFixed=new HashMap<String, String>();
        Form xmlForm=this.loadXmlForm(formFile);
        FormSpecification formSpec=this.getFormScpecification(xmlForm.getObject(), user, el, request);
        for (Field f:xmlForm.getFields()){
            FormSpecificationField ff=formSpec.getFields().get(f.getVar().toUpperCase());
            //log.info("FPS - FIELD: "+f.getVar()+" - "+f.getType()+" - "+f.getLabel());
            if (ff==null){
                //log.warn("FPS - FFNULL! ");
            }else {
                //log.info("FPS - FSFIELD: " + ff.getUniqueFieldName());
            }
            if (ff != null) {
                if (dataSingle.containsKey(ff.getUniqueFieldName() + "-DECODE")) {
                    //log.warn("!!HAS DECODE FIELD!!"+ff.getUniqueFieldName());
                    dataSingleFixed.put(ff.getUniqueFieldName(), dataSingle.get(ff.getUniqueFieldName()) + "###" + dataSingle.get(ff.getUniqueFieldName() + "-DECODE"));
                    //log.warn("DECODE VALUE: "+dataSingle.get(ff.getUniqueFieldName() + "-DECODE"));
                } else {
                    if (f.getType().equals("select") || f.getType().equals("radio") || f.getType().equals("checkbox")) { // || f.getType().equals("ext_dictionary")

                        dataSingleFixed.put(ff.getUniqueFieldName(), dataSingle.get(ff.getUniqueFieldName()) + "###" + ff.getPossibleValues().get(dataSingle.get(ff.getUniqueFieldName())));
                        //log.warn("DECODE VALUE: " + ff.getPossibleValues().get(dataSingle.get(ff.getUniqueFieldName())));

                    } else {
                        dataSingleFixed.put(ff.getUniqueFieldName(), dataSingle.get(ff.getUniqueFieldName()));
                    }
                }
            }
        }
        return dataSingleFixed;
    }

    public HashMap<String, String[]> fixParameters(IUser user, HttpServletRequest request, String formFile, HashMap<String, String[]> data, Element el) throws ParserConfigurationException, SAXException, IOException {
        HashMap<String, String[]> dataFixed=new HashMap<String, String[]>();
        Form xmlForm=this.loadXmlForm(formFile);
        FormSpecification formSpec=this.getFormScpecification(xmlForm.getObject(), user, el, request);
        for (Field f:xmlForm.getFields()){
            FormSpecificationField ff=formSpec.getFields().get(f.getVar().toUpperCase());
            if (ff != null) {
                if (data.get(ff.getUniqueFieldName()+ "-DECODE") != null) {
                    log.warn("!!HAS DECODE FIELD!! "+ff.getUniqueFieldName());
                    String[] newFieldData = new String[data.get(ff.getUniqueFieldName()).length];
                    for (int i = 0; i < data.get(ff.getUniqueFieldName()).length; i++) {
                        newFieldData[i] = data.get(ff.getUniqueFieldName())[i] + "###" +  data.get(ff.getUniqueFieldName() + "-DECODE")[i];
                    }
                    dataFixed.put(ff.getUniqueFieldName(), newFieldData);
                    log.warn("DECODE VALUE: "+data.get(ff.getUniqueFieldName() + "-DECODE").toString());
                } else {
                    if (f.getType().equals("select") || f.getType().equals("radio") || f.getType().equals("checkbox")) {
                        if (data.get(ff.getUniqueFieldName()) != null) {
                            String[] newFieldData = new String[data.get(ff.getUniqueFieldName()).length];
                            for (int i = 0; i < data.get(ff.getUniqueFieldName()).length; i++) {
                                newFieldData[i] = data.get(ff.getUniqueFieldName())[i] + "###" + ff.getPossibleValues().get(data.get(ff.getUniqueFieldName())[i]);
                            }
                            dataFixed.put(ff.getUniqueFieldName(), newFieldData);
                        }
                    } else {
                        if (data.get(ff.getUniqueFieldName()) != null) {
                            dataFixed.put(ff.getUniqueFieldName(), data.get(ff.getUniqueFieldName()));
                        }
                    }
                }
            }
        }
        return dataFixed;
    }


    public String getElementIdStudio(String elementId) throws Exception {

        Element el=getElement(Long.parseLong(elementId));
        String elementIdStudio="";

        if(el.getTypeName().equals("Studio") || el.getTypeName().equals("UsoTerapeutico")){
            elementIdStudio=elementId;
        }else{
            return getElementIdStudio(el.getParent().getId().toString());
        }

        return elementIdStudio;
    }


    public void updateFileInfo(Element el, String autore, String note, String date, String version) throws RestException {
        DateFormat df = new SimpleDateFormat("dd/MM/yyyy");
        Date parsed = null;
        Calendar data = null;
        if (date!=null && !date.isEmpty()) {
            try {
                parsed = df.parse(date.toString());
                data = Calendar.getInstance();
                data.setTime(parsed);
            } catch (java.text.ParseException e) {
                log.error(e.getMessage(),e);  //To change body of catch statement use File | Settings | File Templates.
            }
        }
        if (autore!=null) el.getFile().setAutore(autore);
        if (note!=null) el.getFile().setNote(note);
        if (date!=null) el.getFile().setDate(data);
        if (version!=null) el.getFile().setVersion(version);
        try {
            docDAO.saveOrUpdate(el);
            addElidToBeUpdeated(el.getId(),true);
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        }
    }

    public String getIdCentroFromAnyChild(String elementId) throws Exception {

        Element el=this.getElement(Long.parseLong(elementId));
        String elementIdCentro="";

        if (el.getTypeName().equals("Centro")) {
            elementIdCentro = elementId;
        }else {
            if (el.getParent() != null && el.getParent().getId() != null) {
                elementIdCentro = getIdCentroFromAnyChild(el.getParent().getId().toString());
            }
        }

        return elementIdCentro;
    }


    public void commitTXSessionAndKeepAlive(){
        txManager.commitAndKeepAlive();
        launchIndexing();
    }
    public void commitTxSessionAndClose(){
        txManager.destroy();
        launchIndexing();
    }
    public void commitTXSessionAndKeepAlive(InternalServiceBean newIsb){
        if (isb == null){
            isb = newIsb;
        }
        commitTXSessionAndKeepAlive();
    }
    public void commitTxSessionAndClose(InternalServiceBean newIsb){
        if (isb == null){
            isb = newIsb;
        }
        commitTxSessionAndClose();
    }
    public void launchIndexing(){
        if (isb != null && isb.isActive()) {
            if (getUpdateElIds()!=null && !getUpdateElIds().isEmpty()){
                Iterator<Long> ids=getUpdateElIds().keySet().iterator();
                while (ids.hasNext()){
                    Long id=ids.next();
                    isb.doInternalAsyncRequest("/rest/elk/elementIdxUpdate/" + id);
                }
            }
            updateElIds=new HashMap<Long, Boolean>();
        }

    }

}
