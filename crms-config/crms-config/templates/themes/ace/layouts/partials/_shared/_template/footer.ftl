<div id='centeredElement' style='position:fixed;top:50vh;left:50vw;z-index:-100;opacity:0'></div>
<#if page.footer?? >
<#list page.footer as append >
${append}
</#list>
</#if>


<script>
if(!console){var console={log:function(){return false;}};}
</script>
<script src="${path.custom.assets}/js/${page.layout}.js"></script>
<!-- page specific plugin scripts -->
<#--put IE only scripts here, currently we only use ExCanvas.js from time to time-->
<#if page.ie_scripts??>
	<#list page.ie_scripts as script >
	<!--[if lte IE ${script.version}]>
	  <script src="${path.assets}/js/${script.file_name}"></script>
	<![endif]-->
	</#list>
</#if>

<#if page.scripts??>
	<#list page.scripts as script>
		<#if scripts_map[script]??>
		<#list scripts_map[script] as subScript>
		<script src="${path.assets}/js/${subScript}"></script>
		</#list>
		</#if>
		<#if statics_map[script]?? >
		<#list statics_map[script] as subScript>
		<script src="${path.custom.static}/${subScript}"></script>	
		</#list>
		</#if>
		<#if scripts_custom_map[script]??>
		<#list scripts_custom_map[script] as subScript>
		<script src="${path.custom.assets}/js/${subScript}"></script>
		</#list>
		</#if>
		<#if !scripts_map[script]?? && !statics_map[script]?? && !scripts_custom_map[script]?? >
		<script src="${path.custom.assets}/js/${script}"></script>	
		</#if>
	</#list>
</#if>

<!-- ace scripts -->
<script src="${path.assets}/js/ace-elements.min.js"></script>
<script src="${path.assets}/js/ace.min.js"></script>


<!-- inline scripts related to this page -->
<script type="text/javascript">
var baseUrl="${baseUrl}";
var messages;
$.getJSON(baseUrl+'/app/rest/documents/messages', function(data){
    messages=data.resultMap;
});

var emendamentoId = ${userDetails.getEmeSessionId()!0};
var elementInEmendamento = false;
<#if el?? && el.getInEmendamento()?? && el.getInEmendamento() >
	elementInEmendamento = true;
</#if>

var rootElemendId = ${userDetails.getEmeRootElementId()!0};


if ($.fn.editable) {
    $.fn.editable.defaults.mode = 'inline';
}
<#if page.inline_scripts?? >
<#list page.inline_scripts as inline_script >
${inline_script}
</#list>
</#if>
</script>