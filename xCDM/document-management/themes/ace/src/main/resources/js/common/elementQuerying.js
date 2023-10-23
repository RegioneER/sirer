function getDato(dato) {
	if($.isArray(dato)) {
		return dato[0];
	} else {
		return dato;
	}
}