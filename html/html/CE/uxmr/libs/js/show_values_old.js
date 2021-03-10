var Url = {

    // public method for url encoding
    encode : function (string) {
        return escape(this._utf8_encode(string));
    },

    // public method for url decoding
    decode : function (string) {
        return this._utf8_decode(unescape(string));
    },

    // private method for UTF-8 encoding
    _utf8_encode : function (string) {
        string = string.replace(/\r\n/g,"\n");
        var utftext = "";

        for (var n = 0; n < string.length; n++) {

            var c = string.charCode(n);

            if (c < 128) {
                utftext += String.fromCharCode(c);
            }
            else if((c > 127) && (c < 2048)) {
                utftext += String.fromCharCode((c >> 6) | 192);
                utftext += String.fromCharCode((c & 63) | 128);
            }
            else {
                utftext += String.fromCharCode((c >> 12) | 224);
                utftext += String.fromCharCode(((c >> 6) & 63) | 128);
                utftext += String.fromCharCode((c & 63) | 128);
            }

        }

        return utftext;
    },

    // private method for UTF-8 decoding
    _utf8_decode : function (utftext) {
        var string = "";
        var i = 0;
        var c = c1 = c2 = 0;

        while ( i < utftext.length ) {

            c = utftext.charCodeAt(i);

            if (c < 128) {
                string += String.fromCharCode(c);
                i++;
            }
            else if((c > 191) && (c < 224)) {
                c2 = utftext.charCodeAt(i+1);
                string += String.fromCharCode(((c & 31) << 6) | (c2 & 63));
                i += 2;
            }
            else {
                c2 = utftext.charCodeAt(i+1);
                c3 = utftext.charCodeAt(i+2);
                string += String.fromCharCode(((c & 15) << 12) | ((c2 & 63) << 6) | (c3 & 63));
                i += 3;
            }

        }

        return string;
    }

}

/***********************************************
* Form Field Progress Bar- By Ron Jonk- http://www.euronet.nl/~jonkr/
* Modified by Dynamic Drive for minor changes
* Script featured/ available at Dynamic Drive- http://www.dynamicdrive.com
* Please keep this notice intact
***********************************************/

function textCounter(field,counter,maxlimit,linecounter) {
	// text width//
	var fieldWidth =  parseInt(field.offsetWidth);
	var charcnt = field.value.length;        

	// trim the extra text
	if (charcnt > maxlimit) { 
		field.value = field.value.substring(0, maxlimit);
	}

	else { 
	// progress bar percentage
	var percentage = parseInt(100 - (( maxlimit - charcnt) * 100)/maxlimit) ;
	document.getElementById(counter).style.width =  parseInt((fieldWidth*percentage)/100)+"px";
	document.getElementById(counter).innerHTML="Limit: "+percentage+"%"
	// color correction on style from CCFFF -> CC0000
	setcolor(document.getElementById(counter),percentage,"background-color");
	}
}

function setcolor(obj,percentage,prop){
	obj.style[prop] = "rgb(80%,"+(100-percentage)+"%,"+(100-percentage)+"%)";
}



// *****************************************************************************************
function value_of(campo, forms){
	if (!forms) forms=0;
	f=document.forms[forms];
	el=f.elements;
	if (!el[campo]) return 0;
	eln=el.length;
	for (i=0;i<eln;i++) {
	nome=el[i].name;
	tipo=el[i].type;
	//alert(tipo);
	if (nome==campo){
//alert(nome);		

//alert(el[campo][el[campo].selectedIndex].value);		
		if (tipo=='radio') {
				return radioval(campo, forms);
			}
		if (tipo=='checkbox') {
			
				if (el[campo].checked) return 1;
				else return 0;
			}
		if (tipo=='select-one') {
			//alert(campo+' - '+el[campo][el[campo].selectedIndex].value);
			return el[campo][el[campo].selectedIndex].value;
		}
		if (tipo!='radio' && tipo!='checkbox') return el[campo].value;
		}
	}
}

function radioval(campo, forms){
	if (!forms) forms=0;
	f=document.forms[forms];
	el=f.elements;
	value='';
	for (i=0;el[campo][i];i++){
		if (el[campo][i].checked) value=el[campo][i].value;
	}
	return value;
}

function radio_cond_radio(condizionante, valore, condizionato, forms){
	if (!forms) forms=0;
	f=document.forms[0];
	el=f.elements;
	pass=false;
	for (i=0;el[condizionante][i];i++) {
		if (el[condizionante][i].checked && el[condizionante][i].value==valore) pass=true;
	}
	if (pass){
		pass2=false;
		for (i=0;el[condizionato][i];i++){
			if (el[condizionato][i].checked) pass2=true;
		}
	}
	else pass2=true;
	return pass2;
}


function show_values() {

var w = window.open("",                    // URL (nessuno)
                       "RIASSUNTO",        // nome
                       "resizable,status,scrollbars,menubar"); // caratteristiche
 alert('HO APERTO LA FINESTRA');
var d = w.document;    // Per fare prima a scrivere

// alert('HO DEFINITO f ED el');
d.write('<HTML><HEAD><TITLE></TITLE></HEAD><BODY bgcolor=white>')
var f=w.opener.document.forms[0];
el=f.elements;
eln=el.length;
// alert('Numero campi '+eln)
// doc=op.window;
// d.write('<script language=javascript>');
// d.write('<center><b><font face=arial size=5> LISTA VARIABILI</font></b></center>');
d.write('<TABLE WIDTH="90%" border=1>');
for (i=0;i<eln;i++) {
nome=el[i].name;
tipo=el[i].type;
if (tipo=='select-one') {
j=el[i].selectedIndex;valore=el[i][j].value;
cella4='<TD height=3><FONT FACE=ARIAL SIZE=1>SELECTED INDEX= '+j+'</FONT><br></TD>'+"\n";} // fine if
else {valore=el[i].value} // fine else
if (tipo=='radio' || tipo=='checkbox') {
selez=el[i].checked;
cella4='<TD height=3><FONT FACE=ARIAL SIZE=1>CHECKED= '+selez+'</FONT><br></TD>'+"\n";} // fine if
if (tipo!='select-one' && tipo!='radio' && tipo!='checkbox') {
cella4='<TD height=3><font face=arial size=1 color=white>na<br></font></TD>'} // fine if
cella0='<TD height=3><FONT FACE=ARIAL SIZE=1>'+i+'</FONT><br></TD>'+"\n";
cella1='<TD height=3><FONT FACE=ARIAL SIZE=1>'+nome+'</FONT><br></TD>'+"\n";
cella2='<TD height=3><FONT FACE=ARIAL SIZE=1>VALORE= '+valore+'</FONT><br></TD>'+"\n";
cella3='<TD height=3><FONT FACE=ARIAL SIZE=1>TYPE= '+tipo+'</FONT><br></TD>'+"\n";
riga='<TR>'+cella0+cella1+cella2+cella3+cella4+'</TR>'+"\n";
d.write(''+riga);
} // fine for
d.write('</TABLE>'+"\n");
// d.write('<center><b><font face=arial size=5> FINE LISTA VARIABILI</font></b></center>');
d.write('<form><CENTER><INPUT TYPE=BUTTON VALUE="CHIUDI" onclick="self.close();"></CENTER></form>'+"\n");
d.write('</BODY></HTML>');
d.close();
} // fine show_values
// *****************************************************************************************

// *****************************************************************************************
// Javascript TOOLS per la visualizzazione delle variabili inviate al server
// VERSIONE 0.1b
// by ANDREA CASSA, 9 Novembre 1998
// *****************************************************************************************

// *****************************************************************************************
function show(Seccion){
//alert(Seccion);
document.getElementById(Seccion).style.display="";
}

function hide(Seccion){
//alert(Seccion);
document.getElementById(Seccion).style.display="none";
}

function carica_input(){
var nomiv=new Array();
valoriv=new Array();
var f=document.forms[0];
el=f.elements;
eln=el.length;
k=1;
nomiv[0]='';
valoriv[0]='';
len=0;
//alert('POP_NUM_UE='+document.forms[0].elements['POP_NUM_UE'].value);
//alert(eln);
var i=0;
		for (i=0;i<eln;i++) {
		//alert(i);
		nome=el[i].name;
		tipo=el[i].type;
		//if(nome.match('POP_NUM_')){alert(nome+tipo);}
		//alert(tipo+nome);
		
		if(tipo!='hidden' && tipo!='button' && tipo!='reset'){
		if(tipo=='radio'){
		len=el[nome].length;
//		alert(len);
			for (j=0;j<len;j++) {
				if(el[nome][j].checked){
				valoriv[k]=el[nome][j].value;
				//alert(i+') '+tipo+nome+' '+j+') '+valoriv[k]);
				k++;
				i++;
				break;
				}
			}
		//i=i+len;
		}else if(tipo=='select-one'){
			indice=el[i].selectedIndex;
			valoriv[k]=el[i][indice].value;
			//alert(tipo+nome+indice+valoriv[k]); 
		k++;
		}else if (tipo=='checkbox' && !(el[i].value =='NA' || el[i].value =='-9944')){
				if (el[i].checked==true){
					valoriv[k]=el[i].value; 
//					alert(tipo+nome+valoriv[k]); 
					k++;
					}else{
					valoriv[k]=0; 
//					alert(tipo+nome+valoriv[k]); 
					k++;
					}
		}else{
		valoriv[k]=el[i].value; 
		//alert(tipo+nome+valoriv[k]); 
		k++;
		}
		}
		}
return valoriv;
}
function controlla_output(){
//var nomiv=new Array();
var valorin=new Array();
var f=document.forms[0];
el=f.elements;
eln=el.length;
k=1;
//nomiv[0]='';
valorin[0]='';
conto=0;
l=0;
		for (i=0;i<eln;i++) {
		nome=el[i].name;
		tipo=el[i].type;
		
		
		if(tipo!='hidden' && tipo!='button' && tipo!='reset'){
		if(tipo=='radio'){
		l=el[nome].length;
//		alert(l);
			for (j=0;j<l;j++) {
				if(el[nome][j].checked){
				valorin[k]=el[nome][j].value;
				//alert(inp[k]+"--"+valorin[k]);
					if(valorin[k]!= inp[k]){
					conto++;
					//alert(nome+tipo);
					}
				k++;
				i++;
				break;
				}
			}
		//i=i+l;
			}else if(tipo=='select-one'){
			indice=el[i].selectedIndex;
			valorin[k]=el[i][indice].value;
//			alert(tipo+nome+indice+valoriv[k]); 
				if(valorin[k]!= inp[k]){
				conto++;
				//alert(nome+tipo);
				}
		k++;
		}else if (tipo=='checkbox' ){
				if (el[i].checked==true){
					valorin[k]=el[i].value; 
//					alert(tipo+nome+valorin[k]); 
						if(valorin[k]!= inp[k]){
						if(el[i].value =='NA' || el[i].value =='-9944' || el[i].value =='Non applicabile' || el[i].value =='NON APPLICABILE'){
							//alert('1a'+nome+tipo+el[i].value);
							}else{
							//alert('2a'+nome+tipo);
							conto++;
							}
						}
					k++;
					}else{
					valorin[k]=0; 
//					alert(tipo+nome+valorin[k]);
						if(valorin[k]!= inp[k]){
							if(el[i].value =='NA' || el[i].value =='-9944' || el[i].value =='Non applicabile' || el[i].value =='NON APPLICABILE'){
							//alert('1b'+nome+tipo+'value:'+el[i].value);
							}else{
							conto++;
							//alert('2b'+nome+tipo+conto);
							}
						
						}
					k++;
					}
		}else{
		valorin[k]=el[i].value; 
		
			if(valorin[k]!= inp[k] && el[i].name !='RICHIESTA_NOTE'){
			if(el[i].value =='NA' || el[i].value =='-9944' || el[i].value =='Non applicabile' || el[i].value =='NON APPLICABILE'){
							//alert('1c'+nome+tipo+'value:'+el[i].value);
							}else{
							conto++;
							//alert('2c'+nome+tipo+conto);
							}
			//alert(nome+tipo);
			}
		k++;
				}
		}
		//if (nome=='SPEC_TIPO_FARMACO'){
		//alert(tipo+nome);
		//}
		}
//alert(conto);
return conto;
}


