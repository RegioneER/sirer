package it.cineca.siss.axmr3.doc;

import it.cineca.siss.axmr3.exceptions.AxmrGenericException;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

public class StdUtils {

    public static String toCamelCase(final String init) {

        if (init==null)
            return null;

        final StringBuilder ret = new StringBuilder(init.length());

        for (final String word : init.split(" ")) {
            if (!word.isEmpty()) {
                ret.append(word.substring(0, 1).toUpperCase());
                ret.append(word.substring(1).toLowerCase());
            }
            if (!(ret.length()==init.length()))
                ret.append(" ");
        }

        return ret.toString();

    }

    public static Calendar parseDate(String dateString) throws AxmrGenericException {
        Date parsed = null;
        List<DateFormat> dfs=new LinkedList<DateFormat>();
        dfs.add(new SimpleDateFormat("dd/MM/yyyy"));
        dfs.add(new SimpleDateFormat("EEE MMM dd hh:mm:ss z yyyy", Locale.US));
        dfs.add(new SimpleDateFormat("dd/MM/yyyy hh:mm"));
        for (DateFormat df:dfs){
            try {
                parsed = df.parse(dateString);
                Calendar newCalendar = Calendar.getInstance();
                newCalendar.setTime(parsed);
                return newCalendar;
            } catch (ParseException e) {
                //it.cineca.siss.axmr3.log.Log.info(getClass(),"Data "+val.toString()+" formato non accettato");
            }
        }
        try{
            Long unixTime=Long.parseLong(dateString);
            Calendar newCalendar = Calendar.getInstance();
            newCalendar.setTime(new Date(unixTime));
            return newCalendar;
        }catch (Exception e) {
            //it.cineca.siss.axmr3.log.Log.info(getClass(),"Data "+val.toString()+" formato non accettato");
        }
        throw new AxmrGenericException("Errore conversione data");
    }


}
