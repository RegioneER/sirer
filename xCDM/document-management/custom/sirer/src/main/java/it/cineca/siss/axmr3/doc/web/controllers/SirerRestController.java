package it.cineca.siss.axmr3.doc.web.controllers;

import it.cineca.siss.axmr3.authentication.IAuthority;
import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.authentication.services.SissUserService;
import it.cineca.siss.axmr3.doc.entities.Element;
import it.cineca.siss.axmr3.doc.entities.ElementMetadata;
import it.cineca.siss.axmr3.doc.entities.ElementMetadataValue;
import it.cineca.siss.axmr3.doc.entities.ElementType;
import it.cineca.siss.axmr3.doc.json.ElementJSON;
import it.cineca.siss.axmr3.doc.json.JqGridJSON;
import it.cineca.siss.axmr3.doc.types.PostResult;
import it.cineca.siss.axmr3.doc.web.exceptions.RestException;
import it.cineca.siss.axmr3.doc.web.services.DocumentService;
import it.cineca.siss.axmr3.exceptions.AxmrGenericException;
import it.cineca.siss.axmr3.hibernate.BaseDao;
import it.cineca.siss.axmr3.sirer.actions.ProcessBean;
import org.activiti.engine.runtime.ProcessInstance;
import org.apache.log4j.Logger;
import org.hibernate.Criteria;
import org.hibernate.criterion.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.servlet.http.HttpServletRequest;
import javax.sql.DataSource;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.*;

/**
 * /**
 * Created by cin0562a on 26/09/14.
 */
@Controller
public class SirerRestController {

    @Autowired
    @Qualifier(value = "UserDataSource")
    protected DataSource dataSource;

    public DataSource getDataSource() {
        return dataSource;
    }

    public void setDataSource(DataSource dataSource) {
        this.dataSource = dataSource;
    }

    @Autowired
    protected DocumentService docService;

    public DocumentService getDocService() {
        return docService;
    }

    public void setDocService(DocumentService docService) {
        this.docService = docService;
    }

    @Autowired
    protected SissUserService userService;

    public SissUserService getUserService() {
        return userService;
    }

    public void setUserService(SissUserService userService) {
        this.userService = userService;
    }

    @Autowired
    protected ProcessBean processBean;

    public ProcessBean getProcessBean() {
        return processBean;
    }

    public void setProcessBean(ProcessBean processBean) {
        this.processBean = processBean;
    }



    public DetachedCriteria statoBudgetCriteria(IUser user) {
        DetachedCriteria c;
        if (user == null) {
            c = docService.getAllElementsCriteria("root");
        } else {
            c = docService.getViewableElementsCriteria(user, "root");
        }
        Criteria centroTypeCriteria = docService.getDocTypeDAO().getCriteria();
        centroTypeCriteria.add(Restrictions.eq("typeId", "Centro"));
        centroTypeCriteria.add(Restrictions.eq("deleted", false));
        Criteria budgetTypeCriteria = docService.getDocTypeDAO().getCriteria();
        budgetTypeCriteria.add(Restrictions.eq("typeId", "Budget"));
        budgetTypeCriteria.add(Restrictions.eq("deleted", false));
        ElementType centroType = (ElementType) centroTypeCriteria.uniqueResult();
        ElementType budgetType = (ElementType) budgetTypeCriteria.uniqueResult();
        c.add(Restrictions.eq("root.type", centroType));
        /*
         Seleziono l'ultimo elemento di tipo Budget per ogni centro
         */
        DetachedCriteria maxIdListCriteria = DetachedCriteria.forClass(Element.class, "sq");
        ProjectionList proj = Projections.projectionList();
        proj.add(Projections.max("id"));
        proj.add(Projections.groupProperty("parent"));
        maxIdListCriteria.add(Restrictions.eq("sq.type", budgetType));
        maxIdListCriteria.add(Restrictions.eq("sq.deleted", false));
        maxIdListCriteria.setProjection(proj);
        maxIdListCriteria.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);
        /*
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"Prima query-----\n\n\n\n\n\n");
        docService.getDocDAO().getCriteriaList(maxIdListCriteria);
        */

