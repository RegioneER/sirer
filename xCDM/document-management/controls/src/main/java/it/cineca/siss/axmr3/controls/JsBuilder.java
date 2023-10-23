package it.cineca.siss.axmr3.controls;

import it.cineca.siss.axmr3.doc.controls.json.Rule;
import it.cineca.siss.axmr3.doc.controls.json.StdCriteria;
import it.cineca.siss.axmr3.doc.controls.json.iCriteria;

/**
 * Created by Carlo on 13/09/2016.
 */
public class JsBuilder {

    public static String jsRule(Rule rule){
        String js="";

        js=rule.toJs("it");

        return js;
    }

}
