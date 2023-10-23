var pxps=[];
var costiAggiuntivi=[];
var totPrice=0;
var totPricePaz=0;
var totCostiAgg=0;
function loadBC(){
    loadPXP(false);
    loadCostiAggiuntivi(false);
}

function loadPXP(bootboxClose){
    $.getJSON(baseUrl + "/app/rest/documents/" + elementId + "/getChildren/FolderPXP/maxdepth/1", function (data) {
        pxps=[];
        if (data[0].children){
            pxps=data[0].children;
        }
        buildPXPTable(bootboxClose);
    });
}

function loadCostiAggiuntivi(bootboxClose){
    $.getJSON(baseUrl + "/app/rest/documents/" + elementId + "/getChildren/FolderCostiAggiuntivi/maxdepth/1", function (data) {
        costiAggiuntivi=[];
        if (data[0].children){
            costiAggiuntivi=data[0].children;
        }
        buildCostiAggiuntiviTable(bootboxClose);
    });
}


function buildPXPTable(bootboxClose){
    var tbody=$('#added-costs-1 tbody');
    if (pxps==undefined) {
        if (bootboxClose) bootbox.hideAll();
        return;
    }
    if (pxps.length==0){
            tbody.html('<tr><td colspan=9><span class="help-button">?</span> Tabella riassuntiva delle prestazioni/attivit&agrave; aggiuntive</td></tr>');
    }else {
        tbody.html('');
        var totRow=$('<tr>');
        var totTd1=$('<td>');
        var totTd2=$('<td>');
        var totTd3=$('<td>');
        var totTd4=$('<td>');
        totPricePaz=0;
        for (var i=0;i<pxps.length;i++){
            var row=$('<tr>');
            var td1=$('<td>');
            var td2=$('<td>');
            var td3=$('<td>');
            var td4=$('<td>');
            var td5=$('<td>');
            var td6=$('<td>');
            var td7=$('<td>');
            var td8=$('<td>');
            var td9=$('<td>');

            if (pxps[i].metadata.Prestazioni_CDC && pxps[i].metadata.Prestazioni_CDC[0]){
                td1.append(pxps[i].metadata.Prestazioni_CDC[0].titleString);
            }
            else if (pxps[i].metadata.Prestazioni_CDCCode && pxps[i].metadata.Prestazioni_CDCCode[0]) {
                td1.append(pxps[i].metadata.Prestazioni_CDCCode[0]);
            }

            if (pxps[i].metadata.Prestazioni_Codice && pxps[i].metadata.Prestazioni_Codice[0]){
                td2.append(pxps[i].metadata.Prestazioni_Codice[0]);
            }

            if (pxps[i].metadata.Base_Nome && pxps[i].metadata.Base_Nome[0]){
                td3.append(pxps[i].metadata.Base_Nome[0]);
            }

            var tpriceSSN=0;
            if (pxps[i].metadata.Tariffario_SSN && pxps[i].metadata.Tariffario_SSN[0]){
                tpriceSSN=pxps[i].metadata.Tariffario_SSN[0].replace(",",".")-0;
                td4.append(tpriceSSN.toFixed(2)+" &euro;");
            }

            var tprice=0;
            if (pxps[i].metadata.Costo_TransferPrice && pxps[i].metadata.Costo_TransferPrice[0]){
                tprice=pxps[i].metadata.Costo_TransferPrice[0]-0;
                totPrice+=tprice;
                td5.append(tprice.toFixed(2)+" &euro;");
            }


            if (pxps[i].metadata.Costo_Quantita && pxps[i].metadata.Costo_Quantita[0]) {
                totPricePaz+=tprice*pxps[i].metadata.Costo_Quantita[0];
                td6.append(pxps[i].metadata.Costo_Quantita[0]);
            }


            if (pxps[i].metadata.Costo_Copertura && pxps[i].metadata.Costo_Copertura[0]){
                td7.append(pxps[i].metadata.Costo_Copertura[0].split("###")[1]);
            }

            var deletelink=$('<a>');
            var modlink = $('<a>');
            if(!budgetReadonly) {
                deletelink.attr('data-id', pxps[i].id);
                deletelink.html("<i class='fa fa-trash'></i> Elimina");
                deletelink.click(function () {
                    loadingScreen("Eliminazione voce di costo ...");
                    var elid = $(this).attr('data-id');
                    $.getJSON(baseUrl + "/app/rest/documents/delete/" + elid, function (data) {
                        if (data.result != 'OK') {
                            bootbox.hideAll();
                            bootbox.alert('Errore eliminazione costo');
                        } else {
                            loadPXP(true);
                        }
                    });
                });
                modlink.html('<i class="fa fa-pencil"></i> Modifica');
                modlink.attr('data-id', pxps[i].id);
                modlink.click(function () {
                    var elId = $(this).attr('data-id');
                    var el = null;
                    for (var idx = 0; idx < pxps.length; idx++) {
                        if (elId == pxps[idx].id) el = pxps[idx];
                    }
                    $('#dialog-form').dialog('open');
                    console.log(el);
                    if (el.metadata.Base_Nome && el.metadata.Base_Nome[0]) {
                        $('#dialog-form [name=Base_Nome]').val(el.metadata.Base_Nome[0]);
                    }
                    else {
                        $('#dialog-form [name=Base_Nome]').val("");
                    }
                    if (el.metadata.Prestazioni_Codice && el.metadata.Prestazioni_Codice[0]) {
                        $('#dialog-form [name=Prestazioni_Codice]').val(el.metadata.Prestazioni_Codice[0]);
                    }
                    else {
                        $('#dialog-form [name=Prestazioni_Codice]').val("");
                    }

                    if (el.metadata.Costo_Quantita && el.metadata.Costo_Quantita[0]) {
                        $('#dialog-form [name=Costo_Quantita]').val(el.metadata.Costo_Quantita[0]);
                    }
                    else {
                        $('#dialog-form [name=Costo_Quantita]').val("");
                    }
                    if (el.metadata.Costo_Costo && el.metadata.Costo_Costo[0]) {
                        $('#dialog-form [name=Costo_Costo]').val(el.metadata.Costo_Costo[0]);
                    }
                    else {
                        $('#dialog-form [name=Costo_Costo]').val("");
                    }
                    if (el.metadata.Costo_Markup && el.metadata.Costo_Markup[0]) {
                        $('#dialog-form [name=Costo_Markup]').val(el.metadata.Costo_Markup[0]);
                    }
                    else {
                        $('#dialog-form [name=Costo_Markup]').val("");
                    }
                    if (el.metadata.Tariffario_SSN && el.metadata.Tariffario_SSN[0]) {
                        $('#dialog-form [name=Tariffario_SSN]').val(el.metadata.Tariffario_SSN[0]);
                    }
                    else {
                        $('#dialog-form [name=Tariffario_SSN]').val("");
                    }
                    if (el.metadata.Costo_MarkupUnita && el.metadata.Costo_MarkupUnita[0]) {
                        $('#dialog-form [name=Costo_MarkupUnita]').val(el.metadata.Costo_MarkupUnita[0]);
                    }
                    else {
                        $('#dialog-form [name=Costo_MarkupUnita]').val("");
                    }
                    if (el.metadata.Costo_TransferPrice && el.metadata.Costo_TransferPrice[0]) {
                        $('#dialog-form [name=Costo_TransferPrice]').val(el.metadata.Costo_TransferPrice[0]);
                    }
                    else {
                        $('#dialog-form [name=Costo_TransferPrice]').val("");
                    }
                    if (el.metadata.Prestazioni_CDC && el.metadata.Prestazioni_CDC[0]) {
                        valorizzaCDC($('#dialog-form [name=Prestazioni_CDC]'), {
                            label: el.metadata.Prestazioni_CDC[0].titleString,
                            value: el.metadata.Prestazioni_CDC[0].titleString,
                            id: el.metadata.Prestazioni_CDC[0].id
                        }, 2);
                        $('#dialog-form [name=Prestazioni_CDC]').val(el.metadata.Prestazioni_CDC[0].titleString);
                        //$('#dialog-form [name=Prestazioni_CDC2]').val(el.metadata.Prestazioni_CDCCode[0].titleString);
                    }
                    else if (el.metadata.Prestazioni_CDCCode && el.metadata.Prestazioni_CDCCode[0]) { //CASO PI NON HO CDC (perchè element link
                        valorizzaCDC($('#dialog-form [name=Prestazioni_CDC]'), {
                            label: "PI",
                            value: "PI",
                            id: "-99999"
                        }, 2);
                        $('#dialog-form [name=Prestazioni_CDC]').val(el.metadata.Prestazioni_CDCCode[0]);
                    }

                    if (el.metadata.Prestazioni_Attivita && el.metadata.Prestazioni_Attivita[0]) {
                        $('#dialog-form [name=Prestazioni_Attivita][value=' + el.metadata.Prestazioni_Attivita[0] + ']').prop("checked", true)
                    }
                    if (el.metadata.Costo_Copertura && el.metadata.Costo_Copertura[0]) {
                        $('#dialog-form [name=Costo_Copertura]').val(el.metadata.Costo_Copertura[0]).trigger("change");
                    }

                    $('#dialog-form [name=tipologia]').val('1');
                    $('#dialog-form form').attr('data-type', 'update');
                    $('#dialog-form form').attr('data-id', elId);
                });
            }
            else{
                deletelink.html("<i class='fa fa-ban'></i>");
                modlink.html("<i class='fa fa-ban'></i>");
            }
            td8.append(modlink);
            td9.append(deletelink);
            row.append(td1);
            row.append(td2);
            row.append(td3);
            row.append(td4);
            row.append(td5);
            row.append(td6);
            row.append(td7);
            row.append(td8);
            row.append(td9);
            tbody.append(row);
        }
        $("#show-totPricePaz").html("&euro; " + totPricePaz.toFixed(2));
        $("#show-TotPerPaz").html("&euro; " +(parseFloat(proposta_promotore)+parseFloat(totPricePaz)).toFixed(2));
        //totTd1.append("Totale transfer price");
        //totRow.append(totTd1);
        //totTd2.append(totPrice.toFixed(2)+" &euro;");
        //totRow.append(totTd2);
        //totRow.append(totTd3);
        //totRow.append(totTd4);
        //tbody.append(totRow);
    }
    if (bootboxClose) bootbox.hideAll();
}

