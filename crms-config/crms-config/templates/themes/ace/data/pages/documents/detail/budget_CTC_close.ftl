<#assign type=model['docDefinition']/>
<@breadcrumbsData el />
<#global page={
"content": path.pages+"/"+mainContent,
"styles" : ["fixed_table", "jquery-ui-full", "datepicker","pages/studio.css","x-editable","pace"],
"scripts" : ["fixed_table", "jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable","pace","kinetic","budget_refactored","base"],
"inline_scripts":[],
"title" : "Budget",
"description" : "Budget"
} />
<#assign elStudio=el.getParent().getParent() />
<#include "../../partials/navigation/navigazione_studio.ftl">
<#--include "../../partials/form-elements/select.ftl" /-->

<#include "budget/common/style.ftl"/>
<#include "budget/common/jsLibs.ftl"/>
<#include "budget/common/loadedJsons.ftl"/>

<@script>
var budgetCTC=false;
var budgetStatus="open";
$('#tab1').click(function(){
setTimeout(function(){buildFlowchartTable();}, 500);

});
</@script>