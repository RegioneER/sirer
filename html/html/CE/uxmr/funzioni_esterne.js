function open_ATC(){
	if ($('input[name="TIPO_ATC"]:checked').val()==1) window.open('sfoglia_farmaci_new2.php?AIC6_SPEC=SPECIALITA&AIC=AIC&ATC_LIVELLO=LATC&ATC_INN=GDATC&ATC_CODE=ATC&ATC_DECODE=DATC&AIC6_DSOST=PRINC_ATT&AIC6_CSOST=COD_PRINC_ATT&AIC6_DDITTA=D_TITOLARE_AIC&AIC6_CDITTA=TITOLARE_AIC&AIC9_CONF=CONFEZIONE','finestraindipendente','scrollbars=yes,resizable=yes,width=1000,height=600');
	else if ($('input[name="TIPO_ATC"]:checked').val()==2) window.open('sfoglia_farmaci_new.php?AIC6_SPEC=SPECIALITA&AIC=AIC&ATC_LIVELLO=LATC&ATC_INN=GDATC&ATC_CODE=ATC&ATC_DECODE=DATC&AIC6_DSOST=PRINC_ATT&AIC6_CSOST=COD_PRINC_ATT&AIC6_DDITTA=D_TITOLARE_AIC&AIC6_CDITTA=TITOLARE_AIC&AIC9_CONF=CONFEZIONE','finestraindipendente','scrollbars=yes,resizable=yes,width=1000,height=600');
	else alert('Attenzione, definire prima se si tratta di ATC generico');
}


function ajax_send_crpms(id_stud,vprogr) {
		$('body').fadeTo( "slow", 0.33, cb_ajax );
		
		function cb_ajax(){
			var request = $.ajax({
				url: "/crms-toscana/app/rest/ctc/inserisciStudioFromCE/?",
				method: "GET",
				data: { iD_stud : id_stud , visitnum_progr : vprogr },
				dataType: "json",
				async: false
			});
				
			request.done(function( msg ) {
				if(msg.status=='true'){
					alert('invio effettuato con successo!');
				}
				else{
					alert('errore di invio!');
				}
				location.reload();
			});
				
			request.fail(function( jqXHR, textStatus ) {
				alert( "Request failed: " + textStatus );
				location.reload();
			});
		
		}
		
}

function delete_entries() { 
	$('[name="PEDIATRICO"][value="1"]').parent().parent().hide();
	}

function MEMBRI_APPROV_MCHECK_function(oggetto) {
	var a="MEMBRI_ASTENUTI_MCHECK_";
	membri_mcheck_function(oggetto,a);
	}

function MEMBRI_ASTENUTI_MCHECK_function(oggetto) {
	var a="MEMBRI_APPROV_MCHECK_";
	membri_mcheck_function(oggetto,a);
	}
	
function membri_mcheck_function(oggetto,campo) {
	if(oggetto.prop('checked')){
			var a=oggetto[0].name.split("_");
			var a1=a.pop();
			var b=campo+a1;
			$('[name='+b+']').prop('checked',false);
		}
	}

function cf_ctrl(){
	if(document.forms[0].CF_RICHIEDENTE.value.length==16){
		return true;
	}else{
	alert('Il codice fiscale del procuratore inserito non è di 16 cifre!');
	 return false;
	}
}

function sel_clear_all(check,tipologia) {
		for (i=0;i<document.forms[0].elements.length;i++) {
			if(check==1 && document.forms[0].elements[i].name.match(tipologia)) {
				document.forms[0].elements[i].checked=true;
			}
			if(check==0 && document.forms[0].elements[i].name.match(tipologia)) {
				document.forms[0].elements[i].checked=false;
			}
		}
}


function check_eta(){
f=document.forms[0];
	el=f.elements;

	if (el['ETA_UTERO'].checked==false 
	&& el['ETA_NEONATI'].checked==false 
	&& el['ETA_POP_01M'].checked==false 
	&& el['ETA_POP_123M'].checked==false 
	&& el['ETA_POP_211A'].checked==false 
	&& el['ETA_POP_1318A'].checked==false 
	&& el['ETA_POP_1944A'].checked==false 
	&& el['ETA_POP_4564A'].checked==false 
	&& el['ETA_POP_65A'].checked==false 
	)	{
				alert('Attenzione! Selezionare almeno una fascia d\'età');
				el['ETA_UTERO'].focus();
				return false;
		}
	return true;
}


