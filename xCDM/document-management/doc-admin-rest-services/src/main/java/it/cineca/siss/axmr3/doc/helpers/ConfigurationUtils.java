package it.cineca.siss.axmr3.doc.helpers;

import it.cineca.siss.axmr3.doc.entities.*;
import it.cineca.siss.axmr3.doc.types.MetadataFieldType;
import it.cineca.siss.axmr3.doc.web.services.AdminService;
import org.activiti.engine.repository.Deployment;
import org.activiti.engine.repository.Model;
import org.activiti.engine.repository.ProcessDefinition;
import org.apache.commons.codec.binary.Base64;
import org.apache.commons.codec.binary.Base64OutputStream;
import org.apache.commons.io.IOUtils;
import org.dom4j.CDATA;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

import javax.servlet.ServletOutputStream;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.IOException;
import java.io.InputStream;
import java.io.StringReader;
import java.io.StringWriter;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by cin0562a on 03/10/14.
 */
public class ConfigurationUtils {


    private AdminService admService;
    private Document doc;
    private List<String> processKeys;

    public void setAdmService(AdminService admService) {
        this.admService = admService;
    }

    public AdminService getAdmService() {
        return admService;
    }

    public void getFullExportXml(ServletOutputStream outputStream) throws ParserConfigurationException, TransformerException, IOException {
        DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
        DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
        doc = docBuilder.newDocument();
        Element rootElement = doc.createElement("configuration");
        doc.appendChild(rootElement);
        rootElement.appendChild(typesExporter());
        rootElement.appendChild(templatesExporter());
        rootElement.appendChild(predPoliciesExporter());
        rootElement.appendChild(calendarsExporter());
        rootElement.appendChild(processExporter());
        DOMSource source = new DOMSource(doc);
        TransformerFactory transformerFactory = TransformerFactory.newInstance();
        Transformer transformer = transformerFactory.newTransformer();
        StreamResult result = new StreamResult(outputStream);
        transformer.transform(source, result);
    }


    public Element calendarsExporter() {
        Element calendars = this.doc.createElement("calendars");
        List<CalendarEntity> ts = admService.getCalendars();
        for (CalendarEntity t : ts) {
            calendars.appendChild(calendarExporter(t));
        }
        return calendars;
    }

    public Element calendarExporter(CalendarEntity t) {
        Element calendar = this.doc.createElement("calendar");
        calendar.setAttribute("name", t.getName());
        if (t.getBackgroundColor() != null) calendar.setAttribute("color", t.getBackgroundColor());
        calendar.setAttribute("id", "" + t.getId());
        calendar.setAttribute("start-date-template-name", t.getStartDateField().getTemplate().getName());
        calendar.setAttribute("start-date-field-name", t.getStartDateField().getName());
        if (t.getEndDateField() != null) {
            calendar.setAttribute("end-date-template-name", t.getEndDateField().getTemplate().getName());
            calendar.setAttribute("end-date-field-name", t.getEndDateField().getName());
        }
        if (t.getElementType() != null) calendar.setAttribute("type", t.getElementType().getTypeId());
        if (t.getTitleRegex() != null) {
            Element titleRegex = doc.createElement("title-regex");
            titleRegex.setTextContent(t.getTitleRegex());
            calendar.appendChild(titleRegex);
        }
        return calendar;
    }

    public Element processExporter() throws IOException {
        Element workflows = this.doc.createElement("workflows");
        for (String pkey : processKeys) {
            ProcessDefinition bpmn = admService.getProcessEngine().getRepositoryService().createProcessDefinitionQuery().processDefinitionKey(pkey).latestVersion().singleResult();
            String processFileName = bpmn.getKey() + ".bpmn20.xml";
            InputStream model = admService.getProcessEngine().getRepositoryService().getProcessModel(bpmn.getId());
            byte[] bytes = IOUtils.toByteArray(model);
            byte[] bytes64 = Base64.encodeBase64(bytes);
            String content = new String(bytes64);
            Element workflow = doc.createElement("workflow");
            workflow.setAttribute("filename", processFileName);
            workflow.setAttribute("process-key", pkey);
            workflow.setTextContent(content);
            workflows.appendChild(workflow);
        }
        return workflows;
    }

