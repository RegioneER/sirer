
function parseElement(data){
		instance.elements.globalData=data;
	if(data.children && data.children.length>0){
			$.each(data.children,function(index,child){
				var type=child.type.typeId;
				
				switch(type){
					case 'FolderTimePoint':
						folderTp=child.id;
						instance.elements.tp=child.children;
						instance.elements.tp.sort(sortTp);
					break;
					case 'FolderPrestazioni':
						folderPrestazioni=child.id;
						instance.elements.prestazioni=child.children;
						instance.elements.prestazioni.sort(sortPrestazioni);
					break;
					case 'FolderTpxp':
						folderTpxp=child.id;
						instance.elements.tpxp=child.children;
						//instance.elements.tpxp2update=sortTpxp2update(child.children);
					break;
					case 'FolderCostiAggiuntivi':
						folderCostiAggiuntivi=child.id;
						instance.elements.costiAggiuntivi=child.children;
					case 'FolderPXP':
						folderPxp=child.id;
						instance.elements.pxp=child.children;
					break;
					case 'FolderPXS':
						folderPxs=child.id;
						instance.elements.pxs=child.children;
					break;
					case 'FolderPXPCTC':
						folderPxpCTC=child.id;
						instance.elements.pxpCTC=child.children;
					break;
					case 'FolderPXSCTC':
						folderPxsCTC=child.id;
						instance.elements.pxsCTC=child.children;
					break;
					case 'FolderPassthroughCTC':
						folderPassthroughCTC=child.id;
						instance.elements.passthroughCTC=child.children;
					break;
					case 'FolderBracci':
						folderBracci=child.id;
						instance.elements.bracci=child.children;
					break;
					case 'FolderBudgetStudio':
						folderBudgetStudio=child.id;
						
						if($.isArray(child.children) && child.children.length>0){
							instance.elements.budgetStudio=child.children[0];
						}
						else{
							instance.elements.budgetStudio=$.extend(true,{},emptyBudgetCTC);
						}
					break;
					case 'FolderSingoloBraccio':
							folderBracci=child.id;
							break;
				}
			
			});
		}else{
			$.each(groupItems,function(index,child){
				var type=child.type.typeId;
				
				switch(type){
					case 'FolderTimePoint':
						folderTp=child.id;
						break;
					case 'TimePoint':
						instance.elements.tp[instance.elements.tp.length]=child;
					break;
					case 'FolderPrestazioni':
						folderPrestazioni=child.id;
						break;
					case 'Prestazione':
						if((typeof isUO === 'undefined') || (typeof authorities === 'undefined') || !isUO || isCurrPI){
							instance.elements.prestazioni[instance.elements.prestazioni.length]=child;
						}else if(('Prestazioni_UOCCode' in child.metadata) && child.metadata['Prestazioni_UOCCode'][0]){
							if(getDato(child.metadata['Prestazioni_UOCCode']) in authorities || getDato(child.metadata['Prestazioni_UOC']) in authorities){
								instance.elements.prestazioni[instance.elements.prestazioni.length]=child;
							}
						}
					break;
					case 'PrezzoPrestazione':
						var currTp=getDato(child.metadata['PrezzoFinale_Prestazione']);
						if(currTp.type.typeId=='TimePoint'){
							instance.elements.target[currTp.id]=child;
						}
						else{
							instance.elements.prezzi[instance.elements.prezzi.length]=child;
						}
						
					break;
					case 'FolderCostiAggiuntivi':
						folderCostiAggiuntivi=child.id;
						break;
					case 'CostoAggiuntivo':
						instance.elements.costiAggiuntivi[instance.elements.costiAggiuntivi.length]=child;
						break;
					case 'FolderTpxp':
						folderTpxp=child.id;
						break;
					case 'tpxp':
						instance.elements.tpxp[instance.elements.tpxp.length]=child;
					break;
					case 'FolderPXP':
						folderPxp=child.id;
						break;
					case 'PrestazioneXPaziente':
						if((typeof isUO === 'undefined') || (typeof authorities === 'undefined') || !isUO || isCurrPI){
							instance.elements.pxp[instance.elements.pxp.length]=child;
						}else if(('Prestazioni_UOCCode' in child.metadata) && child.metadata['Prestazioni_UOCCode'][0]){
							if(child.metadata['Prestazioni_UOCCode'][0] in authorities){
								instance.elements.pxp[instance.elements.pxp.length]=child;
							}
						}
						
					break;
					case 'FolderPXS':
						folderPxs=child.id;
						break;
					case 'PrestazioneXStudio':
						if((typeof isUO === 'undefined') || (typeof authorities === 'undefined') || !isUO || isCurrPI){
							if(child.parentTypeId=='FolderPXS'){
								instance.elements.pxs[instance.elements.pxs.length]=child;
							}else if(child.parentTypeId=='FolderPXSCTC'){
								instance.elements.pxsCTC[instance.elements.pxsCTC.length]=child;
							} if(child.parentTypeId=='FolderPassthroughCTC'){
								instance.elements.passthroughCTC[instance.elements.passthroughCTC.length]=child;
							}
						}else if(('Prestazioni_UOCCode' in child.metadata) && child.metadata['Prestazioni_UOCCode'][0]){
							if(child.metadata['Prestazioni_UOCCode'][0] in authorities){
								if(child.parentTypeId=='FolderPXS'){
									instance.elements.pxs[instance.elements.pxs.length]=child;
								}else if(child.parentTypeId=='FolderPXSCTC'){
									instance.elements.pxsCTC[instance.elements.pxsCTC.length]=child;
								} if(child.parentTypeId=='FolderPassthroughCTC'){
									instance.elements.passthroughCTC[instance.elements.passthroughCTC.length]=child;
								}
							}
						}
						
					break;
					case 'FolderPXSCTC':
						folderPxsCTC=child.id;
						
					break;
					case 'FolderPrezzi':
						folderPrezzi=child.id;
						
					break;
					case 'FolderPassthroughCTC':
						folderPassthroughCTC=child.id;
						
					break;
					
					case 'FolderBracci':
						folderBracci=child.id;
						break;
					case 'Braccio':
						instance.elements.bracci[instance.elements.bracci.length]=child;
					break;
					
					case 'FolderBudgetStudio':
						folderBudgetStudio=child.id;
						instance.elements.budgetStudio=$.extend(true,{},emptyBudgetCTC);
						
					break;
					case 'FolderSingoloBraccio':
							folderBracci=child.id;
							break;
				}
			
			});
			instance.elements.tp.sort(sortTp);
			instance.elements.prestazioni.sort(sortPrestazioni);
		}
		instance.elements.tpxp2update=$.extend(true,[],instance.elements.tpxp);
		var data=getDataFromObj(instance.elements);
		//var costi=getCostiFromObj(instance.elements);
		console.log(instance.elements);
		console.log(data);
		loadPrezzi();
		calcolaTotali();
		var checkFolders=false;
		if(folderTp==null){
    		//saveElement(emptyFolderTimePoint,id);
    		checkFolders=true;
    	}
    	if(folderPrestazioni==null){
    		//saveElement(emptyFolderPrestazioni,id);
    		checkFolders=true;
    	}
    	if(folderTpxp==null){
    		//saveElement(emptyFolderTpxp,id);
    		checkFolders=true;
    	}
    	if(folderPxp==null){	
			//saveElement(emptyFolderPXP,id);
    		checkFolders=true;
    	}
    	if(folderCostiAggiuntivi==null){
    		//saveElement(emptyFolderPXP,id);
    		checkFolders=true;
    	}
    	if(folderPxs==null){
    		//saveElement(emptyFolderPXS,id);
    		checkFolders=true;
    	}
    	if(folderBudgetStudio==null){
    		//saveElement(emptyFolderBudgetStudio,id);
    		instance.elements.budgetStudio=$.extend(true,{},emptyBudgetCTC);
    		checkFolders=true;
    	}
    	if(folderPxpCTC==null){
    		//saveElement(emptyFolderPXPCTC,id);
    		checkFolders=true;
    	}
    	if(folderPxsCTC==null){
    		//saveElement(emptyFolderPXSCTC,id);
    		checkFolders=true;
    	}if(folderPassthroughCTC==null){
    		//saveElement(emptyFolderPassthroughCTC,id);
    		checkFolders=true;
    	}
    	if(checkFolders){
    		setTimeout(function(){getFolders(id)},100);
    	}
    	if(callback) callback(instance);
    	toggleLoadingScreen();
    	
}
				