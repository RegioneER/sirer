
<#global page={
"content": path.pages+"/"+mainContent,
"styles" : ["select2","jquery-ui-full", "datepicker", "jqgrid"],
"scripts" : [ "select2","jquery-ui-full","bootbox" ,"datepicker", "jqgrid","pages/home.js","common/elementEdit.js", "chosen" , "spinner" , "datepicker" , "timepicker" , "daterangepicker" , "colorpicker" , "knob" , "autosize", "inputlimiter", "maskedinput", "tag"],
"inline_scripts":[],
"title" : "Lista",
"description" : "Lista"
} />

<#global breadcrumbs=
{
"title":"Lista oggetti",
"links":[]
}
/>
<@script>

$.getJSON('${baseUrl}/app/rest/dm/get/details/${model['dmsession'].id}',function(data){ //carico tutti i dettagli della sessione corrente
if(data.result=='OK'){
console.log(data);
var dmSession=data.resultMap.DM_SESSION;
for (var elementId in dmSession.elements) { //per ogni elemento modificato in sessione creo una tab
var element=dmSession.elements[elementId];
var myNavTabHtml='<li><a data-toggle="tab" href="#EL_'+elementId+'">'+element.titleString+'</a></li>';

$('#templatesNavTab').append(myNavTabHtml);

var myTabContentHtml=$('<div id="EL_'+elementId+'" class="tab-pane"></div>');

var my_table_elementActions=$('<table class="table table-bordered" id="TB_ELEMENT_'+elementId+'"> '+ //ed una tabella
    '    <thead> '+
    '        <tr><th>Tipo Modifica</th><th>Data di Modifica</th><th>Nome Campo</th><th>Tipo Campo</th><th>Vecchio Valore (CODE)</th><th>Vecchio Valore (DECODE)</th><th>Nuovo Valore (CODE)</th><th>Nuovo Valore (DECODE)</th><th>Dettagli</th></tr> '+
    '    </thead> '+
    '    <tbody> '+
    '    </tbody> '+
    '</table>');
var table_displayed_elementActions=false;
var my_table_processes=$('<table class="table table-bordered" id="TB_PROCESSES_'+elementId+'"> '+ //ed una tabella
    '    <thead> '+
    '        <tr><th>Tipo Modifica</th><th>Data di Modifica</th><th>Dettagli</th></tr> '+
    '    </thead> '+
    '    <tbody> '+
    '    </tbody> '+
    '</table>');
var table_displayed_processes=false;
var my_table_childs=$('<table class="table table-bordered" id="TB_CHILDS_'+elementId+'"> '+ //ed una tabella
    '    <thead> '+
    '        <tr><th>Tipo Modifica</th><th>Data di Creazione Figlio</th><th>Dettagli</th></tr> '+
    '    </thead> '+
    '    <tbody> '+
    '    </tbody> '+
    '</table>');
var table_displayed_childs=false;
for(i=0; i<dmSession.elementActions[elementId].length;i++){ //per ogni azione eseguita sull'elemento inserisco una riga in tabella

action=dmSession.elementActions[elementId][i].action;
if(dmSession.elementActions[elementId][i].actionMdAudit!=null){ //se ho modifiche ai campi
if(!table_displayed_elementActions){
myTabContentHtml.append(my_table_elementActions);
table_displayed_elementActions=!table_displayed_elementActions;
}
actionMdAudit=dmSession.elementActions[elementId][i].actionMdAudit[0];

var myHtmlActionTR=$("<tr></tr>");
myHtmlActionTR.attr("data-id",elementId+"_"+actionMdAudit.fieldId);

var myHtmlActionTD=$("<td></td>");

//TIPO MODIFICA
myHtmlActionTD.append(action.action);
myHtmlActionTR.append(myHtmlActionTD);

//DATA MODIFICA
myHtmlActionTD=$("<td></td>");
var my_date=new Date(action.actionDt);
var date=('0'+my_date.getDate()).slice(-2)+'/'+('0'+(my_date.getMonth()+1)).slice(-2)+'/'+ my_date.getFullYear()+' '+('0'+my_date.getHours()).slice(-2)+':'+('0'+my_date.getMinutes()).slice(-2)+':'+('0'+my_date.getSeconds()).slice(-2) ;
myHtmlActionTD.append(date);
myHtmlActionTR.append(myHtmlActionTD);

//NOME CAMPO

var nome_campo=actionMdAudit.templateName+"_"+actionMdAudit.fieldName;
var label_campo=dmSession.fieldLabels[nome_campo];
myHtmlActionTD=$("<td></td>");
myHtmlActionTD.append(label_campo);
myHtmlActionTR.append(myHtmlActionTD);


//TIPO CAMPO

var tipo_campo=dmSession.fieldTypes[nome_campo];
myHtmlActionTD=$("<td></td>");
myHtmlActionTD.append(tipo_campo);
myHtmlActionTR.append(myHtmlActionTD);

//VECCHIO VALORE (CODE)
var vecchio_valore=actionMdAudit.oldVals[0];
myHtmlActionTD=$("<td></td>");
if(tipo_campo=='CHECKBOX' || tipo_campo=='RADIO' || tipo_campo=='SELECT'){
vecchio_valore=vecchio_valore!=null ? vecchio_valore.split('###')[0] : vecchio_valore;
}
else
{
vecchio_valore=null;
}
myHtmlActionTD.append(vecchio_valore);
myHtmlActionTR.append(myHtmlActionTD);


//VECCHIO VALORE (DECODE)
var vecchio_valore=actionMdAudit.oldVals[0];
if(tipo_campo=='CHECKBOX' || tipo_campo=='RADIO' || tipo_campo=='SELECT'){
vecchio_valore=vecchio_valore!=null ? vecchio_valore.split('###')[1] : vecchio_valore;
}
if(tipo_campo=='DATE'){
my_date=new Date(vecchio_valore);
vecchio_valore=('0'+my_date.getDate()).slice(-2)+'/'+('0'+(my_date.getMonth()+1)).slice(-2)+'/'+ my_date.getFullYear() ;
}
myHtmlActionTD=$("<td></td>");
myHtmlActionTD.append(vecchio_valore);
myHtmlActionTR.append(myHtmlActionTD);

//NUOVO VALORE (CODE)
var nuovo_valore=actionMdAudit.newVals[0];
myHtmlActionTD=$("<td></td>");
if(tipo_campo=='CHECKBOX' || tipo_campo=='RADIO' || tipo_campo=='SELECT'){
nuovo_valore=nuovo_valore!=null ? nuovo_valore.split('###')[0] : nuovo_valore;
}
else{
nuovo_valore=null;
}
myHtmlActionTD.append(nuovo_valore);
myHtmlActionTR.append(myHtmlActionTD);

//NUOVO VALORE (DECODE)
var nuovo_valore=actionMdAudit.newVals[0];
if(tipo_campo=='CHECKBOX' || tipo_campo=='RADIO' || tipo_campo=='SELECT'){
nuovo_valore=nuovo_valore!=null ? nuovo_valore.split('###')[1] : nuovo_valore;
}
if(tipo_campo=='DATE'){
my_date=new Date(nuovo_valore);
nuovo_valore=('0'+my_date.getDate()).slice(-2)+'/'+('0'+(my_date.getMonth()+1)).slice(-2)+'/'+ my_date.getFullYear();
}
myHtmlActionTD=$("<td></td>");
myHtmlActionTD.append(nuovo_valore);
myHtmlActionTR.append(myHtmlActionTD);



//per mettere in ordine le modifiche dalla più recente anche rispetto al campo controllo che non sia già stato inserito
if(my_table_elementActions.find("[data-id='"+elementId+"_"+actionMdAudit.fieldId+"']")[0]===undefined){
myHtmlActionTD=$("<td></td>");//bottone per visualizzare le modifiche precedenti INIZIALMENTE VUOTO
myHtmlActionTR.append(myHtmlActionTD);
my_table_elementActions.append(myHtmlActionTR); //se non è già stato inserito lo appendo alla table
}
else{
$(myHtmlActionTR).toggleClass('hide');
$(myHtmlActionTR).css("background-color","lightgray");
myHtmlActionTD=$("<td></td>"); //bottone per visualizzare le modifiche precedenti INSERISCO ICONA PERCHE' ESISTONO MODIFICHE PRECEDENTI
my_table_elementActions.find("[data-id='"+elementId+"_"+actionMdAudit.fieldId+"']").first().find("td").last().html("<div class='action-buttons'> "+
    "<a title='Visualizza Dettagli Modifiche' class='green bigger-140 show-details-btn' href='#'> "+
        "    <i class='ace-icon fa fa-angle-double-down'></i> "+
        "   <span class='sr-only'>Visualizza Dettagli Modifiche</span> "+
        "</a> "+
    " </div>");
myHtmlActionTR.append(myHtmlActionTD);
my_table_elementActions.find("[data-id='"+elementId+"_"+actionMdAudit.fieldId+"']").last("tr").after(myHtmlActionTR); //se è già stato inserito lo inserisco dopo l'ultimo e lo nascondo
}
}
else{ //se non ho modifiche ai campi (allora forse sono in un processo)
console.log(action);
if(!table_displayed_processes){
myTabContentHtml.append(my_table_processes);
table_displayed_processes=!table_displayed_processes;
}

var myHtmlProcessTR=$("<tr></tr>");
myHtmlProcessTR.attr("data-id",elementId+"_"+action.action);

var myHtmlProcessTD=$("<td></td>");

//TIPO MODIFICA
myHtmlProcessTD.append(action.action);
myHtmlProcessTR.append(myHtmlProcessTD);


//DATA MODIFICA
var my_date=new Date(action.actionDt);
var date=('0'+my_date.getDate()).slice(-2)+'/'+('0'+(my_date.getMonth()+1)).slice(-2)+'/'+ my_date.getFullYear()+' '+('0'+my_date.getHours()).slice(-2)+':'+('0'+my_date.getMinutes()).slice(-2)+':'+('0'+my_date.getSeconds()).slice(-2) ;
myHtmlProcessTD=$("<td></td>");
myHtmlProcessTD.append(date);
myHtmlProcessTR.append(myHtmlProcessTD);


//DATA MODIFICA
myHtmlProcessTD=$("<td></td>");
myHtmlProcessTD.append(action.specification);
myHtmlProcessTR.append(myHtmlProcessTD);
my_table_processes.append(myHtmlProcessTR);
}
}

$('#templatesTabContent').append(myTabContentHtml);

}
$('#templatesNavTab').find('li:first').addClass('active');
$('#templatesTabContent').find('div:first').addClass('active');

$('.show-details-btn').on('click', function(e) { // trigger sul click del bottone per visualizzazione ulteriori modifiche precedenti di ciascun campo
e.preventDefault();
$('tr[data-id="'+($(this).parent().closest('tr').attr("data-id")).toString()+'"]').toggleClass('hide');
$('tr[data-id="'+($(this).parent().closest('tr').attr("data-id")).toString()+'"]').first().toggleClass('hide');
$(this).find(".ace-icon").toggleClass('fa-angle-double-down').toggleClass('fa-angle-double-up');
});
}
else{
bootbox.alert("Sessione non presente");
}
});

