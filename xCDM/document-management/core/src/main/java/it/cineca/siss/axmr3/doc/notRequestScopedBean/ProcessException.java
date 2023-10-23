package it.cineca.siss.axmr3.doc.notRequestScopedBean;

import it.cineca.siss.axmr3.transactions.Axmr3TXManagerNonRequestScoped;
import org.apache.log4j.Logger;


/**
 * Created by Carlo on 06/07/2016.
 */
public class ProcessException extends Exception {

    Logger log=Logger.getLogger(ProcessException.class.getName());

    public ProcessException(Exception ex, Axmr3TXManagerNonRequestScoped globalTx) {
        Logger.getLogger(this.getClass()).error(ex.getMessage(), ex);
        globalTx.rollbackAll();
    }
}
