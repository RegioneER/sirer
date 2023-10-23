package it.cineca.siss.axmr3.doc.elk;

import com.google.gson.annotations.Expose;
import it.cineca.siss.axmr3.authentication.IAuthority;
import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.doc.entities.Element;
import org.apache.log4j.Logger;

import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by Carlo on 29/01/2016.
 */
public class ElkFullElement extends ElkSimpleElement {

    @Expose
    public HashMap<String, List<ElkFullElement>> children;



    public HashMap<String, List<ElkFullElement>> getChildren() {
        return children;
    }

    public void setChildren(HashMap<String, List<ElkFullElement>> children) {
        this.children = children;
    }

    public static ElkFullElement elementToComplex(Element el, boolean isRoot, List<String> indexableObjs, List<String> fullIndexWithParentsObjsList){
        ElkSimpleElement sel= ElkSimpleElement.elementToSimple(el);
        return simpleToComplex(sel, el, isRoot, indexableObjs, fullIndexWithParentsObjsList);
    }

    public static ElkFullElement simpleToComplex(ElkSimpleElement se, Element el, boolean isRoot, List<String> indexableObjs, List<String> fullIndexWithParentsObjsList){
        ElkFullElement sel=(ElkFullElement) se;
        HashMap<String, List<ElkFullElement>> children=new HashMap<String, List<ElkFullElement>>();
        //if (isRoot) Logger.getLogger(ElkFullElement.class).info(" - - Processo figli");
        for (Element child:el.getChildren()){
            if (
                    (indexableObjs!=null && indexableObjs.contains(child.getType().getTypeId().toLowerCase())) ||
                    (indexableObjs==null && child.getType().isSearchable())
                    ){
               // System.out.println(" - - Processo figlio " + child.getId() + " - Tipo: " + child.getType().getTypeId());
                if (!children.containsKey(child.getType().getTypeId())) {
                    children.put(child.getType().getTypeId(), new LinkedList<ElkFullElement>());
                }
                children.get(child.getType().getTypeId()).add(ElkFullElement.elementToComplex(child, false, indexableObjs, fullIndexWithParentsObjsList));
            }
        }
        if (el.getParent()!=null){
            if (fullIndexWithParentsObjsList==null || fullIndexWithParentsObjsList.size()==0){
                //System.out.println(" - - Elemento di tipo "+el.getType().getTypeId()+" Aggiungo padre - (non definita fullIndexWithParentsObjsList)");
                sel.setParent(ElkSimpleElement.elementToSimpleWithParents(el.getParent()));
            }else {
                if (fullIndexWithParentsObjsList.contains(el.getType().getTypeId().toLowerCase())){
                    //System.out.println(" - - Elemento di tipo "+el.getType().getTypeId()+" - Aggiungo padre - (presente in lista fullIndexWithParentsObjsList)");
                    sel.setParent(ElkSimpleElement.elementToSimpleWithParents(el.getParent()));
                }else {
                    //System.out.println(" - - Elemento di tipo "+el.getType().getTypeId()+" - SCARTO padre - (NON presente in lista fullIndexWithParentsObjsList)");
                }

            }


        }
        sel.setChildren(children);
        return sel;
    }

    public void adjustScope(IUser user) {
        super.adjustScope(user);
        if (this.getParent()!=null) {
            this.getParent().adjustScope(user);
        }
        HashMap<String, List<ElkFullElement>> chHash = new HashMap<String, List<ElkFullElement>>();
        if (this.getChildren()!=null) {
            Iterator<String> it = this.getChildren().keySet().iterator();
            while (it.hasNext()) {
                String objType = it.next();
                List<ElkFullElement> childrens = new LinkedList<ElkFullElement>();
                for (ElkFullElement chEl : this.getChildren().get(objType)) {
                    boolean groupAuthPassed = false;
                    boolean userAuthPassed = false;
                    if (chEl.getViewableByGroups().size() > 0) {
                        for (int i = 0; i < user.getAuthorities().size(); i++) {
                            String authLowerCase = ((List<IAuthority>) user.getAuthorities()).get(i).getAuthority().toLowerCase();
                            for (String g1 : chEl.getViewableByGroups()) {
                                if (g1.toLowerCase().equals(authLowerCase)) groupAuthPassed = true;
                            }

                        }
                    }
                    if (chEl.getViewableByUsers().size() > 0) {
                        String username = user.getUsername().toLowerCase();
                        for (String u1 : chEl.getViewableByUsers()) {
                            u1 = u1.toLowerCase();
                            if (u1.equals(username) || u1.equals("all_users") || u1.equals("*")) userAuthPassed = true;
                        }
                    }
                    if (groupAuthPassed || userAuthPassed) {
                        chEl.adjustScope(user);
                        childrens.add(chEl);
                    }
                }
                //this.getChildren().remove(objType);
                chHash.put(objType, childrens);
                //this.getChildren().put(objType, childrens);
            }
        }
        this.setChildren(chHash);
    }
}
