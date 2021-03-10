var prestazioni=null;
var tpxp=null;
var timePoint=null;

var prestazioniLoaded=false;
var timePointLoaded=false;
var tpxpLoaded=false;
var flowchartTableBuilded=false;

var prestazioniById={};
var timePointById={};
var tpxpByTp={};
var tpxpByP={};
var tpxpById={};

var folderPrestazioniId=null;
var folderTimePointId=null;
var folderTpxpId=null;

var tbRow2MdRow=null;
var tbRow2MdId=null;
var tbCol2MdCol=null;
var tbCol2MdId=null;
var nextCol=1;

var nextRow=1;


$( '#tabs' ).resize(function() {
    buildFlowchartTable();
});

function loadFolderPrestazioni() {
   $.getJSON(baseUrl + "/app/rest/documents/" + elementId + "/getChildren/FolderPrestazioni/maxdepth/1", function (data) {
        prestazioni = data[0].children;
        prestazioniLoaded = true;
        buildFlowchartTable();
    });
}

function loadTimePoints(){
    $.getJSON(baseUrl+"/app/rest/documents/"+elementId+"/getChildren/FolderTimePoint/maxdepth/1", function(data){
        timePoint=data[0].children;
        timePointLoaded=true;
        buildFlowchartTable();
    });
}

function loadTpxp() {
    $.getJSON(baseUrl + "/app/rest/documents/" + elementId + "/getChildren/FolderTpxp/maxdepth/1", function (data) {
        tpxp = data[0].children;
        tpxpLoaded = true;
        populateTpxp();
    });
}