    public Element predPoliciesExporter() {
        Element policies = this.doc.createElement("policies");
        List<PredefinedPolicy> ts = admService.getPolicies();
        for (PredefinedPolicy t : ts) {
            policies.appendChild(predPolicyExporter(t));
        }
        return policies;
    }

    public Element predPolicyExporter(PredefinedPolicy t) {
        Element policy = this.doc.createElement("policy");
        if (t.getDescription() != null) policy.setAttribute("description", t.getDescription());
        policy.setAttribute("integer-ace", "" + t.getPolicyValue());
        policy.setAttribute("name", t.getName());
        policy.setAttribute("id", "" + t.getId());
        return policy;
    }

    public Element templatesExporter() {
        Element templates = this.doc.createElement("templates");
        List<MetadataTemplate> ts = admService.getMds();
        for (MetadataTemplate t : ts) {
            templates.appendChild(templateExporter(t));
        }
        return templates;
    }

    public Element templateExporter(MetadataTemplate t) {
        Element template = this.doc.createElement("template");
        template.setAttribute("name", t.getName());
        template.setAttribute("id", "" + t.getId());
        template.setAttribute("auditable", "" + t.isAuditable());
        template.setAttribute("calendarizable", "" + t.isCalendarized());
        if (t.getCalendarName() != null) template.setAttribute("calendar-name", t.getCalendarName());
        if (t.getCalendarColor() != null) template.setAttribute("calendar-color", t.getCalendarColor());
        if (t.getStartDateField() != null)
            template.setAttribute("calendar-start-date", t.getStartDateField().getName());
        if (t.getEndDateField() != null) template.setAttribute("calendar-end-date", t.getEndDateField().getName());
        if (t.getFields() != null && t.getFields().size() > 0) {
            Element fields = doc.createElement("fields");
            for (MetadataField f : t.getFields()) {
                Element field = doc.createElement("field");
                field.setAttribute("name", f.getName());
                field.setAttribute("id", "" + f.getId());
                if (f.getExtendedName() != null) field.setAttribute("extended-name", f.getExtendedName());
                if (f.getMacro() != null) field.setAttribute("macro", f.getMacro());
                if (f.getMacroView() != null) field.setAttribute("macro-view", f.getMacroView());
                field.setAttribute("type", f.getType().name());
                if (f.getTypefilters() != null) {
                    Element tf = doc.createElement("type-filters");
                    tf.setTextContent(f.getTypefilters());
                    field.appendChild(tf);
                }

                if (f.getAddFilterFields() != null) {
                    Element tf = doc.createElement("add-filter-fields");
                    tf.setTextContent(f.getAddFilterFields());
                    field.appendChild(tf);
                }

                if (f.getAvailableValues() != null) {
                    Element tf = doc.createElement("available-values");
                    tf.setTextContent(f.getAvailableValues());
                    field.appendChild(tf);
                }

                if (f.getExternalDictionary() != null) {
                    Element tf = doc.createElement("ext-dictionary");
                    tf.setTextContent(f.getExternalDictionary());
                    field.appendChild(tf);
                }
                if (f.getSize() != null) field.setAttribute("size", "" + f.getSize());
                if (f.getPosition() != null) field.setAttribute("position", "" + f.getPosition());

                fields.appendChild(field);
            }
            template.appendChild(fields);
        }
        return template;
    }

    public Element typesExporter() {
        Element types = this.doc.createElement("types");
        List<ElementType> ts = admService.getTypes();
        for (ElementType t : ts) {
            types.appendChild(typeExporter(t));
        }
        return types;
    }

