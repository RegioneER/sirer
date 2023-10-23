function search(str1, regStr){

var pattern = regStr;

if(pattern.test(str1)) return true;
if(!pattern.test(str1)) return false;

//alert(str1 +" - "+regStr);

}

function countSub(){

var t=1;
var counter=0;


while(t){
	
if(t==1){

var U=document.getElementsByName("RECD"+t);
//alert(U[0].checked);
if(U[0].checked==false){
counter=counter+1;	
}

}		
if(t>1){

if(!document.getElementById("tr_REC"+t)||(document.getElementById("tr_REC"+t).style.display=="none")) break;

var U=document.getElementsByName("RECD"+t);
//alert(U[0].checked);
if(U[0].checked==false){
counter=counter+1;	
}	

}	


t=t+1;
//counter=counter+1;
}

//alert(counter);
return counter;
}

function addDays(date1,d) {
	//var date1 = parseDate(date1);
	//if(date1.length==)
	var pattern=/\//;
	//alert("regex" + pattern.test(date1));	
	if(pattern.test(date1))   var date33 = getDateFromFormat(date1,"d/M/yyyy");
	if(!pattern.test(date1))   var date33 = getDateFromFormat(date1,"ddMMyyyy");
	//alert("parse date1 result:" + date1);
    //var date2 = parseDate(date1);
	//alert("parse date2 result:" + date2);	
	var ONE_DAY = 1000 * 60 * 60 * 24;
	date1 = new Date(date33+ONE_DAY*d);
	var dateFormat = formatDate(date1,"d/M/yyyy");
	//var dateFormat = formatDate(date1,"dMyyyy");
	//date1 = formatDate(date1,"dMyyyy");	
	//alert(dateFormat);
	return dateFormat;

}


function addYears(date1,d) {
	//var date1 = parseDate(date1);
	//if(date1.length==)
	var pattern=/\//;
	//alert("regex" + pattern.test(date1));	
	if(pattern.test(date1))   var date33 = getDateFromFormat(date1,"d/M/yyyy");
	if(!pattern.test(date1))   var date33 = getDateFromFormat(date1,"ddMMyyyy");
	//alert("parse date1 result:" + date1);
    //var date2 = parseDate(date1);
	//alert("parse date2 result:" + date2);	
	var ONE_YEAR = 1000 * 60 * 60 * 24 * 365;
	//date1 = new Date(date33+ONE_YEAR*d);
	date1 = new Date(date33);

	var year=date1.getYear()+d;
	var month=date1.getMonth();
	var day=date1.getDate();
	date1 = new Date(year, month, day);
	
	var dateFormat = formatDate(date1,"d/M/yyyy");
	//var dateFormat = formatDate(date1,"dMyyyy");
	//date1 = formatDate(date1,"dMyyyy");	
	//alert(dateFormat);
	return dateFormat;

}


function lPad(val){
return "0"+val;
}


//se una data non è corretta, qiundi è vuota o contiene NA, restituisce false
function isNotDate(date1){
	var dateformat="dd/M/yyyy";
	var d1=getDateFromFormat(date1,dateformat);	
	if (d1==0) {
		return true;
		}	
	return false;
}	

//se una data è corretta e senza NA restituisce true	
function isDate(date1){
	var dateformat="dd/M/yyyy";
	var d1=getDateFromFormat(date1,dateformat);	
	//alert(d1);
	if (d1==0) {
		return false;
		}	
	return true;
}	

function d1d2( date1,date2,v_oper){
	var dateformat="dd/M/yyyy";
	//alert('d1d2-'+date1+'*');
	//alert('d1d2-'+date2+'*');
	if (date2==null) {return false;}
	var leng='';
	leng=date1.length;
	if (leng!=10 ) {return false;}
	leng='';
	leng=date2.length;
	if (leng!=10 ) {return false;}
	var checkNA='';
	checkNA=date1.substring(0,2);
	if (checkNA=='NA' || checkNA=='NK') {return false;}
	checkNA=date1.substring(3,5);
	if (checkNA=='NA' || checkNA=='NK') {return false;}
	checkNA=date1.substring(6,10);
	if (checkNA=='NA' || checkNA=='NK') {return false;}
	var d1=getDateFromFormat(date1,dateformat);
	var dformat='';
	dformat=date2.substring(2,3);
	if (dformat=='/') 
    {	var check2NA='';
		check2NA=date2.substring(0,2);
		if (check2NA=='NA' || checkNA=='NK') {return false;}
		check2NA=date2.substring(3,5);
		if (check2NA=='NA' || checkNA=='NK') {return false;}
		check2NA=date2.substring(6,10);
		if (check2NA=='NA' || checkNA=='NK') {return false;}
		var d2 = getDateFromFormat(date2,"dd/M/yyyy");
	}
	//else if(!pattern.test(date2))  var d2 = getDateFromFormat(date2,"ddMMyyyy");  

	if (d1==0 || d2==0) {return false;}
	else if (v_oper=='>=')
		{	if (d1 >= d2) {return true;}}
	else if (v_oper=='>')
		{	if (d1 > d2) {return true;}}
	else if (v_oper=='<')
		{	if (d1 < d2) {return true;}}
	else if (v_oper=='<=')
		{	if (d1 <= d2) {return true;}}
	else if (v_oper=='==')
		{	if (d1 == d2) {return true;}}
	else if (v_oper=='!=')
		{	if (d1 != d2) {return true;}}
	return false;	
}


