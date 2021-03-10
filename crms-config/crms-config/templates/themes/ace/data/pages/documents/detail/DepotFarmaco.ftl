<#assign type=model['docDefinition']/>
<#global page={
"content": path.pages+"/"+mainContent,
"styles" : ["jquery-ui-full","datetimepicker","pages/studio.css","x-editable","select2","jqgrid"],
"scripts" : ["xCDM-modal","jquery-ui-full","datetimepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable","select2","base","jqgrid","pages/home.js"],
"inline_scripts":[],
"title" : "Gestione Farmaco",
"description" : "Gestione Farmaco"
} />
<@breadcrumbsData el />
<#assign elStudio=el.getParent().getParent() />
<#include "../../partials/navigation/navigazione_studio.ftl">
<#assign json=el.type.getDummyJson() />
<#assign loadedJson=el.getElementCoreJsonToString(userDetails) />
<@script>
$.ajaxSetup({async : false });
myDepotFarmaco=${loadedJson};
var sidebarDefault="${el.getParent().getId()}#DepotFarmacia-tab2";

var initFormAction=function(object){
    var form=object.getForm();
    $(".radio").addClass("left");
    $("div[data-field-ref=depotFarmaco_DepotChiuso]").hide();
    $("div[data-field-ref=depotFarmaco_tipo]").hide();
    if($("input[name=depotFarmaco_tipo]").val()=="2"){
        $("div[data-field-ref=depotFarmaco_formaFarm]").hide();
        $("div[data-field-ref=depotFarmaco_dosaggio]").hide();
        $("div[data-field-ref=depotFarmaco_modalitaPreparazione]").hide();
    }
}

var compilationChecks=function(object){
    var form=object.getForm();
    return true;
}

var farmacoModalEngine;
var farmacoCaricoModalEngine;
var farmacoLottoModalEngine;
var farmacoScaricoModalEngine;

function farmacoSaveCallBack(object){
    return true;
}


var gestioneChiusa=function(){return false;}
$(document).ready(function(){
    if(myDepotFarmaco.metadata.depotFarmaco_DepotChiuso!== undefined && myDepotFarmaco.metadata.depotFarmaco_DepotChiuso.length>0 && myDepotFarmaco.metadata.depotFarmaco_DepotChiuso[0]==1){
        $("#chiudiGestioneButton").hide();
        $("#ScaricoButton").hide();
        $("#CaricoButton").hide();
        gestioneChiusa=function(){return true;}
    }
    carichiList('${el.id}')
    scarichiList('${el.id}');
    farmacoModalEngine=new xCDM_Modal(baseUrl, 'DepotFarmaco', initFormAction, compilationChecks, farmacoSaveCallBack,null,null,gestioneChiusa);
    farmacoCaricoModalEngine=new xCDM_Modal(baseUrl, 'DepotFarmacoCarico', initFarmacoCaricoFormAction, farmacoCaricoChecks, farmacoCaricoSaveCallBack,null,null,gestioneChiusa);
    farmacoLottoModalEngine=new xCDM_Modal(baseUrl, 'DepotFarmacoLotto', initFarmacoLottoFormAction, farmacoLottoChecks, farmacoLottoSaveCallBack,null,null,gestioneChiusa);
    farmacoScaricoModalEngine=new xCDM_Modal(baseUrl, 'DepotFarmacoScarico', initFarmacoScaricoFormAction, farmacoScaricoChecks, farmacoScaricoSaveCallBack,null,null,gestioneChiusa);
    farmacoBarcodeModalEngine=new xCDM_Modal(baseUrl, 'DepotFarmacoBarcode', initFarmacoBarcodeFormAction, farmacoBarcodeChecks, farmacoBarcodeSaveCallBack,null,null,gestioneChiusa);
});

var initFarmacoCaricoFormAction=function(object){
    var form=object.getForm();
    $(".radio").addClass("left");
    $("select[name=depotFarmacoCarico_packaging]").change(function(){
        if($(this).val()=="2###Kit"){
            $("select[name=depotFarmacoCarico_modalitaDistribuzione]").select2('val', '');
            $("select[name=depotFarmacoCarico_modalitaDistribuzione]").find('option:nth-child(2)').prop("disabled",true);
        }
        else{
            $("select[name=depotFarmacoCarico_modalitaDistribuzione]").select2('val', '');
            $("select[name=depotFarmacoCarico_modalitaDistribuzione]").find('option:nth-child(2)').prop("disabled",false);
        }
    });
    if($("select[name=depotFarmacoCarico_packaging]").val()=="2###Kit"){
        $("select[name=depotFarmacoCarico_modalitaDistribuzione]").find('option:nth-child(2)').prop("disabled",true);
    }
    $("input[name=depotFarmacoCarico_conforme]").change(function(){
        if($("input[name=depotFarmacoCarico_conforme]:checked").val()=="2###No"){
            $("div[data-field-ref=depotFarmacoCarico_unitaNonConformi]").show();
        }
        else{
            $("div[data-field-ref=depotFarmacoCarico_unitaNonConformi]").hide();
            $("div[name=depotFarmacoCarico_unitaNonConformi]").val("");
        }
    });
    $("input[name=depotFarmacoCarico_conforme]").trigger("change");
}

