
<#if (model['element']?? && model['docDefinition']??)>
	<#assign el=model['element']/>
	<#assign elType=model['docDefinition']/>
	<#assign infoPanel="right">
	<#assign userPolicy=el.getUserPolicy(userDetails)/>
	<#assign editable=false/>
	<#if userPolicy.canUpdate && !el.locked>
	    <#assign editable=true/>
	</#if>
	<#if userPolicy.canUpdate && el.locked && el.lockedFromUser==userDetails.username>
	    <#assign editable=true/>
	</#if>
<#assign selectedTemplate=""/>
<#assign templates={}/>
<#if userPolicy.ftlTemplates??>
<#list userPolicy.ftlTemplates as template>
	<#assign templates=templates+{template:getLabel(el.type.typeId+".ftl."+template)}/>
</#list>
</#if>
<#if el.type.ftlDetailTemplate?? && el.type.ftlDetailTemplate!="">
	<#assign templates=templates+{el.type.ftlDetailTemplate:getLabel(el.type.typeId+".ftl."+el.type.ftlDetailTemplate)}/>
</#if>


<#if model['cookies']??>
	<#assign keys = model['cookies']?keys>
    <#list keys as key>
    <#if key=="ftlTemplate">
    	<#assign selectedTemplate=model['cookies'][key]/>	
    </#if>
    </#list>
</#if>



<#if !mainContent?contains("documents/custom/") > 
<#if templates?? && templates?size gt 0>
	<#if templates?size gt 1>
		<form id="t-form" method="GET" style="float:right">
		<@selectHash "t" "t" "Visione" templates selectedTemplate/>
		</form>
		<#if selectedTemplate!="">
		<#attempt>
		<#include selectedTemplate+".js.ftl"/>
		<#recover>
		<#include "elementSpecific.js.ftl"/>
		</#attempt>
		</#if>
		<#else>
			<#assign keys = templates?keys>
		    <#list keys as key>
		    	<#assign selectedTemplate=key/>	
		    	<#attempt>
		    	
		    	<#include key+".js.ftl"/>
		    	<#recover>
		    	
		    	<#include "elementSpecific.js.ftl"/>
		    	</#attempt>
		
		    </#list>
	</#if>
    
<#else>
    <#include "elementSpecific.js.ftl"/>
</#if>
</#if>
</#if>