function getCheckedValue(radioObj) {
	
	//if(!radioObj)
		//return "";
	var radioLength = radioObj.length;
	alert(radioLength);
	/*
	if(radioLength == undefined)
		if(radioObj.checked)
			return radioObj.value;
		else
			return "";
		*/
	for(var i = 0; i < radioLength; i++) {
		if(radioObj[i].checked) {
			alert("My radio val= "+radioObj[i].value);
			return radioObj[i].value;
		}
	}
	//return "";
}



function mainCrossChecks(splitted3,idBlock){

var x_visitnum = Trim(document.forms[0].elements['VISITNUM'].value);
var x_codpat = document.forms[0].elements['CODPAT'].value;

var splitted2 = splitted3.replace(/\s+/g,"");
isErr=false;
var splitted = splitted2.split("#");	
var x=0;
var cond="";



while(splitted[x]){
//alert(splitted[x]);
if(!document.forms[0].elements[splitted[x]])	{
cond=cond+splitted[x];
}	
if(document.forms[0].elements[splitted[x]])	{
	var P = document.getElementsByName(splitted[x]);
	var Pid = document.getElementById(splitted[x]);	
	if(!Pid){
		
	if (isArray(P) && (typeof(P.type)=="undefined")) {
	}	
	}
	if(Pid) P=Pid;
var myVal="";
//alert(P.type);
//if(P.type=="radio") myVal=getCheckedValue(document.forms[0].elements[splitted[x]]);
if(P.type=="radio")	myVal=getInputValue(document.forms[0].elements[splitted[x]]);
if(P.type!="radio") myVal=getInputValue(P);
//alert('*'+myVal+'*');
if ((P.type=="text") || (P.type=="hidden"))
{	if (myVal=="") myVal="null";
	else 
	{	if(myVal!="NA" && myVal!="NK")
		{	isNA="";	
		}
		if(myVal=="NA" || myVal=="NK")
		{	var myVal=myVal;		
			//if(myVal=="NA") 
			isNA="Y";
		}
	}
}
if(isNaN(myVal)&& myVal!="" && myVal!="NA" && myVal!="NK") myVal='"'+myVal.toUpperCase()+'"';
if(myVal=="") myVal="null";

cond=cond+myVal;
//x_data_null=cond.indexOf('""NULL"/null/"NULL""');
//alert(x_data_null);
//alert('*'+cond+'*');
}
cond=cond.replace('""NULL"/null/"NULL""','"null/null/null"');
cond=cond.replace('NA==null','"NA"==null');
cond=cond.replace('NK==null','"NK"==null');
cond=cond.replace('NA!=null','"NA"!=null');
cond=cond.replace('NK!=null','"NK"!=null');
cond=cond.replace('NA=="NULL"','"NA"=="NULL"');
cond=cond.replace('NA=="NA"','"NA"=="NA"');
cond=cond.replace('NA==-9911','"NA"==-9911');
cond=cond.replace('NA!="NA"','"NA"!="NA"');
cond=cond.replace('NA!=-9911','"NA"!=-9911');
cond=cond.replace('"NULL"==null&&null==null&&"NULL"==null','null==null&&null==null&&null==null');
cond=cond.replace('"NULL"!=null||null!=null||"NULL"!=null','null!=null||null!=null||null!=null');
//alert('*'+cond+'*');

x=x+1;
}

//alert(cond);
return cond;

}



