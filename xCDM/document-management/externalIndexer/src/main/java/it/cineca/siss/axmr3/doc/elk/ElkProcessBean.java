package it.cineca.siss.axmr3.doc.elk;

import org.springframework.beans.factory.annotation.Autowired;

/**
 * Created by Carlo on 01/02/2016.
 */
public class ElkProcessBean {

    @Autowired
    protected ElkService service;

    public ElkService getService() {
        return service;
    }

    public void setService(ElkService service) {
        this.service = service;
    }


    public ElkProcessBean(){
        it.cineca.siss.axmr3.log.Log.info(getClass(),"Inizializzo il bean ProcessActionsBean");
    }


    public void simpleIndex(Long elId) throws Exception {
        service.simpleIndex(elId);
    }

    public void fullIndex(Long elId) throws Exception {
        service.fullIndex(elId);
    }

    public void fieldIndex(Long elId) throws Exception {
        service.fieldIndex(elId);
    }

    public void doSimpleIndex(String type) throws Exception {
        service.doSimpleIndex(type);
    }

    public void doFullIndex(String type) throws Exception {
        service.doFullIndex(type);
    }

    public void doFieldIndex(String type) throws Exception {
        service.doFieldIndex(type);
    }

    public void doForceSimpleIndex(String type) throws Exception {
        service.doSimpleIndex(type);
    }

    public void doForceFullIndex(String type) throws Exception {
        service.doFullIndex(type);
    }

    public void doForceFieldIndex(String type) throws Exception {
        service.doFieldIndex(type);
    }






}