function force_focus() {
if (!(window.focus())) {window.focus()}
setTimeout("force_focus2()",1000);
return 0;
} // fine funzione
// *****************************************************************************************

// *****************************************************************************************
function force_focus2() {
if (!(window.focus())) {window.focus()}
setTimeout("force_focus()",1000);
return 0;
} // fine funzione
// *****************************************************************************************

// *****************************************************************************************
      
// *****************************************************************************************

function congela() {
alert('Non puoi modificare manualmente questo campo!\n'+'Per favore, usare i pulsanti Sfoglia, Ricerca e Cancella');
return 0;
} // fine funzione

// *****************************************************************************************

function sbianca() {
var i_sb, nome_campo, arg_l;
if (sbianca.arguments.length) {
	for (i_sb=0;i_sb<sbianca.arguments.length;i_sb++) {
		nome_campo=sbianca.arguments[i_sb];
		if (document.forms[0].elements[nome_campo]){
			document.forms[0].elements[nome_campo].value='';
		}
	} // fine for
} // fine if 
else {return false}
return 0;
} // fine funzione

function radioclear (nome) {
el=document.forms[0].elements;
num_bot=el[nome].length; // **************************************************** numero di bottoni
// ***************************************************************************** Netscape (<=4.6) restituisce num_bot=null per array di radio con 1 solo elemento
if (num_bot==null) { // ******************************************************** C'e' un solo radio e si sta usando NS<=4.6
check=el[nome].checked; // ************************************************** La proprieta' checked del radio singolo
if (check) {el[nome].checked=false;//el[nome].value='';
	} // ************************************** c'e' un solo bottone ed e' selezionato, lo sbianco
return true // ***************************************************************** ritorno true
} // *************************************************************************** fine if in num_bot
// ***************************************************************************** Se arriva qui o l'array e' di piu' elementi o non si sta usando Netscape
for (ind=0;ind<num_bot;ind++) {// ********************************************** Percorro il ciclo dei radio omonimi
if (el[nome][ind].checked){el[nome][ind].checked=false;//el[nome][ind].value='';
	} // ********************* se ne trovo uno selezionato ritorno 0
} // *************************************************************************** fine ciclo
return true;
} // fine funzione


function prepara_parametri(nomeform) {
if (!nomeform){nomeform='0';}
var f=document.forms[nomeform];
//var f=document.forms[0];
var parametri='';
el=f.elements;
eln=el.length;
for (ii=0;ii<eln;ii++) {
nome=el[ii].name;
tipo=el[ii].type;
//if (tipo=='select-one') {
//	jj=el[ii].selectedIndex;
//	valore=el[ii][jj].value;
//} // fine if
//else {
//	valore=el[ii].value} // fine else
//if (tipo=='radio' || tipo=='checkbox') {
//	valore=radiovalue(nome,'0');
//} // fine if
if (tipo=='hidden'){
	valore=el[nome].value;
	parametri+=nome+'='+valore+'&';
}
} // fine for
return parametri;
}

