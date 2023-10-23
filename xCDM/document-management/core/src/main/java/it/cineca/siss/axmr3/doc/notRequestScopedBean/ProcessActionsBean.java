package it.cineca.siss.axmr3.doc.notRequestScopedBean;

import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.authentication.services.SissUserService;
import it.cineca.siss.axmr3.doc.acl.Policy;
import it.cineca.siss.axmr3.doc.acl.TemplatePolicy;
import it.cineca.siss.axmr3.doc.beans.InternalServiceBean;
import it.cineca.siss.axmr3.doc.entities.*;
import it.cineca.siss.axmr3.doc.process.IProcessActionsBean;
import it.cineca.siss.axmr3.doc.web.services.DocumentService;
import it.cineca.siss.axmr3.exceptions.AxmrGenericException;
import it.cineca.siss.axmr3.transactions.Axmr3TXManagerNonRequestScoped;
import org.activiti.engine.ProcessEngine;
import org.activiti.engine.delegate.DelegateTask;
import org.activiti.engine.runtime.ProcessInstance;
import org.apache.log4j.Logger;
import org.hibernate.SessionFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.security.core.context.SecurityContextHolder;

import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.text.SimpleDateFormat;
import java.util.*;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 24/10/13
 * Time: 11:00
 * To change this template use File | Settings | File Templates.
 */
public class ProcessActionsBean implements IProcessActionsBean {

    protected Axmr3TXManagerNonRequestScoped globalTx;

    private static final Logger log = Logger.getLogger(ProcessActionsBean.class);

    @Autowired
    protected InternalServiceBean isb;

    public InternalServiceBean getIsb() {
        return isb;
    }

    public void setIsb(InternalServiceBean isb) {
        this.isb = isb;
    }

    @Autowired
    protected SissUserService userService;

    @Autowired
    protected ProcessEngine engine;

    public ProcessEngine getEngine() {
        return engine;
    }

    public void setEngine(ProcessEngine engine) {
        this.engine = engine;
    }

    public SissUserService getUserService() {
        return userService;
    }

    public void setUserService(SissUserService userService) {
        this.userService = userService;
    }

    public Axmr3TXManagerNonRequestScoped getGlobalTx() {
        return globalTx;
    }


    public ProcessActionsBean() {
        it.cineca.siss.axmr3.log.Log.info(getClass(), "Inizializzo il bean ProcessActionsBean");
    }


    @Autowired
    @Qualifier(value = "docSessionFactory")
    protected org.hibernate.SessionFactory docSessionFactory;

    public org.hibernate.SessionFactory getDocSessionFactory() {
        return docSessionFactory;
    }

    public void setDocSessionFactory(org.hibernate.SessionFactory docSessionFactory) {
        this.docSessionFactory = docSessionFactory;
    }

