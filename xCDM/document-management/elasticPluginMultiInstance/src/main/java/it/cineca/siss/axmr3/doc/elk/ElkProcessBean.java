package it.cineca.siss.axmr3.doc.elk;

import it.cineca.siss.axmr3.transactions.Axmr3TXManagerNonRequestScoped;
import org.springframework.beans.factory.annotation.Autowired;

/**
 * Created by Carlo on 01/02/2016.
 */
public class ElkProcessBean {

    @Autowired
    protected Axmr3TXManagerNonRequestScoped globalTx;

    @Autowired
    protected ElkService service;

    public ElkService getService() {
        return service;
    }

    public void setService(ElkService service) {
        this.service = service;
    }

    public Axmr3TXManagerNonRequestScoped getGlobalTx() {
        return globalTx;
    }

    public void setGlobalTx(Axmr3TXManagerNonRequestScoped globalTx) {
        this.globalTx = globalTx;
    }

    public ElkProcessBean(){
        it.cineca.siss.axmr3.log.Log.info(getClass(),"Inizializzo il bean ProcessActionsBean");
    }


    public void simpleIndex(Long elId) throws Exception {
        service.initDocumentService(globalTx);
        service.simpleIndex(elId);
        service.closeDocumentService();
    }

    public void fullIndex(Long elId) throws Exception {
        service.initDocumentService(globalTx);
        service.fullIndex(elId);
        service.closeDocumentService();
    }

    public void fieldIndex(Long elId) throws Exception {
        service.initDocumentService(globalTx);
        service.fieldIndex(elId);
        service.closeDocumentService();
    }

    public void doSimpleIndex(String type) throws Exception {
        service.initDocumentService(globalTx);
        service.doSimpleIndex(type);
        service.closeDocumentService();
    }

    public void doFullIndex(String type) throws Exception {
        service.initDocumentService(globalTx);
        service.doFullIndex(type);
        service.closeDocumentService();
    }

    public void doFieldIndex(String type) throws Exception {
        service.initDocumentService(globalTx);
        service.doFieldIndex(type);
        service.closeDocumentService();
    }

    public void doForceSimpleIndex(String type) throws Exception {
        service.initDocumentService(globalTx);
        service.doSimpleIndex(type, true);
        service.closeDocumentService();
    }

    public void doForceFullIndex(String type) throws Exception {
        service.initDocumentService(globalTx);
        service.doFullIndex(type, true);
        service.closeDocumentService();
    }

    public void doForceFieldIndex(String type) throws Exception {
        service.initDocumentService(globalTx);
        service.doFieldIndex(type, true);
        service.closeDocumentService();
    }






}
