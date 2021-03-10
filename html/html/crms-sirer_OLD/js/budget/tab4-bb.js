var pxps=[];
var costiAggiuntivi=[];


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
        tbody.html('<tr><td colspan=4><span class="help-button">?</span> Tabella riassuntiva delle prestazioni cliniche richiedibili per paziente </td></tr>');
    }else {
        tbody.html('');
        var totRow=$('<tr>');
        var totTd1=$('<td>');
        var totTd2=$('<td>');
        var totTd3=$('<td>');
        var totTd4=$('<td>');
        var totTprice=0;
        for (var i=0;i<pxps.length;i++){
            var row=$('<tr>');
            var td1=$('<td>');
            var td2=$('<td>');
            var td3=$('<td>');
            var td4=$('<td>');
            if (pxps[i].metadata.Base_Nome && pxps[i].metadata.Base_Nome[0]) td1.append(pxps[i].metadata.Base_Nome[0]);
            var tprice=0;
            if (pxps[i].metadata.Costo_TransferPrice && pxps[i].metadata.Costo_TransferPrice[0])
                tprice=pxps[i].metadata.Costo_TransferPrice[0]-0;
            totTprice+=tprice;
            td2.append(tprice.toFixed(2)+" &euro;");
            var deletelink=$('<a>');
            deletelink.attr('data-id',pxps[i].id);
            deletelink.html("<i class='fa fa-trash'></i> Elimina");
            deletelink.click(function(){
                loadingScreen("Eliminazione voce di costo ...");
                var elid=$(this).attr('data-id');
                $.getJSON(baseUrl + "/app/rest/documents/delete/" + elid, function (data) {
                    if (data.result!='OK'){
                        bootbox.hideAll();
                        bootbox.alert('Errore eliminazione costo');
                    }else {
                        loadPXP(true);
                    }
                });
            });
            var modlink=$('<a>');
            modlink.html('<i class="fa fa-pencil"></i> Modifica');
            modlink.attr('data-id', pxps[i].id);
            modlink.click(function(){
                var elId=$(this).attr('data-id');
                var el=null;
                for (var idx=0;idx<pxps.length;idx++){
                    if (elId==pxps[idx].id) el=pxps[idx];
                }
                $('#dialog-form').dialog('open');
                console.log(el);
                if (el.metadata.Base_Nome && el.metadata.Base_Nome[0]) $('#dialog-form [name=Base_Nome]').val(el.metadata.Base_Nome[0]);
                if (el.metadata.Costo_Costo && el.metadata.Costo_Costo[0]) $('#dialog-form [name=Costo_Costo]').val(el.metadata.Costo_Costo[0]);
                if (el.metadata.Costo_Markup && el.metadata.Costo_Markup[0]) $('#dialog-form [name=Costo_Markup]').val(el.metadata.Costo_Markup[0]);
                if (el.metadata.Costo_MarkupUnita && el.metadata.Costo_MarkupUnita[0]) $('#dialog-form [name=Costo_MarkupUnita]').val(el.metadata.Costo_MarkupUnita[0]);
                if (el.metadata.Costo_TransferPrice && el.metadata.Costo_TransferPrice[0]) $('#dialog-form [name=Costo_TransferPrice]').val(el.metadata.Costo_TransferPrice[0]);
                if (el.metadata.Prestazioni_CDC && el.metadata.Prestazioni_CDC[0]) {
                    $('#dialog-form [name=Prestazioni_CDC]').val(el.metadata.Prestazioni_CDC[0]);
                    $('#dialog-form [name=Prestazioni_CDCCode]').val(el.metadata.Prestazioni_CDCCode[0]);
                }
                if (el.metadata.Prestazioni_Attivita && el.metadata.Prestazioni_Attivita[0]){
                    $('#dialog-form [name=Prestazioni_Attivita][value='+el.metadata.Prestazioni_Attivita[0]+']').prop("checked",true)
                }
                if (el.metadata.Costo_Copertura && el.metadata.Costo_Copertura[0]){
                    $('#dialog-form [name=Costo_Copertura]').val(el.metadata.Costo_Copertura[0]).trigger("change");
                }
                $('#dialog-form [name=tipologia]').val('1');
                $('#dialog-form form').attr('data-type','update');
                $('#dialog-form form').attr('data-id',elId);
            });
            td3.append(modlink);
            td4.append(deletelink);
            row.append(td1);
            row.append(td2);
            row.append(td3);
            row.append(td4);
            tbody.append(row);
        }
        totTd1.append("Totale transfer price");
        totRow.append(totTd1);
        totTd2.append(totTprice.toFixed(2)+" &euro;");
        totRow.append(totTd2);
        totRow.append(totTd3);
        totRow.append(totTd4);
        tbody.append(totRow);
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
        tbody.html('<tr><td colspan=6><span class="help-button">?</span> Tabella riassuntiva delle prestazioni cliniche richiedibili per studio </td></tr>');
    }else {
        tbody.html('');
        for (var i=0;i<costiAggiuntivi.length;i++){
            var row=$('<tr>');
            var td1=$('<td>');
            var td2=$('<td>');
            var td3=$('<td>');
            var td4=$('<td>');
            var td5=$('<td>');
            var td6=$('<td>');
            var categoria=costiAggiuntivi[i].metadata.CostoAggiuntivo_Tipologia[0].split('###')[1] || '';
            var descrizione=costiAggiuntivi[i].metadata.CostoAggiuntivo_OggettoPrincipale || '';
            var quantita=costiAggiuntivi[i].metadata.CostoAggiuntivo_Quantita[0] || '0';
            quantita=quantita?quantita:'0';
            var tprice=0;
            if (costiAggiuntivi[i].metadata.CostoAggiuntivo_Costo && costiAggiuntivi[i].metadata.CostoAggiuntivo_Costo[0]) {
                tprice = costiAggiuntivi[i].metadata.CostoAggiuntivo_Costo[0] - 0;
            }
            td1.append(categoria);
            td2.append(descrizione);
            td3.append(quantita);

            td4.append(tprice.toFixed(2)+" &euro;");

            var deletelink=$('<a>');
            deletelink.attr('data-id',costiAggiuntivi[i].id);
            deletelink.html("<i class='fa fa-trash'></i> Elimina");
            deletelink.click(function(){
                loadingScreen("Eliminazione voce di costo ...");
                var elid=$(this).attr('data-id');
                $.getJSON(baseUrl + "/app/rest/documents/delete/" + elid, function (data) {
                    if (data.result!='OK'){
                        bootbox.hideAll();
                        bootbox.alert('Errore eliminazione costo');
                    }else {
                        loadCostiAggiuntivi(true);
                    }
                });
            });

            var modlink=$('<a>');
            modlink.html('<i class="fa fa-pencil"></i> Modifica');
            modlink.attr('data-id', costiAggiuntivi[i].id);
            modlink.click(function(){
                var elId=$(this).attr('data-id');
                var el=null;
                for (var idx=0;idx<costiAggiuntivi.length;idx++){
                    if (elId==costiAggiuntivi[idx].id) el=costiAggiuntivi[idx];
                }
                $('#dialog-form-ca').dialog('open');
                console.log(el);


                var tipologia=el.metadata.CostoAggiuntivo_Tipologia[0] || '';
                var descrizione=el.metadata.CostoAggiuntivo_OggettoPrincipale || '';
                var quantita=el.metadata.CostoAggiuntivo_Quantita[0] || '0';
                var copertura=el.metadata.CostoAggiuntivo_Copertura[0];
                quantita=quantita?quantita:'0';
                var tprice=0;
                if (el.metadata.CostoAggiuntivo_Costo && el.metadata.CostoAggiuntivo_Costo[0]) {
                    tprice = el.metadata.CostoAggiuntivo_Costo[0] - 0;
                }

                $('#dialog-form-ca [name=CostoAggiuntivo_Tipologia-select]').val(tipologia).trigger("change");
                $('#dialog-form-ca [name=CostoAggiuntivo_OggettoPrincipale]').val(descrizione);
                $('#dialog-form-ca [name=CostoAggiuntivo_Quantita]').val(quantita);
                $('#dialog-form-ca [name=CostoAggiuntivo_Costo]').val(tprice);
                $('#dialog-form-ca [name=CostoAggiuntivo_Copertura-select]').val(copertura);
                $('#dialog-form-ca form').attr('data-type','update');
                $('#dialog-form-ca form').attr('data-id',elId);
            });
            td5.append(modlink);
            td6.append(deletelink);
            row.append(td1);
            row.append(td2);
            row.append(td3);
            row.append(td4);
            row.append(td5);
            row.append(td6);
            tbody.append(row);
        }
    }
    if (bootboxClose) bootbox.hideAll();
}

function saveCosto(form){
    loadingScreen("salvataggio in corso");
    /*var prestazioneCdc=form.find('[name=Prestazioni_CDCSelect]').val();
    var psplit=prestazioneCdc.split("###");*/
    var tip=form.parent().attr('id');
    var opType=form.attr('data-type');
    var opId=form.attr('data-id');
    /*form.find('[name=Prestazioni_CDC]').val(psplit[1]);
    form.find('[name=Prestazioni_CDCCode]').val(psplit[0]);*/
    var formToSend=form.clone();
    formToSend.find('[name=Prestazioni_CDCSelect]').remove();
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
            }
        });
    })(postUrl, formToSend, tip);


}
