			//salvo Bracci
        	$.each(docObj.elements.bracci,function(i,braccio){
        		if(braccio){
        			queue=$.when(queue).then(function(data){
        				return saveElement(braccio,folderBracci);
        			});
        		}
        	});	