var initFarmacoLottoFormAction=function(object){
    var form=object.getForm();
    $(".radio").addClass("left");
    /*CALCOLO QUANTITA' MAX PER LOTTO*/
    my_parentId=form.find('input[name="parentId"]').val();
    my_id=parseInt(form.attr("elementid"));
    var quantitaPackagingMassima=0;
    var quantitaPerLottoCaricata=0;
    var quantitaPerLottoCaricabile=0;
    $.getJSON(baseUrl + '/app/rest/documents/getElementJSON/' + my_parentId, function (carico) {
        quantitaPackagingMassima=parseInt(carico.metadata.depotFarmacoCarico_quantitaPackaging[0]);
        //console.log(carico.children);
        $.each(carico.children,function(key,lotto){
            if(lotto.id!=my_id){
                quantitaPerLottoCaricata+=parseInt(lotto.metadata.depotFarmacoLotto_quantitaPerLotto[0]);
            }
        });
        quantitaPerLottoCaricabile=parseInt(quantitaPackagingMassima)-parseInt(quantitaPerLottoCaricata);
        var inputMassima=$("<input>");
        inputMassima.attr("type","hidden");
        inputMassima.attr("name","quantitaPerLottoCaricabile");
        inputMassima.attr("value",quantitaPerLottoCaricabile);
        form.append(inputMassima);
    });
}

var initFarmacoScaricoFormAction=function(object){
    var form=object.getForm();
    $(".radio").addClass("left");
    if($("select[name=depotFarmacoScarico_causale]").val()=="-9999###Altro"){
        $("div[data-field-ref=depotFarmacoScarico_causaleAltro]").show();
    }
    else{
        $("input[name=depotFarmacoScarico_causaleAltro]").val("");
        $("div[data-field-ref=depotFarmacoScarico_causaleAltro]").hide();
    }

    $("select[name=depotFarmacoScarico_causale]").change(function(){
        if($(this).val()=="-9999###Altro"){
            $("div[data-field-ref=depotFarmacoScarico_causaleAltro]").show();
        }
        else{
            $("input[name=depotFarmacoScarico_causaleAltro]").val("");
            $("div[data-field-ref=depotFarmacoScarico_causaleAltro]").hide();
        }
    });
}

var initFarmacoBarcodeFormAction=function(object){
    var form=object.getForm();
    $(".radio").addClass("left");
    $("div[data-field-ref=depotFarmacoBarcode_scaricato]").hide();
}


var farmacoCaricoChecks=function(object){
    var form=object.getForm();
    return true;
}

var farmacoLottoChecks=function(object){
    var form=object.getForm();
    if(parseInt(form.find("input[name=quantitaPerLottoCaricabile]").val()) < parseInt(form.find("input[name=depotFarmacoLotto_quantitaPerLotto]").val())){
        bootbox.alert("La quantità inserita è maggiore rispetto alla quantità disponibile caricabile");
        return false;
    }
    return true;
}

var farmacoScaricoChecks=function(object){
    var form=object.getForm();
    return true;
}

var farmacoBarcodeChecks=function(object){
    var form=object.getForm();
    return true;
}

function farmacoCaricoSaveCallBack(object){
    jQuery("#DepotFarmacoCarico-grid-table").trigger('reloadGrid');
    if(lastLottoSubGridEdited!==undefined){
        jQuery("#"+lastLottoSubGridEdited).trigger('reloadGrid');
    }
}