    public DocumentService getDocumentService() throws ProcessException {
        try {
            DocumentService service = new DocumentService();
            service.setProcessEngine(engine);
            globalTx = new Axmr3TXManagerNonRequestScoped();
            globalTx.setSessionFactories(new HashMap<String, SessionFactory>());
            globalTx.getSessionFactories().put("doc", docSessionFactory);
            service.setTxManager(globalTx);
            service.afterPropertiesSet();
            return service;
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);

            throw new ProcessException(ex, globalTx);
        }
    }

    public void elementIdxUpdate(DocumentService service, Element el, boolean fieldToo) {
        service.addElidToBeUpdeated(el.getId(), fieldToo);
    }
    public void elementIdxUpdate(DocumentService service, Long elementId, boolean fieldToo){
        service.addElidToBeUpdeated(elementId, fieldToo);
    }

    public void closeDocumentService(DocumentService service) {
        service.commitTxSessionAndClose(getIsb());
            }
    public void commitTXSessionAndKeepAlive(DocumentService service){
        service.commitTXSessionAndKeepAlive(getIsb());
    }

    public void addTemplate(String elId, String templateName, DocumentService service) throws Exception {
        service.addTemplateAction(Long.parseLong(elId), templateName);
    }

    public void addTemplate(String elId, String templateName) throws ProcessException {
        try {
            DocumentService service = getDocumentService();
            Logger.getLogger(this.getClass()).info("Sono in punto 1");
            addTemplate(elId, templateName, service);
            Logger.getLogger(this.getClass()).info("Sono in punto 2");
            elementIdxUpdate(service, service.getElement(Long.parseLong(elId)), true);
            closeDocumentService(service);
        } catch (Exception ex) {
            Logger.getLogger(this.getClass()).info("Sono in punto 3");
            Logger.getLogger(this.getClass()).info(ex.getMessage());
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public void addAvailableTemplateToElement(String elId, String templateName) throws Exception {
        DocumentService service = getDocumentService();
        addAvailableTemplateToElement(elId, templateName, service);
    }

    public void addAvailableTemplateToElement(String elId, String templateName, DocumentService service) throws AxmrGenericException, AxmrGenericException {
        Element el = service.getElement(elId);
        service.addAvailableTemplateToElement(el, templateName);
    }

    public void setDescription(DelegateTask task) {
        String description = task.getVariable("descriptionNext").toString();
        task.setDescription(description);
        task.setVariable("descriptionNext", "");
        task.setVariable("descriptionLast", description);
    }

    public void addMetadataValue(String elId, String templateName, String fieldName, Object value) throws ProcessException {
        try {
            DocumentService service = getDocumentService();
            Logger.getLogger(this.getClass()).info(" - 1 - Effettuo update campo" + templateName + "." + fieldName + " con valore:" + value);
            service.addMetadataValueActions(Long.parseLong(elId), templateName, fieldName, value);
            elementIdxUpdate(service, service.getElement(Long.parseLong(elId)), true);
            closeDocumentService(service);
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public void addMetadataValue(Element element, String templateName, String fieldName, Object value, DocumentService service) throws ProcessException {
        try {
            Logger.getLogger(this.getClass()).info(" - 2 - Effettuo update campo" + templateName + "." + fieldName + " con valore:" + value);
            service.addMetadataValueActions(element.getId(), templateName, fieldName, value);
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }


    public void addMetadataValue(String elId, String templateName, String fieldName, Object value, DocumentService service) throws ProcessException {
        try {
            Logger.getLogger(this.getClass()).info(" - 3 - Effettuo update campo" + templateName + "." + fieldName + " con valore:" + value);
            addMetadataValue(Long.parseLong(elId), templateName, fieldName, value, service);
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public void addMetadataValue(Long elId, String templateName, String fieldName, Object value, DocumentService service) throws ProcessException {
        try {
            Logger.getLogger(this.getClass()).info(" - 4 - Effettuo update campo" + templateName + "." + fieldName + " con valore:" + value);
            service.addMetadataValueActions(elId, templateName, fieldName, value);
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public String sysdate() throws ProcessException {
        try {

            String today = new SimpleDateFormat("dd/MM/yyyy").format(new Date());
            return today;
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }

    }


    public Element getElement(String elId, DocumentService service) throws ProcessException {
        try {
            Element result = service.getElement(Long.parseLong(elId));
            return result;
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public String getParentElementId(String elId, DocumentService service) throws ProcessException {
        Element result = service.getElement(Long.parseLong(elId));
        String pid = result.getParent().getId() + "";
        return pid;
    }

    public String getParentElementId(String elId) throws ProcessException {
        try {
            DocumentService service = getDocumentService();
            String pid = getParentElementId(elId, service);
            closeDocumentService(service);
            return pid;
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public Element getElement(String elId) throws ProcessException {
        try {
            DocumentService service = getDocumentService();
            Element result = service.getElement(Long.parseLong(elId));
            closeDocumentService(service);
            return result;
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }


    public void changePermissionToGroup(String elementId, String permissions, String ftl, String group, DocumentService service) throws ProcessException {
        try {
            //Policy pol=Policy.createPolicyByCommaSeparatedString(permissions);
            Element el = service.getElement(Long.parseLong(elementId));
            changePermissionToGroup(el, permissions, ftl, group, service);
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public void changePermissionToGroup(Element el, String permissions, String ftl, String group, DocumentService service) throws ProcessException {
        try {
            service.changePermissionToGroup(el, permissions, ftl, group);
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public void changePermissionToGroup(String elementId, String permissions, String ftl, String group) throws ProcessException {
        try {
            //it.cineca.siss.axmr3.log.Log.info(getClass(),"Cambio i permessi al gruppo "+group+" sull'elemento "+elementId);
            DocumentService service = getDocumentService();
            changePermissionToGroup(elementId, permissions, ftl, group, service);
            elementIdxUpdate(service, service.getElement(Long.parseLong(elementId)), true);
            closeDocumentService(service);
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public void changePermissionToGroupRecursive(String elementId, String permissions, String ftl, String group, DocumentService service) throws ProcessException {
        try {
            Element el = service.getElement(Long.parseLong(elementId));
            changePermissionToGroupRecursive(el, permissions, ftl, group, service);
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }


    public void changePermissionToGroupRecursive(Element el, String permissions, String ftl, String group, DocumentService service) throws ProcessException {
        try {
            service.setElementPolicy(el, ftl, permissions, true, group, true);
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public void changePermissionToGroupRecursive(String elementId, String permissions, String ftl, String group) throws ProcessException {
        try {
            //it.cineca.siss.axmr3.log.Log.info(getClass(),"Cambio i permessi al gruppo "+group+" sull'elemento "+elementId+" in modo ricorsivo");
            DocumentService service = getDocumentService();
            changePermissionToGroupRecursive(elementId, permissions, ftl, group, service);
            elementIdxUpdate(service, service.getElement(Long.parseLong(elementId)), true);
            closeDocumentService(service);
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    //TODO: codice duplicato
    public void changePermissionToUser(String elementId, String permissions, String ftl, String username, DocumentService service) throws ProcessException {
        try {
            service.setElementPolicy(Long.parseLong(elementId), ftl, permissions, false, username);
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }


    public void changePermissionToUser(String elementId, String permissions, String ftl, String username) throws ProcessException {
        try {
            DocumentService service = getDocumentService();
            changePermissionToUser(elementId, permissions, ftl, username, service);
            elementIdxUpdate(service, service.getElement(Long.parseLong(elementId)), true);
            closeDocumentService(service);
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    //TODO: codice duplicato
    public void changePermissionToUserRecursive(String elementId, String permissions, String ftl, String username, DocumentService service) throws ProcessException {
        try {
            service.setElementPolicy(Long.parseLong(elementId), ftl, permissions, false, username, true);
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public void changePermissionToUserRecursive(String elementId, String permissions, String ftl, String username) throws ProcessException {
        try {
            //it.cineca.siss.axmr3.log.Log.info(getClass(),"Cambio i permessi all'utente "+username+" sull'elemento "+elementId);
            DocumentService service = getDocumentService();
            changePermissionToUserRecursive(elementId, permissions, ftl, username, service);
            elementIdxUpdate(service, service.getElement(Long.parseLong(elementId)), true);
            closeDocumentService(service);
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public void changeTemplatePermissionToUser(String elementId, String templateName, String permissions, String username) throws ProcessException {
        try {
            //it.cineca.siss.axmr3.log.Log.info(getClass(),"Cambio i permessi all'utente "+username+" sul template "+templateName+" dell'elemento "+elementId);
            DocumentService service = getDocumentService();
            changeTemplatePermissionToUser(elementId, templateName, permissions, username, service);
            elementIdxUpdate(service, service.getElement(Long.parseLong(elementId)), true);
            closeDocumentService(service);
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public void changeTemplatePermissionToGroup(String elementId, String templateName, String permissions, String group) throws ProcessException {
        try {
            DocumentService service = getDocumentService();
            changeTemplatePermissionToGroup(elementId, templateName, permissions, group, service);
            elementIdxUpdate(service, service.getElement(Long.parseLong(elementId)), true);
            closeDocumentService(service);
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public void removeTemplatePermissionToGroup(Long elementId, String templateName, String group) throws ProcessException {
        try {
            DocumentService service = getDocumentService();
            //Policy pol=Policy.createPolicyByCommaSeparatedString(permissions);
            Element el = service.getElement(elementId);
            removeTemplatePermissionToGroup(el, templateName, group, service);
            elementIdxUpdate(service, service.getElement(elementId), true);
            closeDocumentService(service);
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public void removeTemplatePermissionToGroup(String elementId, String templateName, String group) throws ProcessException {
        try {
            DocumentService service = getDocumentService();
            //Policy pol=Policy.createPolicyByCommaSeparatedString(permissions);
            Element el = service.getElement(Long.parseLong(elementId));
            removeTemplatePermissionToGroup(el, templateName, group, service);
            elementIdxUpdate(service, service.getElement(Long.parseLong(elementId)), true);
            closeDocumentService(service);
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public void removeTemplatePermissionToGroup(Element el, String templateName, String group, DocumentService service) throws ProcessException {
        try {
            service.removeTemplatePolicy(el, templateName, true, group);

        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }


    public void terminateAllProcess(String elementId) throws ProcessException{
        try{
            IUser user =(IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
            DocumentService service = getDocumentService();
            Element element=service.getElement(elementId);
            List<ProcessInstance> activeProcesses;
            activeProcesses = service.getActiveProcesses(element);

            for(ProcessInstance process:activeProcesses){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"HO TROVATO = "+process.getProcessDefinitionId());
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"PROVO A TERMINARE = "+process.getProcessDefinitionId());
                service.terminateProcess(user ,process.getProcessInstanceId());
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"HO TERMINATO = "+process.getProcessDefinitionId());
            }
        }catch (Exception ex){
            log.error(ex.getMessage(),ex);
            throw new ProcessException(ex,globalTx);
        }
    }

    public void terminaProcesso(String elementId, String processDefinition) throws Exception {
        try{
            DocumentService service = getDocumentService();
            Element contratto = service.getElement(elementId);
            List<ProcessInstance> activeProcesses;
            activeProcesses = service.getActiveProcesses(contratto);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "CERCO IL WF " + processDefinition + ": ASSOCIATO ALL'elemento= " + elementId);
            for (ProcessInstance process : activeProcesses) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "HO TROVATO = " + process.getProcessDefinitionId());
                if (process.getProcessDefinitionId().startsWith(processDefinition + ":")) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "PROVO A TERMINARE = " + process.getProcessDefinitionId());
                    String user = "CTC";
                    service.terminateProcess(userService.getUser(user), process.getProcessInstanceId());
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "HO TERMINATO = " + process.getProcessDefinitionId());
                }
            }
        }catch (Exception ex){
            log.error(ex.getMessage(),ex);
            throw new ProcessException(ex,globalTx);
        }
    }

    public List<Element> getChildren(String elementId, List<String> typeIds, HashMap<String, Object> fieldValues, DocumentService service) throws ProcessException {
        try {
            Element el = service.getElement(Long.parseLong(elementId));
            List<Element> els = getChildrenRecursive(el, typeIds, fieldValues);
            return els;
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }


    public List<Element> getChildren(String elementId, List<String> typeIds, HashMap<String, Object> fieldValues) throws ProcessException {
        try {
            DocumentService service = getDocumentService();
            List<Element> els = getChildren(elementId, typeIds, fieldValues, service);
            closeDocumentService(service);
            return els;
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public void sendMail(String[] to, String subject, String message, String from) {
        //To change body of implemented methods use File | Settings | File Templates.
    }

    public Long cloneElement(String elementId, String userid, DocumentService service) throws ProcessException {
        try {
            Element el = service.defaultClone(userid, Long.parseLong(elementId));
            return el.getId();
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public Long cloneElement(String elementId, String userid) throws ProcessException {
        try {
            //it.cineca.siss.axmr3.log.Log.info(getClass(),"Clono l'elemento: "+elementId);
            DocumentService service = getDocumentService();
            Long id = cloneElement(elementId, userid, service);
            elementIdxUpdate(service, service.getElement(Long.parseLong(elementId)), true);
            closeDocumentService(service);
            it.cineca.siss.axmr3.log.Log.info(getClass(), "Elemento clonato: " + id);
            return id;
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    //TODO:Effetture controllo di sicurezza sui permessi che sia possibile creare tutto ciò solo da activiti
    public Long createChild(String elementId, String userid, String typeId, DocumentService service) throws ProcessException {
        try {
            //IUser user= (IUser) userService.loadUserByUsername(userid);
            Element parent = service.getElement(Long.parseLong(elementId));
            ElementType type = null;
            Element el = null;

            it.cineca.siss.axmr3.log.Log.info(getClass(), "elementId= " + elementId);
            it.cineca.siss.axmr3.log.Log.info(getClass(), "parent= " + parent.toString());

            for (ElementType t : parent.getType().getAllowedChilds()) {
                if (t.getTypeId().equals(typeId)) type = t;
            }
            if (type != null) {
                el = service.saveElement(userid, type, new HashMap<String, String>(), null, null, null, "", "", "", "", parent);
            }
            if (el != null) {
                return el.getId();
            } else {
                return null;
            }
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public Long createChild(String elementId, String userid, String typeId) throws ProcessException {
        try {
            it.cineca.siss.axmr3.log.Log.info(getClass(), "Creo un elemento di tipo " + typeId + " nell'elemento: " + elementId);
            DocumentService service = getDocumentService();
            Long id = createChild(elementId, userid, typeId, service);
            elementIdxUpdate(service, service.getElement(Long.parseLong(elementId)), true);
            closeDocumentService(service);
            it.cineca.siss.axmr3.log.Log.info(getClass(), "Elemento creato: " + id);
            return id;
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public Long createChild(String elementId, String userid, String typeId, HashMap<String, String> data) throws Exception {
        it.cineca.siss.axmr3.log.Log.info(getClass(), "Creo un elemento di tipo " + typeId + " nell'elemento: " + elementId);
        DocumentService service = getDocumentService();
        Long id = createChild(elementId, userid, typeId, data, service);
        elementIdxUpdate(service, service.getElement(Long.parseLong(elementId)), true);
        closeDocumentService(service);
        it.cineca.siss.axmr3.log.Log.info(getClass(), "Elemento creato: " + id);
        return id;
    }

    public Long createChild(Element element, String userid, String typeId, HashMap<String, String> data, DocumentService service) throws Exception {

        return createChild(element.getId().toString(), userid, typeId, data, service);
    }

    public Long createChild(String elementId, String userid, String typeId, HashMap<String, String> data, DocumentService service) throws Exception {
        //IUser user= (IUser) userService.loadUserByUsername(userid);
        Element parent = service.getElement(Long.parseLong(elementId));
        ElementType type = null;
        Element el = null;
        it.cineca.siss.axmr3.log.Log.info(getClass(), "parent type " + parent.getType().getTypeId());
        for (ElementType t : parent.getType().getAllowedChilds()) {
            it.cineca.siss.axmr3.log.Log.info(getClass(), "allowed child " + t.getTypeId());
            if (t.getTypeId().equals(typeId)) type = t;
        }
        if (type != null) {
            el = service.saveElement(userid, type, data, null, null, null, "", "", "", "", parent);
        }
        if (el != null) {
            return el.getId();
        } else {
            return null;
        }

    }

    public Long createChild347(String elementId, String userid, String typeId, HashMap<String, String> data, DocumentService service, boolean forceNotCloning) throws Exception {
        //IUser user= (IUser) userService.loadUserByUsername(userid);
        Element parent = service.getElement(Long.parseLong(elementId));
        ElementType type = null;
        Element el = null;
        it.cineca.siss.axmr3.log.Log.info(getClass(), "parent type " + parent.getType().getTypeId());
        for (ElementType t : parent.getType().getAllowedChilds()) {
            it.cineca.siss.axmr3.log.Log.info(getClass(), "allowed child " + t.getTypeId());
            if (t.getTypeId().equals(typeId)) type = t;
        }
        if (type != null) {
            el = service.saveElement(userid, type, data, null, null, null, "", "", "", "", parent, forceNotCloning);
        }
        if (el != null) {
            return el.getId();
        } else {
            return null;
        }
    }

    public Long createChildIfNotExists(String elementId, String userid, String typeId, DocumentService service) throws Exception {
        Element parent = service.getElement(Long.parseLong(elementId));
        ElementType type = null;
        Element el = null;

        it.cineca.siss.axmr3.log.Log.info(getClass(), "elementId= " + elementId);
        it.cineca.siss.axmr3.log.Log.info(getClass(), "parent= " + parent.toString());

        for (ElementType t : parent.getType().getAllowedChilds()) {
            if (t.getTypeId().equals(typeId)) type = t;
        }

        if ((parent.getChildrenByType(typeId).size() == 0) && (type != null)) {
            el = service.saveElement(userid, type, new HashMap<String, String>(), null, null, null, "", "", "", "", parent);
            return el.getId();
        }
        return null;
    }

    public Long createChildIfNotExists(String elementId, String userid, String typeId) throws Exception {
        it.cineca.siss.axmr3.log.Log.info(getClass(), "Creo un elemento di tipo " + typeId + " nell'elemento: " + elementId);
        DocumentService service = getDocumentService();
        Long id = createChildIfNotExists(elementId, userid, typeId, service);
        elementIdxUpdate(service, service.getElement(Long.parseLong(elementId)), true);
        closeDocumentService(service);
        it.cineca.siss.axmr3.log.Log.info(getClass(), "Elemento creato: " + id);
        return id;
    }

    public Long createChildIfNotExists(String elementId, String userid, String typeId, HashMap<String, String> data) throws Exception {
        it.cineca.siss.axmr3.log.Log.info(getClass(), "Creo un elemento di tipo " + typeId + " nell'elemento: " + elementId);
        DocumentService service = getDocumentService();
        Long id = createChildIfNotExists(elementId, userid, typeId, data, service);
        elementIdxUpdate(service, service.getElement(Long.parseLong(elementId)), true);
        closeDocumentService(service);
        it.cineca.siss.axmr3.log.Log.info(getClass(), "Elemento creato: " + id);
        return id;
    }

    public Long createChildIfNotExists(Element element, String userid, String typeId, HashMap<String, String> data, DocumentService service) throws Exception {

        return createChildIfNotExists(element.getId().toString(), userid, typeId, data, service);
    }

    public Long createChildIfNotExists(String elementId, String userid, String typeId, HashMap<String, String> data, DocumentService service) throws Exception {
        //IUser user= (IUser) userService.loadUserByUsername(userid);
        Element parent = service.getElement(Long.parseLong(elementId));
        ElementType type = null;
        Element el = null;
        it.cineca.siss.axmr3.log.Log.info(getClass(), "parent type " + parent.getType().getTypeId());
        for (ElementType t : parent.getType().getAllowedChilds()) {
            it.cineca.siss.axmr3.log.Log.info(getClass(), "allowed child " + t.getTypeId());
            if (t.getTypeId().equals(typeId)) type = t;
        }
        if ((parent.getChildrenByType(typeId).size() == 0) && (type != null)) {
            el = service.saveElement(userid, type, data, null, null, null, "", "", "", "", parent);
            return el.getId();
        }
        return null;
    }

    protected List<Element> getChildrenRecursive(Element parent, List<String> typeIds, HashMap<String, Object> fieldValues) {
        List<Element> els = new LinkedList<Element>();
        for (Element el : parent.getChildren()) {
            boolean inserted = false;
            if (typeIds.contains(el.getType().getTypeId())) {
                for (ElementMetadata d : el.getData()) {
                    List<Object> datas = d.getVals();
                    String fieldId = d.getTemplateName() + "." + d.getField().getName();
                    Iterator<String> it = fieldValues.keySet().iterator();
                    while (!inserted && it.hasNext()) {
                        String fieldName = it.next();
                        if (fieldId.equals(fieldName) && datas.get(0).equals(fieldValues.get(fieldName))) {
                            els.add(el);
                            inserted = true;
                        }
                    }
                    if (inserted) break;
                }
            }
            List<Element> subChild = getChildrenRecursive(el, typeIds, fieldValues);
            for (Element el2 : subChild) {
                els.add(el2);
            }
        }
        return els;
    }

    public void checkTemplateCompleted(String elementId, String template, DelegateTask task, DocumentService service) throws ProcessException {
        try {
            boolean passed = true;
            String message = "";
            if (task.getVariable("passed") == null) {
                it.cineca.siss.axmr3.log.Log.info(getClass(), "\n\n\nSono nella prima esecuzione di checkTemplateCompleted");
                task.setVariable("passed", true);
            } else {
                passed = (Boolean) task.getVariable("passed");
            }
            if (task.getVariable("message") == null) {
                task.setVariable("message", "");
            } else {
                message = (String) task.getVariable("message");
            }
            if (!passed) return;

            Element el = service.getElement(Long.parseLong(elementId));
            it.cineca.siss.axmr3.log.Log.info(getClass(), "Ciclo i metadati");
            List<String> present = new LinkedList<String>();
            for (MetadataTemplate t : el.getTemplates()) {
                if (t.getName().equals(template)) {
                    for (MetadataField f : t.getFields()) {
                        if (f.isMandatory()) {
                            present.add(t.getName() + "." + f.getName());
                            //it.cineca.siss.axmr3.log.Log.info(getClass(),"OBBLIGATORIO: template= "+t.getName()+" campo= "+f.getName()+" ID template "+t.getId()+" ID campo "+f.getId());
                        } else {
                            //it.cineca.siss.axmr3.log.Log.info(getClass(),"FACOLTATIVO: template= "+t.getName()+" campo= "+f.getName()+" ID template "+t.getId()+" ID campo "+f.getId());
                        }
                    }
                }
            }
            boolean checkFields = true;
            for (ElementMetadata md : el.getData()) {
                if (md.getTemplateName().equals(template)) {
                    it.cineca.siss.axmr3.log.Log.info(getClass(), "Metadato: " + md.getTemplate().getName() + " - " + md.getField().getName() + " - " + md.getField().isMandatory());
                    if (present.contains(template + "." + md.getField().getName())) {
                        present.remove(template + "." + md.getField().getName());
                        it.cineca.siss.axmr3.log.Log.info(getClass(), "\n\n\nIl campo " + md.getTemplate().getName() + "_" + md.getField().getName() + " obbligatorio");
                        if (md.getVals() == null || md.getVals().size() == 0 || md.getVals().get(0) == null || md.getVals().get(0).toString().isEmpty()) {
                            it.cineca.siss.axmr3.log.Log.info(getClass(), "\n\n\n" + md.getTemplate().getName() + "_" + md.getField().getName() + " - Lo trovo vuoto ed imposto passed a false");
                            checkFields = false;
                        }
                    }
                }
            }
            it.cineca.siss.axmr3.log.Log.info(getClass(), "Campi non trovati: " + present.size());

            if (present.size() > 0) {
                it.cineca.siss.axmr3.log.Log.info(getClass(), "\n\n\nNon o trovo vuoto ed imposto passed a false");
                passed = false;
            }
            passed = (passed && checkFields);
            if (!passed) {
                /*Properties messProps = new Properties();
                FileInputStream fis=new FileInputStream(service.getMessagesFolder() + "/messages/it_IT.properties");
                messProps.load(fis);
                fis.close();
                */
                String templateLabel = template;//String templateLabel=(String)messProps.get("template."+template);
                message = "'Attenzione! Validazione fallita. Compilare i campi obbligatori della scheda " + templateLabel;
            } else {
                message = "";
            }
            it.cineca.siss.axmr3.log.Log.info(getClass(), "Setto la variabile di esecuzione passed a " + passed);
            it.cineca.siss.axmr3.log.Log.info(getClass(), "Setto la variabile di esecuzione message a " + message);
            task.setVariable("passed", passed);
            task.setVariable("message", message);

            it.cineca.siss.axmr3.log.Log.info(getClass(), "\n\n\n\nEsco da checkTemplateCompleted per il template " + template);
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public void hasChildOfType(String elementId, String typeId, DelegateTask task) throws ProcessException {
        try {
            boolean passed = true;
            if (task.getVariable("passed") == null) {
                it.cineca.siss.axmr3.log.Log.info(getClass(), "\n\n\nSono nella prima esecuzione di checkTemplateCompleted");
                task.setVariable("passed", true);
            } else {
                passed = (Boolean) task.getVariable("passed");
            }
            if (!passed) return;
            DocumentService service = getDocumentService();
            Element el = service.getElement(Long.parseLong(elementId));
            Collection<Element> childs = el.getChildren();
            boolean check = false;
            for (Element e : childs) {
                if (e.getType().getTypeId().equals(typeId)) check = true;
            }
            passed = (passed && check);
            task.setVariable("passed", passed);
            closeDocumentService(service);
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public void checkTemplateCompleted(String elementId, String template, DelegateTask task) throws ProcessException {
        try {
            it.cineca.siss.axmr3.log.Log.info(getClass(), "\n\n\nControllo il template " + template);
            DocumentService service = getDocumentService();
            checkTemplateCompleted(elementId, template, task, service);
            closeDocumentService(service);
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public void checkFieldHasValue(String elementId, String templateName, String fieldName, DelegateTask task) throws Exception {
        boolean passed = true;
        if (task.getVariable("passed") == null) {
            it.cineca.siss.axmr3.log.Log.info(getClass(), "\n\n\nControllo che il campo " + templateName + "." + fieldName + " sia valorizzato");
            task.setVariable("passed", true);
        } else {
            passed = (Boolean) task.getVariable("passed");
        }
        if (!passed) return;
        DocumentService service = getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        if (el.getfieldData(templateName, fieldName) != null && el.getfieldData(templateName, fieldName).size() > 0 && !el.getfieldData(templateName, fieldName).get(0).toString().isEmpty()) {
            it.cineca.siss.axmr3.log.Log.info(getClass(), "\n\n\nOK campo " + templateName + "." + fieldName + " sia valorizzato");
            task.setVariable("passed", true);
        } else {
            it.cineca.siss.axmr3.log.Log.info(getClass(), "\n\n\nNon OK campo " + templateName + "." + fieldName + " sia valorizzato");
            task.setVariable("passed", false);
        }
        closeDocumentService(service);


    }


    public void changeTemplatePermissionToGroup(String elementId, String templateName, String permissions, String group, DocumentService service) throws ProcessException {
        try {
            service.setTemplatePolicy(Long.parseLong(elementId), templateName, permissions, true, group);
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public void changeTemplatePermissionToUser(String elementId, String templateName, String permissions, String username, DocumentService service) throws ProcessException {
        try {
            service.setTemplatePolicy(Long.parseLong(elementId), templateName, permissions, false, username);
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public boolean checkFieldValue(String elementId, String templateName, String fieldName, String value) throws ProcessException {
        try {
            DocumentService service = getDocumentService();
            Element el = service.getElement(Long.parseLong(elementId));
            boolean ret = false;
            if (el.getfieldData(templateName, fieldName).get(0).toString().equals(value)) ret = true;
            it.cineca.siss.axmr3.log.Log.info(getClass(), "prima" + el.getFieldDataCode(templateName, fieldName));
            if (el.getFieldDataCode(templateName, fieldName).equals(value.split("###")[0])) ret = true;
            it.cineca.siss.axmr3.log.Log.info(getClass(), "dopo" + value.split("###")[0]);
            closeDocumentService(service);
            return ret;


        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public boolean checkFieldCode(String elementId, String templateName, String fieldName, String value) throws ProcessException {
        try {
            DocumentService service = getDocumentService();
            Element el = service.getElement(Long.parseLong(elementId));
            boolean ret = false;
            if (el.getFieldDataCode(templateName, fieldName).equals(value)) ret = true;
            closeDocumentService(service);
            return ret;
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public void startParentProcess(String elementId, String processKey) throws ProcessException {
        try {
            DocumentService service = getDocumentService();
            Element el = service.getElement(Long.parseLong(elementId));
            service.startProcess(el.getParent(), processKey);
            closeDocumentService(service);
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public void copyData(Element from, String to, String templateFrom, String fieldFrom, String templateTo, String fieldTo, DocumentService service) throws ProcessException {
        try {
            List<Object> data = from.getfieldData(templateFrom, fieldFrom);
            if (data != null && data.size() > 0) {
                addMetadataValue(to, templateTo, fieldTo, data.get(0), service);
            }
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    //TODO: verificare il problema delle connessione se si può ovviare
    //attenzione creo una connessione ogni volta che invoco il metodo usare con parsimonia
    public boolean userInGroup(String userid, String group) {
        IUser user = (IUser) userService.loadUserByUsername(userid);
        return user.hasRole(group);
    }

    //TODO: verificare il problema delle connessione se si può ovviare
    //attenzione creo una connessione ogni volta che invoco il metodo usare con parsimonia
    public IUser getUser(String userid) {
        IUser user = (IUser) userService.loadUserByUsername(userid);
        return user;
    }

    public String getMetadataField(String elementId, String templateName, String fieldName) throws Exception {
        return getMetadataField(elementId, templateName, fieldName, false);
    }

    public String getMetadataField(String elementId, String templateName, String fieldName, boolean code) throws ProcessException {
        try {
            DocumentService service = getDocumentService();
            String value = getMetadataField(elementId, templateName, fieldName, code, service);
            closeDocumentService(service);
            return value;
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    private String getMetadataField(String elementId, String templateName, String fieldName, boolean code, DocumentService service) {
        Element el = service.getElement(elementId);
        String value = el.getFieldDataString(templateName, fieldName);
        if (code) {
            value = el.getFieldDataCode(templateName, fieldName);
        }
        return value;
    }

    @Autowired
    @Qualifier("messagesFolder")
    protected String templatePath;

    public String getTemplatePath() {
        return templatePath;
    }

    public void setTemplatePath(String templatePath) {
        this.templatePath = templatePath;
    }

    public String getEmailBody(String elementId, String emailTemplateName) throws ProcessException {
        try {
            DocumentService service = getDocumentService();
            String value = getEmailBody(elementId, emailTemplateName, service);
            closeDocumentService(service);
            return value;
        } catch (Exception ex) {
            log.error(ex.getMessage(), ex);
            throw new ProcessException(ex, globalTx);
        }
    }

    public String getEmailBody(String elementId, String emailTemplateName, DocumentService service) throws IOException {
        String mail = readFile(templatePath + "/email/" + emailTemplateName + ".html", Charset.defaultCharset());
        Element el = service.getElement(elementId);
        String mailBodyProcessed = el.applyRegexString(mail);
        return mailBodyProcessed;
    }

    static String readFile(String path, Charset encoding)
            throws IOException {
        byte[] encoded = Files.readAllBytes(Paths.get(path));
        return new String(encoded, encoding);
    }


}
