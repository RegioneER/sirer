<#assign type=model['docDefinition']/>
<#global page={
"content": path.pages+"/"+mainContent,
"styles" : ["jquery-ui-full", "datepicker","pages/studio.css","x-editable","select2"],
"scripts" : ["jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable","select2","base"],
"inline_scripts":[],
"title" : "Dettaglio",
"description" : "Dettaglio"
} />
<@breadcrumbsData el />
<#assign json=el.type.getDummyJson() />
<#assign loadedJson=el.getElementCoreJsonToString(userDetails) />
<#assign jsonParent=el.getParent().type.getDummyJson() />
<#assign loadedJsonParent=el.getParent().getElementCoreJsonToString(userDetails) />
<@script>
var parentElement=${loadedJsonParent};
var tipoStudio;
if(parentElement.metadata.datiStudio_tipoStudio){
    tipoStudio=parentElement.metadata.datiStudio_tipoStudio[0].split("###")[0];
}$('select').select2({containerCssClass:'select2-ace',allowClear: true});


    function showHideTipo(valore){
	    switch (valore) {
		    case '1':
		    $('#informations-Farmaco_categoria').show();
		    $('#Farmaco_categoria-select').trigger('change');
		    $('#informations-Farmaco_dosaggio').show();
		    $('#informations-Farmaco_formaFarm').show();
		    $('#informations-Farmaco_costo').hide();//  NASCONDO SEMPRE
		    $('#informations-Farmaco_totaleValore').hide();// NASCONDO SEMPRE
		    $('#informations-Farmaco_numUnitaPaz').hide();// NASCONDO SEMPRE
		    $('#informations-Farmaco_unitaMisura').hide();// NASCONDO SEMPRE
		    $('#informations-Farmaco_AIC').show();
		    $('#informations-Farmaco_princAtt').show();
		    $('#informations-Farmaco_princAttAltro').show();
		    $('#informations-Farmaco_MarchioCE').hide();
		    $('[name=Farmaco_MarchioCE]').attr('checked', false).trigger('change');
		    $('#informations-Farmaco_DittaProduttriceDisp').hide();
		    $('#informations-Farmaco_numeroRepertorioDisp').hide();
			$('#informations-Farmaco_IndicazioniDisp').hide();
		    $('#informations-Farmaco_classificCNDdisp').hide();
		    $('#informations-Farmaco_descrCNDdisp').hide();
		    $('#informations-Farmaco_classeDiRischioDisp').hide();
		    $('#informations-Farmaco_ImpiegoDestUso').hide();
		    $('#Farmaco_ImpiegoDestUso').attr('checked', false).trigger('change');
		    $('#informations-Farmaco_GaraFornituraDisp').hide();
		    $('#Farmaco_GaraFornituraDisp').attr('checked', false).trigger('change');
		    $('#informations-Farmaco_PrezzoFornituraDisp').hide();
		    $('#Farmaco_PrezzoFornituraDisp').val('');
		    $('#informations-Farmaco_ImpiantabileDisp').hide();
		    $('#Farmaco_ImpiantabileDisp').attr('checked', false).trigger('change');
		    $('#informations-Farmaco_SedeImpiantoDisp').hide();
		    $('#Farmaco_SedeImpiantoDisp').val('');
		    $('#informations-Farmaco_categoriaDisp').hide();
		    $('#Farmaco_DittaProduttriceDisp').val('');
		    $('#Farmaco_numeroRepertorioDisp').val('');
			$('#Farmaco_IndicazioniDisp').val('');
		    $('#Farmaco_classificCNDdisp').val('');
		    $('#Farmaco_descrCNDdisp').val('');
		    $('[name=Farmaco_classeDiRischioDisp]').attr('checked', false).trigger('change');
		    $('#informations-Farmaco_categoriaDisp').hide();
		    $('#Farmaco_categoriaDisp-select').val(null).trigger('change');
		    $('#informations-Farmaco_dispMed').hide();
		    $('#Farmaco_dispMed').tokenInput('clear');
			$('#informations-Farmaco_TessutoAnimaleDisp').hide();
			$('[name=Farmaco_TessutoAnimaleDisp]').attr('checked', false).trigger('change');
			$('#informations-Farmaco_IncorporaMedicinaleDisp').hide();
			$('[name=Farmaco_IncorporaMedicinaleDisp]').attr('checked', false).trigger('change');
			$('#informations-Farmaco_dispMedAltro').hide();
		    $('#Farmaco_dispMedAltro').val('');
		    $("tr[id$='Attr']").hide();
		    $("input[id$='Attr'][type=radio]").attr('checked', false).trigger('change');
		    $("input[id$='Attr'][type=text]").val('');
		    $("tr[id$='Mat']").hide();
		    $("input[id$='Mat'][type=radio]").attr('checked', false).trigger('change');
		    $("input[id$='Mat'][type=text]").val('');
		    $("tr[id$='MatAltro']").hide();
		    $("#Farmaco_descrizioneMatAltro").val("");
		    break;
		    case '2':
		    //$("label[for=Farmaco_modalitaFornitura]").html($("label[for=Farmaco_modalitaFornitura]").html().replace("Modalità di fornitura","Copertura oneri finanziari"));
		    //$("#legendaFarmaco").html($("#legendaFarmaco").html().replace("Modalità di fornitura","Copertura oneri finanziari"));
		    $('#informations-Farmaco_categoria').hide();
		    $('#Farmaco_categoria-select').val(null).trigger('change');
		    $('#informations-Farmaco_dosaggio').hide();
		    $('#Farmaco_dosaggio').val('');
		    $('#informations-Farmaco_formaFarm').hide();
		    $('#Farmaco_formaFarm').val('');
		    $('#informations-Farmaco_costo').hide();//  NASCONDO SEMPRE
		    $('#Farmaco_costo').val('');
		    $('#informations-Farmaco_totaleValore').hide();// NASCONDO SEMPRE
		    $('#Farmaco_totaleValore').val('');
		    $('#informations-Farmaco_numUnitaPaz').hide();// NASCONDO SEMPRE
		    $('#Farmaco_numUnitaPaz').val('');
		    $('#informations-Farmaco_unitaMisura').hide();// NASCONDO SEMPRE
		    $('#Farmaco_unitaMisura').val('');
		
		    $('#informations-Farmaco_AIC').hide();
		    $('[name=Farmaco_AIC]').attr('checked', false).trigger('change');
		    $('#informations-Farmaco_princAtt').hide();
			if($('#Farmaco_princAtt').attr('istokeninput')!==undefined){
		    	$('#Farmaco_princAtt').tokenInput('clear');
			}
		    $('#informations-Farmaco_princAttAltro').hide();
		    $('#Farmaco_princAttAltro').val('');
		    $('#informations-Farmaco_MarchioCE').show();
		    $('#informations-Farmaco_DittaProduttriceDisp').show();
		    $('#informations-Farmaco_numeroRepertorioDisp').show();
			$('#informations-Farmaco_IndicazioniDisp').show();
		    $('#informations-Farmaco_classificCNDdisp').show();
		    $('#informations-Farmaco_descrCNDdisp').show();
		    $('#informations-Farmaco_ImpiegoDestUso').show();
		    $('#informations-Farmaco_GaraFornituraDisp').show();
		    $('#informations-Farmaco_PrezzoFornituraDisp').show();
		    $('#informations-Farmaco_ImpiantabileDisp').show();
		    $('#informations-Farmaco_SedeImpiantoDisp').show();
		    $('#informations-Farmaco_classeDiRischioDisp').show();
		    $('#informations-Farmaco_categoriaDisp').show();
			$('#informations-Farmaco_TessutoAnimaleDisp').show();
			$('#informations-Farmaco_IncorporaMedicinaleDisp').show();
			$('#informations-Farmaco_dispMed').show();
		    $('#informations-Farmaco_dispMedAltro').show();
		    $("tr[id$='Attr']").hide();
		    $("input[id$='Attr'][type=radio]").attr('checked', false).trigger('change');
		    $("input[id$='Attr'][type=text]").val('');
		    $("tr[id$='Mat']").hide();
		    $("input[id$='Mat'][type=radio]").attr('checked', false).trigger('change');
		    $("input[id$='Mat'][type=text]").val('');
		    $("tr[id$='MatAltro']").hide();
		    $("#Farmaco_descrizioneMatAltro").val("");
		    break;
		    case '3':
		    $('#informations-Farmaco_categoria').hide();
		    $('#Farmaco_categoria-select').val(null).trigger('change');
		    $('#informations-Farmaco_dosaggio').hide();
		    $('#Farmaco_dosaggio').val('');
		    $('#informations-Farmaco_formaFarm').hide();
		    $('#Farmaco_formaFarm').val('');
		    $('#informations-Farmaco_costo').hide();//  NASCONDO SEMPRE
		    $('#Farmaco_costo').val('');
		    $('#informations-Farmaco_totaleValore').hide();// NASCONDO SEMPRE
		    $('#Farmaco_totaleValore').val('');
		    $('#informations-Farmaco_numUnitaPaz').hide();// NASCONDO SEMPRE
		    $('#Farmaco_numUnitaPaz').val('');
		    $('#informations-Farmaco_unitaMisura').hide();// NASCONDO SEMPRE
		    $('#Farmaco_unitaMisura').val('');
		    $('#informations-Farmaco_AIC').hide();
		    $('[name=Farmaco_AIC]').attr('checked', false).trigger('change');
		    $('#informations-Farmaco_princAtt').hide();
			if($('#Farmaco_princAtt').attr('istokeninput')!==undefined){
				$('#Farmaco_princAtt').tokenInput('clear');
			}
		    $('#informations-Farmaco_princAttAltro').hide();
		    $('#Farmaco_princAttAltro').val('');
		    $('#informations-Farmaco_MarchioCE').hide();
		    $('[name=Farmaco_MarchioCE]').attr('checked', false).trigger('change');
		    $('#informations-Farmaco_DittaProduttriceDisp').hide();
		    $('#informations-Farmaco_numeroRepertorioDisp').hide();
			$('#informations-Farmaco_IndicazioniDisp').show();
		    $('#informations-Farmaco_classificCNDdisp').hide();
		    $('#informations-Farmaco_descrCNDdisp').hide();
		    $('#informations-Farmaco_classeDiRischioDisp').hide();
		    $('#informations-Farmaco_categoriaDisp').hide();
		    $('#Farmaco_DittaProduttriceDisp').val('');
		    $('#Farmaco_numeroRepertorioDisp').val('');
			$('#Farmaco_IndicazioniDisp').val('');
		    $('#Farmaco_classificCNDdisp').val('');
		    $('#Farmaco_descrCNDdisp').val('');
		    $('#informations-Farmaco_ImpiegoDestUso').hide();
		    $('#Farmaco_ImpiegoDestUso').attr('checked', false).trigger('change');
		    $('#informations-Farmaco_GaraFornituraDisp').hide();
		    $('#Farmaco_GaraFornituraDisp').attr('checked', false).trigger('change');
		    $('#informations-Farmaco_PrezzoFornituraDisp').hide();
		    $('#Farmaco_PrezzoFornituraDisp').val('');
		    $('#informations-Farmaco_ImpiantabileDisp').hide();
		    $('#Farmaco_ImpiantabileDisp').attr('checked', false).trigger('change');
		    $('#informations-Farmaco_SedeImpiantoDisp').hide();
		    $('#Farmaco_SedeImpiantoDisp').val('');
		    $('[name=Farmaco_classeDiRischioDisp]').attr('checked', false).trigger('change');
		    $('#informations-Farmaco_categoriaDisp').hide();
		    $('#Farmaco_categoriaDisp-select').val(null).trigger('change');
		    $('#informations-Farmaco_dispMed').hide();
			if($('#Farmaco_dispMed').attr('istokeninput')!==undefined){
		    	$('#Farmaco_dispMed').tokenInput('clear');
			}
			$('#informations-Farmaco_TessutoAnimaleDisp').hide();
			$('[name=Farmaco_TessutoAnimaleDisp]').attr('checked', false).trigger('change');
			$('#informations-Farmaco_IncorporaMedicinaleDisp').hide();
			$('[name=Farmaco_IncorporaMedicinaleDisp]').attr('checked', false).trigger('change');
		    $('#informations-Farmaco_dispMedAltro').hide();
		    $('#Farmaco_dispMedAltro').val('');
		    $("tr[id$='Attr']").show();
		    $("tr[id$='Mat']").hide();
		    $("input[id$='Mat'][type=radio]").attr('checked', false).trigger('change');
		    $("input[id$='Mat'][type=text]").val('');
		    $("tr[id$='MatAltro']").hide();
		    $("#Farmaco_descrizioneMatAltro").val("");
		    break;
		    case '4':
		    $('#informations-Farmaco_categoria').hide();
		    $('#Farmaco_categoria-select').val(null).trigger('change');
		    $('#informations-Farmaco_dosaggio').hide();
		    $('#Farmaco_dosaggio').val('');
		    $('#informations-Farmaco_formaFarm').hide();
		    $('#Farmaco_formaFarm').val('');
		    $('#informations-Farmaco_costo').hide();//  NASCONDO SEMPRE
		    $('#Farmaco_costo').val('');
		    $('#informations-Farmaco_totaleValore').hide();// NASCONDO SEMPRE
		    $('#Farmaco_totaleValore').val('');
		    $('#informations-Farmaco_numUnitaPaz').hide();// NASCONDO SEMPRE
		    $('#Farmaco_numUnitaPaz').val('');
		    $('#informations-Farmaco_unitaMisura').hide();// NASCONDO SEMPRE
		    $('#Farmaco_unitaMisura').val('');
		    $('#informations-Farmaco_AIC').hide();
		    $('[name=Farmaco_AIC]').attr('checked', false).trigger('change');
		    $('#informations-Farmaco_princAtt').hide();
			if($('#Farmaco_princAtt').attr('istokeninput')!==undefined){
		    	$('#Farmaco_princAtt').tokenInput('clear');
			}
		    $('#informations-Farmaco_princAttAltro').hide();
		    $('#Farmaco_princAttAltro').val('');
		    $('#informations-Farmaco_MarchioCE').hide();
		    $('[name=Farmaco_MarchioCE]').attr('checked', false).trigger('change');
		    $('#informations-Farmaco_DittaProduttriceDisp').hide();
		    $('#informations-Farmaco_numeroRepertorioDisp').hide();
			$('#informations-Farmaco_IndicazioniDisp').hide();
		    $('#informations-Farmaco_classificCNDdisp').hide();
		    $('#informations-Farmaco_descrCNDdisp').hide();
		    $('#informations-Farmaco_classeDiRischioDisp').hide();
		    $('#informations-Farmaco_categoriaDisp').hide();
		    $('#Farmaco_DittaProduttriceDisp').val('');
			$('#Farmaco_IndicazioniDisp').val('');
		    $('#Farmaco_numeroRepertorioDisp').val('');
		    $('#Farmaco_classificCNDdisp').val('');
		    $('#Farmaco_descrCNDdisp').val('');
		    $('#informations-Farmaco_ImpiegoDestUso').hide();
		    $('#Farmaco_ImpiegoDestUso').attr('checked', false).trigger('change');
		    $('#informations-Farmaco_GaraFornituraDisp').hide();
		    $('#Farmaco_GaraFornituraDisp').attr('checked', false).trigger('change');
		    $('#informations-Farmaco_PrezzoFornituraDisp').hide();
		    $('#Farmaco_PrezzoFornituraDisp').val('');
		    $('#informations-Farmaco_ImpiantabileDisp').hide();
		    $('#Farmaco_ImpiantabileDisp').attr('checked', false).trigger('change');
		    $('#informations-Farmaco_SedeImpiantoDisp').hide();
		    $('#Farmaco_SedeImpiantoDisp').val('');
		    $('[name=Farmaco_classeDiRischioDisp]').attr('checked', false).trigger('change');
		    $('#informations-Farmaco_categoriaDisp').hide();
		    $('#Farmaco_categoriaDisp-select').val(null).trigger('change');
		    $('#informations-Farmaco_dispMed').hide();
			if($('#Farmaco_dispMed').attr('istokeninput')!==undefined){
		    	$('#Farmaco_dispMed').tokenInput('clear');
			}
		    $('#informations-Farmaco_dispMedAltro').hide();
		    $('#Farmaco_dispMedAltro').val('');
			$('#informations-Farmaco_TessutoAnimaleDisp').hide();
			$('[name=Farmaco_TessutoAnimaleDisp]').attr('checked', false).trigger('change');
			$('#informations-Farmaco_IncorporaMedicinaleDisp').hide();
			$('[name=Farmaco_IncorporaMedicinaleDisp]').attr('checked', false).trigger('change');
		    $("tr[id$='Attr']").hide();
		    $("input[id$='Attr'][type=radio]").attr('checked', false).trigger('change');
		    $("input[id$='Attr'][type=text]").val('');
		    $("tr[id$='Mat']").show();
		    $("tr[id$='MatAltro']").hide();
		    $("#Farmaco_descrizioneMatAltro").val("");
		    break;
		    case '5':
		    $('#informations-Farmaco_categoria').hide();
		    $('#Farmaco_categoria-select').val(null).trigger('change');
		    $('#informations-Farmaco_dosaggio').hide();
		    $('#Farmaco_dosaggio').val('');
		    $('#informations-Farmaco_formaFarm').hide();
		    $('#Farmaco_formaFarm').val('');
		    $('#informations-Farmaco_costo').hide();//  NASCONDO SEMPRE
		    $('#Farmaco_costo').val('');
		    $('#informations-Farmaco_totaleValore').hide();// NASCONDO SEMPRE
		    $('#Farmaco_totaleValore').val('');
		    $('#informations-Farmaco_numUnitaPaz').hide();// NASCONDO SEMPRE
		    $('#Farmaco_numUnitaPaz').val('');
		    $('#informations-Farmaco_unitaMisura').hide();// NASCONDO SEMPRE
		    $('#Farmaco_unitaMisura').val('');
		    $('#informations-Farmaco_AIC').hide();
		    $('[name=Farmaco_AIC]').attr('checked', false).trigger('change');
		    $('#informations-Farmaco_princAtt').hide();
			if($('#Farmaco_princAtt').attr('istokeninput')!==undefined){
		    	$('#Farmaco_princAtt').tokenInput('clear');
			}
		    $('#informations-Farmaco_princAttAltro').hide();
		    $('#Farmaco_princAttAltro').val('');
		    $('#informations-Farmaco_MarchioCE').hide();
		    $('[name=Farmaco_MarchioCE]').attr('checked', false).trigger('change');
		    $('#informations-Farmaco_DittaProduttriceDisp').hide();
		    $('#informations-Farmaco_numeroRepertorioDisp').hide();
			$('#informations-Farmaco_IndicazioniDisp').hide();
		    $('#informations-Farmaco_classificCNDdisp').hide();
		    $('#informations-Farmaco_descrCNDdisp').hide();
		    $('#informations-Farmaco_classeDiRischioDisp').hide();
		    $('#informations-Farmaco_categoriaDisp').hide();
		    $('#Farmaco_DittaProduttriceDisp').val('');
		    $('#Farmaco_numeroRepertorioDisp').val('');
			$('#Farmaco_IndicazioniDisp').val('');
		    $('#Farmaco_classificCNDdisp').val('');
		    $('#Farmaco_descrCNDdisp').val('');
		    $('#informations-Farmaco_ImpiegoDestUso').hide();
		    $('#Farmaco_ImpiegoDestUso').attr('checked', false).trigger('change');
		    $('#informations-Farmaco_GaraFornituraDisp').hide();
		    $('#Farmaco_GaraFornituraDisp').attr('checked', false).trigger('change');
		    $('#informations-Farmaco_PrezzoFornituraDisp').hide();
		    $('#Farmaco_PrezzoFornituraDisp').val('');
		    $('#informations-Farmaco_ImpiantabileDisp').hide();
		    $('#Farmaco_ImpiantabileDisp').attr('checked', false).trigger('change');
		    $('#informations-Farmaco_SedeImpiantoDisp').hide();
		    $('#Farmaco_SedeImpiantoDisp').val('');
		    $('[name=Farmaco_classeDiRischioDisp]').attr('checked', false).trigger('change');
		    $('#informations-Farmaco_categoriaDisp').hide();
		    $('#Farmaco_categoriaDisp-select').val(null).trigger('change');
		    $('#informations-Farmaco_dispMed').hide();
			if($('#Farmaco_dispMed').attr('istokeninput')!==undefined){
		    	$('#Farmaco_dispMed').tokenInput('clear');
			}
		    $('#informations-Farmaco_dispMedAltro').hide();
		    $('[name=Farmaco_TessutoAnimaleDisp]').attr('checked', false).trigger('change');
			$('#informations-Farmaco_IncorporaMedicinaleDisp').hide();
			$('[name=Farmaco_IncorporaMedicinaleDisp]').attr('checked', false).trigger('change');
		    $("tr[id$='Attr']").hide();
		    $("input[id$='Attr'][type=radio]").attr('checked', false).trigger('change');
		    $("input[id$='Attr'][type=text]").val('');
		    $("tr[id$='Mat']").hide();
		    $("input[id$='Mat'][type=radio]").attr('checked', false).trigger('change');
		    $("input[id$='Mat'][type=text]").val('');
		    $("tr[id$='MatAltro']").show();
		
		    break;
	    }
    }
    
    function showHideMarchioCE(valore){
    	if (valore ==='1###Si') {
			console.log ('si');
			$('#informations-Farmaco_numeroRepertorioDisp').show();
			$('#informations-Farmaco_classificCNDdisp').show();
			$('#informations-Farmaco_descrCNDdisp').show();
			$('#informations-Farmaco_IndicazioniDisp').show();
	    }
		else {
			$('#informations-Farmaco_numeroRepertorioDisp').hide();
			$('[id=Farmaco_numeroRepertorioDisp]').val('');//se nascondo sbianco il valore!
			$('#informations-Farmaco_classificCNDdisp').hide();
			$('[id=Farmaco_classificCNDdisp]').val('');//se nascondo sbianco il valore!
			$('#informations-Farmaco_descrCNDdisp').hide();
			$('[id=Farmaco_descrCNDdisp]').val('');//se nascondo sbianco il valore!
			$('#informations-Farmaco_IndicazioniDisp').hide();
			$('#Farmaco-Farmaco_IndicazioniDisp').val('');
			console.log ('no o undefined');
	    }
    }

	function showHideIncorporaMedicinaleDisp(valore) {
		if (valore ==='1###Si') {
			$('#informations-Farmaco_MedicinaleUnitoDisp').show();
			$('#informations-Farmaco_MedicinaleAccessioriDisp').show();
			$('#informations-Farmaco_MedicinaleSintesiDisp').show();

		}
		else {
			$('#informations-Farmaco_MedicinaleUnitoDisp').hide();
			$('[name=Farmaco_MedicinaleUnitoDisp]').attr('checked', false).trigger('change');
			$('#informations-Farmaco_MedicinaleAccessioriDisp').hide();
			$('[name=Farmaco_MedicinaleAccessioriDisp]').attr('checked', false).trigger('change');
			$('#informations-Farmaco_MedicinaleSintesiDisp').hide();
			$('#Farmaco_MedicinaleSintesiDisp').val('');
		}
	}

    
    function showHideCategoria(valore){
        if (valore == '1') {
		    $('#informations-Farmaco_testOcomparatore').show();
	    } else {
		    $('#informations-Farmaco_testOcomparatore').hide();
		    $('[name=Farmaco_testOcomparatore]').attr('checked', false).trigger('change');
	    }
	}
	
	function showHideFarmacoAIC(valore){
	    if (valore == '1###Si') {
		    $('#informations-Farmaco_SpecialitaAIC').show();
		    $('#informations-Farmaco_CodiceAIC').show();
		    $('#informations-Farmaco_ConfezioneAIC').show();
		    $('#informations-Farmaco_CodiceATC').show();
	    } else {
		    $('#informations-Farmaco_SpecialitaAIC').hide();
		    $('#Farmaco_SpecialitaAIC').val('');
		    $('#informations-Farmaco_CodiceAIC').hide();
		    $('#Farmaco_CodiceAIC').val('');
		    $('#informations-Farmaco_CodiceATC').hide();
		    $('#Farmaco_CodiceATC').val('');
		    $('#informations-Farmaco_ConfezioneAIC').hide();
		    $('#Farmaco_ConfezioneAIC').val('');
	    }
	}
	
	
