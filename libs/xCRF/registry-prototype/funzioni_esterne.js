function checkPreviusTreat(){
	if (document.forms[0].DICPAZ.value!='' &&  document.forms[0].DICPAZ.value!=2){
		alert('The patient cannot be registered if he/she does not state he/she has not undergone a similar treatment before'); 
		return false;
		}
	else return true;
}

var textCounter=function (field,counter,maxlimit,linecounter) {
	// text width//
	var fieldWidth = parseInt(field.offsetWidth);
	var charcnt = field.value.length;
	var count = field.value.match(/\n/g);  
	var subtract=0;
	if(count){
		subtract=count.length;
		charcnt=charcnt+count.length;
	}
	/*field.value=trim(field.value);
	var re = / /g;
	for( var c = 0; re.exec(field.value); ++c );*/
	/*var charcnt=0;
	charcnt = parseInt(field.value.length)+parseInt(c);*/
	/*if(field.id=="maxcharNAT_VAR_241")
	console.log(field.id+":"+charcnt+" char;");*/
	/*console.log("maxlimit:"+maxlimit+" char;");*/
	/*if(console){
		console.log(counter);
		console.log(charcnt);
		if(count)console.log(count.length);
		console.log(maxlimit);
	}*/
	if (charcnt > maxlimit) {
	field.value = field.value.substring(0, maxlimit-subtract);
	} else {
	// progress bar percentage
	var percentage = parseInt(100 - (( maxlimit - charcnt) * 100)/maxlimit) ;
	document.getElementById(counter).style.width = parseInt((fieldWidth*percentage)/100)+"px";
	document.getElementById(counter).innerHTML="&nbsp;Used: "+percentage+"% ("+(maxlimit-charcnt)+" chars remainig)"
	// color correction on style from CCFFF -> CC0000
	setcolor(document.getElementById(counter),percentage,"background");
}
/*if(console){
	console.log(counter+' 2');
		console.log(charcnt);
		console.log(maxlimit);
	}*/
// alert(percentage+'textCounter');
} 

function IsNumber(Expression) {
	Expression = Expression.toLowerCase();
	RefString = "0123456789.-";

	if (Expression.length < 1)
		return (false);

	for ( var i = 0; i < Expression.length; i++) {
		var ch = Expression.substr(i, 1);
		var a = RefString.indexOf(ch, 0);
		if (a == -1) {
			alert("Patient code must be numeric");
			return (false);
		}
	}
	return (true);
}


function checkCheckbox(nombreCondicion,nombreCheckbox,rango){
	f = document.forms[0];
	el = f.elements;
	
	if(el[nombreCondicion].value==1){
		//El campo es si busco que haya un verdadero
		for(i=1;i<rango+1;i++){
			if(el[nombreCheckbox+i].checked)
					return true;
		}
		alert('Almeno uno tra i principi attivi deve essere selezionato');
		return false;
	}
	else{
		//busco que todos sean false
		for(i=1;i<rango+1;i++){
			if(el[nombreCheckbox+i].checked){
		//			alert(el[nombreCheckbox+i].checked);
					alert('Pincipi attivi deve essere vuoto cuando es no');
					el[nombreCheckbox+i].focus();
					return false;
				}
			}
			return true;
		}
}

function Set_farma_ter(val)
{
f=document.forms[0];
el=f.elements;

//selezionato "ospedaliera"
if (val==1)
{
   el['FARMA_TER'].value='';
   el['COD_FARMA_TER'].value='';
   el['FARMA_ALTRA'].value='';
   el['COD_FARMA_ALTRA'].value='';
   el['FARMA_TER'].disabled=false;
}
//selezionata "di domicilio", COINCIDE con residenza
if (val==2 && el['ASLDOD'].value == 2)
{
  el['FARMA_TER'].value=el['ASLR'].value;
  el['COD_FARMA_TER'].value=el['COD_ASLR'].value;
  el['FARMA_TER'].disabled=true;
   el['FARMA_ALTRA'].value='';
   el['COD_FARMA_ALTRA'].value='';
}

//selezionata "di domicilio", DIVERSA da residenza
if (val==2 && el['ASLDOD'].value == 1)
{
  el['FARMA_TER'].value=el['ASLD'].value;
  el['COD_FARMA_TER'].value=el['COD_ASLD'].value;
  el['FARMA_TER'].disabled=true;
   el['FARMA_ALTRA'].value='';
   el['COD_FARMA_ALTRA'].value='';
}

//selezionata "altra farmacia"
if (val==3)
	{
	el['FARMA_TER'].disabled=false;
   el['FARMA_TER'].value='';
   el['COD_FARMA_TER'].value='';
	}
}

function Check_rv()
{
	f=document.forms[0];
	el=f.elements;
	//if ((el['PROGR'].value>2 && el['NRIV'].value<1)||(el['PROGR'].value>6 && el['NRIV'].value<2)||(el['PROGR'].value>13 && el['NRIV'].value<3))
	//{
	//	alert('La richiesta farmaco non puo\' essere effettuata.\ne\' necessaria una rivalutazione dello stato della malattia');
	//	return false;
	//}
return true;

}