function liste(form) {
	if (form == 'locale') {
		installa_lista('PRINC_INV');
		installa_lista('UNITA_OP');
	} else if (form == 'centri') {
		installa_lista('CENTRO');
	}	
	$.each($('.chosen-single').parent(), function(v,i) {
		$(i).width($(i).width()+30);
  	});
}

function installa_lista(lista) {
	$('[name="' + lista + '"]').chosen({search_contains: true});
}

function calcoloDataFine(){
	var unita=parseFloat($('[name="DUR_SPER_UNIT"]:checked').val());
	var durata=parseFloat($('[name="DUR_SPER"]').val());
	var giorno=parseFloat($('[name="INIZ_RECL_ITA_DTD"]').val());
	var mese=$('[name="INIZ_RECL_ITA_DTM"]').val();
	var anno=parseFloat($('[name="INIZ_RECL_ITA_DTY"]').val());
	
	var data = new Date(mese+"/"+giorno+"/"+anno);
	
	var variabili="unita="+unita+" durata="+durata+" giorno="+giorno+" mese="+mese+" anno="+anno;
	
	console.log(data);
	console.log(variabili);
	
	switch(unita){
		
		case 1:
		data.setDate(data.getDate()+durata);
		break;
		
		case 2:
		data.setDate(data.getDate()+durata*7);
		break;
		
		case 3:
		data.setMonth(data.getMonth()+durata);
		break;
		
		case 4:
		data.setFullYear(data.getFullYear()+durata);
		break;
		
		}
	
	console.log("data aggiornata="+data);
	
	$('[name="FINE_RECL_DTD"]').val(data.getDate());
	$('[name="FINE_RECL_DTM"]').val(data.getMonth()+1);
	$('[name="FINE_RECL_DTY"]').val(data.getFullYear());
	
	
}

function checkRange(){
	for(var i=1; i<=4; i++){
		var rd=$('[name="ER'+i+'_DA_SELECT"]').val();
		var ra=$('[name="ER'+i+'_A_SELECT"]').val();
		fascia="primo";
		if(i==2) fascia="secondo";
		if(i==3) fascia="terzo";
		if(i==4) fascia="quarto";
		if(rd && ra){
			if( (rd==1 && (ra==1 || ra==2)) || (rd==4 && (ra==4 || ra==5))){
				alert("ATTENZIONE! Non e' possibile selezionare lo stesso valore di fascia nel "+fascia+" range di eta'");
				$('[name="ER'+i+'_A_SELECT"]').val("");
			}
		}
	}
}

function checkRangeSave(){
	var ret=0;
	for(var i=1; i<=4; i++){
		fascia="primo";
		if(i==2) fascia="secondo";
		if(i==3) fascia="terzo";
		if(i==4) fascia="quarto";
		var ra=$('[name="ER'+i+'_A_SELECT"]').val();
		var ras=$('[name="ER'+i+'_A_SPEC"]').val();
		var a=$('[name="ER'+i+'_A"]').val();		
		if( (ra || ras || a) && (!ra || !ras || !a)) {
			alert("ATTENZIONE! Compilare tutti i dati nel "+fascia+" range di eta'");
			ret=1;
		}
	}
	
	return ret;
}

/*TOSCANA-160 vmazzeo 20.06.2017 disabilito alcune option della select documentazione centro specifica perch? non possono essere pi? inserite lato CE*/
function ce_doc_loc_disable() {
	$('select[name="DOC_LOC"] option').each(function(){
		var my_code=$(this).val();
		if(my_code==10||my_code==11||my_code==12||my_code==13||my_code==14||my_code==17){
			$(this).text($(this).text()+" (disponibile solo per CTO/TFA)");
			$(this).prop('disabled', true);
		}
	});
}