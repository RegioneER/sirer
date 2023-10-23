function bsa(){
	var bsa;
	var prefix='';
	if($('[name=DIAGNOSI]').first().val()==3 || $('[name=DIAGNOSI]').first().val()==2){
		if($('[name=DIAGNOSI]').first().val()==3){
			prefix='GASTRO_';
		}
		height=$('[name='+prefix+'ALTEZZA]').first().val();
		weight=$('[name='+prefix+'PESO]').first().val();
		if(height>0 && weight>0 && !isNaN(height) && !isNaN(weight)){
			bsa=0.007184*Math.pow(weight,0.425)*Math.pow(height*100,0.725);
			bsa=Math.round(bsa*100)/100;
			$('[name='+prefix+'BSA]').val(bsa);
		}
	}
}

function suggested_dosage(){
	var previous_administration=$('[name=PRECEDENTE_SOMM]').val();
	if(previous_administration=='1' || $('[name=PROGR]').val()!=1){
		$('#field_DOSE_TOT_SUGG').html($('[name=DOSE_TOT_SUGG_2]').val());
	}
	else{
		$('#field_DOSE_TOT_SUGG').html($('[name=DOSE_TOT_SUGG_1]').val());
	}
}

function Calc_eleg() {
	f = document.forms[0];
	el = f.elements;
	
	
	//criterio zero di eleggibilità Diasogni = Early Breast Cancer(=2)
	var c0 = (el['DIAGNOSI'].options[el['DIAGNOSI'].selectedIndex].value == '2');
	
	//primo criterio di eleggibilità pT=T0(=0) AND Neoadjuvant chemotherapy=YES(=1) o pT!=T0
	var c1 = ((el['T'].value > 1) || (el['T'].value == '1' && el['CHEMIO_NEOADIUV'].value == '1'));
	
	//secondo criterio di eleggibilità Surgery= YES (=1)
	var c2 = el['INT_CHIR'].value == 1;
	
	//terzo criterio di eleggibilità pM=M0 (=1)
	var c3 = el['M'].value == 2;
	
	//quarto criterio di eleggibilità Hercept Test=3+(=3) OR Fish/Cish=positive(=2) OR CB-11>10(>10)
	var c4 = (el['HERC_TEST'].value == 3 || el['FISH_CISH'].value == 2 || el['CB_VALUE'].value > 10);
	
	//quinto criterio di eleggibilità Neoadjuvant chemotherapy=YES(=1) OR Adjuvant chemotherapy=YES(=1)
	var c5 = ((el['CHEMIO_NEOADIUV'].value == 1) || (el['CHEMIO_ADIUV'].value == 1))
	
	if(!c0) {
		if(!confirm('Patient is not eligible\nthe answer to question "Diagnosis" is incorrect \nCancel to correct, Ok to proceed')) {
			el['DIAGNOSI'].focus();
			return false;
		} else {
			el['ELEGIBILITY'].value = 0;
			return true;
		}
	}
	if(!c1) {
		if(!confirm('Patient is not eligible\nthe answer to question "pT" is incorrect or incoherent with chemotherapy neoadjuvant\nCancel to correct, Ok to proceed')) {
			el['T'].focus();
			
			return false;
		} else {
			el['ELEGIBILITY'].value = 0;
			return true;
		}
	}
	if(!c2) {
		if(!confirm('Patient is not eligible\nthe answer to question "Surgery" is incorrect\nCancel to correct, Ok to proceed')) {
			el['INT_CHIR'].focus();
			return false;
		} else {
			el['ELEGIBILITY'].value = 0;
			return true;
		}
	}
	if(!c3) {
		if(!confirm('Patient is not eligible\nthe answer to question "pM" is incorrect\nCancel to correct, Ok to proceed')) {
			el['M'].focus();
			return false;
		} else {
			el['ELEGIBILITY'].value = 0;
			return true;
		}
	}
	if(!c4) {

		if(!confirm('Patient is not eligible\nthe answer to one of the following questions is incorrect: "Hercept Test", "CB-11" or "FISH/CISH" \nCancel to correct, Ok to proceed')) {
			el['HERC_TEST'].focus();
			return false;
		} else {
			el['ELEGIBILITY'].value = 0;
			return true;
		}
	}
	if(!c5) {
		if(!confirm('Patient is not eligible\nchemotherapy adjuvant or chemotherapy neoadjuvant data are incorrect\nCancel to correct, Ok to proceed')) {
			el['CHEMIO_NEOADIUV'].focus();
			return false;
		} else {
			el['ELEGIBILITY'].value = 0;
			return true;
		}
	}
	el['ELEGIBILITY'].value = 1;
	return true;

}


