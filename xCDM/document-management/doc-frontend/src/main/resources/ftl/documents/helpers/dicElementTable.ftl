<fieldset id="child-box" class="child-box">
	<#if el.childs??>
	<#assign rowNum=4/>
	<#assign firstCycle=true/>
    <table class="pSchema-2">
    <#assign childrenPaged=el.getPagedChildren() />
    <#if childrenPaged??>
	<#list childrenPaged as element>
		<#if firstCycle>
		<tr>
			<#list element.type.enabledTemplates as template>
				<#list template.fields as field>
					<th><strong><@msg template.name+"."+field.name/></strong></th>	
				</#list>
			</#list>
			<th>&nbsp;</th>	
		</tr>
		<#assign firstCycle=false/>
		</#if>
		<tr>
			<#list element.type.enabledTemplates as template>
				<#list template.fields as field>
					<td><@printMetadata template.name+"."+field.name element/></td>	
				</#list>
			</#list>
			<#assign detailLink=baseUrl+"/app/documents/detail/"+element.id/>
			<td><a href="${detailLink}"><img src="${baseUrl}/int/images/AddMetadata.gif" width="14px"></a></td>
		</tr>
		<#assign rowNum=rowNum-1/>
	</#list>
	</#if>
	</table>
	<#assign numChilds=el.getNumChildren() />
	<#if numChilds?? && model['rpp']??>
	<#assign totalPages=(numChilds/model['rpp'])?ceiling/>
	<@pages totalPages model['page'] el.id/>
	</#if>
	</#if>
</fieldset>
