
 function firstLine(testo){
	testo=testo.replace(/(\n.*)*$/g,'');
	return $.trim(testo);
}
        