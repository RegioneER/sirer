<#assign type=model['docDefinition']/>
<#global page={
    "content": path.pages+"/"+mainContent,
    "styles" : ["jquery-ui-full", "datepicker","pages/form.css","jqgrid"],
    "scripts" : ["jquery-ui-full","datepicker","bootbox", "common/elementEdit.js","token-input","jqgrid","pages/home.js"],
    "inline_scripts":[],
    "title" : "Dettaglio progetto",
    "description" : "Dettaglio progetto" 
} />


<#include "../../partials/navigation/navigazione_progetto.ftl">
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

	
/*
	$("[name=ParereCe_esitoParere]").on('change',function(){
		
		if($('#ParereCe_esitoParere:checked').val()!==undefined && $('#ParereCe_esitoParere:checked').val().split("###")[0]==1){ 
			$('#informations-ParereCe_MotivazioniSosp').hide();
			$('[name=ParereCe_MotivazioniSosp-select]').val('');//se nascondo sbianco il valore!
			$('[name=ParereCe_MotivazioniSosp-select]').trigger('change');//se nascondo sbianco il valore!

			$('#informations-ParereCe_MotivazioniNonFav').hide();
			$('[name=ParereCe_MotivazioniNonFav-select]').val('');//se nascondo sbianco il valore!
			$('[name=ParereCe_MotivazioniNonFav-select]').trigger('change');//se nascondo sbianco il valore!
			
			$('#informations-ParereCe_MotivazioniCond').hide();
			$('[id=ParereCe_MotivazioniCond]').val('');//se nascondo sbianco il valore!
			
			$('#informations-ParereCe_RiapriSoloDoc').hide();
			$('[id=ParereCe_RiapriSoloDoc').prop('checked', false);//se nascondo sbianco il valore!
		}
		else if ($('#ParereCe_esitoParere:checked').val()!==undefined && $('#ParereCe_esitoParere:checked').val().split("###")[0]==2){
			$('#informations-ParereCe_MotivazioniSosp').show();
			//$('[name=ParereCe_MotivazioniSosp-select]').val('');//se nascondo sbianco il valore!
			//$('[name=ParereCe_MotivazioniSosp-select]').trigger('change');//se nascondo sbianco il valore!

			$('#informations-ParereCe_MotivazioniNonFav').hide();
			$('[name=ParereCe_MotivazioniNonFav-select]').val('');//se nascondo sbianco il valore!
			$('[name=ParereCe_MotivazioniNonFav-select]').trigger('change');//se nascondo sbianco il valore!
			
			$('#informations-ParereCe_MotivazioniCond').hide();
			$('[id=ParereCe_MotivazioniCond]').val('');//se nascondo sbianco il valore!
			
			$('#informations-ParereCe_RiapriSoloDoc').show();
		}
		else if ($('#ParereCe_esitoParere:checked').val()!==undefined && $('#ParereCe_esitoParere:checked').val().split("###")[0]==3){
			$('#informations-ParereCe_MotivazioniSosp').hide();
			$('[name=ParereCe_MotivazioniSosp-select]').val('');//se nascondo sbianco il valore!
			$('[name=ParereCe_MotivazioniSosp-select]').trigger('change');//se nascondo sbianco il valore!

			$('#informations-ParereCe_MotivazioniNonFav').show();
			//$('[name=ParereCe_MotivazioniNonFav-select]').val('');//se nascondo sbianco il valore!
			//$('[name=ParereCe_MotivazioniNonFav-select]').trigger('change');//se nascondo sbianco il valore!
			
			$('#informations-ParereCe_MotivazioniCond').hide();
			$('[id=ParereCe_MotivazioniCond]').val('');//se nascondo sbianco il valore!
			
			$('#informations-ParereCe_RiapriSoloDoc').hide();
			$('[id=ParereCe_RiapriSoloDoc').prop('checked', false);//se nascondo sbianco il valore!
		}
		else if ($('#ParereCe_esitoParere:checked').val()!==undefined && $('#ParereCe_esitoParere:checked').val().split("###")[0]==4){
			$('#informations-ParereCe_MotivazioniSosp').hide();
			$('[name=ParereCe_MotivazioniSosp-select]').val('');//se nascondo sbianco il valore!
			$('[name=ParereCe_MotivazioniSosp-select]').trigger('change');//se nascondo sbianco il valore!

			$('#informations-ParereCe_MotivazioniNonFav').hide();
			$('[name=ParereCe_MotivazioniNonFav-select]').val('');//se nascondo sbianco il valore!
			$('[name=ParereCe_MotivazioniNonFav-select]').trigger('change');//se nascondo sbianco il valore!
			
			$('#informations-ParereCe_MotivazioniCond').show();
			//$('[id=ParereCe_MotivazioniCond]').val('');//se nascondo sbianco il valore!
			
			$('#informations-ParereCe_RiapriSoloDoc').hide();
			$('[id=ParereCe_RiapriSoloDoc').prop('checked', false);//se nascondo sbianco il valore!
		}
		
		
	});
   */
</@script>



