<#assign type=model['docDefinition']/>
<#global page={
    "content": path.pages+"/"+mainContent,
    "styles" : ["jquery-ui-full", "datepicker","pages/form.css","jqgrid"],
    "scripts" : ["jquery-ui-full","datepicker","bootbox", "common/elementEdit.js","token-input","jqgrid","pages/home.js"],
    "inline_scripts":[],
    "title" : "Dettaglio centro",
    "description" : "Dettaglio centro" 
} />
<#assign elStudio=el.getParent() />

<#include "../../partials/navigation/navigazione_studio.ftl">
<#include "../../partials/form-elements/elementSpecific.ftl">
<#include "../../partials/form-elements/select.ftl" />
<@breadcrumbsData el />
<#assign json=el.type.getDummyJson() />
<#assign loadedJson=el.getElementCoreJsonToString(userDetails) />




<@script>
var loadedElement=${loadedJson};
loadedElement.id=${el.id};
var empties=new Array();
empties[${el.type.id}]=loadedElement;

$('#document-form-submit').ready(function() {
	$('#IstruttoriaCE_istruttoriaWFinviata').parent().parent().hide();
	if($('#IstruttoriaCE_DocCompleta:checked').val()!==undefined && $('#IstruttoriaCE_DocCompleta:checked').val().split("###")[0]==2){
		$('#informations-IstruttoriaCE_CompletezzaDt').hide();
		//$('#informations-IstruttoriaCE_Note').hide();
	}
	
	if($('#IstruttoriaCE_DocCompleta:checked').val()!==undefined && $('#IstruttoriaCE_DocCompleta:checked').val().split("###")[0]==1){
		$('#informations-IstruttoriaCE_IntegrazioniDt').hide();
		//$('#informations-IstruttoriaCE_RichIntegr').hide();
	}
	
	});

	$("[name=IstruttoriaCE_DocCompleta]").on('change',function(){
		
		if($('#IstruttoriaCE_DocCompleta:checked').val()!==undefined && $('#IstruttoriaCE_DocCompleta:checked').val().split("###")[0]==1){
			$('#informations-IstruttoriaCE_CompletezzaDt').show();
			//$('#informations-IstruttoriaCE_Note').show();
			$('#informations-IstruttoriaCE_IntegrazioniDt').hide();
			$('[id=IstruttoriaCE_IntegrazioniDt]').val('');//se nascondo sbianco il valore!
			$('#informations-IstruttoriaCE_RiapriSoloDoc').hide();
			$('[id=IstruttoriaCE_RiapriSoloDoc').prop('checked', false);//se nascondo sbianco il valore!
			//$('#informations-IstruttoriaCE_RichIntegr').hide();
			//$('[id=IstruttoriaCE_RichIntegr]').val('');//se nascondo sbianco il valore!
		}
		else if ($('#IstruttoriaCE_DocCompleta:checked').val()!==undefined && $('#IstruttoriaCE_DocCompleta:checked').val().split("###")[0]==2){
			$('#informations-IstruttoriaCE_CompletezzaDt').hide();
			$('[id=IstruttoriaCE_CompletezzaDt]').val('');//se nascondo sbianco il valore!
			//$('#informations-IstruttoriaCE_Note').hide();
			//$('[id=IstruttoriaCE_Note]').val('');//se nascondo sbianco il valore!
			$('#informations-IstruttoriaCE_IntegrazioniDt').show();
			$('#informations-IstruttoriaCE_RiapriSoloDoc').show();
			//$('#informations-IstruttoriaCE_RichIntegr').show();
		}
		else {
			$('#informations-IstruttoriaCE_CompletezzaDt').hide();
			$('[id=IstruttoriaCE_CompletezzaDt]').val('');//se nascondo sbianco il valore!
			//$('#informations-IstruttoriaCE_Note').hide();
			//$('[id=IstruttoriaCE_Note]').val('');//se nascondo sbianco il valore!
			$('#informations-IstruttoriaCE_IntegrazioniDt').hide();
			$('[id=IstruttoriaCE_IntegrazioniDt]').val('');//se nascondo sbianco il valore!
			$('#informations-IstruttoriaCE_RiapriSoloDoc').hide();
			$('[id=IstruttoriaCE_RiapriSoloDoc').prop('checked', false);//se nascondo sbianco il valore!
			//$('#informations-IstruttoriaCE_RichIntegr').hide();
			//$('[id=IstruttoriaCE_RichIntegr]').val('');//se nascondo sbianco il valore!
		}
	});
   
   
</@script>