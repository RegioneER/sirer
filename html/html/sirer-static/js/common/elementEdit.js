function prepareMetadataForPost(inMetadata) {

	var metadata = $.extend(true, {}, inMetadata);
	$.each(metadata, function(key, value) {
		if(value && value[0]){
			if($.isPlainObject(value[0])) {
				metadata[key] = value[0].id.toString();
			} else {
				if($.isArray(value)) {
					if (value.length==0){
						metadata[key] = "";
					}else {
						for (var i = 0; i < metadata.length; i++) {
							if (value[0] === null || value[0] === undefined) {
								this.splice(i, 1);
								i--;
							} else {
								metadata[key][i] = value[i].toString();
							}
						}
					}
				} else {
					metadata[key] = value.toString();
				}
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


function updateElementEme(element) {
    var metadata = element.metadata;
    if(metadata.lenght==0){
        bootbox.alert('Attenzione, non ci sono dati da salvare.');
        return false;
    }
    //metadata=JSON.stringify(metadata);
    var metadataPost = {};
    $.each(metadata, function(key,valueObj){
        if (jQuery.isArray(valueObj) && valueObj.length==0){
            metadataPost[key] = "";
        }else{
            metadataPost[key] = valueObj;
        }
    });
    return $.ajax({
        method : 'POST',
        url :  baseUrl+'/app/rest/documents/updateEme/' + element.id,
        data : metadataPost
    });

}

function updateElementEmeAlpaca(formName, element) {
	var metadata = element.metadata;
	if(metadata.lenght==0){
		bootbox.alert('Attenzione, non ci sono dati da salvare.');
		return false;
	}
	//metadata=JSON.stringify(metadata);
	metadata=alpacaMetadataPostProcess(formName, metadata);
	var metadataPost = {};
	$.each(metadata, function(key,valueObj){
		if (jQuery.isArray(valueObj) && valueObj.length==0){
			metadataPost[key] = "";
		}else{
			metadataPost[key] = valueObj;
		}
	});
	return $.ajax({
		method : 'POST',
		url :  baseUrl+'/app/rest/documents/updateEmeAlpaca/' + formName + '/' + element.id,
		data : metadataPost
	});

}

function saveElement(element, parent) {
	if(element.id) {
		if (typeof(emendamentoId) != "undefined" && emendamentoId>0 && elementInEmendamento){
            return updateElementEme(element)
        }else
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

function alpacaMetadataPostProcess(formName, metadata){
	for (var key in metadata){
		var inputField=$('#metadataTemplate-'+formName+'-FORM [name="'+key+'"]')[0];
		console.log(inputField);
		//TODO: Verificare qua dataSourceFunction
		if (alpacaJsons[formName].options && alpacaJsons[formName].options.fields[key] && alpacaJsons[formName].options.fields[key].dataSourceFunction){
			var decode=$(inputField).find("option:selected").text();
			metadata[$(inputField).attr('name')+'-DECODE']=decode;
		}
	}
	console.log(metadata);
	return metadata;
}

function updateElementAlpaca(formName, element) {
	var metadata = element.metadata; //prepareMetadataForPost(element.metadata);
	if(metadata.lenght==0){
		bootbox.alert('Attenzione, non ci sono dati da salvare.');
		return false;
	}
	metadata=alpacaMetadataPostProcess(formName, metadata);
	return $.ajax({
		method : 'POST',
		url :  baseUrl+'/app/rest/documents/xml/update/' + formName + '/' + element.id,
		data : metadata
	});

}

function saveElementAlpaca(formName, element, parent) {
	if(element.id) {
		if (typeof(emendamentoId) != "undefined" && emendamentoId>0 && elementInEmendamento){
			return updateElementEmeAlpaca(formName, element);
		}else{
			return updateElementAlpaca(formName, element);
		}
	} else {
		var metadata = element.metadata; //prepareMetadataForPost(element.metadata);
		if(!parent && element.parent){
			if($.isPlainObject(element.parent) || $.isArray(element.parent)){
				parent=element.parent.id;
			}
			else{
				parent=element.parent;
			}
		}
		metadata.parentId = parent;
		metadata=alpacaMetadataPostProcess(formName, metadata);
		return $.ajax({
			method : 'POST',
			url : baseUrl+'/app/rest/documents/xml/save/' + formName,
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
		var checkboxProcessed={};
		form.find(':input'+templateFilter).each(function (){
			var label=$(this).attr('name');

			//label=label.replace(/^[^_]*_/,'');
			//if(empties[element.type.id].metadata[label]!=undefined){
				var type=$(this).attr('type');
				if (type != undefined) {
                    if (type == 'checkbox') {
                        if (checkboxProcessed[label] == undefined) {
                            checkboxProcessed[label] = true;
                            element.metadata[label] = [];
                        }
                        if (this.checked) {
                            if (element.metadata[label] == undefined) element.metadata[label] = [];
                            element.metadata[label][element.metadata[label].length] = this.value;
                        }
                    }
                    else if (type == 'radio') {
                        if (!multiples[label]) {
                            multiples[label] = true;
                            element.metadata[label] = '';
                        }
                        if (this.checked) {
                            element.metadata[label] = this.value;
                        }
                    }
                    else {
                        element.metadata[label] = $(this).val();
                    }
                }
			//}else{
			//}
			if($ && $.axmr){
				$.axmr.setUpdated(element);
			}
			
		});
  form.find('select'+templateFilter).each(function (){
    var elementId=$(this).attr('id');
    var label=$(this).attr('name');
    if (!elementId.endsWith('-select')) {  
      element.metadata[label] = $(this).val();
    }
    if($ && $.axmr){
				$.axmr.setUpdated(element);
			}
    
  });
		return element;
	};

function formToElementAlpaca(form,element,alpacaJSON){
	if(!((typeof form)=='object') && !$.isArray(form)){
		if(!form.match(/^#/)){
			form='#'+form;
		}
		form=$(form);
	}

	var multiples={};
	//Ciclo i campi in alpacaJSON

	$.each(alpacaJSON.options.fields, function(key, val){
		var label=key;
		var $item = $(":input[name="+label+"]");
		//var item = $item[0];
		//label=label.replace(/^[^_]*_/,'');
		if ($item.length>0){
			//OK, ho il campo nativo
			if(empties[element.type.id].metadata[label]!=undefined){
				if ($item[0]) {
					var type = $item.attr('type');
					var alen = $item.length;
					if (alen>1){
						//multivalore
						element.metadata[label] = '';
						$item.each(function(){
							if ($(this).is(':checked')){
								//gestire i multi-valori contemporanei
								element.metadata[label] = $(this).val();
							}
						});
					}else{
						element.metadata[label] = $item.val();
					}
				}
			}else{
				console.log(label);
				console.log(empties[element.type.id].metadata[label]);
			}
		}else{
			//Non ho campo nativo (es. checkbox).
			if (val.type=="checkbox"){
				$itmList = $("div[name="+label+"] input[type=checkbox]");
				element.metadata[label] = [];
				$itmList.each(function(){
					if ($(this).is(':checked')){
						//gestire i multi-valori contemporanei
						//element.metadata[label].push($(this).val());
						element.metadata[label].push($(this).attr("data-checkbox-value"));
					}
				});
			}else{
				console.log("Tipo non gestito: "+val.type); //alert(val);
			}
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


function showAuditData(elementId, templateName, fieldName) {
	bootbox.dialog({
		message: '<p class="text-center">Recupero audit trail del campo ...</p>',
		closeButton: false
	});
	$.getJSON(baseUrl + '/app/rest/documents/audit/' + elementId + '/' + templateName + '/' + fieldName, function (data) {
		bootbox.hideAll();
		if (data.length == 0) {
			bootbox.alert("Non sono presenti informazioni storiche sul campo");
		} else {
			var table = $('<table>');
			table.addClass("table table-striped table-bordered table-hover no-margin-bottom no-border-top");
			table.css('font-size', "12px");
			var thead = $('<thead>');
			var trThead = $('<tr>');
			trThead.append('<th>Utente</th>');
			trThead.append('<th>Tipo modifica</th>');
			trThead.append('<th>Data</th>');
			trThead.append('<th>Valore vecchio</th>');
			trThead.append('<th>Valore nuovo</th>');
			thead.append(trThead);
			table.append(thead);
			var tbody = $('<tbody>');
			for (i = 0; i < data.length; i++) {
				console.log(data[i]);
				var trRows = $('<tr>');

				var newDate = new Date();
				newDate.setTime(data[i].auditDate);
				var options = {
					year: 'numeric',
					month: '2-digit',
					day: '2-digit',
					hour: '2-digit',
					minute: '2-digit',
					second: "2-digit"
				};
				var auditDate = newDate.toLocaleDateString('it-IT', options);
				if (data[i].userFullName != undefined || data[i].userFullName != null) {
					trRows.append('<td>' + data[i].userFullName + '</td>');
				} else {
					trRows.append('<td>' + data[i].userid + '</td>');
				}
				var action = data[i].actionType;
				if (data[i].actionType == 'create') action = "Primo inserimento";
				if (data[i].actionType == 'update') action = "Modifica";
				if (data[i].actionType == 'delete') action = "Eliminazione";
				trRows.append('<td>' + action + '</td>');
				trRows.append('<td>' + auditDate + '</td>');
				if (data[i].oldValues != null) {
					var oldVal = "";
					for (v = 0; v < data[i].oldValues.length; v++) {
						if (data[i].oldValues.length > 1) {
							oldVal += "<li>";
						}
						if (data[i].dataType == 'DATE') {
							var valDate = new Date();
							valDate.setTime(data[i].oldValues[v]);
							oldVal += valDate.toLocaleDateString('it-IT', options);
						} else {
							var val = data[i].oldValues[v];
							if (typeof(val) != "undefined" && val != null) {
								var idx = val.indexOf("###");
								if (idx > 0) {
									var splits = val.split("###");
									oldVal += splits[1] + " (id: " + splits[0] + ")";
								} else {
									oldVal += data[i].oldValues[v];
								}
							}
						}
						if (data[i].oldValues.length > 1) {
							oldVal += "</li>";
						}
					}
					trRows.append('<td>' + oldVal + '</td>');
				} else {
					trRows.append('<td>&nbsp;</td>');
				}


				if (data[i].newValues != null) {
					var newVal = "";
					for (v = 0; v < data[i].newValues.length; v++) {
						if (data[i].newValues.length > 1) {
							newVal += "<li>";
						}
						if (data[i].dataType == 'DATE') {
							var valDate = new Date();
							valDate.setTime(data[i].newValues[v]);
							newVal += valDate.toLocaleDateString('it-IT', options);
						} else {
							var val = data[i].newValues[v];
							if (typeof(val) != "undefined" && val != null) {
								var idx = val.indexOf("###");
								if (idx > 0) {
									var splits = val.split("###");
									newVal += splits[1] + " (id: " + splits[0] + ")";
								} else {
									newVal += data[i].newValues[v];
								}
							}
						}
						if (data[i].newValues.length > 1) {
							newVal += "</li>";
						}
					}
					trRows.append('<td>' + newVal + '</td>');
				} else {
					trRows.append('<td>&nbsp;</td>');
				}

				tbody.append(trRows);
			}
			table.append(tbody);
			bootbox.dialog({
				className: "dialogWide",
				title: "Storico modifiche campo",
				message: table
			});
		}
	});
	return false;
}


function showEmeData(emeId, centerId) {
	bootbox.dialog({
		message: '<p class="text-center">Recupero modifiche emendamento ...</p>',
		closeButton: false
	});
	$.getJSON(baseUrl + '/app/rest/documents/emechanges_center_id/'+emeId+'/'+centerId, function (data) {
		bootbox.hideAll();
		if (data.length == 0) {
			bootbox.alert("Non sono presenti modifiche");
		} else {
			var table = $('<table>');
			table.addClass("table table-striped table-bordered table-hover no-margin-bottom no-border-top");
			table.css('font-size', "12px");
			var thead = $('<thead>');
			var trThead = $('<tr>');
			trThead.append('<th>Utente</th>');
			trThead.append('<th>Oggetto</th>');
			trThead.append('<th>Campo</th>');
			trThead.append('<th>Data</th>');
			trThead.append('<th>Valore vecchio</th>');
			trThead.append('<th>Valore nuovo</th>');
			thead.append(trThead);
			table.append(thead);
			var tbody = $('<tbody>');
			for (i = 0; i < data.length; i++) {
				console.log(data[i]);
				var trRows = $('<tr>');

				var newDate = new Date();
				newDate.setTime(data[i].auditDate);
				var options = {
					year: 'numeric',
					month: '2-digit',
					day: '2-digit',
					hour: '2-digit',
					minute: '2-digit',
					second: "2-digit"
				};
				var auditDate = newDate.toLocaleDateString('it-IT', options);
				if (data[i].userFullName != undefined || data[i].userFullName != null) {
					trRows.append('<td>' + data[i].userFullName + '</td>');
				} else {
					trRows.append('<td>' + data[i].userid + '</td>');
				}
				var action = data[i].actionType;
				var field = data[i].templateFieldName;
				if (data[i].actionType == 'create') action = "Primo inserimento";
				if (data[i].actionType == 'update') action = "Modifica";
				if (data[i].actionType == 'delete') action = "Eliminazione";
				trRows.append('<td>' + action.split('<br/>')[1] + '</td>');
				var label = messages[field];
				if (typeof(label)=="undefined"){
					label = field;
				}
				trRows.append('<td>' + label + '</td>');
				trRows.append('<td>' + auditDate + '</td>');
				if (data[i].oldValues != null) {
					var oldVal = "";
					for (v = 0; v < data[i].oldValues.length; v++) {
						if (data[i].oldValues.length > 1) {
							oldVal += "<li>";
						}
						if (data[i].dataType == 'DATE') {
							var valDate = new Date();
							valDate.setTime(data[i].oldValues[v]);
							oldVal += valDate.toLocaleDateString('it-IT', options);
						} else {
							var val = data[i].oldValues[v];
							if (typeof(val) != "undefined" && val != null) {
								var idx = val.indexOf("###");
								if (idx > 0) {
									var splits = val.split("###");
									oldVal += splits[1] + " (id: " + splits[0] + ")";
								} else {
									oldVal += data[i].oldValues[v];
								}
							}
						}
						if (data[i].oldValues.length > 1) {
							oldVal += "</li>";
						}
					}
					trRows.append('<td>' + oldVal + '</td>');
				} else {
					trRows.append('<td>&nbsp;</td>');
				}


				if (data[i].newValues != null) {
					var newVal = "";
					for (v = 0; v < data[i].newValues.length; v++) {
						if (data[i].newValues.length > 1) {
							newVal += "<li>";
						}
						if (data[i].dataType == 'DATE') {
							var valDate = new Date();
							valDate.setTime(data[i].newValues[v]);
							newVal += valDate.toLocaleDateString('it-IT', options);
						} else {
							var val = data[i].newValues[v];
							if (typeof(val) != "undefined" && val != null) {
								var idx = val.indexOf("###");
								if (idx > 0) {
									var splits = val.split("###");
									newVal += splits[1] + " (id: " + splits[0] + ")";
								} else {
									newVal += data[i].newValues[v];
								}
							}
						}
						if (data[i].newValues.length > 1) {
							newVal += "</li>";
						}
					}
					trRows.append('<td>' + newVal + '</td>');
				} else {
					trRows.append('<td>&nbsp;</td>');
				}

				tbody.append(trRows);
			}
			table.append(tbody);
			bootbox.dialog({
				className: "dialogWide",
				title: "Modifiche emendamento",
				message: table
			});
		}
	});
	return false;
}


function deleteElement(element) {
	if(!((typeof element)=='object') && !$.isArray(element)){
		if(isNaN(parseInt(element))){
			bootbox.alert("Attenzione impossibile riconoscere l'elemento da eliminare");
			return;
		}else{
			return $.ajax({
				url : '../../rest/documents/delete/' + element,

			}).done(function() {
				console.log('DELETED');
				window.location.reload();
			});
		}

	}else if (!element || !element.id){
		bootbox.alert("Attenzione impossibile riconoscere l'elemento da eliminare");
		return;
	}
	else{
		return $.ajax({
			url : '../../rest/documents/delete/' + element.id,

		}).done(function() {
			console.log('DELETED');
			window.location.reload();
		});
	}
}
