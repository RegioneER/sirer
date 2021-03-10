<#assign type=model['docDefinition']/>
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["jquery-ui-full", "datepicker","pages/studio.css","x-editable","select2"],
	"scripts" : ["jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable","select2","base"],
	"inline_scripts":[],
	"title" : "Dettaglio emendamento",
 	"description" : "Dettaglio emendamento" 
} />
<#assign elStudio=el.getParent() />

<#include "../../partials/navigation/navigazione_studio.ftl">
<#include "../../partials/form-elements/elementSpecific.ftl">
<#include "../../partials/form-elements/select.ftl" />
<@breadcrumbsData el />
<#assign json=el.type.getDummyJson() />
<#assign loadedJson=el.getElementCoreJsonToString(userDetails) />
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
 	
 	empties[dummy.type.id]=dummy;
	
	
	$('#document-form-submit').ready(function() {
		$('#DatiEmendamento_inviatoEme').parent().parent().hide();//caso template Form (creazione)
		$('#informations-DatiEmendamento_inviatoEme').hide();//caso template Dettaglio (modifica, visualizzazione)
	});

	$(document).ready(function(){
		$("input[name='DatiEmendamento_TipologiaEme']").change(function(){

			if($("#DatiEmendamento_TipologiaEme:checked").val()=="3###Altre comunicazioni"){
				$('#informations-DatiEmendamento_SpecificareComunicazione').show();
			}
			else{
				$('#DatiEmendamento_SpecificareComunicazione-select').val("").change();
				$('#informations-DatiEmendamento_SpecificareComunicazione').hide();
			}
		});
		$("input[name='DatiEmendamento_TipologiaEme']").trigger("change");
	});
</@script>