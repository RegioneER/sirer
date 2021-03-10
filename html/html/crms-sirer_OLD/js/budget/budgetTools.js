var folderTp,folderPrestazioni,folderTpxp,folderPxp,folderPxpCTC,folderPxs,folderPxsCTC,folderBudgetStudio;

function buildTpDescription(tp){
    var metadata=prepareMetadataForPost(tp.metadata);
    var ricoveri=new Array();
    ricoveri['Ricovero_Ordinario']='ORD.';
    ricoveri['Ricovero_Straordinario']='EXTRA.';
    ricoveri['Ricovero_Ambulatoriale']='AMB.';
    ricoveri['Ricovero_Telefonico']='TEL.';
    var ricoveriStr='';
    for(var curr in ricoveri){
        if(metadata[curr])ricoveriStr+=ricoveri[curr]+'\n';
    }
    var description='';
    if(metadata['TimePoint_DescrizioneSelect']) description=metadata['TimePoint_DescrizioneSelect'].split('###')[1]+'\n';
    else description='\n';
     if(metadata['TimePoint_NumeroVisita']) description='Visita '+metadata['TimePoint_NumeroVisita']+' \n '+description;
     else description+="\n"
     if(metadata['TimePoint_Tempi'] && metadata['TimePoint_TempiSelect']) description+='Tempo: '+metadata['TimePoint_Tempi']+' '+metadata['TimePoint_TempiSelect'].split('###')[1]+'\n';
     else description+="\n"
     if(metadata['TimePoint_DurataSelect'] && metadata['TimePoint_DurataSelect']) description+='Durata: '+metadata['TimePoint_DurataCiclo']+' '+metadata['TimePoint_DurataSelect'].split('###')[1]+'\n';
     else description+="\n"
     if(metadata['TimePoint_RicoveroSelect'] )description+='Ricovero: '+metadata['TimePoint_RicoveroSelect'].split('###')[1]    ;

    return description;
}

function buildTpDescription_old(tp) {
	var metadata = prepareMetadataForPost(tp.metadata);
	var ricoveri = new Array();
	ricoveri['Ricovero_Ordinario'] = 'ORD.';
	ricoveri['Ricovero_Straordinario'] = 'EXTRA.';
	ricoveri['Ricovero_Ambulatoriale'] = 'AMB.';
	ricoveri['Ricovero_Telefonico'] = 'TEL.';
	var ricoveriStr = '';
	for(var curr in ricoveri) {
		if(metadata[curr])
			ricoveriStr += ricoveri[curr] + '\n';
	}
	var description = metadata['TimePoint_Descrizione'] + '\n';
	if(metadata['TimePoint_NumeroVisita'])
		description = metadata['TimePoint_NumeroVisita'] + ' - ' + description;
	if(metadata['TimePoint_Tempi'])
		description += 'Tempi: ' + metadata['TimePoint_Tempi'] + '\n';
	if(metadata['TimePoint_DurataCiclo'])
		description += 'Durata: ' + metadata['TimePoint_DurataCiclo'] + '\n';
	if(ricoveriStr)
		description += 'Ricovero: ' + ricoveriStr;

	return description;
}
/*
function saveGrid(grid,xLink,yLink,rowNum,colNum,folders){
	var layout=$.extend(true,[],$('#'+grid).data('handsontable').getData());
	var elements=$.extend(true,{},$.axmr.getAllElements());
	var coordinates={"x":xLink,"y":yLink,"row":rowNum,"col":colNum};
	var updatedElementsCount=$.axmr.countUpdated()+"";	

	$.each(layout, function (row,cols){
	    $.each(cols,function(col,value){
	       if(value)layout[row][col]=value.toString();
	    });   
	});
	
	$.each(elements,function(idx,element){
	   elements[idx]=prepareElementForPost(element);
	});
	
	folders=prepareElementForPost(folders);
	var grid=$.extend(true,{},{"layout":layout,"elements":elements,"folders":folders,"coordinates":coordinates,"updatedElementsCount":updatedElementsCount});
	var data={"grid":JSON.stringify(grid)};
	return $.ajax({
	        		method:'POST',
	        		url:'../../rest/documents/updateGrid',
	        		data:data
	        });
}
*/
function saveGrid(grid,xLink,yLink,rowNum,colNum,folders,url,bulk){
	grid = grid || '#example';
	url = url || '../../rest/documents/updateGrid';
	var layout=$.extend(true,[],$(grid).data('handsontable').getData());
	var elements=$.extend(true,{},$.axmr.getAllElements());
	var additionals=$.extend(true,{},$.axmr.getAllAdditionals());
	if(!folders){
		folders={};
		folders[emptyTimePoint.type.id]=folderTp;
		folders[emptyPrestazione.type.id]=folderPrestazioni;
		folders[emptytpxp.type.id]=folderTpxp;
	}
	
	var coordinates={"x":xLink,"y":yLink,"row":rowNum,"col":colNum};
	var updatedElementsCount=$.axmr.countUpdated()+"";
	
	$.each(layout, function (row,cols){
	    $.each(cols,function(col,value){
	       if(value)layout[row][col]=value.toString();
	    });   
	});
	
	$.each(elements,function(idx,element){
	   elements[idx]=prepareElementForPost(element);
	});
	$.each(additionals,function(idx,element){
		additionals[idx]=prepareElementForPost(element);
	});
	if(bulk){
		additionals=$.extend(true,additionals,elements);
		elements={};
	}
	
	folders=prepareElementForPost(folders);
	var grid=$.extend(true,{},{"layout":layout,"elements":elements,"additionals":additionals,"folders":folders,"coordinates":coordinates,"updatedElementsCount":updatedElementsCount});
	var data={"grid":JSON.stringify(grid)};
	return $.ajax({
	        		method:'POST',
	        		url:url,
	        		data:data
	        });
}


