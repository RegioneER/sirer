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

$('#document-form-submit').ready(function() {

	if($('#Progetto_aziendeMultiple:checked').val()!==undefined && $('#Progetto_aziendeMultiple:checked').val().split("###")[0]==1){ 
			$('#informations-Progetto_struttureMultiple').show();
		}
		else {
			$('#informations-Progetto_struttureMultiple').hide();
			$('[id=Progetto_struttureMultiple').prop('checked', false);//se nascondo sbianco il valore!
		}
		
	
	if($('#Progetto_StudiCorrelati:checked').val()!==undefined && $('#Progetto_StudiCorrelati:checked').val().split("###")[0]==1){ 
			$('#informations-Progetto_Studi').show();
		}
		else {
			$('#informations-Progetto_Studi').hide();
			$('[name=Progetto_Studi]').val('');//se nascondo sbianco il valore!
			$('[name=Progetto_Studi-select]').trigger('change');//se nascondo sbianco il valore!
		}
	
	});
	
	$("[name=Progetto_aziendeMultiple]").on('change',function(){
		
		if($('#Progetto_aziendeMultiple:checked').val()!==undefined && $('#Progetto_aziendeMultiple:checked').val().split("###")[0]==1){ 
			$('#informations-Progetto_struttureMultiple').show();
		}
		else {
			$('#informations-Progetto_struttureMultiple').hide();
			$('[id=Progetto_struttureMultiple').prop('checked', false);//se nascondo sbianco il valore!
		}
		
	});
   
   

	
	$("[name=Progetto_StudiCorrelati]").on('change',function(){
		
		if($('#Progetto_StudiCorrelati:checked').val()!==undefined && $('#Progetto_StudiCorrelati:checked').val().split("###")[0]==1){ 
			$('#informations-Progetto_Studi').show();
		}
		else {
			$('#informations-Progetto_Studi').hide();
			$('[name=Progetto_Studi]').val('');//se nascondo sbianco il valore!
			$('[name=Progetto_Studi-select]').trigger('change');//se nascondo sbianco il valore!
		}
		
	});
   
</@script>



