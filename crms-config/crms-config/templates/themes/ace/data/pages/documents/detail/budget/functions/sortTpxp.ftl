
function sortTpxp(tpxp){
	console.log(tpxp);
	var result=new Array();
	for(var i=0;i<tpxp.length;i++){
		var currChild=tpxp[i];
		if(currChild.metadata['tp-p_Prestazione'][0]){ 
		if(!$.isArray(result[currChild.metadata['tp-p_Prestazione'][0].metadata['Prestazioni_row']])){
			result[currChild.metadata['tp-p_Prestazione'][0].metadata['Prestazioni_row']]=new Array();
		}
		if(currChild.metadata['tp-p_TimePoint'][0]){
			result[currChild.metadata['tp-p_Prestazione'][0].metadata['Prestazioni_row']][currChild.metadata['tp-p_TimePoint'][0].metadata['TimePoint_NumeroVisita']]=currChild;
			currChild.metadata['tp-p_Prestazione']=currChild.metadata['tp-p_Prestazione'][0].metadata['Prestazioni_row'];
			currChild.metadata['tp-p_TimePoint']=currChild.metadata['tp-p_TimePoint'][0].metadata['TimePoint_NumeroVisita'];
		}
		else{
		
			if(docObj && docObj.elements && docObj.elements.tpxp2delete)docObj.elements.tpxp2delete[docObj.elements.tpxp2delete.length]=currChild;
			continue;
		}
		}
		else{
			continue;
		}
		
	}
	console.log(result);
	return result;
}
        