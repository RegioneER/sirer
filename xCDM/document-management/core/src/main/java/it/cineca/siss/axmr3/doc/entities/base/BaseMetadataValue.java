package it.cineca.siss.axmr3.doc.entities.base;

import it.cineca.siss.axmr3.doc.entities.BaseHibernateEntity;
import it.cineca.siss.axmr3.doc.entities.BaseMDValueEntity;
import it.cineca.siss.axmr3.doc.entities.Element;
import it.cineca.siss.axmr3.doc.types.MetadataFieldType;
import org.codehaus.jackson.annotate.JsonIgnore;

import javax.persistence.*;
import java.util.Calendar;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 09/09/13
 * Time: 11.50
 * To change this template use File | Settings | File Templates.
 */
@MappedSuperclass
public class BaseMetadataValue extends BaseMDValueEntity {

    @Column (name="TXT_VALUE", length=4000)
    private String textValue;
    @Lob
    @Column (name="LONG_TXT_VALUE")
    private String longTextValue;
    @Column (name="CODE")
    private String code;
    @Column (name="DECODE")
    private String decode;
    @Temporal(TemporalType.TIMESTAMP)
    @Column (name="DATE_VALUE")
    private Calendar date;
    @OneToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "ELEMENT_LINK")
    private Element element_link;

    @JsonIgnore
    public String getCode() {
        return code;
    }

    public void setCode(String code) {
        this.code = code;
    }

    @JsonIgnore
    public Calendar getDate() {
        return date;
    }

    public void setDate(Calendar date) {
        this.date = date;
    }

    @JsonIgnore
    public String getDecode() {
        return decode;
    }

    public void setDecode(String decode) {
        this.decode = decode;
    }

    @JsonIgnore
    public Element getElement_link() {
        return element_link;
    }

    public void setElement_link(Element element_link) {
        this.element_link = element_link;
    }

    public String getLongTextValue() {
        return longTextValue;
    }

    public void setLongTextValue(String longTextValue) {
        this.longTextValue = longTextValue;
    }

    public String getTextValue() {
        return textValue;
    }

    public void setTextValue(String textValue) {
        this.textValue = textValue;
    }

    public Object getValue(MetadataFieldType type){
        if (type.equals(MetadataFieldType.TEXTBOX)) return this.textValue;
        if (type.equals(MetadataFieldType.TEXTAREA)) return this.longTextValue;
        if (type.equals(MetadataFieldType.CHECKBOX) || type.equals(MetadataFieldType.RADIO) || type.equals(MetadataFieldType.SELECT)|| type.equals(MetadataFieldType.EXT_DICTIONARY)) {
            if (this.code==null) return null;
            return this.code+"###"+this.decode;
        }
        if (type.equals(MetadataFieldType.DATE)) return this.date;
        if (type.equals(MetadataFieldType.RICHTEXT)) return this.longTextValue;
        if (type.equals(MetadataFieldType.ELEMENT_LINK)) return this.element_link;
        return null;
    }

    public void setValue(MetadataFieldType type, Object value, Object value1){
        if (type.equals(MetadataFieldType.TEXTBOX)) this.textValue=value.toString();
        if (type.equals(MetadataFieldType.TEXTAREA)) this.longTextValue=value.toString();
        if (type.equals(MetadataFieldType.CHECKBOX) || type.equals(MetadataFieldType.RADIO) || type.equals(MetadataFieldType.SELECT)) {
            this.code=value.toString();
            this.decode=value1.toString();
        }
        if (type.equals(MetadataFieldType.EXT_DICTIONARY)) {
            this.code=value.toString();
            this.decode=value1.toString();
        }
        if (type.equals(MetadataFieldType.DATE)) this.date=(Calendar) value;
        if (type.equals(MetadataFieldType.RICHTEXT)) this.longTextValue=value.toString();
        if (type.equals(MetadataFieldType.ELEMENT_LINK)) this.element_link=(Element) value;
    }



}
