<#assign type=model['docDefinition']/>
<#assign templates={}/>
<#if type.ftlFormTemplate??>
<#assign templates=templates+{type.ftlFormTemplate:type.ftlFormTemplate}/>
</#if>
<#assign jsonParent=model['parent'].type.getDummyJson() />
<#assign loadedJsonParent=model['parent'].getElementCoreJsonToString(userDetails) />



<@script>
    var parentElement=${loadedJsonParent};
    var tipoStudio;
    if(parentElement.metadata.datiStudio_tipoStudio){
        tipoStudio=parentElement.metadata.datiStudio_tipoStudio[0].split("###")[0];
    }
    $("#Farmaco_dispMed").bind("change",function(){
        if($('#Farmaco_MarchioCE:checked').val()==="1###Si"){
            loadingScreen("Caricamento informazioni dispositivo", "loading");
            var disp_med_id=$(this).val().split('###')[0];
            $.ajax({
                type : "GET",
                url : "/SfogliaDMdettagli.php?term=" + disp_med_id,
                dataType : "json",
                success : function(data) {
                    if (data.sstatus == 'ko') {
                        alert("ERRORE\n" + data.error + "\n" + data.detail.toString());
                        bootbox.hideAll();
                    } else {
                        $.each(data, function(skey, sval) {
                            $('#Farmaco_DittaProduttriceDisp').val(sval.FABBRICANTE_ASSEMBLATORE);
                            $('#Farmaco_classificCNDdisp').val(sval.CLASSIFICAZIONE_CND);
                            $('#Farmaco_descrCNDdisp').val(sval.DESCRIZIONE_CND);
                        });
                        bootbox.hideAll();
                    }
                }
            });
        }
    });
