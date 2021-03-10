
function getFolders(id,reload){
	if(!(folderCostiAggiuntivi!=null && folderTp!=null && folderPrestazioni!=null && folderTpxp!=null && folderPxp!=null && folderPxs!=null && folderBudgetStudio!=null)){
		$.ajax({
			dataType: "json",
			url:'../../rest/documents/getElementJSON/'+id
		}).done(function(data){
			if(data.children.length>0){
				$.each(data.children,function(index,child){
					var type=child.type.typeId;
					
					switch(type){
						case 'FolderTimePoint':
							folderTp=child.id;
							
						break;
						case 'FolderPrestazioni':
							folderPrestazioni=child.id;
							
						break;
						case 'FolderCostiAggiuntivi':
							folderCostiAggiuntivi=child.id;
							
						break;
						case 'FolderTpxp':
							folderTpxp=child.id;
							
						break;
						case 'FolderPXP':
							folderPxp=child.id;
						break;
						case 'FolderBudgetStudio':
							folderBudgetStudio=child.id;
						break;
						case 'FolderPXS':
							folderPxs=child.id;
						break;
						
						case 'FolderPXPCTC':
							folderPxpCTC=child.id;
						break;
						case 'FolderPXSCTC':
							folderPxsCTC=child.id;
						break;
						case 'FolderPassthroughCTC':
							folderPassthroughCTC=child.id;
						break;
					}
				
				});
			}
			setTimeout(function(){getFolders(id,true)},1000);
			if(reload) console.log('Please reload');
		});
		
	}
}
			