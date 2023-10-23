package it.cineca.siss.axmr3.transactions;

import org.apache.log4j.Logger;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.springframework.beans.factory.InitializingBean;

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
public class MultiSessionTXManager  implements InitializingBean {

    protected Map<String,SessionFactory> sessionFactories=new HashMap<String, SessionFactory>();
    protected HashMap<String, Session> sessions=new HashMap<String, Session>();
    protected HashMap<String, Transaction> txs=new HashMap<String, Transaction>();
    protected boolean exceptionThrown;

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
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Apro la sessione 1 "+this.getClass().getCanonicalName());
                sessions.put(sf, sessionFactories.get(sf).openSession());
                it.cineca.siss.axmr3.log.Log.debug(getClass(),"Begin Transaction 3 "+this.getClass().getCanonicalName());
                txs.put(sf,sessions.get(sf).beginTransaction());
            }
            else {
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

    public void destroy(){
        Logger.getLogger(this.getClass()).info(" - Effettuo Destroy globalTx id:"+this.toString()+" - ");
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

    public void rollbackAll(){
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