$('#farmaco-form-submit').ready(function() {
/*if(tipoStudio!="6"){ //SIRER-28 tolgo MaterialeBiologico da opzioni select in configurazione, ma restano i campi
    $($("#Farmaco_tipo-select").children('option')[4]).attr("disabled",true);
}*/
$($("#Farmaco_tipo-select").children('option')[4]).remove();
var ricerca=$("<a>");
    $(ricerca).click(function(){visualizzaModalRicerca();});
    $(ricerca).attr('href','#');
    $(ricerca).html('<i class="fa fa-search blue"></i>&nbsp;cerca');
    $('#Farmaco_SpecialitaAIC').parent().append(ricerca);
    $('#Farmaco-Farmaco_categoria').parent().hide();
    $('#Farmaco-Farmaco_costo').parent().hide();// NASCONDO SEMPRE
    $('#Farmaco-Farmaco_totaleValore').parent().hide();// NASCONDO SEMPRE
    $('#Farmaco-Farmaco_numUnitaPaz').parent().hide();// NASCONDO SEMPRE
    $('#Farmaco-Farmaco_unitaMisura').parent().hide();// NASCONDO SEMPRE
    $('#Farmaco-Farmaco_testOcomparatore').parent().hide();
    $('#Farmaco-Farmaco_AIC').parent().hide();
    $('#Farmaco-Farmaco_SpecialitaAIC').parent().hide();
    $('#Farmaco-Farmaco_CodiceAIC').parent().hide();
    $('#Farmaco-Farmaco_ConfezioneAIC').parent().hide();
    $('#Farmaco-Farmaco_princAtt').parent().hide();
    $('#Farmaco-Farmaco_princAttAltro').parent().hide();
    $('#Farmaco-Farmaco_CodiceATC').parent().hide();
    $('#Farmaco-Farmaco_MarchioCE').parent().hide();
    $('[name=Farmaco_MarchioCE]').attr('checked', false).trigger('change');
    $('#Farmaco-Farmaco_DittaProduttriceDisp').parent().hide();
    $('#Farmaco-Farmaco_numeroRepertorioDisp').parent().hide();
    $('#Farmaco-Farmaco_classificCNDdisp').parent().hide();
    $('#Farmaco-Farmaco_descrCNDdisp').parent().hide();
    $('#Farmaco-Farmaco_classeDiRischioDisp').parent().hide();
    $('#Farmaco-Farmaco_IndicazioniDisp').parent().hide();
    $('#Farmaco-Farmaco_IndicazioniDisp').val('');
    $('#Farmaco-Farmaco_TessutoAnimaleDisp').parent().hide();
    $('[name=Farmaco_TessutoAnimaleDisp]').attr('checked', false).trigger('change');
    $('#Farmaco-Farmaco_IncorporaMedicinaleDisp').parent().hide();
    $('[name=Farmaco_IncorporaMedicinaleDisp]').attr('checked', false).trigger('change');
    $('#Farmaco-Farmaco_MedicinaleUnitoDisp').parent().hide();
    $('[name=Farmaco_MedicinaleUnitoDisp]').attr('checked', false).trigger('change');
    $('#Farmaco-Farmaco_MedicinaleAccessioriDisp').parent().hide();
    $('[name=Farmaco_MedicinaleAccessioriDisp]').attr('checked', false).trigger('change');
    $('#Farmaco-Farmaco_MedicinaleSintesiDisp').parent().hide();
    $('#Farmaco_MedicinaleSintesiDisp').val('');

    $('#Farmaco-Farmaco_ImpiegoDestUso').parent().hide();
    $('#Farmaco-Farmaco_GaraFornituraDisp').parent().hide();
    $('#Farmaco-Farmaco_PrezzoFornituraDisp').parent().hide();
    $('#Farmaco-Farmaco_ImpiantabileDisp').parent().hide();
    $('#Farmaco-Farmaco_SedeImpiantoDisp').parent().hide();
    $('#Farmaco-Farmaco_categoriaDisp').parent().hide();
    $('#Farmaco-Farmaco_dispMed').parent().hide();
    $('#Farmaco-Farmaco_dispMedAltro').parent().hide();
    $("div[id$='Attr']").parent().hide();
    $("div[id$='Mat']").parent().hide();
    $("div[id$='MatAltro']").parent().hide();
    $('#Farmaco_tipo-select').change(function(){
        var valore=$('#Farmaco_tipo-select').val().split('###')[0];
        //$("label[for=Farmaco_modalitaFornitura]").html($("label[for=Farmaco_modalitaFornitura]").html().replace("Copertura oneri finanziari","Modalità di fornitura"));
        //$("#legendaFarmaco").html($("#legendaFarmaco").html().replace("Copertura oneri finanziari","Modalità di fornitura"));
        switch(valore){
            case "1":
                $('#Farmaco-Farmaco_categoria').parent().show();
                $('#Farmaco-Farmaco_costo').parent().hide();// NASCONDO SEMPRE
                $('#Farmaco-Farmaco_totaleValore').parent().hide();// NASCONDO SEMPRE
                $('#Farmaco-Farmaco_numUnitaPaz').parent().hide();// NASCONDO SEMPRE
                $('#Farmaco-Farmaco_unitaMisura').parent().hide();// NASCONDO SEMPRE
                $('#Farmaco-Farmaco_AIC').parent().show();
                $('#Farmaco-Farmaco_princAtt').parent().show();
                $('#Farmaco-Farmaco_princAttAltro').parent().show();
                $('#Farmaco-Farmaco_CodiceATC').parent().show();
                $('[name=Farmaco_MarchioCE]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_DittaProduttriceDisp').parent().hide();
                $('#Farmaco-Farmaco_numeroRepertorioDisp').parent().hide();
                $('#Farmaco-Farmaco_classificCNDdisp').parent().hide();
                $('#Farmaco-Farmaco_descrCNDdisp').parent().hide();
                $('#Farmaco-Farmaco_classeDiRischioDisp').parent().hide();
                $('#Farmaco-Farmaco_categoriaDisp').parent().hide();
                $('#Farmaco_DittaProduttriceDisp').val('');
                $('#Farmaco_numeroRepertorioDisp').val('');
                $('#Farmaco_classificCNDdisp').val('');
                $('#Farmaco_descrCNDdisp').val('');
                $('#Farmaco-Farmaco_IndicazioniDisp').parent().hide();
                $('#Farmaco-Farmaco_IndicazioniDisp').val('');
                $('#Farmaco-Farmaco_TessutoAnimaleDisp').parent().hide();
                $('[name=Farmaco_TessutoAnimaleDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_IncorporaMedicinaleDisp').parent().hide();
                $('[name=Farmaco_IncorporaMedicinaleDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_MedicinaleUnitoDisp').parent().hide();
                $('[name=Farmaco_MedicinaleUnitoDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_MedicinaleAccessioriDisp').parent().hide();
                $('[name=Farmaco_MedicinaleAccessioriDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_MedicinaleSintesiDisp').parent().hide();
                $('#Farmaco_MedicinaleSintesiDisp').val('');
                $('[name=Farmaco_classeDiRischioDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_ImpiegoDestUso').parent().hide();
                $('[name=Farmaco_ImpiegoDestUso]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_GaraFornituraDisp').parent().hide();
                $('[name=Farmaco_GaraFornituraDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_PrezzoFornituraDisp').parent().hide();
                $('#Farmaco_PrezzoFornituraDisp').val('');
                $('#Farmaco-Farmaco_ImpiantabileDisp').parent().hide();
                $('[name=Farmaco_ImpiantabileDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_SedeImpiantoDisp').parent().hide();
                $('#Farmaco_SedeImpiantoDisp').val('');
                $('#Farmaco_categoriaDisp-select').val(null).trigger('change');
                $('#Farmaco-Farmaco_dispMed').parent().hide();
                $('#Farmaco_dispMed').tokenInput("clear");
                $('#Farmaco-Farmaco_dispMedAltro').parent().hide();
                $('#Farmaco_dispMedAltro').val('');
                $("div[id$='Attr']").parent().hide();
                $("input[id$='Attr'][type=radio]").attr('checked', false).trigger('change');
                $("input[id$='Attr'][type=text]").val('');
                $("div[id$='Mat']").parent().hide();
                $("input[id$='Mat'][type=radio]").attr('checked', false).trigger('change');
                $("input[id$='Mat'][type=text]").val('');
                $("div[id$='MatAltro']").parent().hide();
                $("#Farmaco_descrizioneMatAltro").val("")
                break;
            case "2":
                //$("label[for=Farmaco_modalitaFornitura]").html($("label[for=Farmaco_modalitaFornitura]").html().replace("Modalità di fornitura","Copertura oneri finanziari"));
                //$("#legendaFarmaco").html($("#legendaFarmaco").html().replace("Modalità di fornitura","Copertura oneri finanziari"));

                $('#Farmaco-Farmaco_categoria').parent().hide();
                $('#Farmaco_categoria-select').val(null).trigger('change');
                $('#Farmaco-Farmaco_formaFarm').parent().hide();
                $('#Farmaco_formaFarm').val('');
                $('#Farmaco-Farmaco_costo').parent().hide();// NASCONDO SEMPRE
                $('#Farmaco_costo').val('');
                $('#Farmaco-Farmaco_totaleValore').parent().hide();// NASCONDO SEMPRE
                $('#Farmaco_totaleValore').val('');
                $('#Farmaco-Farmaco_numUnitaPaz').parent().hide();// NASCONDO SEMPRE
                $('#Farmaco_numUnitaPaz').val('');
                $('#Farmaco-Farmaco_unitaMisura').parent().hide();// NASCONDO SEMPRE
                $('#Farmaco_unitaMisura').val('');
                $('#Farmaco-Farmaco_AIC').parent().hide();
                $('[name=Farmaco_AIC]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_princAtt').parent().hide();
                $('#Farmaco_princAtt').tokenInput("clear");
                $('#Farmaco-Farmaco_princAttAltro').parent().hide();
                $('#Farmaco_princAttAltro').val('');
                $('#Farmaco-Farmaco_CodiceATC').parent().hide();
                $('#Farmaco_CodiceATC').val('');
                $('#Farmaco-Farmaco_MarchioCE').parent().show();
                $('#Farmaco-Farmaco_DittaProduttriceDisp').parent().show();
                $('#Farmaco-Farmaco_numeroRepertorioDisp').parent().show();
                $('#Farmaco-Farmaco_classificCNDdisp').parent().show();
                $('#Farmaco-Farmaco_descrCNDdisp').parent().show();
                $('#Farmaco-Farmaco_IndicazioniDisp').parent().show();
                $('#Farmaco-Farmaco_TessutoAnimaleDisp').parent().show();
                $('#Farmaco-Farmaco_IncorporaMedicinaleDisp').parent().show();
                $('#Farmaco-Farmaco_classeDiRischioDisp').parent().show();
                $('#Farmaco-Farmaco_ImpiegoDestUso').parent().show();
                $('#Farmaco-Farmaco_GaraFornituraDisp').parent().show();
                $('#Farmaco-Farmaco_PrezzoFornituraDisp').parent().show();
                $('#Farmaco-Farmaco_ImpiantabileDisp').parent().show();
                $('#Farmaco-Farmaco_SedeImpiantoDisp').parent().show();
                $('#Farmaco-Farmaco_categoriaDisp').parent().show();
                $('#Farmaco-Farmaco_dispMed').parent().show();
                $('#Farmaco-Farmaco_dispMedAltro').parent().show();
                $("div[id$='Attr']").parent().hide();
                $("input[id$='Attr'][type=radio]").attr('checked', false).trigger('change');
                $("input[id$='Attr'][type=text]").val('');
                $("div[id$='Mat']").parent().hide();
                $("input[id$='Mat'][type=radio]").attr('checked', false).trigger('change');
                $("input[id$='Mat'][type=text]").val('');
                $("div[id$='MatAltro']").parent().hide();
                $("#Farmaco_descrizioneMatAltro").val("")
                break;
            case "3":
                $("div[id$='Attr']").parent().show();
                $('#Farmaco-Farmaco_categoria').parent().hide();
                $('#Farmaco_categoria-select').val(null).trigger('change');
                $('#Farmaco-Farmaco_formaFarm').parent().hide();
                $('#Farmaco_formaFarm').val('');
                $('#Farmaco-Farmaco_costo').parent().hide();// NASCONDO SEMPRE
                $('#Farmaco_costo').val('');
                $('#Farmaco-Farmaco_totaleValore').parent().hide();// NASCONDO SEMPRE
                $('#Farmaco_totaleValore').val('');
                $('#Farmaco-Farmaco_numUnitaPaz').parent().hide();// NASCONDO SEMPRE
                $('#Farmaco_numUnitaPaz').val('');
                $('#Farmaco-Farmaco_unitaMisura').parent().hide();// NASCONDO SEMPRE
                $('#Farmaco_unitaMisura').val('');
                $('#Farmaco-Farmaco_AIC').parent().hide();
                $('[name=Farmaco_AIC]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_princAtt').parent().hide();
                $('#Farmaco_princAtt').tokenInput("clear");
                $('#Farmaco-Farmaco_princAttAltro').parent().hide();
                $('#Farmaco_princAttAltro').val('');
                $('#Farmaco-Farmaco_CodiceATC').parent().hide();
                $('#Farmaco_CodiceATC').val('');
                $('#Farmaco-Farmaco_MarchioCE').parent().hide();
                $('[name=Farmaco_MarchioCE]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_DittaProduttriceDisp').parent().hide();
                $('#Farmaco-Farmaco_numeroRepertorioDisp').parent().hide();
                $('#Farmaco-Farmaco_descrCNDdisp').parent().hide();
                $('#Farmaco-Farmaco_IndicazioniDisp').parent().hide();
                $('#Farmaco-Farmaco_IndicazioniDisp').val('');
                $('#Farmaco-Farmaco_classeDiRischioDisp').parent().hide();
                $('#Farmaco-Farmaco_categoriaDisp').parent().hide();
                $('#Farmaco_DittaProduttriceDisp').val('');
                $('#Farmaco_numeroRepertorioDisp').val('');
                $('#Farmaco-Farmaco_classificCNDdisp').parent().hide();
                $('#Farmaco_classificCNDdisp').val('');
                $('#Farmaco_descrCNDdisp').val('');
                $('#Farmaco-Farmaco_TessutoAnimaleDisp').parent().hide();
                $('[name=Farmaco_TessutoAnimaleDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_IncorporaMedicinaleDisp').parent().hide();
                $('[name=Farmaco_IncorporaMedicinaleDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_MedicinaleUnitoDisp').parent().hide();
                $('[name=Farmaco_MedicinaleUnitoDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_MedicinaleAccessioriDisp').parent().hide();
                $('[name=Farmaco_MedicinaleAccessioriDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_MedicinaleSintesiDisp').parent().hide();
                $('#Farmaco_MedicinaleSintesiDisp').val('');
                $('[name=Farmaco_classeDiRischioDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_ImpiegoDestUso').parent().hide();
                $('[name=Farmaco_ImpiegoDestUso]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_GaraFornituraDisp').parent().hide();
                $('#Farmaco_GaraFornituraDisp').val('');
                $('[name=Farmaco_GaraFornituraDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_PrezzoFornituraDisp').parent().hide();
                $('#Farmaco-Farmaco_ImpiantabileDisp').parent().hide();
                $('[name=Farmaco_ImpiantabileDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_SedeImpiantoDisp').parent().hide();
                $('#Farmaco_SedeImpiantoDisp').val('');
                $('#Farmaco-Farmaco_categoriaDisp').parent().hide();
                $('#Farmaco_categoriaDisp-select').val(null).trigger('change');
                $('#Farmaco-Farmaco_dispMed').parent().hide();
                $('#Farmaco_dispMed').tokenInput("clear");
                $('#Farmaco-Farmaco_dispMedAltro').parent().hide();
                $('#Farmaco_dispMedAltro').val('');
                $("div[id$='Mat']").parent().hide();
                $("input[id$='Mat'][type=radio]").attr('checked', false).trigger('change');
                $("input[id$='Mat'][type=text]").val('');
                $("div[id$='MatAltro']").parent().hide();
                $("#Farmaco_descrizioneMatAltro").val("");
                break;
            case "4":
                $("div[id$='Mat']").parent().show();
                $('#Farmaco-Farmaco_categoria').parent().hide();
                $('#Farmaco_categoria-select').val(null).trigger('change');
                $('#Farmaco-Farmaco_formaFarm').parent().hide();
                $('#Farmaco_formaFarm').val('');
                $('#Farmaco-Farmaco_costo').parent().hide();// NASCONDO SEMPRE
                $('#Farmaco_costo').val('');
                $('#Farmaco-Farmaco_totaleValore').parent().hide();// NASCONDO SEMPRE
                $('#Farmaco_totaleValore').val('');
                $('#Farmaco-Farmaco_numUnitaPaz').parent().hide();// NASCONDO SEMPRE
                $('#Farmaco_numUnitaPaz').val('');
                $('#Farmaco-Farmaco_unitaMisura').parent().hide();// NASCONDO SEMPRE
                $('#Farmaco_unitaMisura').val('');
                $('#Farmaco-Farmaco_AIC').parent().hide();
                $('[name=Farmaco_AIC]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_princAtt').parent().hide();
                $('#Farmaco_princAtt').tokenInput("clear");
                $('#Farmaco-Farmaco_princAttAltro').parent().hide();
                $('#Farmaco_princAttAltro').val('');
                $('#Farmaco-Farmaco_CodiceATC').parent().hide();
                $('#Farmaco_CodiceATC').val('');
                $('#Farmaco-Farmaco_MarchioCE').parent().hide();
                $('[name=Farmaco_MarchioCE]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_DittaProduttriceDisp').parent().hide();
                $('#Farmaco-Farmaco_numeroRepertorioDisp').parent().hide();
                $('#Farmaco-Farmaco_descrCNDdisp').parent().hide();
                $('#Farmaco-Farmaco_IndicazioniDisp').parent().hide();
                $('#Farmaco-Farmaco_IndicazioniDisp').val('');
                $('#Farmaco-Farmaco_classeDiRischioDisp').parent().hide();
                $('#Farmaco-Farmaco_categoriaDisp').parent().hide();
                $('#Farmaco_DittaProduttriceDisp').val('');
                $('#Farmaco_numeroRepertorioDisp').val('');
                $('#Farmaco-Farmaco_classificCNDdisp').parent().hide();
                $('#Farmaco_classificCNDdisp').val('');
                $('#Farmaco_descrCNDdisp').val('');
                $('#Farmaco-Farmaco_TessutoAnimaleDisp').parent().hide();
                $('[name=Farmaco_TessutoAnimaleDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_IncorporaMedicinaleDisp').parent().hide();
                $('[name=Farmaco_IncorporaMedicinaleDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_MedicinaleUnitoDisp').parent().hide();
                $('[name=Farmaco_MedicinaleUnitoDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_MedicinaleAccessioriDisp').parent().hide();
                $('[name=Farmaco_MedicinaleAccessioriDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_MedicinaleSintesiDisp').parent().hide();
                $('#Farmaco_MedicinaleSintesiDisp').val('');
                $('[name=Farmaco_classeDiRischioDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_ImpiegoDestUso').parent().hide();
                $('[name=Farmaco_ImpiegoDestUso]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_GaraFornituraDisp').parent().hide();
                $('#Farmaco_GaraFornituraDisp').val('');
                $('[name=Farmaco_GaraFornituraDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_PrezzoFornituraDisp').parent().hide();
                $('#Farmaco-Farmaco_ImpiantabileDisp').parent().hide();
                $('[name=Farmaco_ImpiantabileDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_SedeImpiantoDisp').parent().hide();
                $('#Farmaco_SedeImpiantoDisp').val('');
                $('#Farmaco-Farmaco_categoriaDisp').parent().hide();
                $('#Farmaco_categoriaDisp-select').val(null).trigger('change');
                $('#Farmaco-Farmaco_dispMed').parent().hide();
                $('#Farmaco_dispMed').tokenInput("clear");
                $('#Farmaco-Farmaco_dispMedAltro').parent().hide();
                $('#Farmaco_dispMedAltro').val('');
                $("div[id$='Attr']").parent().hide();
                $("input[id$='Attr'][type=radio]").attr('checked', false).trigger('change');
                $("input[id$='Attr'][type=text]").val('');
                $("div[id$='MatAltro']").parent().hide();
                $("#Farmaco_descrizioneMatAltro").val("");
                break;
            case "5":
                $("div[id$='MatAltro']").parent().show();
                $('#Farmaco-Farmaco_categoria').parent().hide();
                $('#Farmaco_categoria-select').val(null).trigger('change');
                $('#Farmaco-Farmaco_formaFarm').parent().hide();
                $('#Farmaco_formaFarm').val('');
                $('#Farmaco-Farmaco_costo').parent().hide();// NASCONDO SEMPRE
                $('#Farmaco_costo').val('');
                $('#Farmaco-Farmaco_totaleValore').parent().hide();// NASCONDO SEMPRE
                $('#Farmaco_totaleValore').val('');
                $('#Farmaco-Farmaco_numUnitaPaz').parent().hide();// NASCONDO SEMPRE
                $('#Farmaco_numUnitaPaz').val('');
                $('#Farmaco-Farmaco_unitaMisura').parent().hide();// NASCONDO SEMPRE
                $('#Farmaco_unitaMisura').val('');
                $('#Farmaco-Farmaco_AIC').parent().hide();
                $('[name=Farmaco_AIC]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_princAtt').parent().hide();
                $('#Farmaco_princAtt').tokenInput("clear");
                $('#Farmaco-Farmaco_princAttAltro').parent().hide();
                $('#Farmaco_princAttAltro').val('');
                $('#Farmaco-Farmaco_CodiceATC').parent().hide();
                $('#Farmaco_CodiceATC').val('');
                $('#Farmaco-Farmaco_MarchioCE').parent().hide();
                $('[name=Farmaco_MarchioCE]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_DittaProduttriceDisp').parent().hide();
                $('#Farmaco-Farmaco_numeroRepertorioDisp').parent().hide();
                $('#Farmaco-Farmaco_descrCNDdisp').parent().hide();
                $('#Farmaco-Farmaco_classeDiRischioDisp').parent().hide();
                $('#Farmaco-Farmaco_categoriaDisp').parent().hide();
                $('#Farmaco-Farmaco_IndicazioniDisp').parent().hide();
                $('#Farmaco-Farmaco_IndicazioniDisp').val('');
                $('#Farmaco_DittaProduttriceDisp').val('');
                $('#Farmaco_numeroRepertorioDisp').val('');
                $('#Farmaco-Farmaco_classificCNDdisp').parent().hide();
                $('#Farmaco_classificCNDdisp').val('');
                $('#Farmaco_descrCNDdisp').val('');
                $('#Farmaco-Farmaco_TessutoAnimaleDisp').parent().hide();
                $('[name=Farmaco_TessutoAnimaleDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_IncorporaMedicinaleDisp').parent().hide();
                $('[name=Farmaco_IncorporaMedicinaleDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_MedicinaleUnitoDisp').parent().hide();
                $('[name=Farmaco_MedicinaleUnitoDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_MedicinaleAccessioriDisp').parent().hide();
                $('[name=Farmaco_MedicinaleAccessioriDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_MedicinaleSintesiDisp').parent().hide();
                $('#Farmaco_MedicinaleSintesiDisp').val('');
                $('[name=Farmaco_classeDiRischioDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_ImpiegoDestUso').parent().hide();
                $('[name=Farmaco_ImpiegoDestUso]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_GaraFornituraDisp').parent().hide();
                $('#Farmaco_GaraFornituraDisp').val('');
                $('[name=Farmaco_GaraFornituraDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_PrezzoFornituraDisp').parent().hide();
                $('#Farmaco-Farmaco_ImpiantabileDisp').parent().hide();
                $('[name=Farmaco_ImpiantabileDisp]').attr('checked', false).trigger('change');
                $('#Farmaco-Farmaco_SedeImpiantoDisp').parent().hide();
                $('#Farmaco_SedeImpiantoDisp').val('');
                $('#Farmaco-Farmaco_categoriaDisp').parent().hide();
                $('#Farmaco_categoriaDisp-select').val(null).trigger('change');
                $('#Farmaco-Farmaco_dispMed').parent().hide();
                $('#Farmaco_dispMed').tokenInput("clear");
                $('#Farmaco-Farmaco_dispMedAltro').parent().hide();
                $('#Farmaco_dispMedAltro').val('');
                $("div[id$='Attr']").parent().hide();
                $("input[id$='Attr'][type=radio]").attr('checked', false).trigger('change');
                $("input[id$='Attr'][type=text]").val('');
                break;
        }
    });
    $('#Farmaco_categoria-select').change(function(){
        var valore=$('#Farmaco_categoria-select').val().split('###')[0];
        if(valore=="1"){
            $('#Farmaco-Farmaco_testOcomparatore').parent().show();
        }
        else{
            $('#Farmaco-Farmaco_testOcomparatore').parent().hide();
            $('[name=Farmaco_testOcomparatore]').attr('checked', false).trigger('change');
        }
    });
    $('[name=Farmaco_AIC]').change(function(){
        var valore=$('[name=Farmaco_AIC]:checked').val();
        if(valore=="1###Si"){
            $('#Farmaco-Farmaco_SpecialitaAIC').parent().show();
            $('#Farmaco-Farmaco_CodiceAIC').parent().show();
            $('#Farmaco-Farmaco_ConfezioneAIC').parent().show();
        }
        else{
            $('#Farmaco-Farmaco_SpecialitaAIC').parent().hide();
            $('#Farmaco_SpecialitaAIC').val('');
            $('#Farmaco-Farmaco_CodiceAIC').parent().hide();
            $('#Farmaco_CodiceAIC').val('');
            $('#Farmaco-Farmaco_ConfezioneAIC').parent().hide();
            $('#Farmaco_ConfezioneAIC').val('');
        }
    });
});




	$('[id=Farmaco_MarchioCE]').change(function () {
    var valore = $('[name=Farmaco_MarchioCE]:checked').val();
    if (valore ==='1###Si') {
		console.log ('si');
		$('#Farmaco-Farmaco_numeroRepertorioDisp').show();
		$('#Farmaco-Farmaco_classificCNDdisp').show();
		$('#Farmaco-Farmaco_descrCNDdisp').show();
        $('#Farmaco-Farmaco_IndicazioniDisp').parent().show();
    } 
	else {
		$('#Farmaco-Farmaco_numeroRepertorioDisp').hide();
		$('[id=Farmaco_numeroRepertorioDisp]').val('');//se nascondo sbianco il valore!
		$('#Farmaco-Farmaco_classificCNDdisp').hide();
		$('[id=Farmaco_classificCNDdisp]').val('');//se nascondo sbianco il valore!
		$('#Farmaco-Farmaco_descrCNDdisp').hide();
		$('[id=Farmaco_descrCNDdisp]').val('');//se nascondo sbianco il valore!
        $('#Farmaco-Farmaco_IndicazioniDisp').parent().hide();
        $('[id=Farmaco_IndicazioniDisp]').val('');//se nascondo sbianco il valore!
		console.log ('no o undefined');
    }
    });

    $('[id=Farmaco_IncorporaMedicinaleDisp]').change(function () {
        var valore = $('[name=Farmaco_IncorporaMedicinaleDisp]:checked').val();
        if (valore ==='1###Si') {
            $('#Farmaco-Farmaco_MedicinaleUnitoDisp').parent().show();
            $('#Farmaco-Farmaco_MedicinaleAccessioriDisp').parent().show();
            $('#Farmaco-Farmaco_MedicinaleSintesiDisp').parent().show();

    }
        else {
            $('#Farmaco-Farmaco_MedicinaleUnitoDisp').parent().hide();
            $('[name=Farmaco_MedicinaleUnitoDisp]').attr('checked', false).trigger('change');
            $('#Farmaco-Farmaco_MedicinaleAccessioriDisp').parent().hide();
            $('[name=Farmaco_MedicinaleAccessioriDisp]').attr('checked', false).trigger('change');
            $('#Farmaco-Farmaco_MedicinaleSintesiDisp').parent().hide();
            $('#Farmaco_MedicinaleSintesiDisp').val('');
        }
    });





    $('#farmaco-form-submit').closest('.btn').click(function(){
    var formData=new FormData($('#document-form')[0]);
    var actionUrl=$('#document-form').attr("action");
    if ($('#Farmaco_tipo').val()==""){
        console.log("controllo campo obbligatorio Farmaco_tipo di tipo SELECT");
        alert("Il campo Tipo deve essere compilato");
        $('#Farmaco_tipo').focus();
        return false;
    }
    if($('#Farmaco_tipo').val()=="1###Farmaco" || $('#Farmaco_tipo').val()=="4###Parafarmaco" || $('#Farmaco_tipo').val()=="5###Nutraceutica"){
        if ($('#Farmaco_categoria').val()==""){
        console.log("controllo campo obbligatorio Farmaco_categoria di tipo SELECT");
        alert("Il campo Categoria deve essere compilato");
        $('#Farmaco_categoria').focus();
        return false;
        }
        else{
            if ($('#Farmaco_categoria').val()=="1###IMP" && !$('[name=Farmaco_testOcomparatore]').is(':checked')){
                console.log("controllo campo obbligatorio Farmaco_testOcomparatore di tipo RADIO");
                alert("Il campo Specificare se Test o Comparatore deve essere compilato");
                $('#Farmaco_testOcomparatore').focus();
                return false;
            }
        }
        if ( !$('[name=Farmaco_AIC]').is(':checked')){
            console.log("controllo campo obbligatorio Farmaco_AIC di tipo RADIO");
            alert("Il campo Il farmaco è in commercio per altre indicazioni in Italia? deve essere compilato");
            $('#Farmaco_AIC').focus();
            return false;
        }
        if ($('#Farmaco_princAtt').val()==""){
            console.log("controllo campo obbligatorio Farmaco_princAtt di tipo EXT_DICTIONARY");
            alert("Il campo Principio attivo in studio deve essere compilato");
            $('#Farmaco_princAtt').focus();
            return false;
        }
        else if($('#Farmaco_princAtt').val()=="-9999###Non disponibile" && $('#Farmaco_princAttAltro').val()==""){
            console.log("controllo campo obbligatorio Farmaco_princAttAltro di tipo EXT_DICTIONARY");
            alert("Il campo Altro Principio attivo deve essere compilato");
            $('#Farmaco_princAttAltro').focus();
            return false;
        }
    }
    else if($('#Farmaco_tipo').val()=="2###Dispositivo medico"){
        if ($('#Farmaco_MarchioCE:checked').val()===undefined || $('#Farmaco_MarchioCE:checked').val()==""){
            console.log("controllo campo obbligatorio Farmaco_MarchioCE di tipo RADIO");
            alert("Il campo Presenza del marcio CE deve essere compilato");
            $('#Farmaco_MarchioCE').focus();
            return false;
        }

        if ($('#Farmaco_categoriaDisp').val()==""){
            console.log("controllo campo obbligatorio Farmaco_categoriaDisp di tipo SELECT");
            alert("Il campo Categoria deve essere compilato");
            $('#Farmaco_categoriaDisp').focus();
            return false;
        }
        if ($('#Farmaco_dispMed').val()==""){
            console.log("controllo campo obbligatorio Farmaco_dispMed di tipo EXT_DICTIONARY");
            alert("Il campo Dispositivo medico in studio deve essere compilato");
            $('#Farmaco_dispMed').focus();
            return false;
        }
        else if($('#Farmaco_dispMed').val()=="-9999###Non disponibile" && $('#Farmaco_dispMedAltro').val()==""){
            console.log("controllo campo obbligatorio Farmaco_dispMedAltro di tipo EXT_DICTIONARY");
            alert("Il campo Altro dispositivo medico in studio deve essere compilato");
            $('#Farmaco_dispMedAltro').focus();
            return false;
        }
        if ($('#Farmaco_DittaProduttriceDisp').val()==""){
            console.log("controllo campo obbligatorio Farmaco_DittaProduttriceDisp di tipo TEXTBOX");
            alert("Il campo Ditta produttrice deve essere compilato");
            $('#Farmaco_DittaProduttriceDisp').focus();
            return false;
        }
        /* if ($('#Farmaco_classificCNDdisp').val()==""){
            console.log("controllo campo obbligatorio Farmaco_classificCNDdisp di tipo TEXTBOX");
            alert("Il campo Classificazione CND deve essere compilato");
            $('#Farmaco_classificCNDdisp').focus();
            return false;
        }
        if ($('#Farmaco_descrCNDdisp').val()==""){
            console.log("controllo campo obbligatorio Farmaco_descrCNDdisp di tipo TEXTBOX");
            alert("Il campo Descrizione CND deve essere compilato");
            $('#Farmaco_descrCNDdisp').focus();
            return false;
        } */
        if ($('input[name=Farmaco_classeDiRischioDisp]:checked').val()===undefined || $('input[name=Farmaco_classeDiRischioDisp]:checked').val()==""){
            console.log("controllo campo obbligatorio Farmaco_descrCNDdisp di tipo RADIO");
            alert("Il campo Classe di rischio deve essere compilato");
            $('#Farmaco_descrCNDdisp').focus();
            return false;
        }

        if ($('#Farmaco_TessutoAnimaleDisp:checked').val()===undefined || $('#Farmaco_TessutoAnimaleDisp:checked').val()==""){
            console.log("controllo campo obbligatorio Farmaco_TessutoAnimaleDisp di tipo RADIO");
            alert("Il campo 'Il dispositivo presenta tessuto animale a rischio di trasmissione di encefalopatia spongiforme (TSE)?' deve essere compilato");
            $('#Farmaco_TessutoAnimaleDisp').focus();
            return false;
        }
        if ($('#Farmaco_IncorporaMedicinaleDisp:checked').val()===undefined || $('#Farmaco_IncorporaMedicinaleDisp:checked').val()==""){
            console.log("controllo campo obbligatorio Farmaco_IncorporaMedicinaleDisp di tipo RADIO");
            alert("Il campo 'Il dispositivo incorpora un medicinale?' deve essere compilato");
            $('#Farmaco_IncorporaMedicinaleDisp').focus();
            return false;
        }

    }
    loadingScreen("Salvataggio in corso...", "${baseUrl}/int/images/loading.gif");
    $.ajax({
        type: "POST",
        url: actionUrl,
        contentType:false,
        processData:false,
        async:false,
        cache:false,
        data: formData,
        success: function(obj){
            if (obj.result=="OK") {
                loadingScreen("Salvataggio effettuato", "${baseUrl}/int/images/green_check.jpg",2000);
                if (obj.redirect){
                    //alert('redirect?');
                    window.location.href='${baseUrl}/app/documents/detail/${model['parent'].getId()}<#if model['docDefinition'].hashBack?? >#${model['docDefinition'].hashBack}</#if>';
                }
            }else {
                bootbox.hideAll();
                var errorMessage="Errore salvataggio!  <i class='icon-warning-sign red'></i>";
                if(obj.errorMessage.includes("RegexpCheckFailed: ")){
                    var campoLabel="";
                    campoLabel=obj.errorMessage.replace("RegexpCheckFailed: ","");
                    campoLabel=messages[campoLabel];
                    errorMessage="Errore nella validazione del campo:<br/>"+campoLabel;
                }
                bootbox.alert(errorMessage);
                //loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
            }
        },
        error: function(){
            loadingScreen("Errore salvataggio!", "${baseUrl}/int/images/alerta.gif", 3000);
            }
        });
    });

