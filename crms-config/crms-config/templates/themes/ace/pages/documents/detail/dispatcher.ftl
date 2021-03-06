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

<#assign selectedTemplate=""/>
<#if model['cookies']??>
	<#assign keys = model['cookies']?keys>
    <#list keys as key>
    <#if key=="ftlTemplate">
    	<#assign selectedTemplate=model['cookies'][key]/>	
    </#if>
    </#list>
</#if>


<#if templates?? && templates?size gt 0>
	
	<#if templates?size gt 1>
		<#if selectedTemplate!="">	
			<#global mainContent=selectedTemplate+".ftl" />
			<#else>
			<#assign keys = templates?keys>
		    <#list keys as key>
		    	<#assign selectedTemplate=key/>	
		    	<#global mainContent=key+".ftl"/>
		    </#list>
		</#if>
	<#else>
		<#assign keys = templates?keys>
	    <#list keys as key>
	    	<#assign selectedTemplate=key/>	
	    	<#global mainContent=key+".ftl"/>
	    </#list>
	</#if>
<#else>
    <#if elType.container>
    <#global mainContent="container.ftl"/>
    <#else>
        <#global mainContent="default.ftl"/>
    </#if>
</#if>
<#assign mainContent="documents/detail/"+mainContent />