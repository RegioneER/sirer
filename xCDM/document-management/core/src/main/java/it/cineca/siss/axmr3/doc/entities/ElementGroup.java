package it.cineca.siss.axmr3.doc.entities;

import javax.persistence.Entity;
import javax.persistence.Table;

/**
 * Created by giorgio on 09/05/14.
 */
@Entity
@Table(name="DOC_OBJ_GROUP")
public class ElementGroup extends BaseMDValueEntity {

    private Long groupId;
    private Long item;

    public Long getGroupId() {
        return groupId;
    }

    public void setGroupId(Long group) {
        this.groupId = group;
    }

    public Long getItem() {
        return item;
    }

    public void setItem(Long item) {
        this.item = item;
    }
}