function evalCond(cond,y,idRec){

try{
if(eval(cond)){
var myId=HH_CROSS_CHECK[y][1];
var msg=HH_CROSS_CHECK[y][5];


if(myId.toUpperCase().indexOf("$REC")!="-1"){
myId=myId.replace(/\$REC/gim,idRec);
}

if(msg.toUpperCase().indexOf("$REC")!="-1"){
msg=msg.replace(/\$REC/gim,idRec);

}
if(idRec!=""){
msg="Rec. "+ idRec + ": " + msg;
}

var suffix="";
var P = document.getElementsByName(myId);
var PP=P[0];	
var canc=0;

if(HH_CROSS_CHECK[y][3]=="W*"){
	var answer = confirm(msg);
	if (answer){

	myCond = cond;		
	var myReg=/&&/g;
	myCond = myCond.replace(myReg," AND ");	
	isNA="";
	}
	else{
		if (isArray(P) && (typeof(P.type)=="undefined")) {PP=P[0];}
		if(PP.type=="radio") {
		document.getElementById(myId+".0").focus();
		return false;
		}
		if((PP.type=="text")||(PP.type=="select-one")) {
		document.getElementById(myId).focus();
		return false;
		}
	}
}

if((HH_CROSS_CHECK[y][3]=="B")||(HH_CROSS_CHECK[y][3]=="W"))
{
	if(HH_CROSS_CHECK[y][3]=="B")
	{	
		var a = document.URL;
		var x='';
		/*x=a.indexOf("test");
		if (x!=-1)
		{	var answer = confirm(msg);
			if (answer)
			{
				return true;	
			}
			else
				return false;
		}
		else */
		   alert(msg);
		
		return false;
	}
	
	
	
	if(HH_CROSS_CHECK[y][3]=="W")
	{
		var answer = confirm(msg);
		if (answer)
		{
			return true;	
		}
		else
			return false;
			
		/*
		
		if (!answer)
		{
			var P = document.getElementsByName(myId);
			if (isArray(P) && (typeof(P.type)=="undefined"))
			{//P=P[0];
				P[0].focus();	
			}	
			else
			{
			 	P.focus();
			}
			return false;
		}
		*/
	}

	return false;
}
} //fine eval(cond)
	
}

catch(e){

	var myCond=	HH_CROSS_CHECK[y][4];
	
	var objErr="";
	var espressione = /NA/;

	myCond = myCond.replace(/#/g,"");	
	myCond = myCond.replace(/\s+/g,"");
	var myErrString=e.message.toUpperCase();
	var matchPos1 = myErrString.search(espressione);
	
	if(isNA==""){
	var status="E";
	isNA="";	
	var logMsg="Syntax Error";
	}
	if(isNA=="Y"){
	var status="S";	
	var myReg=/&&/g;
	var myCond=cond;
	myCond = myCond.replace(myReg," AND ");		
	var logMsg=myCond;	
	}
	var a = document.URL;
	var x='';
	x=a.indexOf("test");
	if (x!=-1)
	{	var answer = confirm(y +" - " + objErr + " - " + logMsg + " - " +myErrString + " - " +matchPos1);
		if (answer)
		{	return true;	
		}
		else
			return false;
	}
	else 
	alert(y +" - " + objErr + " - " + logMsg );
}	
}

var isNA="";


function advChecks(){

var eform = document.forms[0].elements;
var x_esam = document.forms[0].elements['ESAM'].value;
var x_visitnum = Trim(document.forms[0].elements['VISITNUM'].value);
var myContCheck=new Array();	
var myMainCheck=new Array();
var y=0;	

if(HH_CROSS_IDX[x_visitnum][x_esam]){
//alert(document.getElementsByName('salva')[0]);	
if(!document.getElementsByName('invia')[0]) 
{	if(!document.getElementsByName('salva')[0]) 
	return true;	
}
var condition=HH_CROSS_IDX[x_visitnum][x_esam];
var myId = condition.split("#");	
var i=1;
//alert(myId);
while(i<myId.length){

var myTestCond= HH_CROSS_CHECK[myId[i]][4];

if(myTestCond.toUpperCase().indexOf("$REC")!="-1"){
myContCheck.push(myId[i]);
}	


else{
	
myMainCheck.push(myId[i]);	
	
}	

i=i+1;
}


var i=0;
while (i<myMainCheck.length){

var myTestCond= HH_CROSS_CHECK[myMainCheck[i]][4];	
//alert("MAIN: "+ myTestCond);
var myNewCond=mainCrossChecks(myTestCond,"");

//alert( myNewCond);
var testCond=evalCond(myNewCond,myMainCheck[i],"");
if(testCond==false) return false;	
	
i=i+1;
}

if(myContCheck.length>0){

	
var t=1;


while(t){
if(t>1){

if(!document.getElementById("tr_REC"+t)||(document.getElementById("tr_REC"+t).style.display=="none")) break;

}

var U=document.getElementsByName("RECD"+t);
//alert(U[0].checked);
if(U[0].checked==false){
	
	
var i=0;	
while (i<myContCheck.length){

var myTestCond= HH_CROSS_CHECK[myContCheck[i]][4];
//alert("SUB: "+ myTestCond);	
var myRegTest=myTestCond.replace(/\$REC/gim,t);
var myNewCond=mainCrossChecks(myRegTest,"");

//alert(myRegTest + " - " + myNewCond +" - " + t);
var testCond=evalCond(myNewCond,myContCheck[i],t);
if(testCond==false) return false;		
	
i=i+1;
}	



}

t=t+1;
}



}


}

return true;
}


/*
function d1GTd2(date1,date2){
	var dateformat="dd/M/yyyy";
	var d1=getDateFromFormat(date1,dateformat);
	var pattern=/\//;
	//alert("regex" + pattern.test(date1));	
	if(pattern.test(date2))   var d2 = getDateFromFormat(date2,"dd/M/yyyy");
	if(!pattern.test(date2))   var d2 = getDateFromFormat(date2,"ddMMyyyy");	
	//var d2=parseDate(date2);
	//alert(d1 + " - " +d2);
	if (d1==0 || d2==0) {
		return false;
		}
	else if (d1 > d2) {
		return true;
		}
	return false;	
}

function d1GEd2(date1,date2){
	var dateformat="dd/M/yyyy";
	var d1=getDateFromFormat(date1,dateformat);
	var pattern=/\//;
	//alert("regex" + pattern.test(date1));	
	//alert(date1);
	//alert(date2);
	if(pattern.test(date2))   var d2 = getDateFromFormat(date2,"d/M/yyyy");
	if(!pattern.test(date2))  var d2 = getDateFromFormat(date2,"ddMMyyyy");
	//alert(d1||'+'||d2);
	if (d1==0 || d2==0) {
		return false;
		}
	else if (d1 >= d2) {
		return true;
		}
	return false;	
}

function d1EQd2(date1,date2){
	var dateformat="d/M/yyyy";
	var d1=getDateFromFormat(date1,dateformat);
	var pattern=/\//;
	//alert("regex" + pattern.test(date1));	
	//alert(date2);
	if(pattern.test(date2))   var d2 = getDateFromFormat(date2,"d/M/yyyy");
	if(!pattern.test(date2))   var d2 = getDateFromFormat(date2,"ddMMyyyy");
	if (d1==0 || d2==0) {
		return false;
		}
	else if (d1 == d2) {
		return true;
		}
	return false;	
}

function d1NEQd2(date1,date2){
	var dateformat="d/M/yyyy";
	var d1=getDateFromFormat(date1,dateformat);
	var pattern=/\//;
	//alert("regex" + pattern.test(date1));	
	//alert(date2);
	if(pattern.test(date2))   var d2 = getDateFromFormat(date2,"d/M/yyyy");
	if(!pattern.test(date2))   var d2 = getDateFromFormat(date2,"ddMMyyyy");
	if (d1==0 || d2==0) {
		return false;
		}
	else if (d1 != d2) {
		return true;
		}
	return false;	
}

function d1LTd2(date1,date2){
	var dateformat="d/M/yyyy";
	var d1=getDateFromFormat(date1,dateformat);
	var pattern=/\//;
	//alert("regex" + pattern.test(date1));	
	//alert(date2);
	if(pattern.test(date2))   var d2 = getDateFromFormat(date2,"d/M/yyyy");
	if(!pattern.test(date2))   var d2 = getDateFromFormat(date2,"ddMMyyyy");
		//alert(d1 + " - " +d2);
	//var d2=parseDate(date2);
	if (d1==0 || d2==0) {
		return false;
		}
	else if (d1 < d2) {
		return true;
		}
	return false;	
}

function d1LEd2(date1,date2){
	var dateformat="d/M/yyyy";
	var d1=getDateFromFormat(date1,dateformat);
	var pattern=/\//;
	//alert("regex" + pattern.test(date1));	
	//alert(date2);
	if(pattern.test(date2))   var d2 = getDateFromFormat(date2,"d/M/yyyy");
	if(!pattern.test(date2))   var d2 = getDateFromFormat(date2,"ddMMyyyy");
	if (d1==0 || d2==0) {
		return false;
		}
	else if (d1 <= d2) {
		return true;
		}
	return false;	
}
*/