var numeroBarcodeDaCreare=0;
var barcodeRaiseError = false;
function farmacoLottoSaveCallBack(object,data){
    var form=object.getForm();
    /*Creo figli codebar in base a modalitaDistribuzione e quantità carico*/
    my_parentId=parseInt(form.find('input[name="parentId"]').val());
    my_id=parseInt(form.attr("elementid")); //in caso di editing ho già l'id
    if(isNaN(my_id) && data && data.ret){//altrimenti se sono in fase di creazione lo prendo dal valore di ritorno della post save
        my_id=data.ret;
    }
    console.log(my_parentId);
    console.log(my_id);
    var modalitaDistribuzione="";
    var quantitaPerLottoCaricata=0;
    var quantitaPerPackaging=0;
    numeroBarcodeDaCreare=0;
    $.getJSON(baseUrl + '/app/rest/documents/getElementJSON/' + my_parentId, function (carico) {
        quantitaPerPackaging=parseInt(carico.metadata.depotFarmacoCarico_quantitaPerPackaging[0]);
        modalitaDistribuzione=carico.metadata.depotFarmacoCarico_modalitaDistribuzione[0].split('###')[0];
        $.each(carico.children,function(key,lotto){
            if(lotto.id==my_id){
                quantitaPerLottoCaricata+=parseInt(lotto.metadata.depotFarmacoLotto_quantitaPerLotto[0]);
            }
        });
        if(modalitaDistribuzione=="3"){ //Singola
            numeroBarcodeDaCreare=parseInt(quantitaPerLottoCaricata)*parseInt(quantitaPerPackaging);
        }
        else{//Kit o Confezione
            numeroBarcodeDaCreare=parseInt(quantitaPerLottoCaricata);
        }
        creaBarcode(my_id);
    });
    if(lastLottoAddedParentId!==undefined){
        jQuery("#"+lastLottoAddedParentId+" td.ui-sgcollapsed").trigger('click');
    }
    if(lastLottoSubGridEdited!==undefined){
        jQuery("#"+lastLottoSubGridEdited).trigger('reloadGrid');
    }
}

var numeroBarcodeCreati=0;
function creaBarcode(parentId){
    numeroBarcodeCreati=0;
    barcodeRaiseError=false;

    $.getJSON(baseUrl + '/app/rest/documents/getElementJSON/' + parentId, function (lotto) {
        //conto prima se ci sono già figli di tipo barcode ed eventualmente aggiungere la differenza tra barcodeDaCreare-barcodeCreati
        numeroBarcodeCreati=lotto.children.length;
        if(numeroBarcodeCreati< numeroBarcodeDaCreare){
            numeroBarcodeDaCreare-=numeroBarcodeCreati;
            numeroBarcodeCreati=0;
            if(numeroBarcodeDaCreare>0){
                for (var i=0; i< numeroBarcodeDaCreare ; i++){
                    var postUrl = baseUrl + "/app/rest/documents/save/DepotFarmacoBarcode";
                    var postData= new Object();
                    postData['parentId'] = parentId;
                    postData['depotFarmacoBarcode_scaricato'] = "0";
                    numeroBarcodeCreati++;
                    $.post(postUrl,postData).done(function (data) {
                        if (data.result != 'OK') {
                            barcodeRaiseError = true;
                        } else {
                            numeroBarcodeCreati--;
                            if(numeroBarcodeCreati==0){
                                if (barcodeRaiseError){
                                    bootbox.hideAll();
                                    bootbox.alert('Attenzione!!! Errore nel salvataggio della prestazione');
                                }
                                else {
                                    bootbox.hideAll();
                                }
                            }
                        }
                    });
                }
            }
        }
        else{
            /****** TODO: elimino dei barcode*/
        }
    });
}

