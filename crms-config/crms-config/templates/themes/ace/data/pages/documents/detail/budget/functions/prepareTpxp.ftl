
function prepareTpxp(value,p,tp){
	if(!value){
		//non dovrei più entrare qui
		console.log('non dovrei più entrare qui');
			return;
		}
			
	var myElement=$.extend(true,{},emptytpxp);
	if(value){
			myElement.metadata['tp-p_Prestazione']=$.axmr.guid($('#example').handsontable('getDataAtCell',p,0));
			myElement.metadata['tp-p_Checked']=1;
			docObj.elements.tpxp[docObj.elements.tpxp.length]=myElement;
		
		}
	myElement.coordinates={x:tp,y:p};
	var guid=$.axmr.guid(myElement);
	
	$.axmr.setUpdated(myElement);
	return myElement;
	
}
        