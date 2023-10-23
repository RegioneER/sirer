//---------------------------------------------------------------
//          function VITAL_SIGNS_Checks()
//          function INCLUSION_CRITERIA_Checks()
//          function DEMOGRAPHICS_Checks()
//          function INFORMED_CONSENT_Checks()
//          function RANDOMIZATION_Checks()
//          function DISPENSE_DRUG_Checks()
//          function HOSPITALIZATION_Checks()
//          function LABORATORY_Checks()
//          function CREATININE_Checks()
//          function TERMINATION_Checks()
//          function ADVERSE_EVENT_Checks()
//-----------------------------------------------------------------
//    STANDARD LIBRARY FUNCTIONS
//    function Radio_Mandatory(x_field,nopt,x_message)
//           Check if a radio is mandatory
//           x-radio : variable name
//           nopt : number of possible options for radio input
//           x_message : output message in case of error
//
//    function RadioOther_Mandatory(x_radio,nopt,x_field,x_message)
//           Check if a text field is present when a radio is selected
//           x-radio : radio variable name
//           nopt : option number (from 0) that requires text field
//           x_message : output message in case of error
//
//    function RadioRadio_Mandatory(x_radio,nopt,x_radio2,nopt2,x_message)
//           Check if a text field is present when a radio is selected
//           x-radio : radio variable name
//           nopt : option number (from 0) that requires text field
//           x-radio2 : radio variable name to be checked
//           nopt2 : number of possible options for radio 2
//           x_message : output message in case of error
//
//    function DateValidation(x_date)
//           Check if field contains a valid date
//           x_date : field containing date
//
//    function DateMandatory(x_date,x_message)
//           Check if a date field is mandatory
//           x_date : field containing a date
//           x_message : output message in case of error
//
//    function DateOther_Mandatory(x_date,x_field,x_message)
//           Check if a text field is present when a date field is set
//           x_date : field containing a date
//           x_field : field to be filled
//           x_message : output message in case of error
//
//    function Text_Mandatory(x_field,x_message)
//           Check if a text field is mandatory
//           x_field : text variable name
//           x_message : output message in case of error
//
//    function Valid_Range(x_field,min,max,x_message)
//           Check if a field is included between min and max value
//           x_field : text variable name
//           min : lower acceptable value
//           max : upper acceptable value
//           x_message : output message in case of error
//
//    function Possible_Range(x_field,min,max,x_message)
//           Check if a text field is included in plausibility min and max value
//           x_field : text variable name
//           min : lower acceptable value
//           max : upper acceptable value
//           x_message : output message in case of error
//
//    function SetPatientBar(x_code,x_init)
//           Substitute labels in the patient bar
//           x_code : text displayed in first cell
//           x_init : text displayed in the second cell
//
//-----------------------------------------------------------------

function VITAL_SIGNS_Checks()
{
	f=document.forms[0];
	el=f.elements;

	rc=Text_Mandatory('SYST','Sistolic Blood pressure is mandatory');
	if (rc==-1) return false;
	rc=Text_Mandatory('DIAST','Diastolic Blood pressure is mandatory');
	if (rc==-1) return false;
	rc=Text_Mandatory('HRATE','Heart Rate is mandatory');
	if (rc==-1) return false;
	rc=Text_Mandatory('BODYTEMP','Body temperature is mandatory');
	if (rc==-1) return false;
	rc=Text_Mandatory('WGHT','Body weight is mandatory');
	if (rc==-1) return false;

	if ((1*el['SYST'].value)<(1*el['DIAST'].value))
	{
		alert('The systolic blood pressure must be higher than the diastolic blood pressure.');
		return(-1);
	}



/*
	rc=Valid_Range('SYST',70,280,'Sistolic Blood pressure is out of allowed range');
	if (rc==-1) return false;
	rc=Valid_Range('DIAST',30,180,'Diastolic Blood pressure is out of allowed range');
	if (rc==-1) return false;
	rc=Valid_Range('HRATE',15,200,'Heart Rate is out of allowed range');
	if (rc==-1) return false;
	rc=Valid_Range('BODYTEMP',34,44,'Body Temperature is out of allowed range');
	if (rc==-1) return false;
	rc=Valid_Range('WGHT',20,200,'Body weight is out of allowed range');
	if (rc==-1) return false;
*/

	rc=Possible_Range('SYST',50,250,'The systolic blood pressure is out of the reference region (50-250 mmHg). Please check the entry or give a comment.');
	if (rc==-1) return false;
	rc=Possible_Range('DIAST',30,130,'The diastolic blood pressure is out of the reference region (30-130 mmHg). Please check the entry or give a comment.');
	if (rc==-1) return false;
	rc=Possible_Range('HRATE',30,160,'The pulse rate is out of the reference region (30-160 bqm). Please check the entry or give a comment.');
	if (rc==-1) return false;
	rc=Possible_Range('BODYTEMP',30,42,'The Body temperature is out of the reference region (30-42 °C). Please check the entry or give a comment.');
	if (rc==-1) return false;
	rc=Possible_Range('WGHT',50,95,'The Body weight is out of the reference region (<50 kg or >95 kg). The patient has to be excluded. Please fill out the Study Termination page.');
	if (rc==-1) return false;

	if (el['CMV_ASSESM'][0].checked==false && 
		el['CMV_ASSESM'][1].checked==false && 
		el['CMV_ASSESM'][2].checked==false && 
		el['CMV_ASSESM'][3].checked==false)
	{
		alert("CMV Assessment is mandatory");
		return(false);
	}

	if (el['CMV_ASSESM'][3].checked==true)
	{
		alert("In case of suspected or diagnosed CMV disease, the patient has to be excluded! Please fill out the Study Termination page.");
		return(false);
	}

	return(true);
}

function INCLUSION_CRITERIA_Checks()
{
	f=document.forms[0];
	el=f.elements;
	xcrit1=0;
	xcrit2=0;
	if (el['INC01'][0].checked==false && el['INC01'][1].checked==false) xcrit1=xcrit1+1;
	if (el['INC02'][0].checked==false && el['INC02'][1].checked==false) xcrit1=xcrit1+1;
	if (el['INC03'][0].checked==false && el['INC03'][1].checked==false) xcrit1=xcrit1+1;
	if (el['INC04'][0].checked==false && el['INC04'][1].checked==false) xcrit1=xcrit1+1;
	if (el['INC05'][0].checked==false && el['INC05'][1].checked==false) xcrit1=xcrit1+1;
	if (el['INC06'][0].checked==false && el['INC06'][1].checked==false) xcrit1=xcrit1+1;
	if (el['INC07'][0].checked==false && el['INC07'][1].checked==false) xcrit1=xcrit1+1;
	if (el['INC08'][0].checked==false && el['INC08'][1].checked==false) xcrit1=xcrit1+1;
	if (el['INC09'][0].checked==false && el['INC09'][1].checked==false) xcrit1=xcrit1+1;
	if (el['INC10'][0].checked==false && el['INC10'][1].checked==false) xcrit1=xcrit1+1;
	if (xcrit1>0)
	{
		alert("One or more inclusion criteria are not defined");
		return(false);
	}

	if (el['EXC01'][0].checked==false && el['EXC01'][1].checked==false) xcrit2=xcrit2+1;
	if (el['EXC02'][0].checked==false && el['EXC02'][1].checked==false) xcrit2=xcrit2+1;
	if (el['EXC03'][0].checked==false && el['EXC03'][1].checked==false) xcrit2=xcrit2+1;
	if (el['EXC04'][0].checked==false && el['EXC04'][1].checked==false) xcrit2=xcrit2+1;
	if (el['EXC05'][0].checked==false && el['EXC05'][1].checked==false) xcrit2=xcrit2+1;
	if (el['EXC06'][0].checked==false && el['EXC06'][1].checked==false) xcrit2=xcrit2+1;
	if (el['EXC07'][0].checked==false && el['EXC07'][1].checked==false) xcrit2=xcrit2+1;
	if (el['EXC08'][0].checked==false && el['EXC08'][1].checked==false) xcrit2=xcrit2+1;
	if (el['EXC09'][0].checked==false && el['EXC09'][1].checked==false) xcrit2=xcrit2+1;
	if (el['EXC10'][0].checked==false && el['EXC10'][1].checked==false) xcrit2=xcrit2+1;
	if (el['EXC11'][0].checked==false && el['EXC11'][1].checked==false) xcrit2=xcrit2+1;
	if (el['EXC12'][0].checked==false && el['EXC12'][1].checked==false) xcrit2=xcrit2+1;
	if (el['EXC13'][0].checked==false && el['EXC13'][1].checked==false) xcrit2=xcrit2+1;
	if (el['EXC14'][0].checked==false && el['EXC14'][1].checked==false) xcrit2=xcrit2+1;
	if (el['EXC15'][0].checked==false && el['EXC15'][1].checked==false) xcrit2=xcrit2+1;
	if (el['EXC16'][0].checked==false && el['EXC16'][1].checked==false) xcrit2=xcrit2+1;
	if (el['EXC17'][0].checked==false && el['EXC17'][1].checked==false) xcrit2=xcrit2+1;
	if (xcrit2>0)
	{
		alert("One or more exclusion criteria are not defined");
		return(false);
	}

	if (el['INC10'][0].checked==true)
	{
		alert("The patient has to be excluded. Please fill out the Study Termination page. Please note: Occurrence of pregnancy has to be reported on the Pregnancy Report Form (see Investigator's File). The completed form has to be sent by telefax within one working day to Pierrel Research Europe GmbH: Pierrel Research Europe GmbH 45307 Essen, Germany Phone: ++49 / 201 / 8990-123 Fax: ++49 / 201 / 8990-251");
		
		return(true);
	}

	xcrit1=0;
	if (el['INC01'][0].checked==true) xcrit1=xcrit1+1;
	if (el['INC02'][0].checked==true) xcrit1=xcrit1+1;
	if (el['INC03'][0].checked==true) xcrit1=xcrit1+1;
	if (el['INC04'][0].checked==true) xcrit1=xcrit1+1;
	if (el['INC05'][0].checked==true) xcrit1=xcrit1+1;
	if (el['INC06'][0].checked==true) xcrit1=xcrit1+1;
	if (el['INC07'][0].checked==true) xcrit1=xcrit1+1;
	if (el['INC08'][0].checked==true) xcrit1=xcrit1+1;
	if (el['INC09'][0].checked==true) xcrit1=xcrit1+1;
	if (el['INC10'][0].checked==true) xcrit1=xcrit1+1;
	if (xcrit1!=10)
	{
		alert("The patient has to be excluded. Please fill out the Study Termination Page");
		return(true);
	}

	xcrit2=0;
	if (el['EXC01'][1].checked==true) xcrit2=xcrit2+1;
	if (el['EXC02'][1].checked==true) xcrit2=xcrit2+1;
	if (el['EXC03'][1].checked==true) xcrit2=xcrit2+1;
	if (el['EXC04'][1].checked==true) xcrit2=xcrit2+1;
	if (el['EXC05'][1].checked==true) xcrit2=xcrit2+1;
	if (el['EXC06'][1].checked==true) xcrit2=xcrit2+1;
	if (el['EXC07'][1].checked==true) xcrit2=xcrit2+1;
	if (el['EXC08'][1].checked==true) xcrit2=xcrit2+1;
	if (el['EXC09'][1].checked==true) xcrit2=xcrit2+1;
	if (el['EXC10'][1].checked==true) xcrit2=xcrit2+1;
	if (el['EXC11'][1].checked==true) xcrit2=xcrit2+1;
	if (el['EXC12'][1].checked==true) xcrit2=xcrit2+1;
	if (el['EXC13'][1].checked==true) xcrit2=xcrit2+1;
	if (el['EXC14'][1].checked==true) xcrit2=xcrit2+1;
	if (el['EXC15'][1].checked==true) xcrit2=xcrit2+1;
	if (el['EXC16'][1].checked==true) xcrit2=xcrit2+1;
	if (el['EXC17'][1].checked==true) xcrit2=xcrit2+1;
	if (xcrit2!=17)
	{
		alert("The patient has to be excluded. Please fill out the Study Termination Page");
		return(false);
	}


	return(true);
}