var rowTots=new Object();
var colTots=new Object();
var patTot=0;
var tbData={};
var notDisplayed=[];
var duplicatedTpxp=[];
var totRows = {};
var totCostiRowsA = {};
var totCostiRowsB = {};
var totCostiRowsC = {};
var totCostiRowsD = {};
var totCountSSNRows = {};
var totCountExtraRows = {};
var totCountExtraRowsA = {};
var totCountExtraRowsB = {};
var totCountExtraRowsC = {};
var totCountExtraRowsD = {};
var totCostiCols = {};
var totPrezziCols = {};
var totCountSSNCols = {};
var totCountExtraCols = {};
var totCountsCols = {};
var totTpExtraRoutine={};
function populateTpxp(){
    if (!flowchartTableBuilded) return;
    tpxpByTp={};
    tpxpByP={};
    tpxpById={};
    patTot=0;
    rowTots=[];
    colTots=[];
    totRows = {};
    totCostiRowsA = {};
    totCostiRowsB = {};
    totCostiRowsC = {};
    totCostiRowsD = {};
    totCountSSNRows = {};
    totCountExtraRows = {};
    totCountExtraRowsA = {};
    totCountExtraRowsB = {};
    totCountExtraRowsC = {};
    totCountExtraRowsD = {};
    totCostiCols = {};
    totPrezziCols = {}
    totCountSSNCols = {};
    totCountsCols = {};
    totCountExtraCols = {};
    totTpExtraRoutine={};
    tbData={};
    for (var t=0;t<tpxp.length;t++){

        var totCostiRowA = 0;
        var totCostiRowB = 0;
        var totCostiRowC = 0;
        var totCostiRowD = 0;

        var totCountSSNRow = 0;
        var totCountExtraRow = 0;
        var totCountExtraRowA = 0;
        var totCountExtraRowB = 0;
        var totCountExtraRowC = 0;
        var totCountExtraRowD = 0;

        if (tpxp[t]==null) continue;
        var md=tpxp[t].metadata;
        if (md['tp-p_Prestazione']==undefined || md['tp-p_Prestazione'][0]==undefined){
        	notDisplayed[notDisplayed.length]=tpxp.id;
        	continue;
        }
        if (tbData['P'+md['tp-p_Prestazione'][0].id]==undefined){
        	tbData['P'+md['tp-p_Prestazione'][0].id]={};
        	tbData['P'+md['tp-p_Prestazione'][0].id]['T'+md['tp-p_TimePoint'][0].id]=[];
        }
        if (tbData['P'+md['tp-p_Prestazione'][0].id]['T'+md['tp-p_TimePoint'][0].id]==undefined){
        	tbData['P'+md['tp-p_Prestazione'][0].id]['T'+md['tp-p_TimePoint'][0].id]=[];
        }        
        tbData['P'+md['tp-p_Prestazione'][0].id]['T'+md['tp-p_TimePoint'][0].id][tbData['P'+md['tp-p_Prestazione'][0].id]['T'+md['tp-p_TimePoint'][0].id].length]=tpxp[t].id;
        //var tPos=md['tp-p_TimePoint'][0].metadata.TimePoint_col[0];
        if(md['tp-p_TimePoint']==undefined || md['tp-p_TimePoint'][0]==undefined){
            notDisplayed[notDisplayed.length]=tpxp.id;
            continue;
        }
        else if(timePointById[md['tp-p_TimePoint'][0].id]==undefined){
            continue;
        }
        var tPos=timePointById[md['tp-p_TimePoint'][0].id].metadata.TimePoint_col[0];
        //var pPos=md['tp-p_Prestazione'][0].metadata.Prestazioni_row[0];
        var pPos=prestazioniById[md['tp-p_Prestazione'][0].id].metadata.Prestazioni_row[0];
        if (!tpxpByTp[md['tp-p_TimePoint'][0].id]) tpxpByTp[md['tp-p_TimePoint'][0].id]={};
        tpxpByTp[md['tp-p_TimePoint'][0].id][tpxp[t].id]=tpxp[t];
        if (!tpxpByP[md['tp-p_Prestazione'][0].id]) tpxpByP[md['tp-p_Prestazione'][0].id]={};
        tpxpByP[md['tp-p_Prestazione'][0].id][tpxp[t].id]=tpxp[t];
        tpxpById[tpxp[t].id]=tpxp[t];
        var rimborsabilita=0;
        if (md.Rimborso_Rimborsabilita && md.Rimborso_Rimborsabilita[0]) 
        	rimborsabilita=md.Rimborso_Rimborsabilita[0]-0;
        var cellId='t_'+tPos+'_p_'+pPos;
        var cellColor='lightblue';
        var rimbContent=$('<a>');
        var cell=$('#'+cellId);
        rimbContent.attr('href','#');
        rimbContent.addClass('changeRimbType');
        rimbContent.addClass('crosscheck'); 
        rimbContent.html("<i class='fa fa-check-square-o'></i>&nbsp;");
        rimbContent.attr('data-elid',tpxp[t].id);
        var altTitle='extra SSN/SSR (rimborsato dallo sponsor)';
        cell.removeClass('extraSSN');
        cell.removeClass('extraSponsor');
        cell.removeClass('ssn');
        if (rimborsabilita==0) {
        	cell.addClass('extraSSN');
        	rimbContent.addClass('extraSSN');
            altTitle='extra SSN/SSR (rimborsato dallo sponsor)';
        }
        if (rimborsabilita==1) {
            rimbContent.addClass('extraSponsor');
            cell.addClass('extraSponsor');
            altTitle='SSN/SSR ma rimborsato dallo sponsor';
        }
        if (rimborsabilita==2) {
            cell.addClass('ssn');
            rimbContent.addClass('ssn');
            altTitle='SSN/SSR';
        }
        rimbContent.attr('alt',altTitle);
        rimbContent.attr('title',altTitle);

        cell.html(rimbContent);
        var cellAltTitle='Visita '+md['tp-p_TimePoint'][0].metadata.TimePoint_NumeroVisita[0]+" - Prestazione "+md['tp-p_Prestazione'][0].metadata.Prestazioni_prestazione[0];
        cell.attr('alt', cellAltTitle);
        cell.attr('title', cellAltTitle);
        cell.unbind("click");
        if(!totCountExtraCols[md['tp-p_TimePoint'][0].id])  totCountExtraCols[md['tp-p_TimePoint'][0].id] = 0;
        if(!totCountSSNCols[md['tp-p_TimePoint'][0].id])  totCountSSNCols[md['tp-p_TimePoint'][0].id] = 0;
        if (!totCountExtraRows[md['tp-p_Prestazione'][0].id]) totCountExtraRows[md['tp-p_Prestazione'][0].id]=0;
        if (!totCountSSNRows[md['tp-p_Prestazione'][0].id]) totCountSSNRows[md['tp-p_Prestazione'][0].id]=0;
        if(!totCostiCols[md['tp-p_TimePoint'][0].id])  totCostiCols[md['tp-p_TimePoint'][0].id] = 0;
        if(!totPrezziCols[md['tp-p_TimePoint'][0].id])  totPrezziCols[md['tp-p_TimePoint'][0].id] = 0;
        if(!totCountsCols[md['tp-p_TimePoint'][0].id])  totCountsCols[md['tp-p_TimePoint'][0].id] = 0;

        totCountsCols[md['tp-p_TimePoint'][0].id]++;

        if (rimborsabilita!=2){
            if (md.Costo_TransferPrice && md.Costo_TransferPrice[0]) {
                totRows[md['tp-p_Prestazione'][0].id]++;

                cell.append("<br/>");
                var rowIdx=md['tp-p_Prestazione'][0]['metadata']['Prestazioni_row'][0]-0;
                var colIdx=md['tp-p_TimePoint'][0]['metadata']['TimePoint_col'][0]-0;
                var tPrice=md.Costo_TransferPrice[0]-0;

                var tCosto=0;
                if(md.Costo_Costo!==undefined){
                    md.Costo_Costo[0]-0;
                }

                if (!rowTots[rowIdx]) rowTots[rowIdx] = 0;
                if (!totTpExtraRoutine[md['tp-p_Prestazione'][0].id]) totTpExtraRoutine[md['tp-p_Prestazione'][0].id] =0;
                if (!totCostiRowsA[md['tp-p_Prestazione'][0].id]) totCostiRowsA[md['tp-p_Prestazione'][0].id] =0;
                if (!totCostiRowsB[md['tp-p_Prestazione'][0].id]) totCostiRowsB[md['tp-p_Prestazione'][0].id] =0;
                if (!totCostiRowsC[md['tp-p_Prestazione'][0].id]) totCostiRowsC[md['tp-p_Prestazione'][0].id] =0;
                if (!totCostiRowsD[md['tp-p_Prestazione'][0].id]) totCostiRowsD[md['tp-p_Prestazione'][0].id] =0;
                //alert(rowIdx+" - "+tCosto+" - "+colIdx);
                rowTots[rowIdx]+=tPrice;
                totTpExtraRoutine[md['tp-p_Prestazione'][0].id]+=tPrice;

                if (!totCountExtraRowsA[md['tp-p_Prestazione'][0].id]) totCountExtraRowsA[md['tp-p_Prestazione'][0].id]=0;
                if (!totCountExtraRowsB[md['tp-p_Prestazione'][0].id]) totCountExtraRowsB[md['tp-p_Prestazione'][0].id]=0;
                if (!totCountExtraRowsC[md['tp-p_Prestazione'][0].id]) totCountExtraRowsC[md['tp-p_Prestazione'][0].id]=0;
                if (!totCountExtraRowsD[md['tp-p_Prestazione'][0].id]) totCountExtraRowsD[md['tp-p_Prestazione'][0].id]=0;
                totCostiCols[md['tp-p_TimePoint'][0].id]+=tCosto;
                totPrezziCols[md['tp-p_TimePoint'][0].id]+=tPrice;
                totCountExtraCols[md['tp-p_TimePoint'][0].id]++;
                totCountExtraRows[md['tp-p_Prestazione'][0].id]++;
                if(md.Costo_Copertura!==undefined) {
                    var copertura = md.Costo_Copertura[0];
                }
                if(copertura){
                    if(copertura.match("^1###")){
                        totCountExtraRowsA[md['tp-p_Prestazione'][0].id]++;
                        totCostiRowsA[md['tp-p_Prestazione'][0].id]+=tCosto;
                    }
                    else if(copertura.match("^2###")){
                        totCountExtraRowsB[md['tp-p_Prestazione'][0].id]++;
                        totCostiRowsB[md['tp-p_Prestazione'][0].id]+=tCosto;
                    }
                    else if(copertura.match("^3###")){
                        totCountExtraRowsC[md['tp-p_Prestazione'][0].id]++;
                        totCostiRowsC[md['tp-p_Prestazione'][0].id]+=tCosto;
                    }
                    else if(copertura.match("^4###")){
                        totCountExtraRowsD[md['tp-p_Prestazione'][0].id]++;
                        totCostiRowsD[md['tp-p_Prestazione'][0].id]+=tCosto;
                    }
                }
                if (colTots[colIdx]==undefined){
                	colTots[colIdx]=0;
                }
                colTots[colIdx]+=tPrice;
                patTot+=tPrice;
                cell.append(formatPrice(md.Costo_TransferPrice[0]));
                cell.append("&nbsp;");
                var editBudget=$('<a>');
                editBudget.html("<i class='fa fa-pencil'></i>");
                editBudget.attr('alt','modifica i valori di budget');
                editBudget.attr('title','modifica i valori di budget');
                editBudget.addClass('editBudgetTpxp');
                editBudget.attr('href','#');
                editBudget.attr('data-elid',tpxp[t].id);
                cell.append(editBudget);
            }else {
                cell.append("<br/>");
                var addBudget=$('<a>');
                addBudget.html("<i class='fa fa-plus'></i> aggiungi costi");
                addBudget.attr('alt','aggiungi costi');
                addBudget.attr('title','aggiungi costi');
                addBudget.addClass('addBudgetTpxp');
                addBudget.attr('href','#');
                addBudget.attr('data-elid',tpxp[t].id);
                cell.append(addBudget);
            }
        }else{
            totCountSSNCols[md['tp-p_TimePoint'][0].id]++;
            totCountSSNRows[md['tp-p_Prestazione'][0].id]++;
        }
        var deleteCross=$('<a>');
        deleteCross.html("<i class='fa fa-trash red'></i>");
        deleteCross.attr('alt','elimina la prestazione nella visita corrente');
        deleteCross.attr('title','elimina la prestazione nella visita corrente');
        deleteCross.attr('href','#');
        deleteCross.addClass('deleteTpxp');
        deleteCross.attr('data-elid',tpxp[t].id);
        cell.append('&nbsp;');
        cell.append(deleteCross);
    }
    aggiornaInfoBudgetPDF();
    duplicatedTpxp=[];
    var pkeys=Object.keys(tbData);
    for (var p in pkeys){
    	var tkeys=Object.keys(tbData[pkeys[p]]);
    	for (var t in tkeys){
    		if (tbData[pkeys[p]][tkeys[t]].length>1){
    			for (i=0;i<tbData[pkeys[p]][tkeys[t]].length-1;i++){
    				duplicatedTpxp[duplicatedTpxp.length]=tbData[pkeys[p]][tkeys[t]][i]
    			}
    		}
    	}
    }
    
    for(var d=0;d<duplicatedTpxp.length;d++){
    	console.log('Elimino doppio tpxp '+duplicatedTpxp[d]);
    	/*
    	$.getJSON(baseUrl+"/app/rest/documents/delete/"+duplicatedTpxp[d], function(data) {
    		console.log('Eliminato doppio tpxp');
    	});
    	*/
    }
    
    var keys = Object.keys(rowTots);
    for(c=0;c<keys.length;c++){
    	i=keys[c];
    	$('.flow-prestazioni-container .row-price[data-row-idx='+i+']').html("<strong>Totale</strong>: "+formatPrice(rowTots[i]));
    	$('.flow-prestazioni-container .row-price[data-row-idx='+i+']').css('display','block');
        $('.flow-prestazioni-container .row-price[data-row-idx='+i+']').parent().parent().find('.flow-prestazioni-container').css('float','left');
    	$('.flow-prestazioni-container .row-price[data-row-idx='+i+']').parent().parent().find('.flow-prestazioni-action-container').css('margin-top','-6px');
    }
    var keys = Object.keys(colTots);
    for(i=0;i<keys.length;i++){
    	colIdx=keys[i];  
    	if (colTots[colIdx]){
        		$('.col-price[data-col-idx='+colIdx+']').html(formatPrice(colTots[colIdx]));
    	}
    }
    $('#patTotPrice').html(formatPrice(patTot));
    
    $('a.deleteTpxp').click(function(){
        var crossId=$(this).attr('data-elid');
        deleteCrossfn(crossId);
        return false;
    });
    $('a.addBudgetTpxp').click(function(){
        var crossId=$(this).attr('data-elid');
        addBudgetTpxp(crossId);
        return false;
    });
    $('a.editBudgetTpxp').click(function(){
        var crossId=$(this).attr('data-elid');
        editBudgetTpxp(crossId);
        return false;
    });$('a.changeRimbType').click(function(){
        var crossId=$(this).attr('data-elid');
        changeRimbType('Modifica regime di rimborsabilit&agrave;', crossId);
        return false;
    });
}
function aggiornaInfoBudgetPDF(){

    $.each(prestazioniById,function(idx){
                var postData={};

                postData['InfoBudgetPDF_TotTpExtraRoutine']=totTpExtraRoutine[idx];

                postData['InfoBudgetPDF_TotCostoExtraRoutineA']=totCostiRowsA[idx];
                postData['InfoBudgetPDF_TotCostoExtraRoutineB']=totCostiRowsB[idx];
                postData['InfoBudgetPDF_TotCostoExtraRoutineC']=totCostiRowsC[idx];
                postData['InfoBudgetPDF_TotCostoExtraRoutineD']=totCostiRowsD[idx];
                postData['InfoBudgetPDF_TotCostoExtraRoutine']=totCostiRowsA[idx]+totCostiRowsB[idx]+totCostiRowsC[idx]+totCostiRowsD[idx];
                postData['InfoBudgetPDF_NumSSNRoutine']=totCountSSNRows[idx];
                postData['InfoBudgetPDF_NumExtraRoutine']=totCountExtraRows[idx];
                postData['InfoBudgetPDF_NumTotali']=totCountSSNRows[idx]+totCountExtraRows[idx];
                postData['InfoBudgetPDF_NumExtraRoutineA']=totCountExtraRowsA[idx];
                postData['InfoBudgetPDF_NumExtraRoutineB']=totCountExtraRowsB[idx];
                postData['InfoBudgetPDF_NumExtraRoutineC']=totCountExtraRowsC[idx];
                postData['InfoBudgetPDF_NumExtraRoutineD']=totCountExtraRowsD[idx];

                $.post(baseUrl+"/app/rest/documents/update/"+idx,postData,function(data){
                    console.log(data);
                });
    });
    $.each(timePointById,function(idx){
                var postData={};
                postData['InfoBudgetPDF_TotTpExtraRoutine']=totPrezziCols[idx];
                postData['InfoBudgetPDF_TotCostoExtraRoutine']=totCostiCols[idx];
                postData['InfoBudgetPDF_NumSSNRoutine']=totCountSSNCols[idx];
                postData['InfoBudgetPDF_NumExtraRoutine']=totCountExtraCols[idx];
                postData['InfoBudgetPDF_NumTotali']=totCountSSNCols[idx]+totCountExtraCols[idx];
                $.post(baseUrl+"/app/rest/documents/update/"+idx,postData,function(data){
                    console.log(data);
                });

    });
}
function timePointCompare(a,b){
    if (!a.metadata.TimePoint_col) aPos=0;
    else aPos=a.metadata.TimePoint_col[0]-0;
    if (!b.metadata.TimePoint_col) aPos=0;
    else bPos=b.metadata.TimePoint_col[0]-0;
    if (aPos < bPos)
        return -1;
    if (aPos > bPos)
        return 1;
    return 0;
}

