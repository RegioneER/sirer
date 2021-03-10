function PRESENZE_MCHECK_function(oggetto) {
	var a="PRESENZE_TELE_MCHECK_";
	membri_mcheck_function(oggetto,a);
	}

function PRESENZE_TELE_MCHECK_function(oggetto) {
	var a="PRESENZE_MCHECK_";
	membri_mcheck_function(oggetto,a);
	}

function ESTERNI_MCHECK_function(oggetto) {
	var a="ESTERNI_TELE_MCHECK_";
	membri_mcheck_function(oggetto,a);
	}

function ESTERNI_TELE_MCHECK_function(oggetto) {
	var a="ESTERNI_MCHECK_";
	membri_mcheck_function(oggetto,a);
	}

function PRESENZE_SGR_CE_MCHECK_function(oggetto) {
	var a="PRESENZE_SGR_CE_TELE_MCHECK_";
	membri_mcheck_function(oggetto,a);
	}

function PRESENZE_SGR_CE_TELE_MCHECK_function(oggetto) {
	var a="PRESENZE_SGR_CE_MCHECK_";
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

function dialog(){
	$( "#dialog" ).dialog({minWidth: 400, minHeight: 200});
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

function rimuovi_inutili(){
	$.each($('select'), function (i,v) {
		if ($(v).val() == "") {
		$(v).remove();
		}
});
	
}


function creaTeleconference(idSeduta){
	//alert("CREA");
	//moment($('#meeting_inidt').val(), 'DD/MM/yyyy HH:mm').format()
	var duration = 4;
	var procedi = true;
	var descrizione = $('#field_sed_tipo').text()+" - "+$('#field_sed_id').text();
	if (procedi && !descrizione) {
	  alert('Specificare descrizione');
	  procedi = false;
	}

	var dataOraInizio = $('#field_sed_data').text();
	var oraField = $('#field_sed_ora').text();
	dataOraInizio+=" "+oraField.split(" - ")[0];
	if (procedi && !dataOraInizio) {
	  alert('Specificare data inizio');
	  procedi = false;
	}

	var dataOraFine = "";
	
	if (procedi){
		if (duration == undefined || duration == '') {
			alert('Specificare durata dell\'evento');
		} else {
			dataOraFine = moment(dataOraInizio, 'DD/MM/YYYY HH:mm').add(duration, 'hours').format('DD/MM/YYYY HH:mm');
	        var date = new Date();
	        //alert(moment(dataOraInizio, 'DD/MM/YYYY HH:mm').format());
	        //alert(moment(dataOraFine, 'DD/MM/YYYY HH:mm').format());
	        $.get( "/sedute/new_meeting.php", { 
	        	schedule: 1,
	            meetingTitle: descrizione,
	            dateStart: moment(dataOraInizio, 'DD/MM/YYYY HH:mm').format(),
	            dateEnd: moment(dataOraFine, 'DD/MM/YYYY HH:mm').format(),
	            date : date
	           	}, function( data ) {
	            	var data_info = data.split(":");
	                if (data_info[0] == 'OK') {
	                	//$('#meeting_meetingurl').val(data_info[2]);
	                    //$('#meeting_meetingscoid').val(data_info[1]);
	                    //$('#meeting_meetingurl').parent().parent().parent().parent().show();
	                    //$('#meeting_meetingscoid').parent().parent().parent().parent().show();
	                    window.location='/sedute/index.php?ID_SED='+idSeduta+'&MEETING_URL='+encodeURIComponent(data_info[2])+'&MEETING_SCOID='+encodeURIComponent(data_info[1]);
	                 	//alert("Meeting schedulato correttamente.");
	                 }
	                 if (data_info[0] == 'ERR') {
	                 	if (data_info[1] == 'duplicate') {
	                    	alert('Ci sono altre riunione nel periodo selezionato.');
	                    } else if (data_info[1] == 'range') {
	                    	alert('Questo range temporale non è permesso.');
	                    } else {
	                    	alert(data_info[1]);
	                    }
	                 }
	            });
	                        
	    }
	}else{
		alert('Informazioni di riunione non disponibili.')
	}
	
	return false;
}