$(document).ready(function() {
/*if(tipoStudio!="6"){
    //SIRER-28 tolgo MaterialeBiologico da opzioni select in configurazione, ma restano i campi 4:"Materiale Biologico"
    $($("#Farmaco_tipo-select").children('option')[4]).attr("disabled",true);
}*/
$($("#Farmaco_tipo-select").children('option')[4]).remove();
$('#Farmaco_dispMed').bind('change', function () { //TOSCANA-288
if ($('#Farmaco_MarchioCE:checked').val() === '1###Si') {
loadingScreen('Caricamento informazioni dispositivo', 'loading');
var disp_med_id = $(this).val().split('###') [0];
$.ajax({
type: 'GET',
url: '/SfogliaDMdettagli.php?term=' + disp_med_id,
dataType: 'json',
success: function (data) {
if (data.sstatus == 'ko') {
alert('ERRORE\n' + data.error + '\n' + data.detail.toString());
bootbox.hideAll();
} else {
$.each(data, function (skey, sval) {
$('#Farmaco_DittaProduttriceDisp').val(sval.FABBRICANTE_ASSEMBLATORE); //TOSCANA-288
$('#Farmaco_classificCNDdisp').val(sval.CLASSIFICAZIONE_CND); //TOSCANA-288
$('#Farmaco_descrCNDdisp').val(sval.DESCRIZIONE_CND); //TOSCANA-288
});
bootbox.hideAll();
}
}
});
}
});
var ricerca=$("<a>");
    $(ricerca).click(function(){visualizzaModalRicerca();});
    $(ricerca).attr('href','#');
    $(ricerca).html('<i class="fa fa-search blue"></i>&nbsp;cerca');
    $('#Farmaco_SpecialitaAIC').parent().append(ricerca);
    $('#informations-Farmaco_categoria').hide();
    $('#informations-Farmaco_dosaggio').hide();
    $('#informations-Farmaco_formaFarm').hide();
    $('#informations-Farmaco_costo').hide(); // NASCONDO SEMPRE
    $('#informations-Farmaco_totaleValore').hide();// NASCONDO SEMPRE
    $('#informations-Farmaco_numUnitaPaz').hide();// NASCONDO SEMPRE
    $('#informations-Farmaco_unitaMisura').hide();// NASCONDO SEMPRE
    $('#informations-Farmaco_testOcomparatore').hide();
    $('#informations-Farmaco_AIC').hide();
    $('#informations-Farmaco_SpecialitaAIC').hide();
    $('#informations-Farmaco_CodiceAIC').hide();
    $('#informations-Farmaco_ConfezioneAIC').hide();
    $('#informations-Farmaco_CodiceATC').hide();
    $('#informations-Farmaco_princAtt').hide();
    $('#informations-Farmaco_princAtt').hide();
    $('#informations-Farmaco_princAttAltro').hide();
    $('#informations-Farmaco_MarchioCE').hide();
    $('#informations-Farmaco_DittaProduttriceDisp').hide();
    $('#informations-Farmaco_numeroRepertorioDisp').hide();
	$('#informations-Farmaco_IndicazioniDisp').hide();
    $('#informations-Farmaco_classificCNDdisp').hide();
    $('#informations-Farmaco_descrCNDdisp').hide();
    $('#informations-Farmaco_classeDiRischioDisp').hide();
    $('#informations-Farmaco_ImpiegoDestUso').hide();
    $('#informations-Farmaco_GaraFornituraDisp').hide();
    $('#informations-Farmaco_PrezzoFornituraDisp').hide();
    $('#informations-Farmaco_ImpiantabileDisp').hide();
    $('#informations-Farmaco_SedeImpiantoDisp').hide();
    $('#informations-Farmaco_categoriaDisp').hide();
    $('#informations-Farmaco_dispMed').hide();
    $('#informations-Farmaco_dispMedAltro').hide();
	$('#informations-Farmaco_TessutoAnimaleDisp').hide();
	$('#informations-Farmaco_IncorporaMedicinaleDisp').hide();
	$("tr[id$='Attr']").hide();
    $("tr[id$='Mat']").hide();
    $("tr[id$='MatAltro']").hide();
    
    
    $('#Farmaco_tipo-select').change(function () {
	    var valore = $('#Farmaco_tipo-select').val().split('###') [0];
	    //$("label[for=Farmaco_modalitaFornitura]").html($("label[for=Farmaco_modalitaFornitura]").html().replace("Copertura oneri finanziari","Modalità di fornitura"));
	    //$("#legendaFarmaco").html($("#legendaFarmaco").html().replace("Copertura oneri finanziari","Modalità di fornitura"));
    	showHideTipo(valore);
    });
	
	
	$('[id=Farmaco_MarchioCE]').change(function () {
    	var valore = $('[name=Farmaco_MarchioCE]:checked').val();
    	showHideMarchioCE(valore);
    });
	$('[id=Farmaco_IncorporaMedicinaleDisp]').change(function () {
		var valore = $('[name=Farmaco_IncorporaMedicinaleDisp]:checked').val();
		showHideIncorporaMedicinaleDisp(valore);
	});

	
    $('#Farmaco_categoria-select').change(function () {
	    var valore = $('#Farmaco_categoria-select').val().split('###') [0];
    	showHideCategoria(valore);
    });
    
    $('[name=Farmaco_AIC]').change(function () {
    	var valore = $('[name=Farmaco_AIC]:checked').val();
    	showHideFarmacoAIC(valore);
    });
    
    $('#Farmaco_tipo-select').trigger('change');
	$('[name=Farmaco_AIC]').trigger('change');
    	

    if ($('#Farmaco_tipo-select').length==0){
    	//alert(loadedElement);
	    var tmpvalore = loadedElement.metadata.Farmaco_tipo[0].split('###') [0];
    	showHideTipo(tmpvalore);
    	tmpvalore = loadedElement.metadata.Farmaco_MarchioCE.length==0?0:1;
    	showHideMarchioCE(tmpvalore);
	    tmpvalore = loadedElement.metadata.Farmaco_categoria[0].split('###') [0];
    	showHideCategoria(tmpvalore);
    	tmpvalore = loadedElement.metadata.Farmaco_AIC.length==0?0:1;
    	showHideFarmacoAIC(tmpvalore);
		tmpvalore = loadedElement.metadata.Farmaco_IncorporaMedicinaleDisp.length==0?0:1;
		showHideIncorporaMedicinaleDisp(tmpvalore);
    }
    
    }); //Chiusura del document ready
    
    
    
    $("[name=salvaForm-Farmaco]").unbind('click').on('click',function(){
    var $form=$($(this).data('rel'));
    if($(this).attr('id')){
    var formName=$(this).attr('id').replace("salvaForm-", "");
    }
    else{
    formName="formNonEsistente"
    }
    if ($('#Farmaco_tipo').val()==""){
    console.log("controllo campo obbligatorio Farmaco_tipo di tipo SELECT");
    alert("Il campo Tipo deve essere compilato");
    $('#Farmaco_tipo').focus();
    return false;
    }
    if ($('#Farmaco_tipo').val() == '1###Farmaco' || $('#Farmaco_tipo').val() == '4###Parafarmaco' || $('#Farmaco_tipo').val() == '5###Nutraceutica') {
    if ($('#Farmaco_categoria').val()==""){
    console.log("controllo campo obbligatorio Farmaco_categoria di tipo SELECT");
    alert("Il campo Categoria deve essere compilato");
    $('#Farmaco_categoria').focus();
    return false;
    }
    else {
    if ($('#Farmaco_categoria').val() == '1###IMP' && !$('[name=Farmaco_testOcomparatore]').is(':checked')) {
    console.log('controllo campo obbligatorio Farmaco_testOcomparatore di tipo RADIO');
    alert('Il campo Specificare se Test o Comparatore deve essere compilato');
    $('#Farmaco_testOcomparatore').focus();
    return false;
    }
    }
    if (!$('[name=Farmaco_AIC]').is(':checked')) {
    console.log('controllo campo obbligatorio Farmaco_AIC di tipo RADIO');
    alert('Il campo Il farmaco è in commercio per altre indicazioni in Italia? deve essere compilato');
    $('#Farmaco_AIC').focus();
    return false;
    }
    if ($('#Farmaco_princAtt').val() == '') {
    console.log('controllo campo obbligatorio Farmaco_princAtt di tipo EXT_DICTIONARY');
    alert('Il campo Principio attivo in studio deve essere compilato');
    $('#Farmaco_princAtt').focus();
    return false;
    }
    else if ($('#Farmaco_princAtt').val() == '-9999###Non disponibile' && $('#Farmaco_princAttAltro').val() == '') {
    console.log('controllo campo obbligatorio Farmaco_princAttAltro di tipo EXT_DICTIONARY');
    alert('Il campo Altro Principio attivo deve essere compilato');
    $('#Farmaco_princAttAltro').focus();
    return false;
    }
    }
    else if ($('#Farmaco_tipo').val() == '2###Dispositivo medico') {
    if ($('#Farmaco_MarchioCE:checked').val() === undefined || $('#Farmaco_MarchioCE:checked').val() == '') {
    console.log('controllo campo obbligatorio Farmaco_MarchioCE di tipo RADIO');
    alert('Il campo Presenza del marcio CE deve essere compilato');
    $('#Farmaco_MarchioCE').focus();
    return false;
    }
    if ($('#Farmaco_categoriaDisp-select').val() == '') {
    console.log('controllo campo obbligatorio Farmaco_categoriaDisp di tipo SELECT');
    alert('Il campo Categoria deve essere compilato');
    $('#Farmaco_categoriaDisp').focus();
    return false;
    }
    if ($('#Farmaco_dispMed').val() == '') {
    console.log('controllo campo obbligatorio Farmaco_dispMed di tipo EXT_DICTIONARY');
    alert('Il campo Dispositivo medico in studio deve essere compilato');
    $('#Farmaco_dispMed').focus();
    return false;
    }
    else if ($('#Farmaco_dispMed').val() == '-9999###Non disponibile' && $('#Farmaco_dispMedAltro').val() == '') {
    console.log('controllo campo obbligatorio Farmaco_dispMedAltro di tipo EXT_DICTIONARY');
    alert('Il campo Altro dispositivo medico in studio deve essere compilato');
    $('#Farmaco_dispMedAltro').focus();
    return false;
    }
    if ($('#Farmaco_DittaProduttriceDisp').val() == '') {
    console.log('controllo campo obbligatorio Farmaco_DittaProduttriceDisp di tipo TEXTBOX');
    alert('Il campo Ditta produttrice deve essere compilato');
    $('#Farmaco_DittaProduttriceDisp').focus();
    return false;
    }
    /* if ($('#Farmaco_classificCNDdisp').val() == '') {
    console.log('controllo campo obbligatorio Farmaco_classificCNDdisp di tipo TEXTBOX');
    alert('Il campo Classificazione CND deve essere compilato');
    $('#Farmaco_classificCNDdisp').focus();
    return false;
    } 
    if ($('#Farmaco_descrCNDdisp').val() == '') {
    console.log('controllo campo obbligatorio Farmaco_descrCNDdisp di tipo TEXTBOX');
    alert('Il campo Descrizione CND deve essere compilato');
    $('#Farmaco_descrCNDdisp').focus();
    return false;
    } */
    if ($('input[name=Farmaco_classeDiRischioDisp]:checked').val() === undefined || $('input[name=Farmaco_classeDiRischioDisp]:checked').val() == '') {
    console.log('controllo campo obbligatorio Farmaco_classeDiRischioDisp di tipo RADIO');
    alert('Il campo Classe di rischio deve essere compilato');
    $('#Farmaco_classeDiRischioDisp').focus();
    return false;
    }
    }
    var goon=true;
    if (eval("typeof "+formName+"Checks == 'function'")){
    eval("goon="+formName+"Checks()");
    }
    if (!goon) return false;
    loadingScreen("Salvataggio in corso...", "loading");

    try{
    var myElement={};
    myElement.id=loadedElement.id;
    myElement.type=loadedElement.type;
    myElement.metadata={};
    myElement=formToElement($form,myElement,'Farmaco');
    saveElement(myElement).done(function(data){
    	bootbox.hideAll();
    	if (data.result=="OK") {
    		loadingScreen("Salvataggio effettuato", "green_check");
		    //Giulio 15/09/2014 - Chiusura finestra salvataggio dopo 1 secondo
    		window.setTimeout(function(){
    			bootbox.hideAll();
    		}, 3000);
			if (data.redirect){
    			window.location.href=data.redirect;
    		}
		}else {
			var errorMessage="Errore salvataggio!  <i class='icon-warning-sign red'></i>";
			if(data.errorMessage.includes("RegexpCheckFailed: ")){
				var campoLabel="";
				campoLabel=data.errorMessage.replace("RegexpCheckFailed: ","");
				campoLabel=messages[campoLabel];
				errorMessage="Errore nella validazione del campo:<br/>"+campoLabel;
			}
			bootbox.alert(errorMessage);
		}
    }).fail(function(){
    bootbox.hideAll();
    loadingScreen("Errore salvataggio!", "alerta");


    });
    }catch(err){
    bootbox.hideAll();
    loadingScreen("Errore salvataggio!", "alerta");
    console.log(err);
    }
    });
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


    function deleteElement(element) {
    if(!((typeof element)=='object') && !$.isArray(element)){
    if(isNaN(parseInt(element))){
    bootbox.alert("Attenzione impossibile riconoscere l'elemento da eliminare");
    return;
    }

    }else if (!element || !element.id){
    bootbox.alert("Attenzione impossibile riconoscere l'elemento da eliminare");
    return;
    }
    else{
    return $.ajax({
    url : '../../rest/documents/delete/' + element.id,

    }).done(function() {
    console.log('DELETED');
    window.location.reload();
    });
    }
    }
</@script>