function prestazioniCompare(a,b){
    aPos=a.metadata.Prestazioni_row[0]-0;
    bPos=b.metadata.Prestazioni_row[0]-0;
    if (aPos < bPos)
        return -1;
    if (aPos > bPos)
        return 1;
    return 0;
}


function editPrest(prestId){
    var prestForm=$('#prestazione-diz-dialog').clone();
    prestForm.attr('id', 'prestFormId');
    prestForm.show();
    showPrestazioniForm("Modifica prestazione", prestForm, false, prestId)
}

var reOrdering=null;
var reOrderingInterval=null;

function movePrest(prestId){
    var positions=[];
    var actPos=prestazioniById[prestId].metadata.Prestazioni_row[0]-0;
    var actPosH=actPos+1;
    for (var rowIdx=0;rowIdx<tbRow2MdId.length;rowIdx++){
        if (tbRow2MdId[rowIdx]!=prestId){
            var thisOption=new Object();
            var rowIdxH=rowIdx+1;
            thisOption.text="a riga "+rowIdxH;
            thisOption.value=rowIdx;
            positions[positions.length]=thisOption;
        }
    }
    bootbox.prompt({
        title: "Sposta prestazione da riga "+actPosH,
        inputType: 'select',
        inputOptions: positions,
        callback: function (result) {
            if (result){
                loadingScreen("Riordino le prestazioni");
                reOrdering=0;
                var futPos=result;
                if (actPos>futPos){ //Spostamento verso l'alto
                    for (var i=0;i<prestazioni.length;i++){
                        var pPos=prestazioni[i].metadata.Prestazioni_row[0]-0;
                        if (pPos < actPos && pPos >= futPos){
                            var postObj=new Object();
                            postObj.name="Prestazioni_row";
                            postObj.value=pPos+1;
                            var updateUrl=baseUrl+'/app/rest/documents/updateField/'+prestazioni[i].id;
                            reOrdering++;
                            $.post(updateUrl, postObj).done(function(data){
                                reOrdering--;
                                if (data.result!='OK') bootbox.alert('Errore');
                            });
                        }
                    }
                }else { //Spostamento verso il basso
                    for (var i=0;i<prestazioni.length;i++) {
                        var pPos = prestazioni[i].metadata.Prestazioni_row[0] - 0;
                        if (pPos <= futPos && pPos > actPos) {
                            reOrdering++;
                            var postObj = new Object();
                            postObj.name = "Prestazioni_row";
                            postObj.value = pPos - 1;
                            var updateUrl = baseUrl + '/app/rest/documents/updateField/' + prestazioni[i].id;
                            $.post(updateUrl, postObj).done(function (data) {
                                reOrdering--;
                                if (data.result != 'OK') bootbox.alert('Errore');
                            });
                        }
                    }
                }
                var postObj=new Object();
                postObj.name="Prestazioni_row";
                postObj.value=futPos;
                var updateUrl=baseUrl+'/app/rest/documents/updateField/'+prestId;
                reOrdering++;
                $.post(updateUrl, postObj).done(function(data){
                    reOrdering--;
                    if (data.result!='OK') bootbox.alert('Errore');
                });
                reOrderingInterval= setInterval(function(){
                    if (reOrdering==null || reOrdering==0){
                        clearInterval(reOrderingInterval);
                        loadFolderPrestazioni();
                        bootbox.hideAll();
                    }
                }, 500);
            }
        }
    });
}

function moveTP(tpId){
    var positions=[];
    var actPos=timePointById[tpId].metadata.TimePoint_col[0]-0;
    var actPosH=actPos+1;
    for (var colIdx=0;colIdx<tbCol2MdId.length;colIdx++){
        if (tbCol2MdId[colIdx]!=tpId){
            var thisOption=new Object();
            var colIdxH=colIdx+1;
            thisOption.text="alla colonna "+colIdxH;
            thisOption.value=colIdx;
            positions[positions.length]=thisOption;
        }
    }
    bootbox.prompt({
        title: "Sposta Visita da colonna "+actPosH,
        inputType: 'select',
        inputOptions: positions,
        callback: function (result) {
            if (result){
                loadingScreen("Riordino le prestazioni");
                reOrdering=0;
                var futPos=result;

                if (actPos>futPos){ //Spostamento verso l'alto
                    for (var i=0;i<timePoint.length;i++){
                        var pPos=timePoint[i].metadata.TimePoint_col[0]-0;
                        if (pPos < actPos && pPos >= futPos){
                            var postObj=new Object();
                            postObj.name="TimePoint_col";
                            postObj.value=pPos+1;
                            var updateUrl=baseUrl+'/app/rest/documents/updateField/'+timePoint[i].id;
                            reOrdering++;
                            $.post(updateUrl, postObj).done(function(data){
                                reOrdering--;
                                if (data.result!='OK') bootbox.alert('Errore');
                            });
                        }
                    }
                }else { //Spostamento verso il basso
                    for (var i=0;i<prestazioni.length;i++) {
                        if (prestazioni[i].metadata.TimePoint_col && prestazioni[i].metadata.TimePoint_col[0]){
                            var pPos = prestazioni[i].metadata.TimePoint_col[0] - 0;
                            if (pPos <= futPos && pPos > actPos) {
                                reOrdering++;
                                var postObj = new Object();
                                postObj.name = "TimePoint_col";
                                postObj.value = pPos - 1;
                                var updateUrl = baseUrl + '/app/rest/documents/updateField/' + timePoint[i].id;
                                $.post(updateUrl, postObj).done(function (data) {
                                    reOrdering--;
                                    if (data.result != 'OK') bootbox.alert('Errore');
                                });
                            }
                        }
                    }
                }
                var postObj=new Object();
                postObj.name="TimePoint_col";
                postObj.value=futPos;
                var updateUrl=baseUrl+'/app/rest/documents/updateField/'+tpId;
                reOrdering++;
                $.post(updateUrl, postObj).done(function(data){
                    reOrdering--;
                    if (data.result!='OK') bootbox.alert('Errore');
                });
                reOrderingInterval= setInterval(function(){
                    if (reOrdering==null || reOrdering==0){
                        clearInterval(reOrderingInterval);
                        loadTimePoints();
                        bootbox.hideAll();
                    }
                }, 500);
            }
        }
    });
}

function deletePrest(prestId){
    var deletePrestCalls=1;
    var errors=false;
    (function(deletePrestCalls, errors, prestId){
        bootbox.confirm("Sei sicuro di voler eleminare l'intera riga?", function(result){
            if (result){
                loadingScreen("Eliminazione prestazione in corso...");
                for (var tpxpid in tpxpByP[prestId]) {
                    deletePrestCalls++;
                    $.getJSON(baseUrl+"/app/rest/documents/delete/"+tpxpid, function(data){
                        deletePrestCalls--;
                        if (data.result!='OK'){
                            errors=true;
                        }
                        if (deletePrestCalls==0){
                            if (!errors) {
                                bootbox.hideAll();
                                loadFlow();
                            }else {
                                bootbox.alert("Errore!!!");
                            }
                        }
                    });
                }
                $.getJSON(baseUrl+"/app/rest/documents/delete/"+prestId, function(data){
                    deletePrestCalls--;
                    if (data.result!='OK'){
                        errors=true;
                    }
                    if (deletePrestCalls==0){
                        if (!errors) {
                            bootbox.hideAll();
                            loadFlow();
                        }else {
                            bootbox.alert("Errore!!!");
                        }
                    }
                });
            }
        });
    })(deletePrestCalls, errors, prestId);

}

function updTpField(tpId, fieldName, fieldValue) {
    var updateUrl=baseUrl+'/app/rest/documents/updateField/'+tpId;
    var postObj=new Object();
    postObj.name=fieldName;
    postObj.value=fieldValue;
    if (timePointById && timePointById[tpId]) {
        timePointById[tpId].metadata[fieldName][0]=fieldValue;
    }
    for (var i=0;i<timePoint.length;i++){
        if (tbCol2MdCol && tbCol2MdCol[i]) {
            tbCol2MdCol[i]=timePoint[i].metadata.TimePoint_col[0]-0;
            tbCol2MdId[i]=timePoint[i].id;
        }
        if (timePoint[i].id==tpId) {
            timePoint[i].metadata[fieldName][0]=fieldValue;
        }
    }
    $.post(updateUrl, postObj).done(function(data){
        if (data.result!='OK'){
            bootbox.alert('Errore sistemazione automativa Visite');
        }
    });
}

function updPrestField(tpId, fieldName, fieldValue) {

    var updateUrl=baseUrl+'/app/rest/documents/updateField/'+tpId;
    var postObj=new Object();
    postObj.name=fieldName;
    postObj.value=fieldValue;
    if (prestazioniById && prestazioniById[tpId]) {
        prestazioniById[tpId].metadata[fieldName][0]=fieldValue;
    }
    for (var i=0;i<prestazioni.length;i++){
        if (tbRow2MdRow && tbRow2MdRow[i]) {
            tbRow2MdRow[i]=prestazioni[i].metadata.Prestazioni_row[0]-0;
            tbRow2MdId[i]=prestazioni[i].id;

        }
        if (prestazioni[i].id==tpId) {
            prestazioni[i].metadata[fieldName][0]=fieldValue;
        }
    }
    $.post(updateUrl, postObj).done(function(data){
        if (data.result!='OK'){
            bootbox.alert('Errore sistemazione automativa Prestazioni');
        }
    });
}

