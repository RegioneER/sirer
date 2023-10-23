import org.junit.Test;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 28/11/13
 * Time: 11:35
 * To change this template use File | Settings | File Templates.
 */
public class RegexTest {

    @Test
    public void testRegex(){
        String titleShow="Studio n.ro [UniqueIdStudio.id] - [datiStudio.nome]";
        String pattern="\\[(.*?)\\]";
        Pattern r=Pattern.compile(pattern);
        Matcher m=r.matcher(titleShow);
        while(m.find()) {
            String[] fSpec=m.group(1).split("\\.");
            String templateName=fSpec[0];
            String fieldName=fSpec[1];
            titleShow=titleShow.replaceAll("\\["+m.group(1)+"\\]", execMethod(templateName, fieldName));
        }
        org.junit.Assert.assertEquals("Studio n.ro ###UniqueIdStudio###id### - ###datiStudio###nome###", titleShow);
    }

    @Test
    public void testRegex2(){
        String sqlQuery="select * from ana_utenti where userid=[userid]";
        String pattern="\\[(.*?)\\]";
        Pattern r=Pattern.compile(pattern);
        Matcher m=r.matcher(sqlQuery);
        while(m.find()) {
            if (m.group(1).toLowerCase().equals("userid")) {
                sqlQuery=sqlQuery.replaceAll("\\["+m.group(1)+"\\]", "CONTINO");
            }
        }
        org.junit.Assert.assertEquals("select * from ana_utenti where userid=CONTINO", sqlQuery);

    }

    @Test
    public void testRegex3(){
        String integerCheck="\\s*[+-]?\\d*\\s*";
        String decimalCheck="\\s*[+-]?\\d*[\\.,]?\\d*\\s*";
        String valueToCheck="12045,678";
        String valueToCheck1="12045678";
        String valueToCheck2="12045.678";
        String valueToCheck3="1204.5,678";
        String valueToCheck4="-12045,678";
        String valueToCheck5="012045,678";
        String valueToCheck6="+12045,678";
        org.junit.Assert.assertEquals("integer check - "+valueToCheck1, true, valueToCheck1.matches(integerCheck));
        org.junit.Assert.assertEquals("integer check - "+valueToCheck2, false, valueToCheck2.matches(integerCheck));
        org.junit.Assert.assertEquals("decimal check - "+valueToCheck, true, valueToCheck.matches(decimalCheck));
        org.junit.Assert.assertEquals("decimal check - "+valueToCheck1, true, valueToCheck1.matches(decimalCheck));
        org.junit.Assert.assertEquals("decimal check - "+valueToCheck2, true, valueToCheck2.matches(decimalCheck));
        org.junit.Assert.assertEquals("decimal check - "+valueToCheck3, false, valueToCheck3.matches(decimalCheck));
        org.junit.Assert.assertEquals("decimal check - "+valueToCheck4, true, valueToCheck4.matches(decimalCheck));
        org.junit.Assert.assertEquals("decimal check - "+valueToCheck5, true, valueToCheck5.matches(decimalCheck));
        org.junit.Assert.assertEquals("decimal check - "+valueToCheck6, true, valueToCheck6.matches(decimalCheck));
    }

    public String execMethod(String templateName, String fieldName){
        return "###"+templateName+"###"+fieldName+"###";
    }

}
