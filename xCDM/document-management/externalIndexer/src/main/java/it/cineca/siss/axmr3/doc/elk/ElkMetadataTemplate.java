package it.cineca.siss.axmr3.doc.elk;

import com.google.gson.annotations.Expose;

import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

/**
 * Created by Carlo on 29/01/2016.
 */
public class ElkMetadataTemplate {

    @Expose
    private String name;

    @Expose
    private List<String> viewableByUsers;

    @Expose
    private List<String> viewableByGroups;

    @Expose
    private HashMap<String, Object> values;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public List<String> getViewableByUsers() {
        return viewableByUsers;
    }

    public void setViewableByUsers(List<String> viewableByUsers) {
        this.viewableByUsers = viewableByUsers;
    }

    public List<String> getViewableByGroups() {
        return viewableByGroups;
    }

    public void setViewableByGroups(List<String> viewableByGroups) {
        this.viewableByGroups = viewableByGroups;
    }

    public HashMap<String, Object> getValues() {
        return values;
    }

    public void setValues(HashMap<String, Object> values) {
        this.values = values;
    }

    public void addValues(HashMap<String, Object> values) {
        Iterator<String> it = values.keySet().iterator();
        if (this.values==null) this.values=new HashMap<String, Object>();
        while (it.hasNext()) {
            String key=it.next();
            this.values.put(key, values.get(key));
        }
    }
}
