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
			}).fail(alertError);
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
		}).fail(alertError);
	}
}