function buildFlowchartTable(hideAll){
    if (!prestazioniLoaded || !timePointLoaded) return;
    prestazioniById={};
    timePointById={};
    timePoint.sort(timePointCompare);
    prestazioni.sort(prestazioniCompare);

    for (var i=0;i<timePoint.length;i++){
        var tpPos=timePoint[i].metadata.TimePoint_col[0]-0;
        if (tpPos!=i){
            updTpField(timePoint[i].id, 'TimePoint_col', i);
        }
    }

    for (var i=0;i<prestazioni.length;i++){
        var prestPos=prestazioni[i].metadata.Prestazioni_row[0]-0;
        if (prestPos!=i){
            updPrestField(prestazioni[i].id, 'Prestazioni_row', i);
        }
    }

    var container=$('#flowchartTable');
    container.html("");
    container.addClass('table-responsive');
    var tb=$('<table>');
    tb.addClass('');
    tb.attr('id','flowchartTableId');
    container.append(tb);
    var thead=$('<thead>');
    var thRow=$('<tr>');
    tb.append(thead);
    thead.append(thRow);
    thRow.append('<th>&nbsp;</th>');
    cols=1;
    tbCol2MdCol=[];
    tbCol2MdId=[];
    for (var colIdx=0;colIdx<timePoint.length;colIdx++){
        timePointById[timePoint[colIdx].id]=timePoint[colIdx];
        tbCol2MdCol[colIdx]=timePoint[colIdx].metadata.TimePoint_col[0]-0;
        tbCol2MdId[colIdx]=timePoint[colIdx].id;

        cols++;
        var visitSpec='Visita '+timePoint[colIdx].metadata.TimePoint_NumeroVisita[0];
        if (timePoint[colIdx].metadata.TimePoint_DescrizioneSelect && timePoint[colIdx].metadata.TimePoint_DescrizioneSelect[0])
            visitSpec+='<br/>'+timePoint[colIdx].metadata.TimePoint_DescrizioneSelect[0].split('###')[1];
        if (timePoint[colIdx].metadata.TimePoint_Tempi && timePoint[colIdx].metadata.TimePoint_TempiSelect && timePoint[colIdx].metadata.TimePoint_TempiSelect[0]) visitSpec+='<br/>Tempo: '+timePoint[colIdx].metadata.TimePoint_Tempi[0]+'&nbsp;'+timePoint[colIdx].metadata.TimePoint_TempiSelect[0].split('###')[1];
        //else visitSpec+="<br/>";
        if (timePoint[colIdx].metadata.TimePoint_DurataCiclo && timePoint[colIdx].metadata.TimePoint_DurataCiclo[0] && timePoint[colIdx].metadata.TimePoint_DurataSelect && timePoint[colIdx].metadata.TimePoint_DurataSelect[0]) visitSpec+='<br/>Durata: '+timePoint[colIdx].metadata.TimePoint_DurataCiclo[0]+'&nbsp;'+timePoint[colIdx].metadata.TimePoint_DurataSelect[0].split('###')[1];
        //else visitSpec+="<br/>";
        if (timePoint[colIdx].metadata.TimePoint_RicoveroSelect && timePoint[colIdx].metadata.TimePoint_RicoveroSelect[0]) visitSpec+='<br/>Ricovero: '+timePoint[colIdx].metadata.TimePoint_RicoveroSelect[0].split('###')[1];
        //else visitSpec+="<br/>";
        if (timePoint[colIdx].metadata.TimePoint_Note && timePoint[colIdx].metadata.TimePoint_Note!="") visitSpec+='<br/>Note: '+timePoint[colIdx].metadata.TimePoint_Note;
        //else visitSpec+="<br/>";
        var editLink=$('<a>');
        editLink.html("<i class='fa fa-pencil blue'></i>");
        editLink.addClass('editTP');
        editLink.attr('href','#');
        editLink.attr('data-elid',timePoint[colIdx].id);
        var cloneLink=$('<a>');
        cloneLink.html("<i class='fa fa-copy blue'></i>");
        cloneLink.addClass('cloneTP');
        cloneLink.attr('href','#');
        cloneLink.attr('data-elid',timePoint[colIdx].id);
        var moveLink=$('<a>');
        moveLink.html("<i class='fa fa-arrows black'></i>");
        moveLink.attr("alt", "Sposta visita");
        moveLink.attr("title", "Sposta visita");
        moveLink.attr('href','#');
        moveLink.addClass('moveTP');
        moveLink.attr('data-elid',timePoint[colIdx].id);
        var deleteLink=$('<a>');
        deleteLink.html("<i class='fa fa-trash red'></i>");
        deleteLink.attr('href','#');
        deleteLink.addClass('deleteTP');
        deleteLink.attr('data-elid',timePoint[colIdx].id);
        //TODO Registreare evento di delete
        var actionContainer=$('<div>');
        actionContainer.addClass('flow-tp-action-container');
        var innerActionContainer=$('<div>');
        innerActionContainer.append(editLink);
        innerActionContainer.append('&nbsp;');
        innerActionContainer.append(cloneLink);
        innerActionContainer.append('&nbsp;');
        innerActionContainer.append(moveLink);
        innerActionContainer.append('&nbsp;');
        innerActionContainer.append(deleteLink);
        actionContainer.append(innerActionContainer);
        var th=$('<th>');
        th.append(actionContainer);
        th.append(visitSpec);
        thRow.append(th);
        var thisCol=timePoint[colIdx].metadata.TimePoint_col[0]-0;
        nextCol=thisCol+1;
    }
    var tbody=$('<tbody>');
    var tbody2=$('<tbody>');
    var tbody3=$('<tbody>');
    tb.append(tbody);
    tbRow2MdRow=[];
    tbRow2MdId=[];
    for (var rowIdx=0;rowIdx<prestazioni.length;rowIdx++){
        prestazioniById[prestazioni[rowIdx].id]=prestazioni[rowIdx];
        tbRow2MdRow[rowIdx]=prestazioni[rowIdx].metadata.Prestazioni_row[0]-0;
        tbRow2MdId[rowIdx]=prestazioni[rowIdx].id;
        var prestazioniRow=$('<tr>');
        tbody.append(prestazioniRow);
        row=rowIdx+1;
        var prestRowContent=$('<td>');
        var prestRowContentText=row+') '+prestazioni[rowIdx].metadata.Prestazioni_prestazione[0];
        var prestActionContainer=$('<div>');
        prestActionContainer.addClass('flow-prestazioni-action-container');
        var editLink=$('<a>');
        editLink.html("<i class='fa fa-pencil blue'></i>");
        editLink.attr("alt", "Modifica prestazione");
        editLink.attr("title", "Modifica prestazione");
        editLink.addClass('editPrest');
        editLink.attr('href','#');
        editLink.attr('data-elid',prestazioni[rowIdx].id);
        var moveLink=$('<a>');
        moveLink.html("<i class='fa fa-arrows black'></i>");
        moveLink.attr("alt", "Sposta riga");
        moveLink.attr("title", "Sposta riga");
        moveLink.attr('href','#');
        moveLink.addClass('movePrest');
        moveLink.attr('data-elid',prestazioni[rowIdx].id);
        var deleteLink=$('<a>');
        deleteLink.html("<i class='fa fa-trash red'></i>");
        deleteLink.attr("alt", "Elimina prestazione da budget");
        deleteLink.attr("title", "Elimina prestazione da budget");
        deleteLink.attr('href','#');
        deleteLink.addClass('deletePrest');
        deleteLink.attr('data-elid',prestazioni[rowIdx].id);
        prestActionContainer.append(editLink);
        prestActionContainer.append("&nbsp;");
        prestActionContainer.append(moveLink);
        prestActionContainer.append("&nbsp;");
        prestActionContainer.append(deleteLink);
        prestazioniRow.append(prestRowContent);
        prestRowContent.append(prestActionContainer);
        var prestRowContentTextContainer=$('<div>');
        prestRowContentTextContainer.addClass('flow-prestazioni-container');
        prestRowContentTextContainer.append(prestRowContentText);
        var spanPrezzo=$('<span>');
        spanPrezzo.addClass('row-price');
        spanPrezzo.attr('data-row-idx', rowIdx);
        prestRowContentTextContainer.append(spanPrezzo);
        prestRowContent.append(prestRowContentTextContainer);
        var pPos=prestazioni[rowIdx].metadata.Prestazioni_row[0];
        for (var colIdx=0;colIdx<timePoint.length;colIdx++){
            var tPos=timePoint[colIdx].metadata.TimePoint_col[0];
            var cell=$('<td>');
            cell.attr('id','t_'+tPos+'_p_'+pPos);
            cell.attr('data-prestazione-id', prestazioni[rowIdx].id);
            cell.attr('data-timepoint-id', timePoint[colIdx].id);
            var altTitle='Visita '+timePoint[colIdx].metadata.TimePoint_NumeroVisita[0]+' - Clicca per abilitare la prestazione "'+prestazioni[rowIdx].metadata.Prestazioni_prestazione[0];
            cell.attr('alt',altTitle);
            cell.attr('title',altTitle);
            prestazioniRow.append(cell);
            cell.click(function(){
                createTpxp($(this).attr('data-prestazione-id'), $(this).attr('data-timepoint-id'));
            });
        }
        nextRow=prestazioni[rowIdx].metadata.Prestazioni_row[0];
        nextRow-=0;
        nextRow++;
    }
    var totaliRow=$('<tr>');
    var totHeaderCell=$('<td>');
    totHeaderCell.html("<strong>Totale</strong>");
    totHeaderCell.addClass('totCols');
    totaliRow.append(totHeaderCell);
    for (var colIdx=0;colIdx<timePoint.length;colIdx++){
        var singleColTotCell=$('<td>');
        singleColTotCell.addClass('col-price');
        singleColTotCell.attr('data-col-idx',colIdx);
        singleColTotCell.css('background-color','white');
        totaliRow.append(singleColTotCell);
    }

    tbody.append(totaliRow);
    colModal=[];
    for (var i=0;i<cols;i++){
        colModal[i]={};
        colModal[i].width=100;
        colModal[i].align='center';

    }
    flowchartTableBuilded=true;
    if (tpxpLoaded)	populateTpxp();
    $('#flowchartTableId').fxdHdrCol({
        fixedCols: 1,
        width:     "100%",
        height:    650,
        colModal: colModal
    });

    var tbHeight=94+(45*prestazioni.length)+65;
    
    $('.ft_r th:nth-child(1)').css('min-width',$('.ft_c').css('width'));
    $('.ft_container').css('max-height', tbHeight+"px");
    $('.ft_container').css('height', tbHeight+"px");
    tbHeight-=20;
    $('.ft_cwrapper').css('height', tbHeight+"px");
     $('a.editTP').click(function(){
         tpId=$(this).attr('data-elid');
         (function(tpMd){
             editTp(tpMd);
         })(timePointById[tpId]);
         return false;
     });
    $('a.cloneTP').click(function(){
        tpId=$(this).attr('data-elid');
        (function(tpId){
            cloneTp(tpId);
        })(tpId);
        return false;
    });

    $('a.deleteTP').click(function(){
        tpId=$(this).attr('data-elid');
        (function(tpId){
            deleteVisit(tpId);
        })(tpId);
        return false;
    });

    $('a.moveTP').click(function(){
        moveTP($(this).attr('data-elid'));
        return false;
    });

    $('a.movePrest').click(function(){
         movePrest($(this).attr('data-elid'));
         return false;
    });

    $('a.editPrest').click(function(){
        editPrest($(this).attr('data-elid'));
        return false;
    });

    $('a.deletePrest').click(function(){
        deletePrest($(this).attr('data-elid'));
        return false;
    });

    if (hideAll!=null && hideAll==true){
        bootbox.hideAll();
    }
}

