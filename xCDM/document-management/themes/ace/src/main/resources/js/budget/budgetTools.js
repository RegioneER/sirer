var folderTp,folderPrestazioni,folderTpxp,folderPxp,folderPxpCTC,folderPxs,folderPxsCTC,folderBudgetStudio;


function buildTpDescription(tp) {
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


