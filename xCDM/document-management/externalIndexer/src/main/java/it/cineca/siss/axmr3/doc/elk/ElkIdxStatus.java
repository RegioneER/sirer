package it.cineca.siss.axmr3.doc.elk;

import java.io.Serializable;
import java.util.GregorianCalendar;

/**
 * Created by Carlo on 05/02/2016.
 */
public class ElkIdxStatus implements Serializable{

    private String idxName;
    private String objType;
    private GregorianCalendar lastUpdateDt;
    private Long indexed;
    private Long toBeUpdated;
    private Long missing;

    public String getIdxName() {
        return idxName;
    }

    public void setIdxName(String idxName) {
        this.idxName = idxName;
    }

    public String getObjType() {
        return objType;
    }

    public void setObjType(String objType) {
        this.objType = objType;
    }

    public GregorianCalendar getLastUpdateDt() {
        return lastUpdateDt;
    }

    public void setLastUpdateDt(GregorianCalendar lastUpdateDt) {
        this.lastUpdateDt = lastUpdateDt;
    }

    public Long getIndexed() {
        return indexed;
    }

    public void setIndexed(Long indexed) {
        this.indexed = indexed;
    }

    public Long getToBeUpdated() {
        return toBeUpdated;
    }

    public void setToBeUpdated(Long toBeUpdated) {
        this.toBeUpdated = toBeUpdated;
    }

    public Long getMissing() {
        return missing;
    }

    public void setMissing(Long missing) {
        this.missing = missing;
    }
}
