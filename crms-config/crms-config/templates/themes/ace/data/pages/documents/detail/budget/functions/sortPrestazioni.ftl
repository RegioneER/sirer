
function sortPrestazioni(a,b){
	if(parseInt(getDato(a.metadata['Prestazioni_row']))>parseInt(getDato(b.metadata['Prestazioni_row']))){return 1;}
	else if(parseInt(getDato(a.metadata['Prestazioni_row']))<parseInt(getDato(b.metadata['Prestazioni_row']))){return -1;}
	else{
		return 0;
	}
}