function visualizzaBarcode(lottoId,stampa,scaricoId){
    var numeroLotto="";
    var barcodeDivHtml=$("<div>");
	var url="";
	var barcodeList="";
	if(lottoId=="all"){
	    url=baseUrl+'/../getBarcodeDisponibili.php?DEPOTFARMACO_ID=${el.id}';
	    $.getJSON(url, function (found) {
            if(found.KO){
                var noBarcodeDiv=$("<span>");
                noBarcodeDiv.append("Nessun barcode disponibile");
                barcodeDivHtml.append(noBarcodeDiv);
            }
            else{
                barcodeDivHtml.append("Seleziona i barcode da scaricare<br/>");
                checkDiv=$("<div>");
                checkDiv.addClass("checkbox");
                checkLabel=$("<label>");
                checkInput=$("<input>");
                checkInput.attr("name","selectAll");
                checkInput.attr("value","selectAll");
                checkInput.attr("id","selectAll");
                checkInput.addClass("ace");
                checkInput.attr("type","checkbox");
                checkInput.click( function(){
                    myCheckAll=$(this).prop("checked");
                    $("input[name^='barcode-']").each(function(){
                        $(this).prop("checked",myCheckAll);
                    });
                });
                checkText=$("<span>");
                checkText.addClass("lbl");
                checkText.html("&nbsp;<b>Seleziona Tutti</b>");
                checkLabel.append(checkInput);
                checkLabel.append(checkText);
                checkDiv.append(checkLabel);
                barcodeDivHtml.append(checkDiv);

                $.each(found,function(key,barcode){
                    checkDiv=$("<div>");
                    checkDiv.addClass("checkbox");
                    checkLabel=$("<label>");
                    checkInput=$("<input>");
                    checkInput.attr("name","barcode-"+barcode.ID);
                    checkInput.attr("value",barcode.ID);
                    checkInput.attr("id",barcode.ID);
                    checkInput.addClass("ace");
                    checkInput.attr("type","checkbox");
                    checkText=$("<span>");
                    checkText.addClass("lbl");
                    checkText.html("&nbsp;"+barcode.ID);
                    checkLabel.append(checkInput);
                    checkLabel.append(checkText);
                    checkDiv.append(checkLabel);
                    barcodeDivHtml.append(checkDiv);
                });
                /*barcodeList=$("<ul>");
                $.each(found,function(key,barcode){
                    var barcodeLi=$("<li>");
                    var barcodeHtml=$("<a>");
                    if(!stampa){
                        barcodeHtml.append("scegli quale scaricare: "+barcode.ID);
                        barcodeHtml.bind("click",function(e) {
                            scaricaBarcode(scaricoId,barcode.ID,lottoId,stampa);
                            return false;
                        });
                    }
                    barcodeLi.append(barcodeHtml);
                    barcodeList.append(barcodeLi);
                });
                barcodeDivHtml.append(barcodeList);*/
            }
            bootbox.confirm({
                title: 'Lista barcode da scaricare per lotto <b>'+numeroLotto+'</b>',
                message: barcodeDivHtml,
                callback: function(result){
                    if(result){
                        numeroBarcodeDaScaricare=$("input[name^='barcode-']:checked").length;
                        numeroBarcodeScaricati=0;
                        if(numeroBarcodeScaricati< numeroBarcodeDaScaricare){
                            if(numeroBarcodeDaScaricare>0){
                                $("input[name^='barcode-']:checked").each(function(){
                                        scaricaBarcode(scaricoId,$(this).prop("id"),lottoId,stampa);
                                });
                            }
                        }
                    }
                }
            });
        });
    }
    else{
        url=baseUrl + '/app/rest/documents/getElementJSON/' + lottoId;
        $.getJSON(url, function (lotto) {
            numeroLotto=lotto.metadata.depotFarmacoLotto_numeroLotto[0];
            barcodeList=$("<ul>");
            barcodeList.addClass("list-unstyled spaced");
            $.each(lotto.children,function(key,barcode){
                var barcodeLi=$("<li>");
                barcodeStampa=$("<a>");
                var barcodeHtml=$("<a>");
                if(stampa){
                    barcodeHtml.attr("href","#");
                    barcodeHtml.attr("target","_blank");
                    barcodeHtml.append(" "+barcode.titleString+"&nbsp;");

                    if(barcode.metadata.depotFarmacoBarcode_scaricato=="1"){
                            //barcodeHtml.css("color","red");
                            barcodeHtml.append('<span class="badge badge-danger" style="vertical-align: middle">Gi&agrave; scaricato!</span>');
                            barcodeLi.append('<i class="icon-remove bigger-110 red"></i>');
                    }
                    else{
                        barcodeLi.append('<i class="icon-ok bigger-110 green"></i>');
                    }
                }
                barcodeHtml.bind("click",function(e) {
                        farmacoBarcodeModalEngine.formByElement(barcode);
                        return false;
                });
                barcodeLi.append(barcodeHtml);
                barcodeStampa.append('<span style="padding:4px;vertical-align: middle"><i class="menu-icon fa fa-print"></i></span>');
                barcodeStampa.bind("click",function(e) {
                    alert("stampa etichetta barcode");
                    return false;
                });
                barcodeLi.append(barcodeStampa);
                barcodeList.append(barcodeLi);
            });
            barcodeDivHtml.append(barcodeList);
            bootbox.dialog({
                title: 'Lista barcode per lotto <b>'+numeroLotto+'</b>',
                message: barcodeDivHtml
            });
        });
    }
}

function farmacoScaricoSaveCallBack(object){
    jQuery("#DepotFarmacoScarico-grid-table").trigger('reloadGrid');
}

function farmacoBarcodeSaveCallBack(object){
    return true;
}


