

import org.junit.Test;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 06/12/13
 * Time: 14.51
 * To change this template use File | Settings | File Templates.
 */
public class DateFormatTest {

    @Test
    public void checkDateFormat(){
        //Fri Dec 06 00:00:00 CET 2013
        java.util.Date date=new Date();
        DateFormat df = new SimpleDateFormat("EEE MMM dd hh:mm:ss z yyyy", Locale.US);
        it.cineca.siss.axmr3.log.Log.info(getClass(),df.format(date));
    }
}