function buildCostiAggiuntiviTable(bootboxClose){
    var tbody=$('#added-ca tbody');

    if (costiAggiuntivi==undefined) {
        if (bootboxClose) bootbox.hideAll();
        return;
    }
    if (costiAggiuntivi.length==0){
        tbody.html('<tr><td colspan=6><span class="help-button">?</span> Tabella riassuntiva dei servizi aggiuntivi per studio </td></tr>');
    }else {
        tbody.html('');
        totCostiAgg=0;
        for (var i=0;i<costiAggiuntivi.length;i++){
            var row=$('<tr>');
            var td1=$('<td>');
            var td2=$('<td>');
            var td3=$('<td>');
            var td4=$('<td>');
            var td5=$('<td>');
            var td6=$('<td>');
            var categoria=costiAggiuntivi[i].metadata.CostoAggiuntivo_Tipologia && costiAggiuntivi[i].metadata.CostoAggiuntivo_Tipologia[0] && costiAggiuntivi[i].metadata.CostoAggiuntivo_Tipologia[0].split('###')[1] || '';
            //var previsto=null;
            //if (costiAggiuntivi[i].metadata.CostoAggiuntivo_Previsto && costiAggiuntivi[i].metadata.CostoAggiuntivo_Previsto[0])
            //previsto=costiAggiuntivi[i].metadata.CostoAggiuntivo_Previsto[0].split('###')[1] || '';
            var descrizione=costiAggiuntivi[i].metadata.CostoAggiuntivo_OggettoPrincipale || '';
            var copertura=costiAggiuntivi[i].metadata.CostoAggiuntivo_Copertura[0].split('###')[1] || '';
            var quantita=costiAggiuntivi[i].metadata.CostoAggiuntivo_Quantita[0] || '0';
            quantita=quantita?quantita:'0';
            var tprice=0;

            if (costiAggiuntivi[i].metadata.CostoAggiuntivo_Costo && costiAggiuntivi[i].metadata.CostoAggiuntivo_Costo[0]) {
                tprice = costiAggiuntivi[i].metadata.CostoAggiuntivo_Costo[0] - 0;
            }
            totCostiAgg+=tprice;
            td1.append(categoria);
            //td2.append(previsto);
            td3.append(copertura);

            td4.append(tprice.toFixed(2)+" &euro;");
            var deletelink=$('<a>');
            var modlink=$('<a>');
            if(!budgetReadonly) {

                deletelink.attr('data-id', costiAggiuntivi[i].id);
                deletelink.html("<i class='fa fa-trash'></i> Elimina");
                deletelink.click(function () {
                    loadingScreen("Eliminazione voce di costo ...");
                    var elid = $(this).attr('data-id');
                    $.getJSON(baseUrl + "/app/rest/documents/delete/" + elid, function (data) {
                        if (data.result != 'OK') {
                            bootbox.hideAll();
                            bootbox.alert('Errore eliminazione costo');
                        } else {
                            loadCostiAggiuntivi(true);
                        }
                    });
                });


                modlink.html('<i class="fa fa-pencil"></i> Modifica');
                modlink.attr('data-id', costiAggiuntivi[i].id);
                modlink.click(function () {
                    var elId = $(this).attr('data-id');
                    var el = null;
                    for (var idx = 0; idx < costiAggiuntivi.length; idx++) {
                        if (elId == costiAggiuntivi[idx].id) el = costiAggiuntivi[idx];
                    }
                    $('#dialog-form-ca').dialog('open');
                    console.log(el);


                    var tipologia = el.metadata.CostoAggiuntivo_Tipologia[0] || '';
                    var descrizione = el.metadata.CostoAggiuntivo_OggettoPrincipale || '';
                    var previsto = el.metadata.CostoAggiuntivo_Previsto!==undefined && el.metadata.CostoAggiuntivo_Previsto[0]!==undefined ? el.metadata.CostoAggiuntivo_Previsto[0] : '';
                    var quantita = el.metadata.CostoAggiuntivo_Quantita[0] || '0';
                    var copertura = el.metadata.CostoAggiuntivo_Copertura[0];
                    quantita = quantita ? quantita : '0';
                    var tprice = 0;
                    if (el.metadata.CostoAggiuntivo_Costo && el.metadata.CostoAggiuntivo_Costo[0]) {
                        tprice = el.metadata.CostoAggiuntivo_Costo[0] - 0;
                    }
                    tipologiaSplitted=tipologia.split("###");
                    tipologiaAltro="";
                    if(tipologiaSplitted[0]=="-9999"){
                        tipologia="-9999###Altro";
                        tipologiaAltro=tipologiaSplitted[1];
                    }
                    $('#dialog-form-ca [name=CostoAggiuntivo_Tipologia-select]').val(tipologia).change();
                    if(tipologiaAltro!=""){
                        $('#dialog-form-ca [name=CostoAggiuntivo_Tipologia-altro]').val(tipologiaAltro);
                    }
                    $('#dialog-form-ca [name=CostoAggiuntivo_OggettoPrincipale]').val(descrizione);
                    $('#dialog-form-ca [name=CostoAggiuntivo_Previsto][value="' + previsto + '"]').prop("checked", true);
                    $('#dialog-form-ca [name=CostoAggiuntivo_Quantita]').val(quantita);
                    $('#dialog-form-ca [name=CostoAggiuntivo_Costo]').val(tprice);
                    $('#dialog-form-ca [name=CostoAggiuntivo_Copertura-select]').val(copertura).change();
                    $('#dialog-form-ca form').attr('data-type', 'update');
                    $('#dialog-form-ca form').attr('data-id', elId);
                });
            }
            else{
                deletelink.html("<i class='fa fa-ban'></i>");
                modlink.html("<i class='fa fa-ban'></i>");
            }
            td5.append(modlink);
            td6.append(deletelink);
            row.append(td1);
            //row.append(td2);
            row.append(td3);
            row.append(td4);
            row.append(td5);
            row.append(td6);
            tbody.append(row);
        }
        $("#show-totCostiAgg").html("&euro; " + totCostiAgg.toFixed(2));
    }
    if (bootboxClose) bootbox.hideAll();
}

