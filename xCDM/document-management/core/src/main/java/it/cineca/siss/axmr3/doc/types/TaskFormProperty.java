package it.cineca.siss.axmr3.doc.types;

import org.activiti.engine.form.FormProperty;

import java.io.Serializable;
import java.util.LinkedList;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 10/11/13
 * Time: 12:56
 * To change this template use File | Settings | File Templates.
 */
public class TaskFormProperty implements Serializable {


    private String name;
    private String id;
    private String type;
    private boolean mandatory;
    private boolean writable;
    private boolean readable;
    private String value;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public boolean isMandatory() {
        return mandatory;
    }

    public void setMandatory(boolean mandatory) {
        this.mandatory = mandatory;
    }

    public boolean isWritable() {
        return writable;
    }

    public void setWritable(boolean writable) {
        this.writable = writable;
    }

    public boolean isReadable() {
        return readable;
    }

    public void setReadable(boolean readable) {
        this.readable = readable;
    }

    public String getValue() {
        return value;
    }

    public void setValue(String value) {
        this.value = value;
    }

    public static TaskFormProperty fromActivitiFormProperty(FormProperty p){
        TaskFormProperty prop=new TaskFormProperty();
        prop.name=p.getName();
        prop.id=p.getId();
        prop.type=p.getType().getName();
        prop.mandatory=p.isRequired();
        prop.writable=p.isWritable();
        prop.readable=p.isReadable();
        prop.value=p.getValue();
        return prop;
    }

    public static List<TaskFormProperty> fromActivitiFormPropertyList(List<FormProperty> props){
        List<TaskFormProperty> ret=new LinkedList<TaskFormProperty>();
        for (FormProperty p:props){
            ret.add(fromActivitiFormProperty(p));
        }
        return ret;
    }

}
