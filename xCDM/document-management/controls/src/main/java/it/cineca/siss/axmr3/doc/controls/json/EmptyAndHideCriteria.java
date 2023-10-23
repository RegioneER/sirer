package it.cineca.siss.axmr3.doc.controls.json;

/**
 * Created by Carlo on 12/09/2016.
 */
public class EmptyAndHideCriteria extends StdCriteria implements iCriteria {

    private boolean hide;

    public boolean isHide() {
        return hide;
    }

    public void setHide(boolean hide) {
        this.hide = hide;
    }


    public String toJs(String criteriaType, String fieldId, String lang){
        String js="\n\t\t\tif "+getConditions().toJs()+" {";
        js+="\n\t\t\t\tclearField(that,'"+fieldId+"');";
        if (hide){
            js+="\n\t\t\t\thideField(that,'"+fieldId+"');";
        }
        js+="}else{";
        if (hide){
            js+="\n\t\t\t\tshowField(that,'"+fieldId+"');";
        }
        js+="\n\t\t\t}";
        return js;
    }

}
