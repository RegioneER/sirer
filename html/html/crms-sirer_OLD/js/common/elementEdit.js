function prepareMetadataForPost(inMetadata) {

	var metadata = $.extend(true, {}, inMetadata);
	$.each(metadata, function(key, value) {
		if($.isPlainObject(value[0])) {
			metadata[key] = value[0].id.toString();
		} else {
			if($.isArray(value)) {
				if(value[0] === null || value[0] === undefined)
					metadata[key] = "";
				else
					metadata[key] = value[0].toString();
			} else {
				metadata[key] = value.toString();
			}
		}	
	});
	return metadata;

}

function prepareElementForPost(element) {
	element = $.extend(true, {}, element);
	$.each(element, function(property, value) {
		if(value === null || value === undefined)
			element[property] = "";
		else if(!$.isPlainObject(value) && !$.isArray(value))
			element[property] = value.toString();
	});
	if(element.metadata)
		element.metadata = prepareMetadataForPost(element.metadata);
	return element;
}
function updateElement(element) {
	var metadata = prepareMetadataForPost(element.metadata);
	if(metadata.lenght==0){
		bootbox.alert('Attenzione, non ci sono dati da salvare.');
		return false;
	}
	return $.ajax({
		method : 'POST',
		url :  baseUrl+'/app/rest/documents/update/' + element.id,
		data : metadata
	});

}

function saveElement(element, parent) {
	if(element.id) {
		return updateElement(element);
	} else {
		var metadata = prepareMetadataForPost(element.metadata);
		if(!parent && element.parent){
			if($.isPlainObject(element.parent) || $.isArray(element.parent)){
				parent=element.parent.id;
			}
			else{
				parent=element.parent;
			}
		}
		metadata.parentId = parent;
		return $.ajax({
			method : 'POST',
			url : baseUrl+'/app/rest/documents/save/' + element.type.id,
			data : metadata
		}).done(function(data) {
			element.id = data.ret;
		});
	}
}

function formToElement(form,element,template){
	if(!((typeof form)=='object') && !$.isArray(form)){
		if(!form.match(/^#/)){
			form='#'+form;
		}
		form=$(form);
	}
	var templateFilter="";
	if(template){
		templateFilter="[name^="+template+"]";
	}
	var multiples={};
	form.find(':input'+templateFilter).each(function (){
		var label=$(this).attr('name');
		
		//label=label.replace(/^[^_]*_/,'');
		if(empties[element.type.id].metadata[label]!=undefined){
			var type=$(this).attr('type');
			if(type=='checkbox'){
				if(this.checked) element.metadata[label]=this.value;//$(this).val(); risulta vuoto indagare come mai viene svuotato
				else  element.metadata[label]='';
			}
			else if(type=='radio'){
				if(!multiples[label]){
					multiples[label]=true;
					element.metadata[label]='';
				}
				if(this.checked){
					element.metadata[label]=this.value;
				}
			}
			else{
				element.metadata[label]=$(this).val();
			}
		}
		else{
		console.log(label);
		console.log(empties[element.type.id].metadata[label]);
		}
		if($ && $.axmr){
			$.axmr.setUpdated(element);
		}
		console.log("controlla",element);
	});
	return element;
}

function elementToForm(element, form) {
	$('#' + form).find(':input').each(function() {
		var label = $(this).attr('name');
		//label=label.replace(/^[^_]*_/,'');
		if($(this).attr('type') == 'checkbox') {
			if(getDato(element.metadata[label]))
				this.checked = true;
			else
				this.checked = false;
		} else {
			var dato = getDato(element.metadata[label]);
			if(dato !== undefined && dato !== null)
				$(this).val(dato);
			else if(element.metadata.hasOwnProperty(label))
				$(this).val('');
		}
	});
}