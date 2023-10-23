package it.cineca.siss.axmr3.doc.entities;

import it.cineca.siss.axmr3.doc.entities.base.BaseMetadataField;
import org.codehaus.jackson.annotate.JsonIgnore;

import javax.persistence.*;
import java.util.Objects;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 31/07/13
 * Time: 12.36
 * To change this template use File | Settings | File Templates.
 */
@Entity
@Table (name="DOC_MD_FIELD")
public class MetadataField extends BaseMetadataField {

    @Column (name = "TYPE_FILTERS")
    private String typefilters;
    @ManyToOne
    @JoinColumn(name = "TEMPLATE_ID", nullable = false)
    private MetadataTemplate template;
    @Column (name = "F_SIZE", nullable = true)
    private Integer size;
    @Column (name = "F_MACRO", nullable = true)
    private String macro;


    @Column (name = "F_MACRO_VIEW", nullable = true)
    
    private String macroView;
    @Column(name = "DELETED", nullable = false)
    private boolean deleted;

    @Column(name = "CASCADE", nullable = true,  columnDefinition = "NUMBER(1,0) DEFAULT 0")
    private Boolean cascadeDelete;

    @Column (name = "BASE_NAME_ORA", nullable = true)
    private String baseNameOra;

    @Column(name = "REGEXP_CHECK", nullable = true, length = 4000)
    private String regexpCheck;

    public String getRegexpCheck() {
        return regexpCheck;
    }

    public void setRegexpCheck(String regexpCheck) {
        this.regexpCheck = regexpCheck;
    }

    @Transient
    private boolean emendamentoChangePending = false;

    public Boolean isCascadeDelete() {
        if(cascadeDelete==null){
            cascadeDelete=false;
        }
        return cascadeDelete;
    }

    public void setCascadeDelete(Boolean cascadeDelete) {
        if(cascadeDelete==null){
            cascadeDelete=false;
        }
        this.cascadeDelete = cascadeDelete;
    }

    public boolean isDeleted() {
        return deleted;
    }

    public void setDeleted(boolean deleted) {
        this.deleted = deleted;
    }

    public String getMacroView() {
        return macroView;
    }

    public void setMacroView(String macroView) {
        this.macroView = macroView;
    }

    public String getMacro() {
        return macro;
    }

    public void setMacro(String macro) {
        this.macro = macro;
    }

    public Integer getSize() {
        return size;
    }

    public void setSize(Integer size) {
        this.size = size;
    }

    @JsonIgnore
    public MetadataTemplate getTemplate() {
        return template;
    }

    public String getTemplateName(){
        return this.getTemplate().getName();
    }

    public String getTypefilters() {
        return typefilters;
    }

    public void setTypefilters(String typefilters) {
        this.typefilters = typefilters;
    }

    public void setTemplate(MetadataTemplate template) {
        this.template = template;
    }

    public String getExtendedName(){
        return this.getTemplate().getName()+"."+this.getName();
    }


    public String getBaseNameOra() {
        return baseNameOra;
    }

    public void setBaseNameOra(String baseNameOra) {
        this.baseNameOra = baseNameOra;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;

        MetadataField that = (MetadataField) o;
        return deleted == that.deleted &&
                emendamentoChangePending == that.emendamentoChangePending &&
                Objects.equals(typefilters, that.typefilters) &&
                Objects.equals(template, that.template) &&
                Objects.equals(size, that.size) &&
                Objects.equals(macro, that.macro) &&
                Objects.equals(macroView, that.macroView) &&
                Objects.equals(cascadeDelete, that.cascadeDelete) &&
                Objects.equals(baseNameOra, that.baseNameOra) &&
                Objects.equals(regexpCheck, that.regexpCheck);
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), typefilters, template, size, macro, macroView, deleted, cascadeDelete, baseNameOra, regexpCheck, emendamentoChangePending);
    }

    public boolean isEmendamentoChangePending() {
        return emendamentoChangePending;
    }

    public void setEmendamentoChangePending(boolean emendamentoChangePending) {
        this.emendamentoChangePending = emendamentoChangePending;
    }
}
