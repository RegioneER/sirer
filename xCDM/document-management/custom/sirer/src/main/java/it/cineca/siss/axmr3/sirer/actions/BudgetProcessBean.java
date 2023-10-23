package it.cineca.siss.axmr3.sirer.actions;

import it.cineca.siss.axmr3.doc.entities.Element;
import it.cineca.siss.axmr3.doc.entities.ElementType;
import it.cineca.siss.axmr3.doc.web.services.DocumentService;
import it.cineca.siss.axmr3.transactions.Axmr3TXManagerNonRequestScoped;
import org.activiti.engine.ActivitiException;
import org.activiti.engine.RuntimeService;
import org.activiti.engine.TaskService;
import org.activiti.engine.delegate.DelegateExecution;
import org.activiti.engine.delegate.DelegateTask;
import org.activiti.engine.runtime.Execution;
import org.activiti.engine.runtime.ProcessInstance;
import org.activiti.engine.task.Task;
import org.apache.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;

import javax.sql.DataSource;
import java.io.Serializable;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.text.SimpleDateFormat;
import java.util.*;
//TODO: trasformare tutte le eccezioni in RestException
public class BudgetProcessBean implements Serializable{
    /**
     *
     */
    private static final long serialVersionUID = 1L;

    @Autowired
    @Qualifier(value = "UserDataSource")
    protected DataSource dataSource;

    @Autowired
    @Qualifier(value = "processActions")
    protected it.cineca.siss.axmr3.doc.notRequestScopedBean.ProcessActionsBean commonBean;

    protected String baseUrl="";
    protected String prefix="";

    public DataSource getDataSource() {
        return dataSource;
    }

    public void setDataSource(DataSource dataSource) {
        this.dataSource = dataSource;
    }

    public DataSource getCommonBean() {
        return dataSource;
    }

    public void setCommonBean(it.cineca.siss.axmr3.doc.notRequestScopedBean.ProcessActionsBean bean) {
        this.commonBean = bean;
    }

    @Autowired
    protected Axmr3TXManagerNonRequestScoped globalTx;


    public String getBaseUrl() {
        return baseUrl;
    }

    @Autowired
    @Qualifier(value = "xCdmBaseUrl")
    public void setBaseUrl(String baseUrl) {
        this.baseUrl = baseUrl;
    }

    public String getPrefix() {
        return prefix;
    }

    @Autowired
    @Qualifier(value = "xCdmPrefix")
    public void setPrefix(String prefix) {
        this.prefix = prefix;
    }

    public Axmr3TXManagerNonRequestScoped getGlobalTx() {
        return globalTx;
    }


    public void setGlobalTx(Axmr3TXManagerNonRequestScoped globalTx) {
        this.globalTx = globalTx;
    }


    public void BudgetProcessBean() {
        System.out
                .println("Inizializzo il bean it.cineca.siss.axmr3.sirer.budget.ProcessActionsBean");
    }
    public HashMap<String,List<Long>>  getInvolvedElementsGroupped(Element el,DocumentService service) throws Exception{


        //LinkedList<Element> prestazioni=null;
        Collection<Element> tpxps = el.getChildrenByType("FolderTpxp").get(0).getChildren();
        Collection<Element> pxp = el.getChildrenByType("FolderPXP").get(0).getChildren();
		/*for (Element child:el.getChildren()){
            if (child.getType().getTypeId().equals("FolderTpxp")) tpxp=(LinkedList<Element>) child.getChildren();
        }*/
        String UO;

        Element prestazione=null;
        HashMap<String,List<Long>> ret=new HashMap<String,List<Long>> ();
        for(Element currTpxp:tpxps){
            List<Object> data = currTpxp.getfieldData("tp-p","Prestazione");
            if(data.size()>0){
                prestazione=(Element) data.get(0);
                data=prestazione.getfieldData("Prestazioni","UOC");
                if(data.size()>0){
                    UO=(String)data.get(0);
                    if(ret.get(UO)==null){
                        ret.put(UO,(new LinkedList<Long>()));
                    }
                    ret.get(UO).add(currTpxp.getId());
                }


            }
        }


        for(Element currPxp:pxp){

            List<Object> data = currPxp.getfieldData("Prestazioni","UOC");
            if(data.size()>0){
                UO=(String)data.get(0);
                if(ret.get(UO)==null){
                    ret.put(UO,(new LinkedList<Long>()));
                }
                ret.get(UO).add(currPxp.getId());
            }

        }

        return ret;
    }

    public void prepareMailUO(Collection<String> UOList, Element el, DelegateExecution execution) throws Exception {
        Connection conn=dataSource.getConnection();
        String UOInList="";
        String mail="g.delsignore@cineca.it";
        String sql1="";

        String url=baseUrl+"/app/documents/detail/"+el.getId()+"#tabs-4";
        Integer idx=1;
        String oggetto="SIRER - CTMS - Verifica budget";
        String html="Gentile utente,\n" +
                "e' stata richiesta la sua verifica del budget raggiungibile tramite il seguente link:\n" +
                ""+url+"\n\n" +
                "Cordiali saluti\n" ;

        for(String currUO:UOList){
            if(!UOInList.isEmpty()) {
                UOInList+=",";
            }
            UOInList+="?";
            idx++;
        }

        sql1="select email from ana_utenti_1 a,utenti u where a.userid=u.userid and u.abilitato=1 and a.userid in (select userid from utenti_gruppiu where abilitato=1 and id_gruppou in (select id_gruppou from ana_gruppiu where nome_gruppo in ("+UOInList+")))";
        it.cineca.siss.axmr3.log.Log.debug(getClass(),sql1);
        it.cineca.siss.axmr3.log.Log.debug(getClass(),sql1);

        PreparedStatement stmt = conn.prepareStatement(sql1);
        idx=1;
        for(String currUO:UOList){
            stmt.setString(idx, prefix+"_" + currUO);
            idx++;
        }
        ResultSet rset = stmt.executeQuery();

        //diritti V 	C 	M 	AC 	MC 	E 	MP 	A 	R 	P 	ET 	B
        mail="g.delsignore@cineca.it";
        while(rset.next()){
            if(rset.getString("email")!=null && !rset.getString("email").isEmpty()){
                mail+=","+rset.getString("email");
            }
        }

        execution.setVariable("bcc", mail);
        execution.setVariable("oggetto", oggetto);
        execution.setVariable("to", "undisclosed");
        execution.setVariable("html", html);
        conn.close();
    }

    public void prepareMailCTC( String elementId, DelegateExecution execution) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(elementId);
        Connection conn=dataSource.getConnection();
        String UOInList="";
        String mail="g.delsignore@cineca.it";
        String sql1="";

        String url=baseUrl+"/app/documents/detail/"+el.getId()+"#tabs-4";
        Integer idx=1;
        String oggetto="Richiesta di valutazione economica";
        String html="Gentile utente,\n" +
                "Si richiede la valutazione economica del seguente budget:\n\n" +

                mailInfoCentro(el.getParent().getId().toString())+"\n\n"+

                "Cordiali saluti\n" ;



        sql1="select email from ana_utenti_1 a,utenti u where a.userid=u.userid and u.abilitato=1 and a.userid in (select userid from utenti_gruppiu where abilitato=1 and id_gruppou in (select id_gruppou from ana_gruppiu where nome_gruppo = 'CTMS_CTC' ))";
        it.cineca.siss.axmr3.log.Log.debug(getClass(),sql1);
        it.cineca.siss.axmr3.log.Log.debug(getClass(),sql1);

        PreparedStatement stmt = conn.prepareStatement(sql1);



        ResultSet rset = stmt.executeQuery();

        //diritti V 	C 	M 	AC 	MC 	E 	MP 	A 	R 	P 	ET 	B

        while(rset.next()){
            if(rset.getString("email")!=null && !rset.getString("email").isEmpty()){
                mail+=","+rset.getString("email");
            }
        }

