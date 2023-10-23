package it.cineca.siss.axmr3.doc.entities;

import it.cineca.siss.axmr3.doc.entities.base.BaseMetadata;
import org.codehaus.jackson.annotate.JsonIgnore;

import javax.persistence.*;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 31/07/13
 * Time: 12.45
 * To change this template use File | Settings | File Templates.
 */
@Entity
/*Provo ad inserire il valore Fri Dec 06 00:00:00 CET 2013 in ApprovDADSRETT.dataFirma
Campo in cui inserire: ApprovDADSRETT.dataFirma
Valore da inserire:Fri Dec 06 00:00:00 CET 2013
SetMetadataValue: ApprovDADSRETT - dataFirma - Fri Dec 06 00:00:00 CET 2013*/

@Table (name="DOC_OBJ_MD")
public class ElementMetadata extends BaseMetadata<ElementMetadataValue, MetadataField> {

	@OneToOne(fetch = FetchType.EAGER)
    @JoinColumn(name = "FIELD_ID")
    private MetadataField field;

    public MetadataField getField() {
        return field;
    }

    public void setField(MetadataField field) {
        this.field = field;
    }

    @OneToOne(fetch = FetchType.EAGER)
    @JoinColumn(name = "TEMPLATE_ID")
    private MetadataTemplate template;

    public String getTemplateName(){
        return template.getName();
    }

    public String getFieldName(){
        return getField().getName();
    }

    public Long getTemplateId(){
        return template.getId();
    }

    @JsonIgnore
    public MetadataTemplate getTemplate() {
        return template;
    }

    public void setTemplate(MetadataTemplate template) {
        this.template = template;
    }

    @JsonIgnore
    @Override
    public ElementMetadataValue getMetadataValueInstance() {
        return new ElementMetadataValue();
    }

    @Override
    public String toString() {
        return "ElementMetadata{" +
                "field=" + field +
                ", template=" + template +
                '}';
    }

    @JsonIgnore
    @Transient
    private EmendamentoAction emeAction;

    @JsonIgnore
    public EmendamentoAction getEmeAction() {
        return emeAction;
    }

    public void setEmeAction(EmendamentoAction action) {
        this.emeAction = action;
    }

}
