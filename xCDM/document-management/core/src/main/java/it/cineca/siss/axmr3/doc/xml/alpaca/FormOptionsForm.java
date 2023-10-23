package it.cineca.siss.axmr3.doc.xml.alpaca;

import java.util.*;

public class FormOptionsForm {

    protected FormOptionsFormAttribute attributes;
    protected LinkedHashMap<String, FormOptionsFormButton> buttons;

    public FormOptionsForm() {
        buttons=new LinkedHashMap<String, FormOptionsFormButton>();
        attributes=new FormOptionsFormAttribute();
    }


    public FormOptionsFormAttribute getAttributes() {
        return attributes;
    }

    public void setAttributes(FormOptionsFormAttribute attributes) {
        this.attributes = attributes;
    }

    public LinkedHashMap<String, FormOptionsFormButton> getButtons() {
        return buttons;
    }

    public void setButtons(LinkedHashMap<String, FormOptionsFormButton> buttons) {
        this.buttons = buttons;
    }
}
