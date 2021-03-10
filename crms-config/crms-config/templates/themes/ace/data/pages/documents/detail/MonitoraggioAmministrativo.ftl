<#assign type=model['docDefinition']/>
<#global availableTypes={} />
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["jquery-ui-full", "datepicker","pages/studio.css","x-editable","handsontable"],
	"scripts" : ["budget/axmrTools.js","budget/budgetTools.js","jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable","handsontable","base"],
	"inline_scripts":[],
	"title" : "Dettaglio paziente",
 	"description" : "Dettaglio paziente"
} />
<#assign elCentro=el.getParent() />
<#assign elStudio=elCentro.getParent() />
<#assign json=el.type.getDummyJson() />
<#assign loadedJson=el.getElementCoreJsonToString(userDetails) />
<@script>
	var sidebarDefault='${elCentro.getId()}#MonitoraggioAmministrativo-tab2';
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
 	var groupItems=new Array();
 	var empties=new Array();
<#-- SIRER-72 INIZIO -->
<#if  userDetails.hasRole("CTC")>
	var userIsCTC=true;
<#else>
	var userIsCTC=false;
</#if>
	$(document).ready(function(){
		if(!userIsCTC){
			$("#informations-DatiMonitoraggioAmministrativo_validatoIRINN").hide();
		}
	});
<#-- SIRER-72 FINE -->
 	empties[dummy.type.id]=dummy;
    <#if (model['element'].getFieldDataCode("StatoPaziente","Stato")?string=="" || model['element'].getFieldDataCode("StatoPaziente","Stato")?string=="1") >
		<#assign editMonitoraggio=true />
	<#else>
		<#assign editMonitoraggio=false />
	</#if>
    var edit=<#if editMonitoraggio>true<#else>false</#if>;
    <#list elType.getAllowedChilds() as myType>
		<#assign json=myType.getDummyJson() />
		empties['${myType.id}']=empties['${myType.typeId}']=${json};
		<#list myType.getAllowedChilds() as childType>
			<#assign json=childType.getDummyJson() />
			empties['${childType.id}']=empties['${childType.typeId}']=${json};
		</#list>
	</#list>
</@script>

<#include "../../partials/navigation/navigazione_studio.ftl">
<#include "../../partials/form-elements/elementSpecific.ftl">
<#--include "../../partials/form-elements/select.ftl" /-->
<#global page=page + {"scripts": page.scripts + ["select2"], "styles": page.styles + ["select2"]} />
<@script>
$('select').not('#DatiCustomMonitoraggioAmministrativo_Braccio-select').select2({containerCssClass:'select2-ace',allowClear: true});
</@script>
<@breadcrumbsData el />
<@style>
		.ui-autocomplete.ui-menu{
			z-index:9999!important;
		}
		input[type=checkbox]{
			width:auto;
		}
		#Prestazioni_Altro{
			font-size: 14px;
		}
			.handsontable td{
				font-size: 13px;
				font-weight:200;
			}
			#tabs ul{
				height: 41px!important;
			}
			#tabs li a{
				font-size: 125%;

			    padding: 0.8em 5em;
			}
		/*input[type=text], select,option {
		    font-size: 1.2vw!important;
		    line-height: 1.3vw;

		}
		#tp-dialog-form input[type=text], select,option {
		    font-size: 1vw!important;
		    line-height: 1.1vw;

		}*/
		.largeTd{
			width:110px;
		}
		.top{
			vertical-align:top;
		}
		.gridLabel{
			background-color:#77EF56;
			color:#FFF;
			width:66px;
			font-weight:bold;
			border-radius:25px;
			padding:0px 10px;
			vertical-align:bottom;
		}
		.gridLabel2{
			background-color:#94CCE8;
			color:#FFF;
			width:66px;
			font-weight:bold;
			border-radius:25px;
			padding:0px 10px;
			vertical-align:bottom;

		}
		.gridLabel3{
			background-color:#CCC;
			color:#FFF;
			width:66px;
			font-weight:bold;
			border-radius:25px;
			padding:0px 10px;
			vertical-align:bottom;
		}
		input[type=checkbox]{
			display:inline-block;
		}
		/*label{
			font-size:1.3vw;
			line-height:1.6vw;
		}
		#tp-dialog-form label{
			font-size:1.1vw;
			line-height:1.4vw;
		}
		.ui-dialog button, button.ui-button {
			font-size:1.3vw!important;
			}
		#tp-dialog-form .ui-dialog button, button.ui-button {
			font-size:1.1vw!important;
			}*/
		#monitoraggio th {
			text-align:left;
		}
	    .handsontable tr td{
			vertical-align:bottom;
			padding-bottom:10px;
		}
		/*fix modal form nuova grafica*/
		.ui-dialog-content label{
			display:block;
		}
		.ui-dialog-content #ricoveriList label{
			display:inline-block;
			margin-right:10px;
		}
		.ui-dialog-content input[type=checkbox]{
			vertical-align: middle;
		}
		.dragdealer.horizontal,.dragdealer.horizontal .handle{
			height:17px;
		}
		.dragdealer.vertical,.dragdealer.vertical .handle{
			width:17px;
		}
		.handle{
			cursor:grab;
		}
	</@style>

