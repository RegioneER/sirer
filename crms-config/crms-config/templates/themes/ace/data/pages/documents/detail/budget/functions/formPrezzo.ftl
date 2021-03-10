
function formPrezzo(tipologia,idx){
	var myElement;
	switch(tipologia){
		case '1':
			myElement=docObj.elements.pxp[idx];
		break;
		case '2':
			myElement=docObj.elements.pxs[idx];
		break;
		
	}
	
		form='dialog-form';
		changeButton=false;
	
	        		           		
       		elementToForm(myElement,form);
       		$('#'+form).find('#idx').val(idx);  
       		$('#'+form).find('.ssn_diz').html('');
       		var ssn=getDato(myElement.metadata['Tariffario_SSN']);
       		if(ssn)$('#'+form).find('.ssn_diz').html(' (Valore SSR: '+ssn.formatMoney()+')');
       		$('#tipologia').val(tipologia);  
       		$('#tipologia').attr('disabled','disabled'); 
   
	
     console.log('ora 2');
    $("#"+form).dialog("open");
    return false;
   
 }
 