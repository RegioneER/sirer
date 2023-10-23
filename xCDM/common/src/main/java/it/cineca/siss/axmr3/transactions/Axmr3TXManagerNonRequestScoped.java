package it.cineca.siss.axmr3.transactions;

import org.apache.log4j.Logger;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.springframework.web.context.support.SpringBeanAutowiringSupport;

import java.io.Serializable;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 23/10/13
 * Time: 19:17
 * To change this template use File | Settings | File Templates.
 */
public class Axmr3TXManagerNonRequestScoped extends MultiSessionTXManager implements Serializable {

    public Axmr3TXManagerNonRequestScoped() {
        SpringBeanAutowiringSupport.processInjectionBasedOnCurrentContext(this);
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"Costruttore Axmr3TXManagerNonRequestScoped");
    }



    public HashMap<String, Transaction> getTxs() {
        return txs;
    }

    public void setTxs(HashMap<String, Transaction> txs) {
        this.txs = txs;
    }



    public void afterPropertiesSet() throws Exception {
        it.cineca.siss.axmr3.log.Log.debug(getClass(),this.getClass().getName()+" - afterPropertiesSet");
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"Sessioni caricate: "+this.sessionFactories.size());
        exceptionThrown=false;
    }

    public HashMap<String, Session> getSessions() {
        return sessions;
    }

    public void setSessions(HashMap<String, Session> sessions) {
        this.sessions = sessions;
    }

    public Map<String, SessionFactory> getSessionFactories() {
        return sessionFactories;
    }

    public void setSessionFactories(Map<String, SessionFactory> sessionFactories) {
        this.sessionFactories = sessionFactories;
    }

    public Session getSession(String sf){
        if (sessions.containsKey(sf)){
            if (!sessions.get(sf).isOpen()) {
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Riapro la sessione thread "+this.getClass().getCanonicalName());
                sessions.put(sf, sessionFactories.get(sf).openSession());
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Apro transazione thread "+this.getClass().getCanonicalName());
                txs.put(sf,sessions.get(sf).beginTransaction());
            }
            else {
                if (!txs.get(sf).isActive()){
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Riapro transazione thread "+this.getClass().getCanonicalName());
                    txs.put(sf,sessions.get(sf).beginTransaction());
                }
            }
        }else {
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Apro la sessione 4 "+this.getClass().getCanonicalName());
            sessions.put(sf, sessionFactories.get(sf).openSession());
            txs.put(sf,sessions.get(sf).beginTransaction());

        }
        return sessions.get(sf);
    }

    public boolean isExceptionThrown() {
        return exceptionThrown;
    }

    public void setExceptionThrown(boolean exceptionThrown) {
        this.exceptionThrown = exceptionThrown;
    }
/*
    public void destroy(){
        System.out.println(" - Effettuo Destroy globalTx id:"+this.toString()+" - ");
        Iterator<String> sf=sessionFactories.keySet().iterator();
        while (sf.hasNext()){
            String sfName=sf.next();
            try{
                if (exceptionThrown) {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Effettuo il rollback della sessione "+sfName);
                    txs.get(sfName).rollback();
                }
                else {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Effettuo il commit della sessione "+sfName);
                    txs.get(sfName).commit();
                }
            }catch (Exception ex){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),ex.getMessage());
            }
            try{
                close(sfName);
            }catch (Exception ex){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),ex.getMessage());
            }
        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"ChiudoTXManager");
    }
*/
    public void rollbackAll(){
        Logger.getLogger(this.getClass()).info(" - Effettuo Rollback globalTx id:"+this.toString()+" - ");
        Iterator<String> sf=sessionFactories.keySet().iterator();
        while (sf.hasNext()){
            String sfName=sf.next();
            try{
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Effettuo il rollback della sessione "+sfName);
                txs.get(sfName).rollback();
            }catch (Exception ex){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),ex.getMessage());
            }
            try{
                close(sfName);
            }catch (Exception ex){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),ex.getMessage());
            }
        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"ChiudoTXManager");
    }


    public void commit(){
        Iterator<String> sf=sessionFactories.keySet().iterator();
        while (sf.hasNext()){
            String sfName=sf.next();
            try{
                if (exceptionThrown) {
                    it.cineca.siss.axmr3.log.Log.warn(getClass(),"Effettuo il rollback della sessione "+sfName);
                    txs.get(sfName).rollback();
                }
                else {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Effettuo il commit della sessione "+sfName);
                    txs.get(sfName).commit();
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Begin Transaction 1 "+this.getClass().getCanonicalName());
                    txs.put(sfName,sessions.get(sfName).beginTransaction());
                }
            }catch (Exception ex){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),ex.getMessage());
            }
            try{
                close(sfName);
            }catch (Exception ex){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),ex.getMessage());
            }
        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"ChiudoTXManager");
    }

    public void close(String sfName){
        Session session = sessions.get(sfName);
        session.close();
        //sessions.remove(sfName);
    }

    public void commitAndKeepAlive(){
        Iterator<String> sf=sessionFactories.keySet().iterator();
        while (sf.hasNext()){
            String sfName=sf.next();
            try{
                if (exceptionThrown) {
                    it.cineca.siss.axmr3.log.Log.warn(getClass(),"Effettuo il rollback della sessione "+sfName);
                    txs.get(sfName).rollback();
                }
                else {
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Effettuo il commit della sessione "+sfName);
                    txs.get(sfName).commit();
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Begin Transaction 2 "+this.getClass().getCanonicalName());
                    txs.put(sfName,sessions.get(sfName).beginTransaction());
                }
            }catch (Exception ex){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),ex.getMessage());
            }

        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"Committo e non ChiudoTXManager");
    }

    public void rollbackAndKeepAlive(){
        Iterator<String> sf=sessionFactories.keySet().iterator();
        while (sf.hasNext()){
            String sfName=sf.next();
            try{
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Effettuo il commit della sessione "+sfName);
                    txs.get(sfName).rollback();
                    it.cineca.siss.axmr3.log.Log.debug(getClass(),"Begin Transaction 2 "+this.getClass().getCanonicalName());
                    txs.put(sfName,sessions.get(sfName).beginTransaction());
                }catch (Exception ex){
                it.cineca.siss.axmr3.log.Log.debug(getClass(),ex.getMessage());
            }

        }
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"Committo e non ChiudoTXManager");
    }


}
