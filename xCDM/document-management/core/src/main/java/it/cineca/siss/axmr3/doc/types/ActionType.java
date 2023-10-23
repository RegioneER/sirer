package it.cineca.siss.axmr3.doc.types;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 19/09/13
 * Time: 13:41
 * To change this template use File | Settings | File Templates.
 */
public enum ActionType {

    POPULATE_METADATA(1), ADD_TEMPLATE(2), SEND_EMAIL(3);
    private int value;

    private ActionType(int value){
        this.value=value;
    }



}