/*
$('.dm-edit').click(function(){
console.log('dm-edit');
targetSpan=$("[data-name='"+$(this).attr('data-target')+"']");
targetSpan.attr('contentEditable',true);
targetSpan.addClass('dm-editable');
$(this).hide();
$(".dm-save[data-target='"+$(this).attr('data-target')+"']").show();
return false;
});
*/

$('[data-type="editable-fields"]').change(function(){
lEl=$('<i>');
    lEl.addClass('fa');
    lEl.addClass('fa-spinner');
    lEl.addClass('fa-spin');
    lEl.addClass('fa-fw');
    $('.status[data-ref="'+$(this).attr('data-name')+'"]').html(lEl);
    data=new Object();
    data[$(this).attr('data-name')]=$(this).val();
    attrVal=$(this).attr('data-name');
    $.post( "${baseUrl}/app/rest/dm/updateSession", data)
    .done(function( data ) {
    lEl=$('<i>');
    lEl.addClass('fa');
    lEl.addClass('fa-check');
    lEl.addClass('green');
    $('.status[data-ref="'+attrVal+'"]').html(lEl);
    });
    return false;
    });

    $('.dm-close').click(function(){
    $.post( "${baseUrl}/app/rest/dm/closeSession")
    .done(function( data ) {
    if (data.result=='OK'){
    window.location.href='${baseUrl}/app/documents/dm/session/'+data.ret;
    }
    });
    });
    $('.dm-batch').click(function(){
    loadingScreen("Aggiornamenti in corso ...");
    $.post( "${baseUrl}/app/rest/dm/updateMetadataFromTable/crpms_update_batch")
    .done(function( data ) {
    if (data.result=='OK'){
        window.location.href='${baseUrl}/app/documents/dm/session/';
    }
    });
    });

    $('#hide-dm').click(function(){
    $('.dm-status-bar-hidden').show();
    $('.dm-status-bar').hide();
    });

    $('#show-dm').click(function(){
    $('.dm-status-bar-hidden').hide();
    $('.dm-status-bar').show();
    });
</@script>


