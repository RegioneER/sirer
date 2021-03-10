
function valorizzaCDC(cdc,item,suffix){
	suffix = suffix ? suffix : '';
	$(cdc).val(item.value);
	$(cdc).closest('form').find('input#Prestazioni_UOC'+suffix).val(item.uo);
	$(cdc).closest('form').find('input#Prestazioni_UOCCode'+suffix).val(item.uo_code);
	
	$(cdc).closest('form').find('input#Prestazioni_CDCCode'+suffix).val(item.id);
	
	$('#dizionario'+suffix).val('');
	
	$(cdc).off('keypress').on('keypress',function (){
		if($(cdc).val()!=item.value){
			$(cdc).closest('form').find('.ssn_diz').html('');
	
			var that=cdc;
			$( "#dizionario"+suffix ).val('');
			/*$('#prestazione-diz-dialog').on('dialogclose',function(){
				$(that).off('keypress');
			});*/
			$(cdc).closest('form').find('input#Prestazioni_CDCCode'+suffix).val('');
			$(cdc).closest('form').find('input#Prestazioni_UOC'+suffix).val('');
			$(cdc).closest('form').find('input#Prestazioni_UOCCode'+suffix).val('');
			
			$(this).off('keypress');
		}
	});
	hidebutton();
}
        
        
function valorizzaCDC_start(cdc,item,suffix){
	suffix = suffix ? suffix : '';
	$(cdc).val(item.value);
	
	$(cdc).closest('form').find('input#Tariffario_Solvente'+suffix).val(item.solvente);
	$(cdc).closest('form').find('input#Tariffario_SSN'+suffix).val(item.ssn);
	
	$(cdc).closest('form').find('input#Prestazioni_Codice'+suffix).val(item.id);
	$('#dizionario'+suffix).val('');
	if(item.dizionario)$( "#dizionario"+suffix ).val('1');
	$(cdc).off('keypress').on('keypress',function (){
		if($(cdc).val()!=item.value){
			$(cdc).closest('form').find('.ssn_diz').html('');
			var that=cdc;
			$( "#dizionario"+suffix ).val('');
			/*$('#prestazione-diz-dialog').on('dialogclose',function(){
				$(that).off('keypress');
			});*/
			
			$(cdc).closest('form').find('input#Tariffario_Solvente'+suffix).val('');
			$(cdc).closest('form').find('input#Tariffario_SSN'+suffix).val('');
			$(this).off('keypress');
		}
	});
	hidebutton();
}