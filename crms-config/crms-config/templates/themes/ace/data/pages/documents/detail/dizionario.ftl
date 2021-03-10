
<#assign type=model['docDefinition']/>
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["jquery-ui-full", "datepicker","pages/studio.css","x-editable"],
	"scripts" : ["jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable"],
	"inline_scripts":[],
	"title" : "Dizionario",
 	"description" : "Dizionario" 
} />
<#include "../../partials/form-elements/elementSpecific.ftl">
<#include "../../partials/form-elements/select.ftl" />
<@breadcrumbsData el />
<#assign json=el.type.getDummyJson() />
<#assign elementJson=model['element'].getElementCoreJsonToString(userDetails) />
<@script>
    var loadedElement=${elementJson};
    var dummy=${json};
 	var empties=new Array();
 	
 	empties[dummy.type.id]=dummy;
    
</@script>
