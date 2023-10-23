package it.cineca.siss.axmr3.doc.elk;

import com.google.gson.annotations.Expose;

/**
 * Created by Carlo on 29/01/2016.
 */
public class ElkMapping {

    //@Expose(serialize = false)
    //private String name;

    @Expose
    private String type;

    @Expose
    private String index; //analyzed, not_analized, ...

    //@Expose
    //private String analyzer;

    //public String getName() {
    //    return name;
    //}
    //public void setName(String name) {
    //    this.name = name;
    //}

    public String getType() {
        return type;
    }
    public void setType(String type) {
        this.type = type;
    }

    public String getIndex() {
        return index;
    }
    public void setIndex(String index) {
        this.index = index;
    }

    //public ElkMapping(String name, String type, String index){
    //    this.name=name;
    //    this.type=type;
    //    this.index=index;
    //}

    public ElkMapping(String type, String index){
        //this.name=name;
        this.type=type;
        this.index=index;
        //this.analyzer="standard";
    }

    /*
    public String getAnalyzer() {
        return analyzer;
    }

    public void setAnalyzer(String analyzer) {
        this.analyzer = analyzer;
    }
    */

}