function Calc_eleg_p() {
	f = document.forms[0];
	el = f.elements;
	
	
	//criterio zero di eleggibilità Diagnosi = Early Breast Cancer(=2)
	var c0 = (el['DIAGNOSI'].options[el['DIAGNOSI'].selectedIndex].value == '2');
	
	//primo criterio di eleggibilità Hercept Test=3+(=3) OR ISH >2
	var c1 = (el['HERC_TEST'].value == 3 || el['ISH_TEST'].value == 2 );
	
	//secondo criterio di eleggibilità pM=M1, RECURRENT, RESECTABLE
	var c2 = (el['M'].value == 3 || (el['RECURRENT'].value == 1 && el['RESECTABLE'].value==2));
	
	//terzo criterio di eleggibilità PRIOR_HER2= NO
	var c3 = el['PRIOR_HER2'].value == 2;
	
	//quarto criterio di eleggibilità PRIOR_CHEMO= NO
	var c4 = el['PRIOR_CHEMO'].value == 2;
	
	//quinto criterio di eleggibilità COMBINATION1 or COMBINATION2 =1
	var c5 = (el['COMBINATION1'].checked==true || el['COMBINATION2'].checked==true);
	
	//sesto criterio di eleggibilità TRATTAMENTO=1
	var c6 = (el['TRATTAMENTO'].value==1);

	
	
	if(!c0) {
		if(!confirm('Patient is not eligible\nthe answer to question "Diagnosis" is incorrect \nCancel to correct, Ok to proceed')) {
			el['DIAGNOSI'].focus();
			return false;
		} else {
			el['ELEGIBILITY'].value = 0;
			return true;
		}
	}
	if(!c1) {
		if(!confirm('Patient is not eligible\nthe answer to question "ISH Test" or "IHC Test " is incorrect or incoherent \nCancel to correct, Ok to proceed')) {
			el['HERC_DONE'].focus();
			return false;
		} else {
			el['ELEGIBILITY'].value = 0;
			return true;
		}
	}
	if(!c2) {
		if(!confirm('Patient is not eligible\nthe answer to question "Distant metastasis" is incorrect or incoherent with "recurrent" and "resectable"\nCancel to correct, Ok to proceed')) {
			el['M'].focus();
			return false;
		} else {
			el['ELEGIBILITY'].value = 0;
			return true;
		}
	}
	if(!c3) {
		if(!confirm('Patient is not eligible\nthe answer to question "Received prior antiHER2 therapy" is incorrect\nCancel to correct, Ok to proceed')) {
			el['PRIOR_HER2'].focus();
			return false;
		} else {
			el['ELEGIBILITY'].value = 0;
			return true;
		}
	}
	if(!c4) {
		if(!confirm('Patient is not eligible\nthe answer to question "Received prior chemotherapy" is incorrect\nCancel to correct, Ok to proceed')) {
			el['PRIOR_CHEMO'].focus();
			return false;
		} else {
			el['ELEGIBILITY'].value = 0;
			return true;
		}
	}
	if(!c5) {
		if(!confirm('Patient is not eligible\n the answer to question "used in combination with" is incorrect\nCancel to correct, Ok to proceed')) {
			el['COMBINATION1'].focus();
			return false;
		} else {
			el['ELEGIBILITY'].value = 0;
			return true;
		}
	}
	if(!c6) {
		if(!confirm('Patient is not eligible\n the answer to question "line of treatment" is incorrect\nCancel to correct, Ok to proceed')) {
			el['TRATTAMENTO'].focus();
			return false;
		} else {
			el['ELEGIBILITY'].value = 0;
			return true;
		}
	}
	el['ELEGIBILITY'].value = 1;
	return true;

}