function formatPrice(priceString){
    var price= priceString-0;
    return "&euro; "+price.toFixed(2);
}

function deleteVisit(tpId){
    var deleteVisitCalls=1;
    var errors=false;
    (function(deleteVisitCalls,errors){
        bootbox.confirm("Sei sicuro di voler eleminare l'intera visita?", function(result){
            if (result){
                loadingScreen("Eliminazione visita...");
                for (var tpxpid in tpxpByTp[tpId]) {
                    deleteVisitCalls++;
                    $.getJSON(baseUrl+"/app/rest/documents/delete/"+tpxpid, function(data){
                        deleteVisitCalls--;
                        if (data.result!='OK'){
                            errors=true;
                        }
                        if (deleteVisitCalls==0){
                            if (!errors) {
                                bootbox.hideAll();
                                loadFlow();
                            }else {
                                bootbox.alert("Errore!!!");
                            }
                        }
                    });
                }
                $.getJSON(baseUrl+"/app/rest/documents/delete/"+tpId, function(data){
                    deleteVisitCalls--;
                    if (data.result!='OK'){
                        errors=true;
                    }
                    if (deleteVisitCalls==0){
                        if (!errors) {
                            bootbox.hideAll();
                            loadFlow();
                        }else {
                            bootbox.alert("Errore!!!");
                        }
                    }
                });
            }
        });
    })(deleteVisitCalls, errors);
}

function addTp(){
    var tpForm=null;
    tpForm = $('#tp-dialog-form').clone();
    tpForm.attr('id', 'modalForm-tp');
    tpForm.find('form input[name="parentId"]').val(folderTimePointId);
    tpForm.find('form input[name="TimePoint_col"]').val(nextCol);
    var postUrl=baseUrl + "/app/rest/documents/save/TimePoint";
    tpForm.find('form').attr('action', postUrl);
    showTpForm('Aggiungi Visita', tpForm);
}

function editTp(tpMd){
    var tpForm=null;
    tpForm = $('#tp-dialog-form').clone();
    tpForm.attr('id', 'modalForm-tp');
    tpForm.find('form input[name="parentId"]').val(folderTimePointId);
    for (var mdIdx in tpMd.metadata){
        tpForm.find('[name="'+mdIdx+'"]').val(tpMd.metadata[mdIdx][0]);
    }
    var postUrl=baseUrl+"/app/rest/documents/update/"+tpMd.id;
    tpForm.find('form').attr('action', postUrl);
    showTpForm('Modifica Visita', tpForm, tpMd);
}


function showPrestazioniForm(title, prestForm, isNew, prestId){
    bootbox.dialog({
        title: title,
        message: prestForm,
        closeButton:false,
        buttons: {
            cancel: {
                label: '<i class="fa fa-times"></i> Annulla',
                callback: function (result) {
                    $('#prestFormId').remove();
                }
            },
            confirm: {
                label: '<i class="fa fa-check"></i> Aggiungi prestazione',
                callback: function (result) {
                    return savePrestazione();

                }
            }
        }
    }).on("shown.bs.modal", function(e) {
        prestazioniFormInit();
        if (isNew){
            if ($('#prestFormId form input[name="Prestazioni_row"]').length==0){
                $('#prestFormId form').append('<input type="hidden" name="Prestazioni_row" value="'+nextRow+'"/>');
            }
            if ($('#prestFormId form input[name="parentId"]').length==0){
                $('#prestFormId form').append('<input type="hidden" name="parentId" value="'+folderPrestazioniId+'"/>');
            }
            var postUrl=baseUrl + "/app/rest/documents/save/Prestazione";
            $('#prestFormId form').attr('action', postUrl);
        }else {
            if (prestId!=null){
                for (var fieldName in prestazioniById[prestId].metadata){
                    if (prestazioniById[prestId].metadata[fieldName] && prestazioniById[prestId].metadata[fieldName][0]){


                        if (prestazioniById[prestId].metadata[fieldName+'Code'] && prestazioniById[prestId].metadata[fieldName+'Code'][0]){

                            var selectedValue=prestazioniById[prestId].metadata[fieldName+'Code'][0]+'###'+prestazioniById[prestId].metadata[fieldName][0];
                            if(prestazioniById[prestId].metadata[fieldName+'Code'][0]=='9999'){ //HDCRPMS-796
                                selectedValue="9999###Altro";
                            }
                            $('#prestFormId form [name="'+fieldName+'Select"]').val(selectedValue).trigger("change");//HDCRPMS-796
                        }
                        if($('#prestFormId form input[name="'+fieldName+'"]').attr("type")=="radio"){
                            $('#prestFormId form input[name="'+fieldName+'"][value="'+prestazioniById[prestId].metadata[fieldName][0]+'"]').attr("checked",true).change();
                        }
                        else{
                            $('#prestFormId form input[name="'+fieldName+'"]').val(prestazioniById[prestId].metadata[fieldName][0]);
                        }
                    }
                }
                var postUrl=baseUrl + "/app/rest/documents/update/"+prestId;
                $('#prestFormId form').attr('action', postUrl);
            }
        }
    });
}

var tpFormUuid=null;

