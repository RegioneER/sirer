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
var height=$(window).height()-180;
var height2=$('#sidebar').height()-90;
$('#fullHeightContainer').css('height', height+'px');
$('#fullHeightContainer').css('width', '100%');
$('#fullHeightContainer').css('border', 'none');
function frameSize(){
	height=$(window).height()-180;
	height2=$('#sidebar').height()-90;
	if(height2>height){
		$('#fullHeightContainer').css('height', height2+'px');
	}else{
		$('#fullHeightContainer').css('height', height+'px');
	}
}
$(window).resize(function(){
	frameSize();
});
$('#sidebar').find('a').click(function(){
	setTimeout(frameSize,300);
});
frameSize();
setTimeout(frameSize,100);
</@script>
