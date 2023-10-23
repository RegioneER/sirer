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
<@reportBuilder el/>

<#assign defaultReport=0/>
<#if el.childs??>
	<#assign breakList=false/>
	<#list el.childs as area>
		<#if area.childs??>	
			<#list area.childs as report>
				<#if report.getUserPolicy(userDetails).canBrowse>
					<#if defaultReport==0>
						<#assign defaultReport=report.id/>
					<#else>
						<#if report.getfieldData("report", "default")[0]?? && report.getfieldData("report", "default")[0]=="1###Si">
							<#assign breakList=true/>					
							<#assign defaultReport=report.id/>
						</#if>
					</#if>
					<#if breakList>
						<#break>
					</#if>
				</#if>
			</#list>
		</#if>
		<#if breakList>
			<#break>
		</#if>
	</#list>
</#if>

<@script>


$.getJSON("${baseUrl}/app/rest/documents/advancedSearch/report?report_default_eq=1", function( data ) {
	url='${baseUrl}/app/documents/detail/'+data[0].id;
	$('#fullHeightContainer').attr('src', data[0].metadata.report_url[0]);
	openSidebarByUrl(url);
});

height=$(window).height()-180;
$('#fullHeightContainer').css('height', height+'px');
$('#fullHeightContainer').css('width', '100%');
$('#fullHeightContainer').css('border', 'none');

$(window).resize(function(){
	height=$(window).height()-180;
	$('#fullHeightContainer').css('height', height+'px');
});

</@script>