function saveCosto(form) {
    loadingScreen("salvataggio in corso");
    /*var prestazioneCdc=form.find('[name=Prestazioni_CDCSelect]').val();
    var psplit=prestazioneCdc.split("###");*/
    var tip = form.parent().attr('id');
    var opType = form.attr('data-type');
    var opId = form.attr('data-id');
    /*form.find('[name=Prestazioni_CDC]').val(psplit[1]);
    form.find('[name=Prestazioni_CDCCode]').val(psplit[0]);*/
    var formToSend = form.clone();
    formToSend.find('[name=Prestazioni_CDCSelect]').remove();
    formToSend.find('[name=Prestazioni_CDC]').val(formToSend.find('[name=Prestazioni_CDCCode]').val());
    if (formToSend.find('[name=Prestazioni_CDCCode]').val() != "-99999"){
        formToSend.find('[name=Prestazioni_CDCCode]').val("");
    }
    else{
        formToSend.find('[name=Prestazioni_CDC]').val("");
        formToSend.find('[name=Prestazioni_CDCCode]').val("PI");
    }
    formToSend.find('[name=tipologia]').remove();
    var postUrl="";
    if (tip=="dialog-form"){
        postUrl=baseUrl + "/app/rest/documents/save/PrestazioneXPaziente";
        formToSend.append('<input type="hidden" name="parentId" value="'+folderPXPId+'"/>');
    }else {
        postUrl=baseUrl + "/app/rest/documents/save/CostoAggiuntivo";
        formToSend.find('[name=Tariffario_Solvente]').remove();
        formToSend.find('[name=Tariffario_SSN]').remove();
        formToSend.append('<input type="hidden" name="parentId" value="'+folderCostiAggiuntiviId+'"/>');
    }
    if (opType=='update'){
        var elId=formToSend.attr('data-id');
        postUrl=baseUrl + "/app/rest/documents/update/"+opId;
        formToSend.find('[name="parentId"]').remove();
    }
    (function(postUrl, formToSend, type){
        var postData=formToSend.serialize();
        if(type=="dialog-form" && postData.includes("&Costo_Copertura=&")){
                postData=postData.replace("&Costo_Copertura=&","&Costo_Copertura="+$('#dialog-form [name=Costo_Copertura]').val()+"&");
            }
        //console.log(postData);
        $.post(postUrl, postData).done(function(data){
            if (data.result!='OK'){
                bootbox.hideAll();
                bootbox.alert('Attenzione!!! Errore nel salvataggio della prestazione');
            }else {
                if (type=="dialog-form") loadPXP(true);
                else loadCostiAggiuntivi(true);
                bootbox.hideAll();
            }
        });
    })(postUrl, formToSend, tip);


}