function checkHeight(){
	var prefix='';
	if($('[name=DIAGNOSI]').first().val()==4){
		return true;
	}
	if($('[name=DIAGNOSI]').first().val()==1){
		return true;
	}
	if($('[name=DIAGNOSI]').first().val()==3){
		prefix='GASTRO_';
	}
	if($('[name='+prefix+'ALTEZZA]').first().val()< 1.3 || $('[name='+prefix+'ALTEZZA]').first().val()> 1.9){
		return (confirm('You have inserted an height of: '+$('[name='+prefix+'ALTEZZA]').first().val()+' meters.\nDo you confirm it?'));
	}
	return true;
}

function checkWeight(){
	var prefix='';
	if($('[name=DIAGNOSI]').first().val()==4){
		return true;
	}
	if($('[name=DIAGNOSI]').first().val()==1){
		return true;
	}
	if($('[name=DIAGNOSI]').first().val()==3){
		prefix='GASTRO_';
	}
	if($('[name='+prefix+'PESO]').first().val()< 35 || $('[name='+prefix+'PESO]').first().val()> 100){
		return (confirm('You have inserted a weight of: '+$('[name='+prefix+'PESO]').first().val()+' Kilograms.\nDo you confirm it?'));
	}
	return true;
}

function controlla_data_sis(nome) {
	f = document.forms[0];
	el = f.elements;
	d1 = document.forms[0].elements['SYSDATE'].value;
	D1 = new Date(d1.substr(6, 4), eval(eval(d1.substr(3, 2)) - 1), d1.substr(0, 2));
	d2 = document.forms[0].elements[nome].value;
	// alert(d2);
	D2 = new Date(d2.substr(4, 4), eval(eval(d2.substr(2, 2)) - 1), d2.substr(0, 2));
	if(D1 < D2) {
		alert('Errore: data successiva alla data di oggi');
		el[nome + 'D'].focus();
		return false;
	}
	return true;
}

function check_data_sis(nome, msg) {
	f = document.forms[0];
	el = f.elements;
	d1 = document.forms[0].elements['SYSDATE'].value;
	D1 = new Date(d1.substr(6, 4), eval(eval(d1.substr(3, 2)) - 1), d1.substr(0, 2));
	d2 = document.forms[0].elements[nome].value;
	D2 = new Date(d2.substr(4, 4), eval(eval(d2.substr(2, 2)) - 1), d2.substr(0, 2));
	if(D1 < D2) {
		alert('Errore nel campo:\n' + msg + ': data successiva alla data di oggi');
		el[nome + 'D'].focus();
		return true;
	}
	return false;
}

function controlla_d1_d2_eq(d1, d2, msg) {
	D1 = new Date(d1.substr(4, 4), eval(eval(d1.substr(2, 2)) - 1), d1.substr(0, 2));
	D2 = new Date(d2.substr(4, 4), eval(eval(d2.substr(2, 2)) - 1), d2.substr(0, 2));
	if(D2 >= D1 || d1 == '' || d2 == '') {
		return true;
	}
	alert(msg);
	return false;
}

function controlla_d1_d2(d1, d2) {
	D1 = new Date(d1.substr(4, 4), eval(eval(d1.substr(2, 2)) - 1), d1.substr(0, 2));
	D2 = new Date(d2.substr(4, 4), eval(eval(d2.substr(2, 2)) - 1), d2.substr(0, 2));
	if(D2 > D1 || d1 == '' || d2 == '') {
		return true;
	}

	return false;
}