function DEMOGRAPHICS_Checks()
{
	f=document.forms[0];
	el=f.elements;
	
	dv = el['HD_VISIT_DATE'].value.substring(0,2) + '/' + el['HD_VISIT_DATE'].value.substring(2,4) + '/' + el['HD_VISIT_DATE'].value.substring(4,8);
	db = el['BTH_DATE'].value.substring(0,2) + '/' + el['BTH_DATE'].value.substring(2,4) + '/' + (1*el['BTH_DATE'].value.substring(4,8) + 18);
	
	rc=compareDates(dv,'dd/MM/yyyy',db,'dd/MM/yyyy');
	if (rc!=1)
	{
		alert("The patient has to be excluded. Please fill out the Study Termination Page");
		return(true);
	}
	
	rc=DateValidation('BTH_DATE');
	if (rc==-1) return false;
	rc=DateValidation('DIAG_DATE');
	if (rc==-1) return false;
	rc=DateMandatory('BTH_DATE','Birth date is mandatory');
	if (rc==-1) return false;
	rc=DateMandatory('DIAG_DATE','Date of first diagnosis is mandatory');
	if (rc==-1) return false;

	rc=Radio_Mandatory('SEX',2,'Gender is mandatory');
	if (rc==-1) return false;
	rc=Radio_Mandatory('RACE',4,'Race is mandatory');
	if (rc==-1) return false;
	rc=RadioOther_Mandatory('RACE',3,'RACE_OTH','Other race indicated. Please specify');
	if (rc==-1) return false;

	rc=Radio_Mandatory('SOURCE',3,'Transplant characteristics is mandatory');
	if (rc==-1) return false;
	rc=Radio_Mandatory('TYPECOND',2,'Type of conditioning is mandatory');
	if (rc==-1) return false;
	rc=Radio_Mandatory('TYPEDEPL',2,'Type of T-cell depletion is mandatory');
	if (rc==-1) return false;
	rc=Radio_Mandatory('HLA',2,'HLA identity is mandatory');
	if (rc==-1) return false;

	return(true);
}

function INFORMED_CONSENT_Checks()
{
	f=document.forms[0];
	el=f.elements;
	rc=DateValidation('VISIT_DATE');
	if (rc==-1) return false;
	rc=DateMandatory('VISIT_DATE','Visit date is mandatory');
	if (rc==-1) return false;
	rc=DateValidation('INFCONSENT_DATE');
	if (rc==-1) return false;
	rc=DateMandatory('INFCONSENT_DATE','Informed consente date is mandatory');
	if (rc==-1) return false;
	rc=DateValidation('OPERATION_DATE');
	if (rc==-1) return false;
	rc=DateMandatory('OPERATION_DATE','Date is mandatory');
	if (rc==-1) return false;
	rc=Text_Mandatory('INVESTIGATOR','Investigator name is mandatory');
	if (rc==-1) return false;
	rc=Text_Mandatory('SIGNATURE','Signature is mandatory');
	if (rc==-1) return false;
	rc=DateOther_Mandatory('VISIT_DATE','SIGNATURE','Investigator signature is mandatory');
	if (rc==-1) return false;

	return(true);
}

function RANDOMIZATION_Checks()
{
	f=document.forms[0];
	el=f.elements;
	rc=Radio_Mandatory('TREATMENT',2,'Please specify a treatment group');
	if (rc==-1) return false;

	return(true);
}


function DISPENSE_DRUG_Checks()
{
	f=document.forms[0];
	el=f.elements;

	rc=Radio_Mandatory('DOSE_A',5,'Dose of creatinine clearance is mandatory');
	if (rc==-1) return false;
	rc=Radio_Mandatory('ADDOSE_A',2,'Treatment A:Additional dose adjustment because of other reasons is mandatory');
	if (rc==-1) return false;
	rc=Radio_Mandatory('ADDOSE_B',2,'Treatment B:Additional dose adjustment because of other reasons is mandatory');
	if (rc==-1) return false;
	rc=RadioOther_Mandatory('ADDOSE_A',0,'ADDDOSE_QTY','Treatment A:Additional dose indicated. Please specify quantity');
	if (rc==-1) return false;
	rc=RadioOther_Mandatory('ADDOSE_A',0,'ADDDOSE_REASON','Treatment A:Additional dose indicated. Please specify reason');
	if (rc==-1) return false;
	rc=RadioOther_Mandatory('ADDOSE_B',0,'ADDDOSE_B_QTY','Treatment B:Additional dose indicated. Please specify quantity');
	if (rc==-1) return false;
	rc=RadioOther_Mandatory('ADDOSE_B',0,'ADDDOSE_B_REASON','Treatment B:Additional dose indicated. Please specify reason');
	if (rc==-1) return false;

	return(true);
}

function HOSPITALIZATION_Checks()
{
	f=document.forms[0];
	el=f.elements;

	rc=Radio_Mandatory('HOSP',2,'Was the patient hospitalized since SCT is mandatory');
	if (rc==-1) return false;
	rc=RadioOther_Mandatory('HOSP',0,'HOSP_DAYS','Please specify for how many days');
	if (rc==-1) return false;

	return(true);
}

