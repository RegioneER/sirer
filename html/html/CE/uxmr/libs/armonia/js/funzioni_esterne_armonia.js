/**
 * 
 * Libreria inserita per avere raggruppate tutte le funzioni comuni a tutti i registri
 * nell'ambito del progetto A.R.MON.I.A. (Accorpamento Registri MONitoraggio In Armonia)
 */
//function checkCheckbox(nombreCondicion,nombreCheckbox,rango){
//	f = document.forms[0];
//	el = f.elements;
//	
//	if(el[nombreCondicion].value==1){
//		//El campo es si busco que haya un verdadero
//		for(i=1;i<rango+1;i++){
//			if(el[nombreCheckbox+i].checked)
//					return true;
//		}
//		alert('Almeno uno tra i principi attivi deve essere selezionato');
//		return false;
//	}
//	else{
//		//busco que todos sean false
//		for(i=1;i<rango+1;i++){
//			if(el[nombreCheckbox+i].checked){
//		//			alert(el[nombreCheckbox+i].checked);
//					alert('Pincipi attivi deve essere vuoto cuando es no');
//					el[nombreCheckbox+i].focus();
//					return false;
//				}
//			}
//			return true;
//		}
//}

//function IsNumber(Expression) {
//	Expression = Expression.toLowerCase();
//	RefString = "0123456789.-";
//
//	if (Expression.length < 1)
//		return (false);
//
//	for ( var i = 0; i < Expression.length; i++) {
//		var ch = Expression.substr(i, 1);
//		var a = RefString.indexOf(ch, 0);
//		if (a == -1) {
//			alert("Patient code must be numeric");
//			return (false);
//		}
//	}
//	return (true);
//}

function Set_farma_ter(val){
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