package it.cineca.siss.axmr3.doc.process;

import it.cineca.siss.axmr3.doc.acl.Policy;
import it.cineca.siss.axmr3.doc.entities.Element;
import it.cineca.siss.axmr3.doc.web.services.DocumentService;
import it.cineca.siss.axmr3.transactions.Axmr3TXManagerNonRequestScoped;
import org.activiti.engine.delegate.DelegateTask;

import java.util.HashMap;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 28/10/13
 * Time: 17:15
 * To change this template use File | Settings | File Templates.
 */
public interface IProcessActionsBean {
    Axmr3TXManagerNonRequestScoped getGlobalTx();

    DocumentService getDocumentService() throws Exception;

    void closeDocumentService(DocumentService service);

    void addTemplate(String elId, String templateName) throws Exception;

    void addMetadataValue(String elId, String templateName, String fieldName, Object value) throws Exception;

    void changePermissionToGroup(String elementId,  String permissions,String ftl, String group) throws Exception;

    void changePermissionToUser(String elementId,  String permissions,String ftl, String username) throws Exception;

    List<Element> getChildren(String elementId, List<String> typeIds, HashMap<String, Object> fieldValues) throws Exception;

    void sendMail(String[] to, String subject, String message, String from);

    Long cloneElement(String elementId, String userid) throws Exception;

    void checkTemplateCompleted(String elementId, String template, DelegateTask task) throws Exception;

    void changeTemplatePermissionToUser(String elementId, String templateName, String permissions, String username) throws Exception;

    void changeTemplatePermissionToGroup(String elementId, String templateName, String permissions, String group) throws Exception;
}
