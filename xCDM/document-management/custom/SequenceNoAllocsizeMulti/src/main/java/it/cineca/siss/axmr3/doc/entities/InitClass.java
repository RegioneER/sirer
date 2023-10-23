package it.cineca.siss.axmr3.doc.entities;

import org.apache.log4j.Logger;
import org.springframework.beans.factory.InitializingBean;

/**
 * Created by Carlo on 16/11/2016.
 */
public class InitClass implements InitializingBean {
    public void afterPropertiesSet() throws Exception {
        Logger.getLogger(this.getClass()).info("\n\n\n - - - SEQUENCE NO ALLOCSIZE FIX MULTI - - - \n\n\n");
    }
}
