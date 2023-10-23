var isNA="";
var EE=new Array();
var PP=new Array();
var myId= new Array();
var myNewCond;
var z;
var E;
var P;
var mioId=new Array();
var y;
var c=0;
var indice=new Array();


function clearValue(field2){
	
var splitted = field2.split("#");	
var x=0;


//alert("clear= "+field2);
while(x<splitted.length){
	
	//alert("clear"+ field2);
var P=document.getElementsByName(splitted[x]);

//alert(typeof(P.type));

	if (isArray(P) && (typeof(P.type)=="undefined")) {
	var v=0;	
	while(P[v])	{
		//alert(P[v] + " - " + splitted[x]);
	//P[v].value="";
		var zcv=setSingleInputValue(P[v],"");
	v=v+1;
	}
	//P=P[0];
	//alert(typeof(P.type));
	}	
	else var zcv=setSingleInputValue(P[0],"");
	//P[0].value="";
	

x=x+1;	
}

}


function enable(field2){
//alert(" - " +field2);	
var splitted40 = field2.split("#");	
var x=0;

//alert("EnableDisable= "+splitted[x]);
//alert(splitted40[x].length);
while(splitted40[x]){
	
//alert("pp"+ splitted40[x]);	

var P=document.getElementsByName(splitted40[x]);

	if (isArray(P) && (typeof(P.type)=="undefined")) {
		//alert(field2 + "-"+P[0].type);
	var v=0;	
	while(P[v])	{
	if(P[v].disabled!=false)	P[v].disabled=false;
	//if(P[v].disabled==false)		P[v].disabled=true;	
	v=v+1;
	}
	//P=P[0];
	//alert(typeof(P.type));
	}	
	else 
	{
		//alert(P[0].type);
	if(P[0].disabled!=false) P[0].style.disabled=false;
	//P[0].value="e";
	}

	
x=x+1;	
}	
	
return true;	
}


function disable(field2){
//alert(" - " +field2);	
var splitted40 = field2.split("#");	
var x=0;

//alert("EnableDisable= "+splitted[x]);
//alert(splitted40[x].length);
while(splitted40[x]){
	
//alert("pp"+ splitted40[x]);	

var P=document.getElementsByName(splitted40[x]);
//alert(P[0].type);
	if (isArray(P) && (typeof(P.type)=="undefined")) {
		//alert(field2 + "-"+P[0].type);
	var v=0;	
	while(P[v])	{
	//if(P[v].disabled==true)		P[v].disabled=false;
	//alert("" + P[v].name);
	if(P[v].disabled!=true) P[v].disabled=true;	
	v=v+1;
	}
	//P=P[0];
	//alert(typeof(P.type));
	}	
	else 
	{
		//alert(P[0].type);
	if(P[0].disabled!=true) P[0].style.disabled=true;
	//P[0].value="e";
	}

	
x=x+1;	
}	
	
return true;	
}







function mainCrossChecks2(riga){
	
var splitted3;
splitted3 = riga;
//alert(splitted3);
var splitted2 = splitted3.replace(/\s+/g,"");

isErr=false;
var splitted = splitted2.split("#");	
var x=0;
var cond="";


//alert(splitted[x]);
while(splitted[x]){

//alert(splitted[x] + " - " + document.forms[0].elements[splitted[x]]);
if(!document.forms[0].elements[splitted[x]])	{
//alert(document.forms[0].elements[splitted[x]].value);
cond=cond+splitted[x];
}	
if(document.forms[0].elements[splitted[x]])	{
	
	var T = document.getElementsByName(splitted[x]);
	var Pid = document.getElementById(splitted[x]);	
	if(!Pid){
		
	if (isArray(T) && (typeof(T.type)=="undefined")) {
	//P=P[0];
	//alert(typeof(P.type));
	}	
	}
	if(Pid) P=Pid;
	//if (isArray(P)) {P=P[0];}		
	//alert(P.value);
	//P.focus();	
	
	
//alert(document.forms[0].elements[splitted[x]].value);
var myVal="";
myVal=getInputValue(T);
if(myVal=="") myVal="null";
cond=cond+myVal;
}

x=x+1;
}
//cond=cond+myResult;

//}

//alert("cond="+cond);
return cond;

}



//window.onload=function(){
	
