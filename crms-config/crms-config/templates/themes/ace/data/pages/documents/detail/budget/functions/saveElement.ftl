function saveElement(element,parent){
	if(element.id){
		return updateElement(element);
	}
	else{
		var metadata=prepareMetadataForPost(element.metadata);
		metadata.parentId=parent;
    	return $.ajax({
    		method:'POST',
    		url:'../../rest/documents/save/'+element.type.id,
    		data:metadata
    	}).done(function (data){
    		element.id=data.ret;
    	});
    	 
    }
}