function valueOfField(idField){
    console.log("valueOfField - "+idField);
    console.log(idField);
    field=$('#'+idField);
    if (field.attr('istokeninput')=='true'){
    value=field.tokenInput("get");
    console.log(value);
    if (value.length>0)
        return value[0].id;
        else return "";
    }
    if (field.attr('type')=='radio'){
        return $('#'+idField+':checked').attr('title');
    }else if (field.prop('tagName')=='SELECT'){
        return field.find('option:selected').val();
    }else {
        return field.val();
    }
}


</@script>
<div class="mainContent">

    <form class="form-horizontal" id="document-form" method="POST" action="${baseUrl}/app/rest/documents/save/${model['docDefinition'].id}" onsubmit="return false;" enctype="multipart/form-data">
        <h2><@msg "type.create."+model['docDefinition'].typeId/></h2>
        <#if model['parentId']??>
        <@hidden "parentId" "parentId" model['parentId']/>
    </#if>
    <#assign type=model['docDefinition']/>
    <#if type.associatedTemplates?? && type.associatedTemplates?size gt 0>
    <#list type.associatedTemplates as assocTemplate>
    <#assign templatePolicy=assocTemplate.getUserPolicy(userDetails, type)/>
    <#if assocTemplate.enabled && templatePolicy.canCreate>
    <#assign template=assocTemplate.metadataTemplate/>
    <#if template.fields??>
    <#list template.fields as field>
    <div class="form-group field-component field-editable" id="file_data">
        <@mdfield template field/>
    </div>
