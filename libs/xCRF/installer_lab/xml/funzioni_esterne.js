
function Range_lab_copymale()
{
	f=document.forms[0];
	el=f.elements;

	return true;
}

function Range_lab_load()
{
	f=document.forms[0];
	el=f.elements;
	el['SEX'].value=1;
	el['SEXF'].value=2;
	el['SEX'].disabled=true;
	el['SEXF'].disabled=true;
	
	
	return true;
}

function CheckDateNANK(DateToCheck)
{
	f=document.forms[0];
	el=f.elements;	
	
	if (el[DateToCheck+'D'].value.toUpperCase()=='NA' || el[DateToCheck+'D'].value==-9911  || el[DateToCheck+'D'].value==-9922 || el[DateToCheck+'D'].value.toUpperCase()=='NK') 
	{
		alert('Date: NA is not accepted');
		document.getElementsByName(DateToCheck+'D')[0].focus();
		return false;
	}

	if  (el[DateToCheck+'M'].value.toUpperCase()=='NA' || el[DateToCheck+'M'].value==-9911  || el[DateToCheck+'M'].value==-9922 || el[DateToCheck+'M'].value.toUpperCase()=='NK') 
	{
		alert('Date: NA is not accepted');
		document.getElementsByName(DateToCheck+'M')[0].focus();
		return false;
	}

	if  (el[DateToCheck+'Y'].value.toUpperCase()=='NA' || el[DateToCheck+'Y'].value==-9911 || el[DateToCheck+'Y'].value==-9922 || el[DateToCheck+'Y'].value.toUpperCase()=='NK') 
	{
		alert('Date: NA is not accepted');
		document.getElementsByName(DateToCheck+'Y')[0].focus();
		return false;
	}
	
	return true;
}