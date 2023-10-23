package it.cineca.siss.axmr3.doc.xml.alpaca;

import java.util.Collection;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.List;

public class FormOptionsField {

    protected Integer size;
    protected String type;
    protected String helper;
    protected Integer rows;
    protected Integer cols;
    protected String name;
    protected List<String> optionLabels;
    protected LinkedHashMap<String, Object> dependencies;
    protected String dataSourceFunction;
    protected boolean removeDefaultNone;

    public boolean isRemoveDefaultNone() {
        return removeDefaultNone;
    }

    public void setRemoveDefaultNone(boolean removeDefaultNone) {
        this.removeDefaultNone = removeDefaultNone;
    }

    public String getDataSourceFunction() {
        return dataSourceFunction;
    }

    public void setDataSourceFunction(String dataSourceFunction) {
        this.dataSourceFunction = dataSourceFunction;
    }

    public FormOptionsField() {
        optionLabels=new LinkedList<String>();
        dependencies=new LinkedHashMap<String, Object>();
    }

    public LinkedHashMap<String, Object> getDependencies() {
        return dependencies;
    }

    public void setDependencies(LinkedHashMap<String, Object> dependencies) {
        this.dependencies = dependencies;
    }

    public List<String> getOptionLabels() {
        return optionLabels;
    }

    public void setOptionLabels(List<String> optionLabels) {
        this.optionLabels = optionLabels;
    }


    public Integer getSize() {
        return size;
    }


    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public void setSize(Integer size) {
        this.size = size;
    }

    public String getHelper() {
        return helper;
    }

    public void setHelper(String helper) {
        this.helper = helper;
    }

    public Integer getRows() {
        return rows;
    }

    public void setRows(Integer rows) {
        this.rows = rows;
    }

    public Integer getCols() {
        return cols;
    }

    public void setCols(Integer cols) {
        this.cols = cols;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }



}
