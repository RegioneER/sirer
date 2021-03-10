<#assign type=model['docDefinition']/>
<#assign DepotFarmaco=model['element'] />
<#assign el= DepotFarmaco />
<#global page={
"content": path.pages+"/"+mainContent,
"styles" : ["jquery-ui-full", "datetimepicker","pages/studio.css","x-editable","select2","jqgrid"],
"scripts" : ["xCDM-modal","jquery-ui-full","datetimepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable","select2","base","jqgrid","pages/home.js"],
"inline_scripts":[],
"title" : "Gestione Documentale Magazzino ",
"description" : "Gestione Documentale Magazzino "
} />
<@breadcrumbsData el />
<#assign elStudio=el.getParent().getParent() />
<#include "../../partials/navigation/navigazione_studio.ftl">
<#assign json=el.type.getDummyJson() />
<#assign loadedJson=el.getElementCoreJsonToString(userDetails) />
<@script>

$(document).ready(function(){
caricaDoc('${el.id}');
});

function InitFarmacoDoc(object){
var form=object.getForm();
$(".radio").addClass("left");
if($("select[name=depotFarmacoDoc_tipoDoc]").val()=="-9999###Altro"){
$("div[data-field-ref=depotFarmacoDoc_tipoDocAltro]").show();
}
else{
$("input[name=depotFarmacoDoc_tipoDoc]").val("");
$("div[data-field-ref=depotFarmacoDoc_tipoDocAltro]").hide();
}

$("select[name=depotFarmacoDoc_tipoDoc]").change(function(){
if($(this).val()=="-9999###Altro"){
$("div[data-field-ref=depotFarmacoDoc_tipoDocAltro]").show();
}
else{
$("input[name=depotFarmacoDoc_tipoDocAltro]").val("");
$("div[data-field-ref=depotFarmacoDoc_tipoDocAltro]").hide();
}
});
}
function ChecksFarmacoDoc(object){
var form=object.getForm();
$(".radio").addClass("left");
if($("input[name=file]").val()==""){
bootbox.alert("Attenzione isogna allegare un file");
return false;
}
return true;
}
function SaveCallBackFarmacoDoc(object){
jQuery("#DepotFarmacoDoc-grid-table").trigger('reloadGrid');
}


var docForm=new xCDM_Modal(baseUrl, "DepotFarmacoDoc", InitFarmacoDoc, ChecksFarmacoDoc, SaveCallBackFarmacoDoc);

function addDocument(){
docForm.formByParentId('${el.id}');

}

function caricaDoc(DepotFarmacoId){
var grid_selector = "#DepotFarmacoDoc-grid-table";
var pager_selector = "#DepotFarmacoDoc-grid-pager";

var url=baseUrl+'/app/rest/documents/jqgrid/advancedSearch/DepotFarmacoDoc?parent_obj_id_eq='+DepotFarmacoId;
var colNames=['id','Tipo Documento','Descrizione Aggiuntiva','Operazione collegata','Data','Azioni'];
var colModel=[
{name:'id',index:'id',width:20,jsonmap:"id", sorttype:"int",firstsortorder:"desc",},
{name:'tipoDoc',index:'depotFarmacoDoc_tipoDoc', width:20, formatter:getDecode,jsonmap:"metadata.depotFarmacoDoc_tipoDoc"},
{name:'descrizioneAggiuntiva',index:'depotFarmacoDoc_descrizioneAggiuntiva',width:30,jsonmap:"metadata.depotFarmacoDoc_descrizioneAggiuntiva"},
{name:'operazioneCollegata',index:'depotFarmacoDoc_operazioneCollegata',width:30,formatter:getDecode, jsonmap:"metadata.depotFarmacoDoc_operazioneCollegata"},
{name:'dataDoc',index:'depotFarmacoDoc_dataDoc',formatter:formatDate,  width:40,jsonmap:"metadata.depotFarmacoDoc_dataDoc.0"},
{name:'azioni',index:'azioni', width:80, fixed:true, sortable:false, resize:false,formatter:'actions',formatoptions:{keys:true,delbutton:false,editbutton:false}}
];
var caption = "Lista documenti caricati";

setupGridSubGrid(grid_selector, pager_selector, url, colModel,colNames, caption);
//setupGridSubGrid(grid_selector, pager_selector, url, colModel,colNames, caption,sub_grid_url,sub_grid_colModel,sub_grid_colNames,false);
}

function updateActions(grid_selector){
if(grid_selector=="#DepotFarmacoDoc-grid-table"){
var iCol = getColumnIndexByName(grid_selector, 'azioni');
$(grid_selector).find(">tbody>tr.jqgrow>td:nth-child(" + (iCol + 1) + ")").each(function () {
var my_id = $(this).parent().prop('id');
//INSERISCO ACTION EDIT DOCUMENTO
var editLink=$('<a>');
    editLink.attr('href',baseUrl + '/app/documents/getAttach/' + my_id);
    editLink.attr('title','modifica');
    editLink.html('<i class="fa fa-download"></i>&nbsp;');
    $("<div>", {
        title: "Modifica",
        mouseover: function() {
        $(this).addClass('ui-state-hover');
        },
        mouseout: function() {
        $(this).removeClass('ui-state-hover');
        }
        })
        .css({"margin-right": "5px", float: "left", cursor: "pointer"})
        .addClass("ui-pg-div ui-inline-custom")
        .append(editLink)
        .prependTo($(this).children("div"));
        });
        }
        }
    </@script>
