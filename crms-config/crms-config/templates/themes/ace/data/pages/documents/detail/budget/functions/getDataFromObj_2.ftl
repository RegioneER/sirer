
function getDataFromObj(myObject){
        	var result=new Array();
        	var currRow=new Array();
    		currRow[0]='';
    		$.each(myObject.tp,function(k,currTp){
    			//currRow[k+1]=currTp.metadata['TimePoint_Descrizione'];
    			currRow[k+1]=$.axmr.guid(currTp,buildTpDescription(currTp));
    			currTp.coordinates={x:k+1,y:1};
    		});
    		result[0]=currRow;
        	$.each(myObject.prestazioni, function(i,currPrestazione){
        		var row=i+1;
        		currRow=new Array();
				var labelPrestazione='';
				if(!labelPrestazione)labelPrestazione='';
				else labelPrestazione+=' '
				labelPrestazione+=getDato(currPrestazione.metadata['Prestazioni_prestazione']);
				if(labelPrestazione.length>18){
					labelPrestazione=labelPrestazione.substr(0,15)+'...';
				}
						
				currRow[0]=$.axmr.guid(currPrestazione,labelPrestazione);
        		currPrestazione.coordinates={x:1,y:i+1};
        		for(var col=1;col<result[0].length;col++){
        			currRow[col]='';
        		}
        		result[row]=currRow;
        	});
        	var keep=new Array();
        	keep[0]=true;
        	$.each(myObject.tpxp, function(i,currTpxp){
        		
        		var prestaAssoc='';
        		var tpAssoc='';
        		if($.isPlainObject(getDato(currTpxp.metadata['tp-p_Prestazione']))) prestaAssoc=$.axmr.getById(getDato(currTpxp.metadata['tp-p_Prestazione'])['id']);
        		if($.isPlainObject(getDato(currTpxp.metadata['tp-p_TimePoint']))) tpAssoc=$.axmr.getById(getDato(currTpxp.metadata['tp-p_TimePoint'])['id']);
        		if(prestaAssoc && tpAssoc){
        			result[prestaAssoc.coordinates.y][tpAssoc.coordinates.x]=$.axmr.guid(currTpxp,getDato(currTpxp.metadata['tp-p_Checked']),getDato(currTpxp.metadata['Costo_TransferPrice']));
        			keep[prestaAssoc.coordinates.y]=true;
        		}
        		
        		
        	});
        	var newResult=new Array();
        	$.each(result,function(rowIdx,row){
        		var y=rowIdx;
        		if(keep[y]){
        			newResult[newResult.length]=result[rowIdx];
        		}
        	});
        	return newResult;
        }
        