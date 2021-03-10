<style>

	.xCDM-modalForm .col-sm-3,
	.xCDM-modalForm .col-sm-9{
		float:left;
	}

	.xCDM-modalForm .form-group > div{
		text-align:left;
	}

	.xCDM-modalForm .radio, .xCDM-modalForm .checkbox {
		padding-left: 0px;
	}

	.xCDM-modalForm input[type='text'], .xCDM-modalForm textarea{
		width: 90%;
		max-width: 90%;
	}

	.bootbox-body .xCDM-modalForm {
		font-size: 14px;
	}

	.select2-drop{
		z-index: 100000 !important;
	}

	.ui-autocomplete.ui-menu {
		z-index: 1000000 !important;
	}

	span div.radio.left{float:left;margin-right:20px;}

	.form-group{padding:5px 0px;}
</style>

<@script>

var messages=null;
$.getJSON(baseUrl+'/app/rest/documents/messages', function(data){
messages=data.resultMap;
});

var initFormAction=function(object){
	var form=object.getForm();
	$(".radio").addClass("left");
	$("div[data-field-ref=depotFarmaco_DepotChiuso]").hide();
	$("div[data-field-ref=depotFarmaco_tipo]").hide();
	$("div[data-field-ref=depotFarmaco_linkFarmaco]").show();
	$("div[data-field-ref=depotFarmaco_modalitaFornitura]").show();
	if($("input[name=depotFarmaco_tipo]").val()=="1"){
		$("div[data-field-ref=depotFarmaco_GaraFornituraDisp]").hide();
		$("div[data-field-ref=depotFarmaco_prezzoInCommercio]").hide();
	}
	else if($("input[name=depotFarmaco_tipo]").val()=="2"){
		$("div[data-field-ref=depotFarmaco_GaraFornituraDisp]").show();
$("div[data-field-ref=depotFarmaco_prezzoInCommercio]").show();
	}
	$("div[data-field-ref='depotFarmaco_modalitaRicezione']").remove();
	$("div[data-field-ref='depotFarmaco_formaFarm']").remove();
	$("div[data-field-ref='depotFarmaco_dosaggio']").remove();
	$("div[data-field-ref='depotFarmaco_tempTailPresente']").remove();
	$("div[data-field-ref='depotFarmaco_temperaturaConservazione']").remove();
	$("div[data-field-ref='depotFarmaco_temperaturaConservazioneAltro']").remove();
	$("div[data-field-ref='depotFarmaco_autorizzazioneSmaltimento']").remove();
	$("div[data-field-ref='depotFarmaco_modalitaPreparazione']").remove();
}

var compilationChecks=function(object){
var form=object.getForm();
return true;
}

var farmacoModalEngine=new xCDM_Modal(baseUrl, 'DepotFarmaco', initFormAction, compilationChecks, farmacoSaveCallBack);

function farmacoSaveCallBack(object){
loadFarmaci('${el.id}', $('#DepotFarmacoTable'));
}

function loadFarmaci(centroId, table){
	var url=baseUrl+'/app/rest/documents/'+centroId+'/getChildren/DepotFarmaco/maxdepth/1';
	table.find('tbody').html("<tr><td colspan='4'>caricamento farmaci ...</td></tr>");
	$.getJSON(url, function(data){
		table.find('tbody').html("");
		if (data.length==0) table.find('tbody').html("<tr><td colspan='4'>nessun farmaco presente</td></tr>");
		for (var i=0;i<data.length;i++){
			var farmaco=data[i];
			var tr=$('<tr>');
			var td1=$('<td>');
			td1.html(farmaco.titleString);
			tr.append(td1);
			var td2=$('<td>');
			if(farmaco.metadata['depotFarmaco_modalitaFornitura']!==undefined && farmaco.metadata['depotFarmaco_modalitaFornitura'][0]!==undefined && farmaco.metadata['depotFarmaco_modalitaFornitura'][0].split("###")[1]){
				td2.html(farmaco.metadata['depotFarmaco_modalitaFornitura'][0].split("###")[1]);
			}
			tr.append(td2);
			var td3=$('<td>');
		<#if getUserGroups(userDetails)!='SP'>

			var editLink=$('<a>');
			editLink.attr('href','#');
			editLink.attr('title','modifica');
			editLink.html('<i class="fa fa-pencil fa-2x"></i>&nbsp;');
			(function(farmaco, editLink){
			editLink.click(function(){
			farmacoModalEngine.formByElement(farmaco);
			});
			})(farmaco, editLink);
			td3.append(editLink);

		</#if>
			tr.append(td3);
			table.find('tbody').append(tr);
		}
	});
}
loadFarmaci('${el.id}', $('#DepotFarmacoTable'));

					</@script>


					<#if userDetails.hasRole("CTC") || userDetails.hasRole("CURRENT_PI")>
					<#if model['getCreatableElementTypes']??>
					<#list model['getCreatableElementTypes'] as docType>
					<#if docType.typeId="Farmaco" >
					<button class="submitButton round-button blue btn btn-info" onclick="farmacoModalEngine.formByTypeId('${el.id}');return false;"  ><i class="icon-plus bigger-160"  ></i><b>Aggiungi nuovo farmaco</b></button>
				</#if>
			</#list>
		</#if>
	</#if>
	<br/>	<br/>

	<div class="row">
		<div class="col-xs-12">
			<div class="table-responsive">
				<table id="DepotFarmacoTable" class="table table-striped table-bordered table-hover">
					<thead>
					<tr>
						<th class="hidden-480">Farmaco/Dispositivo/Altro</th>
						<th class="hidden-480">Modalit&agrave; di fornitura/copertura dei costi</th>
						<th class="hidden-480">Azioni</th>
					</tr>
					</thead>

					<tbody>
				</table>
			</div>
		</div>
	</div>
	<#assign legendaFarmaco=true>
	<#include "./legenda.ftl"/>
