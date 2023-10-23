<#assign type=model['docDefinition']/>
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["jquery-ui-full", "datepicker","pages/studio.css","x-editable","select2"],
	"scripts" : ["jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable","select2","base"],
	"inline_scripts":[],
	"title" : "Dettaglio",
 	"description" : "Dettaglio" 
} />
<@breadcrumbsData el />
<#assign json=el.type.getDummyJson() />
<#assign loadedJson=el.getElementCoreJsonToString(userDetails) />
<#include "../../partials/form-elements/elementSpecific.ftl">
<@script>
	$.fn.editable.defaults.mode = 'inline';
	$('.field-inline-anchor').editable({
	    params: function(params) {
		    var metadata={};
		    metadata[params.name]=params.value
		   
		    return metadata;
	    },
	    emptytext :"Valore mancante"	
	});
 	var loadedElement=${loadedJson};
 	var dummy=${json};
 	var empties=new Array();
 	
 	empties[dummy.type.id]=dummy;


$("input").each(function(){
	$(this).attr("size","65");
});
</@script>
