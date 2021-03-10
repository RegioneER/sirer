<#assign el=model['element'] />
<#assign type=model['docDefinition']/>
<@breadcrumbsData el />
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["jquery-ui-full", "datepicker","pages/studio.css","x-editable","pace","handsontable"],
	"scripts" : ["jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable","handsontable","pace","kinetic","budget","base"],
	"inline_scripts":[],
	"title" : "Confronto",
 	"description" : "Confronto" 
} />

<#assign elStudio=el.getParent().getParent() />
<#include "../../partials/navigation/navigazione_studio.ftl">
<#include "../detail/budget/common/style.ftl"/>  