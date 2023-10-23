package it.cineca.siss.axmr3.doc.controls.json;

import java.io.Serializable;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by Carlo on 12/09/2016.
 */
public class Configuration implements Serializable {

    protected List<SubmitButton> submitButtons;
    protected List<Rule> rules;

    public Configuration() {
        this.submitButtons=new LinkedList<SubmitButton>();
        this.rules=new LinkedList<Rule>();
    }

    public List<SubmitButton> getSubmitButtons() {
        return submitButtons;
    }

    public void setSubmitButtons(List<SubmitButton> submitButtons) {
        this.submitButtons = submitButtons;
    }

    public List<Rule> getRules() {
        return rules;
    }

    public void setRules(List<Rule> rules) {
        this.rules = rules;
    }


    public String toJs(String lang, String ctrlsName){
        String triggerEvents="";
        String onLoadEvent="";
        String buttonClickEvents="";
        HashMap<String,List<String>> btnCtrls=new HashMap<String, List<String>>();
        HashMap<String, List<String>> fieldControls=new HashMap<String, List<String>>();

        String jsClass="var "+ctrlsName+"Controls = function(formId) {" +
                "\n\tthis.formId=formId;"+
                "\n\tthis.emptyControls={};"+
                "\n\tthis.disableControls={};"+
                "\n\tthis.mandatoryControls={};"+
                "\n\tthis.confirmControls={};"+
                "\n\tthis.warningControls={};"+
                "\n\tthis.validityControls={};"+
                "\n\tvar that=this;"+
                "\n\tthis.buttonsFields={};";
        for (Rule rule:getRules()){
            if (rule.getCriteria().getEmpty()!=null && rule.getCriteria().getEmpty().getConditions()!=null) {
                jsClass+="\n\tthis.emptyControls['"+rule.getRule()+"']={};";
            }
            if (rule.getCriteria().getDisable()!=null && rule.getCriteria().getDisable().getConditions()!=null) {
                jsClass+="\n\tthis.disableControls['"+rule.getRule()+"']={};";
            }
            if (rule.getCriteria().getMandatory()!=null && (rule.getCriteria().getMandatory().getConditions()!=null || rule.getCriteria().getMandatory().isAlways())) {
                jsClass+="\n\tthis.mandatoryControls['"+rule.getRule()+"']={};";
            }
            if (rule.getCriteria().getConfirm()!=null && rule.getCriteria().getConfirm().getConditions()!=null) {
                jsClass+="\n\tthis.confirmControls['"+rule.getRule()+"']={};";
            }
            if (rule.getCriteria().getWarning()!=null && rule.getCriteria().getWarning().getConditions()!=null) {
                jsClass+="\n\tthis.warningControls['"+rule.getRule()+"']={};";
            }
            if (rule.getCriteria().getValidity()!=null && rule.getCriteria().getValidity().getConditions()!=null) {
                jsClass+="\n\tthis.validityControls['"+rule.getRule()+"']={};";
            }
            jsClass+=rule.toJs(lang);

            List<String> loadJs=new LinkedList<String>();
            if (rule.getCriteria().getEmpty()!=null && rule.getCriteria().getEmpty().getConditions()!=null) {
                for(String field: rule.getEmptyImpactedFields()){
                    if (!fieldControls.containsKey(field)) {
                        LinkedList<String> cntrls = new LinkedList<String>();
                        fieldControls.put(field, cntrls);
                    }
                    for(String field2:rule.getFields()) {
                        String ctrl="that.emptyControls['" + rule.getRule() + "']['"+field2+"']()";
                        fieldControls.get(field).add(ctrl);
                        if (!loadJs.contains(ctrl)) loadJs.add(ctrl);
                    }
                }
            }
            if (rule.getCriteria().getDisable()!=null && rule.getCriteria().getDisable().getConditions()!=null) {
                for(String field: rule.getDisableImpactedFields()){
                    if (!fieldControls.containsKey(field)) {
                        LinkedList<String> cntrls = new LinkedList<String>();
                        fieldControls.put(field, cntrls);
                    }
                    for(String field2:rule.getFields()) {
                        String ctrl="that.disableControls['" + rule.getRule() + "']['"+field2+"']()";
                        fieldControls.get(field).add(ctrl);
                        if (!loadJs.contains(ctrl)) loadJs.add(ctrl);
                    }
                }
            }
            for (String ctrl:loadJs){
                onLoadEvent+="\n\t\t"+ctrl;
            }

            for(SubmitButton btn:getSubmitButtons()) {
                for (String button: rule.getButtons()) {
                    if (btn.getName().equals(button)){
                         for (String field:rule.getFields()){
                             if (btn.getFields().contains(field)){
                                 if (rule.getCriteria().getMandatory()!=null && (rule.getCriteria().getMandatory().getConditions()!=null || rule.getCriteria().getMandatory().isAlways())){
                                     if (!btnCtrls.containsKey(button)) {
                                         btnCtrls.put(button, new LinkedList<String>());
                                     }
                                     btnCtrls.get(button).add("that.mandatoryControls['"+rule.getRule()+"']['"+field+"']()");
                                 }
                                 if (rule.getCriteria().getConfirm()!=null && rule.getCriteria().getConfirm().getConditions()!=null){
                                     if (!btnCtrls.containsKey(button)) {
                                         btnCtrls.put(button, new LinkedList<String>());
                                     }
                                     btnCtrls.get(button).add("that.confirmControls['"+rule.getRule()+"']['"+field+"']()");
                                 }
                                 if (rule.getCriteria().getWarning()!=null && rule.getCriteria().getWarning().getConditions()!=null){
                                     if (!btnCtrls.containsKey(button)) {
                                         btnCtrls.put(button, new LinkedList<String>());
                                     }
                                     btnCtrls.get(button).add("that.warningControls['"+rule.getRule()+"']['"+field+"']()");
                                 }
                                 if (rule.getCriteria().getValidity()!=null && rule.getCriteria().getValidity().getConditions()!=null){
                                     if (!btnCtrls.containsKey(button)) {
                                         btnCtrls.put(button, new LinkedList<String>());
                                     }
                                     btnCtrls.get(button).add("that.validityControls['"+rule.getRule()+"']['"+field+"']()");
                                 }
                             }
                         }
                    }
                }




            }
        }

        jsClass+="\n\tthis.buttons={};";
        for(SubmitButton btn:getSubmitButtons()) {
            jsClass+="\n\tthis.buttons['"+btn.getName()+"']={};" +
                     "\n\tthis.buttons['"+btn.getName()+"'].name='"+btn.getName()+"';";
            if (btn.getBkgrgb()!=null){
                jsClass+="\n\tthis.buttons['"+btn.getName()+"'].bckRGB=["+btn.getBkgrgb()[0]+","+btn.getBkgrgb()[1]+","+btn.getBkgrgb()[2]+"];";
            }
            if (btn.getTxtrgb()!=null){
                jsClass+="\n\tthis.buttons['"+btn.getName()+"'].txtRGB=["+btn.getTxtrgb()[0]+","+btn.getTxtrgb()[1]+","+btn.getTxtrgb()[2]+"];";
            }
            if (btn.getLabel()!=null){
                jsClass+="\n\tthis.buttons['"+btn.getName()+"'].label='"+btn.getLabel()+"';";
            }
            if (btn.getFaIcon()!=null){
                jsClass+="\n\tthis.buttons['"+btn.getName()+"'].faIcon='"+btn.getFaIcon()+"';";
            }
            if (btn.getForms()!=null){
                jsClass+="\n\tthis.buttons['"+btn.getName()+"'].forms=[]";
                for(int f=0;f<btn.getForms().length;f++){
                    jsClass+="\n\tthis.buttons['"+btn.getName()+"'].forms[this.buttons['"+btn.getName()+"'].forms.length]='"+btn.getForms()[f]+"';";
                }
            }
            jsClass+="\n\n\tthis.buttonsFields['"+btn.getName()+"']=new Array();";
            int btnFieldIdx=0;
            for (String f:btn.getFields()){
                jsClass+="\n\tthis.buttonsFields['"+btn.getName()+"']["+btnFieldIdx+"]='"+f+"';";
                btnFieldIdx++;
            }
        }
        String buttonEvents="\n\n";
        buttonEvents+="\n\t/* Eventi bottoni*/\n";
        //buttonEvents+="\n\tvar "+ctrlsName+"buttonClickActions={};";
        buttonEvents+="\n\tthis.buttonClickActions=function(btnName){";
        buttonEvents+="\n\tconsole.log(btnName);";
        Iterator<String> buttonIt = btnCtrls.keySet().iterator();
        while (buttonIt.hasNext()){
            String button=buttonIt.next();
            buttonEvents+="\n\t\tif(btnName=='"+button+"'){";
            for(String ctrl:btnCtrls.get(button)){
                buttonEvents+="\n\t\t\tif (!"+ctrl+") return false;";
            }
            buttonEvents+="\n\t\t}";
        }
        buttonEvents+="\n\tpostFields(this, btnName);";
        buttonEvents+="\n\t};";

        Iterator<String> fieldIt = fieldControls.keySet().iterator();
        String registerEventsOnField="\n\n\tthis.registerEventsOnField={}";

        while (fieldIt.hasNext()){
            String field=fieldIt.next();
            registerEventsOnField+="\n\n\tthis.registerEventsOnField['"+field+"']=function(){";
            triggerEvents+="\n\t\tif (fieldName=='"+ field + "'){";
            for(String ctrl:fieldControls.get(field)){
                triggerEvents+="\n\t\t\t"+ctrl+";";
                registerEventsOnField+="\n\t\t\t"+ctrl+";";
            }
            registerEventsOnField+="\n\t}";
            triggerEvents+="\n\t\t}";
        }

        triggerEvents="\n\n\tthis.triggerEventsOnField=function(fieldName){"+triggerEvents+"\n\t};";
        onLoadEvent="\n\n\tthis.onLoad=function(){"+onLoadEvent+"\n\t}";
        jsClass+=buttonEvents;
        jsClass+=onLoadEvent;
        jsClass+=triggerEvents;
        jsClass+=registerEventsOnField;
        jsClass+="\n};";
        return jsClass;
    }

}
