
//form dei costi
var myForm3Renderer = function (instance, td, row, col, prop, value, cellProperties) {
           
    
    Handsontable.TextCell.renderer.apply(this, arguments);
    var firstData=$.axmr.label($('#example').handsontable('getDataAtCell',row,col));
    
   
    var myContent=$.axmr.label(value,2);
   	if(isNaN(myContent)){
   		myContent='';
   	}
   	var colOcc=$('#costi').handsontable('getDataAtCell',0,col)=='Totale occorrenze';
   	if(myContent && !colOcc){
   		var money=myContent.formatMoney();
   	}
   	else if(colOcc){
   		money=myContent;
   	}
   	else{
   		money='';
   	}
    $(td).html(money);
    if(firstData){
  
    	if(!value)value=$('#example').handsontable('getDataAtCell',row,col);
  		var myElement=$.axmr.guid(value);
    	var rimborso=getDato(myElement.metadata['Rimborso_Rimborsabilita'])
    	rimborso+='';
    	var color='lightblue';
    	switch(rimborso){
    		case '0':
        		color='lightblue';
        		break;
        	case '1':
        		color='orange';
        		break;
        	case '2':
        		color='white';
        		break;
    	}
    	console.log(color);
    	$(td).css({"background-color":color});
    	$(td).off('click').on('click',function(ev){
            ev=ev?ev:window.event;
            ev.stopPropagation();
            ev.preventDefault();
         	$.axmr.deselectGrid('#costi');
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
         	$.axmr.deselectGrid('#costi');
             if(myElement && getDato(myElement.metadata['Rimborso_Rimborsabilita'])==2){
         
            	return;	
            }
            
        
            $("#dialog-form-transfer").off('dialogopen').on('dialogopen',function(ev){
           		var width=$(window).width()/100*80;
                var height=$(window).height()/100*80;
                //$(this).dialog('option',{width:width,height:height});
                $(this).dialog('option',{height:height});
                ev=ev?ev:window.event;
                var that=this;
                if(!myElement) {
                	console.log('controllare');
                	myElement=$.extend(true,{},emptytpxp);
                }
                elementToForm(myElement,'dialog-form-transfer');
                
                $(this).find('input[id^=transfer]').val($.axmr.label(value,2));
                $('#costi').handsontable('deselectCell');
                $(this).find('input[id^=costo]').focus();
                var setTransfer=function(){
	                if($(that).find('select[id^=unita-markup]').val()==2){
	                    var costo=parseFloat($(that).find('input[id^=costo]').val()-0);
	                    var aggiunta=costo * parseFloat($(that).find('input[id^=markup]').val()-0) / 100;
	                    var value=costo+aggiunta;
	                } else{
	                    var value=parseFloat($(that).find('input[id^=costo]').val()-0)+parseFloat($(that).find('input[id^=markup]').val()-0);
	                }
	                $(that).find('input[id^=transfer]').val(value);
	            };
	            var setMarkup=function(){
	                if($(that).find('input[id^=transfer]').val()>0 && $(that).find('input[id^=costo]').val()>0){
	                    $(that).find('select[id^=unita-markup]').val(1);
	                    var value=parseFloat($(that).find('input[id^=transfer]').val())-parseFloat($(that).find('input[id^=costo]').val());
	                    $(that).find('input[id^=markup]').val(value);
	                }
	            };
	            
	            var myPrestazioneGuid=$('#example').handsontable('getDataAtCell',row,0);
	            var myPrestazioneLabel=$.axmr.label(myPrestazioneGuid);
	           var myVisitGuid=$('#example').handsontable('getDataAtCell',0,col);
	            var myVisitLabel=$.axmr.label(myVisitGuid);
	            $("#dialog-form-transfer").prev('.ui-dialog-titlebar').find('.ui-dialog-title').html(myPrestazioneLabel+" - "+myVisitLabel);
	            var myPrestazione=$.axmr.guid(myPrestazioneGuid);
	            var valoreSSN,valoreSolvente,valoreAlpi;
	            if($.isPlainObject(myPrestazione)){
                	valoreSSN=getDato(myPrestazione.metadata['Tariffario_SSN']);
					valoreSolvente=getDato(myPrestazione.metadata['Tariffario_Solvente']);
					valoreAlpi=getDato(myPrestazione.metadata['Tariffario_ALPI']);
				}
				if(valoreSSN){
					$(that).find('#valoreSSN').html(valoreSSN);
					$(that).find('#tariffaSSN').show();
				}
				else{
					$(that).find('#valoreSSN').html('');
					$(that).find('#tariffaSSN').hide();
				}
				if(valoreSolvente){
					$(that).find('#valoreSolvente').html(valoreSolvente);
					$(that).find('#tariffaSolvente').show();
				}
				else{
					$(that).find('#valoreSolvente').html('');
					$(that).find('#tariffaSolvente').hide();
				}
				if(valoreAlpi){
					$(that).find('#valoreAlpi').html(valoreAlpi);
					$(that).find('#tariffaAlpi').show();
				}
				else{
					$(that).find('#valoreAlpi').html('');
					$(that).find('#tariffaAlpi').hide();
				}
                $(this).find('input[id^=costo]').off('change').on('change',setTransfer);
	            $(this).find('input[id^=markup]').off('change').on('change',setTransfer);
	            $(this).find('select[id^=unita-markup]').off('change').on('change',setTransfer);
	            $(this).find('input[id^=transfer]').off('change').on('change',setMarkup);
                $(this).parent().find('button:contains(Aggiungi)').remove();
                $(this).parent().find('button:contains(Applica)').remove();
                 $(this).parent().find(':input').not('button').attr('disabled','disabled');
                
            });
             console.log('ora 2');
            $("#dialog-form-transfer").dialog("open");
            return false;
        });
    }
    else{
    	
        $(td).off('dblclick').on('dblclick',function(ev){
        	ev=ev?ev:window.event;
            ev.stopPropagation();
            ev.preventDefault();
        	$.axmr.deselectGrid('#costi');
        	return;
        });
    	if(value){
    	var rowText=$('#costi').handsontable('getDataAtCell',row,0);
    		if(value<0){
    			$(td).css({"background-color":'#F4505E'});
    		}
    		else if(rowText=='Proposta promotore' || rowText =='TP/Proposta promotore'){
    			$(td).css({"background-color":'#F4EC7F'});
        			
    		}
    		else{
    			//$(td).css({"background-color":'#7EF780'});
    			$(td).css({"font-weight":'bold'});
    		}
    	}
    	else{	
    		$(td).css({"background-color":'#CCC'});
    	}
    }
};
        