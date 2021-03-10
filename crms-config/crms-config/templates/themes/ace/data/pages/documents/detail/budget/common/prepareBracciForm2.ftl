
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
		        	var value=$(this).find('[name=SingoloBraccio_Braccio]').first().val();
		         	if( value=='' || value.match(/^\s*$/)){
		         		alert("Inserire una descrizione.");
		         		return;
		         	}  
		         	else{
		         		//$('#nobracci').remove();
		         		var elementId=$(this).find('[name=elementId]').first().val();
		         		var myElement;
		         		if(elementId=='' || elementId.match(/^\s*$/)){
		         			myElement=$.extend(true,{},emptyBudgetSingoloBraccio);
		         			var elementId=docObj.elements.bracci.length;	
		         			
		         		}else{
		         			myElement=docObj.elements.bracci[elementId];
		         		}
		         		myElement=formToElement("bracci-dialog-form",myElement,folderBracci);
		         		docObj.elements.bracci[elementId]=myElement;
		         		loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");
		         		saveElement(myElement,folderBracci).done(function(data){
			         		if(data.redirect){
			         			location.href=data.redirect;
		         			}else if(data.ret){
		         				location.href=baseUrl+"/app/documents/detail/"+data.ret;
		         			}else{
								var errorMessage="Errore salvataggio! <i class='icon-warning-sign red'></i>";
								if(data.errorMessage.includes("RegexpCheckFailed: ")){
									var campoLabel="";
									campoLabel=data.errorMessage.replace("RegexpCheckFailed: ","");
									campoLabel=messages[campoLabel];
									errorMessage="Errore nella validazione del campo:<br/>"+campoLabel;
								}
								bootbox.alert(errorMessage);
		         			}
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