<@script>
	function updateIds(map){
		var currElement;
		if(map &&  ($.isArray(map) || $.isPlainObject(map))){
			$.each(map, function(guid,id){
				currElement=$.axmr.guid(guid);
				if(currElement &&  ($.isPlainObject(currElement) || $.isArray(currElement))){
					currElement.id=id;
				}
			});
		}
		window.onbeforeunload = function() {

			return;
		}
	}

	var oldSaveUpdateField=saveUpdateField;
	saveUpdateField=function(idField){
		oldSaveUpdateField(idField);
		braccioFilter=$('#DatiCustomMonitoraggioAmministrativo_Braccio_value').text();
		$('#monitoraggio').handsontable('render');
	}
	var braccioFilter;

    <#if (model['element'].getFieldDataCode("StatoPaziente","Stato")?string=="" || model['element'].getFieldDataCode("StatoPaziente","Stato")?string=="1") >
		<#assign editMonitoraggio=true />
	<#else>
		<#assign editMonitoraggio=false />
	</#if>
    var edit=<#if editMonitoraggio>true<#else>false</#if>;

    var docObj;

    var fatturabili={};
    var lastCompleta=0;
    var firstCompleta=0 ;
    function saveAll(){
		loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");
		var queue=$.when({start:true});
		var folders={};
		queue=$.when(queue).then(function(data){
			updateIds(data.resultMap);
			return saveElement(loadedElement);
		});
		$('[name=DatiMonPxP_Fatturabile]').each(function(){
			var that=this;
			queue=$.when(queue).then(function(){return savePrestazione(that);});
		});
		$('[name=DatiMonPxP_numeroPazienti]').each(function(){
			var that=this;
			queue=$.when(queue).then(function(){return savePrestazionePazienti(that);});
		});
		$('[name=DatiMonPazientiFatturabili_numeroPazienti]').each(function(){
			var that=this;
			queue=$.when(queue).then(function(){return saveNumeroPazientiFatturabili(that);});
		});
		$('[name=DatiMonPazientiFatturabili_Prezzo]').each(function(){
			var that=this;
			queue=$.when(queue).then(function(){return savePrezzoPazientiFatturabili(that);});
		});
		$.when(queue).then(function(){loadingScreen("Salvataggio effettuato!", "${baseUrl}/int/images/green_check.jpg", 1500);clearSingleNotification('budgetChange');if((!loadedBraccio && $('#DatiCustomMonitoraggioAmministrativo_Braccio-select').val()) || loadedBraccio!=$('#DatiCustomMonitoraggioAmministrativo_Braccio-select').val()){loadingScreen("Caricamento in corso...", "loading");location.reload(true);}});
	    return;

	}

	function savePrestazione(object){
		var element={id:'',metadata:{}};
		element.id=object.id;
		element.metadata['DatiMonPxP_Fatturabile']=object.value;
		return updateElement(element);
	}

	function savePrestazionePazienti(object){
		var element={id:'',metadata:{}};
		element.id=object.id;
		element.metadata['DatiMonPxP_numeroPazienti']=object.value;
		return updateElement(element);
	}

	function saveNumeroPazientiFatturabili(object){
		var element={id:'',metadata:{}};
		element.id=object.id;
		element.metadata['DatiMonPazientiFatturabili_numeroPazienti']=object.value;
		return updateElement(element);
	}
	function savePrezzoPazientiFatturabili(object){
		var element={id:'',metadata:{}};
		element.id=object.id;
		element.metadata['DatiMonPazientiFatturabili_Prezzo']=object.value;
		return updateElement(element);
	}












</@script>