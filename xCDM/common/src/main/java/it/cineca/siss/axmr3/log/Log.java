package it.cineca.siss.axmr3.log;


import org.apache.log4j.Logger;

/**
 * Created by cin0562a on 21/07/15.
 */
public class Log {

    public static void info(Class c, Object message){
        Logger.getLogger(c.getName()).info(message);
    }

    public static void warn(Class c, Object message){
        Logger.getLogger(c.getName()).warn(message);
    }

    public static void error(Class c, Object message){
        Logger.getLogger(c.getName()).error(message);
    }

    public static void debug(Class c, Object message){
        Logger.getLogger(c.getName()).debug(message);
    }

}