function changeTipologia(){
    var tipologia=$('#tipologia').val()||$('#tipologia2').val();
    $('#Prestazioni-Prestazioni_Attivita').show();
    $('[name=Prestazioni_Attivita][value^=1]').closest('.radio').show();
    $('[name=Prestazioni_Attivita][value^=2]').closest('.radio').show();
    var $that4=$( "#descrizione" );
    if(tipologia==1 || true){
        $('.tip1_exclusive').show();
        if (jQuery("#descrizione").data('autocomplete')) {
            jQuery("#descrizione").autocomplete("destroy");
            jQuery("#descrizione").removeData('autocomplete');
        }
        $( "#descrizione" ).autocomplete({

            minLength: 2,
            select: function( event, ui ) {
                var request={prestazione:$( "#descrizione" ).val(),term:''};
                $that4.next('i.icon-spinner').remove();
                /*$.getJSON(  "/dizionari/prestazioni.php", request, function( data, status, xhr ) {
                    if(data.length==1){
                        valorizzaCDC($( "#Prestazioni_CDC2" ),data[0],2);
                    }
                });*/
                $('#Tariffario_SSN2').val(ui.item.ssn);
                $('span.ssn_diz').html(" (Tariffa SSR: "+ui.item.ssn+" €)");//TOSCANA-185
                $('#costo').val($.trim(ui.item.ssn).replace(/,/,'.'));//TOSCANA-185
                //$('span.ssn_diz').html(" (Tariffa SSR: "+ui.item.ssn+" €)");//TOSCANA-185
                $('#costo2').val($.trim(ui.item.ssn).replace(/,/,'.')).trigger('change');//TOSCANA-185

                $( "#Prestazioni_Codice2" ).val(ui.item.id);
                $(this).off('keypress').on('keypress',function(){
                    $( "#dizionario2" ).not('.dont-clear').val('');
                    hidebutton();
                    if($(this).val()!=ui.item.value){
                        $( "#Prestazioni_CDC2" ).val('');
                        $( "#Prestazioni_CDC2" ).keypress();
                        $( "#dizionario2" ).val('');
                        $(this).off('keypress');
                    }
                });
            },
            source:function( request, response ) {
                $that4.next('i.icon-spinner').remove();
                $that4.after("<i class='icon-spinner icon-spin orange bigger-125' style='position:relative;left:-30px' ></i>");
                var term = request.term;
                if ( term in cache ) {
                    response( cache[ term ] );
                    return;
                }
                $.getJSON(  "/dizionari/prestazioni.php", request, function( data, status, xhr ) {
                    cache[ term ] = data;
                    response( data );
                    $that4.next('i.icon-spinner').remove();
                });
            }

        });
        /*$( "#descrizione" ).change(function(){
            var request={prestazione:$( "#descrizione" ).val(),term:''};
            $.getJSON(  "/dizionari/prestazioni.php", request, function( data, status, xhr ) {
                if(data.length==1){
                    valorizzaCDC($( "#Prestazioni_CDC2" ),data[0],2);
                }
            });
        });*/

        $( "#Prestazioni_CDC2" ).off('click').click(function(){
            $( this ).autocomplete('search','');
        });
        if (jQuery("#Prestazioni_CDC2").data('autocomplete')) {
            jQuery("#Prestazioni_CDC2").autocomplete("destroy");
            jQuery("#Prestazioni_CDC2").removeData('autocomplete');
        }
        var $that5=$( "#Prestazioni_CDC2" );
        $( "#Prestazioni_CDC2" ).autocomplete({

            minLength: 0,
            source:function( request, response ) {
                $that5.next('i.icon-spinner').remove();
                $that5.after("<i class='icon-spinner icon-spin orange bigger-125' style='position:relative;left:-30px' ></i>");
                //request.prestazione=$( "#descrizione" ).val()||'prestazione undefined';
                $.getJSON(   baseUrl + "/app/rest/documents/" + centroId + "/getChildren/FeasibilityServiziRichiesta/maxdepth/1",  function( data, status, xhr ) {

                    var my_data= Array(); //"{";
                    $(data).each(function(key,value){
                        my_data[key]={ 'id' : value.id, 'label' : value.titleString  }
                    });
                    my_data[my_data.length]={ 'id' : '-99999', 'label' : 'PI'  }
                    response( my_data );
                    $that5.next('i.icon-spinner').remove();
                });
            },
            select: function( event, ui ) {
                valorizzaCDC(this,ui.item,2);
            }

        });
        $('.tip_exclusive').show();
    }
}

