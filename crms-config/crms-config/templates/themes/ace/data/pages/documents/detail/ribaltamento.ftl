<#assign type=model['docDefinition']/>
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["jquery-ui-full", "datepicker","pages/studio.css","x-editable"],
	"scripts" : ["jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable"],
	"inline_scripts":[],
	"title" : "Dettaglio riversamento",
 	"description" : "Dettaglio riversamento" 
} />
<#assign elStudio=el.getParent().getParent().getParent().getParent().getParent() />
<#include "../../partials/navigation/navigazione_studio.ftl">
<#include "../../partials/form-elements/elementSpecific.ftl">
<#include "../../partials/form-elements/select.ftl" />
<@breadcrumbsData el />

<#if el.getUserPolicy(userDetails).isCanUpdate() ><#assign editable=true /><#else><#assign editable=false /></#if>

<@script>
	var sidebarDefault="${el.getParent().getParent().getParent().getParent().getId()}#Fatturazione-tab2";
	var html=$('#DatiRibaltamento_TotaleFattura').html();
	//if(!html.match('€') && !html.match('euro')){
	$('#DatiRibaltamento_TotaleFattura').html(html.formatMoney());
	//}
	html=$('#DatiRibaltamento_TotaleIncassato').html();
	//if(!html.match('€') && !html.match('euro')){
	$('#DatiRibaltamento_TotaleIncassato').html(html.formatMoney());
	//}
	var oldExecuteConfirmTask=window.executeConfirmTask;
	var oldExecuteFormTask=window.executeFormTask;

	var executeConfirmTask= function(taskId){
	var queue=$.when({start:true});
	queue=$.when(queue).then(function(){ return saveAll();});
	$.when(queue).then(function(data){
	setTimeout(function(){
	toggleLoadingScreen();
	return oldExecuteConfirmTask(taskId);
	},1500);
	});
	}

	var executeFormTask= function (taskId){
	var queue=$.when({start:true});
	queue=$.when(queue).then(function(){ return saveAll();});
	$.when(queue).then(function(data){
	setTimeout(function(){
	toggleLoadingScreen();
	return oldExecuteFormTask(taskId);
	},1500);
	});
	}

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
	$('form[name=CDCForm]').find('input[name=CDCSummary_Ribaltamento]').each(function(){
	var id=this.id;
	var metadata={"CDCSummary_Ribaltamento":$(this).val()}
	queue=$.when(queue).then(function(){ return update(id,metadata)});
	});
	var metadata={};
	$('#dataTable input').each(function(){
	metadata[$(this).attr('name')]=$(this).val();
	});
	$('#dataTable textarea').each(function(){
	metadata[$(this).attr('name')]=$(this).val();
	});

	queue=$.when(queue).then(function(){ return update('${el.id}',metadata);});

	return queue;
	}
