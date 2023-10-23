package it.cineca.siss.axmr3.doc.entities.base;

import it.cineca.siss.axmr3.doc.entities.BaseHibernateEntity;
import it.cineca.siss.axmr3.doc.entities.BaseMDValueEntity;
import it.cineca.siss.axmr3.doc.entities.Element;
import it.cineca.siss.axmr3.doc.types.MetadataFieldType;
import it.cineca.siss.axmr3.exceptions.AxmrGenericException;
import org.codehaus.jackson.annotate.JsonIgnore;

import javax.persistence.FetchType;
import javax.persistence.JoinColumn;
import javax.persistence.MappedSuperclass;
import javax.persistence.OneToMany;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

import static it.cineca.siss.axmr3.doc.StdUtils.parseDate;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 09/09/13
 * Time: 11.59
 * To change this template use File | Settings | File Templates.
 */
@MappedSuperclass
public abstract class BaseMetadata<T extends BaseMetadataValue, F extends BaseMetadataField> extends BaseMDValueEntity {

    @OneToMany(fetch = FetchType.EAGER)
    @JoinColumn(name = "MD_ID")
    private Collection<T> values;

    @JsonIgnore
    public Collection<T> getValues() {
        return values;
    }

    public void setValues(Collection<T> values) {
        this.values = values;
    }

    public List<Object> getVals() {
        LinkedList<Object> ret = new LinkedList<Object>();
        if (values != null) {
            for (T v : values) {
                if (v.getValue(getField().getType()) != null)
                    ret.add(v.getValue(getField().getType()));
            }
        }
        return ret;
    }

    public abstract F getField();

    public abstract void setField(F field);

    public boolean isType(MetadataFieldType type) {
        return this.getField().getType().equals(type);
    }

    public void setVal(Object val) throws AxmrGenericException {
        if (this.getValues() == null) {
            this.setValues(new LinkedList<T>());
        }
        T v = getMetadataValueInstance();
        if (isType(MetadataFieldType.EXT_DICTIONARY) || isType(MetadataFieldType.RADIO) || isType(MetadataFieldType.SELECT) || isType(MetadataFieldType.CHECKBOX)) {
            if (val.toString().isEmpty()) {
                v.setCode(null);
                v.setDecode(null);
                this.getValues().add(v);
            } else {
                String codeDecode = val.toString();
                String[] vals = codeDecode.split("###");
                v.setCode(vals[0]);
                v.setDecode(vals[1]);
                this.getValues().add(v);
            }
        }
        if (isType(MetadataFieldType.TEXTBOX)) {
            if (val == null) v.setTextValue("");
            else v.setTextValue(val.toString());
            this.getValues().add(v);
        }
        if (isType(MetadataFieldType.TEXTAREA) && val != null) {
            v.setLongTextValue(val.toString());
            this.getValues().add(v);
        }
        if (isType(MetadataFieldType.DATE)) {
            Date parsed = null;
            if (val instanceof String) {
                if (((String) val).isEmpty()) {
                    v.setDate(null);
                    this.getValues().add(v);
                } else {
                    v.setDate(parseDate(val.toString()));
                    this.getValues().add(v);
                    /*
                    List<DateFormat> dfs = new LinkedList<DateFormat>();
                    dfs.add(new SimpleDateFormat("dd/MM/yyyy"));
                    dfs.add(new SimpleDateFormat("EEE MMM dd hh:mm:ss z yyyy", Locale.US));
                    dfs.add(new SimpleDateFormat("dd/MM/yyyy hh:mm"));
                    boolean parsedOk = false;
                    for (DateFormat df : dfs) {
                        try {
                            parsed = df.parse(val.toString());
                            //it.cineca.siss.axmr3.log.Log.info(getClass(),"parsed date: " + parsed);
                            Calendar newCalendar = Calendar.getInstance();
                            newCalendar.setTime(parsed);
                            v.setDate(newCalendar);
                            this.getValues().add(v);
                            parsedOk = true;
                        } catch (ParseException e) {
                            //it.cineca.siss.axmr3.log.Log.info(getClass(),"Data "+val.toString()+" formato non accettato");
                        }
                    }
                    if (!parsedOk) {
                        try {
                            Long unixTime = Long.parseLong(val.toString());
                            Calendar newCalendar = Calendar.getInstance();
                            newCalendar.setTime(new Date(unixTime));
                            v.setDate(newCalendar);
                            this.getValues().add(v);
                        } catch (Exception e) {
                            //it.cineca.siss.axmr3.log.Log.info(getClass(),"Data "+val.toString()+" formato non accettato");
                        }

                    }
                    */
                }
            } else {

            }

            if (val instanceof GregorianCalendar) {
                v.setDate((GregorianCalendar) val);
                this.getValues().add(v);
            }

        }
        if (isType(MetadataFieldType.ELEMENT_LINK) && (val instanceof Element)) {
            v.setElement_link((Element) val);
            this.getValues().add(v);
        }
    }

    public abstract T getMetadataValueInstance();

    @Override
    public String toString() {
        return "BaseMetadata{" +
                "values=" + values +
                '}';
    }
}