function valorizzaCDC(cdc,item,suffix){
    suffix = suffix ? suffix : '';
    $(cdc).val(item.value);
    //$(cdc).closest('form').find('input#Prestazioni_UOC'+suffix).val(item.uo);
    //$(cdc).closest('form').find('input#Prestazioni_UOCCode'+suffix).val(item.uo_code);

    $(cdc).closest('form').find('input#Prestazioni_CDCCode'+suffix).val(item.id);
    $(cdc).closest('form').find('input#Prestazioni_CDC'+suffix).val(item.id);

    $('#dizionario'+suffix).val('');

    $(cdc).off('keypress').on('keypress',function (){
        if($(cdc).val()!=item.value){
            $(cdc).closest('form').find('.ssn_diz').html('');

            var that=cdc;
            $( "#dizionario"+suffix ).val('');
            /*$('#prestazione-diz-dialog').on('dialogclose',function(){
                $(that).off('keypress');
            });*/
            $(cdc).closest('form').find('input#Prestazioni_CDCCode'+suffix).val('');
            $(cdc).closest('form').find('input#Prestazioni_CDC'+suffix).val('');
            //$(cdc).closest('form').find('input#Prestazioni_UOC'+suffix).val('');
            //$(cdc).closest('form').find('input#Prestazioni_UOCCode'+suffix).val('');

            $(this).off('keypress');
        }
    });
    hidebutton();
}
