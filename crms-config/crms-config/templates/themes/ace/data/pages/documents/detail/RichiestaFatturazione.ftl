<#assign type=model['docDefinition']/>
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["jquery-ui-full", "datepicker","pages/studio.css","x-editable"],
	"scripts" : ["jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable"],
	"inline_scripts":[],
	"title" : "Dettaglio milestone",
 	"description" : "Dettaglio milestone" 
} />
<#assign elStudio=el.getParent().getParent().getParent() />
<#include "../../partials/navigation/navigazione_studio.ftl">
<#include "../../partials/form-elements/elementSpecific.ftl">
<#global page=page + {"scripts": page.scripts + ["select2"], "styles": page.styles + ["select2"]} />
<@script>
$('select').select2({containerCssClass:'select2-ace',allowClear: true});
</@script>
<@breadcrumbsData el />

<@script>

var sidebarDefault="${el.getParent().getParent().getId()}#Fatturazione-tab2";

var oldExecuteConfirmTask=window.executeConfirmTask;
var oldExecuteFormTask=window.executeFormTask;

var executeConfirmTask= function(taskId){	
	if(checkAll()){
	var queue=$.when({start:true});
	queue=$.when(queue).then(function(){ return saveAll();});
	$.when(queue).then(function(data){
		toggleLoadingScreen();
		return oldExecuteConfirmTask(taskId);	
	});
}
}

function executeFormTask(taskId){	
	if(checkAll()){
	var queue=$.when({start:true});
	queue=$.when(queue).then(function(){ return saveAll();});
	$.when(queue).then(function(data){
		toggleLoadingScreen();
		return oldExecuteFormTask(taskId);	
	});
}
}
	



	

 	console.log("Sono in RichiestaFatturazione.js.ftl: - ready");
 		var $table=$('tbody [data-order]').parent();
 		var $sorted=$table.find('tr').sort(function (a, b) {
	
	      var contentA =parseInt( $(a).attr('data-order'));
	      var contentB =parseInt( $(b).attr('data-order'));
	      return (contentA < contentB) ? -1 : (contentA > contentB) ? 1 : 0;
	   })
	   
	   $table.append($sorted);
 		
 		$("td[id^='totale']").each(function(){
			var tdid=$(this).attr("id");
			var prezzoPrestazioni=$("#"+tdid).html();
			if(prezzoPrestazioni) {prezzoPrestazioni=prezzoPrestazioni.formatMoney();}
			$("#"+tdid).html(prezzoPrestazioni);
		});
 		
 		$('#giulio select').find('option:not([value])').remove();
 		
 	


	
	
function update(id,metadata){
		return $.ajax({
  	method : 'POST',
  	async : false,
  	url : '../../rest/documents/update/' + id,
  	data : metadata
 		});
	}

function saveAll(){
	loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");
	var queue=$.when({start:true});
	$('form[name=fattura]').each(function(){
		var id=this.id;	
		
		//var tendinaVal = $(this).find("select option:selected").val();
		//if(tendinaVal) {console.log("OK")} else{console.log("NO");};
		
		var metadata={"DatiVoceFattura_SelectFattura":$(this).find("select option:selected").val()}
		queue=$.when(queue).then(function(){ return update(id,metadata)});
	});
	
	$('form[name=prezzoPT]').each(function(){
		var id=this.id;
		var metadata={"DatiPassThroughPrezzo_Prezzo":$(this).find("input").val()}
		queue=$.when(queue).then(function(){ return update(id,metadata)});
	});
	
	$('form[name=fattura2]').each(function(){
		var id=this.id;	
		var metadata={"DatiFatturaScheduling_SelectFattura":$(this).find("select option:selected").val()}
		queue=$.when(queue).then(function(){ return update(id,metadata)});
	});
	
	return queue;
}
function checkAll(){
	var check=true;

	$('#acconto').find('form[name=fattura2]').each(function(){
		var id=this.id;
		
		
		var data=$(this).find("select option:selected").val();
		if(!data || data==""){
			bootbox.alert("Selezionare l'indice di raggruppamento per l'acconto");
			check=false;
			return false;
		}
	});
	if(!check) return false;
	$('#monitoraggio').find('form[name=fattura]').each(function(){
		var id=this.id;
		
		
		var data=$(this).find("select option:selected").val();
		if(!data || data==""){
			bootbox.alert("Selezionare l'indice di raggruppamento per le prestazioni da protocollo");
			check=false;
			return false;
		}
	});
	if(!check) return false;
	$('#richiesta').find('form[name=fattura]').each(function(){
		var id=this.id;
		
		
		var data=$(this).find("select option:selected").val();
		if(!data || data==""){
			bootbox.alert("Selezionare l'indice di raggruppamento per le prestazioni a richiesta");
			check=false;
			return false;
		}
	});
	if(!check) return false;
	
	
	return true;
}
	
</@script>
