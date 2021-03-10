<#assign type=model['docDefinition']/>
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["jquery-ui-full", "datepicker","pages/studio.css","x-editable","select2"],
	"scripts" : ["jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable","select2","base"],
	"inline_scripts":[],
	"title" : "Dettaglio allegato",
 	"description" : "Dettaglio allegato" 
} />
<@breadcrumbsData el />
<#assign json=el.type.getDummyJson() />
<#assign loadedJson=el.getElementCoreJsonToString(userDetails) />
<@script>
	$.fn.editable.defaults.mode = 'inline';
	var loadedElement=${loadedJson};
 	var dummy=${json};
 	var empties=new Array();
 	empties[dummy.type.id]=dummy;
</@script>