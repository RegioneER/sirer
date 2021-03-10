
function deleteElement(element){
	if(element && element.id){
	return $.ajax({
		url:'../../rest/documents/delete/'+element.id,
		data:element.metadata
	}).done(function(){console.log('DELETED');}).fail(alertError);
	}else if (element){
		return $.ajax({
			url:'../../rest/documents/delete/'+element,
			data:element.metadata
		}).done(function(){console.log('DELETED');}).fail(alertError);
	}
}

function deleteElementRow(element,dom){
	if (element){
		return $.ajax({
			url:'../../rest/documents/delete/'+element,
			data:element.metadata
		}).done(function(){bootbox.alert('Eliminazione effettuata con successo.');$(dom).closest('tr').remove();}).fail(alertError);
	}
}