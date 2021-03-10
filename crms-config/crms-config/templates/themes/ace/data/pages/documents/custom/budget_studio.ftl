<#assign el=model['element'] />
<#assign type=model['docDefinition']/>
<@breadcrumbsData el />
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["jquery-ui-full", "datepicker","pages/studio.css","x-editable","pace","handsontable"],
	"scripts" : ["jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable","handsontable","pace","kinetic","budget","base"],
	"inline_scripts":[],
	"title" : "Budget",
 	"description" : "Budget" 
} />
<#assign elCentro=el.getParent().getParent().getParent() />
<#assign elStudio=elCentro.getParent() />
<#include "../../partials/navigation/navigazione_studio.ftl">
<#include "../detail/budget/common/style.ftl"/>  
<@script>
pazienti="${elCentro.getFieldDataString("Feasibility","NrPaz")}"-0;
</@script>