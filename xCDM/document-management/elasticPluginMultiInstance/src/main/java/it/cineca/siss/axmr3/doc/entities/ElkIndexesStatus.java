package it.cineca.siss.axmr3.doc.entities;

import javax.persistence.*;
import java.util.Calendar;

/**
 * Created by Carlo on 01/02/2016.
 */
@Entity
@Table(name = "DOC_ELK_MULTIIDX",
        uniqueConstraints = @UniqueConstraint(
                name = "DOC_ELK_MULTIIDX_UIDX01",
                columnNames = {"NAME", "OBJTYPE", "OBJID", "INSTANCENAME"}
        )
)
public class ElkIndexesStatus extends BaseHibernateEntity {

    @Column(name = "NAME")
    private String indexName;
    @Column(name = "INSTANCENAME")
    private String instance;
    @Column(name = "OBJTYPE")
    private String objType;
    @Column(name = "OBJID")
    private Long objId;
    @Temporal(value = TemporalType.TIMESTAMP)
    @Column(name = "LAST_UDP_DT")
    private Calendar lastUpdateDt;

    public String getInstance() {
        return instance;
    }

    public void setInstance(String instance) {
        this.instance = instance;
    }

    public Long getObjId() {
        return objId;
    }

    public void setObjId(Long objId) {
        this.objId = objId;
    }

    public String getIndexName() {
        return indexName;
    }

    public void setIndexName(String indexName) {
        this.indexName = indexName;
    }

    public Calendar getLastUpdateDt() {
        return lastUpdateDt;
    }

    public void setLastUpdateDt(Calendar lastUpdateDt) {
        this.lastUpdateDt = lastUpdateDt;
    }

    public String getObjType() {
        return objType;
    }

    public void setObjType(String objType) {
        this.objType = objType;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;

        ElkIndexesStatus that = (ElkIndexesStatus) o;

        if (indexName != null ? !indexName.equals(that.indexName) : that.indexName != null) return false;
        if (objType != null ? !objType.equals(that.objType) : that.objType != null) return false;
        return lastUpdateDt != null ? lastUpdateDt.equals(that.lastUpdateDt) : that.lastUpdateDt == null;

    }

    @Override
    public int hashCode() {
        int result = super.hashCode();
        result = 31 * result + (indexName != null ? indexName.hashCode() : 0);
        result = 31 * result + (objType != null ? objType.hashCode() : 0);
        result = 31 * result + (lastUpdateDt != null ? lastUpdateDt.hashCode() : 0);
        return result;
    }


}
