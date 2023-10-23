package it.cineca.siss.axmr3.doc.entities;

import javax.persistence.*;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 22/10/13
 * Time: 12:29
 * To change this template use File | Settings | File Templates.
 */
@Entity
@Table (name = "DOC_EL_PROCESS")
public class ElementProcessInstance extends BaseMDValueEntity{

    @OneToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "ELEMENT_ID", nullable = true)
    private Element element;
    @Column (name = "PROCESS_INSTANCE_ID")
    private String processInstanceId;

    public Element getElement() {
        return element;
    }

    public void setElement(Element element) {
        this.element = element;
    }

    public String getProcessInstanceId() {
        return processInstanceId;
    }

    public void setProcessInstanceId(String processInstanceId) {
        this.processInstanceId = processInstanceId;
    }
}