var numeroBarcodeDaScaricare=0;
var numeroBarcodeScaricati=0;
function scaricaBarcode(scaricoId,barcodeId,lottoId,stampa){
    barcodeRaiseError=false;
    var postUrl = baseUrl + "/app/rest/documents/save/DepotFarmacoScaricoDistr";
    var postData= new Object();
    postData['parentId'] = scaricoId;
    postData['depotFarmacoScaricoDistr_barcode'] = barcodeId;
    $.post(postUrl,postData).done(function (data) {
        if (data.result != 'OK') {
            bootbox.hideAll();
            bootbox.alert('Attenzione!!! Errore nello scaricamento del lotto');
        }
        else {
            var postUrl = baseUrl + "/app/rest/documents/update/" + barcodeId;
            var postData= new Object();
            postData['depotFarmacoBarcode_scaricato'] = "1";
            $.post(postUrl,postData).done(function (data) {
                if (data.result != 'OK') {
                    barcodeRaiseError = true;
                    bootbox.alert('Attenzione!!! Errore nello scaricamento del lotto');
                }
                else {
                    numeroBarcodeScaricati++;
                    if(numeroBarcodeScaricati==numeroBarcodeDaScaricare){
                        if (barcodeRaiseError){
                            bootbox.hideAll();
                            bootbox.alert('Attenzione!!! Errore nel salvataggio della prestazione');
                        }
                        else {
                            carichiLoaded=false;
                            jQuery("#DepotFarmacoCarico-grid-table").trigger('reloadGrid');
                            jQuery("#DepotFarmacoScarico-grid-table").trigger('reloadGrid');
                            bootbox.hideAll();
                            //visualizzaBarcode(lottoId,stampa,scaricoId);
                        }
                    }
                }
            });
        }
    });
}



function carichiList(DepotFarmacoId){
    var grid_selector = "#DepotFarmacoCarico-grid-table";
    var pager_selector = "#DepotFarmacoCarico-grid-pager";

    var url=baseUrl+'/app/rest/documents/jqgrid/advancedSearch/DepotFarmacoCarico?parent_obj_id_eq='+DepotFarmacoId;
    var colNames=['Riferimento D.D.T.','Packaging','Quantit&agrave; di confezioni/kit (Q di carico)','Quantit&agrave; per confezioni/kit (espressa in forma farmaceutica)','Modalit&agrave; di distribuzione','Collocazione','Azioni'];
    var colModel=[
                {name:'ddt',index:'depotFarmacoCarico_DDT',width:20,jsonmap:"metadata.depotFarmacoCarico_DDT"},
                {name:'packaging',index:'depotFarmacoCarico_packaging', width:20, sorttype:"int",formatter:getDecode, firstsortorder:"desc",jsonmap:"metadata.depotFarmacoCarico_packaging"},
                {name:'quantitaPackaging',index:'depotFarmacoCarico_quantitaPackaging',width:30,jsonmap:"metadata.depotFarmacoCarico_quantitaPackaging"},
                {name:'quantitaPerPackaging',index:'depotFarmacoCarico_quantitaPerPackaging',width:30, jsonmap:"metadata.depotFarmacoCarico_quantitaPerPackaging"},
                {name:'modalitaDistribuzione',index:'depotFarmacoCarico_modalitaDistribuzione',formatter:getDecode,  width:40,jsonmap:"metadata.depotFarmacoCarico_modalitaDistribuzione"},
                {name:'collocazione',index:'depotFarmacoCarico_collocazione', width:40,jsonmap:"metadata.depotFarmacoCarico_collocazione"},
                {name:'azioni',index:'azioni', width:120, fixed:true, sortable:false, resize:false,formatter:'actions',formatoptions:{keys:true,delbutton:false,editbutton:false}}
    ];
    var caption = "Storico carichi in magazzino";

    var sub_grid_url=baseUrl+'/app/rest/documents/jqgrid/advancedSearch/DepotFarmacoLotto?parent_obj_id_eq=_rowId_';
    var sub_grid_colNames=['Numero Lotto','Quantit&agrave; confezioni/kit per lotto','Scadenza','Azioni'];
    var sub_grid_colModel=[
        {name:'numeroLotto',index:'numeroLotto',width:10,sorttype:"string",jsonmap:"metadata.depotFarmacoLotto_numeroLotto"},
        {name:'quantitaPerLotto',index:'depotFarmacoLotto_quantitaPerLotto', width:20, sorttype:"int", firstsortorder:"desc",jsonmap:"metadata.depotFarmacoLotto_quantitaPerLotto"},
        {name:'scadenza',index:'depotFarmacoLotto_scadenza',width:30,formatter:formatDate,jsonmap:"metadata.depotFarmacoLotto_scadenza.0"},
        {name:'sub_azioni',index:'sub_azioni', width:160, fixed:true, sortable:false, resize:false,formatter:'actions',formatoptions:{keys:true,delbutton:false,editbutton:false}}
    ];
    //setupGridSubGrid(grid_selector, pager_selector, url, colModel,colNames, caption);
    setupGridSubGrid(grid_selector, pager_selector, url, colModel,colNames, caption,sub_grid_url,sub_grid_colModel,sub_grid_colNames,false);
}

