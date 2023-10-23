package it.cineca.siss.axmr3.doc.elk;

import com.google.gson.annotations.Expose;

/**
 * Created by Carlo on 29/01/2016.
 */
public class ElkTemplate {

    //@Expose(serialize = false)
    //private String name;

    @Expose
    private String match;

    @Expose
    private String match_mapping_type; //analyzed, not_analized, ...

    @Expose
    private ElkMapping mapping;


    public ElkTemplate(String match, String mappingType, ElkMapping mapping){
        //this.name=name;
        this.setMatch(match);
        this.setMatch_mapping_type(mappingType);
        this.setMapping(mapping);
    }

    public String getMatch() {
        return match;
    }

    public void setMatch(String match) {
        this.match = match;
    }

    public String getMatch_mapping_type() {
        return match_mapping_type;
    }

    public void setMatch_mapping_type(String match_pattern) {
        this.match_mapping_type = match_pattern;
    }

    public ElkMapping getMapping() {
        return mapping;
    }

    public void setMapping(ElkMapping mapping) {
        this.mapping = mapping;
    }
}
