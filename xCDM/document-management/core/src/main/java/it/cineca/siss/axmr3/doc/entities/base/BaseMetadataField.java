package it.cineca.siss.axmr3.doc.entities.base;

import com.google.gson.Gson;
import it.cineca.siss.axmr3.doc.entities.BaseHibernateEntity;
import it.cineca.siss.axmr3.doc.entities.BaseModelEntity;
import it.cineca.siss.axmr3.doc.types.MetadataFieldType;
import net.minidev.json.JSONValue;
import org.codehaus.jackson.annotate.JsonIgnore;

import javax.persistence.Column;
import javax.persistence.Lob;
import javax.persistence.MappedSuperclass;
import javax.persistence.Transient;
import java.util.*;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 10/09/13
 * Time: 10.30
 * To change this template use File | Settings | File Templates.
 */
@MappedSuperclass
public class BaseMetadataField extends BaseModelEntity {

    @Column(name="NAME")
    private String name;
    @Column (name="TYPE")
    private MetadataFieldType type;
    @Column (name="MANDATORY")
    private boolean mandatory;
    @Column (name="AVAILABLE_VALUES")
    @Lob
    private String availableValues;
    @Column (name="EXT_DICTIONARY")
    private String externalDictionary;
    @Column (name="ADD_FILTER_FIELDS")
    private String addFilterFields;
    @Column(name = "POSITION")
    private Integer position;
    @Transient
    private HashMap<String, String> availableValuesMap;

    public String getExternalDictionary() {
        return externalDictionary;
    }

    public void setExternalDictionary(String externalDictionary) {
        this.externalDictionary = externalDictionary;
    }

    public String getAddFilterFields() {
        return addFilterFields;
    }

    public void setAddFilterFields(String addFilterFields) {
        this.addFilterFields = addFilterFields;
    }

    public Integer getPosition() {
        return position;
    }

    public void setPosition(Integer position) {
        this.position = position;
    }

    public String getAvailableValues() {
        return availableValues;
    }

    public void setAvailableValues(String availableValues) {
        this.availableValues = availableValues;
    }

    public boolean isMandatory() {
        return mandatory;
    }

    public void setMandatory(boolean mandatory) {
        this.mandatory = mandatory;
    }


    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public MetadataFieldType getType() {
        return type;
    }

    public void setType(MetadataFieldType type) {
        this.type = type;
    }

    @JsonIgnore
    public boolean isJson(){
        try{
            new Gson().fromJson(availableValues, LinkedHashMap.class);
            return true;
        }catch (Exception ex){
            return false;
        }

    }

    @JsonIgnore
    public LinkedHashMap<String, String> getAvailableValuesMap(){
        if (this.availableValuesMap==null) {
            TreeMap<String, String> ret = new TreeMap<String, String>();
            LinkedHashMap<String, String> ret2 = new LinkedHashMap<String, String>();
            LinkedHashMap<String, String> ret3 = new LinkedHashMap<String, String>();
            if (availableValues!=null) {
                if (JSONValue.isValidJson(availableValues)) {
                    ret2 = new Gson().fromJson(availableValues, LinkedHashMap.class);
                    ret3 = (LinkedHashMap<String, String>) JSONValue.parseKeepingOrder(availableValues);
                    ret = new TreeMap<String, String>(ret2);
                } else {
                    ret2.put("jsonFromQuery", this.getId() + "");
                }
            }else return null;
            Set<String> keys = ret.keySet();
            for (String key : keys) {
                //it.cineca.siss.axmr3.log.Log.info(getClass(),"in AvailableValues map ho key: "+key+" value:"+ret.get(key));
            }
            keys = ret2.keySet();
            for (String key : keys) {
                //it.cineca.siss.axmr3.log.Log.info(getClass(),"in AvailableValues map potrei avere key: "+key+" value:"+ret2.get(key));
            }

            keys = ret3.keySet();
            for (String key : keys) {
                //it.cineca.siss.axmr3.log.Log.info(getClass(),"in AvailableValues map potrei avere anche key: "+key+" value:"+ret3.get(key));
            }
            return ret2;
        }else return (LinkedHashMap<String, String>) this.availableValuesMap;

    }

    public void setAvailableValuesMap(HashMap<String, String> availableValuesMap) {
        this.availableValuesMap = availableValuesMap;
    }

    @Override
    public String toString() {
        return "BaseMetadataField{" +
                "name='" + name + '\'' +
                ", type=" + type +
                ", mandatory=" + mandatory +
                "} " + super.toString();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        //if (!super.equals(o)) return false;

        BaseMetadataField that = (BaseMetadataField) o;

        if (mandatory != that.mandatory) return false;
        if (addFilterFields != null ? !addFilterFields.equals(that.addFilterFields) : that.addFilterFields != null)
            return false;
        if (availableValues != null ? !availableValues.equals(that.availableValues) : that.availableValues != null)
            return false;
        if (externalDictionary != null ? !externalDictionary.equals(that.externalDictionary) : that.externalDictionary != null)
            return false;
        if (name != null ? !name.equals(that.name) : that.name != null) return false;
        if (position != null ? !position.equals(that.position) : that.position != null) return false;
        if (type != that.type) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = super.hashCode();
        result = 31 * result + (name != null ? name.hashCode() : 0);
        result = 31 * result + (type != null ? type.hashCode() : 0);
        return result;
    }
}
