
function findElement(element,parent){
	
		var metadata=prepareMetadataForPost(element.metadata);
		metadata.parentId=parent;
    	return $.ajax({
    		method:'POST',
    		url:'../../rest/documents/searchByExample/'+element.type.id,
    		data:metadata
    	}).done(function(){console.log('Found!!!');}).fail(function(){console.log('error',element);});
    	 
   
    }
        