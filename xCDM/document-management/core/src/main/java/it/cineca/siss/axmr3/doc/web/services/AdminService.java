package it.cineca.siss.axmr3.doc.web.services;


import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.common.mvc.handlers.ControllerHandler;
import it.cineca.siss.axmr3.doc.acl.Policy;
import it.cineca.siss.axmr3.doc.acl.TemplatePolicy;
import it.cineca.siss.axmr3.doc.entities.*;
import it.cineca.siss.axmr3.doc.types.MetadataFieldType;
import it.cineca.siss.axmr3.doc.web.exceptions.RestException;
import it.cineca.siss.axmr3.doc.xml.Field;
import it.cineca.siss.axmr3.doc.xml.Form;
import it.cineca.siss.axmr3.exceptions.AxmrGenericException;
import it.cineca.siss.axmr3.hibernate.BaseDao;
import it.cineca.siss.axmr3.log.Log;
import it.cineca.siss.axmr3.transactions.Axmr3TXManager;
import it.cineca.siss.axmr3.web.freemarker.AxmrFreemarkerConfigurer;
import net.lingala.zip4j.exception.ZipException;
import net.lingala.zip4j.io.ZipOutputStream;
import net.lingala.zip4j.model.ZipParameters;
import net.lingala.zip4j.util.Zip4jConstants;
import org.activiti.engine.ProcessEngine;
import org.activiti.engine.RepositoryService;
import org.activiti.engine.repository.DeploymentBuilder;
import org.activiti.engine.repository.ProcessDefinition;
import org.apache.commons.codec.binary.Base64;
import org.apache.commons.io.FileUtils;
import org.apache.commons.io.IOUtils;
import org.apache.log4j.Logger;
import org.hibernate.Criteria;
import org.hibernate.criterion.Order;
import org.hibernate.criterion.Restrictions;
import org.hibernate.internal.util.SerializationHelper;
import org.springframework.beans.factory.InitializingBean;
import org.springframework.beans.factory.annotation.Autowired;
import org.w3c.dom.Document;
import org.xml.sax.SAXException;

import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServletRequest;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.*;
import java.io.File;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.security.MessageDigest;
import java.util.*;

import static it.cineca.siss.axmr3.doc.StdUtils.toCamelCase;


/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 01/08/13
 * Time: 15.01
 * To change this template use File | Settings | File Templates.
 */
public class AdminService implements InitializingBean {
    private BaseDao<ElementType> docTypeDAO;
    private BaseDao<MetadataTemplate> mdDAO;
    private BaseDao<MetadataField> mdFieldDAO;
    private BaseDao<PredefinedPolicy> policyDAO;
    private BaseDao<Acl> aclDAO;
    private BaseDao<AclContainer> aclContainerDAO;
    private BaseDao<ElementTypeAssociatedTemplate> elTypeAssocTemplateDAO;
    private BaseDao<ElementTypeAssociatedWorkflow> wfAssocDAO;
    private BaseDao<TemplateAcl> tplAclDAO;
    private BaseDao<TemplateAclContainer> tplAclContainerDAO;
    private BaseDao<CalendarEntity> calDAO;

    private static final Logger log= Logger.getLogger(AdminService.class);

    @Autowired
    protected ProcessEngine processEngine;

    public ProcessEngine getProcessEngine() {
        return processEngine;
    }

    public void setProcessEngine(ProcessEngine processEngine) {
        this.processEngine = processEngine;
    }

    public Axmr3TXManager getTxManager() {
        return txManager;
    }

    public void setTxManager(Axmr3TXManager txManager) {
        this.txManager = txManager;
    }

    @Autowired
    protected Axmr3TXManager txManager;

    @Autowired
    public AxmrFreemarkerConfigurer fmCfg;

    public AxmrFreemarkerConfigurer getFmCfg() {
        return fmCfg;
    }

    public void setFmCfg(AxmrFreemarkerConfigurer fmCfg) {
        this.fmCfg = fmCfg;
    }

    public ZipOutputStream zipBpm(OutputStream out) throws ZipException, IOException {
        ZipOutputStream zip = new ZipOutputStream(out);
        ZipParameters parameters = new ZipParameters();
        parameters.setCompressionMethod(Zip4jConstants.COMP_DEFLATE);
        parameters.setCompressionLevel(Zip4jConstants.DEFLATE_LEVEL_NORMAL);
        parameters.setSourceExternalStream(true);
        parameters.setEncryptFiles(false);
        RepositoryService repository = processEngine.getRepositoryService();
        List<ProcessDefinition> deployements = repository.createProcessDefinitionQuery().latestVersion().list();
        for (ProcessDefinition deploy : deployements) {
            parameters.setFileNameInZip(deploy.getKey() + ".bpmn20.xml");
            zip.putNextEntry(null, parameters);
            InputStream model = repository.getProcessModel(deploy.getId());

            byte[] readBuff = new byte[4096];
            int readLen = -1;
            while ((readLen = model.read(readBuff)) != -1) {
                zip.write(readBuff, 0, readLen);
                //out.write(readBuff, 0, readLen);
            }
            //ZipFile zipFile = new ZipFile("");
            //zipFile.addStream(model, parameters);
            zip.closeEntry();
            model.close();
        }
        zip.finish();
        //return zip;
        return null;
    }

    public void afterPropertiesSet() throws Exception {
        String txName = "doc";
        docTypeDAO = new BaseDao<ElementType>(txManager, txName, ElementType.class);
        mdDAO = new BaseDao<MetadataTemplate>(txManager, txName, MetadataTemplate.class);
        mdFieldDAO = new BaseDao<MetadataField>(txManager, txName, MetadataField.class);
        policyDAO = new BaseDao<PredefinedPolicy>(txManager, txName, PredefinedPolicy.class);
        aclDAO = new BaseDao<Acl>(txManager, txName, Acl.class);
        aclContainerDAO = new BaseDao<AclContainer>(txManager, txName, AclContainer.class);
        elTypeAssocTemplateDAO = new BaseDao<ElementTypeAssociatedTemplate>(txManager, txName, ElementTypeAssociatedTemplate.class);
        wfAssocDAO = new BaseDao<ElementTypeAssociatedWorkflow>(txManager, txName, ElementTypeAssociatedWorkflow.class);
        tplAclDAO = new BaseDao<TemplateAcl>(txManager, txName, TemplateAcl.class);
        tplAclContainerDAO = new BaseDao<TemplateAclContainer>(txManager, txName, TemplateAclContainer.class);
        calDAO = new BaseDao<CalendarEntity>(txManager, txName, CalendarEntity.class);

    }

