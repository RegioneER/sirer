<#assign type=model['docDefinition']/>
<#global page={
"content": path.pages+"/"+mainContent,
"styles" : ["jquery-ui-full", "datepicker","pages/studio.css","x-editable"],
"scripts" : ["jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable"],
"inline_scripts":[],
"title" : "Dettaglio scheda monitoraggio clinico",
"description" : "Dettaglio scheda monitoraggio clinico"
} />
<#assign elStudio=el.getParent().getParent() />
<#include "../../partials/navigation/navigazione_studio.ftl">
<#include "../../partials/form-elements/elementSpecific.ftl">
<#include "../../partials/form-elements/select.ftl" />
<#assign loadedJson=el.getElementCoreJsonToString(userDetails) />
<@breadcrumbsData el />

<@script>
var loadedElement=${loadedJson};
var sidebarDefault="${el.getParent().getId()}#MonitoraggioClinico-tab2";


$( document ).ready(function() {
    $("#DatiMonitoraggioClinico-DatiMonitoraggioClinico_dataRiferimentoDa div.col-sm-3").removeClass("col-sm-3").addClass("col-sm-9");
    $("#DatiMonitoraggioClinico-DatiMonitoraggioClinico_dataRiferimentoA div.col-sm-3").removeClass("col-sm-3").addClass("col-sm-9");
    $("#DatiMonitoraggioClinico-DatiMonitoraggioClinico_dataRelazione div.col-sm-3").removeClass("col-sm-3").addClass("col-sm-9");
});

</@script>
