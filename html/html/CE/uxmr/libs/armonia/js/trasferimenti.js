function compila_codpat(servizio) {
	riempimento(servizio,'CODPAT', 'CENTRO_ORIGINE', $('#cell_input_CENTRO_ORIGINE select').val());
}

function riempimento(servizio,elenco_slave, elenco_master, val_master) {
	request = $.ajax({
		url:"libs/armonia/scripts/ajax/trasferimenti.php", 
		type:'POST',
		data: { service: servizio, val_master: val_master},
		dataType:"json",
		success: function( jlo ){
			//cancello le vecchie options tranne la prima val=""
			$('[name=CODPAT] option').each(function (){ 
				if($(this).val())$(this).remove();
			});
			//ripopolo il mondo
			$.each(jlo, function(skey, sval){
				$('[name=CODPAT]').append($("<option></option>")
				         .attr("value",skey)
				         .text(sval)); 
			});			 

		}
	});
}