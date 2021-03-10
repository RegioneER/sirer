
function updateElement(element){
	var metadata=prepareMetadataForPost(element.metadata);
	
	return $.ajax({
		method:'POST',
		url:'../../rest/documents/update/'+element.id,
		data:metadata
	});
	
}
        