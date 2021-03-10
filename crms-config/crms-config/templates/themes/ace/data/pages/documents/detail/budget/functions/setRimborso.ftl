
function setRimborso(id,valore){
	var myElement=$.axmr.guid(id);
	myElement.metadata['Rimborso_Rimborsabilita']=valore;
	$.axmr.setUpdated(myElement);
}
        