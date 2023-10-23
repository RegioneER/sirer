package it.cineca.siss.axmr3.sirer.actions;

import java.io.ByteArrayOutputStream;
import it.cineca.siss.axmr3.authentication.IAuthority;
import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.authentication.services.SissUserService;
import it.cineca.siss.axmr3.doc.beans.InternalServiceBean;
import it.cineca.siss.axmr3.doc.entities.*;
import it.cineca.siss.axmr3.doc.notRequestScopedBean.ProcessActionsBean;
import it.cineca.siss.axmr3.doc.notRequestScopedBean.ProcessException;
import it.cineca.siss.axmr3.doc.types.PostResult;
import it.cineca.siss.axmr3.doc.web.services.DocumentService;
import it.cineca.siss.axmr3.exceptions.AxmrGenericException;
import it.cineca.siss.axmr3.log.Log;
import it.cineca.siss.axmr3.transactions.Axmr3TXManagerNonRequestScoped;
import it.cineca.siss.axmr3.transactions.MultiSessionTXManager;
import org.activiti.engine.RuntimeService;
import org.activiti.engine.TaskService;
import org.activiti.engine.delegate.DelegateExecution;
import org.activiti.engine.delegate.DelegateTask;
import org.activiti.engine.runtime.ProcessInstance;
import org.activiti.engine.task.Task;
import org.apache.log4j.Logger;
import org.joda.time.LocalDate;
import org.joda.time.Months;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.security.core.context.SecurityContextHolder;

import javax.sql.DataSource;
import java.io.*;
import java.io.File;
import java.sql.*;
import java.sql.Date;
import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;
import java.util.zip.ZipOutputStream;

/**
 * Created by vmazzeo on 13/02/2017.
 */
public class ProcessBean implements Serializable {

    @Autowired
    @Qualifier(value = "processActions")
    protected ProcessActionsBean commonBean;

    public DataSource getCommonBean() {
        return dataSource;
    }

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
    protected Axmr3TXManagerNonRequestScoped globalTx;

    public Axmr3TXManagerNonRequestScoped getGlobalTx() {
        return globalTx;
    }

    public void setGlobalTx(Axmr3TXManagerNonRequestScoped globalTx) {
        this.globalTx = globalTx;
    }

    @Autowired
    protected SissUserService userService;

    public SissUserService getUserService() {
        return userService;
    }

    public void setUserService(SissUserService userService) {
        this.userService = userService;
    }

    public DocumentService getDocumentService() throws Exception {
        DocumentService service = new DocumentService();
        service.setTxManager(globalTx);
        service.afterPropertiesSet();
        return service;
    }

    public void closeDocumentService() {
        globalTx.destroy();
    }

    public ProcessBean() {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Inizializzo il bean it.cineca.siss.axmr3.cegemelli.ProcessActionsBean");
    }

    public void createCentroChildren(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        commonBean.closeDocumentService(service);
    }

    public void abilitaAO(String elementId, DelegateExecution execution) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(elementId);
        String idCentro = getElementIdCentro(elementId, service);
        Element elCentro = service.getElement(idCentro);
        String idStruttura = elCentro.getFieldDataDecode("IdCentro", "Struttura");
        Connection conn = dataSource.getConnection();
        //Element el=service.getElement(Long.parseLong(elementId));
        //Long idStudio= (Long) el.getParent().getfieldData("UniqueIdStudio", "id").get(0);
        String sql1 = "select replace(nome_gruppo,?,'') gruppo from ana_gruppiu where descrizione=?";
        it.cineca.siss.axmr3.log.Log.debug(getClass(), sql1);
        PreparedStatement stmt = conn.prepareStatement(sql1);
        stmt.setString(1, "CRMS_");
        stmt.setString(2, idStruttura);
        ResultSet rset = stmt.executeQuery();

        String struttura = "";

        if (rset.next()) struttura = rset.getString("gruppo");
        conn.close();
        if (!struttura.isEmpty() && !struttura.equals("*")) {
            commonBean.changePermissionToGroup(el.getId().toString(), "V,AC,B", "", struttura, service);
            execution.setVariable("enabledAO", struttura);
        }

        commonBean.closeDocumentService(service);
    }

    public void aggiungiBottoneRiversamento() throws Exception {
        DocumentService service = commonBean.getDocumentService();
        IUser user = commonBean.getUser("CTC");
        LinkedList<String> types = new LinkedList<String>();
        types.add("Centro");
        List<Element> centri = service.getElementsByTypes(user, types);
        for (Element centro : centri) {
            String stato = centro.getFieldDataCode("statoValidazioneCentro", "valCTC");
            if (stato == null || stato.isEmpty()) {
                service.startProcess(user, centro, "InviaDatiCE");
            }

        }


        commonBean.closeDocumentService(service);
    }

    public void aggiungiBottoneChiusura() throws Exception {
        DocumentService service = commonBean.getDocumentService();
        IUser user = commonBean.getUser("CTC");
        LinkedList<String> types = new LinkedList<String>();
        types.add("Centro");
        List<Element> centri = service.getElementsByTypes(user, types);
        for (Element centro : centri) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "centro = " + centro);
            String stato = centro.getFieldDataCode("statoValidazioneCentro", "valCTC");
            //if(stato==null || stato.isEmpty()){
            if (stato != null && !stato.isEmpty() && stato.equals("1")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "aggiungo a centro = " + centro);
                service.startProcess(user, centro, "Chiusura");
            }

        }


        commonBean.closeDocumentService(service);
    }

    //TOSCANA-174
    public void actionPostPrimoArr(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element elArr = service.getElement(elementId);
        Element elCentro = elArr.getParent();
        IUser user = commonBean.getUser("CTC");

        it.cineca.siss.axmr3.log.Log.debug(getClass(), "aggiungo a centro = " + elCentro);
        service.startProcess(user, elCentro, "Chiusura");
        service.startProcess(user, elCentro, "ArrPrimoPazTrue");

        commonBean.closeDocumentService(service);
    }

    //SIRER-60
    public void creaChiusuraCentro(String elementId) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "INIZIO creaChiusuraCentro");
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "id AvvioCentro : " + elementId);

        DocumentService service = commonBean.getDocumentService();
        Element elAvvioCentro = service.getElement(elementId);
        Element elCentro = elAvvioCentro.getParent();
        //CREO CHIUSURA
        Long newChiusuraCentroId = commonBean.createChild(elCentro.getId().toString(), "CTC", "ChiusuraCentro", service);
        //METTO AVVIO IN READONLY avvio e allegati
        service.changePermissionToGroup(elAvvioCentro, "V,B", "", "CTC");
        service.changePermissionToGroup(elAvvioCentro, "V,B", "", "PI");
        service.changePermissionToGroup(elAvvioCentro, "V,B", "", "COORD");
        service.changePermissionToGroup(elAvvioCentro, "V,B", "", "SEGRETERIA");
        List<Element> elAllegatiAvvio = elAvvioCentro.getChildrenByType("AllegatoAvvioCentro");
        for (Element child : elAllegatiAvvio) {
            service.changePermissionToGroup(child, "V,B", "", "CTC");
            service.changePermissionToGroup(child, "V,B", "", "PI");
            service.changePermissionToGroup(child, "V,B", "", "COOD");
            service.changePermissionToGroup(child, "V,B", "", "SEGRETERIA");
        }
        //CHIUDO PROCESSO RITIRA CENTRO
        List<ProcessInstance> activeProcesses;
        activeProcesses = service.getActiveProcesses(elCentro);
        String processDefinition = "RitiraCentro:";
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "CERCO I WF ASSOCIATI AL CENTRO= ");
        for (ProcessInstance process : activeProcesses) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "HO TROVATO = " + process.getProcessDefinitionId());
            if (process.getProcessDefinitionId().startsWith(processDefinition)) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "PROVO A TERMINARE = " + process.getProcessDefinitionId());
                String user = "CTC";
                service.terminateProcess(userService.getUser(user), process.getProcessInstanceId());
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "HO TERMINATO = " + process.getProcessDefinitionId());
            }
        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "FINE creaChiusuraCentro, ChiusuraCentro ID: " + newChiusuraCentroId);
        commonBean.closeDocumentService(service);
    }

    public void actionPostPrimoArrTrue(String elementId, String dataPrimoArr) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "actionPostPrimoArrTrue");
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "id centro : " + elementId);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "dataPrimoArr : " + dataPrimoArr);

        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(elementId);

        List<Element> elArrPrimoPaz = el.getChildrenByType("ArruolamentoPrimoPaz");
        for (Element child : elArrPrimoPaz) {

            it.cineca.siss.axmr3.log.Log.debug(getClass(), "elArrPrimoPaz= " + child.getId().toString());

            String dataAperturaCentro = child.getFieldDataFormattedDates("DatiArrPrimoPaz", "dataAperturaCentro", "dd/MM/yyyy").get(0);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "dataAperturaCentro= " + dataAperturaCentro);

            if (dataAperturaCentro != null && !dataAperturaCentro.isEmpty()) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "id elemento ArruolamentoPrimoPaz : " + child.getId().toString());
                commonBean.addMetadataValue(child.getId().toString(), "DatiArrPrimoPaz", "dataPrimoArr", dataPrimoArr);

            }
        }
        commonBean.closeDocumentService(service);
    }

    public Long getUniqueStudioId(String elementId) {

        String sqlQuery = "select CE_PK_SEQ.nextval from dual";
        Connection conn;
        try {
            conn = dataSource.getConnection();
            PreparedStatement stmt = conn.prepareStatement(sqlQuery);
            ResultSet rset = stmt.executeQuery();
            Long id = null;
            if (rset.next()) {
                id = rset.getLong(1);

            }
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "L'id atteso e' : " + String.valueOf(id));
            conn.close();
            return id;
        } catch (SQLException e) {
            Logger.getLogger(this.getClass()).error(e.getMessage(), e);
        }
        return null;
    }

    public void createCenterInCeOnline(String elementId, Long idStudCeOnline) throws Exception {


        it.cineca.siss.axmr3.log.Log.debug(getClass(), "inizio createCenterInCeOnline");
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "idStudCeOnline=" + idStudCeOnline);
        DocumentService service = commonBean.getDocumentService();
        Connection conn = dataSource.getConnection();
        Element el = service.getElement(Long.parseLong(elementId));

        boolean recordPresent0 = false;
        boolean recordPresent = false;
        boolean recordPresent4 = false;
        Long idStudio;
        String sql0 = "";
        String sql1 = "";
        String sql2 = "";
        String sql3 = "";
        String sql4 = "";
        String n = "";
        Integer CurrCenterProgr = 0;
        Integer NextCenterProgr;
        Integer idCentro;
        String DenCentro = "";
        Integer idIstituto;
        String DenIstituto = "";
        String DirIstituto = "";
        Integer idDipartimento;
        String DenDipartimento = "";
        String DirDipartimento = "";
        Integer IdUnitaOperativa;
        String DenUnitaOperativa = "";
        String DirUnitaOperativa = "";
        Integer IdPrincInv;
        String DenPrincInv = "";
        Long IdOggetto;
        String NumPaz = "";
        Integer visitclose_centro = 0;
        Integer fine_centro = 0;
        String corrispettivo = "";
        Element budDef;
        Integer ccp = 0;
        Integer docPresente = 0;
        String direttoreUO = "";
        String mailPI = "";
        String telefonoPI = "";
        Integer Coord = 0;
        String CoordDec = "";
        Integer durSper;
        Integer durSperUnit;
        String durSperUnitDec = "";
        Integer monoMulti;
        String monoMultiDesc = "";
        String UseridIns = "";

        idCentro = Integer.valueOf(el.getfieldData("IdCentro", "Struttura").get(0).toString().split("###")[0]);
        DenCentro = el.getfieldData("IdCentro", "Struttura").get(0).toString().split("###")[1];

        String sql = "select centro from ce_elenco_centriloc where id=?";
        PreparedStatement struttura_stmt = conn.prepareStatement(sql);
        struttura_stmt.setInt(1, idCentro);
        ResultSet struttura_rset = struttura_stmt.executeQuery();
        boolean recordPresente1 = struttura_rset.next();
        Integer CE;
        if (recordPresente1) {
            CE = struttura_rset.getInt("centro");
            switch (CE) {
                case 1:
                    UseridIns = "LPOLVERELLI";//CEAV Sud Est
                    break;
                case 2:
                    UseridIns = "DCARIGNANI";//CEAV Nord Ovest
                    break;
                case 3:
                    UseridIns = "MVIETRI";//CEAV Centro
                    break;
                case 4:
                    UseridIns = "MLEO";// CEP
                    break;
            }

        }
        if (Integer.valueOf(el.getParent().getfieldData("datiStudio", "popolazioneStudio").get(0).toString().split("###")[0]) == 1) {
            UseridIns = "MLEO";//se pediatrico sovrascrivo per assegnarlo CEP!!!!
        }
        //GC 30-06-2016 Se è un nuovo studio -> mantengo UniqueIdStudio (id_stud.nextprogr in CE TOSCANA)
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "idStudCeOnline=" + idStudCeOnline);
        if (idStudCeOnline == 0) {
            idStudio = Long.valueOf(el.getParent().getfieldData("UniqueIdStudio", "id").get(0).toString());
            createStudioInCeOnline(conn, elementId, service, UseridIns);
            //it.cineca.siss.axmr3.log.Log.debug(getClass(),"idStudio="+idStudio);
            //sql1="select count(*) as n from CE_REGISTRAZIONE where ID_STUD="+idStudio;
            //PreparedStatement stmt = conn.prepareStatement(sql1);
            //ResultSet rset = stmt.executeQuery();
            //
            //recordPresent=rset.next();
            //it.cineca.siss.axmr3.log.Log.debug(getClass(),"recordPresent="+recordPresent);
            //if(recordPresent) {n=rset.getString("n");}
            //it.cineca.siss.axmr3.log.Log.debug(getClass(),"n="+n);
        } else { //Altrimenti
            // prendo l'id_stud dello studio selezionato in tendina da CE TOSCANA e faccio update di UniqueIdStudio
            idStudio = idStudCeOnline;
            commonBean.addMetadataValue(el.getParent(), "UniqueIdStudio", "id", idStudCeOnline, service);
            //TOSCANA-160: aggiorno anche ce_registrazione.crpms_studio_progr con l'el.getParent()
            String sql_registrazione_stud = "update ce_registrazione set crpms_studio_progr='" + el.getParent().getId() + "' where id_stud=" + idStudCeOnline;
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "sql_registrazione_stud = " + sql_registrazione_stud);
            PreparedStatement stmt_registrazione_stud = conn.prepareStatement(sql_registrazione_stud);
            ResultSet rset1_registrazione_stud = stmt_registrazione_stud.executeQuery();
        }

        //Controllo che il centro non sia già stato inserito attraverso il bottone di invio dati al CE
        sql0 = "select count(*) as ccp from CE_CENTRILOCALI where ID_STUD=" + idStudio + " and crpms_center_progr=" + elementId;
        PreparedStatement stmt0 = conn.prepareStatement(sql0);
        ResultSet rset0 = stmt0.executeQuery();
        recordPresent0 = rset0.next();
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "recordPresent0=" + recordPresent0);
        if (recordPresent0) {
            ccp = rset0.getInt("ccp");
        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "ccp=" + ccp);
        if (ccp > 0) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Il centro è già stato inserito ed esco dal metodo createCenterInCeOnline");
            conn.close();
            commonBean.closeDocumentService(service);
            return;
        }

        //if(n.equals("0")){
        //    //Richiamare il metodo createStudioInCeOnline per inserire prima lo studio
        //    createStudioInCeOnline(conn,elementId, service);
        //}else{
        //Controllo la min(visitclose) della visitnum=0 per capire come impostare la visitclose del centro che sto inserendo
        sql4 = "select min(visitclose) VC from CE_COORDINATE where ID_STUD=" + idStudio + " and visitnum=0 and esam=10";
        PreparedStatement stmt4 = conn.prepareStatement(sql4);
        ResultSet rset4 = stmt4.executeQuery();

        recordPresent4 = rset4.next();
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "recordPresent4=" + recordPresent4);
        if (recordPresent4) {
            visitclose_centro = rset4.getInt("VC");
            fine_centro = rset4.getInt("VC");
        }
        //}

        //Prendo il progressivo dell'ultimo centro e aggiungo 1
        sql2 = "select nvl(max(progr),0) as CurrCenterProgr from CE_CENTRILOCALI where ID_STUD=" + idStudio;
        PreparedStatement stmt2 = conn.prepareStatement(sql2);
        ResultSet rset2 = stmt2.executeQuery();

        recordPresent = rset2.next();
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "ultimo progressivo centro=" + recordPresent);
        if (recordPresent) {
            CurrCenterProgr = Integer.valueOf(rset2.getString("CurrCenterProgr"));
        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "CurrCenterProgr=" + CurrCenterProgr);
        NextCenterProgr = CurrCenterProgr + 1;

        //Inserisco il centro
        CallableStatement cstmt = null;
        String procedure = "{call INSERT_CENTRO_CRPMS_TO_CE(?,?,?, ?,?,?, ?,?,?, ?,?,?, ?,?,?, ?,?,?, ?,?,?, ?,?,?)}";

        cstmt = conn.prepareCall(procedure);

        //sysdate
        //java.util.Date today = new java.util.Date();
        //Timestamp date = new Timestamp(today.getTime());
        //cstmt.setTimestamp(5, date);

        cstmt.setLong(1, idStudio);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "1 - Long - " + idStudio.toString());
        //PROGR di coordinate per l'esam 10
        cstmt.setInt(2, NextCenterProgr);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "2 - Int - " + NextCenterProgr.toString());


        cstmt.setInt(3, idCentro);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "3 - Int - " + idCentro.toString());
        cstmt.setString(4, DenCentro);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "4 - String - " + idCentro);

        IdUnitaOperativa = Integer.valueOf(el.getfieldData("IdCentro", "UO").get(0).toString().split("###")[0]);
        DenUnitaOperativa = el.getfieldData("IdCentro", "UO").get(0).toString().split("###")[1];
        cstmt.setInt(5, IdUnitaOperativa);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "5 - Int - " + IdUnitaOperativa.toString());
        cstmt.setString(6, DenUnitaOperativa);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "6 - String - " + DenUnitaOperativa);


        IdPrincInv = Integer.valueOf(el.getFieldDataCode("IdCentro", "PINomeCognome"));
        DenPrincInv = el.getFieldDataDecode("IdCentro", "PINomeCognome");
        cstmt.setInt(7, IdPrincInv);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "7 - Int - " + IdPrincInv.toString());
        cstmt.setString(8, DenPrincInv);
        cstmt.setString(9, DenPrincInv);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "8 e 9 - String - " + DenPrincInv);

        IdOggetto = el.getId();
        cstmt.setLong(10, IdOggetto);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "10 - Long - " + IdOggetto.toString());

        //VISITNUM_PROGR di coordinate per gli esami 22 e 23
        cstmt.setInt(11, CurrCenterProgr);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "11 - Int - " + CurrCenterProgr.toString());

        NumPaz = el.getFieldDataString("datiCentro", "NrPaz");
        cstmt.setString(12, NumPaz);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "12 - String - " + NumPaz);

        cstmt.setInt(13, visitclose_centro);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "13 - Int - " + visitclose_centro.toString());

        cstmt.setInt(14, fine_centro);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "14 - Int - " + fine_centro.toString());


        corrispettivo = el.getFieldDataString("IdCentro", "corrispettivoEuro");
        if (corrispettivo != null) {
            cstmt.setString(15, corrispettivo);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "15 - String - " + corrispettivo);
        } else {
            cstmt.setNull(15, Types.VARCHAR);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "15 - Null - ");
        }

        direttoreUO = el.getFieldDataString("IdCentro", "direttoreUO");
        if (direttoreUO != null) {
            cstmt.setString(16, direttoreUO);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "16 - String - " + direttoreUO);
        } else {
            cstmt.setNull(16, Types.VARCHAR);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "16 - Null - ");
        }

        mailPI = el.getFieldDataString("IdCentro", "emailPI");
        if (mailPI != null) {
            cstmt.setString(17, mailPI);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "17 - String - " + mailPI);
        } else {
            cstmt.setNull(17, Types.VARCHAR);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "17 - Null - ");
        }

        telefonoPI = el.getFieldDataString("IdCentro", "telefonoPI");
        if (telefonoPI != null) {
            cstmt.setString(18, telefonoPI);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "18 - String - " + telefonoPI);
        } else {
            cstmt.setNull(18, Types.VARCHAR);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "18 - Null - ");
        }

        if (el.getfieldData("AnagPI", "coord") != null && el.getfieldData("AnagPI", "coord").size() > 0) { //TODO DA ASSOCIARE
            Coord = Integer.valueOf(el.getFieldDataCode("AnagPI", "coord"));
            cstmt.setInt(19, Coord);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Coord=" + Coord);

            CoordDec = el.getFieldDataDecode("AnagPI", "coord");
            cstmt.setString(20, CoordDec);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "CoordDec=" + CoordDec);
        } else {
            cstmt.setNull(19, Types.NUMERIC);
            cstmt.setNull(20, Types.VARCHAR);
        }

        if (el.getfieldData("AnagPI", "durSper") != null && el.getfieldData("AnagPI", "durSper").size() > 0) { //TODO DA ASSOCIARE
            durSper = Integer.valueOf(el.getFieldDataString("AnagPI", "durSper"));
            cstmt.setInt(21, durSper);
        } else {
            cstmt.setNull(21, Types.NUMERIC);
        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "durSper=");


        if (el.getfieldData("AnagPI", "durSperUnit") != null && el.getfieldData("AnagPI", "durSperUnit").size() > 0) { //TODO DA ASSOCIARE
            durSperUnit = Integer.valueOf(el.getFieldDataCode("AnagPI", "durSperUnit"));
            cstmt.setInt(22, durSperUnit);

            durSperUnitDec = el.getFieldDataDecode("AnagPI", "durSperUnit");
            cstmt.setString(23, durSperUnitDec);
        } else {
            cstmt.setNull(22, Types.NUMERIC);
            cstmt.setNull(23, Types.VARCHAR);
        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "durSperUnit=");
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "durSperUnitDec=" + durSperUnitDec);

        if (UseridIns != "") {
            cstmt.setString(24, UseridIns);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "USERID_INS= " + UseridIns);
        }

        cstmt.execute();

        /*GC 12/07/2016 - Documentazione centro-specifica*/

        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Riversamento documenti centro-specifici in CE-ONLINE");
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "elCentro=" + el);
        List<Element> elAllegato = el.getChildrenByType("AllegatoCentro");
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "elAllegato=" + elAllegato);
        for (Element child : elAllegato) {
            docPresente = 1;
            //copiaAllegatoCentroInCeOnline(child);//TOSCANA-168 porto tutto dentro un nuovo metodo da chiamare anche dal nuovo WF
            String sqlprogr = "";
            boolean recordPresente;
            Integer p = null;
            String docCs = "";
            String docCsDen = "";
            String docCsAltro = "";
            String docvers = "";
            String docnote = "";
            String sqlIdDocs = "";
            //boolean recordPresente1;
            Integer iddoc;
            String ext = "";
            String autore = "";
            long idTipoRef;
            String keywords = "";
            String fileCeOnline = "";

            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Sono nel ciclo for dei documenti allegati");
            String filename = child.getFile().getFileName();
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "nomefile= " + filename);

            Integer tipoDoc = Integer.valueOf(child.getFieldDataCode("DocCentroSpec", "TipoDocumento"));

            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Ho trovato un documento da portare in CE-ONLINE");


            //if(tipoDoc.equals(4)){docCs="4"; docCsDen="CV dello sperimentatore";}
            //if(tipoDoc.equals(-9999)){docCs="23"; docCsDen="Altro"; docCsAltro=child.getFieldDataDecode("DocCentroSpec", "TipoDocumento");}


            //GC 15/07/2016 Query per mappatura documenti in CE-ONLINE
            String sqlDocsCE = "select id,descrizione from CRMS_DOC_LOC,CE_DOC_LOC where id_doc_ce=id and code=" + tipoDoc;
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Query = " + sqlDocsCE);
            PreparedStatement stmtdocce = conn.prepareStatement(sqlDocsCE);
            ResultSet rsetDocsCe = stmtdocce.executeQuery();
            recordPresente1 = rsetDocsCe.next();
            if (recordPresente1) {
                docCs = rsetDocsCe.getString("id");
                docCsDen = rsetDocsCe.getString("descrizione");
                //HDCE-3084  compila sempre il campo DOC_LOC_ALTRO che andrebbe compilato solo in caso di tipo "Altro"
                if (docCs.equals("18")) {
                    docCsAltro = child.getFieldDataDecode("DocCentroSpec", "TipoDocumento");
                }
            }


            CallableStatement cstmt2 = null;
            String procedure2 = "{call INSERT_DOC_CENTRO_CRPMS_TO_CE(?,?,?, ?,?,?, ?,?,?, ?,?,?, ?,?,?, ?,?)}";

            cstmt2 = conn.prepareCall(procedure2);

            cstmt2.setLong(1, idStudio);

            //recupero il prossimo progressivo del documento
            sqlprogr = "select nvl(max(progr),0)+1 as p from CE_COORDINATE where ID_STUD=" + idStudio + " and visitnum=1 and visitnum_progr=" + CurrCenterProgr + " and esam=23";
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "sqlprogr=" + sqlprogr);
            PreparedStatement stmt = conn.prepareStatement(sqlprogr);
            ResultSet rset = stmt.executeQuery();

            recordPresente = rset.next();
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "recordPresente=" + recordPresente);
            if (recordPresente) {
                keywords = "DOC_CENTROSPEC";
                p = rset.getInt("p");
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "p=" + p);
                cstmt2.setLong(2, p);

                if (CurrCenterProgr == 0) {
                    if (p > 1) {
                        keywords += "_" + p;
                    }
                } else {
                    keywords += "_" + p + "_" + CurrCenterProgr;
                }

                it.cineca.siss.axmr3.log.Log.debug(getClass(), "keywords=" + keywords);
            }

            cstmt2.setString(3, docCs);
            cstmt2.setString(4, docCsDen);
            cstmt2.setString(5, docCsAltro);

            Calendar dataDoc = child.getFile().getDate();
            //java.sql.Date sqlDate =  new java.sql.Date(dataDoc.getTime().getTime() );

            if (dataDoc != null) {
                java.sql.Date sqlDate = new java.sql.Date(dataDoc.getTime().getTime());
                cstmt2.setDate(6, sqlDate);
                cstmt2.setString(7, "OKOKOK");
            } else {
                cstmt2.setNull(6, Types.DATE);
                cstmt2.setNull(7, Types.VARCHAR);
            }

            docvers = child.getFile().getVersion();
            if (docvers != null) {
                cstmt2.setString(8, docvers);
            } else {
                cstmt2.setNull(8, Types.VARCHAR);
            }

            docnote = child.getFile().getNote();
            if (docnote != null) {
                cstmt2.setString(9, docnote);
            } else {
                cstmt2.setNull(9, Types.VARCHAR);
            }

            int i = filename.lastIndexOf(".");
            if (i > 0) {
                ext = filename.substring(i + 1);
            }

            cstmt2.setString(11, ext);

            sqlIdDocs = "select DOCS_ID.NEXTVAL as iddoc from DUAL";
            PreparedStatement stmt1 = conn.prepareStatement(sqlIdDocs);
            ResultSet rset1 = stmt1.executeQuery();
            recordPresente1 = rset1.next();
            if (recordPresente1) {
                iddoc = rset1.getInt("iddoc");
                cstmt2.setInt(10, iddoc);

                //Scrivo il documento nella cartella del CE-ONLINE
                byte[] contenuto = child.getFile().getContent().getContent();
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "contenuto=" + contenuto);
                fileCeOnline = "Doc_Area" + iddoc + "." + ext;
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "recordPresente=" + recordPresente);
                File destFolder = new File("/http/servizi/siss-bundle-01/ricercaclinica-toscana.cineca.it/html/uxmr/WCA/docs/" + fileCeOnline);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "destFolder=" + destFolder);
                FileOutputStream fos = new FileOutputStream(destFolder);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "fos=" + fos);
                fos.write(contenuto);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "write");
                fos.close();
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "close");
            }

            cstmt2.setString(12, filename);

            autore = child.getFile().getAutore();
            if (autore != null) {
                cstmt2.setString(13, autore);
            } else {
                cstmt2.setNull(13, Types.VARCHAR);
            }

            idTipoRef = idStudio + 10000000;
            cstmt2.setLong(14, idTipoRef);

            cstmt2.setString(15, keywords);

            cstmt2.setInt(16, CurrCenterProgr);

            cstmt2.setString(17, UseridIns);

            cstmt2.execute();
            //TOSCANA-168 termino il processo "copiaAllegatoCentroInCeOnline"di invio del singolo allegato al CE

            List<ProcessInstance> activeProcesses;
            activeProcesses = service.getActiveProcesses(child);
            String processDefinition = "copiaAllegatoCentroInCeOnline:";
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "CERCO I WF ASSOCIATI ALL'ALLEGATO= ");
            for (ProcessInstance process : activeProcesses) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "HO TROVATO = " + process.getProcessDefinitionId());
                if (process.getProcessDefinitionId().startsWith(processDefinition)) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "PROVO A TERMINARE = " + process.getProcessDefinitionId());
                    String user = "CTC";
                    service.terminateProcess(userService.getUser(user), process.getProcessInstanceId());
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "HO TERMINATO = " + process.getProcessDefinitionId());
                }
            }
        }

        it.cineca.siss.axmr3.log.Log.debug(getClass(), "docPresente = " + docPresente);

        //non ci sono documenti nel CRPMS, quindi bisogna richiamare la procedura per l'inserimento del record del documento in ce_coordinate
        if (docPresente.equals(0)) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Non ho trovato documenti quindi inserisco il record del documento in ce_coordinate");
            CallableStatement cstmt3 = null;
            String procedure3 = "{call INSERTCE_COORDINATE(?,?,?,?,?,?,?,?,?,?,?,?)}";
            cstmt3 = conn.prepareCall(procedure3);

            cstmt3.setInt(1, 1);
            cstmt3.setInt(2, CurrCenterProgr);
            cstmt3.setInt(3, 1);
            cstmt3.setInt(4, 23);
            cstmt3.setNull(5, Types.NUMERIC);
            cstmt3.setNull(6, Types.NUMERIC);

            java.util.Date d = new java.util.Date();
            java.sql.Date oggi = new java.sql.Date(d.getTime());

            cstmt3.setDate(7, oggi);
            cstmt3.setDate(8, oggi);

            cstmt3.setString(9, UseridIns);
            cstmt3.setInt(10, 0);
            cstmt3.setLong(11, idStudio);
            cstmt3.setInt(12, 1);


            cstmt3.execute();
        }
        commonBean.addMetadataValue(el, "IdCentro", "inviatoCE", "1", service);

        conn.close();
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "fine createCenterInCeOnline");
        commonBean.closeDocumentService(service);
    }

    private void createStudioInCeOnline(Connection conn, String elementId, DocumentService service, String userid_ins) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "inizio createStudioInCeOnline");
        Element el = service.getElement(Long.parseLong(elementId));

        CallableStatement cstmt = null;
        //String procedure="{call INSERT_STUDIO_CRPMS_TO_CE(?,?,?, ?,?,?, ?,?,? , ?,?,?, ?,?,?, ?,?,? , ?,?,?, ?,?,?, ?,?,? , ?,?,?, ?,?,?, ?,?,? , ?,?,?, ?,?,?, ?,?,? , ?,?,?, ?,?,?, ?,?,? , ?,?,?, ?,?,?, ?,?,? , ?,?)}";
        String procedure = "{call INSERT_STUDIO_CRPMS_TO_CE(?,?,?, ?,?,?, ?,?,?, ?,?,?, ?,?,?, ?,?,?, ?,?,?, ?,?,?, ?,?,?, ?,?,?, ?,?,?, ?,?,?,?)}";
        cstmt = conn.prepareCall(procedure);


        Long idStudio; //1
        Long crpms_studio_progr; //2
        Integer TipoStudio; //3
        String DenStudio = ""; //4
        String eudractNumber = ""; //5
        Integer Fase; //6
        String FaseDec = ""; //7
        Integer Profit; //8
        String ProfitDec = ""; //9
        Integer DurataTot;//10
        Integer DurataUnita;//11
        String DurataUnitaDec = "";//12
        Integer EsamRiassunto; //13
        Integer EsamTerapiaStudio;//14
        Integer Pediatrico;//15
        String PediatricoDec;//16
        String CodiceProt = "";//17
        String TitoloProt = "";//18
        String DenSP = ""; //19
        String DenCRO = ""; //20
        Integer IdSP; //21
        Integer IdCRO;//22
        Integer FonteFinTerzi;//23
        String FonteFinTerziDec;//24
        Integer FonteFinSpec;//25
        String FonteFinSpecDec;//26
        Integer FonteFinSponsor;//27
        String FonteFinSponsorDec;//28
        String FonteFinFondazione;//29
        String FonteFinAltro;//30
        String RefSponsor;//31
        String TelSponsor;//32
        String EmailSponsor;//33
        String RefCRO;//34
        String TelCRO;//35
        String EmailCRO;//36
        String UseridIns = userid_ins;//37

        Element studio = el.getParent();
        idStudio = Long.valueOf(studio.getfieldData("UniqueIdStudio", "id").get(0).toString());
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "idStudio= " + idStudio);

        cstmt.setLong(1, idStudio);

        crpms_studio_progr = studio.getId();
        cstmt.setLong(2, crpms_studio_progr);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "crpms_studio_progr= " + crpms_studio_progr);

        TipoStudio = Integer.valueOf(studio.getfieldData("datiStudio", "tipoStudio").get(0).toString().split("###")[0]);
        cstmt.setInt(3, TipoStudio);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "TipoStudio= " + TipoStudio);

        DenStudio = studio.getfieldData("datiStudio", "tipoStudio").get(0).toString().split("###")[1];
        cstmt.setString(4, DenStudio);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "DenStudio= " + DenStudio);


        if (studio.getfieldData("datiStudio", "eudractNumber") != null && studio.getfieldData("datiStudio", "eudractNumber").size() > 0) {
            eudractNumber = studio.getFieldDataString("datiStudio", "eudractNumber");
            cstmt.setString(5, eudractNumber);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "eudractNumber= " + eudractNumber);
        } else {
            cstmt.setNull(5, Types.VARCHAR);
        }
        if (studio.getfieldData("datiStudio", "fase") != null && studio.getfieldData("datiStudio", "fase").size() > 0) {
            Fase = Integer.valueOf(studio.getfieldData("datiStudio", "fase").get(0).toString().split("###")[0]);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Fase = " + Fase);
            FaseDec = studio.getfieldData("datiStudio", "fase").get(0).toString().split("###")[1];
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "FaseDec = " + FaseDec);
            cstmt.setInt(6, Fase);
            cstmt.setString(7, FaseDec);
        } else {
            cstmt.setNull(6, Types.NUMERIC);
            cstmt.setNull(7, Types.VARCHAR);
        }

        Profit = Integer.valueOf(studio.getfieldData("datiStudio", "Profit").get(0).toString().split("###")[0]);
        cstmt.setInt(8, Profit);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Profit=" + Profit);

        ProfitDec = studio.getfieldData("datiStudio", "Profit").get(0).toString().split("###")[1];
        cstmt.setString(9, ProfitDec);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "ProfitDec=" + ProfitDec);

        if (studio.getfieldData("datiStudio", "durataTot") != null && studio.getfieldData("datiStudio", "durataTot").size() > 0) {
            DurataTot = Integer.valueOf(studio.getfieldData("datiStudio", "durataTot").get(0).toString());
            cstmt.setInt(10, DurataTot);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "DurataTot= " + DurataTot);
        } else {
            cstmt.setNull(10, Types.NUMERIC);
        }

        if (studio.getfieldData("datiStudio", "durataTotSelect") != null && studio.getfieldData("datiStudio", "durataTotSelect").size() > 0) {
            DurataUnita = Integer.valueOf(studio.getfieldData("datiStudio", "durataTotSelect").get(0).toString().split("###")[0]);
            cstmt.setInt(11, DurataUnita);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "DurataUnita= " + DurataUnita);
            DurataUnitaDec = studio.getfieldData("datiStudio", "durataTotSelect").get(0).toString().split("###")[1];
            cstmt.setString(12, DurataUnitaDec);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "DurataUnitaDec= " + DurataUnitaDec);
        } else {
            cstmt.setNull(11, Types.NUMERIC);
            cstmt.setNull(12, Types.VARCHAR);
        }

        Pediatrico = Integer.valueOf(studio.getfieldData("datiStudio", "popolazioneStudio").get(0).toString().split("###")[0]);
        cstmt.setInt(15, Pediatrico);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "popolazioneStudio=" + Pediatrico);

        PediatricoDec = studio.getfieldData("datiStudio", "popolazioneStudio").get(0).toString().split("###")[1];
        cstmt.setString(16, PediatricoDec);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "popolazioneStudioDec=" + PediatricoDec);

        CodiceProt = studio.getfieldData("IDstudio", "CodiceProt").get(0).toString();
        cstmt.setString(17, CodiceProt);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "CodiceProt=" + CodiceProt);

        TitoloProt = studio.getfieldData("IDstudio", "TitoloProt").get(0).toString();
        cstmt.setString(18, TitoloProt);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "TitoloProt=" + TitoloProt);

        if (studio.getFieldDataElement("datiPromotore", "promotore") != null && studio.getFieldDataElement("datiPromotore", "promotore").size() > 0) {
            Element sp = studio.getFieldDataElement("datiPromotore", "promotore").get(0);

            IdSP = Integer.valueOf(sp.getfieldData("DatiPromotoreCRO", "id").get(0).toString());
            cstmt.setInt(21, IdSP);
            DenSP = sp.getfieldData("DatiPromotoreCRO", "denominazione").get(0).toString();
            cstmt.setString(19, DenSP);
        } else {
            cstmt.setNull(21, Types.NUMERIC);
            cstmt.setString(19, "NA");
        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "ID SP= ");
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Den SP= " + DenSP);

        if (studio.getfieldData("datiCRO", "denominazione") != null && studio.getfieldData("datiCRO", "denominazione").size() > 0) {

            IdCRO = Integer.valueOf(((Element) studio.getfieldData("datiCRO", "denominazione").get(0)).getfieldData("DatiPromotoreCRO", "id").get(0).toString());
            cstmt.setInt(22, IdCRO);

            DenCRO = ((Element) studio.getfieldData("datiCRO", "denominazione").get(0)).getfieldData("DatiPromotoreCRO", "denominazione").get(0).toString();
            cstmt.setString(20, DenCRO);
        } else {
            cstmt.setNull(22, Types.NUMERIC);
            cstmt.setString(20, "NA");
        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "ID CRO= ");
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Den CRO= " + DenCRO);

        if (studio.getfieldData("datiStudio", "fonteFinTerzi") != null && studio.getfieldData("datiStudio", "fonteFinTerzi").size() > 0) {

            FonteFinTerzi = Integer.valueOf(studio.getfieldData("datiStudio", "fonteFinTerzi").get(0).toString().split("###")[0]);
            cstmt.setInt(23, FonteFinTerzi);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "FonteFinTerzi= " + FonteFinTerzi);

            FonteFinTerziDec = studio.getfieldData("datiStudio", "fonteFinTerzi").get(0).toString().split("###")[1];
            cstmt.setString(24, FonteFinTerziDec);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "FonteFinTerziDec= " + FonteFinTerziDec);
        } else {
            cstmt.setNull(23, Types.NUMERIC);
            cstmt.setNull(24, Types.VARCHAR);
        }

        if (studio.getfieldData("datiStudio", "fonteFinSpec") != null && studio.getfieldData("datiStudio", "fonteFinSpec").size() > 0) {

            FonteFinSpec = Integer.valueOf(studio.getfieldData("datiStudio", "fonteFinSpec").get(0).toString().split("###")[0]);
            cstmt.setInt(25, FonteFinSpec);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "FonteFinSpec= " + FonteFinSpec);

            FonteFinSpecDec = studio.getfieldData("datiStudio", "fonteFinSpec").get(0).toString().split("###")[1];
            cstmt.setString(26, FonteFinSpecDec);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "FonteFinSpecDec= " + FonteFinSpecDec);
        } else {
            cstmt.setNull(25, Types.NUMERIC);
            cstmt.setNull(26, Types.VARCHAR);
        }

        if (studio.getfieldData("datiStudio", "fonteFinSponsor") != null && studio.getfieldData("datiStudio", "fonteFinSponsor").size() > 0) {

            FonteFinSponsor = Integer.valueOf(studio.getfieldData("datiStudio", "fonteFinSponsor").get(0).toString().split("###")[0]);
            cstmt.setInt(27, FonteFinSponsor);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "FonteFinSponsor= " + FonteFinSponsor);

            FonteFinSponsorDec = studio.getfieldData("datiStudio", "fonteFinSponsor").get(0).toString().split("###")[1];
            cstmt.setString(28, FonteFinSponsorDec);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "FonteFinSponsorDec= " + FonteFinSponsorDec);
        } else {
            cstmt.setNull(27, Types.NUMERIC);
            cstmt.setNull(28, Types.VARCHAR);
        }

        if (studio.getfieldData("datiStudio", "fonteFinFondazione") != null && studio.getfieldData("datiStudio", "fonteFinFondazione").size() > 0) {
            FonteFinFondazione = studio.getFieldDataString("datiStudio", "fonteFinFondazione");
            cstmt.setString(29, FonteFinFondazione);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "fonteFinFondazione= " + FonteFinFondazione);
        } else {
            cstmt.setNull(29, Types.VARCHAR);
        }

        if (studio.getfieldData("datiStudio", "fonteFinAltro") != null && studio.getfieldData("datiStudio", "fonteFinAltro").size() > 0) {
            FonteFinAltro = studio.getFieldDataString("datiStudio", "fonteFinAltro");
            cstmt.setString(30, FonteFinAltro);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "fonteFinAltro= " + FonteFinAltro);
        } else {
            cstmt.setNull(30, Types.VARCHAR);
        }

        if (studio.getfieldData("datiPromotore", "RefNomeCognomepR") != null && studio.getfieldData("datiPromotore", "RefNomeCognomepR").size() > 0) {
            RefSponsor = studio.getFieldDataString("datiPromotore", "RefNomeCognomepR");
            cstmt.setString(31, RefSponsor);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "RefNomeCognomepR= " + RefSponsor);
        } else {
            cstmt.setNull(31, Types.VARCHAR);
        }

        if (studio.getfieldData("datiPromotore", "RefTelpR") != null && studio.getfieldData("datiPromotore", "RefTelpR").size() > 0) {
            TelSponsor = studio.getFieldDataString("datiPromotore", "RefTelpR");
            cstmt.setString(32, TelSponsor);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "RefTelpR= " + TelSponsor);
        } else {
            cstmt.setNull(32, Types.VARCHAR);
        }

        if (studio.getfieldData("datiPromotore", "RefEmailpR") != null && studio.getfieldData("datiPromotore", "RefEmailpR").size() > 0) {
            EmailSponsor = studio.getFieldDataString("datiPromotore", "RefEmailpR");
            cstmt.setString(33, EmailSponsor);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "RefEmailpR= " + EmailSponsor);
        } else {
            cstmt.setNull(33, Types.VARCHAR);
        }

        if (studio.getfieldData("datiCRO", "NomeReferenteR") != null && studio.getfieldData("datiCRO", "NomeReferenteR").size() > 0) {
            RefCRO = studio.getFieldDataString("datiCRO", "NomeReferenteR");
            cstmt.setString(34, RefCRO);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "NomeReferenteR= " + RefCRO);
        } else {
            cstmt.setNull(34, Types.VARCHAR);
        }

        if (studio.getfieldData("datiCRO", "telefonoR") != null && studio.getfieldData("datiCRO", "telefonoR").size() > 0) {
            TelCRO = studio.getFieldDataString("datiCRO", "telefonoR");
            cstmt.setString(35, TelCRO);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "telefonoR= " + TelCRO);
        } else {
            cstmt.setNull(35, Types.VARCHAR);
        }

        if (studio.getfieldData("datiCRO", "emailR") != null && studio.getfieldData("datiCRO", "emailR").size() > 0) {
            EmailCRO = studio.getFieldDataString("datiCRO", "emailR");
            cstmt.setString(36, EmailCRO);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "emailR= " + EmailCRO);
        } else {
            cstmt.setNull(36, Types.VARCHAR);
        }

        if (UseridIns != "") {
            cstmt.setString(37, UseridIns);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "USERID_INS= " + UseridIns);
        }
        switch (TipoStudio) {
            case 1: //Interventistico con farmaco
                EsamRiassunto = 1;
                cstmt.setInt(13, EsamRiassunto);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "EsamRiassunto= " + EsamRiassunto);
                EsamTerapiaStudio = 6;
                cstmt.setInt(14, EsamTerapiaStudio);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "EsamTerapiaStudio= " + EsamTerapiaStudio);
                /*if(princAtt!=null){cstmt.setString(44,princAtt);}
                else{cstmt.setNull(44,Types.VARCHAR);}
                cstmt.setNull(45,Types.VARCHAR);
                cstmt.setNull(46,Types.VARCHAR);
                */
                break;
            case 2: //Interventistico senza farmaco e dispositivo
                EsamRiassunto = 9;
                cstmt.setInt(13, EsamRiassunto);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "EsamRiassunto= " + EsamRiassunto);
                EsamTerapiaStudio = 61;
                cstmt.setInt(14, EsamTerapiaStudio);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "EsamTerapiaStudio= " + EsamTerapiaStudio);
                break;
            case 3: //Interventistico con dispositivo medico
                EsamRiassunto = 8;
                cstmt.setInt(13, EsamRiassunto);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "EsamRiassunto= " + EsamRiassunto);
                EsamTerapiaStudio = 7;
                cstmt.setInt(14, EsamTerapiaStudio);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "EsamTerapiaStudio= " + EsamTerapiaStudio);
                break;
            case 5: //Osservazionale con farmaco
                EsamRiassunto = 11;
                cstmt.setInt(13, EsamRiassunto);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "EsamRiassunto= " + EsamRiassunto);
                EsamTerapiaStudio = 15;
                cstmt.setInt(14, EsamTerapiaStudio);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "EsamTerapiaStudio= " + EsamTerapiaStudio);
                break;
            case 6: //Osservazionale senza farmaco e dispositivo
                EsamRiassunto = 16;
                cstmt.setInt(13, EsamRiassunto);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "EsamRiassunto= " + EsamRiassunto);
                EsamTerapiaStudio = 62;
                cstmt.setInt(14, EsamTerapiaStudio);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "EsamTerapiaStudio= " + EsamTerapiaStudio);
                break;
            case 7: //Osservazionale con dispositivo medico
                EsamRiassunto = 17;
                cstmt.setInt(13, EsamRiassunto);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "EsamRiassunto= " + EsamRiassunto);
                EsamTerapiaStudio = 18;
                cstmt.setInt(14, EsamTerapiaStudio);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "EsamTerapiaStudio= " + EsamTerapiaStudio);
                break;
            case 12: //Studi con campioni biologici
                EsamRiassunto = 121;
                cstmt.setInt(13, EsamRiassunto);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "EsamRiassunto= " + EsamRiassunto);
                cstmt.setNull(14, Types.VARCHAR);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "EsamTerapiaStudio= NULL");
                break;
        }

        cstmt.execute();
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "ESEGUITA PROCEDURE INSERT_STUDIO_CRPMS_TO_CE ");


        if (TipoStudio == 1 || TipoStudio == 5 || TipoStudio == 3 || TipoStudio == 7) { //il farmaco viene riversato solo per studi tipo 1 o 5, il dispositivo per studi medici 3 e 7
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "BLOCCO DI RIVERSAMENTO FARMACI IN CE-TOSCANA TipoStudio= " + TipoStudio);
            List<Element> elFarmaco = studio.getChildrenByType("Farmaco");
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "elFarmaco= " + elFarmaco);
            int progr = 1;
            EsamTerapiaStudio = -1;
            String proceduraFarmaco = "";
            String proceduraFarmacoCoordinate = "{call INSERTCE_COORDINATE(?,?,?, ?,?,?, ?,?,?, ?,?,?)}";
            CallableStatement cstmtFarmaco = null;
            CallableStatement cstmtFarmacoCoordinate = null;
            switch (TipoStudio) {
                case 1: //Interventistico con farmaco
                    EsamTerapiaStudio = 6;
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "EsamTerapiaStudio= " + EsamTerapiaStudio);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "RICHIAMO PROCEDURA INSERTCE_FARMACO");
                    proceduraFarmaco = "{call INSERTCE_FARMACO(?,?,?, ?,?,?, ?,?,? ,?,?,? ,?,?,? ,?,?)}";
                    break;
                case 5: //Osservazionale con farmaco
                    EsamTerapiaStudio = 15;
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "EsamTerapiaStudio= " + EsamTerapiaStudio);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "RICHIAMO PROCEDURA INSERTCE_FARMACOOS");
                    proceduraFarmaco = "{call INSERTCE_FARMACOOS(?,?,?, ?,?,?, ?,?,? ,?,?,? ,?,?,? ,?,?)}";
                    break;
                case 3: //Interventistico con dispositivo medico
                    EsamTerapiaStudio = 7;
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "EsamTerapiaStudio= " + EsamTerapiaStudio);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "RICHIAMO PROCEDURA INSERTCE_DISPOSITIVI");
                    proceduraFarmaco = "{call INSERTCE_DISPOSITIVI(?,?,?, ?,?,?, ?,?,?, ?,?,?, ?)}";
                    break;
                case 7: //Osservazionale con dispositivo medico
                    EsamTerapiaStudio = 18;
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "EsamTerapiaStudio= " + EsamTerapiaStudio);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "RICHIAMO PROCEDURA INSERTCE_DISPOSITIVI_OS");
                    proceduraFarmaco = "{call INSERTCE_DISPOSITIVI_OS(?,?,?, ?,?,?, ?,?,?, ?,?,?, ?)}";
                    break;
            }
            if (elFarmaco.isEmpty()) {
                cstmtFarmacoCoordinate = conn.prepareCall(proceduraFarmacoCoordinate);
                //INSERTCE_COORDINATE(VISITNUM,VISITNUM_PROGR,PROGR,ESAM,INIZIO,FINE,INSERTDT,MODDT,USERID,VISITCLOSE,ID_STUD,ABILITATO); --riassunto
                cstmtFarmacoCoordinate.setInt(1, 0);
                cstmtFarmacoCoordinate.setInt(2, 0);
                cstmtFarmacoCoordinate.setInt(3, progr);
                cstmtFarmacoCoordinate.setInt(4, EsamTerapiaStudio);
                cstmtFarmacoCoordinate.setInt(5, 0);
                cstmtFarmacoCoordinate.setNull(6, Types.NUMERIC);

                java.util.Date d = new java.util.Date();
                java.sql.Date oggi = new java.sql.Date(d.getTime());

                cstmtFarmacoCoordinate.setDate(7, oggi);
                cstmtFarmacoCoordinate.setDate(8, oggi);

                cstmtFarmacoCoordinate.setString(9, UseridIns);
                cstmtFarmacoCoordinate.setInt(10, 0);
                cstmtFarmacoCoordinate.setLong(11, idStudio);
                cstmtFarmacoCoordinate.setInt(12, 1);

                cstmtFarmacoCoordinate.execute();
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "ESEGUITA PROCEDURA FARMACO COORDINATE " + progr);
            } else {
                for (Element child : elFarmaco) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "CHILD elFarmaco= " + child);
                    String farmacoTipo = "";
                    switch (TipoStudio) {
                        case 1:
                        case 5:
                            farmacoTipo = "1";
                            break;
                        case 3:
                        case 7:
                            farmacoTipo = "2";
                            break;
                    }
                    if (child.getfieldData("Farmaco", "tipo") != null && child.getfieldData("Farmaco", "tipo").size() > 0 && child.getfieldData("Farmaco", "tipo").get(0).toString().split("###")[0].equals(farmacoTipo)) {

                        cstmtFarmaco = null;
                        cstmtFarmacoCoordinate = null;

                        //INSERISCO IN COORDINATE
                        cstmtFarmacoCoordinate = conn.prepareCall(proceduraFarmacoCoordinate);
                        //INSERTCE_COORDINATE(VISITNUM,VISITNUM_PROGR,PROGR,ESAM,INIZIO,FINE,INSERTDT,MODDT,USERID,VISITCLOSE,ID_STUD,ABILITATO); --riassunto
                        cstmtFarmacoCoordinate.setInt(1, 0);
                        cstmtFarmacoCoordinate.setInt(2, 0);
                        cstmtFarmacoCoordinate.setInt(3, progr);
                        cstmtFarmacoCoordinate.setInt(4, EsamTerapiaStudio);
                        cstmtFarmacoCoordinate.setInt(5, 1);
                        cstmtFarmacoCoordinate.setInt(6, 0);

                        java.util.Date d = new java.util.Date();
                        java.sql.Date oggi = new java.sql.Date(d.getTime());

                        cstmtFarmacoCoordinate.setDate(7, oggi);
                        cstmtFarmacoCoordinate.setDate(8, oggi);

                        cstmtFarmacoCoordinate.setString(9, UseridIns);
                        cstmtFarmacoCoordinate.setInt(10, 0);
                        cstmtFarmacoCoordinate.setLong(11, idStudio);
                        cstmtFarmacoCoordinate.setInt(12, 1);

                        cstmtFarmacoCoordinate.execute();
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "ESEGUITA PROCEDURA FARMACO COORDINATE " + progr);
                        //INSERISCO IN FARMACO
                        cstmtFarmaco = conn.prepareCall(proceduraFarmaco);
                        cstmtFarmaco.setLong(1, idStudio); //1
                        cstmtFarmaco.setLong(2, 0); //2 visitnum_progr
                        cstmtFarmaco.setLong(3, progr++); //3 progr
                        cstmtFarmaco.setString(4, UseridIns); //4 userid_ins

                        cstmtFarmaco.setLong(5, EsamTerapiaStudio); //esam
                        cstmtFarmaco.setLong(6, 0); //6 visitnum
                        if (TipoStudio == 1 || TipoStudio == 5) {
                            String princAtt = "";
                            if (child.getfieldData("Farmaco", "princAtt") != null && child.getfieldData("Farmaco", "princAtt").size() > 0) {
                                princAtt = child.getfieldData("Farmaco", "princAtt").get(0).toString().split("###")[1];
                                it.cineca.siss.axmr3.log.Log.debug(getClass(), "princAtt= " + princAtt);
                                cstmtFarmaco.setString(7, princAtt);
                            } else if (child.getFieldDataString("Farmaco", "princAttAltro") != null) {
                                princAtt = child.getFieldDataString("Farmaco", "princAttAltro");
                                it.cineca.siss.axmr3.log.Log.debug(getClass(), "princAttAltro= " + princAtt);
                                cstmtFarmaco.setString(7, princAtt);
                            } else {
                                cstmtFarmaco.setNull(7, Types.VARCHAR);
                            }
                            //TODO: VIA_SOMMIM E D_VIA_SOMMIN NON LI HO!
                            cstmtFarmaco.setNull(8, Types.VARCHAR);//VIA_SOMMIM
                            cstmtFarmaco.setNull(9, Types.VARCHAR);//D_VIA_SOMMIN


                            if (child.getfieldData("Farmaco", "testOcomparatore") != null && child.getfieldData("Farmaco", "testOcomparatore").size() > 0) {
                                String categoria = child.getfieldData("Farmaco", "testOcomparatore").get(0).toString().split("###")[0];
                                String d_categoria = child.getfieldData("Farmaco", "testOcomparatore").get(0).toString().split("###")[1];
                                cstmtFarmaco.setLong(10, Long.parseLong(categoria)); //10 categoria
                                cstmtFarmaco.setString(11, d_categoria); //11 d_categoria
                            } else {
                                cstmtFarmaco.setNull(10, Types.VARCHAR); //10 categoria
                                cstmtFarmaco.setNull(11, Types.VARCHAR); //11 d_categoria
                            }
                            //TOSCANA-228 INIZIO
                            if (child.getfieldData("Farmaco", "AIC") != null && child.getfieldData("Farmaco", "AIC").size() > 0) {
                                String categoria = child.getfieldData("Farmaco", "AIC").get(0).toString().split("###")[0];
                                String d_categoria = child.getfieldData("Farmaco", "AIC").get(0).toString().split("###")[1].replace("Si", "Si'");
                                cstmtFarmaco.setLong(12, Long.parseLong(categoria)); //12 p_auto_itaai
                                cstmtFarmaco.setString(13, d_categoria); //13 p_d_auto_itaai
                            } else {
                                cstmtFarmaco.setNull(12, Types.VARCHAR); //12 p_auto_itaai
                                cstmtFarmaco.setNull(13, Types.VARCHAR); //13 p_d_auto_itaai
                            }
                            if (child.getfieldData("Farmaco", "SpecialitaAIC") != null) {

                                it.cineca.siss.axmr3.log.Log.debug(getClass(), "SpecialitaAIC= " + child.getfieldData("Farmaco", "SpecialitaAIC"));
                                cstmtFarmaco.setString(14, child.getfieldData("Farmaco", "SpecialitaAIC").toString());//14 p_specialita
                            } else {
                                cstmtFarmaco.setNull(14, Types.VARCHAR);//14 p_specialita
                            }
                            if (child.getfieldData("Farmaco", "CodiceAIC") != null) {

                                it.cineca.siss.axmr3.log.Log.debug(getClass(), "CodiceAIC= " + child.getfieldData("Farmaco", "CodiceAIC"));
                                cstmtFarmaco.setString(15, child.getfieldData("Farmaco", "CodiceAIC").toString());//15 p_aic
                            } else {
                                cstmtFarmaco.setNull(15, Types.VARCHAR);//15 p_aic
                            }
                            if (child.getfieldData("Farmaco", "ConfezioneAIC") != null) {

                                it.cineca.siss.axmr3.log.Log.debug(getClass(), "ConfezioneAIC= " + child.getfieldData("Farmaco", "ConfezioneAIC"));
                                cstmtFarmaco.setString(16, child.getfieldData("Farmaco", "ConfezioneAIC").toString());//16 p_confezione
                            } else {
                                cstmtFarmaco.setNull(16, Types.VARCHAR);//16 p_confezione
                            }
                            if (child.getfieldData("Farmaco", "CodiceATC") != null) {

                                it.cineca.siss.axmr3.log.Log.debug(getClass(), "CodiceATC= " + child.getfieldData("Farmaco", "CodiceATC"));
                                cstmtFarmaco.setString(17, child.getfieldData("Farmaco", "CodiceATC").toString());//17 p_atc
                            } else {
                                cstmtFarmaco.setNull(17, Types.VARCHAR);//17 p_atc
                            }
                            //TOSCANA-FINE INIZIO
                        }
                        if (TipoStudio == 3 || TipoStudio == 7) {
                            String dispMed = "";
                            if (child.getfieldData("Farmaco", "dispMed") != null && child.getfieldData("Farmaco", "dispMed").size() > 0) {
                                dispMed = child.getfieldData("Farmaco", "dispMed").get(0).toString().split("###")[1];
                                it.cineca.siss.axmr3.log.Log.debug(getClass(), "dispMed= " + dispMed);
                                cstmtFarmaco.setString(7, dispMed);
                            } else if (child.getFieldDataString("Farmaco", "dispMedAltro") != null) {
                                dispMed = child.getFieldDataString("Farmaco", "dispMedAltro");
                                it.cineca.siss.axmr3.log.Log.debug(getClass(), "dispMedAltro= " + dispMed);
                                cstmtFarmaco.setString(7, dispMed);
                            } else {
                                cstmtFarmaco.setNull(7, Types.VARCHAR);
                            }
                            //TOSCANA-228 INIZIO
                            if (child.getfieldData("Farmaco", "DittaProduttriceDisp") != null) {

                                it.cineca.siss.axmr3.log.Log.debug(getClass(), "DittaProduttriceDisp= " + child.getfieldData("Farmaco", "DittaProduttriceDisp"));
                                cstmtFarmaco.setString(8, child.getfieldData("Farmaco", "DittaProduttriceDisp").toString());
                            } else {
                                cstmtFarmaco.setNull(8, Types.VARCHAR);
                            }
                            if (child.getfieldData("Farmaco", "classificCNDdisp") != null) {

                                it.cineca.siss.axmr3.log.Log.debug(getClass(), "classificCNDdisp= " + child.getfieldData("Farmaco", "classificCNDdisp"));
                                cstmtFarmaco.setString(9, child.getfieldData("Farmaco", "classificCNDdisp").toString());
                            } else {
                                cstmtFarmaco.setNull(9, Types.VARCHAR);
                            }
                            if (child.getfieldData("Farmaco", "descrCNDdisp") != null) {

                                it.cineca.siss.axmr3.log.Log.debug(getClass(), "descrCNDdisp= " + child.getfieldData("Farmaco", "descrCNDdisp"));
                                cstmtFarmaco.setString(10, child.getfieldData("Farmaco", "descrCNDdisp").toString());
                            } else {
                                cstmtFarmaco.setNull(10, Types.VARCHAR);
                            }
                            if (child.getfieldData("Farmaco", "numeroRepertorioDisp") != null) {

                                it.cineca.siss.axmr3.log.Log.debug(getClass(), "numeroRepertorioDisp= " + child.getfieldData("Farmaco", "numeroRepertorioDisp"));
                                cstmtFarmaco.setString(11, child.getfieldData("Farmaco", "numeroRepertorioDisp").toString());
                            } else {
                                cstmtFarmaco.setNull(11, Types.VARCHAR);
                            }
                            if (child.getfieldData("Farmaco", "MarchioCE") != null && child.getfieldData("Farmaco", "MarchioCE").size() > 0) {
                                String marchioce = child.getfieldData("Farmaco", "MarchioCE").get(0).toString().split("###")[0];
                                String d_marchioce = child.getfieldData("Farmaco", "MarchioCE").get(0).toString().split("###")[1].replace("Si", "Si'");
                                cstmtFarmaco.setLong(12, Long.parseLong(marchioce)); //12 p_auto_itaai
                                cstmtFarmaco.setString(13, d_marchioce); //13 p_d_auto_itaai
                            } else {
                                cstmtFarmaco.setNull(12, Types.VARCHAR); //12 p_auto_itaai
                                cstmtFarmaco.setNull(13, Types.VARCHAR); //13 p_d_auto_itaai
                            }
                            //TOSCANA-228 FINE
                        }
                        cstmtFarmaco.execute();
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "ESEGUITA PROCEDURA FARMACO " + progr);
                    }
                }
            }
        }

        //Documentazione generale
        Integer docPresente = 0;
        Element elStudio = el.getParent();
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Blocco di riversamento documenti in CE-TOSCANA");
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "elStudio=" + elStudio);
        List<Element> elAllegato = elStudio.getChildrenByType("allegato");
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "elAllegato=" + elAllegato);
        for (Element child : elAllegato) {
            docPresente = 1;

            String sqlprogr = "";
            boolean recordPresente;
            Integer p = null;
            String docgen = "";
            String docgenDen = "";
            String docgenAltro = "";
            String docvers = "";
            String docnote = "";
            String sqlIdDocs = "";
            boolean recordPresente1;
            Integer iddoc;
            String ext = "";
            String autore = "";
            long idTipoRef;
            String keywords = "";
            String fileCeOnline = "";

            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Sono nel ciclo for dei documenti allegati");
            String filename = child.getFile().getFileName();
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "nomefile= " + filename);

            Integer tipoDoc = Integer.valueOf(child.getFieldDataCode("DocGenerali", "DocGen"));

            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Ho trovato un documento da portare in CE-ONLINE");

            /*
            if(tipoDoc.equals(1)){docgen="2"; docgenDen="Sinossi del protocollo";}
            if(tipoDoc.equals(2)){docgen="4"; docgenDen="Protocollo di studio in esteso";}
            if(tipoDoc.equals(3)){docgen="25"; docgenDen="Investigator's Brochure o scheda tecnica";}
            if(tipoDoc.equals(-9999)){docgen="23"; docgenDen="Altro"; docgenAltro=child.getFieldDataDecode("DocGenerali", "DocGen");}
            */

            //GC 15/07/2016 Query per mappatura documenti in CE-ONLINE
            String sqlDocsCE = "select id,descrizione from CRMS_DOC_GEN,CE_DOC_GEN where id_doc_ce=id and code=" + tipoDoc;
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Query = " + sqlDocsCE);
            PreparedStatement stmtdocce = conn.prepareStatement(sqlDocsCE);
            ResultSet rsetDocsCe = stmtdocce.executeQuery();
            recordPresente1 = rsetDocsCe.next();
            if (recordPresente1) {
                docgen = rsetDocsCe.getString("id");
                docgenDen = rsetDocsCe.getString("descrizione");
            }
            docgenAltro = child.getFieldDataDecode("DocGenerali", "DocGen");

            CallableStatement cstmt2 = null;
            String procedure2 = "{call INSERT_DOC_CRPMS_TO_CE(?,?,?, ?,?,?, ?,?,?, ?,?,?, ?,?,?, ?)}";

            cstmt2 = conn.prepareCall(procedure2);

            cstmt2.setLong(1, idStudio);

            //recupero il prossimo progressivo del documento
            sqlprogr = "select nvl(max(progr),0)+1 as p from CE_COORDINATE where ID_STUD=" + idStudio + " and visitnum=0 and visitnum_progr=0 and esam=2";
            PreparedStatement stmt = conn.prepareStatement(sqlprogr);
            ResultSet rset = stmt.executeQuery();

            recordPresente = rset.next();
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "recordPresente=" + recordPresente);
            if (recordPresente) {
                keywords = "DOC_CORE";
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "p=" + p);
                p = rset.getInt("p");

                cstmt2.setLong(2, p);
                if (p > 1) {
                    keywords += "_" + p;
                }
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "keywords=" + keywords);
            }

            cstmt2.setString(3, docgen);
            cstmt2.setString(4, docgenDen);
            cstmt2.setString(5, docgenAltro);

            Calendar dataDoc = child.getFile().getDate();

            if (dataDoc != null) {
                java.sql.Date sqlDate = new java.sql.Date(dataDoc.getTime().getTime());
                cstmt2.setDate(6, sqlDate);
                cstmt2.setString(7, "OKOKOK");
            } else {
                cstmt2.setNull(6, Types.DATE);
                cstmt2.setNull(7, Types.VARCHAR);
            }

            docvers = child.getFile().getVersion();
            if (docvers != null) {
                cstmt2.setString(8, docvers);
            } else {
                cstmt2.setNull(8, Types.VARCHAR);
            }

            docnote = child.getFile().getNote();
            if (docnote != null) {
                cstmt2.setString(9, docnote);
            } else {
                cstmt2.setNull(9, Types.VARCHAR);
            }

            int i = filename.lastIndexOf(".");
            if (i > 0) {
                ext = filename.substring(i + 1);
            }

            cstmt2.setString(11, ext);

            sqlIdDocs = "select DOCS_ID.NEXTVAL as iddoc from DUAL";
            PreparedStatement stmt1 = conn.prepareStatement(sqlIdDocs);
            ResultSet rset1 = stmt1.executeQuery();
            recordPresente1 = rset1.next();
            if (recordPresente1) {
                iddoc = rset1.getInt("iddoc");
                cstmt2.setInt(10, iddoc);

                //Scrivo il documento nella cartella del CE-ONLINE
                byte[] contenuto = child.getFile().getContent().getContent();
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "contenuto=" + contenuto);
                fileCeOnline = "Doc_Area" + iddoc + "." + ext;
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "recordPresente=" + recordPresente);
                File destFolder = new File("/http/servizi/siss-bundle-01/ricercaclinica-toscana.cineca.it/html/uxmr/WCA/docs/" + fileCeOnline);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "destFolder=" + destFolder);
                FileOutputStream fos = new FileOutputStream(destFolder);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "fos=" + fos);
                fos.write(contenuto);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "write");
                fos.close();
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "close");
            }

            cstmt2.setString(12, filename);

            autore = child.getFile().getAutore();
            if (autore != null) {
                cstmt2.setString(13, autore);
            } else {
                cstmt2.setNull(13, Types.VARCHAR);
            }

            idTipoRef = idStudio + 10000000;
            cstmt2.setLong(14, idTipoRef);

            cstmt2.setString(15, keywords);
            cstmt2.setString(16, UseridIns);
            cstmt2.execute();

        }

        //non ci sono documenti nel CRPMS, quindi bisogna richiamare la procedura per l'inserimento del record in ce_oordinate del documento
        if (docPresente.equals(0)) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Non ho trovato documenti quindi inserisco il record del documento in ce_coordinate");
            CallableStatement cstmt3 = null;
            String procedure3 = "{call INSERTCE_COORDINATE(?,?,?,?,?,?,?,?,?,?,?,?)}";
            cstmt3 = conn.prepareCall(procedure3);

            cstmt3.setInt(1, 0);
            cstmt3.setInt(2, 0);
            cstmt3.setInt(3, 1);
            cstmt3.setInt(4, 2);
            cstmt3.setNull(5, Types.NUMERIC);
            cstmt3.setNull(6, Types.NUMERIC);

            java.util.Date d = new java.util.Date();
            java.sql.Date oggi = new java.sql.Date(d.getTime());

            cstmt3.setDate(7, oggi);
            cstmt3.setDate(8, oggi);

            cstmt3.setString(9, UseridIns);
            cstmt3.setInt(10, 0);
            cstmt3.setLong(11, idStudio);
            cstmt3.setInt(12, 1);


            cstmt3.execute();
        }

        it.cineca.siss.axmr3.log.Log.debug(getClass(), "fine createStudioInCeOnline");

    }

    public void ParereCeToCRPMS() throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "inizio ParereCeToCRPMS");
        DocumentService service = commonBean.getDocumentService();
        Connection conn = dataSource.getConnection();

        String sql = "";
        String sql1 = "";
        String idCenter = "";
        String esitoParere = "";
        String dataParere;
        Long newParereCeId;
        String id_stud = "";
        String visitnum = "";
        String visitnum_progr = "";
        String esam = "";
        String progr = "";
        String fileParere = "";

        sql = "select * from VALUTAZIONI_TO_CRPMS";
        PreparedStatement stmt = conn.prepareStatement(sql);
        ResultSet rset = stmt.executeQuery();

        while (rset.next()) {
            idCenter = rset.getString("crpms_center_progr");
            if (idCenter != null && !idCenter.equals("")) {
                esitoParere = rset.getString("d_ris_delib");
                dataParere = rset.getString("riunione_ce_dt");
                id_stud = rset.getString("id_stud");
                visitnum = rset.getString("visitnum");
                visitnum_progr = rset.getString("visitnum_progr");
                esam = rset.getString("esam");
                progr = rset.getString("progr");
                fileParere = rset.getString("doc_parere");

                it.cineca.siss.axmr3.log.Log.debug(getClass(), "dataParere=" + dataParere);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "idCenter=" + idCenter);

                newParereCeId = commonBean.createChild(idCenter, "CTC", "ParereCe", service);
                commonBean.addMetadataValue(String.valueOf(newParereCeId), "ParereCe", "esitoParere", esitoParere, service);
                if (dataParere != null) {
                    commonBean.addMetadataValue(String.valueOf(newParereCeId), "ParereCe", "dataParere", dataParere, service);
                }
                if (fileParere != null) {
                    commonBean.addMetadataValue(String.valueOf(newParereCeId), "ParereCe", "fileParere", fileParere, service);
                }

                sql1 = "update ce_valutazione set crpms_aggiornato=1,crpms_ParereCeId=" + newParereCeId + " where visitnum=" + visitnum + " and visitnum_progr=" + visitnum_progr + " and esam=" + esam + " and progr=" + progr + " and id_stud=" + id_stud;
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "sql1 = " + sql1);
                PreparedStatement stmt1 = conn.prepareStatement(sql1);
                ResultSet rset1 = stmt1.executeQuery();
                //TOSCANA-167 invio mail notifica parere PUNTO 20
                if (esitoParere != "2") { //solo se 1 parere positivo o 3 richiesta integrazione/modifica
                    String processKey = "inviaMail";
                    String mailSubject = "TOSCANA - CRMS - Invio dati parere da Segreteria CE a CTO/TFA";
                    String mailInfoCentro = "";
                    Long idStudio;
                    String sponsor = "";
                    String croString = "";
                    String codice = "";
                    String titolo = "";
                    String DenCentro = "";
                    String DenUnitaOperativa = "";
                    String DenPrincInv = "";
                    Element ElementCentro = service.getElement(String.valueOf(idCenter));
                    Element ElementStudio = ElementCentro.getParent();
                    idStudio = ElementStudio.getId();
                    HashMap<String, String> mailData = new HashMap<String, String>();
                    String mailTo = "";
                    String user = ElementCentro.getCreateUser();
                    String sqlMailTO = "select u.email as email from ana_utenti_1 u, studies_profiles sp,users_profiles up where u.userid=up.userid and sp.id=up.profile_id and sp.active=1 and up.active=1 and sp.code=?";
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), sqlMailTO);
                    PreparedStatement stmtMailTo = conn.prepareStatement(sqlMailTO);
                    stmtMailTo.setString(1, getCTOgroup((IUser) userService.loadUserByUsername(user)));
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
                    if (mailTo.equals("")) mailTo = getEmail("ALIAS_CTC");

                    if (ElementStudio.getFieldDataElement("datiPromotore", "promotore") != null && ElementStudio.getFieldDataElement("datiPromotore", "promotore").size() > 0) {
                        Element sp = ElementStudio.getFieldDataElement("datiPromotore", "promotore").get(0);
                        sponsor = sp.getfieldData("DatiPromotoreCRO", "denominazione").get(0).toString();
                    }
                    if (ElementStudio.getFieldDataElement("datiCRO", "denominazione") != null && ElementStudio.getFieldDataElement("datiCRO", "denominazione").size() > 0) {
                        Element cro = ElementStudio.getFieldDataElement("datiCRO", "denominazione").get(0);
                        croString = cro.getfieldData("DatiPromotoreCRO", "denominazione").get(0).toString();
                    }
                    if (ElementStudio.getfieldData("IDstudio", "CodiceProt") != null && ElementStudio.getfieldData("IDstudio", "CodiceProt").size() > 0) {
                        codice = ElementStudio.getfieldData("IDstudio", "CodiceProt").get(0).toString();
                    }
                    if (ElementStudio.getfieldData("IDstudio", "TitoloProt") != null && ElementStudio.getfieldData("IDstudio", "TitoloProt").size() > 0) {
                        titolo = ElementStudio.getfieldData("IDstudio", "TitoloProt").get(0).toString();
                    }
                    DenCentro = ElementCentro.getfieldData("IdCentro", "Struttura").get(0).toString().split("###")[1];
                    DenUnitaOperativa = ElementCentro.getfieldData("IdCentro", "UO").get(0).toString().split("###")[1];
                    DenPrincInv = ElementCentro.getfieldData("IdCentro", "PINomeCognome").get(0).toString().split("###")[1];

                    mailInfoCentro =
                            "ID studio: " + id_stud +
                                    "\nCodice: " + codice +
                                    "\nTitolo: " + titolo +
                                    "\nSponsor: " + sponsor +
                                    "\nCRO: " + croString +
                                    "\nStruttura: " + DenCentro +
                                    "\nUnita' operativa: " + DenUnitaOperativa +
                                    "\nPrincipal Investigator: " + DenPrincInv;

                    String url = getBaseUrl() + "/app/documents/detail/" + ElementCentro.getId();
                    String mailBody = "Gentile utente,\n" +
                            "si comunica che e' stato appena inviato il parere per il seguente centro da Segreteria CE a CTO/TFA:\n\n" +
                            mailInfoCentro + "\n\n" +
                            "E' possibile visualizzare il centro al seguente link:\n\n" +
                            url + "\n\n" +
                            "Cordiali saluti\n\n\n\n" +
                            "Il presente messaggio è stato inviato automaticamente dal sistema, si prega di non rispondere.\n" +
                            "Per contattare il servizio di help desk inviare una mail a help_crpms@cineca.it";
                    mailData.put("to", mailTo);
                    mailData.put("subject", mailSubject);
                    mailData.put("body", mailBody);
                    mailData.put("cc", getEmail("ALIAS_CTC"));
                    mailData.put("ccn", getEmail("ALIAS_CTC"));
                    service.startProcess(user, ElementCentro, processKey, mailData);
                }
            }
        }
        conn.close();
        commonBean.closeDocumentService(service);
    }

    public void AggiornamentiCeToCRPMS(DelegateExecution execution) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "inizio AggiornamentiCeToCRPMS");
        DocumentService service = commonBean.getDocumentService();
        Connection conn = dataSource.getConnection();

        String sql = "";
        String sql1 = "";
        boolean recordPresent = false;
        String idCenter = "";
        String id_stud = "";
        String visitnum = "";
        String visitnum_progr = "";
        String esam = "";
        String progr = "";
        String bodyMail = "";

        sql = "select * from VERIFICHE_TO_CRPMS";
        PreparedStatement stmt = conn.prepareStatement(sql);
        ResultSet rset = stmt.executeQuery();

        while (rset.next()) {
            String bodyMailPart = "";
            String labelBodyMail = "";
            idCenter = rset.getString("crpms_center_progr");
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "idCenter res=" + idCenter);
            id_stud = rset.getString("id_stud");
            visitnum = rset.getString("visitnum");
            visitnum_progr = rset.getString("visitnum_progr");
            esam = rset.getString("esam");
            progr = rset.getString("progr");

            //Confronto i campi in comune tra CE-ONLINE e CRPMS e aggiornare quelli diversi
            Element el = service.getElement(String.valueOf(idCenter));
            Element ElementStudio = el.getParent();
            Long idElementStudio = ElementStudio.getId();
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "idElementStudio res=" + idElementStudio);
            String tipoSper = "";
            tipoSper = rset.getString("tipo_sper");

            String res = "";
            String idStudio = ElementStudio.getfieldData("UniqueIdStudio", "id").get(0).toString();

            String codiceProtCRPMS = ElementStudio.getfieldData("IDstudio", "CodiceProt").get(0).toString();
            String codiceProt = rset.getString("codice_prot");
            if (codiceProt == null || codiceProt.isEmpty()) codiceProt = "";
            labelBodyMail = "Codice Protocollo";
            res = compareFieldValue(labelBodyMail, codiceProtCRPMS, codiceProt);
            if (!res.equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Codice Protocollo res=" + res);
                commonBean.addMetadataValue(idElementStudio, "IDstudio", "CodiceProt", codiceProt, service);
                bodyMailPart += res;
            }

            String titoloProtCRPMS = ElementStudio.getfieldData("IDstudio", "TitoloProt").get(0).toString();
            String titoloProt = rset.getString("titolo_prot");
            if (titoloProt == null || titoloProt.isEmpty()) titoloProt = "";
            labelBodyMail = "Titolo dello studio";
            res = compareFieldValue(labelBodyMail, titoloProtCRPMS, titoloProt);
            if (!res.equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Titolo dello studio res=" + res);
                commonBean.addMetadataValue(idElementStudio, "IDstudio", "TitoloProt", titoloProt, service);
                bodyMailPart += res;
            }

            String Profit = rset.getString("profit");
            String dProfit = rset.getString("d_profit");
            String stringProfit = Profit + "###" + dProfit;
            if (Profit == null || Profit.isEmpty()) {
                Profit = "";
                dProfit = "";
                stringProfit = "";
            }
            String ProfitCRPMS = "";
            String ProfitCRPMSDec = "";
            if (ElementStudio.getfieldData("datiStudio", "Profit") != null && ElementStudio.getfieldData("datiStudio", "Profit").size() > 0) {
                ProfitCRPMS = ElementStudio.getfieldData("datiStudio", "Profit").get(0).toString().split("###")[0];
                ProfitCRPMSDec = ElementStudio.getfieldData("datiStudio", "Profit").get(0).toString().split("###")[1];
            }
            labelBodyMail = "Tipo studio";
            res = compareFieldValue(labelBodyMail, ProfitCRPMS, Profit, ProfitCRPMSDec, dProfit);
            if (!res.equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Tipo studio res=" + res);
                commonBean.addMetadataValue(idElementStudio, "datiStudio", "Profit", stringProfit, service);
                bodyMailPart += res;
            }

            if (tipoSper.equals("1") || tipoSper.equals("3")) {
                String FaseCRPMS = "";
                String FaseCRPMSDec = "";
                if (ElementStudio.getfieldData("datiStudio", "fase") != null && ElementStudio.getfieldData("datiStudio", "fase").size() > 0) {
                    FaseCRPMS = ElementStudio.getfieldData("datiStudio", "fase").get(0).toString().split("###")[0];
                    FaseCRPMSDec = ElementStudio.getfieldData("datiStudio", "fase").get(0).toString().split("###")[1];
                }
                String Fase = rset.getString("fase_sper");
                String dFase = rset.getString("d_fase_sper");
                String stringFase = Fase + "###" + dFase;
                labelBodyMail = "Fase studio";
                res = compareFieldValue(labelBodyMail, FaseCRPMS, Fase, FaseCRPMSDec, dFase);
                if (!res.equals("")) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "Fase Studio res=" + res);
                    commonBean.addMetadataValue(idElementStudio, "datiStudio", "fase", stringFase, service);
                    bodyMailPart += res;
                }

                String eudractNumber = rset.getString("eudract_num");
                if (eudractNumber == null || eudractNumber.isEmpty()) eudractNumber = "";
                String eudractNumberCRPMS = "";
                if (ElementStudio.getfieldData("datiStudio", "eudractNumber") != null && ElementStudio.getfieldData("datiStudio", "eudractNumber").size() > 0) {
                    eudractNumberCRPMS = ElementStudio.getfieldData("datiStudio", "eudractNumber").get(0).toString();
                }
                labelBodyMail = "eudractNumber";
                res = compareFieldValue(labelBodyMail, eudractNumberCRPMS, eudractNumber);
                if (!res.equals("")) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "eudractNumber res=" + res);
                    commonBean.addMetadataValue(idElementStudio, "datiStudio", "eudractNumber", eudractNumber, service);
                    bodyMailPart += res;
                }
            }


            String FonteFinTerzi = rset.getString("fonte_fin_terzi");
            if (FonteFinTerzi == null || FonteFinTerzi.isEmpty()) FonteFinTerzi = "";
            String FonteFinTerziDec = rset.getString("d_fonte_fin_terzi");
            if (FonteFinTerziDec == null || FonteFinTerziDec.isEmpty()) FonteFinTerziDec = "";
            String FonteFinTerziCRPMS = "";
            String FonteFinTerziDecCRPMS = "";
            String stringFonteFinTerzi = FonteFinTerzi + "###" + FonteFinTerziDec;
            if (ElementStudio.getfieldData("datiStudio", "fonteFinTerzi") != null && ElementStudio.getfieldData("datiStudio", "fonteFinTerzi").size() > 0) {

                FonteFinTerziCRPMS = ElementStudio.getfieldData("datiStudio", "fonteFinTerzi").get(0).toString().split("###")[0];
                FonteFinTerziDecCRPMS = ElementStudio.getfieldData("datiStudio", "fonteFinTerzi").get(0).toString().split("###")[1];
            }
            labelBodyMail = "FonteFinTerzi";
            res = compareFieldValue(labelBodyMail, FonteFinTerziCRPMS, FonteFinTerzi, FonteFinTerziDecCRPMS, FonteFinTerziDec);
            if (!res.equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "FonteFinTerzi res=" + res);
                commonBean.addMetadataValue(idElementStudio, "datiStudio", "fonteFinTerzi", stringFonteFinTerzi, service);
                bodyMailPart += res;
            }

            String fonteFinSpec = rset.getString("fonte_fin_spec");
            if (fonteFinSpec == null || fonteFinSpec.isEmpty()) fonteFinSpec = "";
            String fonteFinSpecDec = rset.getString("d_fonte_fin_spec");
            if (fonteFinSpecDec == null || fonteFinSpecDec.isEmpty()) fonteFinSpecDec = "";
            String fonteFinSpecCRPMS = "";
            String fonteFinSpecDecCRPMS = "";
            String stringFonteFinSpec = fonteFinSpec + "###" + fonteFinSpecDec;
            if (ElementStudio.getfieldData("datiStudio", "fonteFinSpec") != null && ElementStudio.getfieldData("datiStudio", "fonteFinSpec").size() > 0) {

                fonteFinSpecCRPMS = ElementStudio.getfieldData("datiStudio", "fonteFinSpec").get(0).toString().split("###")[0];
                fonteFinSpecDecCRPMS = ElementStudio.getfieldData("datiStudio", "fonteFinSpec").get(0).toString().split("###")[1];
            }
            labelBodyMail = "fonteFinSpec";
            res = compareFieldValue(labelBodyMail, fonteFinSpecCRPMS, fonteFinSpec, fonteFinSpecDecCRPMS, fonteFinSpecDec);
            if (!res.equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "fonteFinSpec res=" + res);
                commonBean.addMetadataValue(idElementStudio, "datiStudio", "fonteFinSpec", stringFonteFinSpec, service);
                bodyMailPart += res;
            }

            String fonteFinSponsor = rset.getString("fonte_fin_sponsor");
            if (fonteFinSponsor == null || fonteFinSponsor.isEmpty()) fonteFinSponsor = "";
            String fonteFinSponsorDec = rset.getString("fonte_fin_id_sponsor");
            if (fonteFinSponsorDec == null || fonteFinSponsorDec.isEmpty()) fonteFinSponsorDec = "";
            String fonteFinSponsorCRPMS = "";
            String fonteFinSponsorDecCRPMS = "";
            String stringFonteFinSponsor = fonteFinSponsor + "###" + fonteFinSponsorDec;
            if (ElementStudio.getfieldData("datiStudio", "fonteFinSponsor") != null && ElementStudio.getfieldData("datiStudio", "fonteFinSponsor").size() > 0) {

                fonteFinSponsorCRPMS = ElementStudio.getfieldData("datiStudio", "fonteFinSponsor").get(0).toString().split("###")[0];
                fonteFinSponsorDecCRPMS = ElementStudio.getfieldData("datiStudio", "fonteFinSponsor").get(0).toString().split("###")[1];
            }
            labelBodyMail = "fonteFinSponsor";
            res = compareFieldValue(labelBodyMail, fonteFinSponsorCRPMS, fonteFinSponsor, fonteFinSponsorDecCRPMS, fonteFinSponsorDec);
            if (!res.equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "fonteFinSponsor res=" + res);
                commonBean.addMetadataValue(idElementStudio, "datiStudio", "fonteFinSponsor", stringFonteFinSponsor, service);
                bodyMailPart += res;
            }

            String fonteFinFondazione = rset.getString("fonte_fin_fondazione");
            if (fonteFinFondazione == null || fonteFinFondazione.isEmpty()) fonteFinFondazione = "";
            String fonteFinFondazioneCRPMS = "";
            String stringFonteFinFondazione = fonteFinFondazione;
            if (ElementStudio.getfieldData("datiStudio", "fonteFinFondazione") != null && ElementStudio.getfieldData("datiStudio", "fonteFinFondazione").size() > 0) {

                fonteFinFondazioneCRPMS = ElementStudio.getFieldDataString("datiStudio", "fonteFinFondazione");

            }
            labelBodyMail = "fonteFinFondazione";
            res = compareFieldValue(labelBodyMail, fonteFinFondazioneCRPMS, fonteFinFondazione);
            if (!res.equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "fonteFinFondazione res=" + res);
                commonBean.addMetadataValue(idElementStudio, "datiStudio", "fonteFinFondazione", stringFonteFinFondazione, service);
                bodyMailPart += res;
            }

            String fonteFinAltro = rset.getString("fonte_fin_altro");
            if (fonteFinAltro == null || fonteFinAltro.isEmpty()) fonteFinAltro = "";

            String fonteFinAltroCRPMS = "";
            String stringFonteFinAltro = fonteFinAltro;
            if (ElementStudio.getfieldData("datiStudio", "fonteFinAltro") != null && ElementStudio.getfieldData("datiStudio", "fonteFinAltro").size() > 0) {

                fonteFinAltroCRPMS = ElementStudio.getFieldDataString("datiStudio", "fonteFinAltro");

            }
            labelBodyMail = "fonteFinAltro";
            res = compareFieldValue(labelBodyMail, fonteFinAltroCRPMS, fonteFinAltro);
            if (!res.equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "fonteFinAltro res=" + res);
                commonBean.addMetadataValue(idElementStudio, "datiStudio", "fonteFinAltro", stringFonteFinAltro, service);
                bodyMailPart += res;
            }

            String durataCRPMS = "";
            String durata = rset.getString("dur_sper");
            if (durata == null || durata.isEmpty()) durata = "";
            if (ElementStudio.getfieldData("datiStudio", "durataTot") != null && ElementStudio.getfieldData("datiStudio", "durataTot").size() > 0) {
                durataCRPMS = ElementStudio.getfieldData("datiStudio", "durataTot").get(0).toString();
            }
            labelBodyMail = "Durata";
            res = compareFieldValue(labelBodyMail, durataCRPMS, durata);
            if (!res.equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Durata res=" + res);
                commonBean.addMetadataValue(idElementStudio, "datiStudio", "durataTot", durata, service);
                bodyMailPart += res;
            }

            String durataUnit = rset.getString("dur_sper_unit");
            String durataUnitDec = rset.getString("d_dur_sper_unit");
            String stringdurataUnit = durataUnit + "###" + durataUnitDec;
            if (durataUnit == null || durataUnit.isEmpty() || durataUnit.equals("")) {
                durataUnit = "";
                durataUnitDec = "";
                stringdurataUnit = "";
            }
            String durataUnitCRPMS = "";
            String durataUnitDecCRPMS = "";
            if (ElementStudio.getfieldData("datiStudio", "durataTotSelect") != null && ElementStudio.getfieldData("datiStudio", "durataTotSelect").size() > 0) {
                durataUnitCRPMS = ElementStudio.getFieldDataCode("datiStudio", "durataTotSelect");
                durataUnitDecCRPMS = ElementStudio.getFieldDataDecode("datiStudio", "durataTotSelect");
            }
            labelBodyMail = "Durata prevista dello studio (quantità)";
            res = compareFieldValue(labelBodyMail, durataUnitCRPMS, durataUnit, durataUnitDecCRPMS, durataUnitDec);
            if (!res.equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Durata prevista dello studio (quantità) res=" + res);
                commonBean.addMetadataValue(idElementStudio, "datiStudio", "durataTotSelect", stringdurataUnit, service);
                bodyMailPart += res;
            }


            //Sponsor
            String sponsor = rset.getString("id_sponsor");
            String sponsorDec = rset.getString("descr_sponsor");
            if (sponsor == null || sponsor.isEmpty()) {
                sponsor = "";
                sponsorDec = "";
            }
            String sponsorCRPMS = "";
            String sponsorDecCRPMS = "";
            String idSp = "";
            if (ElementStudio.getFieldDataElement("datiPromotore", "promotore") != null && ElementStudio.getFieldDataElement("datiPromotore", "promotore").size() > 0) {
                Element sp = ElementStudio.getFieldDataElement("datiPromotore", "promotore").get(0);
                sponsorCRPMS = sp.getfieldData("DatiPromotoreCRO", "id").get(0).toString();
                sponsorDecCRPMS = sp.getfieldData("DatiPromotoreCRO", "denominazione").get(0).toString();
            }
            labelBodyMail = "Sponsor";
            res = compareFieldValue(labelBodyMail, sponsorCRPMS, sponsor, sponsorDecCRPMS, sponsorDec);
            if (!res.equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Sponsor res=" + res);
                if (!sponsor.equals("")) {
                    HashMap<String, Object> data = new HashMap<String, Object>();
                    data.put("DatiPromotoreCRO_id", sponsor);
                    List<Element> risSp = service.searchByExample("Promotore", data);
                    idSp = risSp.get(0).getId().toString();
                }
                commonBean.addMetadataValue(idElementStudio, "datiPromotore", "promotore", idSp, service);
                bodyMailPart += res;
            }

            String RefNomeCognomepR = rset.getString("ref_sponsor");
            if (RefNomeCognomepR == null || RefNomeCognomepR.isEmpty()) RefNomeCognomepR = "";
            String RefNomeCognomepRCRPMS = "";
            if (el.getfieldData("datiPromotore", "RefNomeCognomepR") != null && el.getfieldData("datiPromotore", "RefNomeCognomepR").size() > 0) {
                RefNomeCognomepRCRPMS = el.getfieldData("datiPromotore", "RefNomeCognomepR").get(0).toString();
            }
            labelBodyMail = "Nome Cognome Promotore";
            res = compareFieldValue(labelBodyMail, RefNomeCognomepRCRPMS, RefNomeCognomepR);
            if (!res.equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Nome Cognome Promotore res=" + res);
                commonBean.addMetadataValue(idElementStudio, "datiPromotore", "RefNomeCognomepR", RefNomeCognomepR, service);
                bodyMailPart += res;
            }

            String RefEmailpR = rset.getString("email_sponsor");
            if (RefEmailpR == null || RefEmailpR.isEmpty()) RefEmailpR = "";
            String RefEmailpRCRPMS = "";
            if (el.getfieldData("datiPromotore", "RefEmailpR") != null && el.getfieldData("datiPromotore", "RefEmailpR").size() > 0) {
                RefEmailpRCRPMS = el.getfieldData("datiPromotore", "RefEmailpR").get(0).toString();
            }
            labelBodyMail = "Email Promotore";
            res = compareFieldValue(labelBodyMail, RefEmailpRCRPMS, RefEmailpR);
            if (!res.equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Email Promotore res=" + res);
                commonBean.addMetadataValue(idElementStudio, "datiPromotore", "RefEmailpR", RefEmailpR, service);
                bodyMailPart += res;
            }

            String RefTelpR = rset.getString("tel_sponsor");
            if (RefTelpR == null || RefTelpR.isEmpty()) RefTelpR = "";
            String RefTelpRCRPMS = "";
            if (el.getfieldData("datiPromotore", "RefTelpR") != null && el.getfieldData("datiPromotore", "RefTelpR").size() > 0) {
                RefTelpRCRPMS = el.getfieldData("datiPromotore", "RefTelpR").get(0).toString();
            }
            labelBodyMail = "Telefono Promotore";
            res = compareFieldValue(labelBodyMail, RefTelpRCRPMS, RefTelpR);
            if (!res.equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Telefono Promotore res=" + res);
                commonBean.addMetadataValue(idElementStudio, "datiPromotore", "RefTelpR", RefTelpR, service);
                bodyMailPart += res;
            }

            //CRO
            String cro = rset.getString("id_cro");
            String croDec = rset.getString("descr_cro");
            if (cro == null || cro.isEmpty()) {
                cro = "";
                croDec = "";
            }
            String croCRPMS = "";
            String croDecCRPMS = "";
            String idCro = "";
            if (ElementStudio.getFieldDataElement("datiCRO", "denominazione") != null && ElementStudio.getFieldDataElement("datiCRO", "denominazione").size() > 0) {
                Element cr = ElementStudio.getFieldDataElement("datiCRO", "denominazione").get(0);
                croCRPMS = cr.getfieldData("DatiPromotoreCRO", "id").get(0).toString();
                croDecCRPMS = cr.getfieldData("DatiPromotoreCRO", "denominazione").get(0).toString();
            }
            labelBodyMail = "CRO";
            res = compareFieldValue(labelBodyMail, croCRPMS, cro, croDecCRPMS, croDec);
            if (!res.equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "CRO res=" + res);
                if (!cro.equals("")) {
                    HashMap<String, Object> data = new HashMap<String, Object>();
                    data.put("DatiPromotoreCRO_id", cro);
                    List<Element> risCro = service.searchByExample("CRO", data);
                    idCro = risCro.get(0).getId().toString();
                }
                commonBean.addMetadataValue(idElementStudio, "datiCRO", "denominazione", idCro, service);
                bodyMailPart += res;
            }

            String NomeReferenteR = rset.getString("ref_cro");
            if (NomeReferenteR == null || NomeReferenteR.isEmpty()) NomeReferenteR = "";
            String NomeReferenteRCRPMS = "";
            if (el.getfieldData("datiCRO", "NomeReferenteR") != null && el.getfieldData("datiCRO", "NomeReferenteR").size() > 0) {
                NomeReferenteRCRPMS = el.getfieldData("datiCRO", "NomeReferenteR").get(0).toString();
            }
            labelBodyMail = "Nome Cognome CRO";
            res = compareFieldValue(labelBodyMail, NomeReferenteRCRPMS, NomeReferenteR);
            if (!res.equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Nome Cognome CRO res=" + res);
                commonBean.addMetadataValue(idElementStudio, "datiCRO", "NomeReferenteR", NomeReferenteR, service);
                bodyMailPart += res;
            }

            String telefonoR = rset.getString("tel_cro");
            if (telefonoR == null || telefonoR.isEmpty()) telefonoR = "";
            String telefonoRCRPMS = "";
            if (el.getfieldData("datiCRO", "telefonoR") != null && el.getfieldData("datiCRO", "telefonoR").size() > 0) {
                telefonoRCRPMS = el.getfieldData("datiCRO", "telefonoR").get(0).toString();
            }
            labelBodyMail = "Telefono CRO";
            res = compareFieldValue(labelBodyMail, telefonoRCRPMS, telefonoR);
            if (!res.equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Telefono CRO res=" + res);
                commonBean.addMetadataValue(idElementStudio, "datiCRO", "telefonoR", telefonoR, service);
                bodyMailPart += res;
            }

            String emailR = rset.getString("email_cro");
            if (emailR == null || emailR.isEmpty()) emailR = "";
            String emailRCRPMS = "";
            if (el.getfieldData("datiCRO", "emailR") != null && el.getfieldData("datiCRO", "emailR").size() > 0) {
                emailRCRPMS = el.getfieldData("datiCRO", "emailR").get(0).toString();
            }
            labelBodyMail = "Email CRO";
            res = compareFieldValue(labelBodyMail, emailRCRPMS, emailR);
            if (!res.equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Email CRO res=" + res);
                commonBean.addMetadataValue(idElementStudio, "datiCRO", "emailR", emailR, service);
                bodyMailPart += res;
            }

            String numeroPazienti = rset.getString("paz_num");
            if (numeroPazienti == null || numeroPazienti.isEmpty()) numeroPazienti = "";
            String numeroPazientiCRPMS = "";
            if (el.getfieldData("DatiCentro", "NrPaz") != null && el.getfieldData("DatiCentro", "NrPaz").size() > 0) {
                numeroPazientiCRPMS = el.getfieldData("DatiCentro", "NrPaz").get(0).toString();
            }
            labelBodyMail = "Numero di pazienti da arruolare nel centro";
            res = compareFieldValue(labelBodyMail, numeroPazientiCRPMS, numeroPazienti);
            if (!res.equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Numero di pazienti da arruolare nel centro res=" + res);
                commonBean.addMetadataValue(idCenter, "DatiCentro", "NrPaz", numeroPazienti, service);
                bodyMailPart += res;
            }

            String struttura = rset.getString("centro");
            String strutturaDec = rset.getString("d_centro");
            String stringStruttura = struttura + "###" + strutturaDec;
            if (struttura == null || struttura.isEmpty() || struttura.equals("")) {
                struttura = "";
                strutturaDec = "";
                stringStruttura = "";
            }
            String strutturaCRPMS = "";
            String strutturaDecCRPMS = "";
            if (el.getfieldData("IdCentro", "Struttura") != null && el.getfieldData("IdCentro", "Struttura").size() > 0) {
                strutturaCRPMS = el.getFieldDataCode("IdCentro", "Struttura");
                strutturaDecCRPMS = el.getFieldDataDecode("IdCentro", "Struttura");
            }
            labelBodyMail = "Centro";
            res = compareFieldValue(labelBodyMail, strutturaCRPMS, struttura, strutturaDecCRPMS, strutturaDec);
            if (!res.equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Centro res=" + res);
                commonBean.addMetadataValue(idCenter, "IdCentro", "Struttura", stringStruttura, service);
                bodyMailPart += res;
            }

            String uo = rset.getString("unita_op");
            String uoDec = rset.getString("d_unita_op");
            String stringUO = uo + "###" + uoDec;
            if (uo == null || uo.isEmpty() || uo.equals("")) {
                uo = "";
                uoDec = "";
                stringUO = "";
            }
            String uoCRPMS = "";
            String uoDecCRPMS = "";
            if (el.getfieldData("IdCentro", "UO") != null && el.getfieldData("IdCentro", "UO").size() > 0) {
                uoCRPMS = el.getFieldDataCode("IdCentro", "UO");
                uoDecCRPMS = el.getFieldDataDecode("IdCentro", "UO");
            }
            labelBodyMail = "Unita Operativa";
            res = compareFieldValue(labelBodyMail, uoCRPMS, uo, uoDecCRPMS, uoDec);
            if (!res.equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Unita Operativa res=" + res);
                commonBean.addMetadataValue(idCenter, "IdCentro", "UO", stringUO, service);
                bodyMailPart += res;
            }

            String pi = rset.getString("princ_inv");
            String piDec = rset.getString("d_princ_inv");
            String stringPI = pi + "###" + piDec;
            if (pi == null || pi.isEmpty() || pi.equals("")) {
                pi = "";
                piDec = "";
                stringPI = "";
            }
            String piCRPMS = "";
            String piDecCRPMS = "";
            if (el.getfieldData("IdCentro", "PINomeCognome") != null && el.getfieldData("IdCentro", "PINomeCognome").size() > 0) {
                piCRPMS = el.getFieldDataCode("IdCentro", "PINomeCognome");
                piDecCRPMS = el.getFieldDataDecode("IdCentro", "PINomeCognome");
            }
            labelBodyMail = "Principal Investigator";
            res = compareFieldValue(labelBodyMail, piCRPMS, pi, piDecCRPMS, piDec);
            if (!res.equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Principal Investigator res=" + res);
                commonBean.addMetadataValue(idCenter, "IdCentro", "PINomeCognome", stringPI, service);
                bodyMailPart += res;
            }

            String telefonoPI = rset.getString("tel_pi");
            if (telefonoPI == null || telefonoPI.isEmpty()) telefonoPI = "";
            String telefonoPICRPMS = "";
            if (el.getfieldData("IdCentro", "telefonoPI") != null && el.getfieldData("IdCentro", "telefonoPI").size() > 0) {
                telefonoPICRPMS = el.getfieldData("IdCentro", "telefonoPI").get(0).toString();
            }
            labelBodyMail = "Telefono PI";
            res = compareFieldValue(labelBodyMail, telefonoPICRPMS, telefonoPI);
            if (!res.equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Telefono PI res=" + res);
                commonBean.addMetadataValue(idCenter, "IdCentro", "telefonoPI", telefonoPI, service);
                bodyMailPart += res;
            }

            String emailPI = rset.getString("email_pi");
            if (emailPI == null || emailPI.isEmpty()) emailPI = "";
            String emailPICRPMS = "";
            if (el.getfieldData("IdCentro", "emailPI") != null && el.getfieldData("IdCentro", "emailPI").size() > 0) {
                emailPICRPMS = el.getfieldData("IdCentro", "emailPI").get(0).toString();
            }
            labelBodyMail = "Email PI";
            res = compareFieldValue(labelBodyMail, emailPICRPMS, emailPI);
            if (!res.equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Email PI res=" + res);
                commonBean.addMetadataValue(idCenter, "IdCentro", "emailPI", emailPI, service);
                bodyMailPart += res;
            }


            /*
            String etaPazDec="Pazienti";
            String etaPaz=rset.getString("eta_paz");
            String stringEtaPaz= etaPaz+"###"+etaPazDec;
            if(etaPaz==null || etaPaz.isEmpty() || etaPaz.equals("0")){
                etaPaz="";
                etaPazDec="";
                stringEtaPaz="";
            }
            String etaPazCRPMS="";
            String etaPazDecCRPMS="";
            if(ElementStudio.getfieldData("datiStudio","tipoPop1")!=null && ElementStudio.getfieldData("datiStudio","tipoPop1").size()>0){
                etaPazCRPMS= ElementStudio.getFieldDataCode("datiStudio","tipoPop1");
                etaPazDecCRPMS= ElementStudio.getFieldDataDecode("datiStudio","tipoPop1");
            }
            labelBodyMail="Pazienti";
            res=compareFieldValue(labelBodyMail,etaPazCRPMS,etaPaz,etaPazDecCRPMS,etaPazDec);
            if(!res.equals("")){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Pazienti res="+res);
                commonBean.addMetadataValue(idElementStudio,"datiStudio","tipoPop1",stringEtaPaz,service);
                bodyMailPart+=res;
            }

            String etaVolDec="Volontari sani";
            String etaVol=rset.getString("eta_vol");
            String stringEtaVol= etaVol+"###"+etaVolDec;
            if(etaVol==null || etaVol.isEmpty() || etaVol.equals("0")){
                etaVol="";
                etaVolDec="";
                stringEtaVol="";
            }
            String etaVolCRPMS="";
            String etaVolDecCRPMS="";
            if(ElementStudio.getfieldData("datiStudio","tipoPop2")!=null && ElementStudio.getfieldData("datiStudio","tipoPop2").size()>0){
                etaVolCRPMS= ElementStudio.getFieldDataCode("datiStudio","tipoPop2");
                etaVolDecCRPMS= ElementStudio.getFieldDataDecode("datiStudio","tipoPop2");
            }
            labelBodyMail="Volontari sani";
            res=compareFieldValue(labelBodyMail,etaVolCRPMS,etaVol,etaVolDecCRPMS,etaVolDec);
            if(!res.equals("")){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Volontari sani res="+res);
                commonBean.addMetadataValue(idElementStudio,"datiStudio","tipoPop2",stringEtaVol,service);
                bodyMailPart+=res;
            }

            String etaIncaDec="Soggetti incapaci di intendere e di volere";
            String etaInca=rset.getString("eta_inca");
            String stringEtaInca= etaInca+"###"+etaIncaDec;
            if(etaInca==null || etaInca.isEmpty() || etaInca.equals("0")){
                etaInca="";
                etaIncaDec="";
                stringEtaInca="";
            }
            String etaIncaCRPMS="";
            String etaIncaDecCRPMS="";
            if(ElementStudio.getfieldData("datiStudio","tipoPop5")!=null && ElementStudio.getfieldData("datiStudio","tipoPop5").size()>0){
                etaIncaCRPMS= ElementStudio.getFieldDataCode("datiStudio","tipoPop5");
                etaIncaDecCRPMS= ElementStudio.getFieldDataDecode("datiStudio","tipoPop5");
            }
            labelBodyMail="Soggetti incapaci di intendere e di volere";
            res=compareFieldValue(labelBodyMail,etaIncaCRPMS,etaInca,etaIncaDecCRPMS,etaIncaDec);
            if(!res.equals("")){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Soggetti incapaci di intendere e di volere res="+res);
                commonBean.addMetadataValue(idElementStudio,"datiStudio","tipoPop5",stringEtaInca,service);
                bodyMailPart+=res;
            }


                String sessoPop=rset.getString("sesso_pop");
                String sessoPopDec=rset.getString("d_sesso_pop");
                String stringSesso= sessoPop+"###"+sessoPopDec;
                if(sessoPop==null || sessoPop.isEmpty()){
                    sessoPop="";
                    sessoPopDec="";
                    stringSesso="";
                }
                String sessoPopCRPMS="";
                String sessoPopDecCRPMS="";
                if(ElementStudio.getfieldData("datiStudio","sessoPop")!=null && ElementStudio.getfieldData("datiStudio","sessoPop").size()>0){
                    sessoPopCRPMS= ElementStudio.getFieldDataCode("datiStudio","sessoPop");
                    sessoPopDecCRPMS= ElementStudio.getFieldDataDecode("datiStudio","sessoPop");
                }
                labelBodyMail="Sesso Popolazione";
                res=compareFieldValue(labelBodyMail,sessoPopCRPMS,sessoPop,sessoPopDecCRPMS,sessoPopDec);
                if(!res.equals("")){
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Sesso Popolazione res="+res);
                    commonBean.addMetadataValue(idElementStudio,"datiStudio","sessoPop",stringSesso,service);
                    bodyMailPart+=res;
                }

                String etaUteroDec="In utero";
                String etaUtero=rset.getString("eta_utero");
                String stringEtaUtero= etaUtero+"###"+etaUteroDec;
                if(etaUtero==null || etaUtero.isEmpty() || etaUtero.equals("0")){
                    etaUtero="";
                    etaUteroDec="";
                    stringEtaUtero="";
                }
                String etaUteroCRPMS="";
                String etaUteroDecCRPMS="";
                if(ElementStudio.getfieldData("datiStudio","etaUtero")!=null && ElementStudio.getfieldData("datiStudio","etaUtero").size()>0){
                    etaUteroCRPMS= ElementStudio.getFieldDataCode("datiStudio","etaUtero");
                    etaUteroDecCRPMS= ElementStudio.getFieldDataDecode("datiStudio","etaUtero");
                }
                labelBodyMail="Popolazione pediatrica";
                res=compareFieldValue(labelBodyMail,etaUteroCRPMS,etaUtero,etaUteroDecCRPMS,etaUteroDec);
                if(!res.equals("")){
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"In utero res="+res);
                    commonBean.addMetadataValue(idElementStudio,"datiStudio","etaUtero",stringEtaUtero,service);
                    bodyMailPart+=res;
                }

                String etaNeonati=rset.getString("eta_neonati");
                String etaNeonatiDec="Neonati pretermine (inferiore o uguale alla 37a settimana)";
                String stringEtaNeonati= etaNeonati+"###"+etaNeonatiDec;
                if(etaNeonati==null || etaNeonati.isEmpty() || etaNeonati.equals("0")){
                    etaNeonati="";
                    etaNeonatiDec="";
                    stringEtaNeonati="";
                }
                String etaNeonatiCRPMS="";
                String etaNeonatiDecCRPMS="";
                if(ElementStudio.getfieldData("datiStudio","etaNeonati")!=null && ElementStudio.getfieldData("datiStudio","etaNeonati").size()>0){
                    etaNeonatiCRPMS= ElementStudio.getFieldDataCode("datiStudio","etaNeonati");
                    etaNeonatiDecCRPMS= ElementStudio.getFieldDataDecode("datiStudio","etaNeonati");
                }
                labelBodyMail="Popolazione pediatrica";
                res=compareFieldValue(labelBodyMail,etaNeonatiCRPMS,etaNeonati,etaNeonatiDecCRPMS,etaNeonatiDec);
                if(!res.equals("")){
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Neonati pretermine (inferiore o uguale alla 37a settimana) res="+res);
                    commonBean.addMetadataValue(idElementStudio,"datiStudio","etaNeonati",stringEtaNeonati,service);
                    bodyMailPart+=res;
                }

                String etaPop01MDec="Neonati (0-27 giorni)";
                String etaPop01M=rset.getString("eta_pop_01m");
                String stringEtaPop01M= etaPop01M+"###"+etaPop01MDec;
                if(etaPop01M==null || etaPop01M.isEmpty() || etaPop01M.equals("0")){
                    etaPop01M="";
                    etaPop01MDec="";
                    stringEtaPop01M="";
                }
                String etaPop01MCRPMS="";
                String etaPop01MDecCRPMS="";
                if(ElementStudio.getfieldData("datiStudio","etaPop01M")!=null && ElementStudio.getfieldData("datiStudio","etaPop01M").size()>0){
                    etaPop01MCRPMS= ElementStudio.getFieldDataCode("datiStudio","etaPop01M");
                    etaPop01MDecCRPMS= ElementStudio.getFieldDataDecode("datiStudio","etaPop01M");
                }
                labelBodyMail="Popolazione pediatrica";
                res=compareFieldValue(labelBodyMail,etaPop01MCRPMS,etaPop01M,etaPop01MDecCRPMS,etaPop01MDec);
                if(!res.equals("")){
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Eta neonati(0-27 giorni) res="+res);
                    commonBean.addMetadataValue(idElementStudio,"datiStudio","etaPop01M",stringEtaPop01M,service);
                    bodyMailPart+=res;
                }

                String etaPop123M=rset.getString("eta_pop_123m");
                String etaPop123MDec="Lattanti e bambini piccoli (28 giorni-23 mesi)";
                String stringEtaPop123M= etaPop123M+"###"+etaPop123MDec;
                if(etaPop123M==null || etaPop123M.isEmpty() || etaPop123M.equals("0")){
                    etaPop123M="";
                    etaPop123MDec="";
                    stringEtaPop123M="";
                }
                String etaPop123MCRPMS="";
                String etaPop123MDecCRPMS="";
                if(ElementStudio.getfieldData("datiStudio","etaPop123M")!=null && ElementStudio.getfieldData("datiStudio","etaPop123M").size()>0){
                    etaPop123MCRPMS= ElementStudio.getFieldDataCode("datiStudio","etaPop123M");
                    etaPop123MDecCRPMS= ElementStudio.getFieldDataDecode("datiStudio","etaPop123M");
                }
                labelBodyMail="Popolazione pediatrica";
                res=compareFieldValue(labelBodyMail,etaPop123MCRPMS,etaPop123M,etaPop123MDecCRPMS,etaPop123MDec);
                if(!res.equals("")){
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Lattanti e bambini piccoli (28 giorni-23 mesi) res="+res);
                    commonBean.addMetadataValue(idElementStudio,"datiStudio","etaPop123M",stringEtaPop123M,service);
                    bodyMailPart+=res;
                }

                String etaPop211A=rset.getString("eta_pop_211a");
                String etaPop211ADec="Bambini (2-11 anni)";
                String stringEtaPop211A= etaPop211A+"###"+etaPop211ADec;
                if(etaPop211A==null || etaPop211A.isEmpty() || etaPop211A.equals("0")){
                    etaPop211A="";
                    etaPop211ADec="";
                    stringEtaPop211A="";
                }
                String etaPop211ACRPMS="";
                String etaPop211ADecCRPMS="";
                if(ElementStudio.getfieldData("datiStudio","etaPop211A")!=null && ElementStudio.getfieldData("datiStudio","etaPop211A").size()>0){
                    etaPop211ACRPMS= ElementStudio.getFieldDataCode("datiStudio","etaPop211A");
                    etaPop211ADecCRPMS= ElementStudio.getFieldDataDecode("datiStudio","etaPop211A");
                }
                labelBodyMail="Popolazione pediatrica";
                res=compareFieldValue(labelBodyMail,etaPop211ACRPMS,etaPop211A,etaPop211ADecCRPMS,etaPop211ADec);
                if(!res.equals("")){
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Bambini (2-11 anni) res="+res);
                    commonBean.addMetadataValue(idElementStudio,"datiStudio","etaPop211A",stringEtaPop211A,service);
                    bodyMailPart+=res;
                }

                String etaPop1318A=rset.getString("eta_pop_1318a");
                String etaPop1318ADec="Adolescenti (12-17 anni)";
                String stringEtaPop1318A= etaPop1318A+"###"+etaPop1318ADec;
                if(etaPop1318A==null || etaPop1318A.isEmpty() || etaPop1318A.equals("0")){
                    etaPop1318A="";
                    etaPop1318ADec="";
                    stringEtaPop1318A="";
                }
                String etaPop1318ACRPMS="";
                String etaPop1318ADecCRPMS="";
                if(ElementStudio.getfieldData("datiStudio","etaPop12318A")!=null && ElementStudio.getfieldData("datiStudio","etaPop12318A").size()>0){
                    etaPop1318ACRPMS= ElementStudio.getFieldDataCode("datiStudio","etaPop12318A");
                    etaPop1318ADecCRPMS= ElementStudio.getFieldDataDecode("datiStudio","etaPop12318A");
                }
                labelBodyMail="Popolazione pediatrica";
                res=compareFieldValue(labelBodyMail,etaPop1318ACRPMS,etaPop1318A,etaPop1318ADecCRPMS,etaPop1318ADec);
                if(!res.equals("")){
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Adolescenti (12-17 anni) res="+res);
                    commonBean.addMetadataValue(idElementStudio,"datiStudio","etaPop12318A",stringEtaPop1318A,service);
                    bodyMailPart+=res;
                }

                String etaPop1944A=rset.getString("eta_pop_1944a");
                String etaPop1944ADec="Adulti (18-44 anni)";
                String stringEtaPop1944A= etaPop1944A+"###"+etaPop1944ADec;
                if(etaPop1944A==null || etaPop1944A.isEmpty() || etaPop1944A.equals("0")){
                    etaPop1944A="";
                    etaPop1944ADec="";
                    stringEtaPop1944A="";
                }
                String etaPop1944ACRPMS="";
                String etaPop1944ADecCRPMS="";
                if(ElementStudio.getfieldData("datiStudio","etaPop1944A")!=null && ElementStudio.getfieldData("datiStudio","etaPop1944A").size()>0){
                    etaPop1944ACRPMS= ElementStudio.getFieldDataCode("datiStudio","etaPop1944A");
                    etaPop1944ADecCRPMS= ElementStudio.getFieldDataDecode("datiStudio","etaPop1944A");
                }
                labelBodyMail="Popolazione adulta";
                res=compareFieldValue(labelBodyMail,etaPop1944ACRPMS,etaPop1944A,etaPop1944ADecCRPMS,etaPop1944ADec);
                if(!res.equals("")){
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Adulti (18-44 anni) res="+res);
                    commonBean.addMetadataValue(idElementStudio,"datiStudio","etaPop1944A",stringEtaPop1944A,service);
                    bodyMailPart+=res;
                }

                String etaPop4564A=rset.getString("eta_pop_4564a");
                String etaPop4564ADec="Adulti (45-65 anni)";
                String stringEtaPop4564A= etaPop4564A+"###"+etaPop4564ADec;
                if(etaPop4564A==null || etaPop4564A.isEmpty() || etaPop4564A.equals("0")){
                    etaPop4564A="";
                    etaPop4564ADec="";
                    stringEtaPop4564A="";
                }
                String etaPop4564ACRPMS="";
                String etaPop4564ADecCRPMS="";
                if(ElementStudio.getfieldData("datiStudio","etaPop4564A")!=null && ElementStudio.getfieldData("datiStudio","etaPop4564A").size()>0){
                    etaPop4564ACRPMS= ElementStudio.getFieldDataCode("datiStudio","etaPop4564A");
                    etaPop4564ADecCRPMS= ElementStudio.getFieldDataDecode("datiStudio","etaPop4564A");
                }
                labelBodyMail="Popolazione adulta";
                res=compareFieldValue(labelBodyMail,etaPop4564ACRPMS,etaPop4564A,etaPop4564ADecCRPMS,etaPop4564ADec);
                if(!res.equals("")){
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Adulti (45-65 anni) res="+res);
                    commonBean.addMetadataValue(idElementStudio,"datiStudio","etaPop4564A",stringEtaPop4564A,service);
                    bodyMailPart+=res;
                }

                String etaPop65A=rset.getString("eta_pop_65a");
                String etaPop65ADec="Anziani (>65 anni)";
                String stringEtaPop65A= etaPop65A+"###"+etaPop65ADec;
                if(etaPop65A==null || etaPop65A.isEmpty() || etaPop65A.equals("0")){
                    etaPop65A="";
                    etaPop65ADec="";
                    stringEtaPop65A="";
                }
                String etaPop65ACRPMS="";
                String etaPop65ADecCRPMS="";
                if(ElementStudio.getfieldData("datiStudio","etaPop65A")!=null && ElementStudio.getfieldData("datiStudio","etaPop65A").size()>0){
                    etaPop65ACRPMS= ElementStudio.getFieldDataCode("datiStudio","etaPop65A");
                    etaPop65ADecCRPMS= ElementStudio.getFieldDataDecode("datiStudio","etaPop65A");
                }
                labelBodyMail="Popolazione geriatrica";
                res=compareFieldValue(labelBodyMail,etaPop65ACRPMS,etaPop65A,etaPop65ADecCRPMS,etaPop65ADec);
                if(!res.equals("")){
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Anziani (>65 anni) res="+res);
                    commonBean.addMetadataValue(idElementStudio,"datiStudio","etaPop65A",stringEtaPop65A,service);
                    bodyMailPart+=res;
                }

            //}

            String multicentrico =  rset.getString("multicentrica");
            String dMulticentrico =  rset.getString("d_multicentrica");
            String stringMulticentrico = multicentrico+"###"+dMulticentrico;
            if(multicentrico==null || multicentrico.isEmpty()){
                multicentrico = "";
                dMulticentrico = "";
                stringMulticentrico = "";
            }
            String multicentricoCRPMS = "";
            String multicentricoCRPMSDec = "";
            if(ElementStudio.getfieldData("datiStudio","monoMulti")!=null && ElementStudio.getfieldData("datiStudio","monoMulti").size()>0){
                multicentricoCRPMS = ElementStudio.getfieldData("datiStudio","monoMulti").get(0).toString().split("###")[0];
                multicentricoCRPMSDec = ElementStudio.getfieldData("datiStudio","monoMulti").get(0).toString().split("###")[1];
            }
            labelBodyMail="Multicentrico";
            res=compareFieldValue(labelBodyMail,multicentricoCRPMS,multicentrico,multicentricoCRPMSDec,dMulticentrico);
            if(!res.equals("")){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Multicentrico res="+res);
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Multicentrico stringMulticentrico="+stringMulticentrico);
                commonBean.addMetadataValue(idElementStudio,"datiStudio","monoMulti",stringMulticentrico,service);
                bodyMailPart+=res;
            }

            String controllato =  rset.getString("ds3");
            String dControllato =  rset.getString("d_ds3");
            String stringControllato = controllato+"###"+dControllato;
            if(controllato==null || controllato.isEmpty()){
                controllato = "";
                dControllato = "";
                stringControllato = "";
            }
            String controllatoCRPMS = "";
            String controllatoCRPMSDec = "";
            if(ElementStudio.getfieldData("datiStudio","studioControllato")!=null && ElementStudio.getfieldData("datiStudio","studioControllato").size()>0){
                controllatoCRPMS = ElementStudio.getfieldData("datiStudio","studioControllato").get(0).toString().split("###")[0];
                controllatoCRPMSDec = ElementStudio.getfieldData("datiStudio","studioControllato").get(0).toString().split("###")[1];
            }
            labelBodyMail="Controllato";
            res=compareFieldValue(labelBodyMail,controllatoCRPMS,controllato,controllatoCRPMSDec,dControllato);
            if(!res.equals("")){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Controllato res="+res);
                commonBean.addMetadataValue(idElementStudio,"datiStudio","studioControllato",stringControllato,service);
                bodyMailPart+=res;
            }

            String controllatoVs =  rset.getString("ds3_spec");
            String dControllatoVs =  rset.getString("d_ds3_spec");
            String stringControllatoVs = controllatoVs+"###"+dControllatoVs;
            if(controllatoVs==null || controllatoVs.isEmpty()){
                controllatoVs = "";
                dControllatoVs = "";
                stringControllatoVs = "";
            }
            String controllatoVsCRPMS = "";
            String controllatoVsCRPMSDec = "";
            if(ElementStudio.getfieldData("datiStudio","studioControllatoVs")!=null && ElementStudio.getfieldData("datiStudio","studioControllatoVs").size()>0){
                controllatoVsCRPMS = ElementStudio.getfieldData("datiStudio","studioControllatoVs").get(0).toString().split("###")[0];
                controllatoVsCRPMSDec = ElementStudio.getfieldData("datiStudio","studioControllatoVs").get(0).toString().split("###")[1];
            }
            labelBodyMail="Controllato VS";
            res=compareFieldValue(labelBodyMail,controllatoVsCRPMS,controllatoVs,controllatoVsCRPMSDec,dControllatoVs);
            if(!res.equals("")){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Controllato VS res="+res);
                commonBean.addMetadataValue(idElementStudio,"datiStudio","studioControllatoVs",stringControllatoVs,service);
                bodyMailPart+=res;
            }

            String endpoint=rset.getString("endpoint");
            String endpointDec=rset.getString("d_endpoint");
            String stringEndpoint= endpoint+"###"+endpointDec;
            if(endpoint==null || endpoint.isEmpty()){
                endpoint="";
                endpointDec="";
                stringEndpoint="";
            }
            String endpointCRPMS="";
            String endpointDecCRPMS="";
            if(ElementStudio.getfieldData("datiStudio","endpoint")!=null && ElementStudio.getfieldData("datiStudio","endpoint").size()>0){
                endpointCRPMS= ElementStudio.getFieldDataCode("datiStudio","endpoint");
                endpointDecCRPMS= ElementStudio.getFieldDataDecode("datiStudio","endpoint");
            }
            labelBodyMail="Endpoint";
            res=compareFieldValue(labelBodyMail,endpointCRPMS,endpoint,endpointDecCRPMS,endpointDec);
            if(!res.equals("")){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Endpoint res="+res);
                commonBean.addMetadataValue(idElementStudio,"datiStudio","endpoint",stringEndpoint,service);
                bodyMailPart+=res;
            }


            String dataInizioCRPMS = "";
            String dataInizio = rset.getString("iniz_recl_ita_dt");
            if(dataInizio==null || dataInizio.isEmpty()) dataInizio="";
            if(ElementStudio.getfieldData("datiStudio","dataInizio")!=null && ElementStudio.getfieldData("datiStudio","dataInizio").size()>0){
                dataInizioCRPMS = ElementStudio.getFieldDataFormattedDates("datiStudio","dataInizio","dd/MM/yyyy").get(0);
            }
            labelBodyMail="Data Prevista Inizio Studio";
            res=compareFieldValue(labelBodyMail,dataInizioCRPMS,dataInizio);
            if(!res.equals("")){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Data Prevista Inizio Studio res="+res);
                commonBean.addMetadataValue(idElementStudio,"datiStudio","dataInizio",dataInizio,service);
                bodyMailPart+=res;
            }
            */
            /*
            String dataFineCRPMS = "";
            String dataFine = rset.getString("fine_recl_ita_dt");
            if(dataFine==null || dataFine.isEmpty()) dataFine="";
            if(ElementStudio.getfieldData("datiStudio","dataFine")!=null && ElementStudio.getfieldData("datiStudio","dataFine").size()>0){
                dataFineCRPMS = ElementStudio.getFieldDataFormattedDates("datiStudio","dataFine","dd/MM/yyyy").get(0);
            }
            labelBodyMail="Data Prevista Fine Studio";
            res=compareFieldValue(labelBodyMail,dataFineCRPMS,dataFine);
            if(!res.equals("")){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Data Prevista Fine Studio res="+res);
                commonBean.addMetadataValue(idElementStudio,"datiStudio","dataFine",dataFine,service);
                bodyMailPart+=res;
            }
            */

            //Dati centro-specifici

            /* GC 23/01/2015 - Commentata tutta la parte centro-specifica per evitare problemi di utenze con PI
            String numeroPazienti=rset.getString("paz_num");
            if(numeroPazienti==null || numeroPazienti.isEmpty()) numeroPazienti="";
            String numeroPazientiCRPMS="";
            if(el.getfieldData("DatiCentro","NrPaz")!=null && el.getfieldData("DatiCentro","NrPaz").size()>0){
                numeroPazientiCRPMS=el.getfieldData("DatiCentro","NrPaz").get(0).toString();
            }
            labelBodyMail="Numero di pazienti da arruolare nel centro";
            res=compareFieldValue(labelBodyMail,numeroPazientiCRPMS,numeroPazienti);
            if(!res.equals("")){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Numero di pazienti da arruolare nel centro res="+res);
                commonBean.addMetadataValue(idCenter,"DatiCentro","NrPaz",numeroPazienti,service);
                bodyMailPart+=res;
            }

            String struttura=rset.getString("centro");
            String strutturaDec=rset.getString("d_centro");
            String stringStruttura=struttura+"###"+strutturaDec;
            if(struttura==null || struttura.isEmpty() || struttura.equals("")){
                struttura="";
                strutturaDec="";
                stringStruttura="";
            }
            String strutturaCRPMS="";
            String strutturaDecCRPMS="";
            if(el.getfieldData("IdCentro","Struttura")!=null && el.getfieldData("IdCentro","Struttura").size()>0){
                strutturaCRPMS=el.getFieldDataCode("IdCentro","Struttura");
                strutturaDecCRPMS=el.getFieldDataDecode("IdCentro","Struttura");
            }
            labelBodyMail="Centro";
            res=compareFieldValue(labelBodyMail,strutturaCRPMS,struttura,strutturaDecCRPMS,strutturaDec);
            if(!res.equals("")){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Centro res="+res);
                commonBean.addMetadataValue(idCenter,"IdCentro","Struttura",stringStruttura,service);
                bodyMailPart+=res;
            }

            String istituto=rset.getString("istituto");
            String istitutoDec=rset.getString("d_istituto");
            String stringIstituto=istituto+"###"+istitutoDec;
            if(istituto==null || istituto.isEmpty() || istituto.equals("")){
                istituto="";
                istitutoDec="";
                stringIstituto="";
            }
            String istitutoCRPMS="";
            String istitutoDecCRPMS="";
            if(el.getfieldData("IdCentro","Istituto")!=null && el.getfieldData("IdCentro","Istituto").size()>0){
                istitutoCRPMS=el.getFieldDataCode("IdCentro","Istituto");
                istitutoDecCRPMS=el.getFieldDataDecode("IdCentro","Istituto");
            }
            labelBodyMail="Istituto";
            res=compareFieldValue(labelBodyMail,istitutoCRPMS,istituto,istitutoDecCRPMS,istitutoDec);
            if(!res.equals("")){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Istituto res="+res);
                commonBean.addMetadataValue(idCenter,"IdCentro","Istituto",stringIstituto,service);
                bodyMailPart+=res;
            }

            String dipartimento=rset.getString("dipartimento");
            String dipartimentoDec=rset.getString("d_dipartimento");
            String stringDipartimento=dipartimento+"###"+dipartimentoDec;
            if(dipartimento==null || dipartimento.isEmpty() || dipartimento.equals("")){
                dipartimento="";
                dipartimentoDec="";
                stringDipartimento="";
            }
            String dipartimentoCRPMS="";
            String dipartimentoDecCRPMS="";
            if(el.getfieldData("IdCentro","Dipartimento")!=null && el.getfieldData("IdCentro","Dipartimento").size()>0){
                dipartimentoCRPMS=el.getFieldDataCode("IdCentro","Dipartimento");
                dipartimentoDecCRPMS=el.getFieldDataDecode("IdCentro","Dipartimento");
            }
            labelBodyMail="Dipartimento";
            res=compareFieldValue(labelBodyMail,dipartimentoCRPMS,dipartimento,dipartimentoDecCRPMS,dipartimentoDec);
            if(!res.equals("")){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Dipartimento res="+res);
                commonBean.addMetadataValue(idCenter,"IdCentro","Dipartimento",stringDipartimento,service);
                bodyMailPart+=res;
            }

            String uo=rset.getString("unita_op");
            String uoDec=rset.getString("d_unita_op");
            String stringUO=uo+"###"+uoDec;
            if(uo==null || uo.isEmpty() || uo.equals("")){
                uo="";
                uoDec="";
                stringUO="";
            }
            String uoCRPMS="";
            String uoDecCRPMS="";
            if(el.getfieldData("IdCentro","UO")!=null && el.getfieldData("IdCentro","UO").size()>0){
                uoCRPMS=el.getFieldDataCode("IdCentro","UO");
                uoDecCRPMS=el.getFieldDataDecode("IdCentro","UO");
            }
            labelBodyMail="Unita Operativa";
            res=compareFieldValue(labelBodyMail,uoCRPMS,uo,uoDecCRPMS,uoDec);
            if(!res.equals("")){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Unita Operativa res="+res);
                commonBean.addMetadataValue(idCenter,"IdCentro","UO",stringUO,service);
                bodyMailPart+=res;
            }

            String pi=rset.getString("princ_inv");
            String piDec=rset.getString("d_princ_inv");
            String stringPI=pi+"###"+piDec;
            if(pi==null || pi.isEmpty() || pi.equals("")){
                pi="";
                piDec="";
                stringPI="";
            }
            String piCRPMS="";
            String piDecCRPMS="";
            if(el.getfieldData("IdCentro","PINomeCognome")!=null && el.getfieldData("IdCentro","PINomeCognome").size()>0){
                piCRPMS=el.getFieldDataCode("IdCentro","PINomeCognome");
                piDecCRPMS=el.getFieldDataDecode("IdCentro","PINomeCognome");
            }
            labelBodyMail="Principal Investigator";
            res=compareFieldValue(labelBodyMail,piCRPMS,pi,piDecCRPMS,piDec);
            if(!res.equals("")){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Principal Investigator res="+res);
                commonBean.addMetadataValue(idCenter,"IdCentro","PINomeCognome",stringPI,service);
                bodyMailPart+=res;
            }
            */

            if (!bodyMailPart.equals("")) bodyMail += "ID Studio=" + idStudio + "\n\n" + bodyMailPart + "\n\n";

            //Fine

            sql1 = "update ce_reginvio set crpms_aggiornato=1 where visitnum=" + visitnum + " and visitnum_progr=" + visitnum_progr + " and esam=" + esam + " and progr=" + progr + " and id_stud=" + id_stud;
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "sql1 = " + sql1);
            PreparedStatement stmt1 = conn.prepareStatement(sql1);
            ResultSet rset1 = stmt1.executeQuery();

            service.getTxManager().commitAndKeepAlive();

        }

        execution.setVariable("bodyMail", bodyMail);
        conn.close();
        commonBean.closeDocumentService(service);
    }


    /**
     * TOSCANA-190
     * per l'invio del contratto firmato e dell'atto liberativo bisogna che lato CE sia stato già rilasciato il parere (viene richiamato dal WF)
     */
    public boolean checkCentroParereCE(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Connection conn = dataSource.getConnection();
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Sono in checkCentroParereCE - elementId=" + elementId);
        boolean passed = false;
        Element elContratto = service.getElement(Long.parseLong(elementId));
        Integer tipologiaContratto = Integer.valueOf(elContratto.getfieldData("tipologiaContratto", "TipoContratto").get(0).toString().split("###")[0]);
        if (tipologiaContratto != 4 && tipologiaContratto != 7) { //Se non è 4###Convenzione firmata e 7###Atto deliberativo allora procedi all'invio
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "PROCEDI PURE NON DEVO CONTROLLARE L'ESISTENZA DEL PARERE! ");
            passed = true;
        } else {
            //Se è 4###Convenzione firmata o 7###Atto deliberativo allora controlla che lato ce sia stato rilasciato il parere
            Element elCentro = elContratto.getParent().getParent();
            Integer idStudio = Integer.valueOf(elCentro.getParent().getfieldData("UniqueIdStudio", "id").get(0).toString());
            Integer idCentro = Integer.valueOf(elCentro.getfieldData("IdCentro", "Struttura").get(0).toString().split("###")[0]);
            String idCentroDec = elCentro.getfieldData("IdCentro", "Struttura").get(0).toString().split("###")[1];
            String filename = elContratto.getFile().getFileName();
            int i = filename.lastIndexOf(".");
            String ext = "";
            if (i > 0) {
                ext = filename.substring(i + 1);
            }

            String sql = " select r.id_stud,c.visitnum,c.visitnum_progr,c.esam,ce.progr,c.userid from " +
                    "  ce_info_studio i," +
                    "  ce_registrazione r," +
                    "  ce_coordinate c," +
                    "  ce_centrilocali ce" +
                    " where ce.id_stud=i.id_stud(+)" +
                    "  and r.id_stud=c.id_stud" +
                    "  and r.id_stud=ce.id_stud" +
                    "  and nvl(ce.stato,0)=5" +
                    "  and c.visitnum=10" +
                    "  and c.visitnum_progr=ce.progr-1" +
                    "  and c.esam=1" +
                    "  and nvl(c.fine,0)=0" +
                    "  and (r.ritirato is null or r.ritirato=0)" +
                    "  and r.id_stud=? and ce.centro=? and ce.crpms_center_progr=?";
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "eseguo sql: " + sql);
            PreparedStatement parere_ce_stmt = conn.prepareStatement(sql);
            parere_ce_stmt.setInt(1, idStudio);
            parere_ce_stmt.setInt(2, idCentro);
            parere_ce_stmt.setLong(3, elCentro.getId());
            ResultSet parere_ce_rset = parere_ce_stmt.executeQuery();
            boolean parere_cePresente1 = parere_ce_rset.next();
            if (parere_cePresente1) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "parere presente! ");
                passed = true;
            } else {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "parere NON presente! ");
            }
        }
        commonBean.closeDocumentService(service);
        return passed;

    }

    public void copiaContrattoInCeOnline(String elementId) throws Exception {

        it.cineca.siss.axmr3.log.Log.debug(getClass(), "inizio copiaContrattoInCeOnline");
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "idContratto=" + elementId);
        DocumentService service = commonBean.getDocumentService();
        Connection conn = dataSource.getConnection();
        Element elContratto = service.getElement(Long.parseLong(elementId));
        Integer tipologiaContratto = Integer.valueOf(elContratto.getfieldData("tipologiaContratto", "TipoContratto").get(0).toString().split("###")[0]);
        String tipologiaContrattoDec = elContratto.getfieldData("tipologiaContratto", "TipoContratto").get(0).toString().split("###")[1];
        Calendar dataContratto = elContratto.getFile().getDate();
        java.sql.Date dataContrattoSql = new java.sql.Date(dataContratto.getTime().getTime());
        String autore = elContratto.getFile().getAutore();
        String UseridIns = "";
        Element elCentro = elContratto.getParent().getParent();
        Integer idCentro = Integer.valueOf(elCentro.getfieldData("IdCentro", "Struttura").get(0).toString().split("###")[0]);
        String DenCentro = elCentro.getfieldData("IdCentro", "Struttura").get(0).toString().split("###")[1];
        Integer idStudio = Integer.valueOf(elCentro.getParent().getfieldData("UniqueIdStudio", "id").get(0).toString());
        String idCentroDec = elCentro.getfieldData("IdCentro", "Struttura").get(0).toString().split("###")[1];
        boolean recordPresente1;
        String sql = "select centro from ce_elenco_centriloc where id=?";
        PreparedStatement struttura_stmt = conn.prepareStatement(sql);
        struttura_stmt.setInt(1, idCentro);
        ResultSet struttura_rset = struttura_stmt.executeQuery();
        recordPresente1 = struttura_rset.next();
        Integer CE;
        if (recordPresente1) {
            CE = struttura_rset.getInt("centro");
            switch (CE) {
                case 1:
                    UseridIns = "LPOLVERELLI";//CEAV Sud Est
                    break;
                case 2:
                    UseridIns = "DCARIGNANI";//CEAV Nord Ovest
                    break;
                case 3:
                    UseridIns = "MVIETRI";//CEAV Centro
                    break;
                case 4:
                    UseridIns = "MLEO";// CEP
                    break;
            }

        }
        if (Integer.valueOf(elCentro.getParent().getfieldData("datiStudio", "popolazioneStudio").get(0).toString().split("###")[0]) == 1) {
            UseridIns = "MLEO";//se pediatrico sovrascrivo per assegnarlo CEP!!!!
        }
        if (tipologiaContratto != 4 && tipologiaContratto != 7) { //Se non è 4###Convenzione firmata e 7###Atto deliberativo allora procedi all'invio standard (pre TOSCANA-190)

            //Long idStudio = Long.valueOf(elCentro.getParent().getfieldData("UniqueIdStudio", "id").get(0).toString());
            Integer CurrCenterProgr = 0;
            String sqlprogr = "";
            boolean recordPresente;
            Integer p = null;
            String docCs = "";
            String docCsDen = "";
            String docCsAltro = "";
            String docvers = "";
            String docnote = "";
            String sqlIdDocs = "";

            Integer iddoc;
            String ext = "";
            long idTipoRef;
            String keywords = "";
            String fileCeOnline = "";


            sql = "select progr-1 as currcenterprogr from ce_centrilocali where crpms_center_progr=?";
            PreparedStatement currcenterprogr_stmt = conn.prepareStatement(sql);
            currcenterprogr_stmt.setLong(1, elCentro.getId());
            ResultSet currcenterprogr_rset = currcenterprogr_stmt.executeQuery();
            recordPresente1 = currcenterprogr_rset.next();
            if (recordPresente1) {
                CurrCenterProgr = currcenterprogr_rset.getInt("currcenterprogr");
            }

            String filename = elContratto.getFile().getFileName();
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "contratto da portare in CE-ONLINE nomefile= " + filename);

            Integer tipoDoc = 14; //tipologia per contratto

            //GC 15/07/2016 Query per mappatura documenti in CE-ONLINE
            String sqlDocsCE = "select id,descrizione from CRMS_DOC_LOC,CE_DOC_LOC where id_doc_ce=id and code=" + tipoDoc;
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Query = " + sqlDocsCE);
            PreparedStatement stmtdocce = conn.prepareStatement(sqlDocsCE);
            ResultSet rsetDocsCe = stmtdocce.executeQuery();
            recordPresente1 = rsetDocsCe.next();
            if (recordPresente1) {
                docCs = rsetDocsCe.getString("id");
                docCsDen = rsetDocsCe.getString("descrizione");
            }
            docCsAltro = null;//child.getFieldDataDecode("DocCentroSpec", "TipoDocumento");

            CallableStatement cstmt2 = null;
            String procedure2 = "{call INSERT_DOC_CENTRO_CRPMS_TO_CE(?,?,?, ?,?,?, ?,?,?, ?,?,?, ?,?,?, ?,?)}";

            cstmt2 = conn.prepareCall(procedure2);

            cstmt2.setLong(1, idStudio);

            //recupero il prossimo progressivo del documento
            sqlprogr = "select nvl(max(progr),0)+1 as p from CE_COORDINATE where ID_STUD=" + idStudio + " and visitnum=1 and visitnum_progr=" + CurrCenterProgr + " and esam=23";
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "sqlprogr=" + sqlprogr);
            PreparedStatement stmt = conn.prepareStatement(sqlprogr);
            ResultSet rset = stmt.executeQuery();

            recordPresente = rset.next();
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "recordPresente=" + recordPresente);
            if (recordPresente) {
                keywords = "DOC_CENTROSPEC";
                p = rset.getInt("p");
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "p=" + p);
                cstmt2.setLong(2, p);

                if (CurrCenterProgr == 0) {
                    if (p > 1) {
                        keywords += "_" + p;
                    }
                } else {
                    keywords += "_" + p + "_" + CurrCenterProgr;
                }

                it.cineca.siss.axmr3.log.Log.debug(getClass(), "keywords=" + keywords);
            }

            cstmt2.setString(3, docCs);
            cstmt2.setString(4, docCsDen);
            if (docCsAltro != null) {
                cstmt2.setString(5, docCsAltro);
            } else {
                cstmt2.setNull(5, Types.VARCHAR);
            }

            Calendar dataDoc = elContratto.getFile().getDate();
            //java.sql.Date sqlDate =  new java.sql.Date(dataDoc.getTime().getTime() );

            if (dataDoc != null) {
                java.sql.Date sqlDate = new java.sql.Date(dataDoc.getTime().getTime());
                cstmt2.setDate(6, sqlDate);
                cstmt2.setString(7, "OKOKOK");
            } else {
                cstmt2.setNull(6, Types.DATE);
                cstmt2.setNull(7, Types.VARCHAR);
            }

            docvers = elContratto.getFile().getVersion();
            if (docvers != null) {
                cstmt2.setString(8, docvers);
            } else {
                cstmt2.setNull(8, Types.VARCHAR);
            }

            docnote = elContratto.getFile().getNote();
            if (docnote != null) {
                cstmt2.setString(9, docnote);
            } else {
                cstmt2.setNull(9, Types.VARCHAR);
            }

            int i = filename.lastIndexOf(".");
            if (i > 0) {
                ext = filename.substring(i + 1);
            }

            cstmt2.setString(11, ext);

            sqlIdDocs = "select DOCS_ID.NEXTVAL as iddoc from DUAL";
            PreparedStatement stmt1 = conn.prepareStatement(sqlIdDocs);
            ResultSet rset1 = stmt1.executeQuery();
            recordPresente1 = rset1.next();
            if (recordPresente1) {
                iddoc = rset1.getInt("iddoc");
                cstmt2.setInt(10, iddoc);

                //Scrivo il documento nella cartella del CE-ONLINE
                byte[] contenuto = elContratto.getFile().getContent().getContent();
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "contenuto=" + contenuto);
                fileCeOnline = "Doc_Area" + iddoc + "." + ext;
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "recordPresente=" + recordPresente);
                File destFolder = new File("/http/servizi/siss-bundle-01/ricercaclinica-toscana.cineca.it/html/uxmr/WCA/docs/" + fileCeOnline);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "destFolder=" + destFolder);
                FileOutputStream fos = new FileOutputStream(destFolder);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "fos=" + fos);
                fos.write(contenuto);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "write");
                fos.close();
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "close");
            }

            cstmt2.setString(12, filename);

            autore = elContratto.getFile().getAutore();
            if (autore != null) {
                cstmt2.setString(13, autore);
            } else {
                cstmt2.setNull(13, Types.VARCHAR);
            }

            idTipoRef = idStudio + 10000000;
            cstmt2.setLong(14, idTipoRef);

            cstmt2.setString(15, keywords);

            cstmt2.setInt(16, CurrCenterProgr);

            cstmt2.setString(17, UseridIns);

            cstmt2.execute();
        } else { //TOSCANA-190
            //Se è 4###Convenzione firmata o 7###Atto deliberativo allora controlla che lato ce sia stato rilasciato il parere

            String filename = elContratto.getFile().getFileName();
            int i = filename.lastIndexOf(".");
            String ext = "";
            if (i > 0) {
                ext = filename.substring(i + 1);
            }

            sql = " select r.id_stud,c.visitnum,c.visitnum_progr,c.esam,ce.progr,c.userid from " +
                    "  ce_info_studio i," +
                    "  ce_registrazione r," +
                    "  ce_coordinate c," +
                    "  ce_centrilocali ce" +
                    " where ce.id_stud=i.id_stud(+)" +
                    "  and r.id_stud=c.id_stud" +
                    "  and r.id_stud=ce.id_stud" +
                    "  and nvl(ce.stato,0)=5" +
                    "  and c.visitnum=10" +
                    "  and c.visitnum_progr=ce.progr-1" +
                    "  and c.esam=1" +
                    "  and nvl(c.fine,0)=0" +
                    "  and (r.ritirato is null or r.ritirato=0)" +
                    "  and r.id_stud=? and ce.centro=? and ce.crpms_center_progr=?";
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "eseguo sql: " + sql);
            PreparedStatement parere_ce_stmt = conn.prepareStatement(sql);
            parere_ce_stmt.setInt(1, idStudio);
            parere_ce_stmt.setInt(2, idCentro);
            parere_ce_stmt.setLong(3, elCentro.getId());
            ResultSet parere_ce_rset = parere_ce_stmt.executeQuery();
            boolean parere_cePresente1 = parere_ce_rset.next();
            if (parere_cePresente1) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "parere presente! preparo procedura");


                String sqlIdDocs = "select DOCS_ID.NEXTVAL as iddoc from DUAL";
                PreparedStatement stmt1 = conn.prepareStatement(sqlIdDocs);
                ResultSet rset1 = stmt1.executeQuery();
                recordPresente1 = rset1.next();
                int iddoc = -1;
                String fileCeOnline;
                if (recordPresente1) {
                    iddoc = rset1.getInt("iddoc");

                    //Scrivo il documento nella cartella del CE-ONLINE
                    byte[] contenuto = elContratto.getFile().getContent().getContent();
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "contenuto=" + contenuto);
                    fileCeOnline = "Doc_Area" + iddoc + "." + ext;
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "recordPresente=" + recordPresente1);
                    File destFolder = new File("/http/servizi/siss-bundle-01/ricercaclinica-toscana.cineca.it/html/uxmr/WCA/docs/" + fileCeOnline);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "destFolder=" + destFolder);
                    FileOutputStream fos = new FileOutputStream(destFolder);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "fos=" + fos);
                    fos.write(contenuto);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "write");
                    fos.close();
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "close");
                }


                int idTipoRef = idStudio + 10000000;


                CallableStatement parere_ce_cstmt = null;
                String procedure = "";

                it.cineca.siss.axmr3.log.Log.debug(getClass(), " userid " + parere_ce_rset.getString(6));
                if (tipologiaContratto == 4) {
                    procedure = "{call INSERT_DOC_STIPULA_CRPMS_TO_CE(?,?,?, ?,?,?, ?,?,?, ?,?,?, ?,?,?)}"; //TIPOLOGIA 4###Convenzione firmata
                    parere_ce_cstmt = conn.prepareCall(procedure);
                    parere_ce_cstmt.setLong(1, parere_ce_rset.getLong(1)); //id_stud
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), " id_stud " + parere_ce_rset.getLong(1));
                    parere_ce_cstmt.setLong(2, parere_ce_rset.getLong(2)); //visitnum
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), " visitnum " + parere_ce_rset.getLong(2));
                    parere_ce_cstmt.setLong(3, parere_ce_rset.getLong(3)); //visitnum_progr
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), " visitnum_progr " + parere_ce_rset.getLong(3));
                    parere_ce_cstmt.setLong(4, parere_ce_rset.getLong(4)); //esam
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), " esam " + parere_ce_rset.getLong(4));
                    parere_ce_cstmt.setLong(5, 1); //progr = 1 harcoded perchè è fisso (luigi dixit)
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), " progr 1");
                    parere_ce_cstmt.setString(6, UseridIns); //userid
                    if (dataContratto != null) {
                        parere_ce_cstmt.setDate(7, dataContrattoSql); //STIPULA_DT
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), " STIPULA_DT " + dataContrattoSql);
                        parere_ce_cstmt.setString(8, "OKOKOK"); //STIPULA_DTRC
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), " STIPULA_DTRC OKOKOK");
                    } else {
                        parere_ce_cstmt.setNull(7, Types.DATE); //STIPULA_DT
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), " STIPULA_DT NULL");
                        parere_ce_cstmt.setNull(8, Types.VARCHAR); //STIPULA_DTRC
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), " STIPULA_DTRC NULL");
                    }
                    parere_ce_cstmt.setInt(9, iddoc); //STIPULA_FILE
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "iddoc " + iddoc);
                    parere_ce_cstmt.setInt(10, idCentro); //CENTRO
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), " idCentro " + idCentro);
                    parere_ce_cstmt.setString(11, idCentroDec); //D_CENTRO
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), " idCentroDec " + idCentroDec);
                    parere_ce_cstmt.setString(12, ext); //ext
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), " ext " + ext);
                    parere_ce_cstmt.setString(13, filename); //filename
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), " filename " + filename);
                    if (autore != null) {
                        parere_ce_cstmt.setString(14, autore); //autore
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), " autore " + autore);
                    } else {
                        parere_ce_cstmt.setNull(14, Types.VARCHAR); //autore
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), " autore NULL");
                    }
                    parere_ce_cstmt.setLong(15, idTipoRef); //id_tipo_ref
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), " idTipoRef " + idTipoRef);
                }
                if (tipologiaContratto == 7) {
                    procedure = "{call INSERT_DOC_DELIB_CRPMS_TO_CE(?,?,?, ?,?,?, ?,?,?, ?,?,?, ?,?,?, ?,?,?)}"; //TIPOLOGIA 7###Atto deliberativo
                    parere_ce_cstmt = conn.prepareCall(procedure);
                    parere_ce_cstmt.setLong(1, parere_ce_rset.getLong(1)); //id_stud
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), " id_stud " + parere_ce_rset.getLong(1));
                    parere_ce_cstmt.setLong(2, parere_ce_rset.getLong(2)); //visitnum
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), " visitnum " + parere_ce_rset.getLong(2));
                    parere_ce_cstmt.setLong(3, parere_ce_rset.getLong(3)); //visitnum_progr
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), " visitnum_progr " + parere_ce_rset.getLong(3));
                    parere_ce_cstmt.setLong(4, parere_ce_rset.getLong(4)); //esam
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), " esam " + parere_ce_rset.getLong(4));
                    parere_ce_cstmt.setLong(5, 1); //progr = 1 harcoded perchè è fisso (luigi dixit)
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), " progr 1");
                    parere_ce_cstmt.setString(6, UseridIns); //userid
                    int tipologiaContrattoCE = Integer.valueOf(elContratto.getfieldData("tipologiaContratto", "tipoProvvedimento").get(0).toString().split("###")[0]);
                    String tipologiaContrattoCEDec = elContratto.getfieldData("tipologiaContratto", "tipoProvvedimento").get(0).toString().split("###")[1];
                    parere_ce_cstmt.setInt(7, tipologiaContrattoCE); //DELIB_TIPO
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), " tipologiaContratto " + tipologiaContrattoCE);
                    parere_ce_cstmt.setString(8, tipologiaContrattoCEDec); //D_DELIB_TIPO
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), " tipologiaContrattoDec " + tipologiaContrattoCEDec);
                    if (dataContratto != null) {
                        parere_ce_cstmt.setDate(9, dataContrattoSql); //DELIB_DT
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), " DELIB_DT " + dataContrattoSql);
                        parere_ce_cstmt.setString(10, "OKOKOK"); //DELIB_DTRC
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), " DELIB_DTRC OKOKOK");
                    } else {
                        parere_ce_cstmt.setNull(9, Types.DATE); //DELIB_DT
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), " DELIB_DT NULL");
                        parere_ce_cstmt.setNull(10, Types.VARCHAR); //DELIB_DTRC
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), " DELIB_DTRC NULL");
                    }

                    String numeroProtocollo = "";
                    if (elContratto.getfieldData("tipologiaContratto", "numeroProtocollo").size() > 0) {
                        numeroProtocollo = elContratto.getfieldData("tipologiaContratto", "numeroProtocollo").get(0).toString();
                        parere_ce_cstmt.setString(11, numeroProtocollo); //PROT_NUM
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), " numeroProtocollo " + numeroProtocollo);
                    } else {
                        parere_ce_cstmt.setNull(11, Types.VARCHAR); //PROT_NUM
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), " numeroProtocollo NULL");
                    }
                    parere_ce_cstmt.setInt(12, idCentro); //CENTRO
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), " idCentro " + idCentro);
                    parere_ce_cstmt.setString(13, idCentroDec); //D_CENTRO
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), " idCentroDec " + idCentroDec);
                    parere_ce_cstmt.setInt(14, iddoc); //DELIB_FILE
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "iddoc " + iddoc);
                    parere_ce_cstmt.setString(15, ext); //ext
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), " ext " + ext);
                    parere_ce_cstmt.setString(16, filename); //filename
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), " filename " + filename);
                    if (autore != null) {
                        parere_ce_cstmt.setString(17, autore); //autore
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), " autore " + autore);
                    } else {
                        parere_ce_cstmt.setNull(17, Types.VARCHAR); //autore
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), " autore NULL");
                    }
                    parere_ce_cstmt.setLong(18, idTipoRef); //id_tipo_ref
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), " idTipoRef " + idTipoRef);
                }

                it.cineca.siss.axmr3.log.Log.debug(getClass(), " Eseguo procedura " + procedure);
                parere_ce_cstmt.execute();
            }
        }
        conn.close();
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "FINE copiaContrattoInCeOnline");
    }

    public void copiaAllegatoCentroInCeOnline(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Connection conn = dataSource.getConnection();
        Element e = service.getElement(Long.parseLong(elementId));
        Element elCentro = e.getParent();
        Long idStudio = Long.valueOf(elCentro.getParent().getfieldData("UniqueIdStudio", "id").get(0).toString());
        Integer CurrCenterProgr = 0;
        String sqlprogr = "";
        boolean recordPresente;
        Integer p = null;
        String docCs = "";
        String docCsDen = "";
        String docCsAltro = "";
        String docvers = "";
        String docnote = "";
        String sqlIdDocs = "";
        //boolean recordPresente1;
        Integer iddoc;
        String ext = "";
        String autore = "";
        long idTipoRef;
        String keywords = "";
        String fileCeOnline = "";
        boolean recordPresente1;

        String UseridIns = "";
        Integer idCentro = Integer.valueOf(elCentro.getfieldData("IdCentro", "Struttura").get(0).toString().split("###")[0]);
        String DenCentro = elCentro.getfieldData("IdCentro", "Struttura").get(0).toString().split("###")[1];

        String sql = "select centro from ce_elenco_centriloc where id=?";
        PreparedStatement struttura_stmt = conn.prepareStatement(sql);
        struttura_stmt.setInt(1, idCentro);
        ResultSet struttura_rset = struttura_stmt.executeQuery();
        recordPresente1 = struttura_rset.next();
        Integer CE;
        if (recordPresente1) {
            CE = struttura_rset.getInt("centro");
            switch (CE) {
                case 1:
                    UseridIns = "LPOLVERELLI";//CEAV Sud Est
                    break;
                case 2:
                    UseridIns = "DCARIGNANI";//CEAV Nord Ovest
                    break;
                case 3:
                    UseridIns = "MVIETRI";//CEAV Centro
                    break;
                case 4:
                    UseridIns = "MLEO";// CEP
                    break;
            }

        }
        if (Integer.valueOf(elCentro.getParent().getfieldData("datiStudio", "popolazioneStudio").get(0).toString().split("###")[0]) == 1) {
            UseridIns = "MLEO";//se pediatrico sovrascrivo per assegnarlo CEP!!!!
        }

        sql = "select progr-1 as currcenterprogr from ce_centrilocali where crpms_center_progr=?";
        PreparedStatement currcenterprogr_stmt = conn.prepareStatement(sql);
        currcenterprogr_stmt.setLong(1, elCentro.getId());
        ResultSet currcenterprogr_rset = currcenterprogr_stmt.executeQuery();
        recordPresente1 = currcenterprogr_rset.next();
        if (recordPresente1) {
            CurrCenterProgr = currcenterprogr_rset.getInt("currcenterprogr");
        }
        Log.debug(getClass(), "Sono nel ciclo for dei documenti allegati");
        String filename = e.getFile().getFileName();
        Log.debug(getClass(), "nomefile= " + filename);

        Integer tipoDoc = Integer.valueOf(e.getFieldDataCode("DocCentroSpec", "TipoDocumento"));

        Log.debug(getClass(), "Ho trovato un documento da portare in CE-ONLINE");
        Log.debug(getClass(), "tipoDoc : " + tipoDoc);
            /*
            if(tipoDoc.equals(4)){docCs="4"; docCsDen="CV dello sperimentatore";}
            if(tipoDoc.equals(-9999)){docCs="23"; docCsDen="Altro"; docCsAltro=e.getFieldDataDecode("DocCentroSpec", "TipoDocumento");}
            */


        //GC 15/07/2016 Query per mappatura documenti in CE-ONLINE
        String sqlDocsCE = "select id,descrizione from CRMS_DOC_LOC,CE_DOC_LOC where id_doc_ce=id and code=" + tipoDoc;
        Log.debug(getClass(), "Query = " + sqlDocsCE);
        PreparedStatement stmtdocce = conn.prepareStatement(sqlDocsCE);
        ResultSet rsetDocsCe = stmtdocce.executeQuery();
        recordPresente1 = rsetDocsCe.next();
        if (recordPresente1) {
            docCs = rsetDocsCe.getString("id");
            Log.debug(getClass(), "docCs : " + docCs);
            docCsDen = rsetDocsCe.getString("descrizione");
            Log.debug(getClass(), "docCs : " + docCsDen);
            //HDCE-3084  compila sempre il campo DOC_LOC_ALTRO che andrebbe compilato solo in caso di tipo "Altro"
            if (docCs.equals("18")) {
                docCsAltro = e.getFieldDataDecode("DocCentroSpec", "TipoDocumento");
                Log.debug(getClass(), "docCsAltro : " + docCsAltro);
            }
        }


        CallableStatement cstmt2 = null;
        String procedure2 = "{call INSERT_DOC_CENTRO_CRPMS_TO_CE(?,?,?, ?,?,?, ?,?,?, ?,?,?, ?,?,?, ?,?)}";

        cstmt2 = conn.prepareCall(procedure2);

        cstmt2.setLong(1, idStudio);

        //recupero il prossimo progressivo del documento
        sqlprogr = "select nvl(max(progr),0)+1 as p from CE_COORDINATE where ID_STUD=" + idStudio + " and visitnum=1 and visitnum_progr=" + CurrCenterProgr + " and esam=23";
        Log.debug(getClass(), "sqlprogr=" + sqlprogr);
        PreparedStatement stmt = conn.prepareStatement(sqlprogr);
        ResultSet rset = stmt.executeQuery();

        recordPresente = rset.next();
        Log.debug(getClass(), "recordPresente=" + recordPresente);
        if (recordPresente) {
            keywords = "DOC_CENTROSPEC";
            p = rset.getInt("p");
            Log.debug(getClass(), "p=" + p);
            cstmt2.setLong(2, p);

            if (CurrCenterProgr == 0) {
                if (p > 1) {
                    keywords += "_" + p;
                }
            } else {
                keywords += "_" + p + "_" + CurrCenterProgr;
            }

            Log.debug(getClass(), "keywords=" + keywords);
        }

        cstmt2.setString(3, docCs);
        cstmt2.setString(4, docCsDen);
        cstmt2.setString(5, docCsAltro);

        Calendar dataDoc = e.getFile().getDate();
        //java.sql.Date sqlDate =  new java.sql.Date(dataDoc.getTime().getTime() );

        if (dataDoc != null) {
            Date sqlDate = new Date(dataDoc.getTime().getTime());
            cstmt2.setDate(6, sqlDate);
            cstmt2.setString(7, "OKOKOK");
        } else {
            cstmt2.setNull(6, Types.DATE);
            cstmt2.setNull(7, Types.VARCHAR);
        }

        docvers = e.getFile().getVersion();
        if (docvers != null) {
            cstmt2.setString(8, docvers);
        } else {
            cstmt2.setNull(8, Types.VARCHAR);
        }

        docnote = e.getFile().getNote();
        if (docnote != null) {
            cstmt2.setString(9, docnote);
        } else {
            cstmt2.setNull(9, Types.VARCHAR);
        }

        int i = filename.lastIndexOf(".");
        if (i > 0) {
            ext = filename.substring(i + 1);
        }

        cstmt2.setString(11, ext);

        sqlIdDocs = "select DOCS_ID.NEXTVAL as iddoc from DUAL";
        PreparedStatement stmt1 = conn.prepareStatement(sqlIdDocs);
        ResultSet rset1 = stmt1.executeQuery();
        recordPresente1 = rset1.next();
        if (recordPresente1) {
            iddoc = rset1.getInt("iddoc");
            cstmt2.setInt(10, iddoc);

            //Scrivo il documento nella cartella del CE-ONLINE
            byte[] contenuto = e.getFile().getContent().getContent();
            Log.debug(getClass(), "contenuto=" + contenuto);
            fileCeOnline = "Doc_Area" + iddoc + "." + ext;
            Log.debug(getClass(), "recordPresente=" + recordPresente);
            File destFolder = new File("/http/servizi/siss-bundle-01/ricercaclinica-toscana.cineca.it/html/uxmr/WCA/docs/" + fileCeOnline);
            Log.debug(getClass(), "destFolder=" + destFolder);
            FileOutputStream fos = new FileOutputStream(destFolder);
            Log.debug(getClass(), "fos=" + fos);
            fos.write(contenuto);
            Log.debug(getClass(), "write");
            fos.close();
            Log.debug(getClass(), "close");
        }

        cstmt2.setString(12, filename);

        autore = e.getFile().getAutore();
        if (autore != null) {
            cstmt2.setString(13, autore);
        } else {
            cstmt2.setNull(13, Types.VARCHAR);
        }

        idTipoRef = idStudio + 10000000;
        cstmt2.setLong(14, idTipoRef);

        cstmt2.setString(15, keywords);

        cstmt2.setInt(16, CurrCenterProgr);

        cstmt2.setString(17, UseridIns);

        cstmt2.execute();


        String processKey = "inviaMail";
        HashMap<String, String> mailData = new HashMap<String, String>();
        String mailTo = "";
        String sqlMailTO = "select email from ana_utenti_2 where profilo='SGR' and id_ce=(select centro from ce_elenco_centriloc where id=?)";
        it.cineca.siss.axmr3.log.Log.debug(getClass(), sqlMailTO);
        PreparedStatement stmtMailTo = conn.prepareStatement(sqlMailTO);

        stmtMailTo.setInt(1, idCentro);
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
        if (mailTo.equals("")) mailTo = getEmail("ALIAS_CTC");
        String mailSubject = "TOSCANA - CRMS - Invio nuovo documento da CTO/TFA a Segreteria CE ";
        String mailInfoCentro = "";
        //Long idStudio;
        String sponsor = "";
        String croString = "";
        String codice = "";
        String titolo = "";
        String DenUnitaOperativa = "";
        String DenPrincInv = "";

        //idStudio = elStudio.getfieldData("UniqueIdStudio", "id").get(0).toString();
        Element elStudio = elCentro.getParent();
        if (elStudio.getFieldDataElement("datiPromotore", "promotore") != null && elStudio.getFieldDataElement("datiPromotore", "promotore").size() > 0) {
            Element sp = elStudio.getFieldDataElement("datiPromotore", "promotore").get(0);
            sponsor = sp.getfieldData("DatiPromotoreCRO", "denominazione").get(0).toString();
        }
        if (elStudio.getFieldDataElement("datiCRO", "denominazione") != null && elStudio.getFieldDataElement("datiCRO", "denominazione").size() > 0) {
            Element cro = elStudio.getFieldDataElement("datiCRO", "denominazione").get(0);
            croString = cro.getfieldData("DatiPromotoreCRO", "denominazione").get(0).toString();
        }
        if (elStudio.getfieldData("IDstudio", "CodiceProt") != null && elStudio.getfieldData("IDstudio", "CodiceProt").size() > 0) {
            codice = elStudio.getfieldData("IDstudio", "CodiceProt").get(0).toString();
        }
        if (elStudio.getfieldData("IDstudio", "TitoloProt") != null && elStudio.getfieldData("IDstudio", "TitoloProt").size() > 0) {
            titolo = elStudio.getfieldData("IDstudio", "TitoloProt").get(0).toString();
        }
        DenCentro = elCentro.getfieldData("IdCentro", "Struttura").get(0).toString().split("###")[1];
        DenUnitaOperativa = elCentro.getfieldData("IdCentro", "UO").get(0).toString().split("###")[1];
        DenPrincInv = elCentro.getfieldData("IdCentro", "PINomeCognome").get(0).toString().split("###")[1];

        mailInfoCentro =
                "ID studio: " + idStudio +
                        "\nCodice: " + codice +
                        "\nTitolo: " + titolo +
                        "\nSponsor: " + sponsor +
                        "\nCRO: " + croString +
                        "\nStruttura: " + DenCentro +
                        "\nUnita' operativa: " + DenUnitaOperativa +
                        "\nPrincipal Investigator: " + DenPrincInv;

        String url = getBaseUrl() + "/../uxmr/index.php?ID_STUD=" + idStudio + "&VISITNUM=1&exams=visite_exams.xml";
        String mailBody = "Gentile utente,\n" +
                "si comunica che e' stato appena inviato un nuovo documento per il seguente centro da CTO/TFA a Segreteria CE:\n\n" +
                mailInfoCentro + "\n\n" +
                "E' possibile visualizzare il centro al seguente link:\n\n" +
                url + "\n\n" +
                "Cordiali saluti\n\n\n\n" +
                "Il presente messaggio è stato inviato automaticamente dal sistema, si prega di non rispondere.\n" +
                "Per contattare il servizio di help desk inviare una mail a help_crpms@cineca.it";

        mailData.put("to", mailTo);
        mailData.put("subject", mailSubject);
        mailData.put("body", mailBody);
        mailData.put("cc", getEmail("ALIAS_CTC"));
        mailData.put("ccn", getEmail("ALIAS_CTC"));
        service.startProcess(elCentro.getCreateUser(), elCentro, processKey, mailData);
        conn.close();
    }

    public String compareFieldValue(String field, String value1, String value2) {

        return compareFieldValue(field, value1, value2, null, null);
    }

    public String compareFieldValue(String field, String value1, String value2, String decode1, String decode2) {

        String txt = "";

        it.cineca.siss.axmr3.log.Log.debug(getClass(), field + " valore vecchio = " + value1 + " valore nuovo = " + value2);

        if (value1.equals(value2)) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Campi uguali");
        } else {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Campi diversi");
            if (decode1 == null && decode2 == null) {
                txt = field + "\n" + " valore vecchio = " + value1 + "\n" + " valore nuovo = " + value2 + "\n\n";
            } else {
                txt = field + "\n" + " valore vecchio = " + decode1 + "\n" + " valore nuovo = " + decode2 + "\n\n";
            }
        }

        return txt;
    }

    public boolean checkPassed(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Sono in checkPassed - elementId=" + elementId);

        boolean passed = false;
        if (el.getfieldData("statoValidazioneCentro", "fattLocale") != null && el.getfieldData("statoValidazioneCentro", "fattLocale").size() > 0) {
            if (el.getfieldData("statoValidazioneCentro", "fattLocale").get(0).toString().startsWith("1###")) {
                passed = true;
            }
        }
        commonBean.closeDocumentService(service);
        return passed;

    }

    /**
     * TOSCANA-189
     * inserire un controllo all'invio dati al CE e alla chiusura feasibility sulla scheda di Farmaci/DM/comodato d'uso. Se lo studio è
     * interventistico con farmaco o osservazionale con farmaco almeno una scheda farmaco deve essere inserita; se lo studio è interventistico
     * con dispositivo o osservazionale con dispositivo almeno una scheda dispositivo deve essere inserita
     */
    public boolean checkFarmacoDispPresente(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element centro = service.getElement(Long.parseLong(elementId));
        Element studio = centro.getParent();
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Sono in checkPassed - elementId=" + elementId);
        boolean passed = false;
        int tipoStudio = Integer.valueOf(studio.getfieldData("datiStudio", "tipoStudio").get(0).toString().split("###")[0]);
        if (tipoStudio == 1 || tipoStudio == 5 || tipoStudio == 3 || tipoStudio == 7) {//Interventistico con farmaco o Osservazionale con farmaco o Interventistico con dispositivo medico o Osservazionale con dispositivo medico
            List<Element> elFarmaco = studio.getChildrenByType("Farmaco");
            if (elFarmaco.size() > 0) {
                for (Element farm : elFarmaco) {
                    if ((tipoStudio == 1 || tipoStudio == 5) && !passed && farm.getfieldData("Farmaco", "tipo").get(0).toString().startsWith("1###")) {//Interventistico con farmaco o Osservazionale con farmaco
                        passed = true;
                    } else if ((tipoStudio == 3 || tipoStudio == 7) && !passed && farm.getfieldData("Farmaco", "tipo").get(0).toString().startsWith("2###")) {//Interventistico con dispositivo medico o Osservazionale con dispositivo medico
                        passed = true;
                    }
                }

            }
        } else {
            passed = true;//caso studi senza farmaco e dispositivo vai avantri
        }
        commonBean.closeDocumentService(service);
        return passed;

    }

    public void checkAllTemplate(String elementId, DelegateTask task) throws Exception {

        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        String parentId = (el.getParent().getId().toString());
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "elementId=" + elementId);

        commonBean.checkTemplateCompleted(elementId, "IdCentro", task, service);
        commonBean.checkTemplateCompleted(elementId, "DatiCentro", task, service);
        commonBean.checkTemplateCompleted(elementId, "Feasibility", task, service);

        /*
        SIRER-17
         +++ho disabilitato il controllo sulla completezza del template datiStudio perchè il metodo controlla che tutti
         i campi obbligatori siano compilati, ma non gestisce (cosa che abbiamo fatto lato interfaccia grafica) quelli
         condizionati e nascosti, DA IMPLEMENTARE IN SEGUITO TRADUCENDO javascript di condizionamento in java+++

        commonBean.checkTemplateCompleted(parentId, "datiStudio", task, service);
         */
        commonBean.checkTemplateCompleted(parentId, "datiPromotore", task, service);

        commonBean.closeDocumentService(service);
    }

    /**
     * SIRER-41 controllo template obbligatori su studio e centro.
     * <b>Basta controllarne uno non condizionato per accertarmi che tutto il template sia stato correttamente salvato</b>
     *
     * @param elementId
     * @param task
     */
    public void checkTemplateFeasibilityPI(String elementId, DelegateTask task) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "INIZIO checkTemplateFeasibilityPI centro id: " + elementId);
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        Element elStudio = el.getParent();
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "elementId=" + elementId);
        boolean passed = true;
        String message = "Attenzione! Validazione fallita.";
        //CONTROLLO TEMPLATE STUDIO
        if (passed) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "\t\tControllo datiStudio_tipoStudio");
            if (elStudio.getFieldDataCode("datiStudio", "tipoStudio").equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "\t==> Dato Non presente, ESCO!");
                passed = false;
                message += " Compilare i campi obbligatori della scheda Dati generali studio";
            }
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "\t\t\t TIPO STUDIO: " + elStudio.getFieldDataCode("datiStudio", "tipoStudio"));
        }
        if (passed) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "\t\tControllo datiCoordinatore_Disponibile");
            if (elStudio.getFieldDataCode("datiCoordinatore", "Disponibile").equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "\t==> Dato Non presente, ESCO!");
                passed = false;
                message += " Compilare i campi obbligatori della scheda Centro Coordinatore";
            }
        }
        if (passed) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "\t\tControllo esistenza di almeno un promotore");
            if (elStudio.getChildrenByType("PromotoreStudio").size() == 0) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "\t==> Dato Non presente, ESCO!");
                passed = false;
                message += " Inserire almeno un promotore";
            }
        }
        if (passed) {
            if ( elStudio.getFieldDataCode("datiStudio", "tipoStudio").equals("1") ) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "\t\tControllo esistenza di almeno un FARMACO");
                if (elStudio.getChildrenByType("Farmaco").size() == 0) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "\t==> Dato Non presente, ESCO!");
                    passed = false;

                } else {
                    passed = false;
                    for (Element farmaco : elStudio.getChildrenByType("Farmaco")) {
                        if ( !passed && (farmaco.getFieldDataCode("Farmaco", "tipo").equals("1") || farmaco.getFieldDataCode("Farmaco", "tipo").equals("2") || farmaco.getFieldDataCode("Farmaco", "tipo").equals("5")) ) {
                            it.cineca.siss.axmr3.log.Log.debug(getClass(), "\t==> TROVATO FARMACO, RIMANGO!");
                            passed = true;
                        }
                    }
                }
                if (!passed) {
                    message += " Inserire almeno un farmaco, dispositivo medico o altro materiale sperimentale";
                }
            } else if (elStudio.getFieldDataCode("datiStudio", "tipoStudio").equals("2") || elStudio.getFieldDataCode("datiStudio", "tipoStudio").equals("3")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "\t\tControllo esistenza di almeno un DISPOSITIVO");
                if (elStudio.getChildrenByType("Farmaco").size() == 0) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "\t==> Dato Non presente, ESCO!");
                    passed = false;

                } else {
                    passed = false;
                    for (Element farmaco : elStudio.getChildrenByType("Farmaco")) {
                        if (!passed && farmaco.getFieldDataCode("Farmaco", "tipo").equals("2")) {
                            it.cineca.siss.axmr3.log.Log.debug(getClass(), "\t==> TROVATO DISPOSITIVO, RIMANGO!");
                            passed = true;
                        }
                    }

                }
                if (!passed) {
                    message += " Inserire almeno un Dispositivo";
                }
            }
        }
        //CONTROLLO TEMPLATE CENTRO
        if (passed) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "\t\tControllo IdCentro_Struttura");
            if (el.getFieldDataCode("IdCentro", "Struttura").equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "\t==> Dato Non presente, ESCO!");
                passed = false;
                message += " Compilare i campi obbligatori della scheda Informazioni Centro";
            }
        }
        if (passed) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "\t\tControllo DatiCentro_InizioDt");
            if (el.getFieldDataDate("DatiCentro", "InizioDt") == null) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "\t==> Dato Non presente, ESCO!");
                passed = false;
                message += " Compilare i campi obbligatori della scheda Date Centro";
            }
        }
        if (passed) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "\n\t\tControllo Feasibility_ValLocale");
            if (el.getFieldDataCode("Feasibility", "ValLocale").equals("")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "\t==> Dato Non presente, ESCO!");
                passed = false;
                message += " Compilare i campi obbligatori della scheda Fattibilità PI";
            }
        }
        if (passed) {
            for (Element farmacoDepot : el.getChildrenByType("DepotFarmaco")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "\n\t\tControllo depotFarmaco_modalitaFornitura per depot " + el.getTitleString());
                if (passed && farmacoDepot.getFieldDataCode("depotFarmaco", "modalitaFornitura").equals("")) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "\t==> Dato Non presente, ESCO!");
                    passed = false;
                    message += " Compilare i campi obbligatori per ciascuna scheda Farmaci/Dispositivi/Altro";
                }
            }
        }
        commonBean.closeDocumentService(service);
        task.setVariable("passed", passed);
        task.setVariable("message", message);
    }

    /**
     * SIRER-41 controllo template obbligatori su studio e centro.
     * <b>Basta controllarne uno non condizionato per accertarmi che tutto il template sia stato correttamente salvato</b>
     * @param elementId
     * @param task
     * @throws Exception
     */
    public void checkTemplateParerePI(String elementId, DelegateTask task) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "INIZIO checkTemplateParerePI centro id: " + elementId);
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        Element elStudio = el.getParent();
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "elementId=" + elementId);
        boolean passed = true;
        //String message="Attenzione! Validazione fallita.";
        String message = "Validazione OK!";
        commonBean.closeDocumentService(service);
        task.setVariable("passed", passed);
        task.setVariable("message", message);
    }

    public boolean checkIntegrazione(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element centro = service.getElement(Long.parseLong(elementId));

        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Sono in checkPassed - elementId=" + elementId);
        boolean passed = false;
        List<Element> istruttoriaCE = centro.getChildrenByType("IstruttoriaCE");

        if (istruttoriaCE.size() > 0 && centro.getFieldDataCode("statoValidazioneCentro", "idIstruttoriaCEPositiva").equals("")) {

            for (Element istruttoria : istruttoriaCE) {
                String inviata = istruttoria.getFieldDataString("IstruttoriaCE", "istruttoriaWFinviata");
                if (inviata.equals("1")) passed = true;
                else {
                    passed = false;
                    break;
                }
            }

        } else {
            passed = false;
        }

        commonBean.closeDocumentService(service);
        return passed;

    }

    public void closeAllTemplates(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        String parentId = (el.getParent().getId().toString());
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "closeAllTemplates elementId=" + elementId);
        Collection<Element> oggettiFeasibility = el.getChildren();


        //DISABILITO I TEMPLATE AI GRUPPI
        String[] gruppiUtenti = {"CTC", "SP", "PI","COORD", "SEGRETERIA", "FARMACIA","DIR"};
        for (String gr : gruppiUtenti) {
            commonBean.changeTemplatePermissionToGroup(parentId, "datiStudio", "V", gr);
            commonBean.changeTemplatePermissionToGroup(parentId, "datiCoordinatore", "V", gr);

            commonBean.changeTemplatePermissionToGroup(elementId, "IdCentro", "V", gr);
            commonBean.changeTemplatePermissionToGroup(elementId, "DatiCentro", "V", gr);
            commonBean.changeTemplatePermissionToGroup(elementId, "AnalisiCentro", "V", gr);
            commonBean.changeTemplatePermissionToGroup(elementId, "Feasibility", "V", gr);
            commonBean.changeTemplatePermissionToGroup(elementId, "ServiziCoinvolti", "V", gr);
            //DISABILITO I PERMESSI AL DEPOTFARMACO
            for (Element farmacoDepot : el.getChildrenByType("DepotFarmaco")) {
                commonBean.changePermissionToGroup(farmacoDepot.getId() + "", "V,B", null, gr);
            }
            //DISABILITO I PERMESSI AGLI ALLEGATI CENTRO
            for (Element child : el.getChildrenByType("AllegatoCentro")) {
                if(!gr.equals("SEGRETERIA")) { //non tolgo permesi alla alla segreteria per permettere la protocollazione verso babel
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "###################### Sistemo figlio ID =" + child.getId());
                    commonBean.changePermissionToGroup(child.getId() + "", "V,B", null, gr);
                }
            }
            //DISABILITO I PERMESSI AI FIGLI TEAMDISTUDIO
            for (Element child : el.getChildrenByType("TeamDiStudio")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "###################### Sistemo figlio ID =" + child.getId());
                commonBean.changePermissionToGroup(child.getId() + "", "V,B", null, gr);
            }
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "cambio permessi al gruppo" + gr);
        }

        //Chiudo la modifica all'utenza segreteria/CTC e all'utente che ha creato lo studio
        commonBean.changePermissionToGroup(parentId, "V,A,P,B", null, "SEGRETERIA");
        commonBean.changePermissionToGroup(parentId, "V,A,P,B", null, "CTC");
        commonBean.changePermissionToGroup(parentId, "V,A,P,B", null, "PI");
        commonBean.changePermissionToGroup(parentId, "V,A,P,B", null, "COORD");
        commonBean.changePermissionToGroup(parentId, "V,A,P,B", null, "SP");
        //DISABILITO I PERMESSI SULLO STUDIO
        commonBean.changePermissionToUser(parentId, "V,A,P,B", null, el.getParent().getCreateUser());

        //DISABILITO I PERMESSI SUI FIGLI DELLO STUDIO
        String[] figliStudio = {"PromotoreStudio", "FinanziatoreStudio", "CROStudio", "Farmaco", "allegato", "ProdottoStudio", "Emendamento"};
        Element studioEl = service.getElement(Long.parseLong(parentId));
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "###################### CHIUDI FIGLI STUDIO studioId=" + parentId);
        for (String childType : figliStudio) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "###################### ELABORO FILGIO " + childType);
            for (Element child : studioEl.getChildrenByType(childType)) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "###################### Sistemo figlio ID =" + child.getId());
                commonBean.changePermissionToGroup(child.getId() + "", "V,P,B", null, "SEGRETERIA");
                commonBean.changePermissionToGroup(child.getId() + "", "V,P,B", null, "PI");
                commonBean.changePermissionToGroup(child.getId() + "", "V,P,B", null, "COORD");
                commonBean.changePermissionToGroup(child.getId() + "", "V,P,B", null, "CTC");
                commonBean.changePermissionToGroup(child.getId() + "", "V,P,B", null, "SP");
                commonBean.changePermissionToUser(child.getId() + "", "V,P,B", null, child.getCreateUser());
            }
        }

        commonBean.closeDocumentService(service);
    }

    public void closeFeasibilityServizi(String elementId, DelegateExecution execution) throws Exception {

        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        String parentId = (el.getParent().getId().toString());
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "closeFeasibilityServizi elementId=" + elementId);
        Collection<Element> oggettiFeasibility = el.getChildren();

        String[] gruppiUtenti = {"CTC", "PI","COORD", "UOSC", "SR", "REGIONE","DIR"};

        for (String gr : gruppiUtenti) {
            commonBean.changeTemplatePermissionToGroup(elementId, "ServiziCoinvolti", "V", gr);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "cambio permessi al gruppo" + gr);
        }

        //Permessi di sola consultazione ai template associati agli oggetti di feasibility dei servizi
        for (Element of : oggettiFeasibility) {
            if (of.getTypeName().startsWith("Feasibility")) {
                String idOf = of.getId().toString();
                for (String gr : gruppiUtenti) {
                    commonBean.changeTemplatePermissionToGroup(idOf, "FeasibilityServizi", "V", gr);
                    commonBean.changeTemplatePermissionToGroup(idOf, "FeasibilityFarm", "V", gr);
                    commonBean.changeTemplatePermissionToGroup(idOf, "FeasibilityInfermiere", "V", gr);
                }
            }
        }

        //Rimuovo il processo "Invia ai Servizi" (se ancora presente) all'invio del supersì
        RuntimeService runtime = execution.getEngineServices().getRuntimeService();
        Collection<ProcessInstance> instances = service.getActiveProcesses(el);//el.getProcessInstances();

        TaskService taskService = execution.getEngineServices().getTaskService();
        for (ProcessInstance myInstance : instances) {
            //ProcessInstance myInstance = runtime.createProcessInstanceQuery().processInstanceId(instance.getProcessInstanceId()).singleResult();
            if (myInstance != null) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "1. DefinitionID = " + myInstance.getProcessDefinitionId());
                if (myInstance.getProcessDefinitionId().matches("^FeasibilityServizi.*$")) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "rimuovo il process = " + myInstance.getProcessDefinitionId());
                    runtime.deleteProcessInstance(myInstance.getId(), "Rimuovo processo Invia ai servizi perchè c'è il supersì");
                } else {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "2. DefinitionID: " + myInstance.getProcessDefinitionId());
                }
            } else {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "non rimuovo il process");
            }

        }

        commonBean.closeDocumentService(service);
    }

    public boolean fattibilitaPI(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        boolean ret = false;
        if (el.getfieldData("Feasibility", "ValLocale").get(0).toString().startsWith("1###")) {
            ret = true;
        }
        commonBean.closeDocumentService(service);
        return ret;
    }

    public boolean fattibilitaCTC(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        boolean ret = false;
        if (el.getfieldData("ValiditaCTC", "val").get(0).toString().startsWith("1###")) {
            ret = true;
        }
        commonBean.closeDocumentService(service);
        return ret;
    }

    public void abilitaPI(String elementId, DelegateExecution execution) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        abilitaPI(elementId, execution, service);
        commonBean.closeDocumentService(service);

    }

    public void abilitaPI(Element el, DelegateExecution execution, DocumentService service) throws Exception {
        String id_PI = el.getfieldData("IdCentro", "PINomeCognome").get(0).toString();
        abilitaPI(el, id_PI, execution, service);
    }

    public void abilitaPI(String elementId, DelegateExecution execution, DocumentService service) throws Exception {
        Element el = service.getElement(Long.parseLong(elementId));

        String id_PI = el.getfieldData("IdCentro", "PINomeCognome").get(0).toString();

        abilitaPI(elementId, id_PI, execution, service);
    }

    public void abilitaPI(String elementId, String id_PI, DelegateExecution execution, DocumentService service) throws Exception {
        Element el = service.getElement(Long.parseLong(elementId));
        abilitaPI(el, id_PI, execution, service);

    }

    public void abilitaPI(Element el, String id_PI, DelegateExecution execution, DocumentService service) throws Exception {
        TaskService taskService = execution.getEngineServices().getTaskService();
        List<Task> tasks = null;
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "In abilita PI 1 id " + id_PI);
        if (!id_PI.contains("###")) {
            id_PI += "###PI";
        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "In abilita PI 2 id " + id_PI);
        String userid_pi = abilitaPI(el, id_PI, service);
        tasks = taskService.createTaskQuery()

                .processVariableValueEquals("elementId", el.getId().toString())

                .list();
        for (Task task : tasks) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "task id " + task.getId());
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "task execution id " + task.getExecutionId());
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "task name " + task.getName());

            if (task.getName().equals("Chiudi feasibility locale e invia al CTC") || task.getName().equals("Invia ai servizi")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "entro task name " + task.getName());
                taskService.addCandidateUser(task.getId(), userid_pi);
            }
        }
        execution.setVariable("enabledPI", userid_pi);

    }

    public String abilitaPI(Element el, String id_PI, DocumentService service) throws Exception {

        String[] idValue = id_PI.split("###");

        id_PI = idValue[0];
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "In abilita PI 3 id " + id_PI);
        Connection conn = dataSource.getConnection();
        //Element el=service.getElement(Long.parseLong(elementId));
        //Long idStudio= (Long) el.getParent().getfieldData("UniqueIdStudio", "id").get(0);
        String sql1 = "select userid from ANA_UTENTI_1 where USERID='" + id_PI+"'";
        it.cineca.siss.axmr3.log.Log.debug(getClass(), sql1);
        PreparedStatement stmt = conn.prepareStatement(sql1);
        ResultSet rset = stmt.executeQuery();

        String userid_pi = "CTC";

        if (rset.next()) userid_pi = rset.getString("userid");
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "In abilita PI 4 userid " + userid_pi);
        //diritti V 	C 	M 	AC 	MC 	E 	MP 	A 	R 	P 	ET 	B

        abilitaPI(el, id_PI, userid_pi, service);


        conn.close();
        return userid_pi;
    }

    public String getUseridPI(String elementId) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "getUseridPI -> elementId=" + elementId);
        DocumentService service = commonBean.getDocumentService();

        String idCentro = getElementIdCentro(elementId, service);
        Element elCentro = service.getElement(idCentro);
        String id_PI = elCentro.getFieldDataCode("IdCentro", "PINomeCognome");

        //String[] idValue=id_PI.split("###");
        //id_PI=idValue[0];

        it.cineca.siss.axmr3.log.Log.debug(getClass(), "In abilita PI 3 id " + id_PI);
        Connection conn = dataSource.getConnection();
        //Element el=service.getElement(Long.parseLong(elementId));
        //Long idStudio= (Long) el.getParent().getfieldData("UniqueIdStudio", "id").get(0);
        String sql1 = "select userid from ANA_UTENTI_1 where USERID='" + id_PI+"'";
        it.cineca.siss.axmr3.log.Log.debug(getClass(), sql1);
        PreparedStatement stmt = conn.prepareStatement(sql1);
        ResultSet rset = stmt.executeQuery();

        String userid_pi = "CTC";

        if (rset.next()) userid_pi = rset.getString("userid");
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "In abilita PI 4 userid " + userid_pi);

        conn.close();
        commonBean.closeDocumentService(service);

        return userid_pi;
    }

    public void abilitaPI(Element el, String id_PI, String userid_pi, DocumentService service) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "In abilita PI 5 userid " + userid_pi);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "In abilita PI 6 id " + id_PI);
        if (!userid_pi.equals("") && !userid_pi.equals("*")) {
            commonBean.changePermissionToUser(el.getId().toString(), "V,M,AC,MP,A,P,B", "", userid_pi, service);

        }
    }

    public void abilitaPICentroEStudio(String elementId) throws ProcessException {
        DocumentService service = commonBean.getDocumentService();

        commonBean.changePermissionToGroup(elementId, "V,C,M,A,B", "", "PI");
        commonBean.changePermissionToGroup(elementId, "V,C,M,A,B", "", "COORD");

        commonBean.changePermissionToGroup(service.getElement(elementId).getParent().getId().toString(), "V,C,M,A,B", "", "PI");
        commonBean.changePermissionToGroup(service.getElement(elementId).getParent().getId().toString(), "V,C,M,A,B", "", "COORD");
        Collection<Element> children = service.getElement(elementId).getChildren();
        for (Element child : children) {
            if(child.getTypeName().equals("AllegatoCentro")) {
                commonBean.changePermissionToGroup(child.getId().toString(), "V,C,M,A,B", "", "PI");
                commonBean.changePermissionToGroup(child.getId().toString(), "V,C,M,A,B", "", "COORD");
            }
        }

        commonBean.closeDocumentService(service);
    }

    public void disabilitaSPCentroEStudio(String elementId) throws ProcessException {
        DocumentService service = commonBean.getDocumentService();

        //commonBean.changePermissionToGroup(elementId,"V,B","","SP");
        //commonBean.changePermissionToUser(elementId,"V,B","",service.getElement(elementId).getCreateUser());

        commonBean.changePermissionToGroup(service.getElement(elementId).getParent().getId().toString(), "V,A,B", "", "SP");
        commonBean.changePermissionToUser(service.getElement(elementId).getParent().getId().toString(), "V,A,B", "", service.getElement(elementId).getParent().getCreateUser());


        Collection<Element> children = service.getElement(elementId).getParent().getChildren();
        for (Element child : children) {
            if(!child.getTypeName().equals("Centro") || (child.getTypeName().equals("Centro") && child.getId()==Long.parseLong(elementId) )) {
                commonBean.changePermissionToGroup(child.getId().toString(), "V,B", "", "SP");
                commonBean.changePermissionToUser(child.getId().toString(), "V,B", "", service.getElement(elementId).getParent().getCreateUser());
            }
        }


        commonBean.closeDocumentService(service);

    }

    public void abilitaSEGRETERIACentroEStudio(String elementId) throws ProcessException {
        DocumentService service = commonBean.getDocumentService();
        commonBean.changePermissionToGroup(elementId, "V,C,M,A,B", "", "SEGRETERIA");

        commonBean.changePermissionToGroup(service.getElement(elementId).getParent().getId().toString(), "V,C,M,A,B", "", "SEGRETERIA");
        commonBean.closeDocumentService(service);
    }

    public void abilitaCTCCentroEStudio(String elementId) throws ProcessException {
        DocumentService service = commonBean.getDocumentService();
        commonBean.changePermissionToGroup(elementId, "V,C,M,MC,MP,A,R,P,ET,B", "", "CTC");
        commonBean.changePermissionToGroup(service.getElement(elementId).getParent().getId().toString(), "V,C,M,A,B", "", "CTC");
        commonBean.closeDocumentService(service);
    }

    public void newPI(String piUserid, String piId, DelegateExecution execution) throws Exception {
        DocumentService service = commonBean.getDocumentService();

        Connection conn = null;
        String sql = "";
        String output = "";
        List<Element> centri = new LinkedList<Element>();
        HashMap<String, Object> data = new HashMap<String, Object>();
        piUserid = piUserid.toUpperCase();
        if (piUserid.equals("*") && piId.equals("*")) {
            centri = service.getElementsByType("Centro");
            for (Element centro : centri) {
                if (centro.getfieldData("IdCentro", "PINomeCognome") != null && !centro.getfieldData("IdCentro", "PINomeCognome").isEmpty()) {
                    piId = centro.getfieldData("IdCentro", "PINomeCognome").get(0).toString();
                    output += centro.getId().toString() + ",";
                    abilitaPI(centro, piId, execution, service);

                }
            }
        } else {
            conn = dataSource.getConnection();
            if (piId.equals("*")) {
                sql = "select USERID from ANA_UTENTI_1 where USERID=?";
                PreparedStatement stmt = conn.prepareStatement(sql);
                stmt.setString(1, piUserid);
                ResultSet rset = stmt.executeQuery();
                if (rset.next()) {
                    piId = String.valueOf(rset.getInt("progr_pinc_inv"));
                }
            } else if (piUserid.equals("*")) {
                /*sql="select USERID from ANA_UTENTI_1 where USERID=?";
                PreparedStatement stmt = conn.prepareStatement(sql);
                stmt.setInt(1,Integer.parseInt(piId));
                ResultSet rset = stmt.executeQuery();
                if(rset.next()) {
                    piUserid=rset.getString("userid");
                }*/
            } else {
                sql = "update ana_utenti_1 set USERID=?  where userid=?";
                PreparedStatement stmt = conn.prepareStatement(sql);
                stmt.setInt(1, Integer.parseInt(piId));
                stmt.setString(2, piUserid);
                stmt.executeQuery();
                conn.commit();

            }
            conn.close();
            output = "userid: " + piUserid + "\nid: " + piId + "\nLista centri:\n";
            data.put("IdCentro_PI_eq", piId);
            centri = service.advancedSearch("Centro", data);

            for (Element centro : centri) {
                output += centro.getId().toString() + ",";
                abilitaPI(centro, piId, execution, service);


            }
        }

        execution.setVariable("descriptionNext", output);
        commonBean.closeDocumentService(service);
    }

    public void changePI(String elementId, String id_PI, DelegateExecution execution) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        Collection<String> users = el.getUsers();
        for (String user : users) {
            if (!user.equals(el.getCreateUser())) {
                commonBean.changePermissionToUser(elementId, "", "", user, service);
            }
        }
        abilitaPI(elementId, id_PI, execution, service);
        commonBean.closeDocumentService(service);

    }

    public String mailPI(String elementId, DocumentService service) throws Exception {
        String id_PI = "";
        String userid_pi = "";
        String mailPI = "";

        Element elCentro = service.getElement(getElementIdCentro(elementId, service));

        id_PI = elCentro.getFieldDataCode("IdCentro", "PINomeCognome");
        Connection conn = dataSource.getConnection();
        String sql1 = "select userid from ANA_UTENTI_1 where USERID='" + id_PI+"'";
        it.cineca.siss.axmr3.log.Log.info(getClass(), sql1);
        PreparedStatement stmt = conn.prepareStatement(sql1);
        ResultSet rset = stmt.executeQuery();

        if (rset.next()) userid_pi = rset.getString("userid");
        conn.close();

        mailPI = getEmail(userid_pi);

        return mailPI;

    }

    public void creaFatture(String elementId) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "creaFatture INIZIO");
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        Collection<Element> children = el.getChildren();
        String fattura;
        String fatturaAcconto = el.getFieldDataCode("DatiFatturaScheduling", "SelectFattura");
        String accontoAssoluto = el.getFieldDataString("DatiFatturaScheduling", "AccontoAssoluto");
        Element fatturazione = el.getParent();
        String acconto = fatturazione.getFieldDataString("StatoScheduling", "ValoreAcconto");
        String rimborsato = fatturazione.getFieldDataString("StatoScheduling", "AccontoRiassorbito");
        Double accontoVal = 0.0;
        Double rimborsatoVal = 0.0;
        Double left = 0.0;
        Double realeVal = 0.0;
        Double riassorbimentoAccontoValore = 0.0;
        String type = "";
        LinkedList<String> types = new LinkedList<String>();
        types.add("LinkVocePassThroughFattura");
        types.add("LinkVoceSchedulingFattura");
        types.add("LinkVoceMonitoraggioFattura");
        types.add("LinkVoceRiduzioneFattura");
        types.add("LinkVoceAggiuntivaFattura");
        types.add("LinkVocePazientiFattura");
        //String accontoPercentuale=el.getFieldDataString("DatiFatturaScheduling", "AccontoPercentuale");
        LinkedList<Element> vociList;
        HashMap<String, LinkedList<Element>> fatture = new LinkedHashMap<String, LinkedList<Element>>();
        Set<String> fattureKeys;
        Long newChildId;
        Long newFatturaId;
        String tipoVoce = "";
        String tipologia = el.getFieldDataCode("DatiFattura", "Tipologia") + "###" + el.getFieldDataDecode("DatiFattura", "Tipologia");
        double value = 0.0;
        double total = 0.0;
        try {
            accontoVal = Double.parseDouble(acconto);
            rimborsatoVal = Double.parseDouble(rimborsato);
        } catch (NumberFormatException ex) {
            Logger.getLogger(this.getClass()).error(ex.getMessage(), ex);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Errore conversione rimborso");
        }
        for (Element child : children) {
            fattura = child.getFieldDataCode("DatiVoceFattura", "SelectFattura");
            if ((!child.getType().getTypeId().equals("VoceSchedulingFattura") && !child.getType().getTypeId().equals("VoceRiduzioneFattura")) || (fattura != null && !fattura.isEmpty() && !fattura.equals("0"))) {
                if (!fatture.containsKey(fattura)) {
                    vociList = new LinkedList<Element>();
                    fatture.put(fattura, vociList);
                }
                vociList = fatture.get(fattura);
                vociList.add(child);
                fatture.put(fattura, vociList);
            }
        }

        //controllo che ci sia nella mappa la fattura per l'acconto
        if (fatturaAcconto != null && !fatturaAcconto.isEmpty() && !fatturaAcconto.equals("0")) {
            if (!fatture.containsKey(fatturaAcconto)) {
                vociList = new LinkedList<Element>();
                fatture.put(fatturaAcconto, vociList);
            }
        }

        String group = getCTOgroup(commonBean.getUser(el.getCreateUser())).replace("CTO_", "UR_");//TOSCANA-177
        fattureKeys = fatture.keySet();
        for (String key : fattureKeys) {
            total = 0.0;
            vociList = fatture.get(key);
            newFatturaId = commonBean.createChild(elementId, el.getCreateUser(), "Fattura", service);
            commonBean.addMetadataValue(newFatturaId.toString(), "DatiFattura", "Tipologia", tipologia, service);
            for (Element oldChild : vociList) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "type: " + "Link" + oldChild.getType().getTypeId());
                tipoVoce = oldChild.getFieldDataString("DatiVoceFattura", "Tipologia");
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "tipoVoce=" + tipoVoce);
                if (tipoVoce.equals("1") || tipoVoce.equals("2")) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "Calcolo 1/2");
                    value = Double.parseDouble(oldChild.getFieldDataString("DatiMonitoraggioFattura", "Totale"));
                } else if (tipoVoce.equals("3")) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "Calcolo 3");
                    value = Double.parseDouble(oldChild.getFieldDataString("DatiSchedulingFattura", "Prezzo"));
                } else if (tipoVoce.equals("4")) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "Calcolo 4");
                    value = Double.parseDouble(oldChild.getFieldDataString("DatiPassThroughPrezzo", "Prezzo"));
                } else if (tipoVoce.equals("5")) {//TOSCANA-87 prendo l'importo da recuperare
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "Calcolo 5");
                    value = Double.parseDouble(oldChild.getFieldDataString("DatiRiduzioneFattura", "ImportoRecuperato"));
                } else if (tipoVoce.equals("6")) {//SIRER-69 vice aggiuntiva Fattura
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "Calcolo 6");
                    value = Double.parseDouble(oldChild.getFieldDataString("DatiAggiuntivaFattura", "Totale"));
                } else if (tipoVoce.equals("8")) {//SIRER-67 voce pazienti fatturabili Fattura
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "Calcolo 8");
                    value = Double.parseDouble(oldChild.getFieldDataString("DatiPazientiFattura", "Totale"));
                } else {

                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "Non dovrei essere qui tipoVoce=" + tipoVoce + " per " + oldChild.getId().toString());
                    value = 0.0;
                }

                total += value;
                type = "Link" + oldChild.getType().getTypeId();
                if (types.contains(type)) {
                    newChildId = commonBean.createChild(newFatturaId.toString(), el.getCreateUser(), type, service);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "la Voce id vecchio: " + oldChild.getId().toString() + " id nuovo: " + newChildId.toString() + " tipologia: " + tipoVoce + " valore: " + value);
                    commonBean.addMetadataValue(newChildId.toString(), "LinkRichiesta", "Richiesta", oldChild.getId().toString(), service);
                    commonBean.addMetadataValue(oldChild.getId().toString(), "DatiVoceFattura", "LinkFattura", newFatturaId.toString(), service);
                    //TOSCANA-87 setto a recuperata=SI
                    if (tipoVoce.equals("5")) {
                        commonBean.addMetadataValue(oldChild.getFieldDataElement("DatiRiduzioneFattura_LinkRiduzione").get(0).getId().toString(), "RiduzioneFattura", "Recuperata", "Si", service);
                    }
                } else {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "ERRORE: alla Voce id vecchio: " + oldChild.getId().toString() + " tipologia: " + tipoVoce + " valore: " + value);
                }


            }
            if (fatturaAcconto != null && !fatturaAcconto.isEmpty() && fatturaAcconto.equals(key)) {
                commonBean.copyData(el, newFatturaId.toString(), "DatiFatturaScheduling", "AccontoAssoluto", "DatiFatturaScheduling", "AccontoAssoluto", service);
                commonBean.copyData(el, newFatturaId.toString(), "DatiFatturaScheduling", "AccontoPercentuale", "DatiFatturaScheduling", "AccontoPercentuale", service);
                commonBean.copyData(el, newFatturaId.toString(), "DatiFatturaScheduling", "StartUpRimborsabile", "DatiFatturaScheduling", "StartUpRimborsabile", service);
                commonBean.addMetadataValue(elementId, "DatiFatturaScheduling", "LinkFattura", newFatturaId.toString(), service);
                accontoAssoluto = accontoAssoluto.replaceAll(",", ".");
                total += Double.parseDouble(accontoAssoluto);
            }
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Tipologia: " + tipologia);
            if (!tipologia.equals("1###Acconto")) {

                HashMap<String, String> data = new HashMap<String, String>();
                if (accontoVal > rimborsatoVal) {
                    left = accontoVal - rimborsatoVal;
                    if (left >= total) {
                        rimborsatoVal += total;
                        commonBean.addMetadataValue(newFatturaId.toString(), "DatiFatturaWF", "realeFattura", "0", service);
                        riassorbimentoAccontoValore = total;
                        //attachRibaltamentoProcess(newFatturaId.toString());
                        service = commonBean.getDocumentService();
                    } else {

                        realeVal = total - left;
                        rimborsatoVal += left;//TOSCANA-89 bugfix calcolo riassorbimento
                        riassorbimentoAccontoValore = left;
                        //attachRibaltamentoProcess(newFatturaId.toString());
                        commonBean.addMetadataValue(newFatturaId.toString(), "DatiFatturaWF", "realeFattura", String.valueOf(realeVal), service);

                    }
                    commonBean.addMetadataValue(fatturazione, "StatoScheduling", "AccontoRiassorbito", String.valueOf(rimborsatoVal), service);
                    data.put("riassorbimentoAcconto_Valore", String.valueOf(riassorbimentoAccontoValore));
                    commonBean.addMetadataValue(newFatturaId.toString(), "DatiFatturaWF", "totaleFattura", String.valueOf(total), service);
                    newChildId = commonBean.createChild(newFatturaId.toString(), el.getCreateUser(), "riassorbimentoAcconto", data, service);
                } else {
                    commonBean.addMetadataValue(newFatturaId.toString(), "DatiFatturaWF", "realeFattura", String.valueOf(total), service);
                    commonBean.addMetadataValue(newFatturaId.toString(), "DatiFatturaWF", "totaleFattura", String.valueOf(total), service);
                }

                //attachRibaltamentoProcess(newFatturaId.toString());

            } else {
                commonBean.addMetadataValue(newFatturaId.toString(), "DatiFatturaWF", "totaleFattura", String.valueOf(total), service);
                commonBean.addMetadataValue(newFatturaId.toString(), "DatiFatturaWF", "realeFattura", String.valueOf(total), service);
            }

            //TOSCANA-177
            commonBean.copyData(el, newFatturaId.toString(), "DatiFatturaScheduling", "DestinatarioRagSoc", "DatiFatturaScheduling", "DestinatarioRagSoc", service);
            commonBean.copyData(el, newFatturaId.toString(), "DatiFatturaScheduling", "DestinatarioPIVA", "DatiFatturaScheduling", "DestinatarioPIVA", service);
            commonBean.copyData(el, newFatturaId.toString(), "DatiFatturaScheduling", "DestinatarioIndirizzo", "DatiFatturaScheduling", "DestinatarioIndirizzo", service);
            //TOSCANA-163
            commonBean.copyData(el, newFatturaId.toString(), "DatiFatturaScheduling", "FatturazioneRagSoc", "DatiFatturaScheduling", "FatturazioneRagSoc", service);
            commonBean.copyData(el, newFatturaId.toString(), "DatiFatturaScheduling", "FatturazionePIVA", "DatiFatturaScheduling", "FatturazionePIVA", service);
            commonBean.copyData(el, newFatturaId.toString(), "DatiFatturaScheduling", "FatturazioneIndirizzo", "DatiFatturaScheduling", "FatturazioneIndirizzo", service);

            //do i diritti all'ufficio ragioneria competente
            //commonBean.changePermissionToGroup(newFatturaId.toString(), "V,C,M,AC,B,A", "", group, service);
        }
        //do i diritti all'ufficio ragioneria competente
        commonBean.changePermissionToGroup(elementId, "V,AC,B,A", "", group, service);//TOSCANA-89
        String today = new SimpleDateFormat("dd/MM/yyyy").format(new java.util.Date());

        commonBean.addMetadataValue(elementId, "DatiRichiestaFatturazioneWF", "inviata", "1", service);
        commonBean.addMetadataValue(elementId, "DatiRichiestaFatturazioneWF", "dataInvio", today, service);

        commonBean.closeDocumentService(service);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "creaFatture FINE");
    }

    public boolean isBillable(Element scheduling, List<Element> pazienti, String fatturazioneRule, String periodRule, String visiteRule, String numPazRule, String percPazRule, String totPaz, List<Element> visiteCheckpoints) {
        int pazNum = getPazNumFromRules(visiteRule, numPazRule, percPazRule, totPaz);
        return isBillable(scheduling, pazienti, fatturazioneRule, periodRule, visiteRule, pazNum, visiteCheckpoints);
    }

    //da terminare aggiungendo la parte a tempo
    public boolean isBillable(Element scheduling, List<Element> pazienti, String fatturazioneRule, String periodRule, String visiteRule, int pazNum, List<Element> visiteCheckpoints) {
        //int pazNum=0;
        int countPaz = 0;
        boolean pazienteBillable = false;
        Element centro;
        Element primoArruolamento;
        Calendar dataStart = new GregorianCalendar();
        Calendar today = new GregorianCalendar();
        List<Element> primoPazList;
        Element primoPaz;
        LocalDate inizio = null;
        LocalDate fine;
        int months = 0;
        int timePeriod = 0;
        List<Element> checkpointFatturabili;


        it.cineca.siss.axmr3.log.Log.debug(getClass(), "isBillable");

        //it.cineca.siss.axmr3.log.Log.debug(getClass(),"isBillable numPazRule "+numPazRule);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "isBillable fatturazioneRule " + fatturazioneRule);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "isBillable visiteRule " + visiteRule);


        if (fatturazioneRule.equals("2")) { //Fatturazione a quantità


            if (visiteRule.equals("1") || visiteRule.equals("2")) { //n./percentuale Pazienti completati
                //ciclo i pazienti per contare i completati
                for (Element paziente : pazienti) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "isBillable controllo paziente " + paziente.getId().toString());
                    pazienteBillable = isPatientBillable(paziente, fatturazioneRule, visiteRule);
                    if (pazienteBillable) {
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "isBillable controllo paziente " + paziente.getId().toString() + " is billable");
                        countPaz++;
                        if (countPaz >= pazNum) { //raggiunto il numero di pazienti completati necessari
                            it.cineca.siss.axmr3.log.Log.debug(getClass(), "isBillable raggiunto target");
                            it.cineca.siss.axmr3.log.Log.debug(getClass(), "isBillable return billable");
                            return true;
                        }
                    }

                }
            } else if (visiteRule.equals("3") || visiteRule.equals("4")) {    //controllo sulle visite
                checkpointFatturabili = getCheckpointFatturabili(pazienti, visiteRule, pazNum, visiteCheckpoints);
                if (checkpointFatturabili.size() > 0) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "isBillable raggiunto target per " + checkpointFatturabili.size() + " checkpoint");
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "isBillable return billable");
                    return true;
                }
            }
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "isBillable return no billable");
            return false;
        } else if (pazienti != null && pazienti.size() > 0) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "prosegue crontab a tempo per " + scheduling.getId().toString());
            dataStart = scheduling.getFieldDataDate("StatoScheduling", "UltimaMilestoneCrontab");
            if (dataStart != null) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "prosegue crontab data UltimaMilestoneCrontab settata per " + scheduling.getId().toString());
                inizio = new LocalDate(dataStart.getTimeInMillis());
            }
            if (inizio == null) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "prosegue crontab data UltimaMilestoneCrontab non settata per " + scheduling.getId().toString());
                centro = pazienti.iterator().next().getParent();
                try {
                    /*TOSCANA-164 VMAZZEO 23.06.2017
                     *
                     * IMPOSTO DATA INIZIO FATTURA IN BASE AL VALORE DI scheduling_DataInizioFatt
                     *
                     * */
                    String DataInizioFatt = scheduling.getFieldDataCode("scheduling", "DataInizioFatt");
                    if (DataInizioFatt == "1") { //firma del contratto
                        Element firma = centro.getChildrenByType("Contratto").get(0).getChildrenByType("ContrattoFirmaDG").get(0);
                        if (firma != null) {
                            dataStart = firma.getFieldDataDate("DatiContrattoFirmaDG", "dataFirma");

                            inizio = new LocalDate(dataStart.getTimeInMillis());
                        }
                    } else if (DataInizioFatt == "2" || DataInizioFatt == "3") { //apertura del centro oppure arruolamento primo paziente
                        primoPazList = centro.getChildrenByType("ArruolamentoPrimoPaz");

                        if (primoPazList != null && primoPazList.size() > 0) {
                            primoPaz = primoPazList.get(0);
                            if (DataInizioFatt == "2") {//apertura del centro
                                dataStart = primoPaz.getFieldDataDate("DatiArrPrimoPaz", "dataAperturaCentro ");

                                inizio = new LocalDate(dataStart.getTimeInMillis());
                            } else if (DataInizioFatt == "3") {//arruolamento primo paziente
                                dataStart = primoPaz.getFieldDataDate("DatiArrPrimoPaz", "dataPrimoArr");

                                inizio = new LocalDate(dataStart.getTimeInMillis());
                            }

                        }

                    } else if (DataInizioFatt == "4") { //1° Gennaio successivo

                        dataStart = new GregorianCalendar(Calendar.getInstance().get(Calendar.YEAR) + 1, 0, 1);
                        inizio = new LocalDate(dataStart.getTimeInMillis());

                    }
                } catch (Exception ex) {

                }
                /*primoPazList = centro.getChildrenByType("ArruolamentoPrimoPaz");

                if(primoPazList!=null && primoPazList.size()>0){
                    primoPaz=primoPazList.get(0);
                    dataStart = primoPaz.getFieldDataDate("DatiArrPrimoPaz", "dataPrimoArr");

                    inizio = new LocalDate(dataStart.getTimeInMillis());


                }*/
            }
            if (inizio != null) {
                fine = new LocalDate(today.getTimeInMillis());
                months = Months.monthsBetween(inizio, fine).getMonths();
                timePeriod = Integer.parseInt(periodRule);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "prosegue crontab mesi trascorsi " + String.valueOf(months) + " periodo di controllo " + String.valueOf(timePeriod) + " per " + scheduling.getId().toString());
                if (months >= timePeriod) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "isBillable return billable");
                    return true;
                }
            }
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "isBillable return no billable");
            return false;
        } else {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "finisce crontab no pazienti per " + scheduling.getId().toString());
        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "isBillable return no billable");
        return false;
    }

    public boolean isPatientBillable(Element paziente, String fatturazioneRule, String visiteRule) {


        int numVisita = 0;
        boolean pazienteFatturato = false;
        Collection<Element> visite;
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Stato " + paziente.getFieldDataCode("StatoPaziente", "Stato"));
        if (paziente.getFieldDataCode("StatoPaziente", "Stato").equals("5")) {   //screeninfailure non si fattura
            return false;
        }
        if (!paziente.getFieldDataCode("DatiMonitoraggioAmministrativo", "validatoIRINN").equals("1")) {   //SIRER-72 fatturo solo se DatiMonitoraggioAmministrativo_validatoIRINN==1
            return false;
        }

        if (fatturazioneRule.equals("2")) { //Fatturazione a quantità


            if (visiteRule.equals("1") || visiteRule.equals("2")) { //n./percentuale Pazienti completati

                //it.cineca.siss.axmr3.log.Log.debug(getClass(),"Stato "+paziente.getFieldDataCode("StatoPaziente","Stato"));
                if (!paziente.getFieldDataCode("StatoPaziente", "Stato").equals("1")) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "Paziente completato ");
                    pazienteFatturato = false;
                    visite = paziente.getChildrenByType("FolderMonTimePoint").get(0).getChildren();
                    for (Element currVisita : visite) {
                        numVisita = Integer.parseInt(currVisita.getFieldDataElement("DatiMonTimePoint", "TimePoint").get(0).getFieldDataString("TimePoint", "col")) - 1;
                        if (numVisita == 1 && (currVisita.getFieldDataElement("DatiFatturazioneTP", "ReportFatturazione").isEmpty() || currVisita.getFieldDataElement("DatiFatturazioneTP", "ReportFatturazione").get(0) == null)) {
                            break;
                        } else if (!(currVisita.getFieldDataElement("DatiFatturazioneTP", "ReportFatturazione").isEmpty() || currVisita.getFieldDataElement("DatiFatturazioneTP", "ReportFatturazione").get(0) == null)) {
                            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Paziente fatturato per visita " + currVisita.getId().toString() + " ReportFatturazione -" + currVisita.getFieldDataElement("DatiFatturazioneTP", "ReportFatturazione").get(0).getId().toString() + "-");
                            pazienteFatturato = true;
                            break;
                        }
                    }

                    if (!pazienteFatturato) {
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Paziente non fatturato ");
                        return true;
                    } else {
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Paziente fatturato ");
                        return false;
                    }

                } else {
                    return false;
                }
            } else {
                return true;
            }


        } else {
            return true;
        }
    }

    private int getPazNumFromRules(String visiteRule, String numPazRule, String percPazRule, String totPaz) {
        int pazNum = 0;
        if (numPazRule == null || visiteRule == null) return 0;
        if (numPazRule.matches("-?\\d+")) {
            pazNum = Integer.parseInt(numPazRule);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "numPazRule is numeric");
        }
        if (visiteRule.equals("2")) {  //Percentuale pazienti completati
            pazNum = Integer.parseInt(percPazRule) * Integer.parseInt(totPaz) / 100;
        }
        return pazNum;
    }

    private List<Element> getCheckPointFatturabili(List<Element> pazienti, String visiteRule, String numPazRule, String percPazRule, String totPaz, List<Element> checkpoints) {
        int pazNum = getPazNumFromRules(visiteRule, numPazRule, percPazRule, totPaz);
        return getCheckpointFatturabili(pazienti, visiteRule, pazNum, checkpoints);
    }

    private List<Element> getCheckpointFatturabili(List<Element> pazienti, String visiteRule, int pazNum, List<Element> checkpoints) {
        Collection<Element> visite;
        HashMap<Integer, Long> checkpointsMap = new HashMap<Integer, Long>();
        HashMap<Integer, Integer> checkpointsCount = new HashMap<Integer, Integer>();
        HashMap<Long, Integer> visiteFatturabiliCount = new HashMap<Long, Integer>();
        Integer currVisitaFatturabile = 0;
        Integer ultimaVisitaFatturabile = 0;
        Integer currCheckPoint = 0;
        Integer ultimoCheckPoint = 0;
        LinkedList<Element> checkpointsFatturabili = new LinkedList<Element>();
        int currCount = 0;
        boolean everyVisitIsCheckpoint = visiteRule.equals("3");

        if (!visiteRule.equals("4") && !visiteRule.equals("3")) {
            return checkpoints;
        }

        for (Element checkpoint : checkpoints) {
            if (checkpoint.getFieldDataString("DatiTPFatt", "CheckFatt").equals("1") || everyVisitIsCheckpoint) {
                currCheckPoint = Integer.parseInt(checkpoint.getFieldDataElement("DatiTPFatt", "TPBudget").get(0).getFieldDataString("TimePoint", "col"));
                checkpointsCount.put(currCheckPoint, 0);
            }
        }


        for (Element paziente : pazienti) {
            visite = paziente.getChildrenByType("FolderMonTimePoint").get(0).getChildren();
            currVisitaFatturabile = 0;
            ultimaVisitaFatturabile = 0;
            currCheckPoint = 0;
            ultimoCheckPoint = 0;

            for (Element visita : visite) {
                if (visita.getFieldDataString("DatiMonTimePoint", "Fatturabile").equals("1") && visita.getFieldDataElement("DatiFatturazioneTP", "ReportFatturazione").isEmpty()) {
                    currVisitaFatturabile = Integer.parseInt(visita.getFieldDataElement("DatiMonTimePoint", "TimePoint").get(0).getFieldDataString("TimePoint", "col"));
                    if (checkpointsCount.containsKey(currVisitaFatturabile)) {
                        currCount = checkpointsCount.get(currVisitaFatturabile) + 1;
                        checkpointsCount.put(currVisitaFatturabile, currCount);
                    }
                }
            }


        }

        for (Element checkpoint : checkpoints) {
            if (checkpoint.getFieldDataString("DatiTPFatt", "CheckFatt").equals("1") || everyVisitIsCheckpoint) {
                currCheckPoint = Integer.parseInt(checkpoint.getFieldDataElement("DatiTPFatt", "TPBudget").get(0).getFieldDataString("TimePoint", "col"));
                if (checkpointsCount.get(currCheckPoint) >= pazNum) {
                    checkpointsFatturabili.add(checkpoint);
                }
            }
        }

        return checkpointsFatturabili;
    }

    //per ogni paziente ciclo le visite e determino quelle che soddisfano le regole dello scheduling
    public HashMap<String, Element> getVisiteFatturabili(String fatturaId, DocumentService service, Collection<Element> visite, String fatturazioneRule, String visiteRule, Collection<Element> visiteCheckpoints) throws Exception {
        HashMap<String, Element> visiteFatturabili = new HashMap<String, Element>();
        Integer currVisitaFatturabile = 0;
        Integer ultimaVisitaFatturabile = 0;
        Integer currCheckPoint = 0;
        Integer ultimoCheckPoint = 0;

        if (fatturazioneRule.equals("1") || visiteRule.equals("1") || visiteRule.equals("2") || visiteRule.equals("3")) {
            for (Element visita : visite) {
                if (visita.getFieldDataString("DatiMonTimePoint", "Fatturabile").equals("1") && visita.getFieldDataElement("DatiFatturazioneTP", "ReportFatturazione").isEmpty()) {
                    //importante spostarlo dopo al di fuori della funzione
                    commonBean.addMetadataValue(visita.getId().toString(), "DatiFatturazioneTP", "ReportFatturazione", fatturaId, service);
                    visiteFatturabili.put(visita.getId().toString(), visita);
                }
            }
        } else if (visiteRule.equals("4")) {
            for (Element visita : visite) {
                if (visita.getFieldDataString("DatiMonTimePoint", "Fatturabile").equals("1") && visita.getFieldDataElement("DatiFatturazioneTP", "ReportFatturazione").isEmpty()) {
                    currVisitaFatturabile = Integer.parseInt(visita.getFieldDataElement("DatiMonTimePoint", "TimePoint").get(0).getFieldDataString("TimePoint", "col"));
                    if (currVisitaFatturabile.compareTo(ultimaVisitaFatturabile) > 0) {
                        ultimaVisitaFatturabile = currVisitaFatturabile;
                    }
                }
            }
            for (Element checkpoint : visiteCheckpoints) {
                if (checkpoint.getFieldDataString("DatiTPFatt", "CheckFatt").equals("1")) {
                    currCheckPoint = Integer.parseInt(checkpoint.getFieldDataElement("DatiTPFatt", "TPBudget").get(0).getFieldDataString("TimePoint", "col"));
                    if (currCheckPoint.compareTo(ultimaVisitaFatturabile) <= 0 && currCheckPoint.compareTo(ultimoCheckPoint) > 0) {
                        ultimoCheckPoint = currCheckPoint;
                    }
                }
            }
            for (Element visita : visite) {
                if (visita.getFieldDataString("DatiMonTimePoint", "Fatturabile").equals("1") && visita.getFieldDataElement("DatiFatturazioneTP", "ReportFatturazione").isEmpty()) {
                    currVisitaFatturabile = Integer.parseInt(visita.getFieldDataElement("DatiMonTimePoint", "TimePoint").get(0).getFieldDataString("TimePoint", "col"));
                    if (currVisitaFatturabile.compareTo(ultimoCheckPoint) <= 0) {
                        commonBean.addMetadataValue(visita.getId().toString(), "DatiFatturazioneTP", "ReportFatturazione", fatturaId, service);
                        visiteFatturabili.put(visita.getId().toString(), visita);
                    }
                }
            }
        }
        return visiteFatturabili;
    }

    public HashMap<String, VoceMonitoraggioFatturazione> getPrestazioniARichiestaFatturabili(DocumentService service, Collection<Element> prestazioniARichiesta, String fatturaId, HashMap<String, String> cdcs, HashMap<String, VoceMonitoraggioFatturazione> voceMonitoraggioFatturaMap) throws Exception {
        String quantitaFatturabile = "";
        Integer quantitaInt = 0;
        Element prestazioneLink;
        String nomePrestazione = "";
        String prestazioneId = "";
        //HashMap<String, VoceMonitoraggioFatturazione> voceMonitoraggioFatturaMap = new HashMap<String, VoceMonitoraggioFatturazione>();
        VoceMonitoraggioFatturazione listPrestazioniARichiesta;
        String quantitaFatturata = "";
        HashMap<String, String> data = new HashMap<String, String>();

        Element budgetLink;
        String cdcCode = "";
        String cdcDecode = "";
        String transferPrice = "";
        String SSN = "";
        String codice = "";

        for (Element prestazione : prestazioniARichiesta) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "preparaRichiestaFatturaDaMon a richiesta");

            quantitaFatturabile = prestazione.getFieldDataString("DatiMonPxP", "Fatturabile");
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "preparaRichiestaFatturaDaMon quantita " + quantitaFatturabile);
            if (!quantitaFatturabile.isEmpty() && !quantitaFatturabile.equals("0")) {
                try {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "preparaRichiestaFatturaDaMon try ");
                    quantitaInt = Integer.parseInt(quantitaFatturabile);
                    if (quantitaInt > 0) {
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "preparaRichiestaFatturaDaMon in " + quantitaInt.toString());
                        prestazioneLink = prestazione.getFieldDataElement("DatiMonPxP", "BudgetLink").get(0);

                        nomePrestazione = prestazioneLink.getFieldDataString("Base", "Nome");
                        if (!voceMonitoraggioFatturaMap.containsKey(nomePrestazione)) {
                            voceMonitoraggioFatturaMap.put(nomePrestazione, new VoceMonitoraggioFatturazione());
                        }
                        budgetLink = prestazione.getFieldDataElement("DatiMonPxP", "BudgetLink").get(0);
                        cdcCode = budgetLink.getFieldDataString("Prestazioni", "CDCCode");
                        cdcDecode = budgetLink.getFieldDataString("Prestazioni", "CDC");
                        //cdcCode=budgetLink.getFieldDataCode("Prestazioni", "Attivita");
                        //cdcDecode=budgetLink.getFieldDataDecode("Prestazioni","Attivita");
                        transferPrice = budgetLink.getFieldDataString("Costo", "TransferPrice");
                        SSN = budgetLink.getFieldDataString("Tariffario", "SSN");
                        codice = budgetLink.getFieldDataString("Prestazioni_Codice");
                        if (!cdcs.containsKey(cdcCode)) {
                            cdcs.put(cdcCode, cdcDecode);
                        }
                        listPrestazioniARichiesta = voceMonitoraggioFatturaMap.get(nomePrestazione);
                        listPrestazioniARichiesta.add(prestazione, cdcCode, transferPrice, SSN, codice, prestazione.getFieldDataString("DatiMonPxP", "Prezzo"), quantitaInt);
                        voceMonitoraggioFatturaMap.put(nomePrestazione, listPrestazioniARichiesta);

                        quantitaFatturata = prestazione.getFieldDataString("DatiMonPxP", "Fatturato");
                        if (quantitaFatturata.matches("-?\\d+(\\.\\d+)?")) {
                            quantitaInt += Integer.parseInt(quantitaFatturata);
                        }
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "preparaRichiestaFatturaDaMon:Fatturato e Fatturabile per " + prestazione.getId().toString());
                        prestazioneId = prestazione.getId().toString();

                        data.put("LinkFattura_Link", fatturaId);
                        data.put("LinkFattura_Occorrenze", quantitaInt.toString());
                        commonBean.createChild(prestazioneId, "CTC", "LinkFattura", data, service);

                        commonBean.addMetadataValue(prestazioneId, "DatiMonPxP", "Fatturato", quantitaInt.toString(), service);
                        commonBean.addMetadataValue(prestazioneId, "DatiMonPxP", "Fatturabile", "0", service);

                    }
                } catch (Exception ex) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "eccezione");
                    Logger.getLogger(this.getClass()).error(ex.getMessage(), ex);
                }
            }
        }
        return voceMonitoraggioFatturaMap;
    }

    public HashMap<String, VoceMonitoraggioFatturazione> getPazientiFatturabili(DocumentService service, Collection<Element> pazientiCompletati, String fatturaId, HashMap<String, VoceMonitoraggioFatturazione> voceMonitoraggioFatturaMap) throws Exception {
        String quantitaFatturabile = "";
        Integer quantitaInt = 0;
        Element prestazioneLink;
        String nomePrestazione = "";
        String prestazioneId = "";
        //HashMap<String, VoceMonitoraggioFatturazione> voceMonitoraggioFatturaMap = new HashMap<String, VoceMonitoraggioFatturazione>();
        VoceMonitoraggioFatturazione listPazientiCompletati;
        String quantitaFatturata = "";
        HashMap<String, String> data = new HashMap<String, String>();

        Element budgetLink;
        String cdcCode = "";
        String cdcDecode = "";
        String transferPrice = "";
        String SSN = "";
        String codice = "";

        for (Element prestazione : pazientiCompletati) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "preparaRichiestaFatturaDaMon a richiesta");

            quantitaFatturabile = prestazione.getFieldDataString("DatiMonPazientiFatturabili", "Fatturabile");
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "preparaRichiestaFatturaDaMon quantita " + quantitaFatturabile);
            if (!quantitaFatturabile.isEmpty() && !quantitaFatturabile.equals("0")) {
                try {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "preparaRichiestaFatturaDaMon try ");
                    quantitaInt = Integer.parseInt(quantitaFatturabile);
                    if (quantitaInt > 0) {
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "preparaRichiestaFatturaDaMon in " + quantitaInt.toString());

                        nomePrestazione = prestazione.getFieldDataString("DatiMonPazientiFatturabili", "Note");
                        if (!voceMonitoraggioFatturaMap.containsKey(nomePrestazione)) {
                            voceMonitoraggioFatturaMap.put(nomePrestazione, new VoceMonitoraggioFatturazione());
                        }
                        budgetLink = prestazione.getFieldDataElement("DatiMonPazientiFatturabili", "BudgetLink").get(0);
                        transferPrice = budgetLink.getFieldDataString("Costo", "TransferPrice");
                        SSN = budgetLink.getFieldDataString("Tariffario", "SSN");
                        codice = budgetLink.getFieldDataString("Prestazioni_Codice");
                        listPazientiCompletati = voceMonitoraggioFatturaMap.get(nomePrestazione);
                        listPazientiCompletati.add(prestazione, cdcCode, transferPrice, SSN, codice, prestazione.getFieldDataString("DatiMonPazientiFatturabili", "Prezzo"), quantitaInt);
                        HashSet<Long> numPazienti = new HashSet<Long>();
                        for (int i = 0; i <= Integer.parseInt(prestazione.getFieldDataString("DatiMonPazientiFatturabili", "numeroPazienti")); i++) {
                            numPazienti.add(new Long(i));
                        }
                        listPazientiCompletati.setPazienti(numPazienti);
                        voceMonitoraggioFatturaMap.put(nomePrestazione, listPazientiCompletati);

                        quantitaFatturata = prestazione.getFieldDataString("DatiMonPazientiFatturabili", "Fatturato");
                        if (quantitaFatturata.matches("-?\\d+(\\.\\d+)?")) {
                            quantitaInt += Integer.parseInt(quantitaFatturata);
                        }
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "preparaRichiestaFatturaDaMon:Fatturato e Fatturabile per " + prestazione.getId().toString());
                        prestazioneId = prestazione.getId().toString();

                        data.put("LinkFattura_Link", fatturaId);
                        data.put("LinkFattura_Occorrenze", quantitaInt.toString());
                        commonBean.createChild(prestazioneId, "CTC", "LinkFattura", data, service);

                        commonBean.addMetadataValue(prestazioneId, "DatiMonPazientiFatturabili", "Fatturato", quantitaInt.toString(), service);
                        commonBean.addMetadataValue(prestazioneId, "DatiMonPazientiFatturabili", "Fatturabile", "0", service);

                    }
                } catch (Exception ex) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "eccezione");
                    Logger.getLogger(this.getClass()).error(ex.getMessage(), ex);
                }
            }
        }
        return voceMonitoraggioFatturaMap;
    }

    public void preparaRichiestaFatturaDaMon(Element fattura, DocumentService service) throws Exception {
        preparaRichiestaFatturaDaMon(fattura, service, "");
    }

    public void preparaRichiestaFatturaDaMon(Element fattura, DocumentService service, String tipoFatt) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "preparaRichiestaFatturaDaMon:passo 1 ");
        String fatturaId = fattura.getId().toString();
        Element scheduling = fattura.getParent();
        Element centro = scheduling.getParent();
        HashMap<String, String> cdcs = new HashMap<String, String>();

        String fatturazioneRule = scheduling.getFieldDataCode("scheduling", "ModalitaFatturazione");
        String periodRule = scheduling.getFieldDataCode("scheduling", "Periodicita");
        String visiteRule = scheduling.getFieldDataCode("scheduling", "TipologiaCalcolo");
        String numPazRule = scheduling.getFieldDataString("scheduling", "NumPaz");
        String percPazRule = scheduling.getFieldDataString("scheduling", "PercPaz");
        String totPaz = scheduling.getFieldDataString("InfoBudget", "Pazienti");
        List<Element> checkpoints = scheduling.getChildrenByType("TPFatt");

        List<Element> monitoraggi = centro.getChildrenByType("MonitoraggioAmministrativo");
        HashMap<String, Element> visiteFatturabili = new HashMap<String, Element>();
        HashMap<String, VoceMonitoraggioFatturazione> voceMonitoraggioFatturaMap = new HashMap<String, VoceMonitoraggioFatturazione>();
        HashMap<String, VoceMonitoraggioFatturazione> voceMonitoraggioFatturaMap2 = new HashMap<String, VoceMonitoraggioFatturazione>();
        HashMap<String, VoceMonitoraggioFatturazione> vocePazientiFatturaMap = new HashMap<String, VoceMonitoraggioFatturazione>();
        HashMap<String, VoceMonitoraggioFatturazione> voceMonitoraggioFatturaMapTemp = new HashMap<String, VoceMonitoraggioFatturazione>();
        Collection<Element> visite;
        Collection<Element> prestazioniFlowChart;
        Collection<Element> prestazioniARichiesta;
        Collection<Element> pazientiCompletati;
        Element clinicalLink;
        Element prestazioneLink;
        String currVisita = "";
        String nomePrestazione = "";
        HashMap<String, LinkedList<Element>> targetAchieved = new HashMap<String, LinkedList<Element>>();
        LinkedList<Element> listaPazTarget = new LinkedList<Element>();


        Element budgetLink;
        Element pretazioneFlowchart;
        String cdcCode = "";
        String cdcDecode = "";
        String transferPrice = "";
        String SSN = "";
        String codice = "";
        boolean milestoneAutomatica = fattura.getFieldDataString("DatiRichiestaFatturazioneWF", "MilestoneAutomatica").equals("1");
        boolean targetATempo = (fatturazioneRule.equals("1"));
        boolean targetAQuantita = !targetATempo;
        boolean targetAVisita = (targetAQuantita && (visiteRule.equals("3") || visiteRule.equals("4")));

        double totCdc = 0.0;

        if (visiteRule == null) {
            visiteRule = "";
        }
        int pazNum = getPazNumFromRules(visiteRule, numPazRule, percPazRule, totPaz);


        VoceMonitoraggioFatturazione listOccorenzePrestazione;
        VoceMonitoraggioFatturazione listPrestazioniARichiesta;
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "preparaRichiestaFatturaDaMon:passo 2 ");

        if (visiteRule.equals("4") && milestoneAutomatica) {
            checkpoints = getCheckpointFatturabili(monitoraggi, visiteRule, pazNum, checkpoints);
        }

        if (milestoneAutomatica) {
            if (!targetAVisita) {
                targetAchieved.put("Target", new LinkedList<Element>());
            }
        }

        //ciclo i pazienti
        for (Element paziente : monitoraggi) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "preparaRichiestaFatturaDaMon:passo 3 " + paziente.getId().toString());
            if (tipoFatt.equals("3") || isPatientBillable(paziente, fatturazioneRule, visiteRule)) {
                if (paziente.getChildrenByType("FolderMonTimePoint") == null || paziente.getChildrenByType("FolderMonTimePoint").isEmpty())
                    continue;
                visite = paziente.getChildrenByType("FolderMonTimePoint").get(0).getChildren();

                //per ogni paziente ciclo le visite e determino quelle che soddisfano le regole dello scheduling
                visiteFatturabili = getVisiteFatturabili(fatturaId, service, visite, fatturazioneRule, visiteRule, checkpoints);

                //Verifico le prestazioni da flowchart
                prestazioniFlowChart = paziente.getChildrenByType("FolderMonPxT").get(0).getChildren();
                for (Element prestazione : prestazioniFlowChart) {
                    currVisita = prestazione.getFieldDataString("DatiMonPxT", "MonTimePoint");
                    if (!currVisita.isEmpty() && visiteFatturabili.containsKey(currVisita) && prestazione.getFieldDataString("DatiMonPxT", "Eseguito").equals("1") && !prestazione.getFieldDataString("DatiMonPxT", "Fatturato").equals("1")) {
                        commonBean.addMetadataValue(prestazione.getId().toString(), "DatiMonPxT", "Fatturato", "1", service);
                        commonBean.addMetadataValue(prestazione.getId().toString(), "DatiMonPxT", "Fattura", fatturaId, service);
                        clinicalLink = prestazione.getFieldDataElement("DatiMonPxT", "TPxP").get(0);
                        prestazioneLink = clinicalLink.getFieldDataElement("tp-p", "Prestazione").get(0);
                        String prestazioneRimborso = clinicalLink.getFieldDataString("Rimborso_Rimborsabilita");
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "preparaRichiestaFatturaDaMon: Rimborsabilita prestazione " + clinicalLink.getId().toString() + " = " + clinicalLink.getFieldDataString("Rimborso", "Rimborsabilita"));
                        if (!prestazioneRimborso.equals("2")) {//TOSCANA-89 nella fattura non metto le prestazioni a carico ssn/ssr "BIANCHE"
                            nomePrestazione = prestazioneLink.getFieldDataString("Prestazioni", "prestazione");
                            if (!voceMonitoraggioFatturaMap.containsKey(nomePrestazione)) {
                                voceMonitoraggioFatturaMap.put(nomePrestazione, new VoceMonitoraggioFatturazione());
                            }
                            Element oldPrestazione = prestazione;
                            prestazione = correggiSingleMonBudgetLink(prestazione, (LinkedList<Element>) prestazione.getFieldDataElement("DatiMonPxT", "PrezzoLink"), service);
                            it.cineca.siss.axmr3.log.Log.debug(getClass(), "preparaRichiestaFatturaDaMon:passo x " + prestazione.getId().toString());

                            budgetLink = prestazione.getFieldDataElement("PrezzoFinale", "Prestazione").get(0);
                            pretazioneFlowchart = budgetLink.getFieldDataElement("tp-p", "Prestazione").get(0);
                            cdcCode = pretazioneFlowchart.getFieldDataString("Prestazioni", "CDCCode");//TOSCANA-89
                            cdcDecode = pretazioneFlowchart.getFieldDataString("Prestazioni", "CDC");//TOSCANA-89
                            //cdcCode = pretazioneFlowchart.getFieldDataCode("Prestazioni", "Attivita");
                            //cdcDecode = pretazioneFlowchart.getFieldDataDecode("Prestazioni", "Attivita");
                            transferPrice = budgetLink.getFieldDataString("Costo", "TransferPrice");
                            SSN = budgetLink.getFieldDataElement("tp-p", "Prestazione").get(0).getFieldDataString("Tariffario_SSN");
                            codice = budgetLink.getFieldDataString("Prestazioni_Codice");
                            if (codice.isEmpty()) {
                                codice = prestazione.getFieldDataString("Prestazioni_Codice");
                            }
                            if (codice.isEmpty()) {
                                codice = prestazioneLink.getFieldDataString("Prestazioni_Codice");
                            }
                            if (!cdcs.containsKey(cdcCode)) {
                                cdcs.put(cdcCode, cdcDecode);
                            }

                            listOccorenzePrestazione = voceMonitoraggioFatturaMap.get(nomePrestazione);
                            listOccorenzePrestazione.add(oldPrestazione, cdcCode, transferPrice, SSN, codice, prestazione.getFieldDataString("PrezzoFinale", "Prezzo"));
                            voceMonitoraggioFatturaMap.put(nomePrestazione, listOccorenzePrestazione);
                        }
                        if (milestoneAutomatica) {
                            if (targetAVisita) {
                                if (!targetAchieved.containsKey(currVisita)) {
                                    targetAchieved.put(currVisita, new LinkedList<Element>());
                                }
                                targetAchieved.get(currVisita).add(paziente);
                            }
                        }

                    }
                }

                it.cineca.siss.axmr3.log.Log.debug(getClass(), "preparaRichiestaFatturaDaMon:passo 4 ");
                //Verifico le prestazioni fuori flowchart
                prestazioniARichiesta = paziente.getChildrenByType("FolderMonPxP").get(0).getChildren();
                voceMonitoraggioFatturaMap2 = getPrestazioniARichiestaFatturabili(service, prestazioniARichiesta, fatturaId, cdcs, voceMonitoraggioFatturaMap2);
                pazientiCompletati = paziente.getChildrenByType("FolderMonPazientiFatturabili").get(0).getChildren();
                vocePazientiFatturaMap = getPazientiFatturabili(service, pazientiCompletati, fatturaId, vocePazientiFatturaMap);
                if (milestoneAutomatica) {
                    if (!targetAVisita) {
                        targetAchieved.get("Target").add(paziente);
                    }
                }
            }
        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "preparaRichiestaFatturaDaMon:passo 5 ");
        //creo oggetti per la fattura a partire dalle mappe che mi sono creato ciclando il monitoraggio
        fromMapToVoceMonitoraggioFattura(fattura, voceMonitoraggioFatturaMap, "DatiMonPxT", "1", cdcs, service);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "preparaRichiestaFatturaDaMon:passo 6 ");
        fromMapToVoceMonitoraggioFattura(fattura, voceMonitoraggioFatturaMap2, "DatiMonPxP", "2", cdcs, service);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "preparaRichiestaFatturaDaMon:passo 7 ");
        fromMapToVocePazientiFattura(fattura, vocePazientiFatturaMap, "DatiMonPazientiFatturabili", "8", cdcs, service);


        /*
         * TOSCANA-87
         * ciclo le eventuali riduzioni su fatture precedenti con rimborso nelle rate successive e le inserisco in questa richiesta di fatturazione
         */
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "preparaRichiestaFatturaDaMon:passo 7 APPLICO RIDUZIONI SE NE TROVO ");
        List<Element> richieste = scheduling.getChildrenByType("RichiestaFatturazione");
        List<Element> fatture;
        List<Element> riduzioni;
        Long voceRiduzioneFatturaId;
        for (Element richiesta : richieste) {
            if (!richiesta.getId().toString().equals(fatturaId)) {//prendo le richieste di Fatturazione "sorelle"
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "\tRichiestaFattura: " + richiesta.getId());
                fatture = richiesta.getChildrenByType("Fattura");//prendo le fatture
                for (Element mia_fattura : fatture) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "\tFattura: " + mia_fattura.getId());
                    riduzioni = mia_fattura.getChildrenByType("RiduzioneFattura");//prendo le riduzioni
                    for (Element riduzione : riduzioni) {
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "\tRiduzione: " + riduzione.getId());
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "\t\tquando recuperare: " + riduzione.getFieldDataCode("RiduzioneFattura_QuandoRecuperare") + " type " + riduzione.getFieldDataCode("RiduzioneFattura_QuandoRecuperare").getClass().getName());
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "\t\trecuperata: #" + riduzione.getFieldDataString("RiduzioneFattura_Recuperata") + "# type " + riduzione.getFieldDataString("RiduzioneFattura_Recuperata").getClass().getName());
                        if (riduzione.getFieldDataString("RiduzioneFattura_Recuperata") == "" && ((riduzione.getFieldDataCode("RiduzioneFattura_QuandoRecuperare").equals("3") && tipoFatt.equals("2")) || (riduzione.getFieldDataCode("RiduzioneFattura_QuandoRecuperare").equals("1") && tipoFatt.equals("3")))) {
                            it.cineca.siss.axmr3.log.Log.debug(getClass(), "\tHo trovato una riduzione da recuperare: ");
                            it.cineca.siss.axmr3.log.Log.debug(getClass(), "\t\tfattura id: " + mia_fattura.getId());
                            it.cineca.siss.axmr3.log.Log.debug(getClass(), "\t\triduzione id: " + riduzione.getId());
                            it.cineca.siss.axmr3.log.Log.debug(getClass(), "\t\timporto riduzione: " + mia_fattura.getFieldDataString("DatiFatturaWF", "riduzioneFattura"));
                            //se la riduzione non è già stata recuperata e deve essere recuperata in una rata successiva (questa!)
                            voceRiduzioneFatturaId = commonBean.createChild(fattura.getId().toString(), "CTC", "VoceRiduzioneFattura", service);
                            commonBean.addMetadataValue(voceRiduzioneFatturaId, "DatiVoceFattura", "Tipologia", "5", service);//Tipologia 5 è Riduzione
                            commonBean.addMetadataValue(voceRiduzioneFatturaId, "DatiRiduzioneFattura", "LinkRiduzione", riduzione.getId(), service);
                            commonBean.addMetadataValue(voceRiduzioneFatturaId, "DatiRiduzioneFattura", "ImportoRecuperato", mia_fattura.getFieldDataString("DatiFatturaWF", "riduzioneFattura"), service);
                            it.cineca.siss.axmr3.log.Log.debug(getClass(), "\tcreata VoceRiduzioneFattura id: " + voceRiduzioneFatturaId);
                        }
                    }
                }
            }
        }
        /*List<Element> riduzioni = service.getElementsByTypes(commonBean.getUser()
        for(Element centro:centri) {

        }*/

        /*if(milestoneAutomatica){
            addTargeInfo(fattura, targetATempo,targetAVisita,targetAchieved, service);
        } */

    }


    //TODO: Si possono ridurre le righe di codice di 4/5 righe
    private void addTargeInfo(Element fattura, boolean targetATempo, boolean targetAVisita, HashMap<String, LinkedList<Element>> targetAchieved, DocumentService service) throws Exception {
        Long newElementId;
        Long newPazAdded;
        Element visita;
        LinkedList<Element> target;
        if (!targetAVisita) {
            target = targetAchieved.get("Target");
            newElementId = commonBean.createChild(fattura.getId().toString(), "CTC", "TraguardoMilestone", service);
            if (targetATempo) {
                commonBean.addMetadataValue(newElementId, "DatiTraguardoMilestone", "Tipologia", "temporale", service);
            } else {
                commonBean.addMetadataValue(newElementId, "DatiTraguardoMilestone", "Tipologia", "completamento paziente", service);
            }
            commonBean.addMetadataValue(newElementId, "DatiTraguardoMilestone", "NumeroPazienti", target.size(), service);
            for (Element paziente : target) {
                newPazAdded = commonBean.createChild(newElementId.toString(), "CTC", "PazientiTraguardo", service);
                commonBean.addMetadataValue(newPazAdded, "DatiPazientiTraguardo", "Paziente", paziente.getId(), service);
            }
        } else {
            for (String visitaKey : targetAchieved.keySet()) {
                visita = service.getElement(visitaKey);
                target = targetAchieved.get(visitaKey);
                if (target.size() > 0) {
                    newElementId = commonBean.createChild(fattura.getId().toString(), "CTC", "TraguardoMilestone", service);
                    commonBean.addMetadataValue(newElementId, "DatiTraguardoMilestone", "Tipologia", "completamento visita", service);
                    commonBean.addMetadataValue(newElementId, "DatiTraguardoMilestone", "NumeroPazienti", target.size(), service);
                    commonBean.addMetadataValue(newElementId, "DatiTraguardoMilestone", "Visita", visitaKey, service);
                    for (Element paziente : target) {
                        newPazAdded = commonBean.createChild(newElementId.toString(), "CTC", "PazientiTraguardo", service);
                        commonBean.addMetadataValue(newPazAdded, "DatiPazientiTraguardo", "Paziente", paziente.getId(), service);
                    }
                }
            }
        }
    }

    public void fromMapToVocePazientiFattura(Element fattura, HashMap<String, VoceMonitoraggioFatturazione> map, String template, String tipologia, HashMap<String, String> cdcsDecodes, DocumentService service) throws Exception {
        Set<String> mapKeys;
        String newElementId;
        String newChildId;
        HashMap<Element, Integer> elements;
        HashMap<String, HashMap<String, Double>> cdcs;
        HashMap<String, String> dataCdc = new HashMap<String, String>();
        HashMap<String, Double> currCdc;

        VoceMonitoraggioFatturazione listOccorenzePrestazione;

        mapKeys = map.keySet();
        for (String key : mapKeys) {
            newElementId = commonBean.createChild(fattura.getId().toString(), fattura.getCreateUser(), "VocePazientiFattura", service).toString();
            listOccorenzePrestazione = map.get(key);
            cdcs = listOccorenzePrestazione.getCdcs();
            commonBean.addMetadataValue(newElementId, "DatiVoceFattura", "Tipologia", tipologia, service);
            commonBean.addMetadataValue(newElementId, "DatiPazientiFattura", "Descrizione", key, service);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "debug - new id " + newElementId);
            commonBean.addMetadataValue(newElementId, "DatiPazientiFattura", "NumPaz", listOccorenzePrestazione.getPazienti().size(), service);
            commonBean.addMetadataValue(newElementId, "DatiPazientiFattura", "Totale", listOccorenzePrestazione.getTotale().toString(), service);
            elements = listOccorenzePrestazione.getList();

            for (Element currElement : elements.keySet()) {

                newChildId = commonBean.createChild(newElementId, fattura.getCreateUser(), "LinkMonitoraggio", service).toString();
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "debug 2 - linko " + currElement.getId().toString() + " in new element: " + newChildId + " Prezzo: " + currElement.getFieldDataString(template, "Prezzo") + " template: " + template);
                commonBean.addMetadataValue(newChildId, "DatiLinkMonitoraggio", "Link", currElement.getId().toString(), service);
                commonBean.addMetadataValue(newChildId, "DatiLinkMonitoraggio", "Prezzo", currElement.getFieldDataString(template, "Prezzo"), service);
                commonBean.addMetadataValue(newChildId, "DatiLinkMonitoraggio", "Quantita", elements.get(currElement), service);
                commonBean.addMetadataValue(newChildId, "DatiLinkMonitoraggio", "Paziente", currElement.getParent().getParent().getId().toString(), service);
            }
        }
    }

    public void fromMapToVoceMonitoraggioFattura(Element fattura, HashMap<String, VoceMonitoraggioFatturazione> map, String template, String tipologia, HashMap<String, String> cdcsDecodes, DocumentService service) throws Exception {
        Set<String> mapKeys;
        String newElementId;
        String newChildId;
        HashMap<Element, Integer> elements;
        HashMap<String, HashMap<String, Double>> cdcs;
        HashMap<String, String> dataCdc = new HashMap<String, String>();
        HashMap<String, Double> currCdc;

        VoceMonitoraggioFatturazione listOccorenzePrestazione;

        mapKeys = map.keySet();
        for (String key : mapKeys) {
            newElementId = commonBean.createChild(fattura.getId().toString(), fattura.getCreateUser(), "VoceMonitoraggioFattura", service).toString();
            listOccorenzePrestazione = map.get(key);
            cdcs = listOccorenzePrestazione.getCdcs();
            commonBean.addMetadataValue(newElementId, "DatiVoceFattura", "Tipologia", tipologia, service);
            commonBean.addMetadataValue(newElementId, "DatiMonitoraggioFattura", "Descrizione", key, service);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "debug - new id " + newElementId);
            commonBean.addMetadataValue(newElementId, "DatiMonitoraggioFattura", "NumPaz", listOccorenzePrestazione.getPazienti().size(), service);
            commonBean.addMetadataValue(newElementId, "DatiMonitoraggioFattura", "NumPrestazioni", listOccorenzePrestazione.getNumeroPrestazioni().toString(), service);
            commonBean.addMetadataValue(newElementId, "DatiMonitoraggioFattura", "Totale", listOccorenzePrestazione.getTotale().toString(), service);
            commonBean.addMetadataValue(newElementId, "DatiMonitoraggioFattura", "SSN", listOccorenzePrestazione.getSsn(), service);
            commonBean.addMetadataValue(newElementId, "DatiMonitoraggioFattura", "Codice", listOccorenzePrestazione.getCodice(), service);
            commonBean.addMetadataValue(newElementId, "DatiMonitoraggioFattura", "TransferPrice", listOccorenzePrestazione.getTp(), service);
            String prestaCDC = cdcs.keySet().iterator().next();
            commonBean.addMetadataValue(newElementId, "DatiMonitoraggioFattura", "AttivitaCode", prestaCDC, service);
            commonBean.addMetadataValue(newElementId, "DatiMonitoraggioFattura", "AttivitaDecode", cdcsDecodes.get(prestaCDC), service);
            elements = listOccorenzePrestazione.getList();

            for (Element currElement : elements.keySet()) {

                newChildId = commonBean.createChild(newElementId, fattura.getCreateUser(), "LinkMonitoraggio", service).toString();
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "debug 2 - linko " + currElement.getId().toString() + " in new element: " + newChildId + " Prezzo: " + currElement.getFieldDataString(template, "Prezzo") + " template: " + template);
                commonBean.addMetadataValue(newChildId, "DatiLinkMonitoraggio", "Link", currElement.getId().toString(), service);
                commonBean.addMetadataValue(newChildId, "DatiLinkMonitoraggio", "Prezzo", currElement.getFieldDataString(template, "Prezzo"), service);
                commonBean.addMetadataValue(newChildId, "DatiLinkMonitoraggio", "Quantita", elements.get(currElement), service);
                commonBean.addMetadataValue(newChildId, "DatiLinkMonitoraggio", "Paziente", currElement.getParent().getParent().getId().toString(), service);
                try {
                    if (tipologia.equals("1")) {
                        String data = "";
                        String tpString = currElement.getFieldDataString("DatiMonPxT_MonTimePoint");
                        if (!tpString.isEmpty()) {
                            Element tp = service.getElement(tpString);
                            if (tp != null) {
                                data = tp.getFieldDataFormattedDates("DatiMonTimePoint", "DataVisita", "dd/MM/yyyy").get(0);
                            }
                        }

                        commonBean.addMetadataValue(newChildId, "DatiLinkMonitoraggio", "Prestazione", currElement.getFieldDataElement("DatiMonPxT", "TPxP").get(0).getFieldDataElement("tp-p", "Prestazione").get(0).getTitleString(), service);
                        commonBean.addMetadataValue(newChildId, "DatiLinkMonitoraggio", "OrdinePrestazione", currElement.getFieldDataElement("DatiMonPxT", "TPxP").get(0).getFieldDataElement("tp-p", "Prestazione").get(0).getFieldDataString("Prestazioni", "row"), service);
                        commonBean.addMetadataValue(newChildId, "DatiLinkMonitoraggio", "OrdineVisita", currElement.getFieldDataElement("DatiMonPxT", "TPxP").get(0).getFieldDataElement("tp-p", "TimePoint").get(0).getFieldDataString("TimePoint", "col"), service);
                        commonBean.addMetadataValue(newChildId, "DatiLinkMonitoraggio", "TimePoint", currElement.getFieldDataElement("DatiMonPxT", "TPxP").get(0).getFieldDataElement("tp-p", "TimePoint").get(0).getTitleString() + " " + data, service);
                    } else {

                        commonBean.addMetadataValue(newChildId, "DatiLinkMonitoraggio", "Prestazione", currElement.getFieldDataElement("DatiMonPxP", "BudgetLink").get(0).getTitleString(), service);
                        commonBean.addMetadataValue(newChildId, "DatiLinkMonitoraggio", "TimePoint", "n.a.", service);
                    }
                } catch (Exception ex) {
                    try {
                        if (tipologia.equals("1")) {
                            Element correzione = correggiSingleMonBudgetLink(currElement, null, service);
                            commonBean.addMetadataValue(newChildId, "DatiLinkMonitoraggio", "Prestazione", correzione.getFieldDataElement("tp-p", "Prestazione").get(0).getTitleString(), service);
                            commonBean.addMetadataValue(newChildId, "DatiLinkMonitoraggio", "OrdinePrestazione", correzione.getFieldDataElement("tp-p", "Prestazione").get(0).getFieldDataString("Prestazioni", "row"), service);
                            commonBean.addMetadataValue(newChildId, "DatiLinkMonitoraggio", "OrdineVisita", correzione.getFieldDataElement("tp-p", "TimePoint").get(0).getFieldDataString("TimePoint", "col"), service);
                            commonBean.addMetadataValue(newChildId, "DatiLinkMonitoraggio", "TimePoint", correzione.getFieldDataElement("tp-p", "TimePoint").get(0).getTitleString(), service);
                        } else {

                            commonBean.addMetadataValue(newChildId, "DatiLinkMonitoraggio", "Prestazione", currElement.getFieldDataElement("DatiMonPxP", "BudgetLink").get(0).getTitleString(), service);
                            commonBean.addMetadataValue(newChildId, "DatiLinkMonitoraggio", "TimePoint", "n.a.", service);
                        }
                    } catch (Exception ex2) {

                    }
                }
            }

            it.cineca.siss.axmr3.log.Log.debug(getClass(), "itero sui cdc che sono : " + String.valueOf(cdcs.size()));
            for (String cdc : cdcs.keySet()) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "cdc corrente : " + cdc + " - " + cdcsDecodes.get(cdc));
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "elemento padre cdc : " + String.valueOf(newElementId));
                currCdc = cdcs.get(cdc);
                dataCdc.put("CDCSummary_CDCCode", cdc);
                dataCdc.put("CDCSummary_CDCDecode", cdcsDecodes.get(cdc));
                dataCdc.put("CDCSummary_Prezzo", currCdc.get("TotalePrezzo").toString());
                dataCdc.put("CDCSummary_TransferPrice", currCdc.get("TotaleTransferPrice").toString());
                dataCdc.put("CDCSummary_SSN", currCdc.get("TotaleSSN").toString());
                commonBean.createChild(newElementId, fattura.getCreateUser(), "CDCMilestone", dataCdc, service);
            }
        }
    }

    //Metodo per importare i dispositivi medici tramite processo activiti(non usato)
    public void creaDispositivi() throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Long newChild;
        boolean recordPresente;

        Connection conn = dataSource.getConnection();
        String sql = "select progressivo_dm_ass,denominazione_commerciale from DM";
        PreparedStatement stmt = conn.prepareStatement(sql);
        ResultSet rset = stmt.executeQuery();
        int i = 0;

        while (rset.next()) {
            i++;
            String code = rset.getString("progressivo_dm_ass");
            String decode = rset.getString("denominazione_commerciale");
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "code=" + code + " decode=" + decode);

            newChild = commonBean.createChild("39970450", "GCONTINO", "DispositiviMedici", service);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "newChild=" + newChild);
            if (newChild != null) {
                commonBean.addMetadataValue(String.valueOf(newChild), "Base", "Nome", code, service);
                commonBean.addMetadataValue(String.valueOf(newChild), "Identity", "id", decode, service);
            }

            if (i >= 2) {
                i = 0;
                service.getTxManager().commitAndKeepAlive();
            }
        }
        conn.close();
        commonBean.closeDocumentService(service);

    }

    public void crontabRichiesteFattura(DelegateExecution execution) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Long newChild;
        LinkedList<Long> createdFatturazioni = new LinkedList<Long>();
        String mailTxt = "";

        execution.setVariable("mailBody", "");
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Inizia crontab");
        //TODO migliorare performance prendendo solo gli scheduling con stato iniziato e non terminati
        List<Element> elements = service.getDocDAO().getCriteriaList(service.getAllElementsByTypeCriteria("Fatturazione"));
        for (Element scheduling : elements) {
            newChild = crontabSingolaRichiestaFattura(scheduling, service);
            if (newChild != null) {
                createdFatturazioni.add(newChild);
            }
            makeSureSessionIsOpen(service);
        }

        if (createdFatturazioni.size() > 0) {
            mailTxt = "Sono state raggiunte " + createdFatturazioni.size() + " Milestone di fatturazione raggiungibili ai seguenti link:\n\n";
            for (Long created : createdFatturazioni) {
                mailTxt += "" + getBaseUrl() + "/app/documents/detail/" + created.toString() + "\n\n";
            }
        } else {
            mailTxt = "Nessuna nuova milestone";
        }

        execution.setVariable("mailBody", mailTxt);

        commonBean.closeDocumentService(service);
    }

    public Long crontabSingolaRichiestaFattura(Element scheduling, DocumentService service) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "crontab per " + scheduling.getId().toString());
        try {
            scheduling.getFieldDataString("StatoScheduling", "Iniziato");
        } catch (Exception ex) {
            scheduling = service.sync(scheduling);
        }

        if (!scheduling.getFieldDataString("StatoScheduling", "Iniziato").equals("1") || scheduling.getFieldDataString("StatoScheduling", "Terminato").equals("1")) {
            return null;
        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "prosegue crontab stato ok per " + scheduling.getId().toString());
        int conteggioMilestone = 0;
        Long newChild;
        MultiSessionTXManager txManager;
        String fatturazioneRule = scheduling.getFieldDataCode("scheduling", "ModalitaFatturazione");
        String periodRule = scheduling.getFieldDataCode("scheduling", "Periodicita");
        String visiteRule = scheduling.getFieldDataCode("scheduling", "TipologiaCalcolo");
        String numPazRule = scheduling.getFieldDataString("scheduling", "NumPaz");
        String percPazRule = scheduling.getFieldDataString("scheduling", "PercPaz");
        String totPaz = scheduling.getFieldDataString("InfoBudget", "Pazienti");
        List<Element> checkpoints = scheduling.getChildrenByType("TPFatt");
        Element centro = scheduling.getParent();
        List<Element> monitoraggi = centro.getChildrenByType("MonitoraggioAmministrativo");
        HashMap<String, String> data = new HashMap<String, String>();

        data.put("DatiFattura_Tipologia", "2###Rata");
        data.put("DatiRichiestaFatturazioneWF_MilestoneAutomatica", "1");

        if (monitoraggi.size() == 0) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "finisce crontab no pazienti per " + scheduling.getId().toString());
            return null;
        }

        if (isBillable(scheduling, monitoraggi, fatturazioneRule, periodRule, visiteRule, numPazRule, percPazRule, totPaz, checkpoints)) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "prosegue crontab is billable per " + scheduling.getId().toString());
            makeSureSessionIsOpen(service);
            try {
                if (!scheduling.getFieldDataString("StatoScheduling", "ConteggioMilestonCrontab").isEmpty()) {
                    conteggioMilestone = Integer.parseInt(scheduling.getFieldDataString("StatoScheduling", "ConteggioMilestonCrontab"));
                } else {
                    conteggioMilestone = 0;
                }
            } catch (Exception ex) {
                conteggioMilestone = 0;
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Errore nella conversione di conteggio milestone");
            }
            conteggioMilestone++;
            commonBean.addMetadataValue(scheduling, "StatoScheduling", "UltimaMilestoneCrontab", commonBean.sysdate(), service);
            commonBean.addMetadataValue(scheduling, "StatoScheduling", "ConteggioMilestonCrontab", String.valueOf(conteggioMilestone), service);
            newChild = commonBean.createChild(scheduling.getId().toString(), "CTC", "RichiestaFatturazione", data, service);
            makeSureSessionIsOpen(service);

            return newChild;
        } else {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "finisce crontab no billable per " + scheduling.getId().toString());
        }

        return null;
    }

    protected void makeSureSessionIsOpen(DocumentService service) {
        MultiSessionTXManager txManager = service.getTxManager();
        if (!txManager.getSessions().get("doc").isOpen()) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "La sessione è chiusa, la riapro");
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Apro la sessione 7 " + this.getClass().getCanonicalName());
            txManager.getSessions().put("doc", txManager.getSessionFactories().get("doc").openSession());
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Begin Transaction 13 " + this.getClass().getCanonicalName());
            txManager.getTxs().put("doc", txManager.getSessions().get("doc").beginTransaction());
        } else {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "La sessione è aperta, controllo la transazione");
            if (!txManager.getTxs().get("doc").isActive()) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "La transazione non è attiva 1");
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Begin Transaction 14 " + this.getClass().getCanonicalName());
                txManager.getTxs().put("doc", txManager.getSessions().get("doc").beginTransaction());
            } else {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "La transazione era a posto pulire codice");
            }
        }
    }

    public void createPassThrough(Element richiesta, DocumentService service) throws Exception {

        Element center = richiesta.getParent().getParent();
        Element budget = getBudgetChiuso(center, service);
        Element budgetStudio = getBudgetDefinitivo(budget, service);
        HashMap<String, String> data = new HashMap<String, String>();
        Collection<Element> folderPT = new LinkedList<Element>();
        if (budgetStudio.getType().getTypeId().equals("BudgetCTC")) {
            folderPT = budgetStudio.getChildrenByType("FolderPassthroughCTC").get(0).getChildren();
        } else {
            folderPT = budget.getChildrenByType("FolderPassthroughCTC").get(0).getChildren();
        }
        for (Element currPT : folderPT) {
            data.put("DatiPassThroughFattura_Descrizione", currPT.getFieldDataString("Base", "Nome"));
            data.put("DatiPassThroughPrezzo_Prezzo", currPT.getFieldDataString("Costo", "Prezzo"));
            data.put("DatiVoceFattura_Tipologia", "4");
            commonBean.createChild(richiesta, null, "VocePassThroughFattura", data, service);
        }

    }

    public void preparaRichiestaFattura(String elementId) throws Exception {
        try {
            DocumentService service = commonBean.getDocumentService();
            Element el = service.getElement(Long.parseLong(elementId));
            Element scheduling = el.getParent();
            List<Object> data;
            String valoreAssoluto = "";
            String valorePercentuale = "";
            String tipoFatt = el.getFieldDataCodes("DatiFattura", "Tipologia").get(0);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "preparaRichiestaFattura " + tipoFatt);
            List<Element> toCopy = new LinkedList<Element>();
            Element prestFatt;
            Element prestFatt1;
            String childIdTmp;
            HashMap<String, VoceMonitoraggioFatturazione> voceSchedulingFatturaMap = new HashMap<String, VoceMonitoraggioFatturazione>();
            String nomePrestazione = "";
            String pretazioneFlowchart = "";
            String cdcCode = "";
            String cdcDecode = "";
            String transferPrice = "";
            String SSN = "";
            HashMap<String, String> dataCdc = new HashMap<String, String>();
            VoceMonitoraggioFatturazione voce;

            commonBean.addMetadataValue(elementId, "DatiRichiestaFatturazioneWF", "DataCreazione", commonBean.sysdate(), service);

            commonBean.copyData(scheduling, elementId, "scheduling", "DestinatarioRagSoc", "DatiFatturaScheduling", "DestinatarioRagSoc", service);
            commonBean.copyData(scheduling, elementId, "scheduling", "DestinatarioPIVA", "DatiFatturaScheduling", "DestinatarioPIVA", service);
            commonBean.copyData(scheduling, elementId, "scheduling", "DestinatarioIndirizzo", "DatiFatturaScheduling", "DestinatarioIndirizzo", service);

            //TOSCANA-163
            commonBean.copyData(scheduling, elementId, "scheduling", "FatturazioneRagSoc", "DatiFatturaScheduling", "FatturazioneRagSoc", service);
            commonBean.copyData(scheduling, elementId, "scheduling", "FatturazionePIVA", "DatiFatturaScheduling", "FatturazionePIVA", service);
            commonBean.copyData(scheduling, elementId, "scheduling", "FatturazioneIndirizzo", "DatiFatturaScheduling", "FatturazioneIndirizzo", service);

            //Copio i valori assoluti e perc nel nuovo template
            if (tipoFatt.equals("1")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "acconto");
                data = scheduling.getfieldData("scheduling", "ValoreAssoluto");
                if (data != null && data.size() > 0) {
                    valoreAssoluto = data.get(0).toString();
                }

                data = scheduling.getfieldData("scheduling", "ValorePerc");
                if (data != null && data.size() > 0) {
                    valorePercentuale = data.get(0).toString();
                }

                commonBean.copyData(scheduling, elementId, "scheduling", "StartUpRimborsabile", "DatiFatturaScheduling", "StartUpRimborsabile", service);
                commonBean.addMetadataValue(elementId, "DatiFatturaScheduling", "AccontoAssoluto", valoreAssoluto, service);
                commonBean.addMetadataValue(elementId, "DatiFatturaScheduling", "AccontoPercentuale", valorePercentuale, service);
            }
            if (tipoFatt.equals("2") || tipoFatt.equals("3")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "rata");
                preparaRichiestaFatturaDaMon(el, service, tipoFatt);
            }
            if (!tipoFatt.equals("4")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "altra fattura");
                for (Element child : scheduling.getChildrenByType("PrestazioniFatt")) {
                    if (child.getfieldData("DatiPrestazioniFatt", "AccontoRataSaldo") != null && child.getfieldData("DatiPrestazioniFatt", "AccontoRataSaldo").size() > 0) {
                        if (child.getfieldData("DatiPrestazioniFatt", "AccontoRataSaldo").get(0).equals(tipoFatt)) {

                            prestFatt = prestFatt1 = (Element) child.getfieldData("DatiPrestazioniFatt", "PrestazioneBudget").get(0);
                            nomePrestazione = prestFatt.getFieldDataString("Base", "Nome");
                            String prezzo = "0";

                            toCopy.add(child);
                            childIdTmp = String.valueOf(commonBean.createChild(elementId, el.getCreateUser(), "VoceSchedulingFattura", service));
                            if (prestFatt.getType().getTypeId().equals("PrezzoPrestazione")) {
                                prestFatt = (Element) prestFatt.getfieldData("PrezzoFinale", "Prestazione").get(0);

                                if (prestFatt1.getfieldData("PrezzoFinale", "Prezzo") != null && !prestFatt1.getFieldDataString("PrezzoFinale", "Prezzo").isEmpty()) {
                                    prezzo = prestFatt1.getFieldDataString("PrezzoFinale", "Prezzo");
                                    commonBean.copyData(prestFatt1, childIdTmp, "PrezzoFinale", "Prezzo", "DatiSchedulingFattura", "Prezzo", service);

                                } else {
                                    prezzo = prestFatt.getFieldDataString("Costo", "TransferPrice");
                                    commonBean.copyData(prestFatt, childIdTmp, "Costo", "TransferPrice", "DatiSchedulingFattura", "Prezzo", service);
                                }
                                commonBean.addMetadataValue(childIdTmp, "DatiSchedulingFattura", "AttivitaCode", prestFatt.getFieldDataCode("Prestazioni", "Attivita"), service);
                                commonBean.addMetadataValue(childIdTmp, "DatiSchedulingFattura", "AttivitaDecode", prestFatt.getFieldDataDecode("Prestazioni", "Attivita"), service);

                            } else if (prestFatt.getType().getTypeId().equals("CostoAggiuntivo")) {
                                prezzo = prestFatt1.getFieldDataString("CostoAggiuntivo", "Costo");
                                commonBean.copyData(prestFatt1, childIdTmp, "CostoAggiuntivo", "Costo", "DatiSchedulingFattura", "Prezzo", service);
                                commonBean.addMetadataValue(childIdTmp, "DatiSchedulingFattura", "AttivitaCode", prestFatt1.getFieldDataCode("CostoAggiuntivo", "Tipologia"), service);
                                commonBean.addMetadataValue(childIdTmp, "DatiSchedulingFattura", "AttivitaDecode", prestFatt1.getFieldDataDecode("CostoAggiuntivo", "Tipologia"), service);
                            } else {
                                prezzo = prestFatt1.getFieldDataString("Costo", "Prezzo");
                                commonBean.copyData(prestFatt1, childIdTmp, "Costo", "Prezzo", "DatiSchedulingFattura", "Prezzo", service);
                                commonBean.addMetadataValue(childIdTmp, "DatiSchedulingFattura", "AttivitaCode", prestFatt1.getFieldDataCode("Prestazioni", "Attivita"), service);
                                commonBean.addMetadataValue(childIdTmp, "DatiSchedulingFattura", "AttivitaDecode", prestFatt1.getFieldDataDecode("Prestazioni", "Attivita"), service);
                            }
                            //cdcCode=prestFatt.getFieldDataString("Prestazioni", "CDCCode");
                            //cdcDecode=prestFatt.getFieldDataString("Prestazioni","CDC");
                            if (prestFatt.getType().getTypeId().equals("CostoAggiuntivo")) {
                                cdcCode = prestFatt1.getFieldDataCode("CostoAggiuntivo", "Tipologia");
                                cdcDecode = prestFatt1.getFieldDataDecode("CostoAggiuntivo", "Tipologia");
                            } else {
                                cdcCode = prestFatt.getFieldDataCode("Prestazioni", "Attivita");
                                cdcDecode = prestFatt.getFieldDataDecode("Prestazioni", "Attivita");
                            }
                            transferPrice = prestFatt.getFieldDataString("Costo", "TransferPrice");
                            if (transferPrice.isEmpty()) {
                                transferPrice = prestFatt.getFieldDataString("Costo", "Costo");
                            }
                            if (transferPrice.isEmpty()) {
                                transferPrice = "0";
                            }
                            commonBean.copyData(child, childIdTmp, "DatiPrestazioniFatt", "Gruppo", "DatiSchedulingFattura", "Gruppo", service);
                            commonBean.copyData(child, childIdTmp, "DatiPrestazioniFatt", "Rimborso", "DatiSchedulingFattura", "Rimborsabile", service);
                            if (prestFatt.getType().getTypeId().equals("CostoAggiuntivo")) {
                                commonBean.copyData(prestFatt, childIdTmp, "CostoAggiuntivo", "OggettoPrincipale", "DatiSchedulingFattura", "Descrizione", service);
                            } else {
                                commonBean.copyData(prestFatt, childIdTmp, "Base", "Nome", "DatiSchedulingFattura", "Descrizione", service);
                            }
                            commonBean.addMetadataValue(childIdTmp, "DatiSchedulingFattura", "Link", child.getId().toString(), service);
                            commonBean.addMetadataValue(childIdTmp, "DatiVoceFattura", "Tipologia", "3", service);

                            //Aggiungo CDC

                            dataCdc.put("CDCSummary_CDCCode", cdcCode);
                            dataCdc.put("CDCSummary_CDCDecode", cdcDecode);
                            dataCdc.put("CDCSummary_Prezzo", prezzo);
                            dataCdc.put("CDCSummary_TransferPrice", transferPrice);

                            commonBean.createChild(childIdTmp, el.getCreateUser(), "CDCMilestone", dataCdc, service);

                        }
                    }
                }

            }

            if (tipoFatt.equals("4")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "passThrough");
                createPassThrough(el, service);
            }

            commonBean.closeDocumentService(service);
        } catch (Exception ex) {
            Logger.getLogger(this.getClass()).error(ex.getMessage(), ex);
            throw new AxmrGenericException(ex.getMessage());
        }
    }

    public String getElementIdCentro(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();

        String elementIdCentro = getElementIdCentro(elementId, service);

        commonBean.closeDocumentService(service);

        return elementIdCentro;

    }

    public String getElementIdCentro(String elementId, DocumentService service) throws Exception {

        Element el = service.getElement(Long.parseLong(elementId));
        String elementIdCentro = "";

        if (el.getTypeName().equals("Studio")) {
            commonBean.closeDocumentService(service);
            return elementIdCentro;
        }
        if (el.getTypeName().equals("Centro")) {
            elementIdCentro = elementId;
        } else {
            return getElementIdCentro(el.getParent().getId().toString(), service);
        }

        return elementIdCentro;
    }

    /*
    public String getElementIdCentro(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el=service.getElement(Long.parseLong(elementId));
        String elementIdCentro="";

        if(el.getTypeName().equals("Studio")){
            commonBean.closeDocumentService(service);
            return elementIdCentro;
        }
        if(el.getTypeName().equals("Centro")){
            elementIdCentro=elementId;
        }else{
            return getElementIdCentro(el.getParent().getId().toString());
        }

        commonBean.closeDocumentService(service);
        return elementIdCentro;
    }
    */

    public String mailInfoCentroByChild(String elementId) throws Exception {
        return mailInfoCentro(getElementIdCentro(elementId), "");
    }

    public String mailInfoCentroByChild(String elementId, String anchor) throws Exception {
        return mailInfoCentro(getElementIdCentro(elementId), anchor);
    }

    public String mailInfoCentro(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        String infoMail = mailInfoCentro(elementId, service, null);
        commonBean.closeDocumentService(service);

        return infoMail;
    }
   
    public String mailInfoCentro(String elementId, String anchor) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        String infoMail = mailInfoCentro(elementId, service, anchor);
        commonBean.closeDocumentService(service);

        return infoMail;
    }

    public String mailInfoCentro(String elementId, DocumentService service) throws Exception {
        String infoMail = mailInfoCentro(elementId, service, null);
        commonBean.closeDocumentService(service);

        return infoMail;
    }

    public String mailInfoCentro(String elementId, DocumentService service, String anchor) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "mailInfoCentro 2 parametri con id = " + elementId);
        Element el = service.getElement(Long.parseLong(elementId));

        Long idStudio;
        String sponsor = "";
        String croString = "";
        String codice = "";
        String titolo = "";
        String DenStruttura = "";
        String DenOspedalePresidio = "";
        String DenDipartimento = "";
        String DenUnitaOperativa = "";
        String DenPrincInv = "";

        idStudio = Long.valueOf(el.getParent().getfieldData("UniqueIdStudio", "id").get(0).toString());
        if (el.getParent().getFieldDataElement("datiPromotore", "promotore") != null && el.getParent().getFieldDataElement("datiPromotore", "promotore").size() > 0) {
            Element sp = el.getParent().getFieldDataElement("datiPromotore", "promotore").get(0);
            sponsor = sp.getfieldData("DatiPromotoreCRO", "denominazione").get(0).toString();
        }
        if (el.getParent().getFieldDataElement("datiCRO", "denominazione") != null && el.getParent().getFieldDataElement("datiCRO", "denominazione").size() > 0) {
            Element cro = el.getParent().getFieldDataElement("datiCRO", "denominazione").get(0);
            croString = cro.getfieldData("DatiPromotoreCRO", "denominazione").get(0).toString();
        }
        if (el.getParent().getfieldData("IDstudio", "CodiceProt") != null && el.getParent().getfieldData("IDstudio", "CodiceProt").size() > 0) {
            codice = el.getParent().getfieldData("IDstudio", "CodiceProt").get(0).toString();
        }
        if (el.getParent().getfieldData("IDstudio", "TitoloProt") != null && el.getParent().getfieldData("IDstudio", "TitoloProt").size() > 0) {
            titolo = el.getParent().getfieldData("IDstudio", "TitoloProt").get(0).toString();
        }
        DenStruttura = el.getFieldDataDecode("IdCentro", "Struttura");
        DenOspedalePresidio = el.getFieldDataDecode("IdCentro", "OspedalePresidio");
        DenDipartimento = el.getFieldDataDecode("IdCentro", "Dipartimento");
        DenUnitaOperativa = el.getFieldDataDecode("IdCentro", "UO");
        DenPrincInv = el.getFieldDataDecode("IdCentro", "PINomeCognome");
        String url = getBaseUrl() + "/app/documents/detail/" + el.getId() + "";
        if (anchor != null && !anchor.isEmpty()) {
            url += "#" + anchor;
        }

        String text =
                "ID studio: " + idStudio +
                        "\nTitolo: " + titolo +
                        "\nStruttura: " + DenStruttura +
                        "\nOspedale/Presidio: " + DenOspedalePresidio +
                        "\nDipartimento: " + DenDipartimento +
                        "\nUnita' operativa: " + DenUnitaOperativa +
                        "\nPrincipal Investigator: " + DenPrincInv +
                        "\n\nE' possibile visualizzare le informazioni al seguente link:\n\n" +
                        url;

        it.cineca.siss.axmr3.log.Log.debug(getClass(), text);

        return text;

    }

    public Long creaFeasibilityServizi(String elementId) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "INIZIO creaFeasibilityServizi ");
        Long feasibilityServiziId = null;
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        feasibilityServiziId = commonBean.createChild(elementId, el.getCreateUser(), "FeasibilityServizi", service);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "FINE creaFeasibilityServizi - feasibilityServiziId : " + feasibilityServiziId);
        return feasibilityServiziId;
    }

    public String mailInfoStudio(String elementId, String uniqueId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));

        String idUnivoco = "";
        String codProt = "";
        String acronimo = "";
        String titolo = "";
        String titoloIng = "";
        String text = "";

        if (el.getfieldData("IDstudio", "CodiceProt") != null && el.getfieldData("IDstudio", "CodiceProt").size() > 0) {
            codProt = el.getfieldData("IDstudio", "CodiceProt").get(0).toString();
        }
        if (el.getfieldData("IDstudio", "Acronimo") != null && el.getfieldData("IDstudio", "Acronimo").size() > 0) {
            acronimo = el.getfieldData("IDstudio", "Acronimo").get(0).toString();
        }
        if (el.getfieldData("IDstudio", "TitoloProt") != null && el.getfieldData("IDstudio", "TitoloProt").size() > 0) {
            titolo = el.getfieldData("IDstudio", "TitoloProt").get(0).toString();
        }
        if (el.getfieldData("IDstudio", "TitoloProtIng") != null && el.getfieldData("IDstudio", "TitoloProtIng").size() > 0) {
            titoloIng = el.getfieldData("IDstudio", "TitoloProtIng").get(0).toString();
        }

        if (uniqueId != null && !uniqueId.isEmpty() && !uniqueId.equals("")) {
            idUnivoco = "ID studio: " + uniqueId;
        }

        text = idUnivoco +
                "\nCodice protocollo: " + codProt +
                "\nAcronimo: " + acronimo +
                "\nTitolo dello studio: " + titolo +
                "\nTitolo dello studio in inglese: " + titoloIng;

        commonBean.closeDocumentService(service);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), text);

        return text;

    }

    public String mailAvvenutoRibaltamento(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));

        String idCentro = "";


        String bodyMail = "";

        String idFattura = el.getId().toString();
        idCentro = el.getParent().getParent().getParent().getParent().getId().toString();

        String baseUrl = getBaseUrl();
        String urlFattura = baseUrl + "/app/documents/detail/" + idFattura;


        bodyMail = "Gentile utente,\n la ragioneria ha effettuato il riversamento consultabile al seguente link:\n\n";
        bodyMail += "Visualizza riversamento: " + urlFattura + "\n\n";
        bodyMail += mailInfoCentro(idCentro) + "\n\n";

        commonBean.closeDocumentService(service);
        return bodyMail;
    }

    public String mailRichiestaRibaltamento(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));

        String idCentro = "";


        String bodyMail = "";

        String idFattura = el.getId().toString();
        idCentro = el.getParent().getParent().getParent().getParent().getId().toString();

        String baseUrl = getBaseUrl();
        String urlFattura = baseUrl + "/app/documents/detail/" + idFattura;


        bodyMail = "Gentile utente,\n il CTC ha richiesto il riversamento consultabile al seguente link:\n\n";
        bodyMail += "Visualizza riversamento: " + urlFattura + "\n\n";
        bodyMail += mailInfoCentro(idCentro) + "\n\n";

        commonBean.closeDocumentService(service);
        return bodyMail;
    }

    public String mailInfoFattura(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));

        String idCentro = "";
        String totaleFattura = "";
        String tipologiaFattura = "";
        String bodyMail = "";

        String idFattura = el.getId().toString();
        idCentro = el.getParent().getParent().getParent().getId().toString();

        String baseUrl = getBaseUrl();
        String urlFattura = baseUrl + "/app/documents/detail/" + idFattura;

        totaleFattura = el.getFieldDataString("DatiFatturaWF", "realeFattura");
        if (totaleFattura == null || totaleFattura.isEmpty()) {
            totaleFattura = "0";
        }

        tipologiaFattura = el.getFieldDataDecode("DatiFattura", "Tipologia");

        bodyMail = "Gentile utente,\n il CTC ha inserito la fattura ID " + idFattura + " di " + tipologiaFattura + " per un totale di euro " + totaleFattura + " consultabile al seguente link:\n\n";
        bodyMail += "Visualizza fattura: " + urlFattura + "\n\n";
        bodyMail += mailInfoCentro(idCentro) + "\n\n";

        commonBean.closeDocumentService(service);
        return bodyMail;
    }

    public String mailCTCdaParere(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        Element elCentro = service.getElement(getElementIdCentro(elementId));
        String mail = "";
        String mailPI = el.getParent().getFieldDataString("IdCentro_PIemail");
        //MAIL AL PI AL CTC E AL PROMOTORE (che ha inserito lo studio)
        IUser userInstance = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();//STSANSVIL-506 aggiungo anche utente corrente
        mail = mailPI + "," + mailCTC(elCentro.getId().toString()) + "," + mailPromotore(elCentro.getParent().getId().toString())+","+userInstance.getEmail();
        mail=mail.replace(",,",",").replace(" ","");//pulisco gli indirizzi
        return mail;
    }

    public String mailCTCdaParereBody(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        Connection conn = dataSource.getConnection();
        String esistoParere = el.getFieldDataDecode("ParereCe", "esitoParere");
        String body = "E' stato inviato il parere da parte della Segreteria del Comitato Etico con esito \"" + esistoParere + "\" per lo studio/centro:\n" + mailInfoCentroByChild(elementId);
        return body;
    }

    public String mailCTCdaIstruttoria(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element elCentro = service.getElement(getElementIdCentro(elementId));
        String mail = "";
        String mailPI = elCentro.getFieldDataString("IdCentro_PIemail");
        //MAIL AL PI AL CTC E AL PROMOTORE (che ha inserito lo studio)
        IUser userInstance = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();//STSANSVIL-506 aggiungo anche utente corrente
        mail = mailPI + "," + mailCTC(elCentro.getId().toString()) + "," + mailPromotore(elCentro.getParent().getId().toString())+", "+userInstance.getEmail();
        mail=mail.replace(",,",",").replace(" ","");//pulisco gli indirizzi
        return mail;
    }

    public String mailCTCdaIstruttoriaBody(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        Connection conn = dataSource.getConnection();
        String esistoIstruttoria = el.getFieldDataCode("IstruttoriaCE_DocCompleta").equals("1") ? "positivo" : "negativo";
        String body = "E' stata inviata l'istruttoria da parte della Segreteria del Comitato Etico con esito \"" + esistoIstruttoria + "\" per lo studio/centro:\n" + mailInfoCentroByChild(elementId);
        return body;
    }

    public String mailCTCAvvioCentro(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element elCentro = service.getElement(getElementIdCentro(elementId));
        String mail = "";
        String mailPI = elCentro.getFieldDataString("IdCentro_PIemail");
        //MAIL AL PI AL CTC E SEGR CE
        IUser userInstance = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();//STSANSVIL-506 aggiungo anche utente corrente
        mail = mailPI + "," + mailCTC(elCentro.getId().toString()) + "," + mailSegrCE(elCentro.getId().toString())+", "+userInstance.getEmail();
        mail=mail.replace(",,",",").replace(" ","");//pulisco gli indirizzi
        return mail;
    }

    public String mailCTCAvvioCentroBody(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        Connection conn = dataSource.getConnection();
        String dataApertura = el.getFieldDataFormattedDates("DatiAvvioCentro", "dataAperturaCentro", "dd/MM/yyyy").get(0);

        String body = "E' stata inserita la seguente data di apertura centro " + dataApertura + " per lo studio/centro:\n" + mailInfoCentroByChild(elementId);
        return body;
    }

    public String mailCTCChiusuraCentro(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element elCentro = service.getElement(getElementIdCentro(elementId));
        String mail = "";
        String mailPI = elCentro.getFieldDataString("IdCentro_PIemail");
        //MAIL AL PI AL CTC E SEGR CE
        IUser userInstance = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();//STSANSVIL-506 aggiungo anche utente corrente
        mail = mailPI + "," + mailCTC(elCentro.getId().toString()) + "," + mailSegrCE(elCentro.getId().toString())+", "+userInstance.getEmail();
        mail=mail.replace(",,",",").replace(" ","");//pulisco gli indirizzi
        return mail;
    }

    public String mailCTCChiusuraCentroBody(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        Connection conn = dataSource.getConnection();
        String dataChiusura = el.getFieldDataFormattedDates("DatiChiusuraCentro", "dataConclusioneCentro", "dd/MM/yyyy").get(0);
        ;
        String body = "E' stata inserita la seguente data di chiusura centro " + dataChiusura + " per lo studio/centro:\n" + mailInfoCentroByChild(elementId);
        return body;
    }

    public String mailCTCdaContrattoDG(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        Element elCentro = service.getElement(getElementIdCentro(elementId));
        String mail = "";
        String mailPI = elCentro.getFieldDataString("IdCentro_PIemail");
        IUser userInstance = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();//STSANSVIL-506 aggiungo anche utente corrente
        mail = mailPI + "," + mailCTC(elCentro.getId().toString()) + "," + mailSegrCE(elCentro.getId().toString()) + "," + mailPromotore(elCentro.getParent().getId().toString())+", "+userInstance.getEmail();
        mail=mail.replace(",,",",").replace(" ","");//pulisco gli indirizzi
        return mail;
    }

    public String mailCTCdaContrattoDGBody(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        Connection conn = dataSource.getConnection();
        String body = "E' stata inserita la firma del contratto da parte del DG o suo delegato per lo studio/centro::\n" + mailInfoCentroByChild(elementId);
        return body;
    }

    public String mailCTCRichiestaSponsor(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        Connection conn = dataSource.getConnection();
        String mail = "";
        //MAIL A PI, CTC e SEGRETERIA CE afferenti al centro
        IUser userInstance = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();//STSANSVIL-506 aggiungo anche utente corrente
        String mailPI = el.getFieldDataString("IdCentro_PIemail");
        mail = mailPI;
        if(!mailCTC(elementId).isEmpty()){
            mail+= "," + mailCTC(elementId);
        }
        if(!mailSegrCE(elementId).isEmpty()) {
            mail+= "," + mailSegrCE(elementId);
        }
        if(!userInstance.getEmail().isEmpty()){
            mail+=","+userInstance.getEmail();
        }

        mail = mail.replace(",,",",").replace(" ","");//pulisco gli indirizzi
        return mail;
    }

    public String mailCTCFattPI(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        Connection conn = dataSource.getConnection();
        String mail = "";
        //MAIL A  CTC e SEGRETERIA CE afferenti al centro
        String mailPI = el.getFieldDataString("IdCentro_PIemail");
        IUser userInstance = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();//STSANSVIL-506 aggiungo anche utente corrente
        mail = mailPI;
        if(!mailCTC(elementId).isEmpty()){
            mail+= "," + mailCTC(elementId);
        }
        if(!mailSegrCE(elementId).isEmpty()) {
            mail+= "," + mailSegrCE(elementId);
        }
        if(!userInstance.getEmail().isEmpty()){
            mail+=","+userInstance.getEmail();
        }
        mail = mail.replace(",,",",").replace(" ","");//pulisco gli indirizzi
        return mail;
    }

    public String mailCTCFattAz(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        Connection conn = dataSource.getConnection();
        String mail = "";
        //MAIL A PI e SEGRETERIA CE afferenti al centro
        String mailPI = el.getFieldDataString("IdCentro_PIemail");
        IUser userInstance = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();//STSANSVIL-506 aggiungo anche utente corrente
        mail = mailPI + "," + mailSegrCE(elementId)+", "+userInstance.getEmail();
        mail = mail.replace(",,",",").replace(" ","");//pulisco gli indirizzi
        return mail;
    }

    public String mailCTC(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        Connection conn = dataSource.getConnection();
        String strutturaCode = "";
        String mail = "";
        if (el.getTypeName().equals("Centro")) {
            strutturaCode = el.getFieldDataCode("IdCentro_Struttura");
            mail = mailByProfiloEStruttura("CTC", strutturaCode);
        }
        if (mail.equals("")) {
            mail = getEmail("ALIAS_CTC");
        }

        commonBean.closeDocumentService(service);
        return mail;
    }

    /**
     * @param elementId elemento di Tipo Studio
     * @return mail dell'utente di profilo promotore *se* ha inserito lo studio
     * @throws Exception
     */
    public String mailPromotore(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        String mail = "";
        Connection conn = dataSource.getConnection();
        if (el.getTypeName().equals("Studio")) {
            //RESTITUISCO LA MAIL DEll'UTENTE CON PROFILO PROMOTORE SE E' STATO LUI A CREARE LO STUDIO.
            String sql="SELECT ana.email, " +
                    " ana.userid, " +
                    " sp.code profileCode, " +
                    " sp.study_prefix " +
                    " FROM " +
                    " ana_utenti_1 ana, " +
                    " users_profiles up, " +
                    " studies_profiles sp, " +
                    " utenti u " +
                    " WHERE " +
                    " ana.userid         = u.userid " +
                    " AND ana.userid    = up.userid " +
                    " AND up.profile_id   = sp.id " +
                    " AND sp.study_prefix = 'CRMS' " +
                    " AND up.active       = 1 " +
                    " AND sp.active       = 1 " +
                    " AND u.abilitato     = 1 " +
                    " AND ana.userid=? " +
                    " and sp.code='SP' ";
            it.cineca.siss.axmr3.log.Log.info(getClass(), sql);
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, el.getCreateUser());
            ResultSet rset = stmt.executeQuery();

            while (rset.next()) {
                mail += "," + rset.getString(1);
            }
        }
        if(mail.length()>0) {
            mail = mail.substring(1);//tolgo prima virgola
        }
        conn.close();
        commonBean.closeDocumentService(service);

        return mail;
    }

    public String MailCTCFattAzBody(String elementId, String validita) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        String esito = validita.split("###")[1];
        String body = "E' stata chiusa la valutazione aziendale con esito \"" + esito + "\" da parte dell'Ufficio Ricerca per lo studio/centro:\n" +
                mailInfoCentro(elementId, "FeasibilityAreaME-tab2");
        return body;
    }

    public String mailByProfiloEStruttura(String profile, String struttura) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Connection conn = dataSource.getConnection();
        String sql1 = "SELECT ana.email," +
                "  ana.userid," +
                "  s.code strutturaCode," +
                "  s.descr," +
                "  s.pi," +
                "  s.country," +
                "  s.d_country," +
                "  sp.code profileCode," +
                "  sp.study_prefix" +
                " FROM users_sites us," +
                "  ana_utenti_1 ana," +
                "  sites s," +
                "  users_profiles up," +
                "  studies_profiles sp," +
                "  utenti u" +
                " WHERE ana.userid = us.userid" +
                " AND ana.userid         = u.userid" +
                " AND s.id         = us.site_id" +
                " AND ana.userid    = up.userid" +
                " AND up.profile_id   = sp.id" +
                " AND sp.study_prefix = 'CRMS'" +
                " AND up.active       = 1" +
                " AND sp.active       = 1" +
                " AND u.abilitato     = 1"+
                " and s.code=?" +
                " and sp.code=?";
        it.cineca.siss.axmr3.log.Log.debug(getClass(), sql1);
        PreparedStatement stmt = conn.prepareStatement(sql1);
        stmt.setString(1, struttura);
        stmt.setString(2, profile);
        ResultSet rset = stmt.executeQuery();

        String mail = "";
        while (rset.next()) {
            mail += "," + rset.getString("email");
        }
        if (mail.equals("")) {
            mail = getEmail("ALIAS_CTC");
        }
        conn.close();
        commonBean.closeDocumentService(service);
        mail = cleanAddresses(mail);
        return mail;
    }

    public String mailCTC() throws Exception {
        Connection conn = dataSource.getConnection();
        String sql1 = "select email from ana_utenti_1 where userid='ALIAS_CTC'";
        it.cineca.siss.axmr3.log.Log.debug(getClass(), sql1);
        PreparedStatement stmt = conn.prepareStatement(sql1);
        ResultSet rset = stmt.executeQuery();

        String mail = "";
        while (rset.next()) {
            mail += rset.getString("email") + ",";
        }
        conn.close();
        mail = cleanAddresses(mail);
        return mail;

    }

    public String mailSR(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        Connection conn = dataSource.getConnection();
        //Element el=service.getElement(Long.parseLong(elementId));
        //Long idStudio= (Long) el.getParent().getfieldData("UniqueIdStudio", "id").get(0);
        String sql1 = "select email from ana_utenti_1 where userid='ALIAS_SR'";
        it.cineca.siss.axmr3.log.Log.debug(getClass(), sql1);
        PreparedStatement stmt = conn.prepareStatement(sql1);
        ResultSet rset = stmt.executeQuery();

        String mail = "";
        while (rset.next()) {
            mail += rset.getString("email") + ",";
        }
        conn.close();
        commonBean.closeDocumentService(service);
        mail = cleanAddresses(mail);
        return mail;

    }

    public String mailUR() throws Exception {
        Connection conn = dataSource.getConnection();
        String sql1 = "select email from ana_utenti_1 where userid='ALIAS_UR'";
        it.cineca.siss.axmr3.log.Log.debug(getClass(), sql1);
        PreparedStatement stmt = conn.prepareStatement(sql1);
        ResultSet rset = stmt.executeQuery();

        String mail = "";
        while (rset.next()) {
            mail += rset.getString("email") + ",";
        }
        conn.close();
        mail = cleanAddresses(mail);
        return mail;
    }

    public String mailSuperSi() throws Exception {

        String mailSR = "";
        String mailCE = "";

        mailSR = getEmail("ALIAS_SR");
        //mailCE=getEmail("ALIAS_SEGR_CE");

        String mail = mailSR + mailCE;

        return mail;

    }

    //quando viene chiusa fattibilità da CTC invia mail a utenti segreteria CE coinvolti nello studio (chiamato da wf "Chiudi feasibility locale e invia a CTC" )
    public String mailSegrCE(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        Connection conn = dataSource.getConnection();
        String strutturaCode = "";
        String mail = "";
        if (el.getTypeName().equals("Centro")) {
            strutturaCode = el.getFieldDataCode("IdCentro_Struttura");
            mail = mailByProfiloEStruttura("SEGRETERIA", strutturaCode);
        }
        if (mail.equals("")) {
            mail = getEmail("ALIAS_CTC");
        }
        commonBean.closeDocumentService(service);
        return mail;
    }

    public String mailSegrCEOld(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        //Element el=service.getElement(Long.parseLong(elementId));
        Connection conn = dataSource.getConnection();
        Element el = service.getElement(Long.parseLong(elementId));
        Integer idCentro = Integer.valueOf(el.getfieldData("IdCentro", "Struttura").get(0).toString().split("###")[0]);
        String sql1 = "select email from ana_utenti_2 where profilo='SGR' and id_ce=(select centro from ce_elenco_centriloc where id=?)";
        it.cineca.siss.axmr3.log.Log.debug(getClass(), sql1);
        PreparedStatement stmt = conn.prepareStatement(sql1);
        stmt.setInt(1, idCentro);
        ResultSet rset = stmt.executeQuery();

        String mail = "";
        String comma = ",";
        boolean need_comma = false;
        while (rset.next()) {
            String my_mail = rset.getString("email");
            if (my_mail != null && !my_mail.isEmpty()) {
                if (need_comma) {
                    mail += comma;
                }
                mail += my_mail;
                need_comma = true;
            }
        }
        if (mail.equals("")) mail = getEmail("ALIAS_CTC");
        mail = getEmail("ALIAS_CTC");//TODO: per ora override mail SIRER-33
        commonBean.closeDocumentService(service);
        mail = cleanAddresses(mail);
        return mail;
    }

    //TOSCANA-174 copiato da gemelli mail arruolamento primo paziente
    public String mailArrPrimoPaz(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element elArrPrimoPaz = service.getElement(elementId);
        Element elCentro = elArrPrimoPaz.getParent();
        String idCentro = elCentro.getId().toString();

        String dataAperturaCentro = elArrPrimoPaz.getFieldDataFormattedDates("DatiArrPrimoPaz", "dataAperturaCentro", "dd/MM/yyyy").get(0);
        String bodyMail = "E' stata inserita la seguente data di apertura: " + dataAperturaCentro + " nel centro: \n\n";

        bodyMail += mailInfoCentro(idCentro);

        commonBean.closeDocumentService(service);
        return bodyMail;
    }

    public String mailArrPrimoPazTrue(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element elCentro = service.getElement(elementId);
        String dataArr = "";

        List<Element> elArrPrimoPaz = elCentro.getChildrenByType("ArruolamentoPrimoPaz");
        for (Element child : elArrPrimoPaz) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "elArrPrimoPaz= " + child.getId().toString());
            dataArr = child.getFieldDataFormattedDates("DatiArrPrimoPaz", "dataPrimoArr", "dd/MM/yyyy").get(0);
        }

        String bodyMail = "E' stata inserita la seguente data di arruolamento del primo paziente: " + dataArr + " nel centro: \n\n";

        bodyMail += mailInfoCentro(elementId);

        commonBean.closeDocumentService(service);
        return bodyMail;
    }

    public String mailCloseOutVisit() throws Exception {

        String mailCTC = "";
        String mailCE = "";
        String mail = "";

        mailCTC = getEmail("ALIAS_CTC");
        mailCE = getEmail("ALIAS_SEGR_CE");

        mail = mailCTC + mailCE;

        return mail;

    }

    public String mailServiziCoinvolti(String elementId, DocumentService service) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "mailServiziCoinvolti");
        //DocumentService service=commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        //String parentId = (el.getParent().getId().toString());
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "elementId=" + elementId);

        String nomeGruppo = "";
        String email = "";
        String prefix = "CRMS";

        Collection<MetadataTemplate> templates = el.getTemplates();
        for (MetadataTemplate template : templates) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), template.getName());
            if (template.getName().equals("ServiziCoinvolti")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "qui");
                Collection<MetadataField> campi = template.getFields();
                boolean comma = false;
                for (MetadataField campo : campi) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), campo.getName());
                    if (campo.getName().startsWith("SERV")) {
                        if (el.getFieldDataCode(template.getName(), campo.getName()) != null && !el.getFieldDataCode(template.getName(), campo.getName()).isEmpty()) {
                            it.cineca.siss.axmr3.log.Log.debug(getClass(), "campo=" + campo.getName() + " valore=" + el.getFieldDataCode(template.getName(), campo.getName()));
                            int i;
                            String servizio = "";
                            String feasibilityServizio = "";

                            for (i = 1; i <= 52; i++) {
                                servizio = "SERV" + i;
                                feasibilityServizio = "Feasibility" + servizio;
                                if (campo.getName().equals(servizio)) {
                                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "creo figlio per " + servizio);
                                    //commonBean.createChild(elementId, "CTC", feasibilityServizio, service);
                                    nomeGruppo = prefix + "_" + servizio;
                                    if (comma) {
                                        email += ",";
                                    }
                                    email += mailRESP(elementId, nomeGruppo);

                                    comma = true;
                                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "email " + feasibilityServizio + " = " + email);
                                }
                            }
                        }
                    }
                }
            }
        }

        //Congelo il template Servizi Coinvolti
        //commonBean.changeTemplatePermissionToUser(elementId, "ServiziCoinvolti", "V", "*");
        //commonBean.closeDocumentService(service);
        if (email.isEmpty() || email == null) email = getEmail("ALIAS_CTC");
        return (email);
    }

    public String actionServizi(String elementId, DelegateExecution execution) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "actionServizi");
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        //String parentId = (el.getParent().getId().toString());
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "elementId=" + elementId);

        String nomeGruppo = "";
        String email = "";
        String prefix = "CRMS";

        Collection<MetadataTemplate> templates = el.getTemplates();
        for (MetadataTemplate template : templates) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), template.getName());
            if (template.getName().equals("ServiziCoinvolti")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "qui");
                Collection<MetadataField> campi = template.getFields();
                boolean comma = false;
                for (MetadataField campo : campi) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), campo.getName());
                    if (campo.getName().startsWith("SERV")) {
                        if (el.getFieldDataCode(template.getName(), campo.getName()) != null && !el.getFieldDataCode(template.getName(), campo.getName()).isEmpty()) {
                            it.cineca.siss.axmr3.log.Log.debug(getClass(), "campo=" + campo.getName() + " valore=" + el.getFieldDataCode(template.getName(), campo.getName()));
                            int i;
                            String servizio = "";
                            String feasibilityServizio = "";
                            Long newServiceId;
                            String my_cto = getCTOgroup(commonBean.getUser(el.getCreateUser()));
                            String my_farma = "FARMACIA";//my_cto.replace("CTO_","FARMA_");
                            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Assegnati permessi a profilo " + my_farma);
                            for (i = 1; i <= 52; i++) {
                                servizio = "SERV" + i;
                                feasibilityServizio = "Feasibility" + servizio;
                                if (campo.getName().equals(servizio)) {
                                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "creo figlio per " + servizio);
                                    newServiceId = commonBean.createChild(elementId, "CTC", feasibilityServizio, service);
                                    if (i == 5) { //TOSCANA-226 Assegno permessi a gruppo FARMA_* (my_farma)
                                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "FARMACIA! " + servizio + " id= " + newServiceId);
                                        commonBean.changePermissionToGroup(newServiceId.toString(), "V,C,M,AC,MC,E,MP,A,R,P,ET,B", "", my_farma, service);
                                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "abilitato gruppo " + my_farma);
                                    }
                                    nomeGruppo = prefix + "_" + servizio;
                                    String mailResp = mailRESP(elementId, nomeGruppo);
                                    if (mailResp != null && !mailResp.isEmpty()) {
                                        if (comma) {
                                            email += ",";
                                        }
                                        email += mailResp;
                                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "ActionServizi: " + email);
                                    }
                                    comma = true;
                                }
                            }
                        }
                    }
                }
            }
        }
        //Congelo il template Servizi Coinvolti
        commonBean.changeTemplatePermissionToUser(elementId, "ServiziCoinvolti", "V", "*");
        commonBean.closeDocumentService(service);
        if (email.isEmpty() || email == null) email = getEmail("ALIAS_CTC");
        return (email);
    }

    public void apprFeasServ(String elementId, DelegateTask task) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Task apprFeasServ id: " + task.getId());
        Element myElement = service.getElement(Long.parseLong(elementId));
        Element centroEl = myElement.getParent();
        Element studioEl = centroEl.getParent();
        String valueMap = "";

        HashMap<String, String> oggettoGruppo = new HashMap<String, String>();

        int i;
        String servizio = "";
        String feasibilityServizio = "";
        for (i = 1; i <= 52; i++) {
            servizio = "SERV" + i;
            feasibilityServizio = "Feasibility" + servizio;
            oggettoGruppo.put(feasibilityServizio, servizio);
        }

        Set<String> keys = oggettoGruppo.keySet();
        for (String key : keys) {
            if (myElement.getTypeName().equals(key)) {
                valueMap = oggettoGruppo.get(key);
                task.addCandidateGroup(oggettoGruppo.get(key));
                commonBean.changePermissionToGroup(centroEl, "V,B,P,AC", "", valueMap, service);
                commonBean.changePermissionToGroup(studioEl, "V,B", "", valueMap, service);
            }
        }

        //Abilito il Direttore dell'UO
        if (myElement.getTypeName().equals("FeasibilityUO")) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Sono nell'oggetto: " + myElement.getTypeName());
            String id_uo = centroEl.getFieldDataCode("IdCentro", "UO");
            String useridDirUO = getUseridDirUO(id_uo);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Sto per abilitare al processo l'utente: " + useridDirUO);
            task.addCandidateUser(useridDirUO);
        }

        //NON CHIUDERE IL DOCUMENT SERVICE PERCHE' VERRA' POI CHIUSO DA actionServizi
        //commonBean.closeDocumentService(service);
    }

    public void apprFeasServClose(String elementId, DelegateTask task) throws Exception {//SIRER-17
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        String parentId = (el.getParent().getId().toString());
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "INIZIO closeFeasibilityServizi elementId=" + elementId);


        String[] gruppiUtenti = {"CTC", "PI","COORD", "UOSC"};
        //Permessi di sola consultazione ai template associati a FeasibilityServizi
        for (String gr : gruppiUtenti) {
            commonBean.changeTemplatePermissionToGroup(elementId, "FeasibilityServWF", "V", gr);
            commonBean.changePermissionToGroup(elementId, "V", "", gr);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "cambio permessi al gruppo" + gr);
        }
        commonBean.changeTemplatePermissionToUser(elementId, "FeasibilityServWF", "V", el.getCreateUser());
        commonBean.changePermissionToUser(elementId, "V", "", el.getCreateUser());
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "cambio permessi all'utente " + el.getCreateUser());
        commonBean.changeTemplatePermissionToUser(elementId, "FeasibilityServWF", "V", "*");
        commonBean.changePermissionToUser(elementId, "V", "", "*");
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "cambio permessi all'utente *");

        //Permessi di sola consultazione ai template associati anche al parent (FeasibilityServiziRichiesta)
        for (String gr : gruppiUtenti) {
            commonBean.changeTemplatePermissionToGroup(parentId, "FeasibilitySUO", "V", gr);
            commonBean.changePermissionToGroup(parentId, "V", "", gr);
        }
        commonBean.changeTemplatePermissionToUser(parentId, "FeasibilityServWF", "V", el.getCreateUser());
        commonBean.changePermissionToUser(parentId, "V", "", el.getCreateUser());
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "cambio permessi all'utente " + el.getCreateUser());
        commonBean.changeTemplatePermissionToUser(parentId, "FeasibilityServWF", "V", "*");
        commonBean.changePermissionToUser(parentId, "V", "", "*");
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "cambio permessi all'utente *");

        commonBean.closeDocumentService(service);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "FINE closeFeasibilityServizi elementId=" + elementId);
    }

    //GC Vecchio metodo (human task scollegato dal WF) di creazione WF con cardinalità
    public void attivaServizi(String elementId, DelegateTask task) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Task attivaServizi id: " + task.getId());
        HashMap<String, String> servCoinv = ((HashMap<String, String>) task.getVariable("serviziCoinvolti"));
        HashMap<String, String> assignedservCoinv;
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "servCoinv= " + servCoinv.toString());
        Set<String> keys = servCoinv.keySet();
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "keys= " + keys);
        for (String key : keys) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "key id: " + key);
            assignedservCoinv = ((HashMap<String, String>) task.getVariable("assignedElementsGroupped"));
            if (assignedservCoinv.get(key) != null) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "key is assigned: " + key);
                continue;
            } else {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "key is not assigned: " + key);
                assignedservCoinv.put(key, servCoinv.get(key));
                task.addCandidateGroup(key);
                task.setVariableLocal("Servizio", key);
                commonBean.changePermissionToGroup(elementId, "V,B,P,AC", "", key, service);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "elementID= " + elementId);

                Element myElement = service.getElement(Long.parseLong(elementId));
                commonBean.changePermissionToGroup(myElement.getParent(), "V,B", "", key, service);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Id Studio= " + myElement.getParent().getId());


                break;
            }
        }
        commonBean.closeDocumentService(service);
    }

    public void apprFeasNRC(String elementId, DelegateTask task) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Task apprFeasNRC id: " + task.getId());
/*        Element myElement = service.getElement(Long.parseLong(elementId));
        Element centroEl = myElement.getParent();
        Element studioEl = centroEl.getParent();
        String valueMap = "";

        HashMap<String,String>  oggettoGruppo = new HashMap<String, String>();
        oggettoGruppo.put("FeasibilityAreaME","ME");
        oggettoGruppo.put("FeasibilityAreaBS","BS");
        oggettoGruppo.put("FeasibilityAreaAC","AC");
        oggettoGruppo.put("FeasibilityAreaGA","GA");

        Set<String> keys = oggettoGruppo.keySet();
        for(String key:keys){
            if(myElement.getTypeName().equals(key)){
                valueMap = oggettoGruppo.get(key);
                task.addCandidateGroup(oggettoGruppo.get(key));
                commonBean.changePermissionToGroup(centroEl,"V,B,P,AC","",valueMap,service);
                commonBean.changePermissionToGroup(studioEl,"V,B","",valueMap,service);
            }
        }
*/
        commonBean.closeDocumentService(service);
    }

    public void apprAdempAmmNRC(String elementId, DelegateTask task) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Task apprFeasNRC id: " + task.getId());
        Element myElement = service.getElement(Long.parseLong(elementId));
        Element centroEl = myElement.getParent();
        Element studioEl = centroEl.getParent();
        String valueMap = "";

/*        HashMap<String,String>  oggettoGruppo = new HashMap<String, String>();
        oggettoGruppo.put("AdempimentiAmmME","ME");
        oggettoGruppo.put("AdempimentiAmmGA","GA");

        Set<String> keys = oggettoGruppo.keySet();
        for(String key:keys){
            if(myElement.getTypeName().equals(key)){
                valueMap = oggettoGruppo.get(key);
                task.addCandidateGroup(oggettoGruppo.get(key));
                commonBean.changePermissionToGroup(centroEl,"V,B,P,AC","",valueMap,service);
                commonBean.changePermissionToGroup(studioEl,"V,B","",valueMap,service);
            }
        }
*/
        commonBean.closeDocumentService(service);
    }

    public String mailRESP(String elementId, String gruppou) throws Exception {
        //DocumentService service = commonBean.getDocumentService();
        //Element el=service.getElement(Long.parseLong(elementId));
        Connection conn = dataSource.getConnection();
        //Element el=service.getElement(Long.parseLong(elementId));
        //Long idStudio= (Long) el.getParent().getfieldData("UniqueIdStudio", "id").get(0);
        //TODO: riscrivere la query in base ai servizi effettivamente abilitati dal PI/CTC
        String sql1 = "select email from ana_utenti_1 where userid in (select userid from utenti_gruppiu  where id_gruppou in (select id_gruppou from ana_gruppiu where nome_gruppo in ('" + gruppou + "')))";
        it.cineca.siss.axmr3.log.Log.debug(getClass(), sql1);
        PreparedStatement stmt = conn.prepareStatement(sql1);
        ResultSet rset = stmt.executeQuery();

        String mail = "";
        while (rset.next()) {
            if (rset.getString("email") != null && !rset.getString("email").equals("")) {
                if (!mail.isEmpty()) mail += ",";
                mail += rset.getString("email");
            }
        }

        //commonBean.closeDocumentService(service);

        //TODO: mail provvisoria da sostituire con il risultato della query
        //mail="fidopink@msn.com";
        conn.close();
        mail = cleanAddresses(mail);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "mailRESP: " + mail);
        return mail;

    }

    public String getUseridDirUO(String idUO) throws Exception {
        String userid_uo = "";

        /*GC 07/09/2016 da personalizzare per la toscana
        Connection conn=dataSource.getConnection();
        String sql1="select dir_uo from crpms_centri_total where id_uo="+idUO;
        it.cineca.siss.axmr3.log.Log.debug(getClass(),sql1);
        PreparedStatement stmt = conn.prepareStatement(sql1);
        ResultSet rset = stmt.executeQuery();

        if(rset.next()){
            if(rset.getString("dir_uo")!=null && !rset.getString("dir_uo").isEmpty()){
                userid_uo=rset.getString("dir_uo");
            }
        }
        conn.close();
        */
        return userid_uo;
    }

    public void abilitaUO(String elementId) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Entro in abilitaUO");
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));

        String id_uo = "";
        String useridDirUO = "";

        id_uo = el.getFieldDataCode("IdCentro", "UO");
        useridDirUO = getUseridDirUO(id_uo);

        if (!useridDirUO.equals("")) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Trovato Direttore UO= " + useridDirUO);
            //Do i permessi di ReadOnly al centro
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "service= " + service);
            commonBean.changePermissionToUser(elementId, "V,AC,B", "", useridDirUO);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Permessi a " + useridDirUO + " per il centro=" + elementId);

            //creo l'oggetto feasbility_UO
            Long childId = commonBean.createChild(elementId, "CTC", "FeasibilityUO");
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Creo l'oggetto feasbility_UO con id=" + childId);

            //Do i permessi all'oggetto feasbility_UO
            commonBean.changePermissionToUser(childId.toString(), "V,M,AC,MP,A,P,B", "", useridDirUO);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Permessi a " + useridDirUO + " per feasbility_UO=" + childId.toString());
        }

        commonBean.closeDocumentService(service);
    }

    public void mailDirUO(String elementId, DelegateExecution execution) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        Connection conn = dataSource.getConnection();
        String id_uo = "";
        String useridDirUO = "";

        id_uo = el.getFieldDataCode("IdCentro", "UO");
        useridDirUO = getUseridDirUO(id_uo);

        String oggetto = "SIRER - Richiesta valutazione di fattibilit&agrave; direttore UO";
        String url = getBaseUrl() + "/app/documents/detail/" + el.getId() + "#metadataTemplate-FeasibilityRESP2";
        String html = "Gentile utente,\n" +
                "si richiede la sua valutazione di fattibilit&agrave; al seguente link:\n\n" +
                url + "\n\n" +
                "per il seguente studio:\n\n" +
                mailInfoCentro(elementId, service) + "\n\n" +
                "Cordiali saluti\n";

        String sql1 = "select email from ana_utenti_1 where userid='" + useridDirUO + "'";
        it.cineca.siss.axmr3.log.Log.debug(getClass(), sql1);
        PreparedStatement stmt = conn.prepareStatement(sql1);
        ResultSet rset = stmt.executeQuery();

        String mail = "";
        String comma = ",";
        boolean need_comma = false;
        while (rset.next()) {
            String my_mail = rset.getString("email");
            if (!my_mail.isEmpty()) {
                if (need_comma) {
                    mail += comma;
                }
                mail += rset.getString("email");
                need_comma = true;
            }
        }
        //mail=mail.replaceAll(",$",""); //tolgo l'ultima virgola
        if (mail.equals("")) mail = getEmail("ALIAS_CTC");

        commonBean.closeDocumentService(service);
        mail = cleanAddresses(mail);
        execution.setVariableLocal("oggetto", oggetto);
        execution.setVariableLocal("to", mail);
        execution.setVariableLocal("html", html);

        conn.close();
        //return mail;

    }

    public void mailCopiaCE(String elementId, DelegateExecution execution) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        Connection conn = dataSource.getConnection();
        Long idStudio = Long.valueOf(el.getParent().getfieldData("UniqueIdStudio", "id").get(0).toString());
        String oggetto = "SIRER - Invio dati da CTO/TFA a Segreteria CE ";
        String url = getBaseUrl() + "/../uxmr/index.php?ID_STUD=" + idStudio + "&VISITNUM=1&exams=visite_exams.xml";
        String html = "Gentile utente,\n" +
                "si comunica che e' stato appena inviato il seguente centro da CTO/TFA a Segreteria CE:\n\n" +
                mailInfoCentro(elementId, service) + "\n\n" +
                "E' possibile visualizzare il centro al seguente link:\n\n" +
                url + "\n\n" +
                "Cordiali saluti\n";

        Integer idCentro = Integer.valueOf(el.getfieldData("IdCentro", "Struttura").get(0).toString().split("###")[0]);
        if (Integer.valueOf(el.getParent().getfieldData("datiStudio", "popolazioneStudio").get(0).toString().split("###")[0]) == 1) {
            idCentro = 4;//TOSCANA-189 se lo studio è pediatrico allora mando mail a utenti di segreteria CEP
        }
        String sql1 = "select email from ana_utenti_2 where profilo='SGR' and id_ce=(select centro from ce_elenco_centriloc where id=?)";
        it.cineca.siss.axmr3.log.Log.debug(getClass(), sql1);
        PreparedStatement stmt = conn.prepareStatement(sql1);
        stmt.setInt(1, idCentro);
        ResultSet rset = stmt.executeQuery();

        String mail = "";
        String comma = ",";
        boolean need_comma = false;
        while (rset.next()) {
            String my_mail = rset.getString("email");
            if (!my_mail.isEmpty()) {
                if (need_comma) {
                    mail += comma;
                }
                mail += rset.getString("email");
                need_comma = true;
            }
        }
        //mail=mail.replaceAll(",$",""); //tolgo l'ultima virgola
        if (mail.equals("")) mail = getEmail("ALIAS_CTC");

        commonBean.closeDocumentService(service);
        mail = cleanAddresses(mail);
        execution.setVariableLocal("oggetto", oggetto);
        execution.setVariableLocal("to", mail);
        execution.setVariableLocal("html", html);

        conn.close();
        //return mail;

    }

    private String cleanAddresses(String addresses) {
        String cleaned = addresses.replaceAll(",\\s+$", "");
        if (cleaned.isEmpty()) {
            cleaned = "";
        }
        return cleaned;
    }

    public void abilitaSR(String elementId) throws Exception {
        //inizializzo variabili
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));

        //do i diritti al centro e allo studio suo padre
        commonBean.changePermissionToGroup(el.getParent(), "V,B", "", "SR", service);
        commonBean.changePermissionToGroup(el, "V,B,A", "", "SR", service);

        /*COMMENTATO PERCHE' TOGLIEVA I DIRITTI AI TEMPLATI AGLI ALTRI GRUPPI
        //do i diritti ai template del centro
        Collection<MetadataTemplate> templates = el.getTemplates();
        for(MetadataTemplate template:templates){
            commonBean.changeTemplatePermissionToGroup(elementId, template.getName(), "V","SR",service);
        }
        */

        //ciclo i figli del centro e do i diritti di visualizzazione per tutti.
        // Il contratto mantiene i diritti di configurazione
        // il budget ha i diritti solo per il budget definitivo
        Collection<Element> children = el.getChildren();
        for (Element currChild : children) {
            if (!currChild.getType().getTypeId().equals("Contratto") && !currChild.getType().getTypeId().equals("Budget")) {
                commonBean.changePermissionToGroupRecursive(el, "V,B", "", "SR", service);
            }
            //do i diritti per il budget approvato
            else if (currChild.getType().getTypeId().equals("Budget")) {
                commonBean.changePermissionToGroup(currChild, "V,B", "", "SR", service);
                // if(el.getParent()!=null)service.addMetadataValueActions(el.getParent().getId(), "statoValidazioneCentro", "idBudgetApproved", elementId);
                List<Object> budgetApprovedList = el.getfieldData("statoValidazioneCentro", "idBudgetApproved");
                String budgetApproved = "";
                if (budgetApprovedList != null && budgetApprovedList.size() > 0) {
                    budgetApproved = budgetApprovedList.get(0).toString();
                    commonBean.changePermissionToGroupRecursive(budgetApproved, "V,B", "budget_SR_close", "SR", service);
                }

            }
        }

        //


        //diritti V 	C 	M 	AC 	MC 	E 	MP 	A 	R 	P 	ET 	B


        //   commonBean.changePermissionToUser(elementId,"V,M,AC,MP,A,P,B","",userid_pi,service);


        commonBean.closeDocumentService(service);

    }

    //TOSCANA-87
    public void applicaRiduzione(String elementId) throws Exception {
        it.cineca.siss.axmr3.log.Log.warn(getClass(), "Entro in applicaRiduzione");
        //inizializzo variabili
        DocumentService service = commonBean.getDocumentService();
        Element elFattura = service.getElement(Long.parseLong(elementId));
        List<Element> riduzioni = elFattura.getChildrenByType("RiduzioneFattura");
        Double realeFattura = Double.parseDouble(elFattura.getFieldDataString("DatiFatturaWF_realeFattura"));
        it.cineca.siss.axmr3.log.Log.warn(getClass(), "DatiFatturaWF_realeFattura VECCHIO VALORE " + realeFattura);
        Double percentuale = 0.0;
        Double riduzioneFattura = 0.0;

        if (riduzioni.size() > 0) {
            for (Element elRiduzione : riduzioni) {
                String riduzione = elRiduzione.getFieldDataCode("RiduzioneFattura_TipoRiduzione");
                if (riduzione.equals("1")) {//riduzione Percentuale
                    percentuale = Double.parseDouble(elRiduzione.getFieldDataString("RiduzioneFattura", "QuantitaRiduzione"));
                    riduzioneFattura = realeFattura * percentuale / 100;
                } else {
                    riduzioneFattura = Double.parseDouble(elRiduzione.getFieldDataString("RiduzioneFattura", "QuantitaRiduzione"));
                }
                realeFattura = realeFattura - riduzioneFattura;
                it.cineca.siss.axmr3.log.Log.warn(getClass(), "DatiFatturaWF_riduzioneFattura " + riduzioneFattura);
                it.cineca.siss.axmr3.log.Log.warn(getClass(), "DatiFatturaWF_realeFattura NUOVO VALORE " + realeFattura);
                String my_cto = getCTOgroup(commonBean.getUser(elRiduzione.getCreateUser()));
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "appartiene al gruppo= " + my_cto);
                commonBean.changePermissionToGroup(elRiduzione, "V,C,A,B", "", my_cto, service);
                commonBean.changePermissionToGroup(elRiduzione, "V,C,A,B", "", "CTC", service);//TOLGO LA MODIFICA A GRUPPO CTC
                DecimalFormat decimalFormat = new DecimalFormat("#.00");
                commonBean.addMetadataValue(elementId, "DatiFatturaWF", "riduzioneFattura", decimalFormat.format(riduzioneFattura), service);
                commonBean.addMetadataValue(elementId, "DatiFatturaWF", "realeFattura", decimalFormat.format(realeFattura), service);
            }
        }
        commonBean.closeDocumentService(service);
        it.cineca.siss.axmr3.log.Log.warn(getClass(), "Esco da applicaRiduzione");
    }

    public void abilitaURFatturaEInviaMail(String elementId) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Entro in abilitaURFatturaEInviaMail");
        //inizializzo variabili
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));

        Element elCentro = el.getParent().getParent().getParent();
        Element elStudio = elCentro.getParent();
        String group = getCTOgroup(commonBean.getUser(elCentro.getCreateUser())).replace("CTO_", "UR_");//TOSCANA-177
        commonBean.changePermissionToGroup(elementId, "V,C,M,AC,B,A", "", group, service);

        //TOSCANA-177
        Connection conn = dataSource.getConnection();
        String processKey = "inviaMail";
        HashMap<String, String> mailData = new HashMap<String, String>();
        String mailTo = "";
        String sqlMailTO = "select u.email as email from ana_utenti_1 u, studies_profiles sp,users_profiles up where u.userid=up.userid and sp.id=up.profile_id and sp.active=1 and up.active=1 and sp.code=?";
        it.cineca.siss.axmr3.log.Log.debug(getClass(), sqlMailTO);
        PreparedStatement stmtMailTo = conn.prepareStatement(sqlMailTO);

        stmtMailTo.setString(1, group);
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
        if (mailTo.equals("")) mailTo = getEmail("ALIAS_CTC");
        String mailSubject = "SIRER - Avvio Fatturazione";
        String mailInfoCentro = "";
        //Long idStudio;
        String sponsor = "";
        String croString = "";
        String codice = "";
        String titolo = "";
        String DenCentro = "";
        String DenUnitaOperativa = "";
        String DenPrincInv = "";

        String idStudio = elStudio.getfieldData("UniqueIdStudio", "id").get(0).toString();

        if (elStudio.getFieldDataElement("datiPromotore", "promotore") != null && elStudio.getFieldDataElement("datiPromotore", "promotore").size() > 0) {
            Element sp = elStudio.getFieldDataElement("datiPromotore", "promotore").get(0);
            sponsor = sp.getfieldData("DatiPromotoreCRO", "denominazione").get(0).toString();
        }
        if (elStudio.getFieldDataElement("datiCRO", "denominazione") != null && elStudio.getFieldDataElement("datiCRO", "denominazione").size() > 0) {
            Element cro = elStudio.getFieldDataElement("datiCRO", "denominazione").get(0);
            croString = cro.getfieldData("DatiPromotoreCRO", "denominazione").get(0).toString();
        }
        if (elStudio.getfieldData("IDstudio", "CodiceProt") != null && elStudio.getfieldData("IDstudio", "CodiceProt").size() > 0) {
            codice = elStudio.getfieldData("IDstudio", "CodiceProt").get(0).toString();
        }
        if (elStudio.getfieldData("IDstudio", "TitoloProt") != null && elStudio.getfieldData("IDstudio", "TitoloProt").size() > 0) {
            titolo = elStudio.getfieldData("IDstudio", "TitoloProt").get(0).toString();
        }
        DenCentro = elCentro.getfieldData("IdCentro", "Struttura").get(0).toString().split("###")[1];
        DenUnitaOperativa = elCentro.getfieldData("IdCentro", "UO").get(0).toString().split("###")[1];
        DenPrincInv = elCentro.getfieldData("IdCentro", "PINomeCognome").get(0).toString().split("###")[1];

        mailInfoCentro =
                "ID studio: " + idStudio +
                        "\nCodice: " + codice +
                        "\nTitolo: " + titolo +
                        "\nSponsor: " + sponsor +
                        "\nCRO: " + croString +
                        "\nStruttura: " + DenCentro +
                        "\nUnita' operativa: " + DenUnitaOperativa +
                        "\nPrincipal Investigator: " + DenPrincInv;

        String url = getBaseUrl() + "/app/documents/detail/" + elCentro.getId() + "#Fatturazione-tab2";
        String mailBody = "Gentile utente,\n" +
                "si comunica che e' stata appena avviata la fatturazione per il seguente centro:\n\n" +
                mailInfoCentro + "\n\n" +
                "E' possibile visualizzare il centro al seguente link:\n\n" +
                url + "\n\n" +
                "Cordiali saluti\n\n\n\n" +
                "Il presente messaggio è stato inviato automaticamente dal sistema, si prega di non rispondere.\n" +
                "Per contattare il servizio di help desk inviare una mail a help_crpms@cineca.it";

        mailData.put("to", mailTo);
        mailData.put("subject", mailSubject);
        mailData.put("body", mailBody);
        mailData.put("cc", getEmail("ALIAS_CTC"));
        mailData.put("ccn", getEmail("ALIAS_CTC"));
        service.startProcess(elCentro.getCreateUser(), elCentro, processKey, mailData);


        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Esco da abilitaURFatturaEInviaMail");
        commonBean.closeDocumentService(service);
    }

    @Autowired
    protected InternalServiceBean isb;

    public InternalServiceBean getIsb() {
        return isb;
    }

    public void setIsb(InternalServiceBean isb) {
        this.isb = isb;
    }

    public void abilitaUR(String elementId) {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Entro in abilitaUR");
        if (isb.isActive()) {
            isb.doInternalAsyncRequest("/rest/abilitaUR/" + elementId);
        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Esco da abilitaUR");
    }

    public void abilitaUROLD(String elementId) throws Exception {

        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Entro in abilitaUR");
        //inizializzo variabili
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));

        Element elCentro = el.getParent();
        Element elStudio = el.getParent().getParent();
        String group = getCTOgroup(commonBean.getUser(elCentro.getCreateUser())).replace("CTO_", "UR_");//TOSCANA-177
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "ASSOCIO GRUPPO= " + group);
        //do i diritti al centro
        commonBean.changePermissionToGroup(elCentro, "V,B,A", "", group, service);
        String idCentro = elCentro.getId().toString();
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "idCentro=" + idCentro);

        //do i diritti ai figli del centro (documenti)
        Collection<Element> figliCentro = elCentro.getChildren();
        for (Element currfiglio : figliCentro) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "figli di studio=" + currfiglio);
            if (currfiglio.getTypeName().equals("AllegatoCentro")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "figlio allegato");
                commonBean.changePermissionToGroupRecursive(currfiglio, "V,B", "", group, service);
            }
            if (currfiglio.getTypeName().equals("Fatturazione")) {//TOSCANA-177 abilito UR_* anche per fatturazione
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "figlio Fatturazione");
                commonBean.changePermissionToGroupRecursive(currfiglio, "V,B", "", group, service);
            }
        }

        /*
        //do i diritti ai template del centro
        Collection<MetadataTemplate> templates = elCentro.getTemplates();
        for(MetadataTemplate template:templates){
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"template="+template.getName());
            commonBean.changeTemplatePermissionToGroup(idCentro, template.getName(), "V",group,service);
        }
        */

        //ciclo i figli del centro e do i diritti di visualizzazione per tutti.
        // Il contratto mantiene i diritti di configurazione
        // il budget ha i diritti solo per il budget definitivo
        /*
        Collection<Element> children = elCentro.getChildren();
        for(Element currChild:children){
            if (!currChild.getType().getTypeId().equals("Contratto") && !currChild.getType().getTypeId().equals("Budget")){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"figli di centro="+currChild.getType().getTypeId());
                commonBean.changePermissionToGroupRecursive(elCentro,"V,B","",group,service);
            }
            //do i diritti per il budget approvato


            else if(currChild.getType().getTypeId().equals("Budget")){
                commonBean.changePermissionToGroup(currChild,"V,B","",group,service);
                // if(el.getParent()!=null)service.addMetadataValueActions(el.getParent().getId(), "statoValidazioneCentro", "idBudgetApproved", elementId);
                List<Object> budgetApprovedList = el.getfieldData("statoValidazioneCentro", "idBudgetApproved");
                String budgetApproved="";
                if(budgetApprovedList!=null && budgetApprovedList.size()>0) {
                    budgetApproved=   budgetApprovedList.get(0).toString();
                    commonBean.changePermissionToGroupRecursive(budgetApproved,"V,B","budget_SR_close",group,service);
                }
            }

        }
        */

        //do i diritti allo studio
        commonBean.changePermissionToGroup(elStudio, "V,B", "", group, service);
        String idStudio = elStudio.getId().toString();

        /*
        //do i diritti ai template dello studio
        Collection<MetadataTemplate> templatesStudio = elStudio.getTemplates();
        for(MetadataTemplate templateStudio:templatesStudio){
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"template="+templateStudio.getName());
            commonBean.changeTemplatePermissionToGroup(idStudio, templateStudio.getName(), "V",group,service);
        }
        */

        //do i diritti ai figli dello studio (documenti)
        Collection<Element> figliStudio = elStudio.getChildren();
        for (Element currfiglio : figliStudio) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "figli di studio=" + currfiglio);
            if (currfiglio.getTypeName().equals("allegato")) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "figlio allegato");
                commonBean.changePermissionToGroupRecursive(currfiglio, "V,B", "", group, service);
            }
        }

        //SR
        commonBean.changeTemplatePermissionToGroup(idCentro, "Feasibility", "V", group);
        commonBean.changeTemplatePermissionToGroup(idCentro, "DatiCentro", "V", group);
        commonBean.changeTemplatePermissionToGroup(idCentro, "IdCentro", "V", group);

        commonBean.changeTemplatePermissionToGroup(idStudio, "datiStudio", "V", group);

        it.cineca.siss.axmr3.log.Log.debug(getClass(), "COMMIT abilitaUR");
        commonBean.getGlobalTx().commitAndKeepAlive();
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Esco da abilitaUR");
        commonBean.closeDocumentService(service);

    }

    public String getEmail(String userid) throws Exception {
        Connection conn = dataSource.getConnection();
        String sql1 = "select email from ana_utenti_1 where userid=?";
        it.cineca.siss.axmr3.log.Log.debug(getClass(), sql1);
        PreparedStatement stmt = conn.prepareStatement(sql1);
        stmt.setString(1, userid);
        ResultSet rset = stmt.executeQuery();

        String mail = "";
        while (rset.next()) {
            mail += rset.getString("email") + ",";
        }
        conn.close();
        mail = cleanAddresses(mail);
        return mail;

    }

    public void actionPostScheduling(String elementId) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "ENTRO IN actionPostScheduling");
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        String parentId = (el.getParent().getId().toString());
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "elementId=" + elementId);
        String group = getCTOgroup(commonBean.getUser(el.getCreateUser())).replace("CTO_", "UR_");//TOSCANA-177
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "ASSOCIO GRUPPO= " + group);
        commonBean.addMetadataValue(elementId, "StatoScheduling", "ValoreAcconto", el.getFieldDataString("scheduling", "ValoreAssoluto"));
        commonBean.addMetadataValue(elementId, "StatoScheduling", "AccontoRiassorbito", "0");
        commonBean.changeTemplatePermissionToGroup(elementId, "scheduling", "V", "CTC");
        commonBean.changeTemplatePermissionToGroup(elementId, "scheduling", "V", "UR");//TOSCANA-177
        commonBean.changeTemplatePermissionToGroup(elementId, "scheduling", "V", group);//TOSCANA-177
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "COMMIT actionPostScheduling");
        commonBean.getGlobalTx().commitAndKeepAlive();
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "ESCO DA actionPostScheduling");
        commonBean.closeDocumentService(service);
    }

    public void terminaProcesso(String elementId, String processDefinition) throws Exception {
        DocumentService service = commonBean.getDocumentService();
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
    }

    public void attivaFirmaContratto(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element firma = service.getElement(elementId);
        Element contratto = firma.getParent();
        String processDefinition = "FirmaContratto";
        //List<ProcessInstance> activeProcesses;
        //boolean alreadyStarted=(fattura.getChildrenByType("Ribaltamento").size()>0);

        /*
        if(feedback.getFieldDataCode("DatiFatturaFeedback","Feedback").equals("1") && !alreadyStarted){    //incasso
            activeProcesses = service.getActiveProcesses(fattura);
            for(ProcessInstance process:activeProcesses){
                if(process.getProcessDefinitionId().equals(processDefinition)){
                    alreadyStarted=true;
                }
            }
            service.startProcess("CTC",fattura,processDefinition);
        } */

        service.startProcess("CTC", contratto, processDefinition);

        commonBean.closeDocumentService(service);
    }

    public void RinnovoContratto(String elementId) throws Exception {

        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));

        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Rinnovo Contratto");

        String ultimaScadenza = "";

        ultimaScadenza = el.getFieldDataFormattedDates("RinnovoContratto", "DataFineNuova", "dd/MM/yyyy").get(0);

        it.cineca.siss.axmr3.log.Log.debug(getClass(), ultimaScadenza);

        it.cineca.siss.axmr3.log.Log.debug(getClass(), "id contratto= " + el.getParent().getId());

        commonBean.addMetadataValue(el.getParent().getId(), "ValiditaContratto", "UltimaScadenza", ultimaScadenza, service);

        commonBean.closeDocumentService(service);

    }

    public String ContrattiInScadenza() throws Exception {
        DocumentService service = commonBean.getDocumentService();
        //Element el=service.getElement(Long.parseLong(elementId));

        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Inizio");

        List<Element> contrattiScadenza = new LinkedList<Element>();

        HashMap<String, Object> data = new HashMap<String, Object>();
        String bodyMail = "";
        String bodyMailInt = "Contratti in scadenza:\n\n";
        String idContratto = "";
        //String prot1="";
        //String prot2="";
        String numeroProtocollo = "";
        String idCentro = "";
        String today = commonBean.sysdate();
        String todayMoreOneMonth = "";
        Integer contrattiTrovati = 0;

        SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy");
        Calendar c = Calendar.getInstance();
        c.setTime(new java.util.Date());
        c.add(Calendar.DAY_OF_MONTH, 30);
        todayMoreOneMonth = sdf.format(c.getTime());

        /*
        SimpleDateFormat sdf1 = new SimpleDateFormat("yyyy-MM-dd");
        Calendar c1 = Calendar.getInstance();
        c1.setTime(sdf1.parse(today));
        c1.add(Calendar.DATE, 30);  // number of days to add
        String todayMoreOneMonth1 = sdf1.format(c1.getTime());
        */

        it.cineca.siss.axmr3.log.Log.debug(getClass(), "oggi= " + today);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "tra un mese= " + todayMoreOneMonth);

        //it.cineca.siss.axmr3.log.Log.debug(getClass(),"tra un mese= "+todayMoreOneMonth1);

        //data.put("preFirmaContrattoWF_fineValidita_gteq",today);
        //data.put("preFirmaContrattoWF_fineValidita_lteq",todayMoreOneMonth);

        data.put("ValiditaContratto_UltimaScadenza_gteq", today);
        data.put("ValiditaContratto_UltimaScadenza_lteq", todayMoreOneMonth);

        it.cineca.siss.axmr3.log.Log.debug(getClass(), "ValiditaContratto_UltimaScadenza_gteq");

        contrattiScadenza = service.advancedSearch("Contratto", data);

        it.cineca.siss.axmr3.log.Log.debug(getClass(), contrattiScadenza + "Fine");

        /*
        Iterator<Element> it = contrattiScadenza.iterator();
        while(it.hasNext()){
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"while: "+it.next().getId().toString());
        }
        */

        for (Element currel : contrattiScadenza) {
            contrattiTrovati = 1;
            idContratto = currel.getId().toString();
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "for: " + idContratto);
            currel = service.sync(currel);
            idCentro = currel.getParent().getId().toString();

            String baseUrl = getBaseUrl();
            String urlContratto = baseUrl + "/app/documents/detail/" + idContratto;

            /*
            prot1=currel.getChildrenByType("LettAccFirmaContr").get(0).getfieldData("Step1Contr","numProt").get(0).toString();

            if(currel.getChildrenByType("LettAccFirmaContr2")!=null && currel.getChildrenByType("LettAccFirmaContr2").size()>0){
                prot2=currel.getChildrenByType("LettAccFirmaContr2").get(0).getfieldData("Step2Contr","numProt2").get(0).toString();
            }

            if(!prot1.equals("")){numeroProtocollo=prot1+"\n";}
            if(!prot2.equals("")){numeroProtocollo=prot2+"\n";}

            bodyMail+="Numero protocollo interno contratto: "+numeroProtocollo+"\n";
            */

            bodyMail += "Visualizza contratto: " + urlContratto + "\n";
            bodyMail += mailInfoCentro(idCentro) + "\n\n";

        }

        if (contrattiTrovati == 1) {
            bodyMail = bodyMailInt + bodyMail;
        }

        commonBean.closeDocumentService(service);

        return bodyMail;

    }

    public String mailContratto(String elementId) throws Exception {
        return mailContratto(elementId, null);
    }

    public String mailContratto(String elementId, DelegateTask task) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        Element elStudio = el.getParent().getParent();
        String ret = "";

        //Mail al Contact Point Legale del Promotore
        /*TOSCANA-193 rimuovo invio mail promotore
        if(elStudio.getfieldData("datiPromotore", "RefEmailL")!=null && elStudio.getfieldData("datiPromotore", "RefEmailL").size()>0){
            ret=elStudio.getfieldData("datiPromotore", "RefEmailL").get(0).toString();
            it.cineca.siss.axmr3.log.Log.warn(getClass(),"ho trovato la mail="+ret);
            if(task!=null) task.setVariable("passed", true);
        }else{
            it.cineca.siss.axmr3.log.Log.warn(getClass(),"Non ho trovato la mail");
            if(task!=null) task.setVariable("passed", false);
        }
        it.cineca.siss.axmr3.log.Log.warn(getClass(),"mail CPLegale ="+ret);
        */
        //Mail al PI
        String mailPI = mailPI(elementId, service);
        it.cineca.siss.axmr3.log.Log.warn(getClass(), "mail PI =" + mailPI);
        if (mailPI != null && !mailPI.isEmpty()) ret = ret + "," + mailPI;
        else ret = ret + ",";

        it.cineca.siss.axmr3.log.Log.warn(getClass(), "mail CPLegale+PI =" + ret);

        //Mail ai servizi coinvolti
        String idCentro = getElementIdCentro(elementId, service);
        String mailServizi = mailServiziCoinvolti(idCentro, service);
        if (mailServizi != null && !mailServizi.isEmpty()) ret = ret + "," + mailServizi;

        commonBean.closeDocumentService(service);

        it.cineca.siss.axmr3.log.Log.warn(getClass(), "mail finale=" + ret);
        return ret;
    }

    public void checkAllPaz(String elementId, DelegateTask task) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Inizio checkAllPaz");

        DocumentService service = commonBean.getDocumentService();
        boolean passed = true;
        String statoPaz = "";
        Element elCentro = service.getElement(elementId);

        //searchByExample
        HashMap<String, Object> data = new HashMap<String, Object>();
        data.put("StatoPaziente_Stato", "1###In screening / in trattamento");
        List<Element> listaPaz = service.searchByExample(elementId, "MonitoraggioAmministrativo", data);
        if (listaPaz.isEmpty()) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "La lista e' vuota");
        } else {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "La lista e' piena");
        }

        //metodo classico
        List<Element> pazienti = elCentro.getChildrenByType("MonitoraggioAmministrativo");
        if (pazienti.isEmpty()) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Non ci sono pazienti");
            passed = false;
        } else {
            for (Element paziente : pazienti) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "paziente = " + paziente);
                if (paziente.getfieldData("StatoPaziente", "Stato") != null && paziente.getfieldData("StatoPaziente", "Stato").size() > 0) {
                    statoPaz = paziente.getFieldDataCode("StatoPaziente", "Stato");
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "stato = " + statoPaz);
                    if (statoPaz.equals("1")) {
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "passed = " + passed);
                        passed = false;
                    }
                }
            }
        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Setto la variabile di esecuzione passed a " + passed);
        task.setVariable("passed", passed);

        commonBean.closeDocumentService(service);
    }

    //Controllo le fatture di saldo e vedo se sono state incassate o stornate
    public void checkFattSaldoChiusura(String elementId, DelegateTask task) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Inizio checkAllPaz");

        boolean passed2 = false;
        DocumentService service = commonBean.getDocumentService();
        Element elCentro = service.getElement(elementId);

        List<Element> fatturazioni = elCentro.getChildrenByType("Fatturazione");
        if (!fatturazioni.isEmpty()) {
            for (Element fatturazione : fatturazioni) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "fatturazione = " + fatturazione);
                String idFatturazione = fatturazione.getId().toString();
                HashMap<String, Object> data = new HashMap<String, Object>();
                data.put("DatiFattura_Tipologia", "3###Saldo");
                List<Element> richiesteFatturazione = service.searchByExample(idFatturazione, "RichiestaFatturazione", data);
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Richieste di fatturazione = " + richiesteFatturazione);
                if (!richiesteFatturazione.isEmpty()) {
                    for (Element richiestaFatturazione : richiesteFatturazione) {
                        List<Element> fatture = richiestaFatturazione.getChildrenByType("Fattura");
                        if (!fatture.isEmpty()) {
                            for (Element fattura : fatture) {
                                List<Element> feeds = fattura.getChildrenByType("FatturaFeedback");
                                if (!feeds.isEmpty()) {
                                    boolean b = false;
                                    for (Element feed : feeds) {
                                        if (feed.getFieldDataCode("DatiFatturaFeedback", "Feedback").equals("1") || feed.getFieldDataCode("DatiFatturaFeedback", "Feedback").equals("3")) {
                                            b = true;
                                        }
                                    }
                                    if (b) {
                                        passed2 = true;
                                    } else {
                                        passed2 = false;
                                    }
                                } else {
                                    passed2 = false;
                                }
                            }
                        } else {
                            passed2 = false;
                        }
                    }
                } else {
                    passed2 = false;
                }
            }
        } else {
            passed2 = false;
        }

        task.setVariable("passed2", passed2);
        commonBean.closeDocumentService(service);
    }

    //TODO: generalizzare metodo con file di configurazione
    public String getBaseUrl() throws Exception {
        Connection conn = dataSource.getConnection();
        String sql1 = "select base_url from base_url";
        it.cineca.siss.axmr3.log.Log.debug(getClass(), sql1);
        PreparedStatement stmt = conn.prepareStatement(sql1);
        ResultSet rset = stmt.executeQuery();
        rset.next();

        String baseUrl = "";
        baseUrl = rset.getString("base_url");
        conn.close();
        return baseUrl;
    }

    public void createFattBudgetLinks(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        createFattBudgetLinks(elementId, service);
        commonBean.closeDocumentService(service);
    }

    public void createMonBudgetLinks(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        createMonBudgetLinks(elementId, service);
        commonBean.closeDocumentService(service);
    }

    public void createFattBudgetLinks(String elementId, DocumentService service) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "createFattBudgetLinks:passo 1 ");
        Element fatturazione = service.getElement(Long.parseLong(elementId));
        Element center = fatturazione.getParent();
        String totalePaz = "";
        String totale = "";

        //it.cineca.siss.axmr3.log.Log.debug(getClass(),"createFattBudgetLinks:center "+center.getId().toString());
        Element budget = getBudgetChiuso(center, service);
        Element budgetStudio = getBudgetDefinitivo(budget, service);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "createFattBudgetLinks:passo 2 ");

        if (budgetStudio.getfieldData("BudgetCTC", "TotaleStudioCTC") != null && budgetStudio.getfieldData("BudgetCTC", "TotaleStudioCTC").size() > 0) {
            totale = (String) budgetStudio.getfieldData("BudgetCTC", "TotaleStudioCTC").get(0);
        }
        if (budgetStudio.getfieldData("BudgetCTC", "NumeroPazienti") != null && budgetStudio.getfieldData("BudgetCTC", "NumeroPazienti").size() > 0) {
            totalePaz = (String) budgetStudio.getfieldData("BudgetCTC", "NumeroPazienti").get(0);
        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "createFattBudgetLinks:passo 2 bis " + totale);
        commonBean.addMetadataValue(fatturazione.getId().toString(), "InfoBudget", "Prezzo", totale, service);
        commonBean.addMetadataValue(fatturazione.getId().toString(), "InfoBudget", "Pazienti", totalePaz, service);
        commonBean.addMetadataValue(fatturazione.getId().toString(), "InfoBudget", "type", center.getFieldDataString("statoValidazioneCentro", "typeBudgetApproved"), service);
        //it.cineca.siss.axmr3.log.Log.debug(getClass(),"createFattBudgetLinks:budget "+budgetStudio.toString());
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "createFattBudgetLinks:passo 3 ");
        /*List<Element> checkPXS = budget.getChildrenByType("FolderPXS");
        if(checkPXS!=null && checkPXS.size()>0){
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"createFattBudgetLinks:passo 3bis ");
            Collection<Element> prestazioniStudioClinic = checkPXS.get(0).getChildren();
            //addFattPrestazioni(fatturazione,prestazioniStudioClinic,service);
        }          */
        List<Element> checkPXS = new LinkedList<Element>();
        if (budgetStudio.getType().getTypeId().equals("BudgetCTC")) {
            checkPXS = budgetStudio.getChildrenByType("FolderPrezzi");
        } else {
            checkPXS = budgetStudio.getParent().getParent().getChildrenByType("FolderPrezzi");
        }
        if (checkPXS != null && checkPXS.size() > 0) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "createFattBudgetLinks:passo 4bis ");
            Collection<Element> prestazioniStudioPrezzi = checkPXS.get(0).getChildren();
            LinkedList<Element> prestazioniStudioClinicPrezzi = new LinkedList<Element>();
            for (Element prezzo : prestazioniStudioPrezzi) {
                Element currElement = (Element) prezzo.getfieldData("PrezzoFinale", "Prestazione").get(0);
                if (currElement.getType().getTypeId().equals("PrestazioneXStudio")) {
                    prestazioniStudioClinicPrezzi.add(prezzo);
                }
            }
            addFattPrestazioni(fatturazione, prestazioniStudioClinicPrezzi, service);
        }


        it.cineca.siss.axmr3.log.Log.debug(getClass(), "createFattBudgetLinks:passo 4 ");

        if (budgetStudio.getType().getTypeId().equals("BudgetCTC")) {
            checkPXS = budgetStudio.getChildrenByType("FolderPXSCTC");
        } else {
            checkPXS = budgetStudio.getParent().getParent().getChildrenByType("FolderPXSCTC");
        }
        if (checkPXS != null && checkPXS.size() > 0) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "createFattBudgetLinks:passo 4bis ");
            Collection<Element> prestazioniStudio = checkPXS.get(0).getChildren();
            addFattPrestazioni(fatturazione, prestazioniStudio, service);
        }

        it.cineca.siss.axmr3.log.Log.debug(getClass(), "createFattBudgetLinks:passo 4 ");


        checkPXS = budget.getChildrenByType("FolderCostiAggiuntivi");

        if (checkPXS != null && checkPXS.size() > 0) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "createFattBudgetLinks:passo 4bis ");
            Collection<Element> prestazioniStudio = checkPXS.get(0).getChildren();
            addFattPrestazioni(fatturazione, prestazioniStudio, service);
        }

        it.cineca.siss.axmr3.log.Log.debug(getClass(), "createFattBudgetLinks:passo 5 ");
        List<Element> checkTP = budget.getChildrenByType("FolderTimePoint");
        if (checkTP != null && checkTP.size() > 0) {
            Collection<Element> tps = checkTP.get(0).getChildren();
            addFattTP(fatturazione, tps, service);
        }


        it.cineca.siss.axmr3.log.Log.debug(getClass(), "createFattBudgetLinks:passo 6 ");

    }

    public void createMonBudgetLinks(String elementId, DocumentService service) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "createMonBudgetLinks:passo 1 ");
        HashMap<Long, Long> monPrestazioniMap = new HashMap<Long, Long>();
        HashMap<Long, Long> monTPMap = new HashMap<Long, Long>();
        HashMap<Long, Long> monTpxpMap = new HashMap<Long, Long>();
        HashMap<Long, Long> monPxPMap = new HashMap<Long, Long>();
        HashMap<Long, Long> monPxPCTCMap = new HashMap<Long, Long>();
        HashMap<Long, Long> monPazienteFatturabileMap = new HashMap<Long, Long>();
        Collection<Element> prezzi;
        Long origElementId;
        Long createdElementId;
        String template = "";
        String currPrezzoValue = "";
        Integer totVisite = 0;

        Element currPrezzoElement;
        Element monitoraggio = service.getElement(Long.parseLong(elementId));
        service.addTemplate(monitoraggio, "DatiCustomMonitoraggioAmministrativo");
        Element center = monitoraggio.getParent();
        //it.cineca.siss.axmr3.log.Log.debug(getClass(),"createFattBudgetLinks:center "+center.getId().toString());
        Element budget = getBudgetChiuso(center, service);
        //Element budget=service.getElement(monitoraggio.getFieldDataCode("DatiMonitoraggioAmministrativo","BraccioBudget"));
        Element budgetStudio = getBudgetDefinitivo(budget, service);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "createMonBudgetLinks:passo 2 ");
        Element folderPrestazioni = monitoraggio.getChildrenByType("FolderMonPrestazioni").get(0);
        Element folderBracci = monitoraggio.getChildrenByType("FolderMonBracci").get(0);
        Element folderTP = monitoraggio.getChildrenByType("FolderMonTimePoint").get(0);
        Element folderTPxP = monitoraggio.getChildrenByType("FolderMonPxT").get(0);
        Element folderPxP = monitoraggio.getChildrenByType("FolderMonPxP").get(0);
        Element folderPazientiFatturabili = monitoraggio.getChildrenByType("FolderMonPazientiFatturabili").get(0);

        commonBean.addMetadataValue(monitoraggio.getId().toString(), "StatoPaziente", "Stato", "1###In trattamento", service);

        List<Element> checkElements = budget.getChildrenByType("FolderPrestazioni");
        if (checkElements != null && checkElements.size() > 0) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "createMonBudgetLinks:passo 3 ");
            Collection<Element> prestazioni = checkElements.get(0).getChildren();
            monPrestazioniMap = addMonPrestazioni(folderPrestazioni, prestazioni, service);
        }


        checkElements = budget.getChildrenByType("FolderTimePoint");
        if (checkElements != null && checkElements.size() > 0) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "createMonBudgetLinks:passo 4 ");
            Collection<Element> timepoints = checkElements.get(0).getChildren();
            totVisite = timepoints.size();
            commonBean.addMetadataValue(monitoraggio, "DatiCustomMonitoraggioAmministrativo", "VisiteTot", totVisite.toString(), service);
            commonBean.addMetadataValue(monitoraggio, "DatiCustomMonitoraggioAmministrativo", "VisiteFatturabili", "0", service);
            commonBean.addMetadataValue(monitoraggio, "DatiCustomMonitoraggioAmministrativo", "VisiteFatturate", "0", service);
            monTPMap = addMonTP(folderTP, timepoints, service);
        }

        it.cineca.siss.axmr3.log.Log.debug(getClass(), "createFattBudgetLinks:passo 5 ");
        checkElements = budget.getChildrenByType("FolderTpxp");
        if (checkElements != null && checkElements.size() > 0) {
            Collection<Element> tpxp = checkElements.get(0).getChildren();
            monTpxpMap = addMonTpxp(folderTPxP, tpxp, service);
        }


        checkElements = budget.getChildrenByType("FolderPXP");
        if (checkElements != null && checkElements.size() > 0) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "createMonBudgetLinks:passo 5bis ");
            Collection<Element> pxp = checkElements.get(0).getChildren();
            monPxPMap = addMonPxP(folderPxP, pxp, service);
        }

        checkElements = budgetStudio.getChildrenByType("FolderPXPCTC");
        if (checkElements != null && checkElements.size() > 0) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "createMonBudgetLinks:passo 5tris ");
            Collection<Element> pxp = checkElements.get(0).getChildren();
            monPxPCTCMap = addMonPxPCTC(folderPxP, pxp, service);
        }

        checkElements = budget.getChildrenByType("FolderBracci");
        if (checkElements != null && checkElements.size() > 0) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "createMonBudgetLinks:passo 5quater ");
            Collection<Element> bracci = checkElements.get(0).getChildren();
            addMonBracci(folderBracci, bracci, service);
        }

        //SIRER-67 inserisco voci pazienti completati fatturabili
        Long pazientiCompletatiFatturabiliId = commonBean.createChild(folderPazientiFatturabili.getId().toString(), folderPazientiFatturabili.getCreateUser(), "MonPazientiFatturabili", service);
        Element pazientiCompletatiFatturabili = service.getElement(pazientiCompletatiFatturabiliId);
        service.addTemplate(pazientiCompletatiFatturabili, "DatiMonPazientiFatturabili");
        commonBean.addMetadataValue(pazientiCompletatiFatturabiliId.toString(), "DatiMonPazientiFatturabili", "completati", "1");
        commonBean.addMetadataValue(pazientiCompletatiFatturabiliId.toString(), "DatiMonPazientiFatturabili", "BudgetLink", budget.getId().toString(), service);
        String prezzoPaziente = budgetStudio.getFieldDataString("BudgetCTC_TargetPaziente");
        String numeroCompletatiFatturabili = monitoraggio.getFieldDataString("DatiMonitoraggioAmministrativo", "numeroCompletatiFatturabili");
        Double prezzoTotale = Double.parseDouble(prezzoPaziente) * Integer.parseInt(numeroCompletatiFatturabili);
        commonBean.addMetadataValue(pazientiCompletatiFatturabiliId.toString(), "DatiMonPazientiFatturabili", "PrezzoPaziente", prezzoPaziente, service);
        commonBean.addMetadataValue(pazientiCompletatiFatturabiliId.toString(), "DatiMonPazientiFatturabili", "numeroPazienti", numeroCompletatiFatturabili, service);
        commonBean.addMetadataValue(pazientiCompletatiFatturabiliId.toString(), "DatiMonPazientiFatturabili", "Prezzo", prezzoTotale, service);
        commonBean.addMetadataValue(pazientiCompletatiFatturabiliId.toString(), "DatiMonPazientiFatturabili", "Fatturabile", "1", service);
        String numeroCmpletatiFatturabiliNote = "Pazienti completati e fatturabili";
        commonBean.addMetadataValue(pazientiCompletatiFatturabiliId.toString(), "DatiMonPazientiFatturabili", "Note", numeroCmpletatiFatturabiliNote, service);
        //SIRER-67 inserisco voci pazienti NON completati ma fatturabili

        Long pazientiNonCompletatiFatturabiliId = commonBean.createChild(folderPazientiFatturabili.getId().toString(), folderPazientiFatturabili.getCreateUser(), "MonPazientiFatturabili", service);
        Element pazientiNonCompletatiFatturabili = service.getElement(pazientiNonCompletatiFatturabiliId);
        service.addTemplate(pazientiNonCompletatiFatturabili, "DatiMonPazientiFatturabili");
        commonBean.addMetadataValue(pazientiNonCompletatiFatturabiliId.toString(), "DatiMonPazientiFatturabili", "completati", "0");
        commonBean.addMetadataValue(pazientiNonCompletatiFatturabiliId.toString(), "DatiMonPazientiFatturabili", "BudgetLink", budget.getId().toString(), service);
        String numeroNONCompletatiFatturabili = monitoraggio.getFieldDataString("DatiMonitoraggioAmministrativo", "numeroNONCompletatiFatturabili");
        String numeroNONCompletatiFatturabiliNote = "Pazienti non completati ma con visite fatturabili " + monitoraggio.getFieldDataString("DatiMonitoraggioAmministrativo", "note");
        commonBean.addMetadataValue(pazientiNonCompletatiFatturabiliId.toString(), "DatiMonPazientiFatturabili", "numeroPazienti", numeroNONCompletatiFatturabili, service);
        commonBean.addMetadataValue(pazientiNonCompletatiFatturabiliId.toString(), "DatiMonPazientiFatturabili", "Note", numeroNONCompletatiFatturabiliNote, service);
        commonBean.addMetadataValue(pazientiNonCompletatiFatturabiliId.toString(), "DatiMonPazientiFatturabili", "Fatturabile", "1", service);
        //linko i prezzi
        prezzi = budgetStudio.getChildrenByType("FolderPrezzi").get(0).getChildren();
        for (Element currPrezzo : prezzi) {
            service.sync(currPrezzo);
            origElementId = currPrezzo.getFieldDataElement("PrezzoFinale", "Prestazione").get(0).getId();
            createdElementId = null;
            if (monTpxpMap.containsKey(origElementId)) {
                createdElementId = monTpxpMap.get(origElementId);
                template = "DatiMonPxT";
            } else if (monPxPMap.containsKey(origElementId)) {
                createdElementId = monPxPMap.get(origElementId);
                template = "DatiMonPxP";
            }
            if (createdElementId != null) {
                commonBean.addMetadataValue(createdElementId.toString(), template, "PrezzoLink", currPrezzo.getId().toString(), service);
                currPrezzoValue = currPrezzo.getFieldDataString("PrezzoFinale", "Prezzo");
                if (!currPrezzoValue.matches("-?\\d+(\\.\\d+)?")) {
                    currPrezzoValue = currPrezzo.getFieldDataElement("PrezzoFinale", "Prestazione").get(0).getFieldDataString("Costo", "TransferPrice");
                }
                commonBean.addMetadataValue(createdElementId.toString(), template, "Prezzo", currPrezzoValue, service);
            }
        }

        //linko il prezzo per PxPCTC
        Set<Long> origSet = monPxPCTCMap.keySet();
        for (Long currOrigElementId : origSet) {

            createdElementId = monPxPCTCMap.get(currOrigElementId);
            commonBean.addMetadataValue(createdElementId.toString(), "DatiMonPxP", "PrezzoLink", currOrigElementId.toString(), service);
            currPrezzoElement = service.getElement(currOrigElementId);
            currPrezzoValue = currPrezzoElement.getFieldDataString("Costo", "Prezzo");
            if (!currPrezzoValue.matches("-?\\d+(\\.\\d+)?")) {
                currPrezzoValue = currPrezzoElement.getFieldDataString("Costo", "TransferPrice");
            }
            commonBean.addMetadataValue(createdElementId.toString(), "DatiMonPxP", "Prezzo", currPrezzoValue, service);

        }

        service.getTxManager().commitAndKeepAlive();
        makeSureSessionIsOpen(service);
        folderTPxP = service.sync(folderTPxP);
        Collection<Element> monTPxP = folderTPxP.getChildren();
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "createMonBudgetLinks:passo pre 6 " + folderTPxP.getId().toString() + " FIGLI " + String.valueOf(monTPxP.size()) + " elementi mappa " + String.valueOf(monTpxpMap.size()));
        for (Long currElementId : monTpxpMap.values()) {
            //service.sync(currElement);
            Element currElement = service.getElement(currElementId);

            Element relatedPrestazione = (Element) ((Element) currElement.getfieldData("DatiMonPxT", "TPxP").get(0)).getfieldData("tp-p", "Prestazione").get(0);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "createMonBudgetLinks:passo 6 prestazione " + relatedPrestazione.getId().toString());
            commonBean.addMetadataValue(currElement.getId().toString(), "DatiMonPxT", "MonPrestazione", monPrestazioniMap.get(relatedPrestazione.getId()), service);

            Element relatedTp = (Element) ((Element) currElement.getfieldData("DatiMonPxT", "TPxP").get(0)).getfieldData("tp-p", "TimePoint").get(0);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "createMonBudgetLinks:passo 6 tp " + relatedTp.getId().toString());
            commonBean.addMetadataValue(currElement.getId().toString(), "DatiMonPxT", "MonTimePoint", monTPMap.get(relatedTp.getId()), service);
        }

        it.cineca.siss.axmr3.log.Log.debug(getClass(), "createFattBudgetLinks:passo 8 ");

    }

    public void correggiCentroMonBudgetLinks(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element centro = service.getElement(Long.parseLong(elementId));
        List<Element> pazienti = centro.getChildrenByType("MonitoraggioAmministrativo");
        for (Element paziente : pazienti) {
            correggiMonBudgetLinks(paziente.getId().toString(), service);
        }
        commonBean.closeDocumentService(service);
    }

    public void correggiMonBudgetLinks(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        correggiMonBudgetLinks(elementId, service);
        commonBean.closeDocumentService(service);
    }

    public void correggiMonBudgetLinks(String elementId, DocumentService service) throws Exception {
        //DocumentService service=commonBean.getDocumentService();
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "createMonBudgetLinks:passo 1 ");
        HashMap<Long, Long> monPrestazioniMap = new HashMap<Long, Long>();
        HashMap<Long, Long> monTPMap = new HashMap<Long, Long>();
        HashMap<Long, Long> monTpxpMap = new HashMap<Long, Long>();
        HashMap<Long, Long> monPxPMap = new HashMap<Long, Long>();
        HashMap<Long, Long> monPxPCTCMap = new HashMap<Long, Long>();
        Collection<Element> prezzi;
        Long origElementId;
        Long createdElementId;
        String template = "";
        String currPrezzoValue = "";
        Integer totVisite = 0;

        Element currPrezzoElement;
        Element monitoraggio = service.getElement(Long.parseLong(elementId));
        service.addTemplate(monitoraggio, "DatiCustomMonitoraggioAmministrativo");
        Element center = monitoraggio.getParent();
        //it.cineca.siss.axmr3.log.Log.debug(getClass(),"createFattBudgetLinks:center "+center.getId().toString());
        Element budget = getBudgetChiuso(center, service);
        Element budgetStudio = getBudgetDefinitivo(budget, service);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "createMonBudgetLinks:passo 2 ");
        Element folderPrestazioni = monitoraggio.getChildrenByType("FolderMonPrestazioni").get(0);
        Element folderBracci = monitoraggio.getChildrenByType("FolderMonBracci").get(0);
        Element folderTP = monitoraggio.getChildrenByType("FolderMonTimePoint").get(0);
        Element folderTPxP = monitoraggio.getChildrenByType("FolderMonPxT").get(0);
        Element folderPxP = monitoraggio.getChildrenByType("FolderMonPxP").get(0);
        Collection<Element> monPrezzi = folderTPxP.getChildren();
        Collection<Element> monTps = folderTP.getChildren();
        HashMap<Long, String> mapPrezzi = new HashMap<Long, String>();


        //linko i prezzi
        prezzi = budgetStudio.getChildrenByType("FolderPrezzi").get(0).getChildren();
        for (Element currPrezzo : prezzi) {
            List<Element> links = currPrezzo.getFieldDataElement("PrezzoFinale", "Prestazione");
            if (links.size() > 0) {
                mapPrezzi.put(links.get(0).getId(), currPrezzo.getId().toString());
            }

        }

        for (Element currPrestazione : monPrezzi) {
            List<Element> tpxpLinks = currPrestazione.getFieldDataElement("DatiMonPxT", "TPxP");
            List<Element> prezziLinks = currPrestazione.getFieldDataElement("DatiMonPxT", "PrezzoLink");
            List<Element> fatturaLinks = currPrestazione.getFieldDataElement("DatiMonPxT", "Fattura");
            if (prezziLinks.isEmpty() && !tpxpLinks.isEmpty() && mapPrezzi.containsKey(tpxpLinks.get(0).getId())) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "OK funziona per " + currPrestazione.getId().toString());
                commonBean.addMetadataValue(currPrestazione, "DatiMonPxT", "PrezzoLink", mapPrezzi.get(tpxpLinks.get(0).getId()), service);
            } else if (prezziLinks.isEmpty()) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Non funziona per " + currPrestazione.getId().toString());
            }
            commonBean.addMetadataValue(currPrestazione, "DatiMonPxT", "Fattura", "", service);
            commonBean.addMetadataValue(currPrestazione, "DatiMonPxT", "Fatturato", "", service);
        }

        for (Element currTp : monTps) {

            commonBean.addMetadataValue(currTp, "DatiFatturazioneTP", "ReportFatturazione", "", service);
            commonBean.addMetadataValue(currTp, "DatiFatturazioneTP", "ReportFatturazione", "", service);

        }
        for (Element currPXP : folderPxP.getChildren()) {
            commonBean.addMetadataValue(currPXP, "DatiMonPxP", "Fatturabile", currPXP.getFieldDataString("DatiMonPxP", "Fatturato"), service);
            commonBean.addMetadataValue(currPXP, "DatiMonPxP", "Fatturato", "0", service);

        }


        it.cineca.siss.axmr3.log.Log.debug(getClass(), "createFattBudgetLinks:passo 8 ");
        //commonBean.closeDocumentService(service);
    }

    public Element correggiSingleMonBudgetLink(Element currPrestazione, LinkedList<Element> prezzoFound, DocumentService service) throws Exception {

        it.cineca.siss.axmr3.log.Log.debug(getClass(), "correggiSingleMonBudgetLink:passo 1 ");
        if (prezzoFound != null && !prezzoFound.isEmpty()) {
            return prezzoFound.get(0);
        }
        Collection<Element> prezzi;
        Element monitoraggio = currPrestazione.getParent().getParent();
        service.addTemplate(monitoraggio, "DatiCustomMonitoraggioAmministrativo");
        Element center = monitoraggio.getParent();
        //it.cineca.siss.axmr3.log.Log.debug(getClass(),"createFattBudgetLinks:center "+center.getId().toString());
        Element budget = getBudgetChiuso(center, service);
        Element budgetStudio = getBudgetDefinitivo(budget, service);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "createMonBudgetLinks:passo 2 ");
        HashMap<Long, Element> mapPrezzi = new HashMap<Long, Element>();
        //linko i prezzi
        prezzi = budgetStudio.getChildrenByType("FolderPrezzi").get(0).getChildren();
        for (Element currPrezzo : prezzi) {
            List<Element> links = currPrezzo.getFieldDataElement("PrezzoFinale", "Prestazione");
            if (links.size() > 0) {
                mapPrezzi.put(links.get(0).getId(), currPrezzo);
            }

        }
        List<Element> tpxpLinks = currPrestazione.getFieldDataElement("DatiMonPxT", "TPxP");
        List<Element> prezziLinks = currPrestazione.getFieldDataElement("DatiMonPxT", "PrezzoLink");

        Element retPrezzo = null;
        if (prezziLinks.isEmpty() && !tpxpLinks.isEmpty() && mapPrezzi.containsKey(tpxpLinks.get(0).getId())) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "OK funziona per " + currPrestazione.getId().toString());
            retPrezzo = mapPrezzi.get(tpxpLinks.get(0).getId());
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Prezzo  " + retPrezzo.getId().toString());
            commonBean.addMetadataValue(currPrestazione, "DatiMonPxT", "PrezzoLink", retPrezzo.getId().toString(), service);
        } else if (prezziLinks.isEmpty()) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Non funziona per " + currPrestazione.getId().toString());
        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "correggiSingleMonBudgetLink:fine ");
        return retPrezzo;
    }


    public void createChildren(String elId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        createChildren(elId, service);
        commonBean.closeDocumentService(service);
    }

    public void createChildren(String elId, DocumentService service) throws Exception {

        Element el = service.getElement(Long.parseLong(elId));
        Collection<ElementType> types = el.getType().getAllowedChilds();
        for (ElementType type : types) {
            if (el.getChildrenByType(type.getTypeId()) == null || el.getChildrenByType(type.getTypeId()).isEmpty()) {
                //TODO: creo oggetti dalla stringa typeID. meglio usare id numerico.
                commonBean.createChild(elId, el.getCreateUser(), type.getTypeId(), service);
            }
        }
    }

    public Element getBudgetChiuso(Element center, DocumentService service) throws Exception {

        it.cineca.siss.axmr3.log.Log.debug(getClass(), "getBudgetChiuso:passo 1 ");
        String budgetId = center.getFieldDataString("statoValidazioneCentro", "idBudgetApproved");
        if (!budgetId.isEmpty()) {
            Element budget = service.getElement(Long.parseLong(budgetId));
            return budget;
        }
        return null;
    }

    public Element getBudgetDefinitivo(Element budget, DocumentService service) throws Exception {


        Element budgetStudio = null;
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "getBudgetDefinitivo:passo 1 " + budget.getId().toString());
        Collection<Element> allBudgets = budget.getChildrenByType("FolderBudgetStudio").get(0).getChildren();
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "getBudgetDefinitivo:passo 2 ");
        boolean valid = false;
        for (Element currBudget : allBudgets) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "getBudgetDefinitivo:passo 3 " + currBudget.getId().toString());

            if (currBudget.getfieldData("BudgetCTC", "Definitivo") != null && currBudget.getfieldData("BudgetCTC", "Definitivo").size() > 0 && currBudget.getfieldData("BudgetCTC", "Definitivo").get(0).equals("1"))
                budgetStudio = currBudget;
        }
        if (budgetStudio != null) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "getBudgetDefinitivo:budgetStudio= " + budgetStudio.getId().toString());
        } else {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "getBudgetDefinitivo:nessun budgetStudio ");
        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "getBudgetDefinitivo:passo 4 ");
        return budgetStudio;

    }

    public HashMap<Long, Long> addFattPrestazioni(Element fatturazione, Collection<Element> elements, DocumentService service) throws Exception {
        return addBudgetLinks(fatturazione, elements, "PrestazioniFatt", "DatiPrestazioniFatt", "PrestazioneBudget", service);
    }

    public HashMap<Long, Long> addFattTP(Element fatturazione, Collection<Element> elements, DocumentService service) throws Exception {
        return addBudgetLinks(fatturazione, elements, "TPFatt", "DatiTPFatt", "TPBudget", service);

    }

    public HashMap<Long, Long> addBudgetLinks(Element fatturazione, Collection<Element> collection, String type, String template, String field, DocumentService service) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "addBudgetLinks");
        String fattId = fatturazione.getId().toString();
        HashMap<Long, Long> result = new HashMap<Long, Long>();
        if (collection != null && collection.size() > 0) {
            for (Element currItem : collection) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "addBudgetLinks createChild");
                Long childId = commonBean.createChild(fattId, fatturazione.getCreateUser(), type, service);
                commonBean.addMetadataValue(childId.toString(), template, field, currItem.getId().toString(), service);
                result.put(currItem.getId(), childId);
            }
        }
        return result;
    }

    public HashMap<Long, Long> addMonPrestazioni(Element monitoraggio, Collection<Element> elements, DocumentService service) throws Exception {
        return addBudgetLinks(monitoraggio, elements, "MonPrestazioni", "DatiMonPrestazioni", "Prestazione", service);
    }

    public HashMap<Long, Long> addMonBracci(Element monitoraggio, Collection<Element> elements, DocumentService service) throws Exception {
        return addBudgetLinks(monitoraggio, elements, "MonBraccio", "DatiMonBraccio", "Braccio", service);
    }

    public HashMap<Long, Long> addMonTP(Element monitoraggio, Collection<Element> elements, DocumentService service) throws Exception {
        return addBudgetLinks(monitoraggio, elements, "MonTimePoint", "DatiMonTimePoint", "TimePoint", service);

    }

    public HashMap<Long, Long> addMonTpxp(Element monitoraggio, Collection<Element> elements, DocumentService service) throws Exception {
        return addBudgetLinks(monitoraggio, elements, "MonPxT", "DatiMonPxT", "TPxP", service);

    }

    public HashMap<Long, Long> addMonPxP(Element monitoraggio, Collection<Element> elements, DocumentService service) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "addMonPxP");
        return addBudgetLinks(monitoraggio, elements, "MonPxP", "DatiMonPxP", "BudgetLink", service);

    }


    public HashMap<Long, Long> addMonPxPCTC(Element monitoraggio, Collection<Element> elements, DocumentService service) throws Exception {
        return addBudgetLinks(monitoraggio, elements, "MonPxPCTC", "DatiMonPxP", "BudgetLink", service);

    }

    public Long createChildAcconto(String elementId, String userid, String typeId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Long ret = createChildAcconto(elementId, userid, typeId, service);
        commonBean.closeDocumentService(service);
        service = commonBean.getDocumentService();
        commonBean.addMetadataValue(elementId, "StatoScheduling", "Iniziato", "1", service);
        commonBean.closeDocumentService(service);
        return ret;

    }

    public Long createChildAcconto(String elementId, String userid, String typeId, DocumentService service) throws Exception {

        HashMap<String, String> data = new HashMap<String, String>();
        data.put("DatiFattura_Tipologia", "1###Acconto");
        return commonBean.createChild(elementId, userid, typeId, data, service);

    }

    public void attachRibaltamentoProcess(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        //Element feedback = service.getElement(elementId);
        Element fattura = service.getElement(elementId);
        String processDefinition = "Ribaltamento";
        List<ProcessInstance> activeProcesses;
        boolean alreadyStarted = (fattura.getChildrenByType("Ribaltamento").size() > 0);


        //if(feedback.getFieldDataCode("DatiFatturaFeedback","Feedback").equals("1") && !alreadyStarted){    //incasso //TOSCANA-89 facendo partire il ribaltamento alla creazione della fattura annullo il controllo sulla fattura incassata
        if (!alreadyStarted) {    //incasso
            activeProcesses = service.getActiveProcesses(fattura);
            for (ProcessInstance process : activeProcesses) {
                if (process.getProcessDefinitionId().equals(processDefinition)) {
                    alreadyStarted = true;
                }
            }
            service.startProcess("CTC", fattura, processDefinition);
        }
        commonBean.closeDocumentService(service);
    }

    public Long createChildRibaltamento(String elementId, DelegateExecution execution) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "INIZIO createChildRibaltamentoDaFattura richiamato da WF " + elementId);
        DocumentService service = commonBean.getDocumentService();
        Element fattura = service.getElement(elementId);
        Long result = createChildRibaltamentoDaFatt(fattura, service);
        execution.setVariable("elementId", result.toString());
        commonBean.closeDocumentService(service);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "FINE createChildRibaltamentoDaFattura richiamato da WF " + elementId);
        return result;
    }

    //metodo rinominato da createChildRibaltamento in createChildRibaltamentoDaFattura perchè ACTIVITI certe volte sbaglia a richiamarlo perchè non gestisce bene la firma dei metodi
    public Long createChildRibaltamentoDaFatt(Element fattura, DocumentService service) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "INIZIO createChildRibaltamentoDaFattura per fattura " + fattura.getId());
        String typeId = "Ribaltamento";
        Long ribaltamentoId;
        List<Element> feedbacks;
        List<Element> cdcsMilestone;
        List<Element> vociMonitoraggio = fattura.getChildrenByType("LinkVoceMonitoraggioFattura");
        List<Element> vociScheduling = fattura.getChildrenByType("LinkVoceSchedulingFattura");

        HashMap<String, String> dataRibaltamento = new HashMap<String, String>();
        double totaleIncassato = 0.0;
        boolean incassato = false;
        HashMap<String, String> dataCdc = new HashMap<String, String>();
        HashMap<String, String> cdcsDiz = new HashMap<String, String>();
        HashMap<String, Double> cdcsTotalsPrezzi = new HashMap<String, Double>();
        HashMap<String, Double> cdcsTotalsTP = new HashMap<String, Double>();
        HashMap<String, Double> cdcsTotalsSSN = new HashMap<String, Double>();
        double totaleCDC = 0.0;
        double totaleSSN = 0.0;
        String cdcCode = "";
        String cdcCodeFull = "";
        String cdcDecode = "";
        String currSimpleCode = "";


        dataRibaltamento.put("DatiRibaltamento_TotaleFattura", fattura.getFieldDataString("DatiFatturaWF", "totaleFattura"));
        feedbacks = fattura.getChildrenByType("FatturaFeedback");
        for (Element feedback : feedbacks) {
            if (feedback.getFieldDataCode("DatiFatturaFeedback", "Feedback").equals("1")) { //incassata
                incassato = true;
                try {
                    totaleIncassato += Double.parseDouble(feedback.getFieldDataString("DatiFatturaFeedback", "Importo"));
                } catch (NumberFormatException ex) {

                }
            }
        }
        if (totaleIncassato == 0.0 && incassato) {
            try {
                totaleIncassato = Double.parseDouble(fattura.getFieldDataString("DatiFatturaWF", "totaleFattura"));
            } catch (NumberFormatException ex) {

            }

        }
        dataRibaltamento.put("DatiRibaltamento_TotaleIncassato", String.valueOf(totaleIncassato));


        //copio le percentuali di riversamento da Centro_Feasibility
        Element elCentro = fattura.getParent().getParent().getParent();//fattura->RichiestaFatturazione->Fatturazione->Centro
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "copio le percentuali di riversamento da Centro_Feasibility");
        dataRibaltamento.put("RibaltamentoFondi_valorePerc6Feas", elCentro.getFieldDataString("Feasibility_valorePerc6"));
        dataRibaltamento.put("RibaltamentoFondi_compensiDirigenteFeas", elCentro.getFieldDataString("Feasibility_compensiDirigente"));
        dataRibaltamento.put("RibaltamentoFondi_noteCompensiDirigenteFeas", elCentro.getFieldDataString("Feasibility_noteCompensiDirigente"));
        dataRibaltamento.put("RibaltamentoFondi_compensiRepartoFeas", elCentro.getFieldDataString("Feasibility_compensiReparto"));
        dataRibaltamento.put("RibaltamentoFondi_noteCompensiRepartoFeas", elCentro.getFieldDataString("Feasibility_noteCompensiReparto"));
        dataRibaltamento.put("RibaltamentoFondi_valorePerc1Feas", elCentro.getFieldDataString("Feasibility_valorePerc1"));
        dataRibaltamento.put("RibaltamentoFondi_valorePerc1NoteFeas", elCentro.getFieldDataString("Feasibility_valorePerc1Note"));
        dataRibaltamento.put("RibaltamentoFondi_valorePerc2Feas", elCentro.getFieldDataString("Feasibility_valorePerc2"));
        dataRibaltamento.put("RibaltamentoFondi_valorePerc3Feas", elCentro.getFieldDataString("Feasibility_valorePerc3"));
        dataRibaltamento.put("RibaltamentoFondi_valorePerc4Feas", elCentro.getFieldDataString("Feasibility_valorePerc4"));
        dataRibaltamento.put("RibaltamentoFondi_valorePerc7Feas", elCentro.getFieldDataString("Feasibility_valorePerc7"));
        dataRibaltamento.put("RibaltamentoFondi_valorePercFarmacologiaFeas", elCentro.getFieldDataString("Feasibility_valorePercFarmacologia"));
        dataRibaltamento.put("RibaltamentoFondi_valorePercUniversitarioFeas", elCentro.getFieldDataString("Feasibility_valorePercUniversitario"));
        dataRibaltamento.put("RibaltamentoFondi_valorePerc5Feas", elCentro.getFieldDataString("Feasibility_valorePerc5"));
        dataRibaltamento.put("RibaltamentoFondi_notePerc5Feas", elCentro.getFieldDataString("Feasibility_notePerc5"));
        ribaltamentoId = commonBean.createChild(fattura, fattura.getCreateUser(), typeId, dataRibaltamento, service);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Preparo ribaltamento");
        for (Element voce : vociMonitoraggio) {
            Element currLink = voce.getFieldDataElement("LinkRichiesta", "Richiesta").get(0);
            cdcsMilestone = currLink.getChildrenByType("CDCMilestone");

            for (Element cdc : cdcsMilestone) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "tovo mileston cdc =" + cdc.getId().toString());
                cdcCode = cdc.getFieldDataString("CDCSummary", "CDCCode");
                cdcDecode = cdc.getFieldDataString("CDCSummary", "CDCDecode");
                if (!cdcCode.isEmpty() && !cdcDecode.isEmpty()) {
                    cdcCodeFull = cdcCode + " - " + cdcDecode;
                } else {
                    cdcCodeFull = cdcCode + cdcDecode;
                }
                cdcsDiz.put(cdcCodeFull, cdc.getFieldDataString("CDCSummary", "CDCDecode"));
                if (cdcsTotalsTP.containsKey(cdcCodeFull)) {
                    totaleCDC = cdcsTotalsTP.get(cdcCodeFull);
                } else {
                    totaleCDC = 0.0;
                }
                totaleCDC += Double.parseDouble(cdc.getFieldDataString("CDCSummary", "TransferPrice"));
                cdcsTotalsTP.put(cdcCodeFull, totaleCDC);

                if (cdcsTotalsPrezzi.containsKey(cdcCodeFull)) {
                    totaleCDC = cdcsTotalsPrezzi.get(cdcCodeFull);
                } else {
                    totaleCDC = 0.0;
                }
                totaleCDC += Double.parseDouble(cdc.getFieldDataString("CDCSummary", "Prezzo"));
                cdcsTotalsPrezzi.put(cdcCodeFull, totaleCDC);

                if (cdcsTotalsSSN.containsKey(cdcCodeFull)) {
                    totaleSSN = cdcsTotalsSSN.get(cdcCodeFull);

                } else {
                    totaleSSN = 0.0;
                }
                try {
                    totaleSSN += Double.parseDouble(cdc.getFieldDataString("CDCSummary_SSN"));
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "aggiungo SSN 1 per currCode " + cdcCodeFull + " = " + totaleSSN);
                } catch (Exception ex) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "errore SSN 1 per currCode " + cdcCodeFull);
                    Logger.getLogger(this.getClass()).error(ex.getMessage(), ex);
                }
                cdcsTotalsSSN.put(cdcCodeFull, totaleSSN);
            }
        }

        for (Element voce : vociScheduling) {
            cdcsMilestone = voce.getFieldDataElement("LinkRichiesta", "Richiesta").get(0).getChildrenByType("CDCMilestone");
            for (Element cdc : cdcsMilestone) {
                cdcCode = cdc.getFieldDataString("CDCSummary", "CDCCode");
                cdcDecode = cdc.getFieldDataString("CDCSummary", "CDCDecode");
                if (!cdcCode.isEmpty() && !cdcDecode.isEmpty()) {
                    cdcCodeFull = cdcCode + " - " + cdcDecode;
                } else {
                    cdcCodeFull = cdcCode + cdcDecode;
                }
                cdcsDiz.put(cdcCodeFull, cdc.getFieldDataString("CDCSummary", "CDCDecode"));
                if (cdcsTotalsTP.containsKey(cdcCodeFull)) {
                    totaleCDC = cdcsTotalsTP.get(cdcCodeFull);
                } else {
                    totaleCDC = 0.0;
                }
                if (!cdc.getFieldDataString("CDCSummary", "TransferPrice").isEmpty()) {
                    totaleCDC += Double.parseDouble(cdc.getFieldDataString("CDCSummary", "TransferPrice"));
                }
                cdcsTotalsTP.put(cdcCodeFull, totaleCDC);
                if (cdcsTotalsPrezzi.containsKey(cdcCodeFull)) {
                    totaleCDC = cdcsTotalsPrezzi.get(cdcCodeFull);
                } else {
                    totaleCDC = 0.0;
                }
                if (!cdc.getFieldDataString("CDCSummary", "Prezzo").isEmpty()) {
                    totaleCDC += Double.parseDouble(cdc.getFieldDataString("CDCSummary", "Prezzo"));
                }
                cdcsTotalsPrezzi.put(cdcCodeFull, totaleCDC);

                if (cdcsTotalsSSN.containsKey(cdcCodeFull)) {
                    totaleSSN = cdcsTotalsSSN.get(cdcCodeFull);
                } else {
                    totaleSSN = 0.0;
                }
                try {
                    totaleSSN += Double.parseDouble(cdc.getFieldDataString("CDCSummary", "SSN"));
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "aggiungo SSN 2 per currCode " + cdcCodeFull + " = " + totaleSSN);
                } catch (Exception ex) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "errore SSN per currCode " + cdcCodeFull);
                }
                cdcsTotalsSSN.put(cdcCodeFull, totaleSSN);
            }
        }

        for (String currCode : cdcsDiz.keySet()) {
            currSimpleCode = currCode;
            currSimpleCode = currSimpleCode.replaceAll("([ -]{3})?" + cdcsDiz.get(currCode), "");
            dataCdc.put("CDCSummary_CDCCode", currSimpleCode);
            dataCdc.put("CDCSummary_CDCDecode", cdcsDiz.get(currCode));
            dataCdc.put("CDCSummary_TransferPrice", cdcsTotalsTP.get(currCode).toString());
            dataCdc.put("CDCSummary_Prezzo", cdcsTotalsPrezzi.get(currCode).toString());
            dataCdc.put("CDCSummary_SSN", cdcsTotalsSSN.get(currCode).toString());
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "SSN per id " + ribaltamentoId.toString() + " currCode " + currCode + " = " + cdcsTotalsSSN.get(currCode).toString());
            commonBean.createChild(ribaltamentoId.toString(), "CTC", "CDCRibaltamento", dataCdc, service);
        }
        Element el = service.getElement(ribaltamentoId);
        String group = getCTOgroup(commonBean.getUser(elCentro.getCreateUser())).replace("CTO_", "UR_");//TOSCANA-98
        //- do i permessi alla RAGIONERIA (UR) sul ribaltamento
        commonBean.changePermissionToGroupRecursive(ribaltamentoId.toString(), "V,B,M,AC", "ribaltamento", group, service);//TOSCANA-98
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "FINE createChildRibaltamentoDaFattura con id " + ribaltamentoId);
        return ribaltamentoId;

    }


    public void closeRibaltamento(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(elementId);
        commonBean.changePermissionToGroup(elementId, "V,B", "ribaltamento", "CTC", service);
        commonBean.addMetadataValue(elementId, "DatiRibaltamento", "DataRichiesta", commonBean.sysdate(), service);
        String group = getCTOgroup(commonBean.getUser(el.getCreateUser())).replace("CTO_", "UR_");//TOSCANA-177
        commonBean.changePermissionToGroup(elementId, "V,M,B", "ribaltamento", group, service);
        //Giulio - do i permessi alla RAGIONERIA (UR) sul ribaltamento
        //commonBean.changePermissionToGroup(elementId,"V,B,AC","ribaltamento",group,service);//TOSCANA-177
        //commonBean.changePermissionToGroup(elementId,"V,B,AC","ribaltamento","UR",service);
        //do i diritti ai figli del ribaltamento
        Element elRibaltamento = service.getElement(Long.parseLong(elementId));
        Collection<Element> figliRibaltamento = elRibaltamento.getChildren();
        for (Element currfiglio : figliRibaltamento) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "figli di ribaltamento=" + currfiglio);
            //if(currfiglio.getTypeName().equals("allegato")){
            //it.cineca.siss.axmr3.log.Log.debug(getClass(),"figlio allegato");
            commonBean.changePermissionToGroupRecursive(elRibaltamento, "V,M,B", "", group, service);//TOSCANA-177
            commonBean.changePermissionToGroupRecursive(elRibaltamento, "V,M,B", "", "UR", service);
            //}
        }


        commonBean.closeDocumentService(service);
    }

    public void confermaRibaltamento(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(elementId);
        commonBean.changePermissionToGroup(elementId, "V,B", "ribaltamento", "CTC", service);
        String group = getCTOgroup(commonBean.getUser(el.getCreateUser())).replace("CTO_", "UR_");//TOSCANA-177
        //Giulio - do i permessi alla RAGIONERIA (UR) sul ribaltamento
        commonBean.changePermissionToGroup(elementId, "V,B", "ribaltamento", group, service);//TOSCANA-177
        commonBean.changePermissionToGroup(elementId, "V,B", "ribaltamento", "UR", service);
        commonBean.addMetadataValue(elementId, "DatiRibaltamento", "DataConferma", commonBean.sysdate(), service);
        commonBean.closeDocumentService(service);
    }

    public Long ValutazioneRI(String elementId) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "inizio ValutazioneRI");
        DocumentService service = commonBean.getDocumentService();

        Long ValutazioneRIId;
        ValutazioneRIId = commonBean.createChild(elementId, "CTC", "ValutazioneRI", service);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "ValutazioneRIId = " + ValutazioneRIId);

        commonBean.closeDocumentService(service);

        return ValutazioneRIId;
    }

    public void IstruttoriaCE(String elementId) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "inizio IstruttoriaCE");
        DocumentService service = commonBean.getDocumentService();

        Element istruttoriaCE = service.getElement(elementId);
        Element elCentro = istruttoriaCE.getParent();
        Element elStudio = elCentro.getParent();
        String documentazioneCompleta = istruttoriaCE.getFieldDataCode("IstruttoriaCE", "DocCompleta");
        String riapertura = istruttoriaCE.getFieldDataCode("IstruttoriaCE", "RiapriSoloDoc");
        if (documentazioneCompleta.equals("1")) {//SI
            commonBean.addMetadataValue(elementId, "IstruttoriaCE", "istruttoriaWFinviata", "1", service);
            commonBean.changePermissionToGroup(elementId, "V,B", "", "SEGRETERIA", service);
            commonBean.changePermissionToUser(elementId, "V,B", "", istruttoriaCE.getCreateUser(), service);
            commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "idIstruttoriaCEPositiva", elementId, service);
            commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "delibNumIstrCEPositiva", istruttoriaCE.getFieldDataString("IstruttoriaCE_DelibNum"), service);
        } else {//NO
            Logger.getLogger(this.getClass()).debug("--[IstruttoriaCE] - Istruttoria NEGATIVA!");

            if (riapertura.equalsIgnoreCase("2")) {
                //SOLO DOC
                commonBean.addMetadataValue(elementId, "IstruttoriaCE", "istruttoriaWFinviata", "1", service);
                commonBean.changePermissionToGroup(elementId, "V,B", "", "SEGRETERIA", service);
                commonBean.changePermissionToUser(elementId, "V,B", "", istruttoriaCE.getCreateUser(), service);
                commonBean.changePermissionToUser(elCentro.getId().toString(), "V,A,B", "", elCentro.getCreateUser(), service);//se il creator del centro è un SP allora riapro l'inserimento documenti
                System.out.println("########################################### --[IstruttoriaCE] - CAMBIO PERMESSI A elCentro.getCreateUser(): "+elCentro.getCreateUser());
                commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "idIstruttoriaCEPositiva", "", service);
                commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "delibNumIstrCEPositiva","", service);
                System.out.println("########################################### --[IstruttoriaCE] - RIAPERTA SOLO DOC!");
            } else {
                //Elimino i permessi in visibilità dati alla chiusura della feasibilityPI (CloseAllTemplates)

                commonBean.changePermissionToGroup(elStudio.getId() + "", "V,M,A,B", null, "SEGRETERIA");
                commonBean.changePermissionToGroup(elStudio.getId() + "", "V,M,A,B", null, "SP");
                commonBean.changePermissionToGroup(elStudio.getId() + "", "V,M,A,B", null, "CTC");
                commonBean.changePermissionToUser(elStudio.getId() + "", "V,M,A,P,B", null, elStudio.getCreateUser());

                String[] gruppiUtenti = {"CTC", "SP", "PI","COORD", "REGIONE", "SEGRETERIA", "DATAMANAGER","DIR"};

                for (String gr : gruppiUtenti) {
                    commonBean.removeTemplatePermissionToGroup(elStudio.getId(), "datiStudio", gr);
                    commonBean.removeTemplatePermissionToGroup(elStudio.getId(), "datiCoordinatore", gr);
                    commonBean.removeTemplatePermissionToGroup(elCentro.getId(), "IdCentro", gr);
                    commonBean.removeTemplatePermissionToGroup(elCentro.getId(), "DatiCentro", gr);
                    commonBean.removeTemplatePermissionToGroup(elCentro.getId(), "AnalisiCentro", gr);
                    commonBean.removeTemplatePermissionToGroup(elCentro.getId(), "Feasibility", gr);
                    commonBean.removeTemplatePermissionToGroup(elCentro.getId(), "ServiziCoinvolti", gr);
                    for (Element farmacoDepot : elCentro.getChildrenByType("DepotFarmaco")) {
                        commonBean.removeTemplatePermissionToGroup(farmacoDepot.getId().toString(), "depotFarmaco", gr);
                    }

                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "resetto i permessi per il gruppo" + gr);
                }

                String[] figliStudio = {"PromotoreStudio", "FinanziatoreStudio", "CROStudio", "Farmaco", "allegato", "ProdottoStudio", "Emendamento"};
                for (String childType : figliStudio) {
                    for (Element child : elStudio.getChildrenByType(childType)) {
                        commonBean.changePermissionToGroup(child.getId() + "", "V,M,E,A,B", null, "SEGRETERIA");
                        commonBean.changePermissionToGroup(child.getId() + "", "V,M,E,A,B", null, "SP");
                        commonBean.changePermissionToGroup(child.getId() + "", "V,M,MP,A,P,B", null, "CTC");
                        commonBean.changePermissionToUser(child.getId() + "", "V,M,MP,A,P,B", null, child.getCreateUser());
                    }
                }

                //service.setDefaultPermissionOnElement(elCentro);//ridiamo i permessi originali al centro
                List<ProcessInstance> activeProcesses = service.getActiveProcesses(elCentro);
                for (ProcessInstance p : activeProcesses) {
                    String myProcessId = p.getProcessDefinitionId();
                    String myProcessKey = service.getProcessEngine().getRepositoryService().getProcessDefinition(myProcessId).getKey();
                    if (myProcessKey.equals("ce-center-validation")) {
                        service.getProcessEngine().getRuntimeService().deleteProcessInstance(p.getProcessInstanceId(), "PROCESS_DELETE");
                    }
                }
                String pInstanceId = service.startProcess("PROCESS", elCentro, "ce-center-validation", true);//faccio ripartire Fattibilità
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "LUIGI: PROCESSO RILANCIATO" + pInstanceId);
                //service.setDefaultPermissionOnElement(elStudio);//ridiamo i permessi originali allo studio

                commonBean.addMetadataValue(elementId, "IstruttoriaCE", "istruttoriaWFinviata", "1", service);
                commonBean.changePermissionToGroup(elementId, "V,B", "", "SEGRETERIA", service);
                commonBean.changePermissionToUser(elementId, "V,B", "", istruttoriaCE.getCreateUser(), service);
                commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "idIstruttoriaCEPositiva", "", service);
                commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "delibNumIstrCEPositiva", "", service);
                commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "fattLocale", "", service);
                commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "valCTC", "", service);
                Logger.getLogger(this.getClass()).debug("########################################### --[IstruttoriaCE] - RIAPERTO TUTTO!");
            }

        }
        commonBean.closeDocumentService(service);
    }


    public void IstruttoriaEme(String elementId) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "inizio IstruttoriaEme");
        DocumentService service = commonBean.getDocumentService();
        Element istruttoriaEmeId = service.getElement(elementId);
        Element elEmendamentoId = istruttoriaEmeId.getParent();

        HashMap<String, String> data = new HashMap<String, String>();
        data.put("ParereEme_idIstruttoria", istruttoriaEmeId.getId() + "");
        String EmeCentro = istruttoriaEmeId.getFieldDataDecode("IstruttoriaEme", "CentroEme");
        String EmeCentroId = istruttoriaEmeId.getFieldDataCode("IstruttoriaEme", "CentroEme");
        data.put("ParereEme_CentroEme", EmeCentro);
        data.put("ParereEme_CentroEmeId", EmeCentroId);

        commonBean.createChild(elEmendamentoId.getId() + "", istruttoriaEmeId.getCreateUser(), "ParereEme", data, service);

        commonBean.closeDocumentService(service);
    }

    public void ParereEme(String elementId) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "inizio ParereEme");
        DocumentService service = commonBean.getDocumentService();
        Element parereEme = service.getElement(elementId);
        Element elEmendamento = parereEme.getParent();
        Long elEmendamentoId = elEmendamento.getId();

        String EmeCentroId = parereEme.getFieldDataString("ParereEme", "CentroEmeId");
        String esitoParere = parereEme.getFieldDataCode("ParereEme", "esitoParere");

        IUser user = (IUser) SecurityContextHolder.getContext().getAuthentication().getPrincipal();

        Long emeSessionId = service.getEmendamentoSessionId(user, elEmendamentoId, Long.parseLong(EmeCentroId));

        if (emeSessionId > 0) {
            EmendamentoSession dataEme = service.getActiveEmeSession(emeSessionId);
            if (dataEme.getEndDt() == null && (esitoParere.equals("1") || esitoParere.equals("3") || esitoParere.equals("4"))) {
                List dataChange = service.approveEmendamentoChanges(emeSessionId, user);
            } else if (dataEme.getEndDt() == null && esitoParere.equals("2")) {
                List dataChange = service.rejectEmendamentoChanges(emeSessionId);
            }
        }
        commonBean.addMetadataValue(elementId, "ParereEme", "ParereWFinviato", "1", service);
        commonBean.closeDocumentService(service);
    }


    public void ChiudiDocumentazioneIstruttoriaCE(String elementId) throws Exception {
        //TODO: !!
    }

    public void ParereCE(String elementId) throws Exception {
        it.cineca.siss.axmr3.log.Log.info(getClass(), "inizio ParereCE");
        DocumentService service = commonBean.getDocumentService();

        Element parereCE = service.getElement(elementId);
        Element elCentro = parereCE.getParent();
        Element elStudio = elCentro.getParent();
        String esitoParere = parereCE.getFieldDataCode("ParereCe", "esitoParere");
        String riapertura = parereCE.getFieldDataCode("ParereCe", "RiapriSoloDoc");
        String riaperturaSezione = parereCE.getFieldDataCode("ParereCe", "SezioneDocumentale");
        int idEsitoParere = Integer.parseInt(esitoParere.split("###")[0]);
        it.cineca.siss.axmr3.log.Log.info(getClass(), " -- esito Parere: " + esitoParere + ", IDesito: " + idEsitoParere + ", elementId: " + elementId);
        List<ProcessInstance> activeProcesses;

        switch (idEsitoParere) {
            case 1: //Favorevole
                commonBean.addMetadataValue(elementId, "ParereCe", "ParereWFinviato", "1", service);
                commonBean.changePermissionToGroup(elementId, "V,B", "", "SEGRETERIA", service);
                commonBean.changePermissionToUser(elementId, "V,B", "", parereCE.getCreateUser(), service);
                commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "idParereCE", elementId, service);
                commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "parereCEPositivo", "1", service);

                activeProcesses = service.getActiveProcesses(elCentro);
                for (ProcessInstance p : activeProcesses) {
                    String myProcessId = p.getProcessDefinitionId();
                    String myProcessKey = service.getProcessEngine().getRepositoryService().getProcessDefinition(myProcessId).getKey();
                    if (myProcessKey.equals("RitiraCentro")) {
                        service.getProcessEngine().getRuntimeService().deleteProcessInstance(p.getProcessInstanceId(), "PROCESS_DELETE");
                    }
                }

                break;
            case 2: //Sospensivo
                Logger.getLogger(this.getClass()).info("--[ParereCE] - Parere SOSPENSIVO!");

                //Riapro documentazione
                if (riapertura.equalsIgnoreCase("2")) {
                    Logger.getLogger(this.getClass()).info("########################################### --[ParereCE] - RIAPERTO SOLO DOC!");
                    commonBean.addMetadataValue(elementId, "ParereCe", "ParereWFinviato", "1", service);
                    commonBean.changePermissionToGroup(elementId, "V,B", "", "SEGRETERIA", service);
                    commonBean.changePermissionToUser(elementId, "V,B", "", parereCE.getCreateUser(), service);
                    if (riaperturaSezione.equalsIgnoreCase("1") || riaperturaSezione.equalsIgnoreCase("3") ) {
                        //se il creator del centro è un SP allora riapro l'inserimento documenti a livello di centro
                        commonBean.changePermissionToUser(elCentro.getId().toString(), "V,A,B", "", elCentro.getCreateUser(), service);
                    }
                    if (riaperturaSezione.equalsIgnoreCase("2") || riaperturaSezione.equalsIgnoreCase("3") ) {
                        //se il creator del centro è un SP allora riapro l'inserimento documenti a livello di studio
                        commonBean.changePermissionToUser(elStudio.getId().toString(), "V,A,B", "", elStudio.getCreateUser(), service);
                    }
                    commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "idParereCE", "", service);
                    commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "parereCEPositivo", "", service);
                    //commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "idIstruttoriaCEPositiva", "", service);
                    //commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "delibNumIstrCEPositiva", "", service);
                }

                //Riapro feasibility
                if (riapertura.equalsIgnoreCase("1")) {
                    Logger.getLogger(this.getClass()).info("########################################### --[ParereCE] - RIAPERTO TUTTO!");
                    //Elimino i permessi in visibilità dati alla chiusura della feasibilityPI (CloseAllTemplates)

                    commonBean.changePermissionToGroup(elStudio.getId() + "", "V,M,A,B", null, "SEGRETERIA");
                    commonBean.changePermissionToGroup(elStudio.getId() + "", "V,M,A,B", null, "SP");
                    commonBean.changePermissionToGroup(elStudio.getId() + "", "V,M,A,B", null, "CTC");
                    commonBean.changePermissionToUser(elStudio.getId() + "", "V,M,A,P,B", null, elStudio.getCreateUser());

                    String[] gruppiUtenti = {"CTC", "SP", "PI","COORD", "REGIONE", "SEGRETERIA", "DATAMANAGER","DIR", "FARMACIA"};

                    for (String gr : gruppiUtenti) {
                        commonBean.removeTemplatePermissionToGroup(elStudio.getId(), "datiStudio", gr);
                        commonBean.removeTemplatePermissionToGroup(elStudio.getId(), "datiCoordinatore", gr);
                        commonBean.removeTemplatePermissionToGroup(elCentro.getId(), "IdCentro", gr);
                        commonBean.removeTemplatePermissionToGroup(elCentro.getId(), "DatiCentro", gr);
                        commonBean.removeTemplatePermissionToGroup(elCentro.getId(), "AnalisiCentro", gr);
                        commonBean.removeTemplatePermissionToGroup(elCentro.getId(), "Feasibility", gr);
                        commonBean.removeTemplatePermissionToGroup(elCentro.getId(), "ServiziCoinvolti", gr);
                        for (Element farmacoDepot : elCentro.getChildrenByType("DepotFarmaco")) {
                            commonBean.removeTemplatePermissionToGroup(farmacoDepot.getId().toString(), "depotFarmaco", gr);
                        }

                        it.cineca.siss.axmr3.log.Log.info(getClass(), "resetto i permessi per il gruppo" + gr);
                    }

                    String[] figliStudio = {"PromotoreStudio", "FinanziatoreStudio", "CROStudio", "Farmaco", "allegato", "ProdottoStudio", "Emendamento"};
                    for (String childType : figliStudio) {
                        for (Element child : elStudio.getChildrenByType(childType)) {
                            commonBean.changePermissionToGroup(child.getId() + "", "V,M,E,A,B", null, "SEGRETERIA");
                            commonBean.changePermissionToGroup(child.getId() + "", "V,M,E,A,B", null, "SP");
                            commonBean.changePermissionToGroup(child.getId() + "", "V,M,MP,A,P,B", null, "CTC");
                            commonBean.changePermissionToUser(child.getId() + "", "V,M,MP,A,P,B", null, child.getCreateUser());
                        }
                    }

                    //service.setDefaultPermissionOnElement(elCentro);//ridiamo i permessi originali al centro
                    activeProcesses = service.getActiveProcesses(elCentro);
                    for (ProcessInstance p : activeProcesses) {
                        String myProcessId = p.getProcessDefinitionId();
                        String myProcessKey = service.getProcessEngine().getRepositoryService().getProcessDefinition(myProcessId).getKey();
                        if (myProcessKey.equals("ce-center-validation")) {
                            service.getProcessEngine().getRuntimeService().deleteProcessInstance(p.getProcessInstanceId(), "PROCESS_DELETE");
                        }
                    }
                    String pInstanceId = service.startProcess("PROCESS", elCentro, "ce-center-validation", true);//faccio ripartire Fattibilità
                    it.cineca.siss.axmr3.log.Log.info(getClass(), "LUIGI: PROCESSO RILANCIATO" + pInstanceId);
                    //service.setDefaultPermissionOnElement(elStudio);//ridiamo i permessi originali allo studio

                    commonBean.addMetadataValue(elementId, "ParereCe", "ParereWFinviato", "1", service);
                    commonBean.changePermissionToGroup(elementId, "V,B", "", "SEGRETERIA", service);
                    commonBean.changePermissionToUser(elementId, "V,B", "", parereCE.getCreateUser(), service);
                    commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "idParereCE", "", service);
                    commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "parereCEPositivo", "", service);
                    commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "idIstruttoriaCEPositiva", "", service);
                    commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "delibNumIstrCEPositiva", "", service);
                    commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "fattLocale", "", service);
                    commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "valCTC", "", service);
                }
                break;
            case 3: //Contrario
                commonBean.addMetadataValue(elementId, "ParereCe", "ParereWFinviato", "1", service);
                commonBean.changePermissionToGroup(elementId, "V,B", "", "SEGRETERIA", service);
                commonBean.changePermissionToUser(elementId, "V,B", "", parereCE.getCreateUser(), service);
                commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "idParereCE", elementId, service);
                commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "parereCEPositivo", "0", service);
                break;
            case 4: //Favorevole a condizione
                //commonBean.addMetadataValue(elCentro.getId().toString(),"statoValidazioneCentro","idParereCE",elementId,service);
                //commonBean.addMetadataValue(elCentro.getId().toString(),"statoValidazioneCentro","parereCEPositivo","1",service);

                //Riapro documentazione
                if (riapertura.equalsIgnoreCase("2")) {
                    Logger.getLogger(this.getClass()).info("########################################### --[ParereCE] - RIAPERTO SOLO DOC!");
                    commonBean.addMetadataValue(elementId, "ParereCe", "ParereWFinviato", "1", service);
                    commonBean.changePermissionToGroup(elementId, "V,B", "", "SEGRETERIA", service);
                    commonBean.changePermissionToUser(elementId, "V,B", "", parereCE.getCreateUser(), service);
                    if (riaperturaSezione.equalsIgnoreCase("1") || riaperturaSezione.equalsIgnoreCase("3") ) {
                        //se il creator del centro è un SP allora riapro l'inserimento documenti a livello di centro
                        commonBean.changePermissionToUser(elCentro.getId().toString(), "V,A,B", "", elCentro.getCreateUser(), service);
                    }
                    if (riaperturaSezione.equalsIgnoreCase("2") || riaperturaSezione.equalsIgnoreCase("3") ) {
                        //se il creator del centro è un SP allora riapro l'inserimento documenti a livello di studio
                        commonBean.changePermissionToUser(elStudio.getId().toString(), "V,A,B", "", elStudio.getCreateUser(), service);
                    }
                    commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "idParereCE", "", service);
                    commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "parereCEPositivo", "", service);
                    //commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "idIstruttoriaCEPositiva", "", service);
                    //commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "delibNumIstrCEPositiva", "", service);
                }

                //Riapro feasibility
                if (riapertura.equalsIgnoreCase("1")) {
                    Logger.getLogger(this.getClass()).info("########################################### --[ParereCE] - RIAPERTO TUTTO!");
                    //Elimino i permessi in visibilità dati alla chiusura della feasibilityPI (CloseAllTemplates)

                    commonBean.changePermissionToGroup(elStudio.getId() + "", "V,M,A,B", null, "SEGRETERIA");
                    commonBean.changePermissionToGroup(elStudio.getId() + "", "V,M,A,B", null, "SP");
                    commonBean.changePermissionToGroup(elStudio.getId() + "", "V,M,A,B", null, "CTC");
                    commonBean.changePermissionToUser(elStudio.getId() + "", "V,M,A,P,B", null, elStudio.getCreateUser());

                    String[] gruppiUtenti = {"CTC", "SP", "PI","COORD", "REGIONE", "SEGRETERIA", "DATAMANAGER","DIR", "FARMACIA"};

                    for (String gr : gruppiUtenti) {
                        commonBean.removeTemplatePermissionToGroup(elStudio.getId(), "datiStudio", gr);
                        commonBean.removeTemplatePermissionToGroup(elStudio.getId(), "datiCoordinatore", gr);
                        commonBean.removeTemplatePermissionToGroup(elCentro.getId(), "IdCentro", gr);
                        commonBean.removeTemplatePermissionToGroup(elCentro.getId(), "DatiCentro", gr);
                        commonBean.removeTemplatePermissionToGroup(elCentro.getId(), "AnalisiCentro", gr);
                        commonBean.removeTemplatePermissionToGroup(elCentro.getId(), "Feasibility", gr);
                        commonBean.removeTemplatePermissionToGroup(elCentro.getId(), "ServiziCoinvolti", gr);
                        for (Element farmacoDepot : elCentro.getChildrenByType("DepotFarmaco")) {
                            commonBean.removeTemplatePermissionToGroup(farmacoDepot.getId().toString(), "depotFarmaco", gr);
                        }


                        it.cineca.siss.axmr3.log.Log.info(getClass(), "resetto i permessi per il gruppo" + gr);
                    }

                    String[] figliStudio = {"PromotoreStudio", "FinanziatoreStudio", "CROStudio", "Farmaco", "allegato", "ProdottoStudio", "Emendamento"};
                    for (String childType : figliStudio) {
                        for (Element child : elStudio.getChildrenByType(childType)) {
                            commonBean.changePermissionToGroup(child.getId() + "", "V,M,E,A,B", null, "SEGRETERIA");
                            commonBean.changePermissionToGroup(child.getId() + "", "V,M,E,A,B", null, "SP");
                            commonBean.changePermissionToGroup(child.getId() + "", "V,M,MP,A,P,B", null, "CTC");
                            commonBean.changePermissionToUser(child.getId() + "", "V,M,MP,A,P,B", null, child.getCreateUser());
                        }
                    }

                    //service.setDefaultPermissionOnElement(elCentro);//ridiamo i permessi originali al centro
                    activeProcesses = service.getActiveProcesses(elCentro);
                    for (ProcessInstance p : activeProcesses) {
                        String myProcessId = p.getProcessDefinitionId();
                        String myProcessKey = service.getProcessEngine().getRepositoryService().getProcessDefinition(myProcessId).getKey();
                        if (myProcessKey.equals("ce-center-validation")) {
                            service.getProcessEngine().getRuntimeService().deleteProcessInstance(p.getProcessInstanceId(), "PROCESS_DELETE");
                        }
                    }
                    String pInstanceId = service.startProcess("PROCESS", elCentro, "ce-center-validation", true);//faccio ripartire Fattibilità
                    it.cineca.siss.axmr3.log.Log.info(getClass(), "LUIGI: PROCESSO RILANCIATO" + pInstanceId);
                    //service.setDefaultPermissionOnElement(elStudio);//ridiamo i permessi originali allo studio

                    commonBean.addMetadataValue(elementId, "ParereCe", "ParereWFinviato", "1", service);
                    commonBean.changePermissionToGroup(elementId, "V,B", "", "SEGRETERIA", service);
                    commonBean.changePermissionToUser(elementId, "V,B", "", parereCE.getCreateUser(), service);
                    commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "idParereCE", "", service);
                    commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "parereCEPositivo", "", service);
                    commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "idIstruttoriaCEPositiva", "", service);
                    commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "delibNumIstrCEPositiva", "", service);
                    commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "fattLocale", "", service);
                    commonBean.addMetadataValue(elCentro.getId().toString(), "statoValidazioneCentro", "valCTC", "", service);
                }

                activeProcesses = service.getActiveProcesses(elCentro);
                for (ProcessInstance p : activeProcesses) {
                    String myProcessId = p.getProcessDefinitionId();
                    String myProcessKey = service.getProcessEngine().getRepositoryService().getProcessDefinition(myProcessId).getKey();
                    if (myProcessKey.equals("RitiraCentro")) {
                        service.getProcessEngine().getRuntimeService().deleteProcessInstance(p.getProcessInstanceId(), "PROCESS_DELETE");
                    }
                }
                break;
        }
        commonBean.closeDocumentService(service);
    }

    /*TOSCANA-119 INIZIO
     * chiamato dal workflow Creazione Studio (ce-gemelli-create-studio-flow) per abilitare tutti gli utenti appartenenti allo stesso gruppo dell'utente che crea lo Studio
     * */
    public void abilitaCTOStudio(String elementId) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Inizio abilitaCTO per l'elemento Studio = " + elementId);
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(elementId);
        String my_cto = "";
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "l'utente = " + el.getCreateUser());
        my_cto = getCTOgroup(commonBean.getUser(el.getCreateUser()));
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "appartiene al gruppo= " + my_cto);
        commonBean.changePermissionToGroup(elementId, "V,M,AC,MC,E,A,P,ET,B", "", my_cto, service);
        commonBean.changePermissionToGroup(elementId, "V,C,A,B", "", "CTC", service);//TOLGO LA MODIFICA A GRUPPO CTC
        commonBean.addMetadataValue(el, "UniqueIdStudio", "cto", my_cto, service);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Fine abilitaCTO per l'elemento Studio = " + elementId);
        commonBean.closeDocumentService(service);

    }

    public void abilitaCTOFiglioStudio(String elementId) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Inizio abilitaCTO per l'elemento Centro= " + elementId);
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(elementId);
        String my_cto = "";
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "l'utente = " + el.getCreateUser());
        my_cto = getCTOgroup(commonBean.getUser(el.getCreateUser()));
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "appartiene al gruppo= " + my_cto);
        commonBean.changePermissionToGroup(elementId, "V,E,B", "", my_cto, service);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Fine abilitaCTO per l'elemento Centro = " + elementId);
        commonBean.closeDocumentService(service);

    }
    //GESTIONE FARMACIA

    /**
     * Chiamato dal WF creaDepotFarmaci alla creazione del centro, crea tanti elementi DepotFarmaco (figli di Centro) quanti sono gli elementi Farmaco
     * (di tipo farmaco) figli di Studio per il nuovo centro.
     * Chiamato dallo stesso WF alla creazione del farmaco, crea tanti elementi DepotFarmaco quanti sono gli elementi Centro già esistenti nello studio
     * @param elementId id del centro
     * @throws Exception
     */
    public void creaDepotFarmaci(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        if (service.getElement(elementId).getTypeName().equals("Centro")) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Inizio creaDepotFarmaci per l'elemento Centro= " + elementId);
            Element elCentro = service.getElement(elementId);
            Element elStudio = elCentro.getParent();
            String my_cto = "";
            String my_farma = "";
            List<Element> Farmaci = elStudio.getChildrenByType("Farmaco");
            Long idFarmaco;
            Long newDepotFarmacoId;
            String tipo;
            for (Element farmaco : Farmaci) {
                if (farmaco.getfieldData("Farmaco", "tipo") != null && farmaco.getfieldData("Farmaco", "tipo").size() > 0) {
                    tipo = farmaco.getfieldData("Farmaco", "tipo").get(0).toString().split("###")[0];
                    idFarmaco = farmaco.getId();
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "trovato Farmaco in Studio = " + idFarmaco);
                    newDepotFarmacoId = commonBean.createChild(elCentro.getId().toString(), elCentro.getCreateUser(), "DepotFarmaco", service);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "creato DepotFarmaco in Centro= " + newDepotFarmacoId);
                    commonBean.addMetadataValue(newDepotFarmacoId.toString(), "depotFarmaco", "linkFarmaco", idFarmaco, service);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "aggiunto metadato a DepotFarmaco depotFarmaco_linkFarmaco");

                    commonBean.addMetadataValue(newDepotFarmacoId.toString(), "depotFarmaco", "tipo", tipo, service);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "aggiunto metadato a DepotFarmaco depotFarmaco_tipo " + tipo);
                    /*if( tipo.equals("1") || tipo.equals("4") || tipo.equals("5")){
                        commonBean.addMetadataValue(newDepotFarmacoId.toString(), "depotFarmaco", "formaFarm", farmaco.getFieldDataString("Farmaco", "formaFarm"), service);
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "aggiunto metadato a DepotFarmaco depotFarmaco_formaFarm "+farmaco.getFieldDataString("Farmaco", "formaFarm"));
                    commonBean.addMetadataValue(newDepotFarmacoId.toString(), "depotFarmaco", "dosaggio", farmaco.getFieldDataString("Farmaco", "dosaggio"), service);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "aggiunto metadato a DepotFarmaco depotFarmaco_dosaggio "+farmaco.getFieldDataString("Farmaco", "dosaggio"));

                    }*/

                    my_cto = getCTOgroup(commonBean.getUser(elCentro.getCreateUser()));
                    commonBean.changePermissionToGroup(newDepotFarmacoId.toString(), "V,E,B", "", my_cto, service);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "Assegnati permessi a profilo " + my_cto);
                    my_farma = "FARMACIA";//my_cto.replace("CTO_","FARMA_");
                    commonBean.changePermissionToGroup(newDepotFarmacoId.toString(), "V,C,M,AC,A,B", "", my_farma, service);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "Assegnati permessi a profilo " + my_farma);
                }
            }
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Fine creaDepotFarmaci per l'elemento Centro = " + elementId);
        } else {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Inizio creaDepotFarmaci per l'elemento Farmaco= " + elementId);
            Element elFarmaco = service.getElement(elementId);
            String tipo;
            if (elFarmaco.getfieldData("Farmaco", "tipo") != null && elFarmaco.getfieldData("Farmaco", "tipo").size() > 0) {
                Element elStudio = elFarmaco.getParent();
                String my_cto = "";
                String my_farma = "";
                List<Element> centri = elStudio.getChildrenByType("Centro");
                Long idCentro;
                Long newDepotFarmacoId;

                tipo = elFarmaco.getfieldData("Farmaco", "tipo").get(0).toString().split("###")[0];
                for (Element centro : centri) {
                    idCentro = centro.getId();
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "trovato Centro in Studio = " + idCentro);
                    newDepotFarmacoId = commonBean.createChild(centro.getId().toString(), centro.getCreateUser(), "DepotFarmaco", service);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "creato DepotFarmaco in Centro= " + idCentro);
                    commonBean.addMetadataValue(newDepotFarmacoId.toString(), "depotFarmaco", "linkFarmaco", elementId, service);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "aggiunto metadato a DepotFarmaco depotFarmaco_linkFarmaco");
                    commonBean.addMetadataValue(newDepotFarmacoId.toString(), "depotFarmaco", "tipo", tipo, service);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "aggiunto metadato a DepotFarmaco depotFarmaco_tipo " + tipo);
                    /*if( tipo.equals("1") || tipo.equals("4") || tipo.equals("5")){
                    commonBean.addMetadataValue(newDepotFarmacoId.toString(), "depotFarmaco", "formaFarm", elFarmaco.getFieldDataString("Farmaco", "formaFarm"), service);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "aggiunto metadato a DepotFarmaco depotFarmaco_formaFarm "+elFarmaco.getFieldDataString("Farmaco", "formaFarm"));
                    commonBean.addMetadataValue(newDepotFarmacoId.toString(), "depotFarmaco", "dosaggio", elFarmaco.getFieldDataString("Farmaco", "dosaggio"), service);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "aggiunto metadato a DepotFarmaco depotFarmaco_dosaggio "+elFarmaco.getFieldDataString("Farmaco", "dosaggio"));
                    }*/
                    my_cto = getCTOgroup(commonBean.getUser(centro.getCreateUser()));
                    commonBean.changePermissionToGroup(newDepotFarmacoId.toString(), "V,E,B", "", my_cto, service);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "Assegnati permessi a profilo " + my_cto);
                    my_farma = "FARMACIA";//my_cto.replace("CTO_","FARMA_");
                    commonBean.changePermissionToGroup(newDepotFarmacoId.toString(), "V,C,M,AC,A,B", "", my_farma, service);
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "Assegnati permessi a profilo " + my_farma);

                }
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "Fine creaDepotFarmaci per l'elemento Farmaco = " + elementId);
            }
        }
        commonBean.closeDocumentService(service);

    }

    /**
     * Chiamato dal WF eliminaDepotFarmaci all'eliminazione di un oggetto Farmaco, elimina tutti gli elementi DepotFarmaco
     * (di tipo farmaco) figli dei centri in Studio .
     *
     * @param elementId id del Farmaco
     * @throws Exception
     */
    public void eliminaDepotFarmaci(String elementId, String userId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        if (service.getElement(elementId).getTypeName().equals("Farmaco")) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Inizio eliminaDepotFarmaci per l'elemento Farmaco= " + elementId);
            Element elFarmaco = service.getElement(elementId);
            List<Element> depotFarmaciDaEliminare = new ArrayList<Element>();
            Element elStudio = elFarmaco.getParent();
            List<Element> centri = elStudio.getChildrenByType("Centro");
            Long idCentro;
            for (Element centro : centri) {
                idCentro = centro.getId();
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "trovato Centro in Studio = " + idCentro);
                List<Element> depotFarmaci = centro.getChildrenByType("DepotFarmaco");
                String depotFarmacoLinkFarmacoId;
                for (Element depotFarmaco : depotFarmaci) {
                    depotFarmacoLinkFarmacoId = depotFarmaco.getFieldDataElement("depotFarmaco", "linkFarmaco").get(0).getId().toString();
                    if (depotFarmacoLinkFarmacoId.equals(elementId)) {
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "trovato DepotFarmaco DA ELIMINARE in Centro = " + depotFarmaco.getId().toString());
                        depotFarmaciDaEliminare.add(depotFarmaco);
                    }
                }
            }
            for (Element depotDaEliminare : depotFarmaciDaEliminare) {
                depotDaEliminare.setDeleted(true);
                depotDaEliminare.setDeletedBy(userId);
                depotDaEliminare.setDeleteDt(new GregorianCalendar());
                it.cineca.siss.axmr3.log.Log.debug(getClass(), "ELIMINATO DepotFarmaco = " + depotDaEliminare.getId().toString());
            }
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Fine eliminaDepotFarmaci per l'elemento Farmaco = " + elementId);
        }
        commonBean.closeDocumentService(service);

    }

    public void abilitaFarmaCentroEStudio(String elementId) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Inizio abilitaFarmacia per l'elemento Centro= " + elementId);
        DocumentService service = commonBean.getDocumentService();
        Element elCentro = service.getElement(elementId);
        Element elStudio = elCentro.getParent();
        String my_farma = "";
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "l'utente = " + elCentro.getCreateUser());
        my_farma = "FARMACIA";//getCTOgroup(commonBean.getUser(elCentro.getCreateUser())).replace("CTO_","FARMA_");
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "appartiene al gruppo= " + my_farma);
        commonBean.changePermissionToGroup(elementId, "V,E,B", "", my_farma, service);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "abilito permesso anche per lo Studio " + elStudio.getId().toString());
        commonBean.changePermissionToGroup(elStudio.getId().toString(), "V,E,A,B", "", my_farma, service);
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "Fine abilitaFarmacia per l'elemento Centro = " + elementId);
        commonBean.closeDocumentService(service);

    }

    ///FINE GESTIONE FARMACIA
    public String getCTOgroup(IUser user) {
        String group = "";
        for (IAuthority auth : user.getAuthorities()) {
            if (group.equals("") && auth.getAuthority().startsWith("CTO_")) {
                group = auth.getAuthority();
            }
        }
        return group;
    }

    /*TOSCANA-119 FINE*/
    /*TOSCANA-177 INIZIO*/
    public String getEmailCTOGroup(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        Connection conn = dataSource.getConnection();
        Element el = service.getElement(elementId);
        String mailTo = "";
        try {
            String user = el.getCreateUser();
            String sqlMailTO = "select u.email as email from ana_utenti_1 u, studies_profiles sp,users_profiles up where u.userid=up.userid and sp.id=up.profile_id and sp.active=1 and up.active=1 and sp.code=?";
            it.cineca.siss.axmr3.log.Log.debug(getClass(), sqlMailTO);
            PreparedStatement stmtMailTo = conn.prepareStatement(sqlMailTO);
            IUser iuser = (IUser) userService.loadUserByUsername(user);
            stmtMailTo.setString(1, getCTOgroup(iuser));
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
        }
        catch (Exception e){
            Logger.getLogger(this.getClass()).info(e.getMessage(), e);
        }
        if (mailTo.equals("")) mailTo = getEmail("ALIAS_CTC");
        return mailTo;
    }
    /*TOSCANA-177 FINE*/

    /*STSANSVIL-2855*/
    public void zippaDocumentazione(String elementId) throws Exception {
        DocumentService service = commonBean.getDocumentService();
        if (service.getElement(elementId).getTypeName().equals("Centro")) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Inizio zippaDocumentazione per l'elemento Centro = " + elementId);
            Element elCentro = service.getElement(elementId);
            Element elStudio = elCentro.getParent();

            String fileName="DocumentazioneStudio_"+elStudio.getId()+"_"+elCentro.getTitleString()+".zip";
            ByteArrayOutputStream bos = new ByteArrayOutputStream();
            ZipOutputStream zipOut = new ZipOutputStream(bos);
            List<Element> allegatiStudio = elStudio.getChildrenByType("allegato");
            for (Element allegato : allegatiStudio) {
                System.out.println("\n\nINSERISCO "+allegato.getFile().getFileName()+" nello zip");
                ByteArrayInputStream bis =new ByteArrayInputStream(allegato.getFile().getContent().getContent());
                ZipEntry zipEntry = new ZipEntry(allegato.getFile().getFileName());
                zipOut.putNextEntry(zipEntry);
                byte[] bytes = new byte[1024];
                int length;
                while((length = bis.read(bytes)) >= 0) {
                    zipOut.write(bytes, 0, length);
                }
                bis.close();

            }
            Element zipDocEl=null;
            Long zipDocId = null;
            List<Element> allegatiCentro = elCentro.getChildrenByType("AllegatoCentro");
            for (Element allegato : allegatiCentro) {
                if(!allegato.getFieldDataCode("DocCentroSpec", "TipoDocumento").equals("777") && !allegato.getFieldDataCode("DocCentroSpec", "protocollato").equals("1")) {
                    System.out.println("\n\nINSERISCO "+allegato.getFile().getFileName()+" nello zip");
                    ByteArrayInputStream bis = new ByteArrayInputStream(allegato.getFile().getContent().getContent());
                    ZipEntry zipEntry = new ZipEntry(allegato.getFile().getFileName());
                    zipOut.putNextEntry(zipEntry);
                    byte[] bytes = new byte[1024];
                    int length;
                    while ((length = bis.read(bytes)) >= 0) {
                        zipOut.write(bytes, 0, length);
                    }
                    bis.close();
                    commonBean.addMetadataValue(String.valueOf(allegato.getId()), "DocCentroSpec", "zippato", "1", service);

                }
                else{
                    zipDocEl=allegato;//file zip già generato
                }
            }
            zipOut.close();
            bos.close();
            if(zipDocEl==null) {
                zipDocId = commonBean.createChild(elCentro.getId().toString(), "CTC", "AllegatoCentro", service);
                commonBean.addMetadataValue(String.valueOf(zipDocId), "DocCentroSpec", "TipoDocumento", "777###Documentazione Zip", service);
                zipDocEl=service.getElement(zipDocId);
            }


            service.attachFile("PROCESS",zipDocEl,bos.toByteArray(),fileName,(long)bos.toByteArray().length,"","","","","CREATE",true);
            it.cineca.siss.axmr3.log.Log.debug(getClass(), "Fine  zippaDocumentazione per l'elemento Centro = " + elementId);

        }
        commonBean.closeDocumentService(service);

    }

    public void checkDocumentazioneProtocollata(String elementId, DelegateTask task) throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "INIZIO checkDocumentazioneProtocollata centro id: " + elementId);
        DocumentService service = commonBean.getDocumentService();
        Element el = service.getElement(Long.parseLong(elementId));
        Element elStudio = el.getParent();
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "elementId=" + elementId);
        boolean protocollato = false; 
        String message = "";
        
        List<Element> allegatiCentro = el.getChildrenByType("AllegatoCentro");
        for (Element allegato : allegatiCentro) {
            if(allegato.getFieldDataCode("DocCentroSpec", "TipoDocumento").equals("777") && allegato.getFieldDataCode("DocCentroSpec", "protocollato").equals("1")) {
                protocollato = true;
                message = "Documentazione Zip già protocollata. Non è possibile creare una nuova versione zip della documentazione. Inviare a protocollo i singoli file non presenti nello zip";
            }
        }

        commonBean.closeDocumentService(service);
        task.setVariable("protocollato", protocollato);
        task.setVariable("message", message);
    
    }

    /* STSANSVIL-6038 */
    public void zipStudio() throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(), "INIZIO zipStudio");
        DocumentService service = commonBean.getDocumentService();

        List<Element> studi = service.getElementsByType("Studio");
        for (Element studio : studi) {

            List<Element> centri = studio.getChildrenByType("Centro");
            for (Element centro : centri) {
                boolean alreadyStarted=false;
                List<ProcessInstance> activeProcesses = service.getActiveProcesses(centro);
                for (ProcessInstance p : activeProcesses) {
                    String myProcessId = p.getProcessDefinitionId();
                    String myProcessKey = service.getProcessEngine().getRepositoryService().getProcessDefinition(myProcessId).getKey();
                    if (myProcessKey.equals("zipDoc")) {
                        alreadyStarted=true;
                        it.cineca.siss.axmr3.log.Log.debug(getClass(), "zipDoc era presente");
                    }
                }
                if (!alreadyStarted){
                    String pInstanceId = service.startProcess("PROCESS", centro, "zipDoc", true);//faccio partire Documentazione zip
                    it.cineca.siss.axmr3.log.Log.debug(getClass(), "zipDoc LANCIATO" + pInstanceId);
                }

            }//fine ciclo centri
        }//fine ciclo studi
        commonBean.closeDocumentService(service);
    }//fine zipStudio
}