    public Element typeExporter(ElementType t) {
        Element type = this.doc.createElement("type");
        type.setAttribute("id", "" + t.getId());
        type.setAttribute("checkout-enabled", "" + t.isCheckOutEnabled());
        type.setAttribute("sortable", "" + t.isSortable());
        type.setAttribute("container", "" + t.isContainer());
        type.setAttribute("deleted", "" + t.isDeleted());
        type.setAttribute("draftable", "" + t.isDraftable());
        type.setAttribute("has-file-attached", "" + t.isHasFileAttached());
        type.setAttribute("no-fileinfo", "" + t.isNoFileinfo());
        type.setAttribute("rootAble", "" + t.isRootAble());
        type.setAttribute("searchable", "" + t.isSearchable());
        type.setAttribute("self-recursive", "" + t.isSelfRecursive());
        type.setAttribute("name", t.getTypeId());
        if (t.getTitleField() != null) {
            type.setAttribute("titlefield-template", t.getTitleField().getTemplate().getName());
            type.setAttribute("titlefield-name", t.getTitleField().getName());
        }
        Element icon = doc.createElement("icon");
        icon.setTextContent(t.getImageBase64());
        type.appendChild(icon);
        if (t.getTitleRegex() != null) {
            Element titleRegex = doc.createElement("title-regex");
            titleRegex.setTextContent(t.getTitleRegex());
            type.appendChild(titleRegex);
        }
        if (t.getFtlRowTemplate() != null) {
            Element ftlGrid = doc.createElement("ftl-grid");
            ftlGrid.setTextContent(t.getFtlRowTemplate());
            type.appendChild(ftlGrid);
        }
        if (t.getFtlDetailTemplate() != null) {
            Element ftlDetail = doc.createElement("ftl-detail");
            ftlDetail.setTextContent(t.getFtlDetailTemplate());
            type.appendChild(ftlDetail);
        }
        if (t.getFtlFormTemplate() != null) {
            Element ftlForm = doc.createElement("ftl-form");
            ftlForm.setTextContent(t.getFtlFormTemplate());
            type.appendChild(ftlForm);
        }
        if (t.getHashBack() != null) {
            Element hash = doc.createElement("hash");
            hash.setTextContent(t.getHashBack());
            type.appendChild(hash);
        }
        if (t.getGroupUpLevel() != null) type.setAttribute("group-up-level", "" + t.getGroupUpLevel());


        if (t.getAllowedChilds() != null && t.getAllowedChilds().size() > 0) {
            Element children = doc.createElement("children");
            for (ElementType c : t.getAllowedChilds()) {
                Element child = doc.createElement("child");
                child.setAttribute("name", c.getTypeId());
                child.setAttribute("id", "" + c.getId());
                children.appendChild(child);
            }
            type.appendChild(children);
        }

        if (t.getAssociatedTemplates() != null && t.getAssociatedTemplates().size() > 0) {
            Element templates = doc.createElement("templates");
            for (ElementTypeAssociatedTemplate a : t.getAssociatedTemplates()) {
                Element template = doc.createElement("template");
                template.setAttribute("name", a.getMetadataTemplate().getName());
                template.setAttribute("enabled", "" + a.isEnabled());
                template.setAttribute("id", "" + a.getMetadataTemplate().getId());
                if (a.getTemplateAcls() != null && a.getTemplateAcls().size() > 0) {
                    Element acls = doc.createElement("acls");
                    for (TemplateAcl a1 : a.getTemplateAcls()) {
                        Element acl = doc.createElement("acl");
                        acl.setAttribute("id", "" + a1.getId());
                        acl.setAttribute("positional-ace", "" + a1.getPositionalAce());
                        acl.setAttribute("integer-ace", "" + a1.getPolicyValue());
                        if (a1.getContainers() != null && a1.getContainers().size() > 0) {
                            Element containers = doc.createElement("acl-containers");
                            for (TemplateAclContainer ac1 : a1.getContainers()) {
                                Element container = doc.createElement("container");
                                container.setAttribute("group", "" + ac1.isAuthority());
                                container.setAttribute("value", ac1.getContainer());
                                containers.appendChild(container);
                            }
                            acl.appendChild(containers);
                        }
                        acls.appendChild(acl);
                    }
                    template.appendChild(acls);
                }
                templates.appendChild(template);
            }
            type.appendChild(templates);
        }

        if (t.getAcls() != null && t.getAcls().size() > 0) {
            Element acls = doc.createElement("acls");
            for (Acl a : t.getAcls()) {
                Element acl = doc.createElement("acl");
                acl.setAttribute("positionl-ace", a.getPositionalAce());
                if (a.getDetailTemplate() != null) acl.setAttribute("ftl", a.getDetailTemplate());
                acl.setAttribute("integer-ace", "" + a.getPolicyValue());
                if (a.getPredifinedPolicy() != null) {
                    acl.setAttribute("predefined-policy-name", a.getPredifinedPolicy().getName());
                    acl.setAttribute("predefined-policy-id", "" + a.getPredifinedPolicy().getId());
                }
                if (a.getContainers() != null && a.getContainers().size() > 0) {
                    Element containers = doc.createElement("acl-containers");
                    for (AclContainer ac1 : a.getContainers()) {
                        Element container = doc.createElement("container");
                        container.setAttribute("group", "" + ac1.isAuthority());
                        container.setAttribute("value", ac1.getContainer());
                        containers.appendChild(container);
                    }
                    acl.appendChild(containers);
                }
                acls.appendChild(acl);
            }
            type.appendChild(acls);
        }

        if (t.getAssociatedWorkflows() != null && t.getAssociatedWorkflows().size() > 0) {
            Element workflows = doc.createElement("workflows");
            for (ElementTypeAssociatedWorkflow wf : t.getAssociatedWorkflows()) {
                Element wft = doc.createElement("workflow");
                wft.setAttribute("process-key", wf.getProcessKey());
                if (processKeys == null) processKeys = new LinkedList<String>();
                processKeys.add(wf.getProcessKey());
                wft.setAttribute("id", "" + wf.getId());
                wft.setAttribute("enabled", "" + wf.isEnabled());
                wft.setAttribute("start-on-create", "" + wf.isStartOnCreate());
                wft.setAttribute("start-on-delete", "" + wf.isStartOnDelete());
                wft.setAttribute("start-on-update", "" + wf.isStartOnUpdate());
                workflows.appendChild(wft);
            }
            type.appendChild(workflows);
        }

        return type;
    }

