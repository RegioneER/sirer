<#assign type=model['docDefinition']/>
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["jquery-ui-full", "datepicker","pages/studio.css","x-editable","select2"],
	"scripts" : ["jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable","select2","base"],
	"inline_scripts":[],
	"title" : "Dettaglio allegato",
 	"description" : "Dettaglio allegato" 
} />
<@breadcrumbsData el />
<#assign json=el.type.getDummyJson() />
<#assign loadedJson=el.getElementCoreJsonToString(userDetails) />
<@script>


	// @ManuelGozzi :: STSANSVIL-2613
	let jsonObject_toRestrict = ${loadedJson};

	// Booleano che identifica la necessit� di nascondere i dati "Data delibera" e "Numero protocollo delibera"
	var hideInformations = true;

	if (jsonObject_toRestrict !== null
		&& jsonObject_toRestrict.metadata !== null
		&& (jsonObject_toRestrict.metadata.tipologiaContratto_TipoContratto !== undefined &&
		jsonObject_toRestrict.metadata.tipologiaContratto_TipoContratto !== null)
		&& jsonObject_toRestrict.metadata.tipologiaContratto_TipoContratto.length > 0) {

		let tipoContratto = jsonObject_toRestrict.metadata.tipologiaContratto_TipoContratto[0];

			if (tipoContratto !== null) {
				let splitContratto = tipoContratto.split("###");
				if (splitContratto !== null && splitContratto[0] === '7') {

				// Visualizzo i dati quando il tipo del contratto � [7 - Nulla osta aziendale]
				hideInformations = false;
			}
		}
	}
</@script>
<#include "../../partials/form-elements/elementSpecific.ftl">
<@script>
	$.fn.editable.defaults.mode = 'inline';
	
	$('.field-inline-anchor').editable({
	    params: function(params) {
		    var metadata={};
		    metadata[params.name]=params.value
		   
		    return metadata;
	    },
	    emptytext :"Valore mancante"	
	});
	
 	var loadedElement=${loadedJson};
 	var dummy=${json};
 	var empties=new Array();

	if (hideInformations === true) {

		let protocDelibera = $('#informations-tipologiaContratto_NProtocolloDelibera');
		if (protocDelibera !== null) {

			protocDelibera.hide();
		}

		let dataDelibera = $('#informations-tipologiaContratto_DataDelibera');
		if (dataDelibera !== null) {

			dataDelibera.hide();
		}
	}
 	
 	empties[dummy.type.id]=dummy;
</@script>

