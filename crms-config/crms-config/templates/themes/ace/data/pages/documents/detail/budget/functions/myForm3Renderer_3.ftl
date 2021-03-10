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
            }
            else{
            	
	                       		
            	if(value){
		        	var rowText=$('#costi').handsontable('getDataAtCell',row,0);
		        		if(value<0){
		        			$(td).css({"background-color":'#F4505E'});
		        		}
		        		else if(rowText=='Proposta promotore' || rowText =='TP/Proposta promotore'){
		        			$(td).css({"background-color":'#F4EC7F'});
        					//$(td).css({"font-weight":'bold'});
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
             $(td).off('dblclick').on('dblclick',function(ev){
	            	ev=ev?ev:window.event;
	                ev.stopPropagation();
	                ev.preventDefault();
					$.axmr.deselectGrid('#costi');	            	
					return;
	            });
            
        };