    public static MetadataField fieldFromXmlNode(Element node) {
        MetadataField f = new MetadataField();
        f.setName(node.getAttribute("name"));
        if (node.getAttribute("macro") != null) f.setMacro(node.getAttribute("macro"));
        if (node.getAttribute("macro-view") != null) f.setMacroView(node.getAttribute("macro-view"));
        if (node.getAttribute("type") != null)
            f.setType(MetadataFieldType.valueOfIgnoreCase(node.getAttribute("type")));
        if (node.getAttribute("size") != null) f.setSize(Integer.parseInt(node.getAttribute("size")));
        if (node.getAttribute("position") != null) f.setPosition(Integer.parseInt(node.getAttribute("position")));
        if (node.hasChildNodes()) {
            NodeList cl = node.getChildNodes();
            for (int i = 0; i < cl.getLength(); i++) {
                Element c = (Element) cl.item(i);
                if (c.getTagName().equals("type-filters")) f.setTypefilters(c.getTextContent());
                if (c.getTagName().equals("add-filter-fields")) f.setAddFilterFields(c.getTextContent());
                if (c.getTagName().equals("available-values")) f.setAvailableValues(c.getTextContent());
                if (c.getTagName().equals("ext-dictionary")) f.setExternalDictionary(c.getTextContent());
            }
        }
        return f;
    }

