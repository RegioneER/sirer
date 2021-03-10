
function elementToForm(element,form){
	$('#'+form).find(':input').each(function (){
		var label=$(this).attr('name');
		//label=label.replace(/^[^_]*_/,'');
		if($(this).attr('type')=='checkbox' ){
			if(getDato(element.metadata[label]))this.checked=true;
			else this.checked=false;
		}else if($(this).attr('type')=='radio'){
			var metaValue=getDato(element.metadata[label]);
			var decoded = $('<div/>').html(metaValue).text();
			if(decoded==this.value)this.checked=true;
			else this.checked=false;
		}
		else if(this.type.match('.*select.*')){
			var origLabel=label;
			label=label.replace('-select','');
			var dato=getDato(element.metadata[label]);
			$(this).find('option').removeAttr("selected");
			$(this).find('option').each(function(){
				if($(this).val()==dato){
					$(this).prop("selected",true);
				}
			});
			if($(origLabel).select2){
				$(origLabel).select2("val",dato);
			}
			
		}
		else{
			var dato=null;
			if(element && element.metadata)dato=getDato(element.metadata[label]);
			if(dato!==undefined && dato!==null){
				dato=$("<div/>").html(dato).text();
				$(this).val(dato);
			}
			else if(element && element.metadata && (element.metadata.hasOwnProperty(label) || (empties[element.type.id] && empties[element.type.id].metadata.hasOwnProperty(label)))) $(this).val('');
 		}
	});
	if(form=='dialog-form-transfer'){
		element=bracciFromElementToForm(element);
	}
}
