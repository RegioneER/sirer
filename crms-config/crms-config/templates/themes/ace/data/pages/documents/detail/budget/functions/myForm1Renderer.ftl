
var myForm1Renderer = function (instance, td, row, col, prop, value, cellProperties) {
            
    Handsontable.TextCell.renderer.apply(this, arguments);
    
    $(td).html($.axmr.label(value));
    if(value>0) var myElement=$.axmr.guid(value);
    if(myElement){
    	var labelPrestazione='';//getDato(myElement.metadata['Prestazioni_Codice']);
		if(!labelPrestazione)labelPrestazione='';
		else labelPrestazione+=' '
        labelPrestazione+=getDato(myElement.metadata['Prestazioni_prestazione']);
	    //var nth=row+1;
	    $(td).closest('tr').find('th').attr('title',labelPrestazione);
	    $(td).attr('title',labelPrestazione);
    }
    $(td).off('click').on('click',function(ev){
    	$.axmr.deselectGrid('#example');
    	return true;
    });
    $(td).off('click').on('click',function(ev){
    	ev=ev?ev:window.event;
        ev.stopPropagation();
        ev.preventDefault();
        
        $(this).dblclick();
        
    });
    $(td).off('dblclick').on('dblclick',function(ev){
        ev=ev?ev:window.event;
        ev.stopPropagation();
        ev.preventDefault();
       
        $("#prestazione-diz-dialog").off('dialogopen').on('dialogopen',function(ev){
            var width=$(window).width()/100*80;
            var height=$(window).height()/100*80;
            //$(this).dialog('option',{width:width,height:height});
            ev=ev?ev:window.event;
            var that=this;
            $.axmr.deselectGrid('#example');
            var myElement=$.axmr.guid(value);
            if(myElement){
            	elementToForm(myElement,'prestazione-diz-dialog');
           	}
            else{
            	elementToForm(emptyPrestazione,'prestazione-diz-dialog');
            }
           
            $(this).find('input[id^=Prestazioni_prestazione]').focus();
            console.log($(this).find('input[id^=titolo]'));
            var that=this;
            $(this).parent().find('button:contains(Aggiungi)').off('click').on('click',function(){
                var checkAll=true;
                $(that).find('input[type=text]').each(function(){
                	if(!$(this).val()){
                		checkAll=false;
                	}
                });
                if(!checkAll){
                	alert('Compilare tutti i campi per la prestazione.');
                	return;
                }
                if(!myElement){
                	myElement=$.extend(true,{},emptyPrestazione);
                }
                myElement.coordinates={x:col,y:row};
                newValue=$.axmr.guid(myElement,getDato(myElement.metadata['Prestazioni_prestazione']));
                formToElement('prestazione-diz-dialog',myElement);
                var labelPrestazione='';//getDato(myElement.metadata['Prestazioni_Codice']);
		        if(!labelPrestazione)labelPrestazione='';
		        else labelPrestazione+=' '
	        	labelPrestazione+=getDato(myElement.metadata['Prestazioni_prestazione']);
	        	if(labelPrestazione.length>18){
	        		labelPrestazione=labelPrestazione.substr(0,15)+'...';
	        	}
		        
                newValue=$.axmr.guid(myElement,labelPrestazione);
                $('#example').handsontable('setDataAtCell',row,col,newValue);
                $("#prestazione-diz-dialog").dialog('close');
            });
            
            
        });
        $("#prestazione-diz-dialog").dialog("open");
        return false;
    }).css({
        color: 'black'
    });
};
        