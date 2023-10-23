package it.cineca.siss.axmr3.doc.acl;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 29/08/13
 * Time: 10.40
 * To change this template use File | Settings | File Templates.
 */
public enum Permission {
    VIEW(1),CREATE(2),UPDATE(4),ADDCOMMENT(8),MODERATE(16),DELETE(32),CHANGE_PERMISSION(64),ADDCHILD(128),REMOVE_CHECKOUT(256),LAUNCH_PROCESS(512),ENABLE_TEMPLATE(1024),BROWSE(2048);
    private final int value;


    private Permission(int v){
        this.value=v;
    }

    public int getValue(){
        return value;
    }
}