        /*
         Seleziono i Budget che hanno il template ChiusuraBudget disabilitato tra quelli restituiti dalla query precedente
         */
        DetachedCriteria disabledTemplateCriteria = DetachedCriteria.forClass(Element.class, "ds");
        disabledTemplateCriteria.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);
        disabledTemplateCriteria.add(Restrictions.eq("ds.deleted", false));
        disabledTemplateCriteria.setProjection(Projections.property("parent.id"));
        disabledTemplateCriteria.add(docService.templateDisabledCriterion("ChiusuraBudget", disabledTemplateCriteria.getAlias()));
        String[] ps = new String[2];
        ps[0] = "id";
        ps[1] = "parent";
        disabledTemplateCriteria.add(Subqueries.propertiesIn(ps, maxIdListCriteria));
        /*
         Seleziono i Centri "padri" dei risultati precedenti
         */
        c.add(Subqueries.propertyIn("id", disabledTemplateCriteria));
        c.addOrder(Order.desc("root.creationDt"));
        return c;

    }


    public DetachedCriteria contrattoCriteria(IUser user) {
        /*
         Applico primo filtro su campo valCTC del template statoValidazioneCentro = 1
         */
        HashMap<String, Object> filter1 = new HashMap<String, Object>();
        filter1.put("statoValidazioneCentro_valCTC_eq", "1");
        DetachedCriteria c = docService.advancedSearchCriteria(user, "Centro", filter1);

        /*
         Aggiungo clausola sui figli di tipo contratto:
          template ApprovDADSRETT disabilitato o
          template ApprovDADSRETT2 disabilitato
         */
        Criteria contrattoTypeCriteria = docService.getDocTypeDAO().getCriteria();
        contrattoTypeCriteria.add(Restrictions.eq("typeId", "Contratto"));
        ElementType contrattoType = (ElementType) contrattoTypeCriteria.uniqueResult();
        DetachedCriteria contrattoDC = DetachedCriteria.forClass(Element.class, "contratto");
        contrattoDC.add(Restrictions.eq("type", contrattoType));
        contrattoDC.add(Restrictions.eq("deleted", false));
        Criterion contrattoApprovDADSRETT_NotEnabled = docService.templateDisabledCriterion("ApprovDADSRETT", contrattoDC.getAlias());
        Criterion contrattoApprovDADSRETT2_NotEnabled = docService.templateDisabledCriterion("ApprovDADSRETT2", contrattoDC.getAlias());
        Criterion contrattoGlobal = Restrictions.or(contrattoApprovDADSRETT_NotEnabled, Restrictions.and(contrattoApprovDADSRETT_NotEnabled, contrattoApprovDADSRETT2_NotEnabled));
        contrattoDC.add(contrattoGlobal);
        contrattoDC.setProjection(Projections.property("parent.id"));
        c.add(Subqueries.propertyIn("id", contrattoDC));
        return c;
    }

    public DetachedCriteria valutatiCeCriteria(IUser user) {
        Criteria centroTypeCriteria = docService.getDocTypeDAO().getCriteria();
        centroTypeCriteria.add(Restrictions.eq("typeId", "Centro"));
        centroTypeCriteria.add(Restrictions.eq("deleted", false));
        ElementType centroType = (ElementType) centroTypeCriteria.uniqueResult();
        /*
         Clausola di in su centri i cui figli di tipo ParereCE abbiano il campo "esitoParere" del template "ParereCe" like '%approvato%'
         */
        Criteria ParereCeTypeCriteria = docService.getDocTypeDAO().getCriteria();
        ParereCeTypeCriteria.add(Restrictions.eq("typeId", "ParereCe"));
        ElementType ParereCeType = (ElementType) ParereCeTypeCriteria.uniqueResult();
        DetachedCriteria ParereCeDC = DetachedCriteria.forClass(Element.class, "ParereCe");
        ParereCeDC.add(Restrictions.eq("type", ParereCeType));
        ParereCeDC.add(Restrictions.eq("deleted", false));
        ParereCeDC.setProjection(Projections.property("parent.id"));
        ParereCeDC.createAlias("ParereCe.data", "sqdata");
        ParereCeDC.createAlias("ParereCe.data.values", "sqdataValues");
        ParereCeDC.createAlias("ParereCe.data.template", "sqtemplate");
        ParereCeDC.createAlias("ParereCe.data.field", "sqfield");
        Criterion fieldNameCrit = Restrictions.eq("sqfield.name", "esitoParere");
        Criterion templateNameCrit = Restrictions.eq("sqtemplate.name", "ParereCe");
        ParereCeDC.add(fieldNameCrit);
        ParereCeDC.add(templateNameCrit);
        ParereCeDC.add(Restrictions.like("sqdataValues.textValue", "%approvato%").ignoreCase());

        /*
         Controllo che abbia un figlio di tipo "contratto" con
         template ApprovDADSRETT disabilitato o
          template ApprovDADSRETT2 disabilitato
         */
        Criteria contrattoTypeCriteria = docService.getDocTypeDAO().getCriteria();
        contrattoTypeCriteria.add(Restrictions.eq("typeId", "Contratto"));
        ElementType contrattoType = (ElementType) contrattoTypeCriteria.uniqueResult();
        DetachedCriteria contrattoDC = DetachedCriteria.forClass(Element.class, "contratto");
        contrattoDC.add(Restrictions.eq("type", contrattoType));
        contrattoDC.add(Restrictions.eq("deleted", false));
        contrattoDC.setProjection(Projections.property("parent.id"));
        Criterion contrattoApprovDADSRETT_NotEnabled = docService.templateDisabledCriterion("ApprovDADSRETT", contrattoDC.getAlias());
        Criterion contrattoApprovDADSRETT2_NotEnabled = docService.templateDisabledCriterion("ApprovDADSRETT2", contrattoDC.getAlias());
        Criterion contrattoGlobal1 = Restrictions.or(contrattoApprovDADSRETT_NotEnabled, Restrictions.and(contrattoApprovDADSRETT_NotEnabled, contrattoApprovDADSRETT2_NotEnabled));
        contrattoDC.add(contrattoGlobal1);
        /*
            Controllo che non abbia figli di tipo contratto
         */
        DetachedCriteria contrattoDC2 = DetachedCriteria.forClass(Element.class, "contratto2");
        contrattoDC2.add(Restrictions.eq("type", contrattoType));
        contrattoDC2.add(Restrictions.eq("deleted", false));
        contrattoDC2.setProjection(Projections.property("parent.id"));

        Criterion contrattoGlobal = Restrictions.or(
                Subqueries.propertyIn("id", contrattoDC),
                Subqueries.propertyNotIn("id", contrattoDC2)
        );

        DetachedCriteria c = docService.getViewableElementsCriteria(user, "root");
        c.add(Subqueries.propertyIn("id", ParereCeDC));
        c.add(contrattoGlobal);
        c.add(Restrictions.eq("root.type", centroType));
        return c;
    }

    public DetachedCriteria inValutazioneCeCriteria(IUser user) {
        /*
        Condizione 1
         */
        String templateName = "statoValidazioneCentro";
        String fieldName = "fattLocale";
        String value = "1";
        HashMap<String, Object> filter1 = new HashMap<String, Object>();
        filter1.put(templateName + "_" + fieldName + "_eq", value);

        /*
        Condizione 2
        campo ParereCe.esitoParere nullo oppure
        ParereCe.esitoParere like '%sospeso%'
         */

        Criteria ParereCeTypeCriteria = docService.getDocTypeDAO().getCriteria();
        ParereCeTypeCriteria.add(Restrictions.eq("typeId", "ParereCe"));
        ElementType ParereCeType = (ElementType) ParereCeTypeCriteria.uniqueResult();

        DetachedCriteria checkField1Criteria = DetachedCriteria.forClass(Element.class, "ds2");
        checkField1Criteria.add(Restrictions.eq("ds2.type", ParereCeType));
        checkField1Criteria.createAlias("ds2.data", "sds2data");
        checkField1Criteria.createAlias("ds2.data.values", "ds2dataValues");
        checkField1Criteria.createAlias("ds2.data.template", "ds2template");
        checkField1Criteria.createAlias("ds2.data.field", "ds2field");
        Criterion fieldName1Crit = Restrictions.eq("ds2field.name", "esitoParere");
        Criterion templateName1Crit = Restrictions.eq("ds2template.name", "ParereCe");
        checkField1Criteria.add(fieldName1Crit);
        checkField1Criteria.add(templateName1Crit);
        checkField1Criteria.add(Restrictions.isNotNull("ds2dataValues.textValue"));
        checkField1Criteria.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);
        checkField1Criteria.setProjection(Projections.property("ds2.id"));
        Criterion check2_1 = Subqueries.propertyNotIn("id", checkField1Criteria);

        DetachedCriteria checkField2Criteria = DetachedCriteria.forClass(Element.class, "ds3");
        checkField2Criteria.add(Restrictions.eq("ds3.type", ParereCeType));
        checkField2Criteria.add(Restrictions.eq("ds3.deleted", false));
        checkField2Criteria.createAlias("ds3.data", "ds3data");
        checkField2Criteria.createAlias("ds3.data.values", "ds3dataValues");
        checkField2Criteria.createAlias("ds3.data.template", "ds3template");
        checkField2Criteria.createAlias("ds3.data.field", "ds3field");
        Criterion fieldName2Crit = Restrictions.eq("ds3field.name", "esitoParere");
        Criterion templateName2Crit = Restrictions.eq("ds3template.name", "ParereCe");
        checkField2Criteria.add(fieldName2Crit);
        checkField2Criteria.add(templateName2Crit);
        checkField2Criteria.add(Restrictions.like("ds3dataValues.textValue", "%sospeso%").ignoreCase());
        checkField2Criteria.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);
        checkField2Criteria.setProjection(Projections.property("ds3.id"));
        Criterion check2_2 = Subqueries.propertyIn("id", checkField2Criteria);
        Criterion condizione2_ = Restrictions.or(check2_1, check2_2);

        DetachedCriteria maxIdListCriteria = DetachedCriteria.forClass(Element.class, "sq");
        ProjectionList proj = Projections.projectionList();
        proj.add(Projections.max("id"));
        proj.add(Projections.groupProperty("parent"));
        maxIdListCriteria.add(Restrictions.eq("sq.type", ParereCeType));
        maxIdListCriteria.setProjection(proj);
        maxIdListCriteria.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);

        DetachedCriteria condizione2Criteria = DetachedCriteria.forClass(Element.class, "ds");
        condizione2Criteria.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);
        condizione2Criteria.setProjection(Projections.property("parent.id"));
        condizione2Criteria.add(Restrictions.eq("ds.deleted", false));
        String[] ps = new String[2];
        ps[0] = "id";
        ps[1] = "parent";
        condizione2Criteria.add(Subqueries.propertiesIn(ps, maxIdListCriteria));
        condizione2Criteria.add(condizione2_);
        Criterion condizione2 = Subqueries.propertyIn("id", condizione2Criteria);
        /*
        Condizione 3
         */
        DetachedCriteria parereNotPresent = DetachedCriteria.forClass(Element.class);
        parereNotPresent.add(Restrictions.eq("type", ParereCeType));
        parereNotPresent.add(Restrictions.eq("deleted", false));
        parereNotPresent.setProjection(Projections.property("parent.id"));
        Criterion condizione3 = Subqueries.propertyNotIn("id", parereNotPresent);

        /* Condizione1 and (condizione2 or condizione3)*/

        /* applico condizione 1*/
        DetachedCriteria c = docService.advancedSearchCriteria(user, "Centro", filter1);
        /* condizione2 or condizione3 */
        Criterion condizione2Total = Restrictions.or(condizione2, condizione3);
        return c;
    }

    public DetachedCriteria inFatturazioneCriteria(IUser user) {
        DetachedCriteria c;
        if (user == null) {
            c = docService.getAllElementsCriteria("root");
        } else {
            c = docService.getViewableElementsCriteria(user, "root");
        }
        Criteria centroTypeCriteria = docService.getDocTypeDAO().getCriteria();
        centroTypeCriteria.add(Restrictions.eq("typeId", "Centro"));
        centroTypeCriteria.add(Restrictions.eq("deleted", false));
        Criteria fattTypeCriteria = docService.getDocTypeDAO().getCriteria();
        fattTypeCriteria.add(Restrictions.eq("typeId", "Fatturazione"));
        fattTypeCriteria.add(Restrictions.eq("deleted", false));
        ElementType centroType = (ElementType) centroTypeCriteria.uniqueResult();
        ElementType fattType = (ElementType) fattTypeCriteria.uniqueResult();
        c.add(Restrictions.eq("root.type", centroType));
        /*
        Controllo che ci sia almeno un figlio di tipo Fatturazione
         */
        DetachedCriteria check1Criteria = DetachedCriteria.forClass(Element.class, "ds");
        check1Criteria.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);
        check1Criteria.setProjection(Projections.property("ds.parent.id"));
        check1Criteria.add(Restrictions.eq("ds.type", fattType));
        check1Criteria.add(Restrictions.eq("ds.deleted", false));
        //check1Criteria.add(Restrictions.eq("ds.parent.id", "root.id"));
        Criterion check1 = Subqueries.propertyIn("root.id", check1Criteria);
        /*
        Controllo che il template DatiChiusuraWF sia disabilitato
         */
        Criterion check2 = docService.templateEnabledCriterion("DatiChiusuraWF", c.getAlias());
        /*
        Controllo che il template DatiChiusuraWF sia abilitato e dataChiusuraAmm sia nullo
         */
        DetachedCriteria checkFieldCriteria = DetachedCriteria.forClass(Element.class, "ds2");
        checkFieldCriteria.add(Restrictions.eq("ds2.type", centroType));
        centroTypeCriteria.add(Restrictions.eq("ds2.deleted", false));
        checkFieldCriteria.createAlias("ds2.data", "sds2data");
        checkFieldCriteria.createAlias("ds2.data.values", "ds2dataValues");
        checkFieldCriteria.createAlias("ds2.data.template", "ds2template");
        checkFieldCriteria.createAlias("ds2.data.field", "ds2field");
        Criterion fieldNameCrit = Restrictions.eq("ds2field.name", "dataChiusuraAmm");
        Criterion templateNameCrit = Restrictions.eq("ds2template.name", "DatiChiusuraWF");
        checkFieldCriteria.add(fieldNameCrit);
        checkFieldCriteria.add(templateNameCrit);
        checkFieldCriteria.add(Restrictions.isNotNull("ds2dataValues.date"));
        checkFieldCriteria.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);
        checkFieldCriteria.setProjection(Projections.property("ds2.id"));
        Criterion check3 = Subqueries.propertyNotIn("id", checkFieldCriteria);

        /*
        Utilizzo solo la clausola 3
         */
        c.add(check1);
        c.add(Restrictions.or(check2, check3));
        c.addOrder(Order.desc("root.creationDt"));
        return c;

    }


    @RequestMapping(value = "/rest/ctc/budget", method = RequestMethod.GET)
    public
    @ResponseBody
    JqGridJSON budgetController(HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Enumeration paramNames = request.getParameterNames();
        int page = 1;
        int limit = 5;
        while (paramNames.hasMoreElements()) {
            String paramName = (String) paramNames.nextElement();
            if (paramName.equalsIgnoreCase("page") || paramName.equalsIgnoreCase("rows") || paramName.equalsIgnoreCase("sidx") || paramName.equalsIgnoreCase("sord")) {
                if (paramName.equalsIgnoreCase("page")) {
                    page = Integer.parseInt(request.getParameter(paramName));
                }
                if (paramName.equalsIgnoreCase("rows")) {
                    limit = Integer.parseInt(request.getParameter(paramName));
                }
            }
        }
        JqGridJSON res = new JqGridJSON();
        int start = (page - 1) * limit;
        int total;
        DetachedCriteria c = statoBudgetCriteria(user);
        c.setProjection(Projections.countDistinct("id"));
        total = ((Long) docService.getDocTypeDAO().getCriteriaUniqueResult(c)).intValue();
        res.setPage(page);
        res.setRows(limit);
        res.setTotal(total);
        List<Element> els = docService.getDocDAO().getFixedResultSize(c, start, limit, total);
        List<ElementJSON> ret = new LinkedList<ElementJSON>();
        for (Element el : els) {
            ret.add(new ElementJSON(el, user, "single"));
        }
        res.setRoot(ret);
        return res;
    }

    @RequestMapping(value = "/rest/ctc/budgetCount", method = RequestMethod.GET)
    public
    @ResponseBody
    Long budgetControllerCount(HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        DetachedCriteria c = statoBudgetCriteria(user);
        c.setProjection(Projections.countDistinct("id"));
        Long resultCount = (Long) docService.getDocDAO().getCriteriaUniqueResult(c);
        return resultCount;
    }


    @RequestMapping(value = "/rest/ctc/contratto", method = RequestMethod.GET)
    public
    @ResponseBody
    JqGridJSON contrattoController(HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Enumeration paramNames = request.getParameterNames();
        int page = 1;
        int limit = 5;
        while (paramNames.hasMoreElements()) {
            String paramName = (String) paramNames.nextElement();
            if (paramName.equalsIgnoreCase("page") || paramName.equalsIgnoreCase("rows") || paramName.equalsIgnoreCase("sidx") || paramName.equalsIgnoreCase("sord")) {
                if (paramName.equalsIgnoreCase("page")) {
                    page = Integer.parseInt(request.getParameter(paramName));
                }
                if (paramName.equalsIgnoreCase("rows")) {
                    limit = Integer.parseInt(request.getParameter(paramName));
                }
            }
        }
        JqGridJSON res = new JqGridJSON();
        int start = (page - 1) * limit;
        int total;
        DetachedCriteria c = contrattoCriteria(user);
        c.setProjection(Projections.countDistinct("id"));
        total = ((Long) docService.getDocTypeDAO().getCriteriaUniqueResult(c)).intValue();
        res.setPage(page);
        res.setRows(limit);
        res.setTotal(total);
        List<Element> els = docService.getDocDAO().getFixedResultSize(c, start, limit, total);
        List<ElementJSON> ret = new LinkedList<ElementJSON>();
        for (Element el : els) {
            ret.add(new ElementJSON(el, user, "single"));
        }
        res.setRoot(ret);
        return res;
    }

    @RequestMapping(value = "/rest/ctc/contrattoCount", method = RequestMethod.GET)
    public
    @ResponseBody
    Long contrattoControllerCount(HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        DetachedCriteria c = contrattoCriteria(user);
        c.setProjection(Projections.countDistinct("id"));
        Long resultCount = (Long) docService.getDocDAO().getCriteriaUniqueResult(c);
        return resultCount;
    }

    @RequestMapping(value = "/rest/ctc/valutatiCe", method = RequestMethod.GET)
    public
    @ResponseBody
    JqGridJSON valutatiCeController(HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Enumeration paramNames = request.getParameterNames();
        int page = 1;
        int limit = 5;
        while (paramNames.hasMoreElements()) {
            String paramName = (String) paramNames.nextElement();
            if (paramName.equalsIgnoreCase("page") || paramName.equalsIgnoreCase("rows") || paramName.equalsIgnoreCase("sidx") || paramName.equalsIgnoreCase("sord")) {
                if (paramName.equalsIgnoreCase("page")) {
                    page = Integer.parseInt(request.getParameter(paramName));
                }
                if (paramName.equalsIgnoreCase("rows")) {
                    limit = Integer.parseInt(request.getParameter(paramName));
                }
            }
        }
        JqGridJSON res = new JqGridJSON();
        int start = (page - 1) * limit;
        int total;
        DetachedCriteria c = valutatiCeCriteria(user);
        c.setProjection(Projections.countDistinct("id"));
        total = ((Long) docService.getDocTypeDAO().getCriteriaUniqueResult(c)).intValue();
        res.setPage(page);
        res.setRows(limit);
        res.setTotal(total);
        List<Element> els = docService.getDocDAO().getFixedResultSize(c, start, limit, total);
        List<ElementJSON> ret = new LinkedList<ElementJSON>();
        for (Element el : els) {
            ret.add(new ElementJSON(el, user, "single"));
        }
        res.setRoot(ret);
        return res;
    }

    @RequestMapping(value = "/rest/ctc/valutatiCeCount", method = RequestMethod.GET)
    public
    @ResponseBody
    Long valutatiCeControllerCount(HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        DetachedCriteria c = valutatiCeCriteria(user);
        c.setProjection(Projections.countDistinct("id"));
        Long resultCount = (Long) docService.getDocDAO().getCriteriaUniqueResult(c);
        return resultCount;
    }

    @RequestMapping(value = "/rest/ctc/inValutazioneCe", method = RequestMethod.GET)
    public
    @ResponseBody
    JqGridJSON inValutazioneCeController(HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Enumeration paramNames = request.getParameterNames();
        int page = 1;
        int limit = 5;
        while (paramNames.hasMoreElements()) {
            String paramName = (String) paramNames.nextElement();
            if (paramName.equalsIgnoreCase("page") || paramName.equalsIgnoreCase("rows") || paramName.equalsIgnoreCase("sidx") || paramName.equalsIgnoreCase("sord")) {
                if (paramName.equalsIgnoreCase("page")) {
                    page = Integer.parseInt(request.getParameter(paramName));
                }
                if (paramName.equalsIgnoreCase("rows")) {
                    limit = Integer.parseInt(request.getParameter(paramName));
                }
            }
        }
        JqGridJSON res = new JqGridJSON();
        int start = (page - 1) * limit;
        int total;
        DetachedCriteria c = inValutazioneCeCriteria(user);
        c.setProjection(Projections.countDistinct("id"));
        total = ((Long) docService.getDocTypeDAO().getCriteriaUniqueResult(c)).intValue();
        res.setPage(page);
        res.setRows(limit);
        res.setTotal(total);
        List<Element> els = docService.getDocDAO().getFixedResultSize(c, start, limit, total);
        List<ElementJSON> ret = new LinkedList<ElementJSON>();
        for (Element el : els) {
            ElementJSON elJson = new ElementJSON(el, user, "single");
            Long maxIdParere = new Long(0);
            Element lastParere = null;
            List<Element> pareri = el.getChildrenByType("ParereCe");
            for (Element parere : pareri) {
                if (parere.getId() > maxIdParere) lastParere = parere;
            }
            if (lastParere != null) {
                if (lastParere.getFieldDataString("ParereCe", "esitoParere") != null && !lastParere.getFieldDataString("ParereCe", "esitoParere").isEmpty()) {
                    elJson.pushMetadata("dataVal", lastParere.getFieldDataDates("parereCe", "dataParere").toArray());
                } else {
                    elJson.pushMetadata("dataVal", el.getFieldDataDecodes("DatiCentro", "CeDt").toArray());
                }
            } else {
                elJson.pushMetadata("dataVal", el.getFieldDataDecodes("DatiCentro", "CeDt").toArray());
            }
            ret.add(elJson);
        }
        res.setRoot(ret);
        return res;
    }

    @RequestMapping(value = "/rest/ctc/inValutazioneCeCount", method = RequestMethod.GET)
    public
    @ResponseBody
    Long inValutazioneCeControllerCount(HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        DetachedCriteria c = inValutazioneCeCriteria(user);
        c.setProjection(Projections.countDistinct("id"));
        Long resultCount = (Long) docService.getDocDAO().getCriteriaUniqueResult(c);
        return resultCount;
    }

    @RequestMapping(value = "/rest/ctc/inFatturazione", method = RequestMethod.GET)
    public
    @ResponseBody
    JqGridJSON inFatturazioneController(HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Enumeration paramNames = request.getParameterNames();
        int page = 1;
        int limit = 5;
        while (paramNames.hasMoreElements()) {
            String paramName = (String) paramNames.nextElement();
            if (paramName.equalsIgnoreCase("page") || paramName.equalsIgnoreCase("rows") || paramName.equalsIgnoreCase("sidx") || paramName.equalsIgnoreCase("sord")) {
                if (paramName.equalsIgnoreCase("page")) {
                    page = Integer.parseInt(request.getParameter(paramName));
                }
                if (paramName.equalsIgnoreCase("rows")) {
                    limit = Integer.parseInt(request.getParameter(paramName));
                }
            }
        }
        JqGridJSON res = new JqGridJSON();
        int start = (page - 1) * limit;
        int total;
        DetachedCriteria c = inFatturazioneCriteria(user);
        c.setProjection(Projections.countDistinct("id"));
        total = ((Long) docService.getDocTypeDAO().getCriteriaUniqueResult(c)).intValue();
        res.setPage(page);
        res.setRows(limit);
        res.setTotal(total);
        List<Element> els = docService.getDocDAO().getFixedResultSize(c, start, limit, total);
        List<ElementJSON> ret = new LinkedList<ElementJSON>();
        for (Element el : els) {
            ret.add(new ElementJSON(el, user, "single"));
        }
        res.setRoot(ret);
        return res;
    }

    @RequestMapping(value = "/rest/ctc/inFatturazioneCount", method = RequestMethod.GET)
    public
    @ResponseBody
    Long inFatturazioneControllerCount(HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        DetachedCriteria c = inFatturazioneCriteria(user);
        c.setProjection(Projections.countDistinct("id"));
        Long resultCount = (Long) docService.getDocDAO().getCriteriaUniqueResult(c);
        return resultCount;
    }

    public DetachedCriteria inMonitoraggioCriteria(IUser user) {
        DetachedCriteria c;
        if (user == null) {
            c = docService.getAllElementsCriteria("root");
        } else {
            c = docService.getViewableElementsCriteria(user, "root");
        }

        Criteria centroTypeCriteria = docService.getDocTypeDAO().getCriteria();
        centroTypeCriteria.add(Restrictions.eq("typeId", "Centro"));
        centroTypeCriteria.add(Restrictions.eq("deleted", false));
        ElementType centroType = (ElementType) centroTypeCriteria.uniqueResult();
        /*
         Il figlio di centro di tipo ArruolamentoPrimoPaz deve avere il campo "dataAperturaCentro" del template "DatiArrPrimoPaz" valorizzato
         */
        Criteria monTypeCriteria = docService.getDocTypeDAO().getCriteria();
        monTypeCriteria.add(Restrictions.eq("typeId", "ArruolamentoPrimoPaz"));
        monTypeCriteria.add(Restrictions.eq("deleted", false));
        ElementType arrPrimoPazType = (ElementType) monTypeCriteria.uniqueResult();
        DetachedCriteria ArrPrimoPazDC = DetachedCriteria.forClass(Element.class, "APP");
        ArrPrimoPazDC.add(Restrictions.eq("type", arrPrimoPazType));
        ArrPrimoPazDC.add(Restrictions.eq("deleted", false));
        ArrPrimoPazDC.setProjection(Projections.property("parent.id"));
        ArrPrimoPazDC.createAlias("APP.data", "sqdata");
        ArrPrimoPazDC.createAlias("APP.data.values", "sqdataValues");
        ArrPrimoPazDC.createAlias("APP.data.template", "sqtemplate");
        ArrPrimoPazDC.createAlias("APP.data.field", "sqfield");
        Criterion fieldNameCrit = Restrictions.eq("sqfield.name", "dataAperturaCentro");
        Criterion templateNameCrit = Restrictions.eq("sqtemplate.name", "DatiArrPrimoPaz");
        ArrPrimoPazDC.add(fieldNameCrit);
        ArrPrimoPazDC.add(templateNameCrit);
        ArrPrimoPazDC.add(Restrictions.isNotNull("sqdataValues.date"));
        Criterion check1 = Subqueries.propertyIn("id", ArrPrimoPazDC);

        /*
        Controllo che il template DatiChiusuraWF sia abilitato e dataChiusuraAmm sia nullo
         */
        DetachedCriteria checkFieldCriteria = DetachedCriteria.forClass(Element.class, "ds2");
        checkFieldCriteria.add(Restrictions.eq("ds2.type", centroType));
        centroTypeCriteria.add(Restrictions.eq("ds2.deleted", false));
        checkFieldCriteria.createAlias("ds2.data", "sds2data");
        checkFieldCriteria.createAlias("ds2.data.values", "ds2dataValues");
        checkFieldCriteria.createAlias("ds2.data.template", "ds2template");
        checkFieldCriteria.createAlias("ds2.data.field", "ds2field");
        Criterion fieldNameCrit1 = Restrictions.eq("ds2field.name", "dataChiusuraAmm");
        Criterion templateNameCrit1 = Restrictions.eq("ds2template.name", "DatiChiusuraWF");
        checkFieldCriteria.add(fieldNameCrit1);
        checkFieldCriteria.add(templateNameCrit1);
        checkFieldCriteria.add(Restrictions.isNotNull("ds2dataValues.date"));
        checkFieldCriteria.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);
        checkFieldCriteria.setProjection(Projections.property("ds2.id"));
        Criterion check2 = Subqueries.propertyNotIn("id", checkFieldCriteria);

        c.add(Restrictions.and(check1, check2));
        //c.add(check1);
        c.add(Restrictions.eq("root.type", centroType));
        //c.addOrder(Order.desc("root.creationDt"));
        return c;

    }

    @RequestMapping(value = "/rest/ctc/inMonitoraggio", method = RequestMethod.GET)
    public
    @ResponseBody
    JqGridJSON inMonitoraggioController(HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        Enumeration paramNames = request.getParameterNames();
        int page = 1;
        int limit = 5;
        Boolean hasOrder=false;
        while (paramNames.hasMoreElements()) {
            String paramName = (String) paramNames.nextElement();
            if(paramName.equals("sidx")){
                hasOrder=true;
            }
            if (paramName.equalsIgnoreCase("page") || paramName.equalsIgnoreCase("rows") || paramName.equalsIgnoreCase("sidx") || paramName.equalsIgnoreCase("sord")) {
                if (paramName.equalsIgnoreCase("page")) {
                    page = Integer.parseInt(request.getParameter(paramName));
                }
                if (paramName.equalsIgnoreCase("rows")) {
                    limit = Integer.parseInt(request.getParameter(paramName));
                }
            }
        }
        JqGridJSON res = new JqGridJSON();
        int start = (page - 1) * limit;
        int total;
        DetachedCriteria c = inMonitoraggioCriteria(user);
        String fieldOrder="";
        String orderType="";
        if(hasOrder){
            fieldOrder=request.getParameter("sidx");
            try {
                orderType = request.getParameter("sord");
            }catch (Exception ex){
                orderType = "desc";
            }
            if(orderType.isEmpty()){
                orderType = "desc";
            }
            docService.ordDetachedCriteria(c,fieldOrder,orderType);
        }else{
            c.addOrder(Order.desc("root.creationDt"));
        }
        c.setProjection(Projections.countDistinct("id"));
        total = ((Long) docService.getDocTypeDAO().getCriteriaUniqueResult(c)).intValue();
        res.setPage(page);
        res.setRows(limit);
        res.setTotal(total);
        List<Element> els = docService.getDocDAO().getFixedResultSize(c, start, limit, total);
        List<ElementJSON> ret = new LinkedList<ElementJSON>();
        for (Element el : els) {
            ret.add(new ElementJSON(el, user, "single"));
        }
        res.setRoot(ret);
        return res;
    }

    @RequestMapping(value = "/rest/ctc/inMonitoraggioCount", method = RequestMethod.GET)
    public
    @ResponseBody
    Long inMonitoraggioControllerCount(HttpServletRequest request) {
        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        DetachedCriteria c = inMonitoraggioCriteria(user);
        c.setProjection(Projections.countDistinct("id"));
        Long resultCount = (Long) docService.getDocDAO().getCriteriaUniqueResult(c);
        return resultCount;
    }

    @RequestMapping(value = "/rest/ctc/inserisciStudioFromCE", method = RequestMethod.GET)
    public
    @ResponseBody
    HashMap<String,String> inserisciStudioFromCE(HttpServletRequest request) {
        Enumeration paramNames = request.getParameterNames();
        String id_stud="";
        String visitnum_progr="";

        boolean retval=false;
        HashMap<String,String> returnVal=new HashMap<String, String>();
        while (paramNames.hasMoreElements()) {
            String paramName = (String) paramNames.nextElement();
            if (paramName.equalsIgnoreCase("id_stud") || paramName.equalsIgnoreCase("visitnum_progr")) {
                if (paramName.equalsIgnoreCase("id_stud")) {
                    id_stud = request.getParameter(paramName);
                }
                if (paramName.equalsIgnoreCase("visitnum_progr")) {
                    visitnum_progr = request.getParameter(paramName);
                }
            }
        }

        if(!id_stud.equals("")&&!visitnum_progr.equals("")) {
            try {
                retval = importCenterFromCE(id_stud, visitnum_progr);
            } catch (Exception e) {
                Logger.getLogger(this.getClass()).error(e.getMessage(), e);
            }
        }
        returnVal.put("status",String.valueOf(retval) );
        return returnVal;
    }

    /*TOSCANA-93 vmazzeo 14.02.2017*/
    public boolean importCenterFromCE(String id_stud, String visitnum_progr) throws RestException,SQLException {
        Connection conn = dataSource.getConnection();
        boolean retval = true;
        try {
            it.cineca.siss.axmr3.log.Log.warn(getClass(), "inizio importazione centro da CE " + id_stud + " " + visitnum_progr);

            String sql = "";
            String sql1 = "";
            boolean recordPresent = false;
            Long idCenter;
            String visitnum = "";
            String esam = "";
            String progr = "";
            String bodyMail = "";

            sql = "select * from centri_inviabili_al_crpms where id_stud=? and visitnum_progr=?";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setLong(1, Long.parseLong(id_stud));
            stmt.setLong(2, Long.parseLong(visitnum_progr));
            ResultSet rset = stmt.executeQuery();
            it.cineca.siss.axmr3.log.Log.warn(getClass(), "eseguita query: " + sql);
            Element ElementCentro = null;
            Long idElementStudio=null;
            Element ElementStudio=null;
            //TODO GESTIONE UTENTE: devo mettere un utente abilitato a
            String user = "SYSTEM";
            if (rset.next()) {
                String bodyMailPart = "";
                String labelBodyMail = "";

                id_stud = rset.getString("id_stud");
                String codice_prot=rset.getString("codice_prot");
                String titolo_prot=rset.getString("titolo_prot");
                String eudract_num=rset.getString("eudract_num");
                user=rset.getString("cto_crms");
                it.cineca.siss.axmr3.log.Log.warn(getClass(), "CREO GLI OGGETTI CON UTENZA: "+user);


                it.cineca.siss.axmr3.log.Log.warn(getClass(), "CONTROLLO CHE LO STUDIO " + id_stud + " ESISTA");
                String sql_get_studio = "select * from crms_info_studio_centri where id=? or (codiceprot=? and titoloprot=? ";
                if(eudract_num!=null && !eudract_num.equals("NA")) {
                    sql_get_studio += " and  eudractnumber=? ";
                }
                sql_get_studio +=" )";
                PreparedStatement stmt_get_studio = conn.prepareStatement(sql_get_studio);
                stmt_get_studio.setString(1, id_stud);
                it.cineca.siss.axmr3.log.Log.warn(getClass(), "id_stud: " + id_stud);
                stmt_get_studio.setString(2, codice_prot);
                it.cineca.siss.axmr3.log.Log.warn(getClass(), "codice_prot: " + codice_prot);
                stmt_get_studio.setString(3, titolo_prot);
                it.cineca.siss.axmr3.log.Log.warn(getClass(), "titolo_prot: " + titolo_prot);
                if(eudract_num!=null &&!eudract_num.equals("NA")){
                    stmt_get_studio.setString(4, eudract_num);
                    it.cineca.siss.axmr3.log.Log.warn(getClass(), "eudract_num: " + eudract_num);
                }
                ResultSet rset_get_studio = stmt_get_studio.executeQuery();
                it.cineca.siss.axmr3.log.Log.warn(getClass(), "eseguita query: " + sql_get_studio);

                if(rset_get_studio.next()) {
                    idElementStudio = rset_get_studio.getLong("studio_id");
                    it.cineca.siss.axmr3.log.Log.warn(getClass(), "TROVATO STUDIO elementID: " + idElementStudio);
                    if (idElementStudio > 0) {
                        it.cineca.siss.axmr3.log.Log.warn(getClass(), "STUDIO GIA' ESISTENTE = " + idElementStudio);
                        ElementStudio = docService.getElement(idElementStudio);
                        //setto crpms_studio_progr per collegare lo studio al CE
                        sql1="update ce_registrazione set crpms_studio_progr=?, to_crpms=1 where visitnum=? and visitnum_progr=? and progr=? and esam=? and id_stud=?";
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"sql1 = "+sql1);
                        PreparedStatement stmt1 = conn.prepareStatement(sql1);
                        stmt1.setLong(1,idElementStudio);//crpms_studio_progr
                        stmt1.setLong(2,Long.parseLong("0"));//visitnum
                        stmt1.setLong(3,Long.parseLong("0"));//visitnum_progr
                        stmt1.setLong(4,Long.parseLong("1"));//progr
                        stmt1.setLong(5,Long.parseLong("0"));//esam
                        stmt1.setLong(6,Long.parseLong(id_stud));//id_stud
                        ResultSet rset1 = stmt1.executeQuery();
                    }
                }else {
                    it.cineca.siss.axmr3.log.Log.warn(getClass(), "STUDIO NON ESISTENTE");
                    HashMap<String, String> studio_data = new HashMap<String, String>();
                    studio_data.put("IDstudio_CodiceProt", rset.getString("codice_prot"));
                    studio_data.put("IDstudio_TitoloProt", rset.getString("titolo_prot"));
                    ElementType elType = docService.getDocDefinitionByName("Studio");
                    it.cineca.siss.axmr3.log.Log.warn(getClass(), "CREO OGGETTO DI TIPO "+ elType.toString());
                    ElementStudio = docService.saveElement(user, elType, studio_data, null, null, null, null, null, null, null, null);
                    idElementStudio = ElementStudio.getId();
                    it.cineca.siss.axmr3.log.Log.warn(getClass(), "CREATO OGGETTO = " + idElementStudio);
                    //docService.addMetadataValueActions(idElementStudio, "UniqueIdStudio",  "id", id_stud);


                    String Profit =  rset.getString("profit");
                    String dProfit =  rset.getString("d_profit");
                    String stringProfit = Profit+"###"+dProfit;
                    if(Profit==null || Profit.isEmpty()){
                        Profit = "";
                        dProfit = "";
                        stringProfit = "";
                    }


                    docService.addMetadataValueActions(idElementStudio,"datiStudio","Profit",stringProfit);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"aggiornato datiStudio_Profit= "+stringProfit);

                    String popolazioneStudio =  rset.getString("pediatrico");
                    String d_popolazioneStudio =  rset.getString("d_pediatrico");
                    String stringPopolazioneStudio = popolazioneStudio+"###"+d_popolazioneStudio;
                    if(popolazioneStudio==null || popolazioneStudio.isEmpty()){
                        popolazioneStudio = "";
                        d_popolazioneStudio = "";
                        stringPopolazioneStudio = "";
                    }


                    docService.addMetadataValueActions(idElementStudio,"datiStudio","popolazioneStudio",stringPopolazioneStudio);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"aggiornato datiStudio_popolazioneStudio= "+stringPopolazioneStudio);



                    String tipoSper="";
                    tipoSper= rset.getString("tipo_sper");
                    if(tipoSper==null || tipoSper.isEmpty()) tipoSper="";
                    String tipoSperDec = rset.getString("d_tipo_sper");
                    if(tipoSperDec==null || tipoSperDec.isEmpty()) tipoSperDec="";
                    String stringTipoSper= tipoSper+"###"+tipoSperDec;
                    if(!stringTipoSper.equals("###")) {
                        docService.addMetadataValueActions(idElementStudio, "datiStudio", "tipoStudio", stringTipoSper);
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "aggiornato datiStudio_tipoStudio= " + stringTipoSper);
                    }
                    if(tipoSper.equals("1") || tipoSper.equals("3")){
                        String Fase =  rset.getString("fase_sper");
                        String dFase =  rset.getString("d_fase_sper");
                        String stringFase= Fase+"###"+dFase;
                        docService.addMetadataValueActions(idElementStudio,"datiStudio","fase",stringFase);
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"aggiornato datiStudio_fase= "+stringFase);

                        String eudractNumber = rset.getString("eudract_num");
                        if(eudractNumber==null || eudractNumber.isEmpty()) eudractNumber="";
                        docService.addMetadataValueActions(idElementStudio,"datiStudio","eudractNumber",eudractNumber);
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"aggiornato datiStudio_eudractNumber= "+eudractNumber);

                    }


                    String FonteFinTerzi = rset.getString("fonte_fin_terzi");
                    if(FonteFinTerzi==null || FonteFinTerzi.isEmpty()) FonteFinTerzi="";
                        String FonteFinTerziDec = rset.getString("d_fonte_fin_terzi");
                    if(FonteFinTerziDec==null || FonteFinTerziDec.isEmpty()) FonteFinTerziDec="";
                    String stringFonteFinTerzi= FonteFinTerzi+"###"+FonteFinTerziDec;
                    if(!stringFonteFinTerzi.equals("###")) {
                        docService.addMetadataValueActions(idElementStudio, "datiStudio", "fonteFinTerzi", stringFonteFinTerzi);
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "aggiornato datiStudio_fonteFinTerzi= " + stringFonteFinTerzi);
                    }

                    String fonteFinSpec = rset.getString("fonte_fin_spec");
                    if(fonteFinSpec==null || fonteFinSpec.isEmpty()) fonteFinSpec="";
                    String fonteFinSpecDec = rset.getString("d_fonte_fin_spec");
                    if(fonteFinSpecDec==null || fonteFinSpecDec.isEmpty()) fonteFinSpecDec="";
                    String stringFonteFinSpec= fonteFinSpec+"###"+fonteFinSpecDec;
                    if(!stringFonteFinSpec.equals("###")) {
                        docService.addMetadataValueActions(idElementStudio, "datiStudio", "fonteFinSpec", stringFonteFinSpec);
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "aggiornato datiStudio_fonteFinSpec= " + stringFonteFinSpec);
                    }

                    String fonteFinSponsor = rset.getString("fonte_fin_id_sponsor");
                    if(fonteFinSponsor==null || fonteFinSponsor.isEmpty()) fonteFinSponsor="";
                    String fonteFinSponsorDec = rset.getString("fonte_fin_sponsor");
                    if(fonteFinSponsorDec==null || fonteFinSponsorDec.isEmpty()) fonteFinSponsorDec="";
                    String stringFonteFinSponsor= fonteFinSponsor+"###"+fonteFinSponsorDec;
                    if(!stringFonteFinSponsor.equals("###")) {
                        docService.addMetadataValueActions(idElementStudio, "datiStudio", "fonteFinSponsor", stringFonteFinSponsor);
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "aggiornato datiStudio_fonteFinSponsor= " + stringFonteFinSponsor);
                    }

                    String fonteFinFondazione = rset.getString("fonte_fin_fondazione");
                    if(fonteFinFondazione==null || fonteFinFondazione.isEmpty()) fonteFinFondazione="";
                    String stringFonteFinFondazione= fonteFinFondazione;
                    if(!stringFonteFinFondazione.equals("###")) {
                        docService.addMetadataValueActions(idElementStudio, "datiStudio", "fonteFinFondazione", stringFonteFinFondazione);
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "aggiornato datiStudio_fonteFinFondazione= " + stringFonteFinFondazione);
                    }

                    String fonteFinAltro = rset.getString("fonte_fin_altro");
                    if(fonteFinAltro==null || fonteFinAltro.isEmpty()) fonteFinAltro="";
                    String stringFonteFinAltro= fonteFinAltro;
                    docService.addMetadataValueActions(idElementStudio,"datiStudio","fonteFinAltro",stringFonteFinAltro);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"aggiornato datiStudio_fonteFinAltro= "+stringFonteFinAltro);


                    String durata = rset.getString("dur_sper");
                    if(durata==null || durata.isEmpty()) durata="";
                    docService.addMetadataValueActions(idElementStudio,"datiStudio","durataTot",durata);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"aggiornato datiStudio_durataTot= "+durata);

                    String durataUnit=rset.getString("dur_sper_unit");
                    String durataUnitDec=rset.getString("d_dur_sper_unit");
                    String stringdurataUnit=durataUnit+"###"+durataUnitDec;
                    if(durataUnit==null || durataUnit.isEmpty() || durataUnit.equals("")){
                        durataUnit="";
                        durataUnitDec="";
                        stringdurataUnit="";
                    }
                    if(!stringdurataUnit.equals("###")) {
                        docService.addMetadataValueActions(idElementStudio, "datiStudio", "durataTotSelect", stringdurataUnit);
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "aggiornato datiStudio_durataTotSelect= " + stringdurataUnit);
                    }


                    //Sponsor
                    String sponsor=rset.getString("id_sponsor");
                    String sponsorDec=rset.getString("descr_sponsor");
                    if(sponsor==null || sponsor.isEmpty()) {
                        sponsor="";
                        sponsorDec="";
                    }
                    if(!sponsor.equals("")) {
                        String idSp = "";
                        HashMap<String, Object> data = new HashMap<String, Object>();
                        data.put("DatiPromotoreCRO_id", sponsor);
                        List<Element> risSp = docService.searchByExample("Promotore", data);
                        idSp = risSp.get(0).getId().toString();
                        docService.addMetadataValueActions(idElementStudio, "datiPromotore", "promotore", idSp);
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "aggiornato datiPromotore_promotore= " + idSp + "(" + sponsor + " " + sponsorDec + ")");
                    }

                    String RefNomeCognomepR=rset.getString("ref_sponsor");
                    if(RefNomeCognomepR==null || RefNomeCognomepR.isEmpty()) RefNomeCognomepR="";
                    docService.addMetadataValueActions(idElementStudio,"datiPromotore","RefNomeCognomepR",RefNomeCognomepR);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"aggiornato datiPromotore_RefNomeCognomepR= "+RefNomeCognomepR);

                    String RefEmailpR=rset.getString("email_sponsor");
                    if(RefEmailpR==null || RefEmailpR.isEmpty()) RefEmailpR="";
                    docService.addMetadataValueActions(idElementStudio,"datiPromotore","RefEmailpR",RefEmailpR);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"aggiornato datiPromotore_RefEmailpR= "+RefEmailpR);


                    String RefTelpR=rset.getString("tel_sponsor");
                    if(RefTelpR==null || RefTelpR.isEmpty()) RefTelpR="";
                    docService.addMetadataValueActions(idElementStudio,"datiPromotore","RefTelpR",RefTelpR);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"aggiornato datiPromotore_RefTelpR= "+RefTelpR);


                    //CRO
                    String cro=rset.getString("id_cro");
                    String croDec=rset.getString("descr_cro");
                    if(cro==null || cro.isEmpty()) {
                        cro="";
                        croDec="";
                    }
                    if(!cro.equals("")) {
                        String idCro ="";
                        HashMap<String, Object>
                        data = new HashMap<String, Object>();
                        data.put("DatiPromotoreCRO_id",cro);
                        List<Element> risCro = docService.searchByExample("CRO", data);
                        idCro = risCro.get(0).getId().toString();
                        docService.addMetadataValueActions(idElementStudio, "datiCRO", "denominazione", idCro);
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"aggiornato datiCRO_denominazione= "+idCro+" ("+cro+" "+croDec+")");
                    }
                    String NomeReferenteR=rset.getString("ref_cro");
                    if(NomeReferenteR==null || NomeReferenteR.isEmpty()) NomeReferenteR="";

                    docService.addMetadataValueActions(idElementStudio,"datiCRO","NomeReferenteR",NomeReferenteR);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"aggiornato datiCRO_NomeReferenteR= "+NomeReferenteR);

                    String telefonoR=rset.getString("tel_cro");
                    if(telefonoR==null || telefonoR.isEmpty()) telefonoR="";
                    docService.addMetadataValueActions(idElementStudio,"datiCRO","telefonoR",telefonoR);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"aggiornato datiCRO_telefonoR= "+telefonoR);


                    String emailR=rset.getString("email_cro");
                    if(emailR==null || emailR.isEmpty()) emailR="";
                    docService.addMetadataValueActions(idElementStudio,"datiCRO","emailR",emailR);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"aggiornato datiCRO_emailR= "+emailR);


                    //CARICO DOCUMENTI GENERALI STUDIO
                    String sql_get_doc_studio = "SELECT c.doc_core,d.ext, d.nome_file, c.userid_ins, c.d_doc_gen, c.doc_vers, NVL(TO_CHAR(c.doc_dt,'DD/MM/YYYY'),TO_CHAR(sysdate,'DD/MM/YYYY')) AS doc_dt, c.descr_agg, dgen.code||'###'||dgen.decode as docgenerali_docgen FROM ce_documentazione c, docs d, crms_doc_gen dgen WHERE id_stud=? AND d.id=c.doc_core AND c.doc_gen=dgen.id_doc_ce AND c.doc_gen in (4,5)";
                    PreparedStatement stmt_get_doc_studio = conn.prepareStatement(sql_get_doc_studio);
                    stmt_get_doc_studio.setString(1, id_stud);
                    ResultSet rset_get_doc_studio = stmt_get_doc_studio.executeQuery();
                    it.cineca.siss.axmr3.log.Log.warn(getClass(), "eseguita query: " + sql_get_doc_studio);
                    String doc_core="";
                    String ext="";
                    String nome_file="";
                    Path path ;
                    String fileCeOnline="";
                    String versione="";
                    String data="";
                    Element ElementAllegato;
                    ElementType elDocType = docService.getDocDefinitionByName("allegato");
                    HashMap<String, String> doc_data = new HashMap<String, String>();
                    Long idAllegato;

                    while(rset_get_doc_studio.next()) {
                        doc_data = new HashMap<String, String>();
                        doc_data.put("DocGenerali_DocGen", rset_get_doc_studio.getString("docgenerali_docgen"));
                        nome_file=rset_get_doc_studio.getString("NOME_FILE");
                        doc_core=rset_get_doc_studio.getString("DOC_CORE");
                        ext=rset_get_doc_studio.getString("EXT");
                        fileCeOnline = "Doc_Area" + doc_core + "." + ext;
                        versione=rset_get_doc_studio.getString("DOC_VERS");
                        data=rset_get_doc_studio.getString("DOC_DT");
                        path = Paths.get("/http/servizi/siss-bundle-01/ricercaclinica-toscana.cineca.it/html/uxmr/WCA/docs/"+fileCeOnline);
                        byte[] file_data = Files.readAllBytes(path);

                        ElementAllegato = docService.saveElement(user, elDocType, doc_data, file_data, nome_file, new Long(file_data.length), versione, data, "", "", ElementStudio);
                        idAllegato=ElementAllegato.getId();
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"CREATO allegato= "+idAllegato);




                    }

                    //TOSCANA-213 CARICO FARMACI

                    if(tipoSper.equals("1") || tipoSper.equals("5")){ //inserisco figli Farmaco
                        Element ElementFarmaco;
                        ElementType elFarmacoType=docService.getDocDefinitionByName("Farmaco");
                        HashMap<String,String> farmaco_data=new HashMap<String, String>();
                        Long idFarmaco;
                        String tabellaCE="ce_farmaco";
                        String cosaCercoInCE="id_stud,princ_att, categoria,d_categoria,sostanza,cod_princ_att,atc,datc,auto_itaai,d_auto_itaai,specialita,aic,confezione";
                        if(tipoSper.equals("5")){
                            tabellaCE+="os";
                            cosaCercoInCE="id_stud,princ_att, categoria,d_categoria,null as sostanza, cod_princ_att,atc,datc"; //per tipo=5 non ho sostanza tra i campi
                        }
                        String sql_get_farmaci="select "+cosaCercoInCE+" from "+tabellaCE+" where id_stud=?";
                        PreparedStatement stmt_get_farmaci = conn.prepareStatement(sql_get_farmaci);
                        stmt_get_farmaci.setString(1, id_stud);
                        ResultSet rset_get_farmaci = stmt_get_farmaci.executeQuery();
                        it.cineca.siss.axmr3.log.Log.warn(getClass(), "eseguita query: " + sql_get_farmaci);
                        String Farmaco_testOcomparatore="";
                        String Farmaco_princAtt="";
                        String Farmaco_princAttAltro="";
                        String sql_princ_att_code="select distinct sostanza,dsost from farmaci_bduf.farmaci_sfoglia where UPPER(dsost) like upper(?) ";
                        PreparedStatement stmt_princ_att_code;
                        ResultSet rset_princ_att_code;
                        while(rset_get_farmaci.next()) {
                            stmt_princ_att_code=null;
                            Farmaco_princAtt="";
                            Farmaco_princAttAltro="";
                            Farmaco_testOcomparatore="";
                            farmaco_data=new HashMap<String, String>();
                            it.cineca.siss.axmr3.log.Log.warn(getClass(), "farmaco_data: " );
                            farmaco_data.put("Farmaco_tipo","1###Farmaco");
                            it.cineca.siss.axmr3.log.Log.warn(getClass(), "\t\tput Farmaco_tipo: 1###Farmaco ");
                            farmaco_data.put("Farmaco_categoria","1###IMP");
                            it.cineca.siss.axmr3.log.Log.warn(getClass(), "\t\tput Farmaco_categoria: 1###IMP");
                            Farmaco_testOcomparatore=rset_get_farmaci.getString("categoria")+"###"+rset_get_farmaci.getString("d_categoria");
                            farmaco_data.put("Farmaco_testOcomparatore",Farmaco_testOcomparatore);
                            it.cineca.siss.axmr3.log.Log.warn(getClass(), "\t\tput Farmaco_testOcomparatore: "+Farmaco_testOcomparatore);
                            if(rset_get_farmaci.getString("princ_att")!=null){ //se ho il principio attivo allora cerco la relativa decodce in farmaci_bduf.farmaci_sfoglia
                                stmt_princ_att_code = conn.prepareStatement(sql_princ_att_code);
                                stmt_princ_att_code.setString(1, rset_get_farmaci.getString("princ_att"));
                                rset_princ_att_code = stmt_princ_att_code.executeQuery();
                                if(rset_princ_att_code.next()){
                                    Farmaco_princAtt=rset_princ_att_code.getString("sostanza")+"###"+rset_get_farmaci.getString("princ_att");
                                }
                                else{
                                    Farmaco_princAtt="-9999###Non disponibile";
                                    Farmaco_princAttAltro=rset_get_farmaci.getString("princ_att");
                                }
                            }
                            else if(rset_get_farmaci.getString("sostanza")!=null){ //se ho la sostanza allora metto princAtt=-9999#Non disponibile e princAttAltro=sostanza
                                Farmaco_princAtt="-9999###Non disponibile";
                                Farmaco_princAttAltro=rset_get_farmaci.getString("sostanza");
                            }
                            else{ //prendo il datc
                                Farmaco_princAtt="-9999###Non disponibile";
                                Farmaco_princAttAltro=rset_get_farmaci.getString("datc");
                            }
                            farmaco_data.put("Farmaco_princAtt",Farmaco_princAtt);
                            it.cineca.siss.axmr3.log.Log.warn(getClass(), "\t\tput Farmaco_princAtt: "+Farmaco_princAtt);
                            if(Farmaco_princAttAltro!="") {
                                farmaco_data.put("Farmaco_princAttAltro", Farmaco_princAttAltro);
                                it.cineca.siss.axmr3.log.Log.warn(getClass(), "\t\tput Farmaco_princAttAltro: "+Farmaco_princAttAltro);
                            }

                            //TOSCANA-228 TOSCANA-238 inizio
                            if(rset_get_farmaci.getString("auto_itaai")!=null && rset_get_farmaci.getString("d_auto_itaai")!=null) {
                                farmaco_data.put("Farmaco_AIC", rset_get_farmaci.getString("auto_itaai") + "###" + rset_get_farmaci.getString("d_auto_itaai").replace("Si'", "Si"));
                            }
                            if(rset_get_farmaci.getString("specialita")!=null) {
                                farmaco_data.put("Farmaco_SpecialitaAIC", rset_get_farmaci.getString("specialita"));
                            }
                            if(rset_get_farmaci.getString("aic")!=null) {
                                farmaco_data.put("Farmaco_CodiceAIC", rset_get_farmaci.getString("aic"));
                            }
                            if(rset_get_farmaci.getString("confezione")!=null) {
                                farmaco_data.put("Farmaco_ConfezioneAIC", rset_get_farmaci.getString("confezione"));
                            }
                            if(rset_get_farmaci.getString("atc")!=null) {
                                farmaco_data.put("Farmaco_CodiceATC", rset_get_farmaci.getString("atc"));
                            }
                            //TOSCANA-228 TOSCANA-238 fine

                            ElementFarmaco = docService.saveElement(user, elFarmacoType, farmaco_data, null, null, null, null, null, null, null, ElementStudio);
                            idFarmaco=ElementFarmaco.getId();
                            it.cineca.siss.axmr3.log.Log.warn(getClass(),"CREATO Farmaco= "+idFarmaco);
                        }


                    }
                    else if(tipoSper.equals("3") || tipoSper.equals("7")){ //inserisco figli Dispositivo
                        Element ElementFarmaco;
                        ElementType elFarmacoType=docService.getDocDefinitionByName("Farmaco");
                        HashMap<String,String> farmaco_data=new HashMap<String, String>();
                        Long idFarmaco;
                        String tabellaCE="ce_dispositivi";
                        String cosaCercoInCE="*";
                        if(tipoSper.equals("7")){
                            tabellaCE+="_os";
                        }
                        String sql_get_farmaci="select "+cosaCercoInCE+" from "+tabellaCE+" where id_stud=?";
                        PreparedStatement stmt_get_farmaci = conn.prepareStatement(sql_get_farmaci);
                        stmt_get_farmaci.setString(1, id_stud);
                        ResultSet rset_get_farmaci = stmt_get_farmaci.executeQuery();
                        it.cineca.siss.axmr3.log.Log.warn(getClass(), "eseguita query: " + sql_get_farmaci);
                        String Farmaco_princAtt="";
                        String Farmaco_princAttAltro="";
                        String sql_princ_att_code="select PROGRESSIVO_DM_ASS,DENOMINAZIONE_COMMERCIALE from DM where UPPER(DENOMINAZIONE_COMMERCIALE) like UPPER(?||'%') ";
                        PreparedStatement stmt_princ_att_code;
                        ResultSet rset_princ_att_code;
                        while(rset_get_farmaci.next()) {
                            stmt_princ_att_code=null;
                            Farmaco_princAtt="";
                            Farmaco_princAttAltro="";
                            farmaco_data=new HashMap<String, String>();
                            it.cineca.siss.axmr3.log.Log.warn(getClass(), "farmaco_data: " );
                            farmaco_data.put("Farmaco_tipo","2###Dispositivo medico");
                            it.cineca.siss.axmr3.log.Log.warn(getClass(), "\t\tput Farmaco_tipo: 2###Dispositivo medico ");
                            farmaco_data.put("Farmaco_categoriaDisp","1###Dispositivo Medico Sperimentale");
                            it.cineca.siss.axmr3.log.Log.warn(getClass(), "\t\tput Farmaco_categoriaDisp: 1###Dispositivo Medico Sperimentale ");
                            if(rset_get_farmaci.getString("dispositivo")!=null){ //se ho il nome del dispositivo allora cerco la relativa decode in dm
                                stmt_princ_att_code = conn.prepareStatement(sql_princ_att_code);
                                stmt_princ_att_code.setString(1, rset_get_farmaci.getString("dispositivo"));
                                rset_princ_att_code = stmt_princ_att_code.executeQuery();
                                if(rset_princ_att_code.next()){
                                    Farmaco_princAtt=rset_princ_att_code.getString("PROGRESSIVO_DM_ASS")+"###"+rset_princ_att_code.getString("DENOMINAZIONE_COMMERCIALE");
                                }
                                else{//se non trovo la decode metto non disponibile e compilo dispMedAltro
                                    Farmaco_princAtt="-9999###Non disponibile";
                                    Farmaco_princAttAltro=rset_get_farmaci.getString("dispositivo");
                                }
                            }
                            else{
                                Farmaco_princAtt="-9999###Non disponibile";
                                Farmaco_princAttAltro="";
                            }
                            farmaco_data.put("Farmaco_dispMed",Farmaco_princAtt);
                            it.cineca.siss.axmr3.log.Log.warn(getClass(), "\t\tput Farmaco_dispMed: "+Farmaco_princAtt);
                            if(Farmaco_princAttAltro!="") {
                                farmaco_data.put("Farmaco_dispMedAltro", Farmaco_princAttAltro);
                                it.cineca.siss.axmr3.log.Log.warn(getClass(), "\t\tput Farmaco_dispMedAltro: "+Farmaco_princAttAltro);
                            }

                            //TOSCANA-228 TOSCANA-238 inizio
                            if(rset_get_farmaci.getString("marchioce")!=null && rset_get_farmaci.getString("d_marchioce")!=null) {
                                farmaco_data.put("Farmaco_MarchioCE", rset_get_farmaci.getString("marchioce") + "###" + rset_get_farmaci.getString("d_marchioce").replace("Si'", "Si"));
                            }
                            if(rset_get_farmaci.getString("ditta_prod")!=null) {
                                farmaco_data.put("Farmaco_DittaProduttriceDisp", rset_get_farmaci.getString("ditta_prod"));
                            }
                            if(rset_get_farmaci.getString("classificazione_cnd")!=null) {
                                farmaco_data.put("Farmaco_classificCNDdisp", rset_get_farmaci.getString("classificazione_cnd"));
                            }
                            if(rset_get_farmaci.getString("descrizione_cnd")!=null) {
                                farmaco_data.put("Farmaco_descrCNDdisp", rset_get_farmaci.getString("descrizione_cnd"));
                            }
                            if(rset_get_farmaci.getString("numero_repertorio")!=null) {
                                farmaco_data.put("Farmaco_numeroRepertorioDisp", rset_get_farmaci.getString("numero_repertorio"));
                            }
                            //TOSCANA-228 TOSCANA-238 fine


                            ElementFarmaco = docService.saveElement(user, elFarmacoType, farmaco_data, null, null, null, null, null, null, null, ElementStudio);
                            idFarmaco=ElementFarmaco.getId();
                            it.cineca.siss.axmr3.log.Log.warn(getClass(),"CREATO Dispositivo= "+idFarmaco);
                        }


                    }





                    //setto crpms_studio_progr per collegare lo studio al CE
                    sql1="update ce_registrazione set crpms_studio_progr=?, to_crpms=1 where visitnum=? and visitnum_progr=? and progr=? and esam=? and id_stud=?";
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"sql1 = "+sql1);
                    PreparedStatement stmt1 = conn.prepareStatement(sql1);
                    stmt1.setLong(1,idElementStudio);//crpms_studio_progr
                    stmt1.setLong(2,Long.parseLong("0"));//visitnum
                    stmt1.setLong(3,Long.parseLong("0"));//visitnum_progr
                    stmt1.setLong(4,Long.parseLong("1"));//progr
                    stmt1.setLong(5,Long.parseLong("0"));//esam
                    stmt1.setLong(6,Long.parseLong(id_stud));//id_stud
                    ResultSet rset1 = stmt1.executeQuery();
                }

                /*ElementStudio=docService.getElement(idElementStudio);
                BaseDao<ElementMetadataValue> mdValDAO = docService.getElMdValueDAO();
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "CERCO UniqueIdStudio_id");
                for (ElementMetadata md:ElementStudio.getData()){
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "ho trovato " + md.getTemplateName()+"_"+md.getFieldName());
                    if(md.getFieldName().equals("id") && md.getTemplateName().equals("UniqueIdStudio")){
                        Iterator<ElementMetadataValue> md_iterator = md.getValues().iterator();
                        while(md_iterator.hasNext()){
                            ElementMetadataValue mdv=md_iterator.next();
                            mdv.setTextValue(id_stud);
                            mdValDAO.saveOrUpdate(mdv);
                            it.cineca.siss.axmr3.log.Log.debug(getClass(), "aggiornato UniqueIdStudio_id= " + id_stud);
                        }
                    }
                }*/



                HashMap<String,String> process_var=new HashMap<String, String>();
                process_var.put("uniqueId",id_stud);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Faccio partire processo per aggiornare UniqueIdStudio_id= " + id_stud);
                docService.startProcess("PROCESS",idElementStudio+"","updateUniqueIdStudio_id",process_var);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "aggiornato CON Processo UniqueIdStudio_id= " + ElementStudio.getId()+" ");

                ////INIZIO A CREARE IL CENTRO
                HashMap<String, String> centro_data = new HashMap<String, String>();


                String struttura=rset.getString("centro");
                String strutturaDec=rset.getString("d_centro");
                String stringStruttura=struttura+"###"+strutturaDec;
                if(struttura==null || struttura.isEmpty() || struttura.equals("")){
                    struttura="";
                    strutturaDec="";
                    stringStruttura="";
                }
                if(!stringStruttura.equals("")) {
                    centro_data.put("IdCentro_Struttura", stringStruttura);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "aggiunto IdCentro_Struttura= "+stringStruttura);
                }

                String uo=rset.getString("unita_op");
                String uoDec=rset.getString("d_unita_op");
                String stringUO=uo+"###"+uoDec;
                if(uo==null || uo.isEmpty() || uo.equals("")){
                    uo="";
                    uoDec="";
                    stringUO="";
                }
                if(!stringUO.equals("")) {
                    centro_data.put("IdCentro_UO", stringUO);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "aggiunto IdCentro_UO= "+stringUO);
                }

                String pi=rset.getString("princ_inv");
                String piDec=rset.getString("d_princ_inv");
                String stringPI=pi+"###"+piDec;
                if(pi==null || pi.isEmpty() || pi.equals("")){
                    pi="";
                    piDec="";
                    stringPI="";
                }
                if(!pi.equals("")) {
                    centro_data.put("IdCentro_PI", stringPI);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "aggiunto IdCentro_PI= "+stringPI);
                }
                String telefonoPI=rset.getString("tel_pi");
                if(telefonoPI==null || telefonoPI.isEmpty()) telefonoPI="";
                centro_data.put("IdCentro_telefonoPI", telefonoPI);
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"aggiunto IdCentro_telefonoPI= "+telefonoPI);

                String emailPI=rset.getString("email_pi");
                if(emailPI==null || emailPI.isEmpty()) emailPI="";
                centro_data.put("IdCentro_emailPI", emailPI);
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"aggiunto IdCentro_emailPI= "+emailPI);

                centro_data.put("IdCentro_inviatoCE", "1");//HDCE_3084
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"aggiunto IdCentro_inviatoCE= 1");

                /*HDCRPMS-630 INIZIO FIX PER CONTROLLO CENTRO GIA' ESISTENTE IN CRMS*/
                ElementCentro=null;
                it.cineca.siss.axmr3.log.Log.warn(getClass(), "CONTROLLO CHE IL CENTRO " + struttura + " "+ uo + " "+ pi + " ESISTA");
                String sql_get_centro="select * from crms_info_studio_centri where (id=? or codiceprot=? or eudractnumber=?) and struttura_code=? and uo_code=? and pi_code=? ";
                if(eudract_num!=null && eudract_num.equals("NA")){
                    sql_get_centro = "select * from crms_info_studio_centri where (id=? or codiceprot=?) and struttura_code=? and uo_code=? and pi_code=? ";
                }
                PreparedStatement stmt_get_centro = conn.prepareStatement(sql_get_centro);
                stmt_get_centro.setString(1, id_stud);
                stmt_get_centro.setString(2, codice_prot);
                if(eudract_num!=null && eudract_num.equals("NA")) {
                    stmt_get_centro.setString(3, struttura);
                    stmt_get_centro.setString(4, uo);
                    stmt_get_centro.setString(5, pi);
                }
                else{
                    stmt_get_centro.setString(3, eudract_num);
                    stmt_get_centro.setString(4, struttura);
                    stmt_get_centro.setString(5, uo);
                    stmt_get_centro.setString(6, pi);
                }
                ResultSet rset_get_centro = stmt_get_centro.executeQuery();
                it.cineca.siss.axmr3.log.Log.warn(getClass(), "eseguita query: " + sql_get_centro);
                if(rset_get_centro.next()) {
                    idCenter = rset_get_centro.getLong("centro_id");
                    it.cineca.siss.axmr3.log.Log.warn(getClass(), "TROVATO CENTRO elementID: " + idCenter);
                    if (idCenter > 0) {
                        it.cineca.siss.axmr3.log.Log.warn(getClass(), "AGGIORNO CENTRO GIA' ESISTENTE = " + idCenter);
                        ElementCentro = docService.getElement(idCenter);
                        docService.updateElementMetaData(user,ElementCentro,centro_data,"UPDATE");
                    }
                }
                else {
                    ElementType type = docService.getDocDefinitionByName("Centro");
                    ElementCentro = docService.saveElement(user, type, centro_data, null, null, null, "", "", "", "", ElementStudio);
                    idCenter = ElementCentro.getId();
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"CREATO CENTRO= "+idCenter);
                }
                /*HDCRPMS-630 FINE FIX PER CONTROLLO CENTRO GIA' ESISTENTE IN CRMS*/

                //Termino il processo InviaDatiCE
                List<ProcessInstance> activeProcesses;
                activeProcesses = docService.getActiveProcesses(ElementCentro);
                String processDefinition="InviaDatiCE:";
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"CERCO I WF ASSOCIATI AL CENTRO= "+idCenter);
                for(ProcessInstance process:activeProcesses){
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"HO TROVATO = "+process.getProcessDefinitionId());
                    if(process.getProcessDefinitionId().startsWith(processDefinition)){
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"PROVO A TERMINARE = "+process.getProcessDefinitionId());
                        docService.terminateProcess(userService.getUser(user),process.getProcessInstanceId());
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"HO TERMINATO = "+process.getProcessDefinitionId());
                    }
                }



                String numeroPazienti=rset.getString("paz_num");
                if(numeroPazienti==null || numeroPazienti.isEmpty()) numeroPazienti="";
                docService.addMetadataValueActions(idCenter,"DatiCentro","NrPaz",numeroPazienti);
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"aggiunto DatiCentro_NrPaz= "+numeroPazienti);


                //CARICO DOCUMENTI CENTRO SPECIFICI
                String sql_get_doc_centro = "SELECT c.doc_centrospec, d.ext, d.nome_file, c.userid_ins, c.d_doc_loc, c.doc_vers, NVL(TO_CHAR(c.doc_dt,'DD/MM/YYYY'),TO_CHAR(sysdate,'DD/MM/YYYY')) AS doc_dt, c.descr_agg, docloc.code||'###'||docloc.decode as DOCCENTROSPEC_TIPODOCUMENTO FROM ce_docum_centro c, docs d, crms_doc_loc docloc WHERE id_stud=? and c.visitnum_progr=? AND d.id =c.doc_centrospec and c.doc_loc=docloc.id_doc_ce and c.doc_loc in (1,15,12,14,16) and docloc.code not in (6)";
                PreparedStatement stmt_get_doc_centro = conn.prepareStatement(sql_get_doc_centro);
                stmt_get_doc_centro.setString(1, id_stud);
                stmt_get_doc_centro.setString(2, visitnum_progr);
                ResultSet rset_get_doc_centro = stmt_get_doc_centro.executeQuery();
                it.cineca.siss.axmr3.log.Log.warn(getClass(), "eseguita query: " + sql_get_doc_centro);
                String doc_core="";
                String ext="";
                String nome_file="";
                Path path ;
                String fileCeOnline="";
                String versione="";
                String data="";
                Element ElementAllegato;
                ElementType elDocType = docService.getDocDefinitionByName("AllegatoCentro");
                HashMap<String, String> doc_data = new HashMap<String, String>();
                Long idAllegato;

                while(rset_get_doc_centro.next()) {
                    doc_data = new HashMap<String, String>();
                    doc_data.put("DocCentroSpec_TipoDocumento", rset_get_doc_centro.getString("DOCCENTROSPEC_TIPODOCUMENTO"));
                    nome_file=rset_get_doc_centro.getString("NOME_FILE");
                    doc_core=rset_get_doc_centro.getString("DOC_CENTROSPEC");
                    ext=rset_get_doc_centro.getString("EXT");
                    fileCeOnline = "Doc_Area" + doc_core + "." + ext;
                    versione=rset_get_doc_centro.getString("DOC_VERS");
                    data=rset_get_doc_centro.getString("DOC_DT");
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"PATH FILE ALLEGATO = /http/servizi/siss-bundle-01/ricercaclinica-toscana.cineca.it/html/uxmr/WCA/docs/"+fileCeOnline);
                    path = Paths.get("/http/servizi/siss-bundle-01/ricercaclinica-toscana.cineca.it/html/uxmr/WCA/docs/"+fileCeOnline);
                    byte[] file_data = Files.readAllBytes(path);

                    ElementAllegato = docService.saveElement(user, elDocType, doc_data, file_data, nome_file, new Long(file_data.length), versione, data, "", "", ElementCentro);
                    idAllegato=ElementAllegato.getId();
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"CREATO AllegatoCentro = "+idAllegato);
                    //Termino il processo copiaAllegatoCentroInCeOnline
                    activeProcesses = docService.getActiveProcesses(ElementAllegato);
                    processDefinition="copiaAllegatoCentroInCeOnline:";
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"CERCO I WF ASSOCIATI ALL'ALLEGATO= "+idAllegato);
                    for(ProcessInstance process:activeProcesses){
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"HO TROVATO = "+process.getProcessDefinitionId());
                        if(process.getProcessDefinitionId().startsWith(processDefinition)){
                            it.cineca.siss.axmr3.log.Log.debug(getClass(),"PROVO A TERMINARE = "+process.getProcessDefinitionId());
                            docService.terminateProcess(userService.getUser(user),process.getProcessInstanceId());
                            it.cineca.siss.axmr3.log.Log.debug(getClass(),"HO TERMINATO = "+process.getProcessDefinitionId());
                        }
                    }



                }

                //imposto il centro in quarantena
                docService.addTemplate(ElementCentro,"Quarantena");
                docService.addMetadataValueActions(idCenter, "Quarantena",  "quarantena", "1###Si");
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "aggiornato Quarantena_quarantena= " + "1###Si");

                //setto crpms_center_progr per collegare il centro al ce
                sql1="update ce_centrilocali set crpms_center_progr=?, to_crpms=1 where visitnum=? and visitnum_progr=? and progr=? and esam=? and id_stud=?";
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"sql1 = "+sql1);
                PreparedStatement stmt1 = conn.prepareStatement(sql1);
                stmt1.setLong(1,idCenter);//crpms_center_progr
                stmt1.setLong(2,Long.parseLong("0"));//visitnum
                stmt1.setLong(3,Long.parseLong("0"));//visitnum_progr
                stmt1.setLong(4,Long.parseLong(visitnum_progr)+1);//progr
                stmt1.setLong(5,Long.parseLong("10"));//esam
                stmt1.setLong(6,Long.parseLong(id_stud));//id_stud
                ResultSet rset1 = stmt1.executeQuery();



                docService.getTxManager().commitAndKeepAlive();



            }
            else{
                it.cineca.siss.axmr3.log.Log.warn(getClass(), "CENTRO NON INVIABILE");
            }

            if(ElementCentro!=null) {
                String processKey = "inviaMail";
                HashMap<String, String> mailData = new HashMap<String, String>();
                String mailTo = "";
                String sqlMailTO = "select u.email as email from ana_utenti_1 u, studies_profiles sp,users_profiles up where u.userid=up.userid and sp.id=up.profile_id and sp.active=1 and up.active=1 and sp.code=?";
                it.cineca.siss.axmr3.log.Log.debug(getClass(), sqlMailTO);
                PreparedStatement stmtMailTo = conn.prepareStatement(sqlMailTO);
                stmtMailTo.setString(1, processBean.getCTOgroup((IUser) userService.loadUserByUsername(user)));
                ResultSet rsetMailTo = stmtMailTo.executeQuery();

                String comma = ",";
                boolean need_comma = false;
                while (rsetMailTo.next()) {
                    String my_mail = rsetMailTo.getString("email");
                    if (!my_mail.isEmpty()) {
                        if (need_comma) {
                            mailTo += comma;
                        }
                        mailTo += rsetMailTo.getString("email");
                        need_comma = true;
                    }
                }
                //mail=mail.replaceAll(",$",""); //tolgo l'ultima virgola
                if (mailTo.equals("")) mailTo = "noreply@cineca.it";//non invia a nessuno ma almeno non crasha
                String mailSubject = "SIRER - Invio dati da Segreteria CE a CTO/TFA";
                String mailInfoCentro="";
                Long idStudio;
                String sponsor="";
                String croString="";
                String codice="";
                String titolo="";
                String DenCentro="";
                String DenUnitaOperativa="";
                String DenPrincInv="";
                idStudio = idElementStudio;
                if(ElementStudio.getFieldDataElement("datiPromotore", "promotore")!=null && ElementStudio.getFieldDataElement("datiPromotore", "promotore").size()>0){
                    Element sp = ElementStudio.getFieldDataElement("datiPromotore", "promotore").get(0);
                    sponsor = sp.getfieldData("DatiPromotoreCRO","denominazione").get(0).toString();
                }
                if(ElementStudio.getFieldDataElement("datiCRO", "denominazione")!=null && ElementStudio.getFieldDataElement("datiCRO", "denominazione").size()>0){
                    Element cro = ElementStudio.getFieldDataElement("datiCRO", "denominazione").get(0);
                    croString = cro.getfieldData("DatiPromotoreCRO","denominazione").get(0).toString();
                }
                if(ElementStudio.getfieldData("IDstudio","CodiceProt")!=null && ElementStudio.getfieldData("IDstudio","CodiceProt").size()>0){
                    codice=ElementStudio.getfieldData("IDstudio","CodiceProt").get(0).toString();
                }
                if(ElementStudio.getfieldData("IDstudio","TitoloProt")!=null && ElementStudio.getfieldData("IDstudio","TitoloProt").size()>0){
                    titolo=ElementStudio.getfieldData("IDstudio","TitoloProt").get(0).toString();
                }
                DenCentro = ElementCentro.getfieldData("IdCentro","Struttura").get(0).toString().split("###")[1];
                DenUnitaOperativa = ElementCentro.getfieldData("IdCentro","UO").get(0).toString().split("###")[1];
                DenPrincInv = ElementCentro.getfieldData("IdCentro","PI").get(0).toString().split("###")[1];

                mailInfoCentro=
                        "ID studio: "+id_stud+
                                "\nCodice: "+codice+
                                "\nTitolo: "+titolo+
                                "\nSponsor: "+sponsor+
                                "\nCRO: "+croString+
                                "\nStruttura: "+DenCentro+
                                "\nUnita' operativa: "+DenUnitaOperativa+
                                "\nPrincipal Investigator: "+DenPrincInv;

                String url = processBean.getBaseUrl() + "/app/documents/detail/" + ElementCentro.getId();
                String mailBody = "Gentile utente,\n" +
                        "si comunica che e' stato appena inviato il seguente centro da Segreteria CE a CTO/TFA:\n\n" +
                        mailInfoCentro + "\n\n" +
                        "E' possibile visualizzare il centro al seguente link:\n\n" +
                        url + "\n\n" +
                        "Cordiali saluti\n\n\n\n"+
                        "Il presente messaggio è stato inviato automaticamente dal sistema, si prega di non rispondere.\n" +
                        "Per contattare il servizio di help desk inviare una mail a help_crpms@cineca.it";

                mailData.put("to", mailTo);
                mailData.put("subject", mailSubject);
                mailData.put("body", mailBody);
                docService.startProcess(user, ElementCentro, processKey, mailData);
            }
            conn.close();
            it.cineca.siss.axmr3.log.Log.warn(getClass(), "importazione centro da CE COMPLETATA!");
        }catch (Exception ex){
            Logger.getLogger(this.getClass()).error(ex.getMessage(), ex);
            conn.close();
            throw new RestException(ex.getMessage(),9999);
        }
        return retval;
    }
    public Long createChildFromCE(String elementId, String userid, String typeId, HashMap<String,String> data, boolean forceNotCloning) throws Exception{
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"Creo un elemento di tipo "+typeId+" nell'elemento: "+elementId);

        Long id=createChildFromCE(elementId, userid, typeId, data, docService,forceNotCloning);

        it.cineca.siss.axmr3.log.Log.debug(getClass(),"Elemento creato: "+id);
        return id;
    }
    public Long createChildFromCE(String elementId, String userid, String typeId,HashMap<String,String> data, DocumentService service,boolean forceNotCloning) throws Exception{
        //IUser user= (IUser) userService.loadUserByUsername(userid);
        Element parent=service.getElement(Long.parseLong(elementId));
        ElementType type=null;
        Element el=null;
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"parent type "+parent.getType().getTypeId());
        for (ElementType t:parent.getType().getAllowedChilds()){
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"allowed child "+t.getTypeId());
            if (t.getTypeId().equals(typeId)) type=t;
        }
        if (type!=null){
            el=service.saveElement(userid, type, data, null, null, null, "", "", "", "", parent,forceNotCloning);
        }
        return el.getId();
    }