</@script>
<#if editable>
<@script>
var old_value;
$('input[type=text]').focus(function(){
	 old_value=$(this).val();
	}).change(function(){
	var value=$(this).val();
	if($(this).name()!='RibaltamentoFondi_noteCTO'){
		if(value.match(/,/)){
			value=value.replace(/,/,'.');
			$(this).val(value);
		}
	}
	if(isNaN(value)){
		bootbox.alert("Attenzione inserire un valore numerico per i valori da riversare");
		$(this).val(old_value);
		return false;
	}
});
function calcolaRiversamentoDaPercentuali (suffix){
	var totaliCDC;
	totaliCDC=0;


	$('.cdc').each(function(){
		if(!isNaN($(this).val()) && $.trim($(this).val())!=""){
			totaliCDC+=	parseFloat($(this).val());
		}
	});
	$('[name=ribaltamentoTotale]').html((totaliCDC).toLocaleString('it-IT', { style: 'currency', currency: 'EUR' }));

	var totalePercentuale=0;
	var totaleRiversato=0;
	//PRENDO PERCENTUALI
	if($('[name=RibaltamentoFondi_valorePerc6'+suffix+']').val()==""){
		$('[name=RibaltamentoFondi_valorePerc6'+suffix+']').val("0");
	}
	var valorePerc6=$('[name=RibaltamentoFondi_valorePerc6'+suffix+']').val();
	totalePercentuale=totalePercentuale+parseFloat(valorePerc6);

	if($('[name=RibaltamentoFondi_compensiDirigente'+suffix+']').val()==""){
		$('[name=RibaltamentoFondi_compensiDirigente'+suffix+']').val("0");
	}
	var compensiDirigente=$('[name=RibaltamentoFondi_compensiDirigente'+suffix+']').val();
	totalePercentuale=totalePercentuale+parseFloat(compensiDirigente);

	if($('[name=RibaltamentoFondi_compensiReparto'+suffix+']').val()==""){
		$('[name=RibaltamentoFondi_compensiReparto'+suffix+']').val("0");
	}
	var compensiReparto=$('[name=RibaltamentoFondi_compensiReparto'+suffix+']').val();
	totalePercentuale=totalePercentuale+parseFloat(compensiReparto);

	if($('[name=RibaltamentoFondi_valorePerc1'+suffix+']').val()==""){
		$('[name=RibaltamentoFondi_valorePerc1'+suffix+']').val("0");
	}
	var valorePerc1=$('[name=RibaltamentoFondi_valorePerc1'+suffix+']').val();
	totalePercentuale=totalePercentuale+parseFloat(valorePerc1);

	if($('[name=RibaltamentoFondi_valorePerc2'+suffix+']').val()==""){
		$('[name=RibaltamentoFondi_valorePerc2'+suffix+']').val("0");
	}
	var valorePerc2=$('[name=RibaltamentoFondi_valorePerc2'+suffix+']').val();
	totalePercentuale=totalePercentuale+parseFloat(valorePerc2);

	if($('[name=RibaltamentoFondi_valorePerc3'+suffix+']').val()==""){
	$('[name=RibaltamentoFondi_valorePerc3'+suffix+']').val("0");
	}
	var valorePerc3=$('[name=RibaltamentoFondi_valorePerc3'+suffix+']').val();
	totalePercentuale=totalePercentuale+parseFloat(valorePerc3);

	if($('[name=RibaltamentoFondi_valorePerc4'+suffix+']').val()==""){
	$('[name=RibaltamentoFondi_valorePerc4'+suffix+']').val("0");
	}
	var valorePerc4=$('[name=RibaltamentoFondi_valorePerc4'+suffix+']').val();
	totalePercentuale=totalePercentuale+parseFloat(valorePerc4);

	if($('[name=RibaltamentoFondi_valorePerc7'+suffix+']').val()==""){
	$('[name=RibaltamentoFondi_valorePerc7'+suffix+']').val("0");
	}
	var valorePerc7=$('[name=RibaltamentoFondi_valorePerc7'+suffix+']').val();
	totalePercentuale=totalePercentuale+parseFloat(valorePerc7);

	if($('[name=RibaltamentoFondi_valorePercFarmacologia'+suffix+']').val()==""){
	$('[name=RibaltamentoFondi_valorePercFarmacologia'+suffix+']').val("0");
	}
	var valorePercFarmacologia=$('[name=RibaltamentoFondi_valorePercFarmacologia'+suffix+']').val();
	totalePercentuale=totalePercentuale+parseFloat(valorePercFarmacologia);

	if($('[name=RibaltamentoFondi_valorePercUniversitario'+suffix+']').val()==""){
	$('[name=RibaltamentoFondi_valorePercUniversitario'+suffix+']').val("0");
	}
	var valorePercUniversitario=$('[name=RibaltamentoFondi_valorePercUniversitario'+suffix+']').val();
	totalePercentuale=totalePercentuale+parseFloat(valorePercUniversitario);

	if($('[name=RibaltamentoFondi_valorePerc5'+suffix+']').val()==""){
	$('[name=RibaltamentoFondi_valorePerc5'+suffix+']').val("0");
	}
	var valorePerc5=$('[name=RibaltamentoFondi_valorePerc5'+suffix+']').val();
	totalePercentuale=totalePercentuale+parseFloat(valorePerc5);

	$('[name=totalePercentuale'+suffix+']').removeClass("red");
	$('[name=totalePercentuale'+suffix+']').html(totalePercentuale);
	if(totalePercentuale!=100){
		$('[name=totalePercentuale'+suffix+']').addClass("red");
		alert("ATTENZIONE! Il valore totale percentuale da riversare deve essere uguale al 100%\n(l'ammontare percentuale attualmente inserito è del "+totalePercentuale+"%)");
	}
	//CALCOLO RIVERSAMENTI
	var valorePerc6Riversato=(totaliCDC/100*valorePerc6).toFixed(2);
	totaleRiversato=parseFloat((totaleRiversato).toFixed(2))+parseFloat(valorePerc6Riversato);
	var compensiDirigenteRiversato=(totaliCDC/100*compensiDirigente).toFixed(2);
	totaleRiversato=parseFloat((totaleRiversato).toFixed(2))+parseFloat(compensiDirigenteRiversato);
	var compensiRepartoRiversato=(totaliCDC/100*compensiReparto).toFixed(2);
	totaleRiversato=parseFloat((totaleRiversato).toFixed(2))+parseFloat(compensiRepartoRiversato);
	var valorePerc1Riversato=(totaliCDC/100*valorePerc1).toFixed(2);
	totaleRiversato=parseFloat((totaleRiversato).toFixed(2))+parseFloat(valorePerc1Riversato);
	var valorePerc2Riversato=(totaliCDC/100*valorePerc2).toFixed(2);
	totaleRiversato=parseFloat((totaleRiversato).toFixed(2))+parseFloat(valorePerc2Riversato);
	var valorePerc3Riversato=(totaliCDC/100*valorePerc3).toFixed(2);
	totaleRiversato=parseFloat((totaleRiversato).toFixed(2))+parseFloat(valorePerc3Riversato);
	var valorePerc4Riversato=(totaliCDC/100*valorePerc4).toFixed(2);
	totaleRiversato=parseFloat((totaleRiversato).toFixed(2))+parseFloat(valorePerc4Riversato);
	var valorePerc7Riversato=(totaliCDC/100*valorePerc7).toFixed(2);
	totaleRiversato=parseFloat((totaleRiversato).toFixed(2))+parseFloat(valorePerc7Riversato);
	var valorePercFarmacologiaRiversato=(totaliCDC/100*valorePercFarmacologia).toFixed(2);
	totaleRiversato=parseFloat((totaleRiversato).toFixed(2))+parseFloat(valorePercFarmacologiaRiversato);
	var valorePercUniversitarioRiversato=(totaliCDC/100*valorePercUniversitario).toFixed(2);
	totaleRiversato=parseFloat((totaleRiversato).toFixed(2))+parseFloat(valorePercUniversitarioRiversato);
	var valorePerc5Riversato=(totaliCDC/100*valorePerc5).toFixed(2);
	totaleRiversato=parseFloat((totaleRiversato).toFixed(2))+parseFloat(valorePerc5Riversato);
	$('[name=totaleRiversato'+suffix+']').html((totaleRiversato).toLocaleString('it-IT', { style: 'currency', currency: 'EUR' }));
	//totaleRiversato=totaleRiversato.toFixed(2);
	if((totaleRiversato).toFixed(2)!=(totaliCDC).toFixed(2)){
		$('[name=totaleRiversato'+suffix+']').addClass("red");
		alert("ATTENZIONE! Il valore totale da riversare deve essere uguale a "+totaliCDC );
	}
	//COMPILO RIVERSAMENTI
	$('[name=RibaltamentoFondi_valorePerc6Riversato'+suffix+']').val(valorePerc6Riversato);
	$('[name=RibaltamentoFondi_compensiDirigenteRiversato'+suffix+']').val(compensiDirigenteRiversato);
	$('[name=RibaltamentoFondi_compensiRepartoRiversato'+suffix+']').val(compensiRepartoRiversato);
	$('[name=RibaltamentoFondi_compensiRepartoRiversato'+suffix+']').val(compensiRepartoRiversato);
	$('[name=RibaltamentoFondi_valorePerc1Riversato'+suffix+']').val(valorePerc1Riversato);
	$('[name=RibaltamentoFondi_valorePerc2Riversato'+suffix+']').val(valorePerc2Riversato);
	$('[name=RibaltamentoFondi_valorePerc3Riversato'+suffix+']').val(valorePerc3Riversato);
	$('[name=RibaltamentoFondi_valorePerc4Riversato'+suffix+']').val(valorePerc4Riversato);
	$('[name=RibaltamentoFondi_valorePerc7Riversato'+suffix+']').val(valorePerc7Riversato);
	$('[name=RibaltamentoFondi_valorePercFarmacologiaRiversato'+suffix+']').val(valorePercFarmacologiaRiversato);
	$('[name=RibaltamentoFondi_valorePercUniversitarioRiversato'+suffix+']').val(valorePercUniversitarioRiversato);
	$('[name=RibaltamentoFondi_valorePerc5Riversato'+suffix+']').val(valorePerc5Riversato);
}