function LABORATORY_Checks()
{
	f=document.forms[0];
	el=f.elements;
	
	if (el['HD_CMV_DATE'].value!='')
	{
		rc=Text_Mandatory('PARAM01','Hemoglobin: the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM02','Hematocrit : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM03','Platelets : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM04','WBC : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM05','Neutrophils : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM06','Lymphocytes : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM07','B-cell count : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM08','Monocytes : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM09','Eosinophils : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM10','Basophils : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM11','ANC : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM12','Total Bilirubin : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM13','AST : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM14','ALT : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM15','gGT : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM16','Alkaline Phosphatase : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM17','Total Protein : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM18','Albumin : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM19','Uric Acid : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM20','Glucose : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM21','Sodium : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM22','Potassium : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM23','Calcium : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM24','Phosphate : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM25','Serum Creatinine : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM26','Blood Urea Nitrogen (BUN) : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;
		rc=Text_Mandatory('PARAM27','C-Reactive Protein (CRP) : the value for the parameter is missing. Please check the entry or give a comment.');
		if (rc==-1) return false;

		for (j=1; j<=27; j=j+1)
		{
			if (j<10) numrec = '0' + j;
			else numrec = j;

			if (el['NORMAL' + numrec].checked==false && el['ABNORMAL_REL' + numrec].checked==false && el['ABNORMAL_UNREL' + numrec].checked==false)
			{
				alert("The rating for the clinically relevant is missing. Please give a rating.");
				return(false);
			}
		}

		for (j=1; j<=27; j=j+1)
		{
			if (j<10) numrec = '0' + j;
			else numrec = j;

			k=0;
			if (el['ABNORMAL_REL' + numrec].checked==true)
			{
				k=k+1;
			}
			if (k>0)
			{
				alert("The rating for the clinically relevant is 'Abnormal and clinically relevant'. Please document in section Medical History and Concomitant Diseases.");
			}
		}
	}

	return(true);
}

function CREATININE_Checks()
{
	f=document.forms[0];
	el=f.elements;

	rc=Radio_Mandatory('DOSE_A',5,'Dose of creatinine clearance is mandatory');
	if (rc==-1) return false;
	rc=Radio_Mandatory('ADDOSE_A',2,'Treatment A:Additional dose adjustment because of other reasons is mandatory');
	if (rc==-1) return false;
	rc=Radio_Mandatory('ADDOSE_B',2,'Treatment B:Additional dose adjustment because of other reasons is mandatory');
	if (rc==-1) return false;
	rc=RadioOther_Mandatory('ADDOSE_A',0,'ADDDOSE_QTY','Treatment A:Additional dose indicated. Please specify quantity');
	if (rc==-1) return false;
	rc=RadioOther_Mandatory('ADDOSE_A',0,'ADDDOSE_REASON','Treatment A:Additional dose indicated. Please specify reason');
	if (rc==-1) return false;
	rc=RadioOther_Mandatory('ADDOSE_B',0,'ADDDOSE_B_QTY','Treatment B:Additional dose indicated. Please specify quantity');
	if (rc==-1) return false;
	rc=RadioOther_Mandatory('ADDOSE_B',0,'ADDDOSE_B_REASON','Treatment B:Additional dose indicated. Please specify reason');
	if (rc==-1) return false;

	return(true);
}

function CREATININE_Load()
{
	f=document.forms[0];
	el=f.elements;

	/*-------  Trattamento Gruppo A---*/
	if (el['HD_TREATMENT'].value=='1')
	{
		el['DOSE_A'].disabled=false;
		el['ADDOSE_A'].disabled=false;
		el['ADDDOSE_QTY'].disabled=false;
		el['ADDDOSE_REASON'].disabled=false;
		el['DOSE_B'][0].disabled=true;
		el['DOSE_B'][1].disabled=true;
		el['DOSE_B'][2].disabled=true;
		el['DOSE_B'][3].disabled=true;
		el['DOSE_B'][4].disabled=true;
		/*el['DOSE_B'].style.backgroundColor = "gray";*/
		el['ADDOSE_B'][0].disabled=true;
		el['ADDOSE_B'][1].disabled=true;
		/*el['ADDDOSE_B'].style.backgroundColor = "gray";*/
		el['ADDDOSE_B_QTY'].disabled=true;
		el['ADDDOSE_B_QTY'].style.backgroundColor = "gray";
		el['ADDDOSE_B_REASON'].disabled=true;
		el['ADDDOSE_B_REASON'].style.backgroundColor = "gray";
	}
	/*-------  Trattamento Gruppo B---*/
	if (el['HD_TREATMENT'].value=='2')
	{
		el['DOSE_B'].disabled=false;
		el['ADDOSE_B'].disabled=false;
		el['ADDDOSE_B_QTY'].disabled=false;
		el['ADDDOSE_B_REASON'].disabled=false;
		el['DOSE_A'][0].disabled=true;
		el['DOSE_A'][1].disabled=true;
		el['DOSE_A'][2].disabled=true;
		el['DOSE_A'][3].disabled=true;
		el['DOSE_A'][4].disabled=true;
		/*el['DOSE_A'].style.backgroundColor = "gray";*/
		el['ADDOSE_A'][0].disabled=true;
		el['ADDOSE_A'][1].disabled=true;
		/*el['ADDOSE_A'].style.backgroundColor = "gray";*/
		el['ADDDOSE_QTY'].disabled=true;
		el['ADDDOSE_QTY'].style.backgroundColor = "gray";
		el['ADDDOSE_REASON'].disabled=true;
		el['ADDDOSE_REASON'].style.backgroundColor = "gray";
	}
}

function CREATININE_Load_v1()
{
	f=document.forms[0];
	el=f.elements;

	/*-------  Trattamento Gruppo A---*/
	if (el['HD_TREATMENT'].value=='1')
	{
		el['DOSE_A_1'].disabled=false;
		el['ADDOSE_A'].disabled=false;
		el['ADDDOSE_QTY'].disabled=false;
		el['ADDDOSE_REASON'].disabled=false;
		el['DOSE_B_1'][0].disabled=true;
		el['DOSE_B_1'][1].disabled=true;
		el['DOSE_B_1'][2].disabled=true;
		el['DOSE_B_1'][3].disabled=true;
		/*el['DOSE_B'].style.backgroundColor = "gray";*/
		el['ADDOSE_B'][0].disabled=true;
		el['ADDOSE_B'][1].disabled=true;
		/*el['ADDDOSE_B'].style.backgroundColor = "gray";*/
		el['ADDDOSE_B_QTY'].disabled=true;
		el['ADDDOSE_B_QTY'].style.backgroundColor = "gray";
		el['ADDDOSE_B_REASON'].disabled=true;
		el['ADDDOSE_B_REASON'].style.backgroundColor = "gray";
	}
	/*-------  Trattamento Gruppo B---*/
	if (el['HD_TREATMENT'].value=='2')
	{
		el['DOSE_B_1'].disabled=false;
		el['ADDOSE_B'].disabled=false;
		el['ADDDOSE_B_QTY'].disabled=false;
		el['ADDDOSE_B_REASON'].disabled=false;
		el['DOSE_A_1'][0].disabled=true;
		el['DOSE_A_1'][1].disabled=true;
		el['DOSE_A_1'][2].disabled=true;
		el['DOSE_A_1'][3].disabled=true;
		/*el['DOSE_A'].style.backgroundColor = "gray";*/
		el['ADDOSE_A'][0].disabled=true;
		el['ADDOSE_A'][1].disabled=true;
		/*el['ADDOSE_A'].style.backgroundColor = "gray";*/
		el['ADDDOSE_QTY'].disabled=true;
		el['ADDDOSE_QTY'].style.backgroundColor = "gray";
		el['ADDDOSE_REASON'].disabled=true;
		el['ADDDOSE_REASON'].style.backgroundColor = "gray";
	}
}

function TERMINATION_Checks()
{
	f=document.forms[0];
	el=f.elements;

	rc=Radio_Mandatory('DISC_YN',2,'Was the patient prematurely discontinued is mandatory');
	if (rc==-1) return false;
	rc=RadioRadio_Mandatory('DISC_YN',0,'DISC_REASON',13,'Patient discontinued. Please specify a reason');
	if (rc==-1) return false;

	return(true);
}

function ADVERSE_EVENT_Checks()
{
	f=document.forms[0];
	el=f.elements;

	f=document.forms[0];
	el=f.elements;
	rc=Text_Mandatory('AE_DESC','Description of Adverse Event is mandatory');
	if (rc==-1) return false;
	rc=Radio_Mandatory('AE_INTENSITY',4,'Intensity of Adverse Event is mandatory');
	if (rc==-1) return false;
	rc=Radio_Mandatory('AE_OUTCOME',6,'Outcome of Adverse Event is mandatory');
	if (rc==-1) return false;
	rc=Radio_Mandatory('AE_CAUSALITY',2,'Causality of Adverse Event is mandatory');
	if (rc==-1) return false;
	rc=Radio_Mandatory('AE_SERIOUS',2,'Seriousness of Adverse Event is mandatory');
	if (rc==-1) return false;
	//rc=RadioRadio_Mandatory('AE_SERIOUS',0,'AE_REPORT',6,'Report to Sponsor is mandatory');
	//if (rc==-1) return false;

	return(true);
}

function Radio_Mandatory(x_field,nopt,x_message)
{
	f=document.forms[0];
	el=f.elements;
	nn=0;
	for (i=1; i<=nopt; i=i+1)
	{
		if (el[x_field][i-1].checked==false) nn=nn+1;
	}
	if (nn==nopt)
	{
		alert(x_message);
		return(-1);
	}
	else return(0);
}

function RadioOther_Mandatory(x_radio,nopt,x_field,x_message)
{
	f=document.forms[0];
	el=f.elements;

	if (el[x_radio][nopt].checked==true && el[x_field].value=='')
	{
		alert(x_message);
		return(-1);
	}
	else return(0);
}

function RadioRadio_Mandatory(x_radio,nopt,x_radio2,nopt2,x_message)
{
	f=document.forms[0];
	el=f.elements;

	if (el[x_radio][nopt].checked==true)
	{
		nn=0;
		for (i=1; i<=nopt2; i=i+1)
		{
			if (el[x_radio2][i-1].checked==false) nn=nn+1;
		}
		
		if (nn==nopt2)
		{
			alert(x_message);
			return(-1);
		}
		else return(0);
	}
	else return(0);
}

function DateValidation(x_date)
{
	f=document.forms[0];
	el=f.elements;

	x_dated = x_date + 'D';
	x_datem = x_date + 'M';
	x_datey = x_date + 'Y';
		
	err=0;
	if (el[x_dated].value!='' && el[x_datem].value!='' && el[x_datey].value!='')
	{
		if (el[x_datem].value==1 && (el[x_dated].value<1 && el[x_dated].value>31)) err=1;
		if (el[x_datem].value==2 && (el[x_dated].value<1 && el[x_dated].value>28)) err=1;
		if (el[x_datem].value==3 && (el[x_dated].value<1 && el[x_dated].value>31)) err=1;
		if (el[x_datem].value==4 && (el[x_dated].value<1 && el[x_dated].value>30)) err=1;
		if (el[x_datem].value==5 && (el[x_dated].value<1 && el[x_dated].value>31)) err=1;
		if (el[x_datem].value==6 && (el[x_dated].value<1 && el[x_dated].value>30)) err=1;
		if (el[x_datem].value==7 && (el[x_dated].value<1 && el[x_dated].value>31)) err=1;
		if (el[x_datem].value==8 && (el[x_dated].value<1 && el[x_dated].value>31)) err=1;
		if (el[x_datem].value==9 && (el[x_dated].value<1 && el[x_dated].value>30)) err=1;
		if (el[x_datem].value==10 && (el[x_dated].value<1 && el[x_dated].value>31)) err=1;
		if (el[x_datem].value==11 && (el[x_dated].value<1 && el[x_dated].value>30)) err=1;
		if (el[x_datem].value==12 && (el[x_dated].value<1 && el[x_dated].value>31)) err=1;
	
		if (err==1)
		{
			alert('Date is invalid');
			return(-1);
		}
		else return(0);
	}
	else return(0);
}

function DateMandatory(x_date,x_message)
{
	f=document.forms[0];
	el=f.elements;

	x_dated = x_date + 'D';
	x_datem = x_date + 'M';
	x_datey = x_date + 'Y';
		
	if (el[x_dated].value=='' || el[x_datem].value=='' || el[x_datey].value=='')
	{
		alert(x_message);
		return(-1);
	}
	else return(0);
}

function DateOther_Mandatory(x_date,x_field,x_message)
{
	f=document.forms[0];
	el=f.elements;

	x_dated = x_date + 'D';
	x_datem = x_date + 'M';
	x_datey = x_date + 'Y';
	
	if (el[x_dated].value!='' && el[x_datem].value!='' && el[x_datey].value!='' && el[x_field].value=='')
	{
		alert(x_message);
		return(-1);
	}
	else return(0);
}

function Text_Mandatory(x_field,x_message)
{
	f=document.forms[0];
	el=f.elements;

	if (el[x_field].value=='')
	{
		alert(x_message);
		return(-1);
	}
	else return(0);
}

function Valid_Range(x_field,x_min,x_max,x_message)
{
	f=document.forms[0];
	el=f.elements;

	if (el[x_field].value<x_min || el[x_field].value>x_max)
	{
		alert(x_message);
		return(-1);
	}
	else return(0);
}

function Possible_Range(x_field,x_min,x_max,x_message)
{
	f=document.forms[0];
	el=f.elements;

	if (el[x_field].value<x_min || el[x_field].value>x_max)
	{

		if (confirm(x_message)==true) return(0);
		else return(-1);
	}
	else return(0);
}

function SetPatientBar(x_code,x_init)
{
/*
	tbl = document.getElementById('PatCodTxt');
	tbl.innerHTML = x_code
	tbl = document.getElementById('PatIniTxt');
	tbl.innerHTML = x_init;
*/
	return true
}


function REGISTRATION_Load(){
f=document.forms[0];
el=f.elements;	


el['SITEID'].value=el['HD_CODE'].value;	
el['SITEID'].disabled=true;	
el['SITEIDDISPLAY'].value=el['CENTER'].value.substring(1, 3);
el['SITEIDDISPLAY'].disabled=true;

if (el['HD_SUBJID'].value=='' )
{
	el['SUBJID'].value='0001';	
	el['SUBJID'].disabled=true;	
}
else
{
	var v_sub=(el['HD_SUBJID'].value*1)+(1*1);
	if (v_sub <10)
	{
		v_sub='000'+v_sub;
	}
	else 
	if (v_sub <100)
	{	
		v_sub='00'+v_sub;
	}
	else 
	if (v_sub <1000)
	{	
		v_sub='0'+v_sub;
	}

	el['SUBJID'].value=v_sub;	
	el['SUBJID'].disabled=true;	
}

return true;

}


function REGISTRATION(){

var selectbox2=document.getElementsByName("HD_SUBJID");

var selectbox=selectbox2[0];

var selectbox3=document.getElementsByName("SUBJID");
var myValue=selectbox3[0].value;

	var i=0;

	while(i<selectbox.options.length)

	{
		if(selectbox.options[i].value==myValue){
		//
		alert("SUBJID already exists");
		return false;
		}
		i=i+1;
	}	
	
return true;	
}

function concdis_delete(numrecord)
{
	f=document.forms[0];
	el=f.elements;	
		
	if (confirm('This record will be deleted. Please confim?'))
	{
		//el['DISEASE'+numrecord].value='';
		el['DISEASE'+numrecord].disabled=true;			
		//el['STARTDATE'+numrecord+'D'].value='';
		//el['STARTDATE'+numrecord+'M'].value='';
		//el['STARTDATE'+numrecord+'Y'].value='';
		el['STARTDATE'+numrecord+'D'].disabled=true;
		el['STARTDATE'+numrecord+'M'].disabled=true;
		el['STARTDATE'+numrecord+'Y'].disabled=true;
		//el['STOPDATE'+numrecord+'D'].value='';
		//el['STOPDATE'+numrecord+'M'].value='';
		//el['STOPDATE'+numrecord+'Y'].value='';
		el['STOPDATE'+numrecord+'D'].disabled=true;
		el['STOPDATE'+numrecord+'M'].disabled=true;
		el['STOPDATE'+numrecord+'Y'].disabled=true;
		el['ONGOING'+numrecord].disabled=true;	
		el['RECD'+numrecord].disabled=true;	
		el['DISEASE'+numrecord].style.backgroundColor = "gray";
		el['STARTDATE'+numrecord+'D'].style.backgroundColor = "gray";
		el['STARTDATE'+numrecord+'M'].style.backgroundColor = "gray";
		el['STARTDATE'+numrecord+'Y'].style.backgroundColor = "gray";
		el['STOPDATE'+numrecord+'D'].style.backgroundColor = "gray";
		el['STOPDATE'+numrecord+'M'].style.backgroundColor = "gray";
		el['STOPDATE'+numrecord+'Y'].style.backgroundColor = "gray";
		el['ONGOING'+numrecord].style.backgroundColor = "gray";
		el['RECD'+numrecord].style.backgroundColor = "gray";
		return true;
	}
	else 
	{
		el['RECD'+numrecord].checked=false;
		return false;
	}
	
	return true;

}

function load_concdis()
{
	f=document.forms[0];
	el=f.elements;	
	var nrrecord = 15;
	
	for (var i=1; i<=nrrecord; i++)
	{
		if (el['RECD'+i].checked==true) //record cancellato
		{
			el['DISEASE'+i].disabled=true;
			el['STARTDATE'+i+'D'].disabled=true;
			el['STARTDATE'+i+'M'].disabled=true;
			el['STARTDATE'+i+'Y'].disabled=true;
			el['STOPDATE'+i+'D'].disabled=true;
			el['STOPDATE'+i+'M'].disabled=true;
			el['STOPDATE'+i+'Y'].disabled=true;
			el['ONGOING'+i].disabled=true;	
			el['RECD'+i].disabled=true;
			el['DISEASE'+i].style.backgroundColor = "gray";
			el['STARTDATE'+i+'D'].style.backgroundColor = "gray";
			el['STARTDATE'+i+'M'].style.backgroundColor = "gray";
			el['STARTDATE'+i+'Y'].style.backgroundColor = "gray";
			el['STOPDATE'+i+'D'].style.backgroundColor = "gray";
			el['STOPDATE'+i+'M'].style.backgroundColor = "gray";
			el['STOPDATE'+i+'Y'].style.backgroundColor = "gray";
			el['ONGOING'+i].style.backgroundColor = "gray";
			el['RECD'+i].style.backgroundColor = "gray";
		}
		if (el['REC'+i].checked==true) //aggiungi record
		{	
			el['REC'+i].disabled=true;
			el['REC'+i].style.backgroundColor = "gray";
		}
	}
	
	return true;
}


function poststudy_delete(numrecord)
{
	f=document.forms[0];
	el=f.elements;	
		
	if (confirm('This record will be deleted. Please confim?'))
	{
		//el['VISIT_DATE'+numrecord+'D'].value='';
		//el['VISIT_DATE'+numrecord+'M'].value='';
		//el['VISIT_DATE'+numrecord+'Y'].value='';
		el['VISIT_DATE'+numrecord+'D'].disabled=true;
		el['VISIT_DATE'+numrecord+'M'].disabled=true;
		el['VISIT_DATE'+numrecord+'Y'].disabled=true;
		
		//el['VISIT_DESC'+numrecord].value='';
		el['VISIT_DESC'+numrecord].disabled=true;				
		
		var objs=el['DISAPPEAR'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;
			
		//el['DISAPPEAR_DESC'+numrecord].value='';
		el['DISAPPEAR_DESC'+numrecord].disabled=true;		
		
		el['RECD'+numrecord].disabled=true;
		
		el['VISIT_DATE'+numrecord+'D'].style.backgroundColor = "gray";
		el['VISIT_DATE'+numrecord+'M'].style.backgroundColor = "gray";
		el['VISIT_DATE'+numrecord+'Y'].style.backgroundColor = "gray";
		el['VISIT_DESC'+numrecord].style.backgroundColor = "gray";
		el['DISAPPEAR_DESC'+numrecord].style.backgroundColor = "gray";
		el['RECD'+numrecord].style.backgroundColor = "gray";
		return true;
	}
	else 
	{
		el['RECD'+numrecord].checked=false;
		return false;
	}
	
	return true;

}

function load_poststudy()
{
	f=document.forms[0];
	el=f.elements;	
	for (var i=1; i<=5; i++)
	{
		if (el['RECD'+i].checked==true) //record cancellato
		{
			el['VISIT_DATE'+i+'D'].disabled=true;
			el['VISIT_DATE'+i+'M'].disabled=true;
			el['VISIT_DATE'+i+'Y'].disabled=true;
			el['VISIT_DESC'+i].disabled=true;
			var objs=el['DISAPPEAR'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;
				
			el['DISAPPEAR_DESC'+i].disabled=true;	
			el['RECD'+i].disabled=true;
			el['VISIT_DATE'+i+'D'].style.backgroundColor = "gray";
			el['VISIT_DATE'+i+'M'].style.backgroundColor = "gray";
			el['VISIT_DATE'+i+'Y'].style.backgroundColor = "gray";
			el['VISIT_DESC'+i].style.backgroundColor = "gray";
			el['DISAPPEAR_DESC'+i].style.backgroundColor = "gray";
			el['RECD'+i].style.backgroundColor = "gray";
		}
		if (el['REC'+i].checked==true) //aggiungi record
		{	
			el['REC'+i].disabled=true;
			el['REC'+i].style.backgroundColor = "gray";
		}		
	}
	
	return true;
}

function unscheduled_delete(numrecord)
{
	f=document.forms[0];
	el=f.elements;	
		
	if (confirm('This record will be deleted. Please confim?'))
	{
		//el['VISIT_DATE'+numrecord+'D'].value='';
		//el['VISIT_DATE'+numrecord+'M'].value='';
		//el['VISIT_DATE'+numrecord+'Y'].value='';
		el['VISIT_DATE'+numrecord+'D'].disabled=true;
		el['VISIT_DATE'+numrecord+'M'].disabled=true;
		el['VISIT_DATE'+numrecord+'Y'].disabled=true;
		
		//el['REASON'+numrecord].value='';
		el['REASON'+numrecord].disabled=true;				
		
		el['RECD'+numrecord].disabled=true;
		
		el['VISIT_DATE'+numrecord+'D'].style.backgroundColor = "gray";
		el['VISIT_DATE'+numrecord+'M'].style.backgroundColor = "gray";
		el['VISIT_DATE'+numrecord+'Y'].style.backgroundColor = "gray";
		el['REASON'+numrecord].style.backgroundColor = "gray";
		el['RECD'+numrecord].style.backgroundColor = "gray";
		return true;
	}
	else 
	{
		el['RECD'+numrecord].checked=false;
		return false;
	}
	
	return true;

}

function load_unscheduled()
{
	f=document.forms[0];
	el=f.elements;	
	for (var i=1; i<=6; i++)
	{
		if (el['RECD'+i].checked==true) //record cancellato
		{
			el['VISIT_DATE'+i+'D'].disabled=true;
			el['VISIT_DATE'+i+'M'].disabled=true;
			el['VISIT_DATE'+i+'Y'].disabled=true;
			el['REASON'+i].disabled=true;
			el['RECD'+i].disabled=true;
			el['VISIT_DATE'+i+'D'].style.backgroundColor = "gray";
			el['VISIT_DATE'+i+'M'].style.backgroundColor = "gray";
			el['VISIT_DATE'+i+'Y'].style.backgroundColor = "gray";
			el['REASON'+i].style.backgroundColor = "gray";
			el['RECD'+i].style.backgroundColor = "gray";
		}
		if (el['REC'+i].checked==true) //aggiungi record
		{	
			el['REC'+i].disabled=true;
			el['REC'+i].style.backgroundColor = "gray";
		}		
	}
	
	return true;
}

function concmed_delete(numrecord)
{
	f=document.forms[0];
	el=f.elements;	
		
	if (confirm('This record will be deleted. Please confim?'))
	{
		//el['THERAPY'+numrecord].value='';
		el['THERAPY'+numrecord].disabled=true;		

		//el['ROUTE'+numrecord].value='';
		el['ROUTE'+numrecord].disabled=true;		

		//el['DOSE'+numrecord].value='';
		el['DOSE'+numrecord].disabled=true;		

		var objs=el['REASON'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;

		//el['REASON_AE'+numrecord].value='';
		el['REASON_AE'+numrecord].disabled=true;		

		//el['REASON_CMC'+numrecord].value='';
		el['REASON_CMC'+numrecord].disabled=true;		

		//el['REASON_OTHER'+numrecord].value='';
		el['REASON_OTHER'+numrecord].disabled=true;		

		//el['STARTDATE'+numrecord+'D'].value='';
		//el['STARTDATE'+numrecord+'M'].value='';
		//el['STARTDATE'+numrecord+'Y'].value='';
		el['STARTDATE'+numrecord+'D'].disabled=true;
		el['STARTDATE'+numrecord+'M'].disabled=true;
		el['STARTDATE'+numrecord+'Y'].disabled=true;
		
		//el['STOPDATE'+numrecord+'D'].value='';
		//el['STOPDATE'+numrecord+'M'].value='';
		//el['STOPDATE'+numrecord+'Y'].value='';
		el['STOPDATE'+numrecord+'D'].disabled=true;
		el['STOPDATE'+numrecord+'M'].disabled=true;
		el['STOPDATE'+numrecord+'Y'].disabled=true;

		el['ONGOING_END'+numrecord].disabled=true;	
		
		el['RECD'+numrecord].disabled=true;
		
		el['THERAPY'+numrecord].style.backgroundColor = "gray";
		el['ROUTE'+numrecord].style.backgroundColor = "gray";
		el['DOSE'+numrecord].style.backgroundColor = "gray";
		el['REASON_AE'+numrecord].style.backgroundColor = "gray";
		el['REASON_CMC'+numrecord].style.backgroundColor = "gray";
		el['REASON_OTHER'+numrecord].style.backgroundColor = "gray";		
		el['STARTDATE'+numrecord+'D'].style.backgroundColor = "gray";
		el['STARTDATE'+numrecord+'M'].style.backgroundColor = "gray";
		el['STARTDATE'+numrecord+'Y'].style.backgroundColor = "gray";
		el['STOPDATE'+numrecord+'D'].style.backgroundColor = "gray";
		el['STOPDATE'+numrecord+'M'].style.backgroundColor = "gray";
		el['STOPDATE'+numrecord+'Y'].style.backgroundColor = "gray";
		el['ONGOING_END'+numrecord].style.backgroundColor = "gray";
		el['RECD'+numrecord].style.backgroundColor = "gray";
		return true;
	}
	else 
	{
		el['RECD'+numrecord].checked=false;
		return false;
	}
	
	return true;

}

function load_concmed()
{
	f=document.forms[0];
	el=f.elements;	
	var nrrecord = 15;
	
	for (var i=1; i<=nrrecord; i++)
	{
		if (el['RECD'+i].checked==true) //record cancellato
		{
			el['THERAPY'+i].disabled=true;
			el['ROUTE'+i].disabled=true;
			el['DOSE'+i].disabled=true;
			var objs=el['REASON'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;
			
			el['REASON_AE'+i].disabled=true;
			el['REASON_CMC'+i].disabled=true;
			el['REASON_OTHER'+i].disabled=true;
			el['STARTDATE'+i+'D'].disabled=true;
			el['STARTDATE'+i+'M'].disabled=true;
			el['STARTDATE'+i+'Y'].disabled=true;
			el['STOPDATE'+i+'D'].disabled=true;
			el['STOPDATE'+i+'M'].disabled=true;
			el['STOPDATE'+i+'Y'].disabled=true;
			el['ONGOING_END'+i].disabled=true;
			el['RECD'+i].disabled=true;
			el['THERAPY'+i].style.backgroundColor = "gray";
			el['ROUTE'+i].style.backgroundColor = "gray";
			el['DOSE'+i].style.backgroundColor = "gray";
			el['REASON_AE'+i].style.backgroundColor = "gray";
			el['REASON_CMC'+i].style.backgroundColor = "gray";
			el['REASON_OTHER'+i].style.backgroundColor = "gray";
			el['STARTDATE'+i+'D'].style.backgroundColor = "gray";
			el['STARTDATE'+i+'M'].style.backgroundColor = "gray";
			el['STARTDATE'+i+'Y'].style.backgroundColor = "gray";
			el['STOPDATE'+i+'D'].style.backgroundColor = "gray";
			el['STOPDATE'+i+'M'].style.backgroundColor = "gray";
			el['STOPDATE'+i+'Y'].style.backgroundColor = "gray";
			el['ONGOING_END'+i].style.backgroundColor = "gray";
			el['RECD'+i].style.backgroundColor = "gray";
		}
		if (el['REC'+i].checked==true) //aggiungi record
		{	
			el['REC'+i].disabled=true;
			el['REC'+i].style.backgroundColor = "gray";
		}		
	}
	
	return true;
}

function ae_delete(numrecord)
{
	f=document.forms[0];
	el=f.elements;	
		
	if (confirm('This record will be deleted. Please confim?'))
	{
		//el['AE_DESC'+numrecord].value='';
		el['AE_DESC'+numrecord].disabled=true;		

		//el['AE_ONSETDATE'+numrecord+'D'].value='';
		//el['AE_ONSETDATE'+numrecord+'M'].value='';
		//el['AE_ONSETDATE'+numrecord+'Y'].value='';
		el['AE_ONSETDATE'+numrecord+'D'].disabled=true;
		el['AE_ONSETDATE'+numrecord+'M'].disabled=true;
		el['AE_ONSETDATE'+numrecord+'Y'].disabled=true;
		
		el['AE_TIME'+numrecord+'_H'].disabled=true;
		el['AE_TIME'+numrecord+'_M'].disabled=true;
		
		var objs=el['AE_INTENSITY'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;
			
		var objs=el['AE_OUTCOME'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;
			
		//el['AE_RESOLVEDDATE'+numrecord+'D'].value='';
		//el['AE_RESOLVEDDATE'+numrecord+'M'].value='';
		//el['AE_RESOLVEDDATE'+numrecord+'Y'].value='';
		el['AE_RESOLVEDDATE'+numrecord+'D'].disabled=true;
		el['AE_RESOLVEDDATE'+numrecord+'M'].disabled=true;
		el['AE_RESOLVEDDATE'+numrecord+'Y'].disabled=true;

		var objs=el['AE_CAUSALITY'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;
			
		var objs=el['AE_CAUS'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;

			var objs=el['AE_SERIOUS'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;
		
		el['AE_REPORT'+numrecord+'_1_1'].disabled=true;
		el['AE_REPORT'+numrecord+'_2_1'].disabled=true;
		el['AE_REPORT'+numrecord+'_3_1'].disabled=true;
		el['AE_REPORT'+numrecord+'_4_1'].disabled=true;
		el['AE_REPORT'+numrecord+'_5_1'].disabled=true;
		el['AE_REPORT'+numrecord+'_6_1'].disabled=true;
			
		var objs=el['AE_THERAPY'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;
			
		var objs=el['AE_INTAKE'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;
			
		el['RECD'+numrecord].disabled=true;
		
		el['AE_DESC'+numrecord].style.backgroundColor = "gray";
		
		el['AE_ONSETDATE'+numrecord+'D'].style.backgroundColor = "gray";
		el['AE_ONSETDATE'+numrecord+'M'].style.backgroundColor = "gray";
		el['AE_ONSETDATE'+numrecord+'Y'].style.backgroundColor = "gray";
		
		el['AE_TIME'+numrecord+'_H'].style.backgroundColor = "gray";
		el['AE_TIME'+numrecord+'_M'].style.backgroundColor = "gray";

		el['AE_RESOLVEDDATE'+numrecord+'D'].style.backgroundColor = "gray";
		el['AE_RESOLVEDDATE'+numrecord+'M'].style.backgroundColor = "gray";
		el['AE_RESOLVEDDATE'+numrecord+'Y'].style.backgroundColor = "gray";
		
		el['RECD'+numrecord].style.backgroundColor = "gray";
		return true;
	}
	else 
	{
		el['RECD'+numrecord].checked=false;
		return false;
	}
	
	return true;

}

function load_ae()
{
	f=document.forms[0];
	el=f.elements;	
	var nrrecord = 20;
	
	for (var i=1; i<=nrrecord; i++)
	{
		if (el['RECD'+i].checked==true) //record cancellato
		{
			el['AE_DESC'+i].disabled=true;
			
			el['AE_ONSETDATE'+i+'D'].disabled=true;
			el['AE_ONSETDATE'+i+'M'].disabled=true;
			el['AE_ONSETDATE'+i+'Y'].disabled=true;
			
			el['AE_TIME'+i+'_H'].disabled=true;
			el['AE_TIME'+i+'_M'].disabled=true;
			
			var objs=el['AE_INTENSITY'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;
			
			var objs=el['AE_OUTCOME'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;
				
			el['AE_RESOLVEDDATE'+i+'D'].disabled=true;
			el['AE_RESOLVEDDATE'+i+'M'].disabled=true;
			el['AE_RESOLVEDDATE'+i+'Y'].disabled=true;
			
			var objs=el['AE_CAUSALITY'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;

			var objs=el['AE_CAUS'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;

				var objs=el['AE_SERIOUS'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;

			el['AE_REPORT'+i+'_1_1'].disabled=true;
			el['AE_REPORT'+i+'_2_1'].disabled=true;
			el['AE_REPORT'+i+'_3_1'].disabled=true;
			el['AE_REPORT'+i+'_4_1'].disabled=true;
			el['AE_REPORT'+i+'_5_1'].disabled=true;
			el['AE_REPORT'+i+'_6_1'].disabled=true;

			var objs=el['AE_THERAPY'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;

			var objs=el['AE_INTAKE'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;

			
			el['RECD'+i].disabled=true;
			
			el['AE_DESC'+i].style.backgroundColor = "gray";

			el['AE_ONSETDATE'+i+'D'].style.backgroundColor = "gray";
			el['AE_ONSETDATE'+i+'M'].style.backgroundColor = "gray";
			el['AE_ONSETDATE'+i+'Y'].style.backgroundColor = "gray";

			el['AE_TIME'+i+'_H'].style.backgroundColor = "gray";
			el['AE_TIME'+i+'_M'].style.backgroundColor = "gray";

			el['AE_RESOLVEDDATE'+i+'D'].style.backgroundColor = "gray";
			el['AE_RESOLVEDDATE'+i+'M'].style.backgroundColor = "gray";
			el['AE_RESOLVEDDATE'+i+'Y'].style.backgroundColor = "gray";
			
			el['RECD'+i].style.backgroundColor = "gray";
		}
		if (el['REC'+i].checked==true) //aggiungi record
		{	
			el['REC'+i].disabled=true;
			el['REC'+i].style.backgroundColor = "gray";
		}		

		// se Event is final tutti i campi vengono disabilitati

		if (el['FREEZE'+i].checked==true)
		{
			el['AE_DESC'+i].disabled=true;
			
			el['AE_ONSETDATE'+i+'D'].disabled=true;
			el['AE_ONSETDATE'+i+'M'].disabled=true;
			el['AE_ONSETDATE'+i+'Y'].disabled=true;
			
			el['AE_TIME'+i+'_H'].disabled=true;
			el['AE_TIME'+i+'_M'].disabled=true;
			
			var objs=el['AE_INTENSITY'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;
			
			var objs=el['AE_OUTCOME'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;
				
			el['AE_RESOLVEDDATE'+i+'D'].disabled=true;
			el['AE_RESOLVEDDATE'+i+'M'].disabled=true;
			el['AE_RESOLVEDDATE'+i+'Y'].disabled=true;
			
			var objs=el['AE_CAUSALITY'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;

			var objs=el['AE_CAUS'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;

				var objs=el['AE_SERIOUS'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;

			el['AE_REPORT'+i+'_1_1'].disabled=true;
			el['AE_REPORT'+i+'_2_1'].disabled=true;
			el['AE_REPORT'+i+'_3_1'].disabled=true;
			el['AE_REPORT'+i+'_4_1'].disabled=true;
			el['AE_REPORT'+i+'_5_1'].disabled=true;
			el['AE_REPORT'+i+'_6_1'].disabled=true;

			var objs=el['AE_THERAPY'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;

			var objs=el['AE_INTAKE'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;

			
			el['RECD'+i].disabled=true;
			
			el['AE_DESC'+i].style.backgroundColor = "gray";

			el['AE_ONSETDATE'+i+'D'].style.backgroundColor = "gray";
			el['AE_ONSETDATE'+i+'M'].style.backgroundColor = "gray";
			el['AE_ONSETDATE'+i+'Y'].style.backgroundColor = "gray";

			el['AE_TIME'+i+'_H'].style.backgroundColor = "gray";
			el['AE_TIME'+i+'_M'].style.backgroundColor = "gray";

			el['AE_RESOLVEDDATE'+i+'D'].style.backgroundColor = "gray";
			el['AE_RESOLVEDDATE'+i+'M'].style.backgroundColor = "gray";
			el['AE_RESOLVEDDATE'+i+'Y'].style.backgroundColor = "gray";
			
			el['RECD'+i].style.backgroundColor = "gray";
		}
	}
	
	return true;
}

function oi_delete(numrecord)
{
	f=document.forms[0];
	el=f.elements;	
		
	if (confirm('This record will be deleted. Please confim?'))
	{
		el['OI_DESC'+numrecord].disabled=true;		

		el['OI_ONSETDATE'+numrecord+'D'].disabled=true;
		el['OI_ONSETDATE'+numrecord+'M'].disabled=true;
		el['OI_ONSETDATE'+numrecord+'Y'].disabled=true;
		
		el['OI_RESDATE'+numrecord+'D'].disabled=true;
		el['OI_RESDATE'+numrecord+'M'].disabled=true;
		el['OI_RESDATE'+numrecord+'Y'].disabled=true;

		el['OI_ONG'+numrecord].disabled=true;

		var objs=el['OI_INTENSITY'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;
			
		var objs=el['OI_HOSP'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;
			
		el['OI_RESDT_FROM'+numrecord+'D'].disabled=true;
		el['OI_RESDT_FROM'+numrecord+'M'].disabled=true;
		el['OI_RESDT_FROM'+numrecord+'Y'].disabled=true;
		
		el['OI_RESDT_TO'+numrecord+'D'].disabled=true;
		el['OI_RESDT_TO'+numrecord+'M'].disabled=true;
		el['OI_RESDT_TO'+numrecord+'Y'].disabled=true;

			var objs=el['OI_THERAPY'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;
			
		el['RECD'+numrecord].disabled=true;
		
		el['OI_DESC'+numrecord].style.backgroundColor = "gray";
		
		el['OI_ONSETDATE'+numrecord+'D'].style.backgroundColor = "gray";
		el['OI_ONSETDATE'+numrecord+'M'].style.backgroundColor = "gray";
		el['OI_ONSETDATE'+numrecord+'Y'].style.backgroundColor = "gray";
		
		el['OI_RESDATE'+numrecord+'D'].style.backgroundColor = "gray";
		el['OI_RESDATE'+numrecord+'M'].style.backgroundColor = "gray";
		el['OI_RESDATE'+numrecord+'Y'].style.backgroundColor = "gray";
		
		el['OI_ONG'+numrecord].style.backgroundColor = "gray";

		el['OI_RESDT_FROM'+numrecord+'D'].style.backgroundColor = "gray";
		el['OI_RESDT_FROM'+numrecord+'M'].style.backgroundColor = "gray";
		el['OI_RESDT_FROM'+numrecord+'Y'].style.backgroundColor = "gray";
		
		el['OI_RESDT_TO'+numrecord+'D'].style.backgroundColor = "gray";
		el['OI_RESDT_TO'+numrecord+'M'].style.backgroundColor = "gray";
		el['OI_RESDT_TO'+numrecord+'Y'].style.backgroundColor = "gray";

		el['RECD'+numrecord].style.backgroundColor = "gray";
		return true;
	}
	else 
	{
		el['RECD'+numrecord].checked=false;
		return false;
	}
	
	return true;

}

function load_oi()
{
	f=document.forms[0];
	el=f.elements;	
	//var nrrecord = 32;
	var nrrecord = 10;
	
	for (var i=1; i<=nrrecord; i++)
	{
		if (el['RECD'+i].checked==true) //record cancellato
		{
			el['OI_DESC'+i].disabled=true;
			
			el['OI_ONSETDATE'+i+'D'].disabled=true;
			el['OI_ONSETDATE'+i+'M'].disabled=true;
			el['OI_ONSETDATE'+i+'Y'].disabled=true;
			
			el['OI_RESDATE'+i+'D'].disabled=true;
			el['OI_RESDATE'+i+'M'].disabled=true;
			el['OI_RESDATE'+i+'Y'].disabled=true;

			el['OI_ONG'+i].disabled=true;

			var objs=el['OI_INTENSITY'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;
			
			var objs=el['OI_HOSP'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;
				
			el['OI_RESDT_FROM'+i+'D'].disabled=true;
			el['OI_RESDT_FROM'+i+'M'].disabled=true;
			el['OI_RESDT_FROM'+i+'Y'].disabled=true;
			
			el['OI_RESDT_TO'+i+'D'].disabled=true;
			el['OI_RESDT_TO'+i+'M'].disabled=true;
			el['OI_RESDT_TO'+i+'Y'].disabled=true;
			
			var objs=el['OI_THERAPY'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;
			
			el['RECD'+i].disabled=true;
			
			el['OI_DESC'+i].style.backgroundColor = "gray";
			
			el['OI_ONSETDATE'+i+'D'].style.backgroundColor = "gray";
			el['OI_ONSETDATE'+i+'M'].style.backgroundColor = "gray";
			el['OI_ONSETDATE'+i+'Y'].style.backgroundColor = "gray";
			
			el['OI_RESDATE'+i+'D'].style.backgroundColor = "gray";
			el['OI_RESDATE'+i+'M'].style.backgroundColor = "gray";
			el['OI_RESDATE'+i+'Y'].style.backgroundColor = "gray";
			
			el['OI_ONG'+i].style.backgroundColor = "gray";

			el['OI_RESDT_FROM'+i+'D'].style.backgroundColor = "gray";
			el['OI_RESDT_FROM'+i+'M'].style.backgroundColor = "gray";
			el['OI_RESDT_FROM'+i+'Y'].style.backgroundColor = "gray";
			
			el['OI_RESDT_TO'+i+'D'].style.backgroundColor = "gray";
			el['OI_RESDT_TO'+i+'M'].style.backgroundColor = "gray";
			el['OI_RESDT_TO'+i+'Y'].style.backgroundColor = "gray";

			el['RECD'+i].style.backgroundColor = "gray";
		}
		if (el['REC'+i].checked==true) //aggiungi record
		{	
			el['REC'+i].disabled=true;
			el['REC'+i].style.backgroundColor = "gray";
		}		
	}
	
	return true;
}

function cmv_delete(numrecord)
{
	f=document.forms[0];
	el=f.elements;	
		
	if (confirm('This record will be deleted. Please confim?'))
	{
		el['CMV_ONSETDATE'+numrecord+'D'].disabled=true;
		el['CMV_ONSETDATE'+numrecord+'M'].disabled=true;
		el['CMV_ONSETDATE'+numrecord+'Y'].disabled=true;
		
		el['CMV_ONSETTIME'+numrecord+'_H'].disabled=true;
		el['CMV_ONSETTIME'+numrecord+'_M'].disabled=true;

		var objs=el['CMV_CLASSIF'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;

		el['CMV_RESDATE'+numrecord+'D'].disabled=true;
		el['CMV_RESDATE'+numrecord+'M'].disabled=true;
		el['CMV_RESDATE'+numrecord+'Y'].disabled=true;

		el['CMV_ONG'+numrecord].disabled=true;

		var objs=el['CMV_INTENSITY'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;

		var objs=el['CMV_HOSP'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;
			
		el['CMV_RESDT_FROM'+numrecord+'D'].disabled=true;
		el['CMV_RESDT_FROM'+numrecord+'M'].disabled=true;
		el['CMV_RESDT_FROM'+numrecord+'Y'].disabled=true;
		
		el['CMV_RESDT_TO'+numrecord+'D'].disabled=true;
		el['CMV_RESDT_TO'+numrecord+'M'].disabled=true;
		el['CMV_RESDT_TO'+numrecord+'Y'].disabled=true;

		var objs=el['CMV_THERAPY'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;
			
		el['RECD'+numrecord].disabled=true;
		
		el['CMV_ONSETDATE'+numrecord+'D'].style.backgroundColor = "gray";
		el['CMV_ONSETDATE'+numrecord+'M'].style.backgroundColor = "gray";
		el['CMV_ONSETDATE'+numrecord+'Y'].style.backgroundColor = "gray";
		
		el['CMV_ONSETTIME'+numrecord+'_H'].style.backgroundColor = "gray";
		el['CMV_ONSETTIME'+numrecord+'_M'].style.backgroundColor = "gray";
		
		el['CMV_RESDATE'+numrecord+'D'].style.backgroundColor = "gray";
		el['CMV_RESDATE'+numrecord+'M'].style.backgroundColor = "gray";
		el['CMV_RESDATE'+numrecord+'Y'].style.backgroundColor = "gray";

		el['CMV_ONG'+numrecord].style.backgroundColor = "gray";

		el['CMV_RESDT_FROM'+numrecord+'D'].style.backgroundColor = "gray";
		el['CMV_RESDT_FROM'+numrecord+'M'].style.backgroundColor = "gray";
		el['CMV_RESDT_FROM'+numrecord+'Y'].style.backgroundColor = "gray";
		
		el['CMV_RESDT_TO'+numrecord+'D'].style.backgroundColor = "gray";
		el['CMV_RESDT_TO'+numrecord+'M'].style.backgroundColor = "gray";
		el['CMV_RESDT_TO'+numrecord+'Y'].style.backgroundColor = "gray";

		el['RECD'+numrecord].style.backgroundColor = "gray";
		return true;
	}
	else 
	{
		el['RECD'+numrecord].checked=false;
		return false;
	}
	
	return true;

}

function load_cmv()
{
	f=document.forms[0];
	el=f.elements;	
	//var nrrecord = 32;
	var nrrecord = 10;
	
	for (var i=1; i<=nrrecord; i++)
	{
		if (el['RECD'+i].checked==true) //record cancellato
		{
			el['CMV_ONSETDATE'+i+'D'].disabled=true;
			el['CMV_ONSETDATE'+i+'M'].disabled=true;
			el['CMV_ONSETDATE'+i+'Y'].disabled=true;
			
			el['CMV_ONSETTIME'+i+'_H'].disabled=true;
			el['CMV_ONSETTIME'+i+'_M'].disabled=true;

			var objs=el['CMV_CLASSIF'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;

			el['CMV_RESDATE'+i+'D'].disabled=true;
			el['CMV_RESDATE'+i+'M'].disabled=true;
			el['CMV_RESDATE'+i+'Y'].disabled=true;

			el['CMV_ONG'+i].disabled=true;

			var objs=el['CMV_INTENSITY'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;
			
			var objs=el['CMV_HOSP'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;
				
			el['CMV_RESDT_FROM'+i+'D'].disabled=true;
			el['CMV_RESDT_FROM'+i+'M'].disabled=true;
			el['CMV_RESDT_FROM'+i+'Y'].disabled=true;
			
			el['CMV_RESDT_TO'+i+'D'].disabled=true;
			el['CMV_RESDT_TO'+i+'M'].disabled=true;
			el['CMV_RESDT_TO'+i+'Y'].disabled=true;
			
			var objs=el['CMV_THERAPY'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;
			
			el['RECD'+i].disabled=true;
			
			el['CMV_ONSETDATE'+i+'D'].style.backgroundColor = "gray";
			el['CMV_ONSETDATE'+i+'M'].style.backgroundColor = "gray";
			el['CMV_ONSETDATE'+i+'Y'].style.backgroundColor = "gray";
			
			el['CMV_ONSETTIME'+i+'_H'].style.backgroundColor = "gray";
			el['CMV_ONSETTIME'+i+'_M'].style.backgroundColor = "gray";

			el['CMV_RESDATE'+i+'D'].style.backgroundColor = "gray";
			el['CMV_RESDATE'+i+'M'].style.backgroundColor = "gray";
			el['CMV_RESDATE'+i+'Y'].style.backgroundColor = "gray";

			el['CMV_ONG'+i].style.backgroundColor = "gray";

			el['CMV_RESDT_FROM'+i+'D'].style.backgroundColor = "gray";
			el['CMV_RESDT_FROM'+i+'M'].style.backgroundColor = "gray";
			el['CMV_RESDT_FROM'+i+'Y'].style.backgroundColor = "gray";
			
			el['CMV_RESDT_TO'+i+'D'].style.backgroundColor = "gray";
			el['CMV_RESDT_TO'+i+'M'].style.backgroundColor = "gray";
			el['CMV_RESDT_TO'+i+'Y'].style.backgroundColor = "gray";

			el['RECD'+i].style.backgroundColor = "gray";
		}
		if (el['REC'+i].checked==true) //aggiungi record
		{	
			el['REC'+i].disabled=true;
			el['REC'+i].style.backgroundColor = "gray";
		}		
	}
	
	return true;
}

function gd_delete(numrecord)
{
	f=document.forms[0];
	el=f.elements;	
		
	if (confirm('This record will be deleted. Please confim?'))
	{
		el['GD_ONSETDATE'+numrecord+'D'].disabled=true;
		el['GD_ONSETDATE'+numrecord+'M'].disabled=true;
		el['GD_ONSETDATE'+numrecord+'Y'].disabled=true;
		
		el['GD_ONSETTIME'+numrecord+'_H'].disabled=true;
		el['GD_ONSETTIME'+numrecord+'_M'].disabled=true;

		var objs=el['GD_STAGE_SKIN'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;

		var objs=el['GD_STAGE_LIVER'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;

		var objs=el['GD_STAGE_GUT'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;

		var objs=el['GD_GRADE_SKIN'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;

		var objs=el['GD_GRADE_LIVER'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;

		var objs=el['GD_GRADE_GUT'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;

		var objs=el['GD_OUTCOME'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;

		el['GD_STOPDATE'+numrecord+'D'].disabled=true;
		el['GD_STOPDATE'+numrecord+'M'].disabled=true;
		el['GD_STOPDATE'+numrecord+'Y'].disabled=true;

		var objs=el['GD_HOSP'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;

		el['GD_HOSP_FROM'+numrecord+'D'].disabled=true;
		el['GD_HOSP_FROM'+numrecord+'M'].disabled=true;
		el['GD_HOSP_FROM'+numrecord+'Y'].disabled=true;

		el['GD_HOSP_TO'+numrecord+'D'].disabled=true;
		el['GD_HOSP_TO'+numrecord+'M'].disabled=true;
		el['GD_HOSP_TO'+numrecord+'Y'].disabled=true;

		var objs=el['GD_THERAPY'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;

		var objs=el['GD_DISCONT'+numrecord];
		for(var i=0;i<objs.length;i++)
			objs[i].disabled=true;
			
		el['RECD'+numrecord].disabled=true;
		
		el['GD_ONSETDATE'+numrecord+'D'].style.backgroundColor = "gray";
		el['GD_ONSETDATE'+numrecord+'M'].style.backgroundColor = "gray";
		el['GD_ONSETDATE'+numrecord+'Y'].style.backgroundColor = "gray";
		
		el['GD_ONSETTIME'+numrecord+'_H'].style.backgroundColor = "gray";
		el['GD_ONSETTIME'+numrecord+'_M'].style.backgroundColor = "gray";
		
		el['GD_STOPDATE'+numrecord+'D'].style.backgroundColor = "gray";
		el['GD_STOPDATE'+numrecord+'M'].style.backgroundColor = "gray";
		el['GD_STOPDATE'+numrecord+'Y'].style.backgroundColor = "gray";

		el['GD_HOSP_FROM'+numrecord+'D'].style.backgroundColor = "gray";
		el['GD_HOSP_FROM'+numrecord+'M'].style.backgroundColor = "gray";
		el['GD_HOSP_FROM'+numrecord+'Y'].style.backgroundColor = "gray";
		
		el['GD_HOSP_TO'+numrecord+'D'].style.backgroundColor = "gray";
		el['GD_HOSP_TO'+numrecord+'M'].style.backgroundColor = "gray";
		el['GD_HOSP_TO'+numrecord+'Y'].style.backgroundColor = "gray";

		el['RECD'+numrecord].style.backgroundColor = "gray";
		return true;
	}
	else 
	{
		el['RECD'+numrecord].checked=false;
		return false;
	}
	
	return true;

}

function load_gd()
{
	f=document.forms[0];
	el=f.elements;	
	//var nrrecord = 32;
	var nrrecord = 10;
	
	for (var i=1; i<=nrrecord; i++)
	{
		if (el['RECD'+i].checked==true) //record cancellato
		{
			el['GD_ONSETDATE'+i+'D'].disabled=true;
			el['GD_ONSETDATE'+i+'M'].disabled=true;
			el['GD_ONSETDATE'+i+'Y'].disabled=true;
			
			el['GD_ONSETTIME'+i+'_H'].disabled=true;
			el['GD_ONSETTIME'+i+'_M'].disabled=true;

			var objs=el['GD_STAGE_SKIN'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;

			var objs=el['GD_STAGE_LIVER'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;

			var objs=el['GD_STAGE_GUT'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;

			var objs=el['GD_GRADE_SKIN'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;

			var objs=el['GD_GRADE_LIVER'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;

			var objs=el['GD_GRADE_GUT'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;

			var objs=el['GD_OUTCOME'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;

			el['GD_STOPDATE'+i+'D'].disabled=true;
			el['GD_STOPDATE'+i+'M'].disabled=true;
			el['GD_STOPDATE'+i+'Y'].disabled=true;

			var objs=el['GD_HOSP'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;

			el['GD_HOSP_FROM'+i+'D'].disabled=true;
			el['GD_HOSP_FROM'+i+'M'].disabled=true;
			el['GD_HOSP_FROM'+i+'Y'].disabled=true;

			el['GD_HOSP_TO'+i+'D'].disabled=true;
			el['GD_HOSP_TO'+i+'M'].disabled=true;
			el['GD_HOSP_TO'+i+'Y'].disabled=true;

			var objs=el['GD_THERAPY'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;

			var objs=el['GD_DISCONT'+i];
			for(var j=0;j<objs.length;j++)
				objs[j].disabled=true;
				
			el['RECD'+i].disabled=true;
		
			el['GD_ONSETDATE'+i+'D'].style.backgroundColor = "gray";
			el['GD_ONSETDATE'+i+'M'].style.backgroundColor = "gray";
			el['GD_ONSETDATE'+i+'Y'].style.backgroundColor = "gray";
			
			el['GD_ONSETTIME'+i+'_H'].style.backgroundColor = "gray";
			el['GD_ONSETTIME'+i+'_M'].style.backgroundColor = "gray";
			
			el['GD_STOPDATE'+i+'D'].style.backgroundColor = "gray";
			el['GD_STOPDATE'+i+'M'].style.backgroundColor = "gray";
			el['GD_STOPDATE'+i+'Y'].style.backgroundColor = "gray";

			el['GD_HOSP_FROM'+i+'D'].style.backgroundColor = "gray";
			el['GD_HOSP_FROM'+i+'M'].style.backgroundColor = "gray";
			el['GD_HOSP_FROM'+i+'Y'].style.backgroundColor = "gray";
			
			el['GD_HOSP_TO'+i+'D'].style.backgroundColor = "gray";
			el['GD_HOSP_TO'+i+'M'].style.backgroundColor = "gray";
			el['GD_HOSP_TO'+i+'Y'].style.backgroundColor = "gray";

			el['RECD'+i].style.backgroundColor = "gray";
		}
		if (el['REC'+i].checked==true) //aggiungi record
		{	
			el['REC'+i].disabled=true;
			el['REC'+i].style.backgroundColor = "gray";
		}		
	}
	
	return true;
}




/*FUNZIONI PER LA FORM LABORATORY*/
function CalcOutOfRange(num_rec){	
	f=document.forms[0];
	el=f.elements;	
	//alert('*'+el['LBEXT1_'+num_rec].value);
	if (el['LBORRES'+num_rec].value!='')
	{
		if (el['LBEXT'+num_rec+'_1'].checked==false) //non ext lab
		{	if (el['LBORNRLO'+num_rec].value.toUpperCase()!='NA')
			{	
				if ((el['LBORRES'+num_rec].value*1) < (el['LBORNRLO'+num_rec].value*1))
					
					el['LBNRIND'+num_rec+'_1'].checked=true; //out of range
				else if (el['LBORNRHI'+num_rec].value.toUpperCase()!='NA')
				{	
					if ((el['LBORRES'+num_rec].value*1) > (el['LBORNRHI'+num_rec].value*1))
						el['LBNRIND'+num_rec+'_1'].checked=true; //out of range
					else
						el['LBNRIND'+num_rec+'_1'].checked=false;//non out of range
				}
				else
					el['LBNRIND'+num_rec+'_1'].checked=false;//non out of range
			}
			else if (el['LBORNRHI'+num_rec].value.toUpperCase()!='NA')
			{	
				if ((el['LBORRES'+num_rec].value*1) > (el['LBORNRHI'+num_rec].value*1))
					el['LBNRIND'+num_rec+'_1'].checked=true; //out of range
				else
					el['LBNRIND'+num_rec+'_1'].checked=false;//non out of range
			}
			else
				el['LBNRIND'+num_rec+'_1'].checked=false;//non out of range
		}
		else if ( el['LBEXT'+num_rec+'_1'].value==1) //ext lab
		{	if (el['LBORNRLOE'+num_rec].value.toUpperCase()!='NA' && el['LBORNRLOE'+num_rec].value!='')
			{	
				if ((el['LBORRES'+num_rec].value*1) < (el['LBORNRLOE'+num_rec].value*1))
					el['LBNRIND'+num_rec+'_1'].checked=true; //out of range
				else if (el['LBORNRHIE'+num_rec].value.toUpperCase()!='NA' && el['LBORNRHIE'+num_rec].value!='')
				{	
					if ((el['LBORRES'+num_rec].value*1) > (el['LBORNRHIE'+num_rec].value*1))
						el['LBNRIND'+num_rec+'_1'].checked=true; //out of range
					else
						el['LBNRIND'+num_rec+'_1'].checked=false;//non out of range
				}
				else
					el['LBNRIND'+num_rec+'_1'].checked=false;//non out of range
			}
			else if (el['LBORNRHIE'+num_rec].value.toUpperCase()!='NA' && el['LBORNRHIE'+num_rec].value!='')
			{	
				if ((el['LBORRES'+num_rec].value*1) > (el['LBORNRHIE'+num_rec].value*1))
					el['LBNRIND'+num_rec+'_1'].checked=true; //out of range
				else
					el['LBNRIND'+num_rec+'_1'].checked=false;//non out of range
			}
			else
				el['LBNRIND'+num_rec+'_1'].checked=false;//non out of range
		}
	}
	else
		el['LBNRIND'+num_rec+'_1'].checked=false;//non out of range
	return true;
}

// questa funzione verrà chiamata all’ onChange della sampling date della form laboratory
function range_lab_sampling_date(){	
	f=document.forms[0];
	el=f.elements;	
	x_visitnum = document.forms[0].elements['VISITNUM'].value;	
	var num_rec='';
	//si usa la data della tabella LBM sampling date
	var xdatesampling ='';
	xdatesampling=el['LBPERFDATE'].value;
	//GESTIRE IL CASO DATA INCOMPLETA NA/NK!!!!le date incomplete non vengono accettate
	xdatesam_d=xdatesampling.substring(0,2);
	xdatesam_m=xdatesampling.substring(2,4);
	xdatesam_y=xdatesampling.substring(4,8);
	var xdatesampling_d= xdatesam_y+xdatesam_m+xdatesam_d;
	if (xdatesampling!='')
	{	//si ricava il sesso utile per la ricerca
		var xsex=1; //per poseidon non c'è il sesso quindi è stato impostato di default a 1 anche nella range_lab. el['HD_SEX'].value;
		//SE SI HANNO TUTTI I DATI PER PROCEDERE, SI RICERCA SULLA VISTA V_RANGE_LAB_RECORDSET_MALE O V_RANGE_LAB_RECORDSET_FEMALE,
		//DIPENDE DAL SESSO IL RECORDSET DA APPLICARE IN BASE ALLA DATA DELLA VISITA DI VISIT_INFORMATION.
		var num_rec='';
		var date_range ='';
		var giorni_backup=0;
		var recordset_dautilizzare='';
		var myValue='';
		var myrecordset='';
		var mydate='';
		if (xsex!='' && xdatesampling!='')
		{	if (xsex==1) //male
			{	var i=1;
				var selectbox2=document.getElementsByName("HD_SETMALE");
				var selectbox=selectbox2[0];
				while(i<selectbox.options.length)
				{
					myValue=selectbox.options[i].value;
					myrecordset=myValue.substring(0,myValue.indexOf('*'));
					mydate=myValue.substring(myValue.indexOf('*')+1,myValue.length);
					mydate_d=mydate.substring(0,2);
					mydate_m=mydate.substring(2,4);
					mydate_y=mydate.substring(4,8);
					var myDatedate = mydate_y+mydate_m+mydate_d;
					differenza = xdatesampling_d-myDatedate;   	
					giorni_differenza = new String(differenza/86400000);
					if (giorni_backup=='')//primo giro
						giorni_backup=giorni_differenza;
					if ((giorni_differenza*1) <= (giorni_backup*1) && (giorni_differenza*1) >= 0)
					{	giorni_backup = giorni_differenza;
						recordset_dautilizzare=myrecordset;
					}	
					i=i+1;
				}
			}
			else if (xsex==2) //female
			{	var selectbox2=document.getElementsByName("HD_SETFEMALE");
				var i=1;
				var selectbox=selectbox2[0];
				while(i<selectbox.options.length)
				{
					myValue=selectbox.options[i].value;
					myrecordset=myValue.substring(0,myValue.indexOf('*'));
					mydate=myValue.substring(myValue.indexOf('*')+1,myValue.length);
					mydate_d=mydate.substring(0,2);
					mydate_m=mydate.substring(2,4);
					mydate_y=mydate.substring(4,8);
					var myDatedate = mydate_y+mydate_m+mydate_d;
					differenza = xdatesampling_d-myDatedate;    	
					giorni_differenza = new String(differenza/86400000);
					if (giorni_backup=='')//primo giro
						giorni_backup=giorni_differenza;
					if ((giorni_differenza*1) <= (giorni_backup*1) && (giorni_differenza*1) >= 0)
					{	giorni_backup = giorni_differenza;
						recordset_dautilizzare=myrecordset;
					}	
					i=i+1;
				}
			}
			//se non si ha il recordset unita, min e max rimaranno vuoti
			//alert(recordset_dautilizzare);
			if (recordset_dautilizzare=='')
			{	var i=1;
				for (i=1;i<8;i++)
				{	el['LBORRESU'+i].value='';  //UNITA
					el['LBORNRLO'+i].value=''; //MIN
					el['LBORNRHI'+i].value=''; //MAX
				}
				alert('Laboratory normal range are not in database. Please fill-in the laboratory normal range page in order to permit the range uploading');
			}
			else
			{	//adesso si ha il recordset da cercare.
				if (xsex==1 && recordset_dautilizzare!='') //male
				{	var u=1;
					var j=1;
					var x=1;
					var myunit='';
					var mymin='';
					var mymax='';
					var sel_box_unit=document.getElementsByName("HD_UNIT_"+recordset_dautilizzare);
					var s_box_unit=sel_box_unit[0];
					var sel_box_min=document.getElementsByName("HD_VALUE_MIN_"+recordset_dautilizzare);
					var s_box_min=sel_box_min[0];
					var sel_box_max=document.getElementsByName("HD_VALUE_MAX_"+recordset_dautilizzare);
					var s_box_max=sel_box_max[0];
					while(u<s_box_unit.options.length)
					{
						myunit=s_box_unit.options[u].value;
						//alert(myunit);
						myunit=myunit.substring(myunit.indexOf('*')+1,myunit.length);
						//alert(myunit);
						el['LBORRESU'+u].value=myunit;//UNITA
						u=u+1;
					}
					while(j<s_box_min.options.length)
					{
						mymin=s_box_min.options[j].value;
						mymin=mymin.substring(mymin.indexOf('*')+1,mymin.length);
						
						//alert(mymin);
						if(mymin=='-9911'){mymin='NA';}
						if(mymin=='-9922'){mymin='NK';}
						if(mymin=='-9933'){mymin='ND';}
						if(mymin=='-9944'){mymin='NP';}
						if(mymin=='-9955'){mymin='TE';}
						if(mymin=='-9900'){mymin='OT';}
						el['LBORNRLO'+j].value=mymin;  //min
						j=j+1;
					}
					while(x<s_box_max.options.length)
					{
						mymax=s_box_max.options[x].value;
						mymax=mymax.substring(mymax.indexOf('*')+1,mymax.length);
						if(mymax=='-9911'){mymax='NA';}
						if(mymax=='-9922'){mymax='NK';}
						if(mymax=='-9933'){mymax='ND';}
						if(mymax=='-9944'){mymax='NP';}
						if(mymax=='-9955'){mymax='TE';}
						if(mymax=='-9900'){mymax='OT';}
						el['LBORNRHI'+x].value=mymax;  //max
						x=x+1;
					}
				}
				else if (xsex==2 && recordset_dautilizzare!='') //female
				{	var u=1;
					var j=1;
					var x=1;
					var myunit='';
					var mymin='';
					var mymax='';
					var sel_box_unit=document.getElementsByName("HD_FUNIT_"+recordset_dautilizzare);
					var s_box_unit=sel_box_unit[0];
					var sel_box_min=document.getElementsByName("HD_FVALUE_MIN_"+recordset_dautilizzare);
					var s_box_min=sel_box_min[0];
					var sel_box_max=document.getElementsByName("HD_FVALUE_MAX_"+recordset_dautilizzare);
					var s_box_max=sel_box_max[0];
					while(u<s_box_unit.options.length)
					{
						myunit=s_box_unit.options[u].value;
						//alert(myunit);
						myunit=myunit.substring(myunit.indexOf('*')+1,myunit.length);
						//alert(myunit);
						el['LBORRESU'+u].value=myunit;//UNITA
						u=u+1;
					}
					while(j<s_box_min.options.length)
					{
						mymin=s_box_min.options[j].value;
						mymin=mymin.substring(mymin.indexOf('*')+1,mymin.length);
						if(mymin=='-9911'){mymin='NA';}
						if(mymin=='-9922'){mymin='NK';}
						if(mymin=='-9933'){mymin='ND';}
						if(mymin=='-9944'){mymin='NP';}
						if(mymin=='-9955'){mymin='TE';}
						if(mymin=='-9900'){mymin='OT';}
						el['LBORNRLO'+j].value=mymin;  //min
						j=j+1;
					}
					while(x<s_box_max.options.length)
					{
						mymax=s_box_max.options[x].value;
						mymax=mymax.substring(mymax.indexOf('*')+1,mymax.length);
						if(mymax=='-9911'){mymax='NA';}
						if(mymax=='-9922'){mymax='NK';}
						if(mymax=='-9933'){mymax='ND';}
						if(mymax=='-9944'){mymax='NP';}
						if(mymax=='-9955'){mymax='TE';}
						if(mymax=='-9900'){mymax='OT';}
						el['LBORNRHI'+x].value=mymax;  //max
						x=x+1;
					}
				}
			}
		}	
		else if (xsex=='')
		{
			alert('Please, fill-out "Patient demographic medical history"');
		}
	}
	var i=1;
	for (i=1;i<8;i++)
	{	
		el['LBORRESU'+i].disabled=true;  //UNITA
		CalcOutOfRange(i);
		el['LBNRIND'+i+'_1'].disabled=true;
	}
}




function load_toxicity()
{	

	f=document.forms[0];
	el=f.elements;	
	
	x_visitnum = document.forms[0].elements['VISITNUM'].value;	
	//alert(x_visitnum);
	if((x_visitnum!=5)&&(x_visitnum!=6)&&(x_visitnum!=7))
	{
 	document.getElementById('cell_NA_1').style.display="none";
	document.getElementById('cell_input_NA_1').style.display="none";
	}

}

	function laboratoryMainV1(){
	
		
	//document.getElementsByName('')[0]	
	var myVal=getInputValue(document.forms[0].elements['LBPERF']);
	//alert(myVal);
	if(myVal==""){
	alert('The answer "YES" or "NO" for the "Has the examination performed?" has to be given');
	var P = document.getElementsByName('LBPERF');
	if (isArray(P) && (typeof(P.type)=="undefined")) {P=P[0];}	
	P.focus();
	return false;
	}
	if(myVal==1){
	var D=document.getElementsByName('LBANC1D');
	var M=document.getElementsByName('LBANC1M');
	var Y=document.getElementsByName('LBANC1Y');
	var d1=D[0].value;
	var m1=M[0].value;
	var y1=Y[0].value;
	var notDate=isNotDate(d1+"/"+m1+"/"+y1);
	if(notDate==true){
	alert("Please fill-in the date of first ANC analysis");
	D[0].focus();
	return false;
	}
	
	var C=document.getElementsByName('LBANCV1');
	if(C[0].value==""){
	alert('The information "According to inclusion criteria 4, ANC >= 1000 cells/µL on 2 consecutive follow-up within 10 days is required for randomization. Please document date and results of the respective measurements." must be given.');
	C[0].focus();	
	return false;
	}
	
	var DD=document.getElementsByName('LBANC2D');
	var MM=document.getElementsByName('LBANC2M');
	var YY=document.getElementsByName('LBANC2Y');
	var dd1=DD[0].value;
	var mm1=MM[0].value;
	var yy1=YY[0].value;
	var notDate=isNotDate(dd1+"/"+mm1+"/"+yy1);
	if(notDate==true){
	alert("Please fill-in the date of second ANC analysis");
	DD[0].focus();
	return false;
	}
	
	var C=document.getElementsByName('LBANCV2');
	if(C[0].value==""){
	alert('The information "According to inclusion criteria 4, ANC >= 1000 cells/µL on 2 consecutive follow-up within 10 days is required for randomization. Please document date and results of the respective measurements." must be given.');
	C[0].focus();	
	return false;
	}
	
	
	var DDD=document.getElementsByName('LBDATD');
	var MMM=document.getElementsByName('LBDATM');
	var YYY=document.getElementsByName('LBDATY');
	var ddd1=DDD[0].value;
	var mmm1=MMM[0].value;
	var yyy1=YYY[0].value;
	var notDate=isNotDate(ddd1+"/"+mmm1+"/"+yyy1);
	if(notDate==true){
	alert("Please fill-in the date of blood sampling");
	DDD[0].focus();
	return false;
	}	
	
	//alert(d1GEd2(d1+"/"+m1+"/"+y1,dd1+"/"+mm1+"/"+yy1));
	//alert(isDate);
	
	if(d1GEd2(d1+"/"+m1+"/"+y1,dd1+"/"+mm1+"/"+yy1)){
	alert('The "Date of second ANC analysis" has to be after the "Date of first ANC analysis"');
	D[0].focus();
	return false;
	}
	}
	
	//alert(myVal);
	return true;
	}

	function laboratoryMain(){
	
		
	//document.getElementsByName('')[0]	
	var myVal=getInputValue(document.forms[0].elements['LBPERF']);
	//alert(myVal);
	if(myVal==""){
	alert('The answer "YES" or "NO" for the "Has the examination performed?" has to be given');
	var P = document.getElementsByName('LBPERF');
	if (isArray(P) && (typeof(P.type)=="undefined")) {P=P[0];}	
	P.focus();
	return false;
	}
	if(myVal==1){

	
	var DDD=document.getElementsByName('LBDATD');
	var MMM=document.getElementsByName('LBDATM');
	var YYY=document.getElementsByName('LBDATY');
	var ddd1=DDD[0].value;
	var mmm1=MMM[0].value;
	var yyy1=YYY[0].value;
	var notDate=isNotDate(ddd1+"/"+mmm1+"/"+yyy1);
	if(notDate==true){
	alert("Please fill-in the date of blood sampling");
	DDD[0].focus();
	return false;
	}	
	
	//alert(d1GEd2(d1+"/"+m1+"/"+y1,dd1+"/"+mm1+"/"+yy1));
	//alert(isDate);
	

	}
	
	//alert(myVal);
	return true;
	}

	function ESAE_TYPE_save()
	{
		f=document.forms[0];
		el=f.elements;
		
			//chiamata ajax per eseguire il controllo sulla firma elettronica per evitare di riabilitare i campi disabilitati
			var ret="";
			$.ajax({ type : "POST", 
					 url : "index.php",
					 async: false, 
					 data : "CENTER="+el['CENTER'].value+"&CODPAT="+el['CODPAT'].value+"&ESAM="+el['ESAM'].value+"&VISITNUM="+el['VISITNUM'].value+"&VISITNUM_PROGR="+el['VISITNUM_PROGR'].value+"&PROGR="+el['PROGR'].value+"&form=sub_esaereport.xml&esig_singleform=1&ajax_call=1&SINVSIGN="+el['SINVSIGN'].value+"&SAEPWD="+el['SAEPWD'].value, 
					 dataType : "json", 
					 success : function(data) {
		      
						if (data.sstatus == 'ok') {
							ret=true;
							}
					      else if (data.sstatus == 'ko') {
					    	  alert(data.error);
					    	  ret=false;
					    	  }
					 }
			});
			return ret;
		return true;		
	}
	
	function EPRE_TYPE_save()
	{
		f=document.forms[0];
		el=f.elements;
		if(el['DISABLESIGN'].checked==true){
			alert('Warning: this ePregnancy Report Form is only saved.\nPlease sign the form within 24 hours of being aware of the pregnancy.')
		}
		else{
			//chiamata ajax per eseguire il controllo sulla firma elettronica per evitare di riabilitare i campi disabilitati
			var ret="";
			$.ajax({ type : "POST", 
					 url : "index.php",
					 async: false, 
					 data : "CENTER="+el['CENTER'].value+"&CODPAT="+el['CODPAT'].value+"&ESAM="+el['ESAM'].value+"&VISITNUM="+el['VISITNUM'].value+"&VISITNUM_PROGR="+el['VISITNUM_PROGR'].value+"&PROGR="+el['PROGR'].value+"&form=sub_epregnancyreport.xml&esig_singleform=1&ajax_call=1&SINVSIGN="+el['SINVSIGN'].value+"&SAEPWD="+el['SAEPWD'].value, 
					 dataType : "json", 
					 success : function(data) {
		      
						if (data.sstatus == 'ok') {
							ret=true;
							}
					      else if (data.sstatus == 'ko') {
					    	  alert(data.error);
					    	  ret=false;
					    	  }
					 }
			});
			return ret;
		}	
		return true;		
	}