    public static MetadataTemplate templateFromXmlNode(Element node) {
        MetadataTemplate t = new MetadataTemplate();
        t.setName(node.getAttribute("name"));
        if (node.getAttribute("auditable") != null)
            t.setAuditable(Boolean.parseBoolean(node.getAttribute("auditable")));
        else t.setAuditable(false);
        if (node.getAttribute("calendarizable") != null)
            t.setCalendarized(Boolean.parseBoolean(node.getAttribute("calendarizable")));
        else t.setAuditable(false);
        if (node.getAttribute("calendar-name") != null) t.setCalendarName(node.getAttribute("calendar-name"));
        if (node.getAttribute("calendar-color") != null) t.setCalendarColor(node.getAttribute("calendar-color"));
        String startDateFieldName = "";
        if (node.getAttribute("calendar-start-date") != null) {
            startDateFieldName = node.getAttribute("calendar-start-date");
        }
        String endDateFieldName = "";
        if (node.getAttribute("calendar-end-date") != null) {
            endDateFieldName = node.getAttribute("calendar-end-date");
        }
        if (node.hasChildNodes()) {
            NodeList cl = node.getChildNodes();
            for (int i = 0; i < cl.getLength(); i++) {
                Element c = (Element) cl.item(i);
                if (c.hasChildNodes()) {
                    List<MetadataField> fs = new LinkedList<MetadataField>();
                    NodeList fl = c.getChildNodes();
                    for (int fi = 0; fi < fl.getLength(); fi++) {
                        Element fNode = (Element) fl.item(fi);
                        fs.add(fieldFromXmlNode(fNode));
                    }
                }
            }
        }
        for (MetadataField f : t.getFields()) {
            f.setTemplate(t);
            if (!startDateFieldName.isEmpty() && f.getName().equals(startDateFieldName)) t.setStartDateField(f);
            if (!endDateFieldName.isEmpty() && f.getName().equals(endDateFieldName)) t.setEndDateField(f);
        }
        return t;
    }

    public static CalendarEntity calendarFromXmlNode(Element node) {
        CalendarEntity cal = new CalendarEntity();
        cal.setName(node.getAttribute("name"));
        if (node.getAttribute("color") != null) cal.setBackgroundColor(node.getAttribute("color"));
        MetadataField startField = new MetadataField();
        MetadataTemplate startTemplate = new MetadataTemplate();
        startTemplate.setName(node.getAttribute("start-date-template-name"));
        startField.setTemplate(startTemplate);
        startField.setName(node.getAttribute("start-date-field-name"));
        if (node.getAttribute("end-date-template-name") != null) {
            MetadataField endField = new MetadataField();
            MetadataTemplate endTemplate = new MetadataTemplate();
            startTemplate.setName(node.getAttribute("end-date-template-name"));
            startField.setTemplate(startTemplate);
            startField.setName(node.getAttribute("end-date-field-name"));
        }
        if (node.getAttribute("type") != null) {
            ElementType type = new ElementType();
            type.setTypeId(node.getAttribute("type"));
        }
        if (node.hasChildNodes()) {
            NodeList cl = node.getChildNodes();
            for (int i = 0; i < cl.getLength(); i++) {
                Element c = (Element) cl.item(i);
                if (c.getTagName().equals("title-regex")) cal.setTitleRegex(c.getTextContent());
            }
        }
        return cal;
    }

    public static PredefinedPolicy policyFromXmlNode(Element node) {
        PredefinedPolicy pol = new PredefinedPolicy();
        if (node.getAttribute("description") != null) pol.setDescription(node.getAttribute("description"));
        pol.setName(node.getAttribute("name"));
        pol.setPolicyValue(Integer.parseInt(node.getAttribute("integer-ace")));
        return pol;
    }