</#list>
</#if>

</#if>
</#list>
</#if>

<#if model['docDefinition'].hasFileAttached>
<#if !model['docDefinition'].noFileinfo>
<#--
Modifica versioning per CTC gemelli CRPMS-156

<div class="form-group field-component field-editable" id="file_version">
    <label class="col-sm-3 control-label no-padding-right" for="version">Versione<sup style="color:red">*</sup>:</label>
    <div class="col-sm-9">
        <input type="text" name="version" id="version"/>
    </div>
</div>
-->
<input type="hidden" name="version" value="auto"/>
<div class="form-group field-component field-editable" id="file_data">
    <label class="col-sm-3 control-label no-padding-right" for="data">Data<sup style="color:red">*</sup>:</label>
    <div class="col-sm-9">
        <input type="text" name="data" class="datePicker" id="data"/>
        <@script>
        $('#data').datepicker({autoclose:true, format: 'dd/mm/yyyy' });
    </@script>
</div>
</div>
<div class="form-group field-component field-editable" id="file_autore">
    <label class="col-sm-3 control-label no-padding-right" for="autore">Autore:</label>
    <div class="col-sm-9">
        <input type="text" name="autore" id="autore"/>
    </div>
</div>
<div class="form-group field-component field-editable" id="file_node">
    <label class="col-sm-3 control-label no-padding-right" for="note">Note:</label>
    <div class="col-sm-9">
        <textarea name="note" id="note"></textarea>
    </div>
</div>
</#if>
<div class="form-group field-component field-editable">
    <@fileChooser "file" "file" getLabel(model['docDefinition'].typeId+".fileLabel")+"<sup style='color:red'>*</sup>"/>
</div>
</#if>
<div class="clearfix"></div>
<button class="btn btn-warning submitButton" id="farmaco-form-submit" name="farmaco-form-submit"><i class="icon-save bigger-160"></i><b>Salva</b></span>
</button>

</form>
<#-- assign legendaFarmaco=true>
<#include "../helpers/legenda.ftl"/ -->
<#include "../helpers/sfogliaFarmaciDialog.ftl"/>
</div>