function scarichiList(DepotFarmacoId){
    if(!carichiLoaded){
        (function(varlocal){
            setTimeout(function(){
                scarichiList(varlocal);
            },500);
        })(DepotFarmacoId);
        return false;
    }
    var grid_selector = "#DepotFarmacoScarico-grid-table";
    var pager_selector = "#DepotFarmacoScarico-grid-pager";

    var url=baseUrl+'/app/rest/documents/jqgrid/advancedSearch/DepotFarmacoScarico?parent_obj_id_eq='+DepotFarmacoId;
    var colNames=['Id','Causale','Delegato al ritiro','Nominativo personale che consegna il farmaco','Data di scarico','Azioni'];
    var colModel=[
        {name:'id',index:'depotFarmacoScarico_id',width:10,jsonmap:"id"},
        {name:'causale',index:'depotFarmacoScarico_causale',formatter:getDecode,width:10,jsonmap:"metadata.depotFarmacoScarico_causale"},
        {name:'delegatoAlRitiro',index:'depotFarmacoScarico_delegatoAlRitiro',width:30,jsonmap:"metadata.depotFarmacoScarico_delegatoAlRitiro"},
        {name:'farmacista',index:'depotFarmacoScarico_farmacista',width:30,jsonmap:"metadata.depotFarmacoScarico_farmacista"},
        {name:'dataScarico',index:'depotFarmacoScarico_dataScarico',width:30,formatter:formatDate,jsonmap:"metadata.depotFarmacoScarico_dataScarico.0"},
        {name:'scarico_azioni',index:'azioni', width:160, fixed:true, sortable:false, resize:false,formatter:'actions',formatoptions:{keys:true,delbutton:false,editbutton:false}}
    ];
    var caption = "Storico scarichi da magazzino";

    var sub_grid_url=baseUrl+'/app/rest/documents/jqgrid/advancedSearch/DepotFarmacoScaricoDistr?parent_obj_id_eq=_rowId_';
    var sub_grid_colNames=['Numero Barcode','Codice sponsor'];
    var sub_grid_colModel=[
        {name:'barcode',index:'depotFarmacoScaricoDistr_barcode',  width:40,jsonmap:"metadata.depotFarmacoScaricoDistr_barcode.0.titleString"},
        {name:'codicesponsor',index:'depotFarmacoScaricoDistr_codiceSponsor',  width:40,jsonmap:"metadata.depotFarmacoScaricoDistr_barcode.0.metadata.depotFarmacoBarcode_codiceSponsor"}
    ];

    setupGridSubGrid(grid_selector, pager_selector, url, colModel,colNames, caption,sub_grid_url,sub_grid_colModel,sub_grid_colNames,false);
}

