//---------------------------------------------------------------
//	function getParameterFromUrl(parametro) 
//	
//	function gup (parametro)
//
//	function golink(parametro)
//-----------------------------------------------------------------

function getParameterFromUrl(parametro) 
{
	q = location.search;
	qq = q.split("&");
	for (var c=0; c<qq.length; ++c)
	{
		if (qq[c].indexOf(parametro)!=-1) 
		{
			qqq = qq[c].split("=");return qqq[1];
		};
	}	
} 


function gup (name)
{
	name = name.replace(/[\[]/,"\\\[").replace(/[\]]/,"\\\]");  
	var regexS = "[\\?&]"+name+"=([^&#]*)";  
	var regex = new RegExp( regexS );  
	var results = regex.exec( window.location.href );  
	if( results == null )    
		return "";  
	else    
		return results[1];
}


function golink(dest_xml)
{
	centerJS = new Number(gup('CENTER'));		
	codpatJS = new Number(gup('CODPAT'));		
	visitnumJS = new Number(gup('VISITNUM'));		
	esamJS = new Number(gup('ESAM'));		
	progrJS = new Number(gup('PROGR'));		
	
	document.location.href='./index.php?CENTER='+centerJS+'&CODPAT='+codpatJS+'&VISITNUM='+visitnumJS+'&ESAM='+esamJS+'&PROGR='+progrJS+'&form='+dest_xml;
}
	
	
function leftTrim(sString) 
{
	while (sString.substring(0,1) == ' ')
		sString = sString.substring(1, sString.length);

	return sString;
}

function rightTrim(sString) 
{
	while (sString.substring(sString.length-1, sString.length) == ' ')
		sString = sString.substring(0,sString.length-1);

	return sString;
}

function trimAll(sString) 
{
	while (sString.substring(0,1) == ' ')
		sString = sString.substring(1, sString.length);
	
	while (sString.substring(sString.length-1, sString.length) == ' ')
		sString = sString.substring(0,sString.length-1);

	return sString;
}

function DataOggi()
{
	var eform = document.forms[0].elements;

	// Array of month Names
	var monthNames = new Array("jan","feb","mar","apr","may","jun","jul","aug","sep","oct","nov","dec");

	var now = new Date();
	x_oggi = now.getDate() + "/" + monthNames[now.getMonth()] + "/" + now.getFullYear();

	eform['SIGN_DATE'].value = x_oggi;
	eform['SIGN_DATE'].disabled = true;
}