    public String allinea() throws Exception {

        String txName = "doc2";
        String out="";
        BaseDao<ElementType> docTypeDAO2 = new BaseDao<ElementType>(txManager, txName, ElementType.class);
        BaseDao<MetadataTemplate> mdDAO2 = new BaseDao<MetadataTemplate>(txManager, txName, MetadataTemplate.class);
        BaseDao<MetadataField> mdFieldDAO2 = new BaseDao<MetadataField>(txManager, txName, MetadataField.class);
        BaseDao<PredefinedPolicy> policyDAO2 = new BaseDao<PredefinedPolicy>(txManager, txName, PredefinedPolicy.class);
        BaseDao<Acl> aclDAO2 = new BaseDao<Acl>(txManager, txName, Acl.class);
        BaseDao<AclContainer> aclContainerDAO2 = new BaseDao<AclContainer>(txManager, txName, AclContainer.class);
        BaseDao<ElementTypeAssociatedTemplate> elTypeAssocTemplateDAO2 = new BaseDao<ElementTypeAssociatedTemplate>(txManager, txName, ElementTypeAssociatedTemplate.class);
        BaseDao<ElementTypeAssociatedWorkflow> wfAssocDAO2 = new BaseDao<ElementTypeAssociatedWorkflow>(txManager, txName, ElementTypeAssociatedWorkflow.class);
        BaseDao<TemplateAcl> tplAclDAO2 = new BaseDao<TemplateAcl>(txManager, txName, TemplateAcl.class);
        BaseDao<TemplateAclContainer> tplAclContainerDAO2 = new BaseDao<TemplateAclContainer>(txManager, txName, TemplateAclContainer.class);
        BaseDao<CalendarEntity> calDAO2 = new BaseDao<CalendarEntity>(txManager, txName, CalendarEntity.class);

        List<ElementType> types = getTypes();
        List<MetadataTemplate> templates = getMds();
        List<PredefinedPolicy> policies = getPolicies();


        HashMap<ElementType, ElementType> matchedTypes = new HashMap<ElementType, ElementType>();
        HashMap<MetadataTemplate, MetadataTemplate> matchedTemplates = new HashMap<MetadataTemplate, MetadataTemplate>();
        HashMap<PredefinedPolicy, PredefinedPolicy> matchedPolicies = new HashMap<PredefinedPolicy, PredefinedPolicy>();

        HashMap<ElementTypeAssociatedTemplate, ElementTypeAssociatedTemplate> matchedAssociatedTemplates = new HashMap<ElementTypeAssociatedTemplate, ElementTypeAssociatedTemplate>();

        List<ElementType> foundTypes;
        List<MetadataTemplate> foundTemplates;
        List<PredefinedPolicy> foundPolicies;

        HashMap<String, ElementType> newTypes = new HashMap<String, ElementType>();
        HashMap<String, MetadataTemplate> newTemplates = new HashMap<String, MetadataTemplate>();
        HashMap<String, PredefinedPolicy> newPolicies = new HashMap<String, PredefinedPolicy>();


        HashMap<String, TemplateAcl> origTemplateAcls;
        HashMap<String, TemplateAcl> destTemplateAcls;

        String outMessage = "";

        for (ElementType type : types) {
            if (!type.isDeleted()) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Verifico type " + type.getTypeId());
                foundTypes = getElementTypeByTypeId(type.getTypeId(), docTypeDAO2);
                if (foundTypes != null && foundTypes.size() > 0) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"type " + type.getTypeId() + " ha " + foundTypes.size() + " risultati");
                    if (foundTypes.size() == 1) {
                        if (!type.getId().equals(foundTypes.get(0).getId()))
                            it.cineca.siss.axmr3.log.Log.debug(getClass(),"type " + type.getTypeId() + " ha  ID differenti ");
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"type " + type.getTypeId() + " ha  " + type.getHashBack() + " e " + foundTypes.get(0).getHashBack());
                        matchedTypes.put(type, copyToOld(type, foundTypes.get(0)));
                    }
                    if (!foundTypes.get(0).equals(type)) {
                        outMessage = "type " + type.getTypeId() + " non è identico <a href='apply/type/"+type.getTypeId()+"'>Allinea</a>";
                        out+= outMessage+"\n";
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                    }
                } else {
                    outMessage = "type " + type.getTypeId() + " manca <a href='apply/type/"+type.getTypeId()+"'>Allinea</a>";
                    out+= outMessage+"\n";
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                    matchedTypes.put(type, copyToNew(type));
                }
                newTypes.put(type.getTypeId(), matchedTypes.get(type));
            }
        }

        for (MetadataTemplate template : templates) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Verifico template " + template.getName());
            foundTemplates = getTemplateByName(template.getName(), mdDAO2);
            if (foundTemplates != null && foundTemplates.size() > 0) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"template " + template.getName() + " ha " + foundTemplates.size() + " risultati");
                if (foundTemplates.size() == 1) {
                    if (!template.getId().equals(foundTemplates.get(0).getId()))
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"template " + template.getName() + " ha  ID differenti ");
                    matchedTemplates.put(template, copyToOld(template, foundTemplates.get(0)));
                }
                if (!foundTemplates.get(0).equals(template)) {
                    outMessage = "template " + template.getName() + " non è identico";
                    out+= outMessage+"\n";
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                }
            } else {
                outMessage = "template " + template.getName() + " manca";
                out+= outMessage+"\n";
                it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                matchedTemplates.put(template, copyToNew(template));
            }
            newTemplates.put(template.getName(), matchedTemplates.get(template));
        }

        for (PredefinedPolicy policy : policies) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Verifico policy " + policy.getName());
            foundPolicies = getPolicyByName(policy.getName(), policyDAO2);
            if (foundPolicies != null && foundPolicies.size() > 0) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"policy " + policy.getName() + " ha " + foundPolicies.size() + " risultati");
                if (foundPolicies.size() == 1) {
                    if (!policy.getId().equals(foundPolicies.get(0).getId()))
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"policy " + policy.getName() + " ha  ID differenti ");
                    matchedPolicies.put(policy, copyToOld(policy, foundPolicies.get(0)));
                }
            } else {
                outMessage = "policy " + policy.getName() + " manca";
                out+= outMessage+"\n";
                it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                matchedPolicies.put(policy, copyToNew(policy));
            }
            newPolicies.put(policy.getName(), matchedPolicies.get(policy));
        }

        for (ElementType currType : matchedTypes.keySet()) {
            ElementType destType = matchedTypes.get(currType);

            HashMap<String, ElementType> children = currType.getAllowedChildrenMap();
            HashMap<String, ElementType> children2 = new HashMap<String, ElementType>();
            HashMap<String, ElementTypeAssociatedTemplate> associatedTemplates = currType.getAssociatedTemplateMap();
            HashMap<String, ElementTypeAssociatedTemplate> associatedTemplates2 = new HashMap<String, ElementTypeAssociatedTemplate>();
            HashMap<String, ElementTypeAssociatedWorkflow> associatedWF = currType.getAssociatedWorkflowMap();
            HashMap<String, ElementTypeAssociatedWorkflow> associatedWF2 = new HashMap<String, ElementTypeAssociatedWorkflow>();


            if (destType.getId() != null) {
                children2 = destType.getAllowedChildrenMap();
                associatedTemplates2 = destType.getAssociatedTemplateMap();
                associatedWF2 = destType.getAssociatedWorkflowMap();
            } else {
                destType.setAllowedChilds(new LinkedList<ElementType>());
                destType.setAssociatedTemplates(new LinkedList<ElementTypeAssociatedTemplate>());
                destType.setAssociatedWorkflows(new LinkedList<ElementTypeAssociatedWorkflow>());
                destType.setAcls(new LinkedList<Acl>());
            }

            for (String childType : children.keySet()) {
                if (!children2.containsKey(childType)) {
                    outMessage = "in type " + currType.getTypeId() + " manca child " + childType;
                    out+= outMessage+"\n";
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                    destType.getAllowedChilds().add(newTypes.get(childType));
                }
            }


            for (String associatedTemplate : associatedTemplates.keySet()) {
                ElementTypeAssociatedTemplate orig = associatedTemplates.get(associatedTemplate);
                if (associatedTemplates2.containsKey(associatedTemplate)) {

                    ElementTypeAssociatedTemplate dest = associatedTemplates.get(associatedTemplate);
                    matchedAssociatedTemplates.put(orig, copyToOld(orig, dest));
                    origTemplateAcls = orig.getTemplateAclsMap();
                    destTemplateAcls = dest.getTemplateAclsMap();
                    if (!origTemplateAcls.isEmpty() && !destTemplateAcls.isEmpty()) {
                        for (String container : origTemplateAcls.keySet()) {
                            if (!destTemplateAcls.containsKey(container)) {
                                outMessage = "in type " + currType.getTypeId() + " il template " + associatedTemplate + " non ha le stesse acl per container " + container;
                                out+= outMessage+"\n";
                                it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                            }
                        }
                        for (String container : destTemplateAcls.keySet()) {
                            if (!origTemplateAcls.containsKey(container)) {
                                outMessage = "in type " + currType.getTypeId() + " il template " + associatedTemplate + " non ha le stesse acl per container " + container;
                                out+= outMessage+"\n";
                                it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                            }
                        }
                    } else if (!origTemplateAcls.isEmpty() || !destTemplateAcls.isEmpty()) {
                        outMessage = "in type " + currType.getTypeId() + " il template " + associatedTemplate + " non ha le stesse acl";
                        out+= outMessage+"\n";
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                    }
                } else {
                    outMessage = "in type " + currType.getTypeId() + " manca template " + associatedTemplate;
                    out+= outMessage+"\n";
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                    matchedAssociatedTemplates.put(orig, copyToNew(orig, matchedTemplates.get(orig.getMetadataTemplate()),currType));
                }
            }

            for (String wf : associatedWF.keySet()) {
                if (!associatedWF2.containsKey(wf)) {
                    outMessage = "in type " + currType.getTypeId() + " manca il wf " + wf;
                    out+= outMessage+"\n";
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                }else if(!associatedWF2.get(wf).equals(associatedWF.get(wf))){
                    outMessage = "in type " + currType.getTypeId() + " non c'e' uniformita' per il wf " + wf;
                    out+= outMessage+"\n";
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                }
            }

            for (Acl currAcl : currType.getAcls()) {
                boolean found = false;
                String container = "";
                if (currAcl.getContainers().iterator().hasNext())
                    container = currAcl.getContainers().iterator().next().getContainer();
                for (Acl confrontAcl : destType.getAcls()) {
                    PredefinedPolicy predefinedPol = currAcl.getPredifinedPolicy();
                    PredefinedPolicy confrontPol = confrontAcl.getPredifinedPolicy();
                    if (predefinedPol != null) {
                        if (confrontPol != null) {
                            if (predefinedPol.getName().equals(confrontPol.getName()) && container.equals(confrontAcl.getContainers().iterator().next().getContainer())) {
                                found = true;
                                break;
                            }
                        }
                    } else {
                        if (confrontPol == null) {
                            if (confrontAcl.getContainers().iterator().hasNext() && container.equals(confrontAcl.getContainers().iterator().next().getContainer())) {
                                Integer confrontValue = confrontAcl.getPolicyValue();
                                Integer currValue = currAcl.getPolicyValue();
                                if (currValue.equals(confrontValue)) {
                                    found = true;
                                    break;
                                }
                            }
                        }
                    }
                }
                if (!found) {
                    outMessage = "in type " + currType.getTypeId() + " manca acl per container " + container;
                    out+= outMessage+"\n";
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                }
            }
        }

        for (MetadataTemplate currTemplate : matchedTemplates.keySet()) {
            MetadataTemplate destTemplate = matchedTemplates.get(currTemplate);
            try {
                HashMap<String, MetadataField> fields = currTemplate.getFieldsMap();
                HashMap<String, MetadataField> confrontFields = destTemplate.getFieldsMap();
                for (String field : fields.keySet()) {
                    if (!confrontFields.containsKey(field)) {
                        outMessage = "in template " + currTemplate.getName() + " manca field " + field;
                        out+= outMessage+"\n";
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                    } else {
                        if (!confrontFields.get(field).equals(fields.get(field))) {
                            outMessage = "in template " + currTemplate.getName() + " field " + field + " non è identico";
                            out+= outMessage+"\n";
                            it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                        }
                    }
                }
            } catch (Exception ex) {
                outMessage = "in template " + currTemplate.getName() + " non e' riuscito il controllo dei field";
                out+= outMessage+"\n";
                it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
            }
        }
        return out;

    }

    public void allineaType(ServletOutputStream out,String typeId) throws Exception {

        String txName = "doc2";
        //Long inputId=Long.parseLong(typeId);

        BaseDao<ElementType> docTypeDAO2 = new BaseDao<ElementType>(txManager, txName, ElementType.class);
        BaseDao<MetadataTemplate> mdDAO2 = new BaseDao<MetadataTemplate>(txManager, txName, MetadataTemplate.class);
        BaseDao<MetadataField> mdFieldDAO2 = new BaseDao<MetadataField>(txManager, txName, MetadataField.class);
        BaseDao<PredefinedPolicy> policyDAO2 = new BaseDao<PredefinedPolicy>(txManager, txName, PredefinedPolicy.class);
        BaseDao<Acl> aclDAO2 = new BaseDao<Acl>(txManager, txName, Acl.class);
        BaseDao<AclContainer> aclContainerDAO2 = new BaseDao<AclContainer>(txManager, txName, AclContainer.class);
        BaseDao<ElementTypeAssociatedTemplate> elTypeAssocTemplateDAO2 = new BaseDao<ElementTypeAssociatedTemplate>(txManager, txName, ElementTypeAssociatedTemplate.class);
        BaseDao<ElementTypeAssociatedWorkflow> wfAssocDAO2 = new BaseDao<ElementTypeAssociatedWorkflow>(txManager, txName, ElementTypeAssociatedWorkflow.class);
        BaseDao<TemplateAcl> tplAclDAO2 = new BaseDao<TemplateAcl>(txManager, txName, TemplateAcl.class);
        BaseDao<TemplateAclContainer> tplAclContainerDAO2 = new BaseDao<TemplateAclContainer>(txManager, txName, TemplateAclContainer.class);
        BaseDao<CalendarEntity> calDAO2 = new BaseDao<CalendarEntity>(txManager, txName, CalendarEntity.class);

        //List<ElementType> types = getTypes();

        List<PredefinedPolicy> policies = getPolicies();
        ElementType type = getElementTypeByTypeId(typeId).get(0);


        ElementType myType;
        MetadataTemplate myTemplate;
        TemplateAcl myTemplateAcl;
        MetadataField myField;
        Acl myAcl;
        AclContainer myAclContainer;
        ElementTypeAssociatedTemplate myAssocTemplate;
        ElementTypeAssociatedWorkflow myAssocWf;
        MetadataTemplate template;

        HashMap<ElementType, ElementType> matchedTypes = new HashMap<ElementType, ElementType>();
        HashMap<MetadataTemplate, MetadataTemplate> matchedTemplates = new HashMap<MetadataTemplate, MetadataTemplate>();
        HashMap<PredefinedPolicy, PredefinedPolicy> matchedPolicies = new HashMap<PredefinedPolicy, PredefinedPolicy>();

        HashMap<ElementTypeAssociatedTemplate, ElementTypeAssociatedTemplate> matchedAssociatedTemplates = new HashMap<ElementTypeAssociatedTemplate, ElementTypeAssociatedTemplate>();

        List<ElementType> foundTypes;
        List<MetadataTemplate> foundTemplates;
        List<PredefinedPolicy> foundPolicies;

        HashMap<String, ElementType> newTypes = new HashMap<String, ElementType>();
        HashMap<String, MetadataTemplate> newTemplates = new HashMap<String, MetadataTemplate>();
        HashMap<String, PredefinedPolicy> newPolicies = new HashMap<String, PredefinedPolicy>();


        HashMap<String, TemplateAcl> origTemplateAcls;
        HashMap<String, TemplateAcl> destTemplateAcls;

        String outMessage = "";

        //for (ElementType type : types) {
            if (!type.isDeleted()) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Verifico type " + type.getTypeId());
                foundTypes = getElementTypeByTypeId(type.getTypeId(), docTypeDAO2);
                if (foundTypes != null && foundTypes.size() > 0) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"type " + type.getTypeId() + " ha " + foundTypes.size() + " risultati");
                    if (foundTypes.size() == 1) {

                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"type " + type.getTypeId() + " ha  " + type.getHashBack() + " e " + foundTypes.get(0).getHashBack());
                        myType = copyToOld(type, foundTypes.get(0));

                        matchedTypes.put(type, myType);

                        if (!foundTypes.get(0).equals(type)) {

                            docTypeDAO2.getSession().evict(foundTypes.get(0));
                            docTypeDAO2.saveOrUpdate(myType);
                            outMessage = "type " + type.getTypeId() + " non è identico";
                            out.write((outMessage + "\n").getBytes());
                            it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                            outMessage = "type hashback " + myType.getHashBack();
                            out.write((outMessage + "\n").getBytes());
                            it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                        }
                    }
                } else {

                    outMessage = "type " + type.getTypeId() + " manca";
                    out.write((outMessage + "\n").getBytes());
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                    myType = copyToNew(type);
                    docTypeDAO2.saveOrUpdate(myType);
                    matchedTypes.put(type, myType);

                }
                newTypes.put(type.getTypeId(), matchedTypes.get(type));
            }
        //}



        for (PredefinedPolicy policy : policies) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Verifico policy " + policy.getName());
            foundPolicies = getPolicyByName(policy.getName(), policyDAO2);
            if (foundPolicies != null && foundPolicies.size() > 0) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"policy " + policy.getName() + " ha " + foundPolicies.size() + " risultati");
                if (foundPolicies.size() == 1) {
                    if (!policy.getId().equals(foundPolicies.get(0).getId()))
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"policy " + policy.getName() + " ha  ID differenti ");
                    matchedPolicies.put(policy, copyToOld(policy, foundPolicies.get(0)));
                }
            } else {
                outMessage = "policy " + policy.getName() + " manca";
                out.write((outMessage + "\n").getBytes());
                it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                matchedPolicies.put(policy, copyToNew(policy));
            }
            newPolicies.put(policy.getName(), matchedPolicies.get(policy));
        }

        for (ElementType currType : matchedTypes.keySet()) {
            ElementType destType = matchedTypes.get(currType);

            HashMap<String, ElementType> children = currType.getAllowedChildrenMap();
            HashMap<String, ElementType> children2 = new HashMap<String, ElementType>();
            HashMap<String, ElementTypeAssociatedTemplate> associatedTemplates = currType.getAssociatedTemplateMap();
            HashMap<String, ElementTypeAssociatedTemplate> associatedTemplates2 = new HashMap<String, ElementTypeAssociatedTemplate>();
            HashMap<String, ElementTypeAssociatedWorkflow> associatedWF = currType.getAssociatedWorkflowMap();
            HashMap<String, ElementTypeAssociatedWorkflow> associatedWF2 = new HashMap<String, ElementTypeAssociatedWorkflow>();


            if (destType.getId() != null) {
                children2 = destType.getAllowedChildrenMap();
                associatedTemplates2 = destType.getAssociatedTemplateMap();
                associatedWF2 = destType.getAssociatedWorkflowMap();
            } else {
                destType.setAllowedChilds(new LinkedList<ElementType>());
                destType.setAssociatedTemplates(new LinkedList<ElementTypeAssociatedTemplate>());
                destType.setAssociatedWorkflows(new LinkedList<ElementTypeAssociatedWorkflow>());
                destType.setAcls(new LinkedList<Acl>());
            }

            for (String childType : children.keySet()) {
                if (!children2.containsKey(childType)) {
                    List<ElementType> childTypeMatches = getElementTypeByTypeId(childType,docTypeDAO2);
                    ElementType childTypeMatch;
                    outMessage = "in type " + currType.getTypeId() + " manca child " + childType;
                    out.write((outMessage + "\n").getBytes());
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                    if(childTypeMatches.size()==1){

                        childTypeMatch=childTypeMatches.get(0);
                        destType.getAllowedChilds().add(childTypeMatch);
                        docTypeDAO2.saveOrUpdate(destType);
                        outMessage = "in type aggiungo " + destType.getTypeId() + " aggiungo child " + childTypeMatch.getTypeId();
                        out.write((outMessage + "\n").getBytes());
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                    }
                    else{
                        outMessage = "in type " + currType.getTypeId() + " trovati "+childTypeMatches.size()+" risultati per child " + childType;
                        out.write((outMessage + "\n").getBytes());
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                    }

                    destType.getAllowedChilds().add(newTypes.get(childType));
                }
            }


            for (String associatedTemplate : associatedTemplates.keySet()) {
                ElementTypeAssociatedTemplate orig = associatedTemplates.get(associatedTemplate);
                //for (MetadataTemplate template : templates) {
                template=orig.getMetadataTemplate();
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Verifico template " + template.getName());
                foundTemplates = getTemplateByName(template.getName(), mdDAO2);

                if (foundTemplates != null && foundTemplates.size() > 0) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"template " + template.getName() + " ha " + foundTemplates.size() + " risultati");
                    if (foundTemplates.size() == 1) {
                        if (!template.getId().equals(foundTemplates.get(0).getId()))
                            it.cineca.siss.axmr3.log.Log.debug(getClass(),"template " + template.getName() + " ha  ID differenti ");
                        myTemplate=copyToOld(template, foundTemplates.get(0));
                        matchedTemplates.put(template, myTemplate);

                        if (!foundTemplates.get(0).equals(template)) {
                            mdDAO2.getSession().evict(foundTemplates.get(0));
                            mdDAO2.saveOrUpdate(myTemplate);
                            outMessage = "template " + template.getName() + " non è identico";
                            out.write((outMessage + "\n").getBytes());
                            it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                        }
                    }
                } else {
                    myTemplate=copyToNew(template);
                    mdDAO2.saveOrUpdate(myTemplate);
                    outMessage = "template " + template.getName() + " manca";
                    out.write((outMessage + "\n").getBytes());
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                    matchedTemplates.put(template, myTemplate);
                }
                newTemplates.put(template.getName(), matchedTemplates.get(template));
                ///}

                if (associatedTemplates2.containsKey(associatedTemplate)) {

                    ElementTypeAssociatedTemplate dest = associatedTemplates.get(associatedTemplate);



                    origTemplateAcls = orig.getTemplateAclsMap();
                    destTemplateAcls = dest.getTemplateAclsMap();

                    for (String container : origTemplateAcls.keySet()) {
                        if (!destTemplateAcls.containsKey(container) || !destTemplateAcls.get(container).equals(origTemplateAcls.get(container))) {
                            if(destTemplateAcls.containsKey(container)){
                                myTemplateAcl=copyToOld(origTemplateAcls.get(container),destTemplateAcls.get(container));
                                tplAclContainerDAO2.getSession().evict(destTemplateAcls.get(container));
                            }else {
                                myTemplateAcl = copyToNew(destTemplateAcls.get(container),dest);
                                for(TemplateAclContainer currContainer:myTemplateAcl.getContainers()){
                                    currContainer.setId(null);
                                    tplAclContainerDAO2.saveOrUpdate(currContainer);
                                }
                            }
                            tplAclDAO2.saveOrUpdate(myTemplateAcl);
                            dest.getTemplateAcls().add(myTemplateAcl);
                            elTypeAssocTemplateDAO2.saveOrUpdate(dest);
                            outMessage = "in type " + currType.getTypeId() + " il template " + associatedTemplate + " non ha le stesse acl per container " + container;
                            out.write((outMessage + "\n").getBytes());
                            it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                        }
                    }
                    for (String container : destTemplateAcls.keySet()) {
                        if (!origTemplateAcls.containsKey(container)) {
                            tplAclDAO2.delete(destTemplateAcls.get(container));
                            outMessage = "in type " + currType.getTypeId() + " il template " + associatedTemplate + " non ha le stesse acl per container " + container;
                            out.write((outMessage + "\n").getBytes());
                            it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                        }
                    }


                } else {
                    MetadataTemplate destTemplate = matchedTemplates.get(orig.getMetadataTemplate());
                    myAssocTemplate=copyToNew(orig, destTemplate,destType);

                    origTemplateAcls = orig.getTemplateAclsMap();
                    destTemplateAcls = myAssocTemplate.getTemplateAclsMap();
                    elTypeAssocTemplateDAO2.saveOrUpdate(myAssocTemplate);
                    for (String container : origTemplateAcls.keySet()) {
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"Verifico container " + container + " per id "+orig.getId());
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"Verifico dest acl " + destTemplateAcls.get(container).toString());
                            myTemplateAcl=copyToNew(destTemplateAcls.get(container),myAssocTemplate);

                            tplAclDAO2.saveOrUpdate(myTemplateAcl);
                            for(TemplateAclContainer currContainer:myTemplateAcl.getContainers()){
                                currContainer.setId(null);
                                //currContainer.getAcl();
                                tplAclContainerDAO2.saveOrUpdate(currContainer);
                            }
                            myAssocTemplate.getTemplateAcls().add(myTemplateAcl);
                            out.write((outMessage + "\n").getBytes());
                            it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);

                    }


                    outMessage = "in type " + currType.getTypeId() + " manca template " + associatedTemplate;
                    out.write((outMessage + "\n").getBytes());
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                    matchedAssociatedTemplates.put(orig, myAssocTemplate);
                }
            }

            for (MetadataTemplate currTemplate : matchedTemplates.keySet()) {
                MetadataTemplate destTemplate = matchedTemplates.get(currTemplate);
                try {
                    HashMap<String, MetadataField> fields = currTemplate.getFieldsMap();
                    HashMap<String, MetadataField> confrontFields = destTemplate.getFieldsMap();
                    for (String field : fields.keySet()) {
                        if (!confrontFields.containsKey(field)) {
                            myField=copyToNew(fields.get(field),destTemplate);
                            mdFieldDAO2.saveOrUpdate(myField);
                            outMessage = "in template " + currTemplate.getName() + " manca field " + field;
                            out.write((outMessage + "\n").getBytes());
                            it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                        } else {
                            if (!confrontFields.get(field).equals(fields.get(field))) {
                                myField=copyToOld(fields.get(field), confrontFields.get(field));
                                mdFieldDAO2.getSession().evict(confrontFields.get(field));
                                mdFieldDAO2.saveOrUpdate(myField);
                                outMessage = "in template " + currTemplate.getName() + " field " + field + " non e' identico ";

                                out.write((outMessage + "\n").getBytes());
                                it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                            }
                        }
                    }
                } catch (Exception ex) {
                    log.error(ex.getMessage(), ex);
                    outMessage = "in template " + currTemplate.getName() + " non e' riuscito il controllo dei field";
                    out.write((outMessage + "\n").getBytes());
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                }
            }

            MetadataField titleField = type.getTitleField();
            MetadataField newTitleField = currType.getTitleField();

            if(titleField!=null && !titleField.equals(newTitleField)){

                MetadataTemplate templateTitle = matchedTemplates.get(titleField.getTemplate().getName());
                outMessage = "il template del titlefield e' " + templateTitle.getName() + "";
                out.write((outMessage + "\n").getBytes());
                it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                if(templateTitle!=null){


                    HashMap<String, MetadataField> templateFields = templateTitle.getFieldsMap();
                    currType.setTitleField(templateFields.get(titleField.getName()));
                    outMessage = "il field e' " +templateFields.get(titleField.getName()).getId() + "";
                    out.write((outMessage + "\n").getBytes());
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                    docTypeDAO2.saveOrUpdate(currType);
                }
            }

            for (String wf : associatedWF.keySet()) {
                if (!associatedWF2.containsKey(wf)) {
                    myAssocWf=copyToNew(associatedWF.get(wf),destType);
                    wfAssocDAO2.saveOrUpdate(myAssocWf);
                    outMessage = "in type " + currType.getTypeId() + " manca il wf " + wf;
                    out.write((outMessage + "\n").getBytes());
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                }else if(!associatedWF2.get(wf).equals(associatedWF.get(wf))){
                    myAssocWf=copyToOld(associatedWF.get(wf),associatedWF2.get(wf));
                    wfAssocDAO2.getSession().evict(associatedWF2.get(wf));
                    wfAssocDAO2.saveOrUpdate(myAssocWf);
                    outMessage = "in type " + currType.getTypeId() + " non c'e' uniformita' per il wf " + wf;
                    out.write((outMessage + "\n").getBytes());
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                }
            }
            //fin qui
            for (Acl currAcl : currType.getAcls()) {
                boolean found = false;
                String container = "";
                if (currAcl.getContainers().iterator().hasNext())
                    container = currAcl.getContainers().iterator().next().getContainer();
                for (Acl confrontAcl : destType.getAcls()) {
                    PredefinedPolicy predefinedPol = currAcl.getPredifinedPolicy();
                    PredefinedPolicy confrontPol = confrontAcl.getPredifinedPolicy();
                    if (predefinedPol != null) {
                        if (confrontPol != null) {
                            if (predefinedPol.getName().equals(confrontPol.getName()) && container.equals(confrontAcl.getContainers().iterator().next().getContainer())) {
                                found = true;
                                break;
                            }
                        }
                    } else {
                        if (confrontPol == null) {
                            if (confrontAcl.getContainers().iterator().hasNext() && container.equals(confrontAcl.getContainers().iterator().next().getContainer())) {
                                Integer confrontValue = confrontAcl.getPolicyValue();
                                Integer currValue = currAcl.getPolicyValue();
                                if (currValue.equals(confrontValue)) {
                                    found = true;
                                    break;
                                }
                            }
                        }
                    }
                }
                if (!found) {
                    myAcl=copyToNew(currAcl,destType);
                    if(currAcl.getPredifinedPolicy()!=null && newPolicies.containsKey(myAcl.getPredifinedPolicy().getName())){
                        myAcl.setPredifinedPolicy(newPolicies.get(myAcl.getPredifinedPolicy().getName()));
                        aclDAO2.saveOrUpdate(myAcl);
                        for(AclContainer currContainer :myAcl.getContainers()){
                            aclContainerDAO2.saveOrUpdate(currContainer);
                        }
                    }else{
                        aclDAO2.saveOrUpdate(myAcl);
                        for(AclContainer currContainer :myAcl.getContainers()){
                            aclContainerDAO2.saveOrUpdate(currContainer);
                        }
                    }





                    outMessage = "in type " + currType.getTypeId() + " manca acl per container " + container;
                    out.write((outMessage + "\n").getBytes());
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                }
            }
            for (Acl currAcl : destType.getAcls()) {
                boolean found = false;
                String container = "";
                if (currAcl.getContainers().iterator().hasNext())
                    container = currAcl.getContainers().iterator().next().getContainer();
                for (Acl confrontAcl : currType.getAcls()) {
                    PredefinedPolicy predefinedPol = currAcl.getPredifinedPolicy();
                    PredefinedPolicy confrontPol = confrontAcl.getPredifinedPolicy();
                    if (predefinedPol != null) {
                        if (confrontPol != null) {
                            if (predefinedPol.getName().equals(confrontPol.getName()) && container.equals(confrontAcl.getContainers().iterator().next().getContainer())) {
                                found = true;
                                break;
                            }
                        }
                    } else {
                        if (confrontPol == null) {
                            if (confrontAcl.getContainers().iterator().hasNext() && container.equals(confrontAcl.getContainers().iterator().next().getContainer())) {
                                Integer confrontValue = confrontAcl.getPolicyValue();
                                Integer currValue = currAcl.getPolicyValue();
                                if (currValue.equals(confrontValue)) {
                                    found = true;
                                    break;
                                }
                            }
                        }
                    }
                }
                if (!found) {

                    aclDAO2.delete(currAcl);
                    outMessage = "in type " + currType.getTypeId() + " elimino acl per container " + container;
                    out.write((outMessage + "\n").getBytes());
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),outMessage);
                }
            }
        }






    }



   /* public void allineaTemplate(ServletOutputStream out,String typeId) throws Exception {

        String txName = "doc2";
        Long inputId=Long.parseLong(typeId);

        BaseDao<ElementType> docTypeDAO2 = new BaseDao<ElementType>(txManager, txName, ElementType.class);
        BaseDao<MetadataTemplate> mdDAO2 = new BaseDao<MetadataTemplate>(txManager, txName, MetadataTemplate.class);
        BaseDao<MetadataField> mdFieldDAO2 = new BaseDao<MetadataField>(txManager, txName, MetadataField.class);
        BaseDao<PredefinedPolicy> policyDAO2 = new BaseDao<PredefinedPolicy>(txManager, txName, PredefinedPolicy.class);
        BaseDao<Acl> aclDAO2 = new BaseDao<Acl>(txManager, txName, Acl.class);
        BaseDao<AclContainer> aclContainerDAO2 = new BaseDao<AclContainer>(txManager, txName, AclContainer.class);
        BaseDao<ElementTypeAssociatedTemplate> elTypeAssocTemplateDAO2 = new BaseDao<ElementTypeAssociatedTemplate>(txManager, txName, ElementTypeAssociatedTemplate.class);
        BaseDao<ElementTypeAssociatedWorkflow> wfAssocDAO2 = new BaseDao<ElementTypeAssociatedWorkflow>(txManager, txName, ElementTypeAssociatedWorkflow.class);
        BaseDao<TemplateAcl> tplAclDAO2 = new BaseDao<TemplateAcl>(txManager, txName, TemplateAcl.class);
        BaseDao<TemplateAclContainer> tplAclContainerDAO2 = new BaseDao<TemplateAclContainer>(txManager, txName, TemplateAclContainer.class);
        BaseDao<CalendarEntity> calDAO2 = new BaseDao<CalendarEntity>(txManager, txName, CalendarEntity.class);

        List<ElementType> types = getTypes();
        List<MetadataTemplate> templates = getMds();
        List<PredefinedPolicy> policies = getPolicies();
        ElementType type = getElementType(inputId);
        ElementType myType;

        HashMap<ElementType, ElementType> matchedTypes = new HashMap<ElementType, ElementType>();
        HashMap<MetadataTemplate, MetadataTemplate> matchedTemplates = new HashMap<MetadataTemplate, MetadataTemplate>();
        HashMap<PredefinedPolicy, PredefinedPolicy> matchedPolicies = new HashMap<PredefinedPolicy, PredefinedPolicy>();

        HashMap<ElementTypeAssociatedTemplate, ElementTypeAssociatedTemplate> matchedAssociatedTemplates = new HashMap<ElementTypeAssociatedTemplate, ElementTypeAssociatedTemplate>();

        List<ElementType> foundTypes;
        List<MetadataTemplate> foundTemplates;
        List<PredefinedPolicy> foundPolicies;

        HashMap<String, ElementType> newTypes = new HashMap<String, ElementType>();
        HashMap<String, MetadataTemplate> newTemplates = new HashMap<String, MetadataTemplate>();
        HashMap<String, PredefinedPolicy> newPolicies = new HashMap<String, PredefinedPolicy>();


        HashMap<String, TemplateAcl> origTemplateAcls;
        HashMap<String, TemplateAcl> destTemplateAcls;

        String outMessage = "";

        //for (ElementType type : types) {
        if (!type.isDeleted()) {
            it.cineca.siss.axmr3.log.Log.info(getClass(),"Verifico type " + type.getTypeId());
            foundTypes = getElementTypeByTypeId(type.getTypeId(), docTypeDAO2);
            if (foundTypes != null && foundTypes.size() > 0) {
                it.cineca.siss.axmr3.log.Log.info(getClass(),"type " + type.getTypeId() + " ha " + foundTypes.size() + " risultati");
                if (foundTypes.size() == 1) {
                    if (!type.getId().equals(foundTypes.get(0).getId()))
                        it.cineca.siss.axmr3.log.Log.info(getClass(),"type " + type.getTypeId() + " ha  ID differenti ");
                    it.cineca.siss.axmr3.log.Log.info(getClass(),"type " + type.getTypeId() + " ha  " + type.getHashBack() + " e " + foundTypes.get(0).getHashBack());
                    myType = copyToOld(type, foundTypes.get(0));
                    docTypeDAO2.saveOrUpdate(myType);
                    matchedTypes.put(type,myType );
                }
                if (!foundTypes.get(0).equals(type)) {
                    outMessage = "type " + type.getTypeId() + " non è identico";
                    out.write((outMessage + "\n").getBytes());
                    it.cineca.siss.axmr3.log.Log.info(getClass(),outMessage);
                }
            } else {

                outMessage = "type " + type.getTypeId() + " manca";
                out.write((outMessage + "\n").getBytes());
                it.cineca.siss.axmr3.log.Log.info(getClass(),outMessage);
                myType = copyToNew(type);
                docTypeDAO2.saveOrUpdate(myType);
                matchedTypes.put(type, myType);

            }
            newTypes.put(type.getTypeId(), matchedTypes.get(type));
        }
        //}

        for (MetadataTemplate template : templates) {
            it.cineca.siss.axmr3.log.Log.info(getClass(),"Verifico template " + template.getName());
            foundTemplates = getTemplateByName(template.getName(), mdDAO2);
            if (foundTemplates != null && foundTemplates.size() > 0) {
                it.cineca.siss.axmr3.log.Log.info(getClass(),"template " + template.getName() + " ha " + foundTemplates.size() + " risultati");
                if (foundTemplates.size() == 1) {
                    if (!template.getId().equals(foundTemplates.get(0).getId()))
                        it.cineca.siss.axmr3.log.Log.info(getClass(),"template " + template.getName() + " ha  ID differenti ");
                    matchedTemplates.put(template, copyToOld(template, foundTemplates.get(0)));
                }
                if (!foundTemplates.get(0).equals(template)) {
                    outMessage = "template " + template.getName() + " non è identico";
                    out.write((outMessage + "\n").getBytes());
                    it.cineca.siss.axmr3.log.Log.info(getClass(),outMessage);
                }
            } else {
                outMessage = "template " + template.getName() + " manca";
                out.write((outMessage + "\n").getBytes());
                it.cineca.siss.axmr3.log.Log.info(getClass(),outMessage);
                matchedTemplates.put(template, copyToNew(template));
            }
            newTemplates.put(template.getName(), matchedTemplates.get(template));
        }

        for (PredefinedPolicy policy : policies) {
            it.cineca.siss.axmr3.log.Log.info(getClass(),"Verifico policy " + policy.getName());
            foundPolicies = getPolicyByName(policy.getName(), policyDAO2);
            if (foundPolicies != null && foundPolicies.size() > 0) {
                it.cineca.siss.axmr3.log.Log.info(getClass(),"policy " + policy.getName() + " ha " + foundPolicies.size() + " risultati");
                if (foundPolicies.size() == 1) {
                    if (!policy.getId().equals(foundPolicies.get(0).getId()))
                        it.cineca.siss.axmr3.log.Log.info(getClass(),"policy " + policy.getName() + " ha  ID differenti ");
                    matchedPolicies.put(policy, copyToOld(policy, foundPolicies.get(0)));
                }
            } else {
                outMessage = "policy " + policy.getName() + " manca";
                out.write((outMessage + "\n").getBytes());
                it.cineca.siss.axmr3.log.Log.info(getClass(),outMessage);
                matchedPolicies.put(policy, copyToNew(policy));
            }
            newPolicies.put(policy.getName(), matchedPolicies.get(policy));
        }

        for (ElementType currType : matchedTypes.keySet()) {
            ElementType destType = matchedTypes.get(currType);

            HashMap<String, ElementType> children = currType.getAllowedChildrenMap();
            HashMap<String, ElementType> children2 = new HashMap<String, ElementType>();
            HashMap<String, ElementTypeAssociatedTemplate> associatedTemplates = currType.getAssociatedTemplateMap();
            HashMap<String, ElementTypeAssociatedTemplate> associatedTemplates2 = new HashMap<String, ElementTypeAssociatedTemplate>();
            HashMap<String, ElementTypeAssociatedWorkflow> associatedWF = currType.getAssociatedWorkflowMap();
            HashMap<String, ElementTypeAssociatedWorkflow> associatedWF2 = new HashMap<String, ElementTypeAssociatedWorkflow>();


            if (destType.getId() != null) {
                children2 = destType.getAllowedChildrenMap();
                associatedTemplates2 = destType.getAssociatedTemplateMap();
                associatedWF2 = destType.getAssociatedWorkflowMap();
            } else {
                destType.setAllowedChilds(new LinkedList<ElementType>());
                destType.setAssociatedTemplates(new LinkedList<ElementTypeAssociatedTemplate>());
                destType.setAssociatedWorkflows(new LinkedList<ElementTypeAssociatedWorkflow>());
                destType.setAcls(new LinkedList<Acl>());
            }

            for (String childType : children.keySet()) {
                if (!children2.containsKey(childType)) {
                    outMessage = "in type " + currType.getTypeId() + " manca child " + childType;
                    out.write((outMessage + "\n").getBytes());
                    it.cineca.siss.axmr3.log.Log.info(getClass(),outMessage);
                    destType.getAllowedChilds().add(newTypes.get(childType));
                }
            }


            for (String associatedTemplate : associatedTemplates.keySet()) {
                ElementTypeAssociatedTemplate orig = associatedTemplates.get(associatedTemplate);
                if (associatedTemplates2.containsKey(associatedTemplate)) {

                    ElementTypeAssociatedTemplate dest = associatedTemplates.get(associatedTemplate);
                    matchedAssociatedTemplates.put(orig, copyToOld(orig, dest));
                    origTemplateAcls = orig.getTemplateAclsMap();
                    destTemplateAcls = dest.getTemplateAclsMap();
                    if (!origTemplateAcls.isEmpty() && !destTemplateAcls.isEmpty()) {
                        for (String container : origTemplateAcls.keySet()) {
                            if (!destTemplateAcls.containsKey(container)) {
                                outMessage = "in type " + currType.getTypeId() + " il template " + associatedTemplate + " non ha le stesse acl per container " + container;
                                out.write((outMessage + "\n").getBytes());
                                it.cineca.siss.axmr3.log.Log.info(getClass(),outMessage);
                            }
                        }
                        for (String container : destTemplateAcls.keySet()) {
                            if (!origTemplateAcls.containsKey(container)) {
                                outMessage = "in type " + currType.getTypeId() + " il template " + associatedTemplate + " non ha le stesse acl per container " + container;
                                out.write((outMessage + "\n").getBytes());
                                it.cineca.siss.axmr3.log.Log.info(getClass(),outMessage);
                            }
                        }
                    } else if (!origTemplateAcls.isEmpty() || !destTemplateAcls.isEmpty()) {
                        outMessage = "in type " + currType.getTypeId() + " il template " + associatedTemplate + " non ha le stesse acl";
                        out.write((outMessage + "\n").getBytes());
                        it.cineca.siss.axmr3.log.Log.info(getClass(),outMessage);
                    }
                } else {
                    outMessage = "in type " + currType.getTypeId() + " manca template " + associatedTemplate;
                    out.write((outMessage + "\n").getBytes());
                    it.cineca.siss.axmr3.log.Log.info(getClass(),outMessage);
                    matchedAssociatedTemplates.put(orig, copyToNew(orig, newTemplates.get(associatedTemplate)));
                }
            }

            for (String wf : associatedWF.keySet()) {
                if (!associatedWF2.containsKey(wf)) {
                    outMessage = "in type " + currType.getTypeId() + " manca il wf " + wf;
                    out.write((outMessage + "\n").getBytes());
                    it.cineca.siss.axmr3.log.Log.info(getClass(),outMessage);
                }
            }

            for (Acl currAcl : currType.getAcls()) {
                boolean found = false;
                String container = "";
                if (currAcl.getContainers().iterator().hasNext())
                    container = currAcl.getContainers().iterator().next().getContainer();
                for (Acl confrontAcl : destType.getAcls()) {
                    PredefinedPolicy predefinedPol = currAcl.getPredifinedPolicy();
                    PredefinedPolicy confrontPol = confrontAcl.getPredifinedPolicy();
                    if (predefinedPol != null) {
                        if (confrontPol != null) {
                            if (predefinedPol.getName().equals(confrontPol.getName()) && container.equals(confrontAcl.getContainers().iterator().next().getContainer())) {
                                found = true;
                                break;
                            }
                        }
                    } else {
                        if (confrontPol == null) {
                            if (confrontAcl.getContainers().iterator().hasNext() && container.equals(confrontAcl.getContainers().iterator().next().getContainer())) {
                                Integer confrontValue = confrontAcl.getPolicyValue();
                                Integer currValue = currAcl.getPolicyValue();
                                if (currValue.equals(confrontValue)) {
                                    found = true;
                                    break;
                                }
                            }
                        }
                    }
                }
                if (!found) {
                    outMessage = "in type " + currType.getTypeId() + " manca acl per container " + container;
                    out.write((outMessage + "\n").getBytes());
                    it.cineca.siss.axmr3.log.Log.info(getClass(),outMessage);
                }
            }
        }

        for (MetadataTemplate currTemplate : matchedTemplates.keySet()) {
            MetadataTemplate destTemplate = matchedTemplates.get(currTemplate);
            try {
                HashMap<String, MetadataField> fields = currTemplate.getFieldsMap();
                HashMap<String, MetadataField> confrontFields = destTemplate.getFieldsMap();
                for (String field : fields.keySet()) {
                    if (!confrontFields.containsKey(field)) {
                        outMessage = "in template " + currTemplate.getName() + " manca field " + field;
                        out.write((outMessage + "\n").getBytes());
                        it.cineca.siss.axmr3.log.Log.info(getClass(),outMessage);
                    } else {
                        if (!confrontFields.get(field).equals(fields.get(field))) {
                            outMessage = "in template " + currTemplate.getName() + " field " + field + " non è identico";
                            out.write((outMessage + "\n").getBytes());
                            it.cineca.siss.axmr3.log.Log.info(getClass(),outMessage);
                        }
                    }
                }
            } catch (Exception ex) {
                outMessage = "in template " + currTemplate.getName() + " non e' riuscito il controllo dei field";
                out.write((outMessage + "\n").getBytes());
                it.cineca.siss.axmr3.log.Log.info(getClass(),outMessage);
            }
        }


    }*/

    protected MetadataField copyToNew(MetadataField from,  MetadataTemplate newTemplate) {
        MetadataField to = clone(MetadataField.class, from);
        to.setId(null);
        to.setTemplate(newTemplate);
        return to;
    }

    protected MetadataField copyToOld(MetadataField from, MetadataField old) {
        MetadataField to = clone(MetadataField.class, from);
        to.setId(old.getId());
        to.setTemplate(old.getTemplate());
        //return to;
        return to;
    }

    protected ElementTypeAssociatedWorkflow copyToNew(ElementTypeAssociatedWorkflow from,  ElementType newType) {
        ElementTypeAssociatedWorkflow to = clone(ElementTypeAssociatedWorkflow.class, from);
        to.setId(null);
        to.setType(newType);
        return to;
    }

    protected ElementTypeAssociatedWorkflow copyToOld(ElementTypeAssociatedWorkflow from, ElementTypeAssociatedWorkflow old) {
        ElementTypeAssociatedWorkflow to = clone(ElementTypeAssociatedWorkflow.class, from);
        to.setId(old.getId());
        to.setType(old.getType());
        //return to;
        return to;
    }


    protected ElementTypeAssociatedTemplate copyToNew(ElementTypeAssociatedTemplate from, MetadataTemplate newObj, ElementType newType) {
        ElementTypeAssociatedTemplate to = clone(ElementTypeAssociatedTemplate.class, from);
        to.setId(null);
        to.setMetadataTemplate(newObj);
        to.setType(newType);

        LinkedList<TemplateAcl> newAcls = new LinkedList<TemplateAcl>();
        for(TemplateAcl origAcl:from.getTemplateAcls()){
            newAcls.add(copyToNew(origAcl,to));
        }
        to.setTemplateAcls(newAcls);
        return to;
    }
    /*protected TemplateAcl copyToNew(TemplateAcl from) {
        TemplateAcl to = clone(TemplateAcl.class, from);
        to.setId(null);
        to.setContainers(newObj);
        to.setType(newType);
        to.setTemplateAcls(new LinkedList<TemplateAcl>());
        return to;
    }*/

    protected ElementTypeAssociatedTemplate copyToOld(ElementTypeAssociatedTemplate from, ElementTypeAssociatedTemplate old) {
        ElementTypeAssociatedTemplate to = clone(ElementTypeAssociatedTemplate.class, from);
        to.setId(old.getId());
        to.setMetadataTemplate(old.getMetadataTemplate());
        to.setTemplateAcls(old.getTemplateAcls());
        to.setType(old.getType());
        //return to;
        return to;
    }

    protected PredefinedPolicy copyToNew(PredefinedPolicy from) {
        PredefinedPolicy to = clone(PredefinedPolicy.class, from);
        to.setId(null);
        return to;
    }

    protected PredefinedPolicy copyToOld(PredefinedPolicy from, PredefinedPolicy old) {
        PredefinedPolicy to = clone(PredefinedPolicy.class, from);
        to.setId(old.getId());
        //return to;
        return to;
    }

    protected Acl copyToNew(Acl from, ElementType currType) {
        Acl to = clone(Acl.class, from);
        to.setId(null);
        Collection<AclContainer> oldContainers = from.getContainers();
        to.setContainers(new LinkedList<AclContainer>());
        to.setType(currType);
        for(AclContainer currContainer:oldContainers){
            AclContainer newContainer = new AclContainer();
            newContainer.setAcl(to);
            newContainer.setAuthority(currContainer.isAuthority());
            newContainer.setContainer(currContainer.getContainer());
            to.getContainers().add(newContainer);
        }
        return to;
    }

    protected Acl copyToOld(Acl from, Acl old) {
        Acl to = clone(Acl.class, from);
        to.setId(old.getId());
        to.setType(old.getType());
        to.setContainers(old.getContainers());
        to.setPredifinedPolicy(old.getPredifinedPolicy());

        //return to;
        return to;
    }

    protected ElementType copyToNew(ElementType from) {
        ElementType to = clone(ElementType.class, from);
        to.setId(null);
        to.setTitleField(null);
        return to;
    }

    protected ElementType copyToOld(ElementType from, ElementType old) {
        ElementType to = clone(ElementType.class, from);
        to.setId(old.getId());
        to.setAcls(old.getAcls());
        to.setAllowedChilds(old.getAllowedChilds());
        to.setAssociatedTemplates(old.getAssociatedTemplates());
        to.setAssociatedWorkflows(old.getAssociatedWorkflows());
        to.setTitleField(old.getTitleField());

        //return to;
        return to;
    }

    private TemplateAcl copyToNew(TemplateAcl from, ElementTypeAssociatedTemplate newAssociated) {
        TemplateAcl to = clone(TemplateAcl.class, from);
        to.setId(null);
        to.setElementTypeAssociatedTemplate(newAssociated);
        LinkedList<TemplateAclContainer> newContainers = new LinkedList<TemplateAclContainer>();
        for(TemplateAclContainer container:from.getContainers()){
            newContainers.add(copyToNew(container,to));
        }
        to.setContainers(newContainers);
        return to;
    }

    private TemplateAclContainer copyToNew(TemplateAclContainer from, TemplateAcl newTemplate) {
        TemplateAclContainer to = clone(TemplateAclContainer.class, from);
        to.setId(null);
        to.setAcl(newTemplate);
        return to;
    }

    private TemplateAcl copyToOld(TemplateAcl from,TemplateAcl old) {
        TemplateAcl to = clone(TemplateAcl.class, from);
        to.setId(old.getId());
        to.setContainers(old.getContainers());
        to.setElementTemplate(old.getElementTemplate());
        to.setElementTypeAssociatedTemplate(old.getElementTypeAssociatedTemplate());

        //return to;
        return to;
    }

    protected MetadataTemplate copyToNew(MetadataTemplate from) {
        MetadataTemplate to = clone(MetadataTemplate.class, from);
        to.setId(null);
        return to;
    }

    protected MetadataTemplate copyToOld(MetadataTemplate from, MetadataTemplate old) {
        MetadataTemplate to = clone(MetadataTemplate.class, from);
        to.setId(old.getId());
        to.setEndDateField(old.getEndDateField());
        to.setStartDateField(old.getStartDateField());
        to.setFields(old.getFields());

        //return to;
        return to;
    }

    public ElementType saveElementType(String typeId, boolean isContainer, boolean hasFile, boolean selfRecursive, boolean rootAble, boolean checkOutEnabled, byte[] img, Long id, String templateRow, String templateDetail, Long titleField, boolean draftable, boolean searchable, String titleRegex, boolean noFileinfo) throws RestException {
        return saveElementType(typeId, isContainer, hasFile, selfRecursive, rootAble, checkOutEnabled, img, id, templateRow, templateDetail, "", titleField, draftable, searchable, titleRegex, noFileinfo, "", new Long(0), false, false);
    }

    public ElementType saveElementType(String typeId, boolean isContainer, boolean hasFile, boolean selfRecursive, boolean rootAble, boolean checkOutEnabled, byte[] img, Long id, String templateRow, String templateDetail, String templateForm, Long titleField, boolean draftable, boolean searchable, String titleRegex, boolean noFileinfo, String hashBack, Long groupUpLevel, boolean sortable, boolean fileOnFS) throws RestException {
        ElementType el = new ElementType();
        if (id != null) el = docTypeDAO.getById(id);
        el.setTypeId(typeId);
        el.setContainer(isContainer);
        el.setHasFileAttached(hasFile);
        el.setSelfRecursive(selfRecursive);
        el.setRootAble(rootAble);
        el.setCheckOutEnabled(checkOutEnabled);
        el.setFtlDetailTemplate(templateDetail);
        el.setFtlFormTemplate(templateForm);
        el.setFtlRowTemplate(templateRow);
        el.setDraftable(draftable);
        el.setTitleRegex(titleRegex);
        el.setSearchable(searchable);
        el.setNoFileinfo(noFileinfo);
        el.setHashBack(hashBack);
        el.setGroupUpLevel(groupUpLevel);
        el.setSortable(true);
        el.setFileOnFS(fileOnFS);
        it.cineca.siss.axmr3.log.Log.debug(getClass(),titleField);
        if (titleField != null) el.setTitleField(getField(titleField));
        else el.setTitleField(null);
        if (img != null && img.length > 0)
            el.setImg(img);
        try {
            docTypeDAO.saveOrUpdate(el);
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(),el);
        return el;
    }

    public ElementType getElementType(Long id) {
        return docTypeDAO.getById(id);
    }

    public List<ElementType> getTypes() {
        Criteria c = docTypeDAO.getCriteria();
        c.add(Restrictions.eq("deleted", false));
        c.addOrder(Order.asc("typeId").ignoreCase());
        return c.list();
    }

    public MetadataTemplate saveMD() {
        return null;
    }

    public MetadataTemplate getMd(Long id) {
        return mdDAO.getById(id);
    }

    public List<MetadataTemplate> getMds() {
        Criteria c = mdDAO.getCriteria();
        c.add(Restrictions.eq("deleted", false));
        c.addOrder(Order.asc("name").ignoreCase());
        return c.list();
    }

    public Collection<MetadataTemplate> getTypeTemplate(ElementType et) {
        return et.getEnabledTemplates();
    }

    public MetadataField saveField() {
        return null;
    }

    public MetadataField getField(Long id) {
        return mdFieldDAO.getById(id);
    }

    public Collection<MetadataField> getTemplateFields(MetadataTemplate t) {
        return t.getFields();
    }

    public void deleteType(Long id) throws RestException {
        ElementType el = getElementType(id);
        try {
            el.setDeleted(true);
            docTypeDAO.saveOrUpdate(el);
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        }
    }

    public MetadataTemplate saveTemplate(String name, String desc, boolean auditable, boolean wfManaged, boolean calendarized, String calendarName, String calendarColor, Long startDateId, Long endDateId, Long id) throws RestException {
        MetadataTemplate t = null;
        if (id != null) t = mdDAO.getById(id);
        else t = new MetadataTemplate();
        t.setDeleted(false);
        t.setName(name);
        t.setDescription(desc);
        t.setAuditable(auditable);
        t.setCalendarized(calendarized);
        t.setCalendarName(calendarName);
        t.setCalendarColor(calendarColor);
        if (startDateId != null) t.setStartDateField(getField(startDateId));
        if (endDateId != null) t.setEndDateField(getField(endDateId));
        try {
            mdDAO.saveOrUpdate(t);
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        }
        return t;
    }

    public void deleteTemplate(Long id) throws RestException {
        MetadataTemplate t = getMd(id);
        t.setDeleted(true);
        if (t.getFields() != null && t.getFields().size() > 0)
            for (MetadataField f : t.getFields()) {
                try {
                    f.setDeleted(true);
                    mdFieldDAO.saveOrUpdate(f);
                } catch (AxmrGenericException e) {
                    throw new RestException(e.getMessage(), txManager);
                }
            }

        try {
            mdDAO.saveOrUpdate(t);
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        }
    }



    public void addField(MetadataTemplate md, String name, String type, boolean mandatory, String typefilters, String availableValues, String externalDictionary, String addFilterFields, Long idField, Integer size, String macro, String macroView, String baseOraName, String regexpCheck) throws RestException {
        MetadataField f = null;
        boolean isNew = true;
        if (md.getFields() == null) md.setFields(new LinkedList<MetadataField>());
        int pos = md.getFields().size();
        if (idField != null) {
            for (MetadataField f1 : md.getFields()) {
                if (f1.getId().equals(idField)) {
                    f = f1;
                    isNew = false;
                }
            }
        }
        if (f == null) f = new MetadataField();
        if (isNew) f.setPosition(pos);
        f.setName(name);
        Log.debug(getClass(),"il tipo di field è -"+type+"-");
        MetadataFieldType t = MetadataFieldType.TEXTBOX;
        if (type.equals("TEXTBOX")) t = MetadataFieldType.TEXTBOX;
        if (type.equals("TEXTAREA")) t = MetadataFieldType.TEXTAREA;
        if (type.equals("DATE")) t = MetadataFieldType.DATE;
        if (type.equals("SELECT")) t = MetadataFieldType.SELECT;
        if (type.equals("RADIO")) t = MetadataFieldType.RADIO;
        if (type.equals("CHECKBOX")) t = MetadataFieldType.CHECKBOX;
        if (type.equals("EXT_DICTIONARY")) t = MetadataFieldType.EXT_DICTIONARY;
        if (type.equals("PLACE_HOLDER")) {
            t = MetadataFieldType.PLACE_HOLDER;
            f.setTypefilters(typefilters);
        }
        if (type.equals("ELEMENT_LINK")) {
            Log.debug(getClass(),"riconosco che è "+type);
            t = MetadataFieldType.ELEMENT_LINK;
            f.setTypefilters(typefilters);
        }
        Log.debug(getClass(),"Tipo interno -"+t+"-");
        f.setExternalDictionary(externalDictionary);
        Log.debug(getClass(),"External dictionary SET");
        f.setAddFilterFields(addFilterFields);
        Log.debug(getClass(),"Filter Fields SET");
        f.setType(t);
        Log.debug(getClass(),"Type SET");
        f.setAvailableValues(availableValues);
        Log.debug(getClass(),"Available Values SET");
        f.setMandatory(mandatory);
        Log.debug(getClass(),"Mandatory SET");
        f.setSize(size);
        Log.debug(getClass(),"Size SET");
        f.setMacro(macro);
        Log.debug(getClass(),"Macro SET");
        f.setMacroView(macroView);
        Log.debug(getClass(),"Macro View SET");
        f.setTemplate(md);
        Log.debug(getClass(),"Template SET");
        f.setBaseNameOra(baseOraName);
        Log.debug(getClass(),"Base Name SET");
        f.setCascadeDelete(false);
        Log.debug(getClass(),"Cascade Delete SET");
        if ( regexpCheck==null || regexpCheck.isEmpty() ){
            f.setRegexpCheck(null);
            Log.debug(getClass(),"RegExp SET NULL");
        }else {
            f.setRegexpCheck(regexpCheck);
            Log.debug(getClass(),"RegExp SET EXPR");
        }
        Log.debug(getClass(),"Pre try");
        try {
            Log.debug(getClass(),"Tento il salvataggio del campo");
            mdFieldDAO.saveOrUpdate(f);
            Log.debug(getClass(),"Salvataggio campo OK");
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        }
        if (isNew) {
            if (md.getFields() == null) md.setFields(new LinkedList<MetadataField>());
            md.getFields().add(f);
            try {
                Log.debug(getClass(),"Tento il salvataggio del metadata template");
                mdDAO.saveOrUpdate(md);
                Log.debug(getClass(),"Salvataggio template OK");
            } catch (AxmrGenericException e) {
                throw new RestException(e.getMessage(), txManager);
            }
        }

    }

    public void deleteField(MetadataTemplate t, Long idField) throws RestException {
        MetadataField f = null;
        for (MetadataField f1 : t.getFields()) {
            if (f1.getId().equals(idField)) {
                f = f1;
            }
        }
        if (f!=null){
            try {
                f.setDeleted(true);
                mdFieldDAO.saveOrUpdate(f);
            } catch (AxmrGenericException e) {
                throw new RestException(e.getMessage(), txManager);
            }
        }
    }

    public void assocTemplate(ElementType elementType, Long templateId, boolean enabled) throws RestException {
        ElementTypeAssociatedTemplate t = null;
        if (elementType.getAssociatedTemplates() == null)
            elementType.setAssociatedTemplates(new LinkedList<ElementTypeAssociatedTemplate>());
        for (ElementTypeAssociatedTemplate t1 : elementType.getAssociatedTemplates()) {
            if (t1.getMetadataTemplate().getId().equals(templateId)) t = t1;
        }
        if (t == null) {
            t = new ElementTypeAssociatedTemplate();
            t.setEnabled(enabled);
            t.setMetadataTemplate(mdDAO.getById(templateId));
            t.setType(elementType);
            try {
                elTypeAssocTemplateDAO.save(t);
            } catch (AxmrGenericException e) {
                throw new RestException(e.getMessage(), txManager);
            }
            elementType.getAssociatedTemplates().add(t);
            try {
                docTypeDAO.saveOrUpdate(elementType);
            } catch (AxmrGenericException e) {
                throw new RestException(e.getMessage(), txManager);
            }
        } else {
            t.setEnabled(enabled);
            try {
                elTypeAssocTemplateDAO.saveOrUpdate(t);
            } catch (AxmrGenericException e) {
                throw new RestException(e.getMessage(), txManager);
            }
        }


    }

    public void deAssocTemplate(ElementType elementType, Long assocId) throws RestException {

        for (ElementTypeAssociatedTemplate t1 : elementType.getAssociatedTemplates()) {
            if (t1.getId().equals(assocId)) {
                try {
                    elTypeAssocTemplateDAO.delete(t1);
                } catch (AxmrGenericException e) {
                    throw new RestException(e.getMessage(), txManager);
                }
            }
        }
    }

    public void addChild(ElementType elementType, Long elementId) throws RestException {
        if (elementType.getAllowedChilds() == null) elementType.setAllowedChilds(new LinkedList<ElementType>());
        ElementType t = null;
        for (ElementType t1 : elementType.getAllowedChilds()) {
            if (t1.getId().equals(elementId)) t = t1;
        }
        if (t == null) {
            t = docTypeDAO.getById(elementId);
            elementType.getAllowedChilds().add(t);
            try {
                docTypeDAO.saveOrUpdate(elementType);
            } catch (AxmrGenericException e) {
                throw new RestException(e.getMessage(), txManager);
            }
        }
    }

    public void deleteChild(ElementType elementType, Long elementId) throws RestException {
        if (elementType.getAllowedChilds() == null) elementType.setAllowedChilds(new LinkedList<ElementType>());
        ElementType t = null;
        for (ElementType t1 : elementType.getAllowedChilds()) {
            if (t1.getId().equals(elementId)) t = t1;
        }
        if (t != null) {
            elementType.getAllowedChilds().remove(t);
            try {
                docTypeDAO.saveOrUpdate(elementType);
            } catch (AxmrGenericException e) {
                throw new RestException(e.getMessage(), txManager);
            }
        }
    }

    public PredefinedPolicy getPolicy(Long id) {
        return policyDAO.getById(id);
    }

    public List<PredefinedPolicy> getPolicies() {
        Criteria c = policyDAO.getCriteria();
        c.addOrder(Order.asc("name").ignoreCase());
        return c.list();
    }

    public PredefinedPolicy savePolicy(String name, String desc, boolean view, boolean create, boolean update, boolean addComment, boolean moderate, boolean delete, boolean changePermission, boolean addChild, boolean removeCheckOut, boolean launchProcess, boolean enableTemplate, boolean canBrowse, Long id) throws RestException {
        PredefinedPolicy p = null;
        if (id != null) p = policyDAO.getById(id);
        else p = new PredefinedPolicy();
        p.setName(name);
        p.setDescription(desc);
        Policy pol = new Policy();
        pol.setCanView(view);
        pol.setCanCreate(create);
        pol.setCanUpdate(update);
        pol.setCanAddComment(addComment);
        pol.setCanModerate(moderate);
        pol.setCanDelete(delete);
        pol.setCanChangePermission(changePermission);
        pol.setCanAddChild(addChild);
        pol.setCanRemoveCheckOut(removeCheckOut);
        pol.setCanLaunchProcess(launchProcess);
        pol.setCanEnableTemplate(enableTemplate);
        pol.setCanBrowse(canBrowse);
        p.setPolicyValue(pol.toInt());
        it.cineca.siss.axmr3.log.Log.debug(getClass(),pol);
        try {
            policyDAO.saveOrUpdate(p);
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        }
        return p;
    }

    public void deletePolicy(Long id) throws RestException {
        try {
            policyDAO.delete(policyDAO.getById(id));
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        }
    }

    public Acl getAcl(Long typeId, Long aclId) {
        ElementType t = docTypeDAO.getById(typeId);
        Acl ret = null;
        if (t.getAcls() != null) {
            for (Acl a : t.getAcls()) {
                if (a.getId() == aclId) ret = a;
            }
        }
        return ret;
    }

    public void saveAcl(Long typeId, List<String> groups, List<String> users, Policy pol, PredefinedPolicy pp, String detailTemplate, String templateRef, Long id) throws RestException {
        try {

            if (id == null) {
                Acl acl = new Acl();
                acl.setContainers(new LinkedList<AclContainer>());
                acl.setPolicyValue(pol.toInt());
                acl.setDetailTemplate(detailTemplate);
                aclDAO.save(acl);
                if (groups != null && groups.size() > 0) for (String group : groups) {
                    AclContainer c = new AclContainer();
                    c.setContainer(group);
                    c.setAuthority(true);
                    c.setAcl(acl);
                    aclContainerDAO.saveOrUpdate(c);
                    acl.getContainers().add(c);
                }
                if (users != null && users.size() > 0) for (String user : users) {
                    AclContainer c = new AclContainer();
                    c.setContainer(user);
                    c.setAuthority(false);
                    c.setAcl(acl);
                    aclContainerDAO.saveOrUpdate(c);
                    acl.getContainers().add(c);
                }
                if (templateRef != null) {
                    AclContainer c = new AclContainer();
                    c.setContainer(templateRef);
                    c.setAuthority(true);
                    c.setAcl(acl);
                    aclContainerDAO.saveOrUpdate(c);
                    acl.getContainers().add(c);
                }
                if (pp != null) {
                    acl.setPredifinedPolicy(pp);
                }

                ElementType el = docTypeDAO.getById(typeId);
                acl.setType(el);
                try {
                    aclDAO.saveOrUpdate(acl);
                } catch (AxmrGenericException e) {
                    throw new RestException(e.getMessage(), txManager);
                }
            } else {
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Modifica permessi n.ro " + id);
                Acl acl = aclDAO.getById(id);
                for (AclContainer c : acl.getContainers()) {
                    aclContainerDAO.delete(c);
                }
                aclDAO.saveOrUpdate(acl);
                acl.setContainers(new LinkedList<AclContainer>());
                if (groups != null && groups.size() > 0) for (String group : groups) {
                    AclContainer c = new AclContainer();
                    c.setContainer(group);
                    c.setAuthority(true);
                    c.setAcl(acl);
                    aclContainerDAO.saveOrUpdate(c);
                    acl.getContainers().add(c);
                }
                if (users != null && users.size() > 0) for (String user : users) {
                    AclContainer c = new AclContainer();
                    c.setContainer(user);
                    c.setAuthority(false);
                    c.setAcl(acl);
                    aclContainerDAO.saveOrUpdate(c);
                    acl.getContainers().add(c);
                }
                if (templateRef != null) {
                    AclContainer c = new AclContainer();
                    c.setContainer(templateRef);
                    c.setAuthority(true);
                    c.setAcl(acl);
                    aclContainerDAO.saveOrUpdate(c);
                    acl.getContainers().add(c);
                }
                if (pp != null) {
                    acl.setPredifinedPolicy(pp);
                } else {
                    acl.setPredifinedPolicy(null);
                }
                acl.setPolicyValue(pol.toInt());
                ElementType el = docTypeDAO.getById(typeId);
                acl.setType(el);
                aclDAO.saveOrUpdate(acl);
            }
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        }
    }

    public void deleteAcl(Long typeId, Long id) throws RestException {
        Acl acl = aclDAO.getById(id);
        if (acl.getContainers() != null) {
            for (AclContainer c : acl.getContainers()) {
                try {
                    aclContainerDAO.delete(c);
                    aclContainerDAO.getSession().flush();
                } catch (AxmrGenericException e) {
                    throw new RestException(e.getMessage(), txManager);
                }
            }
        }
        try {
            aclDAO.delete(acl);
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        }
    }

    public void assocWorkflow(ElementType el, String wfId, boolean enabled, boolean bStartOnCreate, boolean bStartOnUpdate, boolean bStartOnDelete) throws RestException {
        if (el.getAssociatedWorkflows() == null)
            el.setAssociatedWorkflows(new LinkedList<ElementTypeAssociatedWorkflow>());
        ElementTypeAssociatedWorkflow assoc = new ElementTypeAssociatedWorkflow();
        assoc.setEnabled(enabled);
        assoc.setProcessKey(wfId);
        assoc.setStartOnCreate(bStartOnCreate);
        assoc.setStartOnUpdate(bStartOnUpdate);
        assoc.setStartOnDelete(bStartOnDelete);
        assoc.setType(el);
        try {
            wfAssocDAO.save(assoc);
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        }
        el.getAssociatedWorkflows().add(assoc);
        try {
            docTypeDAO.saveOrUpdate(el);
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        }
    }


    public void deAssocWorkflows(ElementType t, Long idAssoc) throws RestException {
        ElementTypeAssociatedWorkflow assoc = null;
        for (ElementTypeAssociatedWorkflow a : t.getAssociatedWorkflows()) {
            if (a.getId().equals(idAssoc)) assoc = a;
        }
        //t.getAssociatedWorkflows().remove(assoc);
        try {
            wfAssocDAO.delete(assoc);
            //    docTypeDAO.saveOrUpdate(t);
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        }
    }

    public static <T> T clone(Class<T> clazz, T dtls) {
        T clonedObject = (T) SerializationHelper.clone((Serializable) dtls);
        return clonedObject;
    }

    public List<ElementType> getElementTypeByTypeId(String typeId) {
        return getElementTypeByTypeId(typeId, docTypeDAO);
    }

    public List<ElementType> getElementTypeByTypeId(String typeId, BaseDao<ElementType> dao) {
        Criteria c = dao.getCriteria();
        c.add(Restrictions.eq("typeId", typeId));
        return c.list();

    }

    public List<MetadataTemplate> searchTemplate(String term) {
        Criteria c = mdDAO.getCriteria();
        c.add(Restrictions.like("name", "%" + term + "%").ignoreCase());
        return c.list();
    }

    public List<MetadataTemplate> getTemplateByName(String name, BaseDao<MetadataTemplate> dao) {
        Criteria c = dao.getCriteria();
        c.add(Restrictions.eq("name", name));
        return c.list();
    }

    public List<MetadataTemplate> getTemplateByName(String name) {
        return getTemplateByName(name, mdDAO);
    }


    public List<PredefinedPolicy> getPolicyByName(String name, BaseDao<PredefinedPolicy> dao) {
        Criteria c = dao.getCriteria();
        c.add(Restrictions.eq("name", name));
        return c.list();
    }

    public List<PredefinedPolicy> getPolicyByName(String name) {
        return getPolicyByName(name, policyDAO);
    }


    public List<MetadataField> searchTemplateField(String term) {
        Criteria c = mdFieldDAO.getCriteria();
        c.add(Restrictions.like("name", "%" + term + "%").ignoreCase());
        List<MetadataField> fields = c.list();
        List<MetadataTemplate> ts = searchTemplate(term);
        if (ts != null && ts.size() > 0) {
            for (MetadataTemplate t : ts) {
                if (fields == null) fields = new LinkedList<MetadataField>();
                for (MetadataField f : t.getFields()) {
                    if (!fields.contains(f)) fields.add(f);
                }
            }
        }
        return fields;

    }

    public List<ElementType> searchElementType(String term) {
        Criteria c = docTypeDAO.getCriteria();
        c.add(Restrictions.like("typeId", "%" + term + "%").ignoreCase());
        return c.list();

    }

    public List<ElementType> getRootBrowsableElementTypes(IUser user) {
        Criteria c = docTypeDAO.getCriteria();
        Policy pCheck = new Policy();
        pCheck.setCanBrowse(true);
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"Policy to check:" + pCheck.toLikeClause());
        c.createAlias("acls", "acls")
                .createAlias("acls.containers", "aclContainers")
                .add(Restrictions.eq("rootAble", true))
                .add(Restrictions.eq("deleted", false))
                .setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY)
                .add(pCheck.checkCriterion("acls", "aclContainers", user));
        return c.list();
    }

    public boolean isAvailablesCalendars(IUser user) {
        Criteria ct = mdDAO.getCriteria();
        ct.add(Restrictions.eq("calendarized", true));
        if (ct.list().size() > 0) return true;
        else return false;
    }


    public void moveFieldUp(MetadataTemplate md, Long idField) throws RestException {
        try {
            int origPosition = 0;
            for (MetadataField f : md.getFields()) {
                if (f.getId().equals(idField)) {
                    origPosition = f.getPosition();
                }
            }
            int newPosition = origPosition - 1;
            for (MetadataField f : md.getFields()) {
                if (f.getPosition() >= newPosition && f.getPosition() < origPosition) {
                    f.setPosition(f.getPosition() + 1);
                    mdFieldDAO.saveOrUpdate(f);
                }
                if (f.getId().equals(idField)) {
                    f.setPosition(newPosition);

                    mdFieldDAO.saveOrUpdate(f);

                }
            }
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        }

    }

    public void moveFieldDown(MetadataTemplate md, Long idField) throws RestException {
        try {
            int origPosition = 0;
            for (MetadataField f : md.getFields()) {
                if (f.getId().equals(idField)) {
                    origPosition = f.getPosition();
                }
            }
            int newPosition = origPosition + 1;
            for (MetadataField f : md.getFields()) {
                if (f.getPosition() > origPosition && f.getPosition() <= newPosition) {
                    f.setPosition(f.getPosition() - 1);
                    mdFieldDAO.saveOrUpdate(f);
                }
                if (f.getId().equals(idField)) {
                    f.setPosition(newPosition);

                    mdFieldDAO.saveOrUpdate(f);

                }
            }
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        }
    }

    public void moveFieldTop(MetadataTemplate md, Long idField) throws RestException {
        try {
            int origPosition = 0;
            for (MetadataField f : md.getFields()) {
                if (f.getId().equals(idField)) {
                    origPosition = f.getPosition();
                }
            }
            int newPosition = 0;
            for (MetadataField f : md.getFields()) {
                if (f.getPosition() >= newPosition && f.getPosition() < origPosition) {
                    f.setPosition(f.getPosition() + 1);
                    mdFieldDAO.saveOrUpdate(f);
                }
                if (f.getId().equals(idField)) {
                    f.setPosition(newPosition);

                    mdFieldDAO.saveOrUpdate(f);

                }
            }
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        }
    }

    public void moveFieldBottom(MetadataTemplate md, Long idField) throws RestException {
        try {
            int origPosition = 0;
            for (MetadataField f : md.getFields()) {
                if (f.getId().equals(idField)) {
                    origPosition = f.getPosition();
                }
            }
            int newPosition = md.getFields().size() - 1;
            for (MetadataField f : md.getFields()) {
                if (f.getPosition() > origPosition && f.getPosition() <= newPosition) {
                    f.setPosition(f.getPosition() - 1);
                    mdFieldDAO.saveOrUpdate(f);
                }
                if (f.getId().equals(idField)) {
                    f.setPosition(newPosition);

                    mdFieldDAO.saveOrUpdate(f);

                }
            }
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        }
    }

    public void setDocTypeTemplateAcl(Long id, Long assocId, TemplatePolicy pol, List<String> users, List<String> groups) throws RestException {
        try {
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Carico l'associazione " + assocId);
            TemplateAcl acl = new TemplateAcl();
            ElementTypeAssociatedTemplate assocTemplate = elTypeAssocTemplateDAO.getById(assocId);
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Applico i permessi al template:" + assocTemplate.getMetadataTemplate().getName());
            acl.setElementTypeAssociatedTemplate(assocTemplate);
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
        } catch (Exception ex) {
            throw new RestException(ex.getMessage(), txManager);
        }
    }

    public void deleteTemplateAcl(Long id, Long assocId, Long aclId) throws RestException {
        try {
            ElementType t = getElementType(id);
            TemplateAcl a = null;
            ElementTypeAssociatedTemplate et = null;
            for (ElementTypeAssociatedTemplate tpl : t.getAssociatedTemplates()) {
                if (tpl.getId().equals(assocId)) {
                    for (TemplateAcl acl : tpl.getTemplateAcls()) {
                        if (acl.getId().equals(aclId)) {
                            a = acl;
                            et = tpl;
                        }
                    }
                }
            }
            if (a != null) {
                for (TemplateAclContainer c : a.getContainers()) {
                    tplAclContainerDAO.delete(c);
                }
                et.getTemplateAcls().remove(a);
                tplAclDAO.delete(a);
                elTypeAssocTemplateDAO.saveOrUpdate(et);
            }
        } catch (AxmrGenericException ex) {
            throw new RestException(ex.getMessage(), txManager);
        }
    }

    public CalendarEntity getCalendar(Long id) {
        return calDAO.getById(id);

    }

    public List<CalendarEntity> getCalendars() {
        Criteria c = calDAO.getCriteria();
        return c.list();
    }

    public CalendarEntity saveCalendar(String name, String titleRegex, String backgroundColor, Long elementId, Long startField, Long endField, Long id) throws RestException {
        try {
            CalendarEntity c = null;
            if (id != null) c = calDAO.getById(id);
            if (c == null) c = new CalendarEntity();
            c.setBackgroundColor(backgroundColor);
            c.setTitleRegex(titleRegex);
            c.setName(name);
            c.setElementType(docTypeDAO.getById(elementId));
            c.setStartDateField(mdFieldDAO.getById(startField));
            if (endField == null) c.setEndDateField(null);
            else c.setEndDateField(mdFieldDAO.getById(endField));
            calDAO.saveOrUpdate(c);
            return c;
        } catch (Exception ex) {
            throw new RestException(ex.getMessage(), txManager);
        }

    }

    public void deleteCalendar(Long id) throws RestException {
        try {
            calDAO.delete(calDAO.getById(id));
        } catch (AxmrGenericException e) {
            throw new RestException(e.getMessage(), txManager);
        }
    }

    /*gestione importazione configurazione

     */

    public ElementType igetElementTypeByTypeId(String typeId) {
        Criteria c = docTypeDAO.getCriteria();
        c.add(Restrictions.eq("typeId", typeId).ignoreCase());
        return (ElementType) c.uniqueResult();
    }

    public MetadataTemplate igetTemplateByName(String name) {
        Criteria c = mdDAO.getCriteria();
        c.add(Restrictions.eq("name", name).ignoreCase());
        return (MetadataTemplate) c.uniqueResult();
    }

    public MetadataField igetFieldTypeByNames(String templateName, String fieldName) {
        Criteria c = mdFieldDAO.getCriteria();
        c.add(Restrictions.eq("name", fieldName).ignoreCase());
        c.add(Restrictions.eq("template.name", templateName).ignoreCase());
        return (MetadataField) c.uniqueResult();
    }

    public PredefinedPolicy igetPolicyByName(String name) {
        Criteria c = policyDAO.getCriteria();
        c.add(Restrictions.eq("name", name).ignoreCase());
        return (PredefinedPolicy) c.uniqueResult();
    }

    public CalendarEntity igetCalendarByName(String name) {
        Criteria c = calDAO.getCriteria();
        c.add(Restrictions.eq("name", name).ignoreCase());
        return (CalendarEntity) c.uniqueResult();
    }

    public ProcessDefinition igetProcessDefinitionByKey(String pkey) {
        ProcessDefinition bpmn = getProcessEngine().getRepositoryService().createProcessDefinitionQuery().processDefinitionKey(pkey).active().latestVersion().singleResult();
        return bpmn;
    }

    public HashMap<String,Object> getProcessDefinitionAndChecksum(String key) throws RestException {
        ProcessDefinition bpmn = igetProcessDefinitionByKey(key);
        return getProcessDefinitionAndChecksum(bpmn.getKey(),bpmn.getId());
    }
    public HashMap<String,Object> getProcessDefinitionAndChecksum(String key, String id) throws RestException {

        InputStream model = getProcessEngine().getRepositoryService().getProcessModel(id);
        HashMap<String, Object> ret=new HashMap<String, Object>();
        try {
            byte[] bytes = IOUtils.toByteArray(model);
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            byte[] bytes64 = Base64.encodeBase64(bytes);
            String checksum=new String(Base64.encodeBase64(digest.digest(bytes)));
            String content = new String(bytes64);
            ret.put("checksum", checksum);
            ret.put("content", content);
            return ret;
        } catch (Exception e) {
            throw new RestException("BPM EXPORT", 1);
        }
    }

    public HashMap<String, Object> getAllActiveProcessDefinition() throws RestException{
        try {
            RepositoryService repository=processEngine.getRepositoryService();
            List<ProcessDefinition> deployements = repository.createProcessDefinitionQuery().active().latestVersion().list();
            HashMap<String, Object> ret=new HashMap<String, Object>();
            for (ProcessDefinition deploy : deployements) {
                ret.put(deploy.getKey(), getProcessDefinitionAndChecksum(deploy.getKey(),deploy.getId()));
            }
            return ret;
        } catch (Exception e) {
            throw new RestException("BPM EXPORT", 1);
        }
    }

    public void uploadProcess(String processKey, String bpmContentBase64) throws RestException{
        try {
            byte[] bpmDefinition=Base64.decodeBase64(bpmContentBase64);
            String xmlString=new String(bpmDefinition);
            RepositoryService repository=processEngine.getRepositoryService();
            DeploymentBuilder deployBuilder = repository.createDeployment();
            deployBuilder.name(processKey);
            deployBuilder.addString(processKey+".bpmn20.xml", xmlString);
            deployBuilder.deploy();
        } catch (Exception e) {
            throw new RestException("BPM UPLOAD", 1);
        }
    }


    public void syncXmlConfiguration(String xmlFileName) throws RestException{
        try{
            java.io.File file = new File(fmCfg.getAddOnPath()+"/xml/"+xmlFileName+".xml");
            DocumentBuilder dBuilder = DocumentBuilderFactory.newInstance().newDocumentBuilder();

            Document doc = dBuilder.parse(file);
            Form f=new Form(doc, file.getName());
            syncXmlConfiguration(f);
        }catch (IOException e){
            Logger.getLogger(this.getClass()).error(e.getMessage(), e);
        } catch (ParserConfigurationException e) {
            Logger.getLogger(this.getClass()).error(e.getMessage(), e);
        } catch (SAXException e) {
            Logger.getLogger(this.getClass()).error(e.getMessage(), e);
        }
    }

    public ElementType getDocDefinitionByName(String docTypeIdString) {
        Criteria c = docTypeDAO.getCriteria();
        c.add(Restrictions.eq("typeId", docTypeIdString).ignoreCase());
        return (ElementType) c.uniqueResult();
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


    public void syncXmlConfiguration(Form xml) throws RestException{
        Criteria c = docTypeDAO.getCriteria();
        c.add(Restrictions.eq("typeId", xml.getObject()).ignoreCase());
        ElementType et= (ElementType) c.uniqueResult();
        HashMap<String, MetadataTemplate> templates=new HashMap<String, MetadataTemplate>();
        for (ElementTypeAssociatedTemplate at:et.getAssociatedTemplates()){
            templates.put(at.getMetadataTemplateName().toUpperCase(), at.getMetadataTemplate());
        }
        MetadataField mdf=null;
        for(Field f:xml.getFields()){
            if (f.getType().toUpperCase().equals("TEXT")) continue;
            String templateName=f.getVar().split("_")[0];
            String fieldName=f.getVar().split("_")[1];
            Logger.getLogger(this.getClass()).debug("Controllo campo "+templateName+" - "+fieldName);
            boolean found=false;

            if (templates.containsKey(templateName.toUpperCase())){
                for(MetadataField field:templates.get(templateName.toUpperCase()).getFields()){
                    if (fieldName.toUpperCase().equals(field.getName().toUpperCase())){
                        Logger.getLogger(this.getClass()).debug("Campo "+templateName+" - "+fieldName+" trovato in configurazione oggetto");
                        mdf=field;
                        found=true;
                    }
                }
            }
            String externalDictionary=null;
            String addFilterFields=null;
            String type=f.getType().toUpperCase();
            String typeFilter=null;
            if (f.getAttributes().containsKey("el_link_types")) {
                type="ELEMENT_LINK";
                String[] types=f.getAttributes().get("el_link_types").split(",");
                for(String t:types){
                    if (typeFilter==null) {
                        typeFilter=getTypeIdByNameOrId(t)+"";
                    }
                    else {
                        typeFilter+=","+getTypeIdByNameOrId(t);
                    }
                }
            }
            if (f.getAttributes().containsKey("ext_script")) {
                type="EXT_DICTIONARY";
                externalDictionary=f.getAttributes().get("ext_script");
                if (f.getAttributes().containsKey("ext_params")) {
                    addFilterFields=f.getAttributes().get("ext_params");
                }
            }
            if (!found) {
                Logger.getLogger(this.getClass()).debug("Campo non trovato in configurazione");
                MetadataTemplate t=null;
                if (!templates.containsKey(templateName.toUpperCase())){
                    Logger.getLogger(this.getClass()).debug("Devo creare template "+templateName); //toCamelCase(templateName));
                    String tname= templateName; //toCamelCase(templateName);
                    Logger.getLogger(this.getClass()).debug("Cerco un template con quel nome");
                    c = mdDAO.getCriteria();
                    c.add(Restrictions.eq("name", tname).ignoreCase())
                    .add(Restrictions.eq("deleted", false));
                    t= (MetadataTemplate) c.uniqueResult();
                    if (t==null) {
                        Logger.getLogger(this.getClass()).debug("Creo il template "+tname);
                        t = saveTemplate(tname, tname, false, false, false, null, null, null, null, null);
                    }
                    Logger.getLogger(this.getClass()).debug("Associo il template "+tname+" all'tipo di elemento "+et.getTypeId());
                    assocTemplate(et, t.getId(), true);
                }else {

                    t=templates.get(templateName.toUpperCase());
                }
                String fname=fieldName; //toCamelCase(fieldName);
                Logger.getLogger(this.getClass()).debug("Aggiungo il campo "+fname+" al template "+t.getName());
                addField(t, fname, type, false, typeFilter, f.getAvailableValues(), externalDictionary, addFilterFields, null, null, null, null, null, null);
            }else {
                Logger.getLogger(this.getClass()).debug("Aggiorno il campo "+mdf.getExtendedName());
                addField(mdf.getTemplate(), mdf.getName(), type, false, typeFilter, f.getAvailableValues(), externalDictionary, addFilterFields, mdf.getId(), null, null, null, null, null);
            }
        }
    }




    public LinkedList<String> getXmlFiles() throws RestException {
        LinkedList<String> ret=new LinkedList<String>();
        File folder = new File(fmCfg.getAddOnPath()+"/xml");
        if (!folder.exists()){
            throw new RestException("XML_FOLDER_NOT_FOUND",1);
        }
        File[] listOfFiles = folder.listFiles();
        for (int i = 0; i < listOfFiles.length; i++) {
            if (listOfFiles[i].isFile() || listOfFiles[i].getName().endsWith("\\.xml")) {
                ret.add(listOfFiles[i].getName().replaceAll("\\.xml", ""));
                Logger.getLogger(this.getClass()).debug("File " + listOfFiles[i].getName());
            }
        }
        return ret;
    }

    public Form getXmlForm(String xmlFile) throws AxmrGenericException {
        try {
            java.io.File file = new File(fmCfg.getAddOnPath() + "/xml/" + xmlFile + ".xml");
            DocumentBuilder dBuilder = DocumentBuilderFactory.newInstance().newDocumentBuilder();

            Document doc = dBuilder.parse(file);

            Form f = new Form(doc, file.getName());
            return f;
        }catch (Exception ex){
            throw new AxmrGenericException("Errore file XML");
        }
    }

    public String getXmlContent(String xmlFile) throws AxmrGenericException {
        try {
            java.io.File file = new File(fmCfg.getAddOnPath() + "/xml/" + xmlFile + ".xml");
            if (file.exists()) {
                String content = new String(Files.readAllBytes(Paths.get(fmCfg.getAddOnPath() + "/xml/" + xmlFile + ".xml")));
                return content;
            }else return "";
        }catch (Exception ex){
            throw new AxmrGenericException("Errore file XML");
        }
    }

    public void saveXmlContent(String xmlFile, String content) throws AxmrGenericException {
        try {
            java.io.File file = new File(fmCfg.getAddOnPath() + "/xml/" + xmlFile + ".xml");

            FileUtils.writeStringToFile(new File(fmCfg.getAddOnPath() + "/xml/" + xmlFile + ".xml"), content);
        } catch (IOException e) {
            Logger.getLogger(this.getClass()).error(e.getMessage(), e);
            throw new AxmrGenericException(e.getMessage());
        }
    }

    public Properties getMessages() {
        return getMessages(null);
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

    public void changeTemplateStatusForElement(Long id, String templateName) throws AxmrGenericException {
        ElementType type=docTypeDAO.getById(id);
        for (ElementTypeAssociatedTemplate at:type.getAssociatedTemplates()){
            if (at.getMetadataTemplate().getName().toUpperCase().equals(templateName.toUpperCase())) {
                at.setEnabled(!at.isEnabled());
            }
        }
        docTypeDAO.saveOrUpdate(type);

    }
}
