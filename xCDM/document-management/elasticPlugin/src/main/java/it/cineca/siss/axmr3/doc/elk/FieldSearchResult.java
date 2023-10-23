package it.cineca.siss.axmr3.doc.elk;

import java.util.HashMap;

/**
 * Created by Carlo on 03/02/2016.
 */
public class FieldSearchResult implements Comparable<FieldSearchResult> {

    private Long objId;
    private Float score;
    private String title;
    private String objType;
    private HashMap<String, String> matches;
    private HashMap<String, HashMap<String, Object>> parents;

    public Long getObjId() {
        return objId;
    }

    public void setObjId(Long objId) {
        this.objId = objId;
    }

    public Float getScore() {
        return score;
    }

    public void setScore(Float score) {
        this.score = score;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getObjType() {
        return objType;
    }

    public void setObjType(String objType) {
        this.objType = objType;
    }

    public HashMap<String, String> getMatches() {
        return matches;
    }

    public void setMatches(HashMap<String, String> matches) {
        this.matches = matches;
    }

    public HashMap<String, HashMap<String, Object>> getParents() {
        return parents;
    }

    public void setParents(HashMap<String, HashMap<String, Object>> parents) {
        this.parents = parents;
    }

    public static FieldSearchResult buildFromElkValue(ElkValue elkValue, Float score){
        FieldSearchResult fsr=new FieldSearchResult();
        fsr.fromElkValue(elkValue, score);
        return fsr;
    }

    public void fromElkValue(ElkValue elkValue, Float score){
        this.objId=elkValue.getObjId();
        this.objType=elkValue.getObjType();
        this.title=elkValue.getObjTitle();
        if (this.score==null) {
            this.score=score;
        }else {
            if (this.score<score) this.score=score;
        }
        if (this.matches==null){
            this.matches=new HashMap<String, String>();
        }
        this.matches.put(elkValue.getTemplateName(),elkValue.getFieldName());
        this.parents=elkValue.getParents();
    }

    public int compareTo(FieldSearchResult o) {
        if (o.score>this.score) return -1;
        if (o.score<this.score) return 1;
        return 0;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        FieldSearchResult that = (FieldSearchResult) o;

        return objId != null ? objId.equals(that.objId) : that.objId == null;

    }

    @Override
    public int hashCode() {
        return objId != null ? objId.hashCode() : 0;
    }
}
