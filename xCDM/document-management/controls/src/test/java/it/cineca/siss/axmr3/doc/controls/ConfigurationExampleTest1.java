package it.cineca.siss.axmr3.doc.controls;


import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import it.cineca.siss.axmr3.doc.controls.json.*;

import java.util.Arrays;
import java.util.LinkedList;

/**
 * Created by Carlo on 12/09/2016.
 */
public class ConfigurationExampleTest1 {



    public static void main(String[] argv){
        Configuration cfg=new Configuration();

        LinkedList<String> flds1=new LinkedList<String>();
        flds1.add("field-1");
        flds1.add("field-2");
        flds1.add("field-3");
        flds1.add("field-4");
        flds1.add("field-5");

        SubmitButton btn1=new SubmitButton();
        btn1.setName("Salva");
        btn1.setFields(flds1);

        LinkedList<String> flds2=new LinkedList<String>();
        flds2.add("field-1");
        flds2.add("field-2");
        flds2.add("field-3");
        flds2.add("field-4");
        flds2.add("field-5");
        flds2.add("field-6");
        flds2.add("field-7");

        SubmitButton btn2=new SubmitButton();
        btn2.setName("Invia");
        btn2.setFields(flds2);

        cfg.getSubmitButtons().add(btn1);
        cfg.getSubmitButtons().add(btn2);

        Condition cnd1=new Condition("fieldId-2", "gt", Arrays.asList("fieldId-3"), Arrays.asList((Object) 3));
        Condition cnd2=new Condition("fieldId-1", "not in", Arrays.asList("fieldId-3"), Arrays.asList((Object) 4, (Object) 3, (Object) 2));
        AndConditions acnd=new AndConditions();
        acnd.setAnd(Arrays.asList(cnd1,cnd2));
        OrConditions ocnd=new OrConditions();
        ocnd.setOr(Arrays.asList(acnd));
        EmptyAndHideCriteria c=new EmptyAndHideCriteria();
        c.setConditions(ocnd);
        c.setHide(true);
        CriteriaContainer cc=new CriteriaContainer();
        cc.setEmpty(c);
        Rule rule=new Rule();
        rule.setRule("rule-1");
        LinkedList<String> rflds1=new LinkedList<String>();
        rflds1.add("field-1");
        rflds1.add("field-2");
        rflds1.add("field-3");
        rule.setFields(rflds1);
        rule.setButtons(Arrays.asList("Salva", "Invia"));
        rule.setCriteria(cc);
        cfg.setRules(Arrays.asList(rule));
        Gson gson = new GsonBuilder().setPrettyPrinting().create();
        String json = gson.toJson(cfg);
        System.out.println(json);
    }

}