function years_num(d1, d2) {
	D1 = new Date(d1.substr(4, 4), eval(eval(d1.substr(2, 2)) - 1), d1.substr(0, 2));
	D2 = new Date(d2.substr(4, 4), eval(eval(d2.substr(2, 2)) - 1), d2.substr(0, 2));
	years = Math.floor((D2.getTime() - D1.getTime()) / (1000 * 60 * 60 * 24 * 365.25))//tiempo en milisegundos
	return years;
}

function days_num(d1, d2, nday) {
	D1 = new Date(d1.substr(4, 4), eval(eval(d1.substr(2, 2)) - 1), d1.substr(0, 2));
	D2 = new Date(d2.substr(4, 4), eval(eval(d2.substr(2, 2)) - 1), d2.substr(0, 2));
	ndays = Math.floor((D2.getTime() - D1.getTime()) / (1000 * 60 * 60 * 24))//tiempo en milisegundos
	//alert(ndays);
	ndays -= nday;
	return ndays;
}

function confirm_d1_d2(d1, d2, nday, msg) {
	D1 = new Date(d1.substr(4, 4), eval(eval(d1.substr(2, 2)) - 1), d1.substr(0, 2));
	D2 = new Date(d2.substr(4, 4), eval(eval(d2.substr(2, 2)) - 1), d2.substr(0, 2));
	ndays = Math.floor((D2.getTime() - D1.getTime()) / (1000 * 60 * 60 * 24))//tiempo en milisegundos
	if(ndays <= nday) {
		return 1;
	}
	if(!confirm(msg))
		return 0;
	return 2;
}

function confirm_d1_d2_inter(d1, d2, n1, n2, msg) {
	D1 = new Date(d1.substr(4, 4), eval(eval(d1.substr(2, 2)) - 1), d1.substr(0, 2));
	D2 = new Date(d2.substr(4, 4), eval(eval(d2.substr(2, 2)) - 1), d2.substr(0, 2));
	ndays = Math.floor((D2.getTime() - D1.getTime()) / (1000 * 60 * 60 * 24))//tiempo en milisegundos
	if(ndays >= n1 && ndays <= n2) {
		return true;
	}
	if(!confirm(msg))
		return false;
	return true;
}

function Set_dates_con() {
	f = document.forms[0];
	el = f.elements;
	dt = el['RNDDT'].value;
	if(el['RNDDT'].value == '')
		dt = el['DODDT'].value;

	for( i = 0; i < Set_dates_con.arguments.length; i++) {
		alert(dt);
		alert(Set_dates_con.arguments[i]);
		alert(el[Set_dates_con.arguments[i]].value);
		if(el[Set_dates_con.arguments[i]].value != '') {
			k = i + 1;
			nc = nconfirm_d1_d2(dt, el[Set_dates_con.arguments[i]].value, 'The administration date for dose ' + k + ' seems not correct.\nOk to Confirm, Cancel to correct');
			if(nc == 0) {
				el[Set_dates_con.arguments[i] + 'D'].focus();
				return nc;
			}
			//   dt=el[Set_dates_con.arguments[i]].value;
		}
	}
	for( i = 0; i < Set_dates_con.arguments.length; i++) {
		alert(dt);
		alert(Set_dates_con.arguments[i]);
		alert(el[Set_dates_con.arguments[i]].value);
		if(el[Set_dates_con.arguments[i]].value != '') {
			k = i + 1;
			nc = nconfirm_d1_d2(dt, el[Set_dates_con.arguments[i]].value, 'The administration date for dose ' + k + ' seems not correct.\nOk to Confirm, Cancel to correct');
			if(nc == 0) {
				el[Set_dates_con.arguments[i] + 'D'].focus();
				return nc;
			}
			dt = el[Set_dates_con.arguments[i]].value;
		}
	}
	return 1;
}