function calcolaRiversamentoDaValori(suffix){
	var totaliCDC;
	totaliCDC=0;


	$('.cdc').each(function(){
		if(!isNaN($(this).val()) && $.trim($(this).val())!=""){
			totaliCDC+= parseFloat($(this).val());
		}
	});
	$('[name=ribaltamentoTotale]').html((totaliCDC).toLocaleString('it-IT', { style: 'currency', currency: 'EUR' }));
	var totalePercentuale=0;
	var totaleRiversato=0;
	//PRENDO VALORI RIVERSAMENTO
	var valorePerc6Riversato=$('[name=RibaltamentoFondi_valorePerc6Riversato'+suffix+']').val();
	totaleRiversato=totaleRiversato+parseFloat(valorePerc6Riversato);
	var compensiDirigenteRiversato=$('[name=RibaltamentoFondi_compensiDirigenteRiversato'+suffix+']').val();
	totaleRiversato=totaleRiversato+parseFloat(compensiDirigenteRiversato);
	var compensiRepartoRiversato=$('[name=RibaltamentoFondi_compensiRepartoRiversato'+suffix+']').val();
	totaleRiversato=totaleRiversato+parseFloat(compensiRepartoRiversato);
	var valorePerc1Riversato=$('[name=RibaltamentoFondi_valorePerc1Riversato'+suffix+']').val();
	totaleRiversato=totaleRiversato+parseFloat(valorePerc1Riversato);
	var valorePerc2Riversato=$('[name=RibaltamentoFondi_valorePerc2Riversato'+suffix+']').val();
	totaleRiversato=totaleRiversato+parseFloat(valorePerc2Riversato);
	var valorePerc3Riversato=$('[name=RibaltamentoFondi_valorePerc3Riversato'+suffix+']').val();
	totaleRiversato=totaleRiversato+parseFloat(valorePerc3Riversato);
	var valorePerc4Riversato=$('[name=RibaltamentoFondi_valorePerc4Riversato'+suffix+']').val();
	totaleRiversato=totaleRiversato+parseFloat(valorePerc4Riversato);
	var valorePerc7Riversato=$('[name=RibaltamentoFondi_valorePerc7Riversato'+suffix+']').val();
	totaleRiversato=totaleRiversato+parseFloat(valorePerc7Riversato);
	var valorePercFarmacologiaRiversato=$('[name=RibaltamentoFondi_valorePercFarmacologiaRiversato'+suffix+']').val();
	totaleRiversato=totaleRiversato+parseFloat(valorePercFarmacologiaRiversato);
	var valorePercUniversitarioRiversato=$('[name=RibaltamentoFondi_valorePercUniversitarioRiversato'+suffix+']').val();
	totaleRiversato=totaleRiversato+parseFloat(valorePercUniversitarioRiversato);
	var valorePerc5Riversato=$('[name=RibaltamentoFondi_valorePerc5Riversato'+suffix+']').val();
	totaleRiversato=totaleRiversato+parseFloat(valorePerc5Riversato);
	$('[name=totaleRiversato'+suffix+']').removeClass("red");
	$('[name=totaleRiversato'+suffix+']').html((totaleRiversato).toLocaleString('it-IT', { style: 'currency', currency: 'EUR' }));
	if((totaleRiversato).toFixed(2)!=(totaliCDC).toFixed(2)){
	$('[name=totaleRiversato'+suffix+']').addClass("red");
	alert("ATTENZIONE! Il valore totale da riversare deve essere uguale a "+totaliCDC );
	}

	//CALCOLO PERCENTUALI
	var valorePerc6=(valorePerc6Riversato/totaliCDC*100).toFixed(2);
	totalePercentuale=totalePercentuale+parseFloat(valorePerc6);
	var compensiDirigente=(compensiDirigenteRiversato/totaliCDC*100).toFixed(2);
	totalePercentuale=totalePercentuale+parseFloat(compensiDirigente);
	var compensiReparto=(compensiRepartoRiversato/totaliCDC*100).toFixed(2);
	totalePercentuale=totalePercentuale+parseFloat(compensiReparto);
	var valorePerc1=(valorePerc1Riversato/totaliCDC*100).toFixed(2);
	totalePercentuale=totalePercentuale+parseFloat(valorePerc1);
	var valorePerc2=(valorePerc2Riversato/totaliCDC*100).toFixed(2);
	totalePercentuale=totalePercentuale+parseFloat(valorePerc2);
	var valorePerc3=(valorePerc3Riversato/totaliCDC*100).toFixed(2);
	totalePercentuale=totalePercentuale+parseFloat(valorePerc3);
	var valorePerc4=(valorePerc4Riversato/totaliCDC*100).toFixed(2);
	totalePercentuale=totalePercentuale+parseFloat(valorePerc4);
	var valorePerc7=(valorePerc7Riversato/totaliCDC*100).toFixed(2);
	totalePercentuale=totalePercentuale+parseFloat(valorePerc7);
	var valorePercFarmacologia=(valorePercFarmacologiaRiversato/totaliCDC*100).toFixed(2);
	totalePercentuale=totalePercentuale+parseFloat(valorePercFarmacologia);
	var valorePercUniversitario=(valorePercUniversitarioRiversato/totaliCDC*100).toFixed(2);
	totalePercentuale=totalePercentuale+parseFloat(valorePercUniversitario);
	var valorePerc5=(valorePerc5Riversato/totaliCDC*100).toFixed(2);
	totalePercentuale=totalePercentuale+parseFloat(valorePerc5);
	$('[name=totalePercentuale'+suffix+']').html((totalePercentuale));
	if(totalePercentuale!=100){
	$('[name=totalePercentuale'+suffix+']').addClass("red");
		alert("ATTENZIONE! Il valore totale percentuale da riversare deve essere uguale al 100%\n(l'ammontare percentuale attualmente inserito è del "+totalePercentuale+"%)");
	}
	//COMPILO RIVERSAMENTI
	$('[name=RibaltamentoFondi_valorePerc6'+suffix+']').val(valorePerc6);
	$('[name=RibaltamentoFondi_compensiDirigente'+suffix+']').val(compensiDirigente);
	$('[name=RibaltamentoFondi_compensiReparto'+suffix+']').val(compensiReparto);
	$('[name=RibaltamentoFondi_compensiReparto'+suffix+']').val(compensiReparto);
	$('[name=RibaltamentoFondi_valorePerc1'+suffix+']').val(valorePerc1);
	$('[name=RibaltamentoFondi_valorePerc2'+suffix+']').val(valorePerc2);
	$('[name=RibaltamentoFondi_valorePerc3'+suffix+']').val(valorePerc3);
	$('[name=RibaltamentoFondi_valorePerc4'+suffix+']').val(valorePerc4);
	$('[name=RibaltamentoFondi_valorePerc7'+suffix+']').val(valorePerc7);
	$('[name=RibaltamentoFondi_valorePercFarmacologia'+suffix+']').val(valorePercFarmacologia);
	$('[name=RibaltamentoFondi_valorePercUniversitario'+suffix+']').val(valorePercUniversitario);
	$('[name=RibaltamentoFondi_valorePerc5'+suffix+']').val(valorePerc5);
}
$(document).ready(function(){
	<#if getUserGroups(userDetails)?starts_with('CTO_')>
		calcolaRiversamentoDaPercentuali("");
	</#if>
	<#if getUserGroups(userDetails)?starts_with('UR_')>
		calcolaRiversamentoDaPercentuali("");
		calcolaRiversamentoDaPercentuali("UR");
	</#if>
});

</@script>
</#if>
