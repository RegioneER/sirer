
	var prestazioniBraccio;
	$("#bracci-dialog-form").dialog({
	    autoOpen : false,
	    height : 300,
	    width : 450,
	    modal : true,
	    position: { my: "center", at: "center top", of: document.getElementById('centerElement') },
	    buttons:[
 		    {
 				text:"Aggiungi braccio", 
 				click: function() {
		        	var value=$(this).find('[name=Base_Nome]').first().val();
		         	if( value=='' || value.match(/^\s*$/)){
		         		alert("Inserire una descrizione.");
		         		return;
		         	}  
		         	else{
		         		$('#nobracci').remove();
		         		var elementId=$(this).find('[name=elementId]').first().val();
		         		var myElement;
		         		if(elementId=='' || elementId.match(/^\s*$/)){
		         			myElement=$.extend(true,{},emptyBraccio);
		         			var elementId=docObj.elements.bracci.length;	
		         			
		         		}else{
		         			myElement=docObj.elements.bracci[elementId];
		         		}
		         		myElement=formToElement("bracci-dialog-form",myElement,folderBracci);
		         		docObj.elements.bracci[elementId]=myElement;
		         		var oldValue=$('#braccio'+elementId).text();
		         		if(oldValue){
		         			$.each(docObj.elements.tpxp,function(i,currElement){
		         				var currBracci=getDato(currElement.metadata['Costo_Braccio']);
		         				var replaceMatch='\|'+oldValue+'\|';
		         				var replace='|'+value+'|';
		         				if(currBracci && inBraccio(currBracci,oldValue)){
		         					currBracci=currBracci.replace(replaceMatch,replace);
		         					currElement.metadata['Costo_Braccio']=currBracci;
		         					$.axmr.setUpdated(currElement);
		         				}
		         			});
		         		}
		         		$('#braccio'+elementId).remove();
		         		$('#braccioCheck'+elementId).remove();
		         		$('#bracciList').append('<button id="braccio'+elementId+'" class="btn btn-info" name="'+elementId+'" style="margin:3px;" >'+value+'</button>');
		         		$('#bracciChecks').append('<span id="braccioCheck'+elementId+'" name="'+elementId+'" style="margin:3px;" ><input type="checkbox" id="braccioInputCheck'+elementId+'"  onclick="$(\'#tuttiBracci\').each(function(){this.checked=false;});"  name="braccioInputCheck" value="'+value+'"><label for="braccioInputCheck'+elementId+'"  style="display:inline" >'+value+'</label></span>');
	         			$('#braccio'+elementId).button().click(function(){			
	         				$('#bracci-dialog-form').find('[name=elementId]').val(elementId);
	         				elementToForm(myElement,"bracci-dialog-form");	
	         				$("#bracci-dialog-form").dialog("open");
	         			});
		         		$(this).dialog("close");
		         	}     
		               
		
		        },
 				"class" : "btn btn-primary btn-xs"
 			},
 			{
 				text: "Rimuovi",
 				click:function(){
 					var elementId=$(this).find('[name=elementId]').first().val();
	         		var myElement;
	         		if(elementId=='' || elementId.match(/^\s*$/)){
	         			myElement=$.extend(true,{},emptyBraccio);
	         			var elementId=docObj.elements.bracci.length;	
	         			
	         		}else{
	         			myElement=docObj.elements.bracci[elementId];
	         		}
	         		$.axmr.setDeleted(myElement);
 					$('#braccio'+elementId).remove();
 					$(this).dialog("close");
 				},
 				"class":"btn btn-xs btn-danger"
 			},
 			{
 				text: "Annulla", 
 				click:function() {
    				$(this).dialog("close");
    			},
 				"class" : "btn btn-xs"
 			}
 		],
	  
	    open:function(){
	    	var elementId=$(this).find('[name=elementId]').first().val();
	    	if(elementId=='' || elementId.match(/^\s*$/)){
	    		$(this).parent().parent().find('button.btn-danger').hide();
	    	}else{
	    		$(this).parent().parent().find('button.btn-danger').show();
	    	}
	    }
	 
	});
	$("#bracci-button").button().click(function() {
		$('#bracci-dialog-form').find('input').val('');
		$("#bracci-dialog-form").dialog("open");
	});
