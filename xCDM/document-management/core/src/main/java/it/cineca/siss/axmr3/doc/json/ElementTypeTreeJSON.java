package it.cineca.siss.axmr3.doc.json;

import it.cineca.siss.axmr3.doc.entities.ElementType;

import java.util.Collection;
import java.util.HashMap;
import java.util.LinkedList;

/**
 * Created by gdelsignore on 25/02/2016.
 */
public class ElementTypeTreeJSON {
    private ElementType elementType=null;
    private LinkedList<String> tree=null;
    private Boolean recursion=false;
    public ElementTypeTreeJSON(ElementType baseElementType){
        elementType=baseElementType;
        tree=new LinkedList<String>();
        tree.add(elementType.getTypeId());
    }
    public ElementTypeTreeJSON(ElementType baseElementType,LinkedList<String> branch){
        elementType=baseElementType;
        tree=branch;
        tree.add(elementType.getTypeId());
    }
    public ElementTypeTreeJSON(ElementType baseElementType,LinkedList<String> branch,Boolean isRecursive){
        elementType=baseElementType;
        tree=branch;
        tree.add(elementType.getTypeId());
        recursion=isRecursive;
    }
    public Long getId(){
        return elementType.getId();
    }
    public Boolean isRootAble(){
        return elementType.isRootAble();
    }
    public Collection<ElementTypeTreeJSON> getAllowedChilds(){
        LinkedList<ElementTypeTreeJSON> ret = new LinkedList<ElementTypeTreeJSON>();
        if(!recursion){
            for(ElementType currType:elementType.getAllowedChilds()){
                if(!tree.contains(currType.getTypeId())) {
                    ret.add(new ElementTypeTreeJSON(currType,tree));
                }else{
                    ret.add(new ElementTypeTreeJSON(currType,tree,true));
                }
            }
        }
        return ret;
    }
    public String getTypeId(){
        return elementType.getTypeId();
    }
    public String getImageBase64(){
        return elementType.getImageBase64();
    }
}
