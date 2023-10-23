function submitform_send() {
f=document.forms[0];
el=f.elements;
specifiche='A=ON&L=0&F=0';


c1=''+	
'<<t###NOMEDIR###Direttore: Nome>>'+ 
'<<t###COGNOMEDIR###Direttore: Cognome>>'+ 
'<<d00###FIRMDT###Firmata in data>>'+ 
'<<fd00###RICDT###Ricevuta in data>>'+ 
'';

rc=contr(c1,specifiche);
//alert();
if (rc) {return false}

//prepara_decode();
 document.forms[0].action='/user_reg.php'; 
 document.forms[0].submit();
// *******
}


