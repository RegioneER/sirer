function submitform_send() {
f=document.forms[0];
el=f.elements;
specifiche='A=ON&L=0&F=0';


c1=''+	
'<<r###TIPOF###Tipo Farmacia>>'+ 
'<<si###QUAL_RESP###Titolo del medico Responsabile>>'+ 
'<<t###NOME_RESP###Nome del medico Responsabile>>'+ 
'<<t###COGNOME_RESP###Cognome del medico Responsabile>>'+ 
'<<t###NOME###Nome del medico Referente>>'+ 
'<<t###COGNOME###Cognome del medico Referente>>'+ 
'<<si###QUAL###Qualifica del Medico Referente>>'+ 
'<<t###AZIENDA_ENTE###Ospedale>>'+ 
'<<si###DISCIPL###Reparto>>'+ 
'<<t###DIVISIONE###Division>>'+ 
'<<si###SEZIONE###Sezione>>'+ 
'<<t###VIA###Indirizzo del Medico>>'+ 
'<<np00###CAP###CAP>>'+ 
'<<t###CITTA###Citta>>'+ 
'<<np00###TELEFONO###Telefono>>'+ 
'<<np00###FAX###Fax>>'+ 
'<<t###EMAIL1###email>>'+ 
'<<t###EMAIL2###email>>'+ 
'<<si###FARMA###Farmacista>>'+
//'<<t###EMAIL_FARM2###email farmacista>>'+
'';

rc=contr(c1,specifiche);
//alert();
if (rc) {return false}

if (!rc && el['TELEFONO'].value!='' &&(!el['TELEFONO'].value.match(/\d+/) && !el['TELEFONO'].value.match(/\d+[\/\.\-\ ]+/) )){
        alert ('ATTENZIONE!\nTelefono non valido,\nsono ammessi solo numeri e \nquesti tipi di caratteri: \/  \.  \-   ');
        rc=1;
}
if (rc) {return false}

//controllo nome e cognome

if (!rc && el['NOME'].value.match(/([0-9])+/i)) {
	alert ('Il nome non puo\' contenere caratteri numerici');
	el['NOME'].focus();
	return false;
}


if ((!rc) && el['COGNOME'].value.match(/([0-9])+/i)) {
	alert ('Il cognome non puo\' contenere caratteri numerici');
	el['COGNOME'].focus();
	return false;
}

if (!rc && el['NOME_RESP'].value.match(/([0-9])+/i)) {
	alert ('Il nome non puo\' contenere caratteri numerici');
	el['NOME_RESP'].focus();
	return false;
}


if ((!rc) && el['COGNOME_RESP'].value.match(/([0-9])+/i)) {
	alert ('Il cognome non puo\' contenere caratteri numerici');
	el['COGNOME_RESP'].focus();
	return false;
}

if (!rc && el['FAX'].value!='' &&(!el['FAX'].value.match(/\d+/) && !el['FAX'].value.match(/\d+[\/\.\-\ ]+/) )){
        alert ('ATTENZIONE!\nFax non valido,\nsono ammessi solo numeri e \nquesti tipi di caratteri: \/  \.  \-   ');
        rc=1;
}
if (rc) {return false}

//if (!rc && (!el['EMAIL'].value.match(/^.*\@.*\..*/) || el['EMAIL'].value.match(/[\;\|]+/))){
//        alert ('ATTENZIONE!\nIndirizzo email del medico non valido!');
//        rc=1;
//}
//if (rc) {return false}
//
//if (!rc && (!el['EMAIL_FARM'].value.match(/^.*\@.*\..*/) || el['EMAIL_FARM'].value.match(/[\;\|]+/))){
//        alert ('ATTENZIONE!\nIndirizzo email del farmacista non valido!');
//        rc=1;
//}
if (rc) {return false}

if(!rc){
document.forms[0].EMAIL.value=document.forms[0].EMAIL1.value+'\@'+document.forms[0].EMAIL2.value;	
document.forms[0].USERID.value=document.forms[0].USERID_1.value + document.forms[0].USERID_2.value;
//alert(document.forms[0].USERID.value);
//document.forms[0].EMAIL_FARM.value=document.forms[0].EMAIL_FARM1.value+'\@'+document.forms[0].EMAIL_FARM2.value;	
}
prepara_decode();
 //document.forms[0].INVIOCO.value='1';
 document.forms[0].action='/cgi-bin/registra_utenti/save_esam'; 
 document.forms[0].submit();
// *******
}

function Set_rep()
{
document.forms[0].USERID_2.value=document.forms[0].DISCIPL[document.forms[0].DISCIPL.selectedIndex].value;
}

function Clear_farm()
{
for(i=document.forms[0]['FARMA'].options.length-1;i>=0;i--){
    document.forms[0]['FARMA'].options[i]=null;
//  document.forms[0]['FARMA'].options[i]=null;
}
}



function Set_StFarm()
{
sbianca('AZIENDA_ENTE','FAZIENDA_ENTE','VIA','CITTA','CAP');
Clear_farm();
if (document.forms[0]['TIPOF'][0].checked){Hide('ESTIN');Hide('EST');}
if (document.forms[0]['TIPOF'][1].checked){Show('ESTIN');Show('EST');}
}