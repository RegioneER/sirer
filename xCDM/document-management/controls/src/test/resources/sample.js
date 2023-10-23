var ClinicalCaseControls = function(formId) {
    this.formId=formId;
    this.emptyControls={};
    this.disableControls={};
    this.mandatoryControls={};
    this.confirmControls={};
    this.warningControls={};
    this.validityControls={};
    this.buttonsFields={};
    this.mandatoryControls['rule-1']={};
    /*Inizio controlli per campo caseRegistration_urgentCase*/

    this.mandatoryControls['rule-1']['caseRegistration_urgentCase']=function(){
        /*Controllo mandatory*/
        if (getValueCode(this,'caseRegistration_urgentCase')=='' || getValueCode(this,'caseRegistration_urgentCase')==undefined){
            showMessage(this,'Attenzione, il campo '+getLabelOfField(this,'caseRegistration_urgentCase')+' deve essere compilato!');
            focusOn(this,'caseRegistration_urgentCase');
            return false;
        }
        return true;
    };
    /*Fine controlli per campo caseRegistration_urgentCase*/

    this.buttons={};
    this.buttons['salva']={};
    this.buttons['salva'].name='salva';

    this.buttonsFields['salva']=new Array();
    this.buttonsFields['salva'][0]='caseRegistration_urgentCase';
    this.buttonsFields['salva'][1]='caseRegistration_diagnosisAge';
    this.buttonsFields['salva'][2]='caseRegistration_sex';
    this.buttonsFields['salva'][3]='caseRegistration_question';


    /* Eventi bottoni*/

    this.buttonClickActions=function(btnName){
        if(btnName=='salva'){
            if (!this.mandatoryControls['rule-1']['caseRegistration_urgentCase']()) return false;
            postFields(this, 'salva');
        }
    };

    this.onLoad=function(){
    }

    this.triggersByField=function(fieldName){
    };
}