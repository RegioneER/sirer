<#assign type=model['docDefinition']/>
<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["jquery-ui-full", "datepicker","pages/report.css","x-editable"],
	"scripts" : ["jquery-ui-full","datepicker","bootbox", "token-input" ,"common/elementEdit.js","x-editable"],
	"inline_scripts":[],
	"title" : "Report",
 	"description" : "Report" 
} />
<#include "../../partials/form-elements/elementSpecific.ftl">
<#include "../../partials/form-elements/select.ftl" />
<@breadcrumbsData el />
<@reportBuilder el.getParent().getParent()/>
<#assign json=el.type.getDummyJson() />
<#assign loadedJson=el.getElementCoreJsonToString(userDetails) />

<@script>
height=$(window).height()-180;
$('#fullHeightContainer').css('height', height+'px');
$('#fullHeightContainer').css('width', '100%');
$('#fullHeightContainer').css('border', 'none');

$(window).resize(function(){
	height=$(window).height()-180;
	$('#fullHeightContainer').css('height', height+'px');
});

</@script>
