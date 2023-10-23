package it.cineca.siss.axmr3.doc.controls.json;

import java.util.HashMap;

/**
 * Created by Carlo on 13/09/2016.
 */
public interface iCriteria {

    public OrConditions getConditions();

    public HashMap<String, String> getMessage();

    public String toJs();

}