/*TOSCANA-93 FINE*/

    @RequestMapping(value = "/rest/abilitaUR/{elementId}", method = RequestMethod.GET)
    public @ResponseBody
    PostResult abilitaUR(@PathVariable(value = "elementId") Long elementId) throws Exception{
        PostResult res=new PostResult("OK");
        Element el = docService.getDocDAO().getById(elementId);
        Element elCentro = el.getParent();
        Element elStudio = el.getParent().getParent();

        String group= getCTOgroup((IUser) userService.loadUserByUsername(elCentro.getCreateUser())).replace("CTO_","UR_");//TOSCANA-177
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"ASSOCIO GRUPPO= "+group);
        //do i diritti al centro
        docService.changePermissionToGroup(elCentro, "V,B,A", "", group);
        String idCentro = elCentro.getId().toString();
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"idCentro="+idCentro);

        //do i diritti ai figli del centro (documenti)
        Collection<Element> figliCentro = elCentro.getChildren();
        for(Element currfiglio:figliCentro){
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"figli di studio="+currfiglio);
            if(currfiglio.getTypeName().equals("AllegatoCentro")){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"figlio allegato");
                docService.setElementPolicy(currfiglio, null, "V,B", true, group, true);
            }
            if(currfiglio.getTypeName().equals("Fatturazione")){//TOSCANA-177 abilito UR_* anche per fatturazione
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"figlio Fatturazione");
                docService.setElementPolicy(currfiglio, null, "V,AC,B", true, group, true);
            }
        }
        docService.changePermissionToGroup(elStudio,"V,B","",group);
        String idStudio = elStudio.getId().toString();

        Collection<Element> figliStudio = elStudio.getChildren();
        for(Element currfiglio:figliStudio){
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"figli di studio="+currfiglio);
            if(currfiglio.getTypeName().equals("allegato")){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"figlio allegato");
                docService.setElementPolicy(currfiglio,null, "V,B",true,group,true);
            }
        }

        //SR

        docService.setTemplatePolicy(Long.parseLong(idCentro), "Feasibility", "V",true, group);
        docService.setTemplatePolicy(Long.parseLong(idCentro), "DatiCentro", "V",true, group);
        docService.setTemplatePolicy(Long.parseLong(idCentro), "IdCentro", "V",true, group);
        docService.setTemplatePolicy(Long.parseLong(idCentro), "datiStudio", "V",true, group);

        return res;

    }


    public String getCTOgroup(IUser user) {
        String group="";
        for (IAuthority auth : user.getAuthorities()){
            if(group.equals("") && auth.getAuthority().startsWith("CTO_")){
                group=auth.getAuthority();
            }
        }
        return group;
    }


    //TOSCANA-204 chiudere e riavviare il wf Chiudi feasibility locale e invia a CTC
    @RequestMapping(value = "/rest/ctc/TOSCANA-204", method = RequestMethod.GET)
    public
    @ResponseBody
    HashMap<String,String> TOSCANA_204(HttpServletRequest request) throws SQLException {
        boolean retval=false;
        HashMap<String,String> returnVal=new HashMap<String, String>();
        Connection conn = dataSource.getConnection();
        String sql = "select * from toscana_204_master_v where fattlocale is null";
        PreparedStatement stmt = conn.prepareStatement(sql);
        ResultSet rset = stmt.executeQuery();
        it.cineca.siss.axmr3.log.Log.warn(getClass(), "eseguita query: " + sql);
        while (rset.next()) {
            String idCenter = rset.getString("centro_id");
            try {
                retval=chiudiWFapprovFea(idCenter);
                returnVal.put(idCenter,String.valueOf(retval) );
            } catch (AxmrGenericException e) {
                Logger.getLogger(this.getClass()).error(e.getMessage(), e);
            }
        }
        returnVal.put("statusFinale",String.valueOf(retval) );
        return returnVal;
    }
    public boolean chiudiWFapprovFea (String idCenter) throws AxmrGenericException {
        boolean retval=false;
        //Termino il processo InviaDatiCE
        Element ElementCentro = docService.getElement(idCenter);
        List<ProcessInstance> activeProcesses;
        activeProcesses = docService.getActiveProcesses(ElementCentro);
        String processDefinition = "ce-gemelli-center-validation";
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "CERCO I WF ASSOCIATI AL CENTRO= " + idCenter);
        for (ProcessInstance process : activeProcesses) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "HO TROVATO = " + process.getProcessDefinitionId());
            if (process.getProcessDefinitionId().startsWith(processDefinition)) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "PROVO A TERMINARE = " + process.getProcessDefinitionId());
                docService.terminateProcess(userService.getUser(ElementCentro.getCreateUser()), process.getProcessInstanceId());
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "HO TERMINATO = " + process.getProcessDefinitionId());
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "PROVO A RIPARTIRE " + processDefinition);
                docService.startProcess(userService.getUser(ElementCentro.getCreateUser()), ElementCentro, processDefinition);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "E' ripartito" + processDefinition);
                retval=true;
            }
        }
        return retval;
    }


    //CRPMS-448
    @RequestMapping(value = "/rest/chiudiGestioneFarmaco/{elementId}", method = RequestMethod.POST)
    public @ResponseBody
        PostResult chiudiGestioneFarmaco(@PathVariable(value = "elementId") Long elementId) throws Exception{
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"----> INIZIO chiudiGestioneFarmaco "+elementId);
        PostResult res=new PostResult("OK");
        Element el = docService.getDocDAO().getById(elementId);
        String user = "SYSTEM";
        HashMap<String, String> data = new HashMap<String, String>();
        data.put("depotFarmaco_DepotChiuso", "1");
        docService.updateElementMetaData(user,el,data,"UPDATE");
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"aggiunto depotFarmaco_DepotChiuso= 1");
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"modificata policy V,B a CTC RICORSIVAMENTE");
        docService.setElementPolicy(el, "", "V,B", true, "CTC", true);
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"----> FINE chiudiGestioneFarmaco "+elementId);
        return res;
    }
}