function xLoad(){	
	
	//alert("load");
	
try{	
	
var eform = document.forms[0].elements;
var x_esam = document.forms[0].elements['ESAM'].value;
var x_visitnum = Trim(document.forms[0].elements['VISITNUM'].value);	
var y=0;	
var z=1;
if(HH_AUTO_IDX[x_visitnum][x_esam]){
//alert(HH_CROSS_IDX[x_visitnum][x_esam]);
var condition=HH_AUTO_IDX[x_visitnum][x_esam];
myId = condition.split("#");	
	
	//alert(myId.length);
while(z<myId.length){
//var E=document.getElementsByName(HH_AUTO_CHECK[myId[z]][2]);
//P=document.getElementsByName(HH_AUTO_CHECK[myId[z]][1]);
//var test=new objRestore(HH_AUTO_CHECK[myId[z]][0],HH_AUTO_CHECK[myId[z]][1],HH_AUTO_CHECK[myId[z]][2]);

var myField = HH_AUTO_CHECK[myId[z]][2];
//alert(myField);

if(myField.toUpperCase().lastIndexOf("$REC")!="-1"){
//alert(document.getElementById("tr_REC"+))style.display);
var myControl=1;
//alert(document.getElementById("tr_REC2").style.display);

//var myFieldSub=myField.toUpperCase().replace("$REC",myControl);
//var masterCard=document.getElementsByName(myFieldSub);
//var myField222 = myField;

//var myField222=document.getElementsByName(myField.toUpperCase().replace("$REC",myControl))[0];
//while(document.getElementById("tr_REC"+myControl)){
//alert(document.getElementsByName(myField222.toUpperCase().replace("$REC",myControl))[0]);
var myFieldSub=myField.toUpperCase().replace("$REC",myControl);
//myFieldSub=
//alert(myFieldSub);
while(myControl<11){
	//while(document.getElementsByName(myFieldSub)[0]){
//alert(document.getElementsByName(myFieldSub)[0].style.display);
myFieldSub=myField.toUpperCase().replace("$REC",myControl);	
//alert(document.getElementById("tr_REC"+myControl).style.display);
//if((myControl>1)&&(document.getElementById("tr_REC"+myControl).style.display=="none"))  break;


//if(!document.getElementsByName(myFieldSub)[0]) break;

if(document.getElementsByName(myFieldSub)[0]){

var myFieldCond = HH_AUTO_CHECK[myId[z]][0];
//var r = new RegExp('REC', 'g');
//var replace=/$REC/gim;
var myFieldCond=myFieldCond.replace(/\$REC/gim,myControl);

	
//alert(myId[z] + " - " +myFieldCond);
var myFieldMast = HH_AUTO_CHECK[myId[z]][1];
myFieldMast=myFieldMast.toUpperCase().replace("$REC",myControl);


//alert(mainCrossChecks2(myFieldCond));
if(eval(mainCrossChecks2(myFieldCond))) {
clearValue(myFieldSub);
//alert(HH_AUTO_CHECK[myId[z]][2]+ "-" + z);
var myCell =  new disable(myFieldSub);
//clearValue(splitted[x]);
}
if(!eval(mainCrossChecks2(myFieldCond))) {
	//alert(splitted[x] + "=" + "el"+"="+ eval(mainCrossChecks2(HH_AUTO_CHECK[myId[z]][0])));
	//if(myField1[0].type!="radio"){
//alert(HH_AUTO_CHECK[myId[z]][2])
var P=document.getElementsByName(myFieldMast);
//alert(P[0].type);
if(P[0].disabled!=true) var myCell =  new enable(myFieldSub);

	//}
}









//alert(myControl);

//alert(myFieldSub + "-" + document.getElementsByName(myFieldSub));
}
myControl=myControl+1;
}

}
//alert("Out");

if(myField.toUpperCase().lastIndexOf("$REC")=="-1"){
//alert(eval(mainCrossChecks2(HH_AUTO_CHECK[myId[z]][0]))+ "-" +mainCrossChecks2(HH_AUTO_CHECK[myId[z]][0]));
if(eval(mainCrossChecks2(HH_AUTO_CHECK[myId[z]][0]))) {
clearValue(HH_AUTO_CHECK[myId[z]][2]);
//alert(HH_AUTO_CHECK[myId[z]][2]+ "-" + z);
var myCell =  new disable(HH_AUTO_CHECK[myId[z]][2]);
//clearValue(splitted[x]);
}
if(!eval(mainCrossChecks2(HH_AUTO_CHECK[myId[z]][0]))) {
	//alert(splitted[x] + "=" + "el"+"="+ eval(mainCrossChecks2(HH_AUTO_CHECK[myId[z]][0])));
	//if(myField1[0].type!="radio"){
//alert(HH_AUTO_CHECK[myId[z]][2])
var P=document.getElementsByName(HH_AUTO_CHECK[myId[z]][1]);
//alert(P[0].type);
if(P[0].disabled!=true) var myCell =  new enable(HH_AUTO_CHECK[myId[z]][2]);

	//}
}


}

//var myFunc=new stereo(myField);



//
	

z=z+1;
}	

}
}

catch(e){}
//alert("Pippo3"+getInputValue(E[i]));
//if(getInputValue(E[i])=="") P[i][0].disabled=false;

}