function CalcolaClearance()
{
	var eform = document.forms[0].elements;

	x_visitnum = document.forms[0].elements['VISITNUM'].value;
	x_esam = document.forms[0].elements['ESAM'].value;
	
	x_bthdate = document.forms[0].elements['HD_DEMOG_BTHDATE'].value;
	x_sex = document.forms[0].elements['HD_DEMOG_SEX'].value;
	x_bldsampdate = document.forms[0].elements['HD_LAB_BLDSAMPDATE'].value;

	x_weightstring = document.forms[0].elements['HD_VITAL_WGHT'].value;
	if (x_weightstring != '')
		x_weight = parseInt(x_weightstring);
	else
		x_weight = 0;

	x_unit = trimAll(document.forms[0].elements['HD_CREAUNIT'].value);
	x_unitext = trimAll(document.forms[0].elements['HD_CREAUNIT_EXT'].value);

	x_unitlower = x_unit.toLowerCase(); 
	switch(x_unitlower) 
	{
		 case '': case 'g / dl': case 'g / 100ml':
			x_factor = 1000;
			break;
		 case 'mg / dl': case 'mg / 100 ml':
			x_factor = 1;
			break;
		 case 'g / l': case 'mg / ml':
			x_factor = 100;
			break;	
		 case 'mmol / l': case 'mcmol / ml':
			x_factor = 11.312217;
			break;
		 case 'mcmol / l': case 'nmol / ml': case 'micromol / l':
			x_factor = 0.011312217;
			break;
		 default:
			x_factor = 999;
			break;
	} 
	x_unitextlower = x_unitext.toLowerCase(); 
	switch(x_unitextlower) 
	{
		 case '': case 'g / dl': case 'g / 100ml':
			x_factorext = 1000;
			break;
		 case 'mg / dl': case 'mg / 100 ml':
			x_factorext = 1;
			break;
		 case 'g / l': case 'mg / ml':
			x_factorext = 100;
			break;	
		 case 'mmol / l': case 'mcmol / ml':
			x_factorext = 11.312217;
			break;
		 case 'mcmol / l': case 'nmol / ml': case 'micromol / l':
			x_factorext = 0.011312217;
			break;
		 default:
			x_factorext = 999;
			break;
	} 
	
	if (x_factor == 1000) x_factor = x_factorext;

/*	
<value val='6101'>mmol/l</value>
<value val='6102'>mcmol / ml</value>
<value val='6201'>mcmol / l</value>
<value val='7501'>mg / dl</value>
<value val='7503'>mg / 100 ml</value>
*/	
	
	x_creatininastring = document.forms[0].elements['HD_LBORRES25'].value;
	
	if (x_creatininastring != '')
		x_creatinina = parseFloat(x_creatininastring);
	else
		x_creatinina = 0;

	//normalizzo il valore della creatinina in baase all'unita di misura
	x_creatinina = x_creatinina * x_factor;
		
	x_bthdated = x_bthdate.substring(0,2);
	x_bthdatem = x_bthdate.substring(3,5);
	x_bthdatey = x_bthdate.substring(6,10);
	//alert('bthdate: ' + x_bthdated + '/' + x_bthdatem + '/' + x_bthdatey)
	
	x_bldsampdated = x_bldsampdate.substring(0,2);
	x_bldsampdatem = x_bldsampdate.substring(3,5);
	x_bldsampdatey = x_bldsampdate.substring(6,10);
	//alert('bldsampdate: ' + x_bldsampdated + '/' + x_bldsampdatem + '/' + x_bldsampdatey)
	
	//alert('sex: '  + x_sex);
	//alert('bthdate: '  + x_bthdate);
	//alert('bldsampdate: '  + x_bldsampdate);
	//alert('weight: '  + x_weightstring);
	//alert('creatinina: '  + x_creatininastring);
	//alert('unit: '  + x_unitlower);
	
	/*
		CALCOLO AGE
	*/
	if (x_bldsampdated=='' || x_bldsampdatem=='' || x_bldsampdatey=='')
		var date_visit ='';
	else
		var date_visit = new Date (x_bldsampdatey,x_bldsampdatem-1, x_bldsampdated)

	if (x_bthdated=='' || x_bthdatem=='' || x_bthdatey=='')
		var date_birth = '';
	else
		var date_birth = new Date (x_bthdatey,x_bthdatem-1, x_bthdated);

	if (date_visit > date_birth && date_visit !='' && date_birth!='')
	{	
		//differenza tra le date in millisecondi
		differenza = date_visit - date_birth;    	
		//un giorno in millisecondi
		var ONEDAY = 1000*3600*24;
		giorni_differenza = new String(differenza/ONEDAY);
		anni_differenza = new String(giorni_differenza/365.25);
		x_age = parseInt(anni_differenza);
		
		//troncamento x_age (in realtà parseInt lo fa già...)
		x_age = Math.floor(x_age);
		//alert('age: ' + x_age.toString());
	}
	else
		x_age = 0;
	/*
		FINE CALCOLO AGE
	*/

	/*
		CALCOLO creatinine clearance
		for men ((140-age) * weight) / 72 * creatinina
		for women   0.85 * ((140-age) *weight) / 72 * creatinina
	*/
	x_clearance = '';
	
	if ((x_age > 0) && (x_weight > 0) && (x_creatinina > 0) && (x_factor != 999))
	{
		x_clearance = ((140 - x_age) * x_weight)/(72 * x_creatinina);
		
		if (x_sex == 1)  //female
			x_clearance = 0.85 * x_clearance;

		x_clearance = x_clearance.toFixed(3);
		//alert('clearance: '  + x_clearance);

		eform['CREAT'].value = x_clearance;

		//x_clearance = x_clearance.toString();
		//eform['CREAT'].value = x_clearance;
		//alert('eform[CREAT].value: '  + eform['CREAT'].value);
	}
	
	eform['CREAT'].disabled = true;
	
	/*
		FINE CALCOLO creatinine clearance
	*/
	
	return true;
}
