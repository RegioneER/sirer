
function sortTp(a,b){
	if(parseInt(getDato(a.metadata['TimePoint_col']))>parseInt(getDato(b.metadata['TimePoint_col']))){return 1;}
	else if(parseInt(getDato(a.metadata['TimePoint_col']))<parseInt(getDato(b.metadata['TimePoint_col']))){return -1;}
	else{
		return 0;
	}
}
        