    public static ElementType typeFromXmlNode(Element node) {
        ElementType t = new ElementType();
        t.setTypeId(node.getAttribute("name"));
        t.setCheckOutEnabled(Boolean.parseBoolean(node.getAttribute("checkout-enabled")));
        t.setSortable(Boolean.parseBoolean(node.getAttribute("sortable")));
        t.setContainer(Boolean.parseBoolean(node.getAttribute("container")));
        t.setDeleted(Boolean.parseBoolean(node.getAttribute("deleted")));
        t.setDraftable(Boolean.parseBoolean(node.getAttribute("draftable")));
        t.setHasFileAttached(Boolean.parseBoolean(node.getAttribute("has-file-attached")));
        t.setNoFileinfo(Boolean.parseBoolean(node.getAttribute("no-fileinfo")));
        t.setRootAble(Boolean.parseBoolean(node.getAttribute("rootAble")));
        t.setSearchable(Boolean.parseBoolean(node.getAttribute("searchable")));
        t.setSelfRecursive(Boolean.parseBoolean(node.getAttribute("self-recursive")));
        if (node.getAttribute("titlefield-template") != null && !node.getAttribute("titlefield-template").isEmpty()) {
            MetadataTemplate tpl = new MetadataTemplate();
            tpl.setName(node.getAttribute("titlefield-template"));
            MetadataField f = new MetadataField();
            f.setTemplate(tpl);
            f.setName(node.getAttribute("titlefield-name"));
            t.setTitleField(f);
        } else {
            t.setTitleField(null);
        }
        t.setGroupUpLevel(Long.parseLong("0"));
        if (node.getAttribute("group-up-level") != null && !node.getAttribute("group-up-level").isEmpty()) {
            t.setGroupUpLevel(Long.parseLong(node.getAttribute("group-up-level")));
        }
        if (node.hasChildNodes()) {
            NodeList nl = node.getChildNodes();
            for (int i = 0; i < nl.getLength(); i++) {
                Element cn = (Element) nl.item(i);
                if (cn.getTagName().equals("icon") && cn.getTextContent() != null && !cn.getTextContent().isEmpty()) {
                    t.setImg(Base64.decodeBase64(cn.getTextContent()));
                }
                if (cn.getTagName().equals("title-regex")) t.setTitleRegex(cn.getTextContent());
                if (cn.getTagName().equals("ftl-grid")) t.setFtlRowTemplate(cn.getTextContent());
                if (cn.getTagName().equals("ftl-detail")) t.setFtlDetailTemplate(cn.getTextContent());
                if (cn.getTagName().equals("ftl-form")) t.setFtlFormTemplate(cn.getTextContent());
                if (cn.getTagName().equals("hash")) t.setHashBack(cn.getTextContent());
                if (cn.getTagName().equals("children")) {
                    if (cn.hasChildNodes()) {
                        NodeList nl1 = cn.getChildNodes();
                        List<ElementType> children = new LinkedList<ElementType>();
                        for (int c = 0; c < nl1.getLength(); c++) {
                            Element cn1 = (Element) nl1.item(c);
                            ElementType child = new ElementType();
                            child.setTypeId(cn1.getAttribute("name"));
                            children.add(child);
                        }
                        t.setAllowedChilds(children);
                    }
                }
                if (cn.getTagName().equals("templates")) {
                    if (cn.hasChildNodes()) {
                        NodeList nl1 = cn.getChildNodes();
                        List<ElementTypeAssociatedTemplate> templates = new LinkedList<ElementTypeAssociatedTemplate>();
                        for (int i1 = 0; i1 < nl1.getLength(); i1++) {
                            Element cn1 = (Element) nl1.item(i1);
                            ElementTypeAssociatedTemplate at = new ElementTypeAssociatedTemplate();
                            at.setEnabled(Boolean.parseBoolean(cn1.getAttribute("enabled")));
                            MetadataTemplate template = new MetadataTemplate();
                            template.setName(cn1.getAttribute("name"));
                            at.setMetadataTemplate(template);
                            if (cn1.hasChildNodes()) {
                                NodeList nl2 = cn1.getChildNodes();
                                LinkedList<TemplateAcl> acls = new LinkedList<TemplateAcl>();
                                for (int i2 = 0; i2 < nl2.getLength(); i2++) {
                                    Element cn2 = (Element) nl2.item(i2);//tag acls
                                    NodeList nl3 = cn2.getChildNodes();
                                    for (int i3 = 0; i3 < nl3.getLength(); i3++) {
                                        Element cn3 = (Element) nl3.item(i3);//tag acl
                                        TemplateAcl acl = new TemplateAcl();
                                        acl.setPositionalAce(cn3.getAttribute("positional-ace"));
                                        acl.setPolicyValue(Integer.parseInt(cn3.getAttribute("integer-ace")));
                                        if (cn3.hasChildNodes()) {
                                            NodeList nl4 = cn3.getChildNodes();
                                            LinkedList<TemplateAclContainer> cs = new LinkedList<TemplateAclContainer>();
                                            for (int i4 = 0; i4 < nl4.getLength(); i4++) {//nodo acl-containers
                                                Element cn4 = (Element) nl4.item(i4);
                                                NodeList nl5 = cn4.getChildNodes();
                                                for (int i5 = 0; i5 < nl5.getLength(); i5++) {//nodo container
                                                    Element cn5 = (Element) nl5.item(i5);
                                                    TemplateAclContainer tc = new TemplateAclContainer();
                                                    tc.setAuthority(Boolean.parseBoolean(cn5.getAttribute("group")));
                                                    tc.setContainer(cn5.getAttribute("value"));
                                                    cs.add(tc);
                                                }
                                            }
                                            acl.setContainers(cs);
                                        }
                                        acls.add(acl);
                                    }
                                }
                                at.setTemplateAcls(acls);
                            }
                        }
                        t.setAssociatedTemplates(templates);
                    }
                }
                if (cn.getTagName().equals("acls")) {
                    if (cn.hasChildNodes()) {
                        NodeList nl1 = cn.getChildNodes();
                        List<Acl> acls = new LinkedList<Acl>();
                        for (int i1 = 0; i1 < nl1.getLength(); i1++) {//nodo acl
                            Element cn1 = (Element) nl1.item(i1);
                            Acl acl = new Acl();
                            acl.setPositionalAce(cn1.getAttribute("positionl-ace"));
                            acl.setPolicyValue(Integer.parseInt(cn1.getAttribute("integer-ace")));
                            if (cn1.getAttribute("predefined-policy-name") != null) {
                                PredefinedPolicy pol = new PredefinedPolicy();
                                pol.setName(cn1.getAttribute("predefined-policy-name"));
                                acl.setPredifinedPolicy(pol);
                            }
                            if (cn1.hasChildNodes()) {
                                NodeList nl2 = cn1.getChildNodes();
                                List<AclContainer> containers = new LinkedList<AclContainer>();
                                for (int i2 = 0; i2 < nl2.getLength(); i2++) {
                                    Element cn2 = (Element) nl2.item(i2);
                                    AclContainer container = new AclContainer();
                                    container.setAuthority(Boolean.parseBoolean(cn2.getAttribute("group")));
                                    container.setContainer(cn2.getAttribute("value"));
                                    containers.add(container);
                                }
                                acl.setContainers(containers);
                            }
                            acls.add(acl);
                        }
                        t.setAcls(acls);
                    }
                }
                if (cn.getTagName().equals("workflows")) {
                    if (cn.hasChildNodes()) {
                        NodeList nl1 = cn.getChildNodes();

                        List<ElementTypeAssociatedWorkflow> awfs = new LinkedList<ElementTypeAssociatedWorkflow>();
                        for (int i1 = 0; i1 < nl1.getLength(); i1++) {//nodo workflow
                            Element cn1 = (Element) nl1.item(i1);
                            ElementTypeAssociatedWorkflow awf = new ElementTypeAssociatedWorkflow();
                            awf.setEnabled(Boolean.parseBoolean(cn1.getAttribute("enabled")));
                            awf.setStartOnCreate(Boolean.parseBoolean(cn1.getAttribute("start-on-create")));
                            awf.setStartOnDelete(Boolean.parseBoolean(cn1.getAttribute("start-on-delete")));
                            awf.setStartOnUpdate(Boolean.parseBoolean(cn1.getAttribute("start-on-update")));
                            awf.setProcessKey(cn1.getAttribute("process-key"));
                            awfs.add(awf);
                        }
                        t.setAssociatedWorkflows(awfs);
                    }
                }
            }
        }
        return t;
    }

    public ConfigurationComparisonResult doCompare(String xmlFileContent) throws ParserConfigurationException, IOException, SAXException {
        DocumentBuilder db = DocumentBuilderFactory.newInstance().newDocumentBuilder();
        InputSource is = new InputSource();
        is.setCharacterStream(new StringReader(xmlFileContent));
        Document doc = db.parse(is);
        NodeList nodes = doc.getElementsByTagName("types");
        ConfigurationComparisonResult res = new ConfigurationComparisonResult("types");
        res.setComparisonResultType(ComparisonResultType.EQ);
        for (int i = 0; i < nodes.getLength(); i++) {
            Element types = (Element) nodes.item(i);
            if (types.hasChildNodes()) {
                NodeList nl1 = types.getChildNodes();
                for (int i1 = 0; i1 < nl1.getLength(); i1++) {
                    Element node = (Element) nl1.item(i1);
                    res.addSubComparison(ConfigurationComparisonResult.typeCompare(node, this.admService));
                }
            }
        }
        return res;
    }

}
