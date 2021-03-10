
var myTranslateRender= function (instance, td, row, col, prop, value, cellProperties) {         
  Handsontable.TextCell.renderer.apply(this, arguments);
  if(value=='Totale per visita' || value=='Valore con markup' || value=='Totale per prestazione' ){
  		//$(td).css({"background-color":'#00BF00'});
  		$(td).css({"font-weight":'bold'});
  }   
  if(value=='Valore target' || value=='Target markup'){
  		$(td).css({"background-color":'#F7F754'});
		
  }
  if(value>0) var myElement=$.axmr.guid(value);
  if(row==0  ){
	    if(myElement && getDato(myElement.metadata['TimePoint_Note'])){
	    	var note='Note: '+getDato(myElement.metadata['TimePoint_Note']);
		    var nth=col+1;
		    $(td).closest('table').find('thead tr th:eq('+nth+')').attr('title',note);
		    $(td).attr('title',note);
	    }
  }else{
	  	if(myElement){
	    	var labelPrestazione='';//getDato(myElement.metadata['Prestazioni_Codice']);
			if(!labelPrestazione)labelPrestazione='';
			else labelPrestazione+=' '
	        labelPrestazione+=getDato(myElement.metadata['Prestazioni_prestazione']);
		    //var nth=row+1;
		    $(td).closest('tr').find('th').attr('title',labelPrestazione);
		    $(td).attr('title',labelPrestazione);
	    }
  }         
  var label=$.axmr.label(value);
  $(td).html(label);
  $(td).off('dblclick').on('dblclick',function(ev){
		ev=ev?ev:window.event;
	    ev.stopPropagation();
	    ev.preventDefault();
		$.axmr.deselectGrid('#costi');	            	
		return;
	});
	 $(td).off('click').on('click',function(ev){
		ev=ev?ev:window.event;
	    ev.stopPropagation();
	    ev.preventDefault();
		$.axmr.deselectGrid('#costi');	            	
		return;
	});
};
        