        execution.setVariable("bcc", mail);
        execution.setVariable("oggetto", oggetto);
        execution.setVariable("to", "undisclosed");
        execution.setVariable("html", html);
        conn.close();
        commonBean.closeDocumentService(service);
    }



    public void toCTCReimbursement(String elId,DocumentService service) throws Exception {

        Element el=service.getElement(Long.parseLong(elId));
        Element tpxps = el.getChildrenByType("FolderTpxp").get(0);
        Element prestazioni = el.getChildrenByType("FolderPrestazioni").get(0);
        Element tps = el.getChildrenByType("FolderTimePoint").get(0);
        Element center=el.getParent();
        String userid_pi= getPI(center);
        if  (!userid_pi.equals("")){
            commonBean.changePermissionToUser(elId,"V,B", "budget_PI_RO",userid_pi,service);
        }
        commonBean.changePermissionToGroup(elId,"","","PI",service);
        commonBean.changePermissionToGroup(tpxps.getId().toString(),"V,B","","PI",service);
        commonBean.changePermissionToGroup(prestazioni.getId().toString(),"V,B","","PI",service);
        commonBean.changePermissionToGroup(tps.getId().toString(), "V,B", "", "PI", service);
    }

    public void toCTCReimbursementBracci(String elId,DocumentService service) throws Exception {

        Element el=service.getElement(Long.parseLong(elId));
        List<Element> budgets = el.getChildrenByType("FolderBudgetBracci");
        for(Element currBudget:budgets){
            toCTCReimbursementBraccio(currBudget,service);
        }
    }

    public void toCTCReimbursementBraccio(Element el,DocumentService service) throws Exception {
        List<Element> budgets = el.getChildrenByType("FolderBudgetBracci");
        Element tpxps = el.getChildrenByType("FolderTpxp").get(0);
        Element prestazioni = el.getChildrenByType("FolderPrestazioni").get(0);
        Element tps = el.getChildrenByType("FolderTimePoint").get(0);
        Element center=el.getParent().getParent().getParent();
        String userid_pi= getPI(center);
        if  (!userid_pi.equals("")){
            commonBean.changePermissionToUser(el.getId().toString(),"V,B", "budget_PI_RO",userid_pi,service);
        }
        commonBean.changePermissionToGroup(el,"","","PI",service);
        commonBean.changePermissionToGroup(tpxps.getId().toString(),"V,B","","PI",service);
        commonBean.changePermissionToGroup(prestazioni.getId().toString(),"V,B","","PI",service);
        commonBean.changePermissionToGroup(tps.getId().toString(),"V,B","","PI",service);
    }

    public void checkInvioServizi(String elId,DelegateExecution execution) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el=service.getElement(Long.parseLong(elId));
        if(el.getFieldDataString("ApprovazioneClinica","InviaServizi").equals("1")){
            execution.setVariable("InviatoServizi",true);
        }else{
            execution.setVariable("InviatoServizi",false);
        }
        commonBean.closeDocumentService(service);
    }

    public void enablePI(String elId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        enablePI(elId,service);
        commonBean.closeDocumentService(service);
    }

    public void enablePI(String elId,DocumentService service) throws Exception {
        Element el=service.getElement(Long.parseLong(elId));
        Element center=el.getParent();
        String userid_pi= getPI(center);
        if  (!userid_pi.equals("")){
            commonBean.changePermissionToUser(elId,"V,A,M,B", "budget_PI",userid_pi,service);
        }

    }

    public void enablePI2(String elId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        enablePI2(elId, service);
        commonBean.closeDocumentService(service);
    }

    public void enablePI2(String elId,DocumentService service) throws Exception {
        Element el=service.getElement(Long.parseLong(elId));
        Element center=el.getParent();
        String userid_pi= getPI(center);
        if  (!userid_pi.equals("")){
            commonBean.changePermissionToUser(elId,"V,A,M,B", "B_budget_PI",userid_pi,service);
        }

    }

    public void enablePI3(String elId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        enablePI3(elId, service);
        commonBean.closeDocumentService(service);
    }

    public void enablePI3(String elId,DocumentService service) throws Exception {
        Element el=service.getElement(Long.parseLong(elId));
        Element center=el.getParent().getParent().getParent();
        String userid_pi= getPI(center);
        if  (!userid_pi.equals("")){
            commonBean.changePermissionToUser(elId,"V,A,E,M,B", "SB_budget_PI",userid_pi,service);
        }

    }

    public void toCTCReimbursement(String elId) throws Exception {
        DocumentService service=commonBean.getDocumentService();
        toCTCReimbursement(elId,service);
        commonBean.closeDocumentService(service);
    }

    public void toCTCReimbursementBracci(String elId) throws Exception {
        DocumentService service=commonBean.getDocumentService();
        toCTCReimbursementBracci(elId, service);
        commonBean.closeDocumentService(service);
    }


    public void createFolders(String elId) throws Exception {
        DocumentService service=commonBean.getDocumentService();
        createFolders( elId, service)  ;
        commonBean.closeDocumentService(service);
    }

    public void createFolders(String elId,DocumentService service) throws Exception {
        it.cineca.siss.axmr3.log.Log.warn(getClass(),"\tINIZIO createFolders");
        Element el=service.getElement(Long.parseLong(elId));
        Collection<ElementType> types = el.getType().getAllowedChilds();
        Long folderId=null;
        Long budgetCTCid=null;
        for(ElementType type:types){
            if(el.getChildrenByType(type.getTypeId())==null || el.getChildrenByType(type.getTypeId()).isEmpty()){
                it.cineca.siss.axmr3.log.Log.warn(getClass(),"\t\tFolder "+type);
                folderId=commonBean.createChild(elId,el.getCreateUser(),type.getTypeId(),service);
                it.cineca.siss.axmr3.log.Log.warn(getClass(),"\t\t\tFolder "+type.getTypeId()+" creata id: "+folderId.toString());
                if(type.getTypeId().equals("FolderBudgetStudio")){//SIRER-18 creo automaticamente BudgetStudio
                    budgetCTCid=commonBean.createChild(folderId.toString(),el.getCreateUser(),"BudgetCTC",service);
                    it.cineca.siss.axmr3.log.Log.warn(getClass(),"\t\t\t\tBudgetCTC creato id: "+budgetCTCid.toString());
                }
            }
        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"\tFINE createFolders");
    }

    //186202
    public void checkFolders(String typeId) throws Exception {
        DocumentService service=commonBean.getDocumentService();
        Element dummy=new Element();
        ElementType type=new ElementType();
        type.setId(Long.parseLong(typeId));
        dummy.setType(type);
        List<Element> elements = service.searchByExample(dummy);
        for(Element element:elements){
            createFolders(element.getId().toString(),service);
        }
        commonBean.closeDocumentService(service);
    }


    public void cloneForReview(String elId,DelegateExecution execution) throws Exception{
        DocumentService service=commonBean.getDocumentService();
        Element el=null;
        HashMap<String, String> data=new HashMap<String, String>();
        HashMap<String,Object> cloneParams=new HashMap<String, Object>();
        String user=execution.getVariable("lastUserid").toString();
        List<String> types=new LinkedList<String>();
        types.add("BudgetCTC");
        types.add("ReviewBudgetPI");
        cloneParams.put("skipTypes", types);
        data.put("Budget_Origine",elId);
        data.put("ApprovazioneClinica_Approvato","");
        data.put("ChiusuraBudget_Chiuso","");
        el = service.budgetClone(user, Long.parseLong(elId), cloneParams,data);
        service.startProcess(user,el,"budgetUO_2");
        commonBean.closeDocumentService(service);
    }
    public void startReview(String elId,DelegateExecution execution) throws Exception{
        DocumentService service=commonBean.getDocumentService();
        RuntimeService runtime = execution.getEngineServices().getRuntimeService();
        Element el=service.getElement(Long.parseLong(elId));
        Collection<ProcessInstance> instances = service.getActiveProcesses(el);//el.getProcessInstances();

        TaskService taskService = execution.getEngineServices().getTaskService();
        for(ProcessInstance myInstance:instances){
            //ProcessInstance myInstance = runtime.createProcessInstanceQuery().processInstanceId(instance.getProcessInstanceId()).singleResult();
            if(myInstance!=null){
                if(myInstance.getProcessDefinitionId().matches("^budgetUO_1.*$")){

                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"rimuovo process!!!!!!!!!!");
                    runtime.deleteProcessInstance(myInstance.getId(),"Invio ai servizi");
                }
                else {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"DefinitionID: "+myInstance.getProcessDefinitionId());
                }
            } else {
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"non rimuovo process!!!!!!!!!! "+myInstance.getProcessInstanceId());
            }

        }

        HashMap<String,List<Long>>  invEls = new HashMap<String, List<Long>>();
        HashMap<String,List<Long>>  currInvEls = new HashMap<String, List<Long>>();
        Collection<Element> subBudgets;
        if(el.getType().getTypeId().equals("Budget")){
            invEls = getInvolvedElementsGroupped(el,service);
        }else{
            subBudgets=el.getChildrenByType("FolderSingoloBraccio").get(0).getChildren();
            for(Element subBudget:subBudgets){
                currInvEls=getInvolvedElementsGroupped(subBudget,service);
                for(String uo:currInvEls.keySet()){
                    if(invEls.get(uo)==null){
                        invEls.put(uo,(new LinkedList<Long>()));
                    }
                    invEls.get(uo).addAll(currInvEls.get(uo));
                }
            }
        }
        prepareMailUO(invEls.keySet(), el, execution);
        if (invEls==null || invEls.isEmpty()){
            execution.setVariable("message","Attenzione compilare il flowchart per proseguire con il budget clinico");
        }
        else{
            execution.setVariable("message","");
            execution.setVariable("nroUO", invEls.size());
            execution.setVariable("involvedElementsGroupped", invEls);
            execution.setVariable("assignedElementsGroupped", new HashMap<String,List<Long>> ());
        }
        //execution.setVariableLocal("elInvolved", ((List) execution.getVariable("involvedElementGroupped")).get(0));
        //((List) execution.getVariable("involvedElementsGroupped")).remove(0);
        //it.cineca.siss.axmr3.log.Log.debug(getClass(),"elementId: "+execution.getVariable("elementId"));
        //execution.setAssignee("CCONTINO-"+execution.getId());
        commonBean.closeDocumentService(service);

    }

    public void signalBudgetApprovato(String elId,DelegateExecution execution)  {
        //TODO si può semplificare
        try{
            DocumentService service=commonBean.getDocumentService();
            Element el=service.getElement(Long.parseLong(elId));
            RuntimeService runtime = execution.getEngineServices().getRuntimeService();
            Collection<ProcessInstance> instances = service.getActiveProcesses(el);//.getProcessInstances();
            List<Execution> executionsList = runtime.createExecutionQuery().signalEventSubscriptionName("BudgetClinicoApprovato").processInstanceId(execution.getProcessInstanceId()).list();
            for(Execution ex:executionsList){
                try{
                    runtime.signalEventReceived("BudgetClinicoApprovato", ex.getId());
                }
                catch(Exception ex2){

                }
            }

            commonBean.closeDocumentService(service);
        }
        catch(Exception ex3){

        }
    }

    public void startBudgetStudioCTC(String elId,DelegateExecution execution) throws Exception{


        DocumentService service=commonBean.getDocumentService();
        Element el=service.getElement(Long.parseLong(elId));
        if(el.getType().getTypeId().equals("BudgetBracci")){
            toCTCReimbursementBracci(elId, service);
        }else{
            toCTCReimbursement(elId,service);
        }
        makePiRo(el, service);

        RuntimeService runtime = execution.getEngineServices().getRuntimeService();
        Collection<ProcessInstance> instances = service.getActiveProcesses(el);//el.getProcessInstances();
        /*
        Element center=el.getParent();
        String userid_pi= getPI(center);
        if  (!userid_pi.equals("")){
            commonBean.changePermissionToUser(elId,"V,B", "budget_PI_RO",userid_pi,service);
        }
        commonBean.changePermissionToGroup(el,"V,B","budget_CTC_close","CTC",service);
        */
        //ProcessInstance myInstance = runtime.createProcessInstanceQuery().variableValueEquals("elementId", elId).processDefinitionId("budgetCTC").singleResult();
        TaskService taskService = execution.getEngineServices().getTaskService();
        for(ProcessInstance myInstance:instances){
            //ProcessInstance myInstance = runtime.createProcessInstanceQuery().processInstanceId(instance.getProcessInstanceId()).singleResult();
            if(myInstance!=null){
                if(myInstance.getProcessDefinitionId().matches("^budgetUO.*$")){

                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"rimuovo process!!!!!!!!!!");
                    runtime.deleteProcessInstance(myInstance.getId(),"Approvazione da CTC");
                }
                else {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"DefinitionID: "+myInstance.getProcessDefinitionId());
                }
            } else {
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"non rimuovo process!!!!!!!!!! "+myInstance.getProcessInstanceId());
            }
            if(myInstance!=null && myInstance.getProcessDefinitionId().matches("^budgetCTC.*$")){
                List<Task> myTasks = taskService.createTaskQuery().processInstanceId(myInstance.getProcessInstanceId()).taskDefinitionKey("iniziaBudgetStudioCTC").list();
                if(myTasks.isEmpty()){
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"non trovo il task per il processo "+myInstance.getProcessInstanceId());
                }
                for(Task myTask:myTasks){
                    if(myTask!=null){
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"completo task!!!!!!!!!!");
                        taskService.complete(myTask.getId());

                    } else{
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"non completo task!!!!!!!!!!");
                    }
                }
            }
        }


        commonBean.closeDocumentService(service);

    }

    public void selectDefinitivo(String elId) throws Exception{

        DocumentService service=commonBean.getDocumentService();
        Element el=service.getElement(Long.parseLong(elId));
        String today = new SimpleDateFormat("dd/MM/yyyy").format(new Date());
        Element folder = el.getParent();
        Element budget = folder.getParent();
        List<Element> allBudgets = folder.getChildrenByType("BudgetCTC");
        for(Element currBudget:allBudgets){
            if(!currBudget.getId().equals(el.getId()))commonBean.addMetadataValue(currBudget.getId().toString(),"BudgetCTC","Definitivo","",service);
        }

        commonBean.addMetadataValue(el.getId().toString(),"BudgetCTC","Definitivo","1",service);
        commonBean.addMetadataValue(el.getId().toString(),"BudgetCTC","DefinitivoData",today,service);
        if(budget.getType().getTypeId().equals("BudgetSingoloBraccio")){
            commonBean.addMetadataValue(budget.getId().toString(),"BraccioWF","BudgetDefinitivo",el.getId().toString(),service);
            //commonBean.addMetadataValue(budget.getId().toString(),"BraccioWF","BudgetDefinitivoId",el.getId().toString(),service);
        }
        commonBean.closeDocumentService(service);

    }

    private String getPI(Element el) throws Exception {
        String userid_pi="";
        //Element el=service.getElement(Long.parseLong(elementId));
        if(el.getfieldData("IdCentro","PI")!=null && el.getfieldData("IdCentro", "PI").size()>0 ) {
            String id_PI = el.getfieldData("IdCentro", "PI").get(0).toString();

            String[] idValue = id_PI.split("###");

            id_PI = idValue[0];

            Connection conn = dataSource.getConnection();
            //Element el=service.getElement(Long.parseLong(elementId));
            //Long idStudio= (Long) el.getParent().getfieldData("UniqueIdStudio", "id").get(0);
            String sql1 = "select userid from ANA_UTENTI_1 where PROGR_PRINC_INV=" + id_PI;
            it.cineca.siss.axmr3.log.Log.debug(getClass(), sql1);
            PreparedStatement stmt = conn.prepareStatement(sql1);
            ResultSet rset = stmt.executeQuery();


            if (rset.next()) userid_pi = rset.getString("userid");

            //diritti V 	C 	M 	AC 	MC 	E 	MP 	A 	R 	P 	ET 	B

            conn.close();
        }
        return userid_pi;
    }

    public void startBudgetStudioUO(String elId,DelegateExecution execution) throws Exception{

        DocumentService service=commonBean.getDocumentService();
        toCTCReimbursement(elId,service);
        Element el=service.getElement(Long.parseLong(elId));
        String today = new SimpleDateFormat("dd/MM/yyyy").format(new Date());
        Collection<Element> reviews = el.getChildrenByType("FolderApprovazione").get(0).getChildren();
        String approvato="1";//approvato
        for(Element review:reviews){
            if(review.getFieldDataCode("ReviewBudgetPI","Stato").equals("3")){
                approvato="2";//non approvato
            }
        }
        commonBean.addMetadataValue(el.getId().toString(),"ApprovazioneClinica","Approvato",approvato,service);
        commonBean.addMetadataValue(el.getId().toString(),"ApprovazioneClinica","Data",today,service);
        RuntimeService runtime = execution.getEngineServices().getRuntimeService();
        Collection<ProcessInstance> instances = service.getActiveProcesses(el);//.getProcessInstances();

        //ProcessInstance myInstance = runtime.createProcessInstanceQuery().variableValueEquals("elementId", elId).processDefinitionId("budgetCTC").singleResult();
        TaskService taskService = execution.getEngineServices().getTaskService();
        for(ProcessInstance myInstance:instances){
            //ProcessInstance myInstance = runtime.createProcessInstanceQuery().processInstanceId(instance.getProcessInstanceId()).singleResult();
            if(myInstance!=null){
                if(myInstance.getProcessDefinitionId().matches("^budgetCTCClinico.*$")){
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"rimuovo process!!!!!!!!!!");
                    runtime.deleteProcessInstance(myInstance.getId(),"Approvazione da UO");
                }
                else {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"DefinitionID: "+myInstance.getProcessDefinitionId());
                }
            } else {
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"non rimuovo process!!!!!!!!!! "+myInstance.getProcessInstanceId());
            }
            if(myInstance!=null && myInstance.getProcessDefinitionId().matches("^budgetCTC.*$")){
                List<Task> myTasks = taskService.createTaskQuery().processInstanceId(myInstance.getProcessInstanceId()).taskDefinitionKey("iniziaBudgetStudioCTC").list();
                if(myTasks.isEmpty()){
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"non trovo il task per il processo "+myInstance.getProcessInstanceId());
                }
                for(Task myTask:myTasks){
                    if(myTask!=null){
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"completo task!!!!!!!!!!");
                        taskService.complete(myTask.getId());

                    } else{
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"non completo task!!!!!!!!!!");
                    }
                }
            }
        }


        commonBean.closeDocumentService(service);


    }

    public void giveRights(String elId) throws Exception {
        //diritti V 	C 	M 	AC 	MC 	E 	MP 	A 	R 	P 	ET 	B
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(elId);
        if(el.getType().getTypeId().equals("BudgetBracci")){
            commonBean.changePermissionToGroup(elId,"V,C,M,AC,MC,E,MP,A,R,P,ET,B","B_budget_CTC_complete","CTC",service);
            Collection<Element> children = el.getChildrenByType("FolderSingoloBraccio").get(0).getChildren();
            for(Element currChild:children){
                commonBean.changePermissionToGroup(currChild.getId().toString(),"V,C,M,AC,MC,E,MP,A,R,P,ET,B","SB_budget_CTC_complete","CTC",service);
            }
        }else{
            commonBean.changePermissionToGroup(elId,"V,C,M,AC,MC,E,MP,A,R,P,ET,B","budget_CTC_complete","CTC",service);
        }
        commonBean.closeDocumentService(service);
    }
    public void giveRightsPI(String elId,DelegateExecution execution) throws Exception {
        //diritti V 	C 	M 	AC 	MC 	E 	MP 	A 	R 	P 	ET 	B
        DocumentService service = commonBean.getDocumentService();
        Element el= service.getElement(Long.parseLong(elId)) ;
        List<Object> approvedList = el.getfieldData("ApprovazioneClinica","Approvato");
        String approved="";
        if(approvedList!=null && approvedList.size()>0){
            approved = approvedList.get(0).toString();
        }
        if(!approved.equals("1")){
            makePiPartial(el,service);
        }
        commonBean.closeDocumentService(service);
    }

    public void postReview(String elId,DelegateTask task, String review) throws Exception{
        DocumentService service=commonBean.getDocumentService();
        String UO= (String) task.getVariableLocal("UO");
        Element el = service.getElement(elId);
        String approvazione = (String) task.getVariableLocal("approvazioneEl");
        String today = new SimpleDateFormat("dd/MM/yyyy").format(new Date());
        HashMap<String,List<Long>>  assignedInvEls ;
        DelegateExecution execution=task.getExecution();
        assignedInvEls = ((HashMap<String,List<Long>>) task.getVariable("assignedElementsGroupped"));

        commonBean.addMetadataValue(approvazione,"ReviewBudgetPI","Stato",review,service);
        commonBean.addMetadataValue(approvazione,"ReviewBudgetPI","DataVerifica",today,service);
        commonBean.addMetadataValue(approvazione,"ReviewBudgetPI","Reviewer",task.getVariable("lastUserid"),service);

        if(assignedInvEls.get(UO)==null){
            commonBean.closeDocumentService(service);
            return ;
        }
        else{
            List<Long> approved = assignedInvEls.get(UO);
            try{
                checkLocalTransferPrice(approved,execution,service);
            }  catch(Exception ex){
                throw ex;
            }
            for(Long currEl:approved){
                if(currEl==null ) {continue;}
                else{
                    //System.out.print("Approvo "+String.valueOf(currEl));
                    //System.out.print("Assignee "+task.getOwner());
                }
                //TODO: capire perchè le seguenti due righe danno errore e decommentarle
                //service.addMetadataValueActions(currEl, "Rimborso", "ApprovatoDa", task.getOwner());
                //service.addMetadataValueActions(currEl,"Rimborso","UO",UO);
                if(!UO.equals("CTC") && !UO.equals("NRC") && !UO.equals("CTO") && !UO.equals("CTO/TFA")){
                    commonBean.changePermissionToGroup(currEl.toString(),"V,B","",UO,service);
                }

            }


            commonBean.changePermissionToGroup(elId,"V,B","budget_UO",UO,service);

        }
        commonBean.closeDocumentService(service);
    }

    public void assignTask(String elId,DelegateTask task) throws Exception{
        DocumentService service=commonBean.getDocumentService();
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"Task id: "+task.getId());
        HashMap<String,List<Long>>  invEls = ((HashMap<String,List<Long>>) task.getVariable("involvedElementsGroupped"));
        HashMap<String,List<Long>>  assignedInvEls ;
        Element el = service.getElement(elId);
        Element folderApprovazioni = el.getChildrenByType("FolderApprovazione").get(0);
        String today = new SimpleDateFormat("dd/MM/yyyy").format(new Date());
        HashMap<String, String>  approvazioneData=new HashMap<String, String>() ;
        approvazioneData.put("ReviewBudgetPI_Stato", "1###Pending");
        approvazioneData.put("ReviewBudgetPI_TaskId",task.getId());
        approvazioneData.put("ReviewBudgetPI_DataInvio",today);


        Set<String> keys = invEls.keySet();
        for(String key:keys){
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"key id: "+key);
            assignedInvEls = ((HashMap<String,List<Long>>) task.getVariable("assignedElementsGroupped"));
            if(assignedInvEls.get(key)!=null){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"key is assigned: "+key);
                continue;
            }
            else{
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"key is not assigned: "+key);
                assignedInvEls.put(key,invEls.get(key));
                task.addCandidateGroup(key);
                task.setVariableLocal("UO",key);


                task.setVariableLocal("message","Attenzione, e' necessario compilare correttamente il transfer price per ciascuna prestazione.");

                List<Long> toApprove = assignedInvEls.get(key);
                Element firstElement = service.getElement(toApprove.get(0));
                approvazioneData.put("ReviewBudgetPI_UO",key);
                Connection conn=dataSource.getConnection();
                //Element el=service.getElement(Long.parseLong(elementId));
                //Long idStudio= (Long) el.getParent().getfieldData("UniqueIdStudio", "id").get(0);
                String sql1="select descrizione from ana_gruppiu where nome_gruppo=?";
                it.cineca.siss.axmr3.log.Log.debug(getClass(),sql1);
                PreparedStatement stmt = conn.prepareStatement(sql1);
                stmt.setString(1,prefix+"_"+key);
                ResultSet rset = stmt.executeQuery();


                while(rset.next()){
                    approvazioneData.put("ReviewBudgetPI_UODescrizione",rset.getString("descrizione"));
                }
                conn.close();

                Long approvazione = commonBean.createChild(folderApprovazioni, task.getVariable("lastUserid").toString(), "ReviewBudgetPI", approvazioneData, service);
                task.setVariableLocal("approvazioneEl",approvazione.toString());
                for(Long currEl:toApprove){
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"assigning key: "+key+ " el:"+currEl.toString());
                    //service.addMetadataValueActions(currEl,"Rimborso","ApprovatoDa",task.getAssignee());
                    commonBean.addMetadataValue(currEl.toString(),"Rimborso","UO",key,service);
                    if(!key.equals("CTC") && !key.equals("NRC") && !key.equals("CTO") && !key.equals("CTO/TFA")){
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"giving permissions1: "+key);
                        Element currElement=commonBean.getElement(currEl.toString(),service);
                        List<Object> prestazioni = currElement.getfieldData("tp-p", "Prestazione");
                        List<Object> tps = currElement.getfieldData("tp-p", "TimePoint");
                        String prestazioneId="";
                        String tpId="";
                        Boolean addPrestazione=false;
                        Boolean addTp=false;
                        if(!prestazioni.isEmpty()) {
                            Element prestazione = (Element) prestazioni.get(0);
                            prestazioneId=prestazione.getId().toString();
                            addPrestazione =true;
                        }
                        if(!tps.isEmpty()) {
                            Element tp = (Element) tps.get(0);
                            tpId=tp.getId().toString();
                            addTp=true;
                        }

                        if(currElement.getType().getTypeId().equals("PrestazioneXPaziente") || (addPrestazione && addTp)) {
                            it.cineca.siss.axmr3.log.Log.debug(getClass(),"giving permissions2: "+key+ " " +currEl.toString());
                            commonBean.changePermissionToGroup(currEl.toString(),"V,B,M,P,ET","",key,service);
                        }
                        if(addPrestazione) {
                            it.cineca.siss.axmr3.log.Log.debug(getClass(),"giving permissions3: "+key+ " " +prestazioneId.toString());
                            commonBean.changePermissionToGroup(prestazioneId,"V,B,M,P,ET","",key,service);
                        }
                        if(addTp) {
                            it.cineca.siss.axmr3.log.Log.debug(getClass(),"giving permissions4: "+key+ " " +tpId.toString());
                            commonBean.changePermissionToGroup(tpId,"V,B,M,P,ET","",key,service);
                        }
                    }
                    commonBean.changePermissionToGroup(currEl.toString(),"V,B","","PI",service);
                }
                if(!key.equals("CTC") && !key.equals("NRC") && !key.equals("CTO") && !key.equals("CTO/TFA") && el.getType().getTypeId().equals("Budget")){
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"giving permissions5: "+key+ " " +elId.toString());
                    Element myElement = service.getElement(Long.parseLong(elId));
                    Collection<Element> tps = myElement.getChildrenByType("FolderTimePoint").get(0).getChildren();
                    for(Element currTp:tps){
                        commonBean.changePermissionToGroup(currTp.getId().toString(),"V,B,M,P,ET","",key,service);
                    }
                    commonBean.changePermissionToGroup(elId,"V,B,M,P,ET","budget_UO",key,service);
                    commonBean.changePermissionToGroup(myElement.getParent(),"V,B","",key,service) ;
                    commonBean.changePermissionToGroup(myElement.getParent().getParent(),"V,B","",key,service) ;
                }
                if(!key.equals("CTC") && !key.equals("NRC") && !key.equals("CTO") && !key.equals("CTO/TFA") && !el.getType().getTypeId().equals("Budget")){
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"giving permissions5: "+key+ " " +elId.toString());
                    Element bracciElement = service.getElement(Long.parseLong(elId));
                    commonBean.changePermissionToGroup(bracciElement,"V,B,M,P,ET","B_budget_UO",key,service);
                    Collection<Element> children = bracciElement.getChildrenByType("FolderSingoloBraccio").get(0).getChildren();
                    for(Element myElement:children){
                        Collection<Element> tps = myElement.getChildrenByType("FolderTimePoint").get(0).getChildren();
                        for(Element currTp:tps){
                            commonBean.changePermissionToGroup(currTp.getId().toString(),"V,B,M,P,ET","",key,service);
                        }
                        commonBean.changePermissionToGroup(myElement,"V,B,M,P,ET","SB_budget_UO",key,service);
                        commonBean.changePermissionToGroup(myElement.getParent(),"V,B","",key,service) ;
                        commonBean.changePermissionToGroup(myElement.getParent().getParent(),"V,B","",key,service) ;
                    }
                }

                break;
            }
        }

        commonBean.closeDocumentService(service);
    }

    public void makePiRo(Element el,DocumentService service) throws Exception {
        Element center=el.getParent();
        String userid_pi= getPI(center);
        if  (!userid_pi.equals("") && el.getType().getTypeId().equals("Budget")){
            commonBean.changePermissionToUser(el.getId().toString(),"V,B", "budget_PI_RO",userid_pi,service);
        }
        if  (!userid_pi.equals("") && !el.getType().getTypeId().equals("Budget")){
            commonBean.changePermissionToUser(el.getId().toString(),"V,B", "B_budget_PI_RO",userid_pi,service);
            Collection<Element> children = el.getChildrenByType("FolderSingoloBraccio").get(0).getChildren();
            for(Element currChild:children){
                commonBean.changePermissionToUser(currChild.getId().toString(), "V,B", "SB_budget_PI_RO", userid_pi, service);
            }
        }
    }

    public void makePiPartial(Element el,DocumentService service) throws Exception {
        Element center=el.getParent();
        String userid_pi= getPI(center);
        if  (!userid_pi.equals("")){
            commonBean.changePermissionToUser(el.getId().toString(),"V,A,M,B", "budget_PI_partial",userid_pi,service);
        }
    }

    public void budgetApproved(String elementId) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"budgetApproved:start");

        DocumentService service=commonBean.getDocumentService();
        budgetApproved(elementId,service);
        commonBean.closeDocumentService(service);
    }


    public void budgetApproved(String elementId, DocumentService service) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"budgetApproved:start");


        Element el=service.getElement(Long.parseLong(elementId));
        if(el.getParent()!=null){
            service.addMetadataValueActions(el.getParent().getId(), "statoValidazioneCentro", "idBudgetApproved", elementId);
            service.addMetadataValueActions(el.getParent().getId(), "statoValidazioneCentro", "typeBudgetApproved", el.getType().getTypeId());
        }
        makePiRo(el, service);
        String today = new SimpleDateFormat("dd/MM/yyyy").format(new Date());
        try{
            commonBean.addMetadataValue(el.getId().toString(),"ChiusuraBudget","Chiuso","1",service);
            commonBean.addMetadataValue(el.getId().toString(),"ChiusuraBudget","Data",today,service);
        }catch (Exception e){

        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"budgetApproved:changePermCTC ");
        if(el.getType().getTypeId().equals("BudgetBracci")){
            commonBean.changePermissionToGroup(el, "V,B", "B_budget_CTC_close", "CTC", service);
            Collection<Element> children = el.getChildrenByType("FolderSingoloBraccio").get(0).getChildren();
            for(Element currChild:children){
                commonBean.changePermissionToGroup(currChild.getId().toString(),"V,B","SB_budget_CTC_close","CTC",service);
            }
        }else{
            commonBean.changePermissionToGroup(el, "V,B", "budget_CTC_close", "CTC", service);
        }
        /*Collection<Element> allElements = el.getChildren();

        for(Element currEl:allElements){
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"budgetApproved:cycle "+currEl.getId().toString());
            commonBean.changePermissionToGroupRecursive(currEl,"V,B","","CTC",service);
            commonBean.changePermissionToUserRecursive(currEl.getId().toString(), "V,B", "", userid_pi, service);
        }     */

        //RuntimeService runtime = execution.getEngineServices().getRuntimeService();
        /*Collection<ProcessInstance> instances = service.getActiveProcesses(el);//el.getProcessInstances();

        //ProcessInstance myInstance = runtime.createProcessInstanceQuery().variableValueEquals("elementId", elId).processDefinitionId("budgetCTC").singleResult();
        //TaskService taskService = execution.getEngineServices().getTaskService();
        for(ProcessInstance myInstance:instances){
           // ProcessInstance myInstance = runtime.createProcessInstanceQuery().processInstanceId(instance.getProcessInstanceId()).singleResult();
            if(myInstance!=null){
                if(myInstance.getProcessDefinitionId().matches("^budgetCTCClinico.*$") || myInstance.getProcessDefinitionId().matches("^budgetUO.*$")){
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"rimuovo process!!!!!!!!!!");
                    if(!myInstance.isEnded())service.deleteProcessInstance(myInstance.getId(),"Chiusura budget studio");
                }
                else {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"DefinitionID: "+myInstance.getProcessDefinitionId());
                }
            } else {
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"non rimuovo process!!!!!!!!!! ");
            }

        }                    */

    }



    public void checkClosing(String elementId,DelegateExecution execution) throws Exception{
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"checkClosing:start");

        DocumentService service=commonBean.getDocumentService();
        Element el=service.getElement(Long.parseLong(elementId));
        Element budgetDefinitivo=null;
        Element centro=el.getParent();
        Element studio=centro.getParent();
        Element folder = el.getChildrenByType("FolderBudgetStudio").get(0);
        String definitivo="";
        String numeroPazienti="";
        HashMap<String,String> data=new HashMap<String, String>();
        int countDefinitivi=0;

        if(centro.getFieldDataCode("statoValidazioneCentro","fattLocale").isEmpty() ){
            execution.setVariable("message","Attenzione, e' necessario avere la fattibilita' locale, prima di chiudere il budget.");
            commonBean.closeDocumentService(service);
            return;
        }
        String studioProfit = studio.getFieldDataCode("datiStudio", "NaturaDelloStudio");
        /*SIRER-42 elimino controllo su approvazione budget clinico perchè non esiste più
        if(!el.getFieldDataString("ApprovazioneClinica","Approvato").equals("1")){
            execution.setVariable("message","Attenzione, e' necessario avere l'approvazione clinica del budget.");
            commonBean.closeDocumentService(service);
            return;
        } else{
            execution.setVariable("message","");
        }*/


        /*if(centro.getChildrenByType("PropostaSponsor").size()==0 ){
            execution.setVariable("message","Attenzione, e' necessario avere inserito la proposta iniziale sponsor.");
            commonBean.closeDocumentService(service);
            return;
        } else{
            execution.setVariable("message","");
        }*/
        if(el.getType().getTypeId().equals("Budget")){
            List<Element> allBudgets = folder.getChildrenByType("BudgetCTC");
            boolean valid=false;
            for(Element currBudget:allBudgets){
                selectDefinitivo(currBudget.getId().toString());//setto come definitivo l'unico budget studio che abbiamo!
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"checkClosing:check "+currBudget.getId().toString());
                definitivo=currBudget.getFieldDataString("BudgetCTC","Definitivo");
                if(!definitivo.isEmpty() && definitivo.equals("1")){
                    budgetDefinitivo=currBudget;
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"checkClosing:definitivo "+currBudget.getId().toString());
                    valid=true;
                    countDefinitivi++;
                }
            }
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"checkClosing:n. definitivi "+String.valueOf(countDefinitivi));

            it.cineca.siss.axmr3.log.Log.debug(getClass(),"checkClosing:Final valid");
            it.cineca.siss.axmr3.log.Log.debug(getClass(),valid);
            if (!valid){
                execution.setVariable("message","Attenzione, e' necessario selezionare un budget come definitivo.");
            }
            else{
                numeroPazienti=budgetDefinitivo.getFieldDataString("BudgetCTC","NumeroPazienti");
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"numeroPazienti budget definitivo "+numeroPazienti);
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"numeroPazienti centro "+centro.getFieldDataString("Feasibility","NrPaz"));

                /*if(!numeroPazienti.equals(centro.getFieldDataString("Feasibility","NrPaz"))){
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"numeroPazienti centro e budget differenti");
                    execution.setVariable("message","Attenzione, Il numero pazienti e' stato aggiornato dall'ultimo salvataggio del budget definitivo. Effettuare un nuovo salvataggio prima di chiudere il budget.");
                }
                else{*/
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"numeroPazienti centro e budget uguali");
                if(studioProfit.equals("1") && numeroPazienti.isEmpty()){
                    execution.setVariable("message","Attenzione, e' necessario definire il numero dei pazienti.");
                }
                else{
                    execution.setVariable("message","");
                    budgetApproved(elementId,service);
                }
                commonBean.changePermissionToGroup(el,"V,B","budget_CTC_close","CTC",service);
                commonBean.changePermissionToGroup(el,"V,B","budget_CTC_close","PI",service);
                //}
            }
        }else {
            Collection<Element> allBudgets = el.getChildrenByType("FolderSingoloBraccio").get(0).getChildren();
            Collection<Element> allPxp = el.getChildrenByType("FolderPrezzi").get(0).getChildren();
            Collection<Element> allPxpCTC = el.getChildrenByType("FolderPXSCTC").get(0).getChildren();
            boolean valid = true;
            boolean pazientiPresenti = true;
            String totBudgetString = "";
            Double totBudgetNumber = 0.0;
            Double sumTotBudgetNumber = 0.0;
            Integer sumNumeroPazienti = 0;
            for (Element currBudget : allBudgets) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "checkClosing:check " + currBudget.getId().toString());
                definitivo = currBudget.getFieldDataString("BraccioWF", "BudgetDefinitivo");

                if (!definitivo.isEmpty()) {
                    budgetDefinitivo = commonBean.getElement(definitivo, service);

                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "checkClosing:definitivo " + currBudget.getId().toString());
                    totBudgetString = budgetDefinitivo.getFieldDataString("BudgetCTC", "TotaleStudioCTC");
                    numeroPazienti = budgetDefinitivo.getFieldDataString("BudgetCTC", "NumeroPazienti");
                    if (studioProfit.equals("1") && numeroPazienti.isEmpty()) {
                        pazientiPresenti = false;

                    } else if (!totBudgetString.isEmpty()) {
                        try {
                            totBudgetNumber = Double.parseDouble(totBudgetString);
                            sumNumeroPazienti += Integer.parseInt(numeroPazienti);
                            sumTotBudgetNumber += totBudgetNumber;
                        } catch (Exception ex) {
                            totBudgetNumber = 0.0;
                        }

                    }


                } else {
                    valid = false;
                }
            }
            for (Element pxp : allPxp) {
                Element prestazione = pxp.getFieldDataElement("PrezzoFinale_Prestazione").get(0);
                if (prestazione.getType().getTypeId().equals("PrestazioneXStudio")) {
                    double tpValDouble;
                    double prezzoValDouble;
                    String tpVal = prestazione.getFieldDataString("Costo_TransferPrice");
                    String prezzoVal = pxp.getFieldDataString("PrezzoFinale_Prezzo");
                    try {
                        tpValDouble = Double.parseDouble(tpVal);
                    } catch (Exception ex) {
                        tpValDouble = 0.0;
                    }
                    try {
                        prezzoValDouble = Double.parseDouble(prezzoVal);
                    } catch (Exception ex) {
                        prezzoValDouble = tpValDouble;
                    }
                    sumTotBudgetNumber += prezzoValDouble;
                }
            }
            for (Element pxpCTC : allPxpCTC) {
                double tpValDouble;
                double prezzoValDouble;
                String tpVal = pxpCTC.getFieldDataString("Costo_Costo");
                String prezzoVal = pxpCTC.getFieldDataString("Costo_Prezzo");
                try {
                    tpValDouble = Double.parseDouble(tpVal);
                } catch (Exception ex) {
                    tpValDouble = 0.0;
                }
                try {
                    prezzoValDouble = Double.parseDouble(prezzoVal);
                } catch (Exception ex) {
                    prezzoValDouble = tpValDouble;
                }
                sumTotBudgetNumber += prezzoValDouble;

            }
            if(studioProfit.equals("1")){

                if (valid && pazientiPresenti) {
                    data.put("BudgetCTC_NumeroPazienti", sumNumeroPazienti.toString());
                    data.put("BudgetCTC_TotaleStudioCTC", sumTotBudgetNumber.toString());
                    data.put("BudgetCTC_Definitivo", "1");
                    commonBean.createChild(folder, execution.getVariable("lastUserid").toString(), "BudgetCTCSummary", data, service);
                    execution.setVariable("message", "");
                    budgetApproved(elementId, service);
                } else if (!valid) {
                    execution.setVariable("message", "Attenzione, e' necessario definire il numero dei pazienti.");
                } else if (!pazientiPresenti) {
                    execution.setVariable("message", "Attenzione, e' necessario definire il numero dei pazienti per ciascun braccio");
                }
            }
            else{
                data.put("BudgetCTC_Definitivo", "1");
                commonBean.createChild(folder, execution.getVariable("lastUserid").toString(), "BudgetCTCSummary", data, service);
                execution.setVariable("message", "");
                budgetApproved(elementId, service);
            }

        }
        // togliere se da problemi alla chiusura del budget
        commonBean.closeDocumentService(service);
    }

    public void checkTransferPriceBracci(String elementId,DelegateExecution execution) throws Exception{
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"checkTransferPrice");
        String today = new SimpleDateFormat("dd/MM/yyyy").format(new Date());
        DocumentService service=commonBean.getDocumentService();
        Element element=service.getElement(Long.parseLong(elementId));
        Collection<Element> budgets = element.getChildrenByType("FolderSingoloBraccio").get(0).getChildren();
        boolean valid=true;
        for(Element el:budgets){
            Collection<Element> tpxps = el.getChildrenByType("FolderTpxp").get(0).getChildren();

            for(Element currTpxp:tpxps){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"checkTransferPrice: id:"+currTpxp.getId().toString());
                List<Object> rimborsabilita = currTpxp.getfieldData("Rimborso","Rimborsabilita");
                List<Object> data = currTpxp.getfieldData("Costo","TransferPrice");
                boolean rimbCheck=false;
                if(rimborsabilita.size()>0){
                    String rimborsabilitaVal = rimborsabilita.get(0).toString();
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"checkTransferPrice: rimb val: "+rimborsabilitaVal);

                    if(rimborsabilitaVal.equals("2")) {
                        it.cineca.siss.axmr3.log.Log.debug(getClass(),"checkTransferPrice: ok rimb val: ");
                        rimbCheck=true;
                    }
                }
                if(!rimbCheck && data.size()>0 && !data.get(0).equals("")){

                    it.cineca.siss.axmr3.log.Log.debug(getClass(),data.get(0));
                    boolean currValidation = ((String) data.get(0)).matches("-?\\d+(\\.\\d+)?");
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),currValidation);
                    if(!currValidation)valid=false;

                }
                else if(!rimbCheck){
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"checkTransferPrice: rimb size: "+rimborsabilita.size());
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"checkTransferPrice: data size: "+data.size());
                    valid=false;
                }

            }
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"checkTransferPrice:Final valid");
            it.cineca.siss.axmr3.log.Log.debug(getClass(),valid);
        }
        valid=true;
        if (!valid){
            execution.setVariable("message","Attenzione, e' necessario compilare correttamente il transfer price per ciascuna prestazione di ciascun braccio.");
        }
        else{
            commonBean.addMetadataValue(element.getId().toString(),"ApprovazioneClinica","Approvato","1",service);
            commonBean.addMetadataValue(element.getId().toString(),"ApprovazioneClinica","Data",today,service);
            Element folderApprovazioni=element.getChildrenByType("FolderApprovazione").get(0);
            HashMap<String, String>  approvazioneData=new HashMap<String, String>() ;
            approvazioneData.put("ReviewBudgetPI_Stato","2###Approvato");
            approvazioneData.put("ReviewBudgetPI_DataInvio",today);
            approvazioneData.put("ReviewBudgetPI_UO","CTC");
            approvazioneData.put("ReviewBudgetPI_UODescrizione","CTO/TFA");

            commonBean.createChild(folderApprovazioni, execution.getVariable("lastUserid").toString(), "ReviewBudgetPI", approvazioneData, service);
            execution.setVariable("message","");
        }

        commonBean.closeDocumentService(service);
    }

    public void checkTransferPrice(String elementId,DelegateExecution execution) throws Exception{
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"checkTransferPrice");
        String today = new SimpleDateFormat("dd/MM/yyyy").format(new Date());
        DocumentService service=commonBean.getDocumentService();
        Element el=service.getElement(Long.parseLong(elementId));
        Collection<Element> tpxps = el.getChildrenByType("FolderTpxp").get(0).getChildren();
        boolean valid=true;
        for(Element currTpxp:tpxps){
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"checkTransferPrice: id:"+currTpxp.getId().toString());
            List<Object> rimborsabilita = currTpxp.getfieldData("Rimborso","Rimborsabilita");
            List<Object> data = currTpxp.getfieldData("Costo","TransferPrice");
            boolean rimbCheck=false;
            if(rimborsabilita.size()>0){
                String rimborsabilitaVal = rimborsabilita.get(0).toString();
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"checkTransferPrice: rimb val: "+rimborsabilitaVal);

                if(rimborsabilitaVal.equals("2")) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"checkTransferPrice: ok rimb val: ");
                    rimbCheck=true;
                }
            }
            if(!rimbCheck && data.size()>0 && !data.get(0).equals("")){

                it.cineca.siss.axmr3.log.Log.debug(getClass(),data.get(0));
                boolean currValidation = ((String) data.get(0)).matches("-?\\d+(\\.\\d+)?");
                it.cineca.siss.axmr3.log.Log.debug(getClass(),currValidation);
                if(!currValidation)valid=false;

            }
            else if(!rimbCheck){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"checkTransferPrice: rimb size: "+rimborsabilita.size());
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"checkTransferPrice: data size: "+data.size());
                valid=false;
            }

        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"checkTransferPrice:Final valid");
        it.cineca.siss.axmr3.log.Log.debug(getClass(),valid);
        if (!valid){
            execution.setVariable("message","Attenzione, e' necessario compilare correttamente il transfer price per ciascuna prestazione.");
        }
        else{
            commonBean.addMetadataValue(el.getId().toString(),"ApprovazioneClinica","Approvato","1",service);
            commonBean.addMetadataValue(el.getId().toString(),"ApprovazioneClinica","Data",today,service);
            Element folderApprovazioni=el.getChildrenByType("FolderApprovazione").get(0);
            HashMap<String, String>  approvazioneData=new HashMap<String, String>() ;
            approvazioneData.put("ReviewBudgetPI_Stato","2###Approvato");
            approvazioneData.put("ReviewBudgetPI_DataInvio",today);
            approvazioneData.put("ReviewBudgetPI_UO","CTC");
            approvazioneData.put("ReviewBudgetPI_UODescrizione","CTO/TFA");

            commonBean.createChild(folderApprovazioni, execution.getVariable("lastUserid").toString(), "ReviewBudgetPI", approvazioneData, service);
            execution.setVariable("message","");
        }

        commonBean.closeDocumentService(service);
    }

    public void checkLocalTransferPrice(List<Long> approving,DelegateExecution execution) throws Exception{
        DocumentService service=commonBean.getDocumentService();
        checkLocalTransferPrice(approving, execution,service);
        commonBean.closeDocumentService(service);
    }

    public void checkLocalTransferPrice(List<Long> approving,DelegateExecution execution, DocumentService service) throws Exception{
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"checkLocalTransferPrice: in");
        boolean valid=true;
        for(Long currApproved:approving){
            Element el=service.getElement(currApproved);

            it.cineca.siss.axmr3.log.Log.debug(getClass(),"checkLocalTransferPrice: for : el "+el.getId().toString());

            List<Object> rimborsabilita = el.getfieldData("Rimborso","Rimborsabilita");
            List<Object> data = el.getfieldData("Costo","TransferPrice");
            if(rimborsabilita.size()>0 && data.size()>0 && !data.get(0).equals("")){
                String rimborsabilitaVal = rimborsabilita.get(0).toString();
                if(!rimborsabilitaVal.equals("2")) {

                    boolean currValidation = ((String) data.get(0)).matches("-?\\d+(\\.\\d+)?");
                    if(!currValidation){
                        valid=false;
                        throw new ActivitiException("Errore non e' stato compilato il transfer price per tutte le prestazioni soprattutto:"+rimborsabilitaVal);
                    }
                }
            }
            else{
                //it.cineca.siss.axmr3.log.Log.debug(getClass(),"checkLocalTransferPrice: if 1  "+rimborsabilita.size());
                //it.cineca.siss.axmr3.log.Log.debug(getClass(),"checkLocalTransferPrice: if 2  "+data.size());
                //it.cineca.siss.axmr3.log.Log.debug(getClass(),"checkLocalTransferPrice: if 3  "+data.get(0).toString());
                //it.cineca.siss.axmr3.log.Log.debug(getClass(),"checkLocalTransferPrice: else in  "+data.get(0).toString());
                if(data.size()>0 && !data.get(0).equals(""))
                {
                    boolean currValidation2 = ((String) data.get(0)).matches("-?\\d+(\\.\\d+)?");
                    if(!currValidation2)valid=false;
                }
                else{
                    valid=false;
                }
            }

            if (!valid){

                throw new ActivitiException("Errore non e' stato compilato il transfer price per tutte le prestazioni");
            }
            /*else{
                execution.setVariable("message", "");
            }   */
        }

    }

    public void clonaBudget(String elementId,DelegateExecution execution) throws Exception {
        DocumentService service=commonBean.getDocumentService();
        commonBean.closeDocumentService(service);
    }

    public void versioningBudget(String elementId) throws Exception {
        DocumentService service=commonBean.getDocumentService();
        Element el = service.getElement(elementId);
        List<Element> budgets = el.getParent().getChildrenByType("Budget");
        Element last = null;
        String version="";
        Double oldVersion=0.0;
        service.addTemplate(el,"Base");
        service.addTemplate(el,"Budget");
        commonBean.addMetadataValue(el, "Base", "Nome", el.getCreateUser(), service);

        commonBean.addMetadataValue(el, "Budget", "Versione", budgets.size()+".0",service);
        commonBean.closeDocumentService(service);
    }
    public void versioningBudgetStudio(String elementId) throws Exception {
        DocumentService service=commonBean.getDocumentService();
        Element el = service.getElement(elementId);
        List<Element> budgets = el.getParent().getChildrenByType("BudgetCTC");
        Element last = null;
        String version="";
        String majorVersion="";
        Integer minorVersion=1;
        Double oldVersion=0.0;
        String draftVersion="";
        String[] splitVersion=null;
        service.addTemplate(el,"Base");
        service.addTemplate(el,"Budget");
        commonBean.addMetadataValue(el, "Base", "Nome", el.getCreateUser(), service);
        if(budgets.size()>1) {
            last = budgets.get(budgets.size() - 2);
            try{
                oldVersion=Double.parseDouble(el.getParent().getParent().getFieldDataString("Budget", "Versione"));
                draftVersion=oldVersion.toString();
                splitVersion=draftVersion.split("\\.");
                majorVersion=splitVersion[0];
                oldVersion = Double.parseDouble(last.getFieldDataString("Budget","Versione"));
                draftVersion=oldVersion.toString();
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Vecchia versione "+draftVersion);
                splitVersion=draftVersion.split("\\.");
                minorVersion=Integer.parseInt(splitVersion[1])+1;
                version=majorVersion+"."+minorVersion.toString();
            }catch(NumberFormatException ex){
                Logger.getLogger(this.getClass()).error(ex.getMessage(), ex);
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Errore conversione 1");
            }
        }
        if(version.isEmpty()){
            try{
                oldVersion=Double.parseDouble(el.getParent().getParent().getFieldDataString("Budget", "Versione"));

                draftVersion=oldVersion.toString();
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Vecchia versione "+draftVersion);
                splitVersion=draftVersion.split("\\.");
                majorVersion=splitVersion[0];
                minorVersion=1;
                version=majorVersion+"."+minorVersion.toString();
            }catch(NumberFormatException ex){
                Logger.getLogger(this.getClass()).error(ex.getMessage(), ex);
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Errore conversione 2");
            }
        }
        if(version.isEmpty()){
            version="1.1";
        }
        commonBean.addMetadataValue(el, "Budget", "Versione", version,service);
        commonBean.closeDocumentService(service);
    }

    public String mailInfoCentro(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el=service.getElement(Long.parseLong(elementId));

        Long idStudio;
        String sponsor="";
        String croString="";
        String codice="";
        String titolo="";
        String DenCentro="";
        String DenIstituto="";
        String DenDipartimento="";
        String DenUnitaOperativa="";
        String DenPrincInv="";

        idStudio = Long.valueOf(el.getParent().getfieldData("UniqueIdStudio", "id").get(0).toString());
        if(el.getParent().getFieldDataElement("datiPromotore", "promotore")!=null && el.getParent().getFieldDataElement("datiPromotore", "promotore").size()>0){
            Element sp = el.getParent().getFieldDataElement("datiPromotore", "promotore").get(0);
            sponsor = sp.getfieldData("DatiPromotoreCRO","denominazione").get(0).toString();
        }
        if(el.getParent().getFieldDataElement("datiCRO", "denominazione")!=null && el.getParent().getFieldDataElement("datiCRO", "denominazione").size()>0){
            Element cro = el.getParent().getFieldDataElement("datiCRO", "denominazione").get(0);
            croString = cro.getfieldData("DatiPromotoreCRO","denominazione").get(0).toString();
        }
        if(el.getParent().getfieldData("IDstudio","CodiceProt")!=null && el.getParent().getfieldData("IDstudio","CodiceProt").size()>0){
            codice=el.getParent().getfieldData("IDstudio","CodiceProt").get(0).toString();
        }
        if(el.getParent().getfieldData("IDstudio","TitoloProt")!=null && el.getParent().getfieldData("IDstudio","TitoloProt").size()>0){
            titolo=el.getParent().getfieldData("IDstudio","TitoloProt").get(0).toString();
        }
        DenCentro = el.getfieldData("IdCentro","Struttura").get(0).toString().split("###")[1];
        DenIstituto = el.getfieldData("IdCentro","Istituto").get(0).toString().split("###")[1];
        DenDipartimento = el.getfieldData("IdCentro","Dipartimento").get(0).toString().split("###")[1];
        DenUnitaOperativa = el.getfieldData("IdCentro","UO").get(0).toString().split("###")[1];
        DenPrincInv = el.getfieldData("IdCentro","PI").get(0).toString().split("###")[1];

        String text=
                "ID studio: "+idStudio+
                        "\nCodice: "+codice+
                        "\nTitolo: "+titolo+
                        "\nSponsor: "+sponsor+
                        "\nCRO: "+croString+
                        "\nStruttura: "+DenCentro+
                        "\nIstituto: "+DenIstituto+
                        "\nDipartimento: "+DenDipartimento+
                        "\nUnita' operativa: "+DenUnitaOperativa+
                        "\nPrincipal Investigator: "+DenPrincInv;

        commonBean.closeDocumentService(service);
        it.cineca.siss.axmr3.log.Log.debug(getClass(),text);

        return text;

    }

    public void versioningBudgetBracci(String elementId) throws Exception {
        DocumentService service=commonBean.getDocumentService();
        Element el = service.getElement(elementId);
        List<Element> budgets = el.getParent().getChildrenByType("BudgetBracci");
        Element last = null;
        String version="";
        Double oldVersion=0.0;
        List<Element> folderSubList;
        Element folderSub;

        Collection<Element> bracciList;
        service.addTemplate(el,"Base");
        service.addTemplate(el,"Budget");
        version=budgets.size()+".0";
        commonBean.addMetadataValue(el, "Base", "Nome", el.getCreateUser(), service);

        commonBean.addMetadataValue(el, "Budget", "Versione", version,service);

        folderSubList = el.getChildrenByType("FolderSingoloBraccio");
        if(!folderSubList.isEmpty()){
            folderSub=folderSubList.get(0);
            bracciList=folderSub.getChildren();
            for(Element braccio:bracciList){
                commonBean.addMetadataValue(braccio, "Budget", "Versione", version,service);
            }
        }
        commonBean.closeDocumentService(service);
    }

    public void versioningBudgetSingoloBraccio(String elementId) throws Exception {
        DocumentService service=commonBean.getDocumentService();
        Element el = service.getElement(elementId);
        Element budget = el.getParent().getParent();
        Element last = null;
        String version="";
        Double oldVersion=0.0;
        service.addTemplate(el,"Base");
        service.addTemplate(el,"Budget");
        commonBean.addMetadataValue(el, "Base", "Nome", el.getCreateUser(), service);

        commonBean.addMetadataValue(el, "Budget", "Versione", budget.getFieldDataString("Budget","Versione"),service);
        commonBean.closeDocumentService(service);
    }
    public void versioningBudgetBracciStudio(String elementId) throws Exception {
        DocumentService service=commonBean.getDocumentService();
        Element el = service.getElement(elementId);
        List<Element> budgets = el.getParent().getChildrenByType("BudgetCTC");
        Element last = null;
        String version="";
        String majorVersion="";
        Integer minorVersion=1;
        Double oldVersion=0.0;
        String draftVersion="";
        String[] splitVersion=null;
        service.addTemplate(el,"Base");
        service.addTemplate(el,"Budget");
        commonBean.addMetadataValue(el, "Base", "Nome", el.getCreateUser(), service);
        if(budgets.size()>1) {
            last = budgets.get(budgets.size() - 2);
            try{
                oldVersion=Double.parseDouble(el.getParent().getParent().getParent().getParent().getFieldDataString("Budget", "Versione"));
                draftVersion=oldVersion.toString();
                splitVersion=draftVersion.split("\\.");
                majorVersion=splitVersion[0];
                oldVersion = Double.parseDouble(last.getFieldDataString("Budget","Versione"));
                draftVersion=oldVersion.toString();
                Logger.getLogger(this.getClass()).debug("Vecchia versione " + draftVersion);
                splitVersion=draftVersion.split("\\.");
                minorVersion=Integer.parseInt(splitVersion[1])+1;
                version=majorVersion+"."+minorVersion.toString();
            }catch(NumberFormatException ex){
                Logger.getLogger(this.getClass()).error(ex.getMessage(), ex);
                Logger.getLogger(this.getClass()).debug("Errore conversione 1");
            }
        }
        if(version.isEmpty()){
            try{
                oldVersion=Double.parseDouble(el.getParent().getParent().getFieldDataString("Budget", "Versione"));

                draftVersion=oldVersion.toString();
                Logger.getLogger(this.getClass()).debug("Vecchia versione " + draftVersion);
                splitVersion=draftVersion.split("\\.");
                majorVersion=splitVersion[0];
                minorVersion=1;
                version=majorVersion+"."+minorVersion.toString();
            }catch(NumberFormatException ex){
                Logger.getLogger(this.getClass()).error(ex.getMessage(), ex);
                Logger.getLogger(this.getClass()).debug("Errore conversione 2");
            }
        }
        if(version.isEmpty()){
            version="1.1";
        }
        commonBean.addMetadataValue(el, "Budget", "Versione", version,service);
        commonBean.closeDocumentService(service);
    }

}
