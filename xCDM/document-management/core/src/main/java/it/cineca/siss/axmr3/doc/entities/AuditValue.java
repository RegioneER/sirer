package it.cineca.siss.axmr3.doc.entities;

import it.cineca.siss.axmr3.doc.entities.base.BaseMetadataValue;
import it.cineca.siss.axmr3.doc.types.MetadataFieldType;

import javax.persistence.*;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 09/09/13
 * Time: 11.44
 * To change this template use File | Settings | File Templates.
 */
@Entity
@Table(name = "DOC_AUDIT_MD_VAL")
public class AuditValue extends BaseMetadataValue {

    @Column(name = "OLD")
    private boolean old;
    @OneToOne(fetch = FetchType.EAGER)
    @JoinColumn(name = "DM_SESSION_ID", nullable = true)
    private DataManagementSession dmSession;

    public DataManagementSession getDmSession() {
        return dmSession;
    }

    public void setDmSession(DataManagementSession dmSession) {
        this.dmSession = dmSession;
    }

    public boolean isOld() {
        return old;
    }

    public void setOld(boolean old) {
        this.old = old;
    }


    /**
     * override per far restituire, in caso di element link, come code l'id e decode il titleString dell'elemento linkato
     * al posto dell'elemento vero e proprio
     */
    public Object getValue(MetadataFieldType type) {
        if (type.equals(MetadataFieldType.TEXTBOX)) return this.getTextValue();
        if (type.equals(MetadataFieldType.TEXTAREA)) return this.getLongTextValue();
        if (type.equals(MetadataFieldType.CHECKBOX) || type.equals(MetadataFieldType.RADIO) || type.equals(MetadataFieldType.SELECT) || type.equals(MetadataFieldType.EXT_DICTIONARY)) {
            if (this.getCode() == null) return null;
            return this.getCode() + "###" + this.getDecode();
        }
        if (type.equals(MetadataFieldType.DATE)) return this.getDate();
        if (type.equals(MetadataFieldType.RICHTEXT)) return this.getLongTextValue();
        if (type.equals(MetadataFieldType.ELEMENT_LINK))
            return this.getElement_link().getId() + "###" + this.getElement_link().getTitleString();
        return null;
    }

}
