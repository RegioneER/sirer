/*
 * Funzione per la gestione del riempimento delle select
 * @Author Davide Saraceno
 * @Data 02/03/2012
 * @param elenco: elenco da riempire
 * @param script: script da utilizzare
 * @param val: valore di join
 */
function riempimento(elenco, script, val) {
	$.get("ajax.php", {
		script : script,
		val : val
	}, function(data) {
		$('#cell_input_' + elenco + ' select').empty();
		$('#cell_input_' + elenco + ' select').append(data);
	});
}

/*
 * Funzione da inserire nell'onchange delle select master
 * @Author Davide Saraceno
 * @Data 02/03/2012
 * @param elenco: elenco da riempire
 * @param script: script da utilizzare
 * @param val: valore di join
 */
function seleziona(elencomaster, elencoslave) {
	riempimento(elencoslave, elencoslave, $('#cell_input_' + elencomaster + ' :input').val());
}



//function compilacap(elenco, casella) {
//	$.get("ajax.php", {
//		script : casella,
//		val : $('#cell_input_' + elenco + ' :input').val()
//	}, function(data) {
//		$('#cell_input_' + casella + ' :text').val(data);
//
//	});
//}
//
//function riempimento_compila(elenco, script, val, tipocap) {
//	$.get("ajax.php", {
//		script : script,
//		val : val
//	}, function(data) {
//		$('#cell_input_' + elenco + ' select').empty();
//		$('#cell_input_' + elenco + ' select').append(data);
//		compilacap(tipocap + '_COMUNE', tipocap + '_CAP');
//	});
//}
//
//function seleziona_compila(elencomaster, elencoslave, tipocap) {
//	riempimento_compila(elencoslave, elencoslave, $('#cell_input_' + elencomaster + ' :input').val(), tipocap);
//}



//GIULIO

function compila_text(elenco, casella) {
	$.get("ajax.php", {
		script : casella,
		val : $('#cell_input_' + elenco + ' :input').val()
	}, function(data) {
		$('#cell_input_' + casella + ' :text').val(data);

	});
}

function riempimento_compila(elenco, script, val, elenco_m, text_box) {
	$.get("ajax.php", {
		script : script,
		val : val
	}, function(data) {
		$('#cell_input_' + elenco + ' select').empty();
		$('#cell_input_' + elenco + ' select').append(data);
		compila_text(elenco_m,text_box);
	});
}

function seleziona_compila(elencomaster, elencoslave,text_box) {
	riempimento_compila(elencoslave, elencoslave, $('#cell_input_' + elencomaster + ' :input').val(),elencomaster,text_box);
}