var lastLottoAddedParentId=undefined;
var lastScaricoLottoAddedParentId=undefined;
var lastLottoSubGridEdited=undefined;
var carichiLoaded=false;
function updateActions(grid_selector){
    if(grid_selector=="#DepotFarmacoCarico-grid-table"){
        var iCol = getColumnIndexByName(grid_selector, 'azioni');
        $(grid_selector).find(">tbody>tr.jqgrow>td:nth-child(" + (iCol + 1) + ")").each(function () {
            var my_id = $(this).parent().prop('id');
            //AGGIUNGO SCARICA PDF CARICO
            $("<div>", {
                title: "Scarica Modulo di Carico",
                mouseover: function() {
                    $(this).addClass('ui-state-hover');
                },
                mouseout: function() {
                    $(this).removeClass('ui-state-hover');
                },
                click: function(e) {
                    location.href=baseUrl + '/app/documents/pdf/CaricoFarmaco/'+my_id;
                    return false;
                }
            })
            .css({"margin-right": "5px", float: "left", cursor: "pointer"})
            .addClass("ui-pg-div ui-inline-custom")
            .append('<span class="fa-file-pdf-o ui-icon"></span>')
            .prependTo($(this).children("div"));
            if(!gestioneChiusa()){
                //INSERISCO ACTION AGGIUNGI Lotto a CARICO
                $("<div>", {
                    title: "Aggiungi Lotto",
                    mouseover: function() {
                        $(this).addClass('ui-state-hover');
                    },
                    mouseout: function() {
                        $(this).removeClass('ui-state-hover');
                    },
                    click: function(e) {
                        farmacoLottoModalEngine.formByParentId(my_id);
                        lastLottoAddedParentId=my_id;
                        lastLottoSubGridEdited=undefined;
                        return false;
                    }
                })
                .css({"margin-right": "5px", float: "left", cursor: "pointer"})
                .addClass("ui-pg-div ui-inline-custom")
                .append('<span class="ui-icon fa-medkit"></span>')
                .prependTo($(this).children("div"));
            }
            //INSERISCO ACTION EDIT CARICO
            $("<div>", {
                    title: "Modifica",
                        mouseover: function() {
                        $(this).addClass('ui-state-hover');
                    },
                    mouseout: function() {
                        $(this).removeClass('ui-state-hover');
                    },
                    click: function(e) {
                        lastLottoAddedParentId=my_id;
                        $.getJSON(baseUrl + '/app/rest/documents/getElementJSON/' + my_id, function (farmaco) {
                            farmacoCaricoModalEngine.formByElement(farmaco);
                        });
                        return false;
                    }
            })
            .css({"margin-right": "5px", float: "left", cursor: "pointer"})
            .addClass("ui-pg-div ui-inline-custom")
            .append('<span class="ui-icon ui-icon-pencil"></span>')
            .prependTo($(this).children("div"));

        });
        if(lastLottoAddedParentId!==undefined){
            jQuery("#"+lastLottoAddedParentId+" td.ui-sgcollapsed").trigger('click');
        }
        if(!carichiLoaded){
            carichiLoaded=true;
        }
    }
    else if (grid_selector=="#DepotFarmacoScarico-grid-table"){
        var iCol = getColumnIndexByName(grid_selector, 'scarico_azioni');
        $(grid_selector).find(">tbody>tr.jqgrow>td:nth-child(" + (iCol + 1) + ")").each(function () {
            var my_id = $(this).parent().prop('id');
            //AGGIUNGO SCARICA PDF SCARICO
            $("<div>", {
                title: "Scarica Modulo di Scarico",
                mouseover: function() {
                    $(this).addClass('ui-state-hover');
                },
                mouseout: function() {
                    $(this).removeClass('ui-state-hover');
                },
                click: function(e) {
                    location.href=baseUrl + '/app/documents/pdf/ScaricoFarmaco/'+my_id;
                    return false;
                }
            })
            .css({"margin-right": "5px", float: "left", cursor: "pointer"})
            .addClass("ui-pg-div ui-inline-custom")
            .append('<span class="fa-file-pdf-o ui-icon"></span>')
            .prependTo($(this).children("div"));
            if(!gestioneChiusa()){
                 //INSERISCO ACTION AGGIUNGI Lotto a CARICO
                 $("<div>", {
                    title: "Scarica Lotto",
                    mouseover: function() {
                        $(this).addClass('ui-state-hover');
                    },
                    mouseout: function() {
                        $(this).removeClass('ui-state-hover');
                    },
                    click: function(e) {
                        lastScaricoLottoAddedParentId=my_id;
                        visualizzaBarcode("all",false,my_id);
                        return false;
                        bootbox.prompt("Inserici codice a barre", function(barcode){
                            console.log(barcode);
                                if(barcode!==null&&barcode!=""){
                                    $.getJSON(baseUrl+'/app/rest/documents/jqgrid/advancedSearch/DepotFarmacoLotto?depotFarmacoLotto_barcode_eq='+barcode, function (found) {
                                        if(found.total==1){
                                            var lotto_id=found.root[0].id;
                                            var postUrl = baseUrl + "/app/rest/documents/update/" + lotto_id;
                                            var postData= new Object();
                                            postData['depotFarmacoLotto_scaricato'] = my_id;
                                            $.post(postUrl,postData).done(function (data) {

                                                if (data.result != 'OK') {
                                                    bootbox.hideAll();
                                                    bootbox.alert('Attenzione!!! Errore nello scaricamento del lotto');
                                                }
                                                else {
                                                    carichiLoaded=false;
                                                    jQuery("#DepotFarmacoCarico-grid-table").trigger('reloadGrid');
                                                    jQuery("#DepotFarmacoScarico-grid-table").trigger('reloadGrid');
                                                    bootbox.hideAll();
                                                }
                                            });
                                        }
                                        else{
                                            var message='Attenzione!!! Lotto non trovato';
                                            if(found.total>=1){
                                                message='Attenzione!!! Trovato più di un lotto con lo stesso barcode';
                                            }
                                            bootbox.hideAll();
                                            bootbox.alert(message);
                                        }
                                    });
                                }
                                else{
                                }
                        });
                        return false;
                    }
                })
                .css({"margin-right": "5px", float: "left", cursor: "pointer"})
                .addClass("ui-pg-div ui-inline-custom")
                .append('<span class="ui-icon fa-medkit"></span>')
                .prependTo($(this).children("div"));
            }
            //INSERISCO ACTION EDIT SCARICO
            $("<div>", {
                title: "Modifica",
                mouseover: function() {
                $(this).addClass('ui-state-hover');
                },
                mouseout: function() {
                $(this).removeClass('ui-state-hover');
                },
                click: function(e) {
                $.getJSON(baseUrl + '/app/rest/documents/getElementJSON/' + my_id, function (farmaco) {
                    farmacoScaricoModalEngine.formByElement(farmaco);
                });
                return false;
                }
            })
            .css({"margin-right": "5px", float: "left", cursor: "pointer"})
            .addClass("ui-pg-div ui-inline-custom")
            .append('<span class="ui-icon ui-icon-pencil"></span>')
            .prependTo($(this).children("div"));

        });
        if(lastScaricoLottoAddedParentId!==undefined){
            jQuery("#"+lastScaricoLottoAddedParentId+" td.ui-sgcollapsed").trigger('click');
        }
    }
    else{ //CASO SUBGRID
        var iCol = getColumnIndexByName("#"+grid_selector, 'sub_azioni');
        $("#"+grid_selector).find(">tbody>tr.jqgrow>td:nth-child(" + (iCol + 1) + ")").each(function () {
            var myRow=$(this);
            var my_id = $(this).parent().prop('id');
            $.getJSON(baseUrl + '/app/rest/documents/getElementJSON/' + my_id, function (lotto) {
                if(lotto.metadata.depotFarmacoLotto_scaricato===undefined){

                    //AGGIUNGO GENERAZIONE BARCODE
                    $("<div>", {
                        title: "Genera Barcode",
                        mouseover: function() {
                        $(this).addClass('ui-state-hover');
                        },
                        mouseout: function() {
                        $(this).removeClass('ui-state-hover');
                        },
                        click: function(e) {
                            var stampa=true;
                            visualizzaBarcode(lotto.id,stampa);

                            return false;
                        }
                        })
                        .css({"margin-right": "5px", float: "left", cursor: "pointer"})
                        .addClass("ui-pg-div ui-inline-custom")
                        .append('<span class="ui-icon fa-barcode"></span>')
                        .prependTo(myRow.children("div"));

                    //INSERISCO ACTION AGGIUNGI Lotto a CARICO
                    $("<div>", {
                        title: "Modifica",
                        mouseover: function() {
                        $(this).addClass('ui-state-hover');
                        },
                        mouseout: function() {
                        $(this).removeClass('ui-state-hover');
                        },
                        click: function(e) {
                            farmacoLottoModalEngine.formByElement(lotto);
                            lastLottoAddedParentId=undefined;
                            lastLottoSubGridEdited=grid_selector;
                            return false;
                        }
                    })
                    .css({"margin-right": "5px", float: "left", cursor: "pointer"})
                    .addClass("ui-pg-div ui-inline-custom")
                    .append('<span class="ui-icon ui-icon-pencil"></span>')
                    .prependTo(myRow.children("div"));
                }
                else{
                    $("<div>", {
                        title: "LOTTO GI&Agrave; SCARICATO!",
                        mouseover: function() {
                            $(this).addClass('ui-state-hover');
                        },
                        mouseout: function() {
                            $(this).removeClass('ui-state-hover');
                        },
                        click: function(e) {
                            return false;
                        }
                    }).css({"margin-right": "5px", float: "left", cursor: "pointer"})
                    .addClass("ui-pg-div ui-inline-custom")
                    .append('<span class="badge badge-danger">Gi&agrave; scaricato!</span>')
                    .prependTo(myRow.children("div"));
                }
            });
        });
    }
}

function chiudiGestioneFarmaco(depotId){
    bootbox.confirm("Confermi la chiusura?",function(){
        //console.log("devo calcolare quanti lotti sono ancora da scaricare");
        url=baseUrl+'/../getBarcodeDisponibili.php?DEPOTFARMACO_ID='+depotId;
        $.getJSON(url, function (found) {
            if(found.KO){
                //console.log("posso eliminare, non ci sono lotti da scaricare");
                var postUrl = baseUrl + "/app/rest/chiudiGestioneFarmaco/" + depotId;
                var postData= new Object();
                postData['depotFarmaco_DepotChiuso'] = "1";
                $.post(postUrl,postData).done(function (data) {
                    if (data.result == 'OK') {
                        location.href=baseUrl+'/app/documents/detail/'+depotId;
                    }
                else {
                        bootbox.hideAll();
                        bootbox.alert('Attenzione!!! Errore nella chiusura!');
                    }
                });
            }
            else{
                bootbox.hideAll();
                bootbox.alert("Non è possibile chiudere la gestione, sono presenti lotti da scaricare");
            }
        });
    });
}
</@script>
