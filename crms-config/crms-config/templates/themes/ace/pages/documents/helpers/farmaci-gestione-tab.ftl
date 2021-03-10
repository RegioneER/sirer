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

var initFarmaciaFormAction=function(object){
	var form=object.getForm();
	$(".radio").addClass("left");
	$("div[data-field-ref=depotFarmaco_DepotChiuso]").hide();
	$("div[data-field-ref=depotFarmaco_tipo]").hide();
	//$("div[data-field-ref=depotFarmaco_modalitaFornitura]").remove();
	//$("div[data-field-ref=depotFarmaco_GaraFornituraDisp]").remove();
}

var FarmaciaCompilationChecks=function(object){
var form=object.getForm();
return true;
}

var farmaciaModalEngine=new xCDM_Modal(baseUrl, 'DepotFarmaco', initFarmaciaFormAction, FarmaciaCompilationChecks, farmaciaSaveCallBack);

function farmaciaSaveCallBack(object){
loadFarmacia('${el.id}', $('#DepotFarmaciaTable'));
}

function loadFarmacia(centroId, table){
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
			var td2=$('<td>');
			if(farmaco.metadata['depotFarmaco_modalitaFornitura']!==undefined && farmaco.metadata['depotFarmaco_modalitaFornitura'][0]!==undefined && farmaco.metadata['depotFarmaco_modalitaFornitura'][0].split("###")[1]){

			td2.html(farmaco.metadata['depotFarmaco_modalitaFornitura'][0].split("###")[1]);
			}

		var td3=$('<td>');
		var editLink=$('<a>');
			editLink.attr('href','#');
			editLink.attr('title','modifica');
			editLink.html('<i class="fa fa-pencil fa-2x"></i>&nbsp;');
			(function(farmaco, editLink){
			editLink.click(function(){
			farmaciaModalEngine.formByElement(farmaco);
			});
			})(farmaco, editLink);
			td3.append(editLink);

			var depotLink=$('<a>');
			depotLink.attr("href",baseUrl+"/app/documents/detail/"+farmaco.id);
			depotLink.attr('title','gestisci Magazzino');
			depotLink.html('<i class="fa fa-ambulance fa-2x red"></i>&nbsp;');
			td3.append(depotLink);

			var docLink=$('<a>');
			docLink.attr("href",baseUrl+"/app/documents/custom/DepotFarmacoDoc/"+farmaco.id);
			docLink.attr('title','Area Documentale Magazzino');
			docLink.html('<i class="fa fa-folder-open fa-2x orange"></i>&nbsp;');
			td3.append(docLink);
			tr.append(td1);
			//tr.append(td2);
			tr.append(td3);
			table.find('tbody').append(tr);
		}
	});
}
loadFarmacia('${el.id}', $('#DepotFarmaciaTable'));

</@script>
	<br/>	<br/>

	<div class="row">
		<div class="col-xs-12">
			<div class="table-responsive">
				<table id="DepotFarmaciaTable" class="table table-striped table-bordered table-hover">
					<thead>
					<tr>
						<th class="hidden-480">Farmaco/Dispositivo/Altro</th>
						<!--th class="hidden-480">Modalit&agrave; di fornitura/copertura dei costi</th-->
						<th class="hidden-480">Azioni</th>
					</tr>
					</thead>

					<tbody>
				</table>
			</div>
		</div>
	</div>
