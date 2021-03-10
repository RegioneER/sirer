
var myForm2Renderer = function (instance, td, row, col, prop, value, cellProperties) {
            
    Handsontable.TextCell.renderer.apply(this, arguments);
    if(value>0) var myElement=$.axmr.guid(value);
    if(myElement && getDato(myElement.metadata['TimePoint_Note'])){var note='Note: '+getDato(myElement.metadata['TimePoint_Note']);
	    var nth=col+1;
	    $(td).closest('table').find('thead tr th:eq('+nth+')').attr('title',note);
	    $(td).attr('title',note);
    }
    $(td).html($.axmr.label(value));
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
        
        
        $("#tp-dialog-form").off('dialogopen').on('dialogopen',function(ev){
        	var width=$(window).width()/100*80;
            var height=$(window).height()/100*80;
            //$(this).dialog('option',{width:width,height:height});
            ev=ev?ev:window.event;
            var that=this;
            
            $.axmr.deselectGrid('#example');
            var myElement=$.axmr.guid(value);
           
            if(myElement){
            	elementToForm(myElement,'tp-dialog-form');
            }
            else{
            	elementToForm(emptyTimePoint,'tp-dialog-form');
            }
            $('[name=TimePoint_DescrizioneSelect-select]').change();
            var baseVisita= $('#example').handsontable('getDataAtCell',0,1);
            if(!baseVisita){
            	baseVisita=1;
            }else{
            	var objV0=$.axmr.guid(baseVisita);
            	if(objV0){
            		baseVisita=getDato(objV0.metadata['TimePoint_NumeroVisita']);
            		baseVisita=parseInt(baseVisita);
            	}else{
            		baseVisita=0;
            	}
            }
            if(col==1){
            	$('#TimePoint_NumeroVisita').val(baseVisita).prop('disabled',false);
            }else{
            	$('#TimePoint_NumeroVisita').val((col-1+baseVisita)).prop('disabled',true);
            }
            
            $(this).find('input[id$=Descrizione]').focus();
            $(this).parent().find('button:contains(Aggiungi)').off('click').on('click',function(){
                var newValue='';
                
                if(!myElement){
                	myElement=$.extend(true,{},emptyTimePoint)
                }
                if(!$(that).find('[name=TimePoint_DescrizioneSelect]').val()){
                	bootbox.alert('Attenzione scegliere un valore per il campo "Descrizione"');
                	return false;
                }
                var numeric;
                numeric=$(that).find('[name=TimePoint_Tempi]').val();
                if(numeric!='' && isNaN(parseFloat(numeric))){
                	bootbox.alert('Attenzione inserire un valore numerico nel campo "Tempo"');
                	return false;
                }
                
                //if(newData['TimePoint_NumeroVisita']=='')newData['TimePoint_NumeroVisita']=col-1;
                var nroVisita=$(that).find('[name=TimePoint_NumeroVisita]').val();
                if(nroVisita==""){
                	bootbox.alert('Attenzione scegliere un valore per il campo "Numero visita"');
                	return false;
                }else{
                	if(col==1 && nroVisita!="0" && nroVisita!="1"){
                		bootbox.alert('Attenzione scegliere un valore tra 0 e 1 per il campo "Numero visita"');
                		return false;
                	}else if(col==1){
                		nroVisita=parseInt(nroVisita);
                		if($('#example').data('handsontable').isPopulated()){
					      var rowData=$('#example').handsontable('getDataAtRow',0);
					      for(var idx=1;idx<rowData.length;idx++){
					      	var currCol=idx+1;
					      	var myElementIn=$.axmr.guid(rowData[idx]);
					      	if($.isPlainObject(myElementIn) && myElementIn.metadata ){
					      		myElementIn.metadata['TimePoint_col']=currCol;
					      		myElementIn.metadata['TimePoint_NumeroVisita']=idx-1+nroVisita;
					      		$.axmr.setUpdated(myElementIn);
					      		$.axmr.guid(myElementIn,buildTpDescription(myElementIn));
					      	}
					      }
					      $('#example').handsontable('render');
					   }
                		
                	}
                }
                myElement.coordinates={x:col,y:row};
                newValue=$.axmr.guid(myElement,buildTpDescription(myElement));
                formToElement('tp-dialog-form',myElement);
                newValue=$.axmr.guid(myElement,buildTpDescription(myElement));
                $('#example').handsontable('setDataAtCell',row,col,newValue);
               
                $("#tp-dialog-form").dialog('close');
            });
            
            
        });
        $("#tp-dialog-form").dialog("open");
        return false;
    }).css({
        color: 'black'
    });
};