function showTpForm(title, tpForm, md) {
	tpFormUuid=Math.random().toString(16).slice(2);
	tpForm.attr('data-id','uuid'+tpFormUuid);
	//tpForm.find('select').select2();
	setTimeout(function(){
			var fields=[];
			fields[0]='TimePoint_DescrizioneSelect';
			fields[1]='TimePoint_TempiSelect';
			//fields[2]='TimePoint_DurataSelect';
			fields[2]='TimePoint_RicoveroSelect';
			for (i=0;i<fields.length;i++){
				var data;
				if (md != undefined && md.metadata !=undefined && md.metadata[fields[i]] != undefined){
					data=md.metadata[fields[i]][0];
				}
				jsInitFieldFunctions[fields[i]]('[data-id=uuid'+tpFormUuid+']', data);
			}
        $(tpForm).find('[id=TimePoint-TimePoint_Descrizione]').hide();
            $(tpForm).find('[name=TimePoint_DescrizioneSelect-select]').change(function(){
                var value=$(this).find('option:selected').val();
                if(value && value.match(/7###/)){
                    $(tpForm).find('[id=TimePoint-TimePoint_Descrizione]').show();
                }else{
                    $(tpForm).find('[id=TimePoint-TimePoint_Descrizione]').hide();
                }
            });

    }, 500);
    var diag=bootbox.dialog({
        title: title,
        message: tpForm,
        closeButton:false,
        buttons: {
            cancel: {
                label: '<i class="fa fa-times"></i> Annulla',
                callback: function (result) {
                    $('#modalForm-tp').remove();
                }
            },
            confirm: {
                label: '<i class="fa fa-check"></i> Aggiungi visita',
                callback: function (result) {
                    return saveTp();
                }
            }
        }
    });
}


function saveTp(){
    if (!$('#modalForm-tp form [name="TimePoint_DescrizioneSelect"]').val() || $('#modalForm-tp form [name="TimePoint_DescrizioneSelect"]').val()==''){
        bootbox.alert('Inserire la descrizione');
        return false;
    }
    if (!$('#modalForm-tp form [name="TimePoint_NumeroVisita"]').val() || $('#modalForm-tp form [name="TimePoint_NumeroVisita"]').val()==''){
        bootbox.alert('Inserire il numero della visita');
        return false;
    }
    if ($('#modalForm-tp form [name="TimePoint_NumeroVisita"]').val() && isNaN($('#modalForm-tp form [name="TimePoint_NumeroVisita"]').val())){
        bootbox.alert('Inserire un valore numerico nel campo "Numero Visita"');
        return false;
    }
    if ($('#modalForm-tp form [name="TimePoint_Tempi"]').val() && isNaN($('#modalForm-tp form [name="TimePoint_Tempi"]').val())){
        bootbox.alert('Inserire un valore numerico nel campo "Tempo"');
        return false;
    }
    if ($('#modalForm-tp form [name="TimePoint_DurataCiclo"]').val() && isNaN($('#modalForm-tp form [name="TimePoint_DurataCiclo"]').val())){
        bootbox.alert('Inserire un valore numerico nel campo "Durata"');
        return false;
    }
    loadingScreen("salvataggio in corso");
    var url=$('#modalForm-tp form').attr('action');
    $.post(url, $('#modalForm-tp form').serialize()).done(function(data){
        if (data.result!='OK'){
            bootbox.hideAll();
            bootbox.alert('Attenzione!!! Errore nel salvataggio della visita');
        }else {
            $.getJSON(baseUrl+"/app/rest/documents/getElementJSON/"+data.ret, function(data) {
                var isNew=true;
                for (var i=0;i<timePoint.length;i++){
                    if (timePoint[i].id==data.id){
                        isNew=false;
                        timePoint[i]=data;
                    }
                }
                if (isNew) timePoint[timePoint.length]=data;
                buildFlowchartTable();
            });
            bootbox.hideAll();
        }
    });
    $('#modalForm-tp').remove();
}
var cloneTpajax=0;
var cloneTpajaxRaiseError=false;
function cloneTp(sourceTpId){
    cloneTpajaxRaiseError=false;
    loadingScreen("salvataggio in corso");
    var postUrl=baseUrl + "/app/rest/documents/save/TimePoint";
    var postData= new Object();
    var sourceData=timePointById[sourceTpId].metadata;
    $.each(sourceData,function(key,value){
        if(key.includes('TimePoint_')){
            postData[key]=value;
        }
    });
    postData['TimePoint_col']=timePoint.length;//sovrascrivo la colonna mettendola alla fine
    if(postData['TimePoint_Note']!="") {
        postData['TimePoint_Note'] += " - Copiata da Visita " + timePointById[sourceTpId].metadata['TimePoint_NumeroVisita'];
    }
    else{
        postData['TimePoint_Note'] = "Copiata da Visita " + timePointById[sourceTpId].metadata['TimePoint_NumeroVisita'];
    }
    postData['parentId']=timePointById[sourceTpId].parentId;
    console.log(postData);
    $.post(postUrl, postData).done(function(data){
        if (data.result!='OK'){
            bootbox.hideAll();
            bootbox.alert('Attenzione!!! Errore nel salvataggio della visita');
        }else {
            timePointLoaded=false;
            loadTimePoints();

            var postUrlTpxp=baseUrl + "/app/rest/documents/save/tpxp";
            var postDataTpxp=new Object();
            postDataTpxp.parentId=folderTpxpId;

            $.each(tpxpByTp[sourceTpId],function(sourceTpxpID,sourceTpxp){
                var sourceDataTpxp=sourceTpxp.metadata;
                $.each(sourceDataTpxp,function(key,value){
                    if(!key.includes('tp-p_Prestazione')) {
                        postDataTpxp[key] = value;
                    }
                });
                postDataTpxp['tp-p_TimePoint']=data.ret;//sovrascrivo con la TimePoint nuova
                postDataTpxp['tp-p_Prestazione']=sourceTpxp.metadata['tp-p_Prestazione'][0].id;//sovrascrivo con la Prestazione nuova
                cloneTpajax++;
                $.ajax({
                    type: 'POST',
                    url: postUrlTpxp,
                    data: postDataTpxp,
                    success: function(dataTpxp){
                        if (dataTpxp.result != 'OK') {
                            cloneTpajaxRaiseError = true;
                        } else {
                            $.getJSON(baseUrl + "/app/rest/documents/getElementJSON/" + dataTpxp.ret, function (dataTpxp) {
                                tpxp[tpxp.length]=dataTpxp;
                                tpxpById[dataTpxp.id]=dataTpxp;
                                //changeRimbType('Selezione regime di rimborsabilit&agrave;', data.id);
                                populateTpxp();

                            });
                            cloneTpajax--;
                            if(cloneTpajax==0){
                                if (cloneTpajaxRaiseError){
                                    bootbox.hideAll();
                                    bootbox.alert('Attenzione!!! Errore nella copia della visita ');
                                }else {
                                    buildFlowchartTable();
                                    bootbox.hideAll();
                                }
                            }
                        }
                    },
                    dataType: 'json',
                    async:true
                });
            });

        }
    });
}





function savePrestazione(){
    if (!$('#prestFormId form [name="Prestazioni_prestazione"]').val() || $('#prestFormId form [name="Prestazioni_prestazione"]').val()==''){
        bootbox.alert('Necessario inserire una prestazione');
        return false;
    }
    if (!$('#prestFormId form [name="Prestazioni_CDC"]').val() || $('#prestFormId form [name="Prestazioni_CDC"]').val()==''){
        bootbox.alert('Necessario inserire uno centro di costo');
        return false;
    }
    loadingScreen("salvataggio in corso");
    var url=$('#prestFormId form').attr('action');
    $('#prestFormId form [name="Prestazioni_CDCSelect"]').remove();

    var isNew=true;
    if (url.indexOf("update")) isNew=false;
    (function(flag){
        $.post(url, $('#prestFormId form').serialize()).done(function(data){
            if (data.result!='OK'){
                bootbox.hideAll();
                bootbox.alert('Attenzione!!! Errore nel salvataggio della prestazione');
            }else {
                if (flag) {
                   $.getJSON(baseUrl + "/app/rest/documents/getElementJSON/" + data.ret, function (data) {
                        prestazioni[prestazioni.length] = data;
                        buildFlowchartTable();
                    });
                } else {
                    prestazioniLoaded = false;
                    loadFolderPrestazioni();
                }
            bootbox.hideAll();
            }
        });
    })(isNew);
    $('#prestFormId').remove();
}

function loadFlow(){
    loadFolderPrestazioni();
    loadTimePoints();
    loadTpxp();
}

$('button.addVisit').click(function(){
    addTp();
});


$('button.addPrestazione').click(function(){
    addPrestazione();
});

$('button.applicaSSN').click(function(){
    applicaSSN();
});


function deleteCrossfn(crossId){
    bootbox.confirm("Sei sicuro di voler procedere?", function(result){
        if (result){
            loadingScreen("Eliminazione in corso ...");
            $.getJSON(baseUrl+"/app/rest/documents/delete/"+crossId, function(data) {
                bootbox.hideAll();
                if (data.result=='OK') {
                    for (var t=0;t<tpxp.length;t++){
                        if(tpxp[t].id==crossId){
                            tpxp.splice(t,1);
                            buildFlowchartTable();
                            populateTpxp();
                        }
                    }
                }
                else bootbox.alert("Errore eliminazione!!!");
            });
        }
    });
    return false;
}

function addBudgetTpxp(crossId){
    showPriceForm(crossId);
    return false;
}

function editBudgetTpxp(crossId){
    showPriceForm(crossId);
    return false;
}
function changeRimbType(title, crossId){
    bootbox.prompt({
        title: title,
        inputType: 'select',
        inputOptions: [
            {
                text: 'Prestazioni aggiuntive rimborsate dal promotore',
                value: '0',
            },
            {
                text: 'Prestazioni routinarie ma nel caso specifico rimborsate dal promotore',
                value: '1',
            },
            {
                text: 'Prestazioni routinarie a carico SSN/SSR',
                value: '2',
            }
        ],
        callback: function (result) {
            if (result != null) {
                loadingScreen("salvataggio in corso");
                var postData = {};
                if (result==2){
                    for (var mdIdx in tpxpById[crossId].metadata){
                        if (mdIdx.startsWith('Costo'))
                        postData[mdIdx]='';
                    }
                }
                postData.Rimborso_Rimborsabilita = result;
                var url = baseUrl+"/app/rest/documents/update/"+crossId;
                $.post(url, postData).done(function (data) {
                    bootbox.hideAll();
                    if (data.result=='OK'){
                        $.getJSON(baseUrl+"/app/rest/documents/getElementJSON/"+data.ret, function(data) {
                            for (var t=0;t<tpxp.length;t++){
                                if(tpxp[t]!=null && tpxp[t].id==crossId){
                                    tpxp[t]=data;

                                    populateTpxp();
                                }
                            }
                        });
                    }else {
                        bootbox.alert('Errore: '+data.errorMessage);
                    }

                });
            }
        }
    });
    return false;
}


function addPrestazione() {
    var prestForm=$('#prestazione-diz-dialog').clone();
    prestForm.attr('id', 'prestFormId');
    prestForm.show();
    showPrestazioniForm("Aggiungi prestazione", prestForm, true);
}


function prestazioniFormInit(){
    if ($("#prestFormId #Prestazioni_prestazione").data('autocomplete')) {
        $("#prestFormId #Prestazioni_prestazione").autocomplete("destroy");
        $("#prestFormId #Prestazioni_prestazione").removeData('autocomplete');
    }

    var $that1=$( "#prestFormId #Prestazioni_prestazione" );
    $( "#prestFormId #Prestazioni_prestazione" ).autocomplete({
        minLength: 2,
        select: function( event, ui ) {
            $( "#prestFormId #Tariffario_SSN" ).val(ui.item.ssn);
            $(this).closest('form').find('.ssn_diz').html(' (Valore SSN: '+ui.item.ssn.formatMoney()+')');
            $( "#prestFormId #Tariffario_Solvente" ).val(ui.item.solvente);
            $( "#prestFormId #dizionario" ).val('1');
            var request={prestazione:$( "#Prestazioni_prestazione" ).val(),term:''};
            $(this).off('keypress').on('keypress',function(){
                $( "#prestFormId #dizionario" ).val('');
                hidebutton();
                if($(this).val()!=ui.item.value){
                    $( "#prestFormId #Prestazioni_CDC" ).val('');
                    $( "#prestFormId #Prestazioni_CDCSelect" ).find('option:selected').prop('selected',false);
                    $( "#prestFormId #Prestazioni_CDC" ).keypress();
                    $( "#prestFormId #Tariffario_SSN" ).val('');
                    $(this).closest('form').find('.ssn_diz').html('');
                    $( "#prestFormId #Tariffario_Solvente" ).val('');
                    $( "#prestFormId #dizionario" ).val('');
                    $(this).off('keypress');
                }
            });
        },
        source:function( request, response ) {
            $that1.next('i.icon-spinner').remove();
            $that1.after("<i class='icon-spinner icon-spin orange bigger-125' style='position:relative;left:6px' ></i>");
            var term = request.term;
            if ( term in cache ) {
                response( cache[ term ] );
                return;
            }
            $.getJSON( "/dizionari/prestazioni.php", request, function( data, status, xhr ) {
                cache[ term ] = data;
                response( data );
                $that1.next('i.icon-spinner').remove();
            });
        }
    });
    $( "#prestFormId #Prestazioni_prestazione" ).css('width', '352px');
    $( "#prestFormId #Prestazioni_prestazione" ).change(function(){
        var request={prestazione:$( "#prestFormId #Prestazioni_prestazione" ).val(),term:'',check:'1'};
    });
    $( "#prestFormId #Prestazioni_CDC" ).off('click').click(function(){
        $( this ).autocomplete('search','');
    });
    $( "#prestFormId #Prestazioni_CDC2" ).off('click').click(function(){
        $( this ).autocomplete('search','');
    });
    if ($("#prestFormId #Prestazioni_CDC").data('autocomplete')) {
        $("#prestFormId #Prestazioni_CDC").autocomplete("destroy");
        $("#prestFormId #Prestazioni_CDC").removeData('autocomplete');
    }
    var $that2=$( "#prestFormId #Prestazioni_CDC" );
    $( "#prestFormId #Prestazioni_CDC" ).autocomplete({
        minLength: 0,
        source:function( request, response ) {
            $that2.next('i.icon-spinner').remove();
            $that2.after("<i class='icon-spinner icon-spin orange bigger-125' style='position:relative;left:6px' ></i>");
            request.prestazione=$( "#Prestazioni_prestazione" ).val();
            $.getJSON( "/dizionari/prestazioni.php", request, function( data, status, xhr ) {
                response( data );
                $that2.next('i.icon-spinner').remove();
            });
        },
        select: function( event, ui ) {
        }
    });
    if ($("#prestFormId #Prestazioni_CDC2").data('autocomplete')) {
        $("#prestFormId #Prestazioni_CDC2").autocomplete("destroy");
        $("#prestFormId #Prestazioni_CDC2").removeData('autocomplete');
    }
    var $that3=$( "#prestFormId #Prestazioni_CDC2" );
    $( "#prestFormId #Prestazioni_CDC2" ).autocomplete({
        minLength: 0,
        source:function( request, response ) {
            $that3.next('i.icon-spinner').remove();
            $that3.after("<i class='icon-spinner icon-spin orange bigger-125' style='position:relative;left:6px' ></i>");
            request.prestazione=$( "#Prestazioni_prestazione" ).val();
            $.getJSON( "/dizionari/prestazioni.php", request, function( data, status, xhr ) {
                response( data );
                $that3.next('i.icon-spinner').remove();
            });
        },
        select: function( event, ui ) {
        }
    });
    $('#prestFormId #Prestazioni_CDCSelect').change(function(){
        var value=$(this).val();
        var hide=true;
        var item={};
        item['1']='RADIODIAGNOSTICA';
        item['2']='MEDICINA_NUCLEARE';
        item['3']='CARDIOLOGIA';
        item['4']='ANALISI_OI';
        item['5']='ANALISI_VM';
        item['6']='GENETICA_MEDICA';
        item['7']='ANATOMIA';
        item['8']='DIETETICA';
        item['9']='EMATOLOGIA';
        item['10']='MALATTIE_ET';
        item['11']='ANATOMIA';
        item['12']='ANATOMIA';
        item['13']='FARMACIA';
        item['17']='SERVIZIO_INFERMIERISTICO';
        if(value && value.match(/###/)){
            var splitVal=value.split('###');
            var codVal=splitVal[0];
            var decodVal=splitVal[1];
            var selectedItem=item[codVal];
            if(codVal=='9999'){
                $('#prestFormId #CDCSpecifica').find('input').each(function(){
                    var value=$(this).val();
                    if($('#Prestazioni_CDCSelect').find('option[value$="###'+value+'"]').size()>0){
                        $(this).val('');
                    }
                });
                $('#prestFormId #CDCSpecifica').show();
                $(this).closest('form').find('input#Prestazioni_UOC').val('');
                $(this).closest('form').find('input#Prestazioni_UOCCode').val('');
                $(this).closest('form').find('input#Prestazioni_CDCCode').val(codVal);
                hide=false;
            }else{
                if(selectedItem){
                    $(this).closest('form').find('input#Prestazioni_UOC').val(selectedItem);
                    $(this).closest('form').find('input#Prestazioni_UOCCode').val(selectedItem);
                }else{
                    $(this).closest('form').find('input#Prestazioni_UOC').val('');
                    $(this).closest('form').find('input#Prestazioni_UOCCode').val('');
                }
                $(this).closest('form').find('input#Prestazioni_CDCCode').val(codVal);
                $(this).closest('form').find('input#Prestazioni_CDC').val(decodVal);
            }
        }else{
            $('#prestFormId #CDCSpecifica').find('input').val('');
        }
        if(hide){
            $('#prestFormId #CDCSpecifica').hide();
        }
    });
    $('#prestFormId #Prestazioni_CDCSelect2').change(function(){
        var value=$(this).val();
        var hide=true;
        var item={};
        item['1']='RADIODIAGNOSTICA';
        item['2']='MEDICINA_NUCLEARE';
        item['3']='CARDIOLOGIA';
        item['4']='ANALISI_OI';
        item['5']='ANALISI_VM';
        item['6']='GENETICA_MEDICA';
        item['7']='ANATOMIA';
        item['8']='DIETETICA';
        item['9']='EMATOLOGIA';
        item['10']='MALATTIE_ET';
        item['11']='ANATOMIA';
        item['12']='ANATOMIA';
        item['13']='FARMACIA';
        item['17']='SERVIZIO_INFERMIERISTICO';
        if(value && value.match(/###/)){
            var splitVal=value.split('###');
            var codVal=splitVal[0];
            var decodVal=splitVal[1];
            var selectedItem=item[codVal];
            if(codVal=='9999'){
                $('#prestFormId #CDCSpecifica2').find('input').each(function(){
                    var value=$(this).val();
                    if($('#Prestazioni_CDCSelect2').find('option[value$="###'+value+'"]').size()>0){
                        $(this).val('');
                    }
                });
                $('#prestFormId #CDCSpecifica2').show();
                $(this).closest('form').find('input#Prestazioni_UOC2').val('');
                $(this).closest('form').find('input#Prestazioni_UOCCode2').val('');
                $(this).closest('form').find('input#Prestazioni_CDCCode2').val(codVal);
                hide=false;
            }else{
                if(selectedItem){
                    $(this).closest('form').find('input#Prestazioni_UOC2').val(selectedItem);
                    $(this).closest('form').find('input#Prestazioni_UOCCode2').val(selectedItem);
                }else{
                    $(this).closest('form').find('input#Prestazioni_UOC2').val('');
                    $(this).closest('form').find('input#Prestazioni_UOCCode2').val('');
                }
                $(this).closest('form').find('input#Prestazioni_CDCCode2').val(codVal);
                $(this).closest('form').find('input#Prestazioni_CDC2').val(decodVal);
            }
        }else{
            $('#prestFormId #CDCSpecifica2').find('input').val('');
        }
        if(hide){
            $('#prestFormId #CDCSpecifica2').hide();
        }
    });
    $('#prestFormId #Prestazioni_prestazione').change(
        hidebutton
    ).keypress(hidebutton);
    $('#prestFormId #Prestazioni_CDC').change(
        hidebutton
    ).keypress(hidebutton);
    $('#prestFormId #Prestazioni_Altro').hide();
}


var hidebutton=function(){
    if($("#prestFormId #dizionario").val()){
        $('#prestFormId #Prestazioni_Altro').hide();
    }
    else{
        $('#prestFormId #Prestazioni_Altro').show();
    }

};


function createTpxp(prestazioneId, timepointId){
    loadingScreen("salvataggio in corso");
    var url=baseUrl + "/app/rest/documents/save/tpxp"
    var postData={};
    postData.parentId=folderTpxpId;
    postData['tp-p_Prestazione']=prestazioneId;
    postData['tp-p_TimePoint']=timepointId;
    postData['tp-p_Checked']=1;
    postData['Rimborso_Rimborsabilita']=0;
    $.post(url, postData).done(function(data){
        bootbox.hideAll(); 
        if (data.result=='OK') {
            $.getJSON(baseUrl + "/app/rest/documents/getElementJSON/" + data.ret, function (data) {
                tpxp[tpxp.length]=data;
                tpxpById[data.id]=data;
                //changeRimbType('Selezione regime di rimborsabilit&agrave;', data.id);
                populateTpxp();
            });
        }else {
            bootbox.alert('Errore salvataggio');
        }
    });
}


function showPriceForm(elId) {
    var myElement=null;
    for (var i=0;i<tpxp.length;i++){
        if (elId==tpxp[i].id) myElement=tpxp[i];
    }
    (function(myElement){
        $("#dialog-form-transfer").off('dialogopen').on('dialogopen', function(ev) {
            var width = $(window).width() / 100 * 80;
            var height = $(window).height() / 100 * 80;
            $(this).dialog('option', {
                height: height
            });
            ev = ev ? ev : window.event;
            var that = this;
            if (!myElement) {
                myElement = $.extend(true, {}, emptytpxp);
                myElement.metadata['Costo_MarkupUnita'] = 2;
            }
            $(this).find('input').each(function(){
                tel=$(this);
                if (myElement.metadata[tel.attr('name')] && myElement.metadata[tel.attr('name')][0]) {
                    tel.val(myElement.metadata[tel.attr('name')][0]);
                }else {
                    tel.val('');
                }
            });

            if(myElement.metadata['Costo_Copertura']!=undefined && myElement.metadata['Costo_Copertura']!=""){
                $(that).find('[name=Costo_Copertura]').val(myElement.metadata['Costo_Copertura']).change();
            }
            else{ //se è blu e la copertura non è stata selezionata, allora la metto di default 4###D: a carico del promotore profit
                if(myElement.metadata['Rimborso_Rimborsabilita'][0]=="0")
                $(that).find('[name=Costo_Copertura]').val("4###D: a carico del promotore profit").change();
            }



            $(this).find('input[id^=costo]').focus();
            var setTransfer = function() {
                if ($(that).find('select[id^=unita-markup]').val() == 2) {
                    var costo = parseFloat($(that).find('input[id^=costo]').val() - 0);
                    var aggiunta = costo * parseFloat($(that).find('input[id^=markup]').val() - 0) / 100;
                    var value = costo + aggiunta;
                } else {
                    var value = parseFloat($(that).find('input[id^=costo]').val() - 0) + parseFloat($(that).find('input[id^=markup]').val() - 0);
                }
                $(that).find('input[id^=transfer]').val(value);
            };
            var setMarkup = function() {
                if ($(that).find('input[id^=transfer]').val() > 0 && $(that).find('input[id^=costo]').val() > 0) {
                    $(that).find('select[id^=unita-markup]').val(1);
                    var value = parseFloat($(that).find('input[id^=transfer]').val()) - parseFloat($(that).find('input[id^=costo]').val());
                    $(that).find('input[id^=markup]').val(value);
                }
            };
            var myPrestazioneGuid = myElement.metadata['tp-p_Prestazione'][0].id;
            var myPrestazioneLabel = myElement.metadata['tp-p_Prestazione'][0].titleString;
            var myVisitGuid = myElement.metadata['tp-p_TimePoint'][0].id;
            var myVisitLabel = myElement.metadata['tp-p_TimePoint'][0].titleString;

            $("#dialog-form-transfer").prev('.ui-dialog-titlebar').find('.ui-dialog-title').html(myPrestazioneLabel + " - " + myVisitLabel);
            var myPrestazione = myElement.metadata['tp-p_Prestazione'][0];
            var valoreSSN, valoreSolvente, valoreAlpi;
            if ($.isPlainObject(myPrestazione)) {
                valoreSSN = getDato(myPrestazione.metadata['Tariffario_SSN']);
                valoreSolvente = getDato(myPrestazione.metadata['Tariffario_Solvente']);
                valoreAlpi = getDato(myPrestazione.metadata['Tariffario_ALPI']);
            }
            if (valoreSSN) {
                $(that).find('#valoreSSN').html(valoreSSN);
                $(that).find('#tariffaSSN').show();
            } else {
                $(that).find('#valoreSSN').html('');
                $(that).find('#tariffaSSN').hide();
            }
            if (valoreSolvente) {
                $(that).find('#valoreSolvente').html(valoreSolvente);
                $(that).find('#tariffaSolvente').show();
            } else {
                $(that).find('#valoreSolvente').html('');
                $(that).find('#tariffaSolvente').hide();
            }
            if (valoreAlpi) {
                $(that).find('#valoreAlpi').html(valoreAlpi);
                $(that).find('#tariffaAlpi').show();
            } else {
                $(that).find('#valoreAlpi').html('');
                $(that).find('#tariffaAlpi').hide();
            }
            $(this).find('input[id^=costo]').off('change').on('change', setTransfer);
            $(this).find('input[id^=markup]').off('change').on('change', setTransfer);
            $(this).find('select[id^=unita-markup]').off('change').on('change', setTransfer);
            $(this).find('input[id^=transfer]').off('change').on('change', setMarkup);
            $(this).parent().find('button:contains(Aggiungi)').off('click').on('click', function() {
                var numeric;

                if ($(that).find('[name=Costo_Copertura]').val()== '') {
                    //updateTips('Copertura del costo obbligatorio.');
                    bootbox.alert('Campo obbligatorio "Copertura del costo"');
                    return false;
                }
                numeric = $(that).find('[name=Costo_TransferPrice]').val();
                if (numeric=="") {
                    //updateTips('Transfer Price obbligatorio.');
                    bootbox.alert('Campo obbligatorio "Transfer Price"');
                    return false;
                }
                if (numeric != '' && isNaN(parseFloat(numeric))) {
                    bootbox.alert('Attenzione inserire un valore numerico nel campo "Transfer price"');
                    return false;
                }

                var newValue = '';
                var postUrl=baseUrl+"/app/rest/documents/update/"+myElement.id;
                loadingScreen("salvataggio in corso");
                $.post(postUrl, $(that).find('form').serialize()).done(function(data){
                    if (data.result!='OK'){
                        bootbox.hideAll();
                        bootbox.alert('Attenzione!!! Errore nel salvataggio della prestazione');
                    }else {
                        $.getJSON(baseUrl+"/app/rest/documents/getElementJSON/"+data.ret, function(data) {
                            for (var i=0;i<tpxp.length;i++){
                                if (data.id==tpxp[i].id) tpxp[i]=data;
                            }
                            buildFlowchartTable();
                        });
                        bootbox.hideAll();
                    }
                });
                $("#dialog-form-transfer").dialog('close');
            });
            $(this).parent().find('button:contains(Applica)').off('click').on('click', function() {
                var numeric;

                if ($(that).find('[name=Costo_Copertura]').val()== '') {
                    //updateTips('Copertura del costo obbligatorio.');
                    bootbox.alert('Campo obbligatorio "Copertura del costo"');
                    return false;
                }
                numeric = $(that).find('[name=Costo_TransferPrice]').val();
                if (numeric=="") {
                    //updateTips('Transfer Price obbligatorio.');
                    bootbox.alert('Campo obbligatorio "Transfer Price"');
                    return false;
                }
                if (numeric != '' && isNaN(parseFloat(numeric))) {
                    bootbox.alert('Attenzione inserire un valore numerico nel campo "Transfer price"');
                    return false;
                }

                loadingScreen("salvataggio in corso");
                costiRigaAjax=0;
                costiRigaRaiseError=false;
                for (var i=0;i<tpxp.length;i++) {
                    if (tpxp[i].metadata['tp-p_Prestazione'][0]!=undefined && tpxp[i].metadata['tp-p_Prestazione'][0].id==myElement.metadata['tp-p_Prestazione'][0].id){
                        costiRigaAjax++;
                        var postUrl=baseUrl+"/app/rest/documents/update/"+tpxp[i].id;
                        $.post(postUrl, $(that).find('form').serialize()).done(function(data){
                            if (data.result!='OK'){
                                costiRigaRaiseError=true;
                            }else {
                                $.getJSON(baseUrl+"/app/rest/documents/getElementJSON/"+data.ret, function(data) {
                                    for (var i=0;i<tpxp.length;i++){
                                        if (data.id==tpxp[i].id) tpxp[i]=data;
                                    }
                                    costiRigaAppliedCallBack();
                                });
                            }
                        });
                    }
                }

                $("#dialog-form-transfer").dialog('close');
            });
        });
        $("#dialog-form-transfer").dialog("open");
        return false;
    })(myElement);
    return false;

}

var costiRigaAjax=0;
var costiRigaRaiseError=false;
function costiRigaAppliedCallBack(){
    costiRigaAjax--;
    if (costiRigaAjax==0) {
        if (costiRigaRaiseError){
            bootbox.hideAll();
            bootbox.alert('Attenzione!!! Errore nel salvataggio della prestazione');
        }else {
            buildFlowchartTable();
            bootbox.hideAll();
        }
    }
}

function getDato(mdDato){
    if (mdDato && mdDato[0]) return mdDato[0];
    else return null;
}
var applicaSSNajax=0;
function applicaSSN(){
    loadingScreen("salvataggio in corso");
    costiRigaAjax = 0;
    costiRigaRaiseError = false;
    for (var i = 0; i < tpxp.length; i++) {
        if (tpxp[i].metadata['tp-p_Prestazione'][0] != undefined && tpxp[i].metadata['tp-p_Prestazione'][0].metadata['Tariffario_SSN'] != "") {
            costiRigaAjax++;
            var postUrl = baseUrl + "/app/rest/documents/update/" + tpxp[i].id;
            var postData= new Object();
            postData['Costo_Markup'] = "";
            postData['Costo_MarkupUnita'] = "";
            var tariffa=tpxp[i].metadata['tp-p_Prestazione'][0].metadata['Tariffario_SSN'][0];
            postData['Costo_Costo'] = tariffa.replace(/,/,'.');
            postData['Costo_TransferPrice'] = postData['Costo_Costo'];


            applicaSSNajax++;
            $.post(postUrl,postData).done(function (data) {
                if (data.result != 'OK') {
                    costiRigaRaiseError = true;
                } else {
                    $.getJSON(baseUrl + "/app/rest/documents/getElementJSON/" + data.ret, function (data) {
                        for (var i = 0; i < tpxp.length; i++) {
                            if (data.id == tpxp[i].id) tpxp[i] = data;
                        }
                        applicaSSNajax--;
                        if(applicaSSNajax==0){
                            if (costiRigaRaiseError){
                                bootbox.hideAll();
                                bootbox.alert('Attenzione!!! Errore nel salvataggio della prestazione');
                            }else {
                                buildFlowchartTable();
                                bootbox.hideAll();
                            }
                        }
                    });
                }
            });
        }
    }
}