function doSomething(e) {
	//alert(e);
	if (!e) var e = window.event;
	//if (!e) var e = window.event || e;
	//var relTarg = e.relatedTarget || e.toElement;
	//var T=e.target;
if(window.event) // IE check
   var T = window.event.srcElement;
if(e && e.target) // standard-compliant browsers
   var T = e.target;
	
	//alert(T.type +"-"+T.name);
if((T.type=="radio")||(T.type=="text")||(T.type=="checkbox")||(T.type=="textarea")||(T.type=="select-one")){

//alert(T.type);
var x_esam = document.getElementsByName("ESAM")[0].value;
var x_visitnum = document.getElementsByName("VISITNUM")[0].value;	
var y=0;	
var z=1;
//alert();
if(HH_AUTO_IDX[x_visitnum][x_esam]){
		
//alert("ok");

var condition=HH_AUTO_IDX[x_visitnum][x_esam];
myId = condition.split("#");	
	
	//alert(myId.length);
while(z<myId.length){
//var E=document.getElementsByName(HH_AUTO_CHECK[myId[z]][2]);
//P=document.getElementsByName(HH_AUTO_CHECK[myId[z]][1]);
//var test=new objRestore(HH_AUTO_CHECK[myId[z]][0],HH_AUTO_CHECK[myId[z]][1],HH_AUTO_CHECK[myId[z]][2]);
var condizione = HH_AUTO_CHECK[myId[z]][0];

if((condizione.lastIndexOf(T.name)!="-1")&&(condizione.lastIndexOf(T.name+"$REC")=="-1")){
	
	
var myField = HH_AUTO_CHECK[myId[z]][2];
//alert(eval(mainCrossChecks2(HH_AUTO_CHECK[myId[z]][0]))+ "-" +mainCrossChecks2(HH_AUTO_CHECK[myId[z]][0]));
if(eval(mainCrossChecks2(HH_AUTO_CHECK[myId[z]][0]))) {
clearValue(HH_AUTO_CHECK[myId[z]][2]);
//alert(HH_AUTO_CHECK[myId[z]][2]+ "-" + z);
var myCell =  new disable(HH_AUTO_CHECK[myId[z]][2]);
//clearValue(splitted[x]);
}
if(!eval(mainCrossChecks2(HH_AUTO_CHECK[myId[z]][0]))) {
	//alert(splitted[x] + "=" + "el"+"="+ eval(mainCrossChecks2(HH_AUTO_CHECK[myId[z]][0])));
	//if(myField1[0].type!="radio"){
//alert(HH_AUTO_CHECK[myId[z]][2])
var P=document.getElementsByName(HH_AUTO_CHECK[myId[z]][1]);
//alert(P[0].type);
if(P[0].disabled!=true) var myCell =  new enable(HH_AUTO_CHECK[myId[z]][2]);

	//}
}

}


if(condizione.lastIndexOf("$REC")!="-1"){
var i=0;
while(i<33){
var myFieldCond=condizione.replace(/\$REC/gim,i);
	
//alert(myFieldCond);

if(myFieldCond.lastIndexOf(T.name)!="-1"){
	
	//alert("in");
var myField = HH_AUTO_CHECK[myId[z]][2];
myField =myField.replace(/\$REC/gim,i);

//alert(eval(mainCrossChecks2(myFieldCond))+ "-" +mainCrossChecks2(myField));
if(eval(mainCrossChecks2(myFieldCond))) {
clearValue(myField);
//alert(HH_AUTO_CHECK[myId[z]][2]+ "-" + z);
var myCell =  new disable(myField);
//clearValue(splitted[x]);
}
if(!eval(mainCrossChecks2(myFieldCond))) {
	//alert(splitted[x] + "=" + "el"+"="+ eval(mainCrossChecks2(HH_AUTO_CHECK[myId[z]][0])));
	//if(myField1[0].type!="radio"){
//alert(HH_AUTO_CHECK[myId[z]][2])
var myField = HH_AUTO_CHECK[myId[z]][1].replace(/\$REC/gim,i);
var myField1 = HH_AUTO_CHECK[myId[z]][2].replace(/\$REC/gim,i);
var P=document.getElementsByName(myField);
//alert(P[0].type);
if(P[0].disabled!=true) var myCell =  new enable(myField1);

	//}
}
break;
}






//alert("continuous");

i=i+1;
}
}

z=z+1;
}






}

}
}

//if (document.addEventListener) document.addEventListener('click',doSomething,false);
//else window.document.addEventListener('click',doSomething,false);
	//if (document.all){
		//document.body.addEventListener('click',doSomething,false);
	//} else {
  		if (window.addEventListener) {
			//alert("Attach");
      		window.addEventListener('click',doSomething,false);
   		} else {
			//alert("Attach");
window.document.attachEvent('onclick',doSomething,false);
		}
	//}
//window.addEventListener('click',doSomething,false);