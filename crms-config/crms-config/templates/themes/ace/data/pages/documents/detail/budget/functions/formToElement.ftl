
function formToElement(form,element,parent){
	$('#'+form).find(':input').each(function (){
		var label=$(this).attr('name');
		//label=label.replace(/^[^_]*_/,'');
		if(empties[element.type.id].metadata[label]!=undefined){
			if($(this).attr('type')=='checkbox'){
				if(this.checked) {
					if(this.value){
						element.metadata[label]=this.value;
					}
					else{
						element.metadata[label]=1;
					}
				}//$(this).val(); risulta vuoto indagare come mai viene svuotato
				else  {
					element.metadata[label]='';
				}
			}else if($(this).attr('type')=='radio'){
				if(this.checked) element.metadata[label]=$(this).val();
			}
			else{
				var value=$(this).val();
				if(label=='PrezzoFinale_Prezzo' || label=='Costo_Prezzo' || label=='Costo_Costo' || label=='Costo_TransferPrice'){
					value=value.formatMoney().unformatMoney();
				}
				element.metadata[label]=value;
			}
		}
		else{
		console.log(label);
		console.log(empties[element.type.id].metadata[label]);
		}
		$.axmr.setUpdated(element,parent);
		console.log("controlla",element);
	});
	if(form=='dialog-form-transfer'){
		element=bracciFromFormToElement(element);
	}
	return element;
}
        