function Calc_gio()
{
	f=document.forms[0];
	el=f.elements;
	d1=el['PRIMA_RICH'].value;
	d2=el['RICHIESTA_DT'].value;
  if (d1.indexOf('/')!=-1) 
    d1=d1.substr(0,2)+d1.substr(3,2)+d1.substr(6,4);
  D1 = new Date(d1.substr(4,4), eval(eval(d1.substr(2,2))-1), d1.substr(0,2));	
  if (d2.indexOf('/')!=-1) 
    d2=d2.substr(0,2)+d1.substr(3,2)+d2.substr(6,4);
  D2 = new Date(d2.substr(4,4), eval(eval(d2.substr(2,2))-1), d2.substr(0,2));	
  ndays = Math.floor((D2.getTime() - D1.getTime()) / (1000 * 60 * 60 * 24)) ;
  el['NGIORNI'].value=ndays;
//alert(ndays);
}


function Check_minl(ct,l)
{
	f=document.forms[0];
	el=f.elements;
	if (el[ct]&&el[ct].value!=''&&el[ct].value.length<l) {
		alert('Inserire almeno '+l+ ' caratteri');
		el[ct].focus();
		return false;

	}
	return true;
}

//CONTROLLO CARATTERI SU TEXTBOX
/**
 * G.Tufano 13/04/2011
 * CONTROLLO CARATTERI SU TEXTBOX
 * 
 * v1.0
 */
//funzione di libreria TRIM
function trim(str){
    return str.replace(/^\s+|\s+$/g,"");
}

