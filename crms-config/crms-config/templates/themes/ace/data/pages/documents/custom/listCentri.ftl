<#global page={
	"content": path.pages+"/"+mainContent,
	"styles" : ["select2","jquery-ui-full", "datepicker", "jqgrid","daterangepicker"],
	"scripts" : ["select2","jquery-ui-full","bootbox" ,"datepicker", "daterangepicker", "jqgrid","pages/home.js","common/elementEdit.js", "chosen" , "spinner" , "datepicker" , "timepicker" , "daterangepicker" , "colorpicker" , "knob" , "autosize", "inputlimiter", "maskedinput", "tag", "tokenInput"],
	"inline_scripts":[],
	"title" : "Ricerca Avanzata",
 	"description" : "Dynamic tables and grids using jqGrid plugin",
 	"end":true 
} />
<#assign lista=""/>
<#list model['element'].getChildrenByType('Centro') as centro >
	<#assign lista>${lista}<#if lista!="">,</#if>"${centro.getFieldDataDecode("IdCentro","PINomeCognome")}"</#assign>
</#list>
[${lista}]