function ossc_errore_js() {
	var parametri=prepara_parametri();
	var nomescript='/cgi-bin/ossc_errore_js?'+parametri;
	nomescript=nomescript.replace(/\'/g,'`');
	nomescript=nomescript.replace(/\"/g,'``');
	location.href=nomescript;
	//location.href='/cgi-bin/ossc_errore_js';
}
function prepara_decode() {
	for (k=0;k<document.forms.length;k++){
	var f=document.forms[k];
	el=f.elements;
	eln=el.length;
      
		for (i=0;i<eln;i++) {
		nome=el[i].name;
		tipo=el[i].type;
                //alert(nome+' '+tipo+' ');

			if (nome.substring(0,2)=='D_'){
				nomeselect=nome.substring(2,nome.length);
				if (el[nomeselect]){
					valore='';
					if (el[nomeselect].type=='select-one'){
						j=el[nomeselect].selectedIndex;
						valore=el[nomeselect][j].text;
						el[nome].value=valore;
						//alert (nome+'='+valore);
					}else if (el['DESC_'+nomeselect] && el['S_'+nomeselect] && el['S_'+nomeselect].type=='select-multiple'){
						valore=el['DESC_'+nomeselect][0].text;
						el[nome].value=valore;
						//alert (nome+'='+valore);
					}else if (el['S_'+nomeselect] && el['S_'+nomeselect].type=='select-multiple'){
						valore=el['S_'+nomeselect][0].text;
						el[nome].value=valore;
						//alert (nome+'='+valore);
					}else if (el['DESC_'+nomeselect] && el['DESC_'+nomeselect].type=='select-multiple'){
						valore=el['DESC_'+nomeselect][0].text;
						el[nome].value=valore;
						//alert (nome+'='+valore);
					}else if (el['DESC_'+'D_'+nomeselect] && el['DESC_'+'D_'+nomeselect].type=='select-multiple'){
						valore=el['DESC_'+'D_'+nomeselect][0].text;
						el[nome].value=valore;
					//alert (nome+'='+valore);
					}
					
				}
			}
			if (el['I'+nome] && el['I'+nome].type.substring(0,6)=='select' && (el[nome].type=='text' || el[nome].type=='hidden') ){
				//alert('Sono qui');
				el[nome].value=el['I'+nome][el['I'+nome].selectedIndex].text;
			}
			if ((tipo=='text' || tipo=='hidden' || tipo=='textbox') && (el[nome].value.substr(0,5)=='_____' || el[nome].value.substr(0,5)=='-----')){
				el[nome].value='';
			}
			if (tipo=='radio'){
				//alert (nome);
				
				if (!radiovalue(nome,k) && radiovalue(nome,k)!='0'){
					//alert (k+' '+nome+' '+radiovalue(nome,k));
					el[nome][0].value='';
					el[nome][0].checked=true;
					
				}
			}
			if (tipo=='checkbox'){
				if (!el[nome].checked){
					el[nome].value='';
					el[nome].checked=true;
					//document.write('<input type=checkbox name='+nome+' value="" checked>');
				}
			}
		}
		
	}
}

//function prepara_checkbox_onload() {
//	for (k=0;k<document.forms.length;k++){
//	var f=document.forms[k];
//	el=f.elements;
//	eln=el.length;
//		for (i=0;i<eln;i++) {
//		nome=el[i].name;
//		tipo=el[i].type;
//			if (tipo=='checkbox'){
//				alert (nome+'-'+el[nome].checked+'-'+el[nome].value);
//				if (el[nome].checked && !el[nome].value){
//					el[nome].checked=false;
//				}
//			}
//		}
//	}
//}

function precompila_tendine(nome_campo_hidden,nomeform) {
  if (!nomeform){nomeform='0';}
  chiamante=document.forms[nomeform];
  elementi_chiamante=chiamante.elements;

if (elementi_chiamante[nome_campo_hidden]){
	if (elementi_chiamante[nome_campo_hidden].value !=''){
		elementi_chiamante['S_'+nome_campo_hidden][0].text=elementi_chiamante[nome_campo_hidden].value;
	}
}
return 0;
}

function precompila_tendine_auto() {
	for (k=0;k<document.forms.length;k++){
	var f=document.forms[k];
	var tipi;
	el=f.elements;
	eln=el.length;
		for (i=0;i<eln;i++) {
		nome=el[i].name;
		tipo=el[i].type;
		//tipi=tipi+tipo+'\\n';
			if (el['S_'+nome] && (el['S_'+nome].type=='select-one' || el['S_'+nome].type=='select-multiple')){
				
				if (el[nome].value !=''){
					el['S_'+nome][0].text=el[nome].value;
				}
			}
			if (el['DESC_'+nome] && (el['DESC_'+nome].type=='select-one' || el['DESC_'+nome].type=='select-multiple')){
				
				if (el[nome].value !=''){
					if (nome.substr(0,3)=='ID_'){
						alert ('D_'+nome.substr(3,nome.length));
						el['DESC_'+nome][0].text=el['D_'+nome.substr(3,nome.length)].value;
					}else if (el['D_'+nome]) {
						el['DESC_'+nome][0].text=el['D_'+nome].value;
					}else {
						el['DESC_'+nome][0].text=el[nome].value;
					}
				}
			}
		}
	}
	//alert (tipi);
return 0;
}


function detect_browser(){
// Browser Detection
browser_name = navigator.appName;
browser_version = parseFloat(navigator.appVersion); 
if (browser_name == "Netscape" && browser_version >= 3.0) { roll ='true'; }
else if (browser_name == "Microsoft Internet Explorer" && browser_version >= 4.0) { roll = 'true'; }
else { roll = 'false'; }
// Preload images, if browser supports mouseovers
if (roll == 'true') {
	var imglist = new Array ("/images/sfoglia_on.gif","/images/cerca_on.gif","/images/cancella_on.gif", "/images/naviga_on.gif");
	var imgs = new Array();
	var count;
	if (document.images){
       		for (count=0; count<imglist.length; count++){
       			imgs[count]=new Image(); imgs[count].src=imglist[count];
        	}
        }
}
// Use this code if you are only doing one mouseover
}
function msover1(img,ref) {if (roll=='true') {document.images[img].src = ref;}}
function msout1(img,ref)  {if (roll=='true') {document.images[img].src = ref;}}
function apri_window (source,nome) {
	//newwin = window.open(source,nome, 'width=450,height=425,scrollbars=yes')
	//apre sempre UNA SOLA finestra
	var newwin;
	newwin = window.open(source,'window2', 'width=450,height=425,scrollbars=yes,resizable=yes')
	//if (!window.opener) {newwin.opener = self}
}
function apri_windowc (source,nome) {
	newwin = window.open(source,'window2', 'left=0,screenX=0,top=0,screenY=0,width=800,height=600,scrollbars=yes,toolbar=yes');
	if (!window.opener) {newwin.opener = self}
}
function apri_window_big (source,nome) {
	//newwin = window.open(source,nome, 'width=450,height=425,scrollbars=yes')
	//apre sempre UNA SOLA finestra
	if (nome =='') {nome='bwindow';}
	newwin = window.open(source,nome, 'width=750,height=525,scrollbars=yes,resizable=yes')
	if (!window.opener) {newwin.opener = self}
}
function apri_window_pub (source,nome) {
	//newwin = window.open(source,nome, 'width=450,height=425,scrollbars=yes')
	//apre sempre UNA SOLA finestra
	if (nome =='') {nome='bwindow';}
	newwin = window.open(source,nome, 'width=550,height=525,scrollbars=yes,resizable=yes')
	if (!window.opener) {newwin.opener = self}
}
function apri_windowc (source,nome) {
	newwin = window.open(source,'window2', 'left=0,screenX=0,top=0,screenY=0,width=800,height=600,scrollbars=yes,toolbar=yes');
	if (!window.opener) {newwin.opener = self}
}

function sbianca_s(descrizione,dimensione,nomeform,stringavuota) {
  if (!nomeform){nomeform='0'}
  chiamante=document.forms[nomeform];
  elementi_chiamante=chiamante.elements;

  if (dimensione=='1'){
	elementi_chiamante[descrizione][0].value='';
	elementi_chiamante[descrizione][0].text=stringavuota;
  }else {
  	var i,j,k;
  	var vettV=new Array();
  	var vettT=new Array();
  	var eliminati=0;
  	for (i=0;i<elementi_chiamante[descrizione].options.length;i++){
  		if (elementi_chiamante[descrizione][i].selected && elementi_chiamante[descrizione][i].value){
  			eliminati++;
			elementi_chiamante[descrizione][i].value='';
			elementi_chiamante[descrizione][i].text='';
  		}else if (elementi_chiamante[descrizione][i].value) {
  			vettV[i]=elementi_chiamante[descrizione][i].value;
  			vettT[i]=elementi_chiamante[descrizione][i].text;
  		}
  	}
	if (eliminati>0 && elementi_chiamante[descrizione].options.length>1){
  		//Inizio Parte aggiunta da testare
  		elementi_chiamante[descrizione].options.length=1;
  		j=0;
  		for (k=0;k<i;k++){
  			if (vettV[k] && vettT[k]){
  				elementi_chiamante[descrizione].options.length++;
  				elementi_chiamante[descrizione][j].value=vettV[k];
				elementi_chiamante[descrizione][j].text=vettT[k];
				j++; 			
  			}
		}
		//Fine Parte aggiunta da testare
    	}
  	if (!eliminati){alert('Selezionare gli elementi che si vuole eliminare,\nquindi cliccare su Cancella!');}
	if (elementi_chiamante[descrizione].options.length<=1 && elementi_chiamante[descrizione][0].value==''){
		elementi_chiamante[descrizione][0].text=stringavuota;
	}
  }
  return 0;
}

function apri_window_small (source) {
        var newwin;
        newwin = window.open(source,'window1',
'width=450,height=500,scrollbars=yes')
        if (!window.opener) {
                newwin.opener = self
        }
}
///////////////////////////////////////////////////////////////
//                                                      
//     Funzione per bloccare chi scrive  nelle "Textarea",
//       in base alla lunhezza specificata in lung_ta
//            
//           Creata da  Gregorio Greco                      
//                                                     
///////////////////////////////////////////////////////////////

//stringa= new String("");

function errore_old(nome_form,lungh_ta){
var lungh=nome_form.value.length;

 if(lungh ==(lungh_ta-1)) {stringa.value=nome_form.value;}
 if(lungh >(lungh_ta-1)) {

alert('Attenzione: e\' stato raggiunto il limite dei caratteri da inserire:');
nome_form.value=stringa.value;
}
return(true);
}



function errore(nome_form,lungh_ta){
var lungh=nome_form.value.length;
if(lungh >(lungh_ta-1)) {
	alert('Attenzione: e\' stato raggiunto il limite dei caratteri da inserire!');
	nome_form.value=nome_form.value.substr(0,lungh_ta-1);
	return false;
}

//controllo sui caratteri speciali
if(nome_form.value.match('�')||nome_form.value.match('�')){
alert('Attenzione, non � possibile utilizzare caratteri speciali come: �,�');
	nome_form.focus;
	return false;
}
return true;
}

function errore_textarea(nome_form,lungh_ta,msg){
f=document.forms[0];
el=f.elements;
if(el[nome_form].value!=''){
	
var lungh=el[nome_form].value.length;
if(lungh >(lungh_ta-1)) {
	alert('Attenzione: e\' stato raggiunto il limite dei caratteri da inserire nel campo '+msg);
	el[nome_form].value=el[nome_form].value.substr(0,lungh_ta-1);
	el[nome_form].focus();
	return false;
}
}
if(el[nome_form].value.match('�')||el[nome_form].value.match('�')){
alert('Attenzione, non � possibile utilizzare caratteri speciali come: �,� nel campo '+msg);
	el[nome_form].focus();
	return false;
}
return true;
}



function controlla_form_doppi(){
	//function da richiamare nell'onload che permette di verificare se vi siano 
	//dei form doppi nel template, tranne i radiobutton
	
var nomiv=new Array();
valoriv=new Array();
var f=document.forms[0];
el=f.elements;
eln=el.length;
k=1;
nomiv[0]='';
valoriv[0]='';
for (i=0;i<eln;i++) {
		nome=el[i].name;
		tipo=el[i].type;
		
		for (j=0;j<eln;j++) {
			if(el[j].name==nome && i!=j && el[j].type!='radio'){
			alert(el[j].name+'-'+nome+'-'+el[j].value);
			return false;
			}
		
		}
		
	}
}

/*
//funzione per il controllo delle date aggiornata
//da Cristiano Campeggiani il 15/09/2005
function controlla_data_sys(nome,nomey,nomem,nomed,descrizione)
{
	f=document.forms[0];
	el=f.elements;
	d1=document.forms[0].elements['SYSDATE'].value;
	dsys=d1.substr(6,4)+d1.substr(3,2)+d1.substr(0,2);	
	
	//Controllo se mi tutti gli elementi della data hanno un valore numerico
	if((!(isNaN(parseInt(document.forms[0].elements[nomey].value)))) && 
		 (!(isNaN(parseInt(document.forms[0].elements[nomem].value)))) &&
		 (!(isNaN(parseInt(document.forms[0].elements[nomed].value)))))	
	{	//ho esattamente 3 elementi numerici
		if (parseInt(document.forms[0].elements[nomey].value) > 1990)
		{	//Costruisco la data nel formato yyyymmdd controllando
			//se il giorno e il mese sono maggiori di 9: formati quindi da 2 caratteri
			d2=document.forms[0].elements[nomey].value;			
			
			if (Number(document.forms[0].elements[nomem].value) > 9 )
				d2 += document.forms[0].elements[nomem].value;
			else
				d2 += "0" + Number(document.forms[0].elements[nomem].value);
						
			if (Number(document.forms[0].elements[nomed].value) > 9 )
				d2 += document.forms[0].elements[nomed].value;
			else
				d2 += "0" + Number(document.forms[0].elements[nomed].value);			
			
			//alert ('dsys: ' +  dsys + '\nd2:' + d2);
						
			if (dsys<d2)
			{
			 alert('Attenzione, '+descrizione+' non pu� essere successiva alla data odierna');
			 el[nome+'D'].focus();			 
			 return 1;	
			}
			else //OK
				return 0;
		}
		else
		{			
			alert('Attenzione l\'anno di '+descrizione+' deve essere posteriore al 1990');
			el[nome+'D'].focus();						 
			return 1;
		}
	}
	else
	{	//Costruisco la stringa come append degli elementi
		var strTest = new String(document.forms[0].elements[nomey].value+document.forms[0].elements[nomem].value+document.forms[0].elements[nomed].value);
		if (strTest.length == 0)
		{	//La data non � stata inserita
			delete strTest;			
			return 0;
		}
		else
		{			
			if (strTest.toUpperCase() == "NDNDND")
			{	//La data non � nacessaria: tutti gli elementi sono ND
				delete strTest;
				return 0;
			}
			else
			{
				alert('La  '+descrizione+' inserita non � valida');
				el[nome+'D'].focus();
				delete strTest;
				return 1;
			}
		}		
	}
	return 1;
}
*/

/****************************************************/
/*funzione per il controllo delle date aggiornata		*/
/*da Cristiano Campeggiani il 22/09/2005						*/
/****************************************************/
function controlla_data_sys(nome,nomey,nomem,nomed,descrizione)
{
	f=document.forms[0];
	el=f.elements;
	d1=document.forms[0].elements['SYSDATE'].value;	
	//data corrente
	dsys=d1.substr(6,4)+d1.substr(3,2)+d1.substr(0,2);	
	
	//costruisco la data passata come aaaammdd di esattamente 8 caratteri
	//se qualcosa va storto ritorna la stringa vuota
	d2 = build_extended_date(nome);	
	//alert(d2);
	if (!(d2.length == 0))
	{	//ho esattamente 3 elementi numerici
		
		//controllo aggiunto da Vera per saltare questi test nel caso non siano
		//presenti le variabili Y M D ma solo la HIDDEN
		
		if(document.forms[0].elements[nomey] && document.forms[0].elements[nomey].value!=''){
			if (parseInt(document.forms[0].elements[nomey].value) > 1990)
			{	//controllo che la data passata non sia posteriore alla data corrente						
				if (dsys<d2)
				{
				 alert('Attenzione, '+descrizione+' non pu� essere successiva alla data odierna');
				 el[nome+'D'].focus();			 
				 return 1;	
				}
				else //OK
					return 0;
			}
			else
			{			
				alert('Attenzione l\'anno di '+descrizione+' deve essere posteriore al 1990');
				el[nome+'D'].focus();						 
				return 1;
			}
		}else{
			return 0;
		}
	}
	else
	{	//Costruisco la stringa come append degli elementi
		var strTest = new String(document.forms[0].elements[nomey].value+document.forms[0].elements[nomem].value+document.forms[0].elements[nomed].value);
		if (strTest.length == 0)
		{	//La data non � stata inserita
			delete strTest;			
			return 0;
		}
		else
		{			
			if (strTest.toUpperCase() == "NDNDND")
			{	//La data non � nacessaria: tutti gli elementi sono ND
				delete strTest;
				return 0;
			}
			else
			{
				alert('La  '+descrizione+' inserita non � valida');
				el[nome+'D'].focus();
				delete strTest;
				return 1;
			}
		}		
	}
	return 1;
}



/****************************************************************/
/*						Cristiano Campeggiani															*/
/*la prossima funzione prende in ingresso il nome di 2 date			*/
/*nella forma <NOME_DATA_DT>, e che la data denominata lowdate	*/
/*non sia posteriore a quella denominata highDate								*/
/*MsgLowDate ,MsgHighDate sono idealmente il nome delle date		*/
/*cos� come sono visualizzate dal browser e sono utilizzate sia	*/
/*per la chiamata a controlla_data_sys che per gli alert				*/
/*Come per le altre funzioni la funzione ritorna con 1 per 			*/
/*segnalare un errore, viceversa torna 0 (Zero) se ha successo	*/
/****************************************************************/
function compare_dates(lowDate,MsgLowDate,highDate,MsgHighDate)
{	//controllo la validit� della prima data
	if (!controlla_data_sys(lowDate,lowDate + 'Y',lowDate + 'M',lowDate + 'D',MsgLowDate))
	{	//controllo la validit� della seconda data
		if (!controlla_data_sys(highDate,highDate + 'Y',highDate + 'M',highDate + 'D',MsgHighDate))
		{	//Costruisco le date in modo che siano nello stesso formato e con la stessa lunghezza
			//aaaammgg facendo 2 chiamate alla funzione build_extended_date
			var lower = build_extended_date(lowDate);
			var higher = build_extended_date(highDate);
			
			//A questo punto controllo che le date non siano ne vuote ne uguali alla stringa 'NDNDND'
			if ((!(lower.length == 0)) && (!(higher.length == 0)) && (!(lower.toUpperCase() == 'NDNDND')) && (!(higher.toUpperCase() == 'NDNDND')))
			{	//higher non deve essere posteriore a lower				
				if	(higher < lower)
				{
					
					//aggiunta da Vera per visualizzare le date in un formato con le /
					if(!(document.forms[0].elements[lowDate].value.match('/'))){
					
					var lowview=document.forms[0].elements[lowDate].value.substr(0,2)+'/';
					lowview+=document.forms[0].elements[lowDate].value.substr(2,2)+'/';
					lowview+=document.forms[0].elements[lowDate].value.substr(4,4);
					//alert ('low'+lowview);
					}else{
					var lowview=document.forms[0].elements[lowDate].value;
					}
					if(!(document.forms[0].elements[highDate].value.match('/'))){
					var highview=document.forms[0].elements[highDate].value.substr(0,2)+'/';
					highview+=document.forms[0].elements[highDate].value.substr(2,2)+'/';
					highview+=document.forms[0].elements[highDate].value.substr(4,4);
					
					//alert ('high'+highview);
					}else{
					var highview=document.forms[0].elements[highDate].value;
					}
					
					alert ('Attenzione: ' + MsgLowDate +' ('+lowview+')\nnon pu� essere posteriore a ' + MsgHighDate+' ('+highview+')');
					document.forms[0].elements[lowDate + 'D'].focus();
					return 1;
				}
				else //tutto ok
				{
					return 0;
				}					
			}
			else
			{				
				//alert ('Attenzione: ' + MsgLowDate + ' oppure\n ' + MsgHighDate + ' non � valutabile');
				return 0;
			}
		}
		else
		{
			//alert ('Attenzione: '  + MsgHighDate + ' non � valida');
			//document.forms[0].elements[highDate + 'D'].focus();
			return 1;
		}
	}
	else
	{
		//alert ('Attenzione: ' + MsgLowDate + ' non � valida');
		//document.forms[0].elements[lowDate + 'D'].focus();
		return 1;
	}
}

/******************************************************************/
/*Versione con controlli non bloccanti della funzione precedente	*/
/******************************************************************/
function soft_compare_dates(lowDate,MsgLowDate,highDate,MsgHighDate)
{	//controllo la validit� della prima data
	var bStop = 0;	
	
	if (!controlla_data_sys(lowDate,lowDate + 'Y',lowDate + 'M',lowDate + 'D',MsgLowDate))
	{	//controllo la validit� della seconda data
		if (!controlla_data_sys(highDate,highDate + 'Y',highDate + 'M',highDate + 'D',MsgHighDate))
		{	//Costruisco le date in modo che siano nello stesso formato e con la stessa lunghezza
			//aaaammgg facendo 2 chiamate alla funzione build_extended_date
			var lower = build_extended_date(lowDate);
			var higher = build_extended_date(highDate);
			
			//A questo punto controllo che le date non siano ne vuote ne uguali alla stringa 'NDNDND'
			if ((!(lower.length == 0)) && (!(higher.length == 0)) && (!(lower.toUpperCase() == 'NDNDND')) && (!(higher.toUpperCase() == 'NDNDND')))
			{
				//higher non deve essere posteriore a lower
				if	(higher < lower)
				{										
					var strMsg = 'Attenzione: ' + MsgLowDate  + ' ( '+ format_msg_date(document.forms[0].elements[lowDate].value) + ' )';
					strMsg = strMsg + ' dovrebbe essere precedente a ' + MsgHighDate;
					strMsg = strMsg + ' ( ' + format_msg_date(document.forms[0].elements[highDate].value) + ' )';
					strMsg = strMsg + ".\nPremere OK per continuare, Annulla per modificare " + MsgHighDate + ".";
											
					//if (window.confirm ('Attenzione: ' + MsgLowDate + '\nnon dovrebbe essere posteriore a ' + MsgHighDate + ".\nPremere OK per continuare, Annulla per modificare " + MsgLowDate))
					if (window.confirm (strMsg))
						return 0;
					else
					{
						document.forms[0].elements[highDate + 'D'].focus();
						return 1;
					}
				}
				return 0;
			}
			else
			{				
				//alert ('Attenzione: ' + MsgLowDate + ' oppure\n ' + MsgHighDate + ' non � valutabile');
				return 0;
			}
		}
		else
		{
			//alert ('Attenzione: '  + MsgHighDate + ' non � valida');
			//document.forms[0].elements[highDate + 'D'].focus();
			return 1;
		}
	}
	else
	{
		//alert ('Attenzione: ' + MsgLowDate + ' non � valida');
		//document.forms[0].elements[lowDate + 'D'].focus();
		return 1;
	}
}

/**********************************************************************/
/*Questa funzione prende in ingresso il nome di una data nel formato	*/
/*NOME_DATA_DT e costruisce la data nel formato aaaammgg, andando a 	*/
/*recuperare i valori dai corrispondenti elementi della form 					*/
/*Se per qualche ragione non posso costruire la data ritorno col			*/
/*valore ""																														*/
/**********************************************************************/
function build_extended_date(nomedt)
{	//costruissco i nomi delle variabili che "puntano"
	//rispettivamente al campo anno, mese e giorno
	var nomey = nomedt + 'Y';
	var nomem = nomedt + 'M';
	var nomed = nomedt + 'D';
	var new_date = "";	
	
	//ho commentato:
	//controllo aggiunto da Vera:
	//serve nel caso non siano presenti le variabili Y,M,D ma solo la HIDDEN con la data
	if(document.forms[0].elements[nomey] && document.forms[0].elements[nomey].value !=''){
	
	
	
	//Controllo se tutti gli elementi della data hanno un valore numerico
	if((!(isNaN(parseInt(document.forms[0].elements[nomey].value)))) && 
		 (!(isNaN(parseInt(document.forms[0].elements[nomem].value)))) &&
		 (!(isNaN(parseInt(document.forms[0].elements[nomed].value)))))	
	{	//ho esattamente 3 elementi numerici		
			new_date = document.forms[0].elements[nomey].value;			
			
			if (Number(document.forms[0].elements[nomem].value) > 9 )
				new_date += document.forms[0].elements[nomem].value;
			else
				new_date += "0" + Number(document.forms[0].elements[nomem].value);
						
			if (Number(document.forms[0].elements[nomed].value) > 9 )
				new_date += document.forms[0].elements[nomed].value;
			else
				new_date += "0" + Number(document.forms[0].elements[nomed].value);
	}
	
//controllo aggiunto da Vera vedi sopra
}else{
	if(Number(document.forms[0].elements[nomedt].value.substr(6))>1977){
	new_date =document.forms[0].elements[nomedt].value.substr(6);
	new_date +=document.forms[0].elements[nomedt].value.substr(3,2);
	new_date +=document.forms[0].elements[nomedt].value.substr(0,2);
	}
}
	
	//alert ('Data estesa:' + new_date);
	
	return new_date;
}

 
function sbianca_radio_checkbox() {
	for (k=0;k<document.forms.length;k++){
	var f=document.forms[k];
	var el=f.elements;
	var eln=el.length;
	var vet_pass=new Array();
//      alert("somo qui");
		for (i=0;i<eln;i++) {
		nome=el[i].name;
		tipo=el[i].type;
                // alert(nome+' '+tipo+' ');
			if (tipo=='radio'){
				if (!radiovalue(nome,k) && radiovalue(nome,k)!='0'){
					for (ii=0;ii<eln;ii++) {
						nome1=el[ii].name;
						tipo1=el[ii].type;
						if (tipo1=='hidden' && nome1=='' && el[i].name!='' && vet_pass[nome] != '1'){
							el[ii].name=nome;
							el[i].name='dummy';
							vet_pass[nome]=1;
						}
					}
				}
			}
			if (tipo=='checkbox'){
				if (!el[nome].checked){
					for (ii=0;ii<eln;ii++) {
						nome1=el[ii].name;
						tipo1=el[ii].type;
						if (tipo1=='hidden' && nome1=='' && el[i].name!='' && vet_pass[nome] != '1'){
							el[ii].name=nome;
							el[ii].name='dummy';
							vet_pass[nome]=1;
						}
					}
				}
			}
		}
	}
}

function prepara_decode_new() {
	for (k=0;k<document.forms.length;k++){
	var f=document.forms[k];
	el=f.elements;
	eln=el.length;
//      alert("somo qui");
		for (i=0;i<eln;i++) {
		nome=el[i].name;
		tipo=el[i].type;
                // alert(nome+' '+tipo+' ');

			if (nome.substring(0,2)=='D_'){
				nomeselect=nome.substring(2,nome.length);
				if (el[nomeselect]){
					valore='';
					if (el[nomeselect].type=='select-one'){
						j=el[nomeselect].selectedIndex;
						valore=el[nomeselect][j].text;
						el[nome].value=valore;
						//alert (nome+'='+valore);
					}else if (el['DESC_'+nomeselect] && el['S_'+nomeselect] && el['S_'+nomeselect].type=='select-multiple'){
						valore=el['DESC_'+nomeselect][0].text;
						el[nome].value=valore;
						//alert (nome+'='+valore);
					}else if (el['S_'+nomeselect] && el['S_'+nomeselect].type=='select-multiple'){
						valore=el['S_'+nomeselect][0].text;
						el[nome].value=valore;
						//alert (nome+'='+valore);
					}else if (el['DESC_'+nomeselect] && el['DESC_'+nomeselect].type=='select-multiple'){
						valore=el['DESC_'+nomeselect][0].text;
						el[nome].value=valore;
						//alert (nome+'='+valore);
					}else if (el['DESC_'+'D_'+nomeselect] && el['DESC_'+'D_'+nomeselect].type=='select-multiple'){
						valore=el['DESC_'+'D_'+nomeselect][0].text;
						el[nome].value=valore;
						//alert (nome+'='+valore);
					}
					
				}
			}
			if (el['I'+nome] && el['I'+nome].type.substring(0,6)=='select' && (el[nome].type=='text' || el[nome].type=='hidden') ){
				//alert('Sono qui');
				el[nome].value=el['I'+nome][el['I'+nome].selectedIndex].text;
			}
			//if ((tipo=='text' || tipo=='hidden' || tipo=='textbox') && (el[nome].value.substr(0,5)=='_____' || el[nome].value.substr(0,5)=='-----')){
			//	el[nome].value='';
			//}
		}
	}
}

/**********************************************************/
/*Cristiano Campeggiani																		*/
/*Questa funzione accetta in ingresso il nome di una data */
/*nel formato <nome_data_dt> e la restituisce nel formato	*/
/*gg/mm/aaaa, se non pu� costruire una data in questo			*/
/*formato restituisce una stringa vuota										*/
/**********************************************************/
function format_msg_date(namedt)
{
	var strRet = "", bError = 0;
	
	//controllo la lunghezza della stringa ricevuta
	switch (namedt.length)
	{
		case 8:
			//controllo che sia un numero intero, che quindi sia stata passata in ingresso
			//la data nel formato ggmmaaaa
			if (Number(namedt) > 0)
				strRet = namedt.substr(0,2) + "/" + namedt.substr(2,2) + "/"  + namedt.substr(4,4);
			else
				bError = 1;
			break;			
		case 10:
			//controllo che la data sia esattamente nella forma "gg/mm/aaaa"
			if ((Number(namedt.substr(0,2)) > 0) &&
					(namedt.substr(2,1) ==  "/") &&
					(Number(namedt.substr(3,2)) > 0) &&
					(namedt.substr(5,1)  == "/") &&
					(Number(namedt.substr(6,4)) > 0))
				strRet = namedt;
			else
				bError = 1;
			break;			
		default:
			//esco con una stringa vuota
			strRet = "";
			break;			
	}
	
	if (bError)
		alert("Attenzione Data non valida: " + namedt);
				
	return strRet;
}


/************************************************************************/
/*Questa funzione accetta il nome di una data in formato <nome_data_dt>	*/
/*e controlla se esistono le variabili HIDDEN delle singole parti, ossia*/
/*<nome_data_dt(D|M|Y)> se non esistono le crea.												*/
/*Il secondo parametro di input specifica in quale form andare a cercare*/
/*ed eventualmente creare gli elementi hidden														*/
/************************************************************************/
function verify_DMY(namedt,form_index)
{	
	//alert("obj1 --> " + document.getElementsByName(namedt + "D").length + "\nobj2 --> " + document.getElementsByName(namedt + "D").length + "\nobj3 --> " + document.getElementsByName(namedt + "D").length );
	//alert("Nome Form:\t" + document.forms[0].name + "\nForm length:\t" + document.getElementsByName(document.forms[0].name).length);

	
	//Controllo se devo creare l'elemento del tipo nome_data_dtd
	if (document.getElementsByName(namedt + "D").length == 0)
	{		
		if (append_hidden_node(namedt + 'D',"",form_index))
		{
			//alert("Attenzione errore:");
			return 1;
		}		
	}
	
	//Controllo se devo creare l'elemento del tipo nome_data_dtm
	if (document.getElementsByName(namedt + "M").length == 0)
	{		
		if (append_hidden_node(namedt + 'M',"",form_index))
		{
			//alert("Attenzione errore:");
			return 1;
		}
	}
	
	//Controllo se devo creare l'elemento del tipo nome_data_dty
	if (document.getElementsByName(namedt + "Y").length == 0)
	{		
		if (append_hidden_node(namedt + 'Y',"",form_index))
		{
			//alert("Attenzione errore:");
			return 1;
		}
	}
		
	return 0;	
}


/****************************************************************/
/*Questa funzione crea una nuovo nodo input hidden assegandola	*/
/*alla form specificata da input, di conseguenza i parametri		*/
/*accettati da input sono																				*/
/*	node_name		= nome del nuovo nodo da creare,								*/
/*	node_value 	=	valore del nuovo nodo da creare,							*/		
/*	form_name		=	nome della form a cui assegnare								*/
/* 								la nuova variabile hidden.										*/
/****************************************************************/
function append_hidden_node(node_name,node_value,form_index)
{	//alert("node_name:\t"	 + node_name + "\nnode_value:\t" + node_value + "\nform_name:\t" + form_index);
	var oParent = null, new_element = null;	
	
	//alert("sto creando il nuovo elemento");
			
	//acquisisco il riferimento alla form da aggiornare
	if ((oParent = document.forms(form_index)) != null)
	{	//alert("nome form:\t" + oParent.name);
		//creo il nuovo tag e ne setto gli attributi name e value come stringa
		//vedi le specifiche per creare i tag input con il metodo createElement
		strTag = "<input " + "name='" + node_name + "' value='" + node_value + "' />";
		
		//alert("strTag:\t" + strTag);
		
		if ((new_element = document.createElement(strTag)) != null)
		{	//voglio che il nuovo elemento sia hidden
			new_element.setAttribute("type","hidden");
			//inserisco come ultimo elemento della form l'oggetto appena creato		
			oParent.insertBefore(new_element);
			return 0;
		}		
	}
	
	//qualcosa � andato storto
	return 1;
}


function Cod_fisc_contr(cf)
{
f=document.forms[0];
el=f.elements;
el[cf].value=el[cf].value.toUpperCase();
if (el[cf]&&el[cf].value!='') {
  if (el[cf].value.length!=16)
  {
  	  alert('Attenzione!!! Il codice fiscale risulta essere errato');
	  	el[cf].focus();
	  	return false;
  }
  for (i = 0; i < el[cf].value.length; i++)  
  {
   Char =el[cf].value.charAt(i); 
//  alert(Char+' '+i);
   if (i<6||i==8||i==11||i==15)
   {
    if(Char < "A"||Char >"Z")
    {
//   alert(Char+' '+i);
 	    alert('Attenzione!!! Il codice fiscale risulta essere errato');
	  	el[cf].focus();
	  	return false;
    }
   }
   else
   {
    if(Char < "0" || Char > "9")
    {
  	  alert('Attenzione!!! Il codice fiscale risulta essere errato');
	  	el[cf].focus();
	  	return false;
    }
   }
   }
}
return true;
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

function Check_char(ct)
{
f=document.forms[0];
el=f.elements;
for (i = 0; i < el[ct].value.length; i++)  
  {
   Char =el[ct].value.charAt(i); 
    if((Char < "A"||Char >"Z")&&Char!=' '&&Char!='\'')
    {
//   alert(Char+' '+i);
 	    alert('Carattere non ammesso');
	  	el[ct].focus();
	  	return false;
    }
   }
return true;
}


function Conf_eleg()
{
 f=document.forms[0];
el=f.elements;
return Check_eleg();
//if (!Check_eleg())
//{
// if (!confirm('Il paziente non risulta eleggibile')) 
//   {
//   	return false;
//   }
//   else
//   {
//     el['ELEGG'].value=0;
//   }
//}
//else
//  {
//    alert('Il paziente risulta eleggibile');
//    el['ELEGG'].value=1;	 
//   }
//return true;
}

//function Check_eleg()
//{
//f=document.forms[0];
//el=f.elements;
//if (el['STORIA_INF'][el['STORIA_INF'].selectedIndex].value==1 ||
// el['STATO_IMMUNOSOP'][el['STATO_IMMUNOSOP'].selectedIndex].value==1 ||
// (el['GRAVIDANZA_ATTUALE']&&el['GRAVIDANZA_ATTUALE'][el['GRAVIDANZA_ATTUALE'].selectedIndex].value==1) ||
// el['CONTRACCETIVI'][el['CONTRACCETIVI'].selectedIndex].value==2 ||
// el['FIRMA_ALERT'][el['FIRMA_ALERT'].selectedIndex].value==2)
//  return false; 
//
//if (el['IMMUNO_12M'][el['IMMUNO_12M'].selectedIndex].value==1)
//{
// if (el['RICADUTE_12M'].value>1) return true;
// if (el['RICADUTE_12M_ESITI'][el['RICADUTE_12M_ESITI'].selectedIndex].value==2) return false;
// if (el['EDSS_ATTUALE'][el['EDSS_ATTUALE'].selectedIndex].value<4) return false;
// if (el['LESIONI_9'][el['LESIONI_9'].selectedIndex].value==1) return true;
// if (el['T1GD_POS'].value>0) return true;
//}
//if (el['RICADUTE_12M'].value<2) return false;
//if (el['RICADUTE_12M_ESITI'][el['RICADUTE_12M_ESITI'].selectedIndex].value==2) return false;
//if (el['EDSS_ATTUALE'][el['EDSS_ATTUALE'].selectedIndex].value<4) return false;
//if (el['INCREMENTO_T2'][el['INCREMENTO_T2'].selectedIndex].value==1) return true;
//if (el['COMPARSA_LESION'][el['COMPARSA_LESION'].selectedIndex].value==1) return true;
//return false;
//}
//


function Check_eleg_gen()
{
f=document.forms[0];
el=f.elements;
if (el['STORIA_INF'][el['STORIA_INF'].selectedIndex].value==1 )
{
 if (!confirm('Il paziente non risulta eleggibile\nvalore non corretto nel campo Infezioni in atto.\nAnnulla per correggere, Ok per accettare') )
 {
  el['STORIA_INF'].focus();
  return false;
 }
 else 
 {
     el['ELEGG'].value='0';
 }
}
if (el['STATO_IMMUNOSOP'][el['STATO_IMMUNOSOP'].selectedIndex].value==1 )
{
 if (!confirm('Il paziente non risulta eleggibile\nvalore non corretto nel campo Immunosoppressione/Immunodeficienza.\nAnnulla per correggere, Ok per accettare'))
 {
  el['STATO_IMMUNOSOP'].focus();
  return false;
 }
 else 
 {
     el['ELEGG'].value='0';
 }
}

if (el['GRAVIDANZA_ATTUALE']&&el['GRAVIDANZA_ATTUALE'][el['GRAVIDANZA_ATTUALE'].selectedIndex].value==1)
{
 if (!confirm('Il paziente non risulta eleggibile\nvalore non corretto nel campo Gravidanza in atto.\nAnnulla per correggere, Ok per accettare'))
 {
  el['GRAVIDANZA_ATTUALE'].focus();
  return false;
 }
 else 
 {
     el['ELEGG'].value='0';
 }
}
if (el['CONTRACCETIVI']&&el['CONTRACCETIVI'][el['CONTRACCETIVI'].selectedIndex].value==2 )
{
 if (!confirm('Il paziente non risulta eleggibile\nvalore non corretto nel campo Metodi contraccettivi.\nAnnulla per correggere, Ok per accettare')) 
 {
  el['CONTRACCETIVI'].focus();
  return false;
 }
 else 
 {
     el['ELEGG'].value='0';
 }
}
if (el['FIRMA_ALERT'][el['FIRMA_ALERT'].selectedIndex].value==2)
{
 if (!confirm('Il paziente non risulta eleggibile\nvalore non corretto nel campo Firma della carta di "allerta" su Tysabri.\nAnnulla per correggere, Ok per accettare')) 
 {
  el['FIRMA_ALERT'].focus();
  return false;
 }
 else 
 {
     el['ELEGG'].value='0';
 }
}
return true;
}

function Check_eleg_A()
{
if (el['IMMUNO_12M'][el['IMMUNO_12M'].selectedIndex].value==1)
{
 if (el['RICADUTE_12M'].value>1) 
 {
  el['ELEGG'].value='1';	 
  return true;
  }
 if (el['RICADUTE_12M'].value<1) 
 {
 if (!confirm('Il paziente non risulta eleggibile per A\nvalore non corretto nel campo N� di ricadute negli ultimi 12 mesi.\nAnnulla per correggere, Ok per accettare')) 
 {
  el['RICADUTE_12M'].focus();
  return false;
 }
 else 
 {
     el['ELEGG'].value='0';
 }
} 
	
 if (el['RICADUTE_12M_ESITI'][el['RICADUTE_12M_ESITI'].selectedIndex].value==2) 
{
 if (!confirm('Il paziente non risulta eleggibile per A\nvalore non corretto nel campo ricadute con esiti.\nAnnulla per correggere, Ok per accettare')) 
 {
  el['RICADUTE_12M_ESITI'].focus();
  return false;
 }
 else 
 {
     el['ELEGG'].value='0';
 }
} 
if (el['EDSS_ATTUALE'][el['EDSS_ATTUALE'].selectedIndex].value<4) 
{
 if (!confirm('Il paziente non risulta eleggibile per A\nvalore non corretto nel campo EDSS attuale.\nAnnulla per correggere, Ok per accettare')) 
 {
  el['EDSS_ATTUALE'].focus();
  return false;
 }
 else 
 {
     el['ELEGG'].value='0';
 }
} 
 if (el['LESIONI_9'][el['LESIONI_9'].selectedIndex].value==1) 
 {
  el['ELEGG'].value='1';	 
  return true;
 }
 if (el['T1GD_POS'].value>0) 
  {
  el['ELEGG'].value='1';	 
  return true;
 }
}
else
 {
 if (!confirm('Il paziente non risulta eleggibile per A\nvalore non corretto nel campo Il paziente � stato sottoposto ad un trattamento per almeno 12 mesi con immunomodulanti.\nAnnulla per correggere, Ok per accettare')) 
 {
  el['IMMUNO_12M'].focus();
  return false;
 }
 else 
 {
     el['ELEGG'].value='0';
 }
}
return true;
}

function Check_eleg_B()
{
if (el['RICADUTE_12M'].value<2) 
{
 if (!confirm('Il paziente non risulta eleggibile per B\nvalore non corretto nel campo N� di ricadute negli ultimi 12 mesi.\nAnnulla per correggere, Ok per accettare')) 
 {
  el['RICADUTE_12M'].focus();
  return false;
 }
 else 
 {
     el['ELEGG'].value='0';
 }
} 
if (el['RICADUTE_12M_ESITI'][el['RICADUTE_12M_ESITI'].selectedIndex].value==2) 
{
 if (!confirm('Il paziente non risulta eleggibile per B\nvalore non corretto nel campo ricadute con esiti.\nAnnulla per correggere, Ok per accettare')) 
 {
  el['RICADUTE_12M_ESITI'].focus();
  return false;
 }
 else 
 {
     el['ELEGG'].value='0';
 }
} 
if (el['EDSS_ATTUALE'][el['EDSS_ATTUALE'].selectedIndex].value<4) 
{
 if (!confirm('Il paziente non risulta eleggibile per B\nvalore non corretto nel campo EDSS attuale.\nAnnulla per correggere, Ok per accettare')) 
 {
  el['EDSS_ATTUALE'].focus();
  return false;
 }
 else 
 {
     el['ELEGG'].value='0';
 }
} 
if (el['INCREMENTO_T2'][el['INCREMENTO_T2'].selectedIndex].value==1) 
 {
  el['ELEGG'].value='1';	 
  return true;
 }

if (el['COMPARSA_LESION'][el['COMPARSA_LESION'].selectedIndex].value==1) 
 {
  el['ELEGG'].value='1';	 
  return true;
 }
 if (!confirm('Il paziente non risulta eleggibile per B\nvalore non corretto nei campi Incremento significativo delle aree in T2 rispetto alla RMN precedente e/o Comparsa di nuove lesioni in T1 GD positive rispetto alla RMN precedente.\nAnnulla per correggere, Ok per accettare')) 
 {
  el['INCREMENTO_T2'].focus();
  return false;
 }
 else 
 {
     el['ELEGG'].value='0';
 }

return true;
}


function Check_EDSS()
{
f=document.forms[0];
el=f.elements;

if (el['EDSS_ATTUALE'].value==1)
{
  return Check_sf(1,2);
}

if (el['EDSS_ATTUALE'].value==2)
{
  ret=Check_sf(2,2);
  if (!ret) return ret;
  return Check_st_con(2,1,0,1);
}

if (el['EDSS_ATTUALE'].value==3)
{
  ret=Check_sf(2,2);
  if (!ret) return ret;
  return Check_st_con_min(2,2,0,1);
}

if (el['EDSS_ATTUALE'].value==4)
{
  ret=Check_sf(3,3);
  if (!ret) return ret;
  return Check_st_con(3,1,1,1);
}

if (el['EDSS_ATTUALE'].value==5)
{
  ret=Check_sf(3,3);
  if (!ret) return ret;
  return Check_st_con_min(3,2,1,1);
}

if (el['EDSS_ATTUALE'].value==6)
{
  ret=Check_sf(4,4);
  if (!ret) return ret;
  return Check_st_con6();
}

if (el['EDSS_ATTUALE'].value==7)
{
  ret=Check_sf(4,4);
  if (!ret) return ret;
  return Check_st_con7();
}

if (el['EDSS_ATTUALE'].value==8)
{
  ret=Check_sf(5,5);
  if (!ret) return ret;
  return Check_st_con8();
}
return true;
}


function Check_st_con_min(val,cval,men,al)
{
  sval=val-1;
	count=0;
	for (i=0;i < el.length ;i++){
		if (el[i].name.match(/FUNZIONI_/) && el[i].value==val)
		  if (men || !el[i].name.match(/FUNZIONI_M/)) count++;

	}
  if (count<cval)
  {
  tx='Inserire almeno '+cval+' SF con valore '+sval;
  if (!men)
   tx+=' (escludendo SF mentale)';
   if (al) alert(tx);
   return false;
  }
return true;
}

function Check_st_con(val,cval,men,al)
{
  sval=val-1;
	count=0;
	for (i=0;i < el.length ;i++){
		if (el[i].name.match(/FUNZIONI_/)  && el[i].value==val) 
		  if (men || !el[i].name.match(/FUNZIONI_M/)) count++;
	}
  if (count>cval)
  {
  tx='Inserire al massimo '+cval+' SF con valore '+sval;
  if (!men)
   tx+=' (escludendo SF mentale)';
   if (al) alert(tx);
   return false;
  }
return true;
}

function Check_st_con7()
{
	count3=0;
	for (i=0;i < el.length ;i++){
		if (el[i].name.match(/FUNZIONI_/)  && el[i].value==4) count3++;
	}
//alert(count3);
	count2=0;
	for (i=0;i < el.length ;i++){
		if (el[i].name.match(/FUNZIONI_/)  && el[i].value==3) count2++;
	}
//alert(count2);
if ((count3==1 && count2==1)||(count3==0&&count2==5))
  return true;
else
{
   alert('Inserire 1 SF con valore 3 e 1 SF con valore 2 oppure 5 SF con valore 2');
return false;
}
}

function Check_st_con8()
{
	count3=0;
	for (i=0;i < el.length ;i++){
		if (el[i].name.match(/FUNZIONI_/)  && el[i].value==5) count3++;
	}
//alert(count3);
	count2=0;
	for (i=0;i < el.length ;i++){
		if (el[i].name.match(/FUNZIONI_/)  && el[i].value==4) count2++;
	}
//alert(count2);
if ((count3==1 && count2==0)||(count3==0&&count2==2))
  return true;
else
{
  alert('Inserire 1 SF con valore 4 oppure 2 SF con valore 3');
return false;
}
}


function Check_st_con6()
{
	count3=0;
	for (i=0;i < el.length ;i++){
		if (el[i].name.match(/FUNZIONI_/)  && el[i].value==4) count3++;
	}
//alert(count3);
	count2=0;
	for (i=0;i < el.length ;i++){
		if (el[i].name.match(/FUNZIONI_/)  && el[i].value==3) count2++;
	}
//alert(count2);
if ((count3==1 && count2==0)||(count3==0&&(count2==3||count2==4)))
  return true;
else
{
alert('Inserire al massimo 1 SF con valore 3 (gli altri SF al massimo pari a 1)\noppure 3 o 4 SF con valore pari a 2 e nessuno uguale a 3.');
return false;
}
}



function Check_sf(val1,val2)
{
 if (el['FUNZIONI_P'][el['FUNZIONI_P'].selectedIndex].value>val1)
  {
   alert('Valore non congruo con EDSS nel campo: Funzioni piramidali.\n');
   el['FUNZIONI_P'].focus();
   return false;
  }

 if  (el['FUNZIONI_C'][el['FUNZIONI_C'].selectedIndex].value>val1)
  {
    alert('Valore non congruo con EDSS nel campo: Funzioni cerebellari ');
    el['FUNZIONI_C'].focus();
  return false;
  }
 if  (el['FUNZIONI_TE'][el['FUNZIONI_TE'].selectedIndex].value>val1)
  {
   alert('Valore non congruo con EDSS nel campo: Funzioni tronco-encefaliche ');
   el['FUNZIONI_TE'].focus();
   return false;
  }
 if  (el['FUNZIONI_S'][el['FUNZIONI_S'].selectedIndex].value>val1)
  {
   alert('Valore non congruo con EDSS nel campo: Funzioni sensitive ');
   el['FUNZIONI_S'].focus();
   return false;
  }
 if  (el['FUNZIONI_SF'][el['FUNZIONI_SF'].selectedIndex].value>val1)
  {
    alert('Valore non congruo con EDSS nel campo: Funzioni sfinteriche');
   el['FUNZIONI_SF'].focus();
   return false;
  }
 if  (el['FUNZIONI_V'][el['FUNZIONI_V'].selectedIndex].value>val1)
  {
    alert('Valore non congruo con EDSS nel campo: Funzioni visive');
   el['FUNZIONI_V'].focus();
   return false;
  }
 if  (el['FUNZIONI_M'][el['FUNZIONI_M'].selectedIndex].value>val2)
  {
   alert('Valore non congruo con EDSS nel campo: Funzioni mentali');
    el['FUNZIONI_M'].focus();
  return false;
  }

return true;
}


function Check_eleg()
{
f=document.forms[0];
el=f.elements;
el['ELEGG'].value='';
if (!Check_eleg_gen()) return false;
if (el['ELEGG'].value=='0')
{  
  alert('Il Paziente non risulta eleggibile');
  return true;
}  
if (!Check_eleg_A()) return false;
if (el['ELEGG'].value=='1')
{  
  alert('Il Paziente risulta eleggibile A');
  el['TIPOELEG'].value='A';
  return true;
}
if (!Check_eleg_B()) return false;
if (el['ELEGG'].value=='1')
{  
  alert('Il Paziente risulta eleggibile B');
  el['TIPOELEG'].value='B';
  return true;
}
alert('Il Paziente non risulta eleggibile');
return true;
}
//if (el['IMMUNO_12M'][el['IMMUNO_12M'].selectedIndex].value==1)
//{
// if (el['RICADUTE_12M'].value>1) return true;
// if (el['RICADUTE_12M_ESITI'][el['RICADUTE_12M_ESITI'].selectedIndex].value==2) return false;
// if (el['EDSS_ATTUALE'][el['EDSS_ATTUALE'].selectedIndex].value<4) return false;
// if (el['LESIONI_9'][el['LESIONI_9'].selectedIndex].value==1) return true;
// if (el['T1GD_POS'].value>0) return true;
//}
//if (el['RICADUTE_12M'].value<2) return false;
//if (el['RICADUTE_12M_ESITI'][el['RICADUTE_12M_ESITI'].selectedIndex].value==2) return false;
//if (el['EDSS_ATTUALE'][el['EDSS_ATTUALE'].selectedIndex].value<4) return false;
//if (el['INCREMENTO_T2'][el['INCREMENTO_T2'].selectedIndex].value==1) return true;
//if (el['COMPARSA_LESION'][el['COMPARSA_LESION'].selectedIndex].value==1) return true;
//return false;
//}

function Clear(nome)
{
f=document.forms[0];
el=f.elements;
el[nome].value='';
}





function Set_values()
{
f=document.forms[0];
el=f.elements;
for (i=1;i<11;i++)
{
	if (el['TRATTAMENTO'+i][el['TRATTAMENTO'+i].selectedIndex].value==1)
	  el['TRATATC'+i].value='L03AB07';
	if (el['TRATTAMENTO'+i][el['TRATTAMENTO'+i].selectedIndex].value==2)
	  el['TRATATC'+i].value='L03AB07';
	if (el['TRATTAMENTO'+i][el['TRATTAMENTO'+i].selectedIndex].value==3)
	  el['TRATATC'+i].value='L03AB07';
	if (el['TRATTAMENTO'+i][el['TRATTAMENTO'+i].selectedIndex].value==4)
	  el['TRATATC'+i].value='L03AB08';
	if (el['TRATTAMENTO'+i][el['TRATTAMENTO'+i].selectedIndex].value==5)
	  el['TRATATC'+i].value='L03AX13';
	if (el['TRATTAMENTO'+i][el['TRATTAMENTO'+i].selectedIndex].value==6)
	  el['TRATATC'+i].value='L04AX01';
	if (el['TRATTAMENTO'+i][el['TRATTAMENTO'+i].selectedIndex].value==7)
	  el['TRATATC'+i].value='L01BA01';
	if (el['TRATTAMENTO'+i][el['TRATTAMENTO'+i].selectedIndex].value==8)
	  el['TRATATC'+i].value='L01DB07';
	if (el['TRATTAMENTO'+i][el['TRATTAMENTO'+i].selectedIndex].value==9)
	  el['TRATATC'+i].value='L01AA01';
}
}

function Data_ok()
{
f=document.forms[0];
el=f.elements;
var fine_date=new Date();
gg=el['TODAY'].value.substr(0,2);
mm=el['TODAY'].value.substr(2,2);mm--;
aa=el['TODAY'].value.substr(4,4);
// alert('a= '+aa+' m= '+mm+' g= '+gg);
var sysdate = new Date();
sysdate.setFullYear(aa,mm,gg);
for (i=1;i<11;i++)
{
 a=el['TRATT_FINE'+i+'_DTY'].value;
 m=el['TRATT_FINE'+i+'_DTM'].value;m--;
 g=el['TRATT_FINE'+i+'_DTD'].value;
//alert('a= '+a+' m= '+m+' g= '+g);
 fine_date.setFullYear(a,m,g);
//alert(fine_date.getDate()+' '+fine_date.getMonth()+' '+fine_date.getFullYear());
 numero_gi=0;
 if (el['TRATATC'+i].value=='L03AB07'||el['ATC'+i].value=='L03AB07' ||
     el['TRATATC'+i].value=='L03AB08'||el['ATC'+i].value=='L03AB08' ||
     el['TRATATC'+i].value=='L03AX13'||el['ATC'+i].value=='L03AX13' 
     ) 
 numero_gi=30;
 if (el['TRATATC'+i].value=='L04AX01'||el['ATC'+i].value=='L04AX01'||
     el['TRATATC'+i].value=='L01BA01'||el['ATC'+i].value=='L01BA01'||
     el['TRATATC'+i].value=='L04AA01'||el['ATC'+i].value=='L04AA01'||
     el['TRATATC'+i].value=='J06BA02'||el['ATC'+i].value=='J06BA02'
     )
  numero_gi=90;
 if (el['TRATATC'+i].value=='L01DB07'||el['ATC'+i].value=='L01DB07'||
     el['TRATATC'+i].value=='L01AA01'||el['ATC'+i].value=='L01AA01'
     )
   numero_gi=180;
 if (numero_gi!=0)
 {
    fine_date.setDate(fine_date.getDate()+numero_gi);
//	 alert(fine_date.getDate()+' '+fine_date.getMonth()+' '+fine_date.getFullYear());
  if (fine_date>sysdate) 
  {
   if (!confirm('La Data di fine della terapia effettuata numero '+i+' non � corretta.\nNon sono passati '+numero_gi+' giorni.')) 
   {
    el['TRATT_FINE'+i+'_DTD'].focus();
    return false;
   }
  }
 }
}
 return true;
}

function Reg_check()
{
f=document.forms[0];
el=f.elements;
nch=0;
//nb=el['FARM'].length; 
////for (i=0;i<=nb;i++){
//		if (el['FARM'][i].checked) 
//		{
//		nch++;alert(el['FARM'][i].checked);
//	  }
//	}
if (el['FARM'].checked) nch++;
if (nch==0) {alert('Selezionare il farmaco');el['FARM'].focus();return false;}
if (!Check_minl('COGNOME',3)) return false;
if (!Check_minl('COGNOME',3)) return false;
if (!Check_char('COGNOME')) return false;
if (!Check_minl('NOME',3)) return false;
if (!Check_char('NOME')) return false;
if (!Cod_fisc_contr('CODFISC')) return false;
if (el['ESTERO'].checked &&el['COMUNE_NASC'].value!='')
{
 alert('Se e\' indicato Comune di Nascita, Estero non deve essere selezionato');
 el['COMUNE_NASC'].focus();
 return false;
}
if (!el['ESTERO'].checked &&el['COMUNE_NASC'].value=='')
{
 alert('Indicate Comune di Nascita o estero');
 el['COMUNE_NASC'].focus();
 return false;
}
return true;
}


function Sbianca_auto(ct)
{
f=document.forms[0];
el=f.elements;
el[ct].value='';
alert('Campo calcolato automaticamente dal sistema');
}

function Sbianca(ct)
{
f=document.forms[0];
el=f.elements;
el[ct].value='';
alert('Campo non modificabile.\nUsare Cerca, Sfoglia o Naviga');
}

function Clear(ct)
{
f=document.forms[0];
el=f.elements;
el[ct].value='';
}

function Calc_leu_per(ct)
{
f=document.forms[0];
el=f.elements;
var nomi=new Array("NEUTROFILI","EOSINOFILI","BASOFILI","LINFOCITI","MONOCITI");
num_Val=0;sum=0;valore=0;
for (i=0;i<5;i++)
{
 if (el[nomi[i]].value!='' && IsNumeric(el[nomi[i]].value) )
   {
   	 num_Val++;
   	 valore=el[nomi[i]].value-0;
   	 sum+=valore;
   	}
}
//alert(sum);
//alert(num_Val);

if (num_Val!=5) 
{
 for (i=0;i<5;i++)
  el[nomi[i]+'_PERCENT'].value='';
 return;
}
//alert(sum);
for (i=0;i<5;i++)
 el[nomi[i]+'_PERCENT'].value=Math.round((el[nomi[i]].value/sum)*10000)/100;

}


function IsNumeric(sText)
{
   var ValidChars = "0123456789.";
   var IsNumber=true;
   var Char;

 
   for (j = 0; j < sText.length && IsNumber == true; j++) 
      { 
      Char = sText.charAt(j); 
      if (ValidChars.indexOf(Char) == -1) 
         {
         IsNumber = false;
         }
      }
   return IsNumber;
   
   }


function Set_sae_cont()
{
f=document.forms[0];
el=f.elements;
nu=0;
for (i=1;i<6;i++)
 if (el['GRAVITA'+i].checked) nu++;
if (el['GRAVITA'][0].checked && nu==0)
 {
  alert('Se grave non deve essere vuoto');
  return false;
 }
if ((el['GRAVITA1'].checked || el['ESITO'][4].checked) && el['DECESSO_DT'].value=='')
 {
  alert('Data del decesso non deve essere vuoto');
  el['DECESSO_DTD'].focus();
  return false;
 }
if ((el['GRAVITA1'].checked || el['ESITO'][4].checked) && el['CAUSA_DEC'].selectedIndex==-1)
 {
  alert('Causa del decesso non deve essere vuoto');
  el['CAUSA_DEC'].focus();
  return false;
 }
return true;

}

function Fup_check()
{
f=document.forms[0];
el=f.elements;
if (el['ORTICARIA'][el['ORTICARIA'].selectedIndex].value==2 && el['ORTICARIA_PERSIST'].checked)
 {
  alert('Orticaria Persistente non deve essere selezionato');
  el['ORTICARIA_PERSIST'].focus();
  return false;
 }
if (el['GONFIORE'][el['GONFIORE'].selectedIndex].value==2 && el['GONFIORE_PERSIST'].checked)
 {
  alert('Gonfiore al viso, alle labbra o alla lingua Persistente non deve essere selezionato');
  el['GONFIORE_PERSIST'].focus();
  return false;
 }
if (el['DIFFICOLTA_RESPIR'][el['DIFFICOLTA_RESPIR'].selectedIndex].value==2 && el['DIFFICOLTA_RESPIR_PERSIST'].checked)
 {
  alert('Difficolt� respiratoria Persistente non deve essere selezionato');
  el['DIFFICOLTA_RESPIR_PERSIST'].focus();
  return false;
 }
if (el['INFEZIONE_URIN'][el['INFEZIONE_URIN'].selectedIndex].value==2 && el['INFEZIONE_URIN_PERSIST'].checked)
	{
 	alert('Infezione delle vie urinarie Persistente non deve essere selezionato');
 	el['INFEZIONE_URIN_PERSIST'].focus();
 	return false;
	}
 if (el['GOLA_NASO_URIN'][el['GOLA_NASO_URIN'].selectedIndex].value==2 && el['GOLA_NASO_PERSIST'].checked)
 {
  alert('Mal di gola e ipersecrezione nasale Persistente non deve essere selezionato');
  el['GOLA_NASO_PERSIST'].focus();
  return false;
 }
if (el['BRIVIDI'][el['BRIVIDI'].selectedIndex].value==2 && el['BRIVIDI_PERSIST'].checked)
 {
  alert('Brividi di freddo Persistente non deve essere selezionato');
  el['BRIVIDI_PERSIST'].focus();
  return false;
 }
if (el['MALE_TESTA'][el['MALE_TESTA'].selectedIndex].value==2 && el['MALE_TESTA_PERSIST'].checked)
 {
  alert('Mal di testa Persistente non deve essere selezionato');
  el['MALE_TESTA_PERSIST'].focus();
  return false;
 }
if (el['CAPOGIRI'][el['CAPOGIRI'].selectedIndex].value==2 && el['CAPOGIRI_PERSIST'].checked)
 {
  alert('Capogiri Persistente non deve essere selezionato');
  el['CAPOGIRI_PERSIST'].focus();
  return false;
 }
if (el['NAUSEA'][el['NAUSEA'].selectedIndex].value==2 && el['NAUSEA_PERSIST'].checked)
 {
  alert('Nausea Persistente non deve essere selezionato');
  el['NAUSEA_PERSIST'].focus();
  return false;
 }
if (el['VOMITO'][el['VOMITO'].selectedIndex].value==2 && el['VOMITO_PERSIST'].checked)
 {
  alert('Vomito Persistente non deve essere selezionato');
  el['VOMITO_PERSIST'].focus();
  return false;
 }
if (el['DOLORI_ART'][el['DOLORI_ART'].selectedIndex].value==2 && el['DOLORI_ART_PERSIST'].checked)
 {
  alert('Dolori alle articolazioni Persistente non deve essere selezionato');
  el['DOLORI_ART_PERSIST'].focus();
  return false;
 }
if (el['FEBBRE'][el['FEBBRE'].selectedIndex].value==2 && el['FEBBRE_PERSIST'].checked)
 {
  alert('Febbre Persistente non deve essere selezionato');
  el['FEBBRE_PERSIST'].focus();
  return false;
 }
if (el['STANCHEZZA'][el['STANCHEZZA'].selectedIndex].value==2 && el['STANCHEZZA_PERSIST'].checked)
 {
  alert('Stanchezza Persistente non deve essere selezionato');
  el['STANCHEZZA_PERSIST'].focus();
  return false;
 }
if (el['ALLERGIA_GRAVE'][el['STANCHEZZA'].selectedIndex].value==2 && el['ALLERGIA_GRAVE_PERSIST'].checked)
 {
  alert('Allergia grave (ipersensibilit�) Persistente non deve essere selezionato');
  el['ALLERGIA_GRAVE_PERSIST'].focus();
  return false;
 }
return true;
}


function Disp_ok()
{
f=document.forms[0];
el=f.elements;
if (!el['AIC_1'].checked)
 {
  alert('Selezionare AIC');
  el['AIC_1'].focus();
  return false;
 }
 return true;
 }
 
 
function ClearTot(n)
{
f=document.forms[0];
el=f.elements;
if (n==2)
{
for (i=1;i<11;i++)
{
 el['TRATT_INIZ'+i+'_DTD'].value='';
 el['TRATT_INIZ'+i+'_DTM'].value='';
 el['TRATT_INIZ'+i+'_DTY'].value='';
 el['TRATT_FINE'+i+'_DTD'].value='';
 el['TRATT_FINE'+i+'_DTM'].value='';
 el['TRATT_FINE'+i+'_DTY'].value='';
}
}
}
 
function ClearTotAltre(n)
{
f=document.forms[0];
el=f.elements;
if (n==2)
{
for (i=11;i<21;i++)
{
 el['INIZ'+i+'_DTD'].value='';
 el['INIZ'+i+'_DTM'].value='';
 el['INIZ'+i+'_DTY'].value='';
 }
}
}  
 
function ClearPar(n) 
{
f=document.forms[0];
el=f.elements;
//alert(n);
if (n!=-1)
{
for (i=n+1;i<11;i++)
{
// alert(i);
 el['TRATT_INIZ'+i+'_DTD'].value='';
 el['TRATT_INIZ'+i+'_DTM'].value='';
 el['TRATT_INIZ'+i+'_DTY'].value='';
 el['TRATT_FINE'+i+'_DTD'].value='';
 el['TRATT_FINE'+i+'_DTM'].value='';
 el['TRATT_FINE'+i+'_DTY'].value='';
}
}
}
 
function ClearParAltre(n) 
{
f=document.forms[0];
el=f.elements;
//alert(n);
if (n!=-1)
{
for (i=n+1;i<11;i++)
{
 k=10+i;
// alert(i);
 el['INIZ'+k+'_DTD'].value='';
 el['INIZ'+k+'_DTM'].value='';
 el['INIZ'+k+'_DTY'].value='';
}
}
}
 
function Fup_val_set()
{
f=document.forms[0];
el=f.elements;
if (el['TYSABRI_DOSI'].value=='')el['TYSABRI_DOSI'].value=0;
vl='ALTRI_TRATTAMENTI';
//alert(vl);
if (el[vl].value=='' && el['FUP_'+vl].value=='' && el['DIA_'+vl].value !='') el[vl].value=el['DIA_'+vl].value;
if (el[vl].value=='' && el['FUP_'+vl].value !='') el[vl].value=el['FUP_'+vl].value;
vl='ALTRI_TRATTAMENTI_SPEC';
if (el[vl].value=='' && el['FUP_'+vl].value=='' && el['DIA_'+vl].value !='') el[vl].value=el['DIA_'+vl].value;
if (el[vl].value=='' && el['FUP_'+vl].value !='') el[vl].value=el['FUP_'+vl].value;
cvl=new Array;
cvl[0]='D_SOSTANZA';
cvl[1]='ATC';
cvl[2]='INIZ';
cvl[3]='FINE';
for (i=11;i<21;i++)
{
 for (k=0;k<2;k++)
 {
 if (el[cvl[k]+i].value=='' && el['FUP_'+cvl[k]+i].value =='' && el['DIA_'+cvl[k]+i].value !='') el[cvl[k]+i].value=el['DIA_'+cvl[k]+i].value;
 if (el[cvl[k]+i].value=='' && el['FUP_'+cvl[k]+i].value !='') el[cvl[k]+i].value=el['FUP_'+cvl[k]+i].value;
 }
 if (el[cvl[2]+i+'_DT'].value=='' && el['FUP_'+cvl[2]+i+'_DT'].value =='' && el['DIA_'+cvl[2]+i+'_DT'].value !='') 
 {
   el[cvl[2]+i+'_DT'].value=el['DIA_'+cvl[2]+i+'_DT'].value;
  el[cvl[2]+i+'_DTD'].value=el['DIA_'+cvl[2]+i+'_DT'].value.substr(0,2);
  el[cvl[2]+i+'_DTM'].value=el['DIA_'+cvl[2]+i+'_DT'].value.substr(2,2);
  el[cvl[2]+i+'_DTY'].value=el['DIA_'+cvl[2]+i+'_DT'].value.substr(4,4);
 }
 if (el[cvl[2]+i+'_DT'].value=='' && el['FUP_'+cvl[2]+i+'_DT'].value !='') 
 {
   el[cvl[2]+i+'_DT'].value=el['FUP_'+cvl[2]+i+'_DT'].value;
  el[cvl[2]+i+'_DTD'].value=el['FUP_'+cvl[2]+i+'_DT'].value.substr(0,2);
  el[cvl[2]+i+'_DTM'].value=el['FUP_'+cvl[2]+i+'_DT'].value.substr(2,2);
  el[cvl[2]+i+'_DTY'].value=el['FUP_'+cvl[2]+i+'_DT'].value.substr(4,4);
 }
 if (el[cvl[3]+i+'_DT'].value=='' && el['FUP_'+cvl[3]+i+'_DT'].value !='') 
 {
  if (el['FUP_'+cvl[3]+i+'_DTRC'].value =='CONTIN')
  {
   el[cvl[3]+i+'_DT'].value=el['FUP_'+cvl[3]+i+'_DT'].value;
  el[cvl[3]+i+'_DTD'].value='';
  el[cvl[3]+i+'_DTM'].value='';
  el[cvl[3]+i+'_DTY'].value='CONT';
  }
  else
  {
   el[cvl[3]+i+'_DT'].value=el['FUP_'+cvl[3]+i+'_DT'].value;
  el[cvl[3]+i+'_DTD'].value=el['FUP_'+cvl[3]+i+'_DT'].value.substr(0,2);
  el[cvl[3]+i+'_DTM'].value=el['FUP_'+cvl[3]+i+'_DT'].value.substr(2,2);
  el[cvl[3]+i+'_DTY'].value=el['FUP_'+cvl[3]+i+'_DT'].value.substr(4,4);
  }
 }
}
}

function Set_Farm_val()
{
f=document.forms[0];
el=f.elements;
//alert(1);
if (el['TFARMA'][el['TFARMA'].selectedIndex].value==-9900)
{
  el['FARMA'].value=el['FARMACIA'].value;
  el['D_FARMA'].value=el['D_FARMACIA'].value;
// alert(el['FARMA'].value);alert(el['D_FARMA'].value)
}
else
{
  el['FARMA'].value=el['TFARMA'][el['TFARMA'].selectedIndex].value;
  el['D_FARMA'].value=el['TFARMA'][el['TFARMA'].selectedIndex].text;
// alert(el['FARMA'].value);alert(el['D_FARMA'].value)
}
	
}
function check_euro(val) {
	var re = new RegExp(",");
	if(val.match(re)) {
		alert("Utilizzare il punto come separatore dei centesimi di euro (es: 600.00)");
		val=val.substring(0,val.indexOf(",",0));
	}
	var re_dot = new RegExp(/\./);
	if(val.match(re_dot)) {
		//alert(val.substring(val.indexOf(".",0)+1,val.length));
		var len=val.substring(val.indexOf(".",0)+1,val.length);
		if(len.length!=2 ) {
			alert("ATTENZIONE: la tariffa deve essere specificata in euro utilizzando il punto come separatore per i centesimi di euro. Es: 600.00");
			if(len.length<2 )
				new_val=val.substring(0,val.indexOf(".",0))+".00";	
			else
				new_val=val.substring(0,val.indexOf(".",0))+val.substring(val.indexOf(".",0),val.indexOf(".",0)+3);
		} else new_val=val;
	} else {
		new_val=val+".00";
	}
	return new_val;
}

/* Calcola tariffa
 * "totale" -> il totale da versare
 * "versato" -> il versato
 */
function calcola_tariffa(totale,versato) {
	var differenza=(totale-0)-(versato-0);
	differenza=differenza+"";
	var re_dot = new RegExp(/\./);
	if(!differenza.match(re_dot)) { 
		differenza=differenza+".00";
	}
	var differenza_dec=check_euro(differenza);
//	alert(differenza_dec);
	return differenza_dec;
}