//FUNZIONE CHE CONTROLLA i caratteri ammessi in una textbox
function Check_char(ct, label){
	f=document.forms[0];
	el=f.elements;

	el[ct].value = trim(el[ct].value);
	
	reg_ex = /^([a-z]+['\s]?){1,}[a-z]$/ig
	
	stringa = el[ct].value;
	
	if( stringa.match(reg_ex))
		return true;
	else {
		alert("Attention!\nCharacter not allowed for the field "+label+"\n\nOnly letters, spaces and apostrophes are admitted. \nCharacters not allowed:\n - numbers\n - special characters (i.e. ?,@,_,*,+,-,/,à,è,ì,ò,ù)\n - spaces before and after apostrophes\n - double space or double  apostrophe\n - final apostrophe \n - initial and final spaces");
		//el[ct].focus();
		return false;
	}

}
//FINE CONTROLLO CARATTERI SU TEXTBOX

function Cod_fisc_contr_ok(cf)
{
	var controllo=true;
	f=document.forms[0];
	el=f.elements;
	el[cf].value=el[cf].value.toUpperCase();
	var codice=el[cf].value;
	if (codice && codice!='') {
		if (codice.length!=16 && codice.length!=11)
		{
			controllo=false;

		}
		else if(codice.length==11){
			//codice fiscale temporaneo
			if(!isInteger(codice))controllo=false;

		}
		else {
			//inizio controllo se caso valido di omocodia
			if(false){
				var inizioCaratteri=false;
				var valoriNumerici=codice.substr(6,2)+codice.substr(9,2)+codice.substr(12,3);
				if(!isInteger(valoriNumerici)){
					for(var i=0;i<valoriNumerici.length;i++){
						if(!isInteger(valoriNumerici.substr(i,1)))inizioCaratteri=true;
						else if(inizioCaratteri){
							controllo=false;
							break;
						}
					}
				}
			}
			//fine omocodia
			var mesiDiz=new Array();
			mesiDiz['A']='1';
			mesiDiz['B']='2';
			mesiDiz['C']='3';
			mesiDiz['D']='4';
			mesiDiz['E']='5';
			mesiDiz['H']='6';
			mesiDiz['L']='7';
			mesiDiz['M']='8';
			mesiDiz['P']='9';
			mesiDiz['R']='10';
			mesiDiz['S']='11';
			mesiDiz['T']='12';
			var anno=convertToInteger(codice.substr(6,2));
			var mese=mesiDiz[codice.substr(8,1)];
			var giorno=convertToInteger(codice.substr(9,2));

			/*if(!isInteger(anno)) {

			}else
			anno=parseInt(anno,10);
			if(!isInteger(giorno)) {

			}else
			giorno=parseInt(giorno,10);*/
			if(giorno>40){
				var sesso=2;
				giorno=giorno-40;
			}
			else var sesso=1;

			if(el['SESSO'].value!=sesso){
				controllo=false;
			}
			else if(convertToInteger(el['NASCITA_DTD'].value)!=giorno || convertToInteger(el['NASCITA_DTM'].value)!=mese || convertToInteger(el['NASCITA_DTY'].value.substr(2,2))!=anno ) {

				controllo=false;
			}
		}
		//verifica del carattere di controllo per codici di 16 cifre #### DISABILITATO
		if(false && controllo){
			var pariDiz=new Array();
			var dispariDiz=new Array();
			var totDiz=new Array();
			pariDiz['0']=0;
			pariDiz['1']=1;
			pariDiz['2']=2;
			pariDiz['3']=3;
			pariDiz['4']=4;
			pariDiz['5']=5;
			pariDiz['6']=6;
			pariDiz['7']=7;
			pariDiz['8']=8;
			pariDiz['9']=9;
			pariDiz['A']=0;
			pariDiz['B']=1;
			pariDiz['C']=2;
			pariDiz['D']=3;
			pariDiz['E']=4;
			pariDiz['F']=5;
			pariDiz['G']=6;
			pariDiz['H']=7;
			pariDiz['I']=8;
			pariDiz['J']=9;
			pariDiz['K']=10;
			pariDiz['L']=11;
			pariDiz['M']=12;
			pariDiz['N']=13;
			pariDiz['O']=14;
			pariDiz['P']=15;
			pariDiz['Q']=16;
			pariDiz['R']=17;
			pariDiz['S']=18;
			pariDiz['T']=19;
			pariDiz['U']=20;
			pariDiz['V']=21;
			pariDiz['W']=22;
			pariDiz['X']=23;
			pariDiz['Y']=24;
			pariDiz['Z']=25;

			dispariDiz['0']=1;
			dispariDiz['1']=0;
			dispariDiz['2']=5;
			dispariDiz['3']=7;
			dispariDiz['4']=9;
			dispariDiz['5']=13;
			dispariDiz['6']=15;
			dispariDiz['7']=17;
			dispariDiz['8']=19;
			dispariDiz['9']=21;
			dispariDiz['A']=1;
			dispariDiz['B']=0;
			dispariDiz['C']=5;
			dispariDiz['D']=7;
			dispariDiz['E']=9;
			dispariDiz['F']=13;
			dispariDiz['G']=15;
			dispariDiz['H']=17;
			dispariDiz['I']=19;
			dispariDiz['J']=21;
			dispariDiz['K']=2;
			dispariDiz['L']=4;
			dispariDiz['M']=18;
			dispariDiz['N']=20;
			dispariDiz['O']=11;
			dispariDiz['P']=3;
			dispariDiz['Q']=6;
			dispariDiz['R']=8;
			dispariDiz['S']=12;
			dispariDiz['T']=14;
			dispariDiz['U']=16;
			dispariDiz['V']=10;
			dispariDiz['W']=22;
			dispariDiz['X']=25;
			dispariDiz['Y']=24;
			dispariDiz['Z']=23;

			totDiz[0]='A';
			totDiz[1]='B';
			totDiz[2]='C';
			totDiz[3]='D';
			totDiz[4]='E';
			totDiz[5]='F';
			totDiz[6]='G';
			totDiz[7]='H';
			totDiz[8]='I';
			totDiz[9]='J';
			totDiz[10]='K';
			totDiz[11]='L';
			totDiz[12]='M';
			totDiz[13]='N';
			totDiz[14]='O';
			totDiz[15]='P';
			totDiz[16]='Q';
			totDiz[17]='R';
			totDiz[18]='S';
			totDiz[19]='T';
			totDiz[20]='U';
			totDiz[21]='V';
			totDiz[22]='W';
			totDiz[23]='X';
			totDiz[24]='Y';
			totDiz[25]='Z';



			var totaleCaratteri=0;
			for(var i=0;i<codice.length-1;i++){
				if(i%2){
					totaleCaratteri+=pariDiz[codice.substr(i,1)];
				}
				else {
					totaleCaratteri+=dispariDiz[codice.substr(i,1)];
				}
			}

			var carattereControllo=totDiz[totaleCaratteri%26];
			if(carattereControllo!=codice.substr(15,1)){
				controllo=false;
			}



		}
		//fine verifica carattere di controllo
	}




	if(controllo){


		return true;
	}
	else{
		if(!confirm('Attenzione!!! Il codice fiscale risulta essere errato\nPremere Ok per continuare con l\'invio.\nPremere Annulla per correggere il dato.')){
			el[cf].focus();
			return false;
		}
		else{
			return true;
		}
	}
}


function Reg_check()
{
f=document.forms[0];
el=f.elements;
nch=0;
if (!Check_minl('COGNOME',2)) return false;
if (!Check_minl('NOME',2)) return false;
if (!Check_char('COGNOME')) return false;
if (!Check_char('NOME')) return false;
//if (!Cod_fisc_contr('CODFISC')) return false;
//if (el['ESTERO'].checked &&el['COMUNE_NASC'].value!='')
//{
 //alert('Se e\' indicato Comune di Nascita, Estero non deve essere selezionato');
 //el['COMUNE_NASC'].focus();
 //return false;
//}
//if (!el['ESTERO'].checked &&el['COMUNE_NASC'].value=='')
//{
 //alert('Indicate Comune di Nascita o estero');
 //el['COMUNE_NASC'].focus();
 //return false;
//}
return true;
}



function Calc_Media() {
	f = document.forms[0];
	el = f.elements;
	if (el['PAS'].value != '' && el['PAD'].value != '') {
		pas = el['PAS'].value - 0;
		pad = el['PAD'].value - 0;
		px = (pas - pad) / 3;
		// alert(px);
		pam = px + pad;
		// alert(pam);
		el['PAM'].value = Math.round(pam * 100) / 100;
		el['PAM'].disabled = true;
	}
}


function Calc_Tips() {
	f = document.forms[0];
	el = f.elements;
	if (el['PROCEDE'].value == 2
			&& (el['TIPS'].value == 1 || el['NO_TIPS'].value == 1)) {
		el['TIPS_HID'].value = 1;
	} else
		el['TIPS_HID'].value = 0;
}





function EndPoint() {
	f = document.forms[0];
	el = f.elements;

	if (el['ASCITE_REFRATTARIA'].value == 1) {
		el['ASCITE_REFRATTARIA'].focus();
		return confirm('ATTENZIONE!\nIl paziente ha raggiunto un endpoint primario.\nConfermi che sono stati rispettati i criteri IAC \nOk to confirm, Cancel to modify');
	}
	return true;
}

function Set_unita() {
	f = document.forms[0];
	el = f.elements;

	if (el['GLICEMIA'].value != '')
		el['GLICEMIA1'].value = 1;

}

function Set_emo() {
	f = document.forms[0];
	el = f.elements;
	if (el['N_EMORRAGIA_DIG'].value >= 1)
		el['EMORRAGIA1'].value = 1;
	if (el['N_EMORRAGIA_DIG'].value >= 2)
		el['EMORRAGIA1'].value = 2;
	if (el['N_EMORRAGIA_DIG'].value >= 3)
		el['EMORRAGIA1'].value = 3;
	if (el['N_EMORRAGIA_DIG'].value < 1)
		el['EMORRAGIA1'].value = 0;
}











function Set_eta12()
{
	f=document.forms[0];
	el=f.elements;
	if (el['ETA'].value<12)
	{
		alert('Attention!!!\n Patient cannot prooceed the screening because to be eligible patient age, at screening evaluation date, must be 12 and above');
 el['VISITDTD'].focus();
 return false;
	}
	
	return true;
}
	
 





function Set_sae_cont() {
	f = document.forms[0];
	el = f.elements;
	nu = 0;
	for (i = 1; i < 6; i++)
		if (el['GRAVITA' + i].checked)
			nu++;
	if (el['GRAVITA'][0].checked && nu == 0) {
		alert('If serious, reason for seriousness must be selected');
		el['GRAVITA'][0].focus();
		return false;
	}
	if (el['GRAVITA'][1].checked && nu != 0) {
		alert('If not serious, reason for seriousness must not be selected');
		el['GRAVITA'][1].focus();
		return false;
	}

	if ((el['GRAVITA1'].checked || el['ESITO'][4].checked)
			&& el['DECESSO_DT'].value == '') {
		alert('If death is selected, date of death must be filled');
		el['DECESSO_DTD'].focus();
		return false;
	}
	if ((el['GRAVITA1'].checked || el['ESITO'][4].checked)
			&& el['CAUSA_DEC'].selectedIndex == -1) {
		alert('If death is selected, cause of death must be filled');
		el['CAUSA_DEC'].focus();
		return false;
	}

	return true;

}

function Set_sae_cont2(){
	f = document.forms[0];
	el = f.elements;
	nu = 0;
	for (i = 1; i < 6; i++)
		if (el['GRAVITA' + i].checked)
			nu++;
	if (el['GRAVITA'][1].checked && nu != 0) {
		alert('Se non grave deve essere vuoto');
		el['GRAVITA'][1].focus();
		return false;
	}
	
	return true;	
	}

function Check_val(campo, max, min, txt) {
	f = document.forms[0];
	el = f.elements;
	if (el[campo] && el[campo].value
			&& (el[campo].value > max || el[campo].value < min))
		// if (!confirm('Il valore inserito nel campo '+txt+' e\' fuori del range
		// '+min+' - '+max+'.\nOk to confirm, Cancel to modify'))
		if (!confirm('Value inserted in ' + txt + ' is out of range ' + min
				+ ' - ' + max + '.\nReset to correct, Ok to accept')) {
			el[campo].value = '';
			el[campo].focus();
		}
}

function Calc_BMI() {
	f = document.forms[0];
	el = f.elements;
	// alert('ddd');
	alt = el['HEIGHT'].value / 100;
	if (el['WEIGHT'].value != 0 && el['HEIGHT'].value != 0)
		el['BMI'].value = (Math.round((el['WEIGHT'].value / (alt * alt)) * 100)) / 100;
	else
		el['BMI'].value = '';
	el['BMI'].disabled = true;
}

function ControlEsam() {
	f = document.forms[0];
	D1 = f.ESAMI_DT.value;
	// alert ('prova');
	d1 = new Date(D1.substr(4, 4), eval(eval(D1.substr(2, 2)) - 1), D1.substr(
			0, 2));
	d1 = d1.getTime();
	// alert (d1);

	D2 = f.VISITA_DT.value;
	d2 = new Date(D2.substr(4, 4), eval(eval(D2.substr(2, 2)) - 1), D2.substr(
			0, 2));
	d2 = d2.getTime();
	// alert (D2);
	if (d2 < d1) {
		diff = d1 - d2;
		diff = diff / 1000;
		diff = diff / 60;
		diff = diff / 60;
		// alert (diff);
		if (diff > 168) {
			return confirm('Attenzione!!!\nLa data degli esami e\' sucessiva di più di 7 gg alla data di visita\nOk per confermare Annulla per correggere');
		}
	}
	if (d1 < d2) {
		diff = d2 - d1;
		diff = diff / 1000;
		diff = diff / 60;
		diff = diff / 60;
		// alert (diff);
		if (diff > 168) {
			alert('Attenzione!!!\nLa data degli esami non puo\' essere precedente più di 7 giorni dalla data di visita');
			return false;
		}
	}
	// return confirm ('vuoi procedere?');
	return true;
}

function ControlVisita() {
	f = document.forms[0];
	D1 = f.VISIT_PREC.value;
	// alert ('prova');
	d1 = new Date(D1.substr(4, 4), eval(eval(D1.substr(2, 2)) - 1), D1.substr(
			0, 2));
	d1 = d1.getTime();
	// alert (d1);

	D2 = f.VISITA_DT.value;
	d2 = new Date(D2.substr(4, 4), eval(eval(D2.substr(2, 2)) - 1), D2.substr(
			0, 2));
	d2 = d2.getTime();
	// alert (D2);
	if ((d1 != '' && d2 != '') && (d2 < d1)) {
		diff = d1 - d2;
		diff = diff / 1000;
		diff = diff / 60;
		diff = diff / 60;
		// alert (diff);
		if (diff > 0) {
			alert('Attenzione!!!\nLa data di visita non puo\' essere precedente a quella dell\'ultima visita inserita');
			return false;
		}
	}
	if (d1 != '' && d2 != '' && d1 == d2) {
		// diff=d2-d1;
		// diff=diff/1000;
		// diff=diff/60;
		// diff=diff/60;
		// if (diff=0)

		return confirm('Attenzione!!!\nLa data di visita e\' uguale alla data della visita precedente. \nOk per confermare Annulla per correggere');

	}

	if ((d1 != '' && d2 != '') && (d1 < d2)) {
		diff = d2 - d1;
		diff = diff / 1000;
		diff = diff / 60;
		diff = diff / 60;
		// alert (diff);
		if (diff >= 1440) {
			return confirm('Attenzione!!!\nSono passati più di 60 giorni dall\'ultima visita. Se il paziente ha saltato una visita, ricordarsi di inserire \nVisita effettuata=NO   \nOk per confermare Annulla per correggere');

		}
	}
	if (d1 < d2) {
		diff = d2 - d1;
		diff = diff / 1000;
		diff = diff / 60;
		diff = diff / 60;
		// alert (diff);
		if (diff > 960) {
			return confirm('Attenzione!!!\nSono passati più di 40 giorni dall\'ultima visita. Confermi che il paziente non abbia saltato una visita?   \nOk per confermare Annulla per correggere');

		}
	}

	// return confirm ('vuoi procedere?');
	return true;
}



function Set_age() {
	f = document.forms[0];
	el = f.elements;

	if (el['ETA'].value >= 12)
		el['INCLUSION2'].value = 1;
		el['INCLUSION7'].value = 1;

}

function Set_failure() {
	f = document.forms[0];
	el = f.elements;

	el['INCLUSION7'].value = 1;

}


function Set_prot() {
	f = document.forms[0];
	el = f.elements;

	if (el['DIAG_HIV'][el['DIAG_HIV'].selectedIndex].value == 1
			&& el['DIAG_TB'][el['DIAG_TB'].selectedIndex].value != 1
			&& el['DIAG_MAL'][el['DIAG_MAL'].selectedIndex].value != 1)
		el['PROTOCOLLO'].value = 1;

	if (el['DIAG_HIV'][el['DIAG_HIV'].selectedIndex].value == 1
			&& el['DIAG_TB'][el['DIAG_TB'].selectedIndex].value == 1
			&& el['DIAG_MAL'][el['DIAG_MAL'].selectedIndex].value != 1)
		el['PROTOCOLLO'].value = 2;

	if (el['DIAG_HIV'][el['DIAG_HIV'].selectedIndex].value == 1
			&& el['DIAG_TB'][el['DIAG_TB'].selectedIndex].value == 1
			&& el['DIAG_MAL'][el['DIAG_MAL'].selectedIndex].value == 1)
		el['PROTOCOLLO'].value = 3;

	if (el['DIAG_HIV'][el['DIAG_HIV'].selectedIndex].value != 1
			&& el['DIAG_TB'][el['DIAG_TB'].selectedIndex].value == 1
			&& el['DIAG_MAL'][el['DIAG_MAL'].selectedIndex].value == 1)
		el['PROTOCOLLO'].value = 4;

	if (el['DIAG_HIV'][el['DIAG_HIV'].selectedIndex].value != 1
			&& el['DIAG_TB'][el['DIAG_TB'].selectedIndex].value != 1
			&& el['DIAG_MAL'][el['DIAG_MAL'].selectedIndex].value == 1)
		el['PROTOCOLLO'].value = 5;

	if (el['DIAG_HIV'][el['DIAG_HIV'].selectedIndex].value != 1
			&& el['DIAG_TB'][el['DIAG_TB'].selectedIndex].value == 1
			&& el['DIAG_MAL'][el['DIAG_MAL'].selectedIndex].value != 1)
		el['PROTOCOLLO'].value = 6;

	if (el['DIAG_HIV'][el['DIAG_HIV'].selectedIndex].value == 1
			&& el['DIAG_TB'][el['DIAG_TB'].selectedIndex].value != 1
			&& el['DIAG_MAL'][el['DIAG_MAL'].selectedIndex].value == 1)
		el['PROTOCOLLO'].value = 7;

}

function Set_trial()
{
	f=document.forms[0];
	el=f.elements;
	if (el['ENROLLED_OT'][el['ENROLLED_OT'].selectedIndex].value==1)
	{
		if (!confirm('Attention! If the patient is enrolled in another trial it is necessary to discuss with MRC CTU before randomisation'))
		{
			el['ENROLLED_OT'].focus();
			return false;
		}
	}
	return true;
}


function Set_metro()
{
	f=document.forms[0];
	el=f.elements;

//if (el['FARMACI_DMARD_SPEC1'].checked && el['FARMACI_DMARD_FINE'].value== 1 && el['ASSOCIA_METOTRE'].value== 1 )
//{
// alert('Attenzione! In precedenza e\' stato dichiarato che la somministrazione del farmaco Methotrexate e\' stato interrotto per assenza di risposta, non puo\' quindi essere selezionato in associazione con Cimzia');
// el['FARMACI_DMARD_FINE'].focus();
// return false;
//}

if (el['FARMACI_DMARD_SPEC1'].checked && el['FARMACI_DMARD_FINE'].value== 2 && el['ASSOCIA_METOTRE'].value== 1 )
{
 alert('Attenzione! In precedenza e\' stato dichiarato che la somministrazione del farmaco Methotrexate e\' stato interrotto per intolleranza, non puo\' quindi essere selezionato in associazione con Cimzia');
 el['FARMACI_DMARD_FINE'].focus();
 return false;
}



return true;
}

















function Set_ini_val()
{
f=document.forms[0];
el=f.elements;
eln=el.length;
for (i=0;i<eln;i++) {
	nome=el[i].name;
  if (el['NEW_'+nome])
  {
    if (el[i].value=='')el[i].value=el['NEW_'+nome].value;
   
  }
}
}








function Controldiag() {
	f = document.forms[0];
	D1 = f.PRIMA_DIAG_DT.value;
	 //alert ('prova');
	d1 = new Date(D1.substr(4, 4), eval(eval(D1.substr(2, 2)) - 1), D1.substr(
			0, 2));
	d1 = d1.getTime();
	// alert (d1);

	D2 = f.DIAGDT.value;
	d2 = new Date(D2.substr(4, 4), eval(eval(D2.substr(2, 2)) - 1), D2.substr(
			0, 2));
	d2 = d2.getTime();
	// alert (d2);
	if (d2 < d1) {
			return confirm('Attenzione!!!\nLa data di diagnosi e\' precedente al 1 novembre 2006 conferma il dato? \nPremere Ok per continuare.Premere Annulla per correggere');
		}
	
	

	// return confirm ('vuoi procedere?');
	return false;
}

/*
 * code = 0 se si utilizza la data calcolata con Javascript. **ATTENZIONE** questo metodo � insicuro, in quanto si basa sull'ora settata nel computer dell'utente,
 * 			che potrebbe essere sbagliata!
 * code = 1 se si utilizza un campo hidden per il calcolo della seconda data (tipo TODAY_DT = sysdate)
 * code = 2 se si utilizza un campo da compilare per il calcolo della seconda data (tipo VALUT_DT) 
 * nome = il nome dell'eventuale campo hidden contenente la seconda data (formato GGMMAAAA)
 * veta = nome del campo hidden da valorizzare con l'eta' del paziente 
 * al = 1 se bisogna mostrare un avviso (alert) per problemi relativi all'eta' 
 * eta_minima = limite minimo di eta' per l'eleggibilita'
 * 
 * PS: si suppone che esista il campo NASCITA_DT con la data di nascita
 * 
 * vers. 1.5 08/03/2011
 * 
 */
function Check_nascita(code, nome, veta, al, eta_minima){
	f=document.forms[0];
	el=f.elements;
	
	d_nasc=el['NASCITA_DT'].value;
	
	if (d_nasc.indexOf('/')!=-1)
		d_nasc=d_nasc.substr(0,2)+d_nasc.substr(3,2)+d_nasc.substr(6,4);


	Data_nascita = new Date(d_nasc.substr(4,4), eval(eval(d_nasc.substr(2,2))-1), d_nasc.substr(0,2));
//	Data_oggi = new Date();

	switch(code){
		case 0: Data_confr = new Date();
				break;
		case 1:	// la data odierna la prendo dal sistema per evitare problemi nel caso
				// in cui
				// l'utente abbia settato la data errata nel suo pc
				//il formato � DDMMAAAA
				d_cfr = el[nome].value;
				Data_confr = new Date(d_cfr.substr(4,4), eval(eval(d_cfr.substr(2,2))-1), d_cfr.substr(0,2));
				break;
		
		case 2:	//la data la prendo da un campo XMR compilato, tipo VALUT_DT, quindi nel formato nome_D, nome_M, nome_Y
				campo_giorno = nome + "D";
				campo_mese = nome + "M";
				campo_anno = nome + "Y";
				
				gg = parseInt(el[campo_giorno].value,10);
				mm = parseInt(el[campo_mese].value,10);
				aaaa = parseInt(el[campo_anno].value,10);
				
				if (isNaN(gg) || isNaN(mm) || isNaN(aaaa) || gg<1 || gg>31 || mm <1 || mm>12){
					alert("Attenzione la data inserita nel campo "+nome+" non e' valida");
					el[veta].value = '';
					return false;
				}
				
//				gg = (gg > 9)? gg : '0'+ gg;
//				mm = (mm > 9)? mm : '0'+ mm;

				Data_confr = new Date(aaaa, mm-1, gg);
				break;
		default: break;
			
	}
	
	eta_diag = Math.floor((Data_confr.getTime() - Data_nascita.getTime()) / (1000 * 60 * 60 * 24*365.25)) ;
	
	// INSERISCO IL VALORE SOLO SE eta_diag � un numero valido
	if (isNaN(eta_diag)==false ){
		el[veta].value = eta_diag;
	}
	else{
		el[veta].value = '';
	}
	

	if (el[veta].value < eta_minima)
			el['ETA_ELEG'].value='';
	 else
	 		el['ETA_ELEG'].value=1;
	if (el['ETA_ELEG'].value != 1 && al) {
		alert('Patient is not eligible because is less than  '+eta_minima+' years old.');
		return false;
	}
  return true;
}

function Set_asl(){
	f=document.forms[0];
	el=f.elements;
	if (el['ASLDOD'][el['ASLDOD'].selectedIndex].value==2)
	 el['COD_ASLD'].value=el['COD_ASLR'].value;
	
}





function	sistema_numero(numero){
	return parseInt(numero,10);
}



function Set_dose() {
	f = document.forms[0];
	el = f.elements;

	
//	if (el['DOSE_CICLO'].value == 1 && (el['DOSE_DIE'].value != 400))
//	{
//		alert('Attenzione!\nSe la dose/ciclo richiesta = 200 mg allora la dose totale richiesta puo\' essere solo 400mg ');
//		el['DOSE_DIE'].focus();
//	  return false;
//	}
	
	if (/*el['DOSE_CICLO'].value == 2 && */(el['DOSE_DIE'].value != 400 && el['DOSE_DIE'].value != 800 && el['DOSE_DIE'].value != 1200)) 
	{
//		alert('Attenzione!\nSe la dose/ciclo richiesta = 400 mg allora la dose totale richiesta puo\' essere solo 400 o 800 o 1200mg ');
		alert('Attenzione!\nLa dose totale richiesta puo\' essere solo 400 o 800 o 1200mg ');
		el['DOSE_DIE'].focus();
	  return false;
	}
	
	return true;
}





function Set_inf() {
	f = document.forms[0];
	el = f.elements;

	if (el['INFEZIONI'][el['INFEZIONI'].selectedIndex].value != 2) {
		alert('La richiesta farmaco non puo\' essere effettuata. Presenza di infezioni gravi o  sospette');
		el['INFEZIONI'].focus();
	return false;
	}
	return true;
}


function Set_prosegue() {
	f = document.forms[0];
	el = f.elements;

	if (el['PROSEGUE'].selectedIndex == 2) {
		alert('Compilare la scheda di Fine trattamento');
		return false;
	}
	return true;
}

function Set_acr() {
	f = document.forms[0];
	el = f.elements;

	if (el['ACR_VAL'].value < 20) {
		alert('Attenzione, se Valore ACR e\' inferiore a 20 il trattamento dovrebbe essere bloccato');
		return false;
	}
	return true;
}


function Check_ricdt() {
	f = document.forms[0];
	el = f.elements;
	d2 = el['RICHIESTA_DT'].value;
	d1 = el['PREV_RICH'].value;
	if (d1 && d2) {
		if (d1.indexOf('/') != -1)
			d1 = d1.substr(0, 2) + d1.substr(3, 2) + d1.substr(6, 4);
		// alert(d1);
		D1 = new Date(d1.substr(4, 4), eval(eval(d1.substr(2, 2)) - 1), d1
				.substr(0, 2));
		if (d2.indexOf('/') != -1)
			d2 = d2.substr(0, 2) + d1.substr(3, 2) + d2.substr(6, 4);
		// alert(d2);
		D2 = new Date(d2.substr(4, 4), eval(eval(d2.substr(2, 2)) - 1), d2
				.substr(0, 2));
		if (D1>=D2 && el['PROGR'].value >= 3)
	{
		 el['RICHIESTA_DTD'].focus();
		return alert('Date of drug request must be after date of previous drug request');

 return false;
	}
}
return true;
	}
	

function Set_fev() {
	f = document.forms[0];
	el = f.elements;
	if (el['GASTRO_MODALITA_VALUE'].value < 50) {
		el['FEV'].value = 2
	}
	if (el['GASTRO_MODALITA_VALUE'].value >= 50) {
		el['FEV'].value = 1
	}
	
	return true;
}
	

function eleg_colon() {
	f = document.forms[0];
	el = f.elements;

	if (el['DIAGNOSI'].value == 5 && el['METASTATIC'].value != 1) {

		if (!confirm('The patient is not eligible because Metastatic disease = NO \nOk to confirm, Cancel to modify')) {
			el['METASTATIC'].focus();
			return false;
		}
	}
	if (el['DIAGNOSI'].value == 5 && el['IN_COMBINATION_COLORECT'].value == 1) {

		if (!confirm('The patient is not eligible because Bevacizumab will be administered in combination with fluoropirimidine = NO \nOk to confirm, Cancel to modify')) {
			el['IN_COMBINATION_COLORECT'].focus();
			return false;
		}
	}
	if (el['DIAGNOSI'].value == 5 && el['LINE_TREATMENT'].value == 3) {

		if (!confirm('The patient is not eligible because Treatment line planned for metastatic disease = FOLLOWING \nOk to confirm, Cancel to modify')) {
			el['LINE_TREATMENT'].focus();
			return false;
		}
	}
	if (el['DIAGNOSI'].value == 5 && el['AVASTIN_FIRST'].value != '' && el['AVASTIN_FIRST'].value != 2) {

		if (!confirm('The patient is not eligible because Has the patient already received AVASTIN i first line = YES \nOk to confirm, Cancel to modify')) {
			el['AVASTIN_FIRST'].focus();
			return false;
		}
	}
	

	return true;
}

function eleg_breast() {
	f = document.forms[0];
	el = f.elements;

	if (el['DIAGNOSI'].value == 9 && el['CHEMO_METAST'].value == 1) {

		if (!confirm('The patient is not eligible because Has the patient already received chemotherapy for metastatic disease = NO \nOk to confirm, Cancel to modify')) {
			el['CHEMO_METAST'].focus();
			return false;
		}
	}
	if (el['DIAGNOSI'].value == 9 && el['CHEMO_DRUG'].value != 1) {

		if (!confirm('The patient is not eligible because The drug will be administeredin conjunction with = Other \nOk to confirm, Cancel to modify')) {
			el['CHEMO_DRUG'].focus();
			return false;
		}
	}
	
	return true;
}


function eleg_lung() {
	f = document.forms[0];
	el = f.elements;

	if (el['DIAGNOSI'].value == 8 && el['RESECTABLE'].value == 1) {

		if (!confirm('The patient is not eligible because Resectable = YES \nOk to confirm, Cancel to modify')) {
			el['RESECTABLE'].focus();
			return false;
		}
	}
	if (el['DIAGNOSI'].value == 8 && el['SQUAMOUS_CELL_CARCINOMA'].value == 1) {

		if (!confirm('The patient is not eligible because squamous Cell Carcinoma = YES \nOk to confirm, Cancel to modify')) {
			el['SQUAMOUS_CELL_CARCINOMA'].focus();
			return false;
		}
	}
	if (el['DIAGNOSI'].value == 8 && el['PREVIOUS_TREATMENT'].value == 1) {

		if (!confirm('The patient is not eligible because Previous treatment for metastatic disease = YES \nOk to confirm, Cancel to modify')) {
			el['PREVIOUS_TREATMENT'].focus();
			return false;
		}
	}
	if (el['DIAGNOSI'].value == 8 && el['ADDITION_CHEMO'].value == 2) {

		if (!confirm('The patient is not eligible because The drug will be administered in addition to platinum-based chemotherapy = YES \nOk to confirm, Cancel to modify')) {
			el['ADDITION_CHEMO'].focus();
			return false;
		}
	}
	if (el['DIAGNOSI'].value == 8 && el['ELEG_LUNG_H1'].value != 1) {

		if (!confirm('The patient is not eligible because At the question Are other chemotherapy drugs associated neither Paclitaxel nor Gemcitabine have been selected  \nOk to confirm, Cancel to modify')) {
			return false;
		}
	}
	
	return true;
}


function eleg_renal() {
	f = document.forms[0];
	el = f.elements;

	if (el['DIAGNOSI'].value == 10 && el['NEPHRECTOMY'].value == 2) {

		if (!confirm('The patient is not eligible because Previous nephrectomy = NO \nOk to confirm, Cancel to modify')) {
			el['NEPHRECTOMY'].focus();
			return false;
		}
	}
	if (el['DIAGNOSI'].value == 10 && el['TREAT_METAST_ADVAN'].value == 1) {

		if (!confirm('The patient is not eligible because Previous chemotherapy for advanced and / or metastatic disease = YES \nOk to confirm, Cancel to modify')) {
			el['TREAT_METAST_ADVAN'].focus();
			return false;
		}
	}
	if (el['DIAGNOSI'].value == 10 && el['INTERFERON_ALPHA'].value == 2) {

		if (!confirm('The patient is not eligible because Use in conjunction with interferon alpha 2a = NO \nOk to confirm, Cancel to modify')) {
			el['INTERFERON_ALPHA'].focus();
			return false;
		}
	}
	
	return true;
}